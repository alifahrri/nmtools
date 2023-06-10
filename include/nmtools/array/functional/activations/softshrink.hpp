#ifndef NMTOOLS_ARRAY_FUNCTIONAL_ACTIVATIONS_SOFTSHRINK_HPP
#define NMTOOLS_ARRAY_FUNCTIONAL_ACTIVATIONS_SOFTSHRINK_HPP

#include "nmtools/array/functional/functor.hpp"
#include "nmtools/array/view/activations/softshrink.hpp"

namespace nmtools::functional
{
    namespace fun
    {
        struct softshrink_t
        {
            template <typename...args_t>
            constexpr auto operator()(const args_t&...args) const
            {
                return view::softshrink(args...);
            }
        };
    }
    constexpr inline auto softshrink = functor_t(unary_fmap_t<fun::softshrink_t>{});

    template <typename lambda_t, typename...arrays_t>
    struct get_function_t<
        view::decorator_t<
            view::ufunc_t, view::softshrink_t<lambda_t>, arrays_t...
        >
    > {
        using view_type = view::decorator_t<
            view::ufunc_t, view::softshrink_t<lambda_t>, arrays_t...
        >;

        view_type view;

        constexpr auto operator()() const noexcept
        {
            return softshrink[view.op.lambda];
        }
    };
} // namespace nmtools::functional


#endif // NMTOOLS_ARRAY_FUNCTIONAL_ACTIVATIONS_SOFTSHRINK_HPP