#ifndef NMTOOLS_ARRAY_DATA_HPP
#define NMTOOLS_ARRAY_DATA_HPP

#include "nmtools/meta.hpp"
#include "nmtools/utility/forward.hpp"

namespace nmtools::impl::error
{
    template <typename...>
    struct DATA_UNSUPPORTED : meta::detail::fail_t {};
}

namespace nmtools::impl
{
    template <typename T, typename=void>
    struct data_t
    {
        constexpr decltype(auto) operator()(const T& data) const noexcept
        {
            if constexpr (meta::has_data_v<T>) {
                return data.data();
            } else {
                return error::DATA_UNSUPPORTED<T>{};
            }
        }

        constexpr decltype(auto) operator()(T& data) noexcept
        {
            if constexpr (meta::has_data_v<T>) {
                return data.data();
            } else {
                return error::DATA_UNSUPPORTED<T>{};
            }
        }
    };

    template <typename T, size_t N>
    struct data_t<T[N], meta::enable_if_t<meta::is_num_v<T>>>
    {
        constexpr decltype(auto) operator()(const T (&array)[N]) const noexcept
        {
            return static_cast<const T*>(array);
        }

        constexpr decltype(auto) operator()(T (&array)[N]) noexcept
        {
            return static_cast<T*>(array);
        }
    };
}

namespace nmtools
{
    template <typename array_t>
    constexpr decltype(auto) data(array_t&& array)
    {
        using array_type = meta::remove_cvref_pointer_t<array_t>;
        return impl::data_t<array_type>{}(nmtools::forward<array_t>(array));
    } // data
}
#endif // NMTOOLS_ARRAY_DATA_HPP