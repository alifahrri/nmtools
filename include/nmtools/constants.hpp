#ifndef NMTOOLS_CONSTANTS_HPP
#define NMTOOLS_CONSTANTS_HPP

#include "nmtools/meta.hpp"

// TODO: rename this file to "literals.hpp", use constant.hpp only to define None, Ellipsis...

namespace nmtools::detail
{
    /**
     * @brief actual implementation of _ct UDL
     * 
     * @tparam N number of elements
     * @param array array of char
     * @return constexpr auto 
     */
    template <size_t N, template<typename,size_t> typename array_t >
    constexpr auto ct_impl(const array_t<char,N>& array)
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

    // for gcc extensions
    template <typename always_void,typename T, T...Ts>
    struct ct_impl_t;

    // TODO: support val > 9
    template <char val>
    struct ct_impl_t<
        meta::enable_if_t<
            (val > '0' && val <= '9')
        >
        ,char,'-',val>
    {
        constexpr auto operator()() const noexcept
        {
            constexpr auto value = val - '0';
            return meta::ct_v<-value>;
        }
    }; // ct_impl_t

    // clipped_integer
    template <char val, char max>
    struct ct_impl_t<
        meta::enable_if_t<
            (val >= '0' && val <= '9')
            && (max > '0' && max <= '9')
        >
        ,char,val,':','[',max,']'>
    {
        constexpr auto operator()() const noexcept
        {
            // assume size_t for now
            using type = clipped_integer_t<size_t,0,max>;
            return type{(val - '0')};
        }
    };

    // clipped_integer
    template <char val, char min, char max>
    struct ct_impl_t<
        meta::enable_if_t<
            (val >= '0' && val <= '9')
            && (max > '0' && max <= '9')
            && (min >= '0' && min <= '9')
        >
        ,char,val,':','[',min,',',max,']'>
    {
        constexpr auto operator()() const noexcept
        {
            // assume size_t for now
            using type = clipped_integer_t<size_t,min-'0',max-'0'>;
            return type{(val - '0')};
        }
    };

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
     * using expected_t = meta::integral_constant<size_t,123>;
     * STATIC_CHECK_IS_SAME( decltype(c), expected_t );
     * \endcode
     *
     * @tparam cs characters representing the number
     * @return constexpr auto 
     */
    template <char...cs>
    constexpr auto operator ""_ct()
    {
        static_assert( ((cs>='0' && cs<='9') && ...)
            , "unsupported _ct, expect all cs to be digits"
        );

        constexpr auto N = sizeof...(cs);
        using array_t = meta::make_array_type_t<char,N>;
        constexpr auto cs_array = array_t{cs...};
        constexpr auto n = detail::ct_impl(cs_array);
        using type = meta::integral_constant<size_t,n>;

        return type{};
    } // _ct

#if defined(__GNUC__) or defined(__clang__)
#define NMTOOLS_ENABLE_STRING_LITERAL
#endif // __GNUC__ || __clang__

#ifndef NMTOOLS_DISABLE_STRING_LITERAL // may be supplied by user
#ifdef  NMTOOLS_ENABLE_STRING_LITERAL  // automatically enabled on gcc & clang
    template <typename T, T...cs>
    constexpr auto operator ""_ct()
    {
        return detail::ct_impl_t<void,T,cs...>{}();
    } // ""_ct
#endif // NMTOOLS_ENABLE_STRING_LITERAL
#endif // NMTOOLS_DISABLE_STRING_LITERAL

} // namespace nmtools::literals

#endif // NMTOOLS_CONSTANTS_HPP