#ifndef NMTOOLS_ARRAY_FUNCTIONAL_ACTIVATIONS_HARDSWISH_HPP
#define NMTOOLS_ARRAY_FUNCTIONAL_ACTIVATIONS_HARDSWISH_HPP

#include "nmtools/array/functional/functor.hpp"
#include "nmtools/array/view/activations/hardswish.hpp"

namespace nmtools::functional
{
    namespace fun
    {
        struct hardswish_t
        {
            template <typename...args_t>
            constexpr auto operator()(const args_t&...args) const
            {
                return view::hardswish(args...);
            }
        };
    }

    constexpr inline auto hardswish = functor_t(unary_fmap_t<fun::hardswish_t>{});

    template <typename...arrays_t>
    struct get_function_t<
        view::decorator_t<
            view::ufunc_t, view::hardswish_t, arrays_t...
        >
    > {
        using view_type = view::decorator_t<
            view::ufunc_t, view::hardswish_t, arrays_t...
        >;

        view_type view;

        constexpr auto operator()() const noexcept
        {
            return hardswish;
        }
    };
} // namespace nmtools::functional


#endif // NMTOOLS_ARRAY_FUNCTIONAL_ACTIVATIONS_HARDSWISH_HPP