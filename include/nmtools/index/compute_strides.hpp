#ifndef NMTOOLS_ARRAY_INDEX_COMPUTE_STRIDES_HPP
#define NMTOOLS_ARRAY_INDEX_COMPUTE_STRIDES_HPP

#include "nmtools/meta.hpp"
#include "nmtools/utility/at.hpp"
#include "nmtools/utility/shape.hpp"
#include "nmtools/utility/has_value.hpp"
#include "nmtools/utility/unwrap.hpp"

namespace nmtools::index
{
    // tag to resolve stride return type
    struct stride_t {};

    /**
     * @brief compute stride for ndarray offset
     * 
     * @param shape container of shape, should have value_type member type
     * @param k k-th stride to compute
     * @return constexpr auto
     */
    template <typename array_t, typename size_type>
    nmtools_index_attribute
    constexpr auto stride(const array_t& shape, size_type k)
    {
        using result_t = resolve_optype_t<stride_t,array_t,size_type>;
        auto p = result_t {};
        if constexpr (!is_fail_v<result_t>
            && !is_constant_index_v<result_t>
        ) {
            constexpr auto N = len_v<array_t>;

            p = 1;
            if constexpr (N > 0) {
                // note that k may be runtime value
                template_for<N>([&](auto index){
                    constexpr auto i = decltype(index)::value;
                    if ((nm_size_t)i>=(nm_size_t)(k+1)) {
                        if constexpr (is_nullable_num_v<result_t>) {
                            auto shape_j = at(shape,index);
                            if (has_value(shape_j) && has_value(p)) {
                                p *= shape_j;
                            } else {
                                // reset to none;
                                p = result_t{};
                            }
                        } else {
                            p *= at<i>(shape);
                        }
                    }
                });
            } else {
                for (nm_size_t j=k+1; (j<(nm_size_t)len(shape)) && has_value(p); j++) {
                    if constexpr (is_nullable_num_v<result_t>) {
                        auto shape_j = at(shape,j);
                        if (has_value(shape_j) && has_value(p)) {
                            p *= shape_j;
                        } else {
                            // reset to none;
                            p = result_t{};
                        }
                    } else {
                        p *= at(shape,j);
                    }
                }
            }
        }
        return p;
    } // stride

    /**
     * @brief specific tag to resolve return type of compute_strides
     * 
     */
    struct compute_strides_t {};

    /**
     * @brief compute stride for ndarray offset.
     *
     * This follows numpy's row-major
     * <a href="https://numpy.org/doc/stable/reference/arrays.ndarray.html#internal-memory-layout-of-an-ndarray">stride computation</a>.
     * 
     * @param shape container of shape, should have value_type member type
     * @return constexpr auto
     */
    template <typename array_t>
    nmtools_index_attribute
    constexpr auto compute_strides(const array_t& shape)
    {
        // assume when return_t is maybe then shape_t is also maybe
        if constexpr (is_maybe_v<array_t>) {
            using result_t = decltype(compute_strides(unwrap(shape)));
            using return_t = conditional_t<is_maybe_v<result_t>,result_t,nmtools_maybe<result_t>>;
            return (has_value(shape)
                ? return_t{compute_strides(unwrap(shape))}
                : return_t{Nothing}
            );
        } else {
            using result_t = resolve_optype_t<compute_strides_t,array_t>;

            auto result = result_t{};
            if constexpr (!is_fail_v<result_t>
                && !is_constant_index_array_v<result_t>
            ) {
                [[maybe_unused]] auto n = (nm_size_t)len(shape);
                if constexpr (is_resizable_v<result_t>) {
                    result.resize(n);
                }
                constexpr auto N = len_v<result_t>;
                if constexpr (N>0) {
                    // this may be clipped shape
                    template_for<N>([&](auto i){
                        if constexpr (!is_constant_index_v<decltype(at(result,i))>) {
                            auto stride_i = stride(shape,i);
                            if (has_value(stride_i)) {
                                at(result,i) = stride_i;
                            }
                        }
                    });
                } else {
                    for (nm_size_t i=0; i<n; i++) {
                        auto stride_i = stride(shape,i);
                        if (has_value(stride_i)) {
                            at(result,i) = stride_i;
                        }
                    }
                }
            }
            return result;
        }
    } // compute_strides
} // namespace nmtools::index

namespace nmtools::meta
{

    namespace error
    {
        template <typename...>
        struct INDEX_COMPUTE_STRIDE_UNSUPPORTED : detail::fail_t{};
    } // namespace error
    
    template <typename shape_t>
    struct resolve_optype<
        void, index::compute_strides_t, shape_t
    >
    {
        static constexpr auto vtype = [](){
            if constexpr (!is_index_array_v<shape_t>) {
                using type = error::INDEX_COMPUTE_STRIDE_UNSUPPORTED<shape_t>;
                return as_value_v<type>;
            } else if constexpr (
                is_constant_index_array_v<shape_t>
                || is_clipped_index_array_v<shape_t>
                // || is_mixed_index_array_v<shape_t>
            ) {
                constexpr auto shape = to_value_v<shape_t>;
                constexpr auto strides = index::compute_strides(shape);
                // convert back to type
                constexpr auto N = ::nmtools::len(strides);
                using nmtools::at;
                return template_reduce<N>([&](auto init, auto index){
                    using init_t = type_t<decltype(init)>;
                    constexpr auto I = at(strides,index);
                    if constexpr (is_constant_index_array_v<shape_t>) {
                        using result_t = append_type_t<init_t,ct<I>>;
                        return as_value_v<result_t>;
                    } else {
                        using result_t = append_type_t<init_t,clipped_size_t<I>>;
                        return as_value_v<result_t>;
                    }
                }, as_value_v<nmtools_tuple<>>);
            } else if constexpr (is_mixed_index_array_v<shape_t>) {
                constexpr auto shape = to_value_v<shape_t>;
                constexpr auto result = index::compute_strides(shape);
                constexpr auto N = ::nmtools::len(result);
                using nmtools::at;
                return template_reduce<N>([&](auto init, auto index){
                    using init_t = type_t<decltype(init)>;
                    constexpr auto I = at(result,index);
                    if constexpr (has_value(I)) {
                        using type = append_type_t<init_t,ct<(nm_size_t)I>>;
                        return as_value_v<type>;
                    } else {
                        using type = append_type_t<init_t,nm_size_t>;
                        return as_value_v<type>;
                    }
                }, as_value_v<nmtools_tuple<>>);
            } else {
                constexpr auto DIM = len_v<shape_t>;
                [[maybe_unused]]
                constexpr auto B_DIM = max_len_v<shape_t>;
                using index_type = get_index_element_type_t<shape_t>;
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
        using type = type_t<decltype(vtype)>;
    }; // resolve_optype

    namespace error
    {
        template <typename...>
        struct INDEX_STRIDE_UNSUPPORTED : detail::fail_t {};
    } // namespace error

    template <typename array_t, typename size_type>
    struct resolve_optype<
        void, index::stride_t, array_t, size_type
    >
    {
        static constexpr auto vtype = [](){
            if constexpr (!is_num_v<size_type>
                || !is_index_array_v<array_t>
            ) {
                using type = error::INDEX_STRIDE_UNSUPPORTED<array_t,size_type>;
                return as_value_v<type>;
            } else if constexpr (
                is_constant_index_v<size_type>
                && is_constant_index_array_v<array_t>
            ) {
                constexpr auto array  = to_value_v<array_t>;
                constexpr auto stride = index::stride(array,size_type{});
                if constexpr (has_value(stride)) {
                    using type = ct<(nm_size_t)stride>;
                    return as_value_v<type>;
                } else {
                    using type = nm_size_t;
                    return as_value_v<type>;
                }
            } else {
                using index_t = get_index_element_type_t<array_t>;
                using type = index_t;
                return as_value_v<type>;
            }
        }();
        using type = type_t<decltype(vtype)>;
    };
} // namespace nmtools::meta

#endif // NMTOOLS_ARRAY_INDEX_COMPUTE_STRIDES_HPP