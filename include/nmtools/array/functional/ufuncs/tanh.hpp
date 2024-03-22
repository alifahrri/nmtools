#ifndef NMTOOLS_ARRAY_FUNCTIONAL_UFUNCS_TANH_HPP
#define NMTOOLS_ARRAY_FUNCTIONAL_UFUNCS_TANH_HPP

#include "nmtools/array/functional/functor.hpp"
#include "nmtools/array/view/ufuncs/tanh.hpp"
#include "nmtools/array/functional/ufunc/ufunc.hpp"

namespace nmtools::functional
{
    namespace fun
    {
        using tanh = fun::unary_ufunc<view::tanh_t>;
    }

    constexpr inline auto tanh = functor_t(unary_fmap_t<fun::tanh>{});
} // namespace nmtools::functional


#endif // NMTOOLS_ARRAY_FUNCTIONAL_UFUNCS_TANH_HPP