#ifndef NMTOOLS_ARRAY_VIEW_UFUNCS_LOG_HPP
#define NMTOOLS_ARRAY_VIEW_UFUNCS_LOG_HPP

#include "nmtools/utility/to_string/to_string.hpp"
#include "nmtools/core/ufunc.hpp"
#include "nmtools/math.hpp"

namespace nmtools::view::fun
{
    struct log
    {
        template <typename T>
        nmtools_func_attribute
        NMTOOLS_UFUNC_CONSTEXPR
        auto operator()(const T& t) const
        {
            return math::log(t);
        } // operator()
    }; // log
}

namespace nmtools::view
{
    using log_t = fun::log;

    template <typename left_t>
    nmtools_func_attribute
    NMTOOLS_UFUNC_CONSTEXPR
    auto log(const left_t& a)
    {
        return unary_ufunc(log_t{},a);
    } // log
}

#if NMTOOLS_HAS_STRING

namespace nmtools::utils::impl
{
    template <auto...fmt_args>
    struct to_string_t<view::fun::log,fmt_string_t<fmt_args...>>
    {
        using result_type = nmtools_string;

        auto operator()(view::fun::log) const
        {
            nmtools_string str;

            str += "log";

            return str;
        }
    };
} // namespace nmtools::utils::impl

#endif // NMTOOLS_HAS_STRING

#endif // NMTOOLS_ARRAY_VIEW_UFUNCS_LOG_HPP

#ifndef NMTOOLS_ARRAY_FUNCTIONAL_UFUNCS_LOG_HPP
#define NMTOOLS_ARRAY_FUNCTIONAL_UFUNCS_LOG_HPP

#include "nmtools/core/functor.hpp"
#include "nmtools/array/ufuncs/log.hpp"
#include "nmtools/core/ufunc/ufunc.hpp"

namespace nmtools::functional
{
    namespace fun
    {
        using log = fun::unary_ufunc<view::log_t>;
    }

    constexpr inline auto log = functor_t{unary_fmap_t<fun::log>{}};
} // namespace nmtools::functional


#endif // NMTOOLS_ARRAY_FUNCTIONAL_UFUNCS_LOG_HPP

#ifndef NMTOOLS_ARRAY_ARRAY_LOG_HPP
#define NMTOOLS_ARRAY_ARRAY_LOG_HPP

#include "nmtools/core/eval.hpp"
#include "nmtools/array/ufuncs/log.hpp"
#include "nmtools/constants.hpp"

namespace nmtools
{
    namespace fn
    {
        struct log
        {
            template <typename output_t=none_t, typename context_t=none_t, typename resolver_t=eval_result_t<>,
                typename left_t>
            inline constexpr auto operator()(const left_t& a,
                context_t&& context=context_t{}, output_t&& output=output_t{},meta::as_value<resolver_t> resolver=meta::as_value_v<resolver_t>) const
            {
                auto log = view::log(a);
                return eval(log
                    ,nmtools::forward<context_t>(context)
                    ,nmtools::forward<output_t>(output)
                    ,resolver
                );
            } // operator()
        }; // log
    } // namespace fn

    constexpr inline auto log = fn::log{};
} // namespace nmtools

#endif // NMTOOLS_ARRAY_ARRAY_LOG_HPP