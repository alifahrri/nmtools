#ifndef NMTOOLS_ARRAY_FUNCTIONAL_ACTIVATIONS_HARDSWISH_HPP
#define NMTOOLS_ARRAY_FUNCTIONAL_ACTIVATIONS_HARDSWISH_HPP

#include "nmtools/array/functional/functor.hpp"
#include "nmtools/array/view/activations/hardswish.hpp"
#include "nmtools/array/functional/ufunc/ufunc.hpp"

namespace nmtools::functional
{
    namespace fun
    {
        using hardswish = fun::unary_ufunc<view::hardswish_t>;
    }

    constexpr inline auto hardswish = functor_t{unary_fmap_t<fun::hardswish>{}};
} // namespace nmtools::functional


#endif // NMTOOLS_ARRAY_FUNCTIONAL_ACTIVATIONS_HARDSWISH_HPP