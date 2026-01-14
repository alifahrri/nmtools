#ifndef NMTOOLS_CONSTANTS_HPP
#define NMTOOLS_CONSTANTS_HPP

#include "nmtools/meta.hpp"
#include "nmtools/utility/tuple_cat.hpp"

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
    struct ct_impl_t
    {
        constexpr auto operator()() const
        {
            constexpr auto str = [&](){
                auto str = utl::static_string(Ts...);
                str.push_back('\0');
                return str;
            }();
            if constexpr (str == "...") {
                return Ellipsis;
            } else {
                constexpr auto splits = str.split(':');
                constexpr auto N = splits.size();
                return meta::template_reduce<N>([&](auto init, auto I){
                    constexpr auto i = decltype(I)::value;
                    constexpr auto split = splits.at(i);
                    if constexpr (split.size() > 1) {
                        constexpr auto v = utl::stoi(split);
                        return utility::tuple_append(init,ct_v<v>);
                    } else {
                        return utility::tuple_append(init,None);
                    }
                }, nmtools_tuple{});
            }
        }
    };

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
            using type = clipped_integer_t<size_t,0,max-'0'>;
            return type{(val - '0')};
        }
    };

    // clipped_integer
    template <char val1, char val2, char max1, char max2>
    struct ct_impl_t<
        meta::enable_if_t<
            (val1 >= '0' && val1 <= '9')
            && (val2 >= '0' && val2 <= '9')
            && (max1 > '0' && max1 <= '9')
            && (max2 > '0' && max2 <= '9')
        >
        ,char,val1,val2,':','[',max1,max2,']'>
    {
        constexpr auto operator()() const noexcept
        {
            const auto val = ct_impl(nmtools_array{val1,val2});
            const auto max = ct_impl(nmtools_array{max1,max2});
            // assume size_t for now
            using type = clipped_integer_t<size_t,0,max>;
            return type{val};
        }
    };

    // clipped_integer
    template <char val, char max>
    struct ct_impl_t<
        meta::enable_if_t<
            (val >= '0' && val <= '9')
            && (max > '0' && max <= '9')
        >
        ,char,'-',val,':','[',max,']'>
    {
        constexpr auto operator()() const noexcept
        {
            // assume int for now
            constexpr auto value = -(val - '0');
            using type = clipped_integer_t<int,value,max-'0'>;
            return type{value};
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
    template <typename chars_t>
    constexpr auto ct_is_clipped_integer(const chars_t&)
    {
        return false;
    }

    template <typename string_t>
    constexpr auto ct_is_slice(const string_t& str)
    {
        auto result = static_cast<bool>(str.size());
        if (!result) {
            return result;
        }

        auto splits = str.split(':');
        return ((splits.size() == 2) || (splits.size() == 3)) && (str.count('[') == 0) && (str.count(']') == 0);
    }

    template <typename string_t>
    constexpr auto ct_is_number(const string_t& str)
    {
        auto result = static_cast<bool>(str.size());
        if (!result) {
            return result;
        }
        nm_size_t i=0;
        result = result && (((str[i] >= '0') && (str[i] <= '9')) || str[i] == '-');
        for (i=1; result && i<str.size()-1; i++) {
            result = result && (str[i] >= '0') && (str[i] <= '9');
        }
        return result;
    }

    template <typename string_t>
    constexpr auto ct_is_ellipsis(const string_t& str)
    {
        return str == "...";
    }

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
        using array_t = nmtools_array<char,N>;
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

namespace nmtools
{
    template <typename T>
    inline constexpr T pi_v = 3.141592653589793238462643383279502884197;

    inline constexpr auto Pi = pi_v<float>;

    // not everyone has to be saved
} // nmtools

#endif // NMTOOLS_CONSTANTS_HPP