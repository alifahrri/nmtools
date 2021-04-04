#ifndef NMTOOLS_ARRAY_ARRAY_INVERT_HPP
#define NMTOOLS_ARRAY_ARRAY_INVERT_HPP

#include "nmtools/array/eval.hpp"
#include "nmtools/array/view/ufuncs/invert.hpp"
#include "nmtools/constants.hpp"

namespace nmtools::array
{
    namespace fn
    {
        struct invert
        {
            template <typename output_t=none_t, typename context_t=none_t, typename left_t>
            inline constexpr auto operator()(const left_t& a,
                context_t&& context=context_t{}, output_t&& output=output_t{}) const
            {
                auto invert = view::invert(a);
                return eval(invert,context,output);
            } // operator()
        }; // invert
    } // namespace fn

    constexpr inline auto invert = fn::invert{};
} // nmtools::array

#endif // NMTOOLS_ARRAY_ARRAY_INVERT_HPP