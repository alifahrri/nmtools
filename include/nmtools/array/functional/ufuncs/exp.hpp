#ifndef NMTOOLS_ARRAY_FUNCTIONAL_UFUNCS_EXP_HPP
#define NMTOOLS_ARRAY_FUNCTIONAL_UFUNCS_EXP_HPP

#include "nmtools/array/functional/functor.hpp"
#include "nmtools/array/view/ufuncs/exp.hpp"

namespace nmtools::functional
{
    namespace fun
    {
        struct exp_t
        {
            template <typename...args_t>
            constexpr auto operator()(const args_t&...args) const
            {
                return view::exp(args...);
            }
        };
    }

    constexpr inline auto exp = functor_t(unary_fmap_t<fun::exp_t>{});

    template <typename...arrays_t>
    struct get_function_t<
        view::decorator_t<
            view::ufunc_t, view::exp_t, arrays_t...
        >
    > {
        using view_type = view::decorator_t<
            view::ufunc_t, view::exp_t, arrays_t...
        >;

        view_type view;

        constexpr auto operator()() const noexcept
        {
            return exp;
        }
    };
} // namespace nmtools::functional


#endif // NMTOOLS_ARRAY_FUNCTIONAL_UFUNCS_EXP_HPP