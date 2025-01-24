#ifndef NMTOOLS_ARRAY_VIEW_UFUNCS_FMOD_HPP
#define NMTOOLS_ARRAY_VIEW_UFUNCS_FMOD_HPP

#include "nmtools/core/ufunc.hpp"
#include "nmtools/constants.hpp"
#include "nmtools/math.hpp"

namespace nmtools::view
{
    template <
        typename lhs_t=none_t,
        typename rhs_t=none_t,
        typename res_t=none_t,
        typename=void
    >
    struct fmod_t
    {
        template <typename T, typename U>
        NMTOOLS_UFUNC_CONSTEXPR
        auto operator()(const T& t, const U& u) const
        {
            return math::fmod(t,u);
        } // operator()
    }; // fmod_t

    // TODO; unify with primary template, use static cast to res_t
    template <typename res_t>
    struct fmod_t<none_t,none_t,res_t,meta::enable_if_t<meta::is_num_v<res_t>>>
    {
        using result_type = res_t;

        template <typename T, typename U>
        NMTOOLS_UFUNC_CONSTEXPR
        auto operator()(const T& t, const U& u) const -> res_t
        {
            return math::fmod(t,u);
        } // operator()
    }; // fmod_t

    template <typename left_t, typename right_t>
    NMTOOLS_UFUNC_CONSTEXPR
    auto fmod(const left_t& a, const right_t& b)
    {
        return broadcast_binary_ufunc(fmod_t<>{},a,b);
    } // fmod

    template <typename left_t, typename axis_t, typename dtype_t, typename initial_t, typename keepdims_t>
    NMTOOLS_UFUNC_CONSTEXPR
    auto reduce_fmod(const left_t& a, const axis_t& axis, dtype_t dtype, initial_t initial, keepdims_t keepdims)
    {
        static_assert( meta::is_integral_v<axis_t>
            , "reduce_fmod only support single axis with integral type"
        );
        // note that reduce_t takes reference, to support multiple axis
        // while reduce_fmod only support single axis, here axis is const ref
        // to match the signature of reduce_t
        using res_t = get_dtype_t<dtype_t>;
        using op_t  = fmod_t<none_t,none_t,res_t>; 
        return reduce(op_t{},a,axis,dtype,initial,keepdims);
    } // reduce_fmod

    template <typename left_t, typename axis_t, typename dtype_t, typename initial_t>
    NMTOOLS_UFUNC_CONSTEXPR
    auto reduce_fmod(const left_t& a, const axis_t& axis, dtype_t dtype, initial_t initial)
    {
        static_assert( meta::is_integral_v<axis_t>
            , "reduce_fmod only support single axis with integral type"
        );
        // note that reduce_t takes reference, to support multiple axis
        // while reduce_fmod only support single axis, here axis is const ref
        // to match the signature of reduce_t
        using res_t = get_dtype_t<dtype_t>;
        using op_t  = fmod_t<none_t,none_t,res_t>; 
        return reduce(op_t{},a,axis,dtype,initial);
    } // reduce_fmod

    template <typename left_t, typename axis_t, typename dtype_t>
    NMTOOLS_UFUNC_CONSTEXPR
    auto reduce_fmod(const left_t& a, const axis_t& axis, dtype_t dtype)
    {
        return reduce_fmod(a,axis,dtype,None);
    } // reduce_fmod

    // TODO: use default args instead of overloads!
    template <typename left_t, typename axis_t>
    NMTOOLS_UFUNC_CONSTEXPR
    auto reduce_fmod(const left_t& a, const axis_t& axis)
    {
        return reduce_fmod(a,axis,None,None);
    } // reduce_fmod

    template <typename left_t, typename axis_t, typename dtype_t>
    NMTOOLS_UFUNC_CONSTEXPR
    auto accumulate_fmod(const left_t& a, const axis_t& axis, dtype_t dtype)
    {
        using res_t = get_dtype_t<dtype_t>;
        using op_t  = fmod_t<none_t,none_t,res_t>;
        return accumulate(op_t{},a,axis,dtype);
    } // accumulate_fmod

    template <typename left_t, typename axis_t>
    NMTOOLS_UFUNC_CONSTEXPR
    auto accumulate_fmod(const left_t& a, const axis_t& axis)
    {
        return accumulate_fmod(a,axis,None);
    } // accumulate_fmod

    template <typename left_t, typename right_t, typename dtype_t=none_t>
    NMTOOLS_UFUNC_CONSTEXPR
    auto outer_fmod(const left_t& a, const right_t& b, dtype_t dtype=dtype_t{})
    {
        using res_t = get_dtype_t<dtype_t>;
        using op_t  = fmod_t<none_t,none_t,res_t>;
        return outer(op_t{},a,b,dtype);
    } // outer_fmod
};

#endif // NMTOOLS_ARRAY_VIEW_UFUNCS_FMOD_HPP

#ifndef NMTOOLS_ARRAY_ARRAY_FMOD_HPP
#define NMTOOLS_ARRAY_ARRAY_FMOD_HPP

#include "nmtools/core/eval.hpp"
#include "nmtools/array/ufuncs/fmod.hpp"
#include "nmtools/constants.hpp"

namespace nmtools::array
{
    namespace fn
    {
        struct fmod
        {
            template <typename output_t=none_t, typename context_t=none_t, typename resolver_t=eval_result_t<>,
                typename left_t, typename right_t>
            inline constexpr auto operator()(const left_t& a, const right_t& b,
                context_t&& context=context_t{}, output_t&& output=output_t{},meta::as_value<resolver_t> resolver=meta::as_value_v<resolver_t>) const
            {
                auto fmod = view::fmod(a,b);
                return eval(fmod
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
                auto fmod = view::reduce_fmod(a,axis,dtype,initial,keepdims);
                return eval(fmod
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
                auto fmod = view::accumulate_fmod(a,axis,dtype);
                return eval(fmod
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
                auto fmod = view::outer_fmod(a,b,dtype);
                return eval(fmod
                    ,nmtools::forward<context_t>(context)
                    ,nmtools::forward<output_t>(output)
                    ,resolver
                );
            } // outer
        }; // fmod
    } // namespace fn

    constexpr inline auto fmod = fn::fmod{};
} // nmtools::array

#endif // NMTOOLS_ARRAY_ARRAY_FMOD_HPP