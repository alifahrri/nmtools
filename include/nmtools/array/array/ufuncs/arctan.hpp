#ifndef NMTOOLS_ARRAY_ARRAY_ARCTAN_HPP
#define NMTOOLS_ARRAY_ARRAY_ARCTAN_HPP

#include "nmtools/array/eval.hpp"
#include "nmtools/array/view/ufuncs/arctan.hpp"
#include "nmtools/constants.hpp"

namespace nmtools::array
{
    namespace fn
    {
        struct arctan
        {
            template <typename output_t=none_t, typename context_t=none_t, typename left_t>
            inline constexpr auto operator()(const left_t& a,
                context_t&& context=context_t{}, output_t&& output=output_t{}) const
            {
                auto arctan = view::arctan(a);
                return eval(arctan,context,output);
            } // operator()
        }; // arctan
    } // namespace fn

    constexpr inline auto arctan = fn::arctan{};
} // nmtools::array

#endif // NMTOOLS_ARRAY_ARRAY_ARCTAN_HPP