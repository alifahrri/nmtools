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

namespace nmtools::array
{
    /**
     * @brief Eagerly reshape an array. Note that this will copy array by default.
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
    template <typename output_t=none_t, typename context_t=none_t, typename resolver_t=eval_result_t<>,
        typename array_t, typename shape_t>
    constexpr auto reshape(const array_t& array, const shape_t& new_shape,
        context_t&& context=context_t{}, output_t&& output=output_t{},meta::as_value<resolver_t> resolver=meta::as_value_v<resolver_t>)
    {
        auto reshaped = view::reshape(array, new_shape);
        return eval(reshaped
            ,nmtools::forward<context_t>(context)
            ,nmtools::forward<output_t>(output)
            ,resolver
        );
    } // reshape
} // namespace nmtools::array

#endif // NMTOOLS_ARRAY_ARRAY_RESHAPE_HPP