#ifndef NMTOOLS_UTILITY_GET_IF_HPP
#define NMTOOLS_UTILITY_GET_IF_HPP

#include "nmtools/meta/common.hpp"

namespace nmtools::impl::error
{
    template <typename...>
    struct GET_IF_UNSUPPORTED : meta::detail::fail_t {};
} // namespace nmtools::impl::error

namespace nmtools::impl
{
    template <typename T, typename=void>
    struct get_if_t
    {
        template <typename U>
        constexpr auto operator()(const T*) const noexcept
        {
            return error::GET_IF_UNSUPPORTED<T>{};
        }
    }; // get_if_t

    template <typename T>
    constexpr inline auto get_if = get_if_t<T>{};
} // namespace nmtools::impl

namespace nmtools
{
    /**
     * @brief Helper function to return the value of Either object.
     * 
     * @tparam T 
     * @param t 
     * @return constexpr auto 
     */
    template <typename U, typename T>
    constexpr auto get_if(const T* t)
    {
        constexpr auto get_if = impl::get_if<T>;
        return get_if.template operator()<U>(t);
    } // get_if
} // namespace nmtools

#endif // NMTOOLS_UTILITY_GET_IF_HPP

