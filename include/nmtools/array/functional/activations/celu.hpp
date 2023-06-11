#ifndef NMTOOLS_ARRAY_FUNCTIONAL_ACTIVATIONS_CELU_HPP
#define NMTOOLS_ARRAY_FUNCTIONAL_ACTIVATIONS_CELU_HPP

#include "nmtools/array/functional/functor.hpp"
#include "nmtools/array/view/activations/celu.hpp"

namespace nmtools::functional
{
    namespace fun
    {
        struct celu_t
        {
            template <typename...args_t>
            constexpr auto operator()(const args_t&...args) const
            {
                return view::celu(args...);
            }
        };
    }
    constexpr inline auto celu = functor_t(unary_fmap_t<fun::celu_t>{});

    template <typename alpha_t, typename ...arrays_t>
    struct get_function_t<
        view::decorator_t<
            view::ufunc_t, view::celu_t<alpha_t>, arrays_t...
        >
    > {
        using view_type = view::decorator_t<
            view::ufunc_t, view::celu_t<alpha_t>, arrays_t...
        >;

        view_type view;

        constexpr auto operator()() const noexcept
        {
            return celu[view.op.alpha];
        }
    };
} // namespace nmtools::functional


#endif // NMTOOLS_ARRAY_FUNCTIONAL_ACTIVATIONS_CELU_HPP