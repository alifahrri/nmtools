#ifndef NMTOOLS_ARRAY_VIEW_STACK_HPP
#define NMTOOLS_ARRAY_VIEW_STACK_HPP

#include "nmtools/array/concatenate.hpp"
#include "nmtools/array/expand_dims.hpp"

namespace nmtools::view
{
    template <typename lhs_t, typename rhs_t, typename axis_t=meta::ct<0>>
    constexpr auto stack(const lhs_t& lhs, const rhs_t& rhs, axis_t axis=axis_t{})
    {
        auto aliased = view::aliased(lhs,rhs);
        auto a_lhs = nmtools::get<0>(aliased);
        auto a_rhs = nmtools::get<1>(aliased);
        return view::concatenatev2(
              view::expand_dims(a_lhs,axis)
            , view::expand_dims(a_rhs,axis)
            , axis
        );
    }
} // namespace nmtools::view

#endif // NMTOOLS_ARRAY_VIEW_STACK_HPP

#ifndef NMTOOLS_ARRAY_FUNCTIONAL_STACK_HPP
#define NMTOOLS_ARRAY_FUNCTIONAL_STACK_HPP

#include "nmtools/core/functor.hpp"
#include "nmtools/core/indexing.hpp"
#include "nmtools/array/stack.hpp"

namespace nmtools::functional
{
    namespace fun
    {
        struct stack_t
        {
            template <typename...args_t>
            constexpr auto operator()(const args_t&...args) const
            {
                return view::stack(args...);
            }
        };
    }

    constexpr inline auto stack = functor_t{binary_fmap_t<fun::stack_t>{}};
} // namespace nmtools::functional

#endif // NMTOOLS_ARRAY_FUNCTIONAL_STACK_HPP

#ifndef NMTOOLS_ARRAY_ARRAY_STACK_HPP
#define NMTOOLS_ARRAY_ARRAY_STACK_HPP

#include "nmtools/array/stack.hpp"
#include "nmtools/core/eval.hpp"

namespace nmtools::array
{
    template <typename output_t=none_t, typename context_t=none_t, typename resolver_t=eval_result_t<>,
        typename lhs_array_t, typename rhs_array_t, typename axis_t=meta::ct<0>>
    constexpr auto stack(const lhs_array_t& lhs, const rhs_array_t& rhs, axis_t axis=axis_t{}
        , context_t&& context=context_t{}, output_t&& output=output_t{},meta::as_value<resolver_t> resolver=meta::as_value_v<resolver_t>)
    {
        auto result = view::stack(lhs,rhs,axis);
        return eval(result
            , nmtools::forward<context_t>(context)
            , nmtools::forward<output_t>(output)
            , resolver
        );
    } // stack
} // namespace nmtools::array

#endif // NMTOOLS_ARRAY_ARRAY_STACK_HPP