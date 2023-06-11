#ifndef NMTOOLS_ARRAY_FUNCTIONAL_UFUNCS_FLOOR_HPP
#define NMTOOLS_ARRAY_FUNCTIONAL_UFUNCS_FLOOR_HPP

#include "nmtools/array/functional/functor.hpp"
#include "nmtools/array/view/ufuncs/floor.hpp"

namespace nmtools::functional
{
    namespace fun
    {
        struct floor_t
        {
            template <typename...args_t>
            constexpr auto operator()(const args_t&...args) const
            {
                return view::floor(args...);
            }
        };
    }

    constexpr inline auto floor = functor_t(unary_fmap_t<fun::floor_t>{});

    template <typename...arrays_t>
    struct get_function_t<
        view::decorator_t<
            view::ufunc_t, view::floor_t, arrays_t...
        >
    > {
        using view_type = view::decorator_t<
            view::ufunc_t, view::floor_t, arrays_t...
        >;

        view_type view;

        constexpr auto operator()() const noexcept
        {
            return floor;
        }
    };
} // namespace nmtools::functional


#endif // NMTOOLS_ARRAY_FUNCTIONAL_UFUNCS_FLOOR_HPP