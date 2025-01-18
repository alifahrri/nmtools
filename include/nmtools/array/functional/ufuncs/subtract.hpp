#ifndef NMTOOLS_ARRAY_FUNCTIONAL_UFUNCS_SUBTRACT_HPP
#define NMTOOLS_ARRAY_FUNCTIONAL_UFUNCS_SUBTRACT_HPP

#include "nmtools/array/core/functor.hpp"
#include "nmtools/array/view/ufuncs/subtract.hpp"
#include "nmtools/array/functional/ufunc/accumulate.hpp"
#include "nmtools/array/functional/ufunc/reduce.hpp"
#include "nmtools/array/functional/ufunc/outer.hpp"
#include "nmtools/array/functional/ufunc/ufunc.hpp"

namespace nmtools::functional
{
    namespace fun
    {
        using subtract            = fun::broadcast_binary_ufunc<view::subtract_t<>>;
        using reduce_subtract     = fun::reduce<view::subtract_t<>>;
        using outer_subtract      = fun::outer<view::subtract_t<>>;
        using accumulate_subtract = fun::accumulate<view::subtract_t<>>;
    }

    constexpr inline auto subtract = functor_t{binary_fmap_t<fun::subtract>{}};
    constexpr inline auto reduce_subtract = functor_t{unary_fmap_t<fun::reduce_subtract>{}};
    constexpr inline auto outer_subtract = functor_t{binary_fmap_t<fun::outer_subtract>{}};
    constexpr inline auto accumulate_subtract = functor_t{unary_fmap_t<fun::accumulate_subtract>{}};
} // namespace nmtools::functional

#endif // NMTOOLS_ARRAY_FUNCTIONAL_UFUNCS_SUBTRACT_HPP