#ifndef NMTOOLS_ARRAY_ARRAY_GREATER_EQUAL_HPP
#define NMTOOLS_ARRAY_ARRAY_GREATER_EQUAL_HPP

#include "nmtools/array/eval.hpp"
#include "nmtools/array/view/ufuncs/greater_equal.hpp"
#include "nmtools/constants.hpp"

namespace nmtools::array
{
    namespace fn
    {
        struct greater_equal
        {
            template <typename output_t=none_t, typename context_t=none_t, typename left_t, typename right_t>
            inline constexpr auto operator()(const left_t& a, const right_t& b,
                context_t&& context=context_t{}, output_t&& output=output_t{}) const
            {
                auto greater_equal = view::greater_equal(a,b);
                return eval(greater_equal,context,output);
            } // operator()
        }; // greater_equal
    } // namespace fn

    constexpr inline auto greater_equal = fn::greater_equal{};
} // nmtools::array

#endif // NMTOOLS_ARRAY_ARRAY_GREATER_EQUAL_HPP