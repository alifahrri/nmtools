#ifndef NMTOOLS_ARRAY_FUNCTIONAL_ACTIVATIONS_RELU6_HPP
#define NMTOOLS_ARRAY_FUNCTIONAL_ACTIVATIONS_RELU6_HPP

#include "nmtools/array/functional/functor.hpp"
#include "nmtools/array/view/activations/relu6.hpp"

namespace nmtools::functional
{
    constexpr inline auto relu6 = functor_t(unary_fmap_t{
        [](const auto&...args){
            return view::relu6(args...);
    }});
} // namespace nmtools::functional


#endif // NMTOOLS_ARRAY_FUNCTIONAL_ACTIVATIONS_RELU6_HPP