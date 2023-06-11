#ifndef NMTOOLS_ARRAY_FUNCTIONAL_UFUNCS_LOG10_HPP
#define NMTOOLS_ARRAY_FUNCTIONAL_UFUNCS_LOG10_HPP

#include "nmtools/array/functional/functor.hpp"
#include "nmtools/array/view/ufuncs/log10.hpp"

namespace nmtools::functional
{
    namespace fun
    {
        struct log10_t
        {
            template <typename...args_t>
            constexpr auto operator()(const args_t&...args) const
            {
                return view::log10(args...);
            }
        };
    }

    constexpr inline auto log10 = functor_t(unary_fmap_t<fun::log10_t>{});

    template <typename...arrays_t>
    struct get_function_t<
        view::decorator_t<
            view::ufunc_t, view::log10_t, arrays_t...
        >
    > {
        using view_type = view::decorator_t<
            view::ufunc_t, view::log10_t, arrays_t...
        >;

        view_type view;

        constexpr auto operator()() const noexcept
        {
            return log10;
        }
    };
} // namespace nmtools::functional


#endif // NMTOOLS_ARRAY_FUNCTIONAL_UFUNCS_LOG10_HPP