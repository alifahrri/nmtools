#ifndef NMTOOLS_ARRAY_FUNCTIONAL_UFUNCS_CEIL_HPP
#define NMTOOLS_ARRAY_FUNCTIONAL_UFUNCS_CEIL_HPP

#include "nmtools/array/functional/functor.hpp"
#include "nmtools/array/view/ufuncs/ceil.hpp"
#include "nmtools/array/functional/ufunc/ufunc.hpp"

namespace nmtools::functional
{
    namespace fun
    {
        using ceil = fun::unary_ufunc<view::ceil_t>;
    }

    constexpr inline auto ceil = functor_t{unary_fmap_t<fun::ceil>{}};
} // namespace nmtools::functional


#endif // NMTOOLS_ARRAY_FUNCTIONAL_UFUNCS_CEIL_HPP