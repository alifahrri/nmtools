#ifndef NMTOOLS_ARRAY_FUNCTIONAL_ACTIVATIONS_TANHSHRINK_HPP
#define NMTOOLS_ARRAY_FUNCTIONAL_ACTIVATIONS_TANHSHRINK_HPP

#include "nmtools/array/functional/functor.hpp"
#include "nmtools/array/view/activations/tanhshrink.hpp"

namespace nmtools::functional
{
    namespace fun
    {
        struct tanhshrink_t
        {
            template <typename...args_t>
            constexpr auto operator()(const args_t&...args) const
            {
                return view::tanhshrink(args...);
            }
        };
    }

    constexpr inline auto tanhshrink = functor_t(unary_fmap_t<fun::tanhshrink_t>{});

    template <typename...arrays_t>
    struct get_function_t<
        view::decorator_t<
            view::ufunc_t, view::tanhshrink_t, arrays_t...
        >
    > {
        using view_type = view::decorator_t<
            view::ufunc_t, view::tanhshrink_t, arrays_t...
        >;

        view_type view;

        constexpr auto operator()() const
        {
            return tanhshrink;
        }
    };
} // namespace nmtools::functional


#endif // NMTOOLS_ARRAY_FUNCTIONAL_ACTIVATIONS_TANHSHRINK_HPP