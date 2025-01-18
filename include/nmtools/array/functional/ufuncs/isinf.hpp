#ifndef NMTOOLS_ARRAY_FUNCTIONAL_UFUNCS_ISINF_HPP
#define NMTOOLS_ARRAY_FUNCTIONAL_UFUNCS_ISINF_HPP

#include "nmtools/array/core/functor.hpp"
#include "nmtools/array/view/ufuncs/isinf.hpp"
#include "nmtools/array/functional/ufunc/ufunc.hpp"

namespace nmtools::functional
{
    namespace fun
    {
        using isinf = fun::unary_ufunc<view::isinf_t>;
    }

    constexpr inline auto isinf = functor_t{unary_fmap_t<fun::isinf>{}};
} // namespace nmtools::functional


#endif // NMTOOLS_ARRAY_FUNCTIONAL_UFUNCS_ISINF_HPP