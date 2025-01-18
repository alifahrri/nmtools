#ifndef NMTOOLS_ARRAY_FUNCTIONAL_ROLL_HPP
#define NMTOOLS_ARRAY_FUNCTIONAL_ROLL_HPP

#include "nmtools/array/core/functor.hpp"
#include "nmtools/array/functional/indexing.hpp"
#include "nmtools/array/view/roll.hpp"

namespace nmtools::functional
{
    namespace fun
    {
        struct roll
        {
            template <typename...args_t>
            constexpr auto operator()(const args_t&...args) const
            {

                return view::roll(args...);
            }
        };
    } // namespace fun
    constexpr inline auto roll = functor_t{unary_fmap_t<fun::roll>{}};
} // namespace nmtools::functional

#endif // NMTOOLS_ARRAY_FUNCTIONAL_ROLL_HPP