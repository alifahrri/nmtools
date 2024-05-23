#ifndef NMTOOLS_ARRAY_FUNCTIONAL_UFUNCS_ARCSIN_HPP
#define NMTOOLS_ARRAY_FUNCTIONAL_UFUNCS_ARCSIN_HPP

#include "nmtools/array/functional/functor.hpp"
#include "nmtools/array/view/ufuncs/arcsin.hpp"
#include "nmtools/array/functional/ufunc/ufunc.hpp"

namespace nmtools::functional
{
    namespace fun
    {
        using arcsin = fun::unary_ufunc<view::arcsin_t>;
    }

    constexpr inline auto arcsin = functor_t{unary_fmap_t<fun::arcsin>{}};
} // namespace nmtools::functional


#endif // NMTOOLS_ARRAY_FUNCTIONAL_UFUNCS_ARCSIN_HPP