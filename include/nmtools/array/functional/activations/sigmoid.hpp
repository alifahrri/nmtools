#ifndef NMTOOLS_ARRAY_FUNCTIONAL_ACTIVATIONS_SIGMOID_HPP
#define NMTOOLS_ARRAY_FUNCTIONAL_ACTIVATIONS_SIGMOID_HPP

#include "nmtools/array/functional/functor.hpp"
#include "nmtools/array/view/activations/sigmoid.hpp"

namespace nmtools::functional
{
    namespace fun
    {
        struct sigmoid_t
        {
            template <typename...args_t>
            constexpr auto operator()(const args_t&...args) const
            {
                return view::sigmoid(args...);
            }
        };
    }
    constexpr inline auto sigmoid = functor_t(unary_fmap_t<fun::sigmoid_t>{});

    template <typename...arrays_t>
    struct get_function_t<
        view::decorator_t<
            view::ufunc_t, view::sigmoid_t, arrays_t...
        >
    > {
        using view_type = view::decorator_t<
            view::ufunc_t, view::sigmoid_t, arrays_t...
        >;

        view_type view;

        constexpr auto operator()() const noexcept
        {
            return sigmoid;
        }
    };
} // namespace nmtools::functional


#endif // NMTOOLS_ARRAY_FUNCTIONAL_ACTIVATIONS_SIGMOID_HPP