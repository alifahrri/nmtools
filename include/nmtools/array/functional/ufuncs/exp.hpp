#ifndef NMTOOLS_ARRAY_FUNCTIONAL_UFUNCS_EXP_HPP
#define NMTOOLS_ARRAY_FUNCTIONAL_UFUNCS_EXP_HPP

#include "nmtools/array/functional/functor.hpp"
#include "nmtools/array/view/ufuncs/exp.hpp"
#include "nmtools/array/functional/ufunc/ufunc.hpp"

namespace nmtools::functional
{
    namespace fun
    {
        using exp = fun::unary_ufunc<view::exp_t>;
    }

    constexpr inline auto exp = functor_t{unary_fmap_t<fun::exp>{}};
} // namespace nmtools::functional


#endif // NMTOOLS_ARRAY_FUNCTIONAL_UFUNCS_EXP_HPP