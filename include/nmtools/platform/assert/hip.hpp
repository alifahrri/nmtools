#ifndef NMTOOLS_PLATFORM_ASSERT_HIP
#define NMTOOLS_PLATFORM_ASSERT_HIP

#define nmtools_assert_optional(condition, message, return_type, ...) \
    if (!(condition)) return return_type{nmtools::meta::Nothing};

#define nmtools_make_optional(name, type) \
using name [[maybe_unused]] = nmtools_maybe<type>;

#define nmtools_cassert(condition, ...) {}

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

#endif // NMTOOLS_PLATFORM_ASSERT_HIP