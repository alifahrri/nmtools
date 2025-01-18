#ifndef NMTOOLS_ARRAY_FUNCTIONAL_UFUNCS_LOG_HPP
#define NMTOOLS_ARRAY_FUNCTIONAL_UFUNCS_LOG_HPP

#include "nmtools/array/core/functor.hpp"
#include "nmtools/array/view/ufuncs/log.hpp"
#include "nmtools/array/functional/ufunc/ufunc.hpp"

namespace nmtools::functional
{
    namespace fun
    {
        using log = fun::unary_ufunc<view::log_t>;
    }

    constexpr inline auto log = functor_t{unary_fmap_t<fun::log>{}};
} // namespace nmtools::functional


#endif // NMTOOLS_ARRAY_FUNCTIONAL_UFUNCS_LOG_HPP