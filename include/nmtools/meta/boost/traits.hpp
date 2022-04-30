#ifndef NMTOOLS_META_BOOST_TRAITS_HPP
#define NMTOOLS_META_BOOST_TRAITS_HPP

#include <boost/array.hpp>
#include <boost/container/static_vector.hpp>
#include <boost/container/small_vector.hpp>
#include <boost/container/vector.hpp>

#include "nmtools/meta/traits.hpp"

namespace nmtools::meta
{
    // TODO: make default of is_fixed_index_array to return true if fixed_index_array_size is valid
    template <typename T, std::size_t N>
    struct is_fixed_index_array<
        ::boost::array<T,N>, enable_if_t<is_index_v<T>>
    > : true_type {};

    // TODO: make default of is_hybrid_index_array true if hybrid_index_array_max_size is defined
    template <typename T, std::size_t Capacity, typename Options>
    struct is_hybrid_index_array<
        ::boost::container::static_vector<T,Capacity,Options>
    >
    {
        static constexpr auto value = is_index_v<T>;
    }; // is_hybrid_index_array

    template <typename T, std::size_t N, typename Allocator, typename Options>
    struct is_index_array<
        ::boost::container::small_vector<T,N,Allocator,Options>
    >
    {
        static constexpr auto value = is_index_v<T>;
    };

    template <typename T, typename Allocator, typename Options>
    struct is_index_array<
        ::boost::container::vector<T,Allocator,Options>
    >
    {
        static constexpr auto value = is_index_v<T>;
    };
} // namespace nmtools::meta

#endif // NMTOOLS_META_BOOST_TRAITS_HPP