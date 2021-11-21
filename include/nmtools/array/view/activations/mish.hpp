#ifndef NMTOOLS_ARRAY_VIEW_ACTIVATIONS_MISH_HPP
#define NMTOOLS_ARRAY_VIEW_ACTIVATIONS_MISH_HPP

#include "nmtools/array/view/ufunc.hpp"
#include "nmtools/array/view/activations/softplus.hpp"
#include "nmtools/math.hpp"

namespace nmtools::view
{
    /**
     * @brief Function object for mish ufunc
     * 
     */
    struct mish_t
    {
        template <typename T>
        NMTOOLS_UFUNC_CONSTEXPR
        auto operator()(const T& t) const
        {
            return t * math::tanh(softplus_t<>::softplus(t));
        } // operator()
    }; // mish_t

    /**
     * @brief Create element-wise mish ufunc view
     * 
     * @tparam array_t 
     * @param array     input array
     * @return NMTOOLS_UFUNC_CONSTEXPR 
     */
    template <typename array_t>
    NMTOOLS_UFUNC_CONSTEXPR
    auto mish(const array_t& array)
    {
        return ufunc(mish_t{},array);
    } // mish
} // namespace nmtools::view

#endif // NMTOOLS_ARRAY_VIEW_ACTIVATIONS_MISH_HPP