#ifndef NMTOOLS_ARRAY_VIEW_SOFTMIN_HPP
#define NMTOOLS_ARRAY_VIEW_SOFTMIN_HPP

#include "nmtools/array/view/softmax.hpp"
#include "nmtools/array/view/ufuncs/negative.hpp"

namespace nmtools::view
{
    /**
     * @brief Create a view that computes softmin function along an axis
     * 
     * @tparam input_t 
     * @tparam dim_t 
     * @param input     input array
     * @param dim       axis in which softmin to be computed on
     * @return constexpr auto 
     */
    template <typename input_t, typename dim_t>
    constexpr auto softmin(const input_t& input, dim_t dim)
    {
        auto input_ = view::negative(input);
        return view::softmax(input_,dim);
    } // softmin
} // namespace nmtools::view


#endif // NMTOOLS_ARRAY_VIEW_SOFTMIN_HPP
