#ifndef NMTOOLS_ARRAY_IMPL_UTL_HPP
#define NMTOOLS_ARRAY_IMPL_UTL_HPP

// Actual implementation for customization point for UTL

#include "nmtools/utility/shape.hpp"

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

    // TODO: remove this specialization
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

    template <typename T, typename allocator>
    struct len_t<utl::vector<T,allocator>>
    {
        using array = utl::vector<T,allocator>;
        using const_array = const array&;
        using type  = typename array::size_type;

        constexpr type operator()(const_array a) const noexcept
        {
            return a.size();
        }
    };

    template <typename T, size_t Capacity>
    struct len_t<utl::static_vector<T,Capacity>>
    {
        using array = utl::static_vector<T,Capacity>;
        using const_array = const array&;
        using type  = typename array::size_type;

        constexpr type operator()(const_array a) const noexcept
        {
            return a.size();
        }
    };
} // namespace nmtools::impl

#endif // NMTOOLS_ARRAY_IMPL_UTL_HPP