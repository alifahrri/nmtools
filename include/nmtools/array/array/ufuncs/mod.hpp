#ifndef NMTOOLS_ARRAY_ARRAY_MOD_HPP
#define NMTOOLS_ARRAY_ARRAY_MOD_HPP

#include "nmtools/array/eval.hpp"
#include "nmtools/array/view/ufuncs/mod.hpp"
#include "nmtools/constants.hpp"

namespace nmtools::array
{
    namespace fn
    {
        struct mod
        {
            template <typename output_t=none_t, typename context_t=none_t, typename left_t, typename right_t>
            inline constexpr auto operator()(const left_t& a, const right_t& b,
                context_t&& context=context_t{}, output_t&& output=output_t{}) const
            {
                auto mod = view::mod(a,b);
                return eval(mod,context,output);
            } // operator()
        }; // mod
    } // namespace fn

    constexpr inline auto mod = fn::mod{};
} // nmtools::array

#endif // NMTOOLS_ARRAY_ARRAY_MOD_HPP