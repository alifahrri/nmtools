#ifndef NMTOOLS_ARRAY_FUNCTIONAL_SLIDING_WINDOW_HPP
#define NMTOOLS_ARRAY_FUNCTIONAL_SLIDING_WINDOW_HPP

#include "nmtools/array/view/sliding_window.hpp"
#include "nmtools/array/functional/indexing.hpp"

namespace nmtools::functional
{
    namespace fun
    {
        struct sliding_window
        {
            template <typename...args_t>
            constexpr auto operator()(const args_t&...args) const
            {
                return view::sliding_window(args...);
            }
        };
    } // namespace fun

    constexpr auto inline sliding_window = functor_t{unary_fmap_t<fun::sliding_window>{}};
} // namespace nmtools::functional

#endif // NMTOOLS_ARRAY_FUNCTIONAL_SLIDING_WINDOW_HPP