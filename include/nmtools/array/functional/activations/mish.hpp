#ifndef NMTOOLS_ARRAY_FUNCTIONAL_ACTIVATIONS_MISH_HPP
#define NMTOOLS_ARRAY_FUNCTIONAL_ACTIVATIONS_MISH_HPP

#include "nmtools/array/functional/functor.hpp"
#include "nmtools/array/view/activations/mish.hpp"

namespace nmtools::functional
{
    namespace fun
    {
        struct mish_t
        {
            template <typename...args_t>
            constexpr auto operator()(const args_t&...args) const
            {
                return view::mish(args...);
            }
        };
    }

    constexpr inline auto mish = functor_t(unary_fmap_t<fun::mish_t>{});

    template <typename...arrays_t>
    struct get_function_t<
        view::decorator_t<
            view::ufunc_t, view::mish_t, arrays_t...
        >
    > {
        using view_type = view::decorator_t<
            view::ufunc_t, view::mish_t, arrays_t...
        >;

        view_type view;

        constexpr auto operator()() const noexcept
        {
            return mish;
        }
    };
} // namespace nmtools::functional


#endif // NMTOOLS_ARRAY_FUNCTIONAL_ACTIVATIONS_MISH_HPP