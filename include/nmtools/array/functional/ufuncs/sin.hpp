#ifndef NMTOOLS_ARRAY_FUNCTIONAL_UFUNCS_SIN_HPP
#define NMTOOLS_ARRAY_FUNCTIONAL_UFUNCS_SIN_HPP

#include "nmtools/array/core/functor.hpp"
#include "nmtools/array/view/ufuncs/sin.hpp"
#include "nmtools/array/functional/ufunc/ufunc.hpp"

namespace nmtools::functional
{
    namespace fun
    {
        using sin = fun::unary_ufunc<view::sin_t>;
    }

    constexpr inline auto sin = functor_t{unary_fmap_t<fun::sin>{}};
} // namespace nmtools::functional


#endif // NMTOOLS_ARRAY_FUNCTIONAL_UFUNCS_SIN_HPP