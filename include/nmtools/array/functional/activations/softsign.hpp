#ifndef NMTOOLS_ARRAY_FUNCTIONAL_ACTIVATIONS_SOFTSIGN_HPP
#define NMTOOLS_ARRAY_FUNCTIONAL_ACTIVATIONS_SOFTSIGN_HPP

#include "nmtools/array/functional/functor.hpp"
#include "nmtools/array/view/activations/softsign.hpp"
#include "nmtools/array/functional/ufunc/ufunc.hpp"

namespace nmtools::functional
{
    namespace fun
    {
        using softsign = fun::unary_ufunc<view::softsign_t>;
    }

    constexpr inline auto softsign = functor_t{unary_fmap_t<fun::softsign>{}};
} // namespace nmtools::functional


#endif // NMTOOLS_ARRAY_FUNCTIONAL_ACTIVATIONS_SOFTSIGN_HPP