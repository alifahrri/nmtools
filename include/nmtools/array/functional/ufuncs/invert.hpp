#ifndef NMTOOLS_ARRAY_FUNCTIONAL_UFUNCS_INVERT_HPP
#define NMTOOLS_ARRAY_FUNCTIONAL_UFUNCS_INVERT_HPP

#include "nmtools/array/functional/functor.hpp"
#include "nmtools/array/view/ufuncs/invert.hpp"

namespace nmtools::functional
{
    namespace fun
    {
        struct invert_t
        {
            template <typename...args_t>
            constexpr auto operator()(const args_t&...args) const
            {
                return view::invert(args...);
            }
        };
    }

    constexpr inline auto invert = functor_t(unary_fmap_t<fun::invert_t>{});

    template <typename...arrays_t>
    struct get_function_t<
        view::decorator_t<
            view::ufunc_t, view::invert_t, arrays_t...
        >
    > {
        using view_type = view::decorator_t<
            view::ufunc_t, view::invert_t, arrays_t...
        >;

        view_type view;

        constexpr auto operator()() const noexcept
        {
            return invert;
        }
    };
} // namespace nmtools::functional


#endif // NMTOOLS_ARRAY_FUNCTIONAL_UFUNCS_INVERT_HPP