#ifndef NMTOOLS_META_BOOST_TRANSFORM_HPP
#define NMTOOLS_META_BOOST_TRANSFORM_HPP

#include <boost/array.hpp>
#include <boost/container/vector.hpp>
#include <boost/container/small_vector.hpp>
#include <boost/container/static_vector.hpp>

#include "nmtools/meta/transform.hpp"

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

    template <typename T, std::size_t Capacity, typename Options, typename U>
    struct replace_value_type<
        ::boost::container::static_vector<T,Capacity,Options>, U
    >
    {
        using type = ::boost::container::static_vector<U,Capacity,Options>;
    }; // replace_value_type

    template <typename T, std::size_t N, typename U>
    struct replace_value_type<
        ::boost::container::small_vector<T,N>, U
    >
    {
        using type = ::boost::container::small_vector<U,N>;
    }; // replace_value_type

    template <typename T, typename U>
    struct replace_value_type<
        ::boost::container::vector<T>, U
    >
    {
        using type = ::boost::container::vector<U>;
    }; // replace_value_type
    
} // namespace nmtools::meta

#endif // NMTOOLS_META_BOOST_TRANSFORM_HPP