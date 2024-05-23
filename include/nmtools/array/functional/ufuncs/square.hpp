#ifndef NMTOOLS_ARRAY_FUNCTIONAL_UFUNCS_SQUARE_HPP
#define NMTOOLS_ARRAY_FUNCTIONAL_UFUNCS_SQUARE_HPP

#include "nmtools/array/functional/functor.hpp"
#include "nmtools/array/view/ufuncs/square.hpp"
#include "nmtools/array/functional/ufunc/ufunc.hpp"

namespace nmtools::functional
{
    namespace fun
    {
        using square = fun::unary_ufunc<view::square_t>;
    }

    constexpr inline auto square = functor_t{unary_fmap_t<fun::square>{}};
} // namespace nmtools::functional


#endif // NMTOOLS_ARRAY_FUNCTIONAL_UFUNCS_SQUARE_HPP