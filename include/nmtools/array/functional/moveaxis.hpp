#ifndef NMTOOLS_ARRAY_FUNCTIONAL_MOVEAXIS_HPP
#define NMTOOLS_ARRAY_FUNCTIONAL_MOVEAXIS_HPP

#include "nmtools/array/functional/functor.hpp"
#include "nmtools/array/view/moveaxis.hpp"

namespace nmtools::functional
{
    constexpr inline auto moveaxis_fun = [](const auto&...args){
        return view::moveaxis(args...);
    };

    constexpr inline auto moveaxis = functor_t{unary_fmap_t<decltype(moveaxis_fun)>{moveaxis_fun}};
} // namespace nmtools::functional

#endif // NMTOOLS_ARRAY_FUNCTIONAL_MOVEAXIS_HPP