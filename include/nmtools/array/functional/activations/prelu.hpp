#ifndef NMTOOLS_ARRAY_FUNCTIONAL_ACTIVATIONS_PRELU_HPP
#define NMTOOLS_ARRAY_FUNCTIONAL_ACTIVATIONS_PRELU_HPP

#include "nmtools/array/functional/functor.hpp"
#include "nmtools/array/view/activations/prelu.hpp"

namespace nmtools::functional
{
    constexpr inline auto prelu = functor_t(unary_fmap_t{
        [](const auto&...args){
            return view::prelu(args...);
    }});
} // namespace nmtools::functional


#endif // NMTOOLS_ARRAY_FUNCTIONAL_ACTIVATIONS_PRELU_HPP