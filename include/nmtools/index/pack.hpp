#ifndef NMTOOLS_ARRAY_INDEX_PACK_HPP
#define NMTOOLS_ARRAY_INDEX_PACK_HPP

#include "nmtools/meta.hpp"

namespace nmtools::index
{
    /**
     * @brief Pack arbitrary number of indices to a single array.
     * If single index are provided and it is not an integral
     * return as it is.
     * 
     * @tparam size_types 
     * @param indices 
     * @return constexpr auto 
     */
    template <typename size_type, typename...size_types>
    constexpr auto pack_indices(size_type index_, size_types...indices)
    {
        if constexpr (is_maybe_v<size_type> || (is_maybe_v<size_types> || ...)) {
            using result_t = decltype(pack_indices(unwrap(index_),unwrap(indices)...));
            using return_t = conditional_t<is_maybe_v<result_t>,result_t,nmtools_maybe<result_t>>;
            return (has_value(index_) && (has_value(indices) && ...)
                ? return_t{pack_indices(unwrap(index_),unwrap(indices)...)}
                : return_t{Nothing}
            );
        } else if constexpr (is_constant_index_v<size_type> || (is_constant_index_v<size_types> || ...)) {
            using result_t = nmtools_tuple<remove_cvref_t<size_type>,remove_cvref_t<size_types>...>;
            return result_t{index_,indices...};
        } else {
            // error: pack expansion used as argument for non-pack parameter of alias template :|
            // using common_t = promote_index_t<size_types...>;
            using common_t = type_t<meta::promote_index<size_type,size_types...>>;
            if constexpr (is_integral_v<common_t>) {
                using array_t = nmtools_array<common_t,1+sizeof...(indices)>;
                return array_t{static_cast<common_t>(index_),static_cast<common_t>(indices)...};
            } else /* if constexpr (is_index_array_v<size_type>) */ {
                static_assert (sizeof...(indices)==0
                    , "unsupported indices for pack"
                );
                return index_;
            }
        }
    } // pack_indices
} // namespace nmtools::index

#endif // NMTOOLS_ARRAY_INDEX_PACK_HPP