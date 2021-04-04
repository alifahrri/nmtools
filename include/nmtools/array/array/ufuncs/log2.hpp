#ifndef NMTOOLS_ARRAY_ARRAY_LOG2_HPP
#define NMTOOLS_ARRAY_ARRAY_LOG2_HPP

#include "nmtools/array/eval.hpp"
#include "nmtools/array/view/ufuncs/log2.hpp"
#include "nmtools/constants.hpp"

namespace nmtools::array
{
    namespace fn
    {
        struct log2
        {
            template <typename output_t=none_t, typename context_t=none_t, typename left_t>
            inline constexpr auto operator()(const left_t& a,
                context_t&& context=context_t{}, output_t&& output=output_t{}) const
            {
                auto log2 = view::log2(a);
                return eval(log2,context,output);
            } // operator()
        }; // log2
    } // namespace fn

    constexpr inline auto log2 = fn::log2{};
} // nmtools::array

#endif // NMTOOLS_ARRAY_ARRAY_LOG2_HPP