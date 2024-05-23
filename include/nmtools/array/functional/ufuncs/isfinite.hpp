#ifndef NMTOOLS_ARRAY_FUNCTIONAL_UFUNCS_ISFINITE_HPP
#define NMTOOLS_ARRAY_FUNCTIONAL_UFUNCS_ISFINITE_HPP

#include "nmtools/array/functional/functor.hpp"
#include "nmtools/array/view/ufuncs/isfinite.hpp"
#include "nmtools/array/functional/ufunc/ufunc.hpp"

namespace nmtools::functional
{
    namespace fun
    {
        using isfinite = fun::unary_ufunc<view::isfinite_t>;
    }

    constexpr inline auto isfinite = functor_t{unary_fmap_t<fun::isfinite>{}};
} // namespace nmtools::functional


#endif // NMTOOLS_ARRAY_FUNCTIONAL_UFUNCS_ISFINITE_HPP