#ifndef NMTOOLS_ARRAY_FUNCTIONAL_CUMPROD_HPP
#define NMTOOLS_ARRAY_FUNCTIONAL_CUMPROD_HPP

#include "nmtools/array/functional/functor.hpp"
#include "nmtools/array/view/cumprod.hpp"

namespace nmtools::functional
{
    constexpr inline auto cumprod_fun = [](const auto&...args){
        return view::cumprod(args...);
    };

    constexpr inline auto cumprod = functor_t(unary_fmap_t<decltype(cumprod_fun)>{cumprod_fun});
} // namespace nmtools::functional

#endif // NMTOOLS_ARRAY_FUNCTIONAL_CUMPROD_HPP