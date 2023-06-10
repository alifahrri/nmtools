#ifndef NMTOOLS_ARRAY_FUNCTIONAL_UFUNCS_ARCCOS_HPP
#define NMTOOLS_ARRAY_FUNCTIONAL_UFUNCS_ARCCOS_HPP

#include "nmtools/array/functional/functor.hpp"
#include "nmtools/array/view/ufuncs/arccos.hpp"

namespace nmtools::functional
{
    namespace fun
    {
        struct arccos_t
        {
            template <typename...args_t>
            constexpr auto operator()(const args_t&...args) const
            {
                return view::arccos(args...);
            }
        };
    }

    constexpr inline auto arccos = functor_t(unary_fmap_t<fun::arccos_t>{});

    template <typename...arrays_t>
    struct get_function_t<
        view::decorator_t<
            view::ufunc_t, view::arccos_t, arrays_t...
        >
    > {
        using view_type = view::decorator_t<
            view::ufunc_t, view::arccos_t, arrays_t...
        >;

        view_type view;

        constexpr auto operator()() const noexcept
        {
            return arccos;
        }
    };
} // namespace nmtools::functional


#endif // NMTOOLS_ARRAY_FUNCTIONAL_UFUNCS_ARCCOS_HPP