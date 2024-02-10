#ifndef NMTOOLS_ARRAY_FUNCTIONAL_UFUNCS_SQUARE_HPP
#define NMTOOLS_ARRAY_FUNCTIONAL_UFUNCS_SQUARE_HPP

#include "nmtools/array/functional/functor.hpp"
#include "nmtools/array/view/ufuncs/square.hpp"

namespace nmtools::functional
{
    namespace fun
    {
        struct square_t
        {
            template <typename...args_t>
            constexpr auto operator()(const args_t&...args) const
            {
                return view::square(args...);
            }
        };
    }

    constexpr inline auto square = functor_t(unary_fmap_t<fun::square_t>{});

    template <typename...arrays_t>
    struct get_function_t<
        view::decorator_t<
            view::ufunc_t, view::square_t, arrays_t...
        >
    > {
        using view_type = view::decorator_t<
            view::ufunc_t, view::square_t, arrays_t...
        >;

        view_type view;

        constexpr auto operator()() const noexcept
        {
            return square;
        }
    };
} // namespace nmtools::functional


#endif // NMTOOLS_ARRAY_FUNCTIONAL_UFUNCS_SQUARE_HPP