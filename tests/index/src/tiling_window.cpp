#include "nmtools/array/tiling_window.hpp"
#include "nmtools/testing/data/index/tiling_window.hpp"
#include "nmtools/testing/doctest.hpp"

#define SHAPE_TILING_WINDOW_EXPECT_SUBCASE(case_name, exp, ...) \
SUBCASE(#case_name) \
{ \
    NMTOOLS_TESTING_USE_CASE(index, shape_tiling_window, case_name); \
    using namespace args; \
    auto result = nmtools::index::shape_tiling_window(__VA_ARGS__); \
    NMTOOLS_ASSERT_EQUAL_MSG_ATTRIBUTES( result, expect::exp, __VA_ARGS__ ); \
}

#define SHAPE_TILING_WINDOW_SUBCASE(case_name, ...) \
SUBCASE(#case_name) \
{ \
    SHAPE_TILING_WINDOW_EXPECT_SUBCASE(case_name, dst_shape, __VA_ARGS__ ); \
}

#define TILING_WINDOW_SUBCASE(case_name, ...) \
SUBCASE(#case_name) \
{ \
    NMTOOLS_TESTING_USE_CASE(index, tiling_window, case_name); \
    using namespace args; \
    auto result = nmtools::index::tiling_window(__VA_ARGS__); \
    NMTOOLS_ASSERT_EQUAL_MSG_ATTRIBUTES( result, expect::src_indices, __VA_ARGS__ ); \
}

TEST_CASE("shape_tiling_window(case1)" * doctest::test_suite("index::shape_tiling_window"))
{
    SHAPE_TILING_WINDOW_SUBCASE( case1, src_shape, tile_shape );
    SHAPE_TILING_WINDOW_SUBCASE( case1, src_shape_a, tile_shape );
    SHAPE_TILING_WINDOW_SUBCASE( case1, src_shape_f, tile_shape );
    SHAPE_TILING_WINDOW_SUBCASE( case1, src_shape_h, tile_shape );
    SHAPE_TILING_WINDOW_SUBCASE( case1, src_shape_v, tile_shape );

    SHAPE_TILING_WINDOW_SUBCASE( case1, src_shape_ct, tile_shape_ct );
    SHAPE_TILING_WINDOW_SUBCASE( case1, src_shape_ct, tile_shape );

    // should results in mixed index array
    SHAPE_TILING_WINDOW_SUBCASE( case1, src_shape, tile_shape_ct );

    SHAPE_TILING_WINDOW_SUBCASE( case1, src_shape_nl, tile_shape );
    SHAPE_TILING_WINDOW_EXPECT_SUBCASE( case1, dst_shape_nn, src_shape_nn, tile_shape );
}

TEST_CASE("shape_tiling_window(case2)" * doctest::test_suite("index::shape_tiling_window"))
{
    SHAPE_TILING_WINDOW_SUBCASE( case2, src_shape, tile_shape );
    SHAPE_TILING_WINDOW_SUBCASE( case2, src_shape_a, tile_shape_a );
    SHAPE_TILING_WINDOW_SUBCASE( case2, src_shape_f, tile_shape_f );
    SHAPE_TILING_WINDOW_SUBCASE( case2, src_shape_h, tile_shape_h );
    SHAPE_TILING_WINDOW_SUBCASE( case2, src_shape_v, tile_shape_v );

    SHAPE_TILING_WINDOW_SUBCASE( case2, src_shape_ct, tile_shape_ct );
    SHAPE_TILING_WINDOW_SUBCASE( case2, src_shape_mx1, tile_shape_mx1 );

    // should results in mixed index array
    SHAPE_TILING_WINDOW_SUBCASE( case2, src_shape, tile_shape_ct );

    SHAPE_TILING_WINDOW_SUBCASE( case2, src_shape_nl, tile_shape );
    SHAPE_TILING_WINDOW_EXPECT_SUBCASE( case2, dst_shape_nn0, src_shape_nn0, tile_shape );
    SHAPE_TILING_WINDOW_EXPECT_SUBCASE( case2, dst_shape_nn1, src_shape_nn1, tile_shape );
}

TEST_CASE("shape_tiling_window(case2b)" * doctest::test_suite("index::shape_tiling_window"))
{
    SHAPE_TILING_WINDOW_SUBCASE( case2b, src_shape, tile_shape );
    SHAPE_TILING_WINDOW_SUBCASE( case2b, src_shape_a, tile_shape_a );
    SHAPE_TILING_WINDOW_SUBCASE( case2b, src_shape_f, tile_shape_f );
    SHAPE_TILING_WINDOW_SUBCASE( case2b, src_shape_h, tile_shape_h );
    SHAPE_TILING_WINDOW_SUBCASE( case2b, src_shape_v, tile_shape_v );

    SHAPE_TILING_WINDOW_SUBCASE( case2b, src_shape_ct, tile_shape_ct );

    SHAPE_TILING_WINDOW_SUBCASE( case2b, src_shape_nl, tile_shape );
    SHAPE_TILING_WINDOW_EXPECT_SUBCASE( case2b, dst_shape_nn0, src_shape_nn0, tile_shape );
    SHAPE_TILING_WINDOW_EXPECT_SUBCASE( case2b, dst_shape_nn1, src_shape_nn1, tile_shape );
    SHAPE_TILING_WINDOW_EXPECT_SUBCASE( case2b, dst_shape_nn2, src_shape_nn2, tile_shape );
}

TEST_CASE("shape_tiling_window(case2c)" * doctest::test_suite("index::shape_tiling_window"))
{
    SHAPE_TILING_WINDOW_SUBCASE( case2c, src_shape, tile_shape, axis );
    SHAPE_TILING_WINDOW_SUBCASE( case2c, src_shape_a, tile_shape, axis );
    SHAPE_TILING_WINDOW_SUBCASE( case2c, src_shape_f, tile_shape, axis );
    SHAPE_TILING_WINDOW_SUBCASE( case2c, src_shape_h, tile_shape, axis );
    SHAPE_TILING_WINDOW_SUBCASE( case2c, src_shape_v, tile_shape, axis );

    SHAPE_TILING_WINDOW_SUBCASE( case2c, src_shape_ct, tile_shape_ct, axis_ct );

    SHAPE_TILING_WINDOW_SUBCASE( case2c, src_shape_nl, tile_shape, axis );
    SHAPE_TILING_WINDOW_EXPECT_SUBCASE( case2c, dst_shape_nn0, src_shape_nn0, tile_shape, axis );
    SHAPE_TILING_WINDOW_EXPECT_SUBCASE( case2c, dst_shape_nn1, src_shape_nn1, tile_shape, axis );
    SHAPE_TILING_WINDOW_EXPECT_SUBCASE( case2c, dst_shape_nn2, src_shape_nn2, tile_shape, axis );
}

TEST_CASE("shape_tiling_window(case2d)" * doctest::test_suite("index::shape_tiling_window"))
{
    SHAPE_TILING_WINDOW_SUBCASE( case2d, src_shape, tile_shape, axis );
    SHAPE_TILING_WINDOW_SUBCASE( case2d, src_shape_a, tile_shape, axis );
    SHAPE_TILING_WINDOW_SUBCASE( case2d, src_shape_f, tile_shape, axis );
    SHAPE_TILING_WINDOW_SUBCASE( case2d, src_shape_h, tile_shape, axis );
    SHAPE_TILING_WINDOW_SUBCASE( case2d, src_shape_v, tile_shape, axis );

    SHAPE_TILING_WINDOW_SUBCASE( case2d, src_shape_ct, tile_shape_ct, axis_ct );

    SHAPE_TILING_WINDOW_SUBCASE( case2d, src_shape_nl, tile_shape, axis );
    SHAPE_TILING_WINDOW_EXPECT_SUBCASE( case2d, dst_shape_nn0, src_shape_nn0, tile_shape, axis );
    SHAPE_TILING_WINDOW_EXPECT_SUBCASE( case2d, dst_shape_nn1, src_shape_nn1, tile_shape, axis );
    SHAPE_TILING_WINDOW_EXPECT_SUBCASE( case2d, dst_shape_nn2, src_shape_nn2, tile_shape, axis );
}

TEST_CASE("shape_tiling_window(case2e)" * doctest::test_suite("index::shape_tiling_window"))
{
    SHAPE_TILING_WINDOW_SUBCASE( case2e, src_shape, tile_shape );
    SHAPE_TILING_WINDOW_SUBCASE( case2e, src_shape_a, tile_shape );
    SHAPE_TILING_WINDOW_SUBCASE( case2e, src_shape_f, tile_shape );
    SHAPE_TILING_WINDOW_SUBCASE( case2e, src_shape_h, tile_shape );
    SHAPE_TILING_WINDOW_SUBCASE( case2e, src_shape_v, tile_shape );

    SHAPE_TILING_WINDOW_SUBCASE( case2e, src_shape_ct, tile_shape_ct );

    SHAPE_TILING_WINDOW_SUBCASE( case2e, src_shape_nl, tile_shape );
    SHAPE_TILING_WINDOW_EXPECT_SUBCASE( case2e, dst_shape_nn0, src_shape_nn0, tile_shape );
    SHAPE_TILING_WINDOW_EXPECT_SUBCASE( case2e, dst_shape_nn1, src_shape_nn1, tile_shape );
    SHAPE_TILING_WINDOW_EXPECT_SUBCASE( case2e, dst_shape_nn2, src_shape_nn2, tile_shape );
}

TEST_CASE("shape_tiling_window(case3a)" * doctest::test_suite("index::shape_tiling_window"))
{
    SHAPE_TILING_WINDOW_SUBCASE( case3a, src_shape, tile_shape );
    SHAPE_TILING_WINDOW_SUBCASE( case3a, src_shape_a, tile_shape_a );
    SHAPE_TILING_WINDOW_SUBCASE( case3a, src_shape_f, tile_shape_f );
    SHAPE_TILING_WINDOW_SUBCASE( case3a, src_shape_h, tile_shape_h );
    SHAPE_TILING_WINDOW_SUBCASE( case3a, src_shape_v, tile_shape_v );
    
    SHAPE_TILING_WINDOW_SUBCASE( case3a, src_shape_ct, tile_shape_ct );

    SHAPE_TILING_WINDOW_SUBCASE( case3a, src_shape_nl, tile_shape );
    SHAPE_TILING_WINDOW_EXPECT_SUBCASE( case3a, dst_shape_nn0, src_shape_nn0, tile_shape );
    SHAPE_TILING_WINDOW_EXPECT_SUBCASE( case3a, dst_shape_nn1, src_shape_nn1, tile_shape );
    SHAPE_TILING_WINDOW_EXPECT_SUBCASE( case3a, dst_shape_nn2, src_shape_nn2, tile_shape );
}

TEST_CASE("shape_tiling_window(case3d)" * doctest::test_suite("index::shape_tiling_window"))
{
    SHAPE_TILING_WINDOW_SUBCASE( case3d, src_shape, tile_shape, axis );
    SHAPE_TILING_WINDOW_SUBCASE( case3d, src_shape_a, tile_shape_a, axis_a );
    SHAPE_TILING_WINDOW_SUBCASE( case3d, src_shape_f, tile_shape_f, axis_f );
    SHAPE_TILING_WINDOW_SUBCASE( case3d, src_shape_h, tile_shape_h, axis_h );
    SHAPE_TILING_WINDOW_SUBCASE( case3d, src_shape_v, tile_shape_v, axis_v );
    
    // TODO: enable
    // SHAPE_TILING_WINDOW_SUBCASE( case3d, src_shape_ct, tile_shape_ct, axis_ct );

    // TODO: fix
    SHAPE_TILING_WINDOW_SUBCASE( case3d, src_shape_nl, tile_shape, axis );
    SHAPE_TILING_WINDOW_EXPECT_SUBCASE( case3d, dst_shape_nn0, src_shape_nn0, tile_shape, axis );
    SHAPE_TILING_WINDOW_EXPECT_SUBCASE( case3d, dst_shape_nn1, src_shape_nn1, tile_shape, axis );
    SHAPE_TILING_WINDOW_EXPECT_SUBCASE( case3d, dst_shape_nn2, src_shape_nn2, tile_shape, axis );
}

TEST_CASE("tiling_window(case1_0_0)" * doctest::test_suite("index::tiling_window"))
{
    TILING_WINDOW_SUBCASE( case1_0_0, dst_indices, src_shape, tile_shape );
    TILING_WINDOW_SUBCASE( case1_0_0, dst_indices_a, src_shape_a, tile_shape );
    TILING_WINDOW_SUBCASE( case1_0_0, dst_indices_f, src_shape_f, tile_shape );
    TILING_WINDOW_SUBCASE( case1_0_0, dst_indices_h, src_shape_h, tile_shape );
    TILING_WINDOW_SUBCASE( case1_0_0, dst_indices_v, src_shape_v, tile_shape );
}

TEST_CASE("tiling_window(case1_0_1)" * doctest::test_suite("index::tiling_window"))
{
    TILING_WINDOW_SUBCASE( case1_0_1, dst_indices, src_shape, tile_shape );
    TILING_WINDOW_SUBCASE( case1_0_1, dst_indices_a, src_shape_a, tile_shape );
    TILING_WINDOW_SUBCASE( case1_0_1, dst_indices_f, src_shape_f, tile_shape );
    TILING_WINDOW_SUBCASE( case1_0_1, dst_indices_h, src_shape_h, tile_shape );
    TILING_WINDOW_SUBCASE( case1_0_1, dst_indices_v, src_shape_v, tile_shape );
}

TEST_CASE("tiling_window(case1_0_2)" * doctest::test_suite("index::tiling_window"))
{
    TILING_WINDOW_SUBCASE( case1_0_2, dst_indices, src_shape, tile_shape );
    TILING_WINDOW_SUBCASE( case1_0_2, dst_indices_a, src_shape_a, tile_shape );
    TILING_WINDOW_SUBCASE( case1_0_2, dst_indices_f, src_shape_f, tile_shape );
    TILING_WINDOW_SUBCASE( case1_0_2, dst_indices_h, src_shape_h, tile_shape );
    TILING_WINDOW_SUBCASE( case1_0_2, dst_indices_v, src_shape_v, tile_shape );
}

TEST_CASE("tiling_window(case1_1_0)" * doctest::test_suite("index::tiling_window"))
{
    TILING_WINDOW_SUBCASE( case1_1_0, dst_indices, src_shape, tile_shape );
    TILING_WINDOW_SUBCASE( case1_1_0, dst_indices_a, src_shape_a, tile_shape );
    TILING_WINDOW_SUBCASE( case1_1_0, dst_indices_f, src_shape_f, tile_shape );
    TILING_WINDOW_SUBCASE( case1_1_0, dst_indices_h, src_shape_h, tile_shape );
    TILING_WINDOW_SUBCASE( case1_1_0, dst_indices_v, src_shape_v, tile_shape );
}

TEST_CASE("tiling_window(case1_1_1)" * doctest::test_suite("index::tiling_window"))
{
    TILING_WINDOW_SUBCASE( case1_1_1, dst_indices, src_shape, tile_shape );
    TILING_WINDOW_SUBCASE( case1_1_1, dst_indices_a, src_shape_a, tile_shape );
    TILING_WINDOW_SUBCASE( case1_1_1, dst_indices_f, src_shape_f, tile_shape );
    TILING_WINDOW_SUBCASE( case1_1_1, dst_indices_h, src_shape_h, tile_shape );
    TILING_WINDOW_SUBCASE( case1_1_1, dst_indices_v, src_shape_v, tile_shape );
}

TEST_CASE("tiling_window(case1_1_2)" * doctest::test_suite("index::tiling_window"))
{
    TILING_WINDOW_SUBCASE( case1_1_2, dst_indices, src_shape, tile_shape );
    TILING_WINDOW_SUBCASE( case1_1_2, dst_indices_a, src_shape_a, tile_shape );
    TILING_WINDOW_SUBCASE( case1_1_2, dst_indices_f, src_shape_f, tile_shape );
    TILING_WINDOW_SUBCASE( case1_1_2, dst_indices_h, src_shape_h, tile_shape );
    TILING_WINDOW_SUBCASE( case1_1_2, dst_indices_v, src_shape_v, tile_shape );
}

TEST_CASE("tiling_window(case2_0_0_0_0)" * doctest::test_suite("index::tiling_window"))
{
    TILING_WINDOW_SUBCASE( case2_0_0_0_0, dst_indices, src_shape, tile_shape );
    TILING_WINDOW_SUBCASE( case2_0_0_0_0, dst_indices_a, src_shape_a, tile_shape );
    TILING_WINDOW_SUBCASE( case2_0_0_0_0, dst_indices_f, src_shape_f, tile_shape );
    TILING_WINDOW_SUBCASE( case2_0_0_0_0, dst_indices_h, src_shape_h, tile_shape );
    TILING_WINDOW_SUBCASE( case2_0_0_0_0, dst_indices_v, src_shape_v, tile_shape );
}

TEST_CASE("tiling_window(case2_0_0_0_1)" * doctest::test_suite("index::tiling_window"))
{
    TILING_WINDOW_SUBCASE( case2_0_0_0_1, dst_indices, src_shape, tile_shape );
    TILING_WINDOW_SUBCASE( case2_0_0_0_1, dst_indices_a, src_shape_a, tile_shape );
    TILING_WINDOW_SUBCASE( case2_0_0_0_1, dst_indices_f, src_shape_f, tile_shape );
    TILING_WINDOW_SUBCASE( case2_0_0_0_1, dst_indices_h, src_shape_h, tile_shape );
    TILING_WINDOW_SUBCASE( case2_0_0_0_1, dst_indices_v, src_shape_v, tile_shape );
}

TEST_CASE("tiling_window(case2_0_1_0_0)" * doctest::test_suite("index::tiling_window"))
{
    TILING_WINDOW_SUBCASE( case2_0_1_0_0, dst_indices, src_shape, tile_shape );
    TILING_WINDOW_SUBCASE( case2_0_1_0_0, dst_indices_a, src_shape_a, tile_shape );
    TILING_WINDOW_SUBCASE( case2_0_1_0_0, dst_indices_f, src_shape_f, tile_shape );
    TILING_WINDOW_SUBCASE( case2_0_1_0_0, dst_indices_h, src_shape_h, tile_shape );
    TILING_WINDOW_SUBCASE( case2_0_1_0_0, dst_indices_v, src_shape_v, tile_shape );
}

TEST_CASE("tiling_window(case2_0_1_0_1)" * doctest::test_suite("index::tiling_window"))
{
    TILING_WINDOW_SUBCASE( case2_0_1_0_1, dst_indices, src_shape, tile_shape );
    TILING_WINDOW_SUBCASE( case2_0_1_0_1, dst_indices_a, src_shape_a, tile_shape );
    TILING_WINDOW_SUBCASE( case2_0_1_0_1, dst_indices_f, src_shape_f, tile_shape );
    TILING_WINDOW_SUBCASE( case2_0_1_0_1, dst_indices_h, src_shape_h, tile_shape );
    TILING_WINDOW_SUBCASE( case2_0_1_0_1, dst_indices_v, src_shape_v, tile_shape );
}

TEST_CASE("tiling_window(case2_1_0_0_0)" * doctest::test_suite("index::tiling_window"))
{
    TILING_WINDOW_SUBCASE( case2_1_0_0_0, dst_indices, src_shape, tile_shape );
    TILING_WINDOW_SUBCASE( case2_1_0_0_0, dst_indices_a, src_shape_a, tile_shape );
    TILING_WINDOW_SUBCASE( case2_1_0_0_0, dst_indices_f, src_shape_f, tile_shape );
    TILING_WINDOW_SUBCASE( case2_1_0_0_0, dst_indices_h, src_shape_h, tile_shape );
    TILING_WINDOW_SUBCASE( case2_1_0_0_0, dst_indices_v, src_shape_v, tile_shape );
}

TEST_CASE("tiling_window(case2_1_0_0_1)" * doctest::test_suite("index::tiling_window"))
{
    TILING_WINDOW_SUBCASE( case2_1_0_0_1, dst_indices, src_shape, tile_shape );
    TILING_WINDOW_SUBCASE( case2_1_0_0_1, dst_indices_a, src_shape_a, tile_shape );
    TILING_WINDOW_SUBCASE( case2_1_0_0_1, dst_indices_f, src_shape_f, tile_shape );
    TILING_WINDOW_SUBCASE( case2_1_0_0_1, dst_indices_h, src_shape_h, tile_shape );
    TILING_WINDOW_SUBCASE( case2_1_0_0_1, dst_indices_v, src_shape_v, tile_shape );
}

TEST_CASE("tiling_window(case2_1_1_0_0)" * doctest::test_suite("index::tiling_window"))
{
    TILING_WINDOW_SUBCASE( case2_1_1_0_0, dst_indices, src_shape, tile_shape );
    TILING_WINDOW_SUBCASE( case2_1_1_0_0, dst_indices_a, src_shape_a, tile_shape );
    TILING_WINDOW_SUBCASE( case2_1_1_0_0, dst_indices_f, src_shape_f, tile_shape );
    TILING_WINDOW_SUBCASE( case2_1_1_0_0, dst_indices_h, src_shape_h, tile_shape );
    TILING_WINDOW_SUBCASE( case2_1_1_0_0, dst_indices_v, src_shape_v, tile_shape );
}

TEST_CASE("tiling_window(case2_1_1_0_1)" * doctest::test_suite("index::tiling_window"))
{
    TILING_WINDOW_SUBCASE( case2_1_1_0_1, dst_indices, src_shape, tile_shape );
    TILING_WINDOW_SUBCASE( case2_1_1_0_1, dst_indices_a, src_shape_a, tile_shape );
    TILING_WINDOW_SUBCASE( case2_1_1_0_1, dst_indices_f, src_shape_f, tile_shape );
    TILING_WINDOW_SUBCASE( case2_1_1_0_1, dst_indices_h, src_shape_h, tile_shape );
    TILING_WINDOW_SUBCASE( case2_1_1_0_1, dst_indices_v, src_shape_v, tile_shape );
}

TEST_CASE("tiling_window(case2_2_0_0_0)" * doctest::test_suite("index::tiling_window"))
{
    TILING_WINDOW_SUBCASE( case2_2_0_0_0, dst_indices, src_shape, tile_shape );
    TILING_WINDOW_SUBCASE( case2_2_0_0_0, dst_indices_a, src_shape_a, tile_shape );
    TILING_WINDOW_SUBCASE( case2_2_0_0_0, dst_indices_f, src_shape_f, tile_shape );
    TILING_WINDOW_SUBCASE( case2_2_0_0_0, dst_indices_h, src_shape_h, tile_shape );
    TILING_WINDOW_SUBCASE( case2_2_0_0_0, dst_indices_v, src_shape_v, tile_shape );
}

TEST_CASE("tiling_window(case2_2_0_0_1)" * doctest::test_suite("index::tiling_window"))
{
    TILING_WINDOW_SUBCASE( case2_2_0_0_1, dst_indices, src_shape, tile_shape );
    TILING_WINDOW_SUBCASE( case2_2_0_0_1, dst_indices_a, src_shape_a, tile_shape );
    TILING_WINDOW_SUBCASE( case2_2_0_0_1, dst_indices_f, src_shape_f, tile_shape );
    TILING_WINDOW_SUBCASE( case2_2_0_0_1, dst_indices_h, src_shape_h, tile_shape );
    TILING_WINDOW_SUBCASE( case2_2_0_0_1, dst_indices_v, src_shape_v, tile_shape );
}

TEST_CASE("tiling_window(case2_2_1_0_0)" * doctest::test_suite("index::tiling_window"))
{
    TILING_WINDOW_SUBCASE( case2_2_1_0_0, dst_indices, src_shape, tile_shape );
    TILING_WINDOW_SUBCASE( case2_2_1_0_0, dst_indices_a, src_shape_a, tile_shape );
    TILING_WINDOW_SUBCASE( case2_2_1_0_0, dst_indices_f, src_shape_f, tile_shape );
    TILING_WINDOW_SUBCASE( case2_2_1_0_0, dst_indices_h, src_shape_h, tile_shape );
    TILING_WINDOW_SUBCASE( case2_2_1_0_0, dst_indices_v, src_shape_v, tile_shape );
}

TEST_CASE("tiling_window(case2_2_1_0_1)" * doctest::test_suite("index::tiling_window"))
{
    TILING_WINDOW_SUBCASE( case2_2_1_0_1, dst_indices, src_shape, tile_shape );
    TILING_WINDOW_SUBCASE( case2_2_1_0_1, dst_indices_a, src_shape_a, tile_shape );
    TILING_WINDOW_SUBCASE( case2_2_1_0_1, dst_indices_f, src_shape_f, tile_shape );
    TILING_WINDOW_SUBCASE( case2_2_1_0_1, dst_indices_h, src_shape_h, tile_shape );
    TILING_WINDOW_SUBCASE( case2_2_1_0_1, dst_indices_v, src_shape_v, tile_shape );
}

TEST_CASE("tiling_window(case2_2c_0_0_0)" * doctest::test_suite("index::tiling_window"))
{
    TILING_WINDOW_SUBCASE( case2c_0_0_0, dst_indices, src_shape, tile_shape, axis );
    TILING_WINDOW_SUBCASE( case2c_0_0_0, dst_indices_a, src_shape_a, tile_shape, axis );
    TILING_WINDOW_SUBCASE( case2c_0_0_0, dst_indices_f, src_shape_f, tile_shape, axis );
    TILING_WINDOW_SUBCASE( case2c_0_0_0, dst_indices_h, src_shape_h, tile_shape, axis );
    TILING_WINDOW_SUBCASE( case2c_0_0_0, dst_indices_v, src_shape_v, tile_shape, axis );
}

TEST_CASE("tiling_window(case2_2c_0_0_1)" * doctest::test_suite("index::tiling_window"))
{
    TILING_WINDOW_SUBCASE( case2c_0_0_1, dst_indices, src_shape, tile_shape, axis );
    TILING_WINDOW_SUBCASE( case2c_0_0_1, dst_indices_a, src_shape_a, tile_shape, axis );
    TILING_WINDOW_SUBCASE( case2c_0_0_1, dst_indices_f, src_shape_f, tile_shape, axis );
    TILING_WINDOW_SUBCASE( case2c_0_0_1, dst_indices_h, src_shape_h, tile_shape, axis );
    TILING_WINDOW_SUBCASE( case2c_0_0_1, dst_indices_v, src_shape_v, tile_shape, axis );
}

TEST_CASE("tiling_window(case2_2c_0_0_2)" * doctest::test_suite("index::tiling_window"))
{
    TILING_WINDOW_SUBCASE( case2c_0_0_2, dst_indices, src_shape, tile_shape, axis );
    TILING_WINDOW_SUBCASE( case2c_0_0_2, dst_indices_a, src_shape_a, tile_shape, axis );
    TILING_WINDOW_SUBCASE( case2c_0_0_2, dst_indices_f, src_shape_f, tile_shape, axis );
    TILING_WINDOW_SUBCASE( case2c_0_0_2, dst_indices_h, src_shape_h, tile_shape, axis );
    TILING_WINDOW_SUBCASE( case2c_0_0_2, dst_indices_v, src_shape_v, tile_shape, axis );
}

TEST_CASE("tiling_window(case2c_0_1_0)" * doctest::test_suite("index::tiling_window"))
{
    TILING_WINDOW_SUBCASE( case2c_0_1_0, dst_indices, src_shape, tile_shape, axis );
    TILING_WINDOW_SUBCASE( case2c_0_1_0, dst_indices_a, src_shape_a, tile_shape, axis );
    TILING_WINDOW_SUBCASE( case2c_0_1_0, dst_indices_f, src_shape_f, tile_shape, axis );
    TILING_WINDOW_SUBCASE( case2c_0_1_0, dst_indices_h, src_shape_h, tile_shape, axis );
    TILING_WINDOW_SUBCASE( case2c_0_1_0, dst_indices_v, src_shape_v, tile_shape, axis );
}

TEST_CASE("tiling_window(case2c_0_1_1)" * doctest::test_suite("index::tiling_window"))
{
    TILING_WINDOW_SUBCASE( case2c_0_1_1, dst_indices, src_shape, tile_shape, axis );
    TILING_WINDOW_SUBCASE( case2c_0_1_1, dst_indices_a, src_shape_a, tile_shape, axis );
    TILING_WINDOW_SUBCASE( case2c_0_1_1, dst_indices_f, src_shape_f, tile_shape, axis );
    TILING_WINDOW_SUBCASE( case2c_0_1_1, dst_indices_h, src_shape_h, tile_shape, axis );
    TILING_WINDOW_SUBCASE( case2c_0_1_1, dst_indices_v, src_shape_v, tile_shape, axis );
}

TEST_CASE("tiling_window(case2c_0_1_2)" * doctest::test_suite("index::tiling_window"))
{
    TILING_WINDOW_SUBCASE( case2c_0_1_2, dst_indices, src_shape, tile_shape, axis );
    TILING_WINDOW_SUBCASE( case2c_0_1_2, dst_indices_a, src_shape_a, tile_shape, axis );
    TILING_WINDOW_SUBCASE( case2c_0_1_2, dst_indices_f, src_shape_f, tile_shape, axis );
    TILING_WINDOW_SUBCASE( case2c_0_1_2, dst_indices_h, src_shape_h, tile_shape, axis );
    TILING_WINDOW_SUBCASE( case2c_0_1_2, dst_indices_v, src_shape_v, tile_shape, axis );
}

TEST_CASE("tiling_window(case2e_0_0_0_0)" * doctest::test_suite("index::tiling_window"))
{
    TILING_WINDOW_SUBCASE( case2e_0_0_0_0, dst_indices, src_shape, tile_shape );
    TILING_WINDOW_SUBCASE( case2e_0_0_0_0, dst_indices_a, src_shape_a, tile_shape );
    TILING_WINDOW_SUBCASE( case2e_0_0_0_0, dst_indices_f, src_shape_f, tile_shape );
    TILING_WINDOW_SUBCASE( case2e_0_0_0_0, dst_indices_h, src_shape_h, tile_shape );
    TILING_WINDOW_SUBCASE( case2e_0_0_0_0, dst_indices_v, src_shape_v, tile_shape );
}

TEST_CASE("tiling_window(case2e_0_0_0_1)" * doctest::test_suite("index::tiling_window"))
{
    TILING_WINDOW_SUBCASE( case2e_0_0_0_1, dst_indices, src_shape, tile_shape );
    TILING_WINDOW_SUBCASE( case2e_0_0_0_1, dst_indices_a, src_shape_a, tile_shape );
    TILING_WINDOW_SUBCASE( case2e_0_0_0_1, dst_indices_f, src_shape_f, tile_shape );
    TILING_WINDOW_SUBCASE( case2e_0_0_0_1, dst_indices_h, src_shape_h, tile_shape );
    TILING_WINDOW_SUBCASE( case2e_0_0_0_1, dst_indices_v, src_shape_v, tile_shape );
}

TEST_CASE("tiling_window(case2e_0_0_1_0)" * doctest::test_suite("index::tiling_window"))
{
    TILING_WINDOW_SUBCASE( case2e_0_0_1_0, dst_indices, src_shape, tile_shape );
    TILING_WINDOW_SUBCASE( case2e_0_0_1_0, dst_indices_a, src_shape_a, tile_shape );
    TILING_WINDOW_SUBCASE( case2e_0_0_1_0, dst_indices_f, src_shape_f, tile_shape );
    TILING_WINDOW_SUBCASE( case2e_0_0_1_0, dst_indices_h, src_shape_h, tile_shape );
    TILING_WINDOW_SUBCASE( case2e_0_0_1_0, dst_indices_v, src_shape_v, tile_shape );
}

TEST_CASE("tiling_window(case2e_0_0_1_1)" * doctest::test_suite("index::tiling_window"))
{
    TILING_WINDOW_SUBCASE( case2e_0_0_1_1, dst_indices, src_shape, tile_shape );
    TILING_WINDOW_SUBCASE( case2e_0_0_1_1, dst_indices_a, src_shape_a, tile_shape );
    TILING_WINDOW_SUBCASE( case2e_0_0_1_1, dst_indices_f, src_shape_f, tile_shape );
    TILING_WINDOW_SUBCASE( case2e_0_0_1_1, dst_indices_h, src_shape_h, tile_shape );
    TILING_WINDOW_SUBCASE( case2e_0_0_1_1, dst_indices_v, src_shape_v, tile_shape );
}

TEST_CASE("tiling_window(case2e_0_1_0_0)" * doctest::test_suite("index::tiling_window"))
{
    TILING_WINDOW_SUBCASE( case2e_0_1_0_0, dst_indices, src_shape, tile_shape );
    TILING_WINDOW_SUBCASE( case2e_0_1_0_0, dst_indices_a, src_shape_a, tile_shape );
    TILING_WINDOW_SUBCASE( case2e_0_1_0_0, dst_indices_f, src_shape_f, tile_shape );
    TILING_WINDOW_SUBCASE( case2e_0_1_0_0, dst_indices_h, src_shape_h, tile_shape );
    TILING_WINDOW_SUBCASE( case2e_0_1_0_0, dst_indices_v, src_shape_v, tile_shape );
}

TEST_CASE("tiling_window(case2e_0_1_0_1)" * doctest::test_suite("index::tiling_window"))
{
    TILING_WINDOW_SUBCASE( case2e_0_1_0_1, dst_indices, src_shape, tile_shape );
    TILING_WINDOW_SUBCASE( case2e_0_1_0_1, dst_indices_a, src_shape_a, tile_shape );
    TILING_WINDOW_SUBCASE( case2e_0_1_0_1, dst_indices_f, src_shape_f, tile_shape );
    TILING_WINDOW_SUBCASE( case2e_0_1_0_1, dst_indices_h, src_shape_h, tile_shape );
    TILING_WINDOW_SUBCASE( case2e_0_1_0_1, dst_indices_v, src_shape_v, tile_shape );
}

TEST_CASE("tiling_window(case2e_0_1_1_0)" * doctest::test_suite("index::tiling_window"))
{
    TILING_WINDOW_SUBCASE( case2e_0_1_1_0, dst_indices, src_shape, tile_shape );
    TILING_WINDOW_SUBCASE( case2e_0_1_1_0, dst_indices_a, src_shape_a, tile_shape );
    TILING_WINDOW_SUBCASE( case2e_0_1_1_0, dst_indices_f, src_shape_f, tile_shape );
    TILING_WINDOW_SUBCASE( case2e_0_1_1_0, dst_indices_h, src_shape_h, tile_shape );
    TILING_WINDOW_SUBCASE( case2e_0_1_1_0, dst_indices_v, src_shape_v, tile_shape );
}

TEST_CASE("tiling_window(case2e_0_1_1_1)" * doctest::test_suite("index::tiling_window"))
{
    TILING_WINDOW_SUBCASE( case2e_0_1_1_1, dst_indices, src_shape, tile_shape );
    TILING_WINDOW_SUBCASE( case2e_0_1_1_1, dst_indices_a, src_shape_a, tile_shape );
    TILING_WINDOW_SUBCASE( case2e_0_1_1_1, dst_indices_f, src_shape_f, tile_shape );
    TILING_WINDOW_SUBCASE( case2e_0_1_1_1, dst_indices_h, src_shape_h, tile_shape );
    TILING_WINDOW_SUBCASE( case2e_0_1_1_1, dst_indices_v, src_shape_v, tile_shape );
}

TEST_CASE("tiling_window(case2e_1_0_0_0)" * doctest::test_suite("index::tiling_window"))
{
    TILING_WINDOW_SUBCASE( case2e_1_0_0_0, dst_indices, src_shape, tile_shape );
    TILING_WINDOW_SUBCASE( case2e_1_0_0_0, dst_indices_a, src_shape_a, tile_shape );
    TILING_WINDOW_SUBCASE( case2e_1_0_0_0, dst_indices_f, src_shape_f, tile_shape );
    TILING_WINDOW_SUBCASE( case2e_1_0_0_0, dst_indices_h, src_shape_h, tile_shape );
    TILING_WINDOW_SUBCASE( case2e_1_0_0_0, dst_indices_v, src_shape_v, tile_shape );
}

TEST_CASE("tiling_window(case2e_1_0_0_1)" * doctest::test_suite("index::tiling_window"))
{
    TILING_WINDOW_SUBCASE( case2e_1_0_0_1, dst_indices, src_shape, tile_shape );
    TILING_WINDOW_SUBCASE( case2e_1_0_0_1, dst_indices_a, src_shape_a, tile_shape );
    TILING_WINDOW_SUBCASE( case2e_1_0_0_1, dst_indices_f, src_shape_f, tile_shape );
    TILING_WINDOW_SUBCASE( case2e_1_0_0_1, dst_indices_h, src_shape_h, tile_shape );
    TILING_WINDOW_SUBCASE( case2e_1_0_0_1, dst_indices_v, src_shape_v, tile_shape );
}

TEST_CASE("tiling_window(case2e_1_0_1_0)" * doctest::test_suite("index::tiling_window"))
{
    TILING_WINDOW_SUBCASE( case2e_1_0_1_0, dst_indices, src_shape, tile_shape );
    TILING_WINDOW_SUBCASE( case2e_1_0_1_0, dst_indices_a, src_shape_a, tile_shape );
    TILING_WINDOW_SUBCASE( case2e_1_0_1_0, dst_indices_f, src_shape_f, tile_shape );
    TILING_WINDOW_SUBCASE( case2e_1_0_1_0, dst_indices_h, src_shape_h, tile_shape );
    TILING_WINDOW_SUBCASE( case2e_1_0_1_0, dst_indices_v, src_shape_v, tile_shape );
}

TEST_CASE("tiling_window(case2e_1_0_1_1)" * doctest::test_suite("index::tiling_window"))
{
    TILING_WINDOW_SUBCASE( case2e_1_0_1_1, dst_indices, src_shape, tile_shape );
    TILING_WINDOW_SUBCASE( case2e_1_0_1_1, dst_indices_a, src_shape_a, tile_shape );
    TILING_WINDOW_SUBCASE( case2e_1_0_1_1, dst_indices_f, src_shape_f, tile_shape );
    TILING_WINDOW_SUBCASE( case2e_1_0_1_1, dst_indices_h, src_shape_h, tile_shape );
    TILING_WINDOW_SUBCASE( case2e_1_0_1_1, dst_indices_v, src_shape_v, tile_shape );
}

TEST_CASE("tiling_window(case2e_1_1_0_0)" * doctest::test_suite("index::tiling_window"))
{
    TILING_WINDOW_SUBCASE( case2e_1_1_0_0, dst_indices, src_shape, tile_shape );
    TILING_WINDOW_SUBCASE( case2e_1_1_0_0, dst_indices_a, src_shape_a, tile_shape );
    TILING_WINDOW_SUBCASE( case2e_1_1_0_0, dst_indices_f, src_shape_f, tile_shape );
    TILING_WINDOW_SUBCASE( case2e_1_1_0_0, dst_indices_h, src_shape_h, tile_shape );
    TILING_WINDOW_SUBCASE( case2e_1_1_0_0, dst_indices_v, src_shape_v, tile_shape );
}

TEST_CASE("tiling_window(case2e_1_1_0_1)" * doctest::test_suite("index::tiling_window"))
{
    TILING_WINDOW_SUBCASE( case2e_1_1_0_1, dst_indices, src_shape, tile_shape );
    TILING_WINDOW_SUBCASE( case2e_1_1_0_1, dst_indices_a, src_shape_a, tile_shape );
    TILING_WINDOW_SUBCASE( case2e_1_1_0_1, dst_indices_f, src_shape_f, tile_shape );
    TILING_WINDOW_SUBCASE( case2e_1_1_0_1, dst_indices_h, src_shape_h, tile_shape );
    TILING_WINDOW_SUBCASE( case2e_1_1_0_1, dst_indices_v, src_shape_v, tile_shape );
}

TEST_CASE("tiling_window(case2e_1_1_1_0)" * doctest::test_suite("index::tiling_window"))
{
    TILING_WINDOW_SUBCASE( case2e_1_1_1_0, dst_indices, src_shape, tile_shape );
    TILING_WINDOW_SUBCASE( case2e_1_1_1_0, dst_indices_a, src_shape_a, tile_shape );
    TILING_WINDOW_SUBCASE( case2e_1_1_1_0, dst_indices_f, src_shape_f, tile_shape );
    TILING_WINDOW_SUBCASE( case2e_1_1_1_0, dst_indices_h, src_shape_h, tile_shape );
    TILING_WINDOW_SUBCASE( case2e_1_1_1_0, dst_indices_v, src_shape_v, tile_shape );
}

TEST_CASE("tiling_window(case2e_1_1_1_1)" * doctest::test_suite("index::tiling_window"))
{
    TILING_WINDOW_SUBCASE( case2e_1_1_1_1, dst_indices, src_shape, tile_shape );
    TILING_WINDOW_SUBCASE( case2e_1_1_1_1, dst_indices_a, src_shape_a, tile_shape );
    TILING_WINDOW_SUBCASE( case2e_1_1_1_1, dst_indices_f, src_shape_f, tile_shape );
    TILING_WINDOW_SUBCASE( case2e_1_1_1_1, dst_indices_h, src_shape_h, tile_shape );
    TILING_WINDOW_SUBCASE( case2e_1_1_1_1, dst_indices_v, src_shape_v, tile_shape );
}