#ifndef NMTOOLS_ARRAY_FUNCTIONAL_UFUNCS_ARCSINH_HPP
#define NMTOOLS_ARRAY_FUNCTIONAL_UFUNCS_ARCSINH_HPP

#include "nmtools/array/core/functor.hpp"
#include "nmtools/array/view/ufuncs/arcsinh.hpp"
#include "nmtools/array/functional/ufunc/ufunc.hpp"

namespace nmtools::functional
{
    namespace fun
    {
        using arcsinh = fun::unary_ufunc<view::arcsinh_t>;
    }

    constexpr inline auto arcsinh = functor_t{unary_fmap_t<fun::arcsinh>{}};
} // namespace nmtools::functional


#endif // NMTOOLS_ARRAY_FUNCTIONAL_UFUNCS_ARCSINH_HPP