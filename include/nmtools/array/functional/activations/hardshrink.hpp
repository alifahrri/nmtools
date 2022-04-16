#ifndef NMTOOLS_ARRAY_FUNCTIONAL_ACTIVATIONS_HARDSHRINK_HPP
#define NMTOOLS_ARRAY_FUNCTIONAL_ACTIVATIONS_HARDSHRINK_HPP

#include "nmtools/array/functional/functor.hpp"
#include "nmtools/array/view/activations/hardshrink.hpp"

namespace nmtools::functional
{
    constexpr inline auto hardshrink = functor_t(unary_fmap_t{
        [](const auto&...args){
            return view::hardshrink(args...);
    }});
} // namespace nmtools::functional


#endif // NMTOOLS_ARRAY_FUNCTIONAL_ACTIVATIONS_HARDSHRINK_HPP