#ifndef NMTOOLS_ARRAY_VIEW_UFUNCS_DEG2RAD_HPP
#define NMTOOLS_ARRAY_VIEW_UFUNCS_DEG2RAD_HPP

#include "nmtools/constants.hpp"
#include "nmtools/array/view/ufuncs/multiply.hpp"

namespace nmtools::view
{
    template <typename array_t>
    constexpr auto deg2rad(const array_t& a)
    {
        using element_t = meta::get_element_type_t<array_t>;
        constexpr auto b = pi_v<element_t> / 180;
        return view::multiply(a,b);
    }
} // nmtools::view

#endif // NMTOOLS_ARRAY_VIEW_UFUNCS_DEG2RAD_HPP