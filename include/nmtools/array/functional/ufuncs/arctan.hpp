#ifndef NMTOOLS_ARRAY_FUNCTIONAL_UFUNCS_ARCTAN_HPP
#define NMTOOLS_ARRAY_FUNCTIONAL_UFUNCS_ARCTAN_HPP

#include "nmtools/array/functional/functor.hpp"
#include "nmtools/array/view/ufuncs/arctan.hpp"
#include "nmtools/array/functional/ufunc/ufunc.hpp"

namespace nmtools::functional
{
    namespace fun
    {
        using arctan = fun::unary_ufunc<view::arctan_t>;
    }

    constexpr inline auto arctan = functor_t{unary_fmap_t<fun::arctan>{}};
} // namespace nmtools::functional


#endif // NMTOOLS_ARRAY_FUNCTIONAL_UFUNCS_ARCTAN_HPP