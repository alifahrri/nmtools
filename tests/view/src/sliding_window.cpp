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

#include "nmtools/array/sliding_window.hpp"
#include "nmtools/testing/data/array/sliding_window.hpp"
#include "nmtools/testing/doctest.hpp"

#define SLIDING_WINDOW_SUBCASE(case_name, ...) \
SUBCASE(#case_name) \
{ \
    NMTOOLS_TESTING_USE_CASE(array, sliding_window, case_name); \
    using namespace args; \
    auto result = nmtools::view::sliding_window(__VA_ARGS__); \
    NMTOOLS_ASSERT_EQUAL( nmtools::shape(result), nmtools::shape(expect::expected) ); \
    NMTOOLS_ASSERT_CLOSE_COLORIZED( result, expect::expected ); \
}

TEST_CASE("sliding_window(case1)" * doctest::test_suite("view::sliding_window"))
{
    SLIDING_WINDOW_SUBCASE( case1, x, window_shape );
    SLIDING_WINDOW_SUBCASE( case1, x_a, window_shape );
    SLIDING_WINDOW_SUBCASE( case1, x_f, window_shape );
    SLIDING_WINDOW_SUBCASE( case1, x_h, window_shape );
    SLIDING_WINDOW_SUBCASE( case1, x_d, window_shape );

    #if defined(NMTOOLS_TESTING_GENERIC_NDARRAY)
    SLIDING_WINDOW_SUBCASE( case1, x_cs_fb, window_shape );
    SLIDING_WINDOW_SUBCASE( case1, x_cs_hb, window_shape );
    SLIDING_WINDOW_SUBCASE( case1, x_cs_db, window_shape );

    SLIDING_WINDOW_SUBCASE( case1, x_fs_fb, window_shape );
    SLIDING_WINDOW_SUBCASE( case1, x_fs_hb, window_shape );
    SLIDING_WINDOW_SUBCASE( case1, x_fs_db, window_shape );

    SLIDING_WINDOW_SUBCASE( case1, x_hs_fb, window_shape );
    SLIDING_WINDOW_SUBCASE( case1, x_hs_hb, window_shape );
    SLIDING_WINDOW_SUBCASE( case1, x_hs_db, window_shape );

    SLIDING_WINDOW_SUBCASE( case1, x_ds_fb, window_shape );
    SLIDING_WINDOW_SUBCASE( case1, x_ds_hb, window_shape );
    SLIDING_WINDOW_SUBCASE( case1, x_ds_db, window_shape );

    SLIDING_WINDOW_SUBCASE( case1, x_ls_fb, window_shape );
    SLIDING_WINDOW_SUBCASE( case1, x_ls_hb, window_shape );
    SLIDING_WINDOW_SUBCASE( case1, x_ls_db, window_shape );
    #endif
}

TEST_CASE("sliding_window(case2)" * doctest::test_suite("view::sliding_window"))
{
    SLIDING_WINDOW_SUBCASE( case2, x, window_shape );
    SLIDING_WINDOW_SUBCASE( case2, x_a, window_shape_a );
    SLIDING_WINDOW_SUBCASE( case2, x_f, window_shape_f );
    SLIDING_WINDOW_SUBCASE( case2, x_h, window_shape_h );
    SLIDING_WINDOW_SUBCASE( case2, x_d, window_shape_v );

    #if defined(NMTOOLS_TESTING_GENERIC_NDARRAY)
    SLIDING_WINDOW_SUBCASE( case2, x_cs_fb, window_shape_a );
    SLIDING_WINDOW_SUBCASE( case2, x_cs_hb, window_shape_a );
    SLIDING_WINDOW_SUBCASE( case2, x_cs_db, window_shape_a );

    SLIDING_WINDOW_SUBCASE( case2, x_fs_fb, window_shape_a );
    SLIDING_WINDOW_SUBCASE( case2, x_fs_hb, window_shape_a );
    SLIDING_WINDOW_SUBCASE( case2, x_fs_db, window_shape_a );

    SLIDING_WINDOW_SUBCASE( case2, x_hs_fb, window_shape_a );
    SLIDING_WINDOW_SUBCASE( case2, x_hs_hb, window_shape_a );
    SLIDING_WINDOW_SUBCASE( case2, x_hs_db, window_shape_a );

    SLIDING_WINDOW_SUBCASE( case2, x_ds_fb, window_shape_a );
    SLIDING_WINDOW_SUBCASE( case2, x_ds_hb, window_shape_a );
    SLIDING_WINDOW_SUBCASE( case2, x_ds_db, window_shape_a );

    SLIDING_WINDOW_SUBCASE( case2, x_ls_fb, window_shape_a );
    SLIDING_WINDOW_SUBCASE( case2, x_ls_hb, window_shape_a );
    SLIDING_WINDOW_SUBCASE( case2, x_ls_db, window_shape_a );

    SLIDING_WINDOW_SUBCASE( case2, x_cs_fb, window_shape_v );
    SLIDING_WINDOW_SUBCASE( case2, x_cs_hb, window_shape_v );
    SLIDING_WINDOW_SUBCASE( case2, x_cs_db, window_shape_v );

    SLIDING_WINDOW_SUBCASE( case2, x_fs_fb, window_shape_v );
    SLIDING_WINDOW_SUBCASE( case2, x_fs_hb, window_shape_v );
    SLIDING_WINDOW_SUBCASE( case2, x_fs_db, window_shape_v );

    SLIDING_WINDOW_SUBCASE( case2, x_hs_fb, window_shape_v );
    SLIDING_WINDOW_SUBCASE( case2, x_hs_hb, window_shape_v );
    SLIDING_WINDOW_SUBCASE( case2, x_hs_db, window_shape_v );

    SLIDING_WINDOW_SUBCASE( case2, x_ds_fb, window_shape_v );
    SLIDING_WINDOW_SUBCASE( case2, x_ds_hb, window_shape_v );
    SLIDING_WINDOW_SUBCASE( case2, x_ds_db, window_shape_v );

    SLIDING_WINDOW_SUBCASE( case2, x_ls_fb, window_shape_v );
    SLIDING_WINDOW_SUBCASE( case2, x_ls_hb, window_shape_v );
    SLIDING_WINDOW_SUBCASE( case2, x_ls_db, window_shape_v );

    SLIDING_WINDOW_SUBCASE( case2, x_cs_fb, window_shape_h );
    SLIDING_WINDOW_SUBCASE( case2, x_cs_hb, window_shape_h );
    SLIDING_WINDOW_SUBCASE( case2, x_cs_db, window_shape_h );

    SLIDING_WINDOW_SUBCASE( case2, x_fs_fb, window_shape_h );
    SLIDING_WINDOW_SUBCASE( case2, x_fs_hb, window_shape_h );
    SLIDING_WINDOW_SUBCASE( case2, x_fs_db, window_shape_h );

    SLIDING_WINDOW_SUBCASE( case2, x_hs_fb, window_shape_h );
    SLIDING_WINDOW_SUBCASE( case2, x_hs_hb, window_shape_h );
    SLIDING_WINDOW_SUBCASE( case2, x_hs_db, window_shape_h );

    SLIDING_WINDOW_SUBCASE( case2, x_ds_fb, window_shape_h );
    SLIDING_WINDOW_SUBCASE( case2, x_ds_hb, window_shape_h );
    SLIDING_WINDOW_SUBCASE( case2, x_ds_db, window_shape_h );

    SLIDING_WINDOW_SUBCASE( case2, x_ls_fb, window_shape_h );
    SLIDING_WINDOW_SUBCASE( case2, x_ls_hb, window_shape_h );
    SLIDING_WINDOW_SUBCASE( case2, x_ls_db, window_shape_h );
    #endif
}

TEST_CASE("sliding_window(case3)" * doctest::test_suite("view::sliding_window"))
{
    SLIDING_WINDOW_SUBCASE( case3, x, window_shape, axis );
    SLIDING_WINDOW_SUBCASE( case3, x_a, window_shape, axis );
    SLIDING_WINDOW_SUBCASE( case3, x_f, window_shape, axis );
    SLIDING_WINDOW_SUBCASE( case3, x_h, window_shape, axis );
    SLIDING_WINDOW_SUBCASE( case3, x_d, window_shape, axis );

    #if defined(NMTOOLS_TESTING_GENERIC_NDARRAY)
    SLIDING_WINDOW_SUBCASE( case3, x_cs_fb, window_shape, axis );
    SLIDING_WINDOW_SUBCASE( case3, x_cs_hb, window_shape, axis );
    SLIDING_WINDOW_SUBCASE( case3, x_cs_db, window_shape, axis );

    SLIDING_WINDOW_SUBCASE( case3, x_fs_fb, window_shape, axis );
    SLIDING_WINDOW_SUBCASE( case3, x_fs_hb, window_shape, axis );
    SLIDING_WINDOW_SUBCASE( case3, x_fs_db, window_shape, axis );

    SLIDING_WINDOW_SUBCASE( case3, x_hs_fb, window_shape, axis );
    SLIDING_WINDOW_SUBCASE( case3, x_hs_hb, window_shape, axis );
    SLIDING_WINDOW_SUBCASE( case3, x_hs_db, window_shape, axis );

    SLIDING_WINDOW_SUBCASE( case3, x_ds_fb, window_shape, axis );
    SLIDING_WINDOW_SUBCASE( case3, x_ds_hb, window_shape, axis );
    SLIDING_WINDOW_SUBCASE( case3, x_ds_db, window_shape, axis );
    #endif
}

TEST_CASE("sliding_window(case4)" * doctest::test_suite("view::sliding_window"))
{
    SLIDING_WINDOW_SUBCASE( case4, x, window_shape, axis );
    SLIDING_WINDOW_SUBCASE( case4, x_a, window_shape_a, axis_a );
    SLIDING_WINDOW_SUBCASE( case4, x_f, window_shape_f, axis_f );
    SLIDING_WINDOW_SUBCASE( case4, x_h, window_shape_h, axis_h );
    SLIDING_WINDOW_SUBCASE( case4, x_d, window_shape_v, axis_v );

    #if defined(NMTOOLS_TESTING_GENERIC_NDARRAY)
    SLIDING_WINDOW_SUBCASE( case4, x_cs_fb, window_shape_a, axis_a );
    SLIDING_WINDOW_SUBCASE( case4, x_cs_hb, window_shape_a, axis_a );
    SLIDING_WINDOW_SUBCASE( case4, x_cs_db, window_shape_a, axis_a );

    SLIDING_WINDOW_SUBCASE( case4, x_fs_fb, window_shape_a, axis_a );
    SLIDING_WINDOW_SUBCASE( case4, x_fs_hb, window_shape_a, axis_a );
    SLIDING_WINDOW_SUBCASE( case4, x_fs_db, window_shape_a, axis_a );

    SLIDING_WINDOW_SUBCASE( case4, x_hs_fb, window_shape_a, axis_a );
    SLIDING_WINDOW_SUBCASE( case4, x_hs_hb, window_shape_a, axis_a );
    SLIDING_WINDOW_SUBCASE( case4, x_hs_db, window_shape_a, axis_a );

    SLIDING_WINDOW_SUBCASE( case4, x_ds_fb, window_shape_a, axis_a );
    SLIDING_WINDOW_SUBCASE( case4, x_ds_hb, window_shape_a, axis_a );
    SLIDING_WINDOW_SUBCASE( case4, x_ds_db, window_shape_a, axis_a );

    SLIDING_WINDOW_SUBCASE( case4, x_ls_fb, window_shape_a, axis_a );
    SLIDING_WINDOW_SUBCASE( case4, x_ls_hb, window_shape_a, axis_a );
    SLIDING_WINDOW_SUBCASE( case4, x_ls_db, window_shape_a, axis_a );

    SLIDING_WINDOW_SUBCASE( case4, x_cs_fb, window_shape_v, axis_v );
    SLIDING_WINDOW_SUBCASE( case4, x_cs_hb, window_shape_v, axis_v );
    SLIDING_WINDOW_SUBCASE( case4, x_cs_db, window_shape_v, axis_v );

    SLIDING_WINDOW_SUBCASE( case4, x_fs_fb, window_shape_v, axis_v );
    SLIDING_WINDOW_SUBCASE( case4, x_fs_hb, window_shape_v, axis_v );
    SLIDING_WINDOW_SUBCASE( case4, x_fs_db, window_shape_v, axis_v );

    SLIDING_WINDOW_SUBCASE( case4, x_hs_fb, window_shape_v, axis_v );
    SLIDING_WINDOW_SUBCASE( case4, x_hs_hb, window_shape_v, axis_v );
    SLIDING_WINDOW_SUBCASE( case4, x_hs_db, window_shape_v, axis_v );

    SLIDING_WINDOW_SUBCASE( case4, x_ds_fb, window_shape_v, axis_v );
    SLIDING_WINDOW_SUBCASE( case4, x_ds_hb, window_shape_v, axis_v );
    SLIDING_WINDOW_SUBCASE( case4, x_ds_db, window_shape_v, axis_v );

    SLIDING_WINDOW_SUBCASE( case4, x_ls_fb, window_shape_v, axis_v );
    SLIDING_WINDOW_SUBCASE( case4, x_ls_hb, window_shape_v, axis_v );
    SLIDING_WINDOW_SUBCASE( case4, x_ls_db, window_shape_v, axis_v );

    SLIDING_WINDOW_SUBCASE( case4, x_cs_fb, window_shape_h, axis_h );
    SLIDING_WINDOW_SUBCASE( case4, x_cs_hb, window_shape_h, axis_h );
    SLIDING_WINDOW_SUBCASE( case4, x_cs_db, window_shape_h, axis_h );

    SLIDING_WINDOW_SUBCASE( case4, x_fs_fb, window_shape_h, axis_h );
    SLIDING_WINDOW_SUBCASE( case4, x_fs_hb, window_shape_h, axis_h );
    SLIDING_WINDOW_SUBCASE( case4, x_fs_db, window_shape_h, axis_h );

    SLIDING_WINDOW_SUBCASE( case4, x_hs_fb, window_shape_h, axis_h );
    SLIDING_WINDOW_SUBCASE( case4, x_hs_hb, window_shape_h, axis_h );
    SLIDING_WINDOW_SUBCASE( case4, x_hs_db, window_shape_h, axis_h );

    SLIDING_WINDOW_SUBCASE( case4, x_ds_fb, window_shape_h, axis_h );
    SLIDING_WINDOW_SUBCASE( case4, x_ds_hb, window_shape_h, axis_h );
    SLIDING_WINDOW_SUBCASE( case4, x_ds_db, window_shape_h, axis_h );

    SLIDING_WINDOW_SUBCASE( case4, x_ls_fb, window_shape_h, axis_h );
    SLIDING_WINDOW_SUBCASE( case4, x_ls_hb, window_shape_h, axis_h );
    SLIDING_WINDOW_SUBCASE( case4, x_ls_db, window_shape_h, axis_h );
    #endif
}

TEST_CASE("sliding_window(case5)" * doctest::test_suite("view::sliding_window"))
{
    SLIDING_WINDOW_SUBCASE( case5, x, window_shape );
    SLIDING_WINDOW_SUBCASE( case5, x_a, window_shape_a );
    SLIDING_WINDOW_SUBCASE( case5, x_f, window_shape_f );
    SLIDING_WINDOW_SUBCASE( case5, x_h, window_shape_h );
    SLIDING_WINDOW_SUBCASE( case5, x_d, window_shape_v );

    #if defined(NMTOOLS_TESTING_GENERIC_NDARRAY)
    SLIDING_WINDOW_SUBCASE( case5, x_cs_fb, window_shape_a );
    SLIDING_WINDOW_SUBCASE( case5, x_cs_hb, window_shape_a );
    SLIDING_WINDOW_SUBCASE( case5, x_cs_db, window_shape_a );

    SLIDING_WINDOW_SUBCASE( case5, x_fs_fb, window_shape_a );
    SLIDING_WINDOW_SUBCASE( case5, x_fs_hb, window_shape_a );
    SLIDING_WINDOW_SUBCASE( case5, x_fs_db, window_shape_a );

    SLIDING_WINDOW_SUBCASE( case5, x_hs_fb, window_shape_a );
    SLIDING_WINDOW_SUBCASE( case5, x_hs_hb, window_shape_a );
    SLIDING_WINDOW_SUBCASE( case5, x_hs_db, window_shape_a );

    SLIDING_WINDOW_SUBCASE( case5, x_ds_fb, window_shape_a );
    SLIDING_WINDOW_SUBCASE( case5, x_ds_hb, window_shape_a );
    SLIDING_WINDOW_SUBCASE( case5, x_ds_db, window_shape_a );

    SLIDING_WINDOW_SUBCASE( case5, x_ls_fb, window_shape_a );
    SLIDING_WINDOW_SUBCASE( case5, x_ls_hb, window_shape_a );
    SLIDING_WINDOW_SUBCASE( case5, x_ls_db, window_shape_a );
    #endif
}

TEST_CASE("sliding_window(case6)" * doctest::test_suite("view::sliding_window"))
{
    SLIDING_WINDOW_SUBCASE( case6, x, window_shape, axis );
    SLIDING_WINDOW_SUBCASE( case6, x_a, window_shape_a, axis_a );
    SLIDING_WINDOW_SUBCASE( case6, x_f, window_shape_f, axis_f );
    SLIDING_WINDOW_SUBCASE( case6, x_h, window_shape_h, axis_h );
    SLIDING_WINDOW_SUBCASE( case6, x_d, window_shape_v, axis_v );

    #if defined(NMTOOLS_TESTING_GENERIC_NDARRAY)
    SLIDING_WINDOW_SUBCASE( case6, x_cs_fb, window_shape, axis );
    SLIDING_WINDOW_SUBCASE( case6, x_cs_hb, window_shape, axis );
    SLIDING_WINDOW_SUBCASE( case6, x_cs_db, window_shape, axis );

    SLIDING_WINDOW_SUBCASE( case6, x_fs_fb, window_shape, axis );
    SLIDING_WINDOW_SUBCASE( case6, x_fs_hb, window_shape, axis );
    SLIDING_WINDOW_SUBCASE( case6, x_fs_db, window_shape, axis );

    SLIDING_WINDOW_SUBCASE( case6, x_hs_fb, window_shape, axis );
    SLIDING_WINDOW_SUBCASE( case6, x_hs_hb, window_shape, axis );
    SLIDING_WINDOW_SUBCASE( case6, x_hs_db, window_shape, axis );

    SLIDING_WINDOW_SUBCASE( case6, x_ds_fb, window_shape, axis );
    SLIDING_WINDOW_SUBCASE( case6, x_ds_hb, window_shape, axis );
    SLIDING_WINDOW_SUBCASE( case6, x_ds_db, window_shape, axis );
    #endif
}

TEST_CASE("sliding_window(case7)" * doctest::test_suite("view::sliding_window"))
{
    SLIDING_WINDOW_SUBCASE( case7, x, window_shape, axis );
    SLIDING_WINDOW_SUBCASE( case7, x_a, window_shape_a, axis_a );
    SLIDING_WINDOW_SUBCASE( case7, x_f, window_shape_f, axis_f );
    SLIDING_WINDOW_SUBCASE( case7, x_h, window_shape_h, axis_h );
    SLIDING_WINDOW_SUBCASE( case7, x_d, window_shape_v, axis_v );

    #if defined(NMTOOLS_TESTING_GENERIC_NDARRAY)
    SLIDING_WINDOW_SUBCASE( case7, x_cs_fb, window_shape, axis );
    SLIDING_WINDOW_SUBCASE( case7, x_cs_hb, window_shape, axis );
    SLIDING_WINDOW_SUBCASE( case7, x_cs_db, window_shape, axis );

    SLIDING_WINDOW_SUBCASE( case7, x_fs_fb, window_shape, axis );
    SLIDING_WINDOW_SUBCASE( case7, x_fs_hb, window_shape, axis );
    SLIDING_WINDOW_SUBCASE( case7, x_fs_db, window_shape, axis );

    SLIDING_WINDOW_SUBCASE( case7, x_hs_fb, window_shape, axis );
    SLIDING_WINDOW_SUBCASE( case7, x_hs_hb, window_shape, axis );
    SLIDING_WINDOW_SUBCASE( case7, x_hs_db, window_shape, axis );

    SLIDING_WINDOW_SUBCASE( case7, x_ds_fb, window_shape, axis );
    SLIDING_WINDOW_SUBCASE( case7, x_ds_hb, window_shape, axis );
    SLIDING_WINDOW_SUBCASE( case7, x_ds_db, window_shape, axis );

    SLIDING_WINDOW_SUBCASE( case7, x_ls_fb, window_shape, axis );
    SLIDING_WINDOW_SUBCASE( case7, x_ls_hb, window_shape, axis );
    SLIDING_WINDOW_SUBCASE( case7, x_ls_db, window_shape, axis );
    #endif
}

TEST_CASE("sliding_window(case8)" * doctest::test_suite("view::sliding_window"))
{
    SLIDING_WINDOW_SUBCASE( case8, x, window_shape, axis );
    SLIDING_WINDOW_SUBCASE( case8, x_a, window_shape_a, axis_a );
    SLIDING_WINDOW_SUBCASE( case8, x_f, window_shape_f, axis_f );
    SLIDING_WINDOW_SUBCASE( case8, x_h, window_shape_h, axis_h );
    SLIDING_WINDOW_SUBCASE( case8, x_d, window_shape_v, axis_v );

    #if defined(NMTOOLS_TESTING_GENERIC_NDARRAY)
    SLIDING_WINDOW_SUBCASE( case8, x_cs_fb, window_shape_a, axis_f );
    SLIDING_WINDOW_SUBCASE( case8, x_cs_hb, window_shape_f, axis_h );
    SLIDING_WINDOW_SUBCASE( case8, x_cs_db, window_shape_h, axis_v );

    SLIDING_WINDOW_SUBCASE( case8, x_fs_fb, window_shape_a, axis_f );
    SLIDING_WINDOW_SUBCASE( case8, x_fs_hb, window_shape_f, axis_h );
    SLIDING_WINDOW_SUBCASE( case8, x_fs_db, window_shape_h, axis_v );

    SLIDING_WINDOW_SUBCASE( case8, x_hs_fb, window_shape_a, axis_f );
    SLIDING_WINDOW_SUBCASE( case8, x_hs_hb, window_shape_f, axis_h );
    SLIDING_WINDOW_SUBCASE( case8, x_hs_db, window_shape_h, axis_v );

    SLIDING_WINDOW_SUBCASE( case8, x_ds_fb, window_shape_a, axis_f );
    SLIDING_WINDOW_SUBCASE( case8, x_ds_hb, window_shape_f, axis_h );
    SLIDING_WINDOW_SUBCASE( case8, x_ds_db, window_shape_h, axis_v );

    SLIDING_WINDOW_SUBCASE( case8, x_ls_fb, window_shape_a, axis_f );
    SLIDING_WINDOW_SUBCASE( case8, x_ls_hb, window_shape_f, axis_h );
    SLIDING_WINDOW_SUBCASE( case8, x_ls_db, window_shape_h, axis_v );
    #endif
}

TEST_CASE("sliding_window(case9)" * doctest::test_suite("view::sliding_window"))
{
    SLIDING_WINDOW_SUBCASE( case9, x, window_shape );
    SLIDING_WINDOW_SUBCASE( case9, x_a, window_shape_a );
    SLIDING_WINDOW_SUBCASE( case9, x_f, window_shape_f );
    SLIDING_WINDOW_SUBCASE( case9, x_h, window_shape_h );
    SLIDING_WINDOW_SUBCASE( case9, x_d, window_shape_v );

    #if defined(NMTOOLS_TESTING_GENERIC_NDARRAY)
    SLIDING_WINDOW_SUBCASE( case9, x_cs_fb, window_shape_f );
    SLIDING_WINDOW_SUBCASE( case9, x_cs_hb, window_shape_h );
    SLIDING_WINDOW_SUBCASE( case9, x_cs_db, window_shape_v );

    SLIDING_WINDOW_SUBCASE( case9, x_fs_fb, window_shape_f );
    SLIDING_WINDOW_SUBCASE( case9, x_fs_hb, window_shape_h );
    SLIDING_WINDOW_SUBCASE( case9, x_fs_db, window_shape_v );

    SLIDING_WINDOW_SUBCASE( case9, x_hs_fb, window_shape_f );
    SLIDING_WINDOW_SUBCASE( case9, x_hs_hb, window_shape_h );
    SLIDING_WINDOW_SUBCASE( case9, x_hs_db, window_shape_v );

    SLIDING_WINDOW_SUBCASE( case9, x_ds_fb, window_shape_f );
    SLIDING_WINDOW_SUBCASE( case9, x_ds_hb, window_shape_h );
    SLIDING_WINDOW_SUBCASE( case9, x_ds_db, window_shape_v );

    SLIDING_WINDOW_SUBCASE( case9, x_ls_fb, window_shape_f );
    SLIDING_WINDOW_SUBCASE( case9, x_ls_hb, window_shape_h );
    SLIDING_WINDOW_SUBCASE( case9, x_ls_db, window_shape_v );
    #endif
}

TEST_CASE("sliding_window(case10)" * doctest::test_suite("view::sliding_window"))
{
    SLIDING_WINDOW_SUBCASE( case10, x, window_shape, axis );
    SLIDING_WINDOW_SUBCASE( case10, x_a, window_shape_a, axis_a );
    SLIDING_WINDOW_SUBCASE( case10, x_f, window_shape_f, axis_f );
    SLIDING_WINDOW_SUBCASE( case10, x_h, window_shape_h, axis_h );
    SLIDING_WINDOW_SUBCASE( case10, x_d, window_shape_v, axis_v );

    #if defined(NMTOOLS_TESTING_GENERIC_NDARRAY)
    SLIDING_WINDOW_SUBCASE( case10, x_cs_fb, window_shape_f, axis_a );
    SLIDING_WINDOW_SUBCASE( case10, x_cs_hb, window_shape_h, axis_f );
    SLIDING_WINDOW_SUBCASE( case10, x_cs_db, window_shape_v, axis_h );

    SLIDING_WINDOW_SUBCASE( case10, x_fs_fb, window_shape_f, axis_a );
    SLIDING_WINDOW_SUBCASE( case10, x_fs_hb, window_shape_h, axis_f );
    SLIDING_WINDOW_SUBCASE( case10, x_fs_db, window_shape_v, axis_h );

    SLIDING_WINDOW_SUBCASE( case10, x_hs_fb, window_shape_f, axis_a );
    SLIDING_WINDOW_SUBCASE( case10, x_hs_hb, window_shape_h, axis_f );
    SLIDING_WINDOW_SUBCASE( case10, x_hs_db, window_shape_v, axis_h );

    SLIDING_WINDOW_SUBCASE( case10, x_ds_fb, window_shape_f, axis_a );
    SLIDING_WINDOW_SUBCASE( case10, x_ds_hb, window_shape_h, axis_f );
    SLIDING_WINDOW_SUBCASE( case10, x_ds_db, window_shape_v, axis_h );

    SLIDING_WINDOW_SUBCASE( case10, x_ls_fb, window_shape_f, axis_a );
    SLIDING_WINDOW_SUBCASE( case10, x_ls_hb, window_shape_h, axis_f );
    SLIDING_WINDOW_SUBCASE( case10, x_ls_db, window_shape_v, axis_h );
    #endif
}

TEST_CASE("sliding_window(case11)" * doctest::test_suite("view::sliding_window"))
{
    SLIDING_WINDOW_SUBCASE( case11, x, window_shape, axis );
    SLIDING_WINDOW_SUBCASE( case11, x_a, window_shape, axis );
    SLIDING_WINDOW_SUBCASE( case11, x_f, window_shape, axis );
    SLIDING_WINDOW_SUBCASE( case11, x_h, window_shape, axis );
    SLIDING_WINDOW_SUBCASE( case11, x_d, window_shape, axis );

    SLIDING_WINDOW_SUBCASE( case11, x, window_shape_ct, axis_ct );
    SLIDING_WINDOW_SUBCASE( case11, x_a, window_shape_ct, axis_ct );
    SLIDING_WINDOW_SUBCASE( case11, x_f, window_shape_ct, axis_ct );

    #if defined(NMTOOLS_TESTING_GENERIC_NDARRAY)
    SLIDING_WINDOW_SUBCASE( case11, x_cs_fb, window_shape, axis );
    SLIDING_WINDOW_SUBCASE( case11, x_cs_hb, window_shape, axis );
    SLIDING_WINDOW_SUBCASE( case11, x_cs_db, window_shape, axis );

    SLIDING_WINDOW_SUBCASE( case11, x_fs_fb, window_shape, axis );
    SLIDING_WINDOW_SUBCASE( case11, x_fs_hb, window_shape, axis );
    SLIDING_WINDOW_SUBCASE( case11, x_fs_db, window_shape, axis );

    SLIDING_WINDOW_SUBCASE( case11, x_hs_fb, window_shape, axis );
    SLIDING_WINDOW_SUBCASE( case11, x_hs_hb, window_shape, axis );
    SLIDING_WINDOW_SUBCASE( case11, x_hs_db, window_shape, axis );

    SLIDING_WINDOW_SUBCASE( case11, x_ds_fb, window_shape, axis );
    SLIDING_WINDOW_SUBCASE( case11, x_ds_hb, window_shape, axis );
    SLIDING_WINDOW_SUBCASE( case11, x_ds_db, window_shape, axis );

    SLIDING_WINDOW_SUBCASE( case11, x_ls_fb, window_shape, axis );
    SLIDING_WINDOW_SUBCASE( case11, x_ls_hb, window_shape, axis );
    SLIDING_WINDOW_SUBCASE( case11, x_ls_db, window_shape, axis );
    #endif
}

TEST_CASE("sliding_window(case12)" * doctest::test_suite("view::sliding_window"))
{
    SLIDING_WINDOW_SUBCASE( case12, x, window_shape, axis );
    SLIDING_WINDOW_SUBCASE( case12, x_a, window_shape, axis );
    SLIDING_WINDOW_SUBCASE( case12, x_f, window_shape, axis );
    SLIDING_WINDOW_SUBCASE( case12, x_h, window_shape, axis );
    SLIDING_WINDOW_SUBCASE( case12, x_d, window_shape, axis );

    SLIDING_WINDOW_SUBCASE( case12, x, window_shape_ct, axis_ct );
    SLIDING_WINDOW_SUBCASE( case12, x_a, window_shape_ct, axis_ct );
    SLIDING_WINDOW_SUBCASE( case12, x_f, window_shape_ct, axis_ct );

    #if defined(NMTOOLS_TESTING_GENERIC_NDARRAY)
    SLIDING_WINDOW_SUBCASE( case12, x_cs_fb, window_shape, axis );
    SLIDING_WINDOW_SUBCASE( case12, x_cs_hb, window_shape, axis );
    SLIDING_WINDOW_SUBCASE( case12, x_cs_db, window_shape, axis );

    SLIDING_WINDOW_SUBCASE( case12, x_fs_fb, window_shape, axis );
    SLIDING_WINDOW_SUBCASE( case12, x_fs_hb, window_shape, axis );
    SLIDING_WINDOW_SUBCASE( case12, x_fs_db, window_shape, axis );

    SLIDING_WINDOW_SUBCASE( case12, x_hs_fb, window_shape, axis );
    SLIDING_WINDOW_SUBCASE( case12, x_hs_hb, window_shape, axis );
    SLIDING_WINDOW_SUBCASE( case12, x_hs_db, window_shape, axis );

    SLIDING_WINDOW_SUBCASE( case12, x_ds_fb, window_shape, axis );
    SLIDING_WINDOW_SUBCASE( case12, x_ds_hb, window_shape, axis );
    SLIDING_WINDOW_SUBCASE( case12, x_ds_db, window_shape, axis );

    SLIDING_WINDOW_SUBCASE( case12, x_ls_fb, window_shape, axis );
    SLIDING_WINDOW_SUBCASE( case12, x_ls_hb, window_shape, axis );
    SLIDING_WINDOW_SUBCASE( case12, x_ls_db, window_shape, axis );
    #endif
}

TEST_CASE("sliding_window(case13)" * doctest::test_suite("view::sliding_window"))
{
    SLIDING_WINDOW_SUBCASE( case13, x, window_shape, axis );
    SLIDING_WINDOW_SUBCASE( case13, x_a, window_shape, axis );
    SLIDING_WINDOW_SUBCASE( case13, x_f, window_shape, axis );
    SLIDING_WINDOW_SUBCASE( case13, x_h, window_shape, axis );
    SLIDING_WINDOW_SUBCASE( case13, x_d, window_shape, axis );

    SLIDING_WINDOW_SUBCASE( case13, x, window_shape_ct, axis_ct );
    SLIDING_WINDOW_SUBCASE( case13, x_a, window_shape_ct, axis_ct );
    SLIDING_WINDOW_SUBCASE( case13, x_f, window_shape_ct, axis_ct );

    #if defined(NMTOOLS_TESTING_GENERIC_NDARRAY)
    SLIDING_WINDOW_SUBCASE( case13, x_cs_fb, window_shape, axis );
    SLIDING_WINDOW_SUBCASE( case13, x_cs_hb, window_shape, axis );
    SLIDING_WINDOW_SUBCASE( case13, x_cs_db, window_shape, axis );

    SLIDING_WINDOW_SUBCASE( case13, x_fs_fb, window_shape, axis );
    SLIDING_WINDOW_SUBCASE( case13, x_fs_hb, window_shape, axis );
    SLIDING_WINDOW_SUBCASE( case13, x_fs_db, window_shape, axis );

    SLIDING_WINDOW_SUBCASE( case13, x_hs_fb, window_shape, axis );
    SLIDING_WINDOW_SUBCASE( case13, x_hs_hb, window_shape, axis );
    SLIDING_WINDOW_SUBCASE( case13, x_hs_db, window_shape, axis );

    SLIDING_WINDOW_SUBCASE( case13, x_ds_fb, window_shape, axis );
    SLIDING_WINDOW_SUBCASE( case13, x_ds_hb, window_shape, axis );
    SLIDING_WINDOW_SUBCASE( case13, x_ds_db, window_shape, axis );

    SLIDING_WINDOW_SUBCASE( case13, x_ls_fb, window_shape, axis );
    SLIDING_WINDOW_SUBCASE( case13, x_ls_hb, window_shape, axis );
    SLIDING_WINDOW_SUBCASE( case13, x_ls_db, window_shape, axis );
    #endif
}

TEST_CASE("sliding_window(case14)" * doctest::test_suite("view::sliding_window"))
{
    SLIDING_WINDOW_SUBCASE( case14, x, window_shape, axis, stride );
    SLIDING_WINDOW_SUBCASE( case14, x_a, window_shape, axis, stride );
    SLIDING_WINDOW_SUBCASE( case14, x_f, window_shape, axis, stride );
    SLIDING_WINDOW_SUBCASE( case14, x_h, window_shape, axis, stride );
    SLIDING_WINDOW_SUBCASE( case14, x_d, window_shape, axis, stride );

    #if defined(NMTOOLS_TESTING_GENERIC_NDARRAY)
    #endif
}

TEST_CASE("sliding_window(case15)" * doctest::test_suite("view::sliding_window"))
{
    SLIDING_WINDOW_SUBCASE( case15, x, window_shape, axis, stride );
    SLIDING_WINDOW_SUBCASE( case15, x_a, window_shape, axis, stride );
    SLIDING_WINDOW_SUBCASE( case15, x_f, window_shape, axis, stride );
    SLIDING_WINDOW_SUBCASE( case15, x_h, window_shape, axis, stride );
    SLIDING_WINDOW_SUBCASE( case15, x_d, window_shape, axis, stride );

    #if defined(NMTOOLS_TESTING_GENERIC_NDARRAY)
    #endif
}

TEST_CASE("sliding_window(case15b)" * doctest::test_suite("view::sliding_window"))
{
    SLIDING_WINDOW_SUBCASE( case15b, x, window_shape, axis, stride );
    SLIDING_WINDOW_SUBCASE( case15b, x_a, window_shape, axis, stride );
    SLIDING_WINDOW_SUBCASE( case15b, x_f, window_shape, axis, stride );
    SLIDING_WINDOW_SUBCASE( case15b, x_h, window_shape, axis, stride );
    SLIDING_WINDOW_SUBCASE( case15b, x_d, window_shape, axis, stride );

    #if defined(NMTOOLS_TESTING_GENERIC_NDARRAY)
    #endif
}

TEST_CASE("sliding_window(case16)" * doctest::test_suite("view::sliding_window"))
{
    SLIDING_WINDOW_SUBCASE( case16, x, window_shape, axis, stride );
    SLIDING_WINDOW_SUBCASE( case16, x_a, window_shape, axis, stride );
    SLIDING_WINDOW_SUBCASE( case16, x_f, window_shape, axis, stride );
    SLIDING_WINDOW_SUBCASE( case16, x_h, window_shape, axis, stride );
    SLIDING_WINDOW_SUBCASE( case16, x_d, window_shape, axis, stride );

    #if defined(NMTOOLS_TESTING_GENERIC_NDARRAY)
    #endif
}

#if 1
TEST_CASE("sliding_window(case17)" * doctest::test_suite("view::sliding_window"))
{
    SLIDING_WINDOW_SUBCASE( case17, x, window_shape, axis, stride );
    SLIDING_WINDOW_SUBCASE( case17, x_a, window_shape, axis, stride );
    SLIDING_WINDOW_SUBCASE( case17, x_f, window_shape, axis, stride );
    SLIDING_WINDOW_SUBCASE( case17, x_h, window_shape, axis, stride );
    SLIDING_WINDOW_SUBCASE( case17, x_d, window_shape, axis, stride );

    #if defined(NMTOOLS_TESTING_GENERIC_NDARRAY)
    #endif
}
#endif

TEST_CASE("sliding_window(case18)" * doctest::test_suite("view::sliding_window"))
{
    SLIDING_WINDOW_SUBCASE( case18, x, window_shape, axis, stride );
    SLIDING_WINDOW_SUBCASE( case18, x_a, window_shape, axis, stride );
    SLIDING_WINDOW_SUBCASE( case18, x_f, window_shape, axis, stride );
    SLIDING_WINDOW_SUBCASE( case18, x_h, window_shape, axis, stride );
    SLIDING_WINDOW_SUBCASE( case18, x_d, window_shape, axis, stride );

    #if defined(NMTOOLS_TESTING_GENERIC_NDARRAY)
    #endif
}

TEST_CASE("sliding_window(case19)" * doctest::test_suite("view::sliding_window"))
{
    SLIDING_WINDOW_SUBCASE( case19, x, window_shape, axis, stride );
    SLIDING_WINDOW_SUBCASE( case19, x_a, window_shape, axis, stride );
    SLIDING_WINDOW_SUBCASE( case19, x_f, window_shape, axis, stride );
    SLIDING_WINDOW_SUBCASE( case19, x_h, window_shape, axis, stride );
    SLIDING_WINDOW_SUBCASE( case19, x_d, window_shape, axis, stride );

    #if defined(NMTOOLS_TESTING_GENERIC_NDARRAY)
    #endif
}

TEST_CASE("sliding_window(case19b)" * doctest::test_suite("view::sliding_window"))
{
    SLIDING_WINDOW_SUBCASE( case19b, x, window_shape, axis, stride );
    SLIDING_WINDOW_SUBCASE( case19b, x_a, window_shape, axis, stride );
    SLIDING_WINDOW_SUBCASE( case19b, x_f, window_shape, axis, stride );
    SLIDING_WINDOW_SUBCASE( case19b, x_h, window_shape, axis, stride );
    SLIDING_WINDOW_SUBCASE( case19b, x_d, window_shape, axis, stride );

    #if defined(NMTOOLS_TESTING_GENERIC_NDARRAY)
    #endif
}

TEST_CASE("sliding_window(case20)" * doctest::test_suite("view::sliding_window"))
{
    SLIDING_WINDOW_SUBCASE( case20, x, window_shape, axis, stride );
    SLIDING_WINDOW_SUBCASE( case20, x_a, window_shape, axis, stride );
    SLIDING_WINDOW_SUBCASE( case20, x_f, window_shape, axis, stride );
    SLIDING_WINDOW_SUBCASE( case20, x_h, window_shape, axis, stride );
    SLIDING_WINDOW_SUBCASE( case20, x_d, window_shape, axis, stride );

    #if defined(NMTOOLS_TESTING_GENERIC_NDARRAY)
    #endif
}

TEST_CASE("sliding_window(case21)" * doctest::test_suite("view::sliding_window"))
{
    SLIDING_WINDOW_SUBCASE( case21, x, window_shape, axis, stride );
    SLIDING_WINDOW_SUBCASE( case21, x_a, window_shape, axis, stride );
    SLIDING_WINDOW_SUBCASE( case21, x_f, window_shape, axis, stride );
    SLIDING_WINDOW_SUBCASE( case21, x_h, window_shape, axis, stride );
    SLIDING_WINDOW_SUBCASE( case21, x_d, window_shape, axis, stride );

    #if defined(NMTOOLS_TESTING_GENERIC_NDARRAY)
    #endif
}

TEST_CASE("sliding_window(case22)" * doctest::test_suite("view::sliding_window"))
{
    SLIDING_WINDOW_SUBCASE( case22, x, window_shape, axis, stride );
    SLIDING_WINDOW_SUBCASE( case22, x_a, window_shape, axis, stride );
    SLIDING_WINDOW_SUBCASE( case22, x_f, window_shape, axis, stride );
    SLIDING_WINDOW_SUBCASE( case22, x_h, window_shape, axis, stride );
    SLIDING_WINDOW_SUBCASE( case22, x_d, window_shape, axis, stride );

    #if defined(NMTOOLS_TESTING_GENERIC_NDARRAY)
    #endif
}

TEST_CASE("sliding_window(case23)" * doctest::test_suite("view::sliding_window"))
{
    SLIDING_WINDOW_SUBCASE( case23, x, window_shape, axis, stride );
    SLIDING_WINDOW_SUBCASE( case23, x_a, window_shape, axis, stride );
    SLIDING_WINDOW_SUBCASE( case23, x_f, window_shape, axis, stride );
    SLIDING_WINDOW_SUBCASE( case23, x_h, window_shape, axis, stride );
    SLIDING_WINDOW_SUBCASE( case23, x_d, window_shape, axis, stride );

    #if defined(NMTOOLS_TESTING_GENERIC_NDARRAY)
    #endif
}

TEST_CASE("sliding_window(case24)" * doctest::test_suite("view::sliding_window"))
{
    SLIDING_WINDOW_SUBCASE( case24, x, window_shape, axis, stride );
    SLIDING_WINDOW_SUBCASE( case24, x_a, window_shape, axis, stride );
    SLIDING_WINDOW_SUBCASE( case24, x_f, window_shape, axis, stride );
    SLIDING_WINDOW_SUBCASE( case24, x_h, window_shape, axis, stride );
    SLIDING_WINDOW_SUBCASE( case24, x_d, window_shape, axis, stride );

    #if defined(NMTOOLS_TESTING_GENERIC_NDARRAY)
    #endif
}

TEST_CASE("sliding_window(case25)" * doctest::test_suite("view::sliding_window"))
{
    SLIDING_WINDOW_SUBCASE( case25, x, window_shape, axis, stride );
    SLIDING_WINDOW_SUBCASE( case25, x_a, window_shape, axis, stride );
    SLIDING_WINDOW_SUBCASE( case25, x_f, window_shape, axis, stride );
    SLIDING_WINDOW_SUBCASE( case25, x_h, window_shape, axis, stride );
    SLIDING_WINDOW_SUBCASE( case25, x_d, window_shape, axis, stride );

    #if defined(NMTOOLS_TESTING_GENERIC_NDARRAY)
    #endif
}

TEST_CASE("sliding_window(case26)" * doctest::test_suite("view::sliding_window"))
{
    SLIDING_WINDOW_SUBCASE( case26, x, window_shape, axis, stride );
    SLIDING_WINDOW_SUBCASE( case26, x_a, window_shape, axis, stride );
    SLIDING_WINDOW_SUBCASE( case26, x_f, window_shape, axis, stride );
    SLIDING_WINDOW_SUBCASE( case26, x_h, window_shape, axis, stride );
    SLIDING_WINDOW_SUBCASE( case26, x_d, window_shape, axis, stride );

    #if defined(NMTOOLS_TESTING_GENERIC_NDARRAY)
    #endif
}

TEST_CASE("sliding_window(case27)" * doctest::test_suite("view::sliding_window"))
{
    SLIDING_WINDOW_SUBCASE( case27, x, window_shape, axis, stride );
    SLIDING_WINDOW_SUBCASE( case27, x_a, window_shape, axis, stride );
    SLIDING_WINDOW_SUBCASE( case27, x_f, window_shape, axis, stride );
    SLIDING_WINDOW_SUBCASE( case27, x_h, window_shape, axis, stride );
    SLIDING_WINDOW_SUBCASE( case27, x_d, window_shape, axis, stride );

    #if defined(NMTOOLS_TESTING_GENERIC_NDARRAY)
    #endif
}

TEST_CASE("sliding_window(case28)" * doctest::test_suite("view::sliding_window"))
{
    SLIDING_WINDOW_SUBCASE( case28, x, window_shape, axis, stride );
    SLIDING_WINDOW_SUBCASE( case28, x_a, window_shape, axis, stride );
    SLIDING_WINDOW_SUBCASE( case28, x_f, window_shape, axis, stride );
    SLIDING_WINDOW_SUBCASE( case28, x_h, window_shape, axis, stride );
    SLIDING_WINDOW_SUBCASE( case28, x_d, window_shape, axis, stride );

    #if defined(NMTOOLS_TESTING_GENERIC_NDARRAY)
    #endif
}

TEST_CASE("sliding_window(case29)" * doctest::test_suite("view::sliding_window"))
{
    SLIDING_WINDOW_SUBCASE( case29, x, window_shape, axis, stride );
    SLIDING_WINDOW_SUBCASE( case29, x_a, window_shape, axis, stride );
    SLIDING_WINDOW_SUBCASE( case29, x_f, window_shape, axis, stride );
    SLIDING_WINDOW_SUBCASE( case29, x_h, window_shape, axis, stride );
    SLIDING_WINDOW_SUBCASE( case29, x_d, window_shape, axis, stride );

    #if defined(NMTOOLS_TESTING_GENERIC_NDARRAY)
    #endif
}

TEST_CASE("sliding_window(case30)" * doctest::test_suite("view::sliding_window"))
{
    SLIDING_WINDOW_SUBCASE( case30, x, window_shape, axis, stride );
    SLIDING_WINDOW_SUBCASE( case30, x_a, window_shape, axis, stride );
    SLIDING_WINDOW_SUBCASE( case30, x_f, window_shape, axis, stride );
    SLIDING_WINDOW_SUBCASE( case30, x_h, window_shape, axis, stride );
    SLIDING_WINDOW_SUBCASE( case30, x_d, window_shape, axis, stride );

    #if defined(NMTOOLS_TESTING_GENERIC_NDARRAY)
    #endif
}

TEST_CASE("sliding_window(case31)" * doctest::test_suite("view::sliding_window"))
{
    SLIDING_WINDOW_SUBCASE( case31, x, window_shape, axis, stride );
    SLIDING_WINDOW_SUBCASE( case31, x_a, window_shape, axis, stride );
    SLIDING_WINDOW_SUBCASE( case31, x_f, window_shape, axis, stride );
    SLIDING_WINDOW_SUBCASE( case31, x_h, window_shape, axis, stride );
    SLIDING_WINDOW_SUBCASE( case31, x_d, window_shape, axis, stride );

    #if defined(NMTOOLS_TESTING_GENERIC_NDARRAY)
    #endif
}

TEST_CASE("sliding_window(case32)" * doctest::test_suite("view::sliding_window"))
{
    SLIDING_WINDOW_SUBCASE( case32, x, window_shape, axis, stride );
    SLIDING_WINDOW_SUBCASE( case32, x_a, window_shape, axis, stride );
    SLIDING_WINDOW_SUBCASE( case32, x_f, window_shape, axis, stride );
    SLIDING_WINDOW_SUBCASE( case32, x_h, window_shape, axis, stride );
    SLIDING_WINDOW_SUBCASE( case32, x_d, window_shape, axis, stride );

    #if defined(NMTOOLS_TESTING_GENERIC_NDARRAY)
    #endif
}

TEST_CASE("sliding_window(case33)" * doctest::test_suite("view::sliding_window"))
{
    SLIDING_WINDOW_SUBCASE( case33, x, window_shape, axis, stride );
    SLIDING_WINDOW_SUBCASE( case33, x_a, window_shape, axis, stride );
    SLIDING_WINDOW_SUBCASE( case33, x_f, window_shape, axis, stride );
    SLIDING_WINDOW_SUBCASE( case33, x_h, window_shape, axis, stride );
    SLIDING_WINDOW_SUBCASE( case33, x_d, window_shape, axis, stride );

    #if defined(NMTOOLS_TESTING_GENERIC_NDARRAY)
    #endif
}

TEST_CASE("sliding_window(case34)" * doctest::test_suite("view::sliding_window"))
{
    SLIDING_WINDOW_SUBCASE( case34, x, window_shape, axis, stride );
    SLIDING_WINDOW_SUBCASE( case34, x_a, window_shape, axis, stride );
    SLIDING_WINDOW_SUBCASE( case34, x_f, window_shape, axis, stride );
    SLIDING_WINDOW_SUBCASE( case34, x_h, window_shape, axis, stride );
    SLIDING_WINDOW_SUBCASE( case34, x_d, window_shape, axis, stride );

    #if defined(NMTOOLS_TESTING_GENERIC_NDARRAY)
    #endif
}

TEST_CASE("sliding_window(case35)" * doctest::test_suite("view::sliding_window"))
{
    SLIDING_WINDOW_SUBCASE( case35, x, window_shape, axis, stride );
    SLIDING_WINDOW_SUBCASE( case35, x_a, window_shape, axis, stride );
    SLIDING_WINDOW_SUBCASE( case35, x_f, window_shape, axis, stride );
    SLIDING_WINDOW_SUBCASE( case35, x_h, window_shape, axis, stride );
    SLIDING_WINDOW_SUBCASE( case35, x_d, window_shape, axis, stride );

    #if defined(NMTOOLS_TESTING_GENERIC_NDARRAY)
    #endif
}

TEST_CASE("sliding_window(case36)" * doctest::test_suite("view::sliding_window"))
{
    SLIDING_WINDOW_SUBCASE( case36, x, window_shape, axis, stride );
    SLIDING_WINDOW_SUBCASE( case36, x_a, window_shape, axis, stride );
    SLIDING_WINDOW_SUBCASE( case36, x_f, window_shape, axis, stride );
    SLIDING_WINDOW_SUBCASE( case36, x_h, window_shape, axis, stride );
    SLIDING_WINDOW_SUBCASE( case36, x_d, window_shape, axis, stride );

    #if defined(NMTOOLS_TESTING_GENERIC_NDARRAY)
    #endif
}

TEST_CASE("sliding_window(case38)" * doctest::test_suite("view::sliding_window"))
{
    SLIDING_WINDOW_SUBCASE( case38, x, window_shape, axis, stride, dilation );
    SLIDING_WINDOW_SUBCASE( case38, x_a, window_shape, axis, stride, dilation );
    SLIDING_WINDOW_SUBCASE( case38, x_f, window_shape, axis, stride, dilation );
    SLIDING_WINDOW_SUBCASE( case38, x_h, window_shape, axis, stride, dilation );
    SLIDING_WINDOW_SUBCASE( case38, x_d, window_shape, axis, stride, dilation );

    #if defined(NMTOOLS_TESTING_GENERIC_NDARRAY)
    #endif
}

TEST_CASE("sliding_window(case39)" * doctest::test_suite("view::sliding_window"))
{
    SLIDING_WINDOW_SUBCASE( case39, x, window_shape, axis, stride, dilation );
    SLIDING_WINDOW_SUBCASE( case39, x_a, window_shape, axis, stride, dilation );
    SLIDING_WINDOW_SUBCASE( case39, x_f, window_shape, axis, stride, dilation );
    SLIDING_WINDOW_SUBCASE( case39, x_h, window_shape, axis, stride, dilation );
    SLIDING_WINDOW_SUBCASE( case39, x_d, window_shape, axis, stride, dilation );

    #if defined(NMTOOLS_TESTING_GENERIC_NDARRAY)
    #endif
}

TEST_CASE("sliding_window(case40)" * doctest::test_suite("view::sliding_window"))
{
    SLIDING_WINDOW_SUBCASE( case40, x, window_shape, axis, stride, dilation );
    SLIDING_WINDOW_SUBCASE( case40, x_a, window_shape, axis, stride, dilation );
    SLIDING_WINDOW_SUBCASE( case40, x_f, window_shape, axis, stride, dilation );
    SLIDING_WINDOW_SUBCASE( case40, x_h, window_shape, axis, stride, dilation );
    SLIDING_WINDOW_SUBCASE( case40, x_d, window_shape, axis, stride, dilation );

    #if defined(NMTOOLS_TESTING_GENERIC_NDARRAY)
    #endif
}