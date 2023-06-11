#ifndef NMTOOLS_ARRAY_FUNCTIONAL_ATLEAST_2D_HPP
#define NMTOOLS_ARRAY_FUNCTIONAL_ATLEAST_2D_HPP

#include "nmtools/array/functional/functor.hpp"
#include "nmtools/array/view/atleast_2d.hpp"

namespace nmtools::functional
{
    namespace fun 
    {
        struct atleast_2d_t
        {
            template <typename...args_t>
            constexpr auto operator()(const args_t&...args) const
            {
                return view::atleast_2d(args...);
            }
        };
    }

    constexpr inline auto atleast_2d = functor_t(unary_fmap_t<fun::atleast_2d_t>{});

    template <typename...args_t>
    struct get_function_t<
        view::decorator_t<
            view::atleast_2d_t, args_t...
        >
    >
    {
        using view_type = view::decorator_t<
            view::atleast_2d_t, args_t...
        >;

        view_type view;

        constexpr auto operator()() const noexcept
        {
            return atleast_2d;
        }
    };
} // namespace nmtools::functional

#endif // NMTOOLS_ARRAY_FUNCTIONAL_ATLEAST_2D_HPP