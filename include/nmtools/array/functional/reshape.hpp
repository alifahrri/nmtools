#ifndef NMTOOLS_ARRAY_FUNCTIONAL_RESHAPE_HPP
#define NMTOOLS_ARRAY_FUNCTIONAL_RESHAPE_HPP

#include "nmtools/array/functional/functor.hpp"
#include "nmtools/array/view/reshape.hpp"

namespace nmtools::functional
{
    namespace fun
    {
        struct reshape_t
        {
            template <typename...args_t>
            constexpr auto operator()(const args_t&...args) const
            {
                return view::reshape(args...);
            }
        };
    }

    constexpr inline auto reshape = functor_t(unary_fmap_t<fun::reshape_t>{});

    template <typename...args_t>
    struct get_function_t<
        view::decorator_t<
            view::reshape_t, args_t...
        >
    > {
        using view_type = view::decorator_t<
            view::reshape_t, args_t...
        >;

        view_type view;

        constexpr auto operator()() const noexcept
        {
            return reshape[view.new_shape];
        }
    };
} // namespace nmtools::functional

#endif //NMTOOLS_ARRAY_FUNCTIONAL_RESHAPE_HPP