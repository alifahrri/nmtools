#ifndef NMTOOLS_ARRAY_FUNCTIONAL_UFUNCS_LOG1P_HPP
#define NMTOOLS_ARRAY_FUNCTIONAL_UFUNCS_LOG1P_HPP

#include "nmtools/array/functional/functor.hpp"
#include "nmtools/array/view/ufuncs/log1p.hpp"

namespace nmtools::functional
{
    namespace fun
    {
        struct log1p_t
        {
            template <typename...args_t>
            constexpr auto operator()(const args_t&...args) const
            {
                return view::log1p(args...);
            }
        };
    }

    constexpr inline auto log1p = functor_t(unary_fmap_t<fun::log1p_t>{});

    template <typename...arrays_t>
    struct get_function_t<
        view::decorator_t<
            view::ufunc_t, view::log1p_t, arrays_t...
        >
    > {
        using view_type = view::decorator_t<
            view::ufunc_t, view::log1p_t, arrays_t...
        >;

        view_type view;

        constexpr auto operator()() const noexcept
        {
            return log1p;
        }
    };
} // namespace nmtools::functional


#endif // NMTOOLS_ARRAY_FUNCTIONAL_UFUNCS_LOG1P_HPP