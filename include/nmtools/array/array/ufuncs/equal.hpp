#ifndef NMTOOLS_ARRAY_ARRAY_EQUAL_HPP
#define NMTOOLS_ARRAY_ARRAY_EQUAL_HPP

#include "nmtools/array/eval.hpp"
#include "nmtools/array/view/ufuncs/equal.hpp"
#include "nmtools/constants.hpp"

namespace nmtools::array
{
    namespace fn
    {
        struct equal
        {
            template <typename output_t=none_t, typename context_t=none_t, typename left_t, typename right_t>
            inline constexpr auto operator()(const left_t& a, const right_t& b,
                context_t&& context=context_t{}, output_t&& output=output_t{}) const
            {
                auto equal = view::equal(a,b);
                return eval(equal,context,output);
            } // operator()
        }; // equal
    } // namespace fn

    constexpr inline auto equal = fn::equal{};
} // nmtools::array

#endif // NMTOOLS_ARRAY_ARRAY_EQUAL_HPP