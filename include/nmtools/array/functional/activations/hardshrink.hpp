#ifndef NMTOOLS_ARRAY_FUNCTIONAL_ACTIVATIONS_HARDSHRINK_HPP
#define NMTOOLS_ARRAY_FUNCTIONAL_ACTIVATIONS_HARDSHRINK_HPP

#include "nmtools/array/functional/functor.hpp"
#include "nmtools/array/view/activations/hardshrink.hpp"

namespace nmtools::functional
{
    namespace fun
    {
        struct hardshrink_t
        {
            template <typename...args_t>
            constexpr auto operator()(const args_t&...args) const
            {
                return view::hardshrink(args...);
            }
        };
    }

    constexpr inline auto hardshrink = functor_t(unary_fmap_t<fun::hardshrink_t>{});

    template <typename lambda_t, typename...arrays_t>
    struct get_function_t<
        view::decorator_t<
            view::ufunc_t, view::hardshrink_t<lambda_t>, arrays_t...
        >
    > {
        using view_type = view::decorator_t<
            view::ufunc_t, view::hardshrink_t<lambda_t>, arrays_t...
        >;

        view_type view;

        constexpr auto operator()() const noexcept
        {
            return hardshrink[view.op.lambda];
        }
    };
} // namespace nmtools::functional


#endif // NMTOOLS_ARRAY_FUNCTIONAL_ACTIVATIONS_HARDSHRINK_HPP