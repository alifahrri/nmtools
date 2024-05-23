#ifndef NMTOOLS_ARRAY_FUNCTIONAL_ACTIVATIONS_LEAKY_RELU_HPP
#define NMTOOLS_ARRAY_FUNCTIONAL_ACTIVATIONS_LEAKY_RELU_HPP

#include "nmtools/array/functional/functor.hpp"
#include "nmtools/array/view/activations/leaky_relu.hpp"
#include "nmtools/array/functional/ufunc/ufunc.hpp"

namespace nmtools::functional
{
    namespace fun
    {
        using leaky_relu = fun::unary_ufunc<view::leaky_relu_t<>>;
    }
    constexpr inline auto leaky_relu = functor_t{unary_fmap_t<fun::leaky_relu>{}};
} // namespace nmtools::functional


#endif // NMTOOLS_ARRAY_FUNCTIONAL_ACTIVATIONS_LEAKY_RELU_HPP