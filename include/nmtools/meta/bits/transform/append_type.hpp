#ifndef NMTOOLS_META_BITS_TRANSFORM_APPEND_TYPE_HPP
#define NMTOOLS_META_BITS_TRANSFORM_APPEND_TYPE_HPP

#include "nmtools/meta/common.hpp"

namespace nmtools::meta
{
    namespace error
    {
        struct APPEND_TYPE_UNSUPPORTED : detail::fail_t {};
    } // namespace error

    /**
     * @brief Append new type to the end of some type list.
     * 
     * @tparam T        some type list to be appended
     * @tparam new_type desired new type
     */
    template <typename T, typename new_type>
    struct append_type
    {
        using type = error::APPEND_TYPE_UNSUPPORTED;
    }; // append_type


    template <typename T, typename new_type>
    using append_type_t = type_t<append_type<T,new_type>>;
} // namespace nmtools::meta


#endif // NMTOOLS_META_BITS_TRANSFORM_APPEND_TYPE_HPP