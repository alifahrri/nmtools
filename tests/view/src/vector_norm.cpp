#include "nmtools/array/view/vector_norm.hpp"
#include "nmtools/testing/data/array/vector_norm.hpp"
#include "nmtools/testing/doctest.hpp"

#define VECTOR_NORM_SUBCASE(case_name, ...) \
SUBCASE(#case_name) \
{ \
    NMTOOLS_TESTING_USE_CASE( array, vector_norm, case_name ); \
    using namespace args; \
    auto result = nmtools::view::vector_norm(__VA_ARGS__); \
    NMTOOLS_ASSERT_EQUAL( nmtools::shape(result), nmtools::shape(expect::result) ); \
    NMTOOLS_ASSERT_CLOSE( result, expect::result ); \
}

TEST_CASE("vector_norm(case1)" * doctest::test_suite("view::vector_norm"))
{
    VECTOR_NORM_SUBCASE( case1, x );
    VECTOR_NORM_SUBCASE( case1, x_a );
    VECTOR_NORM_SUBCASE( case1, x_f );
    VECTOR_NORM_SUBCASE( case1, x_h );
    VECTOR_NORM_SUBCASE( case1, x_d );
}

TEST_CASE("vector_norm(case2a)" * doctest::test_suite("view::vector_norm"))
{
    VECTOR_NORM_SUBCASE( case2a, x );
    VECTOR_NORM_SUBCASE( case2a, x_a );
    VECTOR_NORM_SUBCASE( case2a, x_f );
    VECTOR_NORM_SUBCASE( case2a, x_h );
    VECTOR_NORM_SUBCASE( case2a, x_d );
}

TEST_CASE("vector_norm(case2b)" * doctest::test_suite("view::vector_norm"))
{
    VECTOR_NORM_SUBCASE( case2b, x, axis );
    VECTOR_NORM_SUBCASE( case2b, x_a, axis );
    VECTOR_NORM_SUBCASE( case2b, x_f, axis );
    VECTOR_NORM_SUBCASE( case2b, x_h, axis );
    VECTOR_NORM_SUBCASE( case2b, x_d, axis );

    VECTOR_NORM_SUBCASE( case2b, x, axis_ct );
    VECTOR_NORM_SUBCASE( case2b, x_a, axis_ct );
    VECTOR_NORM_SUBCASE( case2b, x_f, axis_ct );
    VECTOR_NORM_SUBCASE( case2b, x_h, axis_ct );
    VECTOR_NORM_SUBCASE( case2b, x_d, axis_ct );
}

TEST_CASE("vector_norm(case2c)" * doctest::test_suite("view::vector_norm"))
{
    VECTOR_NORM_SUBCASE( case2c, x, axis, keepdims );
    VECTOR_NORM_SUBCASE( case2c, x_a, axis, keepdims );
    VECTOR_NORM_SUBCASE( case2c, x_f, axis, keepdims );
    VECTOR_NORM_SUBCASE( case2c, x_h, axis, keepdims );
    VECTOR_NORM_SUBCASE( case2c, x_d, axis, keepdims );

    VECTOR_NORM_SUBCASE( case2c, x, axis_ct, keepdims );
    VECTOR_NORM_SUBCASE( case2c, x_a, axis_ct, keepdims );
    VECTOR_NORM_SUBCASE( case2c, x_f, axis_ct, keepdims );
    VECTOR_NORM_SUBCASE( case2c, x_h, axis_ct, keepdims );
    VECTOR_NORM_SUBCASE( case2c, x_d, axis_ct, keepdims );
}

TEST_CASE("vector_norm(case2d)" * doctest::test_suite("view::vector_norm"))
{
    VECTOR_NORM_SUBCASE( case2d, x, axis, keepdims, ord );
    VECTOR_NORM_SUBCASE( case2d, x_a, axis, keepdims, ord );
    VECTOR_NORM_SUBCASE( case2d, x_f, axis, keepdims, ord );
    VECTOR_NORM_SUBCASE( case2d, x_h, axis, keepdims, ord );
    VECTOR_NORM_SUBCASE( case2d, x_d, axis, keepdims, ord );

    VECTOR_NORM_SUBCASE( case2d, x, axis_ct, keepdims, ord );
    VECTOR_NORM_SUBCASE( case2d, x_a, axis_ct, keepdims, ord );
    VECTOR_NORM_SUBCASE( case2d, x_f, axis_ct, keepdims, ord );
    VECTOR_NORM_SUBCASE( case2d, x_h, axis_ct, keepdims, ord );
    VECTOR_NORM_SUBCASE( case2d, x_d, axis_ct, keepdims, ord );
}