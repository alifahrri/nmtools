#ifndef NMTOOLS_ARRAY_FUNCTIONAL_ACTIVATIONS_CELU_HPP
#define NMTOOLS_ARRAY_FUNCTIONAL_ACTIVATIONS_CELU_HPP

#include "nmtools/array/functional/functor.hpp"
#include "nmtools/array/view/activations/celu.hpp"

namespace nmtools::functional
{
    constexpr inline auto celu = functor_t(unary_fmap_t{
        [](const auto&...args){
            return view::celu(args...);
    }});
} // namespace nmtools::functional


#endif // NMTOOLS_ARRAY_FUNCTIONAL_ACTIVATIONS_CELU_HPP