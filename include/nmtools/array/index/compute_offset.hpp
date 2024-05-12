#ifndef NMTOOLS_ARRAY_INDEX_COMPUTE_OFFSET_HPP
#define NMTOOLS_ARRAY_INDEX_COMPUTE_OFFSET_HPP

#include "nmtools/def.hpp"
#include "nmtools/meta.hpp"
#include "nmtools/array/utility/at.hpp"
#include "nmtools/array/index/tuple_at.hpp"
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
        using return_t = meta::resolve_optype_t<compute_offset_t,indices_t,strides_t>;

        if constexpr (meta::is_maybe_v<indices_t>) {
            if (static_cast<bool>(indices)) {
                auto result = compute_offset(*indices,strides);
                if constexpr (meta::is_maybe_v<decltype(result)>) {
                    return (result ? return_t{*result} : return_t{meta::Nothing});
                } else {
                    return return_t{result};
                }
            } else {
                return return_t{meta::Nothing};
            }
        } else if constexpr (meta::is_maybe_v<strides_t>) {
            if (static_cast<bool>(strides)) {
                auto result = compute_offset(indices,*strides);
                return return_t{result};
            } else {
                return return_t{meta::Nothing};
            }
        } else if constexpr (
            meta::is_constant_index_v<return_t>
            || meta::is_fail_v<return_t>
        ) {
            auto result = return_t{};
            return result;
        } else {
            using size_type = nm_size_t;
            size_type offset = 0;
            [[maybe_unused]] auto m = (size_type)len(indices);
            [[maybe_unused]] auto n = (size_type)len(strides);
            constexpr auto N = meta::len_v<indices_t>;
            constexpr auto M = meta::len_v<strides_t>;
            if constexpr ((N > 0) && (M > 0)) {
                meta::template_for<N>([&](auto index){
                    offset += static_cast<size_type>(at(strides,index)) * static_cast<size_type>(at(indices,index));
                });
            } else {
                for (size_type i=0; i<m; i++) {
                    offset += static_cast<size_type>(at(strides,i)) * static_cast<size_type>(at(indices,i));
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
            if constexpr (is_maybe_v<indices_t>) {
                using indices_type = get_maybe_type_t<indices_t>;
                using result_type = resolve_optype_t<index::compute_offset_t,indices_type,strides_t>;
                if constexpr (is_maybe_v<result_type>) {
                    using type = result_type;
                    return as_value_v<type>;
                } else {
                    using type = nmtools_maybe<result_type>;
                    return as_value_v<type>;
                }
            } else if constexpr (is_maybe_v<strides_t>) {
                using strides_type = get_maybe_type_t<strides_t>;
                using result_type = resolve_optype_t<index::compute_offset_t,indices_t,strides_type>;
                using type = nmtools_maybe<result_type>;
                return as_value_v<type>;
            } else if constexpr (
                is_constant_index_array_v<indices_t>
                && is_constant_index_array_v<strides_t>
            ) {
                constexpr auto indices = to_value_v<indices_t>;
                constexpr auto strides = to_value_v<strides_t>;
                constexpr auto result  = index::compute_offset(indices,strides);
                using type = ct<result>;
                return as_value_v<type>;
            } else if constexpr (
                is_index_array_v<indices_t>
                && is_index_array_v<strides_t>
            ) {
                using type = nm_size_t;
                return as_value_v<type>;
            } else {
                using type = error::COMPUTE_OFFSET_UNSUPPORTED<indices_t,strides_t>;
                return as_value_v<type>;
            }
        }();

        using type = type_t<decltype(vtype)>;
    };
} // namespace nmtools::meta

#endif // NMTOOLS_ARRAY_INDEX_COMPUTE_OFFSET_HPP