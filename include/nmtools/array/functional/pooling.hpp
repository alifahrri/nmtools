#ifndef NMTOOLS_ARRAY_FUNCTIONAL_POOLING_HPP
#define NMTOOLS_ARRAY_FUNCTIONAL_POOLING_HPP

#include "nmtools/array/functional/functor.hpp"
#include "nmtools/array/view/pooling.hpp"

namespace nmtools::functional
{
    constexpr inline auto avg_pool2d = functor_t(unary_fmap_t{
        [](const auto&...args){
            return view::avg_pool2d(args...);
    }});

    constexpr inline auto max_pool2d = functor_t(unary_fmap_t{
        [](const auto&...args){
            return view::max_pool2d(args...);
    }});

} // namespace nmtools::functional

#endif // NMTOOLS_ARRAY_FUNCTIONAL_POOLING_HPP