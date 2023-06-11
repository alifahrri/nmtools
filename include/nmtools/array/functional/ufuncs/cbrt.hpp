#ifndef NMTOOLS_ARRAY_FUNCTIONAL_UFUNCS_CBRT_HPP
#define NMTOOLS_ARRAY_FUNCTIONAL_UFUNCS_CBRT_HPP

#include "nmtools/array/functional/functor.hpp"
#include "nmtools/array/view/ufuncs/cbrt.hpp"

namespace nmtools::functional
{
    namespace fun
    {
        struct cbrt_t
        {
            template <typename...args_t>
            constexpr auto operator()(const args_t&...args) const
            {
                return view::cbrt(args...);
            }
        };
    }

    constexpr inline auto cbrt = functor_t(unary_fmap_t<fun::cbrt_t>{});

    template <typename...arrays_t>
    struct get_function_t<
        view::decorator_t<
            view::ufunc_t, view::cbrt_t, arrays_t...
        >
    > {
        using view_type = view::decorator_t<
            view::ufunc_t, view::cbrt_t, arrays_t...
        >;

        view_type view;

        constexpr auto operator()() const noexcept
        {
            return cbrt;
        }
    };
} // namespace nmtools::functional


#endif // NMTOOLS_ARRAY_FUNCTIONAL_UFUNCS_CBRT_HPP