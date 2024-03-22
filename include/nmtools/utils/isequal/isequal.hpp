#ifndef NMTOOLS_UTILS_ISEQUAL_ISEQUAL_HPP
#define NMTOOLS_UTILS_ISEQUAL_ISEQUAL_HPP

#include "nmtools/meta.hpp"

namespace nmtools::utils
{
    template <typename lhs_t, typename rhs_t, typename=void>
    struct isequal_t;

    template <typename lhs_t, typename rhs_t>
    constexpr auto isequal(const lhs_t&, const rhs_t&);
} // namespace nmtools::utils

#endif // NMTOOLS_UTILS_ISEQUAL_ISEQUAL_HPP