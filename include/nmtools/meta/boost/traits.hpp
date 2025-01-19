#ifndef NMTOOLS_META_BOOST_TRAITS_HPP
#define NMTOOLS_META_BOOST_TRAITS_HPP

#include <boost/array.hpp>
#include <boost/container/static_vector.hpp>
#include <boost/container/small_vector.hpp>
#include <boost/container/vector.hpp>

#include "nmtools/meta/traits.hpp"

#include <boost/version.hpp>
#define BOOST_VERSION_MAJOR     (BOOST_VERSION / 100000)
#define BOOST_VERSION_MINOR     ((BOOST_VERSION / 100) % 1000)
#define BOOST_VERSION_SUB_MINOR (BOOST_VERSION % 100)

#define XSTR(x) STR(x)
#define STR(x) #x

#if 0
#pragma message "BOOST_VERSION_MAJOR: " XSTR(BOOST_VERSION_MAJOR)
#pragma message "BOOST_VERSION_MINOR: " XSTR(BOOST_VERSION_MINOR)
#pragma message "BOOST_VERSION_SUB_MINOR: " XSTR(BOOST_VERSION_SUB_MINOR)
#endif

#undef XSTR
#undef STR

#ifndef BOOST_CONTAINER_OPTIONS_MIN_VERSION
#define BOOST_CONTAINER_OPTIONS_MIN_VERSION (65)
#endif

namespace nmtools::meta
{
    // TODO: make default of is_fixed_index_array to return true if fixed_index_array_size is valid
    template <typename T, std::size_t N>
    struct is_fixed_index_array<
        ::boost::array<T,N>, enable_if_t<is_index_v<T>>
    > : true_type {};

    // TODO: make default of is_hybrid_index_array true if hybrid_index_array_max_size is defined
    // NOTE: old boost version doesn't have Options template parameters
    #if BOOST_VERSION_MINOR > (BOOST_CONTAINER_OPTIONS_MIN_VERSION)
    template <typename T, std::size_t Capacity, typename Options>
    struct is_hybrid_index_array<
        ::boost::container::static_vector<T,Capacity,Options>
    >
    {
        static constexpr auto value = is_index_v<T>;
    }; // is_hybrid_index_array
    #else
    template <typename T, std::size_t Capacity>
    struct is_hybrid_index_array<
        ::boost::container::static_vector<T,Capacity>
    >
    {
        static constexpr auto value = is_index_v<T>;
    }; // is_hybrid_index_array
    #endif

    // NOTE: old boost version doesn't have Options template parameters
    #if BOOST_VERSION_MINOR > (BOOST_CONTAINER_OPTIONS_MIN_VERSION)
    template <typename T, std::size_t N, typename Allocator, typename Options>
    struct is_index_array<
        ::boost::container::small_vector<T,N,Allocator,Options>
    >
    {
        static constexpr auto value = is_index_v<T>;
    };
    #else
    template <typename T, std::size_t N, typename Allocator>
    struct is_index_array<
        ::boost::container::small_vector<T,N,Allocator>
    >
    {
        static constexpr auto value = is_index_v<T>;
    };
    #endif

    // NOTE: old boost version doesn't have Options template parameters
    #if BOOST_VERSION_MINOR > (BOOST_CONTAINER_OPTIONS_MIN_VERSION)
    template <typename T, typename Allocator, typename Options>
    struct is_index_array<
        ::boost::container::vector<T,Allocator,Options>
    >
    {
        static constexpr auto value = is_index_v<T>;
    };
    #else
    template <typename T, typename Allocator>
    struct is_index_array<
        ::boost::container::vector<T,Allocator>
    >
    {
        static constexpr auto value = is_index_v<T>;
    };
    #endif
} // namespace nmtools::meta

#endif // NMTOOLS_META_BOOST_TRAITS_HPP