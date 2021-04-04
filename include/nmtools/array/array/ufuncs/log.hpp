#ifndef NMTOOLS_ARRAY_ARRAY_LOG_HPP
#define NMTOOLS_ARRAY_ARRAY_LOG_HPP

#include "nmtools/array/eval.hpp"
#include "nmtools/array/view/ufuncs/log.hpp"
#include "nmtools/constants.hpp"

namespace nmtools::array
{
    namespace fn
    {
        struct log
        {
            template <typename output_t=none_t, typename context_t=none_t, typename left_t>
            inline constexpr auto operator()(const left_t& a,
                context_t&& context=context_t{}, output_t&& output=output_t{}) const
            {
                auto log = view::log(a);
                return eval(log,context,output);
            } // operator()
        }; // log
    } // namespace fn

    constexpr inline auto log = fn::log{};
} // nmtools::array

#endif // NMTOOLS_ARRAY_ARRAY_LOG_HPP