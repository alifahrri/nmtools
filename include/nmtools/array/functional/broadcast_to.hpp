#ifndef NMTOOLS_ARRAY_FUNCTIONAL_BROADCAST_TO_HPP
#define NMTOOLS_ARRAY_FUNCTIONAL_BROADCAST_TO_HPP

#include "nmtools/array/functional/functor.hpp"
#include "nmtools/array/view/broadcast_to.hpp"

namespace nmtools::functional
{
    namespace fun
    {
        struct broadcast_to_t
        {
            template <typename...args_t>
            constexpr auto operator()(const args_t&...args) const
            {
                return view::broadcast_to(args...);
            }
        };
    } // namespace fun

    constexpr inline auto broadcast_to = functor_t(unary_fmap_t<fun::broadcast_to_t>{});

    template <typename array_t, typename shape_t, typename origin_axes_t, typename bsize_t>
    struct get_function_t<
        view::decorator_t<
            view::broadcast_to_t, array_t, shape_t, origin_axes_t, bsize_t
        >
    > {
        using view_type = view::decorator_t< view::broadcast_to_t, array_t, shape_t, origin_axes_t, bsize_t >;

        view_type view;

        constexpr auto operator()() const noexcept
        {
            return broadcast_to [view.shape_] [view.broadcast_size];
        }
    };
} // namespace nmtools::functional

#endif // NMTOOLS_ARRAY_FUNCTIONAL_BROADCAST_TO_HPP