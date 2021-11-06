#ifndef NMTOOLS_META_BITS_TRANSFORM_CONCAT_TYPE_HPP
#define NMTOOLS_META_BITS_TRANSFORM_CONCAT_TYPE_HPP

#include "nmtools/meta/common.hpp"

namespace nmtools::meta
{
    namespace error
    {
        struct CONCAT_TYPE_UNSUPPORTED : detail::fail_t {};
    } // namespace error

    /**
     * @brief Concatenate two type list to single type list.
     * Given List<Ts...> and List<Us...> return List<Ts...,Us...>;
     * 
     * @tparam T type list
     * @tparam U type list
     */
    template <typename T, typename U>
    struct concat_type
    {
        using type = error::CONCAT_TYPE_UNSUPPORTED;
    }; // concat_type

    /**
     * @brief Helper type alias for concat_type
     * 
     * @tparam T type list
     * @tparam U type list
     */
    template <typename T, typename U>
    using concat_type_t = type_t<concat_type<T,U>>;
} // namespace nmtools::meta

#endif // NMTOOLS_META_BITS_TRANSFORM_CONCAT_TYPE_HPP