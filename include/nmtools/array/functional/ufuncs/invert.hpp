#ifndef NMTOOLS_ARRAY_FUNCTIONAL_UFUNCS_INVERT_HPP
#define NMTOOLS_ARRAY_FUNCTIONAL_UFUNCS_INVERT_HPP

#include "nmtools/array/functional/functor.hpp"
#include "nmtools/array/view/ufuncs/invert.hpp"
#include "nmtools/array/functional/ufunc/ufunc.hpp"

namespace nmtools::functional
{
    namespace fun
    {
        using invert = fun::unary_ufunc<view::invert_t>;
    }

    constexpr inline auto invert = functor_t{unary_fmap_t<fun::invert>{}};
} // namespace nmtools::functional


#endif // NMTOOLS_ARRAY_FUNCTIONAL_UFUNCS_INVERT_HPP