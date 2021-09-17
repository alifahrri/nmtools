#ifndef NMTOOLS_ARRAY_ARRAY_ACTIVATIONS_SILU_HPP
#define NMTOOLS_ARRAY_ARRAY_ACTIVATIONS_SILU_HPP

#include "nmtools/array/view/activations/silu.hpp"
#include "nmtools/array/eval.hpp"

namespace nmtools::array
{
    /**
     * @brief Eagerly evaluate element-wise silu function
     * 
     * @tparam output_t 
     * @tparam context_t 
     * @tparam array_t 
     * @param array     input array
     * @param context   evaluation context
     * @param output 
     * @return NMTOOLS_UFUNC_CONSTEXPR 
     */
    template <typename output_t=none_t, typename context_t=none_t,
        typename array_t>
    NMTOOLS_UFUNC_CONSTEXPR
    auto silu(const array_t& array,
        context_t&& context=context_t{}, output_t&& output=output_t{})
    {
        auto a = view::silu(array);
        return eval(a,context,output);
    } // silu
} // namespace nmtools::array

#endif // NMTOOLS_ARRAY_ARRAY_ACTIVATIONS_SILU_HPP