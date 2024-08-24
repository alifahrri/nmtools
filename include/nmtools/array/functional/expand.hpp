#ifndef NMTOOLS_ARRAY_FUNCTIONAL_EXPAND_HPP
#define NMTOOLS_ARRAY_FUNCTIONAL_EXPAND_HPP

#include "nmtools/utils/to_string/to_string.hpp"
#include "nmtools/array/functional/functor.hpp"
#include "nmtools/array/view/expand.hpp"

namespace nmtools::functional::fun
{
    struct expand
    {
        template <typename...args_t>
        constexpr auto operator()(const args_t&...args) const
        {
            return view::expand(args...);
        }
    };
}

namespace nmtools::functional
{
    constexpr inline auto expand = functor_t{unary_fmap_t<fun::expand>{}};

    #if 0
    template <typename...args_t>
    struct get_function_t<
        view::decorator_t<
            view::expand_t, args_t...
        >
    > {
        using view_type = view::decorator_t<
            view::expand_t, args_t...
        >;

        view_type view;

        constexpr auto operator()() const noexcept
        {
            return expand[view.attributes()];
        }
    };
    #endif
} // namespace nmtools::functional

#if 0

#if NMTOOLS_HAS_STRING

namespace nmtools::utils::impl
{
    template <auto...fmt_args>
    struct to_string_t<
        functional::fun::expand, fmt_string_t<fmt_args...>
    >
    {
        using fun_type = functional::fun::expand;
        using result_type = nmtools_string;

        auto operator()(const fun_type&) const noexcept
        {
            auto str = nmtools_string("");

            str += "expand(";
            str += ")";

            return str;
        }
    };
}

#endif // NMTOOLS_HAS_STRING
#endif

#endif // NMTOOLS_ARRAY_FUNCTIONAL_EXPAND_HPP