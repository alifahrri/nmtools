#include "nmtools/array/ufuncs/less.hpp"
#include "nmtools/context/default.hpp"
#include "nmtools/testing/data/array/less.hpp"
#include "nmtools/testing/doctest.hpp"

#include <vector>
#include <array>
#include <algorithm>

namespace nm = nmtools;
namespace na = nmtools;

#define LESS_SUBCASE(case_name, ...) \
SUBCASE(#case_name) \
{ \
    NMTOOLS_TESTING_USE_CASE(view, less, case_name); \
    using namespace args; \
    auto result = nm::less(__VA_ARGS__); \
    NMTOOLS_ASSERT_EQUAL( ::nm::shape(result), expect::shape ); \
    NMTOOLS_ASSERT_CLOSE( result, expect::result ); \
}

TEST_CASE("less(case1)" * doctest::test_suite("array::less"))
{
    LESS_SUBCASE( case1,   a,   b );
    LESS_SUBCASE( case1, a_a, b_a );
    LESS_SUBCASE( case1, a_f, b_f );
}

TEST_CASE("less(case2)" * doctest::test_suite("array::less"))
{
    LESS_SUBCASE( case2,   a, b );
    LESS_SUBCASE( case2, a_a, b );
    LESS_SUBCASE( case2, a_f, b );
}
