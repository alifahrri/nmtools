#ifndef NMTOOLS_ARRAY_UTILITY_MAX_HPP
#define NMTOOLS_ARRAY_UTILITY_MAX_HPP

/* common tag for preconditions, e.g. size assertion */
#include "nmtools/utility/tag.hpp"

#include "nmtools/traits.hpp"
#include "nmtools/meta.hpp"
#include <type_traits>
#include <cmath>
#include <cassert>

namespace nmtools
{
    /**
     * @brief max-element
     * 
     * @tparam Array vector-like
     * @param a vector
     * @return constexpr auto 
     */
    template <typename Array>
    constexpr auto max(const Array& a)
    {
        /* only support 1d array for now */
        static_assert(
            traits::is_array1d_v<Array>,
            "unsupported type of array"
        );
        using value_type = meta::get_vector_value_type_t<Array>;
        value_type m = std::numeric_limits<value_type>::min();
        for (const auto e : a)
            if (e > m)
                m = e;
        return m;
    } // constexpr auto max(const Array& a)
}

#endif // NMTOOLS_ARRAY_UTILITY_MAX_HPP