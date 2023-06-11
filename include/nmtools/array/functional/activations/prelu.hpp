#ifndef NMTOOLS_ARRAY_FUNCTIONAL_ACTIVATIONS_PRELU_HPP
#define NMTOOLS_ARRAY_FUNCTIONAL_ACTIVATIONS_PRELU_HPP

#include "nmtools/array/functional/functor.hpp"
#include "nmtools/array/view/activations/prelu.hpp"

namespace nmtools::functional
{
    namespace fun
    {
        struct prelu_t
        {
            template <typename...args_t>
            constexpr auto operator()(const args_t&...args) const
            {
                return view::prelu(args...);
            }
        };
    }
    constexpr inline auto prelu = functor_t(unary_fmap_t<fun::prelu_t>{});

    template <typename alpha_t, typename ...arrays_t>
    struct get_function_t<
        view::decorator_t<
            view::ufunc_t, view::prelu_t<alpha_t>, arrays_t...
        >
    > {
        using view_type = view::decorator_t<
            view::ufunc_t, view::prelu_t<alpha_t>, arrays_t...
        >;

        view_type view;

        constexpr auto operator()() const noexcept
        {
            return prelu[view.op.alpha];
        }
    };
} // namespace nmtools::functional


#endif // NMTOOLS_ARRAY_FUNCTIONAL_ACTIVATIONS_PRELU_HPP