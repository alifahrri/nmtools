#ifndef NMTOOLS_ARRAY_FUNCTIONAL_ATLEAST_3D_HPP
#define NMTOOLS_ARRAY_FUNCTIONAL_ATLEAST_3D_HPP

#include "nmtools/array/functional/functor.hpp"
#include "nmtools/array/view/atleast_3d.hpp"

namespace nmtools::functional
{
    namespace fun 
    {
        struct atleast_3d_t
        {
            template <typename...args_t>
            constexpr auto operator()(const args_t&...args) const
            {
                return view::atleast_3d(args...);
            }
        };
    }

    constexpr inline auto atleast_3d = functor_t(unary_fmap_t<fun::atleast_3d_t>{});

    template <typename...args_t>
    struct get_function_t<
        view::decorator_t<
            view::atleast_3d_t, args_t...
        >
    >
    {
        using view_type = view::decorator_t<
            view::atleast_3d_t, args_t...
        >;

        view_type view;

        constexpr auto operator()() const noexcept
        {
            return atleast_3d;
        }
    };
} // namespace nmtools::functional

#endif // NMTOOLS_ARRAY_FUNCTIONAL_ATLEAST_3D_HPP