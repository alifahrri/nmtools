#ifndef NMTOOLS_PLATFORM_ASSERT_HPP
#define NMTOOLS_PLATFORM_ASSERT_HPP

#include <cassert>
#if __has_include(<optional>)
    #include <optional>
    #define NMTOOLS_HAS_OPTIONAL 1
#else
    #define NMTOOLS_HAS_OPTIONAL 0
#endif // __has_include(<optional>)

#if __has_include(<stdexcept>)
    #include <stdexcept>
    #define NMTOOLS_HAS_STDEXCEPT 1
#else
    #define NMTOOLS_HAS_STDEXCEPT 0
#endif // __has_include(<stdexcept>)

#define nmtools_assert_throw(condition, message, ...) \
    if (!(condition)) throw std::runtime_error(message);

#define nmtools_assert_optional(condition, message, return_type, ...) \
    if (!(condition)) return return_type{std::nullopt};

#define nmtools_make_optional(name, type) \
using name [[maybe_unused]] = nmtools_maybe<type>;

#define nmtools_cassert(condition, ...) \
{ \
    assert(condition); \
}

#ifdef NMTOOLS_USE_EXCEPTION
#define nmtools_assert nmtools_assert_throw
#undef nmtools_cassert
#define nmtools_cassert nmtools_assert_throw
#endif // NMTOOLS_USE_EXCEPTION

#ifdef NMTOOLS_USE_OPTIONAL
#undef nmtools_assert
#define nmtools_assert nmtools_assert_optional
#endif // NMTOOLS_USE_OPTIONAL

#ifndef nmtools_assert
#define nmtools_assert nmtools_cassert
#endif // nmtools_assert

#ifdef NMTOOLS_USE_OPTIONAL
#define nmtools_assert_prepare_type nmtools_make_optional
#else
#define nmtools_assert_prepare_type(name, type) \
using name = type;
#endif // NMTOOLS_USE_OPTIONAL

#ifndef nmtools_panic
#ifdef NMTOOLS_HAS_STDEXCEPT
#define nmtools_panic nmtools_assert_throw
#else
#define nmtools_panic nmtools_cassert
#endif
#endif // nmtools_panic

#endif // NMTOOLS_PLATFORM_ASSERT_HPP