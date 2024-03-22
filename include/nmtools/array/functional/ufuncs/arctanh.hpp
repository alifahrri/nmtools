#ifndef NMTOOLS_ARRAY_FUNCTIONAL_UFUNCS_ARCTANH_HPP
#define NMTOOLS_ARRAY_FUNCTIONAL_UFUNCS_ARCTANH_HPP

#include "nmtools/array/functional/functor.hpp"
#include "nmtools/array/view/ufuncs/arctanh.hpp"
#include "nmtools/array/functional/ufunc/ufunc.hpp"

namespace nmtools::functional
{
    namespace fun
    {
        using arctanh = fun::unary_ufunc<view::arctanh_t>;
    }

    constexpr inline auto arctanh = functor_t(unary_fmap_t<fun::arctanh>{});
} // namespace nmtools::functional


#endif // NMTOOLS_ARRAY_FUNCTIONAL_UFUNCS_ARCTANH_HPP