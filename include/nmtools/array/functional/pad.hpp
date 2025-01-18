#ifndef NMTOOLS_ARRAY_FUNCTIONAL_PAD_HPP
#define NMTOOLS_ARRAY_FUNCTIONAL_PAD_HPP

#include "nmtools/array/core/functor.hpp"
#include "nmtools/array/functional/indexing.hpp"
#include "nmtools/array/view/pad.hpp"

namespace nmtools::functional
{
    namespace fun
    {
        struct pad
        {
            template <typename...args_t>
            constexpr auto operator()(const args_t&...args) const
            {
                return view::pad(args...);
            }
        };
    }

    constexpr inline auto pad = functor_t{unary_fmap_t<fun::pad>{}};
} // namespace nmtools::functional

#endif // NMTOOLS_ARRAY_FUNCTIONAL_PAD_HPP