#ifndef NMTOOLS_ARRAY_FUNCTIONAL_UFUNCS_MINIMUM_HPP
#define NMTOOLS_ARRAY_FUNCTIONAL_UFUNCS_MINIMUM_HPP

#include "nmtools/array/functional/functor.hpp"
#include "nmtools/array/view/ufuncs/minimum.hpp"
#include "nmtools/array/functional/ufunc/accumulate.hpp"
#include "nmtools/array/functional/ufunc/reduce.hpp"
#include "nmtools/array/functional/ufunc/outer.hpp"
#include "nmtools/array/functional/ufunc/ufunc.hpp"

namespace nmtools::functional
{
    namespace fun
    {
        using minimum            = fun::broadcast_binary_ufunc<view::minimum_t<>>;
        using reduce_minimum     = fun::reduce<view::minimum_t<>>;
        using outer_minimum      = fun::outer<view::minimum_t<>>;
        using accumulate_minimum = fun::accumulate<view::minimum_t<>>;
    }

    constexpr inline auto minimum = functor_t{binary_fmap_t<fun::minimum>{}};
    constexpr inline auto reduce_minimum = functor_t{unary_fmap_t<fun::reduce_minimum>{}};
    constexpr inline auto outer_minimum = functor_t{binary_fmap_t<fun::outer_minimum>{}};
    constexpr inline auto accumulate_minimum = functor_t{unary_fmap_t<fun::accumulate_minimum>{}};
} // namespace nmtools::functional

#endif // NMTOOLS_ARRAY_FUNCTIONAL_UFUNCS_MINIMUM_HPP