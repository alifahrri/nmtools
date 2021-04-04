#ifndef NMTOOLS_ARRAY_ARRAY_POSITIVE_HPP
#define NMTOOLS_ARRAY_ARRAY_POSITIVE_HPP

#include "nmtools/array/eval.hpp"
#include "nmtools/array/view/ufuncs/positive.hpp"
#include "nmtools/constants.hpp"

namespace nmtools::array
{
    namespace fn
    {
        struct positive
        {
            template <typename output_t=none_t, typename context_t=none_t, typename left_t>
            inline constexpr auto operator()(const left_t& a,
                context_t&& context=context_t{}, output_t&& output=output_t{}) const
            {
                auto positive = view::positive(a);
                return eval(positive,context,output);
            } // operator()
        }; // positive
    } // namespace fn

    constexpr inline auto positive = fn::positive{};
} // nmtools::array

#endif // NMTOOLS_ARRAY_ARRAY_POSITIVE_HPP