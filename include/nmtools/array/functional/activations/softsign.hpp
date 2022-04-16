#ifndef NMTOOLS_ARRAY_FUNCTIONAL_ACTIVATIONS_SOFTSIGN_HPP
#define NMTOOLS_ARRAY_FUNCTIONAL_ACTIVATIONS_SOFTSIGN_HPP

#include "nmtools/array/functional/functor.hpp"
#include "nmtools/array/view/activations/softsign.hpp"

namespace nmtools::functional
{
    constexpr inline auto softsign = functor_t(unary_fmap_t{
        [](const auto&...args){
            return view::softsign(args...);
    }});
} // namespace nmtools::functional


#endif // NMTOOLS_ARRAY_FUNCTIONAL_ACTIVATIONS_SOFTSIGN_HPP