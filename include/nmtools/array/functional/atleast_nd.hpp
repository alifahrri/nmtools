#ifndef NMTOOLS_ARRAY_FUNCTIONAL_ATLEAST_ND_HPP
#define NMTOOLS_ARRAY_FUNCTIONAL_ATLEAST_ND_HPP

#include "nmtools/array/functional/functor.hpp"
#include "nmtools/array/functional/indexing.hpp"
#include "nmtools/array/functional/reshape.hpp"
#include "nmtools/array/view/atleast_nd.hpp"

namespace nmtools::functional
{
    namespace fun
    {
        struct atleast_nd_t
        {
            template <typename...args_t>
            constexpr auto operator()(const args_t&...args) const
            {
                return view::atleast_nd(args...);
            }
        };
    } // namespace fun

    constexpr inline auto atleast_nd = functor_t{unary_fmap_t<fun::atleast_nd_t>{}};
} // namespace nmtools::functional

#endif // NMTOOLS_ARRAY_FUNCTIONAL_ATLEAST_ND_HPP