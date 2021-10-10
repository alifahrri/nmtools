#ifndef NMTOOLS_ARRAY_INDEX_ARGFILTER_HPP
#define NMTOOLS_ARRAY_INDEX_ARGFILTER_HPP

#include "nmtools/meta.hpp"
#include "nmtools/array/index/where.hpp"

#include <type_traits>
#include <cstddef>
#include <utility>

namespace nmtools::index
{
    /**
     * @brief specific tag to resolve argfilter op return type
     * 
     */
    struct argfilter_t {};

    // TODO: cleanup or remove index functions
    /**
     * @brief return indices of array that satisfy predicate f
     * 
     * @tparam F unary predicate
     * @tparam array_t 
     * @param f 
     * @param array 
     * @return constexpr auto 
     */
    template <typename index_t=size_t, typename F, typename array_t>
    constexpr auto argfilter(const F& f, const array_t& array)
    {
        return where(f,array);
    } // argfilter
} // namespace nmtools

namespace nmtools::meta
{
    // TODO: cleanup index metafunctions
    /**
     * @brief resolve argfilter return type for resizeable array type
     * 
     * @tparam array_t 
     * @tparam index_t 
     */
    template <typename array_t, typename index_t>
    struct resolve_optype<
        std::enable_if_t<
            meta::is_resizeable_v<array_t>
        >,
        index::argfilter_t, array_t, index_t
    >
    {
        using type = meta::replace_element_type_t<array_t,index_t>;
    }; // resolve_optype argfilter_t

    // TODO: cleanup index metafunctions
    /**
     * @brief resolve argfilter return type for fixed array type
     * 
     * @tparam array_t 
     * @tparam index_t 
     */
    template <typename array_t, typename index_t>
    struct resolve_optype<
        std::enable_if_t<
            !meta::is_resizeable_v<array_t>
            && has_tuple_size_v<array_t>
            && std::is_arithmetic_v<get_element_or_common_type_t<array_t>>
        >,
        index::argfilter_t, array_t, index_t
    >
    {
        static constexpr auto N = std::tuple_size_v<array_t>;
        // need to use hybrid array1d since the size will depends on runtime value
        using type = array::hybrid_ndarray<index_t,N,1>;
    }; // resolve_optype argfilter_t
} // namespace nmtools::meta

#endif // NMTOOLS_ARRAY_INDEX_ARGFILTER_HPP