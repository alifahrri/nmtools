#ifndef NMTOOLS_ARRAY_FUNCTIONAL_POOLING_HPP
#define NMTOOLS_ARRAY_FUNCTIONAL_POOLING_HPP

#include "nmtools/array/functional/functor.hpp"
#include "nmtools/array/view/pooling.hpp"

namespace nmtools::functional
{
    namespace fun
    {
        struct avg_pool2d_t
        {
            template <typename...args_t>
            constexpr auto operator()(const args_t&...args) const
            {
                return view::avg_pool2d(args...);
            }
        };

        struct max_pool2d_t
        {
            template <typename...args_t>
            constexpr auto operator()(const args_t&...args) const
            {
                return view::max_pool2d(args...);
            }
        };
    }
    constexpr inline auto avg_pool2d = functor_t(unary_fmap_t<fun::avg_pool2d_t>{});

    constexpr inline auto max_pool2d = functor_t(unary_fmap_t<fun::max_pool2d_t>{});

    template <typename reducer_t, typename...args_t>
    struct get_function_t<
        view::decorator_t<
            view::pool2d_t, reducer_t, args_t...
        >
    >
    {
        using view_type = view::decorator_t<
            view::pool2d_t, reducer_t, args_t...
        >;

        view_type view;

        constexpr auto operator()() const noexcept
        {
            if constexpr (meta::is_same_v<reducer_t, view::max_reducer_t>) {
                return max_pool2d[view.kernel_size][view.stride][view.ceil_mode];
            } else {
                return avg_pool2d[view.kernel_size][view.stride][view.ceil_mode];
            }
        }
    };

} // namespace nmtools::functional

#endif // NMTOOLS_ARRAY_FUNCTIONAL_POOLING_HPP