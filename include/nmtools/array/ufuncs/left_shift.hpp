#ifndef NMTOOLS_ARRAY_VIEW_UFUNCS_LEFT_SHIFT_HPP
#define NMTOOLS_ARRAY_VIEW_UFUNCS_LEFT_SHIFT_HPP

#include "nmtools/core/ufunc.hpp"
#include "nmtools/constants.hpp"

namespace nmtools::view
{
    template <
        typename lhs_t=none_t,
        typename rhs_t=none_t,
        typename res_t=none_t,
        typename=void
    >
    struct left_shift_t
    {
        template <typename T, typename U>
        constexpr auto operator()(const T& t, const U& u) const
        {
            return t << u;
        } // operator()
    }; // left_shift_t

    template <typename res_t>
    struct left_shift_t<none_t,none_t,res_t,
        meta::enable_if_t<meta::is_num_v<res_t>>
    >
    {
        using result_type = res_t;

        template <typename T, typename U>
        constexpr auto operator()(const T& t, const U& u) const -> res_t
        {
            return t << u;
        } // operator()
    }; // left_shift_t

    template <typename left_t, typename right_t>
    constexpr auto left_shift(const left_t& a, const right_t& b)
    {
        return broadcast_binary_ufunc(left_shift_t<>{},a,b);
    } // left_shift

    template <typename left_t, typename axis_t, typename dtype_t=none_t, typename initial_t=none_t, typename keepdims_t=meta::false_type, typename where_t=none_t>
    constexpr auto reduce_left_shift(const left_t& a, const axis_t& axis, dtype_t dtype=dtype_t{}, initial_t initial=initial_t{}, keepdims_t keepdims=keepdims_t{}, const where_t& where=where_t{})
    {
        static_assert( meta::is_integral_v<axis_t>
            , "reduce_left_shift only support single axis with integral type"
        );
        // note that reduce_t takes reference, to support multiple axis
        // while reduce_left_shift only support single axis, here axis is const ref
        // to match the signature of reduce_t
        using res_t = get_dtype_t<dtype_t>;
        using op_t  = left_shift_t<none_t,none_t,res_t>;
        return reduce(op_t{},a,axis,dtype,initial,keepdims,where);
    } // reduce_left_shift

    template <typename left_t, typename axis_t, typename dtype_t=none_t>
    auto accumulate_left_shift(const left_t& a, const axis_t& axis, dtype_t dtype=dtype_t{})
    {
        using res_t = get_dtype_t<dtype_t>;
        using op_t  = left_shift_t<none_t,none_t,res_t>;
        return accumulate(op_t{},a,axis,dtype);
    } // accumulate_left_shift

    template <typename left_t, typename right_t, typename dtype_t=none_t>
    constexpr auto outer_left_shift(const left_t& a, const right_t& b, dtype_t dtype=dtype_t{})
    {
        using res_t = get_dtype_t<dtype_t>;
        using op_t  = left_shift_t<none_t,none_t,res_t>;
        return outer(op_t{},a,b,dtype);
    } // outer_left_shift
};

#endif // NMTOOLS_ARRAY_VIEW_UFUNCS_LEFT_SHIFT_HPP

#ifndef NMTOOLS_ARRAY_ARRAY_LEFT_SHIFT_HPP
#define NMTOOLS_ARRAY_ARRAY_LEFT_SHIFT_HPP

#include "nmtools/core/eval.hpp"
#include "nmtools/array/ufuncs/left_shift.hpp"
#include "nmtools/constants.hpp"

namespace nmtools::array
{
    namespace fn
    {
        struct left_shift
        {
            template <typename output_t=none_t, typename context_t=none_t, typename resolver_t=eval_result_t<>,
                typename left_t, typename right_t>
            inline constexpr auto operator()(const left_t& a, const right_t& b,
                context_t&& context=context_t{}, output_t&& output=output_t{},meta::as_value<resolver_t> resolver=meta::as_value_v<resolver_t>) const
            {
                auto left_shift = view::left_shift(a,b);
                return eval(left_shift
                    ,nmtools::forward<context_t>(context)
                    ,nmtools::forward<output_t>(output)
                    ,resolver
                );
            } // operator()

            template <typename output_t=none_t, typename context_t=none_t, typename resolver_t=eval_result_t<>,
                typename dtype_t=none_t, typename initial_t=none_t,
                typename keepdims_t=meta::false_type, typename left_t, typename axis_t>
            static constexpr auto reduce(const left_t& a, const axis_t& axis, dtype_t dtype=dtype_t{},
                initial_t initial=initial_t{}, keepdims_t keepdims=keepdims_t{},
                context_t&& context=context_t{}, output_t&& output=output_t{},meta::as_value<resolver_t> resolver=meta::as_value_v<resolver_t>)
            {
                auto left_shift = view::reduce_left_shift(a,axis,dtype,initial,keepdims);
                return eval(left_shift
                    ,nmtools::forward<context_t>(context)
                    ,nmtools::forward<output_t>(output)
                    ,resolver
                );
            } // reduce

            template <typename output_t=none_t, typename context_t=none_t, typename resolver_t=eval_result_t<>,
                typename dtype_t=none_t, typename left_t, typename axis_t>
            static constexpr auto accumulate(const left_t& a, const axis_t& axis, dtype_t dtype=dtype_t{},
                context_t&& context=context_t{}, output_t&& output=output_t{},meta::as_value<resolver_t> resolver=meta::as_value_v<resolver_t>)
            {
                auto left_shift = view::accumulate_left_shift(a,axis,dtype);
                return eval(left_shift
                    ,nmtools::forward<context_t>(context)
                    ,nmtools::forward<output_t>(output)
                    ,resolver
                );
            } // accumulate

            template <typename output_t=none_t, typename context_t=none_t, typename resolver_t=eval_result_t<>,
                typename dtype_t=none_t, typename left_t, typename right_t>
            static constexpr auto outer(const left_t& a, const right_t& b, dtype_t dtype=dtype_t{},
                context_t&& context=context_t{}, output_t&& output=output_t{},meta::as_value<resolver_t> resolver=meta::as_value_v<resolver_t>)
            {
                auto left_shift = view::outer_left_shift(a,b,dtype);
                return eval(left_shift
                    ,nmtools::forward<context_t>(context)
                    ,nmtools::forward<output_t>(output)
                    ,resolver
                );
            } // outer
        }; // left_shift
    } // namespace fn

    constexpr inline auto left_shift = fn::left_shift{};
} // nmtools::array

#endif // NMTOOLS_ARRAY_ARRAY_LEFT_SHIFT_HPP