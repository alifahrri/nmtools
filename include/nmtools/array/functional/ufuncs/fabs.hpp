#ifndef NMTOOLS_ARRAY_FUNCTIONAL_UFUNCS_FABS_HPP
#define NMTOOLS_ARRAY_FUNCTIONAL_UFUNCS_FABS_HPP

#include "nmtools/array/functional/functor.hpp"
#include "nmtools/array/view/ufuncs/fabs.hpp"
#include "nmtools/array/functional/ufunc/ufunc.hpp"

namespace nmtools::functional
{
    namespace fun
    {
        using fabs = fun::unary_ufunc<view::fabs_t>;
    }

    constexpr inline auto fabs = functor_t(unary_fmap_t<fun::fabs>{});
} // namespace nmtools::functional


#endif // NMTOOLS_ARRAY_FUNCTIONAL_UFUNCS_FABS_HPP