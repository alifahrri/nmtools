#ifndef NMTOOLS_ARRAY_INDEX_FILTER_HPP
#define NMTOOLS_ARRAY_INDEX_FILTER_HPP

#include "nmtools/meta.hpp"
#include "nmtools/array/ndarray/hybrid.hpp"
#include "nmtools/array/utility/at.hpp"
#include "nmtools/array/index/tuple_at.hpp"
#include "nmtools/array/index/argfilter.hpp"
#include "nmtools/array/index/choose.hpp"

#include <tuple>

namespace nmtools::index
{
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
        auto indices = argfilter(f,array);
        auto chosen  = choose(indices,array);
        return std::tuple{indices, chosen};
    } // filter
} // namespace nmtools::index

#endif // NMTOOLS_ARRAY_INDEX_FILTER_HPP