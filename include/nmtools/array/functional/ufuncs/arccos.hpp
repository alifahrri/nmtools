#ifndef NMTOOLS_ARRAY_FUNCTIONAL_UFUNCS_ARCCOS_HPP
#define NMTOOLS_ARRAY_FUNCTIONAL_UFUNCS_ARCCOS_HPP

#include "nmtools/array/functional/functor.hpp"
#include "nmtools/array/view/ufuncs/arccos.hpp"
#include "nmtools/array/functional/ufunc/ufunc.hpp"

namespace nmtools::functional
{
    namespace fun
    {
        using arccos = fun::unary_ufunc<view::arccos_t>;
    }

    constexpr inline auto arccos = functor_t(unary_fmap_t<fun::arccos>{});
} // namespace nmtools::functional


#endif // NMTOOLS_ARRAY_FUNCTIONAL_UFUNCS_ARCCOS_HPP