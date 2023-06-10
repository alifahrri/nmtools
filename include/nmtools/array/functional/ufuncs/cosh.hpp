#ifndef NMTOOLS_ARRAY_FUNCTIONAL_UFUNCS_COSH_HPP
#define NMTOOLS_ARRAY_FUNCTIONAL_UFUNCS_COSH_HPP

#include "nmtools/array/functional/functor.hpp"
#include "nmtools/array/view/ufuncs/cosh.hpp"

namespace nmtools::functional
{
    namespace fun
    {
        struct cosh_t
        {
            template <typename...args_t>
            constexpr auto operator()(const args_t&...args) const
            {
                return view::cosh(args...);
            }
        };
    }

    constexpr inline auto cosh = functor_t(unary_fmap_t<fun::cosh_t>{});

    template <typename...arrays_t>
    struct get_function_t<
        view::decorator_t<
            view::ufunc_t, view::cosh_t, arrays_t...
        >
    > {
        using view_type = view::decorator_t<
            view::ufunc_t, view::cosh_t, arrays_t...
        >;

        view_type view;

        constexpr auto operator()() const noexcept
        {
            return cosh;
        }
    };
} // namespace nmtools::functional


#endif // NMTOOLS_ARRAY_FUNCTIONAL_UFUNCS_COSH_HPP