#ifndef NMTOOLS_ARRAY_VIEW_UFUNCS_FLOOR_HPP
#define NMTOOLS_ARRAY_VIEW_UFUNCS_FLOOR_HPP

#include "nmtools/utility/to_string/to_string.hpp"
#include "nmtools/core/ufunc.hpp"
#include "nmtools/math.hpp"

namespace nmtools::view::fun
{
    struct floor
    {
        template <typename T>
        nmtools_func_attribute
        NMTOOLS_UFUNC_CONSTEXPR
        auto operator()(const T& t) const
        {
            return math::floor(t);
        } // operator()
    }; // floor
}

namespace nmtools::view
{
    using floor_t = fun::floor;

    template <typename left_t>
    nmtools_func_attribute
    NMTOOLS_UFUNC_CONSTEXPR
    auto floor(const left_t& a)
    {
        return unary_ufunc(floor_t{},a);
    } // floor
}

#if NMTOOLS_HAS_STRING

namespace nmtools::utils::impl
{
    template <auto...fmt_args>
    struct to_string_t<view::fun::floor,fmt_string_t<fmt_args...>>
    {
        using result_type = nmtools_string;

        auto operator()(view::fun::floor) const
        {
            nmtools_string str;

            str += "floor";

            return str;
        }
    };
} // namespace nmtools::utils::impl

#endif // NMTOOLS_HAS_STRING

#endif // NMTOOLS_ARRAY_VIEW_UFUNCS_FLOOR_HPP

#ifndef NMTOOLS_ARRAY_FUNCTIONAL_UFUNCS_FLOOR_HPP
#define NMTOOLS_ARRAY_FUNCTIONAL_UFUNCS_FLOOR_HPP

#include "nmtools/core/functor.hpp"
#include "nmtools/array/ufuncs/floor.hpp"
#include "nmtools/core/ufunc/ufunc.hpp"

namespace nmtools::functional
{
    namespace fun
    {
        using floor = fun::unary_ufunc<view::floor_t>;
    }

    constexpr inline auto floor = functor_t{unary_fmap_t<fun::floor>{}};
} // namespace nmtools::functional


#endif // NMTOOLS_ARRAY_FUNCTIONAL_UFUNCS_FLOOR_HPP

#ifndef NMTOOLS_ARRAY_ARRAY_FLOOR_HPP
#define NMTOOLS_ARRAY_ARRAY_FLOOR_HPP

#include "nmtools/core/eval.hpp"
#include "nmtools/array/ufuncs/floor.hpp"
#include "nmtools/constants.hpp"

namespace nmtools::array
{
    namespace fn
    {
        struct floor
        {
            template <typename output_t=none_t, typename context_t=none_t, typename resolver_t=eval_result_t<>,
                typename left_t>
            inline constexpr auto operator()(const left_t& a,
                context_t&& context=context_t{}, output_t&& output=output_t{},meta::as_value<resolver_t> resolver=meta::as_value_v<resolver_t>) const
            {
                auto floor = view::floor(a);
                return eval(floor
                    ,nmtools::forward<context_t>(context)
                    ,nmtools::forward<output_t>(output)
                    ,resolver
                );
            } // operator()
        }; // floor
    } // namespace fn

    constexpr inline auto floor = fn::floor{};
} // nmtools::array

#endif // NMTOOLS_ARRAY_ARRAY_FLOOR_HPP