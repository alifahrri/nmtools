#ifndef NMTOOLS_ARRAY_FUNCTIONAL_UFUNC_UFUNC_HPP
#define NMTOOLS_ARRAY_FUNCTIONAL_UFUNC_UFUNC_HPP

#include "nmtools/array/core/ufunc/ufunc.hpp"
#include "nmtools/array/core/ufunc.hpp"
#include "nmtools/array/functional/functor.hpp"
#include "nmtools/utility/to_string/to_string.hpp"
#include "nmtools/utility/to_string/common_types.hpp"
#include "nmtools/array/functional/indexing.hpp"

#include "nmtools/utility/isequal.hpp"

namespace nmtools::functional::fun
{
    template <typename op_t=none_t>
    struct broadcast_binary_ufunc
    {
        template <typename...args_t>
        constexpr auto operator()(const args_t&...args) const
        {
            if constexpr (is_none_v<op_t>) {
                return view::broadcast_binary_ufunc(args...);
            } else {
                return view::broadcast_binary_ufunc(op_t{},args...);
            }
        }
    };

    template <typename op_t=none_t>
    struct binary_ufunc
    {
        template <typename...args_t>
        constexpr auto operator()(const args_t&...args) const
        {
            if constexpr (is_none_v<op_t>) {
                return view::binary_ufunc(args...);
            } else {
                return view::binary_ufunc(op_t{},args...);
            }
        }
    };

    template <typename op_t=none_t>
    struct unary_ufunc
    {
        using op_type = op_t;

        template <typename...args_t>
        constexpr auto operator()(const args_t&...args) const
        {
            if constexpr (is_none_v<op_type>) {
                return view::unary_ufunc(args...);
            } else {
                return view::unary_ufunc(op_type{},args...);
            }
        }
    };
} // namespace nmtools::functional::fun

namespace nmtools::utils
{
    using functional::fun::unary_ufunc;
    using functional::unary_fmap_t;
    using functional::functor_t;

    template <
        typename F, typename lhs_operands_t, typename lhs_attributes_t
        , typename G, typename rhs_operands_t, typename rhs_attributes_t>
    constexpr auto isequal(
        [[maybe_unused]] const functor_t<unary_fmap_t<unary_ufunc<F>>,lhs_operands_t,lhs_attributes_t>& lhs
        , [[maybe_unused]] const functor_t<unary_fmap_t<unary_ufunc<G>>,rhs_operands_t,rhs_attributes_t>& rhs
    )
        -> meta::enable_if_t<(is_none_v<F> || is_none_v<G>) && !meta::is_same_v<F,G>,bool>
    {
        // unfortunately the easiest way to compare is getting the view and extract the function composition
        using dummy_i_array_t = nmtools_array<int,1>;
        using dummy_f_array_t = nmtools_array<float,1>;
        constexpr auto can_call_float = meta::expression_check_v<meta::expr::callable,decltype(lhs),dummy_f_array_t>;
        using dummy_type = meta::conditional_t<
            can_call_float, dummy_f_array_t, dummy_i_array_t
        >;
        auto dummy_array = dummy_type{1};

        // the following should have same op, regardless how many attributes configuration
        auto lhs_view = lhs (dummy_array);
        auto rhs_view = rhs (dummy_array);

        // return isequal(lhs_view.attributes(),rhs_view.attributes());
        return lhs_view.attributes() == rhs_view.attributes();
    }
} // namespace nmtools::utils

namespace nmtools::functional
{
    constexpr inline auto unary_ufunc  = functor_t{unary_fmap_t<fun::unary_ufunc<>>{}};
    constexpr inline auto binary_ufunc = functor_t{binary_fmap_t<fun::binary_ufunc<>>{}};
    constexpr inline auto broadcast_binary_ufunc = functor_t{binary_fmap_t<fun::broadcast_binary_ufunc<>>{}};

    template <typename op_t, typename lhs_t, typename rhs_t>
    struct get_function_t<
        view::decorator_t<
            view::ufunc_t, op_t, lhs_t, rhs_t
        >
    > {
        using view_type = view::decorator_t<
            view::ufunc_t, op_t, lhs_t, rhs_t
        >;

        view_type view;
        constexpr auto operator()() const noexcept
        {
            return broadcast_binary_ufunc[view.attributes()];
        }
    };

    template <typename op_t, typename array_t>
    struct get_function_t<
        view::decorator_t<
            view::ufunc_t, op_t, array_t
        >
    > {
        using view_type = view::decorator_t<
            view::ufunc_t, op_t, array_t
        >;

        view_type view;
        constexpr auto operator()() const noexcept
        {
            return unary_ufunc[view.attributes()];
        }
    };
} // namespace nmtools::functional

#if NMTOOLS_HAS_STRING

namespace nmtools::utils::impl
{
    template <typename op_t, auto...fmt_args>
    struct to_string_t<
        functional::fun::unary_ufunc<op_t>, fmt_string_t<fmt_args...>
    > {
        using ufunc_type = functional::fun::unary_ufunc<op_t>;
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

            str += "ufunc(";
            str += op_str;
            str += ")";

            return str;
        }
    };

    template <typename op_t, auto...fmt_args>
    struct to_string_t<
        functional::fun::binary_ufunc<op_t>, fmt_string_t<fmt_args...>
    > {
        using ufunc_type = functional::fun::binary_ufunc<op_t>;
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

            str += "ufunc(";
            str += op_str;
            str += ")";

            return str;
        }
    };

    template <typename op_t, auto...fmt_args>
    struct to_string_t<
        functional::fun::broadcast_binary_ufunc<op_t>, fmt_string_t<fmt_args...>
    > {
        using ufunc_type = functional::fun::broadcast_binary_ufunc<op_t>;
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

            str += "broadcast_ufunc(";
            str += op_str;
            str += ")";

            return str;
        }
    };
} // namespace nmtools::utils::impl

#endif /// NMTOOLS_HAS_STRING

#endif // NMTOOLS_ARRAY_FUNCTIONAL_UFUNC_UFUNC_HPP