#ifndef NMTOOLS_ASSERT_HPP
#define NMTOOLS_ASSERT_HPP

#include <cassert>

#ifndef nmtools_assert
#define nmtools_assert(condition, message) \
{ \
    assert(condition); \
}
#endif // nmtools_assert

#endif // NMTOOLS_ASSERT_HPP