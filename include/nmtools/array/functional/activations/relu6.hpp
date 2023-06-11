#ifndef NMTOOLS_ARRAY_FUNCTIONAL_ACTIVATIONS_RELU6_HPP
#define NMTOOLS_ARRAY_FUNCTIONAL_ACTIVATIONS_RELU6_HPP

#include "nmtools/array/functional/functor.hpp"
#include "nmtools/array/view/activations/relu6.hpp"

namespace nmtools::functional
{
    namespace fun
    {
        struct relu6_t
        {
            template <typename...args_t>
            constexpr auto operator()(const args_t&...args) const
            {
                return view::relu6(args...);
            }
        };
    } // namespace fun

    constexpr inline auto relu6 = functor_t(unary_fmap_t<fun::relu6_t>{});

    template <typename...arrays_t>
    struct get_function_t<
        view::decorator_t<
            view::ufunc_t, view::relu6_t, arrays_t...
        >
    > {
        using view_type = view::decorator_t<
            view::ufunc_t, view::relu6_t, arrays_t...
        >;

        view_type view;

        constexpr auto operator()() const noexcept
        {
            return relu6;
        }
    };
} // namespace nmtools::functional


#endif // NMTOOLS_ARRAY_FUNCTIONAL_ACTIVATIONS_RELU6_HPP