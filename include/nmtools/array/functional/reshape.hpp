#ifndef NMTOOLS_ARRAY_FUNCTIONAL_RESHAPE_HPP
#define NMTOOLS_ARRAY_FUNCTIONAL_RESHAPE_HPP

#include "nmtools/array/functional/functor.hpp"
#include "nmtools/array/functional/indexing.hpp"
#include "nmtools/array/view/reshape.hpp"

namespace nmtools::functional
{
    namespace fun
    {
        struct reshape_t
        {
            template <typename...args_t>
            constexpr auto operator()(const args_t&...args) const
            {
                return view::reshape(args...);
            }
        };
    }

    constexpr inline auto reshape = functor_t{unary_fmap_t<fun::reshape_t>{}};
} // namespace nmtools::functional

#endif //NMTOOLS_ARRAY_FUNCTIONAL_RESHAPE_HPP