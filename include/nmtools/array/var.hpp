#ifndef NMTOOLS_ARRAY_VIEW_VAR_HPP
#define NMTOOLS_ARRAY_VIEW_VAR_HPP

#include "nmtools/core/alias.hpp"
#include "nmtools/array/ufuncs/fabs.hpp"
#include "nmtools/array/ufuncs/square.hpp"
#include "nmtools/array/ufuncs/subtract.hpp"
#include "nmtools/array/sum.hpp"
#include "nmtools/array/mean.hpp"

namespace nmtools::view
{
    /**
     * @brief Create view that computes variance.
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
    constexpr auto var(const array_t& array, const axis_t& axis, dtype_t dtype=dtype_t{}, ddof_t ddof=ddof_t{0}, keepdims_t keepdims=keepdims_t{})
    {
        // TODO: propagate error handling
        auto dim = unwrap(::nmtools::dim<true>(array));
        // TODO: error handling
        auto m_axis  = [&](){
            if constexpr (is_none_v<axis_t>) {
                return axis;
            } else {
                return unwrap(index::normalize_axis(axis,unwrap(dim)));
            }
        }();

        auto input = view::aliased(array);
        // must keep dimension to properly subtract
        auto a = view::mean(input,m_axis,dtype,/*keepdims=*/True);
        auto b = view::subtract(input, a);
        auto c = view::fabs(b);
        auto d = view::square(c);
        // no reason to start from other initial value
        auto e = view::sum(d,m_axis,dtype,/*initial=*/None,keepdims);
        // TODO: error handling
        auto N = detail::mean_divisor(::nmtools::shape(unwrap(input)),m_axis);
        return view::divide(e,N-ddof);
    } // var
} // namespace nmtools::view


#endif // NMTOOLS_ARRAY_VIEW_VAR_HPP

#ifndef NMTOOLS_ARRAY_FUNCTIONAL_VAR_HPP
#define NMTOOLS_ARRAY_FUNCTIONAL_VAR_HPP

#include "nmtools/core/functor.hpp"
#include "nmtools/array/ufuncs/add.hpp"
#include "nmtools/array/ufuncs/divide.hpp"
#include "nmtools/array/var.hpp"

namespace nmtools::functional
{
    constexpr inline auto var_fun = [](const auto&...args){
        return view::var(args...);
    };

    constexpr inline auto var = functor_t{unary_fmap_t<decltype(var_fun)>{{var_fun}}};
} // namespace nmtools::functional

#endif // NMTOOLS_ARRAY_FUNCTIONAL_VAR_HPP

#ifndef NMTOOLS_ARRAY_ARRAY_VAR_HPP
#define NMTOOLS_ARRAY_ARRAY_VAR_HPP

#include "nmtools/array/var.hpp"
#include "nmtools/core/eval.hpp"

namespace nmtools
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
    template <typename output_t=none_t, typename context_t=none_t, typename resolver_t=eval_result_t<>,
        typename array_t, typename axis_t, typename dtype_t=none_t, typename ddof_t=size_t, typename keepdims_t=meta::false_type>
    constexpr auto var(const array_t& array, const axis_t& axis, dtype_t dtype=dtype_t{}, ddof_t ddof=ddof_t{0}, keepdims_t keepdims=keepdims_t{},
        context_t&& context=context_t{}, output_t&& output=output_t{},meta::as_value<resolver_t> resolver=meta::as_value_v<resolver_t>)
    {
        auto a = view::var(array,axis,dtype,ddof,keepdims);
        return eval(a
            ,nmtools::forward<context_t>(context)
            ,nmtools::forward<output_t>(output)
            ,resolver
        );
    } // var
} // namespace nmtools

#endif // NMTOOLS_ARRAY_ARRAY_VAR_HPP