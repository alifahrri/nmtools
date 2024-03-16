#ifndef NMTOOLS_ARRAY_FUNCTIONAL_ACTIVATIONS_SOFTSHRINK_HPP
#define NMTOOLS_ARRAY_FUNCTIONAL_ACTIVATIONS_SOFTSHRINK_HPP

#include "nmtools/array/functional/functor.hpp"
#include "nmtools/array/view/activations/softshrink.hpp"
#include "nmtools/array/functional/ufunc/ufunc.hpp"

namespace nmtools::functional
{
    namespace fun
    {
        using softshrink = fun::unary_ufunc<view::softshrink_t<>>;
    }
    constexpr inline auto softshrink = functor_t(unary_fmap_t<fun::softshrink>{});
} // namespace nmtools::functional


#endif // NMTOOLS_ARRAY_FUNCTIONAL_ACTIVATIONS_SOFTSHRINK_HPP