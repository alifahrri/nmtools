#ifndef NMTOOLS_ARRAY_INDEX_REMOVE_DIMS_HPP
#define NMTOOLS_ARRAY_INDEX_REMOVE_DIMS_HPP

#include "nmtools/meta.hpp"
#include "nmtools/array/utility/at.hpp"
#include "nmtools/array/shape.hpp"
#include "nmtools/array/ndarray/hybrid.hpp"
#include "nmtools/constants.hpp"

#include <cstddef>
#include <utility>

namespace nmtools::index
{
    struct remove_dims_t {};

    template <typename shape_t, typename axis_t, typename keepdims_t>
    constexpr auto remove_dims(const shape_t& shape, const axis_t& axis, keepdims_t keepdims)
    {
        // note: axis as reference to prevent raw array to ptr
        using return_t = meta::resolve_optype_t<remove_dims_t,shape_t,axis_t,keepdims_t>;
        auto res = return_t {};

        // number of axis to be removed
        // also take keepdims into accounts
        auto n = [&](){
            if constexpr (meta::is_index_array_v<axis_t>)
                return len(axis);
            else return 1;
        }();
        auto dim = len(shape);
        auto new_dim = [&](){
            if (static_cast<bool>(keepdims))
                return dim;
            else return dim-n;
        }();
        if constexpr (meta::is_resizeable_v<return_t>)
            res.resize(new_dim);

        // fn to check if given i is detected in axis
        // representing axis to be removed
        auto in_axis = [&](auto i){
            if constexpr (meta::is_index_v<axis_t>)
                return i==axis;
            else {
                auto f_predicate = [i](auto axis){
                    return i==axis;
                };
                auto found = where(f_predicate, axis);
                return static_cast<bool>(len(found));
            }
        };

        // TODO: formulate how to deduce index type
        // , may be using meta::get_index_type_t
        // use the same type as axis_t for loop index
        constexpr auto idx_vtype = [](){
            if constexpr (meta::is_index_array_v<axis_t>) {
                using type = meta::get_element_type_t<axis_t>;
                return meta::as_value_v<type>;
            } else if constexpr (meta::is_integer_v<axis_t>) {
                return meta::as_value_v<axis_t>;
            } else {
                return meta::as_value_v<size_t>;
            }
        }();
        using idx_t = meta::type_t<decltype(idx_vtype)>;
        idx_t idx = 0;
        // res and shape have different size
        // index to fill res
        for (idx_t i=0; i<dim; i++) {
            auto in_axis_ = in_axis(i);
            if (in_axis_ && !keepdims)
                continue;
            else
                at(res,idx++) = in_axis_ ? 1 : at(shape,i);
        }

        return res;
    } // remove_dims

    template <typename shape_t, typename axis_t>
    constexpr auto remove_dims(const shape_t& shape, const axis_t& axis)
    {
        return remove_dims(shape,axis,False);
    } // remove_dims

} // namespace nmtools::index

namespace nmtools::meta
{
    template <typename shape_t, typename axis_t, typename keepdims_t>
    struct resolve_optype<
        void, index::remove_dims_t, shape_t, axis_t, keepdims_t
    >
    {
        static constexpr auto vtype = [](){
            if constexpr (
                    is_index_array_v<shape_t>
                && !is_fixed_index_array_v<shape_t>
            ) {
                using type = shape_t;
                return as_value_v<type>;
            } else if constexpr (
                   is_fixed_index_array_v<shape_t>
                && is_integral_constant_v<keepdims_t>
            ) {
                constexpr auto keepdims = keepdims_t {};
                if constexpr (keepdims) {
                    return as_value_v<shape_t>;
                } else if constexpr (is_index_v<axis_t>) {
                    // TODO: resize shape_t instead of using std::array
                    constexpr auto N = fixed_index_array_size_v<shape_t>;
                    using type = std::array<size_t,N-1>;
                    return as_value_v<type>;
                } else if constexpr (is_fixed_index_array_v<axis_t>) {
                    // TODO: resize shape_t instead of using std::array
                    constexpr auto N = fixed_index_array_size_v<shape_t>;
                    constexpr auto M = fixed_index_array_size_v<axis_t>;
                    using type = std::array<size_t,N-M>;
                    return as_value_v<type>;
                } else if constexpr (is_index_array_v<axis_t>) {
                    // TODO: consider to provide metafunction make_hybrid_index_array
                    constexpr auto N = fixed_index_array_size_v<shape_t>;
                    using type = array::hybrid_ndarray<size_t,N,1>;
                    return as_value_v<type>;
                }
            } else if constexpr (
                   is_fixed_index_array_v<shape_t>
                && is_boolean_v<keepdims_t>
            ) {
                // here we don't know exact size, but we know maximum size
                // TODO: consider to provide metafunction make_hybrid_index_array
                constexpr auto N = fixed_index_array_size_v<shape_t>;
                using type = array::hybrid_ndarray<size_t,N,1>;
                return as_value_v<type>;
            } else {
                return as_value_v<void>;
            }
        }();
        using type = transform_bounded_array_t<type_t<decltype(vtype)>>;
    }; // resolve_optype
} // namespace nmtools::meta

#endif // NMTOOLS_ARRAY_INDEX_REMOVE_DIMS_HPP