#ifndef NMTOOLS_ARRAY_FUNCTIONAL_STDDEV_HPP
#define NMTOOLS_ARRAY_FUNCTIONAL_STDDEV_HPP

#include "nmtools/array/functional/functor.hpp"
#include "nmtools/array/view/stddev.hpp"

namespace nmtools::functional
{
    constexpr inline auto stddev = functor_t(unary_fmap_t{
        [](const auto&...args){
            return view::stddev(args...);
    }});
} // namespace nmtools::functional

#endif // NMTOOLS_ARRAY_FUNCTIONAL_STDDEV_HPP