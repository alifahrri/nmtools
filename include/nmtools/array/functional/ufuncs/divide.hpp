#ifndef NMTOOLS_ARRAY_FUNCTIONAL_UFUNCS_DIVIDE_HPP
#define NMTOOLS_ARRAY_FUNCTIONAL_UFUNCS_DIVIDE_HPP

#include "nmtools/array/functional/functor.hpp"
#include "nmtools/array/view/ufuncs/divide.hpp"

namespace nmtools::functional
{
    namespace fun
    {
        struct divide_t
        {
            template <typename...args_t>
            constexpr auto operator()(const args_t&...args) const
            {
                return view::divide(args...);
            }
        };
    }

    constexpr inline auto divide = functor_t(binary_fmap_t<fun::divide_t>{});

    template <typename...arrays_t>
    struct get_function_t<
        view::decorator_t<
            view::ufunc_t, view::divide_t, arrays_t...
        >
    > {
        using view_type = view::decorator_t<
            view::ufunc_t, view::divide_t, arrays_t...
        >;
        using array_type = typename view_type::array_type;
        using lhs_array_type = meta::at_t<array_type,0>;
        using rhs_array_type = meta::at_t<array_type,1>;

        view_type view;

        constexpr auto operator()() const noexcept
        {
            if constexpr (meta::is_view_v<lhs_array_type> && !meta::is_same_view_v<view::broadcast_to_t,lhs_array_type>) {
                return divide * get_function(nmtools::get<0>(view.array));
            } else {
                return divide;
            }
        }
    };
} // namespace nmtools::functional

#endif // NMTOOLS_ARRAY_FUNCTIONAL_UFUNCS_DIVIDE_HPP