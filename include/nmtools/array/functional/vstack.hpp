#ifndef NMTOOLS_ARRAY_FUNCTIONAL_VSTACK_HPP
#define NMTOOLS_ARRAY_FUNCTIONAL_VSTACK_HPP

#include "nmtools/array/functional/functor.hpp"
#include "nmtools/array/functional/indexing.hpp"
#include "nmtools/array/view/vstack.hpp"

namespace nmtools::functional
{
    namespace fun
    {
        struct vstack_t
        {
            template <typename...args_t>
            constexpr auto operator()(const args_t&...args) const
            {
                return view::vstack(args...);
            }
        };
    }

    constexpr inline auto vstack = functor_t{binary_fmap_t<fun::vstack_t>{}};
} // namespace nmtools::functional

#endif // NMTOOLS_ARRAY_FUNCTIONAL_VSTACK_HPP