#ifndef NMTOOLS_ARRAY_ARRAY_TANH_HPP
#define NMTOOLS_ARRAY_ARRAY_TANH_HPP

#include "nmtools/array/eval.hpp"
#include "nmtools/array/view/ufuncs/tanh.hpp"
#include "nmtools/constants.hpp"

namespace nmtools::array
{
    namespace fn
    {
        struct tanh
        {
            template <typename output_t=none_t, typename context_t=none_t, typename left_t>
            inline constexpr auto operator()(const left_t& a,
                context_t&& context=context_t{}, output_t&& output=output_t{}) const
            {
                auto tanh = view::tanh(a);
                return eval(tanh,context,output);
            } // operator()
        }; // tanh
    } // namespace fn

    constexpr inline auto tanh = fn::tanh{};
} // nmtools::array

#endif // NMTOOLS_ARRAY_ARRAY_TANH_HPP