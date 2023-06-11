#ifndef NMTOOLS_ARRAY_FUNCTIONAL_ACTIVATIONS_SELU_HPP
#define NMTOOLS_ARRAY_FUNCTIONAL_ACTIVATIONS_SELU_HPP

#include "nmtools/array/functional/functor.hpp"
#include "nmtools/array/view/activations/selu.hpp"

namespace nmtools::functional
{
    namespace fun
    {
        struct selu_t
        {
            template <typename...args_t>
            constexpr auto operator()(const args_t&...args) const
            {
                return view::selu(args...);
            }
        };
    }
    constexpr inline auto selu = functor_t(unary_fmap_t<fun::selu_t>{});

    template <typename...arrays_t>
    struct get_function_t<
        view::decorator_t<
            view::ufunc_t, view::selu_t, arrays_t...
        >
    > {
        using view_type = view::decorator_t<
            view::ufunc_t, view::selu_t, arrays_t...
        >;

        view_type view;

        constexpr auto operator()() const noexcept
        {
            return selu;
        }
    };
} // namespace nmtools::functional


#endif // NMTOOLS_ARRAY_FUNCTIONAL_ACTIVATIONS_SELU_HPP