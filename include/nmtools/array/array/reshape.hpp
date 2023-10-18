#ifndef NMTOOLS_ARRAY_ARRAY_RESHAPE_HPP
#define NMTOOLS_ARRAY_ARRAY_RESHAPE_HPP

#include "nmtools/array/view/reshape.hpp"
#include "nmtools/array/eval.hpp"

namespace nmtools::array
{
    /**
     * @brief Eagerly reshape an array. Note that this will copy array by default.
     * 
     * @tparam output_t 
     * @tparam context_t 
     * @tparam array_t 
     * @tparam shape_t 
     * @param array     input array
     * @param new_shape desired new shape
     * @param context   evaluation context
     * @param output 
     * @return constexpr auto 
     */
    template <typename output_t=none_t, typename context_t=none_t, typename resolver_t=eval_result_t<>,
        typename array_t, typename shape_t>
    constexpr auto reshape(const array_t& array, const shape_t& new_shape,
        context_t&& context=context_t{}, output_t&& output=output_t{},meta::as_value<resolver_t> resolver=meta::as_value_v<resolver_t>)
    {
        auto reshaped = view::reshape(array, new_shape);
        return eval(reshaped
            ,nmtools::forward<context_t>(context)
            ,nmtools::forward<output_t>(output)
            ,resolver
        );
    } // reshape
} // namespace nmtools::array

#endif // NMTOOLS_ARRAY_ARRAY_RESHAPE_HPP