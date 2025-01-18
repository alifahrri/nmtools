#ifndef NMTOOLS_ARRAY_FUNCTIONAL_UFUNC_REDUCE_HPP
#define NMTOOLS_ARRAY_FUNCTIONAL_UFUNC_REDUCE_HPP

#include "nmtools/utility/to_string/to_string.hpp"
#include "nmtools/core/functor.hpp"
#include "nmtools/core/ufunc.hpp"

namespace nmtools::functional::fun
{
    template <typename op_t=none_t>
    struct reduce
    {
        template <typename...args_t>
        constexpr auto operator()(const args_t&...args) const
        {
            if constexpr (is_none_v<op_t>) {
                return view::reduce(args...);
            } else {
                return view::reduce(op_t{},args...);
            }
        }
    };
}

namespace nmtools::functional
{
    constexpr inline auto reduce = functor_t{unary_fmap_t<fun::reduce<>>{}};

    template <typename...args_t>
    struct get_function_t<
        view::decorator_t<
            view::reduce_t, args_t...
        >
    > {
        using view_type = view::decorator_t<
            view::reduce_t, args_t...
        >;

        view_type view;

        constexpr auto operator()() const noexcept
        {
            return reduce[view.attributes()];
        }
    };
}

#if NMTOOLS_HAS_STRING

namespace nmtools::utils::impl
{
    template <typename op_t, auto...fmt_args>
    struct to_string_t<
        functional::fun::reduce<op_t>, fmt_string_t<fmt_args...>
    > {
        using ufunc_type = functional::fun::reduce<op_t>;
        using result_type = nmtools_string;

        auto operator()(const ufunc_type&) const noexcept
        {
            auto op_str = nmtools_string("");
            
            if constexpr (!is_none_v<op_t>) {
                op_str = to_string(op_t{});

                if (op_str.empty()) {
                    op_str += NMTOOLS_TYPENAME_TO_STRING(op_t);
                }
            }

            auto str = nmtools_string("");

            str += "reduce(";
            str += op_str;
            str += ")";

            return str;
        }
    };
} // namespace nmtools::utils::impl

#endif // NMTOOLS_HAS_STRING

#endif // NMTOOLS_ARRAY_FUNCTIONAL_UFUNC_REDUCE_HPP