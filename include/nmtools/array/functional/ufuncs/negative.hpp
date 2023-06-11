#ifndef NMTOOLS_ARRAY_FUNCTIONAL_UFUNCS_NEGATIVE_HPP
#define NMTOOLS_ARRAY_FUNCTIONAL_UFUNCS_NEGATIVE_HPP

#include "nmtools/array/functional/functor.hpp"
#include "nmtools/array/view/ufuncs/negative.hpp"

namespace nmtools::functional
{
    namespace fun
    {
        struct negative_t
        {
            template <typename...args_t>
            constexpr auto operator()(const args_t&...args) const
            {
                return view::negative(args...);
            }
        };
    }

    constexpr inline auto negative = functor_t(unary_fmap_t<fun::negative_t>{});

    template <typename...arrays_t>
    struct get_function_t<
        view::decorator_t<
            view::ufunc_t, view::negative_t, arrays_t...
        >
    > {
        using view_type = view::decorator_t<
            view::ufunc_t, view::negative_t, arrays_t...
        >;

        view_type view;

        constexpr auto operator()() const noexcept
        {
            return negative;
        }
    };
} // namespace nmtools::functional


#endif // NMTOOLS_ARRAY_FUNCTIONAL_UFUNCS_NEGATIVE_HPP