#ifndef NMTOOLS_ARRAY_ARRAY_RIGHT_SHIFT_HPP
#define NMTOOLS_ARRAY_ARRAY_RIGHT_SHIFT_HPP

#include "nmtools/array/eval.hpp"
#include "nmtools/array/view/ufuncs/right_shift.hpp"
#include "nmtools/constants.hpp"

namespace nmtools::array
{
    namespace fn
    {
        struct right_shift
        {
            template <typename output_t=none_t, typename context_t=none_t, typename left_t, typename right_t>
            inline constexpr auto operator()(const left_t& a, const right_t& b,
                context_t&& context=context_t{}, output_t&& output=output_t{}) const
            {
                auto right_shift = view::right_shift(a,b);
                return eval(right_shift,context,output);
            } // operator()

            template <typename output_t=none_t, typename context_t=none_t,
                typename dtype_t=none_t, typename initial_t=none_t,
                typename keepdims_t=std::false_type, typename left_t, typename axis_t>
            static constexpr auto reduce(const left_t& a, const axis_t& axis, dtype_t dtype=dtype_t{},
                initial_t initial=initial_t{}, keepdims_t keepdims=keepdims_t{},
                context_t&& context=context_t{}, output_t&& output=output_t{})
            {
                auto right_shift = view::reduce_right_shift(a,axis,dtype,initial,keepdims);
                return eval(right_shift,context);
            } // reduce

            template <typename output_t=none_t, typename context_t=none_t,
                typename dtype_t=none_t, typename left_t, typename axis_t>
            static constexpr auto accumulate(const left_t& a, const axis_t& axis, dtype_t dtype=dtype_t{},
                context_t&& context=context_t{}, output_t&& output=output_t{})
            {
                auto right_shift = view::accumulate_right_shift(a,axis,dtype);
                return eval(right_shift,context);
            } // accumulate

            template <typename output_t=none_t, typename context_t=none_t,
                typename dtype_t=none_t, typename left_t, typename right_t>
            static constexpr auto outer(const left_t& a, const right_t& b, dtype_t dtype=dtype_t{},
                context_t&& context=context_t{}, output_t&& output=output_t{})
            {
                auto right_shift = view::outer_right_shift(a,b,dtype);
                return eval(right_shift,context,output);
            } // outer
        }; // right_shift
    } // namespace fn

    constexpr inline auto right_shift = fn::right_shift{};
} // nmtools::array

#endif // NMTOOLS_ARRAY_ARRAY_RIGHT_SHIFT_HPP