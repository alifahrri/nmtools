#ifndef NMTOOLS_ARRAY_VIEW_UFUNC_ACCUMULATE_HPP
#define NMTOOLS_ARRAY_VIEW_UFUNC_ACCUMULATE_HPP

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
     * @brief Type constructor for accumulate ufuncs.
     *
     * Accumulate the result on given axis.
     * 
     * @tparam op_t operator type
     * @tparam array_t array type
     * @tparam axis_t axis type
     */
    template <typename op_t, typename array_t, typename axis_t>
    struct accumulate_t
    {
        // if given array is a view, just use value instead of reference
        static constexpr auto operands_vtype = [](){
            if constexpr (is_view_v<array_t>) {
                return meta::as_value_v<array_t>;
            } else {
                return meta::as_value_v<const array_t&>;
            }
        }();
        using operands_type = meta::type_t<decltype(operands_vtype)>;
        using array_type    = operands_type;
        using axis_type     = axis_t;
        using op_type       = op_t;
        using reducer_type  = reducer_t<op_t>;
        using element_type  = meta::get_element_type_t<array_t>;

        using result_type = meta::type_t<detail::get_result_type<element_type,op_type>>;

        op_type      op;
        array_type   array;
        axis_type    axis;
        reducer_type reducer;

        constexpr accumulate_t(op_type op, array_type array, axis_type axis)
            : op(op), array(array), axis(axis), reducer{op} {}

        constexpr auto shape() const
        {
            return ::nmtools::shape(array);
        } // shape

        constexpr auto dim() const
        {
            return ::nmtools::dim(array);
        } // dim

        template <typename...size_types>
        constexpr auto operator()(size_types...indices) const
        {
            // here we directly provide operator() to actually performing operations,
            // instead of returning (transformed) index only
            auto indices_ = pack_indices(indices...);
            // for now, assume axis is int and array is fixed_dim
            [[maybe_unused]] constexpr auto DIM = meta::fixed_dim_v<array_t>;
            // type for slicing is DIMx2 where 2 represent start and stop
            constexpr auto slices_vtype = [](){
                using slice_type = nmtools_array<size_t,2>;
                if constexpr (meta::is_fixed_dim_ndarray_v<array_t>) {
                    using slices_type = nmtools_array<slice_type,DIM>;
                    return meta::as_value_v<slices_type>;
                } else {
                    using slices_type = nmtools_list<slice_type>;
                    return meta::as_value_v<slices_type>;
                }
            }();
            using slices_type = meta::type_t<decltype(slices_vtype)>;
            auto slices = slices_type {};
            // TODO: consider to unroll when dim is fixed
            // here, len(slices) already matched the dimension of source array
            auto dim = detail::dim(array);
            if constexpr (meta::is_resizeable_v<slices_type>) {
                slices.resize(dim);
            }
            for (size_t i=0; i<dim; i++) {
                // index at axis i
                auto s = at(indices_,i);
                using common_t = meta::promote_index_t<decltype(axis),size_t>;
                auto start = (common_t)i==(common_t)axis ? 0 : s;
                auto stop  = s + 1;
                at(slices,i) = {start,stop};
            }
            auto sliced = apply_slice(array, slices);
            auto flattened = flatten(sliced);
            return reducer.template operator()<result_type>(flattened);
        } // operator()
    }; // accumulate_t
} // namespace nmtools::view

namespace nmtools::meta
{
    /**
     * @brief Compile-time shape inference for accumulate ufunc
     * 
     * @tparam op_t 
     * @tparam array_t 
     * @tparam axis_t 
     */
    template <typename op_t, typename array_t, typename axis_t>
    struct fixed_ndarray_shape<
        view::accumulate_t< op_t, array_t, axis_t >
    >
    {
        // accumulate ufunc doesnt change the shape
        static inline constexpr auto value = fixed_ndarray_shape_v<array_t>;
        using value_type = decltype(value);
    }; // fixed_ndarray_shape

    template <typename op_t, typename array_t, typename axis_t>
    struct is_ndarray< 
        view::decorator_t< view::accumulate_t, op_t, array_t, axis_t >
    >
    {
        static constexpr auto value = is_ndarray_v<array_t>;
    };

    // provide specialization for reducer
    template <typename op_t, typename array_t, typename axis_t>
    struct get_element_type<
        view::decorator_t< view::accumulate_t, op_t, array_t, axis_t >
    >
    {
        using type = typename view::accumulate_t<op_t, array_t, axis_t>::result_type;
    };
} // namespace nmtools::meta


#endif // NMTOOLS_ARRAY_VIEW_UFUNC_ACCUMULATE_HPP