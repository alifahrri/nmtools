#ifndef NMTOOLS_ARRAY_ARRAY_CONCATENATE_HPP
#define NMTOOLS_ARRAY_ARRAY_CONCATENATE_HPP

#include "nmtools/array/view/concatenate.hpp"
#include "nmtools/array/eval.hpp"

namespace nmtools::array
{
    /**
     * @brief Eagerly concatenate two array.
     * 
     * @tparam output_t 
     * @tparam context_t 
     * @tparam lhs_array_t 
     * @tparam rhs_array_t 
     * @tparam axis_t 
     * @param lhs       input array
     * @param rhs       input array
     * @param axis      the axis along which the arrays will be joined. if None, arrays are flattened before joined.
     * @param context   evaluation context
     * @param output 
     * @return constexpr auto 
     */
    template <typename output_t=none_t, typename context_t=none_t,
        typename lhs_array_t, typename rhs_array_t, typename axis_t>
    constexpr auto concatenate(const lhs_array_t& lhs, const rhs_array_t& rhs, axis_t axis,
        context_t&& context=context_t{}, output_t&& output=output_t{})
    {
        auto concatenated = view::concatenate(lhs,rhs,axis);
        return eval(concatenated,context,output);
    } // concatenate
} // namespace nmtools::array

#endif // NMTOOLS_ARRAY_ARRAY_CONCATENATE_HPP