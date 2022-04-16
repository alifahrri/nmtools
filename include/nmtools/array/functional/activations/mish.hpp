#ifndef NMTOOLS_ARRAY_FUNCTIONAL_ACTIVATIONS_MISH_HPP
#define NMTOOLS_ARRAY_FUNCTIONAL_ACTIVATIONS_MISH_HPP

#include "nmtools/array/functional/functor.hpp"
#include "nmtools/array/view/activations/mish.hpp"

namespace nmtools::functional
{
    constexpr inline auto mish = functor_t(unary_fmap_t{
        [](const auto&...args){
            return view::mish(args...);
    }});
} // namespace nmtools::functional


#endif // NMTOOLS_ARRAY_FUNCTIONAL_ACTIVATIONS_MISH_HPP