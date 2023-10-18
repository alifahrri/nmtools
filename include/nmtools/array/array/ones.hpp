#ifndef NMTOOLS_ARRAY_ARRAY_ONES_HPP
#define NMTOOLS_ARRAY_ARRAY_ONES_HPP

#include "nmtools/array/view/ones.hpp"
#include "nmtools/array/eval.hpp"

namespace nmtools::array
{
    /**
     * @brief Eagerly compute ones.
     * 
     * @tparam output_t 
     * @tparam context_t 
     * @tparam shape_t 
     * @tparam T 
     * @param shape   Desired shape
     * @param dtype   Desired data type
     * @param context Evaluation context
     * @param output 
     * @return constexpr auto 
     */
    template <typename output_t=none_t, typename context_t=none_t, typename resolver_t=eval_result_t<>,
        typename shape_t, typename T=float>
    constexpr auto ones(const shape_t& shape, dtype_t<T> dtype=float32,
        context_t&& context=context_t{}, output_t&& output=output_t{},meta::as_value<resolver_t> resolver=meta::as_value_v<resolver_t>)
    {
        auto a = view::ones(shape,dtype);
        return eval(a
            ,nmtools::forward<context_t>(context)
            ,nmtools::forward<output_t>(output)
            ,resolver
        );
    } // ones
} // namespace nmtools::array

#endif // NMTOOLS_ARRAY_ARRAY_ONES_HPP