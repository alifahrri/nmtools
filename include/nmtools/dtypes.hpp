#ifndef NMTOOLS_DTYPES_HPP
#define NMTOOLS_DTYPES_HPP

#include "nmtools/meta/common.hpp"
#include "nmtools/meta/bits/transform/remove_cvref.hpp"

#include "nmtools/def.hpp"

namespace nmtools
{
    template <typename T,typename=void>
    struct dtype_t
    {
        using type = T;
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
    
} // namespace nmtools

#endif // NMTOOLS_DTYPES_HPP