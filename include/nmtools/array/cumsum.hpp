#ifndef NMTOOLS_ARRAY_VIEW_CUMSUM_HPP
#define NMTOOLS_ARRAY_VIEW_CUMSUM_HPP

#include "nmtools/array/ufuncs/add.hpp"

namespace nmtools::view
{
    /**
     * @brief Create a view that represents the cumulative sum of elements along a given axis.
     *
     * This view is equivalent to view::accumulate_add.
     * 
     * @tparam array_t 
     * @tparam axis_t 
     * @tparam dtype_t 
     * @param a     input array.
     * @param axis  axis in which the cumulative sum is to be operated on.
     * @param dtype desired data type
     * @return constexpr auto 
     */
    template <typename array_t, typename axis_t, typename dtype_t>
    constexpr auto cumsum(const array_t& a, axis_t axis, dtype_t)
    {
        using res_t = get_dtype_t<dtype_t>;
        using op_t  = add_t<none_t,none_t,res_t>;
        return view::accumulate(op_t{},a,axis);
    } // cumsum

    template <typename array_t, typename axis_t>
    constexpr auto cumsum(const array_t& a, axis_t axis)
    {
        return view::cumsum(a,axis,None);
    } // cumsum
} // namespace nmtools::view

#endif // NMTOOLS_ARRAY_VIEW_CUMSUM_HPP

#ifndef NMTOOLS_ARRAY_FUNCTIONAL_CUMSUM_HPP
#define NMTOOLS_ARRAY_FUNCTIONAL_CUMSUM_HPP

#include "nmtools/core/functor.hpp"
#include "nmtools/array/cumsum.hpp"

namespace nmtools::functional
{
    constexpr inline auto cumsum_fun = [](const auto&...args){
        return view::cumsum(args...);
    };

    constexpr inline auto cumsum = functor_t{unary_fmap_t<decltype(cumsum_fun)>{cumsum_fun}};
} // namespace nmtools::functional

#endif // NMTOOLS_ARRAY_FUNCTIONAL_CUMSUM_HPP

#ifndef NMTOOLS_ARRAY_ARRAY_CUMSUM_HPP
#define NMTOOLS_ARRAY_ARRAY_CUMSUM_HPP

#include "nmtools/array/cumsum.hpp"
#include "nmtools/core/eval.hpp"

namespace nmtools::array
{
    /**
     * @brief Eagerly evaluate the cumulative sum of elements along a given axis.
     * 
     * @tparam output_t 
     * @tparam context_t 
     * @tparam array_t 
     * @tparam axis_t 
     * @tparam dtype_t 
     * @param a     input array.
     * @param axis  axis in which the cumulative sum is to be operated on.
     * @param dtype desired data type
     * @param context evaluation context
     * @param output  optional output
     * @return constexpr auto 
     */
    template <typename output_t=none_t, typename context_t=none_t, typename resolver_t=eval_result_t<>,
        typename array_t, typename axis_t, typename dtype_t=none_t>
    constexpr auto cumsum(const array_t& a, axis_t axis, dtype_t dtype=dtype_t{},
        context_t&& context=context_t{}, output_t&& output=output_t{},meta::as_value<resolver_t> resolver=meta::as_value_v<resolver_t>)
    {
        auto array = view::cumsum(a,axis,dtype);
        return eval(array
            ,nmtools::forward<context_t>(context)
            ,nmtools::forward<output_t>(output)
            ,resolver
        );
    } // cumsum
} // namespace nmtools::array

#endif // NMTOOLS_ARRAY_ARRAY_CUMSUM_HPP