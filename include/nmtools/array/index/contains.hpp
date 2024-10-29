#ifndef NMTOOLS_ARRAY_INDEX_CONTAINS_HPP
#define NMTOOLS_ARRAY_INDEX_CONTAINS_HPP

#include "nmtools/meta.hpp"
#include "nmtools/utility/shape.hpp"
#include "nmtools/utility/isequal.hpp"

namespace nmtools::index
{
    template <typename array_t, typename value_t>
    constexpr auto contains(const array_t& array, const value_t& value)
    {
        for (nm_size_t i=0; i<(nm_size_t)len(array); i++) {
            if (utils::isequal(at(array,i),value)) {
                return true;
            }
        }
        return false;
    } // contains
} // nmtools::index

#endif // NMTOOLS_ARRAY_INDEX_CONTAINS_HPP