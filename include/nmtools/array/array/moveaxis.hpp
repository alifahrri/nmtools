#ifndef NMTOOLS_ARRAY_ARRAY_MOVEAXIS_HPP
#define NMTOOLS_ARRAY_ARRAY_MOVEAXIS_HPP

#include "nmtools/array/view/moveaxis.hpp"
#include "nmtools/array/eval.hpp"

namespace nmtools::array
{
    /**
     * @brief Eagerly move axis of an array to another position
     * 
     * @tparam output_t 
     * @tparam context_t 
     * @tparam array_t 
     * @tparam source_t 
     * @tparam destination_t 
     * @param array         input array
     * @param source        original position of axes to be moved
     * @param destination   desired position for each axes
     * @param context       evaluation context
     * @param output 
     * @return constexpr auto 
     */
    template <typename output_t=none_t, typename context_t=none_t,
        typename array_t, typename source_t, typename destination_t>
    constexpr auto moveaxis(const array_t& array, const source_t& source, const destination_t& destination,
        context_t&& context=context_t{}, output_t&& output=output_t{})
    {
        auto a = view::moveaxis(array,source,destination);
        return eval(a,context,output);
    } // moveaxis
} // namespace nmtools::array


#endif // NMTOOLS_ARRAY_ARRAY_MOVEAXIS_HPP