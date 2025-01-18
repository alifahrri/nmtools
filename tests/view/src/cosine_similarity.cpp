#include "nmtools/array/cosine_similarity.hpp"
#include "nmtools/testing/data/array/cosine_similarity.hpp"
#include "nmtools/testing/doctest.hpp"

#define COSINE_SIMILARITY_SUBCASE(case_name, ...) \
SUBCASE(#case_name) \
{ \
    NMTOOLS_TESTING_USE_CASE(array,cosine_similarity,case_name); \
    auto result = nmtools::view::cosine_similarity(__VA_ARGS__); \
    NMTOOLS_ASSERT_EQUAL( nmtools::shape(result), nmtools::shape(expect::result) ); \
    NMTOOLS_ASSERT_CLOSE( result, expect::result ); \
}

TEST_CASE("cosine_similarity(case1a)" * doctest::test_suite("view::cosine_similarity"))
{
    COSINE_SIMILARITY_SUBCASE( case1a, a, b );
    COSINE_SIMILARITY_SUBCASE( case1a, a_a, b_a );
    COSINE_SIMILARITY_SUBCASE( case1a, a_f, b_f );
    COSINE_SIMILARITY_SUBCASE( case1a, a_h, b_h );
    COSINE_SIMILARITY_SUBCASE( case1a, a_d, b_d );
}

TEST_CASE("cosine_similarity(case1b)" * doctest::test_suite("view::cosine_similarity"))
{
    COSINE_SIMILARITY_SUBCASE( case1b, a, b );
    COSINE_SIMILARITY_SUBCASE( case1b, a_a, b_a );
    COSINE_SIMILARITY_SUBCASE( case1b, a_f, b_f );
    COSINE_SIMILARITY_SUBCASE( case1b, a_h, b_h );
    COSINE_SIMILARITY_SUBCASE( case1b, a_d, b_d );
}

TEST_CASE("cosine_similarity(case1c)" * doctest::test_suite("view::cosine_similarity"))
{
    COSINE_SIMILARITY_SUBCASE( case1c, a, b, axis_ct );
    COSINE_SIMILARITY_SUBCASE( case1c, a_a, b_a, axis_ct );
    COSINE_SIMILARITY_SUBCASE( case1c, a_f, b_f, axis_ct );
    COSINE_SIMILARITY_SUBCASE( case1c, a_h, b_h, axis_ct );
    COSINE_SIMILARITY_SUBCASE( case1c, a_d, b_d, axis_ct );
}

TEST_CASE("cosine_similarity(case2a)" * doctest::test_suite("view::cosine_similarity"))
{
    COSINE_SIMILARITY_SUBCASE( case2a, a, b, axis_ct );
    COSINE_SIMILARITY_SUBCASE( case2a, a_a, b_a, axis_ct );
    COSINE_SIMILARITY_SUBCASE( case2a, a_f, b_f, axis_ct );
    COSINE_SIMILARITY_SUBCASE( case2a, a_h, b_h, axis_ct );
    COSINE_SIMILARITY_SUBCASE( case2a, a_d, b_d, axis_ct );
}

TEST_CASE("cosine_similarity(case2b)" * doctest::test_suite("view::cosine_similarity"))
{
    COSINE_SIMILARITY_SUBCASE( case2b, a, b, axis_ct );
    COSINE_SIMILARITY_SUBCASE( case2b, a_a, b_a, axis_ct );
    COSINE_SIMILARITY_SUBCASE( case2b, a_f, b_f, axis_ct );
    COSINE_SIMILARITY_SUBCASE( case2b, a_h, b_h, axis_ct );
    COSINE_SIMILARITY_SUBCASE( case2b, a_d, b_d, axis_ct );
}

TEST_CASE("cosine_similarity(case2c)" * doctest::test_suite("view::cosine_similarity"))
{
    COSINE_SIMILARITY_SUBCASE( case2c, a, b, axis_ct );
    COSINE_SIMILARITY_SUBCASE( case2c, a_a, b_a, axis_ct );
    COSINE_SIMILARITY_SUBCASE( case2c, a_f, b_f, axis_ct );
    COSINE_SIMILARITY_SUBCASE( case2c, a_h, b_h, axis_ct );
    COSINE_SIMILARITY_SUBCASE( case2c, a_d, b_d, axis_ct );
}

TEST_CASE("cosine_similarity(case2d)" * doctest::test_suite("view::cosine_similarity"))
{
    COSINE_SIMILARITY_SUBCASE( case2d, a, b, axis_ct );
    COSINE_SIMILARITY_SUBCASE( case2d, a_a, b_a, axis_ct );
    COSINE_SIMILARITY_SUBCASE( case2d, a_f, b_f, axis_ct );
    COSINE_SIMILARITY_SUBCASE( case2d, a_h, b_h, axis_ct );
    COSINE_SIMILARITY_SUBCASE( case2d, a_d, b_d, axis_ct );
}