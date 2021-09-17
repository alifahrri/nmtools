#ifndef NMTOOLS_ARRAY_VIEW_ACTIVATIONS_HARDTANH_HPP
#define NMTOOLS_ARRAY_VIEW_ACTIVATIONS_HARDTANH_HPP

#include "nmtools/array/view/ufunc.hpp"

namespace nmtools::view
{
    /**
     * @brief Function object for hardtanh ufunc.
     * 
     * @tparam min_val_t 
     * @tparam max_val_t 
     */
    template <typename min_val_t=float, typename max_val_t=float>
    struct hardtanh_t
    {
        const min_val_t min_val = -1.0;
        const max_val_t max_val =  1.0;

        template <typename T>
        constexpr auto operator()(const T& t) const
        {
            if (t < min_val) {
                return min_val;
            } else if (t > max_val) {
                return max_val;
            } else {
                return t;
            }
        } // operator()
    }; // hardtanh_t

    template <typename min_val_t, typename max_val_t>
    hardtanh_t(min_val_t,max_val_t) -> hardtanh_t<min_val_t,max_val_t>;

    /**
     * @brief Create element-wise hardtanh ufunc view.
     * 
     * @tparam array_t 
     * @tparam min_val_t 
     * @tparam max_val_t 
     * @param array     input array
     * @param min_val   minimum value of the linear region
     * @param max_val   maximum value of the linear region
     * @return constexpr auto 
     */
    template <typename array_t, typename min_val_t=float, typename max_val_t=float>
    constexpr auto hardtanh(const array_t& array, const min_val_t min_val=min_val_t{-1.0},
        const max_val_t max_val=max_val_t{1.0})
    {
        return ufunc(hardtanh_t{min_val,max_val},array);
    } // hardtanh
} // namespace nmtools::view

#endif // NMTOOLS_ARRAY_VIEW_ACTIVATIONS_HARDTANH_HPP