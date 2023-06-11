#ifndef NMTOOLS_ARRAY_FUNCTIONAL_UFUNCS_ARCSINH_HPP
#define NMTOOLS_ARRAY_FUNCTIONAL_UFUNCS_ARCSINH_HPP

#include "nmtools/array/functional/functor.hpp"
#include "nmtools/array/view/ufuncs/arcsinh.hpp"

namespace nmtools::functional
{
    namespace fun
    {
        struct arcsinh_t
        {
            template <typename...args_t>
            constexpr auto operator()(const args_t&...args) const
            {
                return view::arcsinh(args...);
            }
        };
    }
    constexpr inline auto arcsinh = functor_t(unary_fmap_t<fun::arcsinh_t>{});

    template <typename...arrays_t>
    struct get_function_t<
        view::decorator_t<
            view::ufunc_t, view::arcsinh_t, arrays_t...
        >
    > {
        using view_type = view::decorator_t<
            view::ufunc_t, view::arcsinh_t, arrays_t...
        >;

        view_type view;

        constexpr auto operator()() const noexcept
        {
            return arcsinh;
        }
    };
} // namespace nmtools::functional


#endif // NMTOOLS_ARRAY_FUNCTIONAL_UFUNCS_ARCSINH_HPP