#ifndef NMTOOLS_ARRAY_FUNCTIONAL_ACTIVATIONS_MISH_HPP
#define NMTOOLS_ARRAY_FUNCTIONAL_ACTIVATIONS_MISH_HPP

#include "nmtools/array/functional/functor.hpp"
#include "nmtools/array/view/activations/mish.hpp"
#include "nmtools/array/functional/ufunc/ufunc.hpp"

namespace nmtools::functional
{
    namespace fun
    {
        using mish = fun::unary_ufunc<view::mish_t>;
    }

    constexpr inline auto mish = functor_t{unary_fmap_t<fun::mish>{}};
} // namespace nmtools::functional


#endif // NMTOOLS_ARRAY_FUNCTIONAL_ACTIVATIONS_MISH_HPP