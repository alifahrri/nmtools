#ifndef NMTOOLS_ARRAY_FUNCTIONAL_UFUNCS_FLOOR_HPP
#define NMTOOLS_ARRAY_FUNCTIONAL_UFUNCS_FLOOR_HPP

#include "nmtools/array/core/functor.hpp"
#include "nmtools/array/view/ufuncs/floor.hpp"
#include "nmtools/array/functional/ufunc/ufunc.hpp"

namespace nmtools::functional
{
    namespace fun
    {
        using floor = fun::unary_ufunc<view::floor_t>;
    }

    constexpr inline auto floor = functor_t{unary_fmap_t<fun::floor>{}};
} // namespace nmtools::functional


#endif // NMTOOLS_ARRAY_FUNCTIONAL_UFUNCS_FLOOR_HPP