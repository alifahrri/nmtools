#ifndef NMTOOLS_ARRAY_ARRAY_GREATER_HPP
#define NMTOOLS_ARRAY_ARRAY_GREATER_HPP

#include "nmtools/array/eval.hpp"
#include "nmtools/array/view/ufuncs/greater.hpp"
#include "nmtools/constants.hpp"

namespace nmtools::array
{
    namespace fn
    {
        struct greater
        {
            template <typename output_t=none_t, typename context_t=none_t, typename left_t, typename right_t>
            inline constexpr auto operator()(const left_t& a, const right_t& b,
                context_t&& context=context_t{}, output_t&& output=output_t{}) const
            {
                auto greater = view::greater(a,b);
                return eval(greater,context,output);
            } // operator()
        }; // greater
    } // namespace fn

    constexpr inline auto greater = fn::greater{};
} // nmtools::array

#endif // NMTOOLS_ARRAY_ARRAY_GREATER_HPP