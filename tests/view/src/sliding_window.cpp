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

#include "nmtools/array/view/sliding_window.hpp"
#include "nmtools/testing/data/array/sliding_window.hpp"
#include "nmtools/testing/doctest.hpp"

#define SLIDING_WINDOW_SUBCASE(case_name, ...) \
SUBCASE(#case_name) \
{ \
    NMTOOLS_TESTING_DECLARE_NS(array, sliding_window, case_name); \
    using namespace args; \
    auto result = nmtools::view::sliding_window(__VA_ARGS__); \
    NMTOOLS_ASSERT_CLOSE( result, expect::expected ); \
}

TEST_CASE("sliding_window(case1)" * doctest::test_suite("view::sliding_window"))
{
    SLIDING_WINDOW_SUBCASE( case1, x, window_shape );
    SLIDING_WINDOW_SUBCASE( case1, x_a, window_shape );
    SLIDING_WINDOW_SUBCASE( case1, x_f, window_shape );
    SLIDING_WINDOW_SUBCASE( case1, x_h, window_shape );
    SLIDING_WINDOW_SUBCASE( case1, x_d, window_shape );

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
}

TEST_CASE("sliding_window(case2)" * doctest::test_suite("view::sliding_window"))
{
    SLIDING_WINDOW_SUBCASE( case2, x, window_shape );
    SLIDING_WINDOW_SUBCASE( case2, x_a, window_shape_a );
    SLIDING_WINDOW_SUBCASE( case2, x_f, window_shape_f );
    SLIDING_WINDOW_SUBCASE( case2, x_h, window_shape_h );
    SLIDING_WINDOW_SUBCASE( case2, x_d, window_shape_v );

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
}

TEST_CASE("sliding_window(case3)" * doctest::test_suite("view::sliding_window"))
{
    SLIDING_WINDOW_SUBCASE( case3, x, window_shape, axis );
    SLIDING_WINDOW_SUBCASE( case3, x_a, window_shape, axis );
    SLIDING_WINDOW_SUBCASE( case3, x_f, window_shape, axis );
    SLIDING_WINDOW_SUBCASE( case3, x_h, window_shape, axis );
    SLIDING_WINDOW_SUBCASE( case3, x_d, window_shape, axis );

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
}

TEST_CASE("sliding_window(case4)" * doctest::test_suite("view::sliding_window"))
{
    SLIDING_WINDOW_SUBCASE( case4, x, window_shape, axis );
    SLIDING_WINDOW_SUBCASE( case4, x_a, window_shape_a, axis_a );
    SLIDING_WINDOW_SUBCASE( case4, x_f, window_shape_f, axis_f );
    SLIDING_WINDOW_SUBCASE( case4, x_h, window_shape_h, axis_h );
    SLIDING_WINDOW_SUBCASE( case4, x_d, window_shape_v, axis_v );

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
}

TEST_CASE("sliding_window(case5)" * doctest::test_suite("view::sliding_window"))
{
    SLIDING_WINDOW_SUBCASE( case5, x, window_shape );
    SLIDING_WINDOW_SUBCASE( case5, x_a, window_shape_a );
    SLIDING_WINDOW_SUBCASE( case5, x_f, window_shape_f );
    SLIDING_WINDOW_SUBCASE( case5, x_h, window_shape_h );
    SLIDING_WINDOW_SUBCASE( case5, x_d, window_shape_v );

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
}

TEST_CASE("sliding_window(case6)" * doctest::test_suite("view::sliding_window"))
{
    SLIDING_WINDOW_SUBCASE( case6, x, window_shape, axis );
    SLIDING_WINDOW_SUBCASE( case6, x_a, window_shape_a, axis_a );
    SLIDING_WINDOW_SUBCASE( case6, x_f, window_shape_f, axis_f );
    SLIDING_WINDOW_SUBCASE( case6, x_h, window_shape_h, axis_h );
    SLIDING_WINDOW_SUBCASE( case6, x_d, window_shape_v, axis_v );

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
}

TEST_CASE("sliding_window(case7)" * doctest::test_suite("view::sliding_window"))
{
    SLIDING_WINDOW_SUBCASE( case7, x, window_shape, axis );
    SLIDING_WINDOW_SUBCASE( case7, x_a, window_shape_a, axis_a );
    SLIDING_WINDOW_SUBCASE( case7, x_f, window_shape_f, axis_f );
    SLIDING_WINDOW_SUBCASE( case7, x_h, window_shape_h, axis_h );
    SLIDING_WINDOW_SUBCASE( case7, x_d, window_shape_v, axis_v );

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
}

TEST_CASE("sliding_window(case8)" * doctest::test_suite("view::sliding_window"))
{
    SLIDING_WINDOW_SUBCASE( case8, x, window_shape, axis );
    SLIDING_WINDOW_SUBCASE( case8, x_a, window_shape_a, axis_a );
    SLIDING_WINDOW_SUBCASE( case8, x_f, window_shape_f, axis_f );
    SLIDING_WINDOW_SUBCASE( case8, x_h, window_shape_h, axis_h );
    SLIDING_WINDOW_SUBCASE( case8, x_d, window_shape_v, axis_v );

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
}

TEST_CASE("sliding_window(case9)" * doctest::test_suite("view::sliding_window"))
{
    SLIDING_WINDOW_SUBCASE( case9, x, window_shape );
    SLIDING_WINDOW_SUBCASE( case9, x_a, window_shape_a );
    SLIDING_WINDOW_SUBCASE( case9, x_f, window_shape_f );
    SLIDING_WINDOW_SUBCASE( case9, x_h, window_shape_h );
    SLIDING_WINDOW_SUBCASE( case9, x_d, window_shape_v );

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
}

TEST_CASE("sliding_window(case10)" * doctest::test_suite("view::sliding_window"))
{
    SLIDING_WINDOW_SUBCASE( case10, x, window_shape, axis );
    SLIDING_WINDOW_SUBCASE( case10, x_a, window_shape_a, axis_a );
    SLIDING_WINDOW_SUBCASE( case10, x_f, window_shape_f, axis_f );
    SLIDING_WINDOW_SUBCASE( case10, x_h, window_shape_h, axis_h );
    SLIDING_WINDOW_SUBCASE( case10, x_d, window_shape_v, axis_v );

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
}