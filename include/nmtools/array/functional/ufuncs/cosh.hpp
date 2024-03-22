#ifndef NMTOOLS_ARRAY_FUNCTIONAL_UFUNCS_COSH_HPP
#define NMTOOLS_ARRAY_FUNCTIONAL_UFUNCS_COSH_HPP

#include "nmtools/array/functional/functor.hpp"
#include "nmtools/array/view/ufuncs/cosh.hpp"
#include "nmtools/array/functional/ufunc/ufunc.hpp"

namespace nmtools::functional
{
    namespace fun
    {
        using cosh = fun::unary_ufunc<view::cosh_t>;
    }

    constexpr inline auto cosh = functor_t(unary_fmap_t<fun::cosh>{});
} // namespace nmtools::functional


#endif // NMTOOLS_ARRAY_FUNCTIONAL_UFUNCS_COSH_HPP