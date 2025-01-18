#ifndef NMTOOLS_ARRAY_FUNCTIONAL_BROADCAST_TO_HPP
#define NMTOOLS_ARRAY_FUNCTIONAL_BROADCAST_TO_HPP

#include "nmtools/array/core/functor.hpp"
#include "nmtools/array/functional/indexing.hpp"
#include "nmtools/array/view/broadcast_to.hpp"

namespace nmtools::functional
{
    namespace fun
    {
        struct broadcast_to_t
        {
            template <typename...args_t>
            constexpr auto operator()(const args_t&...args) const
            {
                return view::broadcast_to(args...);
            }
        };
    } // namespace fun

    constexpr inline auto broadcast_to = functor_t{unary_fmap_t<fun::broadcast_to_t>{}};
} // namespace nmtools::functional

#endif // NMTOOLS_ARRAY_FUNCTIONAL_BROADCAST_TO_HPP