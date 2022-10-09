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

        using lhs_shape_type = decltype(nmtools::shape<true>(meta::declval<lhs_t>()));
        using rhs_shape_type = decltype(nmtools::shape<true>(meta::declval<rhs_t>()));
        using lhs_size_type  = decltype(nmtools::size<true>(meta::declval<lhs_t>()));
        using rhs_size_type  = decltype(nmtools::size<true>(meta::declval<rhs_t>()));
        using dst_shape_type = const meta::resolve_optype_t<index::shape_outer_t,lhs_shape_type,rhs_shape_type>;
        using dst_size_type  = const meta::resolve_optype_t<index::size_outer_t,dst_shape_type,lhs_size_type,rhs_size_type>;

        op_type op;
        operands_type operands;

        dst_shape_type shape_;
        dst_size_type  size_;

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
            : op(op)
            , operands(initialize_operands(lhs,rhs))
            , shape_(index::shape_outer(nmtools::shape<true>(lhs),nmtools::shape<true>(rhs)))
            , size_(index::size_outer(shape_,nmtools::size<true>(lhs),nmtools::size<true>(rhs)))
        {}
        
        constexpr auto shape() const
        {
            return shape_;
        } // shape

        constexpr auto dim() const
        {
            // TODO: make sure to return compile time index whenever possible
            return len(shape());
        } // dim

        constexpr auto size() const noexcept
        {
            return size_;
        }

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

    template <typename op_t, typename lhs_t, typename rhs_t>
    struct bounded_size<
        view::decorator_t< view::outer_t, op_t, lhs_t, rhs_t >
    >
    {
        using view_type = view::decorator_t< view::outer_t, op_t, lhs_t, rhs_t >;

        static constexpr auto value = [](){
            if constexpr (is_bounded_size_v<lhs_t> && is_bounded_size_v<rhs_t>) {
                return bounded_size_v<lhs_t> * bounded_size_v<rhs_t>;
            } else {
                return error::BOUNDED_SIZE_UNSUPPORTED<view_type>{};
            }
        }();
    }; // bounded_size

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