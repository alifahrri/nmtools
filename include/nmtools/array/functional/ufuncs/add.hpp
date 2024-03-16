#ifndef NMTOOLS_ARRAY_FUNCTIONAL_UFUNCS_ADD_HPP
#define NMTOOLS_ARRAY_FUNCTIONAL_UFUNCS_ADD_HPP

#include "nmtools/array/functional/functor.hpp"
#include "nmtools/array/view/ufuncs/add.hpp"
#include "nmtools/array/functional/ufunc/accumulate.hpp"
#include "nmtools/array/functional/ufunc/reduce.hpp"
#include "nmtools/array/functional/ufunc/outer.hpp"
#include "nmtools/array/functional/ufunc/ufunc.hpp"

namespace nmtools::functional
{
    namespace fun
    {
        using add            = fun::broadcast_binary_ufunc<view::add_t<>>;
        using reduce_add     = fun::reduce<view::add_t<>>;
        using outer_add      = fun::outer<view::add_t<>>;
        using accumulate_add = fun::accumulate<view::add_t<>>;
    }

    constexpr inline auto add = functor_t(binary_fmap_t<fun::add>{});
    constexpr inline auto reduce_add = functor_t(unary_fmap_t<fun::reduce_add>{});
    constexpr inline auto outer_add = functor_t(binary_fmap_t<fun::outer_add>{});
    constexpr inline auto accumulate_add = functor_t(unary_fmap_t<fun::accumulate_add>{});
} // namespace nmtools::functional

#endif // NMTOOLS_ARRAY_FUNCTIONAL_UFUNCS_ADD_HPP