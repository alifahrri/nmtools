#ifndef NMTOOLS_ARRAY_VIEW_UFUNCS_ARCTAN2_HPP
#define NMTOOLS_ARRAY_VIEW_UFUNCS_ARCTAN2_HPP

#include "nmtools/utility/to_string/to_string.hpp"
#include "nmtools/core/ufunc.hpp"
#include "nmtools/math.hpp"

namespace nmtools::view::fun
{
    struct arctan2
    {
        template <typename T, typename U>
        nmtools_func_attribute
        NMTOOLS_UFUNC_CONSTEXPR
        auto operator()(const T& t, const U& u) const
        {
            return math::atan2(t,u);
        } // operator()
    }; // arctan2
}

namespace nmtools::view
{
    using arctan2_t = fun::arctan2;

    template <typename left_t, typename right_t>
    nmtools_func_attribute
    NMTOOLS_UFUNC_CONSTEXPR
    auto arctan2(const left_t& a, const right_t& b)
    {
        return broadcast_binary_ufunc(arctan2_t{},a,b);
    } // arctan2
}

#if NMTOOLS_HAS_STRING

namespace nmtools::utils::impl
{
    template <auto...fmt_args>
    struct to_string_t<view::fun::arctan2,fmt_string_t<fmt_args...>>
    {
        using result_type = nmtools_string;

        auto operator()(view::fun::arctan2) const
        {
            auto str = nmtools_string();

            str += "arctan2";

            return str;
        }
    };
}

#endif // NMTOOLS_HAS_STRING

#endif // NMTOOLS_ARRAY_VIEW_UFUNCS_ARCTAN2_HPP

#ifndef NMTOOLS_ARRAY_FUNCTIONAL_UFUNCS_ARCTAN2_HPP
#define NMTOOLS_ARRAY_FUNCTIONAL_UFUNCS_ARCTAN2_HPP

#include "nmtools/core/functor.hpp"
#include "nmtools/array/ufuncs/arctan2.hpp"

namespace nmtools::functional
{
    namespace fun
    {
        struct arctan2_t
        {
            template <typename...args_t>
            constexpr auto operator()(const args_t&...args) const noexcept
            {
                return view::arctan2(args...);
            }
        };
    }

    constexpr inline auto arctan2 = functor_t{binary_fmap_t<fun::arctan2_t>{}};

    template <typename...arrays_t>
    struct get_function_t<
        view::decorator_t<
            view::ufunc_t, view::arctan2_t, arrays_t...
        >
    > {
        using view_type = view::decorator_t<
            view::ufunc_t, view::arctan2_t, arrays_t...
        >;

        view_type view;

        constexpr auto operator()() const noexcept
        {
           return arctan2; 
        }
    };
} // namespace nmtools::functional


#endif // NMTOOLS_ARRAY_FUNCTIONAL_UFUNCS_ARCTAN2_HPP

#ifndef NMTOOLS_ARRAY_ARRAY_ARCTAN2_HPP
#define NMTOOLS_ARRAY_ARRAY_ARCTAN2_HPP

#include "nmtools/core/eval.hpp"
#include "nmtools/array/ufuncs/arctan2.hpp"
#include "nmtools/constants.hpp"

namespace nmtools
{
    namespace fn
    {
        struct arctan2
        {
            template <typename output_t=none_t, typename context_t=none_t, typename resolver_t=eval_result_t<>,
                typename left_t, typename right_t>
            inline constexpr auto operator()(const left_t& a, const right_t& b,
                context_t&& context=context_t{}, output_t&& output=output_t{},meta::as_value<resolver_t> resolver=meta::as_value_v<resolver_t>) const
            {
                auto arctan2 = view::arctan2(a,b);
                return eval(arctan2
                    ,nmtools::forward<context_t>(context)
                    ,nmtools::forward<output_t>(output)
                    ,resolver
                );
            } // operator()
        }; // arctan2
    } // namespace fn

    constexpr inline auto arctan2 = fn::arctan2{};
} // namespace nmtools

#endif // NMTOOLS_ARRAY_ARRAY_ARCTAN2_HPP