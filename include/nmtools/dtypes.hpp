#ifndef NMTOOLS_DTYPES_HPP
#define NMTOOLS_DTYPES_HPP

#include "nmtools/meta/common.hpp"
#include "nmtools/meta/bits/transform/remove_cvref.hpp"
#include "nmtools/meta/bits/transform/get_element_type.hpp"
// #include "nmtools/meta/bits/transform/to_value.hpp"

#include "nmtools/def.hpp"

namespace nmtools::meta
{
    template <typename T, typename>
    struct to_value;
}

namespace nmtools
{
    enum class DType : int
    {
        UNKNOWN = -1,
        UInt8   = 0,
        UInt16  = 1,
        UInt32  = 2,
        UInt64  = 3,
        Int8    = 4,
        Int16   = 5,
        Int32   = 6,
        Int64   = 7,
        Float32 = 8,
        Float64 = 9,
    };

    template <typename T,typename=void>
    struct dtype_t
    {
        using type = T;

        constexpr auto operator==(DType other) const noexcept
        {
            return meta::to_value<dtype_t,void>::value == other;
        }
    };  // dtype_t

    template <typename T>
    struct is_dtype : meta::false_type {};

    // specialization
    template <typename T>
    struct is_dtype<dtype_t<T>> : meta::true_type {};

    template <typename T>
    constexpr inline auto is_dtype_v = is_dtype<T>::value;

    namespace casting
    {
        enum class Casting {
            AUTO=0,
            EQUIV,
            SAME_KIND
        };
        using auto_t      = meta::as_type<Casting::AUTO>;
        using equiv_t     = meta::as_type<Casting::EQUIV>;
        using same_kind_t = meta::as_type<Casting::SAME_KIND>;

        constexpr inline auto AUTO      = auto_t {};
        constexpr inline auto EQUIV     = equiv_t {};
        constexpr inline auto SAME_KIND = same_kind_t {};

        namespace error
        {
            template <typename...>
            struct CASTING_UNSUPPORTED : meta::detail::fail_t {};
        }
    } // namespace casting

    template <typename T>
    struct get_casting
    {
        static constexpr auto value = casting::error::CASTING_UNSUPPORTED<T>{};
    };

    template <casting::Casting kind>
    struct get_casting<
        meta::as_type<kind>
    > {
        static constexpr auto value = kind;
    };

    template <typename T>
    constexpr inline auto get_casting_v = get_casting<T>::value;

    namespace dtype {
        using float32_t = dtype_t<::nmtools::float32_t>;
        using float64_t = dtype_t<::nmtools::float64_t>;
        using int8_t    = dtype_t<::nmtools::int8_t>;
        using int16_t   = dtype_t<::nmtools::int16_t>;
        using int32_t   = dtype_t<::nmtools::int32_t>;
        using int64_t   = dtype_t<::nmtools::int64_t>;
        using uint8_t   = dtype_t<::nmtools::uint8_t>;
        using uint16_t  = dtype_t<::nmtools::uint16_t>;
        using uint32_t  = dtype_t<::nmtools::uint32_t>;
        using uint64_t  = dtype_t<::nmtools::uint64_t>;

        #ifdef NMTOOLS_HAS_FLOAT16
        using float16_t = dtype_t<::nmtools::float16_t>;
        #endif // NMTOOLS_HAS_FLOAT16
    } // dtype

    // inline variables
    // can be used to specify dtype for ufuncs
    constexpr inline auto float32 = dtype::float32_t {};
    constexpr inline auto float64 = dtype::float64_t {};
    constexpr inline auto int8    = dtype::int8_t    {};
    constexpr inline auto int16   = dtype::int16_t   {};
    constexpr inline auto int32   = dtype::int32_t   {};
    constexpr inline auto int64   = dtype::int64_t   {};
    constexpr inline auto uint8   = dtype::uint8_t   {};
    constexpr inline auto uint16  = dtype::uint16_t  {};
    constexpr inline auto uint32  = dtype::uint32_t  {};
    constexpr inline auto uint64  = dtype::uint64_t  {};

    #ifdef NMTOOLS_HAS_FLOAT16
    constexpr inline auto float16 = dtype::float16_t {};
    #endif // NMTOOLS_HAS_FLOAT16

    /**
     * @brief Helper metafunction to get the type
     * 
     * @tparam T 
     * @tparam typename 
     */
    template <typename T, typename=void>
    struct get_dtype { using type = T; };

    template <typename T>
    struct get_dtype<dtype_t<T>> { using type = T; };
    
    template <typename T>
    using get_dtype_t = typename get_dtype<T>::type;

    template <typename T>
    using lhs_type_t = typename T::lhs_type;

    template <typename T>
    using rhs_type_t = typename T::rhs_type;

    template <typename T>
    using res_type_t = typename T::res_type;

    template <typename T, typename=void>
    struct make_float
    {
        static constexpr auto vtype = [](){
            constexpr auto N = sizeof(T);
            if constexpr (N<=4)
                return meta::as_value_v<float>;
            else return meta::as_value_v<double>;
        }();

        using type = meta::remove_cvref_t<decltype(vtype)>;
    };

    template <typename T>
    using make_float_t = typename make_float<T>::type;

    template <typename array_t>
    constexpr auto type(const array_t&)
    {
        using T = get_element_type_t<array_t>;
        return dtype_t<T>{};
    }

    template <typename T>
    struct is_runtime_dtype : meta::false_type {};

    template <>
    struct is_runtime_dtype<DType> : meta::true_type {};

    template <typename T>
    constexpr inline auto is_runtime_dtype_v = is_runtime_dtype<T>::value;

    constexpr inline auto is_floating_point(const DType dtype)
    {
        return (dtype == DType::Float32)
            || (dtype == DType::Float64)
            ;
    }

    constexpr inline auto is_integer(const DType dtype)
    {
        return (dtype == DType::UInt8)
            || (dtype == DType::UInt16)
            || (dtype == DType::UInt32)
            || (dtype == DType::UInt64)
            || (dtype == DType::Int8)
            || (dtype == DType::Int16)
            || (dtype == DType::Int32)
            || (dtype == DType::Int64)
            ;
    }
    
} // namespace nmtools

namespace nmtools::meta
{
    template <>
    struct to_value<dtype_t<int8_t>,void>
    {
        static constexpr auto value = DType::Int8;
    };

    template <>
    struct to_value<dtype_t<int16_t>,void>
    {
        static constexpr auto value = DType::Int16;
    };

    template <>
    struct to_value<dtype_t<int32_t>,void>
    {
        static constexpr auto value = DType::Int32;
    };

    template <>
    struct to_value<dtype_t<int64_t>,void>
    {
        static constexpr auto value = DType::Int64;
    };
    
    template <>
    struct to_value<dtype_t<uint8_t>,void>
    {
        static constexpr auto value = DType::UInt8;
    };

    template <>
    struct to_value<dtype_t<uint16_t>,void>
    {
        static constexpr auto value = DType::UInt16;
    };

    template <>
    struct to_value<dtype_t<uint32_t>,void>
    {
        static constexpr auto value = DType::UInt32;
    };

    template <>
    struct to_value<dtype_t<uint64_t>,void>
    {
        static constexpr auto value = DType::UInt64;
    };

    template <>
    struct to_value<dtype_t<float>,void>
    {
        static constexpr auto value = DType::Float32;
    };

    template <>
    struct to_value<dtype_t<double>,void>
    {
        static constexpr auto value = DType::Float64;
    };
}

#endif // NMTOOLS_DTYPES_HPP