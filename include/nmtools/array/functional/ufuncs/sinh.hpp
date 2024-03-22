#ifndef NMTOOLS_ARRAY_FUNCTIONAL_UFUNCS_SINH_HPP
#define NMTOOLS_ARRAY_FUNCTIONAL_UFUNCS_SINH_HPP

#include "nmtools/array/functional/functor.hpp"
#include "nmtools/array/view/ufuncs/sinh.hpp"
#include "nmtools/array/functional/ufunc/ufunc.hpp"

namespace nmtools::functional
{
    namespace fun
    {
        using sinh = fun::unary_ufunc<view::sinh_t>;
    }

    constexpr inline auto sinh = functor_t(unary_fmap_t<fun::sinh>{});
} // namespace nmtools::functional


#endif // NMTOOLS_ARRAY_FUNCTIONAL_UFUNCS_SINH_HPP