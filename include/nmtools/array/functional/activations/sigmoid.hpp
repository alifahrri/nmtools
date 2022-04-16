#ifndef NMTOOLS_ARRAY_FUNCTIONAL_ACTIVATIONS_SIGMOID_HPP
#define NMTOOLS_ARRAY_FUNCTIONAL_ACTIVATIONS_SIGMOID_HPP

#include "nmtools/array/functional/functor.hpp"
#include "nmtools/array/view/activations/sigmoid.hpp"

namespace nmtools::functional
{
    constexpr inline auto sigmoid = functor_t(unary_fmap_t{
        [](const auto&...args){
            return view::sigmoid(args...);
    }});
} // namespace nmtools::functional


#endif // NMTOOLS_ARRAY_FUNCTIONAL_ACTIVATIONS_SIGMOID_HPP