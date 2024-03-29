#ifndef NMTOOLS_ARRAY_ARRAY_UFUNCS_AMAX_HPP
#define NMTOOLS_ARRAY_ARRAY_UFUNCS_AMAX_HPP

#include "nmtools/array/view/ufuncs/amax.hpp"
#include "nmtools/array/eval.hpp"

namespace nmtools::array
{
    /**
     * @brief Eagerly computes the maximum of an array the maximum along the given axis.
     * 
     * @tparam output_t 
     * @tparam context_t 
     * @tparam array_t 
     * @tparam axis_t 
     * @tparam dtype_t 
     * @tparam initial_t 
     * @tparam keepdims_t 
     * @param a         input array
     * @param axis      axis to be reduced
     * @param dtype 
     * @param initial   optional initial value 
     * @param keepdims  set to true if the reduced axis are to be kept
     * @param context   evaluation context
     * @param output 
     * @return constexpr auto 
     */
    template <typename output_t=none_t, typename context_t=none_t, typename resolver_t=eval_result_t<>,
        typename array_t, typename axis_t=none_t, typename dtype_t=none_t, typename initial_t=none_t, typename keepdims_t=meta::false_type>
    constexpr auto amax(const array_t& a, const axis_t& axis=None, dtype_t dtype=dtype_t{}, initial_t initial=initial_t{}, keepdims_t keepdims=False,
        context_t&& context=context_t{}, output_t&& output=output_t{},meta::as_value<resolver_t> resolver=meta::as_value_v<resolver_t>)
    {
        auto reduced = view::amax(a,axis,dtype,initial,keepdims);
        return eval(reduced
            ,nmtools::forward<context_t>(context)
            ,nmtools::forward<output_t>(output)
            ,resolver
        );
    } // amax
} // namespace nmtools::array

#endif // NMTOOLS_ARRAY_ARRAY_UFUNCS_AMAX_HPP