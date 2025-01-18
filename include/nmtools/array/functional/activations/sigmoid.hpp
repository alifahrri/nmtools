#ifndef NMTOOLS_ARRAY_FUNCTIONAL_ACTIVATIONS_SIGMOID_HPP
#define NMTOOLS_ARRAY_FUNCTIONAL_ACTIVATIONS_SIGMOID_HPP

#include "nmtools/array/core/functor.hpp"
#include "nmtools/array/view/activations/sigmoid.hpp"
#include "nmtools/array/functional/ufunc/ufunc.hpp"

namespace nmtools::functional
{
    namespace fun
    {
        using sigmoid = fun::unary_ufunc<view::sigmoid_t>;
    }
    constexpr inline auto sigmoid = functor_t{unary_fmap_t<fun::sigmoid>{}};
} // namespace nmtools::functional


#endif // NMTOOLS_ARRAY_FUNCTIONAL_ACTIVATIONS_SIGMOID_HPP