#ifndef NMTOOLS_ARRAY_ARRAY_ACTIVATIONS_HARDSHRINK_HPP
#define NMTOOLS_ARRAY_ARRAY_ACTIVATIONS_HARDSHRINK_HPP

#include "nmtools/array/view/activations/hardshrink.hpp"
#include "nmtools/array/eval.hpp"

namespace nmtools::array
{
    /**
     * @brief Eagerly compute element-wise hardshrink function.
     * 
     * @tparam output_t 
     * @tparam context_t 
     * @tparam array_t 
     * @tparam lambda_t 
     * @param array     input array
     * @param lambda     the lambda value in hardshrink formulation
     * @param context   evaluation context
     * @param output 
     * @return NMTOOLS_UFUNC_CONSTEXPR 
     */
    template <typename output_t=none_t, typename context_t=none_t,
        typename array_t, typename lambda_t=float>
    NMTOOLS_UFUNC_CONSTEXPR
    auto hardshrink(const array_t& array, lambda_t lambda=lambda_t{0.5},
        context_t&& context=context_t{}, output_t&& output=output_t{})
    {
        auto a = view::hardshrink(array,lambda);
        return eval(a,context,output);
    } // hardshrink
} // namespace nmtools::view


#endif // NMTOOLS_ARRAY_ARRAY_ACTIVATIONS_HARDSHRINK_HPP