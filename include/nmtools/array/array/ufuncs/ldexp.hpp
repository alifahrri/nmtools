#ifndef NMTOOLS_ARRAY_ARRAY_LDEXP_HPP
#define NMTOOLS_ARRAY_ARRAY_LDEXP_HPP

#include "nmtools/array/eval.hpp"
#include "nmtools/array/view/ufuncs/ldexp.hpp"
#include "nmtools/constants.hpp"

namespace nmtools::array
{
    namespace fn
    {
        struct ldexp
        {
            template <typename output_t=none_t, typename context_t=none_t, typename resolver_t=eval_result_t,
                typename left_t, typename right_t>
            inline constexpr auto operator()(const left_t& a, const right_t& b,
                context_t&& context=context_t{}, output_t&& output=output_t{},meta::as_value<resolver_t> resolver=meta::as_value_v<resolver_t>) const
            {
                auto ldexp = view::ldexp(a,b);
                return eval(ldexp
                    ,nmtools::forward<context_t>(context)
                    ,nmtools::forward<output_t>(output)
                    ,resolver
                );
            } // operator()
        }; // ldexp
    } // namespace fn

    constexpr inline auto ldexp = fn::ldexp{};
} // nmtools::array

#endif // NMTOOLS_ARRAY_ARRAY_LDEXP_HPP