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

    template <typename T, typename allocator>
    struct is_dynamic_index_array<utl::vector<T,allocator>>
    {
        static constexpr auto value = is_index_v<T>;
    };

    template <typename T, size_t Capacity>
    struct is_hybrid_index_array<utl::static_vector<T,Capacity>,enable_if_t<is_index_v<T> || is_boolean_v<T>>> : true_type {};

    template <typename T, typename allocator>
    struct is_ndarray<utl::vector<T,allocator>> : is_num<T> {};

    template <typename T, size_t Capacity>
    struct is_ndarray<utl::static_vector<T,Capacity>> : is_num<T> {};

    template <typename T, typename allocator>
    struct is_list<utl::vector<T,allocator>> : true_type {};

    template <typename T, size_t Capacity>
    struct is_list<utl::static_vector<T,Capacity>> : true_type {};

    template <typename T, size_t N>
    struct has_tuple_size<utl::array<T,N>> : true_type {};

    template <typename...Ts>
    struct has_tuple_size<utl::tuple<Ts...>> : true_type {};
} // namespace nmtools::meta

#endif // NMTOOLS_META_UTL_TRAITS_HPP