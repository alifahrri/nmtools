#ifndef NMTOOLS_ARRAY_ARRAY_RINT_HPP
#define NMTOOLS_ARRAY_ARRAY_RINT_HPP

#include "nmtools/array/eval.hpp"
#include "nmtools/array/view/ufuncs/rint.hpp"
#include "nmtools/constants.hpp"

namespace nmtools::array
{
    namespace fn
    {
        struct rint
        {
            template <typename output_t=none_t, typename context_t=none_t, typename left_t>
            inline constexpr auto operator()(const left_t& a,
                context_t&& context=context_t{}, output_t&& output=output_t{}) const
            {
                auto rint = view::rint(a);
                return eval(rint,context,output);
            } // operator()
        }; // rint
    } // namespace fn

    constexpr inline auto rint = fn::rint{};
} // nmtools::array

#endif // NMTOOLS_ARRAY_ARRAY_RINT_HPP