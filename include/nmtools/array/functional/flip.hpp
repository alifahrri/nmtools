#ifndef NMTOOLS_ARRAY_FUNCTIONAL_FLIP_HPP
#define NMTOOLS_ARRAY_FUNCTIONAL_FLIP_HPP

#include "nmtools/array/functional/functor.hpp"
#include "nmtools/array/functional/indexing.hpp"
#include "nmtools/array/view/flip.hpp"

namespace nmtools::functional
{
    namespace fun
    {
        struct flip_t
        {
            template <typename...args_t>
            constexpr auto operator()(const args_t&...args) const
            {
                return view::flip(args...);
            }
        };
    }

    constexpr inline auto flip = functor_t(unary_fmap_t<fun::flip_t>{});
} // namespace nmtools::functional


#endif // NMTOOLS_ARRAY_FUNCTIONAL_FLIP_HPP