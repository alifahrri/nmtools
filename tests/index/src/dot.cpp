#include "nmtools/array/dot.hpp"
#include "nmtools/testing/data/index/dot.hpp"
#include "nmtools/testing/doctest.hpp"

#define DOT_RHS_TRANSPOSE_SUBCASE(case_name, ...) \
SUBCASE(#case_name) \
{ \
    NMTOOLS_TESTING_USE_CASE( index, dot_rhs_transpose, case_name ); \
    auto result = nmtools::index::dot_rhs_transpose( __VA_ARGS__ ); \
    NMTOOLS_ASSERT_EQUAL( result, expect::result ); \
}

#define DOT_LHS_TILE_SUBCASE(case_name, ...) \
SUBCASE(#case_name) \
{ \
    NMTOOLS_TESTING_USE_CASE( index, dot_lhs_tile, case_name ); \
    auto result = nmtools::index::dot_lhs_tile( __VA_ARGS__ ); \
    NMTOOLS_ASSERT_EQUAL( result, expect::result ); \
}

#define DOT_LHS_RESHAPE_SUBCASE(case_name, ...) \
SUBCASE(#case_name) \
{ \
    NMTOOLS_TESTING_USE_CASE( index, dot_lhs_reshape, case_name ); \
    auto result = nmtools::index::dot_lhs_reshape( __VA_ARGS__ ); \
    NMTOOLS_ASSERT_EQUAL( result, expect::result ); \
}

TEST_CASE("dot_rhs_transpose(case1)" * doctest::test_suite("index::dot_rhs_transpose"))
{
    DOT_RHS_TRANSPOSE_SUBCASE( case1, rhs_shape );
    DOT_RHS_TRANSPOSE_SUBCASE( case1, rhs_shape_a );
    DOT_RHS_TRANSPOSE_SUBCASE( case1, rhs_shape_f );
    DOT_RHS_TRANSPOSE_SUBCASE( case1, rhs_shape_h );
    DOT_RHS_TRANSPOSE_SUBCASE( case1, rhs_shape_v );

    DOT_RHS_TRANSPOSE_SUBCASE( case1, rhs_shape_ct );
}

TEST_CASE("dot_rhs_transpose(case2)" * doctest::test_suite("index::dot_rhs_transpose"))
{
    DOT_RHS_TRANSPOSE_SUBCASE( case2, rhs_shape );
    DOT_RHS_TRANSPOSE_SUBCASE( case2, rhs_shape_a );
    DOT_RHS_TRANSPOSE_SUBCASE( case2, rhs_shape_f );
    DOT_RHS_TRANSPOSE_SUBCASE( case2, rhs_shape_h );
    DOT_RHS_TRANSPOSE_SUBCASE( case2, rhs_shape_v );

    DOT_RHS_TRANSPOSE_SUBCASE( case2, rhs_shape_ct );
}

TEST_CASE("dot_rhs_transpose(case2b)" * doctest::test_suite("index::dot_rhs_transpose"))
{
    DOT_RHS_TRANSPOSE_SUBCASE( case2b, rhs_shape );
    DOT_RHS_TRANSPOSE_SUBCASE( case2b, rhs_shape_a );
    DOT_RHS_TRANSPOSE_SUBCASE( case2b, rhs_shape_f );
    DOT_RHS_TRANSPOSE_SUBCASE( case2b, rhs_shape_h );
    DOT_RHS_TRANSPOSE_SUBCASE( case2b, rhs_shape_v );

    DOT_RHS_TRANSPOSE_SUBCASE( case2b, rhs_shape_ct );
}

TEST_CASE("dot_rhs_transpose(case2c)" * doctest::test_suite("index::dot_rhs_transpose"))
{
    DOT_RHS_TRANSPOSE_SUBCASE( case2c, rhs_shape );
    DOT_RHS_TRANSPOSE_SUBCASE( case2c, rhs_shape_a );
    DOT_RHS_TRANSPOSE_SUBCASE( case2c, rhs_shape_f );
    DOT_RHS_TRANSPOSE_SUBCASE( case2c, rhs_shape_h );
    DOT_RHS_TRANSPOSE_SUBCASE( case2c, rhs_shape_v );

    DOT_RHS_TRANSPOSE_SUBCASE( case2c, rhs_shape_ct );
}

TEST_CASE("dot_rhs_transpose(case2d)" * doctest::test_suite("index::dot_rhs_transpose"))
{
    DOT_RHS_TRANSPOSE_SUBCASE( case2d, rhs_shape );
    DOT_RHS_TRANSPOSE_SUBCASE( case2d, rhs_shape_a );
    DOT_RHS_TRANSPOSE_SUBCASE( case2d, rhs_shape_f );
    DOT_RHS_TRANSPOSE_SUBCASE( case2d, rhs_shape_h );
    DOT_RHS_TRANSPOSE_SUBCASE( case2d, rhs_shape_v );

    DOT_RHS_TRANSPOSE_SUBCASE( case2d, rhs_shape_ct );
}

TEST_CASE("dot_rhs_transpose(case3)" * doctest::test_suite("index::dot_rhs_transpose"))
{
    DOT_RHS_TRANSPOSE_SUBCASE( case3, rhs_shape );
    DOT_RHS_TRANSPOSE_SUBCASE( case3, rhs_shape_a );
    DOT_RHS_TRANSPOSE_SUBCASE( case3, rhs_shape_f );
    DOT_RHS_TRANSPOSE_SUBCASE( case3, rhs_shape_h );
    DOT_RHS_TRANSPOSE_SUBCASE( case3, rhs_shape_v );

    DOT_RHS_TRANSPOSE_SUBCASE( case3, rhs_shape_ct );
}

TEST_CASE("dot_rhs_transpose(case3b)" * doctest::test_suite("index::dot_rhs_transpose"))
{
    DOT_RHS_TRANSPOSE_SUBCASE( case3b, rhs_shape );
    DOT_RHS_TRANSPOSE_SUBCASE( case3b, rhs_shape_a );
    DOT_RHS_TRANSPOSE_SUBCASE( case3b, rhs_shape_f );
    DOT_RHS_TRANSPOSE_SUBCASE( case3b, rhs_shape_h );
    DOT_RHS_TRANSPOSE_SUBCASE( case3b, rhs_shape_v );

    DOT_RHS_TRANSPOSE_SUBCASE( case3b, rhs_shape_ct );
}

TEST_CASE("dot_rhs_transpose(case3c)" * doctest::test_suite("index::dot_rhs_transpose"))
{
    DOT_RHS_TRANSPOSE_SUBCASE( case3c, rhs_shape );
    DOT_RHS_TRANSPOSE_SUBCASE( case3c, rhs_shape_a );
    DOT_RHS_TRANSPOSE_SUBCASE( case3c, rhs_shape_f );
    DOT_RHS_TRANSPOSE_SUBCASE( case3c, rhs_shape_h );
    DOT_RHS_TRANSPOSE_SUBCASE( case3c, rhs_shape_v );

    DOT_RHS_TRANSPOSE_SUBCASE( case3c, rhs_shape_ct );
}

TEST_CASE("dot_rhs_transpose(case3d)" * doctest::test_suite("index::dot_rhs_transpose"))
{
    DOT_RHS_TRANSPOSE_SUBCASE( case3d, rhs_shape );
    DOT_RHS_TRANSPOSE_SUBCASE( case3d, rhs_shape_a );
    DOT_RHS_TRANSPOSE_SUBCASE( case3d, rhs_shape_f );
    DOT_RHS_TRANSPOSE_SUBCASE( case3d, rhs_shape_h );
    DOT_RHS_TRANSPOSE_SUBCASE( case3d, rhs_shape_v );

    DOT_RHS_TRANSPOSE_SUBCASE( case3d, rhs_shape_ct );
}

TEST_CASE("dot_lhs_tile(case1)" * doctest::test_suite("index::dot_lhs_tile"))
{
    DOT_LHS_TILE_SUBCASE( case1, lhs_shape, rhs_shape );
    DOT_LHS_TILE_SUBCASE( case1, lhs_shape_a, rhs_shape_a );
    DOT_LHS_TILE_SUBCASE( case1, lhs_shape_f, rhs_shape_f );
    DOT_LHS_TILE_SUBCASE( case1, lhs_shape_h, rhs_shape_h );
    DOT_LHS_TILE_SUBCASE( case1, lhs_shape_v, rhs_shape_v );

    DOT_LHS_TILE_SUBCASE( case1, lhs_shape_ct, rhs_shape_ct );
}

TEST_CASE("dot_lhs_tile(case2)" * doctest::test_suite("index::dot_lhs_tile"))
{
    DOT_LHS_TILE_SUBCASE( case2, lhs_shape, rhs_shape );
    DOT_LHS_TILE_SUBCASE( case2, lhs_shape_a, rhs_shape_a );
    DOT_LHS_TILE_SUBCASE( case2, lhs_shape_f, rhs_shape_f );
    DOT_LHS_TILE_SUBCASE( case2, lhs_shape_h, rhs_shape_h );
    DOT_LHS_TILE_SUBCASE( case2, lhs_shape_v, rhs_shape_v );

    DOT_LHS_TILE_SUBCASE( case2, lhs_shape_ct, rhs_shape_ct );
}

TEST_CASE("dot_lhs_tile(case2b)" * doctest::test_suite("index::dot_lhs_tile"))
{
    DOT_LHS_TILE_SUBCASE( case2b, lhs_shape, rhs_shape );
    DOT_LHS_TILE_SUBCASE( case2b, lhs_shape_a, rhs_shape_a );
    DOT_LHS_TILE_SUBCASE( case2b, lhs_shape_f, rhs_shape_f );
    DOT_LHS_TILE_SUBCASE( case2b, lhs_shape_h, rhs_shape_h );
    DOT_LHS_TILE_SUBCASE( case2b, lhs_shape_v, rhs_shape_v );

    DOT_LHS_TILE_SUBCASE( case2b, lhs_shape_ct, rhs_shape_ct );
}

TEST_CASE("dot_lhs_tile(case2c)" * doctest::test_suite("index::dot_lhs_tile"))
{
    DOT_LHS_TILE_SUBCASE( case2c, lhs_shape, rhs_shape );
    DOT_LHS_TILE_SUBCASE( case2c, lhs_shape_a, rhs_shape_a );
    DOT_LHS_TILE_SUBCASE( case2c, lhs_shape_f, rhs_shape_f );
    DOT_LHS_TILE_SUBCASE( case2c, lhs_shape_h, rhs_shape_h );
    DOT_LHS_TILE_SUBCASE( case2c, lhs_shape_v, rhs_shape_v );

    DOT_LHS_TILE_SUBCASE( case2c, lhs_shape_ct, rhs_shape_ct );
}

TEST_CASE("dot_lhs_tile(case2d)" * doctest::test_suite("index::dot_lhs_tile"))
{
    DOT_LHS_TILE_SUBCASE( case2d, lhs_shape, rhs_shape );
    DOT_LHS_TILE_SUBCASE( case2d, lhs_shape_a, rhs_shape_a );
    DOT_LHS_TILE_SUBCASE( case2d, lhs_shape_f, rhs_shape_f );
    DOT_LHS_TILE_SUBCASE( case2d, lhs_shape_h, rhs_shape_h );
    DOT_LHS_TILE_SUBCASE( case2d, lhs_shape_v, rhs_shape_v );

    DOT_LHS_TILE_SUBCASE( case2d, lhs_shape_ct, rhs_shape_ct );
}

TEST_CASE("dot_lhs_tile(case3)" * doctest::test_suite("index::dot_lhs_tile"))
{
    DOT_LHS_TILE_SUBCASE( case3, lhs_shape, rhs_shape );
    DOT_LHS_TILE_SUBCASE( case3, lhs_shape_a, rhs_shape_a );
    DOT_LHS_TILE_SUBCASE( case3, lhs_shape_f, rhs_shape_f );
    DOT_LHS_TILE_SUBCASE( case3, lhs_shape_h, rhs_shape_h );
    DOT_LHS_TILE_SUBCASE( case3, lhs_shape_v, rhs_shape_v );

    DOT_LHS_TILE_SUBCASE( case3, lhs_shape_ct, rhs_shape_ct );
}

TEST_CASE("dot_lhs_tile(case3b)" * doctest::test_suite("index::dot_lhs_tile"))
{
    DOT_LHS_TILE_SUBCASE( case3b, lhs_shape, rhs_shape );
    DOT_LHS_TILE_SUBCASE( case3b, lhs_shape_a, rhs_shape_a );
    DOT_LHS_TILE_SUBCASE( case3b, lhs_shape_f, rhs_shape_f );
    DOT_LHS_TILE_SUBCASE( case3b, lhs_shape_h, rhs_shape_h );
    DOT_LHS_TILE_SUBCASE( case3b, lhs_shape_v, rhs_shape_v );

    DOT_LHS_TILE_SUBCASE( case3b, lhs_shape_ct, rhs_shape_ct );
}

TEST_CASE("dot_lhs_tile(case3c)" * doctest::test_suite("index::dot_lhs_tile"))
{
    DOT_LHS_TILE_SUBCASE( case3c, lhs_shape, rhs_shape );
    DOT_LHS_TILE_SUBCASE( case3c, lhs_shape_a, rhs_shape_a );
    DOT_LHS_TILE_SUBCASE( case3c, lhs_shape_f, rhs_shape_f );
    DOT_LHS_TILE_SUBCASE( case3c, lhs_shape_h, rhs_shape_h );
    DOT_LHS_TILE_SUBCASE( case3c, lhs_shape_v, rhs_shape_v );

    DOT_LHS_TILE_SUBCASE( case3c, lhs_shape_ct, rhs_shape_ct );
}

TEST_CASE("dot_lhs_tile(case3d)" * doctest::test_suite("index::dot_lhs_tile"))
{
    DOT_LHS_TILE_SUBCASE( case3d, lhs_shape, rhs_shape );
    DOT_LHS_TILE_SUBCASE( case3d, lhs_shape_a, rhs_shape_a );
    DOT_LHS_TILE_SUBCASE( case3d, lhs_shape_f, rhs_shape_f );
    DOT_LHS_TILE_SUBCASE( case3d, lhs_shape_h, rhs_shape_h );
    DOT_LHS_TILE_SUBCASE( case3d, lhs_shape_v, rhs_shape_v );

    DOT_LHS_TILE_SUBCASE( case3d, lhs_shape_ct, rhs_shape_ct );
}

TEST_CASE("dot_lhs_reshape(case1)" * doctest::test_suite("index::dot_lhs_reshape"))
{
    DOT_LHS_RESHAPE_SUBCASE( case1, lhs_shape, rhs_shape );
    DOT_LHS_RESHAPE_SUBCASE( case1, lhs_shape_a, rhs_shape_a );
    DOT_LHS_RESHAPE_SUBCASE( case1, lhs_shape_f, rhs_shape_f );
    DOT_LHS_RESHAPE_SUBCASE( case1, lhs_shape_h, rhs_shape_h );
    DOT_LHS_RESHAPE_SUBCASE( case1, lhs_shape_v, rhs_shape_v );

    DOT_LHS_RESHAPE_SUBCASE( case1, lhs_shape_ct, rhs_shape_ct );
}

TEST_CASE("dot_lhs_reshape(case2)" * doctest::test_suite("index::dot_lhs_reshape"))
{
    DOT_LHS_RESHAPE_SUBCASE( case2, lhs_shape, rhs_shape );
    DOT_LHS_RESHAPE_SUBCASE( case2, lhs_shape_a, rhs_shape_a );
    DOT_LHS_RESHAPE_SUBCASE( case2, lhs_shape_f, rhs_shape_f );
    DOT_LHS_RESHAPE_SUBCASE( case2, lhs_shape_h, rhs_shape_h );
    DOT_LHS_RESHAPE_SUBCASE( case2, lhs_shape_v, rhs_shape_v );

    DOT_LHS_RESHAPE_SUBCASE( case2, lhs_shape_ct, rhs_shape_ct );
}

TEST_CASE("dot_lhs_reshape(case2b)" * doctest::test_suite("index::dot_lhs_reshape"))
{
    DOT_LHS_RESHAPE_SUBCASE( case2b, lhs_shape, rhs_shape );
    DOT_LHS_RESHAPE_SUBCASE( case2b, lhs_shape_a, rhs_shape_a );
    DOT_LHS_RESHAPE_SUBCASE( case2b, lhs_shape_f, rhs_shape_f );
    DOT_LHS_RESHAPE_SUBCASE( case2b, lhs_shape_h, rhs_shape_h );
    DOT_LHS_RESHAPE_SUBCASE( case2b, lhs_shape_v, rhs_shape_v );

    DOT_LHS_RESHAPE_SUBCASE( case2b, lhs_shape_ct, rhs_shape_ct );
}

TEST_CASE("dot_lhs_reshape(case2c)" * doctest::test_suite("index::dot_lhs_reshape"))
{
    DOT_LHS_RESHAPE_SUBCASE( case2c, lhs_shape, rhs_shape );
    DOT_LHS_RESHAPE_SUBCASE( case2c, lhs_shape_a, rhs_shape_a );
    DOT_LHS_RESHAPE_SUBCASE( case2c, lhs_shape_f, rhs_shape_f );
    DOT_LHS_RESHAPE_SUBCASE( case2c, lhs_shape_h, rhs_shape_h );
    DOT_LHS_RESHAPE_SUBCASE( case2c, lhs_shape_v, rhs_shape_v );

    DOT_LHS_RESHAPE_SUBCASE( case2c, lhs_shape_ct, rhs_shape_ct );
}

TEST_CASE("dot_lhs_reshape(case2d)" * doctest::test_suite("index::dot_lhs_reshape"))
{
    DOT_LHS_RESHAPE_SUBCASE( case2d, lhs_shape, rhs_shape );
    DOT_LHS_RESHAPE_SUBCASE( case2d, lhs_shape_a, rhs_shape_a );
    DOT_LHS_RESHAPE_SUBCASE( case2d, lhs_shape_f, rhs_shape_f );
    DOT_LHS_RESHAPE_SUBCASE( case2d, lhs_shape_h, rhs_shape_h );
    DOT_LHS_RESHAPE_SUBCASE( case2d, lhs_shape_v, rhs_shape_v );

    DOT_LHS_RESHAPE_SUBCASE( case2d, lhs_shape_ct, rhs_shape_ct );
}

TEST_CASE("dot_lhs_reshape(case3)" * doctest::test_suite("index::dot_lhs_reshape"))
{
    DOT_LHS_RESHAPE_SUBCASE( case3, lhs_shape, rhs_shape );
    DOT_LHS_RESHAPE_SUBCASE( case3, lhs_shape_a, rhs_shape_a );
    DOT_LHS_RESHAPE_SUBCASE( case3, lhs_shape_f, rhs_shape_f );
    DOT_LHS_RESHAPE_SUBCASE( case3, lhs_shape_h, rhs_shape_h );
    DOT_LHS_RESHAPE_SUBCASE( case3, lhs_shape_v, rhs_shape_v );

    DOT_LHS_RESHAPE_SUBCASE( case3, lhs_shape_ct, rhs_shape_ct );
}

TEST_CASE("dot_lhs_reshape(case3b)" * doctest::test_suite("index::dot_lhs_reshape"))
{
    DOT_LHS_RESHAPE_SUBCASE( case3b, lhs_shape, rhs_shape );
    DOT_LHS_RESHAPE_SUBCASE( case3b, lhs_shape_a, rhs_shape_a );
    DOT_LHS_RESHAPE_SUBCASE( case3b, lhs_shape_f, rhs_shape_f );
    DOT_LHS_RESHAPE_SUBCASE( case3b, lhs_shape_h, rhs_shape_h );
    DOT_LHS_RESHAPE_SUBCASE( case3b, lhs_shape_v, rhs_shape_v );

    DOT_LHS_RESHAPE_SUBCASE( case3b, lhs_shape_ct, rhs_shape_ct );
}

TEST_CASE("dot_lhs_reshape(case3c)" * doctest::test_suite("index::dot_lhs_reshape"))
{
    DOT_LHS_RESHAPE_SUBCASE( case3c, lhs_shape, rhs_shape );
    DOT_LHS_RESHAPE_SUBCASE( case3c, lhs_shape_a, rhs_shape_a );
    DOT_LHS_RESHAPE_SUBCASE( case3c, lhs_shape_f, rhs_shape_f );
    DOT_LHS_RESHAPE_SUBCASE( case3c, lhs_shape_h, rhs_shape_h );
    DOT_LHS_RESHAPE_SUBCASE( case3c, lhs_shape_v, rhs_shape_v );

    DOT_LHS_RESHAPE_SUBCASE( case3c, lhs_shape_ct, rhs_shape_ct );
}

TEST_CASE("dot_lhs_reshape(case3d)" * doctest::test_suite("index::dot_lhs_reshape"))
{
    DOT_LHS_RESHAPE_SUBCASE( case3d, lhs_shape, rhs_shape );
    DOT_LHS_RESHAPE_SUBCASE( case3d, lhs_shape_a, rhs_shape_a );
    DOT_LHS_RESHAPE_SUBCASE( case3d, lhs_shape_f, rhs_shape_f );
    DOT_LHS_RESHAPE_SUBCASE( case3d, lhs_shape_h, rhs_shape_h );
    DOT_LHS_RESHAPE_SUBCASE( case3d, lhs_shape_v, rhs_shape_v );

    DOT_LHS_RESHAPE_SUBCASE( case3d, lhs_shape_ct, rhs_shape_ct );
}