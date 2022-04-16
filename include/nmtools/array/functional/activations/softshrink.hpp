#ifndef NMTOOLS_ARRAY_FUNCTIONAL_ACTIVATIONS_SOFTSHRINK_HPP
#define NMTOOLS_ARRAY_FUNCTIONAL_ACTIVATIONS_SOFTSHRINK_HPP

#include "nmtools/array/functional/functor.hpp"
#include "nmtools/array/view/activations/softshrink.hpp"

namespace nmtools::functional
{
    constexpr inline auto softshrink = functor_t(unary_fmap_t{
        [](const auto&...args){
            return view::softshrink(args...);
    }});
} // namespace nmtools::functional


#endif // NMTOOLS_ARRAY_FUNCTIONAL_ACTIVATIONS_SOFTSHRINK_HPP