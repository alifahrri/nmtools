#ifndef NMTOOLS_ARRAY_VIEW_ZEROS_LIKE_HPP
#define NMTOOLS_ARRAY_VIEW_ZEROS_LIKE_HPP

#include "nmtools/meta.hpp"
#include "nmtools/array/view/full.hpp"

namespace nmtools::view
{
    template <typename array_t, typename dtype_t=none_t>
    constexpr auto zeros_like(const array_t& array, dtype_t=dtype_t{})
    {
        auto element_vtype = [](){
            if constexpr (is_none_v<dtype_t>) {
                using element_t = meta::get_element_type_t<array_t>;
                return meta::as_value_v<element_t>;
            } else {
                using element_t = get_dtype_t<dtype_t>;
                return meta::as_value_v<element_t>;
            }
        }();
        using element_t = meta::type_t<decltype(element_vtype)>;
        auto src_shape  = shape<true>(array);
        return full(src_shape,static_cast<element_t>(0));
    }
} // nmtools::view

#endif // NMTOOLS_ARRAY_VIEW_ZEROS_LIKE_HPP