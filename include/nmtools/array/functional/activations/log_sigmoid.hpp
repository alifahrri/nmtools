#ifndef NMTOOLS_ARRAY_FUNCTIONAL_ACTIVATIONS_LOG_SIGMOID_HPP
#define NMTOOLS_ARRAY_FUNCTIONAL_ACTIVATIONS_LOG_SIGMOID_HPP

#include "nmtools/array/functional/functor.hpp"
#include "nmtools/array/view/activations/log_sigmoid.hpp"
#include "nmtools/array/functional/ufunc/ufunc.hpp"

namespace nmtools::functional
{
    namespace fun
    {
        using log_sigmoid = fun::unary_ufunc<view::log_sigmoid_t>;
    }
    constexpr inline auto log_sigmoid = functor_t(unary_fmap_t<fun::log_sigmoid>{});
} // namespace nmtools::functional


#endif // NMTOOLS_ARRAY_FUNCTIONAL_ACTIVATIONS_LOG_SIGMOID_HPP