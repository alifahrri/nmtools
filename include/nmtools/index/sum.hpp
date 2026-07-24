#ifndef NMTOOLS_ARRAY_INDEX_SUM_HPP
#define NMTOOLS_ARRAY_INDEX_SUM_HPP

#include "nmtools/meta.hpp"
#include "nmtools/utility/at.hpp"

namespace nmtools::index
{
    // tag to resolve sum return type
    struct sum_t {};

    /**
     * @brief compute sum of 1D array
     *
     * Useful to compute number of elements.
     * 
     * @tparam array_t 
     * @param vec 
     * @return constexpr auto 
     */
    template <typename array_t>
    constexpr auto sum(const array_t& vec)
    {
        using result_t = resolve_optype_t<sum_t,array_t>;
        auto res = result_t{};
        // res already calculated if it is a constant index, see meta below
        if constexpr (!is_constant_index_v<result_t>) {
            res = 0;
            for (nm_size_t i=0; i<(nm_size_t)len(vec); i++) {
                res = res + at(vec,i);
            }
        }
        return res;
    } // sum
} // namespace nmtools::index

namespace nmtools::meta
{
    namespace error
    {
        template <typename...>
        struct INDEX_SUM_UNSUPPORTED : detail::fail_t {};
    }

    template <typename array_t>
    struct resolve_optype<
        void, index::sum_t, array_t
    >
    {
        static constexpr auto vtype = [](){
            if constexpr (!is_index_array_v<array_t>) {
                using type = error::INDEX_SUM_UNSUPPORTED<array_t>;
                return as_value_v<type>;
            } else if constexpr (
                is_constant_index_array_v<array_t>
                || is_clipped_index_array_v<array_t>
                || is_mixed_index_array_v<array_t>
            ) {
                constexpr auto array = to_value_v<array_t>;
                constexpr auto sum   = index::sum(array);
                if constexpr (is_clipped_index_array_v<array_t>) {
                    using type = clipped_size_t<sum>;
                    return as_value_v<type>;
                } else if constexpr (has_value(sum)) {
                    using type = ct<sum>;
                    return as_value_v<type>;
                } else {
                    using type = nm_size_t;
                    return as_value_v<type>;
                }
            } else {
                // TODO deduce width & sign of null type result from array_t
                using element_t = conditional_t<
                    is_nullable_index_array_v<array_t>
                    , null_int
                    , get_index_element_type_t<array_t>
                >;
                return as_value_v<element_t>;
            }
        }();
        using type = type_t<decltype(vtype)>;
    };
} // namespace nmtools::meta

#endif // NMTOOLS_ARRAY_INDEX_SUM_HPP