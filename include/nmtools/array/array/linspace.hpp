#ifndef NMTOOLS_ARRAY_ARRAY_LINSPACE_HPP
#define NMTOOLS_ARRAY_ARRAY_LINSPACE_HPP

#include "nmtools/array/view/linspace.hpp"
#include "nmtools/array/eval.hpp"

namespace nmtools::array
{
    template <typename output_t=none_t, typename context_t=none_t, typename resolver_t=eval_result_t<>
        , typename start_t, typename stop_t, typename num_t=nm_size_t, typename endpoint_t=meta::true_type, typename retstep_t=meta::false_type, typename dtype_t=none_t>
    constexpr auto linspace(const start_t& start, const stop_t& stop, num_t num=num_t{50}, endpoint_t endpoint=endpoint_t{}, retstep_t retstep=retstep_t{}, dtype_t dtype=dtype_t{}
        , context_t&& context=context_t{}, output_t&& output=output_t{},meta::as_value<resolver_t> resolver=meta::as_value_v<resolver_t>)
    {
        auto a = view::linspace(start,stop,num,endpoint,retstep,dtype);
        if constexpr (meta::is_tuple_v<decltype(a)>) {
            return nmtools_tuple{
                eval(nmtools::get<0>(a)
                    , nmtools::forward<context_t>(context)
                    , nmtools::forward<output_t>(output)
                    , resolver)
                , nmtools::get<1>(a)
            };
        } else {
            return eval(a
                , nmtools::forward<context_t>(context)
                , nmtools::forward<output_t>(output)
                , resolver);
        }
    } // linspace
} // nmtools::array

#endif // NMTOOLS_ARRAY_ARRAY_LINSPACE_HPP