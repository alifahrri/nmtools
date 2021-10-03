#ifndef NMTOOLS_ARRAY_ARRAY_ATLEAST_2D_HPP
#define NMTOOLS_ARRAY_ARRAY_ATLEAST_2D_HPP

#include "nmtools/array/view/atleast_2d.hpp"
#include "nmtools/array/eval.hpp"

namespace nmtools::array
{
    /**
     * @brief Eagerly compute atleast_2d.
     * 
     * @tparam output_t 
     * @tparam context_t 
     * @tparam array_t 
     * @param array   Input array
     * @param context Evaluation context
     * @param output 
     * @return constexpr auto 
     */
    template <typename output_t=none_t, typename context_t=none_t,
        typename array_t>
    constexpr auto atleast_2d(const array_t& array,
        context_t&& context=context_t{}, output_t&& output=output_t{})
    {
        auto viewed = view::atleast_2d(array);
        return eval(viewed,context,output);
    } // atleast_2d
} // namespace nmtools::array

#endif // NMTOOLS_ARRAY_ARRAY_ATLEAST_2D_HPP