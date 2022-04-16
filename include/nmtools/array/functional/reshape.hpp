#ifndef NMTOOLS_ARRAY_FUNCTIONAL_RESHAPE_HPP
#define NMTOOLS_ARRAY_FUNCTIONAL_RESHAPE_HPP

#include "nmtools/array/functional/functor.hpp"
#include "nmtools/array/view/reshape.hpp"

namespace nmtools::functional
{
    constexpr inline auto reshape = functor_t(unary_fmap_t{
        [](const auto&...args){
            return view::reshape(args...);
    }});
} // namespace nmtools::functional

#endif //NMTOOLS_ARRAY_FUNCTIONAL_RESHAPE_HPP