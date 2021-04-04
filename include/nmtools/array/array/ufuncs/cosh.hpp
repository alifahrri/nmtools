#ifndef NMTOOLS_ARRAY_ARRAY_COSH_HPP
#define NMTOOLS_ARRAY_ARRAY_COSH_HPP

#include "nmtools/array/eval.hpp"
#include "nmtools/array/view/ufuncs/cosh.hpp"
#include "nmtools/constants.hpp"

namespace nmtools::array
{
    namespace fn
    {
        struct cosh
        {
            template <typename output_t=none_t, typename context_t=none_t, typename left_t>
            inline constexpr auto operator()(const left_t& a,
                context_t&& context=context_t{}, output_t&& output=output_t{}) const
            {
                auto cosh = view::cosh(a);
                return eval(cosh,context,output);
            } // operator()
        }; // cosh
    } // namespace fn

    constexpr inline auto cosh = fn::cosh{};
} // nmtools::array

#endif // NMTOOLS_ARRAY_ARRAY_COSH_HPP