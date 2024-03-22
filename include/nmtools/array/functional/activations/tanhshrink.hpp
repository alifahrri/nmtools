#ifndef NMTOOLS_ARRAY_FUNCTIONAL_ACTIVATIONS_TANHSHRINK_HPP
#define NMTOOLS_ARRAY_FUNCTIONAL_ACTIVATIONS_TANHSHRINK_HPP

#include "nmtools/array/functional/functor.hpp"
#include "nmtools/array/view/activations/tanhshrink.hpp"
#include "nmtools/array/functional/ufunc/ufunc.hpp"

namespace nmtools::functional
{
    namespace fun
    {
        using tanhshrink = fun::unary_ufunc<view::tanhshrink_t>;
    }

    constexpr inline auto tanhshrink = functor_t(unary_fmap_t<fun::tanhshrink>{});
} // namespace nmtools::functional


#endif // NMTOOLS_ARRAY_FUNCTIONAL_ACTIVATIONS_TANHSHRINK_HPP