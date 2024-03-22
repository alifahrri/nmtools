#ifndef NMTOOLS_ARRAY_FUNCTIONAL_ACTIVATIONS_RELU6_HPP
#define NMTOOLS_ARRAY_FUNCTIONAL_ACTIVATIONS_RELU6_HPP

#include "nmtools/array/functional/functor.hpp"
#include "nmtools/array/view/activations/relu6.hpp"
#include "nmtools/array/functional/ufunc/ufunc.hpp"

namespace nmtools::functional
{
    namespace fun
    {
        using relu6 = fun::unary_ufunc<view::relu6_t>;
    } // namespace fun

    constexpr inline auto relu6 = functor_t(unary_fmap_t<fun::relu6>{});
} // namespace nmtools::functional


#endif // NMTOOLS_ARRAY_FUNCTIONAL_ACTIVATIONS_RELU6_HPP