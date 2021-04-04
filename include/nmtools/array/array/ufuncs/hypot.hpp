#ifndef NMTOOLS_ARRAY_ARRAY_HYPOT_HPP
#define NMTOOLS_ARRAY_ARRAY_HYPOT_HPP

#include "nmtools/array/eval.hpp"
#include "nmtools/array/view/ufuncs/hypot.hpp"
#include "nmtools/constants.hpp"

namespace nmtools::array
{
    namespace fn
    {
        struct hypot
        {
            template <typename output_t=none_t, typename context_t=none_t, typename left_t, typename right_t>
            inline constexpr auto operator()(const left_t& a, const right_t& b,
                context_t&& context=context_t{}, output_t&& output=output_t{}) const
            {
                auto hypot = view::hypot(a,b);
                return eval(hypot,context,output);
            } // operator()
        }; // hypot
    } // namespace fn

    constexpr inline auto hypot = fn::hypot{};
} // nmtools::array

#endif // NMTOOLS_ARRAY_ARRAY_HYPOT_HPP