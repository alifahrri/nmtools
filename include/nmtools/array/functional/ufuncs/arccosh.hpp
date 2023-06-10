#ifndef NMTOOLS_ARRAY_FUNCTIONAL_UFUNCS_ARCCOSH_HPP
#define NMTOOLS_ARRAY_FUNCTIONAL_UFUNCS_ARCCOSH_HPP

#include "nmtools/array/functional/functor.hpp"
#include "nmtools/array/view/ufuncs/arccosh.hpp"

namespace nmtools::functional
{
    namespace fun
    {
        struct arccosh_t
        {
            template <typename...args_t>
            constexpr auto operator()(const args_t&...args) const
            {
                return view::arccosh(args...);
            }
        };
    }

    constexpr inline auto arccosh = functor_t(unary_fmap_t<fun::arccosh_t>{});

    template <typename...arrays_t>
    struct get_function_t<
        view::decorator_t<
            view::ufunc_t, view::arccosh_t, arrays_t...
        >
    > {
        using view_type = view::decorator_t<
            view::ufunc_t, view::arccosh_t, arrays_t...
        >;

        view_type view;

        constexpr auto operator()() const noexcept
        {
            return arccosh;
        }
    };
} // namespace nmtools::functional


#endif // NMTOOLS_ARRAY_FUNCTIONAL_UFUNCS_ARCCOSH_HPP