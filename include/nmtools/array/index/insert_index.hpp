#ifndef NMTOOLS_ARRAY_INDEX_INSERT_INDEX_HPP
#define NMTOOLS_ARRAY_INDEX_INSERT_INDEX_HPP

#include "nmtools/meta.hpp"
#include "nmtools/array/at.hpp"
#include "nmtools/array/index/normalize_axis.hpp"

namespace nmtools::index
{
    struct insert_index_t {};

    /**
     * @brief Insert an index, or None, or Ellipsis to an indices at given axis/dim.
     * 
     * @tparam indices_t index array
     * @tparam index_t   index or tuple or Ellipsis
     * @tparam axis_t    axis to insert at
     * @return constexpr auto 
     */
    template <typename indices_t, typename index_t, typename axis_t>
    constexpr auto insert_index(const indices_t& indices, const index_t& index, axis_t axis)
    {
        using result_t = meta::resolve_optype_t<insert_index_t,indices_t,index_t,axis_t>;
        using return_t = nmtools_maybe<result_t>;

        constexpr auto axis_vtype = [](){
            if constexpr (meta::is_integral_constant_v<axis_t>) {
                using type = typename axis_t::value_type;
                return meta::as_value_v<type>;
            } else {
                using type = axis_t;
                return meta::as_value_v<type>;
            }
        }();
        using axis_type = meta::type_t<decltype(axis_vtype)>;

        auto dim = len(indices);
        auto new_dim = dim + 1;

        if constexpr (meta::is_index_array_v<index_t> || meta::is_slice_index_array_v<index_t>) {
            new_dim = dim + len(index);
        }
        auto maybe_axis = normalize_axis(axis,new_dim);
        if (((axis < 0) && !maybe_axis) || (axis > (axis_type)dim)) {
            return return_t {}; // Nothing
        }

        auto result = result_t {};

        if constexpr (meta::is_resizeable_v<result_t>) {
            result.resize(new_dim);
        }

        auto axis_ = (axis < 0 ? *maybe_axis : axis);
        if constexpr (meta::is_index_array_v<index_t>) {
            auto idx_dim = len(index);
            auto src_i = (size_t)0;
            auto idx_i = (size_t)0;
            for (size_t i=0; i<(size_t)new_dim; i++) {
                if ((i<(size_t)axis_) && (src_i < dim)) {
                    at(result,i) = at(indices,src_i++);
                } else if (idx_i < idx_dim) {
                    at(result,i) = at(index,idx_i++);
                } else {
                    at(result,i) = at(indices,src_i++);
                }
            }
        } else {
            at(result,axis_) = index;
            for (size_t i=0; i<(size_t)len(indices);i++) {
                if (i<(size_t)axis_) {
                    at(result,i) = at(indices,i);
                } else {
                    at(result,i+1) = at(indices,i);
                }
            }
        }

        return return_t{result};
    } // insert_index
} // namespace nmtools::index

namespace nmtools::meta
{
    namespace error
    {
        template<typename...>
        struct INSERT_INDEX_UNSUPPORTED : detail::fail_t {};
    } // namespace error
    
    template <typename indices_t, typename index_t, typename axis_t>
    struct resolve_optype<void,index::insert_index_t,indices_t,index_t,axis_t>
    {
        static constexpr auto vtype = [](){
            constexpr auto is_slice_range_index = [](){
                constexpr auto N = len_v<index_t>;
                // restrict slice range to tuple, no index array supported
                if constexpr (is_tuple_v<index_t> && ((N == 2) || (N == 3))) {
                    using start_t = decltype(nmtools::at(declval<index_t>(),ct_v<0>));
                    using stop_t  = decltype(nmtools::at(declval<index_t>(),ct_v<1>));
                    constexpr auto slice_vtype = [](){
                        if constexpr (N == 3) {
                            using type = decltype(nmtools::at(declval<index_t>(),ct_v<2>));
                            return as_value_v<type>;
                        } else {
                            return as_value_v<none_t>;
                        }
                    }();
                    using step_t = type_t<decltype(slice_vtype)>;
                    return (is_none_v<start_t> || is_index_v<start_t>)
                        && (is_none_v<stop_t>  || is_index_v<stop_t>)
                        && (is_none_v<step_t>  || is_index_v<step_t>);
                } else {
                    return is_ellipsis_v<index_t>;
                }
            }();

            // TODO: support tuple indices
            if constexpr (
                   (is_index_array_v<indices_t> && !is_tuple_v<indices_t>) // to be able to use replace_element_type
                && (is_index_v<index_t> || is_slice_range_index)
                &&  is_index_v<axis_t>
            ) {
                using element_t = get_element_type_t<indices_t>;
                constexpr auto new_element_vtype = [](){
                    if constexpr (is_index_v<index_t>) {
                        return as_value_v<element_t>;
                    } else {
                        using type = nmtools_either<element_t,index_t>;
                        return as_value_v<type>;
                    }
                }();
                using new_element_t = type_t<decltype(new_element_vtype)>;
                if constexpr (is_fixed_index_array_v<indices_t>) {
                    constexpr auto new_size = len_v<indices_t> + 1;
                    using resized_t = resize_fixed_index_array_t<transform_bounded_array_t<indices_t>,new_size>;
                    using type = replace_value_type_t<resized_t,new_element_t>;
                    if constexpr (is_fail_v<type> || is_fail_v<resized_t>) {
                        return as_value_v<nmtools_array<new_element_t,new_size>>;
                    } else {
                        return as_value_v<type>;
                    }
                } else {
                    using type = replace_value_type_t<transform_bounded_array_t<indices_t>,new_element_t>;
                    return as_value_v<type>;
                }
            } else if constexpr (
                   (is_fixed_index_array_v<indices_t> && !is_tuple_v<indices_t>)
                && (is_fixed_index_array_v<index_t>)
                &&  is_index_v<axis_t>
            ) {
                constexpr auto n_indices = len_v<indices_t>;
                constexpr auto n_index   = len_v<index_t>;
                constexpr auto dim = n_indices + n_index;
                using resized_t = resize_fixed_index_array_t<indices_t,dim>;
                if constexpr (is_fail_v<resized_t>) {
                    return as_value_v<nmtools_array<get_element_type_t<indices_t>,dim>>;
                } else {
                    return as_value_v<resized_t>;
                }
            } else if constexpr (
                   (is_hybrid_index_array_v<indices_t> && !is_tuple_v<indices_t>)
                && (is_hybrid_index_array_v<index_t>)
                &&  is_index_v<axis_t>
            ) {
                constexpr auto n_indices = hybrid_index_array_max_size_v<indices_t>;
                constexpr auto n_index   = hybrid_index_array_max_size_v<index_t>;
                constexpr auto max = n_indices + n_index;
                using resized_t = resize_hybrid_index_array_max_size_t<indices_t,max>;
                return as_value_v<resized_t>;
            } else if constexpr (
                   (is_index_array_v<indices_t>)
                && (is_index_array_v<index_t>)
                &&  is_index_v<axis_t>
            ) {
                using type = indices_t;
                return as_value_v<type>;
            } else if constexpr (
                    is_slice_index_array_v<indices_t>
                && (is_slice_index_array_v<index_t> || is_index_array_v<index_t>)
                && (is_index_v<axis_t>)
            ) {
                // NOTE: assume has value_type
                using src_value_type = get_value_type_t<indices_t>;
                constexpr auto idx_vtype = [](){
                    if constexpr (is_slice_index_array_v<index_t>) {
                        using type = get_value_type_t<index_t>;
                        return as_value_v<type>;
                    } else /* if constexpr (is_index_array_v<index_t>) */ {
                        using type = get_element_type_t<index_t>;
                        return as_value_v<type>;
                    }
                }();
                using idx_value_type = type_t<decltype(idx_vtype)>;
                constexpr auto res_vtype = [](){
                    if constexpr (is_either_v<src_value_type>) {
                        using left_t  = get_either_left_t<src_value_type>;
                        using right_t = get_either_right_t<src_value_type>;
                        // TODO: check if idx_value_type is either type & check if same with left/right
                        if constexpr (is_same_v<left_t,idx_value_type> || is_same_v<right_t,idx_value_type>) {
                            using type = src_value_type;
                            return as_value_v<type>;
                        } else {
                            using type = nmtools_either<src_value_type,idx_value_type>;
                            return as_value_v<type>;
                        }
                    } else {
                        // TODO: check if idx_value_type is either type & check if same with src
                        using type = nmtools_either<src_value_type,idx_value_type>;
                        return as_value_v<type>;
                    }
                }();
                // TODO: skip make either if src & idx are the same type or idx is in either src left/right
                using res_value_type = type_t<decltype(res_vtype)>;
                using type = nmtools_list<res_value_type>;
                return as_value_v<type>;
            } else {
                using type = error::INSERT_INDEX_UNSUPPORTED<indices_t,index_t,axis_t>;
                return as_value_v<type>;
            }
        }();
        using type = type_t<decltype(vtype)>;
    };
    
} // namespace nmtools::meta


#endif // NMTOOLS_ARRAY_INDEX_INSERT_INDEX_HPP