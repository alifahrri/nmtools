#include "nmtools/array/linear.hpp"
#include "nmtools/testing/data/array/linear.hpp"
#include "nmtools/testing/doctest.hpp"

#define LINEAR_SUBCASE(case_name,...) \
SUBCASE(#case_name) \
{ \
    NMTOOLS_TESTING_USE_CASE(array,linear,case_name); \
    auto result = nmtools::array::linear(__VA_ARGS__); \
    NMTOOLS_ASSERT_EQUAL( nmtools::shape(result), nmtools::shape(expect::result) ); \
    NMTOOLS_ASSERT_CLOSE( result, expect::result ); \
}

TEST_CASE("linear(case1a)" * doctest::test_suite("array::linear"))
{
    LINEAR_SUBCASE( case1a, input, weight );
    LINEAR_SUBCASE( case1a, input_a, weight_a );
    LINEAR_SUBCASE( case1a, input_f, weight_f );
    LINEAR_SUBCASE( case1a, input_h, weight_h );
    // LINEAR_SUBCASE( case1a, input_d, weight_d );
}

TEST_CASE("linear(case1b)" * doctest::test_suite("array::linear"))
{
    LINEAR_SUBCASE( case1b, input, weight );
    LINEAR_SUBCASE( case1b, input_a, weight_a );
    LINEAR_SUBCASE( case1b, input_f, weight_f );
    LINEAR_SUBCASE( case1b, input_h, weight_h );
    // LINEAR_SUBCASE( case1b, input_d, weight_d );
}

TEST_CASE("linear(case1c)" * doctest::test_suite("array::linear"))
{
    LINEAR_SUBCASE( case1c, input, weight, bias );
    LINEAR_SUBCASE( case1c, input_a, weight_a, bias_a );
    LINEAR_SUBCASE( case1c, input_f, weight_f, bias_f );
    LINEAR_SUBCASE( case1c, input_h, weight_h, bias_h );
    // LINEAR_SUBCASE( case1c, input_d, weight_d, bias_d );
}

TEST_CASE("linear(case2a)" * doctest::test_suite("array::linear"))
{
    LINEAR_SUBCASE( case2a, input, weight );
    LINEAR_SUBCASE( case2a, input_a, weight_a );
    LINEAR_SUBCASE( case2a, input_f, weight_f );
    LINEAR_SUBCASE( case2a, input_h, weight_h );
    LINEAR_SUBCASE( case2a, input_d, weight_d );
}

TEST_CASE("linear(case2b)" * doctest::test_suite("array::linear"))
{
    LINEAR_SUBCASE( case2b, input, weight );
    LINEAR_SUBCASE( case2b, input_a, weight_a );
    LINEAR_SUBCASE( case2b, input_f, weight_f );
    LINEAR_SUBCASE( case2b, input_h, weight_h );
    LINEAR_SUBCASE( case2b, input_d, weight_d );
}

TEST_CASE("linear(case2c)" * doctest::test_suite("array::linear"))
{
    LINEAR_SUBCASE( case2c, input, weight, bias );
    LINEAR_SUBCASE( case2c, input_a, weight_a, bias );
    LINEAR_SUBCASE( case2c, input_f, weight_f, bias );
    LINEAR_SUBCASE( case2c, input_h, weight_h, bias );
    LINEAR_SUBCASE( case2c, input_d, weight_d, bias );
}

TEST_CASE("linear(case3a)" * doctest::test_suite("array::linear"))
{
    LINEAR_SUBCASE( case3a, input, weight );
    LINEAR_SUBCASE( case3a, input_a, weight_a );
    LINEAR_SUBCASE( case3a, input_f, weight_f );
    LINEAR_SUBCASE( case3a, input_h, weight_h );
    LINEAR_SUBCASE( case3a, input_d, weight_d );
}

TEST_CASE("linear(case3b)" * doctest::test_suite("array::linear"))
{
    LINEAR_SUBCASE( case3b, input, weight );
    LINEAR_SUBCASE( case3b, input_a, weight_a );
    LINEAR_SUBCASE( case3b, input_f, weight_f );
    LINEAR_SUBCASE( case3b, input_h, weight_h );
    LINEAR_SUBCASE( case3b, input_d, weight_d );
}

TEST_CASE("linear(case3c)" * doctest::test_suite("array::linear"))
{
    LINEAR_SUBCASE( case3c, input, weight, bias );
    LINEAR_SUBCASE( case3c, input_a, weight_a, bias_a );
    LINEAR_SUBCASE( case3c, input_f, weight_f, bias_f );
    LINEAR_SUBCASE( case3c, input_h, weight_h, bias_h );
    LINEAR_SUBCASE( case3c, input_d, weight_d, bias_d );
}