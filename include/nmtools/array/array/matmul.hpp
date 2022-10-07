#ifndef NMTOOLS_ARRAY_ARRAY_MATMUL_HPP
#define NMTOOLS_ARRAY_ARRAY_MATMUL_HPP

#include "nmtools/array/view/matmul.hpp"
#include "nmtools/array/eval.hpp"

namespace nmtools::array
{
    /**
     * @brief Eagerly computes matrix product of two arrays.
     * 
     * The resulting shape is following numpy's matmul,
     * The axis -2..0 are broadcasted.
     * 
     * @tparam output_t 
     * @tparam context_t 
     * @tparam lhs_t 
     * @tparam rhs_t 
     * @param lhs 
     * @param rhs 
     * @param context evaluation context
     * @param output 
     * @return constexpr auto 
     */
    template <typename output_t=none_t, typename context_t=none_t, typename resolver_t=eval_result_t,
        typename lhs_t, typename rhs_t>
    constexpr auto matmul(const lhs_t& lhs, const rhs_t& rhs,
        context_t&& context=context_t{}, output_t&& output=output_t{},meta::as_value<resolver_t> resolver=meta::as_value_v<resolver_t>)
    {
        auto a = view::matmul(lhs,rhs);
        return eval(a
            ,nmtools::forward<context_t>(context)
            ,nmtools::forward<output_t>(output)
            ,resolver
        );
    } // matmul
} // namespace nmtools::array

#endif // NMTOOLS_ARRAY_ARRAY_MATMUL_HPP