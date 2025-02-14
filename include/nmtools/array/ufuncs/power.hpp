#ifndef NMTOOLS_ARRAY_VIEW_UFUNCS_POWER_HPP
#define NMTOOLS_ARRAY_VIEW_UFUNCS_POWER_HPP

#include "nmtools/core/ufunc.hpp"
#include "nmtools/math.hpp"

namespace nmtools::view
{
    #if 0
    template <
        typename lhs_t=none_t, typename rhs_t=none_t,
        typename res_t=none_t, typename=void>
    struct power_t
    {
        template <typename T, typename U>
        NMTOOLS_UFUNC_CONSTEXPR
        auto operator()(const T& t, const U& u) const
        {
            // TODO: formalize casting rules
            using common_t [[maybe_unused]] = meta::common_type_t<T,U>;
            using result_t [[maybe_unused]] = meta::conditional_t<is_none_v<res_t>,common_t,res_t>;
            auto lhs = [&](){
                if constexpr (!is_none_v<lhs_t>) {
                    return static_cast<lhs_t>(t);
                } else {
                    return static_cast<result_t>(t);
                }
            }();
            auto rhs = [&](){
                if constexpr (!is_none_v<rhs_t>) {
                    return static_cast<rhs_t>(u);
                } else {
                    return static_cast<result_t>(u);
                }
            }();
            auto result = math::pow(lhs,rhs);
            if constexpr (!is_none_v<res_t>) {
                return static_cast<res_t>(result);
            } else {
                return result;
            }
        } // operator()
    }; // power_t
    #else
    template <
        typename lhs_t=none_t, typename rhs_t=none_t,
        typename res_t=none_t, typename=void>
    struct power_t
    {
        template <typename T, typename U>
        NMTOOLS_UFUNC_CONSTEXPR
        nmtools_func_attribute
        auto operator()(const T& t, const U& u) const
        {
            if constexpr (meta::is_view_v<T> || meta::is_view_v<U>) {
                using common_t [[maybe_unused]] = meta::common_type_t<T,U>;
                return math::pow(static_cast<common_t>(t),static_cast<common_t>(u));
            } else {
                return math::pow(t,u);
            }
        } // operator()
    }; // power_t

    // TODO: unify with primary template, use static cast to res_t
    template <typename res_t>
    struct power_t<none_t,none_t,res_t,
        meta::enable_if_t<(!is_none_v<res_t>)>
    >
    {
        using result_type = res_t;

        template <typename T, typename U>
        NMTOOLS_UFUNC_CONSTEXPR
        auto operator()(const T& t, const U& u) const -> res_t
        {
            return math::pow(t,u);
        } // operator()
    }; // power_t

    // TODO: unify with primary template, use static cast to lhs_t, rhs_t, res_t
    template <typename lhs_t, typename rhs_t, typename res_t>
    struct power_t<lhs_t,rhs_t,res_t,meta::enable_if_t<
        (!is_none_v<lhs_t>) && (!is_none_v<rhs_t>) && (!is_none_v<res_t>)
    >>
    {
        using result_type = res_t;

        NMTOOLS_UFUNC_CONSTEXPR
        auto operator()(const lhs_t& t, const rhs_t& u) const -> res_t
        {
            return math::pow(t,u);
        } // operator()
    }; // power_t
    #endif

    template <typename left_t, typename right_t>
    NMTOOLS_UFUNC_CONSTEXPR
    auto power(const left_t& a, const right_t& b)
    {
        return broadcast_binary_ufunc(power_t<>{},a,b);
    } // power

    template <typename left_t, typename axis_t, typename dtype_t, typename initial_t, typename keepdims_t>
    NMTOOLS_UFUNC_CONSTEXPR
    auto reduce_power(const left_t& a, const axis_t& axis, dtype_t dtype, initial_t initial, keepdims_t keepdims)
    {
        static_assert( meta::is_integral_v<axis_t>
            , "reduce_power only support single axis with integral type"
        );
        using res_t = get_dtype_t<dtype_t>;
        using op_t  = power_t<none_t,none_t,res_t>;
        return reduce(op_t{},a,axis,dtype,initial,keepdims);
    } // reduce_power

    template <typename left_t, typename axis_t, typename dtype_t, typename initial_t>
    NMTOOLS_UFUNC_CONSTEXPR
    auto reduce_power(const left_t& a, const axis_t& axis, dtype_t dtype, initial_t initial)
    {
        static_assert( meta::is_integral_v<axis_t>
            , "reduce_power only support single axis with integral type"
        );
        using res_t = get_dtype_t<dtype_t>;
        using op_t  = power_t<none_t,none_t,res_t>;
        return reduce(op_t{},a,axis,dtype,initial);
    } // reduce_power

    template <typename left_t, typename axis_t, typename dtype_t>
    NMTOOLS_UFUNC_CONSTEXPR
    auto reduce_power(const left_t& a, const axis_t& axis, dtype_t dtype)
    {
        static_assert( meta::is_integral_v<axis_t>
            , "reduce_power only support single axis with integral type"
        );
        using res_t = get_dtype_t<dtype_t>;
        using op_t = power_t<none_t,none_t,res_t>;
        return reduce(op_t{},a,axis,dtype,None);
    } // reduce_power

    // TODO: use default args, instead of overload!
    template <typename left_t, typename axis_t>
    NMTOOLS_UFUNC_CONSTEXPR
    auto reduce_power(const left_t& a, const axis_t& axis)
    {
        return reduce_power(a,axis,None);
    } // reduce_power

    template <typename left_t, typename axis_t, typename dtype_t>
    NMTOOLS_UFUNC_CONSTEXPR
    auto accumulate_power(const left_t& a, const axis_t& axis, dtype_t dtype)
    {
        using res_t = get_dtype_t<dtype_t>;
        using op_t  = power_t<none_t,none_t,res_t>;
        return accumulate(op_t{},a,axis,dtype);
    } // accumulate_power

    template <typename left_t, typename axis_t>
    NMTOOLS_UFUNC_CONSTEXPR
    auto accumulate_power(const left_t& a, const axis_t& axis)
    {
        return accumulate_power(a,axis,None);
    } // accumulate_power

    template <typename left_t, typename right_t, typename dtype_t=none_t>
    NMTOOLS_UFUNC_CONSTEXPR
    auto outer_power(const left_t& a, const right_t& b, dtype_t dtype=dtype_t{})
    {
        using res_t = get_dtype_t<dtype_t>;
        using op_t  = power_t<none_t,none_t,res_t>;
        return outer(op_t{},a,b,dtype);
    } // outer_power
}

#if NMTOOLS_HAS_STRING

namespace nmtools::utils::impl
{
    template <
        typename lhs_t, typename rhs_t,
        typename res_t, auto...fmt_args>
    struct to_string_t<view::power_t<lhs_t,rhs_t,res_t>,fmt_string_t<fmt_args...>>
    {
        using result_type = nmtools_string;

        auto operator()(view::power_t<lhs_t,rhs_t,res_t>) const
        {
            auto str = nmtools_string();

            str += "power";

            return str;
        }
    };
}

#endif // NMTOOLS_HAS_STRING

#endif // NMTOOLS_ARRAY_VIEW_UFUNCS_POWER_HPP

#ifndef NMTOOLS_ARRAY_ARRAY_POWER_HPP
#define NMTOOLS_ARRAY_ARRAY_POWER_HPP

#include "nmtools/core/eval.hpp"
#include "nmtools/array/ufuncs/power.hpp"
#include "nmtools/constants.hpp"

namespace nmtools::array
{
    namespace fn
    {
        struct power
        {
            template <typename output_t=none_t, typename context_t=none_t, typename resolver_t=eval_result_t<>,
                typename left_t, typename right_t>
            inline constexpr auto operator()(const left_t& a, const right_t& b,
                context_t&& context=context_t{}, output_t&& output=output_t{},meta::as_value<resolver_t> resolver=meta::as_value_v<resolver_t>) const
            {
                auto power = view::power(a,b);
                return eval(power
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
                auto power = view::reduce_power(a,axis,dtype,initial,keepdims);
                return eval(power
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
                auto power = view::accumulate_power(a,axis,dtype);
                return eval(power
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
                auto power = view::outer_power(a,b,dtype);
                return eval(power
                    ,nmtools::forward<context_t>(context)
                    ,nmtools::forward<output_t>(output)
                    ,resolver
                );
            } // outer
        }; // power
    } // namespace fn

    constexpr inline auto power = fn::power{};
} // nmtools::array

#endif // NMTOOLS_ARRAY_ARRAY_POWER_HPP