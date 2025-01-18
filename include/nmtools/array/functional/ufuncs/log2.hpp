#ifndef NMTOOLS_ARRAY_FUNCTIONAL_UFUNCS_LOG2_HPP
#define NMTOOLS_ARRAY_FUNCTIONAL_UFUNCS_LOG2_HPP

#include "nmtools/array/core/functor.hpp"
#include "nmtools/array/view/ufuncs/log2.hpp"
#include "nmtools/array/functional/ufunc/ufunc.hpp"

namespace nmtools::functional
{
    namespace fun
    {
        using log2 = fun::unary_ufunc<view::log2_t>;
    }

    constexpr inline auto log2 = functor_t{unary_fmap_t<fun::log2>{}};
} // namespace nmtools::functional


#endif // NMTOOLS_ARRAY_FUNCTIONAL_UFUNCS_LOG2_HPP