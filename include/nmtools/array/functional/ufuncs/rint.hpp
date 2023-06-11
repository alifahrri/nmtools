#ifndef NMTOOLS_ARRAY_FUNCTIONAL_UFUNCS_RINT_HPP
#define NMTOOLS_ARRAY_FUNCTIONAL_UFUNCS_RINT_HPP

#include "nmtools/array/functional/functor.hpp"
#include "nmtools/array/view/ufuncs/rint.hpp"

namespace nmtools::functional
{
    namespace fun
    {
        struct rint_t
        {
            template <typename...args_t>
            constexpr auto operator()(const args_t&...args) const
            {
                return view::rint(args...);
            }
        };
    }

    constexpr inline auto rint = functor_t(unary_fmap_t<fun::rint_t>{});

    template <typename...arrays_t>
    struct get_function_t<
        view::decorator_t<
            view::ufunc_t, view::rint_t, arrays_t...
        >
    > {
        using view_type = view::decorator_t<
            view::ufunc_t, view::rint_t, arrays_t...
        >;

        view_type view;

        constexpr auto operator()() const noexcept
        {
            return rint;
        }
    };
} // namespace nmtools::functional


#endif // NMTOOLS_ARRAY_FUNCTIONAL_UFUNCS_RINT_HPP