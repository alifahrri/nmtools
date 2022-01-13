#ifndef NMTOOLS_UTILITY_UTL_GET_HPP
#define NMTOOLS_UTILITY_UTL_GET_HPP

#include "nmtools/utility/get.hpp"

#include "nmtools/utl/tuple.hpp"
#include "nmtools/utl/array.hpp"

namespace nmtools
{
    template <size_t I, typename T, size_t N>
    struct get_t<I,utl::array<T,N>>
    {
        using array = utl::array<T,N>;
        using reference = T&;
        using const_reference = const T&;

        constexpr const_reference operator()(const array& t) const noexcept
        {
            return t.template get<I>();
        }

        constexpr reference operator()(array& t) noexcept
        {
            return t.template get<I>();
        }
    };

    template <size_t I, typename...Args>
    struct get_t<I,utl::tuple<Args...>>
    {
        using tuple = utl::tuple<Args...>;

        constexpr decltype(auto) operator()(const tuple& tp) const noexcept
        {
            return utl::get<I>(tp);
        }

        constexpr decltype(auto) operator()(tuple& tp) noexcept
        {
            return utl::get<I>(tp);
        }
    };
    
} // namespace nmtools


#endif // NMTOOLS_UTILITY_UTL_GET_HPP