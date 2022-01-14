#ifndef NMTOOLS_UTL_ARRAY_HPP
#define NMTOOLS_UTL_ARRAY_HPP

#include "nmtools/dtypes.hpp"
#include "nmtools/meta/bits/transform/common_type.hpp"

// poor man's array,
// very simple and minimalistic implementation of array

namespace nmtools::utl
{
    /**
     * @brief Poor man's array type.
     * 
     * This structure doesn't aim to be fully STL-compatible,
     * only subset of that is used in nmtools.
     * 
     * @tparam T 
     * @tparam N 
     */
    template <typename T, size_t N>
    struct array
    {
        using buffer_type = T[N];
        using value_type  = T;
        using pointer     = T*;
        using reference   = T&;
        using size_type   = size_t;
        using const_pointer   = const T*;
        using const_reference = const T&;

        T buffer[N];

        constexpr reference at(size_t i)
        {
            // TODO: assert/throw
            return buffer[i];
        }

        constexpr const_reference at(size_t i) const
        {
            // TODO: assert/throw
            return buffer[i];
        }

        constexpr auto size() const noexcept
        {
            return N;
        }

        constexpr reference operator[](size_t i) noexcept
        {
            return buffer[i];
        }

        constexpr const_reference operator[](size_t i) const noexcept
        {
            return buffer[i];
        }

        template <size_t I>
        constexpr reference get()
        {
            static_assert( I<N );
            return buffer[I];
        }

        template <size_t I>
        constexpr const_reference get() const
        {
            static_assert( I<N );
            return buffer[I];
        }
    };

    template <typename T, size_t N>
    constexpr auto size(const array<T,N>&)
    {
        return N;
    }

    template <typename T, size_t N>
    constexpr auto begin(const array<T,N>& a)
    {
        return a.buffer;
    }

    template <typename T, size_t N>
    constexpr auto begin(array<T,N>& a)
    {
        return a.buffer;
    }

    template <typename T, size_t N>
    constexpr auto end(const array<T,N>& a)
    {
        return a.buffer + N;
    }

    template <typename T, size_t N>
    constexpr auto end(array<T,N>& a)
    {
        return a.buffer + N;
    }

    // 🤦
    // error: pack expansion used as argument for non-pack parameter of alias template
    // template <typename...Args>
    // array(const Args&...) -> array<meta::common_type_t<Args...>,sizeof...(args)>;

    // allow CTAD
    template <typename...Args>
    array(const Args&...) -> array<typename meta::common_type<Args...>::type,sizeof...(Args)>;


    template <typename T>
    struct tuple_size;

    template <size_t I, typename T>
    struct tuple_element;

    template <typename T, size_t N>
    struct tuple_size<array<T,N>>
    {
        static constexpr auto value = N;
    };

    template <size_t I, typename T, size_t N>
    struct tuple_element<I, array<T,N>>
    {
        static_assert( I < N );
        using type = T;
    };
    
    template <size_t I, typename T, size_t N>
    constexpr decltype(auto) get(const array<T,N>& a)
    {
        return a.template get<I>();
    }

    template <size_t I, typename T, size_t N>
    constexpr decltype(auto) get(array<T,N>& a)
    {
        return a.template get<I>();
    }
} // namespace nmtools::utl

// folowing https://en.cppreference.com/w/cpp/language/structured_binding
// must expose some of metafunction to std namespace 🤦

// NOTE: to avoid ambiguous on clang with libc++,
// apparently on android NDK, the struct is located at std::__ndk1::tuple_size 🤦,
// on emscripten it is 'std::__2::tuple_size' 🤦,
// which triggers ambiguous reference when trying to specialize

#if !defined(__ANDROID__) && !defined(__EMSCRIPTEN__)
namespace std
{
    template <typename T>
    struct tuple_size;

    template <size_t I, typename T>
    struct tuple_element;
} // namespace std
#endif // __ANDROID__ __EMSCRIPTEN__

template <typename T, size_t N>
struct std::tuple_size<nmtools::utl::array<T,N>>
{
    using array_type = nmtools::utl::array<T,N>;
    static constexpr auto value = nmtools::utl::tuple_size<array_type>::value;
};

template <size_t I, typename T, size_t N>
struct std::tuple_element<I,nmtools::utl::array<T,N>>
{
    using array_type = nmtools::utl::array<T,N>;
    using type = typename nmtools::utl::tuple_element<I,array_type>::type;
};

// NOTE: the following const specializations are to please avr-gcc 9

template <typename T, size_t N>
struct std::tuple_size<const nmtools::utl::array<T,N>>
{
    using array_type = nmtools::utl::array<T,N>;
    static constexpr auto value = nmtools::utl::tuple_size<array_type>::value;
};

template <size_t I, typename T, size_t N>
struct std::tuple_element<I,const nmtools::utl::array<T,N>>
{
    using array_type = nmtools::utl::array<T,N>;
    using type = const typename nmtools::utl::tuple_element<I,array_type>::type;
};

#endif // NMTOOLS_UTL_ARRAY_HPP