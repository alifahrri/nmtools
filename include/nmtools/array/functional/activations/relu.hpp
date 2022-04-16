#ifndef NMTOOLS_ARRAY_FUNCTIONAL_ACTIVATIONS_RELU_HPP
#define NMTOOLS_ARRAY_FUNCTIONAL_ACTIVATIONS_RELU_HPP

#include "nmtools/array/functional/functor.hpp"
#include "nmtools/array/view/activations/relu.hpp"

namespace nmtools::functional
{
    constexpr inline auto relu = functor_t(unary_fmap_t{
        [](const auto&...args){
            return view::relu(args...);
    }});
} // namespace nmtools::functional


#endif // NMTOOLS_ARRAY_FUNCTIONAL_ACTIVATIONS_RELU_HPP