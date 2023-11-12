#ifndef NMTOOLS_DEF_HPP
#define NMTOOLS_DEF_HPP

// this file may be used to resolve size_t
// for example, avr gcc should include <stddef.h>
// c++ for opencl can't include but already have size_t
// https://godbolt.org/z/d3vsh5T49
// https://godbolt.org/z/qEGc6orGb

#ifdef ARDUINO

#include <stddef.h>
#include <stdint.h>

namespace nmtools
{
    using size_t = ::size_t;
    using float32_t = float;
    using float64_t = double;
    using int8_t    = ::int8_t;
    using int16_t   = ::int16_t;
    using int32_t   = ::int32_t;
    using int64_t   = ::int64_t;
    using uint8_t   = ::uint8_t;
    using uint16_t  = ::uint16_t;
    using uint32_t  = ::uint32_t;
    using uint64_t  = ::uint64_t;
} // namespace nmtools

#elif defined(__OPENCL_VERSION__)

namespace nmtools
{
    using size_t = size_t;
    using float32_t = float;
    using float64_t = double;
    using int8_t    = char;
    using int16_t   = short;
    using int32_t   = int;
    using int64_t   = long;
    using uint8_t   = unsigned char;
    using uint16_t  = unsigned short;
    using uint32_t  = unsigned int;
    using uint64_t  = unsigned long;
}

#elif defined(__CUDA__)

namespace nmtools
{
    using size_t = size_t;
    using float32_t = float;
    using float64_t = double;
    using int8_t    = char;
    using int16_t   = short;
    using int32_t   = int;
    using int64_t   = long;
    using uint8_t   = unsigned char;
    using uint16_t  = unsigned short;
    using uint32_t  = unsigned int;
    using uint64_t  = unsigned long;
}

#else // (not ARDUINO)
#include <cstddef>
#include <cstdint>

namespace nmtools
{
    using size_t = std::size_t;
    using float32_t = float;
    using float64_t = double;
    using int8_t    = std::int8_t;
    using int16_t   = std::int16_t;
    using int32_t   = std::int32_t;
    using int64_t   = std::int64_t;
    using uint8_t   = std::uint8_t;
    using uint16_t  = std::uint16_t;
    using uint32_t  = std::uint32_t;
    using uint64_t  = std::uint64_t;
}
#endif // ARDUINO

namespace nmtools
{
    template <typename T, auto Min, auto Max>
    struct clipped_integer_t
    {
        using value_type = T;

        static constexpr auto min = Min;
        static constexpr auto max = Max;

        static_assert( (min < max), "invalid value for Min and Max, expect Min < Max" );

        constexpr clipped_integer_t() {}

        constexpr clipped_integer_t(const clipped_integer_t& other)
            : value(other.value)
        {}

        constexpr clipped_integer_t(T other)
            : value(other > Max ? Max : (other < Min ? Min : other))
        {}

        constexpr operator T() const noexcept
        {
            return value;
        }

        constexpr clipped_integer_t& operator=(clipped_integer_t other)
        {
            // from same type with same Min Max
            value = other.value;

            return *this;
        }

        constexpr clipped_integer_t& operator=(T other)
        {
            *this = clipped_integer_t{other};

            return *this;
        }

        // avoid ambiguous call to operator
        #if 0
        clipped_integer_t operator+(T other) const noexcept
        {
            return clipped_integer_t{T(value + other)};
        }

        clipped_integer_t operator-(T other) const noexcept
        {
            return clipped_integer_t{T(value - other)};
        }
        #endif

        template <auto OtherMin, auto OtherMax>
        constexpr clipped_integer_t& operator=(clipped_integer_t<T,OtherMin,OtherMax> other)
        {
            *this = {(T)other};
            return *this;
        }

        template <typename U, auto OtherMin, auto OtherMax>
        constexpr clipped_integer_t& operator=(clipped_integer_t<U,OtherMin,OtherMax> other)
        {
            *this = {(T)other};
            return *this;
        }

        private:
        T value = Min;
    }; // clipped_integer_t

    #define NMTOOLS_DECLARE_CLIPPED_TYPE(type) \
    template <auto Max, auto Min=0> \
    using clipped_##type = clipped_integer_t<type,Min,Max>;

    NMTOOLS_DECLARE_CLIPPED_TYPE(size_t)
    NMTOOLS_DECLARE_CLIPPED_TYPE(int8_t)
    NMTOOLS_DECLARE_CLIPPED_TYPE(int16_t)
    NMTOOLS_DECLARE_CLIPPED_TYPE(int32_t)
    NMTOOLS_DECLARE_CLIPPED_TYPE(int64_t)
    NMTOOLS_DECLARE_CLIPPED_TYPE(uint8_t)
    NMTOOLS_DECLARE_CLIPPED_TYPE(uint16_t)
    NMTOOLS_DECLARE_CLIPPED_TYPE(uint32_t)
    NMTOOLS_DECLARE_CLIPPED_TYPE(uint64_t)

    #undef NMTOOLS_DECLARE_CLIPPED_TYPE
}

// NOTE: to make it consistent for separate host device compilation
#ifndef nm_size_t
#define nm_size_t unsigned int
#endif // nm_size_t

// NOTE: using int here breaks c++ for opencl kernel compilation (invalid cast)
#ifndef nm_index_t
#define nm_index_t unsigned int
#endif // nm_index_t

#endif // NMTOOLS_DEF_HPP