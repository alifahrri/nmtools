#ifndef NMTOOLS_ARRAY_FUNCTIONAL_ACTIVATIONS_LEAKY_RELU_HPP
#define NMTOOLS_ARRAY_FUNCTIONAL_ACTIVATIONS_LEAKY_RELU_HPP

#include "nmtools/array/functional/functor.hpp"
#include "nmtools/array/view/activations/leaky_relu.hpp"

namespace nmtools::functional
{
    constexpr inline auto leaky_relu = functor_t(unary_fmap_t{
        [](const auto&...args){
            return view::leaky_relu(args...);
    }});
} // namespace nmtools::functional


#endif // NMTOOLS_ARRAY_FUNCTIONAL_ACTIVATIONS_LEAKY_RELU_HPP