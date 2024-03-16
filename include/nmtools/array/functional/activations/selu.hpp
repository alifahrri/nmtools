#ifndef NMTOOLS_ARRAY_FUNCTIONAL_ACTIVATIONS_SELU_HPP
#define NMTOOLS_ARRAY_FUNCTIONAL_ACTIVATIONS_SELU_HPP

#include "nmtools/array/functional/functor.hpp"
#include "nmtools/array/view/activations/selu.hpp"
#include "nmtools/array/functional/ufunc/ufunc.hpp"

namespace nmtools::functional
{
    namespace fun
    {
        using selu = fun::unary_ufunc<view::selu_t>;
    }
    constexpr inline auto selu = functor_t(unary_fmap_t<fun::selu>{});
} // namespace nmtools::functional


#endif // NMTOOLS_ARRAY_FUNCTIONAL_ACTIVATIONS_SELU_HPP