#ifndef NMTOOLS_ARRAY_VIEW_MATMUL_HPP
#define NMTOOLS_ARRAY_VIEW_MATMUL_HPP

#include "nmtools/array/view/decorator.hpp"
#include "nmtools/array/index/broadcast_shape.hpp"
#include "nmtools/array/index/product.hpp"
#include "nmtools/array/ndarray/hybrid.hpp"
#include "nmtools/array/view/ufunc.hpp"
#include "nmtools/array/view/ufuncs/add.hpp"
#include "nmtools/array/view/ufuncs/multiply.hpp"
#include "nmtools/array/at.hpp"
#include "nmtools/meta.hpp"

namespace nmtools::view::detail
{
    // special tag to resolve shape_matmul return type
    struct shape_matmul_t {};

    // special tag to resolve index array splitting
    struct split_index_t {};

    /**
     * @brief Split an index array to two parts at index N.
     * 
     * @tparam shape_t 
     * @param shape 
     * @param N 
     * @return constexpr auto 
     */
    template <typename shape_t, typename index_t>
    constexpr auto split(const shape_t& shape, index_t N)
    {
        using result_t = meta::resolve_optype_t<split_index_t,shape_t,index_t>;
        using left_t   = meta::at_t<result_t,0>;
        using right_t  = meta::at_t<result_t,1>;

        auto dim  = len(shape);
        auto axis = dim;
        using axis_t [[maybe_unused]] = decltype(axis);

        if constexpr (meta::is_signed_v<index_t>) {
            axis = (N<0) ? (dim+N) : N;
        } else {
            // unsigned, no need to check
            axis = N;
        }

        
        auto left  = left_t  {};
        auto right = right_t {};
        if constexpr (meta::is_resizeable_v<left_t>) {
            auto ldim  = axis;
            left.resize(ldim);
        }
        if constexpr (meta::is_resizeable_v<right_t>) {
            auto rdim  = dim - axis;
            right.resize(rdim);
        }

        for (size_t i=0; i<dim; i++) {
            if (i<axis) {
                at(left,i) = at(shape,i);
            } else {
                at(right,i-axis) = at(shape,i);
            }
        }

        return result_t{left,right};
    } // split

    /**
     * @brief Computes the resulting shape of matmul, following numpy rules.
     * 
     * @tparam lhs_shape_t 
     * @tparam rhs_shape_t 
     * @param ashape        lhs shape
     * @param bshape        rhs shape
     * @return constexpr auto 
     */
    template <typename lhs_shape_t, typename rhs_shape_t>
    constexpr auto shape_matmul(const lhs_shape_t& ashape, const rhs_shape_t& bshape)
    {
        using result_t = meta::resolve_optype_t<shape_matmul_t,lhs_shape_t,rhs_shape_t>;
        using return_t = meta::make_maybe_type_t<result_t>;

        using idx1_t = meta::ct<-1>;
        using idx2_t = meta::ct<-2>;

        constexpr auto i1 = idx1_t{};
        constexpr auto i2 = idx2_t{};

        const auto [b_ashape, m_ashape] = split(ashape,-2);
        const auto [b_bshape, m_bshape] = split(bshape,-2);

        auto l1 = at(ashape,i1);
        // auto l2 = at(ashape,i2);
        // auto r1 = at(bshape,i1);
        auto r2 = at(bshape,i2);

        auto adim = len(ashape);
        auto bdim = len(bshape);
        const auto [h_dim, l_dim] = (adim > bdim) ? nmtools_tuple{adim,bdim} : nmtools_tuple{bdim,adim};

        // check matrix shape
        auto valid_shape = l1 == r2;
        // broadcast shape, if possible
        const auto [success, b_shape] = index::broadcast_shape(b_ashape,b_bshape);

        valid_shape = valid_shape && success;

        if (valid_shape) {
            auto dim = h_dim;
            auto result = result_t{};
            if constexpr (meta::is_resizeable_v<result_t>) {
                result.resize(dim);
            }
            for (size_t i=0; i<(dim-2); i++) {
                at(result,i) = at(b_shape,i);
            }
            at(result,i1) = at(bshape,i1);
            at(result,i2) = at(ashape,i2);
            return return_t{result};
        } else {
            return return_t{meta::Nothing};
        }
    } // shape_matmul

    /**
     * @brief Computes src indices corresponding to src shape, given dst (matmul) indices.
     * 
     * The src_shape is expected to be full shape (not splitted).
     * The indices are expected to be broadcast indices only (splitted).
     * The dst_shape is expected to be broadcast indices only (splitted).
     * 
     * Only fixed index arrays are supported for now.
     * 
     */
    template <typename indices_t, typename src_shape_t, typename dst_shape_t>
    constexpr auto broadcast_matmul_indices(const indices_t& indices, const src_shape_t& src_shape, const dst_shape_t& dst_shape)
    {
        [[maybe_unused]] auto b_src_shape = at(split(src_shape,meta::ct_v<-2>),meta::ct_v<0>);
        if constexpr (meta::is_fixed_index_array_v<src_shape_t>) {
            // assume src_shape is fixed index array
            constexpr auto dim = meta::len_v<src_shape_t>;
            // the result of broadcasting 
            // may be zero for src_shape when len(indices) > len(src_shape),
            // for such case: return ellipsis
            // NOTE: this may produce wrong result for dynamic dimension
            // TODO: also support dynamic dimension
            if constexpr (dim<=2) {
                return Ellipsis;
            } else {
                return ::nmtools::index::broadcast_to(indices,b_src_shape,dst_shape);
            }
        } else {
            auto dim = len(src_shape);
            auto broadcasted = index::broadcast_to(indices,b_src_shape,dst_shape);
            using broadcasted_t = decltype(broadcasted);
            using result_t = nmtools_either<ellipsis_t,broadcasted_t>;
            if (dim <= 2) {
                return result_t{Ellipsis};
            } else {
                return result_t{broadcasted};
            }
        }
    } // broadcast_matmul_indices

    /**
     * @brief Join broadcasted indices with non-broadcasted matmul indices.
     * 
     * This is necessary because matmul broadcasting only happened at axis 0 upto -2.
     * Can not use meta::append_type because indices is not guaranteed to be known at compile-time.
     * 
     */
    template <typename indices_t, typename tuple_t>
    constexpr auto concat_indices(const indices_t& indices, const tuple_t& tuple)
    {
        if constexpr (meta::is_fixed_index_array_v<indices_t>) {
            constexpr auto n_index = meta::len_v<indices_t>;
            auto i0   = at(indices,meta::ct_v<0>);
            auto init = nmtools_tuple{i0};
            auto joined = meta::template_reduce<n_index>([&](auto init, auto index){
                constexpr auto i = decltype(index)::value;
                if constexpr (i<(n_index-1)) {
                    auto index_i = at(indices,meta::ct_v<i+1>);
                    return tuple_cat(init,nmtools_tuple{index_i});
                } else {
                    return tuple_cat(init,tuple);
                }
            }, /*init=*/init);
            return joined;
        } else {
            // assume dynamic shape
            using value_t = meta::get_value_type_t<indices_t>;
            // specific for matmul
            // if tuple is indeed tuple, assume its element is either integer or {None,None}
            using either_t = nmtools_either<value_t,nmtools_tuple<none_t,none_t>>;
            using result_t = meta::replace_value_type_t<indices_t,either_t>;

            auto res = result_t {};
            auto n_index = len(indices);
            // assume tuple is tuple
            constexpr auto n_tuple = meta::len_v<tuple_t>;
            if constexpr (meta::is_resizeable_v<result_t>) {
                res.resize(n_index+n_tuple);
            }

            for (size_t i=0; i<n_index; i++) {
                at(res,i) = at(indices,i);
            }

            meta::template_for<n_tuple>([&](auto index){
                at(res,index+n_index) = at(tuple,index);
            });

            return res;
        }
        // TODO: error handling (compile-time and runtime)
    } // concat_indices

    /**
     * @brief Computes the left and right indices for corresponding original array given
     * the resulting matmul indices, src (original) shape, and dst (matmul) shape.
     * 
     * The indices are expected to be used by apply_slice.
     * 
     * @tparam indices_t 
     * @tparam lshape_t 
     * @tparam rshape_t 
     * @tparam shape_t 
     * @param indices indices from dst (matmul) shape
     * @param lshape  shape from src (original) left operands
     * @param rshape  shape from src (original) right operands
     * @param shape   resulting matmul shape (from shape_matmul)
     * @return constexpr auto slicing args for left and right operands
     */
    template <typename indices_t, typename lshape_t, typename rshape_t, typename shape_t>
    constexpr auto matmul(const indices_t& indices, const lshape_t& lshape, const rshape_t& rshape, const shape_t& shape)
    {
        if constexpr (meta::is_dynamic_index_array_v<indices_t>
            && meta::is_dynamic_index_array_v<lshape_t>
            && meta::is_dynamic_index_array_v<rshape_t>
        ) {
            using index_t  = meta::get_element_type_t<indices_t>;
            using slice_t  = nmtools_either<index_t,nmtools_tuple<none_t,none_t>>;
            // assume indices, lshape, rshape, shape is dynamic index array
            using result_t = nmtools_list<slice_t>;
            auto l_slices = result_t {};
            auto r_slices = result_t {};

            auto ldim = len(lshape);
            auto rdim = len(rshape);
            [[maybe_unused]] auto matmul_dim = len(shape);
            if constexpr (meta::is_resizeable_v<result_t>) {
                l_slices.resize(ldim);
                r_slices.resize(rdim);
            }

            constexpr auto all = nmtools_tuple{None,None};

            // matmul slices
            // for example left  -> [?,::]
            //             right -> [::,?]
            at(l_slices,meta::ct_v<-1>) = all;
            at(r_slices,meta::ct_v<-2>) = all;

            // active col/row slices
            // for example left  -> [i_{-2},::]
            //             right -> [::,i_{-1}]
            at(l_slices,meta::ct_v<-2>) = at(indices,meta::ct_v<-2>);
            at(r_slices,meta::ct_v<-1>) = at(indices,meta::ct_v<-1>);

            // broadcasted indices

            auto l_offset = matmul_dim - ldim;
            for (size_t i=0; (ldim > 2) && (i<(ldim-2)); i++) {
                // broadcasted indices can only same or 1
                auto si = at(lshape,i);
                at(l_slices,i) = (si == 1 ? 0 : at(indices,i+l_offset));
            }

            auto r_offset = matmul_dim - rdim;
            for (size_t i=0; (rdim > 2) && (i<(rdim-2)); i++) {
                // broadcasted indices can only same or 1
                auto si = at(rshape,i);
                at(r_slices,i) = (si == 1 ? 0 : at(indices,i+r_offset));
            }

            return nmtools_tuple{l_slices,r_slices};
        } else {
            const auto row = at(indices,meta::ct_v<-2>);
            const auto col = at(indices,meta::ct_v<-1>);

            const auto split_indices = detail::split(indices,meta::ct_v<-2>);
            const auto b_indices     = at(split_indices,meta::ct_v<0>);

            [[maybe_unused]] auto all_slices = nmtools_tuple{None,None};
            using all_slices_t [[maybe_unused]] = nmtools_tuple<none_t,none_t>;

            [[maybe_unused]] auto all_ellipsis = nmtools_tuple{Ellipsis,Ellipsis};
            using all_ellipsis_t [[maybe_unused]] = nmtools_tuple<ellipsis_t,ellipsis_t>;

            /**
             * @brief Computes broadcasted left and right indices to corresponding original shape.
             * 
             */
            const auto lr_indices = [&](){
                constexpr auto dim = meta::len_v<indices_t>;
                if constexpr (dim > 2) {
                    // broadcasted shape
                    auto shape_    = split(shape,meta::ct_v<-2>);
                    auto b_shape   = at(shape_,meta::ct_v<0>);
                    // need to compute broadcast indices
                    auto l_indices = broadcast_matmul_indices(b_indices,lshape,b_shape);
                    auto r_indices = broadcast_matmul_indices(b_indices,rshape,b_shape);
                    return nmtools_tuple{l_indices,r_indices};
                } else {
                    return all_ellipsis;
                }
            }();

            auto get_lslice_indices = [&](const auto& l_indices){
                // here l_indices maybe ellipsis, index array, or either (ellipsis/index array)
                using l_indices_t = meta::remove_cvref_t<decltype(l_indices)>;
                // matmul slices for left operands, [...,row,:]
                auto matmul_indices = nmtools_tuple{row, all_slices};
                if constexpr (is_ellipsis_v<l_indices_t>) {
                    return matmul_indices;
                } else {
                    return concat_indices(l_indices, matmul_indices);
                }
            };

            auto get_rslice_indices = [&](const auto& r_indices){
                using r_indices_t = meta::remove_cvref_t<decltype(r_indices)>;
                // matmul slices for right operands [...,:,col]
                auto matmul_indices = nmtools_tuple{all_slices, col};
                if constexpr (is_ellipsis_v<r_indices_t>) {
                    return matmul_indices;
                } else {
                    return concat_indices(r_indices, matmul_indices);
                }
            };

            using namespace nmtools::literals;

            const auto l_indices = at(lr_indices,0_ct);
            const auto r_indices = at(lr_indices,1_ct);
            auto lslice_indices = get_lslice_indices(l_indices);
            auto rslice_indices = get_rslice_indices(r_indices);
            return nmtools_tuple{lslice_indices,rslice_indices};
        }
    } // matmul
} // namespace nmtools::view

namespace nmtools::view
{
    /**
     * @brief Matmul view type constructor.
     * 
     * @tparam lhs_t 
     * @tparam rhs_t 
     */
    template <typename lhs_t, typename rhs_t>
    struct matmul_t
    {
        using operands_type = detail::get_operands_type_t<lhs_t,rhs_t>;
        using array_type    = operands_type;
        using lhs_elem_type = meta::get_element_type_t<lhs_t>;
        using rhs_elem_type = meta::get_element_type_t<rhs_t>;
        using result_type   = meta::common_type_t<lhs_elem_type,rhs_elem_type>;

        operands_type operands;

        // the following is needed because cant use view::initialize<...>
        // can't handle tuple yet
        static constexpr auto initialize_operands(const lhs_t& lhs, const rhs_t& rhs)
        {
            using op_lhs_t = meta::at_t<operands_type,0>;
            using op_rhs_t = meta::at_t<operands_type,1>;
            if constexpr (meta::is_pointer_v<op_lhs_t> && meta::is_pointer_v<op_rhs_t>) {
                return operands_type{&lhs,&rhs};
            } else if constexpr (meta::is_pointer_v<op_lhs_t>) {
                return operands_type{&lhs,rhs};
            } else if constexpr (meta::is_pointer_v<op_rhs_t>) {
                return operands_type{lhs,&rhs};
            } else {
                return operands_type{lhs,rhs};
            }
        } // initialize_operands

        constexpr matmul_t(const lhs_t& lhs, const rhs_t& rhs)
            : operands(initialize_operands(lhs,rhs)) {}
        
        constexpr auto shape() const
        {
            const auto ashape = detail::shape(nmtools::get<0>(operands));
            const auto bshape = detail::shape(nmtools::get<1>(operands));
            // must has value
            return *detail::shape_matmul(ashape,bshape);
        } // shape

        constexpr auto dim() const
        {
            return len(shape());
        } // dim

        template <typename...size_types>
        constexpr auto view_at(const size_types&...indices) const
        {
            const auto& lhs = nmtools::get<0>(operands);
            const auto& rhs = nmtools::get<1>(operands);
            using lhs_type  = meta::remove_cvref_t<decltype(lhs)>;
            using rhs_type  = meta::remove_cvref_t<decltype(rhs)>;

            const auto packed_indices = pack_indices(indices...);
            const auto ashape   = detail::shape(lhs);
            const auto bshape   = detail::shape(rhs);
            auto indices_       = detail::matmul(packed_indices,ashape,bshape,shape());
            auto lslice_indices = at(indices_,meta::ct_v<0>);
            auto rslice_indices = at(indices_,meta::ct_v<1>);

            auto lslice = [&](){
                if constexpr (meta::is_pointer_v<lhs_type>) {
                    return apply_slice(*lhs, lslice_indices);
                } else {
                    return apply_slice(lhs, lslice_indices);
                }
            }();
            auto rslice = [&](){
                if constexpr (meta::is_pointer_v<rhs_type>) {
                    return apply_slice(*rhs, rslice_indices);
                } else {
                    return apply_slice(rhs, rslice_indices);
                }
            }();
            // element multiplication with broadcasting
            auto multiplied = multiply(lslice,rslice);
            auto reduced    = reduce_add(multiplied,/*axis=*/None);
            return reduced;
        } // view_at

        template <typename...size_types>
        constexpr auto operator()(const size_types&...indices) const
        {
            auto reduced = view_at(indices...);
            // reduced must be num type
            // the return must be result_type
            return static_cast<result_type>(reduced);
        } // operator()
    }; // matmul_t

    /**
     * @brief Create a view representing matrix product of two arrays.
     * 
     * This view should behave like numpy's matmul,
     * The axis -2..0 are broadcasted.
     * 
     * @tparam lhs_t 
     * @tparam rhs_t 
     * @param lhs 
     * @param rhs 
     * @return constexpr auto 
     */
    template <typename lhs_t, typename rhs_t>
    constexpr auto matmul(const lhs_t& lhs, const rhs_t& rhs)
    {
        // TODO: support ufunc datatype promotions
        using view_t = decorator_t<matmul_t, lhs_t, rhs_t>;
        return view_t{{lhs,rhs}};
    } // matmul
} // nmtools::view

namespace nmtools::meta
{

    namespace error
    {
        struct SHAPE_MATMUL_ERROR : detail::fail_t {};
    } // namespace error
    
    /**
     * @brief Resolve return type for shape_matmul
     * 
     * @tparam lhs_shape_t 
     * @tparam rhs_shape_t 
     */
    template <typename lhs_shape_t, typename rhs_shape_t>
    struct resolve_optype< void, view::detail::shape_matmul_t, lhs_shape_t, rhs_shape_t >
    {
        static constexpr auto vtype = [](){
            if constexpr (is_dynamic_index_array_v<lhs_shape_t> && is_dynamic_index_array_v<rhs_shape_t>) {
                return as_value_v<lhs_shape_t>;
            } else if constexpr (is_hybrid_index_array_v<lhs_shape_t> && is_hybrid_index_array_v<rhs_shape_t>) {
                constexpr auto lhs_max  = hybrid_index_array_max_size_v<lhs_shape_t>;
                constexpr auto rhs_max  = hybrid_index_array_max_size_v<rhs_shape_t>;
                constexpr auto max_size = lhs_max > rhs_max ? lhs_max : rhs_max;
                using type = resize_hybrid_index_array_max_size_t< lhs_shape_t, max_size >;
                return as_value_v<type>;
            } else if constexpr (is_fixed_index_array_v<lhs_shape_t> && is_fixed_index_array_v<rhs_shape_t>) {
                constexpr auto adim = len_v<lhs_shape_t>;
                constexpr auto bdim = len_v<rhs_shape_t>;
                constexpr auto size = adim > bdim ? adim : bdim;
                using type = resize_fixed_index_array_t<transform_bounded_array_t<lhs_shape_t>,size>;
                return as_value_v<type>;
            } else if constexpr (is_dynamic_index_array_v<lhs_shape_t>) {
                return as_value_v<lhs_shape_t>;
            } else if constexpr (is_dynamic_index_array_v<rhs_shape_t>) {
                return as_value_v<rhs_shape_t>;
            }
            // from this point, either lhs or rhs will be dynamic
            else if constexpr (is_hybrid_index_array_v<lhs_shape_t>) {
                // always select max
                constexpr auto lhs = hybrid_index_array_max_size_v<lhs_shape_t>;
                constexpr auto rhs = fixed_index_array_size_v<rhs_shape_t>;
                constexpr auto max = lhs > rhs ? lhs : rhs;
                using type = resize_hybrid_index_array_max_size_t<lhs_shape_t,max>;
                return as_value_v<type>;
            } else if constexpr (is_hybrid_index_array_v<rhs_shape_t>) {
                constexpr auto lhs = fixed_index_array_size_v<lhs_shape_t>;
                constexpr auto rhs = hybrid_index_array_max_size_v<rhs_shape_t>;
                constexpr auto max = lhs > rhs ? lhs : rhs;
                using type = resize_hybrid_index_array_max_size_t<rhs_shape_t,max>;
                return as_value_v<type>;
            }
            // unsupported
            else {
                return as_value_v<error::SHAPE_MATMUL_ERROR>;
            }
        }();

        using type = type_t<decltype(vtype)>;
    }; // resolve_optype

    namespace error
    {
        template <typename...>
        struct SPLIT_INDEX_UNSUPPORTED : detail::fail_t {};
    }

    /**
     * @brief Resolve return type for matmul split index (for partial broadcasting)
     * 
     * @tparam shape_t 
     * @tparam split_t 
     */
    template <typename shape_t, typename split_t>
    struct resolve_optype<
        void, view::detail::split_index_t, shape_t, split_t
    >
    {
        static constexpr auto vtype = [](){
            if constexpr (is_dynamic_index_array_v<shape_t>) {
                using type = make_tuple_type_t<shape_t,shape_t>;
                return as_value_v<type>;
            } else if constexpr (is_hybrid_index_array_v<shape_t>) {
                using type = make_tuple_type_t<shape_t,shape_t>;
                return as_value_v<type>;
            } else if constexpr (is_constant_index_array_v<shape_t>) {
                // not supported yet
                using type = error::SPLIT_INDEX_UNSUPPORTED<shape_t,split_t>;
                return as_value_v<type>;
            } else if constexpr (is_fixed_index_array_v<shape_t> && !is_constant_index_v<split_t>) {
                // shape is fixed size but the index to split is runtime value
                constexpr auto max_elements = fixed_index_array_size_v<shape_t>;
                using element_t = get_element_type_t<shape_t>;
                using hybrid_t  = make_hybrid_ndarray_t<element_t,max_elements,1>;
                using type = make_tuple_type_t<hybrid_t,hybrid_t>;
                return as_value_v<type>;
            } else if constexpr (is_fixed_index_array_v<shape_t> && is_constant_index_v<split_t>) {
                // number of dimension of the array
                constexpr auto N = fixed_index_array_size_v<shape_t>;
                // split index (a.k.a. position) normalize negative value
                constexpr auto i = [](){
                    constexpr auto index = split_t::value;
                    if constexpr (index < 0) {
                        return N + index;
                    } else {
                        return index;
                    }
                }();
                using element_t = get_element_type_t<shape_t>;

                using left_size_t  = make_tuple_type_t<ct<i>>;
                using right_size_t = make_tuple_type_t<ct<N-i>>;
                using left_t  = make_fixed_ndarray_t<element_t,left_size_t>;
                using right_t = make_fixed_ndarray_t<element_t,right_size_t>;
                using type    = make_tuple_type_t<left_t,right_t>;
                return as_value_v<type>;
            } else {
                // unhandled type
                using type = error::SPLIT_INDEX_UNSUPPORTED<shape_t,split_t>;
                return as_value_v<type>;
            }
        }();
        using type = type_t<decltype(vtype)>;
    }; // resolve_optype<split_index_t>

    /**
     * @brief Infre return type of matmul
     * 
     * @tparam lhs_t 
     * @tparam rhs_t 
     */
    template <typename lhs_t, typename rhs_t>
    struct get_element_type<
        view::decorator_t< view::matmul_t, lhs_t, rhs_t >
    >
    {
        using type = typename view::matmul_t<lhs_t,rhs_t>::result_type;
    }; // get_element_type

    template <typename lhs_t, typename rhs_t>
    struct is_ndarray<
        view::decorator_t< view::matmul_t, lhs_t, rhs_t >
    >
    {
        static constexpr auto value = is_ndarray_v<lhs_t> && is_ndarray_v<rhs_t>;
    }; // is_ndarray

    /**
     * @brief Infer the resulting shape of matmul at compile-time.
     * 
     * @tparam lhs_t 
     * @tparam rhs_t 
     */
    template <typename lhs_t, typename rhs_t>
    struct fixed_ndarray_shape<
        view::matmul_t< lhs_t, rhs_t >
    >
    {
        static inline constexpr auto value = [](){
            if constexpr (is_fixed_size_ndarray_v<lhs_t> && is_fixed_size_ndarray_v<rhs_t>) {
                constexpr auto lhs_shape = fixed_ndarray_shape_v<lhs_t>;
                constexpr auto rhs_shape = fixed_ndarray_shape_v<rhs_t>;
                constexpr auto shape = view::detail::shape_matmul(lhs_shape,rhs_shape);
                if constexpr (static_cast<bool>(shape)) {
                    return shape.value();
                } else {
                    return detail::Fail;
                }
            } else {
                return detail::Fail;
            }
        }();
        using value_type = remove_cvref_t<decltype(value)>;
    }; // fixed_ndarray_shape

    /**
     * @brief Infer the maximum size of the resulting matmul, at compile-time.
     * 
     * @tparam lhs_t 
     * @tparam rhs_t 
     */
    template <typename lhs_t, typename rhs_t>
    struct hybrid_ndarray_max_size<
        view::decorator_t< view::matmul_t, lhs_t, rhs_t >
    >
    {
        static inline constexpr auto value = [](){
            if constexpr (is_hybrid_ndarray_v<lhs_t> && is_hybrid_ndarray_v<rhs_t>) {
                // worst case maximum value
                return hybrid_ndarray_max_size_v<lhs_t> * hybrid_ndarray_max_size_v<rhs_t>;
            } else if constexpr (is_fixed_size_ndarray_v<lhs_t> && is_hybrid_ndarray_v<rhs_t>) {
                constexpr auto shape = fixed_ndarray_shape_v<lhs_t>;
                return index::product(shape) * hybrid_ndarray_max_size_v<rhs_t>;
            } else if constexpr (is_hybrid_ndarray_v<lhs_t> && is_fixed_size_ndarray_v<rhs_t>) {
                constexpr auto shape = fixed_ndarray_shape_v<rhs_t>;
                return index::product(shape) * hybrid_ndarray_max_size_v<lhs_t>;
            } else {
                return detail::Fail;
            }
        }();
        // TODO: simplify is_ndarray default deduction
        using value_type = remove_cvref_t<decltype(value)>;
        using type = value_type;
    }; // hybrid_ndarray_max_size

    /**
     * @brief Infer the resulting dimension of matmul, at compile-time.
     * 
     * @tparam lhs_t 
     * @tparam rhs_t 
     */
    template <typename lhs_t, typename rhs_t>
    struct fixed_dim<
        view::decorator_t< view::matmul_t, lhs_t, rhs_t >
    >
    {
        static inline constexpr auto value = [](){
            if constexpr (is_fixed_dim_ndarray_v<lhs_t> && is_fixed_dim_ndarray_v<rhs_t>) {
                // simply take maximum
                constexpr auto ldim = fixed_dim_v<lhs_t>;
                constexpr auto rdim = fixed_dim_v<rhs_t>;
                return (ldim > rdim ? ldim : rdim); 
            } else {
                return detail::Fail;
            }
        }();
        // TODO: consider to use fail type to indicate fail instead of void
        using value_type = detail::fail_to_void_t<remove_cvref_t<decltype(value)>>;
        using type = value_type;
    }; // fixed_dim
} // namespace nmtools::meta


#endif // NMTOOLS_ARRAY_VIEW_MATMUL_HPP