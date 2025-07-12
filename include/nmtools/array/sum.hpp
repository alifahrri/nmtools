#ifndef NMTOOLS_ARRAY_VIEW_SUM_HPP
#define NMTOOLS_ARRAY_VIEW_SUM_HPP

#include "nmtools/array/ufuncs/add.hpp"
#include "nmtools/constants.hpp"

namespace nmtools::view
{
    /**
     * @brief Create a view that represents sum of array elements over a given axis.
     *
     * This function is equivalent to view::reduce_add.
     * 
     * @tparam left_t 
     * @tparam axis_t 
     * @tparam dtype_t 
     * @tparam initial_t 
     * @tparam keepdims_t 
     * @param a        input array.
     * @param axis     axis or axes in which sum are to be performed.
     * @param dtype    desired data type.
     * @param initial  initial value of the sum.
     * @param keepdims if true, the reduced axis are kept in the results.
     * @return constexpr auto 
     */
    template <typename left_t, typename axis_t=none_t, typename dtype_t=none_t, typename initial_t=none_t, typename keepdims_t=meta::false_type>
    constexpr auto sum(const left_t& a, const axis_t& axis=axis_t{}, dtype_t dtype=dtype_t{}, initial_t initial=initial_t{}, keepdims_t keepdims=keepdims_t{})
    {
        using res_t = get_dtype_t<dtype_t>;
        using op_t  = add_t<none_t,none_t,res_t>;
        return reduce(op_t{},a,axis,dtype,initial,keepdims);
    } // add
} // namespace nmtools::view

#endif // NMTOOLS_ARRAY_VIEW_SUM_HPP

#ifndef NMTOOLS_ARRAY_FUNCTIONAL_SUM_HPP
#define NMTOOLS_ARRAY_FUNCTIONAL_SUM_HPP

#include "nmtools/core/functor.hpp"
#include "nmtools/array/sum.hpp"

namespace nmtools::functional
{
    constexpr inline auto sum_fun = [](const auto&...args){
        return view::sum(args...);
    };

    constexpr inline auto sum = functor_t{unary_fmap_t<decltype(sum_fun)>{{sum_fun}}};
} // namespace nmtools::functional

#endif // NMTOOLS_ARRAY_FUNCTIONAL_SUM_HPP

#ifndef NMTOOLS_ARRAY_ARRAY_SUM_HPP
#define NMTOOLS_ARRAY_ARRAY_SUM_HPP

#include "nmtools/core/eval.hpp"
#include "nmtools/array/sum.hpp"
#include "nmtools/constants.hpp"

namespace nmtools
{
    /**
     * @brief Eagerly evaluate sum of array elements over a given axis.
     * 
     * @tparam output_t 
     * @tparam context_t 
     * @tparam dtype_t 
     * @tparam initial_t 
     * @tparam keepdims_t 
     * @tparam array_t 
     * @tparam axis_t 
     * @param a        input array.
     * @param axis     axis in which the sum is to be performed on.
     * @param dtype    desired data type.
     * @param initial  initial value.
     * @param keepdims if true, the reduced axes are kept in the resulting array.
     * @param context  evaluation context.
     * @param output   optional output.
     * @return constexpr auto 
     */
    template <typename output_t=none_t, typename context_t=none_t, typename resolver_t=eval_result_t<>,
        typename dtype_t=none_t, typename initial_t=none_t,
        typename keepdims_t=meta::false_type, typename array_t, typename axis_t=none_t>
    constexpr auto sum(const array_t& a, const axis_t& axis=axis_t{}, dtype_t dtype=dtype_t{},
        initial_t initial=initial_t{}, keepdims_t keepdims=keepdims_t{},
        context_t&& context=context_t{}, output_t&& output=output_t{},meta::as_value<resolver_t> resolver=meta::as_value_v<resolver_t>)
    {
        auto sum_ = view::sum(a,axis,dtype,initial,keepdims);
        return eval(sum_
            ,nmtools::forward<context_t>(context)
            ,nmtools::forward<output_t>(output)
            ,resolver
        );
    } // sum
} // namespace nmtools

#endif // NMTOOLS_ARRAY_ARRAY_SUM_HPP