#ifndef NMTOOLS_ARRAY_ARRAY_EXPM1_HPP
#define NMTOOLS_ARRAY_ARRAY_EXPM1_HPP

#include "nmtools/array/eval.hpp"
#include "nmtools/array/view/ufuncs/expm1.hpp"
#include "nmtools/constants.hpp"

namespace nmtools::array
{
    namespace fn
    {
        struct expm1
        {
            template <typename output_t=none_t, typename context_t=none_t, typename left_t>
            inline constexpr auto operator()(const left_t& a,
                context_t&& context=context_t{}, output_t&& output=output_t{}) const
            {
                auto expm1 = view::expm1(a);
                return eval(expm1,context,output);
            } // operator()
        }; // expm1
    } // namespace fn

    constexpr inline auto expm1 = fn::expm1{};
} // nmtools::array

#endif // NMTOOLS_ARRAY_ARRAY_EXPM1_HPP