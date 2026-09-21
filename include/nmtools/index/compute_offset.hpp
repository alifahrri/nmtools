#ifndef NMTOOLS_ARRAY_INDEX_COMPUTE_OFFSET_HPP
#define NMTOOLS_ARRAY_INDEX_COMPUTE_OFFSET_HPP

#include "nmtools/def.hpp"
#include "nmtools/meta.hpp"
#include "nmtools/utility/at.hpp"
#include "nmtools/utility/unwrap.hpp"
#include "nmtools/utility/has_value.hpp"
#include "nmtools/index/tuple_at.hpp"
#include "nmtools/index/compute_indices.hpp"
#include "nmtools/assert.hpp"

namespace nmtools::index
{
    struct compute_offset_t {};

    // TODO: cleanup index functions
    /**
     * @brief compute offset from given indices and computed strides
     * 
     * Indices to offset (flat index).
     * 
     * @param indices container of indices
     * @param strides container of strides
     * @return constexpr auto 
     */
    template <typename indices_t, typename strides_t>
    nmtools_index_attribute
    constexpr auto compute_offset(const indices_t& indices, const strides_t& strides)
    {
        if constexpr (is_maybe_v<indices_t> || is_maybe_v<strides_t>) {
            using result_t = decltype(compute_offset(unwrap(indices),unwrap(strides)));
            using return_t = conditional_t<is_maybe_v<result_t>,result_t,nmtools_maybe<result_t>>;
            return (has_value(indices) && has_value(strides)
                ? return_t{compute_offset(unwrap(indices),unwrap(strides))}
                : return_t{Nothing}
            );
        } else {
            using result_t = resolve_optype_t<compute_offset_t,indices_t,strides_t>;
            // TODO: enable this
            #if 0
            using return_t = conditional_t<
                !is_fail_v<result_t> && !is_constant_index_array_v<result_t>
                , nmtools_maybe<result_t> // need extra check that m == n
                , result_t
            >;
            #endif

            auto offset = result_t{};

            if constexpr (!is_fail_v<result_t>
                && !is_constant_index_v<result_t>
            ) {
                [[maybe_unused]] auto m = (nm_size_t)len(indices);
                [[maybe_unused]] auto n = (nm_size_t)len(strides);

                // TODO: enable this
                #if 0
                if (m != n) {
                    return return_t{Nothing};
                }
                #endif

                constexpr auto N = len_v<indices_t>;
                constexpr auto M = len_v<strides_t>;

                using index_t = get_index_element_type_t<result_t>;

                if constexpr ((N > 0) && (M > 0)) {
                    offset = 0;
                    template_for<N>([&](auto i){
                        auto stride_i = at(strides,i);
                        auto index_i  = at(indices,i);
                        if (has_value(offset) && has_value(stride_i) && has_value(index_i)) {
                            offset += stride_i * index_i;
                        } else {
                            offset = result_t{};
                        }
                    });
                } else {
                    offset = 0;
                    for (nm_size_t i=0; i<m; i++) {
                        auto stride_i = at(strides,i);
                        auto index_i  = at(indices,i);
                        if (has_value(offset) && has_value(stride_i) && has_value(index_i)) {
                            offset += (index_t)stride_i * (index_t)index_i;
                        } else {
                            offset = result_t{};
                        }
                    }
                }
            }

            // TODO: enable this
            #if 0
            return return_t{offset};
            #else
            return offset;
            #endif
        }
    } // compute_offset

    // this variant handle nested shape/strides
    template <typename indices_t, typename shape_t, typename strides_t>
    constexpr auto compute_offset(const indices_t& indices, [[maybe_unused]] const shape_t& shape, const strides_t& strides)
    {
        if constexpr (is_maybe_v<indices_t> || is_maybe_v<shape_t> || is_maybe_v<strides_t>) {
            using result_t = decltype(compute_offset(unwrap(indices),unwrap(shape),unwrap(strides)));
            using return_t = conditional_t<is_maybe_v<result_t>,result_t,nmtools_maybe<result_t>>;
            return (has_value(indices) && has_value(indices) && has_value(strides)
                ? return_t{compute_offset(unwrap(indices),unwrap(shape),unwrap(strides))}
                : return_t{Nothing}
            );
        } else {
            using result_t = resolve_optype_t<compute_offset_t,indices_t,shape_t,strides_t>;

            auto offset = result_t{};

            if constexpr (!is_fail_v<result_t>
                && !is_constant_index_v<result_t>
            ) {
                [[maybe_unused]] constexpr auto N_INDICES = len_v<indices_t>;
                [[maybe_unused]] constexpr auto N_SHAPE   = len_v<shape_t>;
                [[maybe_unused]] constexpr auto N_STRIDES = len_v<strides_t>;

                using index_t [[maybe_unused]] = get_index_element_type_t<result_t>;

                if constexpr ((N_SHAPE > 0) && (N_STRIDES > 0)) {
                    [[maybe_unused]]
                    auto n_indices = (nm_size_t)len(indices);
                    // assume n_shape == n_strides == n_indices for now
                    // TODO: error handling

                    offset = 0;
                    template_for<N_SHAPE>([&](auto i){
                        [[maybe_unused]]
                        const auto shape_i   = at(shape,i);
                        const auto indices_i = at(indices,i);
                        const auto strides_i = at(strides,i);

                        using shape_i_t   = decltype(shape_i);
                        using strides_i_t = decltype(strides_i);
                        using indices_i_t [[maybe_unused]] = decltype(indices_i);

                        if constexpr (is_index_array_v<shape_i_t> && is_index_array_v<strides_i_t>) {
                            auto indices = index::compute_indices(indices_i,shape_i);
                            if (has_value(offset) && has_value(indices)) {
                                offset += compute_offset(indices,strides_i);
                            } else {
                                offset = result_t{};
                            }
                        } else {
                            // TODO: check if nested
                            if (has_value(offset) && has_value(strides_i) && has_value(indices_i)) {
                                offset += (index_t)strides_i * (index_t)indices_i;
                            } else {
                                offset = result_t{};
                            }
                        }
                    });
                } else {
                    // currently assume no nested index take this path
                    // TODO: handle runtime nested index array
                    [[maybe_unused]] auto m = (nm_size_t)len(indices);
                    [[maybe_unused]] auto n = (nm_size_t)len(strides);
                    offset = 0;
                    for (nm_size_t i=0; i<m; i++) {
                        auto stride_i = at(strides,i);
                        auto index_i  = at(indices,i);
                        if (has_value(offset) && has_value(stride_i) && has_value(index_i)) {
                            offset += (index_t)stride_i * (index_t)index_i;
                        } else {
                            offset = result_t{};
                        }
                    }   
                }
            }

            return offset;
        }
    }
} // namespace nmtools::index

namespace nmtools::meta
{
    namespace error
    {
        template <typename...>
        struct COMPUTE_OFFSET_UNSUPPORTED : detail::fail_t {};
        template <typename...>
        struct COMPUTE_OFFSET_INVALID : detail::fail_t {};
    }

    template <typename indices_t, typename strides_t>
    struct resolve_optype<
        void, index::compute_offset_t, indices_t, strides_t
    > {
        static constexpr auto vtype = [](){
            if constexpr (!is_index_array_v<indices_t>
                || !is_index_array_v<strides_t>
            ) {
                using type = error::COMPUTE_OFFSET_UNSUPPORTED<indices_t,strides_t>;
                return as_value_v<type>;
            } else if constexpr (
                is_constant_index_array_v<indices_t>
                && is_constant_index_array_v<strides_t>
            ) {
                // TODO: also handle clipped index array
                constexpr auto indices = to_value_v<indices_t>;
                constexpr auto strides = to_value_v<strides_t>;
                constexpr auto result  = index::compute_offset(indices,strides);
                if constexpr (has_value(result)) {
                    constexpr auto value = unwrap(result);
                    using type = ct<value>;
                    return as_value_v<type>;
                } else {
                    using type = error::COMPUTE_OFFSET_INVALID<indices_t,strides_t>;
                    return as_value_v<type>;
                }
            } else if constexpr (
                is_mixed_index_array_v<indices_t>
                && is_mixed_index_array_v<strides_t>
            ) {
                using type = nm_size_t;
                return as_value_v<type>;
            } else {
                using index_t  = get_index_element_type_t<indices_t>;
                using stride_t = get_index_element_type_t<strides_t>;
                using type = conditional_t<
                    is_nullable_num_v<index_t> || is_nullable_num_v<stride_t>
                    , null_size_t, nm_size_t>;
                return as_value_v<type>;
            }
        }();

        using type = type_t<decltype(vtype)>;
    };

    template <typename indices_t, typename shape_t, typename strides_t>
    struct resolve_optype<
        void, index::compute_offset_t, indices_t, shape_t, strides_t
    > {
        static constexpr auto vtype = [](){
            if constexpr (!is_index_array_v<indices_t>
                || !is_index_array_v<shape_t>
                || !is_index_array_v<strides_t>
            ) {
                using type = error::COMPUTE_OFFSET_UNSUPPORTED<indices_t,shape_t,strides_t>;
                return as_value_v<type>;
            } else if constexpr (
                is_constant_index_array_v<indices_t>
                && is_constant_index_array_v<shape_t>
                && is_constant_index_array_v<strides_t>
            ) {
                // TODO: also handle clipped index array
                constexpr auto indices = to_value_v<indices_t>;
                constexpr auto shape   = to_value_v<shape_t>;
                constexpr auto strides = to_value_v<strides_t>;
                constexpr auto result  = index::compute_offset(indices,shape,strides);
                using result_t = decltype(unwrap(result));
                if constexpr (has_value(result) && !is_f2_num_v<result_t>) {
                    constexpr auto value = unwrap(result);
                    using type = ct<value>;
                    return as_value_v<type>;
                } else if constexpr (has_value(result) && is_f2_num_v<result_t>) {
                    // TODO: find better way
                    constexpr auto value = unwrap(result).i;
                    using type = f2<ct<value>>;
                    return as_value_v<type>;
                } else {
                    using type = error::COMPUTE_OFFSET_INVALID<indices_t,shape_t,strides_t>;
                    return as_value_v<type>;
                }
            } else if constexpr (
                is_mixed_index_array_v<indices_t>
                && is_mixed_index_array_v<shape_t>
                && is_mixed_index_array_v<strides_t>
            ) {
                using type = get_index_element_type_t<strides_t>;
                return as_value_v<type>;
            } else {
                using index_t  = get_index_element_type_t<indices_t>;
                using dim_t    = get_index_element_type_t<shape_t>;
                using stride_t = get_index_element_type_t<strides_t>;
                using idx_t = conditional_t<
                    is_f2_num_v<index_t> || is_f2_num_v<dim_t> || is_f2_num_v<stride_t>
                    , f2<nm_size_t>
                    , nm_size_t
                >;
                using type  = conditional_t<
                    is_nullable_num_v<index_t> || is_nullable_num_v<stride_t> || is_nullable_num_v<dim_t>
                    , nullable_num<idx_t>, idx_t>;
                return as_value_v<type>;
            }
        }();

        using type = type_t<decltype(vtype)>;
    };
} // namespace nmtools::meta

#endif // NMTOOLS_ARRAY_INDEX_COMPUTE_OFFSET_HPP