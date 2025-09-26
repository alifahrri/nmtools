#ifndef NMTOOLS_META_BITS_TRANSFORM_TYPE_NAME_HPP
#define NMTOOLS_META_BITS_TRANSFORM_TYPE_NAME_HPP

#include "nmtools/meta/common.hpp"
#include "nmtools/utl/array.hpp"
#include "nmtools/utl/static_vector.hpp"

// clang and gcc constexpr evaluation limit to 512 calls
// note: constexpr evaluation exceeded maximum depth of 512 calls
// error: 'constexpr' evaluation depth exceeds maximum of 512 (use '-fconstexpr-depth=' to increase the maximum)
constexpr size_t nm_strlen(const char* str)
{
    return *str ? 1 + nm_strlen(str + 1) : 0;
}

#ifndef NMTOOLS_DEFAULT_TYPE_NAME_MAX_BUFFER_SIZE
#define NMTOOLS_DEFAULT_TYPE_NAME_MAX_BUFFER_SIZE (1024*2)
#endif

template <typename T>
constexpr auto nm_get_function_name()
{
    // TODO: wrap macro so that it can be adapted to different compiler
    constexpr auto str = __PRETTY_FUNCTION__;

    #ifdef __clang__
    // auto nm_get_function_name() [T = nmtools::functional::functor_t<@
    auto start = 33;
    #else
    // constexpr auto nm_get_function_name() [with T = nmtools::functio@
    auto start = 48;
    #endif

    constexpr auto max_type_name = NMTOOLS_DEFAULT_TYPE_NAME_MAX_BUFFER_SIZE;
    using type = nmtools::utl::static_vector<char,max_type_name>;
    auto result = type{};
    for (size_t i=start; i<max_type_name; i++) {
        auto s = str[i];
        if (s == ']') {
            result.push_back('\0');
            break;
        } else if (s) {
            result.push_back(s);
        } else {
            break;
        }
    }

    return result;
}

namespace nmtools::meta
{
    template <typename T>
    struct type_name
    {
        static constexpr auto value = nm_get_function_name<T>();
    };

    template <typename T>
    constexpr inline auto type_name_v = type_name<T>::value;
}

#endif // NMTOOLS_META_BITS_TRANSFORM_TYPE_NAME_HPP