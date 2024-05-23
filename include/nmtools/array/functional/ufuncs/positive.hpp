#ifndef NMTOOLS_ARRAY_FUNCTIONAL_UFUNCS_POSITIVE_HPP
#define NMTOOLS_ARRAY_FUNCTIONAL_UFUNCS_POSITIVE_HPP

#include "nmtools/array/functional/functor.hpp"
#include "nmtools/array/view/ufuncs/positive.hpp"
#include "nmtools/array/functional/ufunc/ufunc.hpp"

namespace nmtools::functional
{
    namespace fun
    {
        using positive = fun::unary_ufunc<view::positive_t>;
    }

    constexpr inline auto positive = functor_t{unary_fmap_t<fun::positive>{}};
} // namespace nmtools::functional


#endif // NMTOOLS_ARRAY_FUNCTIONAL_UFUNCS_POSITIVE_HPP