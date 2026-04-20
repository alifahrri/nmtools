#include "nmtools/array/ufuncs/not_equal.hpp"
#include "nmtools/context/default.hpp"
#include "nmtools/testing/data/array/not_equal.hpp"
#include "nmtools/testing/doctest.hpp"

#include <vector>
#include <array>
#include <algorithm>

namespace nm = nmtools;
namespace na = nmtools;

#define NOT_EQUAL_SUBCASE(case_name, ...) \
SUBCASE(#case_name) \
{ \
    NMTOOLS_TESTING_USE_CASE(view, not_equal, case_name); \
    using namespace args; \
    auto result = nm::not_equal(__VA_ARGS__); \
    NMTOOLS_ASSERT_EQUAL( ::nm::shape(result), expect::shape ); \
    NMTOOLS_ASSERT_CLOSE( result, expect::result ); \
}

TEST_CASE("not_equal(case1)" * doctest::test_suite("array::not_equal"))
{
    NOT_EQUAL_SUBCASE( case1,   a,   b );
    NOT_EQUAL_SUBCASE( case1, a_a, b_a );
    NOT_EQUAL_SUBCASE( case1, a_f, b_f );
}

TEST_CASE("not_equal(case2)" * doctest::test_suite("array::not_equal"))
{
    NOT_EQUAL_SUBCASE( case2,   a, b );
    NOT_EQUAL_SUBCASE( case2, a_a, b );
    NOT_EQUAL_SUBCASE( case2, a_f, b );
}
