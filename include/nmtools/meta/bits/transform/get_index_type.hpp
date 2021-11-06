#ifndef NMTOOLS_META_BITS_TRANSFORM_GET_INDEX_TYPE_HPP
#define NMTOOLS_META_BITS_TRANSFORM_GET_INDEX_TYPE_HPP

#include "nmtools/meta/common.hpp"

namespace nmtools::meta
{
    namespace error
    {
        // default type (error-type) for get_index_type
        struct GET_INDEX_TYPE_UNSUPPORTED : detail::fail_t {};
    } // namespace error

    template <typename array_t, typename=void>
    struct get_index_type
    {
        using type = error::GET_INDEX_TYPE_UNSUPPORTED;
    }; // get_index_type

    template <typename array_t>
    using get_index_type_t = type_t<get_index_type<array_t>>;
} // namespace nmtools::meta

#endif // NMTOOLS_META_BITS_TRANSFORM_GET_INDEX_TYPE_HPP