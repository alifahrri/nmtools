#ifndef NMTOOLS_ARRAY_INDEX_FILTER_HPP
#define NMTOOLS_ARRAY_INDEX_FILTER_HPP

#include "nmtools/index/where.hpp"
#include "nmtools/index/choose.hpp"

#include "nmtools/meta.hpp"

namespace nmtools::index
{
    // TODO: cleanup index functions or remove
    /**
     * @brief filter an array with predicate f
     * 
     * @tparam F 
     * @tparam array_t 
     * @param f 
     * @param array 
     * @return constexpr auto 
     */
    template <typename F, typename array_t>
    constexpr auto filter(const F& f, const array_t& array)
    {
        auto indices = where(f,array);
        auto chosen  = choose(indices,array);
        using indices_t = meta::remove_cvref_t<decltype(indices)>;
        using chosen_t  = meta::remove_cvref_t<decltype(chosen)>;
        using return_t  = nmtools_tuple<indices_t,chosen_t>;
        return return_t{indices, chosen};
    } // filter
} // namespace nmtools::index

#endif // NMTOOLS_ARRAY_INDEX_FILTER_HPP