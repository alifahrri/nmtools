#ifndef NMTOOLS_ARRAY_IMPL_BOOST_HPP
#define NMTOOLS_ARRAY_IMPL_BOOST_HPP

// TODO: consider to move to nmtools/utility

#include <boost/array.hpp>
#include <boost/container/static_vector.hpp>
#include <boost/container/small_vector.hpp>
#include <boost/container/vector.hpp>

#include "nmtools/array/ndarray/ndarray.hpp"
#include "nmtools/array/shape.hpp"
#include "nmtools/meta.hpp"
#include "nmtools/meta/boost.hpp"
#include "nmtools/utility/boost/get.hpp"

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

    template <typename T, std::size_t Capacity, typename Options>
    struct len_t<::boost::container::static_vector<T,Capacity,Options>>
    {
        using array_type = ::boost::container::static_vector<T,Capacity,Options>;

        auto operator()(const array_type& array) const
        {
            return array.size();
        } // operator()
    }; // len_t

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
    
} // namespace nmtools::impl

namespace boost::container
{
    // NOTE: currently compute_indices, call free function "size"
    // TODO: consider to remove, use len instead
    // since using free function easily confuses lookup
    // usually should be declared prior to the callsite
    template <typename T, std::size_t Capacity, typename Options>
    auto size(const ::boost::container::static_vector<T,Capacity,Options>& array)
    {
        return array.size();
    }

    // NOTE: currently compute_indices, call free function "size"
    // TODO: consider to remove, use len instead
    // since using free function easily confuses lookup
    // usually should be declared prior to the callsite
    template <typename T, std::size_t N, typename Allocator, typename Options>
    auto size(const ::boost::container::small_vector<T,N,Allocator,Options>& array)
    {
        return array.size();
    }

    // NOTE: currently compute_indices, call free function "size"
    // TODO: consider to remove, use len instead
    // since using free function easily confuses lookup
    // usually should be declared prior to the callsite
    template <typename T, typename Allocator, typename Options>
    auto size(const ::boost::container::vector<T,Allocator,Options>& array)
    {
        return array.size();
    }
} // namespace boost::container



#endif // NMTOOLS_ARRAY_IMPL_BOOST_HPP