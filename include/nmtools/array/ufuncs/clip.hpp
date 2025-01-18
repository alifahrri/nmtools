#ifndef NMTOOLS_ARRAY_ARRAY_CLIP_HPP
#define NMTOOLS_ARRAY_ARRAY_CLIP_HPP

#include "nmtools/array/core/eval.hpp"
#include "nmtools/array/view/ufuncs/clip.hpp"
#include "nmtools/constants.hpp"

namespace nmtools::array
{
    /**
     * @brief Eagerly evaluate clip
     * 
     * @tparam output_t 
     * @tparam context_t 
     * @tparam array_t 
     * @tparam amin_t 
     * @tparam amax_t 
     * @param a array to be clipped
     * @param amin 
     * @param amax 
     * @param context execution context
     * @param output 
     * @return constexpr auto 
     */
    template <typename output_t=none_t, typename context_t=none_t, typename resolver_t=eval_result_t<>,
        typename array_t, typename amin_t, typename amax_t>
    constexpr auto clip(const array_t& a, const amin_t& amin, const amax_t& amax,
        context_t&& context=context_t{}, output_t&& output=output_t{},meta::as_value<resolver_t> resolver=meta::as_value_v<resolver_t>) 
    {
        auto clipped = view::clip(a,amin,amax);
        return eval(clipped
            ,nmtools::forward<context_t>(context)
            ,nmtools::forward<output_t>(output)
            ,resolver
        );
    } // clip
} // nmtools::array

#endif // NMTOOLS_ARRAY_ARRAY_CLIP_HPP