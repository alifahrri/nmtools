#ifndef NMTOOLS_ARRAY_VIEW_PROD_HPP
#define NMTOOLS_ARRAY_VIEW_PROD_HPP

#include "nmtools/array/ufuncs/multiply.hpp"
#include "nmtools/core/ufunc.hpp"
#include "nmtools/constants.hpp"

namespace nmtools::view
{
    /**
     * @brief Create a view that represents product of array elements over a given axis.
     *
     * This function is equivalent to view::reduce_multiply.
     * 
     * @tparam left_t 
     * @tparam axis_t 
     * @tparam dtype_t 
     * @tparam initial_t 
     * @tparam keepdims_t 
     * @param a        input array.
     * @param axis     axis or axes in which product are to be performed.
     * @param dtype    desired data type.
     * @param initial  initial value of the product.
     * @param keepdims if true, the reduced axis are kept in the results.
     * @return constexpr auto 
     */
    template <typename left_t, typename axis_t, typename dtype_t, typename initial_t, typename keepdims_t>
    constexpr auto prod(const left_t& a, const axis_t& axis, dtype_t dtype, initial_t initial, keepdims_t keepdims)
    {
        using res_t = get_dtype_t<dtype_t>;
        using op_t  = multiply_t<none_t,none_t,res_t>;
        return view::reduce(op_t{},a,axis,dtype,initial,keepdims);
    } // prod

    template <typename left_t, typename axis_t, typename dtype_t, typename initial_t>
    constexpr auto prod(const left_t& a, const axis_t& axis, dtype_t dtype, initial_t initial)
    {
        using res_t = get_dtype_t<dtype_t>;
        using op_t  = multiply_t<none_t,none_t,res_t>;
        return view::reduce(op_t{},a,axis,dtype,initial);
    } // prod

    template <typename left_t, typename axis_t, typename dtype_t>
    constexpr auto prod(const left_t& a, const axis_t& axis, dtype_t dtype)
    {
        return view::prod(a,axis,dtype,None);
    } // prod

    template <typename left_t, typename axis_t>
    constexpr auto prod(const left_t& a, const axis_t& axis)
    {
        return view::prod(a,axis,None,None);
    } // prod
} // namespace nmtools::view

#endif // NMTOOLS_ARRAY_VIEW_PROD_HPP

#ifndef NMTOOLS_ARRAY_FUNCTIONAL_PROD_HPP
#define NMTOOLS_ARRAY_FUNCTIONAL_PROD_HPP

#include "nmtools/core/functor.hpp"
#include "nmtools/array/prod.hpp"

namespace nmtools::functional
{
    constexpr inline auto prod_fun = [](const auto&...args){
        return view::prod(args...);
    };

    constexpr inline auto prod = functor_t{unary_fmap_t<decltype(prod_fun)>{prod_fun}};
} // namespace nmtools::functional

#endif // NMTOOLS_ARRAY_FUNCTIONAL_PROD_HPP

#ifndef NMTOOLS_ARRAY_ARRAY_PROD_HPP
#define NMTOOLS_ARRAY_ARRAY_PROD_HPP

#include "nmtools/core/eval.hpp"
#include "nmtools/array/prod.hpp"
#include "nmtools/constants.hpp"

namespace nmtools::array
{
    /**
     * @brief Eagerly evaluate prodduct of array elements over a given axis.
     * 
     * @tparam output_t 
     * @tparam context_t 
     * @tparam dtype_t 
     * @tparam initial_t 
     * @tparam keepdims_t 
     * @tparam array_t 
     * @tparam axis_t 
     * @param a        input array.
     * @param axis     axis in which the product is to be performed on.
     * @param dtype    desired data type.
     * @param initial  initial value.
     * @param keepdims if true, the reduced axes are kept in the resulting array.
     * @param context  evaluation context.
     * @param output   optional output.
     * @return constexpr auto 
     */
    template <typename output_t=none_t, typename context_t=none_t, typename resolver_t=eval_result_t<>,
        typename dtype_t=none_t, typename initial_t=none_t,
        typename keepdims_t=meta::false_type, typename array_t, typename axis_t>
    constexpr auto prod(const array_t& a, const axis_t& axis, dtype_t dtype=dtype_t{},
        initial_t initial=initial_t{}, keepdims_t keepdims=keepdims_t{},
        context_t&& context=context_t{}, output_t&& output=output_t{},meta::as_value<resolver_t> resolver=meta::as_value_v<resolver_t>)
    {
        auto prod_ = view::prod(a,axis,dtype,initial,keepdims);
        return eval(prod_
            ,nmtools::forward<context_t>(context)
            ,nmtools::forward<output_t>(output)
            ,resolver
        );
    } // prod
} // namespace nmtools::array

#endif // NMTOOLS_ARRAY_ARRAY_PROD_HPP