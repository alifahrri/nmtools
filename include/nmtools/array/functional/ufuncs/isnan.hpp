#ifndef NMTOOLS_ARRAY_FUNCTIONAL_UFUNCS_ISNAN_HPP
#define NMTOOLS_ARRAY_FUNCTIONAL_UFUNCS_ISNAN_HPP

#include "nmtools/array/core/functor.hpp"
#include "nmtools/array/view/ufuncs/isnan.hpp"
#include "nmtools/array/functional/ufunc/ufunc.hpp"

namespace nmtools::functional
{
    namespace fun
    {
        using isnan = fun::unary_ufunc<view::isnan_t>;
    }

    constexpr inline auto isnan = functor_t{unary_fmap_t<fun::isnan>{}};
} // namespace nmtools::functional


#endif // NMTOOLS_ARRAY_FUNCTIONAL_UFUNCS_ISNAN_HPP