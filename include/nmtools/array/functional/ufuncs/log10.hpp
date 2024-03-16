#ifndef NMTOOLS_ARRAY_FUNCTIONAL_UFUNCS_LOG10_HPP
#define NMTOOLS_ARRAY_FUNCTIONAL_UFUNCS_LOG10_HPP

#include "nmtools/array/functional/functor.hpp"
#include "nmtools/array/view/ufuncs/log10.hpp"
#include "nmtools/array/functional/ufunc/ufunc.hpp"

namespace nmtools::functional
{
    namespace fun
    {
        using log10 = fun::unary_ufunc<view::log10_t>;
    }

    constexpr inline auto log10 = functor_t(unary_fmap_t<fun::log10>{});
} // namespace nmtools::functional


#endif // NMTOOLS_ARRAY_FUNCTIONAL_UFUNCS_LOG10_HPP