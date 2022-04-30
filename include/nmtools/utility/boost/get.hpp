#ifndef NMTOOLS_UTILITY_BOOST_GET_HPP
#define NMTOOLS_UTILITY_BOOST_GET_HPP

#include "nmtools/utility/get.hpp"

#include <boost/array.hpp>

namespace nmtools
{
    template <std::size_t I, typename T, std::size_t N>
    struct get_t<I,boost::array<T,N>>
    {
        using array_type = boost::array<T,N>;

        decltype(auto) operator()(const array_type& array) const noexcept
        {
            return boost::get<I>(array);
        }

        decltype(auto) operator()(array_type& array) noexcept
        {
            return boost::get<I>(array);
        }
    };
} // namespace nmtools


#endif // NMTOOLS_UTILITY_BOOST_GET_HPP