#ifndef NMTOOLS_ARRAY_FUNCTIONAL_TAKE_HPP
#define NMTOOLS_ARRAY_FUNCTIONAL_TAKE_HPP

#include "nmtools/array/core/functor.hpp"
#include "nmtools/array/view/take.hpp"

namespace nmtools::functional
{
    constexpr inline auto take_fun = [](const auto&...args){
        return view::take(args...);
    };

    constexpr inline auto take = functor_t{unary_fmap_t<decltype(take_fun)>{take_fun}};
} // namespace nmtools::functional

#endif // NMTOOLS_ARRAY_FUNCTIONAL_TAKE_HPP