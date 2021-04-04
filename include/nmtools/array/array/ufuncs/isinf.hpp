#ifndef NMTOOLS_ARRAY_ARRAY_ISINF_HPP
#define NMTOOLS_ARRAY_ARRAY_ISINF_HPP

#include "nmtools/array/eval.hpp"
#include "nmtools/array/view/ufuncs/isinf.hpp"
#include "nmtools/constants.hpp"

namespace nmtools::array
{
    namespace fn
    {
        struct isinf
        {
            template <typename output_t=none_t, typename context_t=none_t, typename left_t>
            inline constexpr auto operator()(const left_t& a,
                context_t&& context=context_t{}, output_t&& output=output_t{}) const
            {
                auto isinf = view::isinf(a);
                return eval(isinf,context,output);
            } // operator()
        }; // isinf
    } // namespace fn

    constexpr inline auto isinf = fn::isinf{};
} // nmtools::array

#endif // NMTOOLS_ARRAY_ARRAY_ISINF_HPP