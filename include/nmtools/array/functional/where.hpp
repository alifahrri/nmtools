#ifndef NMTOOLS_ARRAY_FUNCTIONAL_WHERE_HPP
#define NMTOOLS_ARRAY_FUNCTIONAL_WHERE_HPP

#include "nmtools/array/functional/functor.hpp"
#include "nmtools/array/view/where.hpp"

namespace nmtools::functional
{
    namespace fun
    {
        struct where_t
        {
            template <typename...args_t>
            constexpr auto operator()(const args_t&...args) const
            {
                return view::where(args...);
            }
        };
    }

    constexpr inline auto where = functor_t(ternary_fmap_t<fun::where_t>{});

    template <typename...args_t>
    struct get_function_t<
        view::decorator_t<
            view::where_t, args_t...
        >
    > {
        using view_type = view::decorator_t<
            view::where_t, args_t...
        >;

        view_type view;

        constexpr auto operator()() const noexcept
        {
            return where;
        }
    };
} // namespace nmtools::functional

#endif // NMTOOLS_ARRAY_FUNCTIONAL_WHERE_HPP