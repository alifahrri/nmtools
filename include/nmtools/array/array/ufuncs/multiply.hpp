#ifndef NMTOOLS_ARRAY_ARRAY_MULTIPLY_HPP
#define NMTOOLS_ARRAY_ARRAY_MULTIPLY_HPP

#include "nmtools/array/eval.hpp"
#include "nmtools/array/view/ufuncs/multiply.hpp"
#include "nmtools/constants.hpp"

namespace nmtools::array
{
    namespace fn
    {
        struct multiply
        {
            template <typename output_t=none_t, typename context_t=none_t, typename left_t, typename right_t>
            inline constexpr auto operator()(const left_t& a, const right_t& b,
                context_t&& context=context_t{}, output_t&& output=output_t{}) const
            {
                auto multiply = view::multiply(a,b);
                return eval(multiply,context,output);
            } // operator()

            template <typename output_t=none_t, typename context_t=none_t,
                typename dtype_t=none_t, typename initial_t=none_t,
                typename keepdims_t=std::false_type, typename left_t, typename axis_t>
            static constexpr auto reduce(const left_t& a, const axis_t& axis, dtype_t dtype=dtype_t{},
                initial_t initial=initial_t{}, keepdims_t keepdims=keepdims_t{},
                context_t&& context=context_t{}, output_t&& output=output_t{})
            {
                auto multiply = view::reduce_multiply(a,axis,dtype,initial,keepdims);
                return eval(multiply,context,output);
            } // reduce

            template <typename output_t=none_t, typename context_t=none_t,
                typename dtype_t=none_t, typename left_t, typename axis_t>
            static constexpr auto accumulate(const left_t& a, const axis_t& axis, dtype_t dtype=dtype_t{},
                context_t&& context=context_t{}, output_t&& output=output_t{})
            {
                auto multiply = view::accumulate_multiply(a,axis,dtype);
                return eval(multiply,context,output);
            } // accumulate

            template <typename output_t=none_t, typename context_t=none_t,
                typename dtype_t=none_t, typename left_t, typename right_t>
            static constexpr auto outer(const left_t& a, const right_t& b, dtype_t dtype=dtype_t{},
                context_t&& context=context_t{}, output_t&& output=output_t{})
            {
                auto multiply = view::outer_multiply(a,b,dtype);
                return eval(multiply,context,output);
            } // outer
        }; // multiply
    } // namespace fn

    constexpr inline auto multiply = fn::multiply{};
} // nmtools::array

#endif // NMTOOLS_ARRAY_ARRAY_MULTIPLY_HPP