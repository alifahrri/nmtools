#ifndef NMTOOLS_UTL_EXPECTED_HPP
#define NMTOOLS_UTL_EXPECTED_HPP

#include "nmtools/def.hpp"
#include "nmtools/meta/common.hpp"
#include "nmtools/meta/bits/traits/is_constructible.hpp"
#include "nmtools/utl/variant.hpp"

namespace nmtools::utl
{
    template <typename E>
    struct unexpected
    {
        E e;

        constexpr unexpected(const E& e)
            : e{e}
        {}

        template <typename T, enable_if_t<is_constructible_v<E,T>,int>,int=0>
        constexpr unexpected(const T& t)
            : e(t)
        {}

        constexpr decltype(auto) error() const noexcept
        {
            return (e);
        }

        constexpr decltype(auto) error() noexcept
        {
            return (e);
        }

        // TODO: check for operator ==
        template <typename T>
        constexpr auto operator==(const T& other) const noexcept
        {
            return e == other;
        }
    };

    template <typename T, typename E>
    struct expected : variant<T,unexpected<E>>
    {
        using unexpected_type = unexpected<E>;
        using value_type      = T;
        using error_type      = E;
        using base_type       = variant<T,unexpected<E>>;

        constexpr expected()
            : base_type()
        {}

        constexpr expected(const T& val)
            : base_type(val)
        {}

        constexpr expected(const unexpected_type& unexpected)
            : base_type(unexpected)
        {}

        constexpr auto has_value() const noexcept
        {
            return (base_type::index() == 0);
        }

        constexpr operator bool() const noexcept
        {
            return has_value();
        }

        constexpr auto value() const
        {
            auto ptr = base_type::template get_if<T>();

            // TODO: throw
            nmtools_assert( ptr
                , "invalid state for value call" );

            return *ptr;
        }

        constexpr auto value()
        {
            auto ptr = base_type::template get_if<T>();

            // TODO: throw
            nmtools_assert( ptr
                , "invalid state for value call" );

            return *ptr;
        }

        constexpr decltype(auto) operator*() const
        {
            return value();
        }

        constexpr decltype(auto) operator*()
        {
            return value();
        }

        constexpr decltype(auto) error() const
        {
            auto ptr = base_type::template get_if<unexpected_type>();

            // TODO: throw
            nmtools_assert( ptr
                , "invalid state for value call" );

            return *ptr;
        }
    };
}

#endif // NMTOOLS_UTL_EXPECTED_HPP