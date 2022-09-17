#ifndef NMTOOLS_ARRAY_INDEX_MATMUL_HPP
#define NMTOOLS_ARRAY_INDEX_MATMUL_HPP

#include "nmtools/meta.hpp"
#include "nmtools/utility.hpp"
#include "nmtools/array/index/broadcast_shape.hpp"
#include "nmtools/array/index/broadcast_to.hpp"
#include "nmtools/array/index/product.hpp"
#include "nmtools/array/ndarray/hybrid.hpp"
#include "nmtools/array/at.hpp"


namespace nmtools::index
{
    // special tag to resolve index array splitting
    struct split_index_t {};

    // TODO: move to separate file
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
        auto axis = (size_t)dim; // quick workaround to make axis runtime
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


    // TODO: properly resolve op return type
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
                    return utility::tuple_cat(init,nmtools_tuple{index_i});
                } else {
                    return utility::tuple_cat(init,tuple);
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
}

namespace nmtools::meta
{
    namespace error
    {
        template <typename...>
        struct SPLIT_INDEX_UNSUPPORTED : detail::fail_t {};
    }

    // TODO: move to separate file
    /**
     * @brief Resolve return type for matmul split index (for partial broadcasting)
     * 
     * @tparam shape_t 
     * @tparam split_t 
     */
    template <typename shape_t, typename split_t>
    struct resolve_optype<
        void, index::split_index_t, shape_t, split_t
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
                // TODO: check if split_t is constant index and then compute at compile-time
                using type = resolve_optype_t<index::split_index_t,remove_cvref_t<decltype(to_value_v<shape_t>)>,split_t>;
                return as_value_v<type>;
            } else if constexpr (is_fixed_index_array_v<shape_t> && !is_constant_index_v<split_t>) {
                // shape is fixed size but the index to split is runtime value
                constexpr auto max_elements = fixed_index_array_size_v<shape_t>;
                using element_t = get_element_type_t<shape_t>;
                // NOTE: use make_hybrid_ndarray instead of make_hybrid_ndarray_t to avoid including ndarray.hpp
                using hybrid_t  = typename make_hybrid_ndarray<element_t,max_elements,1>::type;
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
                using left_t  = typename make_fixed_ndarray<element_t,left_size_t>::type;
                using right_t = typename make_fixed_ndarray<element_t,right_size_t>::type;
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
}

namespace nmtools::index
{
    // special tag to resolve shape_matmul return type
    struct shape_matmul_t {};

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

        auto adim = (size_t)len(ashape);
        auto bdim = (size_t)len(bshape);
        #if 0 // breaks on avr-gcc with nmtools_tuple = utl::tuple :(
        const auto [h_dim, l_dim] = (adim > bdim) ? nmtools_tuple{adim,bdim} : nmtools_tuple{bdim,adim};
        #else
        const auto [h_dim, l_dim] = [&](){
            return ((adim > bdim) ? nmtools_tuple{adim,bdim} : nmtools_tuple{bdim,adim});
        }();
        #endif

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

    // TODO: remove
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

    struct matmul_t {};

    /**
     * @brief Computes the left and right indices for corresponding original array given
     * the resulting matmul indices, src (original) shape, and dst (matmul) shape.
     * 
     * The indices are expected to be used by apply_slice.
     * 
     * @tparam indices_t 
     * @tparam left_shape_t 
     * @tparam right_shape_t 
     * @tparam shape_t 
     * @param indices indices from dst (matmul) shape
     * @param lshape  shape from src (original) left operands
     * @param rshape  shape from src (original) right operands
     * @param shape   resulting matmul shape (from shape_matmul)
     * @return constexpr auto slicing args for left and right operands
     */
    template <typename indices_t, typename left_shape_t, typename right_shape_t, typename shape_t>
    constexpr auto matmul(const indices_t& indices, const left_shape_t& lshape, const right_shape_t& rshape, const shape_t& shape)
    {
        // TODO: properly resolve type

        using result_pack_t = meta::resolve_optype_t<matmul_t,indices_t,left_shape_t,right_shape_t,shape_t>;
        using left_slice_t  = meta::at_t<result_pack_t,0>;
        using right_slice_t = meta::at_t<result_pack_t,1>;

        [[maybe_unused]] const auto row = at(indices,meta::ct_v<-2>);
        [[maybe_unused]] const auto col = at(indices,meta::ct_v<-1>);

        [[maybe_unused]] auto all = nmtools_tuple{None,None};

        // TODO: return if result_t is compile-time value

        // matmul slices
        // for example left  -> [?,::]
        //             right -> [::,?]

        // active col/row slices
        // for example left  -> [i_{-2},::]
        //             right -> [::,i_{-1}]

        auto matmul_dim = len(shape);
        auto fill_non_matmul_index = [&](auto& slices, auto i, const auto& src_shape){
            auto offset = matmul_dim - len(src_shape);
            auto si = at(src_shape,i);
            at(slices,i) = (si == 1 ? 0 : at(indices,i+offset));
        };
        auto fill_non_matmul_indices = [&](auto& slices, const auto& src_shape){
            // NOTE: use len, to handle tuple properly, assume 0 is dynamic size
            constexpr auto LEN = meta::len_v<decltype(slices)>;
            if constexpr (LEN == 0) {
                auto dim = len(src_shape);
                // fill non-matmul axes
                for (size_t i=0; (dim > 2) && (i<(dim-2)); i++) {
                    // broadcasted indices can only same or 1
                    fill_non_matmul_index(slices,i,src_shape);
                }
            } else {
                meta::template_for<LEN-2>([&](auto index){
                    fill_non_matmul_index(slices,index,src_shape);
                });
            }
        };

        auto l_slices = [&](){
            auto l_slices = left_slice_t{};
            [[maybe_unused]] auto l_dim = len(lshape);
            if constexpr (meta::is_resizeable_v<left_slice_t>) {
                // at this point the value type should be either type
                l_slices.resize(l_dim);
            }

            at(l_slices,meta::ct_v<-1>) = all;
            at(l_slices,meta::ct_v<-2>) = at(indices,meta::ct_v<-2>);

            fill_non_matmul_indices(l_slices,lshape);

            return l_slices;
        }();

        auto r_slices = [&](){
            auto r_slices = right_slice_t{};
            [[maybe_unused]] auto r_dim = len(rshape);
            if constexpr (meta::is_resizeable_v<right_slice_t>) {
                r_slices.resize(r_dim);
            }

            at(r_slices,meta::ct_v<-2>) = all;
            at(r_slices,meta::ct_v<-1>) = at(indices,meta::ct_v<-1>);

            fill_non_matmul_indices(r_slices,rshape);

            return r_slices;
        }();

        return nmtools_tuple{l_slices,r_slices};

        #if 0
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

            const auto split_indices = split(indices,meta::ct_v<-2>);
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
        #endif
    } // matmul
} // namespace nmtools::index

namespace nmtools::meta
{
    namespace error
    {
        struct SHAPE_MATMUL_ERROR : detail::fail_t {};

        template <typename...>
        struct MATMUL_ERROR : detail::fail_t {};
    } // namespace error
    
    /**
     * @brief Resolve return type for shape_matmul
     * 
     * @tparam lhs_shape_t 
     * @tparam rhs_shape_t 
     */
    template <typename lhs_shape_t, typename rhs_shape_t>
    struct resolve_optype< void, index::shape_matmul_t, lhs_shape_t, rhs_shape_t >
    {
        static constexpr auto vtype = [](){
            // TODO: compute at compile time whenever possible
            if constexpr (is_constant_index_array_v<lhs_shape_t>) {
                using lhs_shape_type = remove_cvref_t<decltype(to_value_v<lhs_shape_t>)>;
                return as_value_v<resolve_optype_t<index::shape_matmul_t, lhs_shape_type, rhs_shape_t> >;
            } else if constexpr (is_constant_index_array_v<rhs_shape_t>) {
                using rhs_shape_type = remove_cvref_t<decltype(to_value_v<rhs_shape_t>)>;
                return as_value_v<resolve_optype_t<index::shape_matmul_t, lhs_shape_t, rhs_shape_type> >;
            } else if constexpr (is_dynamic_index_array_v<lhs_shape_t> && is_dynamic_index_array_v<rhs_shape_t>) {
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

    #if 1
    template <typename indices_t, typename left_shape_t, typename right_shape_t, typename shape_t>
    struct resolve_optype<
        void, index::matmul_t, indices_t, left_shape_t, right_shape_t, shape_t
    >
    {
        static constexpr auto vtype = [](){
            using index_t = get_index_element_type_t<shape_t>;
            using all_t [[maybe_unused]]   = nmtools_tuple<none_t,none_t>;
            using slice_t [[maybe_unused]] = nmtools_either<index_t,all_t>;
            constexpr auto slice_vtype = [](auto shape_vtype, [[maybe_unused]] auto f_init_vtype){
                using m_shape_t = type_t<decltype(shape_vtype)>;
                [[maybe_unused]] constexpr auto f_size = fixed_size_v<m_shape_t>;
                [[maybe_unused]] constexpr auto b_size = bounded_size_v<m_shape_t>;
                if constexpr (!is_fail_v<decltype(f_size)>) {
                    using i_slice_t  = type_t<decltype(f_init_vtype)>;
                    return meta::template_reduce<f_size-2>([](auto init, auto){
                        using concatenated = concat_type_t<nmtools_tuple<index_t>,type_t<decltype(init)>>;
                        return as_value_v<concatenated>;
                    }, as_value_v<i_slice_t>);
                } else if constexpr (!is_fail_v<decltype(b_size)>) {
                    using m_slice_t = replace_value_type_t<m_shape_t,slice_t>;
                    return as_value_v<resize_bounded_size_t<m_slice_t,b_size>>;
                } else {
                    // assume m_shape_t is index array
                    using m_slice_t = replace_value_type_t<m_shape_t,slice_t>;
                    return as_value_v<m_slice_t>;
                }
            };
            constexpr auto left_slice_vtype  = slice_vtype(as_value_v<left_shape_t>,as_value_v<nmtools_tuple<index_t,all_t>>);
            constexpr auto right_slice_vtype = slice_vtype(as_value_v<right_shape_t>,as_value_v<nmtools_tuple<all_t,index_t>>);
            using left_slice_t [[maybe_unused]]  = type_t<decltype(left_slice_vtype)>;
            using right_slice_t [[maybe_unused]] = type_t<decltype(right_slice_vtype)>;

            // TODO: check indices/left/right/shape size compatibility
            // e.g. len(indices) >= {len(left),len(right)}; len(indices) == len(shape); ...
            // assume index array
            if constexpr (
                is_index_array_v<indices_t>
                && is_index_array_v<left_shape_t>
                && is_index_array_v<right_shape_t>
                && is_index_array_v<shape_t>
            ) {
                using slices_t = nmtools_tuple<left_slice_t,right_slice_t>;
                return as_value_v<slices_t>;
            } else {
                return as_value_v<error::MATMUL_ERROR<indices_t,left_shape_t,right_shape_t,shape_t>>;
            }
        }();
        using type = type_t<decltype(vtype)>;
    };
    #endif
}

namespace nmtools::view::detail
{
    using index::shape_matmul;
    using index::broadcast_matmul_indices;
    using index::matmul;
}

#endif // NMTOOLS_ARRAY_INDEX_MATMUL_HPP