#ifndef NMTOOLS_ARRAY_FUNCTIONAL_STACK_HPP
#define NMTOOLS_ARRAY_FUNCTIONAL_STACK_HPP

#include "nmtools/array/functional/functor.hpp"
#include "nmtools/array/functional/indexing.hpp"
#include "nmtools/array/view/stack.hpp"

namespace nmtools::functional
{
    namespace fun
    {
        struct stack_t
        {
            template <typename...args_t>
            constexpr auto operator()(const args_t&...args) const
            {
                return view::stack(args...);
            }
        };
    }

    constexpr inline auto stack = functor_t{binary_fmap_t<fun::stack_t>{}};
} // namespace nmtools::functional

#endif // NMTOOLS_ARRAY_FUNCTIONAL_STACK_HPP