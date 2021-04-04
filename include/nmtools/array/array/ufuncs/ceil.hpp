#ifndef NMTOOLS_ARRAY_ARRAY_CEIL_HPP
#define NMTOOLS_ARRAY_ARRAY_CEIL_HPP

#include "nmtools/array/eval.hpp"
#include "nmtools/array/view/ufuncs/ceil.hpp"
#include "nmtools/constants.hpp"

namespace nmtools::array
{
    namespace fn
    {
        struct ceil
        {
            template <typename output_t=none_t, typename context_t=none_t, typename left_t>
            inline constexpr auto operator()(const left_t& a,
                context_t&& context=context_t{}, output_t&& output=output_t{}) const
            {
                auto ceil = view::ceil(a);
                return eval(ceil,context,output);
            } // operator()
        }; // ceil
    } // namespace fn

    constexpr inline auto ceil = fn::ceil{};
} // nmtools::array

#endif // NMTOOLS_ARRAY_ARRAY_CEIL_HPP