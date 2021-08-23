#ifndef NMTOOLS_ARRAY_DTYPES_HPP
#define NMTOOLS_ARRAY_DTYPES_HPP

#include "nmtools/constants.hpp"
#include "nmtools/meta.hpp"

#include <type_traits>
#include <cstdint>

namespace nmtools
{
    template <typename T,typename=void>
    struct dtype_t
    {
        using type = T;
    };  // dtype_t

    template <typename T>
    struct is_dtype : std::false_type {};

    // specialization
    template <typename T>
    struct is_dtype<dtype_t<T>> : std::true_type {};

    template <typename T>
    constexpr inline auto is_dtype_v = is_dtype<T>::value;

    namespace dtype {
        using float32_t = dtype_t<float>;
        using float64_t = dtype_t<double>;
        using int8_t    = dtype_t<std::int8_t>;
        using int16_t   = dtype_t<std::int16_t>;
        using int32_t   = dtype_t<std::int32_t>;
        using int64_t   = dtype_t<std::int64_t>;
        using uint8_t   = dtype_t<std::uint8_t>;
        using uint16_t  = dtype_t<std::uint16_t>;
        using uint32_t  = dtype_t<std::uint32_t>;
        using uint64_t  = dtype_t<std::uint64_t>;
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
        static constexpr auto _value = [](){
            constexpr auto N = sizeof(T);
            if constexpr (N<=4)
                return float{};
            else return double{};
        }();

        using type = meta::remove_cvref_t<decltype(_value)>;
    };

    template <typename T>
    using make_float_t = typename make_float<T>::type;
} // namespace nmtools

#endif // NMTOOLS_ARRAY_DTYPES_HPP