#ifndef NMTOOLS_ARRAY_ARRAY_LESS_HPP
#define NMTOOLS_ARRAY_ARRAY_LESS_HPP

#include "nmtools/array/eval.hpp"
#include "nmtools/array/view/ufuncs/less.hpp"
#include "nmtools/constants.hpp"

namespace nmtools::array
{
    namespace fn
    {
        struct less
        {
            template <typename output_t=none_t, typename context_t=none_t, typename left_t, typename right_t>
            inline constexpr auto operator()(const left_t& a, const right_t& b,
                context_t&& context=context_t{}, output_t&& output=output_t{}) const
            {
                auto less = view::less(a,b);
                return eval(less,context,output);
            } // operator()
        }; // less
    } // namespace fn

    constexpr inline auto less = fn::less{};
} // nmtools::array

#endif // NMTOOLS_ARRAY_ARRAY_LESS_HPP