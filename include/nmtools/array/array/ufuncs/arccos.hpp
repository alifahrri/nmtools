#ifndef NMTOOLS_ARRAY_ARRAY_ARCCOS_HPP
#define NMTOOLS_ARRAY_ARRAY_ARCCOS_HPP

#include "nmtools/array/eval.hpp"
#include "nmtools/array/view/ufuncs/arccos.hpp"
#include "nmtools/constants.hpp"

namespace nmtools::array
{
    namespace fn
    {
        struct arccos
        {
            template <typename output_t=none_t, typename context_t=none_t, typename left_t>
            inline constexpr auto operator()(const left_t& a,
                context_t&& context=context_t{}, output_t&& output=output_t{}) const
            {
                auto arccos = view::arccos(a);
                return eval(arccos,context,output);
            } // operator()
        }; // arccos
    } // namespace fn

    constexpr inline auto arccos = fn::arccos{};
} // nmtools::array

#endif // NMTOOLS_ARRAY_ARRAY_ARCCOS_HPP