#ifndef NMTOOLS_ARRAY_ARRAY_CBRT_HPP
#define NMTOOLS_ARRAY_ARRAY_CBRT_HPP

#include "nmtools/array/eval.hpp"
#include "nmtools/array/view/ufuncs/cbrt.hpp"
#include "nmtools/constants.hpp"

namespace nmtools::array
{
    namespace fn
    {
        struct cbrt
        {
            template <typename output_t=none_t, typename context_t=none_t, typename left_t>
            inline constexpr auto operator()(const left_t& a,
                context_t&& context=context_t{}, output_t&& output=output_t{}) const
            {
                auto cbrt = view::cbrt(a);
                return eval(cbrt,context,output);
            } // operator()
        }; // cbrt
    } // namespace fn

    constexpr inline auto cbrt = fn::cbrt{};
} // nmtools::array

#endif // NMTOOLS_ARRAY_ARRAY_CBRT_HPP