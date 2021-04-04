#ifndef NMTOOLS_ARRAY_ARRAY_ARCSINH_HPP
#define NMTOOLS_ARRAY_ARRAY_ARCSINH_HPP

#include "nmtools/array/eval.hpp"
#include "nmtools/array/view/ufuncs/arcsinh.hpp"
#include "nmtools/constants.hpp"

namespace nmtools::array
{
    namespace fn
    {
        struct arcsinh
        {
            template <typename output_t=none_t, typename context_t=none_t, typename left_t>
            inline constexpr auto operator()(const left_t& a,
                context_t&& context=context_t{}, output_t&& output=output_t{}) const
            {
                auto arcsinh = view::arcsinh(a);
                return eval(arcsinh,context,output);
            } // operator()
        }; // arcsinh
    } // namespace fn

    constexpr inline auto arcsinh = fn::arcsinh{};
} // nmtools::array

#endif // NMTOOLS_ARRAY_ARRAY_ARCSINH_HPP