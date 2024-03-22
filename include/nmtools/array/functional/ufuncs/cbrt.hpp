#ifndef NMTOOLS_ARRAY_FUNCTIONAL_UFUNCS_CBRT_HPP
#define NMTOOLS_ARRAY_FUNCTIONAL_UFUNCS_CBRT_HPP

#include "nmtools/array/functional/functor.hpp"
#include "nmtools/array/view/ufuncs/cbrt.hpp"
#include "nmtools/array/functional/ufunc/ufunc.hpp"

namespace nmtools::functional
{
    namespace fun
    {
        using cbrt = fun::unary_ufunc<view::cbrt_t>;
    }

    constexpr inline auto cbrt = functor_t(unary_fmap_t<fun::cbrt>{});
} // namespace nmtools::functional


#endif // NMTOOLS_ARRAY_FUNCTIONAL_UFUNCS_CBRT_HPP