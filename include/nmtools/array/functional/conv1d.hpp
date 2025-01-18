#ifndef NMTOOLS_ARRAY_FUNCTIONAL_CONV1D_HPP
#define NMTOOLS_ARRAY_FUNCTIONAL_CONV1D_HPP

#include "nmtools/array/functional/sliding_window.hpp"
#include "nmtools/array/functional/ufuncs/multiply.hpp"
#include "nmtools/array/functional/sum.hpp"
#include "nmtools/array/functional/reshape.hpp"
#include "nmtools/array/functional/expand.hpp"
#include "nmtools/array/functional/pad.hpp"
#include "nmtools/array/core/functor.hpp"
#include "nmtools/array/view/conv1d.hpp"

namespace nmtools::functional
{
    namespace fun
    {
        struct conv1d
        {
            template <typename array_t, typename weight_t, typename...args_t>
            constexpr auto operator()(const array_t& array, const weight_t& weight, const args_t&...args) const
            {
                return view::conv1d(array,weight,None,args...);
            }
        };

        struct conv1d_bias
        {
            template <typename array_t, typename weight_t, typename bias_t, typename...args_t>
            constexpr auto operator()(const array_t& array, const weight_t& weight, const bias_t& bias, const args_t&...args) const
            {
                return view::conv1d(array,weight,bias,args...);
            }
        };
    } // namespace fun

    constexpr inline auto conv1d = functor_t{binary_fmap_t<fun::conv1d>{}};

    constexpr inline auto conv1d_bias = functor_t{ternary_fmap_t<fun::conv1d_bias>{}};
} // namespace nmtools::functional

#endif // NMTOOLS_ARRAY_FUNCTIONAL_CONV1D_HPP