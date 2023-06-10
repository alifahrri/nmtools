#ifndef NMTOOLS_ARRAY_FUNCTIONAL_UFUNCS_RECIPROCAL_HPP
#define NMTOOLS_ARRAY_FUNCTIONAL_UFUNCS_RECIPROCAL_HPP

#include "nmtools/array/functional/functor.hpp"
#include "nmtools/array/view/ufuncs/reciprocal.hpp"

namespace nmtools::functional
{
    namespace fun
    {
        struct reciprocal_t
        {
            template <typename...args_t>
            constexpr auto operator()(const args_t&...args) const
            {
                return view::reciprocal(args...);
            }
        };
    }

    constexpr inline auto reciprocal = functor_t(unary_fmap_t<fun::reciprocal_t>{});

    template <typename...arrays_t>
    struct get_function_t<
        view::decorator_t<
            view::ufunc_t, view::reciprocal_t, arrays_t...
        >
    > {
        using view_type = view::decorator_t<
            view::ufunc_t, view::reciprocal_t, arrays_t...
        >;

        view_type view;

        constexpr auto operator()() const noexcept
        {
            return reciprocal;
        }
    };
} // namespace nmtools::functional


#endif // NMTOOLS_ARRAY_FUNCTIONAL_UFUNCS_RECIPROCAL_HPP