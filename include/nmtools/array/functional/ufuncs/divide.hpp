#ifndef NMTOOLS_ARRAY_FUNCTIONAL_UFUNCS_DIVIDE_HPP
#define NMTOOLS_ARRAY_FUNCTIONAL_UFUNCS_DIVIDE_HPP

#include "nmtools/array/functional/functor.hpp"
#include "nmtools/array/view/ufuncs/divide.hpp"
#include "nmtools/array/functional/ufunc/ufunc.hpp"

namespace nmtools::functional
{
    namespace fun
    {
        using divide = fun::broadcast_binary_ufunc<view::divide_t>;
    }

    constexpr inline auto divide = functor_t{binary_fmap_t<fun::divide>{}};
} // namespace nmtools::functional

#endif // NMTOOLS_ARRAY_FUNCTIONAL_UFUNCS_DIVIDE_HPP