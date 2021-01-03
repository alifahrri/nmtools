#ifndef NMTOOLS_META_ARITHMETIC_HPP
#define NMTOOLS_META_ARITHMETIC_HPP

#include "nmtools/meta/common.hpp"

#include <type_traits>
#include <utility>
#include <ratio>

namespace nmtools::meta
{
    namespace detail
    {
        template <typename T, typename U>
        struct mul
        {
            using type = void;
        }; // mul

        template <typename T, typename U, auto a, auto b>
        struct mul<std::integral_constant<T,a>,std::integral_constant<U,b>>
        {
            using common_t = std::common_type_t<T,U>;
            using type = std::integral_constant<common_t,a*b>;
        }; // mul

        template <typename T, auto a, auto b, auto c>
        struct mul<std::integral_constant<T,a>,std::ratio<b,c>>
        {
            using type = std::ratio_multiply<std::ratio<a>,std::ratio<b,c>>;
        }; // mul

        template <typename U, auto a, auto b, auto c>
        struct mul<std::ratio<a,b>,std::integral_constant<U,c>>
        {
            using type = std::ratio_multiply<std::ratio<a,b>,std::ratio<c>>;
        }; // mul

        template <auto a, auto b, auto c, auto d>
        struct mul<std::ratio<a,b>,std::ratio<c,d>>
        {
            using type = std::ratio_multiply<std::ratio<a,b>,std::ratio<c,d>>;
        }; // mul
    } // namespace detail

    template <typename T, typename U>
    struct mul
    {
        using type = type_t<detail::mul<T,U>>;
    }; // mul

    namespace detail
    {
        template <typename T, typename U>
        struct add
        {
            using type = void;
        }; // add

        template <typename T, typename U, auto a, auto b>
        struct add<std::integral_constant<T,a>,std::integral_constant<U,b>>
        {
            using common_t = std::common_type_t<T,U>;
            using type = std::integral_constant<common_t,a+b>;
        }; // add

        template <typename T, auto a, auto b, auto c>
        struct add<std::integral_constant<T,a>,std::ratio<b,c>>
        {
            using type = std::ratio_add<std::ratio<a>,std::ratio<b,c>>;
        }; // add

        template <typename U, auto a, auto b, auto c>
        struct add<std::ratio<a,b>,std::integral_constant<U,c>>
        {
            using type = std::ratio_add<std::ratio<a,b>,std::ratio<c>>;
        }; // add

        template <auto a, auto b, auto c, auto d>
        struct add<std::ratio<a,b>,std::ratio<c,d>>
        {
            using type = std::ratio_add<std::ratio<a,b>,std::ratio<c,d>>;
        }; // add
    } // namespace detail

    template <typename T, typename U>
    struct add
    {
        using type = type_t<detail::add<T,U>>;
    }; // add

    namespace detail
    {
        template <typename T, typename U>
        struct sub
        {
            using type = void;
        }; // sub

        template <typename T, typename U, auto a, auto b>
        struct sub<std::integral_constant<T,a>,std::integral_constant<U,b>>
        {
            using common_t = std::common_type_t<T,U>;
            using type = std::integral_constant<common_t,a-b>;
        }; // sub

        template <typename T, auto a, auto b, auto c>
        struct sub<std::integral_constant<T,a>,std::ratio<b,c>>
        {
            using type = std::ratio_subtract<std::ratio<a>,std::ratio<b,c>>;
        }; // sub

        template <typename U, auto a, auto b, auto c>
        struct sub<std::ratio<a,b>,std::integral_constant<U,c>>
        {
            using type = std::ratio_subtract<std::ratio<a,b>,std::ratio<c>>;
        }; // sub

        template <auto a, auto b, auto c, auto d>
        struct sub<std::ratio<a,b>,std::ratio<c,d>>
        {
            using type = std::ratio_subtract<std::ratio<a,b>,std::ratio<c,d>>;
        }; // sub
    } // namespace detail

    template <typename T, typename U>
    struct sub
    {
        using type = type_t<detail::sub<T,U>>;
    }; // sub

    namespace detail
    {
        template <typename T, typename U>
        struct div
        {
            using type = void;
        }; // div

        template <typename T, typename U, auto a, auto b>
        struct div<std::integral_constant<T,a>,std::integral_constant<U,b>>
        {
            using type = std::ratio<a,b>;
        }; // div

        template <auto a, auto b, auto c, auto d>
        struct div<std::ratio<a,b>,std::ratio<c,d>>
        {
            using type = std::ratio_divide<std::ratio<a,b>,std::ratio<c,d>>;
        }; // div

        template <auto a, auto b, typename T, auto c>
        struct div<std::integral_constant<T,c>,std::ratio<a,b>>
        {
            using type = std::ratio_divide<std::ratio<c>,std::ratio<a,b>>;
        }; // div

        template <auto a, auto b, typename T, auto c>
        struct div<std::ratio<a,b>,std::integral_constant<T,c>>
        {
            using type = std::ratio_divide<std::ratio<a,b>,std::ratio<c>>;
        }; // div
    } // namespace detail

    template <typename T, typename U>
    struct div
    {
        using type = type_t<detail::div<T,U>>;
    }; // div

    /**
     * @brief equality compare integral_constant T with constant I
     *
     * Return true if type T is integral_constant and its value is equal to I.
     * 
     * @tparam T 
     * @tparam I 
     */
    template <typename T, auto I>
    using constant_eq = std::is_same<std::integral_constant<decltype(I),I>,T>;

    /**
     * @brief helper variable template for constant_eq
     * 
     * @tparam T 
     * @tparam I 
     */
    template <typename T, auto I>
    static inline constexpr auto constant_eq_v = constant_eq<T,I>::value;

    /**
     * @brief greater-than comparison between type T with constant I.
     *
     * Return true if type T is integral_constant and its value is greater than I.
     * 
     * @tparam T type to test
     * @tparam I constant value
     * @tparam typename 
     */
    template <typename T, auto I, typename=void>
    struct constant_gt : std::false_type {};

    template <auto A, auto B>
    struct constant_gt<
        std::integral_constant<decltype(A),A>, B,
        std::enable_if_t< (A>B) >
    > : std::true_type {};

    /**
     * @brief lower-than comparison between type T with constant I.
     *
     * Return true if type T is integral_constant and its value is lower than I.
     * 
     * @tparam T type to test
     * @tparam I constant value
     * @tparam typename 
     */
    template <typename T, auto I, typename=void>
    struct constant_lt : std::false_type {};

    template <auto A, auto B>
    struct constant_lt<
        std::integral_constant<decltype(A),A>, B,
        std::enable_if_t< (A<B) >
    > : std::true_type {};

} // nmtools

#endif // NMTOOLS_META_ARITHMETIC_HPP