#ifndef NMTOOLS_ARRAY_FUNCTIONAL_ACTIVATIONS_RELU_HPP
#define NMTOOLS_ARRAY_FUNCTIONAL_ACTIVATIONS_RELU_HPP

#include "nmtools/array/functional/functor.hpp"
#include "nmtools/array/view/activations/relu.hpp"

namespace nmtools::functional
{
    namespace fun
    {
        struct relu_t
        {
            template <typename...args_t>
            constexpr auto operator()(const args_t&...args) const
            {
                return view::relu(args...);
            }
        };
    } // namespace fun

    constexpr inline auto relu = functor_t(unary_fmap_t<fun::relu_t>{});

    template <typename...arrays_t>
    struct get_function_t<
        view::decorator_t<
            view::ufunc_t, view::relu_t, arrays_t...
        >
    > {
        using view_type = view::decorator_t<
            view::ufunc_t, view::relu_t, arrays_t...
        >;

        view_type view;

        constexpr auto operator()() const noexcept
        {
            return relu;
        }
    };
} // namespace nmtools::functional


#endif // NMTOOLS_ARRAY_FUNCTIONAL_ACTIVATIONS_RELU_HPP