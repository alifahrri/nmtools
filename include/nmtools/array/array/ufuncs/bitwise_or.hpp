#ifndef NMTOOLS_ARRAY_ARRAY_BITWISE_OR_HPP
#define NMTOOLS_ARRAY_ARRAY_BITWISE_OR_HPP

#include "nmtools/array/eval.hpp"
#include "nmtools/array/view/ufuncs/bitwise_or.hpp"
#include "nmtools/constants.hpp"

namespace nmtools::array
{
    namespace fn
    {
        struct bitwise_or
        {
            template <typename output_t=none_t, typename context_t=none_t, typename left_t, typename right_t>
            inline constexpr auto operator()(const left_t& a, const right_t& b,
                context_t&& context=context_t{}, output_t&& output=output_t{}) const
            {
                auto bitwise_or = view::bitwise_or(a,b);
                return eval(bitwise_or,context,output);
            } // operator()
        }; // bitwise_or
    } // namespace fn

    constexpr inline auto bitwise_or = fn::bitwise_or{};
} // nmtools::array

#endif // NMTOOLS_ARRAY_ARRAY_BITWISE_OR_HPP