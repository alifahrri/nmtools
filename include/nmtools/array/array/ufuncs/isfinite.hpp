#ifndef NMTOOLS_ARRAY_ARRAY_ISFINITE_HPP
#define NMTOOLS_ARRAY_ARRAY_ISFINITE_HPP

#include "nmtools/array/eval.hpp"
#include "nmtools/array/view/ufuncs/isfinite.hpp"
#include "nmtools/constants.hpp"

namespace nmtools::array
{
    namespace fn
    {
        struct isfinite
        {
            template <typename output_t=none_t, typename context_t=none_t, typename left_t>
            inline constexpr auto operator()(const left_t& a,
                context_t&& context=context_t{}, output_t&& output=output_t{}) const
            {
                auto isfinite = view::isfinite(a);
                return eval(isfinite,context,output);
            } // operator()
        }; // isfinite
    } // namespace fn

    constexpr inline auto isfinite = fn::isfinite{};
} // nmtools::array

#endif // NMTOOLS_ARRAY_ARRAY_ISFINITE_HPP