#ifndef NMTOOLS_ARRAY_FUNCTIONAL_ACTIVATIONS_ELU_HPP
#define NMTOOLS_ARRAY_FUNCTIONAL_ACTIVATIONS_ELU_HPP

#include "nmtools/array/functional/functor.hpp"
#include "nmtools/array/view/activations/elu.hpp"

namespace nmtools::functional
{
    namespace fun
    {
        struct elu_t
        {
            template <typename ...args_t>
            constexpr auto operator()(const args_t&...args) const
            {
                return view::elu(args...);
            }
        };
    }

    constexpr inline auto elu = functor_t(unary_fmap_t<fun::elu_t>{});

    template <typename alpha_t, typename...arrays_t>
    struct get_function_t<
        view::decorator_t<
            view::ufunc_t, view::elu_t<alpha_t>, arrays_t...
        >
    > {
        using view_type = view::decorator_t<
            view::ufunc_t, view::elu_t<alpha_t>, arrays_t...
        >;

        view_type view;

        constexpr auto operator()() const noexcept
        {
            return elu[view.op.alpha];
        }
    };
} // namespace nmtools::functional


#endif // NMTOOLS_ARRAY_FUNCTIONAL_ACTIVATIONS_ELU_HPP