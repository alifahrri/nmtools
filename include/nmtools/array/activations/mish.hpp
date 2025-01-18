#ifndef NMTOOLS_ARRAY_VIEW_ACTIVATIONS_MISH_HPP
#define NMTOOLS_ARRAY_VIEW_ACTIVATIONS_MISH_HPP

#include "nmtools/core/ufunc.hpp"
#include "nmtools/utility/to_string/to_string.hpp"
#include "nmtools/array/activations/softplus.hpp"
#include "nmtools/math.hpp"

namespace nmtools::view::fun
{
    /**
     * @brief Function object for mish ufunc
     * 
     */
    struct mish
    {
        template <typename T>
        nmtools_func_attribute
        NMTOOLS_UFUNC_CONSTEXPR
        auto operator()(const T& t) const
        {
            return t * math::tanh(softplus<>::eval(t));
        } // operator()
    }; // mish
} // namespace nmtools::view::fun

#if NMTOOLS_HAS_STRING

namespace nmtools::utils::impl
{
    template <auto...fmt_args>
    struct to_string_t<view::fun::mish,fmt_string_t<fmt_args...>>
    {
        using result_type = nmtools_string;

        auto operator()(view::fun::mish) const
        {
            nmtools_string str;

            str += "mish";

            return str;
        }
    };
}

#endif // NMTOOLS_HAS_STRING

namespace nmtools::view
{
    using mish_t = fun::mish;

    /**
     * @brief Create element-wise mish ufunc view
     * 
     * @tparam array_t 
     * @param array     input array
     * @return NMTOOLS_UFUNC_CONSTEXPR 
     */
    template <typename array_t>
    nmtools_func_attribute
    NMTOOLS_UFUNC_CONSTEXPR
    auto mish(const array_t& array)
    {
        return ufunc(mish_t{},array);
    } // mish
} // namespace nmtools::view

#endif // NMTOOLS_ARRAY_VIEW_ACTIVATIONS_MISH_HPP

#ifndef NMTOOLS_ARRAY_FUNCTIONAL_ACTIVATIONS_MISH_HPP
#define NMTOOLS_ARRAY_FUNCTIONAL_ACTIVATIONS_MISH_HPP

#include "nmtools/core/functor.hpp"
#include "nmtools/array/activations/mish.hpp"
#include "nmtools/array/ufunc/ufunc.hpp"

namespace nmtools::functional
{
    namespace fun
    {
        using mish = fun::unary_ufunc<view::mish_t>;
    }

    constexpr inline auto mish = functor_t{unary_fmap_t<fun::mish>{}};
} // namespace nmtools::functional


#endif // NMTOOLS_ARRAY_FUNCTIONAL_ACTIVATIONS_MISH_HPP

#ifndef NMTOOLS_ARRAY_ARRAY_ACTIVATIONS_MISH_HPP
#define NMTOOLS_ARRAY_ARRAY_ACTIVATIONS_MISH_HPP

#include "nmtools/array/activations/mish.hpp"
#include "nmtools/core/eval.hpp"

namespace nmtools::array
{
    template <typename output_t=none_t, typename context_t=none_t, typename resolver_t=eval_result_t<>,
        typename array_t>
    NMTOOLS_UFUNC_CONSTEXPR
    auto mish(const array_t& array,
        context_t&& context=context_t{}, output_t&& output=output_t{},meta::as_value<resolver_t> resolver=meta::as_value_v<resolver_t>)
    {
        auto a = view::mish(array);
        return eval(a
            ,nmtools::forward<context_t>(context)
            ,nmtools::forward<output_t>(output)
            ,resolver
        );
    } // mish
} // namespace nmtools::array


#endif // NMTOOLS_ARRAY_ARRAY_ACTIVATIONS_MISH_HPP