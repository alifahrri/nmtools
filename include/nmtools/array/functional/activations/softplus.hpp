#ifndef NMTOOLS_ARRAY_FUNCTIONAL_ACTIVATIONS_SOFTPLUS_HPP
#define NMTOOLS_ARRAY_FUNCTIONAL_ACTIVATIONS_SOFTPLUS_HPP

#include "nmtools/array/core/functor.hpp"
#include "nmtools/array/view/activations/softplus.hpp"
#include "nmtools/array/functional/ufunc/ufunc.hpp"

namespace nmtools::functional
{
    namespace fun
    {
        using softplus = fun::unary_ufunc<view::softplus_t<>>;
    }

    constexpr inline auto softplus = functor_t{unary_fmap_t<fun::softplus>{}};
} // namespace nmtools::functional


#endif // NMTOOLS_ARRAY_FUNCTIONAL_ACTIVATIONS_SOFTPLUS_HPP