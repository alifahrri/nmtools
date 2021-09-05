#ifndef NMTOOLS_CONSTANTS_HPP
#define NMTOOLS_CONSTANTS_HPP

#include <utility>
#include <array>
#include <type_traits>

namespace nmtools::detail
{
    using std::size_t;

    /**
     * @brief actual implementation of _ct UDL
     * 
     * @tparam N number of elements
     * @param array array of char
     * @return constexpr auto 
     */
    template <size_t N>
    constexpr auto ct_impl(const std::array<char,N>& array)
    {
        auto pow = [](size_t a, size_t b)
        {
            size_t res = 1;
            for (size_t i=0; i<b; i++)
                res *= a;
            return res;
        }; // pow

        auto ret = size_t{0};
        for (size_t i=0; i<N; i++)
            ret += (array.at(i) - '0') * pow(10,N-i-1);
        return ret;
    } // ct_impl

} // nmtools::detail

namespace nmtools::literals
{
    /**
     * @brief define UDL for _ct
     * 
     * Example:
     * \code{.cpp}
     * using namespace nmtools::literals;
     * auto c = 123_ct;
     * using expected_t = std::integral_constant<size_t,123>;
     * STATIC_CHECK_IS_SAME( decltype(c), expected_t );
     * \endcode
     *
     * @tparam cs characters representing the number
     * @return constexpr auto 
     */
    template <char...cs>
    constexpr auto operator ""_ct()
    {
        using std::size_t;
        static_assert( ((cs>='0' && cs<='9') && ...)
            , "unsupported _ct, expect all cs to be digits"
        );

        constexpr auto cs_array = std::array{cs...};
        constexpr auto n = detail::ct_impl(cs_array);
        using type = std::integral_constant<size_t,n>;

        return type{};
    } // _ct
} // namespace nmtools::literals

namespace nmtools
{
    /**
     * @brief specific tag to represents "None" type
     * 
     */
    struct none_t {};

    /**
     * @brief special inline variable to represent "None" value
     * 
     */
    inline constexpr auto None = none_t {};

    /**
     * @brief Special tag to represents "..." a.k.a. "Elipsis" type
     * 
     */
    struct elipsis_t {};

    inline constexpr auto Elipsis = elipsis_t {};

    /**
     * @brief special constant for true_type
     * 
     */
    inline constexpr auto True  = std::true_type {};

    /**
     * @brief sepcial constant for false_type
     * 
     */
    inline constexpr auto False = std::false_type {};

    // TODO: do not directly use std::integral_constant, create meta::make_constant
    /**
     * @brief Special constant to represents "-1"
     * 
     */
    inline constexpr auto Last = std::integral_constant<int,-1>{};

    /**
     * @brief helper traits to check for "None" type
     * 
     * @tparam T 
     */
    template <typename T>
    struct is_none : std::false_type {};

    template <>
    struct is_none<none_t> : std::true_type {};

    /**
     * @brief helper inline variable template to check for "None" type
     * 
     * @tparam T 
     */
    template <typename T>
    inline constexpr auto is_none_v = is_none<T>::value;

    template <typename T>
    struct is_elipsis : std::false_type {};

    template <typename T>
    struct is_elipsis<const T> : is_elipsis<T> {};

    template <typename T>
    struct is_elipsis<const T&> : is_elipsis<T> {};

    template <>
    struct is_elipsis<elipsis_t> : std::true_type {};

    template <typename T>
    inline constexpr auto is_elipsis_v = is_elipsis<T>::value;
} // namespace nmtools

#endif // NMTOOLS_CONSTANTS_HPP