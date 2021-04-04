#ifndef NMTOOLS_ARRAY_ARRAY_NEGATIVE_HPP
#define NMTOOLS_ARRAY_ARRAY_NEGATIVE_HPP

#include "nmtools/array/eval.hpp"
#include "nmtools/array/view/ufuncs/negative.hpp"
#include "nmtools/constants.hpp"

namespace nmtools::array
{
    namespace fn
    {
        struct negative
        {
            template <typename output_t=none_t, typename context_t=none_t, typename left_t>
            inline constexpr auto operator()(const left_t& a,
                context_t&& context=context_t{}, output_t&& output=output_t{}) const
            {
                auto negative = view::negative(a);
                return eval(negative,context,output);
            } // operator()
        }; // negative
    } // namespace fn

    constexpr inline auto negative = fn::negative{};
} // nmtools::array

#endif // NMTOOLS_ARRAY_ARRAY_NEGATIVE_HPP