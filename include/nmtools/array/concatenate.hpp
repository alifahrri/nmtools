#ifndef NMTOOLS_ARRAY_VIEW_CONCATENATE_HPP
#define NMTOOLS_ARRAY_VIEW_CONCATENATE_HPP

#include "nmtools/core/decorator.hpp"

#include "nmtools/index/concatenate.hpp"
#include "nmtools/utility/shape.hpp"

namespace nmtools::view
{
    template <typename lhs_array_t, typename rhs_array_t, typename axis_t>
    struct concatenate_t
    {
        using lhs_type = resolve_array_type_t<lhs_array_t>;
        using rhs_type = resolve_array_type_t<rhs_array_t>;
        using lhs_value_type = meta::get_element_type_t<lhs_array_t>;
        using rhs_value_type = meta::get_element_type_t<rhs_array_t>;
        using value_type = meta::common_type_t<lhs_value_type,rhs_value_type>;
        using array_type = nmtools_tuple<lhs_type,rhs_type>;
        using axis_type  = resolve_attribute_type_t<axis_t>;
        using lhs_shape_type = decltype(nmtools::shape<true>(meta::declval<lhs_array_t>()));
        using rhs_shape_type = decltype(nmtools::shape<true>(meta::declval<rhs_array_t>()));
        using lhs_size_type  = decltype(nmtools::size<true>(meta::declval<lhs_array_t>()));
        using rhs_size_type  = decltype(nmtools::size<true>(meta::declval<rhs_array_t>()));
        using shape_type = const meta::resolve_optype_t<index::shape_concatenate_t,lhs_shape_type,rhs_shape_type,axis_t,lhs_size_type,rhs_size_type>;

        // lhs_type  lhs;
        // rhs_type  rhs;
        array_type array;
        axis_type axis;
        shape_type shape_;

        constexpr concatenate_t(const lhs_array_t& lhs,  const rhs_array_t& rhs, const axis_t& axis_)
            : array({initialize<lhs_type>(lhs),initialize<rhs_type>(rhs)})
            , axis(init_attribute<axis_type>(axis_))
            , shape_(nmtools::get<1>(index::shape_concatenate(
                nmtools::shape<true>(lhs),
                nmtools::shape<true>(rhs),
                axis_,
                nmtools::size<true>(lhs),
                nmtools::size<true>(rhs)))
            )
        {}

        constexpr auto operands() const noexcept
        {
            return array_type{array};
        }

        constexpr auto attributes() const noexcept
        {
            return nmtools_tuple{axis};
        }
        
        constexpr auto shape() const
        {
            return shape_;
        } // shape

        constexpr auto dim() const
        {
            return len(shape());
        } // dim

        template <typename...size_types>
        constexpr auto operator()(size_types...indices) const
        {
            auto indices_ = pack_indices(indices...);
            const auto& [lhs, rhs] = array;
            // @todo do not always request shape! e.g. for fixed size array, or provide options to turn this off
            const auto ashape = detail::shape(lhs);
            const auto bshape = detail::shape(rhs);
            const auto [aflag, bflag, a_idx, b_idx] = index::concatenate(ashape,bshape,indices_,axis);
            // @todo better error handling
            nmtools_cassert ( aflag || bflag
                , "out of bound access"
            );
            // @todo maybe provide options/customization to select type casting
            using common_t = value_type;
            if (aflag)
                return static_cast<common_t>(detail::apply_at(lhs,a_idx));
            else
                return static_cast<common_t>(detail::apply_at(rhs,b_idx));
        } // operator()
    }; // concatenate_t

    /**
     * @brief Join two arrays along existing axis.
     * 
     * @tparam lhs_array_t 
     * @tparam rhs_array_t 
     * @tparam axis_t 
     * @param lhs lhs array
     * @param rhs rhs array
     * @param axis The axis along which the arrays will be joined. If axis is None, arrays are flattened before use.
     * @return constexpr auto 
     */
    template <typename lhs_array_t, typename rhs_array_t, typename axis_t>
    constexpr auto concatenate(const lhs_array_t& lhs, const rhs_array_t& rhs, axis_t axis)
    {
        if constexpr (meta::is_maybe_v<lhs_array_t>) {
            using lhs_type = meta::get_maybe_type_t<lhs_array_t>;
            using result_t = decltype(view::concatenate(meta::declval<lhs_type>(),rhs,axis));
            using return_t = meta::conditional_t<meta::is_maybe_v<result_t>,result_t,nmtools_maybe<result_t>>;
            return (lhs
                ? return_t{view::concatenate(*lhs,rhs,axis)}
                : return_t{meta::Nothing}
            );
        } else if constexpr (meta::is_maybe_v<rhs_array_t>) {
            using rhs_type = meta::get_maybe_type_t<rhs_array_t>;
            using result_t = decltype(view::concatenate(lhs,meta::declval<rhs_type>(),axis));
            using return_t = meta::conditional_t<meta::is_maybe_v<result_t>,result_t,nmtools_maybe<result_t>>;
            return (rhs
                ? return_t{(view::concatenate(lhs,*rhs,axis))}
                : return_t{meta::Nothing}
            );
        } else {
            auto ashape = shape(lhs);
            auto bshape = shape(rhs);
            [[maybe_unused]] const auto [success, shape] = index::shape_concatenate(ashape,bshape,axis);
            // TODO: use nmtools_assert macro
            nmtools_cassert (success
                , "unsupported concatenate, mismatched shape"
            );
            return decorator_t<concatenate_t,lhs_array_t,rhs_array_t,axis_t>{{lhs,rhs,axis}};
        }
    } // concatenate
} // namespace nmtools::view

namespace nmtools::meta
{
    /**
     * @brief Infer the element type of concatenate view.
     * 
     * @tparam lhs_t 
     * @tparam rhs_t 
     * @tparam axis_t 
     */
    template <typename lhs_t, typename rhs_t, typename axis_t>
    struct get_element_type< view::decorator_t< view::concatenate_t, lhs_t, rhs_t, axis_t > >
    {
        // by default, get_element_type should accept type with value_type
        // but fail on this case.
        using view_type = view::decorator_t< view::concatenate_t, lhs_t, rhs_t, axis_t >;
        using type = typename view_type::value_type;
    }; // get_element_type

    template <typename lhs_array_t, typename rhs_array_t, typename axis_t>
    struct is_ndarray< 
        view::decorator_t<
            view::concatenate_t, lhs_array_t, rhs_array_t, axis_t
        >
    >
    {
        static constexpr auto value = is_ndarray_v<lhs_array_t> && is_ndarray_v<rhs_array_t>;
    }; // is_ndarray
} // namespace nmtools::view

#endif // NMTOOLS_ARRAY_VIEW_CONCATENATE_HPP

#ifndef NMTOOLS_ARRAY_FUNCTIONAL_CONCATENATE_HPP
#define NMTOOLS_ARRAY_FUNCTIONAL_CONCATENATE_HPP

#include "nmtools/core/functor.hpp"
#include "nmtools/array/concatenate.hpp"

namespace nmtools::functional
{
    namespace fun
    {
        struct concatenate_t
        {
            template <typename...args_t>
            constexpr auto operator()(const args_t&...args) const
            {
                return view::concatenate(args...);
            }
        };
    }

    constexpr inline auto concatenate = functor_t{binary_fmap_t<fun::concatenate_t>{}};

    template <typename...args_t>
    struct get_function_t<
        view::decorator_t<
            view::concatenate_t, args_t...
        >
    > {
        using view_type = view::decorator_t<
            view::concatenate_t, args_t...
        >;

        view_type view;

        constexpr auto operator()() const noexcept
        {
            return concatenate[view.axis];
        }
    };
} // namespace nmtools::functional


#endif // NMTOOLS_ARRAY_FUNCTIONAL_CONCATENATE_HPP

#ifndef NMTOOLS_ARRAY_ARRAY_CONCATENATE_HPP
#define NMTOOLS_ARRAY_ARRAY_CONCATENATE_HPP

#include "nmtools/array/concatenate.hpp"
#include "nmtools/core/eval.hpp"

namespace nmtools::array
{
    /**
     * @brief Eagerly concatenate two array.
     * 
     * @tparam output_t 
     * @tparam context_t 
     * @tparam lhs_array_t 
     * @tparam rhs_array_t 
     * @tparam axis_t 
     * @param lhs       input array
     * @param rhs       input array
     * @param axis      the axis along which the arrays will be joined. if None, arrays are flattened before joined.
     * @param context   evaluation context
     * @param output 
     * @return constexpr auto 
     */
    template <typename output_t=none_t, typename context_t=none_t, typename resolver_t=eval_result_t<>,
        typename lhs_array_t, typename rhs_array_t, typename axis_t>
    constexpr auto concatenate(const lhs_array_t& lhs, const rhs_array_t& rhs, axis_t axis,
        context_t&& context=context_t{}, output_t&& output=output_t{},meta::as_value<resolver_t> resolver=meta::as_value_v<resolver_t>)
    {
        auto concatenated = view::concatenate(lhs,rhs,axis);
        return eval(concatenated
            ,nmtools::forward<context_t>(context)
            ,nmtools::forward<output_t>(output)
            ,resolver
        );
    } // concatenate
} // namespace nmtools::array

#endif // NMTOOLS_ARRAY_ARRAY_CONCATENATE_HPP