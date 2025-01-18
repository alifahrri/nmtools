#ifndef NMTOOLS_ARRAY_FUNCTIONAL_ACTIVATIONS_RELU_HPP
#define NMTOOLS_ARRAY_FUNCTIONAL_ACTIVATIONS_RELU_HPP

#include "nmtools/array/core/functor.hpp"
#include "nmtools/array/view/activations/relu.hpp"
#include "nmtools/array/functional/ufunc/ufunc.hpp"

namespace nmtools::functional
{
    namespace fun
    {
        using relu = fun::unary_ufunc<view::relu_t>;
    } // namespace fun

    constexpr inline auto relu = functor_t{unary_fmap_t<fun::relu>{}};
} // namespace nmtools::functional


#endif // NMTOOLS_ARRAY_FUNCTIONAL_ACTIVATIONS_RELU_HPP