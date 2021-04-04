#ifndef NMTOOLS_ARRAY_ARRAY_SIN_HPP
#define NMTOOLS_ARRAY_ARRAY_SIN_HPP

#include "nmtools/array/eval.hpp"
#include "nmtools/array/view/ufuncs/sin.hpp"
#include "nmtools/constants.hpp"

namespace nmtools::array
{
    namespace fn
    {
        struct sin
        {
            template <typename output_t=none_t, typename context_t=none_t, typename left_t>
            inline constexpr auto operator()(const left_t& a,
                context_t&& context=context_t{}, output_t&& output=output_t{}) const
            {
                auto sin = view::sin(a);
                return eval(sin,context,output);
            } // operator()
        }; // sin
    } // namespace fn

    constexpr inline auto sin = fn::sin{};
} // nmtools::array

#endif // NMTOOLS_ARRAY_ARRAY_SIN_HPP