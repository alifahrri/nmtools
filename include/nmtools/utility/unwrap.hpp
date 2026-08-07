#ifndef NMTOOLS_UTILITY_UNWRAP_HPP
#define NMTOOLS_UTILITY_UNWRAP_HPP

#include "nmtools/meta.hpp"
#include "nmtools/assert.hpp"
#include "nmtools/utility/has_value.hpp"

namespace nmtools
{
    struct unwrap_t {};

    template <typename T>
    constexpr auto unwrap(const T& t)
        -> const resolve_optype_t<unwrap_t,T>
    {
        if constexpr (is_maybe_v<T> || is_expected_v<T> || is_nullable_num_v<T>) {
            if (!has_value(t)) {
                // extra if to make it usable in constant expression
                nmtools_panic( has_value(t)
                    , "tried to unwrap invalid state"
                );
            }
            return *t;
        } else {
            return t;
        }
    }

    template <typename T>
    constexpr auto unwrap(T& t)
        -> resolve_optype_t<unwrap_t,T>
    {
        if constexpr (is_maybe_v<T> || is_expected_v<T> || is_nullable_num_v<T>) {
            if (!has_value(t)) {
                // extra if to make it usable in constant expression
                nmtools_panic( has_value(t)
                    , "tried to unwrap invalid state"
                );
            }
            return *t;
        } else {
            return t;
        }
    }

    template <typename T, auto N>
    constexpr auto unwrap(const T(&t)[N])
        -> const T(&)[N]
    {
        return t;
    }

    template <typename T, auto N>
    constexpr auto unwrap(T(&t)[N])
        -> T(&)[N]
    {
        return t;
    }

    // inspired by rust's unwrap_err
    template <typename T>
    constexpr auto unwrap_error(const T& t)
    {
        if (has_value(t)) {
            nmtools_panic( !has_value(t)
                , "tried to unwrap error from a valid state"
            );
        }
        if constexpr (is_maybe_v<T>) {
            return Nothing;
        } else if constexpr (is_expected_v<T>) {
            return t.error();
        }
    }
}

namespace nmtools::meta
{
    template <typename T>
    struct resolve_optype<void,unwrap_t,T>
    {
        static constexpr auto vtype = [](){
            if constexpr (is_maybe_v<T> || is_nullable_num_v<T> || is_expected_v<T>) {
                using type = get_value_type_t<T>;
                // TODO: handle nested maybe type
                return as_value_v<type>;
            } else {
                using type = T;
                return as_value_v<type>;
            }
        }();
        using type = type_t<decltype(vtype)>;
    };
} // namespace nmtools::meta

#endif // NMTOOLS_UTILITY_UNWRAP_HPP