#ifndef NMTOOLS_ARRAY_FUNCTIONAL_MEAN_HPP
#define NMTOOLS_ARRAY_FUNCTIONAL_MEAN_HPP

#include "nmtools/array/functional/functor.hpp"
#include "nmtools/array/view/mean.hpp"

namespace nmtools::functional
{
    constexpr inline auto mean_fun = [](const auto&...args){
        return view::mean(args...);
    };

    constexpr inline auto mean = functor_t{unary_fmap_t<decltype(mean_fun)>{mean_fun}};
} // namespace nmtools::functional

#endif // NMTOOLS_ARRAY_FUNCTIONAL_MEAN_HPP