#ifndef NMTOOLS_PLATFORM_ASSERT_HPP
#define NMTOOLS_PLATFORM_ASSERT_HPP

#include <assert.h>

// TODO: support maybe type (using utl's maybe)
#define nmtools_assert_prepare_type(name, type) \
using name = type;

#define nmtools_cassert(condition, ...) \
{ \
    assert(condition); \
}

#define nmtools_assert nmtools_cassert

#define nmtools_make_optional(name, type) \
using name [[maybe_unused]] = nmtools_maybe<type>;

#ifndef nmtools_panic
#ifdef NMTOOLS_HAS_STDEXCEPT
#define nmtools_panic nmtools_assert_throw
#else
#define nmtools_panic nmtools_cassert
#endif
#endif // nmtools_panic

#endif // NMTOOLS_PLATFORM_ASSERT_HPP