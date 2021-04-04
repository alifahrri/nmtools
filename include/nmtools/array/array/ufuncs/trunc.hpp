#ifndef NMTOOLS_ARRAY_ARRAY_TRUNC_HPP
#define NMTOOLS_ARRAY_ARRAY_TRUNC_HPP

#include "nmtools/array/eval.hpp"
#include "nmtools/array/view/ufuncs/trunc.hpp"
#include "nmtools/constants.hpp"

namespace nmtools::array
{
    namespace fn
    {
        struct trunc
        {
            template <typename output_t=none_t, typename context_t=none_t, typename left_t>
            inline constexpr auto operator()(const left_t& a,
                context_t&& context=context_t{}, output_t&& output=output_t{}) const
            {
                auto trunc = view::trunc(a);
                return eval(trunc,context,output);
            } // operator()
        }; // trunc
    } // namespace fn

    constexpr inline auto trunc = fn::trunc{};
} // nmtools::array

#endif // NMTOOLS_ARRAY_ARRAY_TRUNC_HPP