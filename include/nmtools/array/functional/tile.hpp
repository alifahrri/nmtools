#ifndef NMTOOLS_ARRAY_FUNCTIONAL_TILE_HPP
#define NMTOOLS_ARRAY_FUNCTIONAL_TILE_HPP

#include "nmtools/array/functional/functor.hpp"
#include "nmtools/array/view/tile.hpp"

namespace nmtools::functional
{
    namespace fun
    {
        struct tile_t
        {
            template <typename...args_t>
            constexpr auto operator()(const args_t&...args) const
            {
                return view::tile(args...);
            }
        };
    }

    constexpr inline auto tile = functor_t(unary_fmap_t<fun::tile_t>{});

    template <typename...args_t>
    struct get_function_t<
        view::decorator_t<
            view::tile_t, args_t...
        >
    > {
        using view_type = view::decorator_t<
            view::tile_t, args_t...
        >;

        view_type view;

        constexpr auto operator()() const noexcept
        {
            return tile[view.reps];
        }
    };
} // namespace nmtools::functional

#endif // NMTOOLS_ARRAY_FUNCTIONAL_TILE_HPP