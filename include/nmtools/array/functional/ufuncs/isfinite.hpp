#ifndef NMTOOLS_ARRAY_FUNCTIONAL_UFUNCS_ISFINITE_HPP
#define NMTOOLS_ARRAY_FUNCTIONAL_UFUNCS_ISFINITE_HPP

#include "nmtools/array/functional/functor.hpp"
#include "nmtools/array/view/ufuncs/isfinite.hpp"

namespace nmtools::functional
{
    namespace fun
    {
        struct isfinite_t
        {
            template <typename...args_t>
            constexpr auto operator()(const args_t&...args) const
            {
                return view::isfinite(args...);
            }
        };
    }

    constexpr inline auto isfinite = functor_t(unary_fmap_t<fun::isfinite_t>{});

    template <typename...arrays_t>
    struct get_function_t<
        view::decorator_t<
            view::ufunc_t, view::isfinite_t, arrays_t...
        >
    > {
        using view_type = view::decorator_t<
            view::ufunc_t, view::isfinite_t, arrays_t...
        >;

        view_type view;

        constexpr auto operator()() const noexcept
        {
            return isfinite;
        }
    };
} // namespace nmtools::functional


#endif // NMTOOLS_ARRAY_FUNCTIONAL_UFUNCS_ISFINITE_HPP