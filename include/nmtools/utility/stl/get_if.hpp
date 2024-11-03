#ifndef NMTOOLS_UTILITY_STL_GET_IF_HPP
#define NMTOOLS_UTILITY_STL_GET_IF_HPP

#include "nmtools/utility/get_if.hpp"

#include <variant>

namespace nmtools::impl
{
    template <typename...Ts>
    struct get_if_t<std::variant<Ts...>>
    {
        using variant_t = std::variant<Ts...>;

        template <typename U>
        constexpr auto operator()(variant_t* variant) noexcept
        {
            return std::get_if<U>(variant);
        }

        template <typename U>
        constexpr auto operator()(const variant_t* variant) const noexcept
        {
            return std::get_if<U>(variant);
        }
    }; // get_if_t    
} // namespace nmtools::impl

#endif // NMTOOLS_UTILITY_STL_GET_IF_HPP