#ifndef NMTOOLS_ARRAY_INDEX_MATMUL_HPP
#define NMTOOLS_ARRAY_INDEX_MATMUL_HPP

#include "nmtools/meta.hpp"
#include "nmtools/utility.hpp"
#include "nmtools/array/index/broadcast_shape.hpp"
#include "nmtools/array/index/broadcast_to.hpp"
#include "nmtools/array/index/product.hpp"
#include "nmtools/array/ndarray.hpp"
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
        if constexpr (meta::is_resizable_v<left_t>) {
            auto ldim  = axis;
            left.resize(ldim);
        }
        if constexpr (meta::is_resizable_v<right_t>) {
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
            if constexpr (is_constant_index_array_v<shape_t>) {
                // TODO: check if split_t is constant index and then compute at compile-time
                using type = resolve_optype_t<index::split_index_t,remove_cvref_t<decltype(to_value_v<shape_t>)>,split_t>;
                return as_value_v<type>;
            } else if constexpr (is_fixed_index_array_v<shape_t> && !is_constant_index_v<split_t>) {
                // shape is fixed size but the index to split is runtime value
                constexpr auto max_elements = fixed_index_array_size_v<shape_t>;
                using element_t = get_index_element_type_t<shape_t>;
                // NOTE: use make_hybrid_ndarray instead of make_hybrid_ndarray_t to avoid including ndarray.hpp
                using hybrid_t  = typename make_hybrid_ndarray<element_t,max_elements,1>::type;
                using type = nmtools_tuple<hybrid_t,hybrid_t>;
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
                using element_t = get_index_element_type_t<shape_t>;

                using left_size_t  = nmtools_tuple<ct<i>>;
                using right_size_t = nmtools_tuple<ct<N-i>>;
                using left_t  = typename make_fixed_ndarray<element_t,left_size_t>::type;
                using right_t = typename make_fixed_ndarray<element_t,right_size_t>::type;
                using type    = nmtools_tuple<left_t,right_t>;
                return as_value_v<type>;
            } else if constexpr (is_index_array_v<shape_t>) {
                using type = nmtools_tuple<shape_t,shape_t>;
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
        using return_t = nmtools_maybe<result_t>;

        if constexpr (meta::is_constant_index_array_v<result_t>) {
            // still use maybe for simplicity at caller site
            return return_t{result_t{}};
        } else {
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
            auto valid_shape = (size_t)l1 == (size_t)r2;
            // broadcast shape, if possible
            #if 0
            const auto [success, b_shape] = index::broadcast_shape(b_ashape,b_bshape);
            #else
            const auto result = index::broadcast_shape(b_ashape,b_bshape);
            const auto success = static_cast<bool>(result);
            #endif

            valid_shape = valid_shape && success;

            if (valid_shape) {
                const auto& b_shape = *result;
                auto dim = h_dim;
                auto result = result_t{};
                if constexpr (meta::is_resizable_v<result_t>) {
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
        }
    } // shape_matmul

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

        [[maybe_unused]] const auto all = nmtools_tuple{none_t{},none_t{}};

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
            if constexpr (meta::is_resizable_v<left_slice_t>) {
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
            if constexpr (meta::is_resizable_v<right_slice_t>) {
                r_slices.resize(r_dim);
            }

            at(r_slices,meta::ct_v<-2>) = all;
            at(r_slices,meta::ct_v<-1>) = at(indices,meta::ct_v<-1>);

            fill_non_matmul_indices(r_slices,rshape);

            return r_slices;
        }();

        return nmtools_tuple{l_slices,r_slices};
    } // matmul
} // namespace nmtools::index

namespace nmtools::meta
{
    namespace error
    {
        template <typename...>
        struct SHAPE_MATMUL_ERROR : detail::fail_t {};

        template <typename...>
        struct SHAPE_MATMUL_UNSUPPORTED : detail::fail_t {};

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
            if constexpr (is_constant_index_array_v<lhs_shape_t> && is_constant_index_array_v<rhs_shape_t>) {
                constexpr auto lhs_shape = to_value_v<lhs_shape_t>;
                constexpr auto rhs_shape = to_value_v<rhs_shape_t>;
                constexpr auto result = index::shape_matmul(lhs_shape,rhs_shape);
                if constexpr (static_cast<bool>(result)) {
                    using nmtools::len, nmtools::at;
                    return template_reduce<len(*result)-1>([&](auto init, auto index){
                        using init_type = type_t<decltype(init)>;
                        using type = append_type_t<init_type,ct<at(*result,index+1)>>;
                        return as_value_v<type>;
                    }, as_value_v<nmtools_tuple<ct<at(*result,0)>>>);
                } else {
                    using type = error::SHAPE_MATMUL_ERROR<lhs_shape_t,rhs_shape_t>;
                    return as_value_v<type>;
                }
            } else if constexpr (is_constant_index_array_v<lhs_shape_t>) {
                using lhs_shape_type = remove_cvref_t<decltype(to_value_v<lhs_shape_t>)>;
                return as_value_v<resolve_optype_t<index::shape_matmul_t, lhs_shape_type, rhs_shape_t> >;
            } else if constexpr (is_constant_index_array_v<rhs_shape_t>) {
                using rhs_shape_type = remove_cvref_t<decltype(to_value_v<rhs_shape_t>)>;
                return as_value_v<resolve_optype_t<index::shape_matmul_t, lhs_shape_t, rhs_shape_type> >;
            } else if constexpr (is_index_array_v<lhs_shape_t> && is_index_array_v<rhs_shape_t>) {
                constexpr auto len_a = len_v<lhs_shape_t>;
                constexpr auto len_b = len_v<rhs_shape_t>;
                [[maybe_unused]] constexpr auto b_size_a = bounded_size_v<lhs_shape_t>;
                [[maybe_unused]] constexpr auto b_size_b = bounded_size_v<rhs_shape_t>;
                if constexpr ((len_a > 0) && (len_b > 0)) {
                    constexpr auto max_size = (len_a > len_b) ? len_a : len_b;
                    // TODO: use index_type instead of size_t
                    using type = nmtools_array<size_t,max_size>;
                    return as_value_v<type>;
                } else if constexpr (!is_fail_v<decltype(b_size_a)> && !is_fail_v<decltype(b_size_b)>) {
                    constexpr auto max_size = (b_size_a > b_size_b ? b_size_a : b_size_b);
                    using type = array::static_vector<size_t,max_size>;
                    return as_value_v<type>;
                } else if constexpr (!is_fail_v<decltype(b_size_a)> && (len_b > 0)) {
                    if constexpr (len_b >= b_size_a) {
                        using type = nmtools_array<size_t,len_b>;
                        return as_value_v<type>;
                    } else {
                        using type = array::static_vector<size_t,b_size_a>;
                        return as_value_v<type>;
                    }
                } else if constexpr ((len_a > 0) && !is_fail_v<decltype(b_size_b)>) {
                    if constexpr (len_a >= b_size_b) {
                        using type = nmtools_array<size_t,len_a>;
                        return as_value_v<type>;
                    } else {
                        using type = array::static_vector<size_t,b_size_b>;
                        return as_value_v<type>;
                    }
                } else {
                    using type = nmtools_list<size_t>;
                    return as_value_v<type>;
                }
            }
            // unsupported
            else {
                return as_value_v<error::SHAPE_MATMUL_UNSUPPORTED<lhs_shape_t,rhs_shape_t>>;
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
                constexpr auto f_size = len_v<m_shape_t>;
                [[maybe_unused]] constexpr auto b_size = bounded_size_v<m_shape_t>;
                if constexpr (f_size > 0) {
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
    using index::matmul;
}

#endif // NMTOOLS_ARRAY_INDEX_MATMUL_HPP