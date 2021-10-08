#ifndef NMTOOLS_ARRAY_INDEX_REMOVE_DIMS_HPP
#define NMTOOLS_ARRAY_INDEX_REMOVE_DIMS_HPP

#include "nmtools/meta.hpp"
#include "nmtools/array/utility/at.hpp"
#include "nmtools/array/shape.hpp"
#include "nmtools/array/ndarray/hybrid.hpp"
#include "nmtools/constants.hpp"
#include "nmtools/array/index/ref.hpp"

#include <cstddef>
#include <utility>

namespace nmtools::index
{
    struct remove_dims_t {};

    /**
     * @brief Remove desired axes from shape, optionally keep the size/dimension
     * 
     * This is useful to compute the shape of reduce-like operation
     * that operates on specified axis.
     * 
     * @tparam shape_t 
     * @tparam axis_t 
     * @tparam keepdims_t 
     * @param shape_ 
     * @param axis 
     * @param keepdims 
     * @return constexpr auto 
     */
    template <typename shape_t, typename axis_t, typename keepdims_t>
    constexpr auto remove_dims(const shape_t& shape_, const axis_t& axis, [[maybe_unused]] keepdims_t keepdims)
    {
        // note: axis as reference to prevent raw array to ptr
        using return_t = meta::resolve_optype_t<remove_dims_t,shape_t,axis_t,keepdims_t>;
        auto res = return_t {};

        const auto shape = [&](){
            if constexpr (meta::is_constant_index_array_v<shape_t>) {
                return meta::to_value_v<shape_t>;
            } else if constexpr (meta::is_bounded_array_v<shape_t>) {
                return index::ref(shape_);
            } else {
                return shape_;
            }
        }();

        [[maybe_unused]] auto dim = len(shape);
        if constexpr (meta::is_resizeable_v<return_t>) {
            // number of axis to be removed
            // also take keepdims into accounts
            auto n = [&](){
                if constexpr (meta::is_index_array_v<axis_t>)
                    return len(axis);
                else return 1;
            }();
            auto new_dim = [&](){
                if (static_cast<bool>(keepdims))
                    return dim;
                else return dim-n;
            }();
            res.resize(new_dim);
        }
        // fn to check if given i is detected in axis
        // representing axis to be removed
        [[maybe_unused]]
        auto in_axis = [&](auto i){
            if constexpr (meta::is_index_v<axis_t>) {
                using common_t = meta::promote_index_t<axis_t,decltype(i)>;
                return (common_t)i==(common_t)axis;
            } else {
                auto f_predicate = [i](auto axis){
                    using common_t = meta::promote_index_t<decltype(axis),decltype(i)>;
                    return (common_t)i==(common_t)axis;
                };
                auto found = where(f_predicate, axis);
                return static_cast<bool>(len(found));
            }
        };

        // NOTE: axis maybe signed, so prefer signed size for now

        // TODO: formulate how to deduce index type
        // , may be using meta::get_index_type_t
        // use the same type as axis_t for loop index
        constexpr auto idx_vtype = [](){
            if constexpr (meta::is_constant_index_array_v<axis_t>) {
                // std::commont_type can't handle constant index array :|
                // shortcut for now, just use int
                return meta::as_value_v<int>;
            } else if constexpr (meta::is_index_array_v<axis_t>) {
                using type = meta::get_element_type_t<axis_t>;
                return meta::as_value_v<type>;
            } else if constexpr (meta::is_integer_v<axis_t>) {
                return meta::as_value_v<axis_t>;
            } else {
                return meta::as_value_v<int>;
            }
        }();

        // if return_t (inferred from result_optype_t<...>) is constant index array
        // assume it is the final result already
        // so skip the following computation
        if constexpr (!meta::is_constant_index_array_v<return_t>) {
            using idx_t = meta::type_t<decltype(idx_vtype)>;
            idx_t idx = 0;
            // res and shape have different size
            // index to fill res
            for (idx_t i=0; i<(idx_t)dim; i++) {
                auto in_axis_ = in_axis(i);
                if (in_axis_ && !keepdims)
                    continue;
                else {
                    auto si = at(shape,i);
                    at(res,idx++) = in_axis_ ? 1 : si;
                }
            }
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
    namespace error
    {
        struct REMOVE_DIMS_UNSUPPORTED : detail::fail_t {};
    }

    template <typename shape_t, typename axis_t, typename keepdims_t>
    struct resolve_optype<
        void, index::remove_dims_t, shape_t, axis_t, keepdims_t
    >
    {
        static constexpr auto vtype = [](){
            if constexpr (
                    is_constant_index_array_v<shape_t>
                && (is_constant_index_v<axis_t> || is_constant_index_array_v<axis_t>)
                &&  is_integral_constant_v<keepdims_t>
            ) {
                // all values are known at compile-time,
                // compute result at compile-time
                constexpr auto shape = to_value_v<shape_t>;
                constexpr auto axis  = to_value_v<axis_t>;
                constexpr auto keepdims = keepdims_t::value;
                constexpr auto newshape = index::remove_dims(shape,axis,keepdims);
                constexpr auto N = ::nmtools::len(newshape);
                constexpr auto initial = ::nmtools::at(newshape,0);
                // convert back from value to type
                constexpr auto result = meta::template_reduce<N-1>([&](auto init, auto index){
                    using init_t = type_t<remove_cvref_t<decltype(init)>>;
                    constexpr auto s_i1 = ::nmtools::at(newshape,index+1);
                    using r_t = append_type_t<init_t,ct<s_i1>>;
                    return as_value_v<r_t>;
                }, as_value_v<std::tuple<ct<initial>>>);
                return result;
            } else if constexpr (
                is_constant_index_array_v<shape_t>
            ) {
                using new_shape_t = remove_cvref_t<decltype(to_value_v<shape_t>)>;
                using type = resolve_optype_t<index::remove_dims_t,new_shape_t,axis_t,keepdims_t>;
                return as_value_v<type>;
            } else if constexpr (
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
                    // TODO: create and/or use meta::make_array
                    constexpr auto N = fixed_index_array_size_v<shape_t>;
                    using type = std::array<size_t,N-1>;
                    return as_value_v<type>;
                } else if constexpr (is_fixed_index_array_v<axis_t>) {
                    // TODO: resize shape_t instead of using std::array
                    // TODO: create and/or use meta::make_array
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
                // TODO: use meta::make_hybrid_ndarray
                using type = array::hybrid_ndarray<size_t,N,1>;
                return as_value_v<type>;
            } else {
                return as_value_v<error::REMOVE_DIMS_UNSUPPORTED>;
            }
        }();
        using type = transform_bounded_array_t<type_t<decltype(vtype)>>;
    }; // resolve_optype
} // namespace nmtools::meta

#endif // NMTOOLS_ARRAY_INDEX_REMOVE_DIMS_HPP