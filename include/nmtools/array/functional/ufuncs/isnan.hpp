#ifndef NMTOOLS_ARRAY_FUNCTIONAL_UFUNCS_ISNAN_HPP
#define NMTOOLS_ARRAY_FUNCTIONAL_UFUNCS_ISNAN_HPP

#include "nmtools/array/functional/functor.hpp"
#include "nmtools/array/view/ufuncs/isnan.hpp"

namespace nmtools::functional
{
    namespace fun
    {
        struct isnan_t
        {
            template <typename...args_t>
            constexpr auto operator()(const args_t&...args) const
            {
                return view::isnan(args...);
            }
        };
    }

    constexpr inline auto isnan = functor_t(unary_fmap_t<fun::isnan_t>{});

    template <typename...arrays_t>
    struct get_function_t<
        view::decorator_t<
            view::ufunc_t, view::isnan_t, arrays_t...
        >
    > {
        using view_type = view::decorator_t<
            view::ufunc_t, view::isnan_t, arrays_t...
        >;

        view_type view;

        constexpr auto operator()() const noexcept
        {
            return isnan;
        }
    };
} // namespace nmtools::functional


#endif // NMTOOLS_ARRAY_FUNCTIONAL_UFUNCS_ISNAN_HPP