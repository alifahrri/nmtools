#ifndef NMTOOLS_ARRAY_ARRAY_COS_HPP
#define NMTOOLS_ARRAY_ARRAY_COS_HPP

#include "nmtools/array/eval.hpp"
#include "nmtools/array/view/ufuncs/cos.hpp"
#include "nmtools/constants.hpp"

namespace nmtools::array
{
    namespace fn
    {
        struct cos
        {
            template <typename output_t=none_t, typename context_t=none_t, typename left_t>
            inline constexpr auto operator()(const left_t& a,
                context_t&& context=context_t{}, output_t&& output=output_t{}) const
            {
                auto cos = view::cos(a);
                return eval(cos,context,output);
            } // operator()
        }; // cos
    } // namespace fn

    constexpr inline auto cos = fn::cos{};
} // nmtools::array

#endif // NMTOOLS_ARRAY_ARRAY_COS_HPP