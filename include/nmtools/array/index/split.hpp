#ifndef NMTOOLS_ARRAY_INDEX_SPLIT_HPP
#define NMTOOLS_ARRAY_INDEX_SPLIT_HPP

#include "nmtools/meta.hpp"
#include "nmtools/utility/at.hpp"
#include "nmtools/utility/shape.hpp"

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

#endif // NMTOOLS_ARRAY_INDEX_SPLIT_HPP