#ifndef NMTOOLS_ARRAY_ARRAY_MEAN_HPP
#define NMTOOLS_ARRAY_ARRAY_MEAN_HPP

#include "nmtools/array/view/mean.hpp"
#include "nmtools/array/ufuncs/add.hpp"
#include "nmtools/array/ufuncs/divide.hpp"
#include "nmtools/array/core/eval.hpp"

namespace nmtools::array
{
    /**
     * @brief Eagerly compute mean of an array along the specified axis.
     * 
     * @tparam output_t 
     * @tparam context_t 
     * @tparam array_t 
     * @tparam axis_t 
     * @tparam dtype_t 
     * @tparam keepdims_t 
     * @param array     input array
     * @param axis      axis or axes along which the means are to be computed.
     * @param dtype     type to compute the means.
     * @param keepdims  set if the reduced axis are to be kept.
     * @param context   evaluation context.
     * @param output 
     * @return constexpr auto 
     */
    template <typename output_t=none_t, typename context_t=none_t, typename resolver_t=eval_result_t<>,
        typename array_t, typename axis_t, typename dtype_t=none_t, typename keepdims_t=meta::false_type>
    constexpr auto mean(const array_t& array, const axis_t& axis, dtype_t dtype=dtype_t{}, keepdims_t keepdims=keepdims_t{},
        context_t&& context=context_t{}, output_t&& output=output_t{},meta::as_value<resolver_t> resolver=meta::as_value_v<resolver_t>)
    {
        auto a = view::mean(array, axis, dtype, keepdims);
        return eval(a
            ,nmtools::forward<context_t>(context)
            ,nmtools::forward<output_t>(output)
            ,resolver
        );
    } // mean
} // namespace nmtools::array

#endif // NMTOOLS_ARRAY_ARRAY_MEAN_HPP