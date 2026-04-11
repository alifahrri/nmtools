#include "nmtools/array/softmax.hpp"
#include "nmtools/testing/data/array/softmax.hpp"
#include "nmtools/context/default.hpp"
#include "nmtools/testing/doctest.hpp"

#define SOFTMAX_SUBCASE(case_name, ...) \
SUBCASE(#case_name) \
{ \
    NMTOOLS_TESTING_USE_CASE(array, softmax, case_name); \
    using namespace args; \
    auto result = nmtools::softmax(__VA_ARGS__); \
    NMTOOLS_ASSERT_CLOSE( result, expect::result ); \
}

TEST_CASE("softmax(case1)" * doctest::test_suite("array::softmax"))
{
    SOFTMAX_SUBCASE( case1, input, dim );
    SOFTMAX_SUBCASE( case1, input_a, dim );
    SOFTMAX_SUBCASE( case1, input_f, dim );
    SOFTMAX_SUBCASE( case1, input_h, dim );
    SOFTMAX_SUBCASE( case1, input_d, dim );
}

TEST_CASE("softmax(case2)" * doctest::test_suite("array::softmax"))
{
    SOFTMAX_SUBCASE( case2, input, dim );
    SOFTMAX_SUBCASE( case2, input_a, dim );
    SOFTMAX_SUBCASE( case2, input_f, dim );
    SOFTMAX_SUBCASE( case2, input_h, dim );
    SOFTMAX_SUBCASE( case2, input_d, dim );
}

TEST_CASE("softmax(case3)" * doctest::test_suite("array::softmax"))
{
    SOFTMAX_SUBCASE( case3, input, dim );
    SOFTMAX_SUBCASE( case3, input_a, dim );
    SOFTMAX_SUBCASE( case3, input_f, dim );
    SOFTMAX_SUBCASE( case3, input_h, dim );
    SOFTMAX_SUBCASE( case3, input_d, dim );
}

TEST_CASE("softmax(case4)" * doctest::test_suite("array::softmax"))
{
    SOFTMAX_SUBCASE( case4, input, dim );
    SOFTMAX_SUBCASE( case4, input_a, dim );
    SOFTMAX_SUBCASE( case4, input_f, dim );
    SOFTMAX_SUBCASE( case4, input_h, dim );
    SOFTMAX_SUBCASE( case4, input_d, dim );
}

TEST_CASE("softmax(case5)" * doctest::test_suite("array::softmax"))
{
    SOFTMAX_SUBCASE( case5, input, dim );
    SOFTMAX_SUBCASE( case5, input_a, dim );
    SOFTMAX_SUBCASE( case5, input_f, dim );
    SOFTMAX_SUBCASE( case5, input_h, dim );
    SOFTMAX_SUBCASE( case5, input_d, dim );
}