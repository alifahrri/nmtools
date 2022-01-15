#ifndef NMTOOLS_UTILITY_STL_GET_HPP
#define NMTOOLS_UTILITY_STL_GET_HPP

#include "nmtools/utility/get.hpp"

#include <tuple>
#include <array>
#include <utility>
#include <type_traits>

namespace nmtools
{
    template <size_t I, typename...Ts>
    struct get_t<I,std::tuple<Ts...> >
    {
        using tuple_t = std::tuple<Ts...>;
        using reference = decltype(std::get<I>(std::declval<tuple_t&>()));
        using const_reference = decltype(std::get<I>(std::declval<const tuple_t&>()));

        constexpr const_reference operator()(const tuple_t& t) const noexcept
        {
            return std::get<I>(t);
        }

        constexpr reference operator()(tuple_t& t) noexcept
        {
            return std::get<I>(t);
        }
    };

    template <size_t I, typename T, size_t N>
    struct get_t<I,std::array<T,N>>
    {
        using array_t = std::array<T,N>;
        using reference = decltype(std::get<I>(std::declval<array_t&>()));
        using const_reference = decltype(std::get<I>(std::declval<const array_t&>()));

        constexpr const_reference operator()(const array_t& t) const noexcept
        {
            return std::get<I>(t);
        }

        constexpr reference operator()(array_t& t) noexcept
        {
            return std::get<I>(t);
        }
    };
}

#endif // NMTOOLS_UTILITY_STL_GET_HPP