#ifndef NMTOOLS_ARRAY_FUNCTIONAL_UFUNCS_SIN_HPP
#define NMTOOLS_ARRAY_FUNCTIONAL_UFUNCS_SIN_HPP

#include "nmtools/array/functional/functor.hpp"
#include "nmtools/array/view/ufuncs/sin.hpp"

namespace nmtools::functional
{
    namespace fun
    {
        struct sin_t
        {
            template <typename...args_t>
            constexpr auto operator()(const args_t&...args) const
            {
                return view::sin(args...);
            }
        };
    }

    constexpr inline auto sin = functor_t(unary_fmap_t<fun::sin_t>{});

    template <typename...arrays_t>
    struct get_function_t<
        view::decorator_t<
            view::ufunc_t, view::sin_t, arrays_t...
        >
    > {
        using view_type = view::decorator_t<
            view::ufunc_t, view::sin_t, arrays_t...
        >;

        view_type view;

        constexpr auto operator()() const noexcept
        {
            return sin;
        }
    };
} // namespace nmtools::functional


#endif // NMTOOLS_ARRAY_FUNCTIONAL_UFUNCS_SIN_HPP