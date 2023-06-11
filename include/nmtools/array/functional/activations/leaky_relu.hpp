#ifndef NMTOOLS_ARRAY_FUNCTIONAL_ACTIVATIONS_LEAKY_RELU_HPP
#define NMTOOLS_ARRAY_FUNCTIONAL_ACTIVATIONS_LEAKY_RELU_HPP

#include "nmtools/array/functional/functor.hpp"
#include "nmtools/array/view/activations/leaky_relu.hpp"

namespace nmtools::functional
{
    namespace fun
    {
        struct leaky_relu_t
        {
            template <typename...args_t>
            constexpr auto operator()(const args_t&...args) const
            {
                return view::leaky_relu(args...);
            }
        };
    }
    constexpr inline auto leaky_relu = functor_t(unary_fmap_t<fun::leaky_relu_t>{});

    template <typename negative_slope_t, typename...arrays_t>
    struct get_function_t<
        view::decorator_t<
            view::ufunc_t, view::leaky_relu_t<negative_slope_t>, arrays_t...
        >
    > {
        using view_type = view::decorator_t<
            view::ufunc_t, view::leaky_relu_t<negative_slope_t>, arrays_t...
        >;

        view_type view;

        constexpr auto operator()() const noexcept
        {
            return leaky_relu[view.op.negative_slope];
        }
    };
} // namespace nmtools::functional


#endif // NMTOOLS_ARRAY_FUNCTIONAL_ACTIVATIONS_LEAKY_RELU_HPP