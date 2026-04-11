#include "nmtools/array/softmin.hpp"
#include "nmtools/testing/data/array/softmin.hpp"
#include "nmtools/context/default.hpp"
#include "nmtools/testing/doctest.hpp"

#define SOFTMIN_SUBCASE(case_name, ...) \
SUBCASE(#case_name) \
{ \
    NMTOOLS_TESTING_USE_CASE(array, softmin, case_name); \
    using namespace args; \
    auto result = nmtools::softmin(__VA_ARGS__); \
    NMTOOLS_ASSERT_CLOSE( result, expect::result ); \
}

TEST_CASE("softmin(case1)" * doctest::test_suite("array::softmin"))
{
    SOFTMIN_SUBCASE( case1, input, dim );
    SOFTMIN_SUBCASE( case1, input_a, dim );
    SOFTMIN_SUBCASE( case1, input_f, dim );
    SOFTMIN_SUBCASE( case1, input_h, dim );
    SOFTMIN_SUBCASE( case1, input_d, dim );
}

TEST_CASE("softmin(case2)" * doctest::test_suite("array::softmin"))
{
    SOFTMIN_SUBCASE( case2, input, dim );
    SOFTMIN_SUBCASE( case2, input_a, dim );
    SOFTMIN_SUBCASE( case2, input_f, dim );
    SOFTMIN_SUBCASE( case2, input_h, dim );
    SOFTMIN_SUBCASE( case2, input_d, dim );
}

TEST_CASE("softmin(case3)" * doctest::test_suite("array::softmin"))
{
    SOFTMIN_SUBCASE( case3, input, dim );
    SOFTMIN_SUBCASE( case3, input_a, dim );
    SOFTMIN_SUBCASE( case3, input_f, dim );
    SOFTMIN_SUBCASE( case3, input_h, dim );
    SOFTMIN_SUBCASE( case3, input_d, dim );
}

TEST_CASE("softmin(case4)" * doctest::test_suite("array::softmin"))
{
    SOFTMIN_SUBCASE( case4, input, dim );
    SOFTMIN_SUBCASE( case4, input_a, dim );
    SOFTMIN_SUBCASE( case4, input_f, dim );
    SOFTMIN_SUBCASE( case4, input_h, dim );
    SOFTMIN_SUBCASE( case4, input_d, dim );
}

TEST_CASE("softmin(case5)" * doctest::test_suite("array::softmin"))
{
    SOFTMIN_SUBCASE( case5, input, dim );
    SOFTMIN_SUBCASE( case5, input_a, dim );
    SOFTMIN_SUBCASE( case5, input_f, dim );
    SOFTMIN_SUBCASE( case5, input_h, dim );
    SOFTMIN_SUBCASE( case5, input_d, dim );
}