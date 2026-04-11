#include "nmtools/array/ufuncs/logical_xor.hpp"
#include "nmtools/testing/data/array/logical_xor.hpp"
#include "nmtools/testing/doctest.hpp"
#include "nmtools/context/default.hpp"

#include <vector>
#include <array>
#include <algorithm> // std::max

namespace nm = nmtools;
namespace na = nmtools;

#define LOGICAL_XOR_SUBCASE(case_name, ...) \
SUBCASE(#case_name) \
{ \
    NMTOOLS_TESTING_USE_CASE(view, logical_xor, case_name); \
    using namespace args; \
    auto result = nm::logical_xor(__VA_ARGS__); \
    NMTOOLS_ASSERT_EQUAL( ::nm::shape(result), expect::shape ); \
    NMTOOLS_ASSERT_CLOSE( result, expect::result ); \
}

TEST_CASE("logical_xor(case1)" * doctest::test_suite("array::logical_xor"))
{
    LOGICAL_XOR_SUBCASE( case1,   a,   b );
    LOGICAL_XOR_SUBCASE( case1, a_a, b_a );
    LOGICAL_XOR_SUBCASE( case1, a_f, b_f );
    // TODO: drop support for vector of bool
    #if 0
    LOGICAL_XOR_SUBCASE( case1, a_d, b_d );
    LOGICAL_XOR_SUBCASE( case1, a_h, b_h );
    #endif
}

TEST_CASE("logical_xor(case2)" * doctest::test_suite("array::logical_xor"))
{
    LOGICAL_XOR_SUBCASE( case2,   a, b );
    LOGICAL_XOR_SUBCASE( case2, a_a, b );
    LOGICAL_XOR_SUBCASE( case2, a_f, b );
    // TODO: drop support for vector of bool
    #if 0
    LOGICAL_XOR_SUBCASE( case2, a_d, b );
    LOGICAL_XOR_SUBCASE( case2, a_h, b );
    #endif
}