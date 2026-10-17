#ifndef NMTOOLS_ARRAY_FUNCTIONAL_RESHAPE_HPP
#define NMTOOLS_ARRAY_FUNCTIONAL_RESHAPE_HPP

#include "nmtools/core/functor.hpp"
#include "nmtools/core/indexing.hpp"
#include "nmtools/core/reshape.hpp"

namespace nmtools::functional
{
    namespace fun
    {
        struct reshape_t
        {
            template <typename...args_t>
            constexpr auto operator()(const args_t&...args) const
            {
                return view::reshape(args...);
            }
        };
    }

    constexpr inline auto reshape = functor_t{unary_fmap_t<fun::reshape_t>{}};
} // namespace nmtools::functional

#endif //NMTOOLS_ARRAY_FUNCTIONAL_RESHAPE_HPP

#ifndef NMTOOLS_ARRAY_ARRAY_RESHAPE_HPP
#define NMTOOLS_ARRAY_ARRAY_RESHAPE_HPP

#include "nmtools/core/reshape.hpp"
#include "nmtools/core/eval.hpp"

namespace nmtools
{
    /**
     * @brief Eagerly reshape an array. Note that this will copy array by default.
     *
     * The result follows numpy's default C-order semantics: elements are
     * reread from the source in logical row-major order and materialized
     * with canonical row-major striding. There is deliberately no order
     * parameter; other layouts are expressed through explicit strides,
     * which compose with every kind of striding (column-major, blocked,
     * transposed), for example an F-order view over the same buffer:
     * `view::stride(x, shape, index::compute_col_major_strides(shape))`.
     *
     * @tparam output_t 
     * @tparam context_t 
     * @tparam array_t 
     * @tparam shape_t 
     * @param array     input array
     * @param new_shape desired new shape
     * @param context   evaluation context
     * @param output 
     * @return constexpr auto 
     */
    template <typename output_t=none_t, typename context_t=default_context_t<>,
        typename array_t, typename shape_t>
    constexpr auto reshape(const array_t& array, const shape_t& new_shape,
        context_t&& context=context_t{}, output_t&& output=output_t{})
    {
        auto reshaped = view::reshape(array, new_shape);
        return eval(reshaped
            ,nmtools::forward<context_t>(context)
            ,nmtools::forward<output_t>(output)
        );
    } // reshape
} // namespace nmtools

#endif // NMTOOLS_ARRAY_ARRAY_RESHAPE_HPP