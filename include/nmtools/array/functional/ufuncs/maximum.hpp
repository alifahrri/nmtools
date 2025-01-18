#ifndef NMTOOLS_ARRAY_FUNCTIONAL_UFUNCS_MAXIMUM_HPP
#define NMTOOLS_ARRAY_FUNCTIONAL_UFUNCS_MAXIMUM_HPP

#include "nmtools/array/core/functor.hpp"
#include "nmtools/array/view/ufuncs/maximum.hpp"
#include "nmtools/array/functional/ufunc/accumulate.hpp"
#include "nmtools/array/functional/ufunc/reduce.hpp"
#include "nmtools/array/functional/ufunc/outer.hpp"
#include "nmtools/array/functional/ufunc/ufunc.hpp"

namespace nmtools::functional
{
    namespace fun
    {
        using maximum            = fun::broadcast_binary_ufunc<view::maximum_t<>>;
        using reduce_maximum     = fun::reduce<view::maximum_t<>>;
        using outer_maximum      = fun::outer<view::maximum_t<>>;
        using accumulate_maximum = fun::accumulate<view::maximum_t<>>;
    }

    constexpr inline auto maximum = functor_t{binary_fmap_t<fun::maximum>{}};
    constexpr inline auto reduce_maximum = functor_t{unary_fmap_t<fun::reduce_maximum>{}};
    constexpr inline auto outer_maximum = functor_t{binary_fmap_t<fun::outer_maximum>{}};
    constexpr inline auto accumulate_maximum = functor_t{unary_fmap_t<fun::accumulate_maximum>{}};
} // namespace nmtools::functional

#endif // NMTOOLS_ARRAY_FUNCTIONAL_UFUNCS_MAXIMUM_HPP