#ifndef NMTOOLS_ARRAY_FUNCTIONAL_CUMSUM_HPP
#define NMTOOLS_ARRAY_FUNCTIONAL_CUMSUM_HPP

#include "nmtools/array/core/functor.hpp"
#include "nmtools/array/view/cumsum.hpp"

namespace nmtools::functional
{
    constexpr inline auto cumsum_fun = [](const auto&...args){
        return view::cumsum(args...);
    };

    constexpr inline auto cumsum = functor_t{unary_fmap_t<decltype(cumsum_fun)>{cumsum_fun}};
} // namespace nmtools::functional

#endif // NMTOOLS_ARRAY_FUNCTIONAL_CUMSUM_HPP