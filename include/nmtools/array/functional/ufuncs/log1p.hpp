#ifndef NMTOOLS_ARRAY_FUNCTIONAL_UFUNCS_LOG1P_HPP
#define NMTOOLS_ARRAY_FUNCTIONAL_UFUNCS_LOG1P_HPP

#include "nmtools/array/functional/functor.hpp"
#include "nmtools/array/view/ufuncs/log1p.hpp"
#include "nmtools/array/functional/ufunc/ufunc.hpp"

namespace nmtools::functional
{
    namespace fun
    {
        using log1p = fun::unary_ufunc<view::log1p_t>;
    }

    constexpr inline auto log1p = functor_t(unary_fmap_t<fun::log1p>{});
} // namespace nmtools::functional


#endif // NMTOOLS_ARRAY_FUNCTIONAL_UFUNCS_LOG1P_HPP