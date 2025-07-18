#ifndef NMTOOLS_ARRAY_INDEX_HSTACK_HPP
#define NMTOOLS_ARRAY_INDEX_HSTACK_HPP

#include "nmtools/meta.hpp"
#include "nmtools/utility/shape.hpp"

namespace nmtools::index
{
    struct hstack_axis_t {};

    template <typename lhs_shape_t, typename rhs_shape_t>
    constexpr auto hstack_axis([[maybe_unused]] const lhs_shape_t& lhs_shape, const rhs_shape_t&)
    {
        using result_t = meta::resolve_optype_t<hstack_axis_t,lhs_shape_t,rhs_shape_t>;

        auto result = result_t {};

        if constexpr (!meta::is_constant_index_v<result_t>) {
            auto lhs_dim = len(lhs_shape);
            result = ((lhs_dim == 1) ? 0 : 1);
        }
        
        return result;
    }
} // namespace nmtools::index

namespace nmtools::meta
{
    namespace error
    {
        template <typename...>
        struct HSTACK_AXIS_UNSUPPORTED : detail::fail_t {};
    }

    template <typename lhs_shape_t, typename rhs_shape_t>
    struct resolve_optype<void,index::hstack_axis_t,lhs_shape_t,rhs_shape_t>
    {
        static constexpr auto vtype = [](){
            constexpr auto lhs_dim  = len_v<lhs_shape_t>;
            constexpr auto rhs_dim  = len_v<rhs_shape_t>;
            if constexpr ((lhs_dim > 0) && (lhs_dim == rhs_dim)) {
                using type = ct<((lhs_dim == 1) ? 0 : 1)>;
                return as_value_v<type>;
            } else if constexpr (is_index_array_v<lhs_shape_t>
                && is_index_array_v<rhs_shape_t>
            ) {
                using type = nm_size_t;
                return as_value_v<type>;
            } else {
                using type = error::HSTACK_AXIS_UNSUPPORTED<lhs_shape_t,rhs_shape_t>;
                return as_value_v<type>;
            }
        }();
        using type = type_t<decltype(vtype)>;
    };
} // namespace nmtools::meta

#endif // NMTOOLS_ARRAY_INDEX_HSTACK_HPP

#ifndef NMTOOLS_ARRAY_VIEW_HSTACK_HPP
#define NMTOOLS_ARRAY_VIEW_HSTACK_HPP

#include "nmtools/meta.hpp"
#include "nmtools/array/concatenate.hpp"

namespace nmtools::view
{
    template <typename lhs_t, typename rhs_t>
    constexpr auto hstack(const lhs_t& lhs, const rhs_t& rhs)
    {
        auto axis = index::hstack_axis(
              shape<true>(lhs)
            , shape<true>(rhs)
        );
        return view::concatenate(lhs,rhs,axis);
    }
} // namespace nmtools::view

#endif // NMTOOLS_ARRAY_VIEW_HSTACK_HPP

#ifndef NMTOOLS_ARRAY_FUNCTIONAL_HSTACK_HPP
#define NMTOOLS_ARRAY_FUNCTIONAL_HSTACK_HPP

#include "nmtools/core/functor.hpp"
#include "nmtools/core/indexing.hpp"
#include "nmtools/array/hstack.hpp"

namespace nmtools::functional
{
    namespace fun
    {
        struct hstack_t
        {
            template <typename...args_t>
            constexpr auto operator()(const args_t&...args) const
            {
                return view::hstack(args...);
            }
        };
    }

    constexpr inline auto hstack = functor_t{binary_fmap_t<fun::hstack_t>{}};
} // namespace nmtools::functional

#endif // NMTOOLS_ARRAY_FUNCTIONAL_HSTACK_HPP

#ifndef NMTOOLS_ARRAY_ARRAY_HSTACK_HPP
#define NMTOOLS_ARRAY_ARRAY_HSTACK_HPP

#include "nmtools/array/hstack.hpp"
#include "nmtools/core/eval.hpp"

namespace nmtools
{
    template <typename output_t=none_t, typename context_t=none_t, typename resolver_t=eval_result_t<>,
        typename lhs_array_t, typename rhs_array_t>
    constexpr auto hstack(const lhs_array_t& lhs, const rhs_array_t& rhs,
        context_t&& context=context_t{}, output_t&& output=output_t{},meta::as_value<resolver_t> resolver=meta::as_value_v<resolver_t>)
    {
        auto result = view::hstack(lhs,rhs);
        return eval(result
            , nmtools::forward<context_t>(context)
            , nmtools::forward<output_t>(output)
            , resolver
        );
    } // hstack
} // namespace nmtools

#endif // NMTOOLS_ARRAY_ARRAY_HSTACK_HPP