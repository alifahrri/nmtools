#ifndef NMTOOLS_ARRAY_ARRAY_VAR_HPP
#define NMTOOLS_ARRAY_ARRAY_VAR_HPP

#include "nmtools/array/view/var.hpp"
#include "nmtools/array/eval.hpp"

namespace nmtools::array
{
    /**
     * @brief Eagerly computes the variance of an array along given axis.
     * 
     * @tparam output_t 
     * @tparam context_t 
     * @tparam array_t 
     * @tparam axis_t 
     * @tparam dtype_t 
     * @tparam ddof_t 
     * @tparam keepdims_t 
     * @param array     input array
     * @param axis      axis to operates in
     * @param dtype     optional datatype
     * @param ddof      delta degrees of freedom
     * @param keepdims  keep the dimension of the result, makes broadcasting work properly
     * @param context   evaluation context
     * @param output 
     * @return constexpr auto 
     */
    template <typename output_t=none_t, typename context_t=none_t,
        typename array_t, typename axis_t, typename dtype_t=none_t, typename ddof_t=size_t, typename keepdims_t=std::false_type>
    constexpr auto var(const array_t& array, const axis_t& axis, dtype_t dtype=dtype_t{}, ddof_t ddof=ddof_t{0}, keepdims_t keepdims=keepdims_t{},
        context_t&& context=context_t{}, output_t&& output=output_t{})
    {
        auto a = view::var(array,axis,dtype,ddof,keepdims);
        return eval(a,context,output);
    } // var
} // namespace nmtools::array

#endif // NMTOOLS_ARRAY_ARRAY_VAR_HPP