#ifndef NMTOOLS_ARRAY_VIEW_STDDEV_HPP
#define NMTOOLS_ARRAY_VIEW_STDDEV_HPP

#include "nmtools/array/var.hpp"
#include "nmtools/array/ufuncs/sqrt.hpp"

namespace nmtools::view
{
    /**
     * @brief Create a view that computes standard deviation.
     * 
     * @tparam array_t 
     * @tparam axis_t 
     * @tparam dtype_t 
     * @tparam ddof_t 
     * @tparam keepdims_t 
     * @param array     input array
     * @param axis      axis to operates in
     * @param dtype     optional datatype
     * @param ddof      delta degrees of freedom
     * @param keepdims  keep the dimension of the result, makes broadcasting with original array work properly
     * @return constexpr auto 
     */
    template <typename array_t, typename axis_t, typename dtype_t=none_t, typename ddof_t=size_t, typename keepdims_t=meta::false_type>
    constexpr auto stddev(const array_t& array, const axis_t& axis, dtype_t dtype=dtype_t{}, ddof_t ddof=ddof_t{0}, keepdims_t keepdims=keepdims_t{})
    {
        auto a = view::var(array,axis,dtype,ddof,keepdims);
        return view::sqrt(a);
    } // stddev
} // namespace nmtools::view


#endif // NMTOOLS_ARRAY_VIEW_STDDEV_HPP

#ifndef NMTOOLS_ARRAY_FUNCTIONAL_STDDEV_HPP
#define NMTOOLS_ARRAY_FUNCTIONAL_STDDEV_HPP

#include "nmtools/core/functor.hpp"
#include "nmtools/array/stddev.hpp"

namespace nmtools::functional
{
    constexpr inline auto stddev_fun = [](const auto&...args){
        return view::stddev(args...);
    };

    constexpr inline auto stddev = functor_t{unary_fmap_t<decltype(stddev_fun)>{{stddev_fun}}};
} // namespace nmtools::functional

#endif // NMTOOLS_ARRAY_FUNCTIONAL_STDDEV_HPP

#ifndef NMTOOLS_ARRAY_ARRAY_STDDEV_HPP
#define NMTOOLS_ARRAY_ARRAY_STDDEV_HPP

#include "nmtools/array/stddev.hpp"
#include "nmtools/core/eval.hpp"

namespace nmtools::array
{
    /**
     * @brief Eagerly compute the standard deviation of an array.
     * 
     * @tparam output_t 
     * @tparam context_t 
     * @tparam array_t 
     * @tparam axis_t 
     * @tparam dtype_t 
     * @tparam ddof_t 
     * @tparam keepdims_t 
     * @param array     input array
     * @param axis      axis to operates on
     * @param dtype     optional datatype
     * @param ddof      delta degrees of freedom
     * @param keepdims  keep the dimension of the result, makes broadcasting with original array work properly
     * @param context   evaluation context
     * @param output 
     * @return constexpr auto 
     */
    template <typename output_t=none_t, typename context_t=none_t, typename resolver_t=eval_result_t<>,
        typename array_t, typename axis_t, typename dtype_t=none_t, typename ddof_t=size_t, typename keepdims_t=meta::false_type>
    constexpr auto stddev(const array_t& array, const axis_t& axis, dtype_t dtype=dtype_t{}, ddof_t ddof=ddof_t{0}, keepdims_t keepdims=keepdims_t{},
        context_t&& context=context_t{}, output_t&& output=output_t{},meta::as_value<resolver_t> resolver=meta::as_value_v<resolver_t>)
    {
        auto a = view::stddev(array,axis,dtype,ddof,keepdims);
        return eval(a
            ,nmtools::forward<context_t>(context)
            ,nmtools::forward<output_t>(output)
            ,resolver
        );
    } // var
} // namespace nmtools::array

#endif // NMTOOLS_ARRAY_ARRAY_STDDEV_HPP