#include "nmtools/array/ufuncs/greater_equal.hpp"
#include "nmtools/context/default.hpp"
#include "nmtools/testing/data/array/greater_equal.hpp"
#include "nmtools/testing/doctest.hpp"

#include <vector>
#include <array>
#include <algorithm>

namespace nm = nmtools;
namespace na = nmtools;

#define GREATER_EQUAL_SUBCASE(case_name, ...) \
SUBCASE(#case_name) \
{ \
    NMTOOLS_TESTING_USE_CASE(view, greater_equal, case_name); \
    using namespace args; \
    auto result = nm::greater_equal(__VA_ARGS__); \
    NMTOOLS_ASSERT_EQUAL( ::nm::shape(result), expect::shape ); \
    NMTOOLS_ASSERT_CLOSE( result, expect::result ); \
}

TEST_CASE("greater_equal(case1)" * doctest::test_suite("array::greater_equal"))
{
    GREATER_EQUAL_SUBCASE( case1,   a,   b );
    GREATER_EQUAL_SUBCASE( case1, a_a, b_a );
    GREATER_EQUAL_SUBCASE( case1, a_f, b_f );
}

TEST_CASE("greater_equal(case2)" * doctest::test_suite("array::greater_equal"))
{
    GREATER_EQUAL_SUBCASE( case2,   a, b );
    GREATER_EQUAL_SUBCASE( case2, a_a, b );
    GREATER_EQUAL_SUBCASE( case2, a_f, b );
}
