#ifndef NMTOOLS_ARRAY_FUNCTIONAL_UFUNCS_SIGNBIT_HPP
#define NMTOOLS_ARRAY_FUNCTIONAL_UFUNCS_SIGNBIT_HPP

#include "nmtools/array/functional/functor.hpp"
#include "nmtools/array/view/ufuncs/signbit.hpp"
#include "nmtools/array/functional/ufunc/ufunc.hpp"

namespace nmtools::functional
{
    namespace fun
    {
        using signbit = fun::unary_ufunc<view::signbit_t>;
    }

    constexpr inline auto signbit = functor_t{unary_fmap_t<fun::signbit>{}};
} // namespace nmtools::functional


#endif // NMTOOLS_ARRAY_FUNCTIONAL_UFUNCS_SIGNBIT_HPP