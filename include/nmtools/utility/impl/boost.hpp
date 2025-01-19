#ifndef NMTOOLS_ARRAY_IMPL_BOOST_HPP
#define NMTOOLS_ARRAY_IMPL_BOOST_HPP

// TODO: consider to move to nmtools/utility

#include <boost/array.hpp>
#include <boost/container/static_vector.hpp>
#include <boost/container/small_vector.hpp>
#include <boost/container/vector.hpp>

#include "nmtools/utility/shape.hpp"
#include "nmtools/meta.hpp"
#include "nmtools/meta/boost.hpp"
#include "nmtools/utility/boost/get.hpp"

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

namespace nmtools::impl
{
    template <typename T, std::size_t N>
    struct len_t<
        ::boost::array<T,N>
    >
    {
        using array_type = ::boost::array<T,N>;

        auto operator()(const array_type&) const
        {
            return N;
        }
    }; // len_t

    #if BOOST_VERSION_MINOR > BOOST_CONTAINER_OPTIONS_MIN_VERSION
    template <typename T, std::size_t Capacity, typename Options>
    struct len_t<::boost::container::static_vector<T,Capacity,Options>>
    {
        using array_type = ::boost::container::static_vector<T,Capacity,Options>;

        auto operator()(const array_type& array) const
        {
            return array.size();
        } // operator()
    }; // len_t
    #else
    template <typename T, std::size_t Capacity>
    struct len_t<::boost::container::static_vector<T,Capacity>>
    {
        using array_type = ::boost::container::static_vector<T,Capacity>;

        auto operator()(const array_type& array) const
        {
            return array.size();
        } // operator()
    }; // len_t
    #endif

    #if BOOST_VERSION_MINOR > BOOST_CONTAINER_OPTIONS_MIN_VERSION
    template <typename T, std::size_t N, typename Allocator, typename Options>
    struct len_t<
        ::boost::container::small_vector<T,N,Allocator,Options>
    >
    {
        using array_type = ::boost::container::small_vector<T,N,Allocator,Options>;

        auto operator()(const array_type& array) const
        {
            return array.size();
        } // operator()
    }; // len_t
    #else
    template <typename T, std::size_t N, typename Allocator>
    struct len_t<
        ::boost::container::small_vector<T,N,Allocator>
    >
    {
        using array_type = ::boost::container::small_vector<T,N,Allocator>;

        auto operator()(const array_type& array) const
        {
            return array.size();
        } // operator()
    }; // len_t
    #endif

    #if BOOST_VERSION_MINOR > BOOST_CONTAINER_OPTIONS_MIN_VERSION
    template <typename T, typename Allocator, typename Options>
    struct len_t<
        ::boost::container::vector<T,Allocator,Options>
    >
    {
        using array_type = ::boost::container::vector<T,Allocator,Options>;

        auto operator()(const array_type& array) const
        {
            return array.size();
        } // operator()
    }; // operator()
    #else
    template <typename T, typename Allocator>
    struct len_t<
        ::boost::container::vector<T,Allocator>
    >
    {
        using array_type = ::boost::container::vector<T,Allocator>;

        auto operator()(const array_type& array) const
        {
            return array.size();
        } // operator()
    }; // operator()
    #endif
    
} // namespace nmtools::impl

namespace boost::container
{
    // NOTE: currently compute_indices, call free function "size"
    // TODO: consider to remove, use len instead
    // since using free function easily confuses lookup
    // usually should be declared prior to the callsite
    #if BOOST_VERSION_MINOR > BOOST_CONTAINER_OPTIONS_MIN_VERSION
    template <typename T, std::size_t Capacity, typename Options>
    auto size(const ::boost::container::static_vector<T,Capacity,Options>& array)
    {
        return array.size();
    }
    #else
    template <typename T, std::size_t Capacity>
    auto size(const ::boost::container::static_vector<T,Capacity>& array)
    {
        return array.size();
    }
    #endif

    // NOTE: currently compute_indices, call free function "size"
    // TODO: consider to remove, use len instead
    // since using free function easily confuses lookup
    // usually should be declared prior to the callsite
    #if BOOST_VERSION_MINOR > BOOST_CONTAINER_OPTIONS_MIN_VERSION
    template <typename T, std::size_t N, typename Allocator, typename Options>
    auto size(const ::boost::container::small_vector<T,N,Allocator,Options>& array)
    {
        return array.size();
    }
    #else
    template <typename T, std::size_t N, typename Allocator>
    auto size(const ::boost::container::small_vector<T,N,Allocator>& array)
    {
        return array.size();
    }
    #endif

    // NOTE: currently compute_indices, call free function "size"
    // TODO: consider to remove, use len instead
    // since using free function easily confuses lookup
    // usually should be declared prior to the callsite
    #if BOOST_VERSION_MINOR > BOOST_CONTAINER_OPTIONS_MIN_VERSION
    template <typename T, typename Allocator, typename Options>
    auto size(const ::boost::container::vector<T,Allocator,Options>& array)
    {
        return array.size();
    }
    #else
    template <typename T, typename Allocator>
    auto size(const ::boost::container::vector<T,Allocator>& array)
    {
        return array.size();
    }
    #endif
} // namespace boost::container



#endif // NMTOOLS_ARRAY_IMPL_BOOST_HPP