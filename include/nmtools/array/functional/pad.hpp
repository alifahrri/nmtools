#ifndef NMTOOLS_ARRAY_FUNCTIONAL_PAD_HPP
#define NMTOOLS_ARRAY_FUNCTIONAL_PAD_HPP

#include "nmtools/array/functional/functor.hpp"
#include "nmtools/array/view/pad.hpp"

namespace nmtools::functional
{
    namespace fun
    {
        struct pad_t
        {
            template <typename...args_t>
            constexpr auto operator()(const args_t&...args) const
            {
                return view::pad(args...);
            }
        };
    }

    constexpr inline auto pad = functor_t(unary_fmap_t<fun::pad_t>{});

    template <typename...args_t>
    struct get_function_t<
        view::decorator_t<
            view::pad_t, args_t...
        >
    > {
        using view_type = view::decorator_t<
            view::pad_t, args_t...
        >;

        view_type view;

        constexpr auto operator()() const noexcept
        {
            return pad[view.pad_width][view.pad_value];
        }
    };
} // namespace nmtools::functional

#endif // NMTOOLS_ARRAY_FUNCTIONAL_PAD_HPP