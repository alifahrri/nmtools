#ifndef NMTOOLS_UTILS_TO_STRING_TO_STRING_HPP
#define NMTOOLS_UTILS_TO_STRING_TO_STRING_HPP

#if __has_include(<string>)
    #define NMTOOLS_HAS_STRING true
    #include <string>
    #define nmtools_string std::string
    // NOTE: quick hack, arduino (esp. atmel avr) doesn't have std::to_string
    // TODO: find better alternative
    #define nmtools_to_string std::to_string
#elif defined(ARDUINO)
    // TODO: do not include arduino here (?)
    #include <Arduino.h>
    #define NMTOOLS_HAS_STRING true
    #define nmtools_string String
    // NOTE: quick hack
    // TODO: find better alternative
    #define nmtools_to_string String
#else
#define NMTOOLS_HAS_STRING false
#endif

// TODO: remove this HAS_STRING macro, prefer NMTOOLS_HAS_STRING
#define HAS_STRING NMTOOLS_HAS_STRING

#if __has_include(<sstream>)
#include <sstream>
#define NMTOOLS_HAS_SSTREAM true
#define nmtools_sstream ::std::stringstream
#else
#define NMTOOLS_HAS_SSTREAM false
#endif

#if defined(__clang__)
  #if __has_feature(cxx_rtti)
    #define NMTOOLS_HAS_RTTI
  #endif
#elif defined(__GNUG__)
  #if defined(__GXX_RTTI)
    #define NMTOOLS_HAS_RTTI
  #endif
#elif defined(_MSC_VER)
  #if defined(_CPPRTTI)
    #define NMTOOLS_HAS_RTTI
  #endif
#endif


#if __has_include(<boost/type_index.hpp>)
    #include <boost/type_index.hpp>
    #define NMTOOLS_TYPENAME_TO_STRING(type) \
    boost::typeindex::type_id<type>().pretty_name()
#elif defined(NMTOOLS_HAS_RTTI)
    #define NMTOOLS_TYPENAME_TO_STRING(type) \
    typeid(type).name()
#else
    #define NMTOOLS_TYPENAME_TO_STRING(type) ""
#endif

#include "nmtools/meta.hpp"

#if NMTOOLS_HAS_STRING
namespace nmtools::utils
{
    #if 0
    // NOTE: forward declare function here to allow function object to_string_t to
    // call the function,
    // this is because to_string_t can't deduce template args automatically (no constructor, and operator() cant be static)
    // TODO: revisit this and maybe refactor
    template <typename formatter_t=none_t, typename T>
    auto to_string(const T& array, formatter_t=formatter_t{}) -> nmtools_string;
    #endif

    struct graphviz_t {};

    constexpr inline auto Graphviz = graphviz_t {};
}

namespace nmtools::utils::impl
{
    template <typename T, typename formatter_t, typename=void>
    struct to_string_t;
}

namespace nmtools::utils
{
    /**
     * @brief to_string given array to given stream type.
     * 
     * @tparam stream_t stream type, e.g. std::stringstream,
     * @tparam T array-like, 2d, 1d, or scalar
     * @param array array to to_string
     * @return auto stream with type of stream_t
     */
    template <typename formatter_t=none_t, typename T>
    auto to_string(const T& array, formatter_t=formatter_t{}) -> nmtools_string
    {
        constexpr auto to_string_impl = impl::to_string_t<T,formatter_t>{};
        return to_string_impl(array);
    } // auto to_string
} // namespace nmtools::utils
#endif // NMTOOLS_HAS_STRING

#endif // NMTOOLS_UTILS_TO_STRING_TO_STRING_HPP