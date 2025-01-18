#ifndef NMTOOLS_ARRAY_VIEW_SOFTMAX_HPP
#define NMTOOLS_ARRAY_VIEW_SOFTMAX_HPP

#include "nmtools/core/alias.hpp"
#include "nmtools/array/ufuncs/exp.hpp"
#include "nmtools/array/ufuncs/add.hpp"
#include "nmtools/array/ufuncs/maximum.hpp"
#include "nmtools/array/ufuncs/subtract.hpp"
#include "nmtools/array/ufuncs/divide.hpp"

namespace nmtools::view
{
    /**
     * @brief Applies softmax function along specified axis
     * 
     * @tparam input_t 
     * @tparam axis_t 
     * @param input input array
     * @param axis  axis where softmax to be applied
     * @return constexpr auto 
     */
    template <typename input_t, typename axis_t>
    constexpr auto softmax(const input_t& input, axis_t axis)
    {
        auto a_input = view::aliased(input);
        // following pytorch, only allow index axis (index array axis not allowed)
        static_assert( meta::is_index_v<axis_t>
            , "unsupported softmax, expect axis to be index"
        );
        // NOTE: this follow https://cs231n.github.io/linear-classify/#softmax for numerical stability
        auto a = view::reduce_maximum(a_input,axis,/*dtype=*/None,/*initial=*/None,/*keepdims=*/True);
        auto b = view::subtract(a_input,a);
        auto c = view::exp(b);
        auto d = view::reduce_add(c,axis,/*dtype=*/None,/*initial=*/None,/*keepdims=*/True);
        return view::divide(c,d);
    } // softmax
} // namespace nmtools::view

#endif // NMTOOLS_ARRAY_VIEW_SOFTMAX_HPP

#ifndef NMTOOLS_ARRAY_FUNCTIONAL_SOFTMAX_HPP
#define NMTOOLS_ARRAY_FUNCTIONAL_SOFTMAX_HPP

#include "nmtools/core/functor.hpp"
#include "nmtools/array/ufuncs/maximum.hpp"
#include "nmtools/array/ufuncs/subtract.hpp"
#include "nmtools/array/ufuncs/exp.hpp"
#include "nmtools/array/ufuncs/add.hpp"
#include "nmtools/array/ufuncs/divide.hpp"
#include "nmtools/array/softmax.hpp"

namespace nmtools::functional
{
    constexpr inline auto softmax_fun = [](const auto&...args){
        return view::softmax(args...);
    };

    constexpr inline auto softmax = functor_t{unary_fmap_t<decltype(softmax_fun)>{softmax_fun}};

} // namespace nmtools::functional


#endif // NMTOOLS_ARRAY_FUNCTIONAL_SOFTMAX_HPP

#ifndef NMTOOLS_ARRAY_ARRAY_SOFTMAX_HPP
#define NMTOOLS_ARRAY_ARRAY_SOFTMAX_HPP

#include "nmtools/array/softmax.hpp"
#include "nmtools/core/eval.hpp"

namespace nmtools::array
{
    /**
     * @brief Eagerly computes softmax function along an axis.
     * 
     * @tparam output_t 
     * @tparam context_t=none_t 
     * @tparam input_t 
     * @tparam dim_t 
     * @param input     input array
     * @param dim       axis to operate softmax
     * @param context 
     * @param output 
     * @return constexpr auto 
     */
    template <typename output_t=none_t, typename context_t=none_t, typename resolver_t=eval_result_t<>,
        typename input_t, typename dim_t>
    constexpr auto softmax(const input_t& input, dim_t dim,
        context_t&& context=context_t{}, output_t&& output=output_t{},meta::as_value<resolver_t> resolver=meta::as_value_v<resolver_t>)
    {
        auto softmax_ = view::softmax(input,dim);
        return eval(softmax_
            ,nmtools::forward<context_t>(context)
            ,nmtools::forward<output_t>(output)
            ,resolver
        );
    } // softmax
} // namespace nmtools::array

#endif // NMTOOLS_ARRAY_ARRAY_SOFTMAX_HPP