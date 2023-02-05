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
        using array_type    = resolve_array_type_t<array_t>;
        using axis_type     = resolve_attribute_type_t<axis_t>;
        using op_type       = op_t;
        using reducer_type  = reducer_t<op_t>;
        using element_type  = meta::get_element_type_t<array_t>;

        using result_type = meta::type_t<detail::get_result_type<element_type,op_type>>;

        using shape_type = decltype(nmtools::shape<true>(meta::declval<array_t>()));
        using size_type  = decltype(nmtools::size<true>(meta::declval<array_t>()));

        op_type      op;
        array_type   array;
        axis_type    axis;
        reducer_type reducer;
        shape_type   shape_;
        size_type    size_;

        constexpr accumulate_t(op_type op, const array_t& array_, const axis_t& axis)
            : op(op)
            , array(initialize<array_type>(array_))
            , axis(init_attribute<axis_type>(axis))
            , reducer{op}
            , shape_(nmtools::shape<true>(array_))
            , size_(nmtools::size<true>(array_))
        {}

        constexpr auto shape() const
        {
            return shape_;
        } // shape

        constexpr auto dim() const
        {
            return len(shape());
        } // dim

        constexpr auto size() const
        {
            return size_;
        } // size

        template <typename...size_types>
        constexpr auto operator()(size_types...indices) const
        {
            // here we directly provide operator() to actually performing operations,
            // instead of returning (transformed) index only
            auto indices_ = pack_indices(indices...);
            // for now, assume axis is int and array is fixed_dim
            [[maybe_unused]] constexpr auto DIM = meta::fixed_dim_v<array_t>;
            [[maybe_unused]] constexpr auto B_DIM = meta::bounded_dim_v<array_t>;
            // type for slicing is DIMx2 where 2 represent start and stop
            constexpr auto slices_vtype = [&](){
                using slice_type = nmtools_array<size_t,2>;
                if constexpr (!meta::is_fail_v<decltype(DIM)>) {
                    using slices_type = nmtools_array<slice_type,(size_t)DIM>;
                    return meta::as_value_v<slices_type>;
                } else if constexpr (!meta::is_fail_v<decltype(B_DIM)>) {
                    using slices_type = array::static_vector<slice_type,(size_t)B_DIM>;
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
            if constexpr (meta::is_resizable_v<slices_type>) {
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
            auto sliced = [&](){
                if constexpr (meta::is_pointer_v<array_type>) {
                    return apply_slice(*array, slices);
                } else {
                    return apply_slice(array, slices);
                }
            }();
            auto flattened = flatten(sliced);
            return reducer.template operator()<result_type>(flattened);
        } // operator()
    }; // accumulate_t
} // namespace nmtools::view

namespace nmtools::meta
{
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