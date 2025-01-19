#ifndef NMTOOLS_ARRAY_FUNCTIONAL_BROADCAST_TO_HPP
#define NMTOOLS_ARRAY_FUNCTIONAL_BROADCAST_TO_HPP

#include "nmtools/core/functor.hpp"
#include "nmtools/core/indexing.hpp"
#include "nmtools/core/broadcast_to.hpp"

namespace nmtools::functional
{
    namespace fun
    {
        struct broadcast_to_t
        {
            template <typename...args_t>
            constexpr auto operator()(const args_t&...args) const
            {
                return view::broadcast_to(args...);
            }
        };
    } // namespace fun

    constexpr inline auto broadcast_to = functor_t{unary_fmap_t<fun::broadcast_to_t>{}};
} // namespace nmtools::functional

#endif // NMTOOLS_ARRAY_FUNCTIONAL_BROADCAST_TO_HPP

#ifndef NMTOOLS_ARRAY_ARRAY_BROADCAST_TO_HPP
#define NMTOOLS_ARRAY_ARRAY_BROADCAST_TO_HPP

#include "nmtools/core/eval.hpp"
#include "nmtools/array/broadcast_to.hpp"
#include "nmtools/constants.hpp"

namespace nmtools::array
{
    template <typename output_t=none_t, typename context_t=none_t, typename resolver_t=eval_result_t<>,
        typename array_t, typename shape_t>
    constexpr auto broadcast_to(const array_t& array, shape_t& shape,
        context_t&& context=context_t{}, output_t&& output=output_t{},meta::as_value<resolver_t> resolver=meta::as_value_v<resolver_t>)
    {
        auto broadcasted = view::broadcast_to(array,shape);
        return eval(broadcasted
            ,nmtools::forward<context_t>(context)
            ,nmtools::forward<output_t>(output)
            ,resolver
        );
    } // broadcast_to
} // namespace nmtools::array

#endif // NMTOOLS_ARRAY_ARRAY_BROADCAST_TO_HPP