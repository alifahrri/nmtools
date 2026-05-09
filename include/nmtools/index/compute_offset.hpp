#ifndef NMTOOLS_ARRAY_INDEX_COMPUTE_OFFSET_HPP
#define NMTOOLS_ARRAY_INDEX_COMPUTE_OFFSET_HPP

#include "nmtools/def.hpp"
#include "nmtools/meta.hpp"
#include "nmtools/utility/at.hpp"
#include "nmtools/utility/unwrap.hpp"
#include "nmtools/utility/has_value.hpp"
#include "nmtools/index/tuple_at.hpp"
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

            auto offset = result_t{};

            if constexpr (!is_fail_v<result_t>
                && !is_constant_index_v<result_t>
            ) {
                [[maybe_unused]] auto m = (nm_size_t)len(indices);
                [[maybe_unused]] auto n = (nm_size_t)len(strides);

                constexpr auto N = len_v<indices_t>;
                constexpr auto M = len_v<strides_t>;

                if constexpr ((N > 0) && (M > 0)) {
                    offset = 0;
                    template_for<N>([&](auto i){
                        auto stride_i = at(strides,i);
                        auto index_i  = at(indices,i);
                        if (has_value(offset) && has_value(stride_i) && has_value(index_i)) {
                            offset += (nm_size_t)stride_i * (nm_size_t)index_i;
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
                            offset += (nm_size_t)stride_i * (nm_size_t)index_i;
                        } else {
                            offset = result_t{};
                        }
                    }
                }
            }
            return offset;
        }
    } // compute_offset
} // namespace nmtools::index

namespace nmtools::meta
{
    namespace error
    {
        template <typename...>
        struct COMPUTE_OFFSET_UNSUPPORTED : detail::fail_t {};
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
                using type = ct<result>;
                return as_value_v<type>;
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
} // namespace nmtools::meta

#endif // NMTOOLS_ARRAY_INDEX_COMPUTE_OFFSET_HPP