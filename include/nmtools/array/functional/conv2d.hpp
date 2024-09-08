#ifndef NMTOOLS_ARRAY_FUNCTIONAL_CONV2D_HPP
#define NMTOOLS_ARRAY_FUNCTIONAL_CONV2D_HPP

#include "nmtools/array/functional/sliding_window.hpp"
#include "nmtools/array/functional/ufuncs/multiply.hpp"
#include "nmtools/array/functional/sum.hpp"
#include "nmtools/array/functional/reshape.hpp"
#include "nmtools/array/functional/expand.hpp"
#include "nmtools/array/functional/pad.hpp"
#include "nmtools/array/functional/functor.hpp"
#include "nmtools/array/view/conv2d.hpp"

namespace nmtools::functional
{
    namespace fun
    {
        struct conv2dv2
        {
            template <typename...args_t>
            constexpr auto operator()(const args_t&...args) const
            {
                return view::conv2dv2(args...);
            }
        };
    } // namespace fun

    constexpr inline auto conv2dv2 = functor_t{binary_fmap_t<fun::conv2dv2>{}};
} // namespace nmtools::functional

#endif // NMTOOLS_ARRAY_FUNCTIONAL_CONV2D_HPP