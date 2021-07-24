#ifndef NMTOOLS_ARRAY_ARRAY_ARANGE
#define NMTOOLS_ARRAY_ARRAY_ARANGE

#include "nmtools/array/eval.hpp"
#include "nmtools/array/view/arange.hpp"
#include "nmtools/constants.hpp"

namespace nmtools::array
{
    /**
     * @brief Eagerly compute arange.
     * 
     * @tparam output_t 
     * @tparam context_t 
     * @tparam start_t 
     * @tparam stop_t 
     * @tparam step_t 
     * @tparam T 
     * @param start   start of the interval
     * @param stop    end of the interval
     * @param step    spacing between interval
     * @param dtype   desired data type
     * @param context evaluation context
     * @param output 
     * @return constexpr auto 
     */
    template <typename output_t=none_t, typename context_t=none_t,
        typename start_t, typename stop_t, typename step_t, typename T=float>
    constexpr auto arange(start_t start, stop_t stop, step_t step, dtype_t<T> dtype=float32,
        context_t&& context=context_t{}, output_t&& output=output_t{})
    {
        auto range = view::arange(start,stop,step,dtype);
        return eval(range,context,output);
    } // arange

    template <typename output_t=none_t, typename context_t=none_t,
        typename start_t, typename stop_t, typename T=float>
    constexpr auto arange(start_t start, stop_t stop, dtype_t<T> dtype=float32,
        context_t&& context=context_t{}, output_t&& output=output_t{})
    {
        auto range = view::arange(start,stop,1,dtype);
        return eval(range,context,output);
    } // arange

    template <typename output_t=none_t, typename context_t=none_t,
        typename stop_t, typename T=float>
    constexpr auto arange(stop_t stop, dtype_t<T> dtype=float32,
        context_t&& context=context_t{}, output_t&& output=output_t{})
    {
        auto range = view::arange(0,stop,1,dtype);
        return eval(range,context,output);
    } // arange
} // nmtools::array

#endif // NMTOOLS_ARRAY_ARRAY_ARANGE