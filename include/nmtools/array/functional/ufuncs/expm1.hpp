#ifndef NMTOOLS_ARRAY_FUNCTIONAL_UFUNCS_EXPM1_HPP
#define NMTOOLS_ARRAY_FUNCTIONAL_UFUNCS_EXPM1_HPP

#include "nmtools/array/functional/functor.hpp"
#include "nmtools/array/view/ufuncs/expm1.hpp"
#include "nmtools/array/functional/ufunc/ufunc.hpp"

namespace nmtools::functional
{
    namespace fun
    {
        using expm1 = fun::unary_ufunc<view::expm1_t>;
    }

    constexpr inline auto expm1 = functor_t{unary_fmap_t<fun::expm1>{}};
} // namespace nmtools::functional


#endif // NMTOOLS_ARRAY_FUNCTIONAL_UFUNCS_EXPM1_HPP