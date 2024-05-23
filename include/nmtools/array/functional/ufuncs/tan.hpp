#ifndef NMTOOLS_ARRAY_FUNCTIONAL_UFUNCS_TAN_HPP
#define NMTOOLS_ARRAY_FUNCTIONAL_UFUNCS_TAN_HPP

#include "nmtools/array/functional/functor.hpp"
#include "nmtools/array/view/ufuncs/tan.hpp"
#include "nmtools/array/functional/ufunc/ufunc.hpp"

namespace nmtools::functional
{
    namespace fun
    {
        using tan = fun::unary_ufunc<view::tan_t>;
    }

    constexpr inline auto tan = functor_t{unary_fmap_t<fun::tan>{}};
} // namespace nmtools::functional


#endif // NMTOOLS_ARRAY_FUNCTIONAL_UFUNCS_TAN_HPP