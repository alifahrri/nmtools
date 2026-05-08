#ifndef NMTOOLS_ARRAY_INDEX_COMPUTE_INDICES_HPP
#define NMTOOLS_ARRAY_INDEX_COMPUTE_INDICES_HPP

#include "nmtools/meta.hpp"
#include "nmtools/utility/at.hpp"
#include "nmtools/utility/shape.hpp"
#include "nmtools/index/tuple_at.hpp"
#include "nmtools/index/compute_strides.hpp"

namespace nmtools::index
{
    /**
     * @brief specific tag to resolve op type of compute_indices
     * 
     */
    struct compute_indices_t {};

    // TODO: remove this move to index::compute_indices
    namespace impl
    {
        template <typename indices_t, typename offset_t, typename shape_t, typename strides_t>
        nmtools_index_attribute
        constexpr auto compute_indices(indices_t& indices, const offset_t& offset, const shape_t& shape, const strides_t& strides)
        {
            constexpr auto N = len_v<indices_t>;
            if constexpr (N > 0) {
                template_for<N>([&](auto index){
                    if constexpr (!is_constant_index_v<decltype(at(indices,index))>) {
                        auto shape_i  = at(shape,index);
                        auto stride_i = at(strides,index);
                        if (has_value(stride_i) && has_value(shape_i) && has_value(offset)) {
                            at(indices,index) = (offset / stride_i) % shape_i;
                        }
                    }
                });
            } else {
                for (nm_size_t i=0; i<(nm_size_t)len(shape); i++) {
                    auto shape_i  = at(shape,i);
                    auto stride_i = at(strides,i);
                    if (has_value(stride_i) && has_value(shape_i) && has_value(offset)) {
                        at(indices,i) = (offset / stride_i) % shape_i;
                    }
                }
            }
        } // compute_indices
    } // namespace impl

    // TODO: cleanup index functions
    /**
     * @brief inverse operation of compute_offset
     * 
     * @param offset flat indices to be mapped
     * @param shape desired shape
     * @param strides computed strides, should be computed from shape
     * @return constexpr auto 
     */
    template <typename offset_t, typename shape_t, typename strides_t>
    nmtools_index_attribute
    constexpr auto compute_indices(const offset_t& offset, const shape_t& shape, const strides_t& strides)
    {
        if constexpr (is_maybe_v<offset_t>
            || is_maybe_v<shape_t>
            || is_maybe_v<strides_t>
        ) {
            using result_t = decltype(compute_indices(unwrap(offset),unwrap(shape),unwrap(strides)));
            using return_t = conditional_t<is_maybe_v<result_t>,result_t,nmtools_maybe<result_t>>;
            return (has_value(offset) && has_value(shape) && has_value(strides)
                ? return_t{compute_indices(unwrap(offset),unwrap(shape),unwrap(strides))}
                : return_t{Nothing}
            );
        } else {
            using result_t = resolve_optype_t<compute_indices_t,offset_t,shape_t,strides_t>;

            auto result = result_t {};

            if constexpr (!is_fail_v<result_t>
                && !is_constant_index_array_v<result_t>
            ) {
                [[maybe_unused]]
                auto dim = len(shape);
                if constexpr (is_resizable_v<result_t>) {
                    result.resize(dim);
                }

                impl::compute_indices(result, offset, shape, strides);
            }

            return result;
        }
    } // compute indices

    /**
     * @brief inverse operation of compute_offset
     * 
     * Offset (flat index) to indices.
     * 
     * @param offset flat indices to be mapped
     * @param shape desired shape
     * @return constexpr auto 
     */
    template <typename offset_t, typename shape_t>
    nmtools_index_attribute
    constexpr auto compute_indices(const offset_t& offset, const shape_t& shape)
    {
        auto strides = compute_strides(shape);
        return compute_indices(offset, shape, strides);
    } // compute_indices
} // namespace nmtools::index

namespace nmtools::meta
{

    namespace error
    {
        template <typename...>
        struct COMPUTE_INDICES_UNSUPPORTED : detail::fail_t {};
    }

    // TODO: improve type deduction
    /**
     * @brief resolve return type for compute_indices
     * 
     * @tparam offset_t 
     * @tparam shape_t 
     * @tparam strides_t 
     */
    template <typename offset_t, typename shape_t, typename strides_t>
    struct resolve_optype< void, index::compute_indices_t, offset_t, shape_t, strides_t >
    {
        static constexpr auto vtype = [](){
            if constexpr (!is_index_v<offset_t>
                || !is_index_array_v<shape_t>
                || !is_index_array_v<strides_t>
            ) {
                using type = error::COMPUTE_INDICES_UNSUPPORTED<offset_t,shape_t,strides_t>;
                return as_value_v<type>;
            } else if constexpr (
                is_constant_index_v<offset_t>
                && (is_constant_index_array_v<shape_t> || is_mixed_index_array_v<shape_t>)
                && (is_constant_index_array_v<strides_t> || is_mixed_index_array_v<strides_t>)
            ) {
                constexpr auto offset  = to_value_v<offset_t>;
                constexpr auto shape   = to_value_v<shape_t>;
                constexpr auto strides = to_value_v<strides_t>;
                constexpr auto result  = index::compute_indices(offset,shape,strides);
                using nmtools::len, nmtools::at, nmtools::has_value;
                return template_reduce<len(result)>([&](auto init, auto index){
                    constexpr auto I = decltype(index)::value;
                    constexpr auto result_i = at(result,I);
                    using init_t = type_t<decltype(init)>;
                    if constexpr (has_value(result_i)) {
                        using type = append_type_t<init_t,ct<(nm_size_t)result_i>>;
                        return as_value_v<type>;
                    } else {
                        using type = append_type_t<init_t,nm_size_t>;
                        return as_value_v<type>;
                    }
                }, as_value_v<nmtools_tuple<>>);
            } else {
                using index_type = get_index_element_type_t<shape_t>;
                constexpr auto DIM = len_v<shape_t>;
                [[maybe_unused]]
                constexpr auto B_DIM = max_len_v<shape_t>;
                if constexpr (DIM > 0) {
                    using type = nmtools_array<index_type,DIM>;
                    return as_value_v<type>;
                } else if constexpr (B_DIM > 0) {
                    using type = nmtools_static_vector<index_type,B_DIM>;
                    return as_value_v<type>;
                } else {
                    using type = nmtools_list<index_type>;
                    return as_value_v<type>;
                }
            }
        }();
        using type = type_t<remove_cvref_t<decltype(vtype)>>;
    }; // resolve_optype

} // namespace nmtools::meta

#endif // NMTOOLS_ARRAY_INDEX_COMPUTE_INDICES_HPP