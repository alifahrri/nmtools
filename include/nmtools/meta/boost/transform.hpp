#ifndef NMTOOLS_META_BOOST_TRANSFORM_HPP
#define NMTOOLS_META_BOOST_TRANSFORM_HPP

#include <boost/array.hpp>
#include <boost/container/vector.hpp>
#include <boost/container/small_vector.hpp>
#include <boost/container/static_vector.hpp>

#include "nmtools/meta/transform.hpp"

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
    // TODO: remove, use resize_size
    template <typename T, std::size_t N, std::size_t M>
    struct resize_fixed_vector<
        ::boost::array<T,N>, M
    >
    {
        using type = ::boost::array<T,M>;
    }; // resize_fixed_vector

    template <typename T, std::size_t N, typename U>
    struct replace_value_type<
        ::boost::array<T,N>, U
    >
    {
        using type = ::boost::array<U,N>;
    }; // replace_value_type

    template <typename T, std::size_t N, typename U>
    struct replace_element_type<
        ::boost::array<T,N>, U
    >
    {
        // TODO: constraint to ndarray only
        // NOTE: doesn't support nested array yet.
        using type = ::boost::array<U,N>;
    }; // replace_element_type

    #if BOOST_VERSION_MINOR > (BOOST_CONTAINER_OPTIONS_MIN_VERSION)
    template <typename T, std::size_t Capacity, typename Options, typename U>
    struct replace_value_type<
        ::boost::container::static_vector<T,Capacity,Options>, U
    >
    {
        using type = ::boost::container::static_vector<U,Capacity,Options>;
    }; // replace_value_type
    #else
    template <typename T, std::size_t Capacity, typename U>
    struct replace_value_type<
        ::boost::container::static_vector<T,Capacity>, U
    >
    {
        using type = ::boost::container::static_vector<U,Capacity>;
    }; // replace_value_type
    #endif

    #if BOOST_VERSION_MINOR > BOOST_CONTAINER_OPTIONS_MIN_VERSION
    template <typename T, std::size_t Capacity, typename Options, typename U>
    struct replace_element_type<
        ::boost::container::static_vector<T,Capacity,Options>, U, enable_if_t< is_num_v<T> && is_num_v<U> >
    > : replace_value_type<::boost::container::static_vector<T,Capacity,Options>, U> {};
    #else
    template <typename T, std::size_t Capacity, typename U>
    struct replace_element_type<
        ::boost::container::static_vector<T,Capacity>, U, enable_if_t< is_num_v<T> && is_num_v<U> >
    > : replace_value_type<::boost::container::static_vector<T,Capacity>, U> {};
    #endif

    template <typename T, std::size_t N, typename U>
    struct replace_value_type<
        ::boost::container::small_vector<T,N>, U
    >
    {
        using type = ::boost::container::small_vector<U,N>;
    }; // replace_value_type

    template <typename T, std::size_t N, typename U>
    struct replace_element_type<
        ::boost::container::small_vector<T,N>, U, enable_if_t< is_num_v<T> && is_num_v<U> >
    > : replace_value_type<::boost::container::small_vector<T,N>, U> {};

    template <typename T, typename U>
    struct replace_value_type<
        ::boost::container::vector<T>, U
    >
    {
        using type = ::boost::container::vector<U>;
    }; // replace_value_type

    template <typename T, typename U>
    struct replace_element_type<
        ::boost::container::vector<T>, U, enable_if_t< is_num_v<T> && is_num_v<U> >
    > : replace_value_type<::boost::container::vector<T>, U> {};
    
} // namespace nmtools::meta

#endif // NMTOOLS_META_BOOST_TRANSFORM_HPP