#ifndef NMTOOLS_ARRAY_VIEW_ACTIVATIONS_RELU6_HPP
#define NMTOOLS_ARRAY_VIEW_ACTIVATIONS_RELU6_HPP

#include "nmtools/array/view/ufunc.hpp"

namespace nmtools::view
{
    struct relu6_t
    {
        template <typename T>
        constexpr auto operator()(const T& t) const
        {
            auto x = t;
            if (x < 0) {
                x = 0;
            } else if (x > 6) {
                x = 6;
            }
            return x;
        } // operator()
    }; // relu6_t

    template <typename array_t>
    constexpr auto relu6(const array_t& array)
    {
        return ufunc(relu6_t{},array);
    } // relu6
} // namespace nmtools::view

#endif // NMTOOLS_ARRAY_VIEW_ACTIVATIONS_RELU6_HPP