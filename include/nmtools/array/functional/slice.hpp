#ifndef NMTOOLS_ARRAY_FUNCTIONAL_SLICE_HPP
#define NMTOOLS_ARRAY_FUNCTIONAL_SLICE_HPP

#include "nmtools/array/core/functor.hpp"
#include "nmtools/array/functional/indexing.hpp"
#include "nmtools/array/view/slice.hpp"

namespace nmtools::functional
{
    namespace fun
    {
        struct slice_t
        {
            template <typename...args_t>
            constexpr auto operator()(const args_t&...args) const
            {
                return view::slice(args...);
            }
        };

        struct apply_slice_t
        {
            template <typename...args_t>
            constexpr auto operator()(const args_t&...args) const
            {
                return view::apply_slice(args...);
            }
        };
    }

    constexpr inline auto slice = functor_t{unary_fmap_t<fun::slice_t>{}};

    constexpr inline auto apply_slice = functor_t{unary_fmap_t<fun::apply_slice_t>{}};
} // namespace nmtools::functional

#endif // NMTOOLS_ARRAY_FUNCTIONAL_SLICE_HPP