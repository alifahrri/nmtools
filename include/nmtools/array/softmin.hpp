#ifndef NMTOOLS_ARRAY_VIEW_SOFTMIN_HPP
#define NMTOOLS_ARRAY_VIEW_SOFTMIN_HPP

#include "nmtools/array/softmax.hpp"
#include "nmtools/array/ufuncs/negative.hpp"

namespace nmtools::view
{
    /**
     * @brief Create a view that computes softmin function along an axis
     * 
     * @tparam input_t 
     * @tparam dim_t 
     * @param input     input array
     * @param dim       axis in which softmin to be computed on
     * @return constexpr auto 
     */
    template <typename input_t, typename dim_t>
    constexpr auto softmin(const input_t& input, dim_t dim)
    {
        auto input_ = view::negative(input);
        return view::softmax(input_,dim);
    } // softmin
} // namespace nmtools::view


#endif // NMTOOLS_ARRAY_VIEW_SOFTMIN_HPP

#ifndef NMTOOLS_ARRAY_FUNCTIONAL_SOFTMIN_HPP
#define NMTOOLS_ARRAY_FUNCTIONAL_SOFTMIN_HPP

#include "nmtools/core/functor.hpp"
#include "nmtools/array/ufuncs/negative.hpp"
#include "nmtools/array/softmax.hpp"
#include "nmtools/array/softmin.hpp"

namespace nmtools::functional
{
    constexpr inline auto softmin_fun = [](const auto&...args){
        return view::softmin(args...);
    };

    constexpr inline auto softmin = functor_t{unary_fmap_t<decltype(softmin_fun)>{{softmin_fun}}};
} // namespace nmtools::functional

#endif // NMTOOLS_ARRAY_FUNCTIONAL_SOFTMIN_HPP

#ifndef NMTOOLS_ARRAY_ARRAY_SOFTMIN_HPP
#define NMTOOLS_ARRAY_ARRAY_SOFTMIN_HPP

#include "nmtools/array/softmin.hpp"
#include "nmtools/core/eval.hpp"

namespace nmtools
{
    /**
     * @brief Eagerly computes softmin function along an axis.
     * 
     * @tparam output_t 
     * @tparam context_t=none_t 
     * @tparam input_t 
     * @tparam dim_t 
     * @param input     input array
     * @param dim       compute axis
     * @param context 
     * @param output 
     * @return constexpr auto 
     */
    template <typename output_t=none_t, typename context_t=none_t, typename resolver_t=eval_result_t<>,
        typename input_t, typename dim_t>
    constexpr auto softmin(const input_t& input, dim_t dim,
        context_t&& context=context_t{}, output_t&& output=output_t{},meta::as_value<resolver_t> resolver=meta::as_value_v<resolver_t>)
    {
        auto softmin_ = view::softmin(input,dim);
        return eval(softmin_
            ,nmtools::forward<context_t>(context)
            ,nmtools::forward<output_t>(output)
            ,resolver
        );
    } // softmin
} // namespace nmtools

#endif // NMTOOLS_ARRAY_ARRAY_SOFTMIN_HPP