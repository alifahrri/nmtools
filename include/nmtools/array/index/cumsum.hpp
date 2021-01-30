#ifndef NMTOOLS_ARRAY_INDEX_CUMSUM_HPP
#define NMTOOLS_ARRAY_INDEX_CUMSUM_HPP

#include "nmtools/meta.hpp"

#include "nmtools/array/utility/at.hpp"

namespace nmtools::index
{
    /**
     * @brief specific tag to resolve return type of cumsum
     * 
     */
    struct cumsum_t {};

    /**
     * @brief compute cumulative sum or 1D array
     * 
     * @tparam array_t 
     * @param array 
     * @return constexpr auto 
     */
    template <typename array_t>
    constexpr auto cumsum(const array_t& array)
    {
        using return_t = meta::resolve_optype_t<cumsum_t,array_t>;
        auto ret = return_t {};
        if constexpr (meta::is_resizeable_v<return_t>)
            ret.resize(size(array));
        
        at(ret,0) = at(array,0);
        for (int i=1; i<size(ret); i++)
            at(ret,i) = at(ret,i-1) + at(array,i);
        
        return ret;
    } // cumsum
} // namespace nmtools::index

namespace nmtools::meta
{
    /**
     * @brief resolve return type of index::cumsum
     * 
     * @tparam array_t 
     */
    template <typename array_t>
    struct resolve_optype< void, index::cumsum_t, array_t >
    {
        using type = transform_bounded_array_t<tuple_to_array_t<array_t>>;
    };
}

#endif // NMTOOLS_ARRAY_INDEX_CUMSUM_HPP