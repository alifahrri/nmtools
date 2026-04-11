#include "nmtools/array/ufuncs/logical_or.hpp"
#include "nmtools/testing/data/array/logical_or.hpp"
#include "nmtools/testing/doctest.hpp"
#include "nmtools/context/default.hpp"

#include <vector>
#include <array>
#include <algorithm> // std::max

namespace nm = nmtools;
namespace na = nmtools;

#define LOGICAL_OR_SUBCASE(case_name, ...) \
SUBCASE(#case_name) \
{ \
    NMTOOLS_TESTING_USE_CASE(view, logical_or, case_name); \
    using namespace args; \
    auto result = nm::logical_or(__VA_ARGS__); \
    NMTOOLS_ASSERT_EQUAL( ::nm::shape(result), expect::shape ); \
    NMTOOLS_ASSERT_CLOSE( result, expect::result ); \
}

TEST_CASE("logical_or(case1)" * doctest::test_suite("array::logical_or"))
{
    LOGICAL_OR_SUBCASE( case1,   a,   b );
    LOGICAL_OR_SUBCASE( case1, a_a, b_a );
    LOGICAL_OR_SUBCASE( case1, a_f, b_f );
    // TODO: drop support for vector of bool
    #if 0
    LOGICAL_OR_SUBCASE( case1, a_d, b_d );
    LOGICAL_OR_SUBCASE( case1, a_h, b_h );
    #endif
}

TEST_CASE("logical_or(case2)" * doctest::test_suite("array::logical_or"))
{
    LOGICAL_OR_SUBCASE( case2,   a, b );
    LOGICAL_OR_SUBCASE( case2, a_a, b );
    LOGICAL_OR_SUBCASE( case2, a_f, b );
    // TODO: drop support for vector of bool
    #if 0
    LOGICAL_OR_SUBCASE( case2, a_d, b );
    LOGICAL_OR_SUBCASE( case2, a_h, b );
    #endif
}