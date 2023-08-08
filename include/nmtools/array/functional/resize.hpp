#ifndef NMTOOLS_ARRAY_FUNCTIONAL_RESIZE_HPP
#define NMTOOLS_ARRAY_FUNCTIONAL_RESIZE_HPP

#include "nmtools/array/functional/functor.hpp"
#include "nmtools/array/view/resize.hpp"

namespace nmtools::functional
{
    namespace fun
    {
        struct resize_t
        {
            template <typename...args_t>
            constexpr auto operator()(const args_t&...args) const
            {
                return view::resize(args...);
            }
        };
    }

    constexpr inline auto resize = functor_t(unary_fmap_t<fun::resize_t>{});

    template <typename...args_t>
    struct get_function_t<
        view::decorator_t<
            view::resize_t, args_t...
        >
    > {
        using view_type = view::decorator_t<
            view::resize_t, args_t...
        >;

        view_type view;

        constexpr auto operator()() const noexcept
        {
            return resize[view.dst_shape];
        }
    };
} // namespace nmtools::functional

#endif // NMTOOLS_ARRAY_FUNCTIONAL_RESIZE_HPP