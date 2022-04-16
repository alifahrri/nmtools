#ifndef NMTOOLS_ARRAY_FUNCTIONAL_ACTIVATIONS_SOFTPLUS_HPP
#define NMTOOLS_ARRAY_FUNCTIONAL_ACTIVATIONS_SOFTPLUS_HPP

#include "nmtools/array/functional/functor.hpp"
#include "nmtools/array/view/activations/softplus.hpp"

namespace nmtools::functional
{
    constexpr inline auto softplus = functor_t(unary_fmap_t{
        [](const auto&...args){
            return view::softplus(args...);
    }});
} // namespace nmtools::functional


#endif // NMTOOLS_ARRAY_FUNCTIONAL_ACTIVATIONS_SOFTPLUS_HPP