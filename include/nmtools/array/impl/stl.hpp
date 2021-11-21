#ifndef NMTOOLS_ARRAY_IMPL_STL_HPP
#define NMTOOLS_ARRAY_IMPL_STL_HPP

#include "nmtools/array/shape.hpp"

#include <array>
#include <tuple>
#include <type_traits>

namespace nmtools::impl
{
    template <typename T, size_t N>
    struct len_t<std::array<T,N>>
    {
        using array = const std::array<T,N>&;
        using type  = decltype(std::declval<array>().size());

        constexpr auto operator()(array a) const noexcept
        {
            return a.size();
        }
    }; // len_t<const std::array<T,N>&>

    template <typename...Ts>
    struct len_t<std::tuple<Ts...>>
    {
        using tuple = const std::tuple<Ts...>&;
        using type  = size_t;

        constexpr auto operator()(tuple) const noexcept -> type
        {
            return sizeof...(Ts);
        }
    }; // len_t<const std::tuple<Ts...>&>

    template <typename T>
    struct len_t<std::vector<T>>
    {
        using vector = const std::vector<T>&;
        using type   = size_t;

        constexpr auto operator()(vector v) const noexcept -> type
        {
            return v.size();
        }
    }; // len_t<const std::vector<T>&>

    template <typename T, size_t N>
    struct shape_t<std::array<T,N>>
    {
        using array = const std::array<T,N>&;

        constexpr auto operator()(array) const noexcept
        {
            return meta::fixed_ndarray_shape_v<std::array<T,N>>;
        }
    }; // shape_t<const std::array<T,N>&>

    // TODO: remove support for nested vector
    template <typename T>
    struct shape_t<std::vector<T>
        , meta::enable_if_t<meta::is_num_v<T>>>
    {
        using vector_t = const std::vector<T>&;

        constexpr auto operator()(vector_t vector) const
        {
            return std::array{vector.size()};
        }
    }; // shape_t<std::vector<T>>

    // TODO: remove support for nested vector
    template <typename T>
    struct shape_t<std::vector<std::vector<T>>
        , meta::enable_if_t<meta::is_num_v<T>>>
    {
        using vector_t = const std::vector<std::vector<T>>&;

        constexpr auto operator()(vector_t vector) const
        {
            return std::array{vector.size(),vector.at(0).size()};
        }
    }; // shape_t<std::vector<std::vector<T>>>

    // TODO: remove support for nested vector
    template <typename T>
    struct shape_t<std::vector<std::vector<std::vector<T>>>
        , meta::enable_if_t<meta::is_num_v<T>>>
    {
        using vector_t = const std::vector<std::vector<std::vector<T>>>&;

        constexpr auto operator()(vector_t vector) const
        {
            return std::array{vector.size(),vector.at(0).size(),vector.at(0).at(0).size()};
        }
    }; // shape_t<std::vector<std::vector<T>>>
    
    template <typename...Ts>
    struct get_if_t<std::variant<Ts...>>
    {
        using variant_t = const std::variant<Ts...>*;

        template <typename U>
        constexpr auto operator()(variant_t variant) const noexcept
        {
            return std::get_if<U>(variant);
        }
    }; // get_if_t
} // namespace nmtools::impl

#endif // NMTOOLS_ARRAY_IMPL_STL_HPP