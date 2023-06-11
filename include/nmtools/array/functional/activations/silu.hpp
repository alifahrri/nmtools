#ifndef NMTOOLS_ARRAY_FUNCTIONAL_ACTIVATIONS_SILU_HPP
#define NMTOOLS_ARRAY_FUNCTIONAL_ACTIVATIONS_SILU_HPP

#include "nmtools/array/functional/functor.hpp"
#include "nmtools/array/view/activations/silu.hpp"

namespace nmtools::functional
{
    namespace fun
    {
        struct silu_t
        {
            template <typename...args_t>
            constexpr auto operator()(const args_t&...args) const
            {
                return view::silu(args...);
            }
        };
    }

    constexpr inline auto silu = functor_t(unary_fmap_t<fun::silu_t>{});

    template <typename...arrays_t>
    struct get_function_t<
        view::decorator_t<
            view::ufunc_t, view::silu_t, arrays_t...
        >
    > {
        using view_type = view::decorator_t<
            view::ufunc_t, view::silu_t, arrays_t...
        >;

        view_type view;

        constexpr auto operator()() const noexcept
        {
            return silu;
        }
    };
} // namespace nmtools::functional


#endif // NMTOOLS_ARRAY_FUNCTIONAL_ACTIVATIONS_SILU_HPP