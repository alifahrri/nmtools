#include "nmtools/array/view/dot.hpp"
#include "nmtools/testing/data/array/dot.hpp"
#include "nmtools/testing/doctest.hpp"

#define DOT_SUBCASE(case_name, ...) \
SUBCASE(#case_name) \
{ \
    NMTOOLS_TESTING_USE_CASE( array, dot, case_name ); \
    auto result = nmtools::view::dot(__VA_ARGS__); \
    NMTOOLS_ASSERT_EQUAL( nmtools::shape(result), nmtools::shape(expect::result) ); \
    NMTOOLS_ASSERT_CLOSE( result, expect::result ); \
}

TEST_CASE("dot(case1)" * doctest::test_suite("view::dot"))
{
    DOT_SUBCASE( case1, a, b );
    DOT_SUBCASE( case1, a_a, b_a );
    DOT_SUBCASE( case1, a_f, b_f );
    DOT_SUBCASE( case1, a_h, b_h );
    // TODO: fix compile
    // DOT_SUBCASE( case1, a_d, b_d );
}

TEST_CASE("dot(case2)" * doctest::test_suite("view::dot"))
{
    DOT_SUBCASE( case2, a, b );
    DOT_SUBCASE( case2, a_a, b_a );
    DOT_SUBCASE( case2, a_f, b_f );
    DOT_SUBCASE( case2, a_h, b_h );
    DOT_SUBCASE( case2, a_d, b_d );
}

TEST_CASE("dot(case2b)" * doctest::test_suite("view::dot"))
{
    DOT_SUBCASE( case2b, a, b );
    DOT_SUBCASE( case2b, a_a, b_a );
    DOT_SUBCASE( case2b, a_f, b_f );
    DOT_SUBCASE( case2b, a_h, b_h );
    DOT_SUBCASE( case2b, a_d, b_d );
}

TEST_CASE("dot(case2c)" * doctest::test_suite("view::dot"))
{
    DOT_SUBCASE( case2c, a, b );
    DOT_SUBCASE( case2c, a_a, b_a );
    DOT_SUBCASE( case2c, a_f, b_f );
    DOT_SUBCASE( case2c, a_h, b_h );
    DOT_SUBCASE( case2c, a_d, b_d );
}

TEST_CASE("dot(case2d)" * doctest::test_suite("view::dot"))
{
    DOT_SUBCASE( case2d, a, b );
    DOT_SUBCASE( case2d, a_a, b_a );
    DOT_SUBCASE( case2d, a_f, b_f );
    DOT_SUBCASE( case2d, a_h, b_h );
    DOT_SUBCASE( case2d, a_d, b_d );
}

TEST_CASE("dot(case3)" * doctest::test_suite("view::dot"))
{
    DOT_SUBCASE( case3, a, b );
    DOT_SUBCASE( case3, a_a, b_a );
    DOT_SUBCASE( case3, a_f, b_f );
    DOT_SUBCASE( case3, a_h, b_h );
    DOT_SUBCASE( case3, a_d, b_d );
}

TEST_CASE("dot(case3b)" * doctest::test_suite("view::dot"))
{
    DOT_SUBCASE( case3b, a, b );
    DOT_SUBCASE( case3b, a_a, b_a );
    DOT_SUBCASE( case3b, a_f, b_f );
    DOT_SUBCASE( case3b, a_h, b_h );
    DOT_SUBCASE( case3b, a_d, b_d );
}

TEST_CASE("dot(case3c)" * doctest::test_suite("view::dot"))
{
    DOT_SUBCASE( case3c, a, b );
    DOT_SUBCASE( case3c, a_a, b_a );
    DOT_SUBCASE( case3c, a_f, b_f );
    DOT_SUBCASE( case3c, a_h, b_h );
    DOT_SUBCASE( case3c, a_d, b_d );
}

TEST_CASE("dot(case3d)" * doctest::test_suite("view::dot"))
{
    DOT_SUBCASE( case3d, a, b );
    DOT_SUBCASE( case3d, a_a, b_a );
    DOT_SUBCASE( case3d, a_f, b_f );
    DOT_SUBCASE( case3d, a_h, b_h );
    DOT_SUBCASE( case3d, a_d, b_d );
}