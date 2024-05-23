#ifndef NMTOOLS_ARRAY_FUNCTIONAL_UFUNCS_COS_HPP
#define NMTOOLS_ARRAY_FUNCTIONAL_UFUNCS_COS_HPP

#include "nmtools/array/functional/functor.hpp"
#include "nmtools/array/view/ufuncs/cos.hpp"
#include "nmtools/array/functional/ufunc/ufunc.hpp"

namespace nmtools::functional
{
    namespace fun
    {
        using cos = fun::unary_ufunc<view::cos_t>;
    }

    constexpr inline auto cos = functor_t{unary_fmap_t<fun::cos>{}};
} // namespace nmtools::functional


#endif // NMTOOLS_ARRAY_FUNCTIONAL_UFUNCS_COS_HPP