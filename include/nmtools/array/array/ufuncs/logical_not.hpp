#ifndef NMTOOLS_ARRAY_ARRAY_LOGICAL_NOT_HPP
#define NMTOOLS_ARRAY_ARRAY_LOGICAL_NOT_HPP

#include "nmtools/array/eval.hpp"
#include "nmtools/array/view/ufuncs/logical_not.hpp"
#include "nmtools/constants.hpp"

namespace nmtools::array
{
    namespace fn
    {
        struct logical_not
        {
            template <typename output_t=none_t, typename context_t=none_t, typename left_t>
            inline constexpr auto operator()(const left_t& a,
                context_t&& context=context_t{}, output_t&& output=output_t{}) const
            {
                auto logical_not = view::logical_not(a);
                return eval(logical_not,context,output);
            } // operator()
        }; // logical_not
    } // namespace fn

    constexpr inline auto logical_not = fn::logical_not{};
} // nmtools::array

#endif // NMTOOLS_ARRAY_ARRAY_LOGICAL_NOT_HPP