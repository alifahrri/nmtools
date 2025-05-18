#ifndef NMTOOLS_ARRAY_VIEW_UFUNCS_DIVIDE_HPP
#define NMTOOLS_ARRAY_VIEW_UFUNCS_DIVIDE_HPP

#include "nmtools/utility/to_string/to_string.hpp"
#include "nmtools/core/ufunc.hpp"
#include "nmtools/core/cast.hpp"

namespace nmtools::view::fun
{
    struct divide
    {
        template <typename T, typename U>
        constexpr auto operator()(const T& t, const U& u) const
        {
            return t / u;
        } // operator()
    }; // divide
}

namespace nmtools::meta
{
    template <typename T, typename U>
    struct get_ufunc_result_type<
        void, view::fun::divide, T, U
    > {
        static constexpr auto vtype = [](){
            if constexpr (is_integer_v<T> && is_integer_v<U>) {
                using type = float;
                return as_value_v<type>;
            } else if constexpr (is_floating_point_v<T> && is_integer_v<U>) {
                using type = T;
                return as_value_v<type>;
            } else if constexpr (is_integer_v<T> && is_floating_point_v<U>) {
                using type = U;
                return as_value_v<type>;
            } else {
                if constexpr (sizeof(T) > sizeof(U)) {
                    using type = T;
                    return as_value_v<type>;
                } else {
                    using type = U;
                    return as_value_v<type>;
                }
            }
        }();
        using type = type_t<decltype(vtype)>;
    };
}

namespace nmtools::view
{
    using divide_t = fun::divide;

    template <typename left_t, typename right_t>
    constexpr auto divide(const left_t& a, const right_t& b)
    {
        // still handle maybe here to avoid calling nmtools::get on maybe type
        if constexpr (meta::is_maybe_v<left_t> || meta::is_maybe_v<right_t>) {
            using result_t = decltype(divide(unwrap(a),unwrap(b)));
            using return_t = meta::conditional_t<
                meta::is_maybe_v<result_t>, result_t, nmtools_maybe<result_t>>;
            return (has_value(a) && has_value(b)
                ? return_t{divide(unwrap(a),unwrap(b))}
                : return_t{meta::Nothing}
            );
        } else if constexpr (meta::is_either_v<left_t>) {
            using either_left_t  = meta::get_either_left_t<left_t>;
            using either_right_t = meta::get_either_right_t<left_t>;
            using res_left_t  = decltype(divide(meta::declval<either_left_t>(),b));
            using res_right_t = decltype(divide(meta::declval<either_right_t>(),b));
            using result_t = meta::conditional_t<
                meta::is_same_v<res_left_t,res_right_t>, res_left_t
                , nmtools_either<res_left_t,res_right_t>>;
            if (auto l_ptr = nmtools::get_if<either_left_t>(&a)) {
                return result_t{divide(*l_ptr,b)};
            } else {
                auto r_ptr = nmtools::get_if<either_right_t>(&a);
                return result_t{divide(*r_ptr,b)};
            }
        } else if constexpr (meta::is_either_v<right_t>) {
            using either_left_t  = meta::get_either_left_t<right_t>;
            using either_right_t = meta::get_either_right_t<right_t>;
            using res_left_t  = decltype(a,divide(meta::declval<either_left_t>()));
            using res_right_t = decltype(a,divide(meta::declval<either_right_t>()));
            using result_t = meta::conditional_t<
                meta::is_same_v<res_left_t,res_right_t>, res_left_t
                , nmtools_either<res_left_t,res_right_t>>;
            if (auto l_ptr = nmtools::get_if<either_left_t>(&b)) {
                return result_t{divide(a,*l_ptr)};
            } else {
                auto r_ptr = nmtools::get_if<either_right_t>(&b);
                return result_t{divide(a,*r_ptr)};
            }
        } else {
            using left_element_t  = meta::get_element_type_t<left_t>;
            using right_element_t = meta::get_element_type_t<right_t>;
            using result_t = meta::get_ufunc_result_type_t<divide_t,left_element_t,right_element_t>;
            auto dtype     = dtype_t<result_t>{};
            auto aliased   = view::aliased(a,b);
            auto a_a = nmtools::get<0>(aliased);
            auto a_b = nmtools::get<1>(aliased);
            auto c_a = view::cast(a_a,dtype);
            auto c_b = view::cast(a_b,dtype);
            return broadcast_binary_ufunc(divide_t{},c_a,c_b);
        }
    } // divide
}

#if NMTOOLS_HAS_STRING

namespace nmtools::utils::impl
{
    template <auto...fmt_args>
    struct to_string_t<view::fun::divide,fmt_string_t<fmt_args...>>
    {
        using result_type = nmtools_string;

        auto operator()(view::fun::divide) const
        {
            auto str = nmtools_string();

            str += "divide";

            return str;
        }
    };
}

#endif // NMTOOLS_HAS_STRING

#endif // NMTOOLS_ARRAY_VIEW_UFUNCS_DIVIDE_HPP

#ifndef NMTOOLS_ARRAY_FUNCTIONAL_UFUNCS_DIVIDE_HPP
#define NMTOOLS_ARRAY_FUNCTIONAL_UFUNCS_DIVIDE_HPP

#include "nmtools/core/functor.hpp"
#include "nmtools/array/ufuncs/divide.hpp"
#include "nmtools/core/ufunc/ufunc.hpp"

namespace nmtools::functional
{
    namespace fun
    {
        using divide = fun::broadcast_binary_ufunc<view::divide_t>;
    }

    constexpr inline auto divide = functor_t{binary_fmap_t<fun::divide>{}};
} // namespace nmtools::functional

#endif // NMTOOLS_ARRAY_FUNCTIONAL_UFUNCS_DIVIDE_HPP

#ifndef NMTOOLS_ARRAY_ARRAY_DIVIDE_HPP
#define NMTOOLS_ARRAY_ARRAY_DIVIDE_HPP

#include "nmtools/core/eval.hpp"
#include "nmtools/array/ufuncs/divide.hpp"
#include "nmtools/constants.hpp"

namespace nmtools::array
{
    namespace fn
    {
        struct divide
        {
            template <typename output_t=none_t, typename context_t=none_t, typename resolver_t=eval_result_t<>,
                typename left_t, typename right_t>
            inline constexpr auto operator()(const left_t& a, const right_t& b,
                context_t&& context=context_t{}, output_t&& output=output_t{},meta::as_value<resolver_t> resolver=meta::as_value_v<resolver_t>) const
            {
                auto divide = view::divide(a,b);
                return eval(divide
                    ,nmtools::forward<context_t>(context)
                    ,nmtools::forward<output_t>(output)
                    ,resolver
                );
            } // operator()

            template <typename output_t=none_t, typename context_t=none_t, typename resolver_t=eval_result_t<>,
                typename left_t, typename right_t>
            inline constexpr auto operator()(const left_t& a, const right_t& b, casting::same_kind_t,
                context_t&& context=context_t{}, output_t&& output=output_t{},meta::as_value<resolver_t> resolver=meta::as_value_v<resolver_t>) const
            {
                auto divide = view::divide(a,b);
                return eval(divide
                    ,nmtools::forward<context_t>(context)
                    ,nmtools::forward<output_t>(output)
                    ,resolver
                );
            } // operator()
        }; // divide
    } // namespace fn

    constexpr inline auto divide = fn::divide{};
} // nmtools::array

#endif // NMTOOLS_ARRAY_ARRAY_DIVIDE_HPP