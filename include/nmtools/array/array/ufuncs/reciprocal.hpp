#ifndef NMTOOLS_ARRAY_ARRAY_RECIPROCAL_HPP
#define NMTOOLS_ARRAY_ARRAY_RECIPROCAL_HPP

#include "nmtools/array/eval.hpp"
#include "nmtools/array/view/ufuncs/reciprocal.hpp"
#include "nmtools/constants.hpp"

namespace nmtools::array
{
    namespace fn
    {
        struct reciprocal
        {
            template <typename output_t=none_t, typename context_t=none_t, typename left_t>
            inline constexpr auto operator()(const left_t& a,
                context_t&& context=context_t{}, output_t&& output=output_t{}) const
            {
                auto reciprocal = view::reciprocal(a);
                return eval(reciprocal,context,output);
            } // operator()
        }; // reciprocal
    } // namespace fn

    constexpr inline auto reciprocal = fn::reciprocal{};
} // nmtools::array

#endif // NMTOOLS_ARRAY_ARRAY_RECIPROCAL_HPP