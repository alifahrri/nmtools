#ifndef NMTOOLS_ARRAY_FUNCTIONAL_UFUNCS_SQRT_HPP
#define NMTOOLS_ARRAY_FUNCTIONAL_UFUNCS_SQRT_HPP

#include "nmtools/array/functional/functor.hpp"
#include "nmtools/array/view/ufuncs/sqrt.hpp"

namespace nmtools::functional
{
    namespace fun
    {
        struct sqrt_t
        {
            template <typename...args_t>
            constexpr auto operator()(const args_t&...args) const
            {
                return view::sqrt(args...);
            }
        };
    }

    constexpr inline auto sqrt = functor_t(unary_fmap_t<fun::sqrt_t>{});

    template <typename...arrays_t>
    struct get_function_t<
        view::decorator_t<
            view::ufunc_t, view::sqrt_t, arrays_t...
        >
    > {
        using view_type = view::decorator_t<
            view::ufunc_t, view::sqrt_t, arrays_t...
        >;

        view_type view;

        constexpr auto operator()() const noexcept
        {
            return sqrt;
        }
    };
} // namespace nmtools::functional


#endif // NMTOOLS_ARRAY_FUNCTIONAL_UFUNCS_SQRT_HPP