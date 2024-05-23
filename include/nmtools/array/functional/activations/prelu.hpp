#ifndef NMTOOLS_ARRAY_FUNCTIONAL_ACTIVATIONS_PRELU_HPP
#define NMTOOLS_ARRAY_FUNCTIONAL_ACTIVATIONS_PRELU_HPP

#include "nmtools/array/functional/functor.hpp"
#include "nmtools/array/view/activations/prelu.hpp"
#include "nmtools/array/functional/ufunc/ufunc.hpp"

namespace nmtools::functional
{
    namespace fun
    {
        using prelu = fun::unary_ufunc<view::prelu_t<>>;
    }
    constexpr inline auto prelu = functor_t{unary_fmap_t<fun::prelu>{}};
} // namespace nmtools::functional


#endif // NMTOOLS_ARRAY_FUNCTIONAL_ACTIVATIONS_PRELU_HPP