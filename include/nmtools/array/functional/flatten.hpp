#ifndef NMTOOLS_ARRAY_FUNCTIONAL_FLATTEN_HPP
#define NMTOOLS_ARRAY_FUNCTIONAL_FLATTEN_HPP

#include "nmtools/array/functional/functor.hpp"
#include "nmtools/array/view/flatten.hpp"

namespace nmtools::functional
{
    namespace fun 
    {
        struct flatten_t
        {
            template <typename...args_t>
            constexpr auto operator()(const args_t&...args) const
            {
                return view::flatten(args...);
            }
        };
    }

    constexpr inline auto flatten = functor_t(unary_fmap_t<fun::flatten_t>{});

    template <typename...args_t>
    struct get_function_t<
        view::decorator_t<
            view::flatten_t, args_t...
        >
    >
    {
        using view_type = view::decorator_t<
            view::flatten_t, args_t...
        >;

        view_type view;

        constexpr auto operator()() const noexcept
        {
            return flatten;
        }
    };
} // namespace nmtools::functional

#endif // NMTOOLS_ARRAY_FUNCTIONAL_FLATTEN_HPP