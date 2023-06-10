#ifndef NMTOOLS_ARRAY_FUNCTIONAL_SQUEEZE_HPP
#define NMTOOLS_ARRAY_FUNCTIONAL_SQUEEZE_HPP

#include "nmtools/array/functional/functor.hpp"
#include "nmtools/array/view/squeeze.hpp"

namespace nmtools::functional
{
    namespace fun
    {
        struct squeeze_t
        {
            template <typename...args_t>
            constexpr auto operator()(const args_t&...args) const
            {
                return view::squeeze(args...);
            }
        };
    }

    constexpr inline auto squeeze = functor_t(unary_fmap_t<fun::squeeze_t>{});

    template <typename...args_t>
    struct get_function_t<
        view::decorator_t<
            view::squeeze_t, args_t...
        >
    > {
        using view_type = view::decorator_t<
            view::squeeze_t, args_t...
        >;

        view_type view;

        constexpr auto operator()() const noexcept
        {
            return squeeze;
        }
    };
} // namespace nmtools::functional

#endif // NMTOOLS_ARRAY_FUNCTIONAL_SQUEEZE_HPP