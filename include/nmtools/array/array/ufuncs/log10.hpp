#ifndef NMTOOLS_ARRAY_ARRAY_LOG10_HPP
#define NMTOOLS_ARRAY_ARRAY_LOG10_HPP

#include "nmtools/array/eval.hpp"
#include "nmtools/array/view/ufuncs/log10.hpp"
#include "nmtools/constants.hpp"

namespace nmtools::array
{
    namespace fn
    {
        struct log10
        {
            template <typename output_t=none_t, typename context_t=none_t, typename left_t>
            inline constexpr auto operator()(const left_t& a,
                context_t&& context=context_t{}, output_t&& output=output_t{}) const
            {
                auto log10 = view::log10(a);
                return eval(log10,context,output);
            } // operator()
        }; // log10
    } // namespace fn

    constexpr inline auto log10 = fn::log10{};
} // nmtools::array

#endif // NMTOOLS_ARRAY_ARRAY_LOG10_HPP