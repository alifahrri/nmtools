#ifndef NMTOOLS_ARRAY_FUNCTIONAL_ZEROS_HPP
#define NMTOOLS_ARRAY_FUNCTIONAL_ZEROS_HPP

#include "nmtools/array/functional/functor.hpp"
#include "nmtools/array/functional/full.hpp"
#include "nmtools/array/view/zeros.hpp"

namespace nmtools::functional
{
    namespace fun 
    {
        struct zeros_t
        {
            template <typename...args_t>
            constexpr auto operator()(const args_t&...args) const
            {
                return view::zeros(args...);
            }
        };
    }

    constexpr inline auto zeros = functor_t(nullary_fmap_t<fun::zeros_t>{});
} // namespace nmtools::functional

#endif // NMTOOLS_ARRAY_FUNCTIONAL_ZEROS_HPP