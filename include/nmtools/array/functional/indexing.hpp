#ifndef NMTOOLS_ARRAY_FUNCTIONAL_INDEXING_HPP
#define NMTOOLS_ARRAY_FUNCTIONAL_INDEXING_HPP

#include "nmtools/utility/to_string/to_string.hpp"
#include "nmtools/array/functional/functor.hpp"
#include "nmtools/array/core/indexing.hpp"

namespace nmtools::functional::fun
{
    struct indexing
    {
        template <typename...args_t>
        constexpr auto operator()(const args_t&...args) const
        {
            return view::indexing(args...);
        }
    };
}

namespace nmtools::functional
{
    constexpr inline auto indexing = functor_t{unary_fmap_t<fun::indexing>{}};

    template <typename...args_t>
    struct get_function_t<
        view::decorator_t<
            view::indexing_t, args_t...
        >
    > {
        using view_type = view::decorator_t<
            view::indexing_t, args_t...
        >;

        view_type view;

        constexpr auto operator()() const noexcept
        {
            return indexing[view.attributes()];
        }
    };
} // namespace nmtools::functional

#if NMTOOLS_HAS_STRING

namespace nmtools::utils::impl
{
    template <auto...fmt_args>
    struct to_string_t<
        functional::fun::indexing, fmt_string_t<fmt_args...>
    >
    {
        using fun_type = functional::fun::indexing;
        using result_type = nmtools_string;

        auto operator()(const fun_type&) const noexcept
        {
            auto str = nmtools_string("");

            str += "indexing(";
            str += ")";

            return str;
        }
    };
}

#endif // NMTOOLS_HAS_STRING

#endif // NMTOOLS_ARRAY_FUNCTIONAL_INDEXING_HPP