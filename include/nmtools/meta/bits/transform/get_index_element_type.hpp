#ifndef NMTOOLS_META_BITS_TRANSFORM_GET_INDEX_ELEMENT_TYPE_HPP
#define NMTOOLS_META_BITS_TRANSFORM_GET_INDEX_ELEMENT_TYPE_HPP

#include "nmtools/meta/common.hpp"
#include "nmtools/meta/bits/traits/is_constant_index.hpp"
#include "nmtools/meta/bits/transform/get_element_or_common_type.hpp"

namespace nmtools::meta
{
    /**
     * @brief provide non-ambiguous runtime index type, given T index array
     * 
     * @tparam T 
     */
    template <typename T>
    struct get_index_element_type
    {
        static constexpr auto vtype = [](){
            using index_t = get_element_or_common_type_t<T>;
            if constexpr (is_constant_index_v<index_t>) {
                using type = typename index_t::value_type;
                return as_value_v<type>;
            } else {
                return as_value_v<index_t>;
            }
        }();
        using type = type_t<decltype(vtype)>;
    }; // get_index_element_type

    template <typename T>
    using get_index_element_type_t = type_t<get_index_element_type<T>>;
} // namespace nmtools::meta


#endif // NMTOOLS_META_BITS_TRANSFORM_GET_INDEX_ELEMENT_TYPE_HPP