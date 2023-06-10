#ifndef NMTOOLS_ARRAY_FUNCTIONAL_UFUNCS_CEIL_HPP
#define NMTOOLS_ARRAY_FUNCTIONAL_UFUNCS_CEIL_HPP

#include "nmtools/array/functional/functor.hpp"
#include "nmtools/array/view/ufuncs/ceil.hpp"

namespace nmtools::functional
{
    namespace fun
    {
        struct ceil_t
        {
            template <typename...args_t>
            constexpr auto operator()(const args_t&...args) const
            {
                return view::ceil(args...);
            }
        };
    }

    constexpr inline auto ceil = functor_t(unary_fmap_t<fun::ceil_t>{});

    template <typename...arrays_t>
    struct get_function_t<
        view::decorator_t<
            view::ufunc_t, view::ceil_t, arrays_t...
        >
    > {
        using view_type = view::decorator_t<
            view::ufunc_t, view::ceil_t, arrays_t...
        >;

        view_type view;

        constexpr auto operator()() const noexcept
        {
            return ceil;
        }
    };
} // namespace nmtools::functional


#endif // NMTOOLS_ARRAY_FUNCTIONAL_UFUNCS_CEIL_HPP