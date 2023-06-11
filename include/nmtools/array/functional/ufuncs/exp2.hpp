#ifndef NMTOOLS_ARRAY_FUNCTIONAL_UFUNCS_EXP2_HPP
#define NMTOOLS_ARRAY_FUNCTIONAL_UFUNCS_EXP2_HPP

#include "nmtools/array/functional/functor.hpp"
#include "nmtools/array/view/ufuncs/exp2.hpp"

namespace nmtools::functional
{
    namespace fun
    {
        struct exp2_t
        {
            template <typename...args_t>
            constexpr auto operator()(const args_t&...args) const
            {
                return view::exp2(args...);
            }
        };
    }
    constexpr inline auto exp2 = functor_t(unary_fmap_t<fun::exp2_t>{});

    template <typename...arrays_t>
    struct get_function_t<
        view::decorator_t<
            view::ufunc_t, view::exp2_t, arrays_t...
        >
    > {
        using view_type = view::decorator_t<
            view::ufunc_t, view::exp2_t, arrays_t...
        >;

        view_type view;

        constexpr auto operator()() const noexcept
        {
            return exp2;
        }
    };
} // namespace nmtools::functional


#endif // NMTOOLS_ARRAY_FUNCTIONAL_UFUNCS_EXP2_HPP