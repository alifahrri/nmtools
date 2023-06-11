#ifndef NMTOOLS_ARRAY_FUNCTIONAL_ACTIVATIONS_LOG_SIGMOID_HPP
#define NMTOOLS_ARRAY_FUNCTIONAL_ACTIVATIONS_LOG_SIGMOID_HPP

#include "nmtools/array/functional/functor.hpp"
#include "nmtools/array/view/activations/log_sigmoid.hpp"

namespace nmtools::functional
{
    namespace fun
    {
        struct log_sigmoid_t
        {
            template <typename...args_t>
            constexpr auto operator()(const args_t&...args) const
            {
                return view::log_sigmoid(args...);
            }
        };
    }
    constexpr inline auto log_sigmoid = functor_t(unary_fmap_t<fun::log_sigmoid_t>{});

    template <typename...arrays_t>
    struct get_function_t<
        view::decorator_t<
            view::ufunc_t, view::log_sigmoid_t, arrays_t...
        >
    > {
        using view_type = view::decorator_t<
            view::ufunc_t, view::log_sigmoid_t, arrays_t...
        >;

        view_type view;

        constexpr auto operator()() const
        {
            return log_sigmoid;
        }
    };
} // namespace nmtools::functional


#endif // NMTOOLS_ARRAY_FUNCTIONAL_ACTIVATIONS_LOG_SIGMOID_HPP