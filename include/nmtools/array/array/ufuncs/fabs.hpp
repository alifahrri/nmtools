#ifndef NMTOOLS_ARRAY_ARRAY_FABS_HPP
#define NMTOOLS_ARRAY_ARRAY_FABS_HPP

#include "nmtools/array/eval.hpp"
#include "nmtools/array/view/ufuncs/fabs.hpp"
#include "nmtools/constants.hpp"

namespace nmtools::array
{
    namespace fn
    {
        struct fabs
        {
            template <typename output_t=none_t, typename context_t=none_t, typename left_t>
            inline constexpr auto operator()(const left_t& a,
                context_t&& context=context_t{}, output_t&& output=output_t{}) const
            {
                auto fabs = view::fabs(a);
                return eval(fabs,context,output);
            } // operator()
        }; // fabs
    } // namespace fn

    constexpr inline auto fabs = fn::fabs{};
} // nmtools::array

#endif // NMTOOLS_ARRAY_ARRAY_FABS_HPP