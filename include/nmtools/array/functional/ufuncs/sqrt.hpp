#ifndef NMTOOLS_ARRAY_FUNCTIONAL_UFUNCS_SQRT_HPP
#define NMTOOLS_ARRAY_FUNCTIONAL_UFUNCS_SQRT_HPP

#include "nmtools/array/functional/functor.hpp"
#include "nmtools/array/view/ufuncs/sqrt.hpp"
#include "nmtools/array/functional/ufunc/ufunc.hpp"

namespace nmtools::functional
{
    namespace fun
    {
        using sqrt = fun::unary_ufunc<view::sqrt_t>;
    }

    constexpr inline auto sqrt = functor_t{unary_fmap_t<fun::sqrt>{}};
} // namespace nmtools::functional


#endif // NMTOOLS_ARRAY_FUNCTIONAL_UFUNCS_SQRT_HPP