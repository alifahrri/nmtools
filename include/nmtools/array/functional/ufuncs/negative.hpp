#ifndef NMTOOLS_ARRAY_FUNCTIONAL_UFUNCS_NEGATIVE_HPP
#define NMTOOLS_ARRAY_FUNCTIONAL_UFUNCS_NEGATIVE_HPP

#include "nmtools/array/functional/functor.hpp"
#include "nmtools/array/view/ufuncs/negative.hpp"
#include "nmtools/array/functional/ufunc/ufunc.hpp"

namespace nmtools::functional
{
    namespace fun
    {
        using negative = fun::unary_ufunc<view::negative_t>;
    }

    constexpr inline auto negative = functor_t(unary_fmap_t<fun::negative>{});
} // namespace nmtools::functional


#endif // NMTOOLS_ARRAY_FUNCTIONAL_UFUNCS_NEGATIVE_HPP