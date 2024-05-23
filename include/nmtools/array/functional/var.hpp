#ifndef NMTOOLS_ARRAY_FUNCTIONAL_VAR_HPP
#define NMTOOLS_ARRAY_FUNCTIONAL_VAR_HPP

#include "nmtools/array/functional/functor.hpp"
#include "nmtools/array/view/var.hpp"

namespace nmtools::functional
{
    constexpr inline auto var_fun = [](const auto&...args){
        return view::var(args...);
    };

    constexpr inline auto var = functor_t{unary_fmap_t<decltype(var_fun)>{var_fun}};
} // namespace nmtools::functional

#endif // NMTOOLS_ARRAY_FUNCTIONAL_VAR_HPP