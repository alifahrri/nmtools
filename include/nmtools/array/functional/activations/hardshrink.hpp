#ifndef NMTOOLS_ARRAY_FUNCTIONAL_ACTIVATIONS_HARDSHRINK_HPP
#define NMTOOLS_ARRAY_FUNCTIONAL_ACTIVATIONS_HARDSHRINK_HPP

#include "nmtools/array/core/functor.hpp"
#include "nmtools/array/view/activations/hardshrink.hpp"
#include "nmtools/array/functional/ufunc/ufunc.hpp"

namespace nmtools::functional
{
    namespace fun
    {
        using hardshrink = fun::unary_ufunc<view::hardshrink_t<>>;
    }

    constexpr inline auto hardshrink = functor_t{unary_fmap_t<fun::hardshrink>{}};
} // namespace nmtools::functional


#endif // NMTOOLS_ARRAY_FUNCTIONAL_ACTIVATIONS_HARDSHRINK_HPP