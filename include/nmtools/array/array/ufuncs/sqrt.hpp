#ifndef NMTOOLS_ARRAY_ARRAY_SQRT_HPP
#define NMTOOLS_ARRAY_ARRAY_SQRT_HPP

#include "nmtools/array/eval.hpp"
#include "nmtools/array/view/ufuncs/sqrt.hpp"
#include "nmtools/constants.hpp"

namespace nmtools::array
{
    namespace fn
    {
        struct sqrt
        {
            template <typename output_t=none_t, typename context_t=none_t, typename left_t>
            inline constexpr auto operator()(const left_t& a,
                context_t&& context=context_t{}, output_t&& output=output_t{}) const
            {
                auto sqrt = view::sqrt(a);
                return eval(sqrt,context,output);
            } // operator()
        }; // sqrt
    } // namespace fn

    constexpr inline auto sqrt = fn::sqrt{};
} // nmtools::array

#endif // NMTOOLS_ARRAY_ARRAY_SQRT_HPP