#ifndef NMTOOLS_ARRAY_FUNCTIONAL_PROD_HPP
#define NMTOOLS_ARRAY_FUNCTIONAL_PROD_HPP

#include "nmtools/array/functional/functor.hpp"
#include "nmtools/array/view/prod.hpp"

namespace nmtools::functional
{
    constexpr inline auto prod = functor_t(unary_fmap_t{
        [](const auto&...args){
            return view::prod(args...);
    }});
} // namespace nmtools::functional

#endif // NMTOOLS_ARRAY_FUNCTIONAL_PROD_HPP