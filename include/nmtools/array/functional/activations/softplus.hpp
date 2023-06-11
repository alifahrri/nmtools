#ifndef NMTOOLS_ARRAY_FUNCTIONAL_ACTIVATIONS_SOFTPLUS_HPP
#define NMTOOLS_ARRAY_FUNCTIONAL_ACTIVATIONS_SOFTPLUS_HPP

#include "nmtools/array/functional/functor.hpp"
#include "nmtools/array/view/activations/softplus.hpp"

namespace nmtools::functional
{
    namespace fun
    {
        struct softplus_t
        {
            template <typename...args_t>
            constexpr auto operator()(const args_t&...args) const
            {
                return view::softplus(args...);
            }
        };
    }

    constexpr inline auto softplus = functor_t(unary_fmap_t<fun::softplus_t>{});

    template <typename beta_t, typename threshold_t, typename...arrays_t>
    struct get_function_t<
        view::decorator_t<
            view::ufunc_t, view::softplus_t<beta_t,threshold_t>, arrays_t...
        >
    > {
        using view_type = view::decorator_t<
            view::ufunc_t, view::softplus_t<beta_t,threshold_t>, arrays_t...
        >;

        view_type view;

        constexpr auto operator()() const noexcept
        {
            return softplus[view.op.beta][view.op.threshold];
        }
    };
} // namespace nmtools::functional


#endif // NMTOOLS_ARRAY_FUNCTIONAL_ACTIVATIONS_SOFTPLUS_HPP