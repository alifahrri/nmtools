#ifndef NMTOOLS_ARRAY_ARRAY_ACTIVATIONS_HARDTANH_HPP
#define NMTOOLS_ARRAY_ARRAY_ACTIVATIONS_HARDTANH_HPP

#include "nmtools/array/view/activations/hardtanh.hpp"
#include "nmtools/array/eval.hpp"

namespace nmtools::array
{
    /**
     * @brief Eagerly compute element-wise hardtanh ufunc.
     * 
     * @tparam output_t 
     * @tparam context_t 
     * @tparam array_t 
     * @tparam min_val_t 
     * @tparam max_val_t 
     * @param array     input array
     * @param min_val   minimum value of linear region
     * @param max_val   maximum value of linear region
     * @param context   evaluation context
     * @param output 
     * @return constexpr auto 
     */
    template <typename output_t=none_t, typename context_t=none_t,
        typename array_t, typename min_val_t=float, typename max_val_t=float>
    constexpr auto hardtanh(const array_t& array, const min_val_t min_val=min_val_t{-1.0},
        const max_val_t max_val=max_val_t{1.0},
        context_t&& context=context_t{}, output_t&& output=output_t{})
    {
        auto a = view::hardtanh(array,min_val,max_val);
        return eval(a,context,output);
    } // hardtanh
} // namespace nmtools::array

#endif // NMTOOLS_ARRAY_ARRAY_ACTIVATIONS_HARDTANH_HPP