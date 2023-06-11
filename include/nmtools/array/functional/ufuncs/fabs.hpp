#ifndef NMTOOLS_ARRAY_FUNCTIONAL_UFUNCS_FABS_HPP
#define NMTOOLS_ARRAY_FUNCTIONAL_UFUNCS_FABS_HPP

#include "nmtools/array/functional/functor.hpp"
#include "nmtools/array/view/ufuncs/fabs.hpp"

namespace nmtools::functional
{
    namespace fun
    {
        struct fabs_t
        {
            template <typename...args_t>
            constexpr auto operator()(const args_t&...args) const
            {
                return view::fabs(args...);
            }
        };
    }

    constexpr inline auto fabs = functor_t(unary_fmap_t<fun::fabs_t>{});

    template <typename...arrays_t>
    struct get_function_t<
        view::decorator_t<
            view::ufunc_t, view::fabs_t, arrays_t...
        >
    > {
        using view_type = view::decorator_t<
            view::ufunc_t, view::fabs_t, arrays_t...
        >;

        view_type view;

        constexpr auto operator()() const noexcept
        {
            return fabs;
        }
    };
} // namespace nmtools::functional


#endif // NMTOOLS_ARRAY_FUNCTIONAL_UFUNCS_FABS_HPP