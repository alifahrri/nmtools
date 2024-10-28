#include "nmtools/array/array/vecdot.hpp"
#include "nmtools/testing/data/array/vecdot.hpp"
#include "nmtools/testing/doctest.hpp"

using nmtools::None;

#define VECDOT_SUBCASE(case_name,...) \
SUBCASE(#case_name) \
{ \
    NMTOOLS_TESTING_USE_CASE(array,vecdot,case_name); \
    auto result = nmtools::array::vecdot(__VA_ARGS__); \
    NMTOOLS_ASSERT_EQUAL( nmtools::shape(result), nmtools::shape(expect::result) ); \
    NMTOOLS_ASSERT_CLOSE( result, expect::result ); \
}

TEST_CASE("vecdot(case1a)" * doctest::test_suite("array::vecdot"))
{
    VECDOT_SUBCASE( case1a, a, b );
    VECDOT_SUBCASE( case1a, a_a, b_a );
    VECDOT_SUBCASE( case1a, a_f, b_f );
    VECDOT_SUBCASE( case1a, a_h, b_h );
    // VECDOT_SUBCASE( case1a, a_d, b_d );
}

TEST_CASE("vecdot(case1b)" * doctest::test_suite("array::vecdot"))
{
    VECDOT_SUBCASE( case1b, a, b, None, keepdims );
    VECDOT_SUBCASE( case1b, a_a, b_a, None, keepdims );
    VECDOT_SUBCASE( case1b, a_f, b_f, None, keepdims );
    VECDOT_SUBCASE( case1b, a_h, b_h, None, keepdims );
    VECDOT_SUBCASE( case1b, a_d, b_d, None, keepdims );
}

TEST_CASE("vecdot(case1c)" * doctest::test_suite("array::vecdot"))
{
    VECDOT_SUBCASE( case1c, a, b );
    VECDOT_SUBCASE( case1c, a_a, b_a );
    VECDOT_SUBCASE( case1c, a_f, b_f );
    VECDOT_SUBCASE( case1c, a_h, b_h );
    // VECDOT_SUBCASE( case1c, a_d, b_d );
}

TEST_CASE("vecdot(case1d)" * doctest::test_suite("array::vecdot"))
{
    VECDOT_SUBCASE( case1d, a, b, None, keepdims );
    VECDOT_SUBCASE( case1d, a_a, b_a, None, keepdims );
    VECDOT_SUBCASE( case1d, a_f, b_f, None, keepdims );
    VECDOT_SUBCASE( case1d, a_h, b_h, None, keepdims );
    VECDOT_SUBCASE( case1d, a_d, b_d, None, keepdims );
}

TEST_CASE("vecdot(case1e)" * doctest::test_suite("array::vecdot"))
{
    VECDOT_SUBCASE( case1e, a, b );
    VECDOT_SUBCASE( case1e, a_a, b_a );
    VECDOT_SUBCASE( case1e, a_f, b_f );
    VECDOT_SUBCASE( case1e, a_h, b_h );
    // VECDOT_SUBCASE( case1e, a_d, b_d );
}

TEST_CASE("vecdot(case1f)" * doctest::test_suite("array::vecdot"))
{
    VECDOT_SUBCASE( case1f, a, b, None, keepdims );
    VECDOT_SUBCASE( case1f, a_a, b_a, None, keepdims );
    VECDOT_SUBCASE( case1f, a_f, b_f, None, keepdims );
    VECDOT_SUBCASE( case1f, a_h, b_h, None, keepdims );
    VECDOT_SUBCASE( case1f, a_d, b_d, None, keepdims );
}

TEST_CASE("vecdot(case2a)" * doctest::test_suite("array::vecdot"))
{
    VECDOT_SUBCASE( case2a, a, b );
    VECDOT_SUBCASE( case2a, a_a, b_a );
    VECDOT_SUBCASE( case2a, a_f, b_f );
    VECDOT_SUBCASE( case2a, a_h, b_h );
    VECDOT_SUBCASE( case2a, a_d, b_d );
}

TEST_CASE("vecdot(case2b)" * doctest::test_suite("array::vecdot"))
{
    VECDOT_SUBCASE( case2b, a, b, None, keepdims );
    VECDOT_SUBCASE( case2b, a_a, b_a, None, keepdims );
    VECDOT_SUBCASE( case2b, a_f, b_f, None, keepdims );
    VECDOT_SUBCASE( case2b, a_h, b_h, None, keepdims );
    VECDOT_SUBCASE( case2b, a_d, b_d, None, keepdims );
}

TEST_CASE("vecdot(case2c)" * doctest::test_suite("array::vecdot"))
{
    VECDOT_SUBCASE( case2c, a, b );
    VECDOT_SUBCASE( case2c, a_a, b_a );
    VECDOT_SUBCASE( case2c, a_f, b_f );
    VECDOT_SUBCASE( case2c, a_h, b_h );
    VECDOT_SUBCASE( case2c, a_d, b_d );
}

TEST_CASE("vecdot(case2d)" * doctest::test_suite("array::vecdot"))
{
    VECDOT_SUBCASE( case2d, a, b, None, keepdims );
    VECDOT_SUBCASE( case2d, a_a, b_a, None, keepdims );
    VECDOT_SUBCASE( case2d, a_f, b_f, None, keepdims );
    VECDOT_SUBCASE( case2d, a_h, b_h, None, keepdims );
    VECDOT_SUBCASE( case2d, a_d, b_d, None, keepdims );
}

TEST_CASE("vecdot(case2e)" * doctest::test_suite("array::vecdot"))
{
    VECDOT_SUBCASE( case2e, a, b );
    VECDOT_SUBCASE( case2e, a_a, b_a );
    VECDOT_SUBCASE( case2e, a_f, b_f );
    VECDOT_SUBCASE( case2e, a_h, b_h );
    VECDOT_SUBCASE( case2e, a_d, b_d );
}

TEST_CASE("vecdot(case2f)" * doctest::test_suite("array::vecdot"))
{
    VECDOT_SUBCASE( case2f, a, b, None, keepdims );
    VECDOT_SUBCASE( case2f, a_a, b_a, None, keepdims );
    VECDOT_SUBCASE( case2f, a_f, b_f, None, keepdims );
    VECDOT_SUBCASE( case2f, a_h, b_h, None, keepdims );
    VECDOT_SUBCASE( case2f, a_d, b_d, None, keepdims );
}

TEST_CASE("vecdot(case3a)" * doctest::test_suite("array::vecdot"))
{
    VECDOT_SUBCASE( case3a, a, b );
    VECDOT_SUBCASE( case3a, a_a, b_a );
    VECDOT_SUBCASE( case3a, a_f, b_f );
    VECDOT_SUBCASE( case3a, a_h, b_h );
    VECDOT_SUBCASE( case3a, a_d, b_d );
}

TEST_CASE("vecdot(case3b)" * doctest::test_suite("array::vecdot"))
{
    VECDOT_SUBCASE( case3b, a, b, None, keepdims );
    VECDOT_SUBCASE( case3b, a_a, b_a, None, keepdims );
    VECDOT_SUBCASE( case3b, a_f, b_f, None, keepdims );
    VECDOT_SUBCASE( case3b, a_h, b_h, None, keepdims );
    VECDOT_SUBCASE( case3b, a_d, b_d, None, keepdims );
}

TEST_CASE("vecdot(case3c)" * doctest::test_suite("array::vecdot"))
{
    VECDOT_SUBCASE( case3c, a, b );
    VECDOT_SUBCASE( case3c, a_a, b_a );
    VECDOT_SUBCASE( case3c, a_f, b_f );
    VECDOT_SUBCASE( case3c, a_h, b_h );
    VECDOT_SUBCASE( case3c, a_d, b_d );
}
