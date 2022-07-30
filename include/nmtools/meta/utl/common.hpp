#ifndef NMTOOLS_META_UTL_COMMON_HPP
#define NMTOOLS_META_UTL_COMMON_HPP

#include "nmtools/meta/common.hpp"
#include "nmtools/utl/array.hpp"
#include "nmtools/utl/either.hpp"
#include "nmtools/utl/maybe.hpp"
#include "nmtools/utl/tuple.hpp"
#include "nmtools/utl/vector.hpp"

namespace nmtools::meta
{
#ifndef NMTOOLS_META_MAKE_MAYBE_TYPE
#define NMTOOLS_META_MAKE_MAYBE_TYPE

    template <typename T, typename>
    struct make_maybe_type
    {
        using type = utl::maybe<T>;
    };

    template <typename T>
    using make_maybe_type_t = type_t<make_maybe_type<T>>;

    inline constexpr auto Nothing = utl::nothing;

    // alias template doesn't have ctad:
    // https://godbolt.org/z/51zMTrEGK
    // so use macro for now
    #define nmtools_maybe ::nmtools::utl::maybe
#endif // NMTOOLS_META_MAKE_MAYBE_TYPE

#ifndef NMTOOLS_META_MAKE_TUPLE
#define NMTOOLS_META_MAKE_TUPLE

    template <typename...Ts>
    struct make_tuple
    {
        using type = utl::tuple<Ts...>;
    };

    template <typename...Ts>
    using make_tuple_type_t = type_t<make_tuple<Ts...>>;

    // alias template doesn't have ctad:
    // https://godbolt.org/z/51zMTrEGK
    // so use macro for now
    #define nmtools_tuple ::nmtools::utl::tuple
#endif // NMTOOLS_MEtA_MAKE_TUPLE

#ifndef NMTOOLS_META_MAKE_ARRAY_TYPE
#define NMTOOLS_META_MAKE_ARRAY_TYPE

    template <typename T, size_t N, typename>
    struct make_array_type
    {
        using type = utl::array<T,N>;
    };

    template <typename T, size_t N>
    using make_array_type_t = type_t<make_array_type<T,N>>;

    // alias template doesn't have ctad, use macro
    #define nmtools_array ::nmtools::utl::array
#endif // NMTOOLS_META_MAKE_ARRAY_TYPE

#ifndef NMTOOLS_META_MAKE_EITHER
#define NMTOOLS_META_MAKE_EITHER

    template <typename left_t, typename right_t, typename>
    struct make_either_type
    {
        using type = utl::either<left_t,right_t>;
    };

    template <typename left_t, typename right_t>
    using make_either_type_t = type_t<make_either_type<left_t,right_t>>;

    // alias template doesn't have ctad:
    // https://godbolt.org/z/51zMTrEGK
    // so use macro for now
    #define nmtools_either ::nmtools::utl::either
#endif // NMTOOLS_META_MAKE_EITHER

#ifndef NMTOOLS_META_MAKE_SEQUENCE
#define NMTOOLS_META_MAKE_SEQUENCE

    namespace error
    {
        template <typename...>
        struct UTL_SEQUENCE_UNSUPPORTED : detail::fail_t {};
    }

    // TODO: support sequence type by adding utl::vector
    template <typename T, typename Allocator>
    struct make_sequence_type
    {
        using type = utl::vector<T,Allocator>;
    };

    template <typename T, typename Allocator=utl::allocator<T>>
    using make_sequence_type_t = type_t<make_sequence_type<T,Allocator>>;

    // TODO: support sequence type by adding utl::vector
    #define nmtools_list ::nmtools::utl::vector

#endif // NMTOOLS_META_MAKE_SEQUENCE
} // namespace nmtools::meta

#endif // NMTOOLS_META_UTL_COMMON_HPP