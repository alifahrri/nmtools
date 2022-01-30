#ifndef NMTOOLS_ARRAY_ARRAY_POOLING_HPP
#define NMTOOLS_ARRAY_ARRAY_POOLING_HPP

#include "nmtools/array/view/pooling.hpp"
#include "nmtools/array/eval.hpp"

namespace nmtools::array
{
    // TODO: implement padding
    // TODO: implement dilation
    /**
     * @brief Eagerly applies a max pooling on 2D window.
     * 
     * @tparam output_t 
     * @tparam context_t 
     * @tparam array_t 
     * @tparam kernel_size_t 
     * @tparam stride_t 
     * @tparam ceil_mode_t 
     * @param array         input array
     * @param kernel_size   the size of the window to take max
     * @param stride        the stride of the window
     * @param ceil_mode 
     * @param context       optional evaluation context
     * @param output        optional output
     * @return constexpr auto 
     */
    template <typename output_t=none_t, typename context_t=none_t,
        typename array_t, typename kernel_size_t, typename stride_t, typename ceil_mode_t>
    constexpr auto max_pool2d(const array_t& array, const kernel_size_t& kernel_size, const stride_t& stride, ceil_mode_t ceil_mode,
        context_t&& context=context_t{}, output_t&& output=output_t{})
    {
        auto pool = view::max_pool2d(array,kernel_size,stride,ceil_mode);
        return eval(pool,nmtools::forward<context_t>(context),nmtools::forward<output_t>(output));
    } // max_pool

    // TODO: implement padding
    // TODO: implement dilation
    /**
     * @brief Eagerly applies a average pooling with 2D window.
     * 
     * @tparam output_t 
     * @tparam context_t 
     * @tparam array_t 
     * @tparam kernel_size_t 
     * @tparam stride_t 
     * @tparam ceil_mode_t 
     * @param array         input array
     * @param kernel_size   the size of the window to take average
     * @param stride        the stride of the window
     * @param ceil_mode 
     * @param context       optional evaluation context
     * @param output        optional output
     * @return constexpr auto 
     */
    template <typename output_t=none_t, typename context_t=none_t,
        typename array_t, typename kernel_size_t, typename stride_t, typename ceil_mode_t>
    constexpr auto avg_pool2d(const array_t& array, const kernel_size_t& kernel_size, const stride_t& stride, ceil_mode_t ceil_mode,
        context_t&& context=context_t{}, output_t&& output=output_t{})
    {
        auto pool = view::avg_pool2d(array,kernel_size,stride,ceil_mode);
        return eval(pool,nmtools::forward<context_t>(context),nmtools::forward<output_t>(output));
    } // avg_pool
} // namespace nmtools::array


#endif // NMTOOLS_ARRAY_ARRAY_POOLING_HPP