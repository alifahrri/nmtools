#ifndef NMTOOLS_ARRAY_ARRAY_UFUNCS_AMIN_HPP
#define NMTOOLS_ARRAY_ARRAY_UFUNCS_AMIN_HPP

#include "nmtools/array/view/ufuncs/amin.hpp"
#include "nmtools/array/eval.hpp"

namespace nmtools::array
{
    /**
     * @brief Eagerly computes the minimum of an array or the minimum along the gien axis.
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
    template <typename output_t=none_t, typename context_t=none_t,
        typename array_t, typename axis_t=none_t, typename dtype_t=none_t, typename initial_t=none_t, typename keepdims_t=meta::false_type>
    constexpr auto amin(const array_t& a, const axis_t& axis=None, dtype_t dtype=dtype_t{}, initial_t initial=initial_t{}, keepdims_t keepdims=False,
        context_t&& context=context_t{}, output_t&& output=output_t{})
    {
        auto reduced = view::amin(a,axis,dtype,initial,keepdims);
        return eval(reduced,context,output);
    } // amin
} // namespace nmtools::array

#endif // NMTOOLS_ARRAY_ARRAY_UFUNCS_AMIN_HPP