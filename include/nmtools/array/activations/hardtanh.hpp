#ifndef NMTOOLS_ARRAY_VIEW_ACTIVATIONS_HARDTANH_HPP
#define NMTOOLS_ARRAY_VIEW_ACTIVATIONS_HARDTANH_HPP

#include "nmtools/utility/isclose.hpp"
#include "nmtools/utility/to_string/to_string.hpp"
#include "nmtools/core/ufunc.hpp"

namespace nmtools::view::fun
{
    /**
     * @brief Function object for hardtanh ufunc.
     * 
     * @tparam min_val_t 
     * @tparam max_val_t 
     */
    template <typename min_val_t=float, typename max_val_t=min_val_t>
    struct hardtanh
    {
        const min_val_t min_val = -1.0;
        const max_val_t max_val =  1.0;

        template <typename T>
        constexpr auto operator()(const T& t) const -> T
        {
            if (t < min_val) {
                return min_val;
            } else if (t > max_val) {
                return max_val;
            } else {
                return t;
            }
        } // operator()

        template <template<typename...>typename tuple, typename T, typename U>
        constexpr auto operator[](const tuple<T,U>& t) const noexcept
        {
            return hardtanh<T,U>{nmtools::get<0>(t),nmtools::get<1>(t)};
        }

        template <template<typename...>typename tuple, typename T>
        constexpr auto operator[](const tuple<T>& t) const noexcept
        {
            return hardtanh<T>{nmtools::get<0>(t)};
        }

        template <typename T>
        constexpr auto operator==(const hardtanh<T> other) const
        {
            return utils::isclose(min_val,other.min_val)
                && utils::isclose(max_val,other.max_val);
        }
    }; // hardtanh
} // namespace nmtools::view::fun

#if NMTOOLS_HAS_STRING

namespace nmtools::utils::impl
{
    template <typename min_val_t, typename max_val_t
        , auto...fmt_args
    >
    struct to_string_t<view::fun::hardtanh<min_val_t,max_val_t>
        , fmt_string_t<fmt_args...>
    > {
        using result_type = nmtools_string;

        auto operator()(view::fun::hardtanh<min_val_t,max_val_t> op) const
        {
            nmtools_string str;

            str += "hardtanh";
            str += "{";
            str += ".min_val=";
            str += to_string(op.min_val);
            str += ",.max_val=";
            str += to_string(op.max_val);
            str += "}";

            return str;
        }
    };
}

#endif // NMTOOLS_HAS_STRING

namespace nmtools::view
{
    template <typename min_val_t=float, typename max_val_t=min_val_t>
    using hardtanh_t = fun::hardtanh<min_val_t,max_val_t>;

    /**
     * @brief Create element-wise hardtanh ufunc view.
     * 
     * @tparam array_t 
     * @tparam min_val_t 
     * @tparam max_val_t 
     * @param array     input array
     * @param min_val   minimum value of the linear region
     * @param max_val   maximum value of the linear region
     * @return constexpr auto 
     */
    template <typename array_t, typename min_val_t=float, typename max_val_t=min_val_t>
    constexpr auto hardtanh(const array_t& array, const min_val_t min_val=min_val_t{-1.0},
        const max_val_t max_val=max_val_t{1.0})
    {
        return ufunc(hardtanh_t<min_val_t,max_val_t>{min_val,max_val},array);
    } // hardtanh

    template <typename array_t, typename min_val_t=float, typename max_val_t=min_val_t>
    constexpr auto hardtanh(const array_t& array, fun::hardtanh<min_val_t,max_val_t> op)
    {
        return ufunc(op,array);
    } // hardtanh
} // namespace nmtools::view

#endif // NMTOOLS_ARRAY_VIEW_ACTIVATIONS_HARDTANH_HPP

#ifndef NMTOOLS_ARRAY_FUNCTIONAL_ACTIVATIONS_HARDTANH_HPP
#define NMTOOLS_ARRAY_FUNCTIONAL_ACTIVATIONS_HARDTANH_HPP

#include "nmtools/core/functor.hpp"
#include "nmtools/array/activations/hardtanh.hpp"
#include "nmtools/core/ufunc/ufunc.hpp"

namespace nmtools::functional
{
    namespace fun
    {
        using hardtanh = fun::unary_ufunc<view::hardtanh_t<>>;
    }

    constexpr inline auto hardtanh = functor_t{unary_fmap_t<fun::hardtanh>{}};
} // namespace nmtools::functional


#endif // NMTOOLS_ARRAY_FUNCTIONAL_ACTIVATIONS_HARDTANH_HPP

#ifndef NMTOOLS_ARRAY_ARRAY_ACTIVATIONS_HARDTANH_HPP
#define NMTOOLS_ARRAY_ARRAY_ACTIVATIONS_HARDTANH_HPP

#include "nmtools/array/activations/hardtanh.hpp"
#include "nmtools/core/eval.hpp"

namespace nmtools
{
    /**
     * @brief Eagerly compute element-wise hardtanh ufunc.
     * 
     * @tparam output_t 
     * @tparam context_t 
     * @tparam array_t 
     * @tparam min_val_t 
     * @tparam max_val_t 
     * @param array     input array
     * @param min_val   minimum value of linear region
     * @param max_val   maximum value of linear region
     * @param context   evaluation context
     * @param output 
     * @return constexpr auto 
     */
    template <typename output_t=none_t, typename context_t=none_t, typename resolver_t=eval_result_t<>,
        typename array_t, typename min_val_t=float, typename max_val_t=float>
    constexpr auto hardtanh(const array_t& array, const min_val_t min_val=min_val_t{-1.0},
        const max_val_t max_val=max_val_t{1.0},
        context_t&& context=context_t{}, output_t&& output=output_t{},meta::as_value<resolver_t> resolver=meta::as_value_v<resolver_t>)
    {
        auto a = view::hardtanh(array,min_val,max_val);
        return eval(a
            ,nmtools::forward<context_t>(context)
            ,nmtools::forward<output_t>(output)
            ,resolver
        );
    } // hardtanh
} // namespace nmtools

#endif // NMTOOLS_ARRAY_ARRAY_ACTIVATIONS_HARDTANH_HPP