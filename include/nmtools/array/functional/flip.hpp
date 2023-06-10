#ifndef NMTOOLS_ARRAY_FUNCTIONAL_FLIP_HPP
#define NMTOOLS_ARRAY_FUNCTIONAL_FLIP_HPP

#include "nmtools/array/functional/functor.hpp"
#include "nmtools/array/view/flip.hpp"

namespace nmtools::functional
{
    namespace fun
    {
        struct flip_t
        {
            template <typename...args_t>
            constexpr auto operator()(const args_t&...args) const
            {
                return view::flip(args...);
            }
        };
    }

    constexpr inline auto flip = functor_t(unary_fmap_t<fun::flip_t>{});

    template <typename...args_t>
    struct get_function_t<
        view::decorator_t<
            view::flip_t, args_t...
        >
    > {
        using view_type = view::decorator_t<
            view::flip_t, args_t...
        >;

        view_type view;

        constexpr auto operator()() const noexcept
        {
            return flip[view.axes];
        }
    };
} // namespace nmtools::functional


#endif // NMTOOLS_ARRAY_FUNCTIONAL_FLIP_HPP