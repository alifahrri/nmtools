#ifndef NMTOOLS_DEF_HPP
#define NMTOOLS_DEF_HPP

// this file may be used to resolve size_t
// for example, avr gcc should include <stddef.h>
// c++ for opencl can't include but already have size_t
// https://godbolt.org/z/d3vsh5T49
// https://godbolt.org/z/qEGc6orGb

#if __has_include(<stddef.h>)

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
    // use uint8 as bool to avoid vector of bool weirdness, esp. on device kernel
    using bool_t    = uint8_t;
} // namespace nmtools

#else

namespace nmtools
{
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
    using size_t    = uint64_t; // TODO: use uint32 / uint8 when it's more appropiate
    // use uint8 as bool to avoid vector of bool weirdness, esp. on device kernel
    using bool_t    = uint8_t;
}

#endif // __has_include(<stddef.h>)

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
    using clipped_##type = clipped_integer_t<nmtools::type,Min,Max>;

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

#include "nmtools/assert.hpp"

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
     * @brief Special tag to represents "..." a.k.a. "Ellipsis" type
     * 
     */
    struct ellipsis_t {};

    inline constexpr auto Ellipsis = ellipsis_t {};
} // namespace nmtools

namespace nmtools
{
    template <typename T>
    struct nullable_num
    {
        // changing union is c++20 feature
        // TODO: detect if c++20
        #if 0
        union {
            none_t none;
            T num;
        };
        #else
        none_t none = {};
        T num       = {};
        #endif
        enum Tag
        {
            NONE,
            NUMBER,
        };
        Tag tag;

        using value_type = T;

        constexpr nullable_num()
            : none{}
            , tag(Tag::NONE)
        {}

        constexpr nullable_num(T num)
            : num(num)
            , tag(Tag::NUMBER)
        {}

        constexpr auto is_none() const noexcept
        {
            return tag == Tag::NONE;
        }

        constexpr auto is_num() const noexcept
        {
            return tag == Tag::NUMBER;
        }

        constexpr auto has_value() const noexcept
        {
            return is_num();
        }

        constexpr explicit operator bool() const noexcept
        {
            return has_value();
        }

        constexpr decltype(auto) operator=(T t)
        {
            num = t;
            tag = Tag::NUMBER;
            return *this;
        }

        constexpr decltype(auto) operator=(none_t t)
        {
            none = t;
            tag = Tag::NONE;
            return *this;
        }

        constexpr decltype(auto) operator*=(T t)
        {
            if (!is_num()) {
                nmtools_panic( false
                    , "invalid cast for nullable_num" );
            }
            num *= t;
            return *this;
        }

        constexpr decltype(auto) operator/=(T t)
        {
            if (!is_num()) {
                nmtools_panic( false
                    , "invalid cast for nullable_num" );
            }
            num /= t;
            return *this;
        }

        constexpr decltype(auto) operator+=(T t)
        {
            if (!is_num()) {
                nmtools_panic( false
                    , "invalid cast for nullable_num" );
            }
            num += t;
            return *this;
        }

        constexpr decltype(auto) operator-=(T t)
        {
            if (!is_num()) {
                nmtools_panic( false
                    , "invalid cast for nullable_num" );
            }
            num -= t;
            return *this;
        }

        constexpr operator T() const
        {
            if (!is_num()) {
                nmtools_panic( false
                    , "invalid cast for nullable_num" );
            }
            return num;
        }

        constexpr T operator*() const
        {
            if (!is_num()) {
                nmtools_panic( false
                    , "invalid cast for nullable_num" );
            }
            return num;
        }
    };

    using nullable_int      = nullable_num<int>;
    using nullable_long     = nullable_num<long>;
    using nullable_char     = nullable_num<char>;
    using nullable_size_t   = nullable_num<size_t>;
    using nullable_int8_t   = nullable_num<int8_t>;
    using nullable_int16_t  = nullable_num<int16_t>;
    using nullable_int32_t  = nullable_num<int32_t>;
    using nullable_int64_t  = nullable_num<int64_t>;
    using nullable_uint8_t  = nullable_num<uint8_t>;
    using nullable_uint16_t = nullable_num<uint16_t>;
    using nullable_uint32_t = nullable_num<uint32_t>;
    using nullable_uint64_t = nullable_num<uint64_t>;
}

// NOTE: to make it consistent for separate host device compilation
#ifndef nm_size_t
#define nm_size_t ::nmtools::size_t
#endif // nm_size_t

#ifndef nm_index_t
#define nm_index_t int
#endif // nm_index_t

#ifndef nm_bool_t
#define nm_bool_t ::nmtools::bool_t
#endif // nm_bool_t

namespace nmtools
{
    template <typename T>
    struct is_ellipsis;

    // useful for constexpr-ready runtime slice index
    template <typename index_t=nm_index_t>
    struct vslice
    {
        using index_type = nullable_num<index_t>;
        // case [0:-1:2]
        // case [0:-1]
        // case [0]
        index_type index0 = {};
        index_type index1 = {};
        index_type index2 = {};
        // case [0:]
        // case [::2]
        // case [0::-1]
        none_t none0;
        none_t none1;
        none_t none2;
        // case [...]
        ellipsis_t ellipsis;

        enum Tag : int {
            UNKNOWN=-1,
            INDEX=0,
            NONE=1,
            ELLIPSIS=2,
        };
        Tag tag0 = Tag::UNKNOWN;
        Tag tag1 = Tag::UNKNOWN;
        Tag tag2 = Tag::UNKNOWN;

        // slice index can be 1,2,3
        // 0 means invalid
        nm_size_t num = 0;

        constexpr vslice() {}

        // e.g [1]
        constexpr vslice(index_type index0)
            : index0(index0)
            , tag0(Tag::INDEX)
            , num(1)
        {}

        // e.g [1:-1]
        constexpr vslice(index_type index0, index_type index1)
            : index0(index0)
            , index1(index1)
            , tag0(Tag::INDEX)
            , tag1(Tag::INDEX)
            , num(2)
        {}

        // e.g [1:-2:2]
        constexpr vslice(index_type index0, index_type index1, index_type index2)
            : index0(index0)
            , index1(index1)
            , index2(index2)
            , tag0(Tag::INDEX)
            , tag1(Tag::INDEX)
            , tag2(Tag::INDEX)
            , num(3)
        {}

        // e.g [1:]
        constexpr vslice(index_type index0, none_t)
            : index0(index0)
            , none1{}
            , tag0(Tag::INDEX)
            , tag1(Tag::NONE)
            , num(2)
        {}

        // e.g [:]
        constexpr vslice(none_t, none_t)
            : none0{}
            , none1{}
            , tag0(Tag::NONE)
            , tag1(Tag::NONE)
            , num(2)
        {}

        // e.g [:-1]
        constexpr vslice(none_t, index_type index1)
            : none0{}
            , index1(index1)
            , tag0(Tag::NONE)
            , tag1(Tag::INDEX)
            , num(2)
        {}

        // e.g [::]
        constexpr vslice(none_t, none_t, none_t)
            : none0{}
            , none1{}
            , none2{}
            , tag0(Tag::NONE)
            , tag1(Tag::NONE)
            , tag2(Tag::NONE)
            , num(3)
        {}

        // e.g [1::]
        constexpr vslice(index_type index0, none_t, none_t)
            : index0(index0)
            , none1{}
            , none2{}
            , tag0(Tag::INDEX)
            , tag1(Tag::NONE)
            , tag2(Tag::NONE)
            , num(3)
        {}

        // e.g [1:-2:]
        constexpr vslice(index_type index0, index_type index1, none_t)
            : index0(index0)
            , index1(index1)
            , none2{}
            , tag0(Tag::INDEX)
            , tag1(Tag::INDEX)
            , tag2(Tag::NONE)
            , num(3)
        {}

        // e.g [:-1:]
        constexpr vslice(none_t, index_type index1, none_t)
            : none0{}
            , index1(index1)
            , none2{}
            , tag0(Tag::NONE)
            , tag1(Tag::INDEX)
            , tag2(Tag::NONE)
            , num(3)
        {}

        // e.g [::-1]
        constexpr vslice(none_t, none_t, index_type index2)
            : none0{}
            , none1{}
            , index2(index2)
            , tag0(Tag::NONE)
            , tag1(Tag::NONE)
            , tag2(Tag::INDEX)
            , num(3)
        {}

        // e.g [2::-1]
        constexpr vslice(index_type index0, none_t, index_type index2)
            : index0(index0)
            , none1{}
            , index2(index2)
            , tag0(Tag::NONE)
            , tag1(Tag::NONE)
            , tag2(Tag::INDEX)
            , num(3)
        {}

        // e.g [:-1:2]
        constexpr vslice(none_t, index_type index1, index_type index2)
            : none0{}
            , index1(index1)
            , index2(index2)
            , tag0(Tag::NONE)
            , tag1(Tag::INDEX)
            , tag2(Tag::INDEX)
            , num(3)
        {}

        constexpr vslice(ellipsis_t ellipsis)
            : ellipsis(ellipsis)
            , tag0(Tag::ELLIPSIS)
            , num(1)
        {}

        template <typename T>
        constexpr operator T() const
        {
            T result;

            if constexpr (is_ellipsis<T>::value) {
                if (tag0 != Tag::ELLIPSIS) {
                    nmtools_panic( false
                        , "invalid cast to Ellipsis");
                }
                result = ellipsis_t{};
            }

            return result;
        }
    };
}

#endif // NMTOOLS_DEF_HPP