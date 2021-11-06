#ifndef NMTOOLS_META_BITS_TRANSFORM_REMOVE_CVREF_HPP
#define NMTOOLS_META_BITS_TRANSFORM_REMOVE_CVREF_HPP

#include <type_traits>

namespace nmtools::meta
{
    // TODO cleanup metafunctions
    /**
     * @brief helper alias template combining remove_cv and remove_reference
     * 
     * @tparam T 
     */
    template <typename T>
    using remove_cvref_t = std::remove_cv_t<std::remove_reference_t<T>>;
} // namespace nmtools::meta

#endif // NMTOOLS_META_BITS_TRANSFORM_REMOVE_CVREF_HPP