#ifndef NMTOOLS_ARRAY_FUNCTIONAL_SQUEEZE_HPP
#define NMTOOLS_ARRAY_FUNCTIONAL_SQUEEZE_HPP

#include "nmtools/array/core/functor.hpp"
#include "nmtools/array/functional/indexing.hpp"
#include "nmtools/array/view/squeeze.hpp"

namespace nmtools::functional
{
    namespace fun
    {
        struct squeeze_t
        {
            template <typename...args_t>
            constexpr auto operator()(const args_t&...args) const
            {
                return view::squeeze(args...);
            }
        };
    }

    constexpr inline auto squeeze = functor_t{unary_fmap_t<fun::squeeze_t>{}};
} // namespace nmtools::functional

#endif // NMTOOLS_ARRAY_FUNCTIONAL_SQUEEZE_HPP