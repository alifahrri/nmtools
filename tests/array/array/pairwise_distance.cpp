// TODO: improve precision?
#define NMTOOLS_TESTING_PRECISION (1e-3)

#include "nmtools/array/pairwise_distance.hpp"
#include "nmtools/testing/data/array/pairwise_distance.hpp"
#include "nmtools/testing/doctest.hpp"

#define PAIRWISE_DISTANCE_SUBCASE( case_name, ... ) \
SUBCASE(#case_name) \
{ \
    NMTOOLS_TESTING_USE_CASE( array, pairwise_distance, case_name ); \
    auto result = nmtools::array::pairwise_distance(__VA_ARGS__); \
    NMTOOLS_ASSERT_EQUAL( nmtools::shape(result), nmtools::shape(expect::result) ); \
    NMTOOLS_ASSERT_CLOSE( result, expect::result ); \
}

TEST_CASE("pairwise_distance(case1a)" * doctest::test_suite("array::pairwise_distance"))
{
    PAIRWISE_DISTANCE_SUBCASE( case1a, a, b );
    PAIRWISE_DISTANCE_SUBCASE( case1a, a_a, b_a );
    PAIRWISE_DISTANCE_SUBCASE( case1a, a_f, b_f );
    PAIRWISE_DISTANCE_SUBCASE( case1a, a_h, b_h );
    // TODO: fix
    // PAIRWISE_DISTANCE_SUBCASE( case1a, a_d, b_d );
}

TEST_CASE("pairwise_distance(case1b)" * doctest::test_suite("array::pairwise_distance"))
{
    PAIRWISE_DISTANCE_SUBCASE( case1b, a, b );
    PAIRWISE_DISTANCE_SUBCASE( case1b, a_a, b_a );
    PAIRWISE_DISTANCE_SUBCASE( case1b, a_f, b_f );
    PAIRWISE_DISTANCE_SUBCASE( case1b, a_h, b_h );
    // TODO: fix
    // PAIRWISE_DISTANCE_SUBCASE( case1b, a_d, b_d );
}

TEST_CASE("pairwise_distance(case1c)" * doctest::test_suite("array::pairwise_distance"))
{
    auto ord = 2;
    auto eps = 1e-6;
    PAIRWISE_DISTANCE_SUBCASE( case1c, a, b, ord, eps, keepdims_ct );
    PAIRWISE_DISTANCE_SUBCASE( case1c, a_a, b_a, ord, eps, keepdims_ct );
    PAIRWISE_DISTANCE_SUBCASE( case1c, a_f, b_f, ord, eps, keepdims_ct );
    PAIRWISE_DISTANCE_SUBCASE( case1c, a_h, b_h, ord, eps, keepdims_ct );
    PAIRWISE_DISTANCE_SUBCASE( case1c, a_d, b_d, ord, eps, keepdims_ct );
}

TEST_CASE("pairwise_distance(case1d)" * doctest::test_suite("array::pairwise_distance"))
{
    auto ord = 2;
    auto eps = 1e-6;
    PAIRWISE_DISTANCE_SUBCASE( case1d, a, b, ord, eps, keepdims_ct );
    PAIRWISE_DISTANCE_SUBCASE( case1d, a_a, b_a, ord, eps, keepdims_ct );
    PAIRWISE_DISTANCE_SUBCASE( case1d, a_f, b_f, ord, eps, keepdims_ct );
    PAIRWISE_DISTANCE_SUBCASE( case1d, a_h, b_h, ord, eps, keepdims_ct );
    PAIRWISE_DISTANCE_SUBCASE( case1d, a_d, b_d, ord, eps, keepdims_ct );
}

TEST_CASE("pairwise_distance(case2a)" * doctest::test_suite("array::pairwise_distance"))
{
    PAIRWISE_DISTANCE_SUBCASE( case2a, a, b );
    PAIRWISE_DISTANCE_SUBCASE( case2a, a_a, b_a );
    PAIRWISE_DISTANCE_SUBCASE( case2a, a_f, b_f );
    PAIRWISE_DISTANCE_SUBCASE( case2a, a_h, b_h );
    PAIRWISE_DISTANCE_SUBCASE( case2a, a_d, b_d );
}

TEST_CASE("pairwise_distance(case2b)" * doctest::test_suite("array::pairwise_distance"))
{
    PAIRWISE_DISTANCE_SUBCASE( case2b, a, b );
    PAIRWISE_DISTANCE_SUBCASE( case2b, a_a, b_a );
    PAIRWISE_DISTANCE_SUBCASE( case2b, a_f, b_f );
    PAIRWISE_DISTANCE_SUBCASE( case2b, a_h, b_h );
    PAIRWISE_DISTANCE_SUBCASE( case2b, a_d, b_d );
}

TEST_CASE("pairwise_distance(case2c)" * doctest::test_suite("array::pairwise_distance"))
{
    PAIRWISE_DISTANCE_SUBCASE( case2c, a, b );
    PAIRWISE_DISTANCE_SUBCASE( case2c, a_a, b_a );
    PAIRWISE_DISTANCE_SUBCASE( case2c, a_f, b_f );
    PAIRWISE_DISTANCE_SUBCASE( case2c, a_h, b_h );
    PAIRWISE_DISTANCE_SUBCASE( case2c, a_d, b_d );
}

TEST_CASE("pairwise_distance(case2d)" * doctest::test_suite("array::pairwise_distance"))
{
    PAIRWISE_DISTANCE_SUBCASE( case2d, a, b );
    PAIRWISE_DISTANCE_SUBCASE( case2d, a_a, b_a );
    PAIRWISE_DISTANCE_SUBCASE( case2d, a_f, b_f );
    PAIRWISE_DISTANCE_SUBCASE( case2d, a_h, b_h );
    PAIRWISE_DISTANCE_SUBCASE( case2d, a_d, b_d );
}

TEST_CASE("pairwise_distance(case2e)" * doctest::test_suite("array::pairwise_distance"))
{
    auto eps = 1e-6;
    PAIRWISE_DISTANCE_SUBCASE( case2e, a, b, ord, eps, keepdims_ct );
    PAIRWISE_DISTANCE_SUBCASE( case2e, a_a, b_a, ord, eps, keepdims_ct );
    PAIRWISE_DISTANCE_SUBCASE( case2e, a_f, b_f, ord, eps, keepdims_ct );
    PAIRWISE_DISTANCE_SUBCASE( case2e, a_h, b_h, ord, eps, keepdims_ct );
    PAIRWISE_DISTANCE_SUBCASE( case2e, a_d, b_d, ord, eps, keepdims_ct );
}

TEST_CASE("pairwise_distance(case2f)" * doctest::test_suite("array::pairwise_distance"))
{
    auto eps = 1e-6;
    PAIRWISE_DISTANCE_SUBCASE( case2f, a, b, ord, eps );
    PAIRWISE_DISTANCE_SUBCASE( case2f, a_a, b_a, ord, eps );
    PAIRWISE_DISTANCE_SUBCASE( case2f, a_f, b_f, ord, eps );
    PAIRWISE_DISTANCE_SUBCASE( case2f, a_h, b_h, ord, eps );
    PAIRWISE_DISTANCE_SUBCASE( case2f, a_d, b_d, ord, eps );
}