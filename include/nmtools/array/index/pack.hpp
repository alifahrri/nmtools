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
        // error: pack expansion used as argument for non-pack parameter of alias template :|
        // using common_t = meta::promote_index_t<size_types...>;
        using common_t = meta::type_t<meta::promote_index<size_type,size_types...>>;
        if constexpr (meta::is_integral_v<common_t>) {
            using array_t = meta::make_array_type_t<common_t,1+sizeof...(indices)>;
            return array_t{index_,indices...};
        } else /* if constexpr (meta::is_index_array_v<size_type>) */ {
            static_assert (sizeof...(indices)==0
                , "unsupported indices for pack"
            );
            return index_;
        }
    } // pack_indices
} // namespace nmtools::index

#endif // NMTOOLS_ARRAY_INDEX_PACK_HPP