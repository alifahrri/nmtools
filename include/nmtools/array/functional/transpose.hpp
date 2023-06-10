#ifndef NMTOOLS_ARRAY_FUNCTIONAL_TRANSPOSE_HPP
#define NMTOOLS_ARRAY_FUNCTIONAL_TRANSPOSE_HPP

#include "nmtools/array/functional/functor.hpp"
#include "nmtools/array/view/transpose.hpp"

namespace nmtools::functional
{
    namespace fun
    {
        struct transpose_t
        {
            template <typename...args_t>
            constexpr auto operator()(const args_t&...args) const
            {
                return view::transpose(args...);
            }
        };
    }
    constexpr inline auto transpose = functor_t(unary_fmap_t<fun::transpose_t>{});

    template <typename...args_t>
    struct get_function_t<  
        view::decorator_t<
            view::transpose_t, args_t...
        >
    > {
        using view_type = view::decorator_t<
            view::transpose_t, args_t...
        >;

        view_type view;

        constexpr auto operator()() const noexcept
        {
            return transpose[view.axes];
        }
    };
} // namespace nmtools::functional

#endif // NMTOOLS_ARRAY_FUNCTIONAL_TRANSPOSE_HPP