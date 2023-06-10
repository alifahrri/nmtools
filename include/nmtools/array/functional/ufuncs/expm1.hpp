#ifndef NMTOOLS_ARRAY_FUNCTIONAL_UFUNCS_EXPM1_HPP
#define NMTOOLS_ARRAY_FUNCTIONAL_UFUNCS_EXPM1_HPP

#include "nmtools/array/functional/functor.hpp"
#include "nmtools/array/view/ufuncs/expm1.hpp"

namespace nmtools::functional
{
    namespace fun
    {
        struct expm1_t
        {
            template <typename...args_t>
            constexpr auto operator()(const args_t&...args) const
            {
                return view::expm1(args...);
            }
        };
    }
    constexpr inline auto expm1 = functor_t(unary_fmap_t<fun::expm1_t>{});

    template <typename...arrays_t>
    struct get_function_t<
        view::decorator_t<
            view::ufunc_t, view::expm1_t, arrays_t...
        >
    > {
        using view_type = view::decorator_t<
            view::ufunc_t, view::expm1_t, arrays_t...
        >;

        view_type view;

        constexpr auto operator()() const noexcept
        {
            return expm1;
        }
    };
} // namespace nmtools::functional


#endif // NMTOOLS_ARRAY_FUNCTIONAL_UFUNCS_EXPM1_HPP