#ifndef NMTOOLS_ARRAY_FUNCTIONAL_UFUNCS_RECIPROCAL_HPP
#define NMTOOLS_ARRAY_FUNCTIONAL_UFUNCS_RECIPROCAL_HPP

#include "nmtools/array/functional/functor.hpp"
#include "nmtools/array/view/ufuncs/reciprocal.hpp"
#include "nmtools/array/functional/ufunc/ufunc.hpp"

namespace nmtools::functional
{
    namespace fun
    {
        using reciprocal = fun::unary_ufunc<view::reciprocal_t>;
    }

    constexpr inline auto reciprocal = functor_t(unary_fmap_t<fun::reciprocal>{});
} // namespace nmtools::functional


#endif // NMTOOLS_ARRAY_FUNCTIONAL_UFUNCS_RECIPROCAL_HPP