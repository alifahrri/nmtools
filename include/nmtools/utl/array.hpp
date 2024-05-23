#ifndef NMTOOLS_UTL_ARRAY_HPP
#define NMTOOLS_UTL_ARRAY_HPP

#include "nmtools/platform.hpp"
#include "nmtools/dtypes.hpp"
#include "nmtools/utl/common.hpp"
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
    template <typename T, nm_size_t N>
    struct array
    {
        #if 1
        using data_type = meta::remove_address_space_t<T>;
        #else
        using data_type = T;
        #endif
        using buffer_type = data_type[N];
        using value_type  = data_type;
        using pointer     = data_type*;
        using reference   = data_type&;
        using size_type   = nm_utl_size_t;
        using index_type  = nm_utl_index_t;
        using const_pointer   = const data_type*;
        using const_reference = const data_type&;

        data_type buffer[N];

        constexpr reference at(index_type i)
        {
            // TODO: assert/throw
            return buffer[i];
        }

        constexpr const_reference at(index_type i) const
        {
            // TODO: assert/throw
            return buffer[i];
        }

        constexpr auto size() const noexcept
        {
            return (size_type)N;
        }

        // The following is intended to enable copy assignment of maybe<array> type in constexpr function/lambda
        // but then it deprecates the definition of implicit copy constructor
        #if 0
        constexpr array& operator=(const array& other) noexcept
        {
            for (nm_size_t i=0; i<N; i++) {
                buffer[i] = other.buffer[i];
            }
            return *this;
        }
        #endif

        constexpr reference operator[](index_type i) noexcept
        {
            return buffer[i];
        }

        constexpr const_reference operator[](index_type i) const noexcept
        {
            return buffer[i];
        }

        constexpr pointer data()
        {
            return buffer;
        }

        constexpr const_pointer data() const
        {
            return buffer;
        }

        // TODO: try to avoid macro branching
        #ifndef __OPENCL_VERSION__
        template <nm_size_t I>
        constexpr reference get()
        {
            static_assert( I<N );
            return buffer[I];
        }

        template <nm_size_t I>
        constexpr const_reference get() const
        {
            static_assert( I<N );
            return buffer[I];
        }
        #endif // __OPENCL_VERSION__
    };

    template <typename T, nm_size_t N>
    constexpr auto size(const array<T,N>&)
    {
        return (nm_utl_size_t)N;
    }

    template <typename T, nm_size_t N>
    constexpr auto begin(const array<T,N>& a)
    {
        return a.buffer;
    }

    template <typename T, nm_size_t N>
    constexpr auto begin(array<T,N>& a)
    {
        return a.buffer;
    }

    template <typename T, nm_size_t N>
    constexpr auto end(const array<T,N>& a)
    {
        return a.buffer + (nm_utl_index_t)N;
    }

    template <typename T, nm_size_t N>
    constexpr auto end(array<T,N>& a)
    {
        return a.buffer + (nm_utl_index_t)N;
    }

    // 🤦
    // error: pack expansion used as argument for non-pack parameter of alias template
    // template <typename...Args>
    // array(const Args&...) -> array<meta::common_type_t<Args...>,sizeof...(args)>;

    // allow CTAD
    template <typename...Args>
    nmtools_func_attribute
    array(const Args&...) -> array<typename meta::common_type<Args...>::type,sizeof...(Args)>;


    template <typename T>
    struct tuple_size;

    template <nm_size_t I, typename T>
    struct tuple_element;

    template <typename T, nm_size_t N>
    struct tuple_size<array<T,N>>
    {
        static constexpr auto value = N;
    };

    template <nm_size_t I, typename T, nm_size_t N>
    struct tuple_element<I, array<T,N>>
    {
        static_assert( I < N );
        using type = T;
    };
    
    template <nm_size_t I, typename T, nm_size_t N>
    constexpr decltype(auto) get(const array<T,N>& a)
    {
        // TODO: try to avoid macro branching
        #ifndef __OPENCL_VERSION__
        return a.template get<I>();
        #else
        return a.buffer[(nm_utl_index_t)I];
        #endif // __OPENCL_VERSION__
    }

    template <nm_size_t I, typename T, nm_size_t N>
    constexpr decltype(auto) get(array<T,N>& a)
    {
        // TODO: try to avoid macro branching
        #ifndef __OPENCL_VERSION__
        return a.template get<I>();
        #else
        return a.buffer[(nm_utl_index_t)I];
        #endif // __OPENCL_VERSION__
    }
} // namespace nmtools::utl

// folowing https://en.cppreference.com/w/cpp/language/structured_binding
// must expose some of metafunction to std namespace 🤦

// NOTE: to avoid ambiguous on clang with libc++,
// apparently on android NDK, the struct is located at std::__ndk1::tuple_size 🤦,
// on emscripten it is 'std::__2::tuple_size' 🤦,
// which triggers ambiguous reference when trying to specialize

// make sure to follow stl tuple, if has stl
#if __has_include(<tuple>)
#include <tuple>
#else
namespace std
{
    template <typename T>
    struct tuple_size;

    template <nm_size_t I, typename T>
    struct tuple_element;
} // namespace std
#endif // <tuple>

template <typename T, nm_size_t N>
struct std::tuple_size<nmtools::utl::array<T,N>>
{
    using array_type = nmtools::utl::array<T,N>;
    static constexpr auto value = nmtools::utl::tuple_size<array_type>::value;
};

template <nm_size_t I, typename T, nm_size_t N>
struct std::tuple_element<I,nmtools::utl::array<T,N>>
{
    using array_type = nmtools::utl::array<T,N>;
    using type = typename nmtools::utl::tuple_element<I,array_type>::type;
};

// NOTE: the following const specializations are to please avr-gcc 9

template <typename T, nm_size_t N>
struct std::tuple_size<const nmtools::utl::array<T,N>>
{
    using array_type = nmtools::utl::array<T,N>;
    static constexpr auto value = nmtools::utl::tuple_size<array_type>::value;
};

template <nm_size_t I, typename T, nm_size_t N>
struct std::tuple_element<I,const nmtools::utl::array<T,N>>
{
    using array_type = nmtools::utl::array<T,N>;
    using type = const typename nmtools::utl::tuple_element<I,array_type>::type;
};

#ifdef NMTOOLS_HAS_ADDRESS_SPACE

template <typename array_type>
struct std::tuple_size<nmtools_address_private array_type>
    : std::tuple_size<array_type> {};

template <typename array_type>
struct std::tuple_size<nmtools_address_generic array_type>
    : std::tuple_size<array_type> {};

template <nm_size_t I, typename array_type>
struct std::tuple_element<I,nmtools_address_private array_type>
    : std::tuple_element<I,array_type> {};

template <nm_size_t I, typename array_type>
struct std::tuple_element<I,nmtools_address_generic array_type>
    : std::tuple_element<I,array_type> {};

#endif // NMTOOLS_HAS_ADDRESS_SPACE

#endif // NMTOOLS_UTL_ARRAY_HPP