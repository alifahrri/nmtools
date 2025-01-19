#ifndef NMTOOLS_ARRAY_VIEW_CUMPROD_HPP
#define NMTOOLS_ARRAY_VIEW_CUMPROD_HPP

#include "nmtools/array/ufuncs/multiply.hpp"

namespace nmtools::view
{
    /**
     * @brief Create a view that represents the cumulative product of elements along a given axis.
     *
     * This view is equivalent to view::accumulate_multiply.
     * 
     * @tparam array_t 
     * @tparam axis_t 
     * @tparam dtype_t 
     * @param a     input array.
     * @param axis  axis in which the cumulative product is to be operated on.
     * @param dtype desired data type
     * @return constexpr auto 
     */
    template <typename array_t, typename axis_t, typename dtype_t>
    constexpr auto cumprod(const array_t& a, axis_t axis, dtype_t)
    {
        using res_t = get_dtype_t<dtype_t>;
        using op_t  = multiply_t<none_t,none_t,res_t>;
        return view::accumulate(op_t{},a,axis);
    } // cumprod

    template <typename array_t, typename axis_t>
    constexpr auto cumprod(const array_t& a, axis_t axis)
    {
        return view::cumprod(a,axis,None);
    } // cumprod
} // namespace nmtools::view

#endif // NMTOOLS_ARRAY_VIEW_CUMPROD_HPP

#ifndef NMTOOLS_ARRAY_FUNCTIONAL_CUMPROD_HPP
#define NMTOOLS_ARRAY_FUNCTIONAL_CUMPROD_HPP

#include "nmtools/core/functor.hpp"
#include "nmtools/array/cumprod.hpp"

namespace nmtools::functional
{
    constexpr inline auto cumprod_fun = [](const auto&...args){
        return view::cumprod(args...);
    };

    constexpr inline auto cumprod = functor_t{unary_fmap_t<decltype(cumprod_fun)>{{cumprod_fun}}};
} // namespace nmtools::functional

#endif // NMTOOLS_ARRAY_FUNCTIONAL_CUMPROD_HPP

#ifndef NMTOOLS_ARRAY_ARRAY_CUMPROD_HPP
#define NMTOOLS_ARRAY_ARRAY_CUMPROD_HPP

#include "nmtools/array/cumprod.hpp"
#include "nmtools/core/eval.hpp"

namespace nmtools::array
{
    /**
     * @brief Eagerly evaluate the cumulative product of elements along a given axis.
     * 
     * @tparam output_t 
     * @tparam context_t 
     * @tparam array_t 
     * @tparam axis_t 
     * @tparam dtype_t 
     * @param a     input array.
     * @param axis  axis in which the cumulative product is to be operated on.
     * @param dtype desired data type
     * @param context evaluation context
     * @param output  optional output
     * @return constexpr auto 
     */
    template <typename output_t=none_t, typename context_t=none_t, typename resolver_t=eval_result_t<>,
        typename array_t, typename axis_t, typename dtype_t=none_t>
    constexpr auto cumprod(const array_t& a, axis_t axis, dtype_t dtype=dtype_t{},
        context_t&& context=context_t{}, output_t&& output=output_t{},meta::as_value<resolver_t> resolver=meta::as_value_v<resolver_t>)
    {
        auto array = view::cumprod(a,axis,dtype);
        return eval(array
            ,nmtools::forward<context_t>(context)
            ,nmtools::forward<output_t>(output)
            ,resolver
        );
    } // cumprod
} // namespace nmtools::array

#endif // NMTOOLS_ARRAY_ARRAY_CUMPROD_HPP