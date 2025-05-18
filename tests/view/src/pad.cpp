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

#include "nmtools/array/pad.hpp"
#include "nmtools/testing/data/array/pad.hpp"
#include "nmtools/testing/doctest.hpp"

#define PAD2_SUBCASE(case_name, ...) \
SUBCASE(#case_name) \
{ \
    NMTOOLS_TESTING_USE_CASE(array, pad, case_name); \
    using namespace args; \
    auto result = nmtools::view::pad2(__VA_ARGS__); \
    NMTOOLS_ASSERT_EQUAL( nmtools::shape(result), nmtools::shape(expect::result) ); \
    NMTOOLS_ASSERT_EQUAL( result, expect::result ); \
}

#define PAD_SUBCASE(case_name, ...) \
SUBCASE(#case_name) \
{ \
    NMTOOLS_TESTING_USE_CASE(array, pad, case_name); \
    using namespace args; \
    auto result = nmtools::view::pad(__VA_ARGS__); \
    NMTOOLS_ASSERT_EQUAL( nmtools::shape(result), nmtools::shape(expect::result) ); \
    NMTOOLS_ASSERT_EQUAL( result, expect::result ); \
}

#define PAD3_SUBCASE(case_name, ...) \
SUBCASE(#case_name) \
{ \
    NMTOOLS_TESTING_USE_CASE(array, pad, case_name); \
    using namespace args; \
    auto result = nmtools::view::pad3(__VA_ARGS__); \
    NMTOOLS_ASSERT_EQUAL( nmtools::shape(result), nmtools::shape(expect::result) ); \
    NMTOOLS_ASSERT_EQUAL( result, expect::result ); \
}

TEST_CASE("pad(case1)" * doctest::test_suite("view::pad"))
{
    #if !defined(NMTOOLS_TESTING_GENERIC_NDARRAY)
    PAD2_SUBCASE( case1, array, pads );
    PAD2_SUBCASE( case1, array_a, pads_a );
    PAD2_SUBCASE( case1, array_f, pads_f );
    PAD2_SUBCASE( case1, array_h, pads_h );
    PAD2_SUBCASE( case1, array_d, pads_v );

    PAD_SUBCASE( case1, array, pad_width );
    PAD_SUBCASE( case1, array_a, pad_width_a );
    PAD_SUBCASE( case1, array_f, pad_width_f );
    PAD_SUBCASE( case1, array_h, pad_width_h );
    PAD_SUBCASE( case1, array_d, pad_width_d );

    PAD3_SUBCASE( case1, array, pad );
    PAD3_SUBCASE( case1, array_a, pad_a );
    PAD3_SUBCASE( case1, array_f, pad_f );
    PAD3_SUBCASE( case1, array_h, pad_h );
    PAD3_SUBCASE( case1, array_d, pad_v );

    #else
    PAD2_SUBCASE( case1, array_cs_fb, pads_a );
    PAD2_SUBCASE( case1, array_cs_hb, pads_a );
    PAD2_SUBCASE( case1, array_cs_db, pads_a );

    PAD_SUBCASE( case1, array_cs_fb, pad_width_a );
    PAD_SUBCASE( case1, array_cs_hb, pad_width_a );
    PAD_SUBCASE( case1, array_cs_db, pad_width_a );

    PAD3_SUBCASE( case1, array_cs_fb, pad_a );
    PAD3_SUBCASE( case1, array_cs_hb, pad_a );
    PAD3_SUBCASE( case1, array_cs_db, pad_a );

    PAD2_SUBCASE( case1, array_fs_fb, pads_a );
    PAD2_SUBCASE( case1, array_fs_hb, pads_a );
    PAD2_SUBCASE( case1, array_fs_db, pads_a );

    PAD_SUBCASE( case1, array_fs_fb, pad_width_a );
    PAD_SUBCASE( case1, array_fs_hb, pad_width_a );
    PAD_SUBCASE( case1, array_fs_db, pad_width_a );

    PAD3_SUBCASE( case1, array_fs_fb, pad_a );
    PAD3_SUBCASE( case1, array_fs_hb, pad_a );
    PAD3_SUBCASE( case1, array_fs_db, pad_a );

    PAD2_SUBCASE( case1, array_hs_fb, pads_a );
    PAD2_SUBCASE( case1, array_hs_hb, pads_a );
    PAD2_SUBCASE( case1, array_hs_db, pads_a );

    PAD_SUBCASE( case1, array_hs_fb, pad_width_a );
    PAD_SUBCASE( case1, array_hs_hb, pad_width_a );
    PAD_SUBCASE( case1, array_hs_db, pad_width_a );

    PAD3_SUBCASE( case1, array_hs_fb, pad_a );
    PAD3_SUBCASE( case1, array_hs_hb, pad_a );
    PAD3_SUBCASE( case1, array_hs_db, pad_a );

    PAD2_SUBCASE( case1, array_ds_fb, pads_a );
    PAD2_SUBCASE( case1, array_ds_hb, pads_a );
    PAD2_SUBCASE( case1, array_ds_db, pads_a );

    PAD_SUBCASE( case1, array_ds_fb, pad_width_a );
    PAD_SUBCASE( case1, array_ds_hb, pad_width_a );
    PAD_SUBCASE( case1, array_ds_db, pad_width_a );

    PAD3_SUBCASE( case1, array_ds_fb, pad_a );
    PAD3_SUBCASE( case1, array_ds_hb, pad_a );
    PAD3_SUBCASE( case1, array_ds_db, pad_a );

    PAD2_SUBCASE( case1, array_ls_fb, pads_a );
    PAD2_SUBCASE( case1, array_ls_hb, pads_a );
    PAD2_SUBCASE( case1, array_ls_db, pads_a );

    PAD_SUBCASE( case1, array_ls_fb, pad_width_a );
    PAD_SUBCASE( case1, array_ls_hb, pad_width_a );
    PAD_SUBCASE( case1, array_ls_db, pad_width_a );

    PAD3_SUBCASE( case1, array_ls_fb, pad_a );
    PAD3_SUBCASE( case1, array_ls_hb, pad_a );
    PAD3_SUBCASE( case1, array_ls_db, pad_a );
    #endif
}

TEST_CASE("pad(case2)" * doctest::test_suite("view::pad"))
{
    #if !defined(NMTOOLS_TESTING_GENERIC_NDARRAY)
    PAD2_SUBCASE( case2, array, pads );
    PAD2_SUBCASE( case2, array_a, pads_a );
    PAD2_SUBCASE( case2, array_f, pads_f );
    PAD2_SUBCASE( case2, array_h, pads_h );
    PAD2_SUBCASE( case2, array_d, pads_a );

    PAD_SUBCASE( case2, array, pad_width );
    PAD_SUBCASE( case2, array_a, pad_width_a );
    PAD_SUBCASE( case2, array_f, pad_width_f );
    PAD_SUBCASE( case2, array_h, pad_width_h );
    PAD_SUBCASE( case2, array_d, pad_width_a );

    PAD3_SUBCASE( case2, array, pad );
    PAD3_SUBCASE( case2, array_a, pad_a );
    PAD3_SUBCASE( case2, array_f, pad_f );
    PAD3_SUBCASE( case2, array_h, pad_h );
    PAD3_SUBCASE( case2, array_d, pad_a );

    #else
    PAD2_SUBCASE( case2, array_cs_fb, pads_a );
    PAD2_SUBCASE( case2, array_cs_hb, pads_a );
    PAD2_SUBCASE( case2, array_cs_db, pads_a );

    PAD_SUBCASE( case2, array_cs_fb, pad_width_a );
    PAD_SUBCASE( case2, array_cs_hb, pad_width_a );
    PAD_SUBCASE( case2, array_cs_db, pad_width_a );

    PAD3_SUBCASE( case2, array_cs_fb, pad_a );
    PAD3_SUBCASE( case2, array_cs_hb, pad_a );
    PAD3_SUBCASE( case2, array_cs_db, pad_a );

    PAD2_SUBCASE( case2, array_fs_fb, pads_a );
    PAD2_SUBCASE( case2, array_fs_hb, pads_a );
    PAD2_SUBCASE( case2, array_fs_db, pads_a );

    PAD_SUBCASE( case2, array_fs_fb, pad_width_a );
    PAD_SUBCASE( case2, array_fs_hb, pad_width_a );
    PAD_SUBCASE( case2, array_fs_db, pad_width_a );

    PAD3_SUBCASE( case2, array_fs_fb, pad_a );
    PAD3_SUBCASE( case2, array_fs_hb, pad_a );
    PAD3_SUBCASE( case2, array_fs_db, pad_a );

    PAD2_SUBCASE( case2, array_hs_fb, pads_a );
    PAD2_SUBCASE( case2, array_hs_hb, pads_a );
    PAD2_SUBCASE( case2, array_hs_db, pads_a );

    PAD_SUBCASE( case2, array_hs_fb, pad_width_a );
    PAD_SUBCASE( case2, array_hs_hb, pad_width_a );
    PAD_SUBCASE( case2, array_hs_db, pad_width_a );

    PAD3_SUBCASE( case2, array_hs_fb, pad_a );
    PAD3_SUBCASE( case2, array_hs_hb, pad_a );
    PAD3_SUBCASE( case2, array_hs_db, pad_a );

    PAD2_SUBCASE( case2, array_ds_fb, pads_a );
    PAD2_SUBCASE( case2, array_ds_hb, pads_a );
    PAD2_SUBCASE( case2, array_ds_db, pads_a );

    PAD_SUBCASE( case2, array_ds_fb, pad_width_a );
    PAD_SUBCASE( case2, array_ds_hb, pad_width_a );
    PAD_SUBCASE( case2, array_ds_db, pad_width_a );

    PAD3_SUBCASE( case2, array_ds_fb, pad_a );
    PAD3_SUBCASE( case2, array_ds_hb, pad_a );
    PAD3_SUBCASE( case2, array_ds_db, pad_a );

    // Added ls variants for case2 based on case1 pattern
    PAD2_SUBCASE( case2, array_ls_fb, pads_a );
    PAD2_SUBCASE( case2, array_ls_hb, pads_a );
    PAD2_SUBCASE( case2, array_ls_db, pads_a );

    PAD_SUBCASE( case2, array_ls_fb, pad_width_a );
    PAD_SUBCASE( case2, array_ls_hb, pad_width_a );
    PAD_SUBCASE( case2, array_ls_db, pad_width_a );

    PAD3_SUBCASE( case2, array_ls_fb, pad_a );
    PAD3_SUBCASE( case2, array_ls_hb, pad_a );
    PAD3_SUBCASE( case2, array_ls_db, pad_a );
    #endif
}

TEST_CASE("pad(case3)" * doctest::test_suite("view::pad"))
{
    #if !defined(NMTOOLS_TESTING_GENERIC_NDARRAY)
    PAD2_SUBCASE( case3, array, pads );
    PAD2_SUBCASE( case3, array_a, pads_a );
    PAD2_SUBCASE( case3, array_f, pads_f );
    PAD2_SUBCASE( case3, array_h, pads_h );
    PAD2_SUBCASE( case3, array_d, pads_a );

    PAD_SUBCASE( case3, array, pad_width );
    PAD_SUBCASE( case3, array_a, pad_width_a );
    PAD_SUBCASE( case3, array_f, pad_width_f );
    PAD_SUBCASE( case3, array_h, pad_width_h );
    PAD_SUBCASE( case3, array_d, pad_width_a );

    PAD3_SUBCASE( case3, array, pad );
    PAD3_SUBCASE( case3, array_a, pad_a );
    PAD3_SUBCASE( case3, array_f, pad_f );
    PAD3_SUBCASE( case3, array_h, pad_h );
    PAD3_SUBCASE( case3, array_d, pad_a );

    #else
    PAD2_SUBCASE( case3, array_cs_fb, pads_a );
    PAD2_SUBCASE( case3, array_cs_hb, pads_a );
    PAD2_SUBCASE( case3, array_cs_db, pads_a );

    PAD_SUBCASE( case3, array_cs_fb, pad_width_a );
    PAD_SUBCASE( case3, array_cs_hb, pad_width_a );
    PAD_SUBCASE( case3, array_cs_db, pad_width_a );

    PAD3_SUBCASE( case3, array_cs_fb, pad_a );
    PAD3_SUBCASE( case3, array_cs_hb, pad_a );
    PAD3_SUBCASE( case3, array_cs_db, pad_a );

    PAD2_SUBCASE( case3, array_fs_fb, pads_a );
    PAD2_SUBCASE( case3, array_fs_hb, pads_a );
    PAD2_SUBCASE( case3, array_fs_db, pads_a );

    PAD_SUBCASE( case3, array_fs_fb, pad_width_a );
    PAD_SUBCASE( case3, array_fs_hb, pad_width_a );
    PAD_SUBCASE( case3, array_fs_db, pad_width_a );

    PAD3_SUBCASE( case3, array_fs_fb, pad_a );
    PAD3_SUBCASE( case3, array_fs_hb, pad_a );
    PAD3_SUBCASE( case3, array_fs_db, pad_a );

    PAD2_SUBCASE( case3, array_hs_fb, pads_a );
    PAD2_SUBCASE( case3, array_hs_hb, pads_a );
    PAD2_SUBCASE( case3, array_hs_db, pads_a );

    PAD_SUBCASE( case3, array_hs_fb, pad_width_a );
    PAD_SUBCASE( case3, array_hs_hb, pad_width_a );
    PAD_SUBCASE( case3, array_hs_db, pad_width_a );

    PAD3_SUBCASE( case3, array_hs_fb, pad_a );
    PAD3_SUBCASE( case3, array_hs_hb, pad_a );
    PAD3_SUBCASE( case3, array_hs_db, pad_a );

    PAD2_SUBCASE( case3, array_ds_fb, pads_a );
    PAD2_SUBCASE( case3, array_ds_hb, pads_a );
    PAD2_SUBCASE( case3, array_ds_db, pads_a );

    PAD_SUBCASE( case3, array_ds_fb, pad_width_a );
    PAD_SUBCASE( case3, array_ds_hb, pad_width_a );
    PAD_SUBCASE( case3, array_ds_db, pad_width_a );

    PAD3_SUBCASE( case3, array_ds_fb, pad_a );
    PAD3_SUBCASE( case3, array_ds_hb, pad_a );
    PAD3_SUBCASE( case3, array_ds_db, pad_a );

    // Added ls variants for case3 based on case1 pattern
    PAD2_SUBCASE( case3, array_ls_fb, pads_a );
    PAD2_SUBCASE( case3, array_ls_hb, pads_a );
    PAD2_SUBCASE( case3, array_ls_db, pads_a );

    PAD_SUBCASE( case3, array_ls_fb, pad_width_a );
    PAD_SUBCASE( case3, array_ls_hb, pad_width_a );
    PAD_SUBCASE( case3, array_ls_db, pad_width_a );

    PAD3_SUBCASE( case3, array_ls_fb, pad_a );
    PAD3_SUBCASE( case3, array_ls_hb, pad_a );
    PAD3_SUBCASE( case3, array_ls_db, pad_a );
    #endif
}

TEST_CASE("pad(case4)" * doctest::test_suite("view::pad"))
{
    #if !defined(NMTOOLS_TESTING_GENERIC_NDARRAY)
    PAD2_SUBCASE( case4, array, pads );
    PAD2_SUBCASE( case4, array_a, pads_a );
    PAD2_SUBCASE( case4, array_f, pads_f );
    PAD2_SUBCASE( case4, array_h, pads_h );
    PAD2_SUBCASE( case4, array_d, pads_a );

    PAD_SUBCASE( case4, array, pad_width );
    PAD_SUBCASE( case4, array_a, pad_width_a );
    PAD_SUBCASE( case4, array_f, pad_width_f );
    PAD_SUBCASE( case4, array_h, pad_width_h );
    PAD_SUBCASE( case4, array_d, pad_width_a );

    PAD3_SUBCASE( case4, array, pad );
    PAD3_SUBCASE( case4, array_a, pad_a );
    PAD3_SUBCASE( case4, array_f, pad_f );
    PAD3_SUBCASE( case4, array_h, pad_h );
    PAD3_SUBCASE( case4, array_d, pad_a );

    #else
    PAD2_SUBCASE( case4, array_cs_fb, pads_a );
    PAD2_SUBCASE( case4, array_cs_hb, pads_a );
    PAD2_SUBCASE( case4, array_cs_db, pads_a );

    PAD_SUBCASE( case4, array_cs_fb, pad_width_a );
    PAD_SUBCASE( case4, array_cs_hb, pad_width_a );
    PAD_SUBCASE( case4, array_cs_db, pad_width_a );

    PAD3_SUBCASE( case4, array_cs_fb, pad_a );
    PAD3_SUBCASE( case4, array_cs_hb, pad_a );
    PAD3_SUBCASE( case4, array_cs_db, pad_a );

    PAD2_SUBCASE( case4, array_fs_fb, pads_a );
    PAD2_SUBCASE( case4, array_fs_hb, pads_a );
    PAD2_SUBCASE( case4, array_fs_db, pads_a );

    PAD_SUBCASE( case4, array_fs_fb, pad_width_a );
    PAD_SUBCASE( case4, array_fs_hb, pad_width_a );
    PAD_SUBCASE( case4, array_fs_db, pad_width_a );

    PAD3_SUBCASE( case4, array_fs_fb, pad_a );
    PAD3_SUBCASE( case4, array_fs_hb, pad_a );
    PAD3_SUBCASE( case4, array_fs_db, pad_a );

    PAD2_SUBCASE( case4, array_hs_fb, pads_a );
    PAD2_SUBCASE( case4, array_hs_hb, pads_a );
    PAD2_SUBCASE( case4, array_hs_db, pads_a );

    PAD_SUBCASE( case4, array_hs_fb, pad_width_a );
    PAD_SUBCASE( case4, array_hs_hb, pad_width_a );
    PAD_SUBCASE( case4, array_hs_db, pad_width_a );

    PAD3_SUBCASE( case4, array_hs_fb, pad_a );
    PAD3_SUBCASE( case4, array_hs_hb, pad_a );
    PAD3_SUBCASE( case4, array_hs_db, pad_a );

    PAD2_SUBCASE( case4, array_ds_fb, pads_a );
    PAD2_SUBCASE( case4, array_ds_hb, pads_a );
    PAD2_SUBCASE( case4, array_ds_db, pads_a );

    PAD_SUBCASE( case4, array_ds_fb, pad_width_a );
    PAD_SUBCASE( case4, array_ds_hb, pad_width_a );
    PAD_SUBCASE( case4, array_ds_db, pad_width_a );

    PAD3_SUBCASE( case4, array_ds_fb, pad_a );
    PAD3_SUBCASE( case4, array_ds_hb, pad_a );
    PAD3_SUBCASE( case4, array_ds_db, pad_a );

    // Added ls variants for case4 based on case1 pattern
    PAD2_SUBCASE( case4, array_ls_fb, pads_a );
    PAD2_SUBCASE( case4, array_ls_hb, pads_a );
    PAD2_SUBCASE( case4, array_ls_db, pads_a );

    PAD_SUBCASE( case4, array_ls_fb, pad_width_a );
    PAD_SUBCASE( case4, array_ls_hb, pad_width_a );
    PAD_SUBCASE( case4, array_ls_db, pad_width_a );

    PAD3_SUBCASE( case4, array_ls_fb, pad_a );
    PAD3_SUBCASE( case4, array_ls_hb, pad_a );
    PAD3_SUBCASE( case4, array_ls_db, pad_a );
    #endif
}

TEST_CASE("pad(case5)" * doctest::test_suite("view::pad"))
{
    #if !defined(NMTOOLS_TESTING_GENERIC_NDARRAY)
    PAD2_SUBCASE( case5, array, pads );
    PAD2_SUBCASE( case5, array_a, pads_a );
    PAD2_SUBCASE( case5, array_f, pads_f );
    PAD2_SUBCASE( case5, array_h, pads_h );
    PAD2_SUBCASE( case5, array_d, pads_a );

    PAD_SUBCASE( case5, array, pad_width );
    PAD_SUBCASE( case5, array_a, pad_width_a );
    PAD_SUBCASE( case5, array_f, pad_width_f );
    PAD_SUBCASE( case5, array_h, pad_width_h );
    PAD_SUBCASE( case5, array_d, pad_width_a );

    PAD3_SUBCASE( case5, array, pad );
    PAD3_SUBCASE( case5, array_a, pad_a );
    PAD3_SUBCASE( case5, array_f, pad_f );
    PAD3_SUBCASE( case5, array_h, pad_h );
    PAD3_SUBCASE( case5, array_d, pad_a );

    #else
    PAD2_SUBCASE( case5, array_cs_fb, pads_a );
    PAD2_SUBCASE( case5, array_cs_hb, pads_a );
    PAD2_SUBCASE( case5, array_cs_db, pads_a );

    PAD_SUBCASE( case5, array_cs_fb, pad_width_a );
    PAD_SUBCASE( case5, array_cs_hb, pad_width_a );
    PAD_SUBCASE( case5, array_cs_db, pad_width_a );

    PAD3_SUBCASE( case5, array_cs_fb, pad_a );
    PAD3_SUBCASE( case5, array_cs_hb, pad_a );
    PAD3_SUBCASE( case5, array_cs_db, pad_a );

    PAD2_SUBCASE( case5, array_fs_fb, pads_a );
    PAD2_SUBCASE( case5, array_fs_hb, pads_a );
    PAD2_SUBCASE( case5, array_fs_db, pads_a );

    PAD_SUBCASE( case5, array_fs_fb, pad_width_a );
    PAD_SUBCASE( case5, array_fs_hb, pad_width_a );
    PAD_SUBCASE( case5, array_fs_db, pad_width_a );

    PAD3_SUBCASE( case5, array_fs_fb, pad_a );
    PAD3_SUBCASE( case5, array_fs_hb, pad_a );
    PAD3_SUBCASE( case5, array_fs_db, pad_a );

    PAD2_SUBCASE( case5, array_hs_fb, pads_a );
    PAD2_SUBCASE( case5, array_hs_hb, pads_a );
    PAD2_SUBCASE( case5, array_hs_db, pads_a );

    PAD_SUBCASE( case5, array_hs_fb, pad_width_a );
    PAD_SUBCASE( case5, array_hs_hb, pad_width_a );
    PAD_SUBCASE( case5, array_hs_db, pad_width_a );

    PAD3_SUBCASE( case5, array_hs_fb, pad_a );
    PAD3_SUBCASE( case5, array_hs_hb, pad_a );
    PAD3_SUBCASE( case5, array_hs_db, pad_a );

    PAD2_SUBCASE( case5, array_ds_fb, pads_a );
    PAD2_SUBCASE( case5, array_ds_hb, pads_a );
    PAD2_SUBCASE( case5, array_ds_db, pads_a );

    PAD_SUBCASE( case5, array_ds_fb, pad_width_a );
    PAD_SUBCASE( case5, array_ds_hb, pad_width_a );
    PAD_SUBCASE( case5, array_ds_db, pad_width_a );

    PAD3_SUBCASE( case5, array_ds_fb, pad_a );
    PAD3_SUBCASE( case5, array_ds_hb, pad_a );
    PAD3_SUBCASE( case5, array_ds_db, pad_a );

    // Added ls variants for case5 based on case1 pattern
    PAD2_SUBCASE( case5, array_ls_fb, pads_a );
    PAD2_SUBCASE( case5, array_ls_hb, pads_a );
    PAD2_SUBCASE( case5, array_ls_db, pads_a );

    PAD_SUBCASE( case5, array_ls_fb, pad_width_a );
    PAD_SUBCASE( case5, array_ls_hb, pad_width_a );
    PAD_SUBCASE( case5, array_ls_db, pad_width_a );

    PAD3_SUBCASE( case5, array_ls_fb, pad_a );
    PAD3_SUBCASE( case5, array_ls_hb, pad_a );
    PAD3_SUBCASE( case5, array_ls_db, pad_a );
    #endif
}

TEST_CASE("pad(case6)" * doctest::test_suite("view::pad"))
{
    #if !defined(NMTOOLS_TESTING_GENERIC_NDARRAY)
    PAD2_SUBCASE( case6, array, pads );
    PAD2_SUBCASE( case6, array_a, pads_a );
    PAD2_SUBCASE( case6, array_f, pads_f );
    PAD2_SUBCASE( case6, array_h, pads_h );
    PAD2_SUBCASE( case6, array_d, pads_a );

    PAD_SUBCASE( case6, array, pad_width );
    PAD_SUBCASE( case6, array_a, pad_width_a );
    PAD_SUBCASE( case6, array_f, pad_width_f );
    PAD_SUBCASE( case6, array_h, pad_width_h );
    PAD_SUBCASE( case6, array_d, pad_width_a );

    PAD3_SUBCASE( case6, array, pad );
    PAD3_SUBCASE( case6, array_a, pad_a );
    PAD3_SUBCASE( case6, array_f, pad_f );
    PAD3_SUBCASE( case6, array_h, pad_h );
    PAD3_SUBCASE( case6, array_d, pad_a );

    #else
    // Added missing generic ndarray tests for case6

    PAD2_SUBCASE( case6, array_cs_fb, pads_a );
    PAD2_SUBCASE( case6, array_cs_hb, pads_a );
    PAD2_SUBCASE( case6, array_cs_db, pads_a );

    PAD_SUBCASE( case6, array_cs_fb, pad_width_a );
    PAD_SUBCASE( case6, array_cs_hb, pad_width_a );
    PAD_SUBCASE( case6, array_cs_db, pad_width_a );

    PAD3_SUBCASE( case6, array_cs_fb, pad_a );
    PAD3_SUBCASE( case6, array_cs_hb, pad_a );
    PAD3_SUBCASE( case6, array_cs_db, pad_a );

    PAD2_SUBCASE( case6, array_fs_fb, pads_a );
    PAD2_SUBCASE( case6, array_fs_hb, pads_a );
    PAD2_SUBCASE( case6, array_fs_db, pads_a );

    PAD_SUBCASE( case6, array_fs_fb, pad_width_a );
    PAD_SUBCASE( case6, array_fs_hb, pad_width_a );
    PAD_SUBCASE( case6, array_fs_db, pad_width_a );

    PAD3_SUBCASE( case6, array_fs_fb, pad_a );
    PAD3_SUBCASE( case6, array_fs_hb, pad_a );
    PAD3_SUBCASE( case6, array_fs_db, pad_a );

    PAD2_SUBCASE( case6, array_hs_fb, pads_a );
    PAD2_SUBCASE( case6, array_hs_hb, pads_a );
    PAD2_SUBCASE( case6, array_hs_db, pads_a );

    PAD_SUBCASE( case6, array_hs_fb, pad_width_a );
    PAD_SUBCASE( case6, array_hs_hb, pad_width_a );
    PAD_SUBCASE( case6, array_hs_db, pad_width_a );

    PAD3_SUBCASE( case6, array_hs_fb, pad_a );
    PAD3_SUBCASE( case6, array_hs_hb, pad_a );
    PAD3_SUBCASE( case6, array_hs_db, pad_a );

    PAD2_SUBCASE( case6, array_ds_fb, pads_a );
    PAD2_SUBCASE( case6, array_ds_hb, pads_a );
    PAD2_SUBCASE( case6, array_ds_db, pads_a );

    PAD_SUBCASE( case6, array_ds_fb, pad_width_a );
    PAD_SUBCASE( case6, array_ds_hb, pad_width_a );
    PAD_SUBCASE( case6, array_ds_db, pad_width_a );

    PAD3_SUBCASE( case6, array_ds_fb, pad_a );
    PAD3_SUBCASE( case6, array_ds_hb, pad_a );
    PAD3_SUBCASE( case6, array_ds_db, pad_a );

    // Added ls variants for case6 based on case1 pattern
    PAD2_SUBCASE( case6, array_ls_fb, pads_a );
    PAD2_SUBCASE( case6, array_ls_hb, pads_a );
    PAD2_SUBCASE( case6, array_ls_db, pads_a );

    PAD_SUBCASE( case6, array_ls_fb, pad_width_a );
    PAD_SUBCASE( case6, array_ls_hb, pad_width_a );
    PAD_SUBCASE( case6, array_ls_db, pad_width_a );

    PAD3_SUBCASE( case6, array_ls_fb, pad_a );
    PAD3_SUBCASE( case6, array_ls_hb, pad_a );
    PAD3_SUBCASE( case6, array_ls_db, pad_a );
    #endif
}