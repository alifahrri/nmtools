#ifndef NMTOOLS_ARRAY_FUNCTIONAL_UFUNCS_MULTIPLY_HPP
#define NMTOOLS_ARRAY_FUNCTIONAL_UFUNCS_MULTIPLY_HPP

#include "nmtools/array/core/functor.hpp"
#include "nmtools/array/view/ufuncs/multiply.hpp"
#include "nmtools/array/functional/ufunc/accumulate.hpp"
#include "nmtools/array/functional/ufunc/reduce.hpp"
#include "nmtools/array/functional/ufunc/outer.hpp"
#include "nmtools/array/functional/ufunc/ufunc.hpp"

namespace nmtools::functional
{
    namespace fun
    {
        using multiply            = fun::broadcast_binary_ufunc<view::multiply_t<>>;
        using reduce_multiply     = fun::reduce<view::multiply_t<>>;
        using outer_multiply      = fun::outer<view::multiply_t<>>;
        using accumulate_multiply = fun::accumulate<view::multiply_t<>>;
    }

    constexpr inline auto multiply = functor_t{binary_fmap_t<fun::multiply>{}};
    constexpr inline auto reduce_multiply = functor_t{unary_fmap_t<fun::reduce_multiply>{}};
    constexpr inline auto outer_multiply = functor_t{binary_fmap_t<fun::outer_multiply>{}};
    constexpr inline auto accumulate_multiply = functor_t{unary_fmap_t<fun::accumulate_multiply>{}};
} // namespace nmtools::functional

#endif // NMTOOLS_ARRAY_FUNCTIONAL_UFUNCS_MULTIPLY_HPP