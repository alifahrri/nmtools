#ifndef NMTOOLS_ARRAY_FUNCTIONAL_ACTIVATIONS_SILU_HPP
#define NMTOOLS_ARRAY_FUNCTIONAL_ACTIVATIONS_SILU_HPP

#include "nmtools/array/functional/functor.hpp"
#include "nmtools/array/view/activations/silu.hpp"
#include "nmtools/array/functional/ufunc/ufunc.hpp"

namespace nmtools::functional
{
    namespace fun
    {
        using silu = fun::unary_ufunc<view::silu_t>;
    }

    constexpr inline auto silu = functor_t{unary_fmap_t<fun::silu>{}};
} // namespace nmtools::functional


#endif // NMTOOLS_ARRAY_FUNCTIONAL_ACTIVATIONS_SILU_HPP