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

        // quick workaround for c++ for opencl error:
        // binding reference of type 'const __private unsigned long' to value of type 'const __generic nmtools::utl::array<__private unsigned long, 1>::data_type'
        // (aka 'const __generic unsigned long') changes address space
        #ifndef __OPENCL_VERSION__
        constexpr const_reference operator()(const array& t) const noexcept
        {
            return t.template get<I>();
        }

        constexpr reference operator()(array& t) noexcept
        {
            return t.template get<I>();
        }
        #else
        constexpr decltype(auto) operator()(const array& t) const noexcept
        {
            return t.buffer[I];
        }

        constexpr decltype(auto) operator()(array& t) noexcept
        {
            return t.buffer[I];
        }
        #endif // __OPENCL_VERSION__
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