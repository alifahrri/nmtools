#ifndef NMTOOLS_ARRAY_FUNCTIONAL_UFUNCS_ARCSIN_HPP
#define NMTOOLS_ARRAY_FUNCTIONAL_UFUNCS_ARCSIN_HPP

#include "nmtools/array/functional/functor.hpp"
#include "nmtools/array/view/ufuncs/arcsin.hpp"

namespace nmtools::functional
{
    namespace fun
    {
        struct arcsin_t
        {
            template <typename...args_t>
            constexpr auto operator()(const args_t&...args) const
            {
                return view::arcsin(args...);
            }
        };
    }

    constexpr inline auto arcsin = functor_t(unary_fmap_t<fun::arcsin_t>{});

    template <typename...arrays_t>
    struct get_function_t<
        view::decorator_t<
            view::ufunc_t, view::arcsin_t, arrays_t...
        >
    > {
        using view_type = view::decorator_t<
            view::ufunc_t, view::arcsin_t, arrays_t...
        >;

        view_type view;

        constexpr auto operator()() const noexcept
        {
            return arcsin;
        }
    };
} // namespace nmtools::functional


#endif // NMTOOLS_ARRAY_FUNCTIONAL_UFUNCS_ARCSIN_HPP