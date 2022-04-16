#ifndef NMTOOLS_ARRAY_FUNCTIONAL_ACTIVATIONS_SELU_HPP
#define NMTOOLS_ARRAY_FUNCTIONAL_ACTIVATIONS_SELU_HPP

#include "nmtools/array/functional/functor.hpp"
#include "nmtools/array/view/activations/selu.hpp"

namespace nmtools::functional
{
    constexpr inline auto selu = functor_t(unary_fmap_t{
        [](const auto&...args){
            return view::selu(args...);
    }});
} // namespace nmtools::functional


#endif // NMTOOLS_ARRAY_FUNCTIONAL_ACTIVATIONS_SELU_HPP