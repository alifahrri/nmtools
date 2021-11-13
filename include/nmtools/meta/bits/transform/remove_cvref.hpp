#ifndef NMTOOLS_META_BITS_TRANSFORM_REMOVE_CVREF_HPP
#define NMTOOLS_META_BITS_TRANSFORM_REMOVE_CVREF_HPP

#include "nmtools/meta/common.hpp"

namespace nmtools::meta
{
    /**
     * @brief remove const and volatile
     * 
     * @tparam T 
     */
    template <typename T>
    struct remove_cv
    {
        using type = T;
    };

    template <typename T>
    using remove_cv_t = type_t<remove_cv<T>>;

    /**
     * @brief remove reference
     * 
     * @tparam T 
     */
    template <typename T>
    struct remove_reference
    {
        using type = T;
    };

    template <typename T>
    using remove_reference_t = type_t<remove_reference<T>>;

    /**
     * @brief helper alias template combining remove_cv and remove_reference
     * 
     * @tparam T 
     */
    template <typename T>
    using remove_cvref_t = remove_cv_t<remove_reference_t<T>>;
} // namespace nmtools::meta

// specializations:
namespace nmtools::meta
{
    template <typename T>
    struct remove_cv<const T>
    {
        using type = T;
    };

    template <typename T>
    struct remove_cv<volatile T>
    {
        using type = T;
    };

    template <typename T>
    struct remove_cv<const volatile T>
    {
        using type = T;
    };

    template <typename T>
    struct remove_reference<T&>
    {
        using type = T;
    };

    template <typename T>
    struct remove_reference<T&&>
    {
        using type = T;
    };
} // namespace nmtools::meta

#endif // NMTOOLS_META_BITS_TRANSFORM_REMOVE_CVREF_HPP