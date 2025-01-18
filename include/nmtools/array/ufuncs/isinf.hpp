#ifndef NMTOOLS_ARRAY_ARRAY_ISINF_HPP
#define NMTOOLS_ARRAY_ARRAY_ISINF_HPP

#include "nmtools/array/core/eval.hpp"
#include "nmtools/array/view/ufuncs/isinf.hpp"
#include "nmtools/constants.hpp"

namespace nmtools::array
{
    namespace fn
    {
        struct isinf
        {
            template <typename output_t=none_t, typename context_t=none_t, typename resolver_t=eval_result_t<>,
                typename left_t>
            inline constexpr auto operator()(const left_t& a,
                context_t&& context=context_t{}, output_t&& output=output_t{},meta::as_value<resolver_t> resolver=meta::as_value_v<resolver_t>) const
            {
                auto isinf = view::isinf(a);
                return eval(isinf
                    ,nmtools::forward<context_t>(context)
                    ,nmtools::forward<output_t>(output)
                    ,resolver
                );
            } // operator()
        }; // isinf
    } // namespace fn

    constexpr inline auto isinf = fn::isinf{};
} // nmtools::array

#endif // NMTOOLS_ARRAY_ARRAY_ISINF_HPP