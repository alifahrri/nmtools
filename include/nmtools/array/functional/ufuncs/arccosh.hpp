#ifndef NMTOOLS_ARRAY_FUNCTIONAL_UFUNCS_ARCCOSH_HPP
#define NMTOOLS_ARRAY_FUNCTIONAL_UFUNCS_ARCCOSH_HPP

#include "nmtools/array/functional/functor.hpp"
#include "nmtools/array/view/ufuncs/arccosh.hpp"
#include "nmtools/array/functional/ufunc/ufunc.hpp"

namespace nmtools::functional
{
    namespace fun
    {
        using arccosh = fun::unary_ufunc<view::arccosh_t>;
    }

    constexpr inline auto arccosh = functor_t(unary_fmap_t<fun::arccosh>{});
} // namespace nmtools::functional


#endif // NMTOOLS_ARRAY_FUNCTIONAL_UFUNCS_ARCCOSH_HPP