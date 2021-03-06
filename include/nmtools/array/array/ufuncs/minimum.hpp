#ifndef NMTOOLS_ARRAY_ARRAY_MINIMUM_HPP
#define NMTOOLS_ARRAY_ARRAY_MINIMUM_HPP

#include "nmtools/array/eval.hpp"
#include "nmtools/array/view/ufuncs/minimum.hpp"
#include "nmtools/constants.hpp"

namespace nmtools::array
{
    namespace fn
    {
        struct minimum
        {
            template <typename output_t=none_t, typename context_t=none_t, typename left_t, typename right_t>
            inline constexpr auto operator()(const left_t& a, const right_t& b,
                context_t&& context=context_t{}, output_t&& output=output_t{}) const
            {
                auto minimum = view::minimum(a,b);
                return eval(minimum,context,output);
            } // operator()

            template <typename output_t=none_t, typename context_t=none_t,
                typename dtype_t=none_t, typename initial_t=none_t,
                typename keepdims_t=std::false_type, typename left_t, typename axis_t>
            static constexpr auto reduce(const left_t& a, const axis_t& axis, dtype_t dtype=dtype_t{},
                initial_t initial=initial_t{}, keepdims_t keepdims=keepdims_t{},
                context_t&& context=context_t{}, output_t&& output=output_t{})
            {
                auto minimum = view::reduce_minimum(a,axis,dtype,initial,keepdims);
                return eval(minimum,context);
            } // reduce

            template <typename output_t=none_t, typename context_t=none_t,
                typename dtype_t=none_t, typename left_t, typename axis_t>
            static constexpr auto accumulate(const left_t& a, const axis_t& axis, dtype_t dtype=dtype_t{},
                context_t&& context=context_t{}, output_t&& output=output_t{})
            {
                auto minimum = view::accumulate_minimum(a,axis,dtype);
                return eval(minimum,context);
            } // accumulate

            template <typename output_t=none_t, typename context_t=none_t,
                typename dtype_t=none_t, typename left_t, typename right_t>
            static constexpr auto outer(const left_t& a, const right_t& b, dtype_t dtype=dtype_t{},
                context_t&& context=context_t{}, output_t&& output=output_t{})
            {
                auto minimum = view::outer_minimum(a,b,dtype);
                return eval(minimum,context,output);
            } // outer
        }; // minimum
    } // namespace fn

    constexpr inline auto minimum = fn::minimum{};
} // nmtools::array

#endif // NMTOOLS_ARRAY_ARRAY_MINIMUM_HPP