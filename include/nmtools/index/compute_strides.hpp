#ifndef NMTOOLS_ARRAY_INDEX_COMPUTE_STRIDES_HPP
#define NMTOOLS_ARRAY_INDEX_COMPUTE_STRIDES_HPP

#include "nmtools/meta.hpp"
#include "nmtools/utility/at.hpp"
#include "nmtools/utility/shape.hpp"
#include "nmtools/utility/has_value.hpp"
#include "nmtools/utility/unwrap.hpp"
#include "nmtools/index/gather.hpp"
#include "nmtools/index/reverse.hpp"

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
     * @brief specific tag to resolve return type of compute_row_major_strides
     * 
     */
    struct compute_row_major_strides_t {};

    /**
     * @brief specific tag to resolve return type of compute_col_major_strides
     * 
     */
    struct compute_col_major_strides_t {};

    /**
     * @brief compute column-major stride for ndarray offset
     *
     * k-th stride is the product of shape elements before it.
     *
     * @param shape container of shape, should have value_type member type
     * @param k k-th stride to compute
     * @return constexpr auto
     */
    template <typename array_t, typename size_type>
    nmtools_index_attribute
    constexpr auto col_stride(const array_t& shape, size_type k)
    {
        // same element type resolution as row-major stride
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
                    if ((nm_size_t)i < (nm_size_t)k) {
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
                for (nm_size_t j=0; j<k && has_value(p); j++) {
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
    } // col_stride

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

    /**
     * @brief compute row-major strides for ndarray offset.
     *
     * Alias of compute_strides, kept for symmetry with
     * compute_col_major_strides.
     *
     * @param shape container of shape, should have value_type member type
     * @return constexpr auto
     */
    template <typename array_t>
    nmtools_index_attribute
    constexpr auto compute_row_major_strides(const array_t& shape)
    {
        return compute_strides(shape);
    } // compute_row_major_strides

    /**
     * @brief compute column-major strides for ndarray offset.
     *
     * k-th stride is the product of shape elements before it, so the
     * first axis is contiguous. Equivalent to reversing the result of
     * row-major stride computation on a reversed shape.
     *
     * @param shape container of shape, should have value_type member type
     * @return constexpr auto
     */
    template <typename array_t>
    nmtools_index_attribute
    constexpr auto compute_col_major_strides(const array_t& shape)
    {
        // assume when return_t is maybe then shape_t is also maybe
        if constexpr (is_maybe_v<array_t>) {
            using result_t = decltype(compute_col_major_strides(unwrap(shape)));
            using return_t = conditional_t<is_maybe_v<result_t>,result_t,nmtools_maybe<result_t>>;
            return (has_value(shape)
                ? return_t{compute_col_major_strides(unwrap(shape))}
                : return_t{Nothing}
            );
        } else {
            using result_t = resolve_optype_t<compute_col_major_strides_t,array_t>;

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
                            auto stride_i = col_stride(shape,i);
                            if (has_value(stride_i)) {
                                at(result,i) = stride_i;
                            }
                        }
                    });
                } else {
                    for (nm_size_t i=0; i<n; i++) {
                        auto stride_i = col_stride(shape,i);
                        if (has_value(stride_i)) {
                            at(result,i) = stride_i;
                        }
                    }
                }
            }
            return result;
        }
    } // compute_col_major_strides

    /**
     * @brief compute transposed row-major strides from shape and axes
     *
     * Equivalent to transposing the row-major strides of shape, without
     * needing the original array strides. For example shape (2,4,3) with
     * axes (2,0,1) returns {1,12,3}, which is the striding of
     * arange(24).reshape(2,4,3).transpose(2,0,1).
     *
     * The result is the gather of the row-major strides by axes, so
     * result[i] equals row_major_strides(shape)[axes[i]]. Axes of none_t
     * reverses the strides, like a full transpose.
     *
     * @param shape container of shape
     * @param axes container of axis indices, None (none_t) to reverse
     * @return constexpr auto
     */
    template <typename shape_t, typename axes_t=none_t>
    nmtools_index_attribute
    constexpr auto compute_transposed_strides(const shape_t& shape, const axes_t& axes=axes_t{})
    {
        auto strides = compute_row_major_strides(shape);
        if constexpr (is_none_v<axes_t>) {
            return index::reverse(strides);
        } else {
            return index::gather(strides, axes);
        }
    } // compute_transposed_strides

    namespace detail
    {
        // whether every order priority value fits within 2D blocking
        template <typename order_t>
        struct blocked_order_is_2d
        {
            static constexpr auto value = [](){
                constexpr auto o = to_value_v<order_t>;
                return template_reduce<len_v<order_t>>([&](auto acc, auto i){
                    return acc && ((nm_size_t)at(o,i) < 2);
                }, true);
            }();
        }; // blocked_order_is_2d
    } // namespace detail

    /**
     * @brief compute blocked (tiled) strides from shape, block and orders
     *
     * A blocked layout splits every mode into (grid, inner) submodes:
     * grid_d = shape_d / block_d (division must be exact). The result is
     * a nested strides array parallel to the nested shape
     * ((grid_0,block_0),(grid_1,block_1),...), so
     * result[d] = tuple{grid_stride_d, inner_stride_d} where grid
     * strides are placed by grid_order scaled by the block size, and
     * inner strides describe the striding within a block.
     *
     * Orders are constant index arrays of per-mode priorities, modes
     * with smaller value vary faster. For example shape (8,8) blocked
     * into (4,2) tiles with grid_order {1_ct,0_ct} (row-major) and
     * inner_order {0_ct,1_ct} (column-major) returns ((32,1),(8,4)),
     * the striding of a blocked column major 8x8 matrix.
     *
     * Currently limited to 2D blocking: order values must be < 2.
     * Higher ranks only need order values up to N-1 once supported.
     *
     * @param shape container of shape, fixed-size
     * @param block container of block sizes per mode, fixed-size
     * @param grid_order constant index array of grid mode priorities
     * @param inner_order constant index array of inner mode priorities
     * @return constexpr auto nested tuple of stride pairs
     */
    template <typename shape_t, typename block_t, typename grid_order_t, typename inner_order_t>
    nmtools_index_attribute
    constexpr auto compute_blocked_strides(const shape_t& shape, const block_t& block
        , const grid_order_t& grid_order, const inner_order_t& inner_order
    ) {
        static_assert(is_constant_index_array_v<grid_order_t>
            , "compute_blocked_strides: grid_order must be a constant index array"
        );
        static_assert(is_constant_index_array_v<inner_order_t>
            , "compute_blocked_strides: inner_order must be a constant index array"
        );

        constexpr auto N = len_v<shape_t>;
        static_assert(N > 0, "compute_blocked_strides: shape must have fixed size");
        static_assert(len_v<block_t> == N
            , "compute_blocked_strides: block must have the same length as shape"
        );
        static_assert(len_v<grid_order_t> == N && len_v<inner_order_t> == N
            , "compute_blocked_strides: orders must have the same length as shape"
        );

        // scope limited to 2D blocking for now, remove these assertions
        // together with testing of higher rank blocking
        static_assert(detail::blocked_order_is_2d<grid_order_t>::value
            && detail::blocked_order_is_2d<inner_order_t>::value
            , "compute_blocked_strides: only 2D blocking is supported (order values must be < 2)"
        );
        static_assert(N <= 2, "compute_blocked_strides: only 2D blocking is supported");

        // number of elements in a single block
        auto block_size = 1;
        template_for<N>([&](auto j){
            block_size *= at(block,j);
        });

        // grid_d = shape_d / block_d, modes with smaller order vary faster
        auto grid_stride = [&](auto i){
            auto s = 1;
            template_for<N>([&](auto j){
                if (at(grid_order,j) < at(grid_order,i)) {
                    s *= at(shape,j)/at(block,j);
                }
            });
            return s * block_size;
        };
        auto inner_stride = [&](auto i){
            auto s = 1;
            template_for<N>([&](auto j){
                if (at(inner_order,j) < at(inner_order,i)) {
                    s *= at(block,j);
                }
            });
            return s;
        };

        if constexpr (N == 1) {
            return nmtools_tuple{ nmtools_tuple{grid_stride(ct_v<0>), inner_stride(ct_v<0>)} };
        } else {
            return nmtools_tuple{
                nmtools_tuple{grid_stride(ct_v<0>), inner_stride(ct_v<0>)}
                , nmtools_tuple{grid_stride(ct_v<1>), inner_stride(ct_v<1>)}
            };
        }
    } // compute_blocked_strides

    // shared implementation of is_row_major/is_col_major
    template <typename shape_t, typename strides_t, typename canonical_t>
    constexpr auto is_major(const shape_t& shape, const strides_t& strides
        , const canonical_t& canonical
    ) {
        // per-dim comparison used by is_row_major/is_col_major:
        // the stride of a dim with known extent <= 1 is don't care, while
        // unknown extents or strides cannot prove a match, so they yield
        // false (conservative)
        auto stride_dim_may_match = [](const auto& extent
            , const auto& stride
            , const auto& expected
        )
        {
            using extent_t = decltype(extent);
            using stride_t = decltype(stride);
            using expect_t = decltype(expected);
            if constexpr (is_nullable_num_v<extent_t>) {
                if (has_value(extent) && (nm_size_t)extent <= 1) {
                    return true;
                }
            } else {
                if ((nm_size_t)extent <= 1) {
                    return true;
                }
            }
            auto known = true;
            if constexpr (is_nullable_num_v<stride_t>) {
                known = known && has_value(stride);
            }
            if constexpr (is_nullable_num_v<expect_t>) {
                known = known && has_value(expected);
            }
            if (!known) {
                return false;
            }
            return (nm_size_t)stride == (nm_size_t)expected;
        };

        auto res = true;
        constexpr auto N = len_v<shape_t>;
        if constexpr (N > 0) {
            template_for<N>([&](auto i){
                if (res) {
                    res = stride_dim_may_match(at(shape,i), at(strides,i), at(canonical,i));
                }
            });
        } else {
            auto n = (nm_size_t)len(shape);
            for (nm_size_t i=0; i<n && res; i++) {
                res = stride_dim_may_match(at(shape,i), at(strides,i), at(canonical,i));
            }
        }
        return res;
    } // is_major

    /**
     * @brief check if strides produce the same memory image as fresh
     *        row-major striding of shape
     *
     * Equivalent to comparing strides against compute_row_major_strides,
     * except the stride of dims with known extent <= 1 is don't care.
     * Broadcast zero-strides therefore fail unless the dim is degenerate.
     * Unknown (null) extents or strides cannot prove a match, so results
     * are conservative: true only when provably row-major. Maybe-wrapped
     * input propagates to a maybe result.
     *
     * @param shape container of shape
     * @param strides container of strides, same length as shape
     * @return constexpr auto bool, or maybe<bool> for maybe input
     */
    template <typename shape_t, typename strides_t>
    nmtools_index_attribute
    constexpr auto is_row_major(const shape_t& shape, const strides_t& strides)
    {
        if constexpr (is_maybe_v<shape_t> || is_maybe_v<strides_t>) {
            using result_t = decltype(is_row_major(unwrap(shape), unwrap(strides)));
            using return_t = conditional_t<is_maybe_v<result_t>,result_t,nmtools_maybe<result_t>>;
            return (has_value(shape) && has_value(strides)
                ? return_t{is_row_major(unwrap(shape), unwrap(strides))}
                : return_t{Nothing}
            );
        } else {
            auto canonical = index::compute_strides(shape);
            return is_major(shape, strides, canonical);
        }
    } // is_row_major

    /**
     * @brief check if strides produce the same memory image as fresh
     *        column-major striding of shape
     *
     * Column-major counterpart of is_row_major, comparing against
     * compute_col_major_strides with the same don't care and
     * conservative-unknown rules.
     *
     * @param shape container of shape
     * @param strides container of strides, same length as shape
     * @return constexpr auto bool, or maybe<bool> for maybe input
     */
    template <typename shape_t, typename strides_t>
    nmtools_index_attribute
    constexpr auto is_col_major(const shape_t& shape, const strides_t& strides)
    {
        if constexpr (is_maybe_v<shape_t> || is_maybe_v<strides_t>) {
            using result_t = decltype(is_col_major(unwrap(shape), unwrap(strides)));
            using return_t = conditional_t<is_maybe_v<result_t>,result_t,nmtools_maybe<result_t>>;
            return (has_value(shape) && has_value(strides)
                ? return_t{is_col_major(unwrap(shape), unwrap(strides))}
                : return_t{Nothing}
            );
        } else {
            auto canonical = index::compute_col_major_strides(shape);
            return is_major(shape, strides, canonical);
        }
    } // is_col_major
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

    // row-major strides are compute_strides themselves
    template <typename shape_t>
    struct resolve_optype<
        void, index::compute_row_major_strides_t, shape_t
    > : resolve_optype<void, index::compute_strides_t, shape_t>
    {}; // resolve_optype

    template <typename shape_t>
    struct resolve_optype<
        void, index::compute_col_major_strides_t, shape_t
    >
    {
        static constexpr auto vtype = [](){
            if constexpr (!is_index_array_v<shape_t>) {
                using type = error::INDEX_COMPUTE_STRIDE_UNSUPPORTED<shape_t>;
                return as_value_v<type>;
            } else if constexpr (
                is_constant_index_array_v<shape_t>
                || is_clipped_index_array_v<shape_t>
            ) {
                constexpr auto shape = to_value_v<shape_t>;
                constexpr auto strides = index::compute_col_major_strides(shape);
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
                constexpr auto result = index::compute_col_major_strides(shape);
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