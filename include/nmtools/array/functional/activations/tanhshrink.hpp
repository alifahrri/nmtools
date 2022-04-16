#ifndef NMTOOLS_ARRAY_FUNCTIONAL_ACTIVATIONS_TANHSHRINK_HPP
#define NMTOOLS_ARRAY_FUNCTIONAL_ACTIVATIONS_TANHSHRINK_HPP

#include "nmtools/array/functional/functor.hpp"
#include "nmtools/array/view/activations/tanhshrink.hpp"

namespace nmtools::functional
{
    constexpr inline auto tanhshrink = functor_t(unary_fmap_t{
        [](const auto&...args){
            return view::tanhshrink(args...);
    }});
} // namespace nmtools::functional


#endif // NMTOOLS_ARRAY_FUNCTIONAL_ACTIVATIONS_TANHSHRINK_HPP