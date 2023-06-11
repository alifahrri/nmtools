#ifndef NMTOOLS_ARRAY_FUNCTIONAL_EXPAND_DIMS_HPP
#define NMTOOLS_ARRAY_FUNCTIONAL_EXPAND_DIMS_HPP

#include "nmtools/array/functional/functor.hpp"
#include "nmtools/array/view/expand_dims.hpp"

namespace nmtools::functional
{
    namespace fun
    {
        struct expand_dims_t
        {
            template <typename...args_t>
            constexpr auto operator()(const args_t&...args) const
            {
                return view::expand_dims(args...);
            }
        };
    }

    constexpr inline auto expand_dims = functor_t(unary_fmap_t<fun::expand_dims_t>{});

    template <typename...args_t>
    struct get_function_t<
        view::decorator_t<
            view::expand_dims_t, args_t...
        >
    > {
        using view_type = view::decorator_t<
            view::expand_dims_t, args_t...
        >;

        view_type view;

        constexpr auto operator()() const noexcept
        {
            return expand_dims[view.axis];
        }
    };
} // namespace nmtools::functional


#endif // NMTOOLS_ARRAY_FUNCTIONAL_EXPAND_DIMS_HPP