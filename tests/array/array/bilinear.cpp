#include "nmtools/array/array/bilinear.hpp"
#include "nmtools/testing/data/array/bilinear.hpp"
#include "nmtools/testing/doctest.hpp"

#define BILINEAR_SUBCASE(case_name,...) \
SUBCASE(#case_name) \
{ \
    NMTOOLS_TESTING_USE_CASE(array,bilinear,case_name); \
    auto result = nmtools::array::bilinear(__VA_ARGS__); \
    NMTOOLS_ASSERT_EQUAL( nmtools::shape(result), nmtools::shape(expect::result) ); \
    NMTOOLS_ASSERT_CLOSE( result, expect::result ); \
}

TEST_CASE("bilinear(case1a)" * doctest::test_suite("array::bilinear"))
{
    BILINEAR_SUBCASE( case1a, a, b, weight );
    BILINEAR_SUBCASE( case1a, a_a, b_a, weight_a );
    BILINEAR_SUBCASE( case1a, a_f, b_f, weight_f );
    BILINEAR_SUBCASE( case1a, a_h, b_h, weight_h );
    BILINEAR_SUBCASE( case1a, a_d, b_d, weight_d );
}

TEST_CASE("bilinear(case1b)" * doctest::test_suite("array::bilinear"))
{
    BILINEAR_SUBCASE( case1b, a, b, weight );
    BILINEAR_SUBCASE( case1b, a_a, b_a, weight_a );
    BILINEAR_SUBCASE( case1b, a_f, b_f, weight_f );
    BILINEAR_SUBCASE( case1b, a_h, b_h, weight_h );
    BILINEAR_SUBCASE( case1b, a_d, b_d, weight_d );
}

TEST_CASE("bilinear(case2a)" * doctest::test_suite("array::bilinear"))
{
    BILINEAR_SUBCASE( case2a, a, b, weight );
    BILINEAR_SUBCASE( case2a, a_a, b_a, weight_a );
    BILINEAR_SUBCASE( case2a, a_f, b_f, weight_f );
    BILINEAR_SUBCASE( case2a, a_h, b_h, weight_h );
    BILINEAR_SUBCASE( case2a, a_d, b_d, weight_d );
}

TEST_CASE("bilinear(case2c)" * doctest::test_suite("array::bilinear"))
{
    BILINEAR_SUBCASE( case2b, a, b, weight );
    BILINEAR_SUBCASE( case2b, a_a, b_a, weight_a );
    BILINEAR_SUBCASE( case2b, a_f, b_f, weight_f );
    BILINEAR_SUBCASE( case2b, a_h, b_h, weight_h );
    BILINEAR_SUBCASE( case2b, a_d, b_d, weight_d );
}

TEST_CASE("bilinear(case2c)" * doctest::test_suite("array::bilinear"))
{
    BILINEAR_SUBCASE( case2c, a, b, weight, bias );
    BILINEAR_SUBCASE( case2c, a_a, b_a, weight_a, bias_a );
    BILINEAR_SUBCASE( case2c, a_f, b_f, weight_f, bias_f );
    BILINEAR_SUBCASE( case2c, a_h, b_h, weight_h, bias_h );
    BILINEAR_SUBCASE( case2c, a_d, b_d, weight_d, bias_d );
}

TEST_CASE("bilinear(case3a)" * doctest::test_suite("array::bilinear"))
{
    BILINEAR_SUBCASE( case3a, a, b, weight );
    BILINEAR_SUBCASE( case3a, a_a, b_a, weight_a );
    BILINEAR_SUBCASE( case3a, a_f, b_f, weight_f );
    BILINEAR_SUBCASE( case3a, a_h, b_h, weight_h );
    BILINEAR_SUBCASE( case3a, a_d, b_d, weight_d );
}

TEST_CASE("bilinear(case3b)" * doctest::test_suite("array::bilinear"))
{
    BILINEAR_SUBCASE( case3b, a, b, weight );
    BILINEAR_SUBCASE( case3b, a_a, b_a, weight_a );
    BILINEAR_SUBCASE( case3b, a_f, b_f, weight_f );
    BILINEAR_SUBCASE( case3b, a_h, b_h, weight_h );
    BILINEAR_SUBCASE( case3b, a_d, b_d, weight_d );
}

TEST_CASE("bilinear(case3c)" * doctest::test_suite("array::bilinear"))
{
    BILINEAR_SUBCASE( case3c, a, b, weight );
    BILINEAR_SUBCASE( case3c, a_a, b_a, weight_a );
    BILINEAR_SUBCASE( case3c, a_f, b_f, weight_f );
    BILINEAR_SUBCASE( case3c, a_h, b_h, weight_h );
    BILINEAR_SUBCASE( case3c, a_d, b_d, weight_d );
}

TEST_CASE("bilinear(case3d)" * doctest::test_suite("array::bilinear"))
{
    BILINEAR_SUBCASE( case3d, a, b, weight, bias );
    BILINEAR_SUBCASE( case3d, a_a, b_a, weight_a, bias_a );
    BILINEAR_SUBCASE( case3d, a_f, b_f, weight_f, bias_f );
    BILINEAR_SUBCASE( case3d, a_h, b_h, weight_h, bias_h );
    BILINEAR_SUBCASE( case3d, a_d, b_d, weight_d, bias_d );
}

TEST_CASE("bilinear(case4a)" * doctest::test_suite("array::bilinear"))
{
    BILINEAR_SUBCASE( case4a, a, b, weight, bias );
    BILINEAR_SUBCASE( case4a, a_a, b_a, weight_a, bias_a );
    BILINEAR_SUBCASE( case4a, a_f, b_f, weight_f, bias_f );
    BILINEAR_SUBCASE( case4a, a_h, b_h, weight_h, bias_h );
    BILINEAR_SUBCASE( case4a, a_d, b_d, weight_d, bias_d );
}