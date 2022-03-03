#ifndef NMTOOLS_ARRAY_INDEX_INSERT_INDEX_HPP
#define NMTOOLS_ARRAY_INDEX_INSERT_INDEX_HPP

#include "nmtools/meta.hpp"
#include "nmtools/array/at.hpp"

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
        auto dim = len(indices);
        if (axis > (axis_t)dim) {
            return return_t {}; // Nothing
        } else {
            // using value_t = meta::get_value_type_t<result_t>;
            auto result = result_t {};
            if constexpr (meta::is_resizeable_v<result_t>) {
                result.resize(dim+1);
            }

            // TODO: normalize axis
            at(result,axis) = index;
            for (size_t i=0; i<(size_t)len(indices);i++) {
                if (i<(size_t)axis) {
                    at(result,i) = at(indices,i);
                } else {
                    at(result,i+1) = at(indices,i);
                }
            }

            return return_t{result};
        }
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
                if constexpr ((N == 2) || (N == 3)) {
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
                    using resized_t = resize_fixed_index_array_t<indices_t,new_size>;
                    using type = replace_value_type_t<resized_t,new_element_t>;
                    return as_value_v<type>;
                } else {
                    using type = replace_value_type_t<indices_t,new_element_t>;
                    return as_value_v<type>;
                }
            } else {
                using type = error::INSERT_INDEX_UNSUPPORTED<indices_t,index_t,axis_t>;
                return as_value_v<type>;
            }
        }();
        using type = type_t<decltype(vtype)>;
    };
    
} // namespace nmtools::meta


#endif // NMTOOLS_ARRAY_INDEX_INSERT_INDEX_HPP