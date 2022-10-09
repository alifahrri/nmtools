#ifndef NMTOOLS_ARRAY_ARRAY_FMIN_HPP
#define NMTOOLS_ARRAY_ARRAY_FMIN_HPP

#include "nmtools/array/eval.hpp"
#include "nmtools/array/view/ufuncs/fmin.hpp"
#include "nmtools/constants.hpp"

namespace nmtools::array
{
    namespace fn
    {
        struct fmin
        {
            template <typename output_t=none_t, typename context_t=none_t, typename resolver_t=eval_result_t,
                typename left_t, typename right_t>
            inline constexpr auto operator()(const left_t& a, const right_t& b,
                context_t&& context=context_t{}, output_t&& output=output_t{},meta::as_value<resolver_t> resolver=meta::as_value_v<resolver_t>) const
            {
                auto fmin = view::fmin(a,b);
                return eval(fmin
                    ,nmtools::forward<context_t>(context)
                    ,nmtools::forward<output_t>(output)
                    ,resolver
                );
            } // operator()

            template <typename output_t=none_t, typename context_t=none_t, typename resolver_t=eval_result_t,
                typename dtype_t=none_t, typename initial_t=none_t,
                typename keepdims_t=meta::false_type, typename left_t, typename axis_t>
            static constexpr auto reduce(const left_t& a, const axis_t& axis, dtype_t dtype=dtype_t{},
                initial_t initial=initial_t{}, keepdims_t keepdims=keepdims_t{},
                context_t&& context=context_t{}, output_t&& output=output_t{},meta::as_value<resolver_t> resolver=meta::as_value_v<resolver_t>)
            {
                auto fmin = view::reduce_fmin(a,axis,dtype,initial,keepdims);
                return eval(fmin
                    ,nmtools::forward<context_t>(context)
                    ,nmtools::forward<output_t>(output)
                    ,resolver
                );
            } // reduce

            template <typename output_t=none_t, typename context_t=none_t, typename resolver_t=eval_result_t,
                typename dtype_t=none_t, typename left_t, typename axis_t>
            static constexpr auto accumulate(const left_t& a, const axis_t& axis, dtype_t dtype=dtype_t{},
                context_t&& context=context_t{}, output_t&& output=output_t{},meta::as_value<resolver_t> resolver=meta::as_value_v<resolver_t>)
            {
                auto fmin = view::accumulate_fmin(a,axis,dtype);
                return eval(fmin
                    ,nmtools::forward<context_t>(context)
                    ,nmtools::forward<output_t>(output)
                    ,resolver
                );
            } // accumulate

            template <typename output_t=none_t, typename context_t=none_t, typename resolver_t=eval_result_t,
                typename dtype_t=none_t, typename left_t, typename right_t>
            static constexpr auto outer(const left_t& a, const right_t& b, dtype_t dtype=dtype_t{},
                context_t&& context=context_t{}, output_t&& output=output_t{},meta::as_value<resolver_t> resolver=meta::as_value_v<resolver_t>)
            {
                auto fmin = view::outer_fmin(a,b,dtype);
                return eval(fmin
                    ,nmtools::forward<context_t>(context)
                    ,nmtools::forward<output_t>(output)
                    ,resolver
                );
            } // outer
        }; // fmin
    } // namespace fn

    constexpr inline auto fmin = fn::fmin{};
} // nmtools::array

#endif // NMTOOLS_ARRAY_ARRAY_FMIN_HPP