#ifndef NMTOOLS_ARRAY_FUNCTIONAL_SUM_HPP
#define NMTOOLS_ARRAY_FUNCTIONAL_SUM_HPP

#include "nmtools/array/core/functor.hpp"
#include "nmtools/array/view/sum.hpp"

namespace nmtools::functional
{
    constexpr inline auto sum_fun = [](const auto&...args){
        return view::sum(args...);
    };

    constexpr inline auto sum = functor_t{unary_fmap_t<decltype(sum_fun)>{sum_fun}};
} // namespace nmtools::functional

#endif // NMTOOLS_ARRAY_FUNCTIONAL_SUM_HPP