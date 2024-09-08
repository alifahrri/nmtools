#ifndef NMTOOLS_ARRAY_INDEX_REMOVE_DIMS_HPP
#define NMTOOLS_ARRAY_INDEX_REMOVE_DIMS_HPP

#include "nmtools/meta.hpp"
#include "nmtools/array/utility/at.hpp"
#include "nmtools/array/shape.hpp"
#include "nmtools/array/ndarray/hybrid.hpp"
#include "nmtools/constants.hpp"
#include "nmtools/array/index/ref.hpp"
#include "nmtools/array/index/where.hpp"
#include "nmtools/array/index/normalize_axis.hpp"
#include "nmtools/utility/unwrap.hpp"

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
    constexpr auto remove_dims(const shape_t& shape, const axis_t& m_axis, [[maybe_unused]] keepdims_t keepdims)
    {
        // note: axis as reference to prevent raw array to ptr
        using return_t = meta::resolve_optype_t<remove_dims_t,shape_t,axis_t,keepdims_t>;
        // TODO: wrap result in maybe type if necessary
        auto res = return_t {};

        auto src_dim = len(shape);
        [[maybe_unused]] auto axis = [&](){
            if constexpr (is_none_v<axis_t>) {
                return m_axis;
            } else {
                // TODO: propagate error
                return unwrap(index::normalize_axis(m_axis,src_dim));
            }
        }();

        [[maybe_unused]] auto dim = len(shape);
        if constexpr (meta::is_resizable_v<return_t>) {
            // number of axis to be removed
            // also take keepdims into accounts
            auto n = [&](){
                if constexpr (meta::is_index_array_v<axis_t>)
                    return len(axis);
                else return 1;
            }();
            auto new_dim = [&](){
                if (static_cast<bool>(keepdims)) {
                    return static_cast<nm_size_t>(dim);
                } else {
                    return static_cast<nm_size_t>(dim-n);
                }
            }();
            res.resize(new_dim);
        }
        // fn to check if given i is detected in axis
        // representing axis to be removed
        [[maybe_unused]]
        auto in_axis = [&]([[maybe_unused]] auto i){
            if constexpr (meta::is_index_v<axis_t>) {
                using common_t = meta::promote_index_t<axis_t,decltype(i)>;
                return (common_t)i==(common_t)axis;
            } else if constexpr (is_none_v<axis_t>) {
                return true;
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
        [[maybe_unused]]
        constexpr auto idx_vtype = [](){
            if constexpr (meta::is_constant_index_array_v<axis_t>) {
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
        if constexpr (!meta::is_constant_index_array_v<return_t> && !is_none_v<return_t>) {
            using idx_t = meta::type_t<decltype(idx_vtype)>;
            idx_t idx = 0;
            // res and shape have different size
            // index to fill res
            for (idx_t i=0; i<(idx_t)dim; i++) {
                auto in_axis_ = in_axis(i);
                auto keepdims_ = [&](){
                    if constexpr (is_none_v<keepdims_t>) {
                        return false;
                    } else {
                        return keepdims;
                    }
                }();
                if (in_axis_ && !keepdims_)
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
        // unknown type
        template <typename...>
        struct REMOVE_DIMS_UNSUPPORTED : detail::fail_t {};

        // error
        template <typename...>
        struct REMOVE_DIMS_INVALID : detail::fail_t {};
    }

    template <typename shape_t, typename axis_t, typename keepdims_t>
    struct resolve_optype<
        void, index::remove_dims_t, shape_t, axis_t, keepdims_t
    >
    {
        static constexpr auto vtype = [](){
            if constexpr (
                    is_constant_index_array_v<shape_t>
                && (is_constant_index_v<axis_t> || is_constant_index_array_v<axis_t> || is_none_v<axis_t>)
                && (is_constant_index_v<keepdims_t> || is_none_v<keepdims_t>)
            ) {
                // all values are known at compile-time,
                // compute result at compile-time
                constexpr auto shape = to_value_v<shape_t>;
                constexpr auto axis  = to_value_v<axis_t>;
                constexpr auto keepdims = keepdims_t{};
                constexpr auto result = index::remove_dims(shape,axis,keepdims);
                if constexpr (!is_none_v<decltype(result)>) {
                    using nmtools::len, nmtools::at;
                    return template_reduce<len(result)-1>([&](auto init, auto index){
                        using init_type = type_t<decltype(init)>;
                        using type = append_type_t<init_type,ct<(size_t)at(result,ct_v<index+1>)>>;
                        return as_value_v<type>;
                    }, as_value_v<nmtools_tuple<ct<(size_t)at(result,ct_v<0>)>>>);
                } else /* if constexpr (is_none_v<decltype(result)>) */ {
                    return as_value_v<decltype(result)>;
                }
            } else if constexpr (
                is_constant_index_array_v<shape_t>
            ) {
                using type = resolve_optype_t<index::remove_dims_t,remove_cvref_t<decltype(to_value_v<shape_t>)>,axis_t,keepdims_t>;
                return as_value_v<type>;
            } else if constexpr (
                   is_index_array_v<shape_t>
                && (is_index_v<axis_t> || is_index_array_v<axis_t>)
                && (is_constant_index_v<keepdims_t> || is_none_v<keepdims_t>)
            ) {
                constexpr auto dim = len_v<shape_t>;
                [[maybe_unused]] constexpr auto b_dim = bounded_size_v<shape_t>;
                [[maybe_unused]] constexpr auto keepdims = [](){
                    if constexpr (is_none_v<keepdims_t>) {
                        return false;
                    } else {
                        return static_cast<bool>(keepdims_t{});
                    }
                }();
                [[maybe_unused]] constexpr auto n_reduce_axes = [](){
                    [[maybe_unused]] constexpr auto N = len_v<axis_t>;
                    if constexpr (is_index_v<axis_t>) {
                        return 1;
                    } else if constexpr (N > 0) {
                        return N;
                    } else {
                        return detail::fail_t {};
                    }
                }();
                [[maybe_unused]] constexpr auto new_dim = [&](){
                    if constexpr ((dim > 0) && keepdims) {
                        return dim;
                    } else if constexpr ((dim > 0) && !keepdims && !is_fail_v<decltype(n_reduce_axes)>) {
                        return dim - n_reduce_axes;
                    } else {
                        return detail::fail_t {};
                    }
                }();
                if constexpr (!is_fail_v<decltype(new_dim)>) {
                    using type = nmtools_array<size_t,new_dim>;
                    return as_value_v<type>;
                } else if constexpr (!is_fail_v<decltype(b_dim)>) {
                    using type = array::static_vector<size_t,b_dim>;
                    return as_value_v<type>;
                } else {
                    using type = nmtools_list<size_t>;
                    return as_value_v<type>;
                }
            } else if constexpr (
                   is_index_array_v<shape_t>
                && (is_index_v<axis_t> || is_index_array_v<axis_t>)
                && is_index_v<keepdims_t>
            ) {
                constexpr auto dim = len_v<shape_t>;
                [[maybe_unused]] constexpr auto b_dim = bounded_size_v<shape_t>;
                if constexpr (dim > 0) {
                    using type = array::static_vector<size_t,dim>;
                    return as_value_v<type>;
                } else if constexpr (!is_fail_v<decltype(b_dim)>) {
                    using type = array::static_vector<size_t,b_dim>;
                    return as_value_v<type>;
                } else {
                    using type = nmtools_list<size_t>;
                    return as_value_v<type>;
                }
            } else if constexpr (
                   is_index_array_v<shape_t>
                && is_none_v<axis_t>
                && (is_constant_index_v<keepdims_t> || is_none_v<keepdims_t>)
            ) {
                constexpr auto size = len_v<shape_t>;
                [[maybe_unused]]
                constexpr auto b_size = bounded_size_v<shape_t>;
                [[maybe_unused]]
                constexpr auto keepdims = [](){
                    if constexpr (is_none_v<keepdims_t>) {
                        return false;
                    } else {
                        return static_cast<bool>(keepdims_t{});
                    }
                }();
                if constexpr ((size > 0) && keepdims) {
                    return template_reduce<size-1>([](auto init, auto){
                        using init_type = type_t<decltype(init)>;
                        return as_value_v<append_type_t<init_type,ct<1>>>;
                    }, as_value_v<nmtools_tuple<ct<1>>>);
                } else if constexpr (!is_fail_v<decltype(b_size)> && keepdims) {
                    using type = array::static_vector<size_t,b_size>;
                    return as_value_v<type>;
                } else if constexpr (keepdims) {
                    using type = shape_t;
                    return as_value_v<type>;
                } else {
                    using type = none_t;
                    return as_value_v<type>;
                }
            } else {
                return as_value_v<error::REMOVE_DIMS_UNSUPPORTED<shape_t,axis_t,keepdims_t>>;
            }
        }();
        using type = transform_bounded_array_t<type_t<decltype(vtype)>>;
    }; // resolve_optype
} // namespace nmtools::meta

#endif // NMTOOLS_ARRAY_INDEX_REMOVE_DIMS_HPP