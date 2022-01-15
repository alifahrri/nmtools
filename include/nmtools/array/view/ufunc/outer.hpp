#ifndef NMTOOLS_ARRAY_VIEW_UFUNC_OUTER_HPP
#define NMTOOLS_ARRAY_VIEW_UFUNC_OUTER_HPP

#include "nmtools/meta.hpp"
#include "nmtools/array/view/ref.hpp"
#include "nmtools/array/utility/apply_at.hpp"
#include "nmtools/array/view/decorator.hpp"
#include "nmtools/array/view/slice.hpp"
#include "nmtools/array/view/flatten.hpp"
#include "nmtools/array/view/broadcast_arrays.hpp"
#include "nmtools/array/index/outer.hpp"
#include "nmtools/array/index/remove_dims.hpp"
#include "nmtools/array/index/where.hpp"
#include "nmtools/array/index/sum.hpp"
#include "nmtools/array/shape.hpp"
#include "nmtools/array/dtypes.hpp"
#include "nmtools/array/ndarray.hpp"
#include "nmtools/array/eval.hpp"
#include "nmtools/constants.hpp"

#include "nmtools/array/view/ufunc/detail.hpp"

namespace nmtools::view
{
    /**
     * @brief Type constructor for outer ufuncs.
     * 
     * Apply op to pairs of element of lhs and rhs.
     *
     * @tparam op_t 
     * @tparam lhs_t 
     * @tparam rhs_t 
     */
    template <typename op_t, typename lhs_t, typename rhs_t>
    struct outer_t
    {
        using operands_type = detail::get_operands_type_t<lhs_t,rhs_t>;
        using array_type = operands_type;
        using op_type = op_t;
        using lhs_element_type = meta::get_element_type_t<lhs_t>;
        using rhs_element_type = meta::get_element_type_t<rhs_t>;
        using result_type = detail::get_ufunc_result_type_t<op_t,lhs_element_type,rhs_element_type>;

        op_type op;
        operands_type operands;

        // the following is needed because cant use view::initialize<...>
        // can't handle tuple yet
        static constexpr auto initialize_operands(const lhs_t& lhs, const rhs_t& rhs)
        {
            using op_lhs_t = meta::at_t<operands_type,0>;
            using op_rhs_t = meta::at_t<operands_type,1>;
            if constexpr (meta::is_pointer_v<op_lhs_t> && meta::is_pointer_v<op_rhs_t>) {
                return operands_type{&lhs,&rhs};
            } else if constexpr (meta::is_pointer_v<op_lhs_t>) {
                return operands_type{&lhs,rhs};
            } else if constexpr (meta::is_pointer_v<op_rhs_t>) {
                return operands_type{lhs,&rhs};
            } else {
                return operands_type{lhs,rhs};
            }
        } // initialize_operands

        constexpr outer_t(op_type op, const lhs_t& lhs, const rhs_t& rhs)
            : op(op), operands(initialize_operands(lhs,rhs)) {}
        
        constexpr auto shape() const
        {
            auto ashape = detail::shape(nmtools::get<0>(operands));
            auto bshape = detail::shape(nmtools::get<1>(operands));
            return index::shape_outer(ashape,bshape);
        } // shape

        constexpr auto dim() const
        {
            return len(shape());
        } // dim

        template <typename...size_types>
        constexpr auto operator()(size_types...indices) const
        {
            // here we directly provide operator() to actually performing operations,
            // instead of returning (transformed) index only
            auto indices_ = pack_indices(indices...);
            const auto& a = nmtools::get<0>(operands);
            const auto& b = nmtools::get<1>(operands);
            auto ashape = detail::shape(a);
            auto bshape = detail::shape(b);
            const auto [aidx, bidx] = index::outer(indices_,ashape,bshape);
            return op(view::detail::apply_at(a,aidx),view::detail::apply_at(b,bidx));
        } // operator()
    }; // outer_t
} // namespace nmtools::view

namespace nmtools::meta
{

    /**
     * @brief Compile-time shape inference for outer ufunc.
     * 
     * @tparam op_t 
     * @tparam lhs_t 
     * @tparam rhs_t 
     */
    template <typename op_t, typename lhs_t, typename rhs_t>
    struct fixed_ndarray_shape<
        view::outer_t< op_t, lhs_t, rhs_t >
    >
    {
        static inline constexpr auto value = [](){
            if constexpr (is_fixed_size_ndarray_v<lhs_t> && is_fixed_size_ndarray_v<rhs_t>) {
                constexpr auto lhs_shape = fixed_ndarray_shape_v<lhs_t>;
                constexpr auto rhs_shape = fixed_ndarray_shape_v<rhs_t>;
                return index::shape_outer(lhs_shape,rhs_shape);
            } else {
                return detail::fail_t{};
            }
        }();
        using value_type = remove_cvref_t<decltype(value)>;
    }; // fixed_ndarray_shape

    /**
     * @brief Infer the fixed dim for outer view.
     *
     * Return Fail when dimension of the view is not known at compile-time.
     * 
     * @tparam op_t 
     * @tparam lhs_t 
     * @tparam rhs_t 
     */
    template <typename op_t, typename lhs_t, typename rhs_t>
    struct fixed_dim<
        view::decorator_t< view::outer_t, op_t, lhs_t, rhs_t >
    >
    {
        static constexpr auto value = [](){
            if constexpr (
                   is_fixed_dim_ndarray_v<lhs_t>
                && is_fixed_dim_ndarray_v<rhs_t>
            ) {
                return fixed_dim_v<lhs_t> + fixed_dim_v<rhs_t>;
            } else {
                return detail::Fail;
            }
        }();
        using value_type = detail::fail_to_void_t<remove_cvref_t<decltype(value)>>;
        using type = value_type;
    };

    /**
     * @brief Infer maximum size (of hybrid ndarray) for outer view.
     * 
     * Return Fail when the view is not hybrid ndarray.
     * 
     * @tparam op_t 
     * @tparam lhs_t 
     * @tparam rhs_t 
     */
    template <typename op_t, typename lhs_t, typename rhs_t>
    struct hybrid_ndarray_max_size<
        view::decorator_t< view::outer_t, op_t, lhs_t, rhs_t >
    >
    {
        static constexpr auto value = [](){
            if constexpr (
                   is_hybrid_ndarray_v<lhs_t>
                && is_hybrid_ndarray_v<rhs_t>
            ) {
                return hybrid_ndarray_max_size_v<lhs_t> * hybrid_ndarray_max_size_v<rhs_t>;
            } else if constexpr (
                   is_fixed_size_ndarray_v<lhs_t>
                && is_hybrid_ndarray_v<rhs_t>
            ) {
                constexpr auto shape = fixed_ndarray_shape_v<lhs_t>;
                constexpr auto lhs = index::sum(shape);
                constexpr auto rhs = hybrid_ndarray_max_size_v<rhs_t>;
                return lhs * rhs;
            }  else if constexpr (
                   is_hybrid_ndarray_v<lhs_t>
                && is_fixed_size_ndarray_v<rhs_t>
            ) {
                constexpr auto lhs = hybrid_ndarray_max_size_v<lhs_t>;
                constexpr auto shape = fixed_ndarray_shape_v<rhs_t>;
                constexpr auto rhs = index::sum(shape);
                return lhs * rhs;
            } else {
                return detail::Fail;
            }
        }();
        using value_type = remove_cvref_t<decltype(value)>;
        using type = value_type;
    };

    template <typename op_t, typename lhs_t, typename rhs_t>
    struct is_ndarray< 
        view::decorator_t< view::outer_t, op_t, lhs_t, rhs_t >
    >
    {
        static constexpr auto value = is_ndarray_v<lhs_t> && is_ndarray_v<rhs_t>;
    };

    // provide specialization for reducer
    template <typename op_t, typename lhs_t, typename rhs_t>
    struct get_element_type<
        view::decorator_t< view::outer_t, op_t, lhs_t, rhs_t >
    >
    {
        using type = typename view::outer_t<op_t, lhs_t, rhs_t>::result_type;
    };
} // namespace nmtools::meta

#endif // NMTOOLS_ARRAY_VIEW_UFUNC_OUTER_HPP