#ifndef NMTOOLS_ARRAY_FUNCTIONAL_PROD_HPP
#define NMTOOLS_ARRAY_FUNCTIONAL_PROD_HPP

#include "nmtools/array/core/functor.hpp"
#include "nmtools/array/view/prod.hpp"

namespace nmtools::functional
{
    constexpr inline auto prod_fun = [](const auto&...args){
        return view::prod(args...);
    };

    constexpr inline auto prod = functor_t{unary_fmap_t<decltype(prod_fun)>{prod_fun}};
} // namespace nmtools::functional

#endif // NMTOOLS_ARRAY_FUNCTIONAL_PROD_HPP