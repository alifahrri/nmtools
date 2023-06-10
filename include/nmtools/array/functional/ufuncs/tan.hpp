#ifndef NMTOOLS_ARRAY_FUNCTIONAL_UFUNCS_TAN_HPP
#define NMTOOLS_ARRAY_FUNCTIONAL_UFUNCS_TAN_HPP

#include "nmtools/array/functional/functor.hpp"
#include "nmtools/array/view/ufuncs/tan.hpp"

namespace nmtools::functional
{
    namespace fun
    {
        struct tan_t
        {
            template <typename...args_t>
            constexpr auto operator()(const args_t&...args) const
            {
                return view::tan(args...);
            }
        };
    }

    constexpr inline auto tan = functor_t(unary_fmap_t<fun::tan_t>{});

    template <typename...arrays_t>
    struct get_function_t<
        view::decorator_t<
            view::ufunc_t, view::tan_t, arrays_t...
        >
    > {
        using view_type = view::decorator_t<
            view::ufunc_t, view::tan_t, arrays_t...
        >;

        view_type view;

        constexpr auto operator()() const noexcept
        {
            return tan;
        }
    };
} // namespace nmtools::functional


#endif // NMTOOLS_ARRAY_FUNCTIONAL_UFUNCS_TAN_HPP