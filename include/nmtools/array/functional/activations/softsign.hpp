#ifndef NMTOOLS_ARRAY_FUNCTIONAL_ACTIVATIONS_SOFTSIGN_HPP
#define NMTOOLS_ARRAY_FUNCTIONAL_ACTIVATIONS_SOFTSIGN_HPP

#include "nmtools/array/functional/functor.hpp"
#include "nmtools/array/view/activations/softsign.hpp"

namespace nmtools::functional
{
    namespace fun
    {
        struct softsign_t
        {
            template <typename...args_t>
            constexpr auto operator()(const args_t&...args) const
            {
                return view::softsign(args...);
            }
        };
    }

    constexpr inline auto softsign = functor_t(unary_fmap_t<fun::softsign_t>{});

    template <typename...arrays_t>
    struct get_function_t<
        view::decorator_t<
            view::ufunc_t, view::softsign_t, arrays_t...
        >
    > {
        using view_type = view::decorator_t<
            view::ufunc_t, view::softsign_t, arrays_t...
        >;

        view_type view;

        constexpr auto operator()() const noexcept
        {
            return softsign;
        }
    };
} // namespace nmtools::functional


#endif // NMTOOLS_ARRAY_FUNCTIONAL_ACTIVATIONS_SOFTSIGN_HPP