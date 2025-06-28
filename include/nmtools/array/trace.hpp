#ifndef NMTOOLS_ARRAY_VIEW_TRACE_HPP
#define NMTOOLS_ARRAY_VIEW_TRACE_HPP

#include "nmtools/array/diagonal.hpp"
#include "nmtools/array/sum.hpp"

namespace nmtools::view
{
    template <typename array_t, typename offset_t=meta::ct<0>, typename axis1_t=meta::ct<0>, typename axis2_t=meta::ct<1>, typename dtype_t=none_t>
    constexpr auto trace(const array_t& array, offset_t offset=offset_t{}, axis1_t axis1=axis1_t{}, axis2_t axis2=axis2_t{}, dtype_t dtype=dtype_t{})
    {
        auto axis = meta::ct_v<-1>;
        auto initial = None;
        auto keepdims = False;
        auto diagonal = view::diagonal(array,offset,axis1,axis2);
        return view::sum(diagonal,axis,dtype,initial,keepdims);
    }
} // nmtools::view

#endif // NMTOOLS_ARRAY_VIEW_TRACE_HPP

#ifndef NMTOOLS_ARRAY_ARRAY_TRACE_HPP
#define NMTOOLS_ARRAY_ARRAY_TRACE_HPP

#include "nmtools/array/trace.hpp"
#include "nmtools/core/eval.hpp"

namespace nmtools
{
    template <typename output_t=none_t, typename context_t=none_t, typename resolver_t=eval_result_t<>
        , typename array_t, typename offset_t=meta::ct<0>, typename axis1_t=meta::ct<0>, typename axis2_t=meta::ct<1>, typename dtype_t=none_t>
    constexpr auto trace(const array_t& array, offset_t offset=offset_t{}, axis1_t axis1=axis1_t{}, axis2_t axis2=axis2_t{}, dtype_t dtype=dtype_t{}
        , context_t&& context=context_t{}, output_t&& output=output_t{},meta::as_value<resolver_t> resolver=meta::as_value_v<resolver_t>)
    {
        auto a = view::trace(array,offset,axis1,axis2,dtype);
        return eval(
            a
            , nmtools::forward<context_t>(context)
            , nmtools::forward<output_t>(output)
            , resolver
        );
    } // trace
} // nmtools

#endif // NMTOOLS_ARRAY_ARRAY_TRACE_HPP