#ifndef NMTOOLS_ARRAY_FUNCTIONAL_TRANSPOSE_HPP
#define NMTOOLS_ARRAY_FUNCTIONAL_TRANSPOSE_HPP

#include "nmtools/array/functional/functor.hpp"
#include "nmtools/array/functional/indexing.hpp"
#include "nmtools/array/view/transpose.hpp"

namespace nmtools::functional
{
    namespace fun
    {
        struct transpose_t
        {
            template <typename...args_t>
            constexpr auto operator()(const args_t&...args) const
            {
                return view::transpose(args...);
            }
        };
    }
    constexpr inline auto transpose = functor_t(unary_fmap_t<fun::transpose_t>{});
} // namespace nmtools::functional

#endif // NMTOOLS_ARRAY_FUNCTIONAL_TRANSPOSE_HPP