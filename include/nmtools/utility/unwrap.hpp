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
        -> const meta::resolve_optype_t<unwrap_t,T>
    {
        nmtools_cassert( has_value(t), "tried to unwrap invalid state" );
        if constexpr (meta::is_maybe_v<T>) {
            return *t;
        } else {
            return t;
        }
    }

    template <typename T>
    constexpr auto unwrap(T& t)
        -> meta::resolve_optype_t<unwrap_t,T>
    {
        nmtools_cassert( has_value(t), "tried to unwrap invalid state" );
        if constexpr (meta::is_maybe_v<T>) {
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
}

namespace nmtools::meta
{
    template <typename T>
    struct resolve_optype<void,unwrap_t,T>
    {
        static constexpr auto vtype = [](){
            if constexpr (is_maybe_v<T>) {
                using type = get_maybe_type_t<T>;
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