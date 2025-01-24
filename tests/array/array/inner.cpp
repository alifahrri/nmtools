#include "nmtools/array/inner.hpp"
#include "nmtools/testing/data/array/inner.hpp"
#include "nmtools/testing/doctest.hpp"

#define INNER_SUBCASE(case_name, ...) \
SUBCASE(#case_name) \
{ \
    NMTOOLS_TESTING_USE_CASE( array, inner, case_name ); \
    auto result = nmtools::array::inner(__VA_ARGS__); \
    NMTOOLS_ASSERT_EQUAL( nmtools::shape(result), nmtools::shape(expect::result) ); \
    NMTOOLS_ASSERT_CLOSE( result, expect::result ); \
}

TEST_CASE("inner(case1)" * doctest::test_suite("array::inner"))
{
    INNER_SUBCASE( case1, a, b );
    INNER_SUBCASE( case1, a_a, b_a );
    INNER_SUBCASE( case1, a_f, b_f );
    INNER_SUBCASE( case1, a_h, b_h );
    // TODO: fix compile
    // INNER_SUBCASE( case1, a_d, b_d );
}

TEST_CASE("inner(case1b)" * doctest::test_suite("array::inner"))
{
    INNER_SUBCASE( case1b, a, b );
    INNER_SUBCASE( case1b, a_a, b_a );
    INNER_SUBCASE( case1b, a_f, b_f );
    INNER_SUBCASE( case1b, a_h, b_h );
    INNER_SUBCASE( case1b, a_d, b_d );
}

TEST_CASE("inner(case1c)" * doctest::test_suite("array::inner"))
{
    INNER_SUBCASE( case1c, a, b );
    INNER_SUBCASE( case1c, a_a, b_a );
    INNER_SUBCASE( case1c, a_f, b_f );
    INNER_SUBCASE( case1c, a_h, b_h );
    INNER_SUBCASE( case1c, a_d, b_d );
}

TEST_CASE("inner(case2)" * doctest::test_suite("array::inner"))
{
    INNER_SUBCASE( case2, a, b );
    INNER_SUBCASE( case2, a_a, b_a );
    INNER_SUBCASE( case2, a_f, b_f );
    INNER_SUBCASE( case2, a_h, b_h );
    INNER_SUBCASE( case2, a_d, b_d );
}

TEST_CASE("inner(case2b)" * doctest::test_suite("array::inner"))
{
    INNER_SUBCASE( case2b, a, b );
    INNER_SUBCASE( case2b, a_a, b_a );
    INNER_SUBCASE( case2b, a_f, b_f );
    INNER_SUBCASE( case2b, a_h, b_h );
    INNER_SUBCASE( case2b, a_d, b_d );
}

TEST_CASE("inner(case2c)" * doctest::test_suite("array::inner"))
{
    INNER_SUBCASE( case2c, a, b );
    INNER_SUBCASE( case2c, a_a, b_a );
    INNER_SUBCASE( case2c, a_f, b_f );
    INNER_SUBCASE( case2c, a_h, b_h );
    INNER_SUBCASE( case2c, a_d, b_d );
}

TEST_CASE("inner(case2d)" * doctest::test_suite("array::inner"))
{
    INNER_SUBCASE( case2d, a, b );
    INNER_SUBCASE( case2d, a_a, b_a );
    INNER_SUBCASE( case2d, a_f, b_f );
    INNER_SUBCASE( case2d, a_h, b_h );
    INNER_SUBCASE( case2d, a_d, b_d );
}

TEST_CASE("inner(case3)" * doctest::test_suite("array::inner"))
{
    INNER_SUBCASE( case3, a, b );
    INNER_SUBCASE( case3, a_a, b_a );
    INNER_SUBCASE( case3, a_f, b_f );
    INNER_SUBCASE( case3, a_h, b_h );
    INNER_SUBCASE( case3, a_d, b_d );
}

TEST_CASE("inner(case3b)" * doctest::test_suite("array::inner"))
{
    INNER_SUBCASE( case3b, a, b );
    INNER_SUBCASE( case3b, a_a, b_a );
    INNER_SUBCASE( case3b, a_f, b_f );
    INNER_SUBCASE( case3b, a_h, b_h );
    INNER_SUBCASE( case3b, a_d, b_d );
}

TEST_CASE("inner(case3c)" * doctest::test_suite("array::inner"))
{
    INNER_SUBCASE( case3c, a, b );
    INNER_SUBCASE( case3c, a_a, b_a );
    INNER_SUBCASE( case3c, a_f, b_f );
    INNER_SUBCASE( case3c, a_h, b_h );
    INNER_SUBCASE( case3c, a_d, b_d );
}

TEST_CASE("inner(case3d)" * doctest::test_suite("array::inner"))
{
    INNER_SUBCASE( case3d, a, b );
    INNER_SUBCASE( case3d, a_a, b_a );
    INNER_SUBCASE( case3d, a_f, b_f );
    INNER_SUBCASE( case3d, a_h, b_h );
    INNER_SUBCASE( case3d, a_d, b_d );
}