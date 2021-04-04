#ifndef NMTOOLS_ARRAY_ARRAY_MAXIMUM_HPP
#define NMTOOLS_ARRAY_ARRAY_MAXIMUM_HPP

#include "nmtools/array/eval.hpp"
#include "nmtools/array/view/ufuncs/maximum.hpp"
#include "nmtools/constants.hpp"

namespace nmtools::array
{
    namespace fn
    {
        struct maximum
        {
            template <typename output_t=none_t, typename context_t=none_t, typename left_t, typename right_t>
            inline constexpr auto operator()(const left_t& a, const right_t& b,
                context_t&& context=context_t{}, output_t&& output=output_t{}) const
            {
                auto maximum = view::maximum(a,b);
                return eval(maximum,context,output);
            } // operator()

            template <typename output_t=none_t, typename context_t=none_t,
                typename dtype_t=none_t, typename initial_t=none_t,
                typename keepdims_t=std::false_type, typename left_t, typename axis_t>
            static constexpr auto reduce(const left_t& a, const axis_t& axis, dtype_t dtype=dtype_t{},
                initial_t initial=initial_t{}, keepdims_t keepdims=keepdims_t{},
                context_t&& context=context_t{}, output_t&& output=output_t{})
            {
                auto maximum = view::reduce_maximum(a,axis,dtype,initial,keepdims);
                return eval(maximum,context);
            } // reduce

            template <typename output_t=none_t, typename context_t=none_t,
                typename dtype_t=none_t, typename left_t, typename axis_t>
            static constexpr auto accumulate(const left_t& a, const axis_t& axis, dtype_t dtype=dtype_t{},
                context_t&& context=context_t{}, output_t&& output=output_t{})
            {
                auto maximum = view::accumulate_maximum(a,axis,dtype);
                return eval(maximum,context);
            } // accumulate

            template <typename output_t=none_t, typename context_t=none_t,
                typename dtype_t=none_t, typename left_t, typename right_t>
            static constexpr auto outer(const left_t& a, const right_t& b, dtype_t dtype=dtype_t{},
                context_t&& context=context_t{}, output_t&& output=output_t{})
            {
                auto maximum = view::outer_maximum(a,b,dtype);
                return eval(maximum,context,output);
            } // outer
        }; // maximum
    } // namespace fn

    constexpr inline auto maximum = fn::maximum{};
} // nmtools::array

#endif // NMTOOLS_ARRAY_ARRAY_MAXIMUM_HPP