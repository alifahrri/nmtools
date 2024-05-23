#ifndef NMTOOLS_ARRAY_VIEW_WHERE_HPP
#define NMTOOLS_ARRAY_VIEW_WHERE_HPP

#include "nmtools/array/utility/apply_at.hpp"
#include "nmtools/array/view/decorator.hpp"
#include "nmtools/array/view/broadcast_arrays.hpp"
#include "nmtools/utils/isequal.hpp"
#include "nmtools/meta.hpp"

namespace nmtools::view
{
    template <typename condition_t, typename x_t, typename y_t>
    struct where_t
    {
        // deduce array types, copy if view, take const ref if concrete array
        using condition_type = meta::fwd_operand_t<condition_t>;
        using x_type = meta::fwd_operand_t<x_t>;
        using y_type = meta::fwd_operand_t<y_t>;
        // needed by decorator_t, also used to deduce underlying array type
        using array_type = nmtools_tuple<condition_type,x_type,y_type>;
        // result type, use common type for now
        using element_type = meta::common_type_t<
            meta::get_element_type_t<condition_t>,
            meta::get_element_type_t<x_t>, meta::get_element_type_t<y_t>
        >;

        array_type array;

        constexpr where_t(const condition_t& condition, const x_t& x, const y_t& y)
            : array{fwd_operand(condition), fwd_operand(x), fwd_operand(y)}
        {}

        constexpr auto operands() const noexcept
        {
            return array_type{array};
        }

        constexpr auto attributes() const noexcept
        {
            return nmtools_tuple{};
        }
        
        constexpr auto shape() const
        {
            return detail::shape(::nmtools::get<0>(array));
        } // shape

        constexpr auto dim() const
        {
            return detail::dim(::nmtools::get<0>(array));
        } // dim

        template <typename...size_types>
        constexpr auto operator()(size_types...indices) const
        {
            auto indices_ = pack_indices(indices...);
            auto c  = apply_at(nmtools::get<0>(array), indices_);
            return static_cast<element_type>(c ?
                  apply_at(nmtools::get<1>(array), indices_)
                : apply_at(nmtools::get<2>(array), indices_)
            );
        } // operator()
    }; // where_t

    /**
     * @brief Return elements chosen from x or y depending on condition.
     * 
     * @tparam condition_t 
     * @tparam x_t 
     * @tparam y_t 
     * @param condition 
     * @param x Array in which its elements are to be selected if corresponding condition is true.
     * @param y Array in which its elements are to be selected if corresponding condition is false.
     * @return constexpr auto 
     */
    template <typename condition_t, typename x_t, typename y_t>
    constexpr auto where(const condition_t& condition, const x_t& x, const y_t& y)
    {
        auto broadcasted = broadcast_arrays(condition, x, y);
        if constexpr (meta::is_maybe_v<decltype(broadcasted)>) {
            using bcondition_t = meta::remove_cvref_t<decltype(nmtools::get<0>(*broadcasted))>;
            using bx_t = meta::remove_cvref_t<decltype(nmtools::get<1>(*broadcasted))>;
            using by_t = meta::remove_cvref_t<decltype(nmtools::get<2>(*broadcasted))>;
            using result_t = decorator_t<where_t,bcondition_t,bx_t,by_t>;
            using return_t = nmtools_maybe<result_t>;
            return (broadcasted?
                return_t{result_t{{
                      nmtools::get<0>(*broadcasted)
                    , nmtools::get<1>(*broadcasted)
                    , nmtools::get<2>(*broadcasted)}}}
                : return_t{meta::Nothing}
            );
        } else {
            auto condition = nmtools::get<0>(broadcasted);
            auto x = nmtools::get<1>(broadcasted);
            auto y = nmtools::get<2>(broadcasted);
            using bcondition_t = meta::remove_cvref_t<decltype(condition)>;
            using bx_t = meta::remove_cvref_t<decltype(x)>;
            using by_t = meta::remove_cvref_t<decltype(y)>;

            return decorator_t<where_t,bcondition_t,bx_t,by_t>{{condition,x,y}};
        }
    } // where
} // namespace nmtools::view

namespace nmtools::meta
{
    template <typename condition_t, typename x_t, typename y_t>
    struct get_element_type< view::decorator_t<view::where_t, condition_t, x_t, y_t> >
    {
        using view_t = view::where_t<condition_t,x_t,y_t>;
        using type = typename view_t::element_type;
    }; // get_element_type

    template <typename condition_t, typename x_t, typename y_t>
    struct hybrid_ndarray_max_size< view::decorator_t<view::where_t, condition_t, x_t, y_t> >
    {
        static inline constexpr auto value = [](){
            if constexpr (is_hybrid_ndarray_v<condition_t> && is_hybrid_ndarray_v<x_t> && is_hybrid_ndarray_v<y_t>) {
                auto cmax = hybrid_ndarray_max_size_v<condition_t>;
                auto xmax = hybrid_ndarray_max_size_v<x_t>;
                auto ymax = hybrid_ndarray_max_size_v<y_t>;
                auto max = cmax;
                max = max > xmax ? max : xmax;
                max = max > ymax ? max : ymax;
                return max;
            } else {
                return detail::Fail;
            }
        }();
        using value_type = remove_cvref_t<decltype(value)>;
        using type = value_type;
    }; // hybrid_ndarray_max_size

    template <typename condition_t, typename x_t, typename y_t>
    struct fixed_dim<
        view::decorator_t<view::where_t, condition_t, x_t, y_t>
    >
    {
        static inline constexpr auto value = [](){
            if constexpr (is_fixed_dim_ndarray_v<condition_t> && is_fixed_dim_ndarray_v<x_t> && is_fixed_dim_ndarray_v<y_t>) {
                constexpr auto cdim = fixed_dim_v<condition_t>;
                constexpr auto xdim = fixed_dim_v<x_t>;
                constexpr auto ydim = fixed_dim_v<y_t>;
                if constexpr ( (cdim == xdim) && (xdim == ydim)) {
                    return cdim;
                } else {
                    return detail::Fail;
                }
            } else {
                return detail::Fail;
            }
        }();
        using value_type = remove_cvref_t<decltype(value)>;
        using type = value_type;
    }; // fixed_dim

    template <typename condition_t, typename x_t, typename y_t>
    struct fixed_ndarray_shape< view::where_t< condition_t, x_t, y_t> >
    {
        static inline constexpr auto value = [](){
            if constexpr (is_fixed_size_ndarray_v<condition_t> && is_fixed_size_ndarray_v<x_t> && is_fixed_size_ndarray_v<y_t>) {
                using utils::isequal;
                constexpr auto cshape = fixed_ndarray_shape_v<condition_t>;
                constexpr auto xshape = fixed_ndarray_shape_v<x_t>;
                constexpr auto yshape = fixed_ndarray_shape_v<y_t>;
                if constexpr (isequal(cshape,xshape) && isequal(xshape,yshape)) {
                    return cshape;
                } else {
                    return detail::Fail;
                }
            } else {
                return detail::Fail;
            }
        }();
        using value_type = remove_cvref_t<decltype(value)>;
        using type = value_type;
    }; // fixed_ndarray_shape

    template <typename condition_t, typename x_t, typename y_t>
    struct is_ndarray< view::decorator_t< view::where_t, condition_t, x_t, y_t >>
    {
        static constexpr auto value = is_ndarray_v<condition_t> && is_ndarray_v<x_t> && is_ndarray_v<y_t>;
    };
} // namespace nmtools::meta

#endif // NMTOOLS_ARRAY_VIEW_WHERE_HPP