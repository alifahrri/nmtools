#ifndef NMTOOLS_ARRAY_FUNCTIONAL_EXPAND_HPP
#define NMTOOLS_ARRAY_FUNCTIONAL_EXPAND_HPP

#include "nmtools/utils/to_string/to_string.hpp"
#include "nmtools/array/functional/functor.hpp"
#include "nmtools/array/view/expand.hpp"

namespace nmtools::functional::fun
{
    struct expand
    {
        template <typename...args_t>
        constexpr auto operator()(const args_t&...args) const
        {
            return view::expand(args...);
        }
    };
}

namespace nmtools::functional
{
    constexpr inline auto expand = functor_t{unary_fmap_t<fun::expand>{}};
} // namespace nmtools::functional

#endif // NMTOOLS_ARRAY_FUNCTIONAL_EXPAND_HPP