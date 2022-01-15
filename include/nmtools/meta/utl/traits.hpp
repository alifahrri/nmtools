#ifndef NMTOOLS_META_UTL_TRAITS_HPP
#define NMTOOLS_META_UTL_TRAITS_HPP

#include "nmtools/utl.hpp"
#include "nmtools/meta/traits.hpp"

namespace nmtools::meta
{
    template <>
    struct is_nothing<utl::nothing_t> : true_type {};

    template <typename left_t, typename right_t>
    struct is_either<utl::either<left_t,right_t>> : true_type {};

    template <typename T>
    struct is_maybe<utl::maybe<T>> : true_type {};

    template <typename...Args>
    struct is_tuple<utl::tuple<Args...>> : true_type {};

    template <typename...Ts>
    struct is_constant_index_array<utl::tuple<Ts...>,enable_if_t<(is_constant_index_v<Ts> && ...)>> : true_type {};

    template <typename T, size_t N>
    struct is_fixed_index_array<utl::array<T,N>,enable_if_t<is_index_v<T>>> : true_type {};

    template <typename...Ts>
    struct is_fixed_index_array<utl::tuple<Ts...>,enable_if_t<(is_index_v<Ts> && ...)>> : true_type {};
} // namespace nmtools::meta

#endif // NMTOOLS_META_UTL_TRAITS_HPP