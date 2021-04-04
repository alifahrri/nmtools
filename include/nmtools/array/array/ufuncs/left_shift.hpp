#ifndef NMTOOLS_ARRAY_ARRAY_LEFT_SHIFT_HPP
#define NMTOOLS_ARRAY_ARRAY_LEFT_SHIFT_HPP

#include "nmtools/array/eval.hpp"
#include "nmtools/array/view/ufuncs/left_shift.hpp"
#include "nmtools/constants.hpp"

namespace nmtools::array
{
    namespace fn
    {
        struct left_shift
        {
            template <typename output_t=none_t, typename context_t=none_t, typename left_t, typename right_t>
            inline constexpr auto operator()(const left_t& a, const right_t& b,
                context_t&& context=context_t{}, output_t&& output=output_t{}) const
            {
                auto left_shift = view::left_shift(a,b);
                return eval(left_shift,context,output);
            } // operator()

            template <typename output_t=none_t, typename context_t=none_t,
                typename dtype_t=none_t, typename initial_t=none_t,
                typename keepdims_t=std::false_type, typename left_t, typename axis_t>
            static constexpr auto reduce(const left_t& a, const axis_t& axis, dtype_t dtype=dtype_t{},
                initial_t initial=initial_t{}, keepdims_t keepdims=keepdims_t{},
                context_t&& context=context_t{}, output_t&& output=output_t{})
            {
                auto left_shift = view::reduce_left_shift(a,axis,dtype,initial,keepdims);
                return eval(left_shift,context);
            } // reduce

            template <typename output_t=none_t, typename context_t=none_t,
                typename dtype_t=none_t, typename left_t, typename axis_t>
            static constexpr auto accumulate(const left_t& a, const axis_t& axis, dtype_t dtype=dtype_t{},
                context_t&& context=context_t{}, output_t&& output=output_t{})
            {
                auto left_shift = view::accumulate_left_shift(a,axis,dtype);
                return eval(left_shift,context);
            } // accumulate

            template <typename output_t=none_t, typename context_t=none_t,
                typename dtype_t=none_t, typename left_t, typename right_t>
            static constexpr auto outer(const left_t& a, const right_t& b, dtype_t dtype=dtype_t{},
                context_t&& context=context_t{}, output_t&& output=output_t{})
            {
                auto left_shift = view::outer_left_shift(a,b,dtype);
                return eval(left_shift,context,output);
            } // outer
        }; // left_shift
    } // namespace fn

    constexpr inline auto left_shift = fn::left_shift{};
} // nmtools::array

#endif // NMTOOLS_ARRAY_ARRAY_LEFT_SHIFT_HPP