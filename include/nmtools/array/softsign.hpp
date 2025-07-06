#ifndef NMTOOLS_ARRAY_VIEW_ACTIVATION_SOFTSIGN_HPP
#define NMTOOLS_ARRAY_VIEW_ACTIVATION_SOFTSIGN_HPP

#include "nmtools/utility/to_string/to_string.hpp"
#include "nmtools/core/ufunc.hpp"

namespace nmtools::view::fun
{
    /**
     * @brief Function object for softsign ufunc
     * 
     */
    struct softsign
    {
        template <typename T>
        constexpr auto operator()(const T& x) const
        {
            auto abs_x = x > 0 ? x : -x;
            return x / (1 + abs_x);
        } // operator()
    }; // softsign
}

#if NMTOOLS_HAS_STRING

namespace nmtools::utils::impl
{
    template <auto...fmt_args>
    struct to_string_t<view::fun::softsign,fmt_string_t<fmt_args...>>
    {
        using result_type = nmtools_string;

        auto operator()(view::fun::softsign) const
        {
            nmtools_string str;

            str += "softsign";

            return str;
        }
    };
}

#endif // NMTOOLS_HAS_STRING

namespace nmtools::view
{
    using softsign_t = fun::softsign;

    /**
     * @brief Create element-wise softsign ufunc view
     * 
     * @tparam array_t 
     * @param array     input array
     * @return constexpr auto 
     */
    template <typename array_t>
    constexpr auto softsign(const array_t& array)
    {
        return ufunc(softsign_t{}, array);
    } // softsign
} // namespace nmtools::view

#endif // NMTOOLS_ARRAY_VIEW_ACTIVATION_SOFTSIGN_HPP

#ifndef NMTOOLS_ARRAY_FUNCTIONAL_ACTIVATIONS_SOFTSIGN_HPP
#define NMTOOLS_ARRAY_FUNCTIONAL_ACTIVATIONS_SOFTSIGN_HPP

#include "nmtools/core/functor.hpp"
#include "nmtools/array/softsign.hpp"
#include "nmtools/core/ufunc/ufunc.hpp"

namespace nmtools::functional
{
    namespace fun
    {
        using softsign = fun::unary_ufunc<view::softsign_t>;
    }

    constexpr inline auto softsign = functor_t{unary_fmap_t<fun::softsign>{}};
} // namespace nmtools::functional


#endif // NMTOOLS_ARRAY_FUNCTIONAL_ACTIVATIONS_SOFTSIGN_HPP

#ifndef NMTOOLS_ARRAY_ARRAY_ACTIVATIONS_SOFTSIGN_HPP
#define NMTOOLS_ARRAY_ARRAY_ACTIVATIONS_SOFTSIGN_HPP

#include "nmtools/array/softsign.hpp"
#include "nmtools/core/eval.hpp"

namespace nmtools
{
    /**
     * @brief Eagerly evaluate element-wise softsign function
     * 
     * @tparam output_t 
     * @tparam context_t 
     * @tparam array_t 
     * @param array     input array
     * @param context   evaluation context
     * @param output 
     * @return constexpr auto 
     */
    template <typename output_t=none_t, typename context_t=none_t, typename resolver_t=eval_result_t<>,
        typename array_t>
    constexpr auto softsign(const array_t& array,
        context_t&& context=context_t{}, output_t&& output=output_t{},meta::as_value<resolver_t> resolver=meta::as_value_v<resolver_t>)
    {
        auto a = view::softsign(array);
        return eval(a
            ,nmtools::forward<context_t>(context)
            ,nmtools::forward<output_t>(output)
            ,resolver
        );
    } // softsign
} // namespace nmtools

#endif // NMTOOLS_ARRAY_ARRAY_ACTIVATIONS_SOFTSIGN_HPP