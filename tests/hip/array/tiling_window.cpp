#if defined(NMTOOLS_TESTING_GENERIC_NDARRAY)
#define NMTOOLS_CAST_ARRAYS_EXTRA(name) \
inline auto name##_cs_fb = nmtools::cast(name, nmtools::array::kind::ndarray_cs_fb); \
inline auto name##_cs_hb = nmtools::cast(name, nmtools::array::kind::ndarray_cs_hb); \
inline auto name##_cs_db = nmtools::cast(name, nmtools::array::kind::ndarray_cs_db); \
inline auto name##_fs_fb = nmtools::cast(name, nmtools::array::kind::ndarray_fs_fb); \
inline auto name##_fs_hb = nmtools::cast(name, nmtools::array::kind::ndarray_fs_hb); \
inline auto name##_fs_db = nmtools::cast(name, nmtools::array::kind::ndarray_fs_db); \
inline auto name##_hs_fb = nmtools::cast(name, nmtools::array::kind::ndarray_hs_fb); \
inline auto name##_hs_hb = nmtools::cast(name, nmtools::array::kind::ndarray_hs_hb); \
inline auto name##_hs_db = nmtools::cast(name, nmtools::array::kind::ndarray_hs_db); \
inline auto name##_ds_fb = nmtools::cast(name, nmtools::array::kind::ndarray_ds_fb); \
inline auto name##_ds_hb = nmtools::cast(name, nmtools::array::kind::ndarray_ds_hb); \
inline auto name##_ds_db = nmtools::cast(name, nmtools::array::kind::ndarray_ds_db); \
inline auto name##_ls_fb = nmtools::cast(name, nmtools::array::kind::ndarray_ls_fb); \
inline auto name##_ls_hb = nmtools::cast(name, nmtools::array::kind::ndarray_ls_hb); \
inline auto name##_ls_db = nmtools::cast(name, nmtools::array::kind::ndarray_ls_db);
#endif

#include "nmtools/array/tiling_window.hpp"
#include "nmtools/testing/data/array/tiling_window.hpp"
#include "nmtools/evaluator/hip.hpp"
#include "nmtools/testing/doctest.hpp"

#define TILING_WINDOW_SUBCASE(case_name, ...) \
SUBCASE(#case_name) \
{ \
    NMTOOLS_TESTING_USE_CASE(array, tiling_window, case_name); \
    using namespace args; \
    auto view = nmtools::view::tiling_window(__VA_ARGS__); \
    auto ctx = nmtools::array::hip::default_context(); \
    auto result = ctx->eval(view); \
    NMTOOLS_ASSERT_EQUAL( nmtools::shape(result), nmtools::shape(expect::expected) ); \
    NMTOOLS_ASSERT_CLOSE( result, expect::expected ); \
}

TEST_CASE("tiling_window(case1)" * doctest::test_suite("array::tiling_window"))
{
    #ifndef NMTOOLS_TESTING_GENERIC_NDARRAY
    // TILING_WINDOW_SUBCASE( case1, x, tile_shape );
    // TILING_WINDOW_SUBCASE( case1, x_a, tile_shape );
    TILING_WINDOW_SUBCASE( case1, x_f, tile_shape );
    TILING_WINDOW_SUBCASE( case1, x_h, tile_shape );
    TILING_WINDOW_SUBCASE( case1, x_d, tile_shape );

    // TILING_WINDOW_SUBCASE( case1, x, tile_shape_ct );
    #else
    TILING_WINDOW_SUBCASE( case1, x_cs_fb, tile_shape );
    TILING_WINDOW_SUBCASE( case1, x_cs_hb, tile_shape );
    TILING_WINDOW_SUBCASE( case1, x_cs_db, tile_shape );

    TILING_WINDOW_SUBCASE( case1, x_fs_fb, tile_shape );
    TILING_WINDOW_SUBCASE( case1, x_fs_hb, tile_shape );
    TILING_WINDOW_SUBCASE( case1, x_fs_db, tile_shape );

    TILING_WINDOW_SUBCASE( case1, x_hs_fb, tile_shape );
    TILING_WINDOW_SUBCASE( case1, x_hs_hb, tile_shape );
    TILING_WINDOW_SUBCASE( case1, x_hs_db, tile_shape );

    TILING_WINDOW_SUBCASE( case1, x_ds_fb, tile_shape );
    TILING_WINDOW_SUBCASE( case1, x_ds_hb, tile_shape );
    TILING_WINDOW_SUBCASE( case1, x_ds_db, tile_shape );
    #endif
}

TEST_CASE("tiling_window(case2)" * doctest::test_suite("array::tiling_window"))
{
    #ifndef NMTOOLS_TESTING_GENERIC_NDARRAY
    // TILING_WINDOW_SUBCASE( case2, x, tile_shape );
    // TILING_WINDOW_SUBCASE( case2, x_a, tile_shape_a );
    TILING_WINDOW_SUBCASE( case2, x_f, tile_shape_f );
    TILING_WINDOW_SUBCASE( case2, x_h, tile_shape_h );
    TILING_WINDOW_SUBCASE( case2, x_d, tile_shape_v );

    // TILING_WINDOW_SUBCASE( case2, x, tile_shape_ct );
    #else
    TILING_WINDOW_SUBCASE( case2, x_cs_fb, tile_shape );
    TILING_WINDOW_SUBCASE( case2, x_cs_hb, tile_shape );
    TILING_WINDOW_SUBCASE( case2, x_cs_db, tile_shape );

    TILING_WINDOW_SUBCASE( case2, x_fs_fb, tile_shape );
    TILING_WINDOW_SUBCASE( case2, x_fs_hb, tile_shape );
    TILING_WINDOW_SUBCASE( case2, x_fs_db, tile_shape );

    TILING_WINDOW_SUBCASE( case2, x_hs_fb, tile_shape );
    TILING_WINDOW_SUBCASE( case2, x_hs_hb, tile_shape );
    TILING_WINDOW_SUBCASE( case2, x_hs_db, tile_shape );

    TILING_WINDOW_SUBCASE( case2, x_ds_fb, tile_shape );
    TILING_WINDOW_SUBCASE( case2, x_ds_hb, tile_shape );
    TILING_WINDOW_SUBCASE( case2, x_ds_db, tile_shape );
    #endif
}

TEST_CASE("tiling_window(case2b)" * doctest::test_suite("array::tiling_window"))
{
    #ifndef NMTOOLS_TESTING_GENERIC_NDARRAY
    // TILING_WINDOW_SUBCASE( case2b, x, tile_shape );
    // TILING_WINDOW_SUBCASE( case2b, x_a, tile_shape_a );
    TILING_WINDOW_SUBCASE( case2b, x_f, tile_shape_f );
    TILING_WINDOW_SUBCASE( case2b, x_h, tile_shape_h );
    TILING_WINDOW_SUBCASE( case2b, x_d, tile_shape_v );

    // TILING_WINDOW_SUBCASE( case2b, x, tile_shape_ct );
    #else
    TILING_WINDOW_SUBCASE( case2b, x_cs_fb, tile_shape );
    TILING_WINDOW_SUBCASE( case2b, x_cs_hb, tile_shape );
    TILING_WINDOW_SUBCASE( case2b, x_cs_db, tile_shape );

    TILING_WINDOW_SUBCASE( case2b, x_fs_fb, tile_shape );
    TILING_WINDOW_SUBCASE( case2b, x_fs_hb, tile_shape );
    TILING_WINDOW_SUBCASE( case2b, x_fs_db, tile_shape );

    TILING_WINDOW_SUBCASE( case2b, x_hs_fb, tile_shape );
    TILING_WINDOW_SUBCASE( case2b, x_hs_hb, tile_shape );
    TILING_WINDOW_SUBCASE( case2b, x_hs_db, tile_shape );

    TILING_WINDOW_SUBCASE( case2b, x_ds_fb, tile_shape );
    TILING_WINDOW_SUBCASE( case2b, x_ds_hb, tile_shape );
    TILING_WINDOW_SUBCASE( case2b, x_ds_db, tile_shape );
    #endif
}

#if 1
TEST_CASE("tiling_window(case2c)" * doctest::test_suite("array::tiling_window"))
{
    #ifndef NMTOOLS_TESTING_GENERIC_NDARRAY
    // TILING_WINDOW_SUBCASE( case2c, x, tile_shape, axis );
    // TILING_WINDOW_SUBCASE( case2c, x_a, tile_shape, axis );
    TILING_WINDOW_SUBCASE( case2c, x_f, tile_shape, axis );
    TILING_WINDOW_SUBCASE( case2c, x_h, tile_shape, axis );
    TILING_WINDOW_SUBCASE( case2c, x_d, tile_shape, axis );

    // TILING_WINDOW_SUBCASE( case2c, x, tile_shape_ct, axis_ct );
    #else
    TILING_WINDOW_SUBCASE( case2c, x_cs_fb, tile_shape, axis );
    TILING_WINDOW_SUBCASE( case2c, x_cs_hb, tile_shape, axis );
    TILING_WINDOW_SUBCASE( case2c, x_cs_db, tile_shape, axis );

    TILING_WINDOW_SUBCASE( case2c, x_fs_fb, tile_shape, axis );
    TILING_WINDOW_SUBCASE( case2c, x_fs_hb, tile_shape, axis );
    TILING_WINDOW_SUBCASE( case2c, x_fs_db, tile_shape, axis );

    TILING_WINDOW_SUBCASE( case2c, x_hs_fb, tile_shape, axis );
    TILING_WINDOW_SUBCASE( case2c, x_hs_hb, tile_shape, axis );
    TILING_WINDOW_SUBCASE( case2c, x_hs_db, tile_shape, axis );

    TILING_WINDOW_SUBCASE( case2c, x_ds_fb, tile_shape, axis );
    TILING_WINDOW_SUBCASE( case2c, x_ds_hb, tile_shape, axis );
    TILING_WINDOW_SUBCASE( case2c, x_ds_db, tile_shape, axis );
    #endif
}
#endif

#if 1
TEST_CASE("tiling_window(case2d)" * doctest::test_suite("array::tiling_window"))
{
    #ifndef NMTOOLS_TESTING_GENERIC_NDARRAY
    // TILING_WINDOW_SUBCASE( case2d, x, tile_shape, axis );
    // TILING_WINDOW_SUBCASE( case2d, x_a, tile_shape, axis );
    TILING_WINDOW_SUBCASE( case2d, x_f, tile_shape, axis );
    TILING_WINDOW_SUBCASE( case2d, x_h, tile_shape, axis );
    TILING_WINDOW_SUBCASE( case2d, x_d, tile_shape, axis );

    // TILING_WINDOW_SUBCASE( case2d, x, tile_shape_ct, axis_ct );
    #else
    
    #endif
}
#endif

TEST_CASE("tiling_window(case2e)" * doctest::test_suite("array::tiling_window"))
{
    #ifndef NMTOOLS_TESTING_GENERIC_NDARRAY
    // TILING_WINDOW_SUBCASE( case2e, x, tile_shape );
    // TILING_WINDOW_SUBCASE( case2e, x_a, tile_shape );
    TILING_WINDOW_SUBCASE( case2e, x_f, tile_shape );
    TILING_WINDOW_SUBCASE( case2e, x_h, tile_shape );
    TILING_WINDOW_SUBCASE( case2e, x_d, tile_shape );

    // TILING_WINDOW_SUBCASE( case2e, x, tile_shape_ct );
    #else
    TILING_WINDOW_SUBCASE( case2e, x_cs_fb, tile_shape );
    TILING_WINDOW_SUBCASE( case2e, x_cs_hb, tile_shape );
    TILING_WINDOW_SUBCASE( case2e, x_cs_db, tile_shape );

    TILING_WINDOW_SUBCASE( case2e, x_fs_fb, tile_shape );
    TILING_WINDOW_SUBCASE( case2e, x_fs_hb, tile_shape );
    TILING_WINDOW_SUBCASE( case2e, x_fs_db, tile_shape );

    TILING_WINDOW_SUBCASE( case2e, x_hs_fb, tile_shape );
    TILING_WINDOW_SUBCASE( case2e, x_hs_hb, tile_shape );
    TILING_WINDOW_SUBCASE( case2e, x_hs_db, tile_shape );

    TILING_WINDOW_SUBCASE( case2e, x_ds_fb, tile_shape );
    TILING_WINDOW_SUBCASE( case2e, x_ds_hb, tile_shape );
    TILING_WINDOW_SUBCASE( case2e, x_ds_db, tile_shape );
    #endif
}

TEST_CASE("tiling_window(case3a)" * doctest::test_suite("array::tiling_window"))
{
    #ifndef NMTOOLS_TESTING_GENERIC_NDARRAY
    // TILING_WINDOW_SUBCASE( case3a, x, tile_shape );
    // TILING_WINDOW_SUBCASE( case3a, x_a, tile_shape_a );
    TILING_WINDOW_SUBCASE( case3a, x_f, tile_shape_f );
    TILING_WINDOW_SUBCASE( case3a, x_h, tile_shape_h );
    TILING_WINDOW_SUBCASE( case3a, x_d, tile_shape_v );

    // TILING_WINDOW_SUBCASE( case3a, x, tile_shape_ct );
    #else
    TILING_WINDOW_SUBCASE( case3a, x_cs_fb, tile_shape );
    TILING_WINDOW_SUBCASE( case3a, x_cs_hb, tile_shape );
    TILING_WINDOW_SUBCASE( case3a, x_cs_db, tile_shape );

    TILING_WINDOW_SUBCASE( case3a, x_fs_fb, tile_shape );
    TILING_WINDOW_SUBCASE( case3a, x_fs_hb, tile_shape );
    TILING_WINDOW_SUBCASE( case3a, x_fs_db, tile_shape );

    TILING_WINDOW_SUBCASE( case3a, x_hs_fb, tile_shape );
    TILING_WINDOW_SUBCASE( case3a, x_hs_hb, tile_shape );
    TILING_WINDOW_SUBCASE( case3a, x_hs_db, tile_shape );

    TILING_WINDOW_SUBCASE( case3a, x_ds_fb, tile_shape );
    TILING_WINDOW_SUBCASE( case3a, x_ds_hb, tile_shape );
    TILING_WINDOW_SUBCASE( case3a, x_ds_db, tile_shape );
    #endif
}

TEST_CASE("tiling_window(case3b)" * doctest::test_suite("array::tiling_window"))
{
    #ifndef NMTOOLS_TESTING_GENERIC_NDARRAY
    // TILING_WINDOW_SUBCASE( case3b, x, tile_shape );
    // TILING_WINDOW_SUBCASE( case3b, x_a, tile_shape );
    TILING_WINDOW_SUBCASE( case3b, x_f, tile_shape );
    TILING_WINDOW_SUBCASE( case3b, x_h, tile_shape );
    TILING_WINDOW_SUBCASE( case3b, x_d, tile_shape );

    // TILING_WINDOW_SUBCASE( case3b, x, tile_shape_ct );
    #else
    TILING_WINDOW_SUBCASE( case3b, x_cs_fb, tile_shape );
    TILING_WINDOW_SUBCASE( case3b, x_cs_hb, tile_shape );
    TILING_WINDOW_SUBCASE( case3b, x_cs_db, tile_shape );

    TILING_WINDOW_SUBCASE( case3b, x_fs_fb, tile_shape );
    TILING_WINDOW_SUBCASE( case3b, x_fs_hb, tile_shape );
    TILING_WINDOW_SUBCASE( case3b, x_fs_db, tile_shape );

    TILING_WINDOW_SUBCASE( case3b, x_hs_fb, tile_shape );
    TILING_WINDOW_SUBCASE( case3b, x_hs_hb, tile_shape );
    TILING_WINDOW_SUBCASE( case3b, x_hs_db, tile_shape );

    TILING_WINDOW_SUBCASE( case3b, x_ds_fb, tile_shape );
    TILING_WINDOW_SUBCASE( case3b, x_ds_hb, tile_shape );
    TILING_WINDOW_SUBCASE( case3b, x_ds_db, tile_shape );
    #endif
}

TEST_CASE("tiling_window(case3c)" * doctest::test_suite("array::tiling_window"))
{
    #ifndef NMTOOLS_TESTING_GENERIC_NDARRAY
    // TILING_WINDOW_SUBCASE( case3c, x, tile_shape, axis );
    // TILING_WINDOW_SUBCASE( case3c, x_a, tile_shape, axis );
    TILING_WINDOW_SUBCASE( case3c, x_f, tile_shape, axis );
    TILING_WINDOW_SUBCASE( case3c, x_h, tile_shape, axis );
    TILING_WINDOW_SUBCASE( case3c, x_d, tile_shape, axis );

    // TILING_WINDOW_SUBCASE( case3c, x, tile_shape_ct, axis_ct );
    #else
    TILING_WINDOW_SUBCASE( case3c, x_cs_fb, tile_shape, axis );
    TILING_WINDOW_SUBCASE( case3c, x_cs_hb, tile_shape, axis );
    TILING_WINDOW_SUBCASE( case3c, x_cs_db, tile_shape, axis );

    TILING_WINDOW_SUBCASE( case3c, x_fs_fb, tile_shape, axis );
    TILING_WINDOW_SUBCASE( case3c, x_fs_hb, tile_shape, axis );
    TILING_WINDOW_SUBCASE( case3c, x_fs_db, tile_shape, axis );

    TILING_WINDOW_SUBCASE( case3c, x_hs_fb, tile_shape, axis );
    TILING_WINDOW_SUBCASE( case3c, x_hs_hb, tile_shape, axis );
    TILING_WINDOW_SUBCASE( case3c, x_hs_db, tile_shape, axis );

    TILING_WINDOW_SUBCASE( case3c, x_ds_fb, tile_shape, axis );
    TILING_WINDOW_SUBCASE( case3c, x_ds_hb, tile_shape, axis );
    TILING_WINDOW_SUBCASE( case3c, x_ds_db, tile_shape, axis );
    #endif
}

TEST_CASE("tiling_window(case3d)" * doctest::test_suite("array::tiling_window"))
{
    #ifndef NMTOOLS_TESTING_GENERIC_NDARRAY
    // TILING_WINDOW_SUBCASE( case3d, x, tile_shape, axis );
    // TILING_WINDOW_SUBCASE( case3d, x_a, tile_shape_a, axis_a );
    TILING_WINDOW_SUBCASE( case3d, x_f, tile_shape_f, axis_f );
    TILING_WINDOW_SUBCASE( case3d, x_h, tile_shape_h, axis_h );
    TILING_WINDOW_SUBCASE( case3d, x_d, tile_shape_v, axis_v );

    // TILING_WINDOW_SUBCASE( case3d, x, tile_shape_ct, axis_ct );
    #else
    TILING_WINDOW_SUBCASE( case3d, x_cs_fb, tile_shape, axis );
    TILING_WINDOW_SUBCASE( case3d, x_cs_hb, tile_shape, axis );
    TILING_WINDOW_SUBCASE( case3d, x_cs_db, tile_shape, axis );

    TILING_WINDOW_SUBCASE( case3d, x_fs_fb, tile_shape, axis );
    TILING_WINDOW_SUBCASE( case3d, x_fs_hb, tile_shape, axis );
    TILING_WINDOW_SUBCASE( case3d, x_fs_db, tile_shape, axis );

    TILING_WINDOW_SUBCASE( case3d, x_hs_fb, tile_shape, axis );
    TILING_WINDOW_SUBCASE( case3d, x_hs_hb, tile_shape, axis );
    TILING_WINDOW_SUBCASE( case3d, x_hs_db, tile_shape, axis );

    TILING_WINDOW_SUBCASE( case3d, x_ds_fb, tile_shape, axis );
    TILING_WINDOW_SUBCASE( case3d, x_ds_hb, tile_shape, axis );
    TILING_WINDOW_SUBCASE( case3d, x_ds_db, tile_shape, axis );
    #endif
}
