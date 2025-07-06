#ifndef NMTOOLS_ARRAY_VIEW_ACTIVATIONS_RELU6_HPP
#define NMTOOLS_ARRAY_VIEW_ACTIVATIONS_RELU6_HPP

#include "nmtools/utility/to_string/to_string.hpp"
#include "nmtools/core/ufunc.hpp"

namespace nmtools::view::fun
{
    struct relu6
    {
        template <typename T>
        constexpr auto operator()(const T& t) const
        {
            auto x = t;
            if (x < 0) {
                x = 0;
            } else if (x > 6) {
                x = 6;
            }
            return x;
        } // operator()
    }; // relu6
} // namespace nmtools::view::fun

#if NMTOOLS_HAS_STRING

namespace nmtools::utils::impl
{
    template <auto...fmt_args>
    struct to_string_t<view::fun::relu6,fmt_string_t<fmt_args...>>
    {
        using result_type = nmtools_string;

        auto operator()(view::fun::relu6) const
        {
            nmtools_string str;

            str += "relu6";

            return str;
        }
    };
}

#endif // NMTOOLS_HAS_STRING

namespace nmtools::view
{
    using relu6_t = fun::relu6;

    template <typename array_t>
    constexpr auto relu6(const array_t& array)
    {
        return ufunc(relu6_t{},array);
    } // relu6
} // namespace nmtools::view

#endif // NMTOOLS_ARRAY_VIEW_ACTIVATIONS_RELU6_HPP

#ifndef NMTOOLS_ARRAY_FUNCTIONAL_ACTIVATIONS_RELU6_HPP
#define NMTOOLS_ARRAY_FUNCTIONAL_ACTIVATIONS_RELU6_HPP

#include "nmtools/core/functor.hpp"
#include "nmtools/array/relu6.hpp"
#include "nmtools/core/ufunc/ufunc.hpp"

namespace nmtools::functional
{
    namespace fun
    {
        using relu6 = fun::unary_ufunc<view::relu6_t>;
    } // namespace fun

    constexpr inline auto relu6 = functor_t{unary_fmap_t<fun::relu6>{}};
} // namespace nmtools::functional


#endif // NMTOOLS_ARRAY_FUNCTIONAL_ACTIVATIONS_RELU6_HPP

#ifndef NMTOOLS_ARRAY_ARRAY_ACTIVATIONS_RELU6_HPP
#define NMTOOLS_ARRAY_ARRAY_ACTIVATIONS_RELU6_HPP

#include "nmtools/array/relu6.hpp"
#include "nmtools/core/eval.hpp"

namespace nmtools
{
    /**
     * @brief Eagerly compute element-wise relu6.
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
    constexpr auto relu6(const array_t& array,
        context_t&& context=context_t{}, output_t&& output=output_t{},meta::as_value<resolver_t> resolver=meta::as_value_v<resolver_t>)
    {
        auto a = view::relu6(array);
        return eval(a
            ,nmtools::forward<context_t>(context)
            ,nmtools::forward<output_t>(output)
            ,resolver
        );
    } // relu6
} // namespace nmtools

#endif // NMTOOLS_ARRAY_ARRAY_ACTIVATIONS_RELU6_HPP