#ifndef NMTOOLS_CORE_CAST_HPP
#define NMTOOLS_CORE_CAST_HPP

#include "nmtools/meta.hpp"
#include "nmtools/utility.hpp"
#include "nmtools/core/ufunc.hpp"
#include "nmtools/core/functor.hpp"
#include "nmtools/core/eval.hpp"

namespace nmtools::view::fun
{
    template <typename dst_t>
    struct cast
    {
        using dst_type = dst_t;

        template <typename T>
        constexpr auto operator()(const T& t) const noexcept
        {
            return static_cast<dst_type>(t);
        }
    };
}

namespace nmtools::view
{
    template <typename array_t, typename dtype_t>
    constexpr auto cast(const array_t& array, dtype_t)
    {
        using dst_t = get_dtype_t<dtype_t>;
        using op_t = fun::cast<dst_t>;
        return unary_ufunc(op_t{},array);
    }

    template <typename array_t, typename dtype_t>
    constexpr auto astype(const array_t& array, dtype_t)
    {
        using dst_t = get_dtype_t<dtype_t>;
        using op_t = fun::cast<dst_t>;
        return unary_ufunc(op_t{},array);
    }
}

#if NMTOOLS_HAS_STRING

namespace nmtools::utils::impl
{
    template <typename dst_t, auto...fmt_args>
    struct to_string_t<
        view::fun::cast<dst_t>,fmt_string_t<fmt_args...>
    > {
        using result_type = nmtools_string;

        auto operator()(view::fun::cast<dst_t>) const noexcept
        {
            nmtools_string str;

            str += "cast";
            str += "(";
            str += NMTOOLS_TYPENAME_TO_STRING(dst_t);
            str += ")";
            
            return str;
        }
    };
}

#endif // NMTOOLS_HAS_STRING

namespace nmtools::functional
{
    namespace fun
    {
        struct cast
        {
            template <typename...args_t>
            constexpr auto operator()(const args_t&...args) const
            {
                return view::cast(args...);
            }
        };
    }

    constexpr inline auto cast = functor_t{unary_fmap_t<fun::cast>{}};

    constexpr inline auto astype = functor_t{unary_fmap_t<fun::cast>{}};
}

namespace nmtools::array
{
    template <typename output_t=none_t, typename context_t=none_t, typename resolver_t=eval_result_t<>
        , typename array_t, typename dtype_t>
    constexpr auto cast(const array_t& array, dtype_t dtype
        , context_t&& context=context_t{}, output_t&& output=output_t{},meta::as_value<resolver_t> resolver=meta::as_value_v<resolver_t>)
    {
        auto v = view::cast(array,dtype);
        return eval(v
            , nmtools::forward<context_t>(context)
            , nmtools::forward<output_t>(output)
            , resolver
        );
    }

    template <typename output_t=none_t, typename context_t=none_t, typename resolver_t=eval_result_t<>
        , typename array_t, typename dtype_t>
    constexpr auto astype(const array_t& array, dtype_t dtype
        , context_t&& context=context_t{}, output_t&& output=output_t{},meta::as_value<resolver_t> resolver=meta::as_value_v<resolver_t>)
    {
        auto v = view::astype(array,dtype);
        return eval(v
            , nmtools::forward<context_t>(context)
            , nmtools::forward<output_t>(output)
            , resolver
        );
    }
}

#endif // NMTOOLS_CORE_CAST_HPP