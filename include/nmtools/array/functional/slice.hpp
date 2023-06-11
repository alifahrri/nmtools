#ifndef NMTOOLS_ARRAY_FUNCTIONAL_SLICE_HPP
#define NMTOOLS_ARRAY_FUNCTIONAL_SLICE_HPP

#include "nmtools/array/functional/functor.hpp"
#include "nmtools/array/view/slice.hpp"

namespace nmtools::functional
{
    namespace fun
    {
        struct slice_t
        {
            template <typename...args_t>
            constexpr auto operator()(const args_t&...args) const
            {
                return view::slice(args...);
            }
        };

        struct apply_slice_t
        {
            template <typename...args_t>
            constexpr auto operator()(const args_t&...args) const
            {
                return view::apply_slice(args...);
            }
        };
    }

    constexpr inline auto slice = functor_t(unary_fmap_t<fun::slice_t>{});

    constexpr inline auto apply_slice = functor_t(unary_fmap_t<fun::apply_slice_t>{});

    template <typename...args_t>
    struct get_function_t<
        view::decorator_t<
            view::slice_t, args_t...
        >
    > {
        using view_type = view::decorator_t<
            view::slice_t, args_t...
        >;

        view_type view;

        constexpr auto operator()() const noexcept
        {
            return apply_slice[view.slices];
        }
    };
} // namespace nmtools::functional

#endif // NMTOOLS_ARRAY_FUNCTIONAL_SLICE_HPP