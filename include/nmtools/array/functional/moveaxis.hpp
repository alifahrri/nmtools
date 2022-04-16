#ifndef NMTOOLS_ARRAY_FUNCTIONAL_MOVEAXIS_HPP
#define NMTOOLS_ARRAY_FUNCTIONAL_MOVEAXIS_HPP

#include "nmtools/array/functional/functor.hpp"
#include "nmtools/array/view/moveaxis.hpp"

namespace nmtools::functional
{
    constexpr inline auto moveaxis = functor_t(unary_fmap_t{
        [](const auto&...args){
            return view::moveaxis(args...);
    }});
} // namespace nmtools::functional

#endif // NMTOOLS_ARRAY_FUNCTIONAL_MOVEAXIS_HPP