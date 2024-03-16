#ifndef NMTOOLS_ARRAY_FUNCTIONAL_UFUNCS_RINT_HPP
#define NMTOOLS_ARRAY_FUNCTIONAL_UFUNCS_RINT_HPP

#include "nmtools/array/functional/functor.hpp"
#include "nmtools/array/view/ufuncs/rint.hpp"
#include "nmtools/array/functional/ufunc/ufunc.hpp"

namespace nmtools::functional
{
    namespace fun
    {
        using rint = fun::unary_ufunc<view::rint_t>;
    }

    constexpr inline auto rint = functor_t(unary_fmap_t<fun::rint>{});
} // namespace nmtools::functional


#endif // NMTOOLS_ARRAY_FUNCTIONAL_UFUNCS_RINT_HPP