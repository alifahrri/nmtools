#include "nmtools/array/unsqueeze.hpp"
#include "nmtools/testing/data/array/unsqueeze.hpp"
#include "nmtools/context/default.hpp"
#include "nmtools/testing/doctest.hpp"

#define UNSQUEEZE_SUBCASE(case_name, ...) \
SUBCASE(#case_name) \
{ \
    NMTOOLS_TESTING_USE_CASE(unsqueeze,case_name) \
    using namespace args; \
    auto result = nmtools::unsqueeze(__VA_ARGS__); \
    NMTOOLS_ASSERT_EQUAL( nmtools::shape(result), nmtools::shape(expect::result) ); \
    NMTOOLS_ASSERT_CLOSE( result, expect::result ); \
}

TEST_CASE("unsqueeze(case1)" * doctest::test_suite("array::unsqueeze"))
{
    UNSQUEEZE_SUBCASE( case1, array, axis );
    UNSQUEEZE_SUBCASE( case1, array_a, axis );
    UNSQUEEZE_SUBCASE( case1, array_f, axis );
    UNSQUEEZE_SUBCASE( case1, array_h, axis );
    UNSQUEEZE_SUBCASE( case1, array_d, axis );

    UNSQUEEZE_SUBCASE( case1, array, axis_ct );
}

TEST_CASE("unsqueeze(case2)" * doctest::test_suite("array::unsqueeze"))
{
    UNSQUEEZE_SUBCASE( case2, array, axis );
    UNSQUEEZE_SUBCASE( case2, array_a, axis );
    UNSQUEEZE_SUBCASE( case2, array_f, axis );
    UNSQUEEZE_SUBCASE( case2, array_h, axis );
    UNSQUEEZE_SUBCASE( case2, array_d, axis );

    UNSQUEEZE_SUBCASE( case2, array, axis_ct );
}

TEST_CASE("unsqueeze(case3)" * doctest::test_suite("array::unsqueeze"))
{
    UNSQUEEZE_SUBCASE( case3, array, axis );
    UNSQUEEZE_SUBCASE( case3, array_a, axis );
    UNSQUEEZE_SUBCASE( case3, array_f, axis );
    UNSQUEEZE_SUBCASE( case3, array_h, axis );
    UNSQUEEZE_SUBCASE( case3, array_d, axis );

    UNSQUEEZE_SUBCASE( case3, array, axis_ct );
}

TEST_CASE("unsqueeze(case4)" * doctest::test_suite("array::unsqueeze"))
{
    UNSQUEEZE_SUBCASE( case4, array, axis );
    UNSQUEEZE_SUBCASE( case4, array_a, axis );
    UNSQUEEZE_SUBCASE( case4, array_f, axis );
    UNSQUEEZE_SUBCASE( case4, array_h, axis );
    UNSQUEEZE_SUBCASE( case4, array_d, axis );

    UNSQUEEZE_SUBCASE( case4, array, axis_ct );
}

TEST_CASE("unsqueeze(case5)" * doctest::test_suite("array::unsqueeze"))
{
    UNSQUEEZE_SUBCASE( case5, array, axis );
    UNSQUEEZE_SUBCASE( case5, array_a, axis );
    UNSQUEEZE_SUBCASE( case5, array_f, axis );
    UNSQUEEZE_SUBCASE( case5, array_h, axis );
    UNSQUEEZE_SUBCASE( case5, array_d, axis );

    UNSQUEEZE_SUBCASE( case5, array, axis_ct );
}

TEST_CASE("unsqueeze(case6)" * doctest::test_suite("array::unsqueeze"))
{
    UNSQUEEZE_SUBCASE( case6, array, axis );
    UNSQUEEZE_SUBCASE( case6, array_a, axis );
    UNSQUEEZE_SUBCASE( case6, array_f, axis );
    UNSQUEEZE_SUBCASE( case6, array_h, axis );
    UNSQUEEZE_SUBCASE( case6, array_d, axis );

    UNSQUEEZE_SUBCASE( case6, array, axis_ct );
}

TEST_CASE("unsqueeze(case7)" * doctest::test_suite("array::unsqueeze"))
{
    UNSQUEEZE_SUBCASE( case7, array, axis );
    UNSQUEEZE_SUBCASE( case7, array_a, axis );
    UNSQUEEZE_SUBCASE( case7, array_f, axis );
    UNSQUEEZE_SUBCASE( case7, array_h, axis );
    UNSQUEEZE_SUBCASE( case7, array_d, axis );

    UNSQUEEZE_SUBCASE( case7, array, axis_ct );
}

TEST_CASE("unsqueeze(case8)" * doctest::test_suite("array::unsqueeze"))
{
    UNSQUEEZE_SUBCASE( case8, array, axis );
    UNSQUEEZE_SUBCASE( case8, array_a, axis );
    UNSQUEEZE_SUBCASE( case8, array_f, axis );
    UNSQUEEZE_SUBCASE( case8, array_h, axis );
    UNSQUEEZE_SUBCASE( case8, array_d, axis );

    UNSQUEEZE_SUBCASE( case8, array, axis_ct );
}

TEST_CASE("unsqueeze(case9)" * doctest::test_suite("array::unsqueeze"))
{
    UNSQUEEZE_SUBCASE( case9, array, axis );
    UNSQUEEZE_SUBCASE( case9, array_a, axis );
    UNSQUEEZE_SUBCASE( case9, array_f, axis );
    UNSQUEEZE_SUBCASE( case9, array_h, axis );
    UNSQUEEZE_SUBCASE( case9, array_d, axis );

    UNSQUEEZE_SUBCASE( case9, array, axis_ct );
}
