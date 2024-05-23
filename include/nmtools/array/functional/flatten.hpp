#ifndef NMTOOLS_ARRAY_FUNCTIONAL_FLATTEN_HPP
#define NMTOOLS_ARRAY_FUNCTIONAL_FLATTEN_HPP

#include "nmtools/array/functional/functor.hpp"
#include "nmtools/array/functional/indexing.hpp"
#include "nmtools/array/view/flatten.hpp"

namespace nmtools::functional
{
    namespace fun 
    {
        struct flatten_t
        {
            template <typename...args_t>
            constexpr auto operator()(const args_t&...args) const
            {
                return view::flatten(args...);
            }
        };
    }

    constexpr inline auto flatten = functor_t{unary_fmap_t<fun::flatten_t>{}};
} // namespace nmtools::functional

#endif // NMTOOLS_ARRAY_FUNCTIONAL_FLATTEN_HPP