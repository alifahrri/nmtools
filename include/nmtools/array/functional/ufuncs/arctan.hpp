#ifndef NMTOOLS_ARRAY_FUNCTIONAL_UFUNCS_ARCTAN_HPP
#define NMTOOLS_ARRAY_FUNCTIONAL_UFUNCS_ARCTAN_HPP

#include "nmtools/array/functional/functor.hpp"
#include "nmtools/array/view/ufuncs/arctan.hpp"

namespace nmtools::functional
{
    namespace fun
    {
        struct arctan_t
        {
            template <typename...args_t>
            constexpr auto operator()(const args_t&...args) const
            {
                return view::arctan(args...);
            }
        };
    }

    constexpr inline auto arctan = functor_t(unary_fmap_t<fun::arctan_t>{});

    template <typename...arrays_t>
    struct get_function_t<
        view::decorator_t<
            view::ufunc_t, view::arctan_t, arrays_t...
        >
    > {
        using view_type = view::decorator_t<
            view::ufunc_t, view::arctan_t, arrays_t...
        >;

        view_type view;

        constexpr auto operator()() const noexcept
        {
            return arctan;
        }
    };
} // namespace nmtools::functional


#endif // NMTOOLS_ARRAY_FUNCTIONAL_UFUNCS_ARCTAN_HPP