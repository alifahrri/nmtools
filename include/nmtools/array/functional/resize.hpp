#ifndef NMTOOLS_ARRAY_FUNCTIONAL_RESIZE_HPP
#define NMTOOLS_ARRAY_FUNCTIONAL_RESIZE_HPP

#include "nmtools/array/functional/functor.hpp"
#include "nmtools/array/functional/indexing.hpp"
#include "nmtools/array/view/resize.hpp"

namespace nmtools::functional
{
    namespace fun
    {
        struct resize_t
        {
            template <typename...args_t>
            constexpr auto operator()(const args_t&...args) const
            {
                return view::resize(args...);
            }
        };
    }

    constexpr inline auto resize = functor_t(unary_fmap_t<fun::resize_t>{});
} // namespace nmtools::functional

#endif // NMTOOLS_ARRAY_FUNCTIONAL_RESIZE_HPP