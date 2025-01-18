#ifndef NMTOOLS_ARRAY_FUNCTIONAL_ONES_HPP
#define NMTOOLS_ARRAY_FUNCTIONAL_ONES_HPP

#include "nmtools/array/core/functor.hpp"
#include "nmtools/array/functional/full.hpp"
#include "nmtools/array/view/ones.hpp"

namespace nmtools::functional
{
    namespace fun 
    {
        struct ones_t
        {
            template <typename...args_t>
            constexpr auto operator()(const args_t&...args) const
            {
                return view::ones(args...);
            }
        };
    }

    constexpr inline auto ones = functor_t{nullary_fmap_t<fun::ones_t>{}};
} // namespace nmtools::functional

#endif // NMTOOLS_ARRAY_FUNCTIONAL_ONES_HPP