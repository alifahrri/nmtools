#include "nmtools/array/view/diagonal.hpp"
#include "nmtools/testing/data/index/diagonal.hpp"
#include "nmtools/testing/doctest.hpp"

#define SHAPE_DIAGONAL_SUBCASE(case_name, ...) \
SUBCASE(#case_name) \
{ \
    NMTOOLS_TESTING_USE_CASE(index,shape_diagonal,case_name) \
    using namespace args; \
    auto result = nmtools::index::shape_diagonal(__VA_ARGS__); \
    NMTOOLS_ASSERT_EQUAL( result, expect::result ); \
}

TEST_CASE("shape_diagonal(case1a)" * doctest::test_suite("index::shape_diagonal"))
{
    SHAPE_DIAGONAL_SUBCASE( case1a, src_shape, offset, axis1, axis2 );
    SHAPE_DIAGONAL_SUBCASE( case1a, src_shape_a, offset, axis1, axis2 );
    SHAPE_DIAGONAL_SUBCASE( case1a, src_shape_f, offset, axis1, axis2 );
    SHAPE_DIAGONAL_SUBCASE( case1a, src_shape_h, offset, axis1, axis2 );
    SHAPE_DIAGONAL_SUBCASE( case1a, src_shape_v, offset, axis1, axis2 );

    SHAPE_DIAGONAL_SUBCASE( case1a, src_shape_ct, offset_ct, axis1_ct, axis2_ct );
}

TEST_CASE("shape_diagonal(case1b)" * doctest::test_suite("index::shape_diagonal"))
{
    SHAPE_DIAGONAL_SUBCASE( case1b, src_shape, offset, axis1, axis2 );
    SHAPE_DIAGONAL_SUBCASE( case1b, src_shape_a, offset, axis1, axis2 );
    SHAPE_DIAGONAL_SUBCASE( case1b, src_shape_f, offset, axis1, axis2 );
    SHAPE_DIAGONAL_SUBCASE( case1b, src_shape_h, offset, axis1, axis2 );
    SHAPE_DIAGONAL_SUBCASE( case1b, src_shape_v, offset, axis1, axis2 );

    SHAPE_DIAGONAL_SUBCASE( case1b, src_shape_ct, offset_ct, axis1_ct, axis2_ct );
}

TEST_CASE("shape_diagonal(case1c)" * doctest::test_suite("index::shape_diagonal"))
{
    SHAPE_DIAGONAL_SUBCASE( case1c, src_shape, offset, axis1, axis2 );
    SHAPE_DIAGONAL_SUBCASE( case1c, src_shape_a, offset, axis1, axis2 );
    SHAPE_DIAGONAL_SUBCASE( case1c, src_shape_f, offset, axis1, axis2 );
    SHAPE_DIAGONAL_SUBCASE( case1c, src_shape_h, offset, axis1, axis2 );
    SHAPE_DIAGONAL_SUBCASE( case1c, src_shape_v, offset, axis1, axis2 );

    SHAPE_DIAGONAL_SUBCASE( case1c, src_shape_ct, offset_ct, axis1_ct, axis2_ct );
}

TEST_CASE("shape_diagonal(case1d)" * doctest::test_suite("index::shape_diagonal"))
{
    SHAPE_DIAGONAL_SUBCASE( case1d, src_shape, offset, axis1, axis2 );
    SHAPE_DIAGONAL_SUBCASE( case1d, src_shape_a, offset, axis1, axis2 );
    SHAPE_DIAGONAL_SUBCASE( case1d, src_shape_f, offset, axis1, axis2 );
    SHAPE_DIAGONAL_SUBCASE( case1d, src_shape_h, offset, axis1, axis2 );
    SHAPE_DIAGONAL_SUBCASE( case1d, src_shape_v, offset, axis1, axis2 );

    SHAPE_DIAGONAL_SUBCASE( case1d, src_shape_ct, offset_ct, axis1_ct, axis2_ct );
}

TEST_CASE("shape_diagonal(case2a)" * doctest::test_suite("index::shape_diagonal"))
{
    SHAPE_DIAGONAL_SUBCASE( case2a, src_shape, offset, axis1, axis2 );
    SHAPE_DIAGONAL_SUBCASE( case2a, src_shape_a, offset, axis1, axis2 );
    SHAPE_DIAGONAL_SUBCASE( case2a, src_shape_f, offset, axis1, axis2 );
    SHAPE_DIAGONAL_SUBCASE( case2a, src_shape_h, offset, axis1, axis2 );
    SHAPE_DIAGONAL_SUBCASE( case2a, src_shape_v, offset, axis1, axis2 );

    SHAPE_DIAGONAL_SUBCASE( case2a, src_shape_ct, offset_ct, axis1_ct, axis2_ct );
}

TEST_CASE("shape_diagonal(case2b)" * doctest::test_suite("index::shape_diagonal"))
{
    SHAPE_DIAGONAL_SUBCASE( case2b, src_shape, offset, axis1, axis2 );
    SHAPE_DIAGONAL_SUBCASE( case2b, src_shape_a, offset, axis1, axis2 );
    SHAPE_DIAGONAL_SUBCASE( case2b, src_shape_f, offset, axis1, axis2 );
    SHAPE_DIAGONAL_SUBCASE( case2b, src_shape_h, offset, axis1, axis2 );
    SHAPE_DIAGONAL_SUBCASE( case2b, src_shape_v, offset, axis1, axis2 );

    SHAPE_DIAGONAL_SUBCASE( case2b, src_shape_ct, offset_ct, axis1_ct, axis2_ct );
}

TEST_CASE("shape_diagonal(case2c)" * doctest::test_suite("index::shape_diagonal"))
{
    SHAPE_DIAGONAL_SUBCASE( case2c, src_shape, offset, axis1, axis2 );
    SHAPE_DIAGONAL_SUBCASE( case2c, src_shape_a, offset, axis1, axis2 );
    SHAPE_DIAGONAL_SUBCASE( case2c, src_shape_f, offset, axis1, axis2 );
    SHAPE_DIAGONAL_SUBCASE( case2c, src_shape_h, offset, axis1, axis2 );
    SHAPE_DIAGONAL_SUBCASE( case2c, src_shape_v, offset, axis1, axis2 );

    SHAPE_DIAGONAL_SUBCASE( case2c, src_shape_ct, offset_ct, axis1_ct, axis2_ct );
}

TEST_CASE("shape_diagonal(case2d)" * doctest::test_suite("index::shape_diagonal"))
{
    SHAPE_DIAGONAL_SUBCASE( case2d, src_shape, offset, axis1, axis2 );
    SHAPE_DIAGONAL_SUBCASE( case2d, src_shape_a, offset, axis1, axis2 );
    SHAPE_DIAGONAL_SUBCASE( case2d, src_shape_f, offset, axis1, axis2 );
    SHAPE_DIAGONAL_SUBCASE( case2d, src_shape_h, offset, axis1, axis2 );
    SHAPE_DIAGONAL_SUBCASE( case2d, src_shape_v, offset, axis1, axis2 );

    SHAPE_DIAGONAL_SUBCASE( case2d, src_shape_ct, offset_ct, axis1_ct, axis2_ct );
}

TEST_CASE("shape_diagonal(case2e)" * doctest::test_suite("index::shape_diagonal"))
{
    SHAPE_DIAGONAL_SUBCASE( case2e, src_shape, offset, axis1, axis2 );
    SHAPE_DIAGONAL_SUBCASE( case2e, src_shape_a, offset, axis1, axis2 );
    SHAPE_DIAGONAL_SUBCASE( case2e, src_shape_f, offset, axis1, axis2 );
    SHAPE_DIAGONAL_SUBCASE( case2e, src_shape_h, offset, axis1, axis2 );
    SHAPE_DIAGONAL_SUBCASE( case2e, src_shape_v, offset, axis1, axis2 );

    SHAPE_DIAGONAL_SUBCASE( case2e, src_shape_ct, offset_ct, axis1_ct, axis2_ct );
}

TEST_CASE("shape_diagonal(case2f)" * doctest::test_suite("index::shape_diagonal"))
{
    SHAPE_DIAGONAL_SUBCASE( case2f, src_shape, offset, axis1, axis2 );
    SHAPE_DIAGONAL_SUBCASE( case2f, src_shape_a, offset, axis1, axis2 );
    SHAPE_DIAGONAL_SUBCASE( case2f, src_shape_f, offset, axis1, axis2 );
    SHAPE_DIAGONAL_SUBCASE( case2f, src_shape_h, offset, axis1, axis2 );
    SHAPE_DIAGONAL_SUBCASE( case2f, src_shape_v, offset, axis1, axis2 );

    SHAPE_DIAGONAL_SUBCASE( case2f, src_shape_ct, offset_ct, axis1_ct, axis2_ct );
}

TEST_CASE("shape_diagonal(case3a)" * doctest::test_suite("index::shape_diagonal"))
{
    SHAPE_DIAGONAL_SUBCASE( case3a, src_shape, offset, axis1, axis2 );
    SHAPE_DIAGONAL_SUBCASE( case3a, src_shape_a, offset, axis1, axis2 );
    SHAPE_DIAGONAL_SUBCASE( case3a, src_shape_f, offset, axis1, axis2 );
    SHAPE_DIAGONAL_SUBCASE( case3a, src_shape_h, offset, axis1, axis2 );
    SHAPE_DIAGONAL_SUBCASE( case3a, src_shape_v, offset, axis1, axis2 );

    SHAPE_DIAGONAL_SUBCASE( case3a, src_shape_ct, offset_ct, axis1_ct, axis2_ct );
}

TEST_CASE("shape_diagonal(case3b)" * doctest::test_suite("index::shape_diagonal"))
{
    SHAPE_DIAGONAL_SUBCASE( case3b, src_shape, offset, axis1, axis2 );
    SHAPE_DIAGONAL_SUBCASE( case3b, src_shape_a, offset, axis1, axis2 );
    SHAPE_DIAGONAL_SUBCASE( case3b, src_shape_f, offset, axis1, axis2 );
    SHAPE_DIAGONAL_SUBCASE( case3b, src_shape_h, offset, axis1, axis2 );
    SHAPE_DIAGONAL_SUBCASE( case3b, src_shape_v, offset, axis1, axis2 );

    SHAPE_DIAGONAL_SUBCASE( case3b, src_shape_ct, offset_ct, axis1_ct, axis2_ct );
}