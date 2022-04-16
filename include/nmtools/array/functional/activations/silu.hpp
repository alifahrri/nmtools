#ifndef NMTOOLS_ARRAY_FUNCTIONAL_ACTIVATIONS_SILU_HPP
#define NMTOOLS_ARRAY_FUNCTIONAL_ACTIVATIONS_SILU_HPP

#include "nmtools/array/functional/functor.hpp"
#include "nmtools/array/view/activations/silu.hpp"

namespace nmtools::functional
{
    constexpr inline auto silu = functor_t(unary_fmap_t{
        [](const auto&...args){
            return view::silu(args...);
    }});
} // namespace nmtools::functional


#endif // NMTOOLS_ARRAY_FUNCTIONAL_ACTIVATIONS_SILU_HPP