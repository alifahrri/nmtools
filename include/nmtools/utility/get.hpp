#ifndef NMTOOLS_UTILITY_GET_HPP
#define NMTOOLS_UTILITY_GET_HPP

#include "nmtools/meta/common.hpp"
#include "nmtools/meta/bits/traits/has_address_space.hpp"
#include "nmtools/meta/bits/transform/remove_address_space.hpp"

namespace nmtools::meta
{
    namespace error
    {
        template <typename...>
        struct TEMPLATE_GET_UNSUPPORTED : detail::fail_t {};
    }
}

namespace nmtools
{
    template <size_t I, typename T, typename=void>
    struct get_t
    {
        using type = meta::error::TEMPLATE_GET_UNSUPPORTED<T,meta::as_type<I>>;

        constexpr type operator()([[maybe_unused]] const T& t) const noexcept
        {
            return type{};
        }

        constexpr type operator()([[maybe_unused]] T& t) const noexcept
        {
            return type{};
        }
    };

    // ignore const/ref, the type should have overload
    template <size_t I, typename T>
    struct get_t<I, const T&> : get_t<I,T> {};

    template <size_t I, typename T>
    struct get_t<I, T&> : get_t<I,T> {};

    template <size_t I, typename T>
    struct get_t<I,T,meta::enable_if_t<meta::has_address_space_v<T>>>
        : get_t<I,meta::remove_address_space_t<T>> {};

    // NOTE: gcc(9.3) failed when using auto, must use size_t, while clang(10.0) accepts happily
    template <size_t I, typename T>
    constexpr decltype(auto)
    get(const T& t)
    {
        return get_t<I,T>{}(t);
    }

    template <size_t I, typename T>
    constexpr decltype(auto)
    get(T& t)
    {
        return get_t<I,T>{}(t);
    }
}

#endif // NMTOOLS_UTILITY_GET_HPP