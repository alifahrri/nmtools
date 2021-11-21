#ifndef NMTOOLS_ARRAY_ARRAY_SUBTRACT_HPP
#define NMTOOLS_ARRAY_ARRAY_SUBTRACT_HPP

#include "nmtools/array/eval.hpp"
#include "nmtools/array/view/ufuncs/subtract.hpp"
#include "nmtools/constants.hpp"

namespace nmtools::array
{
    namespace fn
    {
        struct subtract
        {
            template <typename output_t=none_t, typename context_t=none_t, typename left_t, typename right_t>
            inline constexpr auto operator()(const left_t& a, const right_t& b,
                context_t&& context=context_t{}, output_t&& output=output_t{}) const
            {
                auto subtract = view::subtract(a,b);
                return eval(subtract,context,output);
            } // operator()

            template <typename output_t=none_t, typename context_t=none_t,
                typename dtype_t=none_t, typename initial_t=none_t,
                typename keepdims_t=meta::false_type, typename left_t, typename axis_t>
            static constexpr auto reduce(const left_t& a, const axis_t& axis, dtype_t dtype=dtype_t{},
                initial_t initial=initial_t{}, keepdims_t keepdims=keepdims_t{},
                context_t&& context=context_t{}, output_t&& output=output_t{})
            {
                auto subtract = view::reduce_subtract(a,axis,dtype,initial,keepdims);
                return eval(subtract,context,output);
            } // reduce

            template <typename output_t=none_t, typename context_t=none_t,
                typename dtype_t=none_t, typename left_t, typename axis_t>
            static constexpr auto accumulate(const left_t& a, const axis_t& axis, dtype_t dtype=dtype_t{},
                context_t&& context=context_t{}, output_t&& output=output_t{})
            {
                auto subtract = view::accumulate_subtract(a,axis,dtype);
                return eval(subtract,context,output);
            } // accumulate

            template <typename output_t=none_t, typename context_t=none_t,
                typename dtype_t=none_t, typename left_t, typename right_t>
            static constexpr auto outer(const left_t& a, const right_t& b, dtype_t dtype=dtype_t{},
                context_t&& context=context_t{}, output_t&& output=output_t{})
            {
                auto subtract = view::outer_subtract(a,b,dtype);
                return eval(subtract,context,output);
            } // outer
        }; // subtract
    } // namespace fn

    constexpr inline auto subtract = fn::subtract{};
} // nmtools::array

#endif // NMTOOLS_ARRAY_ARRAY_SUBTRACT_HPP