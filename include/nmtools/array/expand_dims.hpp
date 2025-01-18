#ifndef NMTOOLS_ARRAY_VIEW_EXPAND_DIMS_HPP
#define NMTOOLS_ARRAY_VIEW_EXPAND_DIMS_HPP

#include "nmtools/array/index/expand_dims.hpp"
#include "nmtools/array/reshape.hpp"
#include "nmtools/utility/shape.hpp"

namespace nmtools::view
{
    /**
     * @brief expand the shape of an array
     * 
     * @tparam array_t array_like
     * @tparam axis_t integer or array of integer
     * @param array input array
     * @param axis Position in the expanded axes where the new axis (or axes) is placed.
     * @return constexpr auto expand_dims view
     */
    template <typename array_t, typename axis_t>
    constexpr auto expand_dims(const array_t& array, const axis_t& axis)
    {
        auto src_shape = shape<true>(array);
        auto dst_shape = index::shape_expand_dims(src_shape,axis);
        return view::reshape(array,dst_shape);
    } // expand_dims

} // namespace nmtools::view

#endif // NMTOOLS_ARRAY_VIEW_EXPAND_DIMS_HPP

#ifndef NMTOOLS_ARRAY_FUNCTIONAL_EXPAND_DIMS_HPP
#define NMTOOLS_ARRAY_FUNCTIONAL_EXPAND_DIMS_HPP

#include "nmtools/core/functor.hpp"
#include "nmtools/array/indexing.hpp"
#include "nmtools/array/expand_dims.hpp"

namespace nmtools::functional
{
    namespace fun
    {
        struct expand_dims_t
        {
            template <typename...args_t>
            constexpr auto operator()(const args_t&...args) const
            {
                return view::expand_dims(args...);
            }
        };
    }

    constexpr inline auto expand_dims = functor_t{unary_fmap_t<fun::expand_dims_t>{}};
} // namespace nmtools::functional


#endif // NMTOOLS_ARRAY_FUNCTIONAL_EXPAND_DIMS_HPP

#ifndef NMTOOLS_ARRAY_ARRAY_EXPAND_DIMS_HPP
#define NMTOOLS_ARRAY_ARRAY_EXPAND_DIMS_HPP

#include "nmtools/array/expand_dims.hpp"
#include "nmtools/core/eval.hpp"

namespace nmtools::array
{
    /**
     * @brief Eagerly expand the shape of an array.
     * 
     * @tparam output_t 
     * @tparam context_t 
     * @tparam array_t 
     * @tparam axis_t 
     * @param array     input array
     * @param axis      position in the expanded axes where the new axis (or axes) is placed.
     * @param context   evaluation context
     * @param output 
     * @return constexpr auto 
     */
    template <typename output_t=none_t, typename context_t=none_t, typename resolver_t=eval_result_t<>,
        typename array_t, typename axis_t>
    constexpr auto expand_dims(const array_t& array, axis_t axis,
        context_t&& context=context_t{}, output_t&& output=output_t{},meta::as_value<resolver_t> resolver=meta::as_value_v<resolver_t>)
    {
        auto expanded = view::expand_dims(array,axis);
        return eval(expanded
            ,nmtools::forward<context_t>(context)
            ,nmtools::forward<output_t>(output)
            ,resolver
        );
    } // expand_dims
} // namespace nmtools::array

#endif // NMTOOLS_ARRAY_ARRAY_EXPAND_DIMS_HPP