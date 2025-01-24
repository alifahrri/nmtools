#ifndef NMTOOLS_ARRAY_VIEW_SQUEEZE_HPP
#define NMTOOLS_ARRAY_VIEW_SQUEEZE_HPP

#include "nmtools/meta.hpp"
#include "nmtools/array/reshape.hpp"
#include "nmtools/utility/shape.hpp"
#include "nmtools/index/squeeze.hpp"

namespace nmtools::view
{
    /**
     * @brief remove single dimensional entry from array
     * 
     * @tparam array_t 
     * @param array 
     * @return constexpr auto 
     */
    template <typename array_t>
    constexpr auto squeeze(const array_t& array)
    {
        auto src_shape = shape<true>(array);
        auto dst_shape = index::shape_squeeze(src_shape);
        return view::reshape(array,dst_shape);
    } // squeeze
} // namespace nmtools::view

#endif // NMTOOLS_ARRAY_VIEW_SQUEEZE_HPP

#ifndef NMTOOLS_ARRAY_FUNCTIONAL_SQUEEZE_HPP
#define NMTOOLS_ARRAY_FUNCTIONAL_SQUEEZE_HPP

#include "nmtools/core/functor.hpp"
#include "nmtools/core/indexing.hpp"
#include "nmtools/array/squeeze.hpp"

namespace nmtools::functional
{
    namespace fun
    {
        struct squeeze_t
        {
            template <typename...args_t>
            constexpr auto operator()(const args_t&...args) const
            {
                return view::squeeze(args...);
            }
        };
    }

    constexpr inline auto squeeze = functor_t{unary_fmap_t<fun::squeeze_t>{}};
} // namespace nmtools::functional

#endif // NMTOOLS_ARRAY_FUNCTIONAL_SQUEEZE_HPP

#ifndef NMTOOLS_ARRAY_ARRAY_SQUEEZE_HPP
#define NMTOOLS_ARRAY_ARRAY_SQUEEZE_HPP

#include "nmtools/array/squeeze.hpp"
#include "nmtools/core/eval.hpp"

namespace nmtools::array
{
    /**
     * @brief Eagerly squeeze an arrray. Removes single dimensions from the array.
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
    constexpr auto squeeze(const array_t& array,
        context_t&& context=context_t{}, output_t&& output=output_t{},meta::as_value<resolver_t> resolver=meta::as_value_v<resolver_t>)
    {
        auto squeezed = view::squeeze(array);
        return eval(squeezed
            ,nmtools::forward<context_t>(context)
            ,nmtools::forward<output_t>(output)
            ,resolver
        );
    } // reshape
} // namespace nmtools::array

#endif // NMTOOLS_ARRAY_ARRAY_SQUEEZE_HPP