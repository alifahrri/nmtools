#ifndef NMTOOLS_ARRAY_FUNCTIONAL_HSTACK_HPP
#define NMTOOLS_ARRAY_FUNCTIONAL_HSTACK_HPP

#include "nmtools/array/core/functor.hpp"
#include "nmtools/array/functional/indexing.hpp"
#include "nmtools/array/view/hstack.hpp"

namespace nmtools::functional
{
    namespace fun
    {
        struct hstack_t
        {
            template <typename...args_t>
            constexpr auto operator()(const args_t&...args) const
            {
                return view::hstack(args...);
            }
        };
    }

    constexpr inline auto hstack = functor_t{binary_fmap_t<fun::hstack_t>{}};
} // namespace nmtools::functional

#endif // NMTOOLS_ARRAY_FUNCTIONAL_HSTACK_HPP