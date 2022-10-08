#ifndef NMTOOLS_ARRAY_VIEW_UFUNC_UFUNC_HPP
#define NMTOOLS_ARRAY_VIEW_UFUNC_UFUNC_HPP

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
#include "nmtools/array/index/ufunc.hpp"
#include "nmtools/array/shape.hpp"
#include "nmtools/array/dtypes.hpp"
#include "nmtools/array/ndarray.hpp"
#include "nmtools/array/eval.hpp"
#include "nmtools/constants.hpp"

#include "nmtools/array/view/ufunc/detail.hpp"

namespace nmtools::view
{
    /**
     * @brief An ufunc type constructor to specialize handling on scalar type.
     * 
     * Note: since using sfinae on decorator_t with ufunc_t is rather painful,
     * make specific class instead. The decision logic on which type constructor
     * to be called (ufunc_t or scalar_ufunc_t) is performed from ufunc function instead.
     * 
     * @tparam op_t 
     * @tparam lhs_t 
     * @tparam rhs_t 
     */
    template <typename op_t, typename...arrays_t>
    struct scalar_ufunc_t
    {
        // dont take reference for the operands, a Num type should be copied
        // and view type should be cheap to copy
        using operands_type = meta::make_tuple_type_t<arrays_t...>;
        using array_type    = operands_type;
        using op_type       = op_t;
        using result_type   = detail::get_ufunc_result_type_t<op_t,meta::get_element_type_t<arrays_t>...>;

        op_type op;
        operands_type operands;

        constexpr scalar_ufunc_t(op_type op, const arrays_t&...arrays)
            : op(op), operands{arrays...} {}
        
        constexpr auto dim() const noexcept
        {
            // TODO: use constant index
            return 0;
        } // dim

        constexpr auto shape() const noexcept
        {
            return None;
        } // shape

        constexpr auto size() const noexcept
        {
            return meta::ct_v<1ul>;
        }

        template <size_t...Is>
        static constexpr auto apply_at(op_type op, const operands_type& operands, meta::index_sequence<Is...>)
        {
            return op(nmtools::get<Is>(operands)...);
        } // apply_at

        constexpr operator result_type() const
        {
            constexpr auto N = sizeof...(arrays_t);
            return apply_at(op, operands, meta::make_index_sequence<N>{});
        } // operator result_type()
    }; // scalar_ufunc_t

    /**
     * @brief A type constructor for actual ufuncs.
     *
     * The number of arrays passed must be matched with op's arity.
     * 
     * @tparam op_t 
     * @tparam arrays_t 
     */
    template <typename op_t, typename...arrays_t>
    struct ufunc_t
    {
        using operands_type = detail::get_operands_type_t<arrays_t...>;
        using array_type = operands_type;
        using op_type = op_t;
        using result_type = detail::get_ufunc_result_type_t<op_t,meta::get_element_type_t<arrays_t>...>;
        using shape_type  = const meta::resolve_optype_t<index::shape_ufunc_t,decltype(nmtools::shape<true>(meta::declval<arrays_t>()))...>;

        op_type op;
        operands_type operands;
        shape_type shape_;

        constexpr ufunc_t(op_type op, const arrays_t&...operands)
            : op(op)
            , operands(initialize_operands<operands_type>(operands...))
            , shape_(*index::shape_ufunc(nmtools::shape<true>(operands)...))
        {}
        
        constexpr auto shape() const
        {
            return shape_;
        } // shape

        constexpr auto dim() const
        {
            return len(shape());
        } // dim

        template <typename indices_t, size_t...Is>
        static constexpr auto apply_at(op_type op, const operands_type& operands, const indices_t& indices, meta::index_sequence<Is...>)
        {
            using view::detail::apply_at;
            return op(detail::apply_at(nmtools::get<Is>(operands),indices)...);
        } // apply_at

        template <typename...size_types>
        constexpr auto operator()(size_types...indices) const
        {
            // here we directly provide operator() to actually performing operations,
            // instead of returning (transformed) index only
            auto indices_ = pack_indices(indices...);
            constexpr auto N = sizeof...(arrays_t);
            return apply_at(op, operands, indices_, meta::make_index_sequence<N>{});
        } // operator()
    }; // ufunc_t
} // namespace nmtools::view

namespace nmtools::meta
{
    /**
     * @brief Scalar ufunc is num
     * 
     * @tparam op_t 
     * @tparam arrays_t 
     */
    template <typename op_t, typename...arrays_t>
    struct is_num<
        view::decorator_t< view::scalar_ufunc_t, op_t, arrays_t... >
    >
    {
        static constexpr auto value = true;
    }; // is_num

    /**
     * @brief Element type deduction for scalar_ufunc_t
     * 
     * @tparam op_t 
     * @tparam arrays_t 
     */
    template <typename op_t, typename...arrays_t>
    struct get_element_type<
        view::decorator_t< view::scalar_ufunc_t, op_t, arrays_t... >
    >
    {
        using view_t = view::decorator_t< view::scalar_ufunc_t, op_t, arrays_t... >;
        using type = typename view_t::result_type;
    }; // is_num

    template <typename op_t, typename...arrays_t>
    struct is_ndarray< view::decorator_t< view::ufunc_t, op_t, arrays_t... >>
    {
        static constexpr auto value = (is_ndarray_v<arrays_t> && ...);
    };

    template <typename op_t, typename...arrays_t>
    struct fixed_size< view::decorator_t< view::ufunc_t, op_t, arrays_t... >>
    {
        using view_type = view::decorator_t< view::ufunc_t, op_t, arrays_t... >;
        using type_list = meta::type_list<arrays_t...>;

        static constexpr auto value = [](){
            constexpr auto fixed_shape = fixed_shape_v<view_type>;
            if constexpr (!is_fail_v<decltype(fixed_shape)>) {
                return index::product(fixed_shape);
            } else {
                return error::FIXED_SHAPE_UNSUPPORTED<view_type>{};
            }
        }();
    }; // fixed_size

    template <typename op_t, typename...arrays_t>
    struct bounded_size< view::decorator_t< view::ufunc_t, op_t, arrays_t... >>
        : fixed_size< view::decorator_t< view::ufunc_t, op_t, arrays_t... >>
    {};

    template <typename op_t, typename...arrays_t>
    struct get_element_type<
        view::decorator_t< view::ufunc_t, op_t, arrays_t... >
    >
    {
        using type = typename view::ufunc_t<op_t, arrays_t...>::result_type;
    };
} // namespace nmtools::meta


#endif // NMTOOLS_ARRAY_VIEW_UFUNC_UFUNC_HPP