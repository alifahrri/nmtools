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

    template<>
    struct ct_impl_t<void,char,'-','1'>
    {
        constexpr auto operator()() const noexcept
        {
            return meta::ct_v<-1>;
        }
    }; // ct_impl_t

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
    template <typename T, T...cs>
    constexpr auto operator ""_ct()
    {
        return detail::ct_impl_t<void,T,cs...>{}();
    } // ""_ct
#endif // __GNUC__ || __clang__
} // namespace nmtools::literals

#endif // NMTOOLS_CONSTANTS_HPP