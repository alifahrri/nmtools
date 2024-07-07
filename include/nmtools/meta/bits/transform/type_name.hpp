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
#define NMTOOLS_DEFAULT_TYPE_NAME_MAX_BUFFER_SIZE 2048
#endif

template <typename T>
constexpr auto nm_get_function_name()
{
    // TODO: wrap macro so that it can be adapted to different compiler
    constexpr auto str = __PRETTY_FUNCTION__;

    #if 0
    constexpr auto str_len = nm_strlen(str);
    using type = nmtools::utl::array<char,str_len>;
    auto result = type{};
    for (size_t i=0; i<str_len; i++) {
        result[i] = str[i];
    }
    #else
    // avoid constexpr evaluation calls limit
    constexpr auto max_type_name = NMTOOLS_DEFAULT_TYPE_NAME_MAX_BUFFER_SIZE;
    using type = nmtools::utl::static_vector<char,max_type_name>;
    auto result = type{};
    auto size = max_type_name;
    result.resize(size);
    for (size_t i=0; i<max_type_name; i++) {
        auto string = str[i];
        if (string) {
            result[i] = string;
        } else {
            size = i;
            break;
        }
    }
    result.resize(size);
    #endif


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