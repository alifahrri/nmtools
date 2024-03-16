#ifndef NMTOOLS_UTILS_ISCLOSE_ISCLOSE_HPP
#define NMTOOLS_UTILS_ISCLOSE_ISCLOSE_HPP

#include "nmtools/meta.hpp"

namespace nmtools::utils
{
    template <typename lhs_t, typename rhs_t, typename epsilon_t, typename=void>
    struct isclose_t;

    template <typename lhs_t, typename rhs_t, typename epsilon_t=double>
    constexpr auto isclose(const lhs_t& lhs, const rhs_t& rhs, epsilon_t=static_cast<epsilon_t>(1e-6));
} // namespace nmtools::utils

#endif // NMTOOLS_UTILS_ISCLOSE_ISCLOSE_HPP