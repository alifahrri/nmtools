#ifndef NMTOOLS_ARRAY_FUNCTIONAL_UFUNCS_EXP2_HPP
#define NMTOOLS_ARRAY_FUNCTIONAL_UFUNCS_EXP2_HPP

#include "nmtools/array/functional/functor.hpp"
#include "nmtools/array/view/ufuncs/exp2.hpp"
#include "nmtools/array/functional/ufunc/ufunc.hpp"

namespace nmtools::functional
{
    namespace fun
    {
        using exp2 = fun::unary_ufunc<view::exp2_t>;
    }

    constexpr inline auto exp2 = functor_t(unary_fmap_t<fun::exp2>{});
} // namespace nmtools::functional


#endif // NMTOOLS_ARRAY_FUNCTIONAL_UFUNCS_EXP2_HPP