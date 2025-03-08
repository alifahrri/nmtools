#ifndef NMTOOLS_ARRAY_VIEW_VECTOR_NORM_HPP
#define NMTOOLS_ARRAY_VIEW_VECTOR_NORM_HPP

#include "nmtools/array/ufuncs/square.hpp"
#include "nmtools/array/ufuncs/sqrt.hpp"
#include "nmtools/array/ufuncs/fabs.hpp"
#include "nmtools/array/ufuncs/power.hpp"
#include "nmtools/array/sum.hpp"

namespace nmtools::view
{
    template <typename array_t, typename axis_t=none_t, typename keepdims_t=meta::false_type, typename ord_t=meta::ct<2>>
    constexpr auto vector_norm(const array_t& array, const axis_t& axis=axis_t{}, keepdims_t keepdims=keepdims_t{}, ord_t ord=ord_t{})
    {
        if constexpr (meta::is_constant_index_v<ord_t>) {
            if constexpr (ord_t::value == 2) {
                auto v1 = view::fabs(array);
                auto v2 = view::square(v1);
                auto v3 = view::sum(v2,axis,/*dtype*/None,/*initial*/None,keepdims);
                auto v4 = view::sqrt(v3);
                return v4;
            } else {
                return view::vector_norm(array,axis,keepdims,ord_t::value);
            }
        } else {
            auto v1 = view::fabs(array);
            auto v2 = view::power(v1,ord);
            auto v3 = view::sum(v2,axis,/*dtype*/None,/*initial*/None,keepdims);
            auto v4 = view::power(v3,1.f/ord);
            return v4;
        }
    } // vector_norm
} // nmtools::view

#endif // NMTOOLS_ARRAY_VIEW_VECTOR_NORM_HPP

#ifndef NMTOOLS_ARRAY_ARRAY_VECTOR_NORM_HPP
#define NMTOOLS_ARRAY_ARRAY_VECTOR_NORM_HPP

#include "nmtools/array/vector_norm.hpp"
#include "nmtools/core/eval.hpp"

namespace nmtools::array
{
    template <typename output_t=none_t, typename context_t=none_t, typename resolver_t=eval_result_t<>
        , typename array_t, typename axis_t=none_t, typename keepdims_t=meta::false_type, typename ord_t=nm_index_t>
    constexpr auto vector_norm(const array_t& array, const axis_t& axis=axis_t{}, keepdims_t keepdims=keepdims_t{}, ord_t ord=ord_t{2}
        , context_t&& context=context_t{}, output_t&& output=output_t{},meta::as_value<resolver_t> resolver=meta::as_value_v<resolver_t>)
    {
        auto a = view::vector_norm(array,axis,keepdims,ord);
        return eval(
            a
            , nmtools::forward<context_t>(context)
            , nmtools::forward<output_t>(output)
            , resolver
        );
    } // vector_norm
} // nmtools::array

#endif // NMTOOLS_ARRAY_ARRAY_VECTOR_NORM_HPP