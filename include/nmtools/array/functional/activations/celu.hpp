#ifndef NMTOOLS_ARRAY_FUNCTIONAL_ACTIVATIONS_CELU_HPP
#define NMTOOLS_ARRAY_FUNCTIONAL_ACTIVATIONS_CELU_HPP

#include "nmtools/array/functional/functor.hpp"
#include "nmtools/array/view/activations/celu.hpp"
#include "nmtools/array/functional/ufunc/ufunc.hpp"

namespace nmtools::functional
{
    namespace fun
    {
        using celu = fun::unary_ufunc<view::celu_t<>>;
    }

    // we want celu[alpha] to works, so do not use fun::unary_ufunc<view::celu_t<>>;
    constexpr inline auto celu = functor_t{unary_fmap_t<fun::celu>{}};

    // using lambda breaks boost type index: Type name demangling failed
    // constexpr inline auto celu = functor_t(unary_fmap_t<decltype(celu_fun)>{celu_fun});
} // namespace nmtools::functional


#endif // NMTOOLS_ARRAY_FUNCTIONAL_ACTIVATIONS_CELU_HPP