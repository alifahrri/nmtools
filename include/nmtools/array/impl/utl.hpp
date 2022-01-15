#ifndef NMTOOLS_ARRAY_IMPL_UTL_HPP
#define NMTOOLS_ARRAY_IMPL_UTL_HPP

// Actual implementation for customization point for UTL

#include "nmtools/array/shape.hpp"

#include "nmtools/utl.hpp"

namespace nmtools::impl
{
    template <typename T, size_t N>
    struct len_t<utl::array<T,N>>
    {
        using array = const utl::array<T,N>&;
        using type  = decltype(meta::declval<array>().size());

        constexpr auto operator()(array a) const noexcept
        {
            return a.size();
        }
    };

    template <typename...Ts>
    struct len_t<utl::tuple<Ts...>>
    {
        using tuple = const utl::tuple<Ts...>&;
        using type  = size_t;

        constexpr auto operator()(tuple) const noexcept
        {
            return sizeof...(Ts);
        }
    };
} // namespace nmtools::impl

#endif // NMTOOLS_ARRAY_IMPL_UTL_HPP