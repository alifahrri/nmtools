#ifndef NMTOOLS_ASSERT_HPP
#define NMTOOLS_ASSERT_HPP

#include <cassert>
#if __has_include(<optional>)
    #include <optional>
    #define NMTOOLS_HAS_OPTIONAL 1
#else
    #define NMTOOLS_HAS_OPTIONAL 0
#endif
#if __has_include(<stdexcept>)
    #include <stdexcept>
    #define NMTOOLS_HAS_STDEXCEPT 1
#else
    #define NMTOOLS_HAS_STDEXCEPT 0
#endif

#define nmtools_assert_throw(condition, message, ...) \
    if (!condition) throw std::runtime_error(message);

#define nmtools_assert_optional(condition, message, return_type, ...) \
    if (!condition) return return_type{std::nullopt};

#define nmtools_make_optional(name, type) \
using name = std::optional<type>;

#ifdef NMTOOLS_USE_EXCEPTION
#define nmtools_assert nmtools_assert_throw
#endif

#ifdef NMTOOLS_USE_OPTIONAL
#undef nmtools_assert
#define nmtools_assert nmtools_assert_optional
#endif

#ifndef nmtools_assert
#define nmtools_assert(condition, message, ...) \
{ \
    assert(condition); \
}
#endif // nmtools_assert

#ifdef NMTOOLS_USE_OPTIONAL
#define nmtools_assert_prepare_type nmtools_make_optional
#else
#define nmtools_assert_prepare_type(name, type) \
using name = type;
#endif

#endif // NMTOOLS_ASSERT_HPP