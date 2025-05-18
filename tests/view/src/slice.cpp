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

#include "nmtools/array/slice.hpp"
#include "nmtools/testing/data/array/slice.hpp"
#include "nmtools/testing/doctest.hpp"

namespace nm = nmtools;
namespace na = nmtools::array;

#define SLICE_SUBCASE(case_name, ...) \
SUBCASE(#case_name) \
{ \
    NMTOOLS_TESTING_USE_CASE(array, slice, case_name); \
    using namespace args; \
    auto result = nmtools::view::slice(__VA_ARGS__); \
    NMTOOLS_ASSERT_EQUAL( nmtools::shape(result), nmtools::shape(expect::result) ); \
    NMTOOLS_ASSERT_EQUAL( result, expect::result ); \
}

TEST_CASE("slice(case1)" * doctest::test_suite("view::slice"))
{
    #if !defined(NMTOOLS_TESTING_GENERIC_NDARRAY)
    SLICE_SUBCASE(case1,   array, slice0, slice1, slice2);
    SLICE_SUBCASE(case1, array_a, slice0, slice1, slice2);
    SLICE_SUBCASE(case1, array_f, slice0, slice1, slice2);
    SLICE_SUBCASE(case1, array_d, slice0, slice1, slice2);
    SLICE_SUBCASE(case1, array_h, slice0, slice1, slice2);

    #else
    SLICE_SUBCASE(case1, array_cs_fb, slice0, slice1, slice2);
    SLICE_SUBCASE(case1, array_cs_hb, slice0, slice1, slice2);
    SLICE_SUBCASE(case1, array_cs_db, slice0, slice1, slice2);

    SLICE_SUBCASE(case1, array_fs_fb, slice0, slice1, slice2);
    SLICE_SUBCASE(case1, array_fs_hb, slice0, slice1, slice2);
    SLICE_SUBCASE(case1, array_fs_db, slice0, slice1, slice2);

    SLICE_SUBCASE(case1, array_hs_fb, slice0, slice1, slice2);
    SLICE_SUBCASE(case1, array_hs_hb, slice0, slice1, slice2);
    SLICE_SUBCASE(case1, array_hs_db, slice0, slice1, slice2);

    SLICE_SUBCASE(case1, array_ds_fb, slice0, slice1, slice2);
    SLICE_SUBCASE(case1, array_ds_hb, slice0, slice1, slice2);
    SLICE_SUBCASE(case1, array_ds_db, slice0, slice1, slice2);

    SLICE_SUBCASE(case1, array_ls_fb, slice0, slice1, slice2);
    SLICE_SUBCASE(case1, array_ls_hb, slice0, slice1, slice2);
    SLICE_SUBCASE(case1, array_ls_db, slice0, slice1, slice2);
    #endif
}

TEST_CASE("slice(case2)" * doctest::test_suite("view::slice"))
{
    #if !defined(NMTOOLS_TESTING_GENERIC_NDARRAY)
    SLICE_SUBCASE(case2,   array, slice0, slice1, slice2);
    SLICE_SUBCASE(case2, array_a, slice0, slice1, slice2);
    SLICE_SUBCASE(case2, array_f, slice0, slice1, slice2);
    SLICE_SUBCASE(case2, array_d, slice0, slice1, slice2);
    SLICE_SUBCASE(case2, array_h, slice0, slice1, slice2);

    #else
    SLICE_SUBCASE(case2, array_cs_fb, slice0, slice1, slice2);
    SLICE_SUBCASE(case2, array_cs_hb, slice0, slice1, slice2);
    SLICE_SUBCASE(case2, array_cs_db, slice0, slice1, slice2);

    SLICE_SUBCASE(case2, array_fs_fb, slice0, slice1, slice2);
    SLICE_SUBCASE(case2, array_fs_hb, slice0, slice1, slice2);
    SLICE_SUBCASE(case2, array_fs_db, slice0, slice1, slice2);

    SLICE_SUBCASE(case2, array_hs_fb, slice0, slice1, slice2);
    SLICE_SUBCASE(case2, array_hs_hb, slice0, slice1, slice2);
    SLICE_SUBCASE(case2, array_hs_db, slice0, slice1, slice2);

    SLICE_SUBCASE(case2, array_ds_fb, slice0, slice1, slice2);
    SLICE_SUBCASE(case2, array_ds_hb, slice0, slice1, slice2);
    SLICE_SUBCASE(case2, array_ds_db, slice0, slice1, slice2);

    SLICE_SUBCASE(case2, array_ls_fb, slice0, slice1, slice2);
    SLICE_SUBCASE(case2, array_ls_hb, slice0, slice1, slice2);
    SLICE_SUBCASE(case2, array_ls_db, slice0, slice1, slice2);
    #endif
}

TEST_CASE("slice(case3)" * doctest::test_suite("view::slice"))
{
    #if !defined(NMTOOLS_TESTING_GENERIC_NDARRAY)
    SLICE_SUBCASE(case3,   array, slice0, slice1, slice2);
    SLICE_SUBCASE(case3, array_a, slice0, slice1, slice2);
    SLICE_SUBCASE(case3, array_f, slice0, slice1, slice2);
    SLICE_SUBCASE(case3, array_d, slice0, slice1, slice2);
    SLICE_SUBCASE(case3, array_h, slice0, slice1, slice2);

    #else
    SLICE_SUBCASE(case3, array_cs_fb, slice0, slice1, slice2);
    SLICE_SUBCASE(case3, array_cs_hb, slice0, slice1, slice2);
    SLICE_SUBCASE(case3, array_cs_db, slice0, slice1, slice2);

    SLICE_SUBCASE(case3, array_fs_fb, slice0, slice1, slice2);
    SLICE_SUBCASE(case3, array_fs_hb, slice0, slice1, slice2);
    SLICE_SUBCASE(case3, array_fs_db, slice0, slice1, slice2);

    SLICE_SUBCASE(case3, array_hs_fb, slice0, slice1, slice2);
    SLICE_SUBCASE(case3, array_hs_hb, slice0, slice1, slice2);
    SLICE_SUBCASE(case3, array_hs_db, slice0, slice1, slice2);

    SLICE_SUBCASE(case3, array_ds_fb, slice0, slice1, slice2);
    SLICE_SUBCASE(case3, array_ds_hb, slice0, slice1, slice2);
    SLICE_SUBCASE(case3, array_ds_db, slice0, slice1, slice2);

    SLICE_SUBCASE(case3, array_ls_fb, slice0, slice1, slice2);
    SLICE_SUBCASE(case3, array_ls_hb, slice0, slice1, slice2);
    SLICE_SUBCASE(case3, array_ls_db, slice0, slice1, slice2);
    #endif
}

TEST_CASE("slice(case4)" * doctest::test_suite("view::slice"))
{
    #if !defined(NMTOOLS_TESTING_GENERIC_NDARRAY)
    SLICE_SUBCASE(case4,   array, slice0, slice1, slice2);
    SLICE_SUBCASE(case4, array_a, slice0, slice1, slice2);
    SLICE_SUBCASE(case4, array_f, slice0, slice1, slice2);
    SLICE_SUBCASE(case4, array_d, slice0, slice1, slice2);
    SLICE_SUBCASE(case4, array_h, slice0, slice1, slice2);

    #else
    SLICE_SUBCASE(case4, array_cs_fb, slice0, slice1, slice2);
    SLICE_SUBCASE(case4, array_cs_hb, slice0, slice1, slice2);
    SLICE_SUBCASE(case4, array_cs_db, slice0, slice1, slice2);

    SLICE_SUBCASE(case4, array_fs_fb, slice0, slice1, slice2);
    SLICE_SUBCASE(case4, array_fs_hb, slice0, slice1, slice2);
    SLICE_SUBCASE(case4, array_fs_db, slice0, slice1, slice2);

    SLICE_SUBCASE(case4, array_hs_fb, slice0, slice1, slice2);
    SLICE_SUBCASE(case4, array_hs_hb, slice0, slice1, slice2);
    SLICE_SUBCASE(case4, array_hs_db, slice0, slice1, slice2);

    SLICE_SUBCASE(case4, array_ds_fb, slice0, slice1, slice2);
    SLICE_SUBCASE(case4, array_ds_hb, slice0, slice1, slice2);
    SLICE_SUBCASE(case4, array_ds_db, slice0, slice1, slice2);

    SLICE_SUBCASE(case4, array_ls_fb, slice0, slice1, slice2);
    SLICE_SUBCASE(case4, array_ls_hb, slice0, slice1, slice2);
    SLICE_SUBCASE(case4, array_ls_db, slice0, slice1, slice2);
    #endif
}

TEST_CASE("slice(case5)" * doctest::test_suite("view::slice"))
{
    #if !defined(NMTOOLS_TESTING_GENERIC_NDARRAY)
    SLICE_SUBCASE(case5,   array, slice0, slice1, slice2);
    SLICE_SUBCASE(case5, array_a, slice0, slice1, slice2);
    SLICE_SUBCASE(case5, array_f, slice0, slice1, slice2);
    SLICE_SUBCASE(case5, array_d, slice0, slice1, slice2);
    SLICE_SUBCASE(case5, array_h, slice0, slice1, slice2);

    #else
    SLICE_SUBCASE(case5, array_cs_fb, slice0, slice1, slice2);
    SLICE_SUBCASE(case5, array_cs_hb, slice0, slice1, slice2);
    SLICE_SUBCASE(case5, array_cs_db, slice0, slice1, slice2);

    SLICE_SUBCASE(case5, array_fs_fb, slice0, slice1, slice2);
    SLICE_SUBCASE(case5, array_fs_hb, slice0, slice1, slice2);
    SLICE_SUBCASE(case5, array_fs_db, slice0, slice1, slice2);

    SLICE_SUBCASE(case5, array_hs_fb, slice0, slice1, slice2);
    SLICE_SUBCASE(case5, array_hs_hb, slice0, slice1, slice2);
    SLICE_SUBCASE(case5, array_hs_db, slice0, slice1, slice2);

    SLICE_SUBCASE(case5, array_ds_fb, slice0, slice1, slice2);
    SLICE_SUBCASE(case5, array_ds_hb, slice0, slice1, slice2);
    SLICE_SUBCASE(case5, array_ds_db, slice0, slice1, slice2);

    SLICE_SUBCASE(case5, array_ls_fb, slice0, slice1, slice2);
    SLICE_SUBCASE(case5, array_ls_hb, slice0, slice1, slice2);
    SLICE_SUBCASE(case5, array_ls_db, slice0, slice1, slice2);
    #endif
}

TEST_CASE("slice(case6)" * doctest::test_suite("view::slice"))
{
    #if !defined(NMTOOLS_TESTING_GENERIC_NDARRAY)
    SLICE_SUBCASE(case6,   array, slice0, slice1, slice2);
    SLICE_SUBCASE(case6, array_a, slice0, slice1, slice2);
    SLICE_SUBCASE(case6, array_f, slice0, slice1, slice2);
    SLICE_SUBCASE(case6, array_d, slice0, slice1, slice2);
    SLICE_SUBCASE(case6, array_h, slice0, slice1, slice2);

    #else
    SLICE_SUBCASE(case6, array_cs_fb, slice0, slice1, slice2);
    SLICE_SUBCASE(case6, array_cs_hb, slice0, slice1, slice2);
    SLICE_SUBCASE(case6, array_cs_db, slice0, slice1, slice2);

    SLICE_SUBCASE(case6, array_fs_fb, slice0, slice1, slice2);
    SLICE_SUBCASE(case6, array_fs_hb, slice0, slice1, slice2);
    SLICE_SUBCASE(case6, array_fs_db, slice0, slice1, slice2);

    SLICE_SUBCASE(case6, array_hs_fb, slice0, slice1, slice2);
    SLICE_SUBCASE(case6, array_hs_hb, slice0, slice1, slice2);
    SLICE_SUBCASE(case6, array_hs_db, slice0, slice1, slice2);

    SLICE_SUBCASE(case6, array_ds_fb, slice0, slice1, slice2);
    SLICE_SUBCASE(case6, array_ds_hb, slice0, slice1, slice2);
    SLICE_SUBCASE(case6, array_ds_db, slice0, slice1, slice2);

    SLICE_SUBCASE(case6, array_ls_fb, slice0, slice1, slice2);
    SLICE_SUBCASE(case6, array_ls_hb, slice0, slice1, slice2);
    SLICE_SUBCASE(case6, array_ls_db, slice0, slice1, slice2);
    #endif
}

TEST_CASE("slice(case7)" * doctest::test_suite("view::slice"))
{
    #if !defined(NMTOOLS_TESTING_GENERIC_NDARRAY)
    SLICE_SUBCASE(case7,   array, slice0, slice1, slice2);
    SLICE_SUBCASE(case7, array_a, slice0, slice1, slice2);
    SLICE_SUBCASE(case7, array_f, slice0, slice1, slice2);
    SLICE_SUBCASE(case7, array_d, slice0, slice1, slice2);
    SLICE_SUBCASE(case7, array_h, slice0, slice1, slice2);

    #else
    SLICE_SUBCASE(case7, array_cs_fb, slice0, slice1, slice2);
    SLICE_SUBCASE(case7, array_cs_hb, slice0, slice1, slice2);
    SLICE_SUBCASE(case7, array_cs_db, slice0, slice1, slice2);

    SLICE_SUBCASE(case7, array_fs_fb, slice0, slice1, slice2);
    SLICE_SUBCASE(case7, array_fs_hb, slice0, slice1, slice2);
    SLICE_SUBCASE(case7, array_fs_db, slice0, slice1, slice2);

    SLICE_SUBCASE(case7, array_hs_fb, slice0, slice1, slice2);
    SLICE_SUBCASE(case7, array_hs_hb, slice0, slice1, slice2);
    SLICE_SUBCASE(case7, array_hs_db, slice0, slice1, slice2);

    SLICE_SUBCASE(case7, array_ds_fb, slice0, slice1, slice2);
    SLICE_SUBCASE(case7, array_ds_hb, slice0, slice1, slice2);
    SLICE_SUBCASE(case7, array_ds_db, slice0, slice1, slice2);

    SLICE_SUBCASE(case7, array_ls_fb, slice0, slice1, slice2);
    SLICE_SUBCASE(case7, array_ls_hb, slice0, slice1, slice2);
    SLICE_SUBCASE(case7, array_ls_db, slice0, slice1, slice2);
    #endif
}

TEST_CASE("slice(case8)" * doctest::test_suite("view::slice"))
{
    #if !defined(NMTOOLS_TESTING_GENERIC_NDARRAY)
    SLICE_SUBCASE(case8,   array, slice0, slice1, slice2);
    SLICE_SUBCASE(case8, array_a, slice0, slice1, slice2);
    SLICE_SUBCASE(case8, array_f, slice0, slice1, slice2);
    SLICE_SUBCASE(case8, array_d, slice0, slice1, slice2);
    SLICE_SUBCASE(case8, array_h, slice0, slice1, slice2);

    #else
    SLICE_SUBCASE(case8, array_cs_fb, slice0, slice1, slice2);
    SLICE_SUBCASE(case8, array_cs_hb, slice0, slice1, slice2);
    SLICE_SUBCASE(case8, array_cs_db, slice0, slice1, slice2);

    SLICE_SUBCASE(case8, array_fs_fb, slice0, slice1, slice2);
    SLICE_SUBCASE(case8, array_fs_hb, slice0, slice1, slice2);
    SLICE_SUBCASE(case8, array_fs_db, slice0, slice1, slice2);

    SLICE_SUBCASE(case8, array_hs_fb, slice0, slice1, slice2);
    SLICE_SUBCASE(case8, array_hs_hb, slice0, slice1, slice2);
    SLICE_SUBCASE(case8, array_hs_db, slice0, slice1, slice2);

    SLICE_SUBCASE(case8, array_ds_fb, slice0, slice1, slice2);
    SLICE_SUBCASE(case8, array_ds_hb, slice0, slice1, slice2);
    SLICE_SUBCASE(case8, array_ds_db, slice0, slice1, slice2);

    SLICE_SUBCASE(case8, array_ls_fb, slice0, slice1, slice2);
    SLICE_SUBCASE(case8, array_ls_hb, slice0, slice1, slice2);
    SLICE_SUBCASE(case8, array_ls_db, slice0, slice1, slice2);
    #endif
}

TEST_CASE("slice(case9)" * doctest::test_suite("view::slice"))
{
    #if !defined(NMTOOLS_TESTING_GENERIC_NDARRAY)
    SLICE_SUBCASE(case9,   array, slice0, slice1, slice2);
    SLICE_SUBCASE(case9, array_a, slice0, slice1, slice2);
    SLICE_SUBCASE(case9, array_f, slice0, slice1, slice2);
    SLICE_SUBCASE(case9, array_d, slice0, slice1, slice2);
    SLICE_SUBCASE(case9, array_h, slice0, slice1, slice2);

    #else
    SLICE_SUBCASE(case9, array_cs_fb, slice0, slice1, slice2);
    SLICE_SUBCASE(case9, array_cs_hb, slice0, slice1, slice2);
    SLICE_SUBCASE(case9, array_cs_db, slice0, slice1, slice2);

    SLICE_SUBCASE(case9, array_fs_fb, slice0, slice1, slice2);
    SLICE_SUBCASE(case9, array_fs_hb, slice0, slice1, slice2);
    SLICE_SUBCASE(case9, array_fs_db, slice0, slice1, slice2);

    SLICE_SUBCASE(case9, array_hs_fb, slice0, slice1, slice2);
    SLICE_SUBCASE(case9, array_hs_hb, slice0, slice1, slice2);
    SLICE_SUBCASE(case9, array_hs_db, slice0, slice1, slice2);

    SLICE_SUBCASE(case9, array_ds_fb, slice0, slice1, slice2);
    SLICE_SUBCASE(case9, array_ds_hb, slice0, slice1, slice2);
    SLICE_SUBCASE(case9, array_ds_db, slice0, slice1, slice2);

    SLICE_SUBCASE(case9, array_ls_fb, slice0, slice1, slice2);
    SLICE_SUBCASE(case9, array_ls_hb, slice0, slice1, slice2);
    SLICE_SUBCASE(case9, array_ls_db, slice0, slice1, slice2);
    #endif
}

TEST_CASE("slice(case10)" * doctest::test_suite("view::slice"))
{
    #if !defined(NMTOOLS_TESTING_GENERIC_NDARRAY)
    SLICE_SUBCASE(case10,   array, slice0, slice1, slice2);
    SLICE_SUBCASE(case10, array_a, slice0, slice1, slice2);
    SLICE_SUBCASE(case10, array_f, slice0, slice1, slice2);
    SLICE_SUBCASE(case10, array_d, slice0, slice1, slice2);
    SLICE_SUBCASE(case10, array_h, slice0, slice1, slice2);

    #else
    SLICE_SUBCASE(case10, array_cs_fb, slice0, slice1, slice2);
    SLICE_SUBCASE(case10, array_cs_hb, slice0, slice1, slice2);
    SLICE_SUBCASE(case10, array_cs_db, slice0, slice1, slice2);

    SLICE_SUBCASE(case10, array_fs_fb, slice0, slice1, slice2);
    SLICE_SUBCASE(case10, array_fs_hb, slice0, slice1, slice2);
    SLICE_SUBCASE(case10, array_fs_db, slice0, slice1, slice2);

    SLICE_SUBCASE(case10, array_hs_fb, slice0, slice1, slice2);
    SLICE_SUBCASE(case10, array_hs_hb, slice0, slice1, slice2);
    SLICE_SUBCASE(case10, array_hs_db, slice0, slice1, slice2);

    SLICE_SUBCASE(case10, array_ds_fb, slice0, slice1, slice2);
    SLICE_SUBCASE(case10, array_ds_hb, slice0, slice1, slice2);
    SLICE_SUBCASE(case10, array_ds_db, slice0, slice1, slice2);

    SLICE_SUBCASE(case10, array_ls_fb, slice0, slice1, slice2);
    SLICE_SUBCASE(case10, array_ls_hb, slice0, slice1, slice2);
    SLICE_SUBCASE(case10, array_ls_db, slice0, slice1, slice2);
    #endif
}

TEST_CASE("slice(case11)" * doctest::test_suite("view::slice"))
{
    #if !defined(NMTOOLS_TESTING_GENERIC_NDARRAY)
    SLICE_SUBCASE(case11,   array, slice0, slice1);
    SLICE_SUBCASE(case11, array_a, slice0, slice1);
    SLICE_SUBCASE(case11, array_f, slice0, slice1);
    SLICE_SUBCASE(case11, array_d, slice0, slice1);
    SLICE_SUBCASE(case11, array_h, slice0, slice1);

    #else
    SLICE_SUBCASE(case11, array_cs_fb, slice0, slice1);
    SLICE_SUBCASE(case11, array_cs_hb, slice0, slice1);
    SLICE_SUBCASE(case11, array_cs_db, slice0, slice1);

    SLICE_SUBCASE(case11, array_fs_fb, slice0, slice1);
    SLICE_SUBCASE(case11, array_fs_hb, slice0, slice1);
    SLICE_SUBCASE(case11, array_fs_db, slice0, slice1);

    SLICE_SUBCASE(case11, array_hs_fb, slice0, slice1);
    SLICE_SUBCASE(case11, array_hs_hb, slice0, slice1);
    SLICE_SUBCASE(case11, array_hs_db, slice0, slice1);

    SLICE_SUBCASE(case11, array_ds_fb, slice0, slice1);
    SLICE_SUBCASE(case11, array_ds_hb, slice0, slice1);
    SLICE_SUBCASE(case11, array_ds_db, slice0, slice1);

    SLICE_SUBCASE(case11, array_ls_fb, slice0, slice1);
    SLICE_SUBCASE(case11, array_ls_hb, slice0, slice1);
    SLICE_SUBCASE(case11, array_ls_db, slice0, slice1);
    #endif
}

TEST_CASE("slice(case12)" * doctest::test_suite("view::slice"))
{
    #if !defined(NMTOOLS_TESTING_GENERIC_NDARRAY)
    SLICE_SUBCASE(case12,   array, slice0, slice1);
    SLICE_SUBCASE(case12, array_a, slice0, slice1);
    SLICE_SUBCASE(case12, array_f, slice0, slice1);
    SLICE_SUBCASE(case12, array_d, slice0, slice1);
    SLICE_SUBCASE(case12, array_h, slice0, slice1);

    #else
    SLICE_SUBCASE(case12, array_cs_fb, slice0, slice1);
    SLICE_SUBCASE(case12, array_cs_hb, slice0, slice1);
    SLICE_SUBCASE(case12, array_cs_db, slice0, slice1);

    SLICE_SUBCASE(case12, array_fs_fb, slice0, slice1);
    SLICE_SUBCASE(case12, array_fs_hb, slice0, slice1);
    SLICE_SUBCASE(case12, array_fs_db, slice0, slice1);

    SLICE_SUBCASE(case12, array_hs_fb, slice0, slice1);
    SLICE_SUBCASE(case12, array_hs_hb, slice0, slice1);
    SLICE_SUBCASE(case12, array_hs_db, slice0, slice1);

    SLICE_SUBCASE(case12, array_ds_fb, slice0, slice1);
    SLICE_SUBCASE(case12, array_ds_hb, slice0, slice1);
    SLICE_SUBCASE(case12, array_ds_db, slice0, slice1);

    SLICE_SUBCASE(case12, array_ls_fb, slice0, slice1);
    SLICE_SUBCASE(case12, array_ls_hb, slice0, slice1);
    SLICE_SUBCASE(case12, array_ls_db, slice0, slice1);
    #endif
}

TEST_CASE("slice(case13)" * doctest::test_suite("view::slice"))
{
    #if !defined(NMTOOLS_TESTING_GENERIC_NDARRAY)
    SLICE_SUBCASE(case13,   array, slice0, slice1);
    SLICE_SUBCASE(case13, array_a, slice0, slice1);
    SLICE_SUBCASE(case13, array_f, slice0, slice1);
    SLICE_SUBCASE(case13, array_d, slice0, slice1);
    SLICE_SUBCASE(case13, array_h, slice0, slice1);

    #else
    SLICE_SUBCASE(case13, array_cs_fb, slice0, slice1);
    SLICE_SUBCASE(case13, array_cs_hb, slice0, slice1);
    SLICE_SUBCASE(case13, array_cs_db, slice0, slice1);

    SLICE_SUBCASE(case13, array_fs_fb, slice0, slice1);
    SLICE_SUBCASE(case13, array_fs_hb, slice0, slice1);
    SLICE_SUBCASE(case13, array_fs_db, slice0, slice1);

    SLICE_SUBCASE(case13, array_hs_fb, slice0, slice1);
    SLICE_SUBCASE(case13, array_hs_hb, slice0, slice1);
    SLICE_SUBCASE(case13, array_hs_db, slice0, slice1);

    SLICE_SUBCASE(case13, array_ds_fb, slice0, slice1);
    SLICE_SUBCASE(case13, array_ds_hb, slice0, slice1);
    SLICE_SUBCASE(case13, array_ds_db, slice0, slice1);

    SLICE_SUBCASE(case13, array_ls_fb, slice0, slice1);
    SLICE_SUBCASE(case13, array_ls_hb, slice0, slice1);
    SLICE_SUBCASE(case13, array_ls_db, slice0, slice1);
    #endif
}

TEST_CASE("slice(case14)" * doctest::test_suite("view::slice"))
{
    #if !defined(NMTOOLS_TESTING_GENERIC_NDARRAY)
    SLICE_SUBCASE(case14,   array, slice0, slice1);
    SLICE_SUBCASE(case14, array_a, slice0, slice1);
    SLICE_SUBCASE(case14, array_f, slice0, slice1);
    SLICE_SUBCASE(case14, array_d, slice0, slice1);
    SLICE_SUBCASE(case14, array_h, slice0, slice1);

    #else
    SLICE_SUBCASE(case14, array_cs_fb, slice0, slice1);
    SLICE_SUBCASE(case14, array_cs_hb, slice0, slice1);
    SLICE_SUBCASE(case14, array_cs_db, slice0, slice1);

    SLICE_SUBCASE(case14, array_fs_fb, slice0, slice1);
    SLICE_SUBCASE(case14, array_fs_hb, slice0, slice1);
    SLICE_SUBCASE(case14, array_fs_db, slice0, slice1);

    SLICE_SUBCASE(case14, array_hs_fb, slice0, slice1);
    SLICE_SUBCASE(case14, array_hs_hb, slice0, slice1);
    SLICE_SUBCASE(case14, array_hs_db, slice0, slice1);

    SLICE_SUBCASE(case14, array_ds_fb, slice0, slice1);
    SLICE_SUBCASE(case14, array_ds_hb, slice0, slice1);
    SLICE_SUBCASE(case14, array_ds_db, slice0, slice1);

    SLICE_SUBCASE(case14, array_ls_fb, slice0, slice1);
    SLICE_SUBCASE(case14, array_ls_hb, slice0, slice1);
    SLICE_SUBCASE(case14, array_ls_db, slice0, slice1);
    #endif
}

TEST_CASE("slice(case15)" * doctest::test_suite("view::slice"))
{
    #if !defined(NMTOOLS_TESTING_GENERIC_NDARRAY)
    SLICE_SUBCASE(case15,   array, slice0, slice1);
    SLICE_SUBCASE(case15, array_a, slice0, slice1);
    SLICE_SUBCASE(case15, array_f, slice0, slice1);
    SLICE_SUBCASE(case15, array_d, slice0, slice1);
    SLICE_SUBCASE(case15, array_h, slice0, slice1);

    #else
    SLICE_SUBCASE(case15, array_cs_fb, slice0, slice1);
    SLICE_SUBCASE(case15, array_cs_hb, slice0, slice1);
    SLICE_SUBCASE(case15, array_cs_db, slice0, slice1);

    SLICE_SUBCASE(case15, array_fs_fb, slice0, slice1);
    SLICE_SUBCASE(case15, array_fs_hb, slice0, slice1);
    SLICE_SUBCASE(case15, array_fs_db, slice0, slice1);

    SLICE_SUBCASE(case15, array_hs_fb, slice0, slice1);
    SLICE_SUBCASE(case15, array_hs_hb, slice0, slice1);
    SLICE_SUBCASE(case15, array_hs_db, slice0, slice1);

    SLICE_SUBCASE(case15, array_ds_fb, slice0, slice1);
    SLICE_SUBCASE(case15, array_ds_hb, slice0, slice1);
    SLICE_SUBCASE(case15, array_ds_db, slice0, slice1);

    SLICE_SUBCASE(case15, array_ls_fb, slice0, slice1);
    SLICE_SUBCASE(case15, array_ls_hb, slice0, slice1);
    SLICE_SUBCASE(case15, array_ls_db, slice0, slice1);
    #endif
}

TEST_CASE("slice(case16)" * doctest::test_suite("view::slice"))
{
    #if !defined(NMTOOLS_TESTING_GENERIC_NDARRAY)
    SLICE_SUBCASE(case16,   array, slice0, slice1);
    SLICE_SUBCASE(case16, array_a, slice0, slice1);
    SLICE_SUBCASE(case16, array_f, slice0, slice1);
    SLICE_SUBCASE(case16, array_d, slice0, slice1);
    SLICE_SUBCASE(case16, array_h, slice0, slice1);

    #else
    SLICE_SUBCASE(case16, array_cs_fb, slice0, slice1);
    SLICE_SUBCASE(case16, array_cs_hb, slice0, slice1);
    SLICE_SUBCASE(case16, array_cs_db, slice0, slice1);

    SLICE_SUBCASE(case16, array_fs_fb, slice0, slice1);
    SLICE_SUBCASE(case16, array_fs_hb, slice0, slice1);
    SLICE_SUBCASE(case16, array_fs_db, slice0, slice1);

    SLICE_SUBCASE(case16, array_hs_fb, slice0, slice1);
    SLICE_SUBCASE(case16, array_hs_hb, slice0, slice1);
    SLICE_SUBCASE(case16, array_hs_db, slice0, slice1);

    SLICE_SUBCASE(case16, array_ds_fb, slice0, slice1);
    SLICE_SUBCASE(case16, array_ds_hb, slice0, slice1);
    SLICE_SUBCASE(case16, array_ds_db, slice0, slice1);

    SLICE_SUBCASE(case16, array_ls_fb, slice0, slice1);
    SLICE_SUBCASE(case16, array_ls_hb, slice0, slice1);
    SLICE_SUBCASE(case16, array_ls_db, slice0, slice1);
    #endif
}

TEST_CASE("slice(case17)" * doctest::test_suite("view::slice"))
{
    #if !defined(NMTOOLS_TESTING_GENERIC_NDARRAY)
    SLICE_SUBCASE(case17,   array, slice0, slice1);
    SLICE_SUBCASE(case17, array_a, slice0, slice1);
    SLICE_SUBCASE(case17, array_f, slice0, slice1);
    SLICE_SUBCASE(case17, array_d, slice0, slice1);
    SLICE_SUBCASE(case17, array_h, slice0, slice1);

    #else
    SLICE_SUBCASE(case17, array_cs_fb, slice0, slice1);
    SLICE_SUBCASE(case17, array_cs_hb, slice0, slice1);
    SLICE_SUBCASE(case17, array_cs_db, slice0, slice1);

    SLICE_SUBCASE(case17, array_fs_fb, slice0, slice1);
    SLICE_SUBCASE(case17, array_fs_hb, slice0, slice1);
    SLICE_SUBCASE(case17, array_fs_db, slice0, slice1);

    SLICE_SUBCASE(case17, array_hs_fb, slice0, slice1);
    SLICE_SUBCASE(case17, array_hs_hb, slice0, slice1);
    SLICE_SUBCASE(case17, array_hs_db, slice0, slice1);

    SLICE_SUBCASE(case17, array_ds_fb, slice0, slice1);
    SLICE_SUBCASE(case17, array_ds_hb, slice0, slice1);
    SLICE_SUBCASE(case17, array_ds_db, slice0, slice1);

    SLICE_SUBCASE(case17, array_ls_fb, slice0, slice1);
    SLICE_SUBCASE(case17, array_ls_hb, slice0, slice1);
    SLICE_SUBCASE(case17, array_ls_db, slice0, slice1);
    #endif
}

TEST_CASE("slice(case18)" * doctest::test_suite("view::slice"))
{
    #if !defined(NMTOOLS_TESTING_GENERIC_NDARRAY)
    SLICE_SUBCASE(case18,   array, slice0, slice1);
    SLICE_SUBCASE(case18, array_a, slice0, slice1);
    SLICE_SUBCASE(case18, array_f, slice0, slice1);
    SLICE_SUBCASE(case18, array_d, slice0, slice1);
    SLICE_SUBCASE(case18, array_h, slice0, slice1);

    #else
    SLICE_SUBCASE(case18, array_cs_fb, slice0, slice1);
    SLICE_SUBCASE(case18, array_cs_hb, slice0, slice1);
    SLICE_SUBCASE(case18, array_cs_db, slice0, slice1);

    SLICE_SUBCASE(case18, array_fs_fb, slice0, slice1);
    SLICE_SUBCASE(case18, array_fs_hb, slice0, slice1);
    SLICE_SUBCASE(case18, array_fs_db, slice0, slice1);

    SLICE_SUBCASE(case18, array_hs_fb, slice0, slice1);
    SLICE_SUBCASE(case18, array_hs_hb, slice0, slice1);
    SLICE_SUBCASE(case18, array_hs_db, slice0, slice1);

    SLICE_SUBCASE(case18, array_ds_fb, slice0, slice1);
    SLICE_SUBCASE(case18, array_ds_hb, slice0, slice1);
    SLICE_SUBCASE(case18, array_ds_db, slice0, slice1);

    SLICE_SUBCASE(case18, array_ls_fb, slice0, slice1);
    SLICE_SUBCASE(case18, array_ls_hb, slice0, slice1);
    SLICE_SUBCASE(case18, array_ls_db, slice0, slice1);
    #endif
}

TEST_CASE("slice(case19)" * doctest::test_suite("view::slice"))
{
    #if !defined(NMTOOLS_TESTING_GENERIC_NDARRAY)
    SLICE_SUBCASE(case19,   array, slice0, slice1);
    SLICE_SUBCASE(case19, array_a, slice0, slice1);
    SLICE_SUBCASE(case19, array_f, slice0, slice1);
    SLICE_SUBCASE(case19, array_d, slice0, slice1);
    SLICE_SUBCASE(case19, array_h, slice0, slice1);

    #else
    SLICE_SUBCASE(case19, array_cs_fb, slice0, slice1);
    SLICE_SUBCASE(case19, array_cs_hb, slice0, slice1);
    SLICE_SUBCASE(case19, array_cs_db, slice0, slice1);

    SLICE_SUBCASE(case19, array_fs_fb, slice0, slice1);
    SLICE_SUBCASE(case19, array_fs_hb, slice0, slice1);
    SLICE_SUBCASE(case19, array_fs_db, slice0, slice1);

    SLICE_SUBCASE(case19, array_hs_fb, slice0, slice1);
    SLICE_SUBCASE(case19, array_hs_hb, slice0, slice1);
    SLICE_SUBCASE(case19, array_hs_db, slice0, slice1);

    SLICE_SUBCASE(case19, array_ds_fb, slice0, slice1);
    SLICE_SUBCASE(case19, array_ds_hb, slice0, slice1);
    SLICE_SUBCASE(case19, array_ds_db, slice0, slice1);

    SLICE_SUBCASE(case19, array_ls_fb, slice0, slice1);
    SLICE_SUBCASE(case19, array_ls_hb, slice0, slice1);
    SLICE_SUBCASE(case19, array_ls_db, slice0, slice1);
    #endif
}

TEST_CASE("slice(case20)" * doctest::test_suite("view::slice"))
{
    #if !defined(NMTOOLS_TESTING_GENERIC_NDARRAY)
    SLICE_SUBCASE(case20,   array, slice0, slice1);
    SLICE_SUBCASE(case20, array_a, slice0, slice1);
    SLICE_SUBCASE(case20, array_f, slice0, slice1);
    SLICE_SUBCASE(case20, array_d, slice0, slice1);
    SLICE_SUBCASE(case20, array_h, slice0, slice1);

    #else
    SLICE_SUBCASE(case20, array_cs_fb, slice0, slice1);
    SLICE_SUBCASE(case20, array_cs_hb, slice0, slice1);
    SLICE_SUBCASE(case20, array_cs_db, slice0, slice1);

    SLICE_SUBCASE(case20, array_fs_fb, slice0, slice1);
    SLICE_SUBCASE(case20, array_fs_hb, slice0, slice1);
    SLICE_SUBCASE(case20, array_fs_db, slice0, slice1);

    SLICE_SUBCASE(case20, array_hs_fb, slice0, slice1);
    SLICE_SUBCASE(case20, array_hs_hb, slice0, slice1);
    SLICE_SUBCASE(case20, array_hs_db, slice0, slice1);

    SLICE_SUBCASE(case20, array_ds_fb, slice0, slice1);
    SLICE_SUBCASE(case20, array_ds_hb, slice0, slice1);
    SLICE_SUBCASE(case20, array_ds_db, slice0, slice1);

    SLICE_SUBCASE(case20, array_ls_fb, slice0, slice1);
    SLICE_SUBCASE(case20, array_ls_hb, slice0, slice1);
    SLICE_SUBCASE(case20, array_ls_db, slice0, slice1);
    #endif
}

TEST_CASE("slice(case21)" * doctest::test_suite("view::slice"))
{
    #if !defined(NMTOOLS_TESTING_GENERIC_NDARRAY)
    SLICE_SUBCASE(case21,   array, slice0, slice1);
    SLICE_SUBCASE(case21, array_a, slice0, slice1);
    SLICE_SUBCASE(case21, array_f, slice0, slice1);
    SLICE_SUBCASE(case21, array_d, slice0, slice1);
    SLICE_SUBCASE(case21, array_h, slice0, slice1);

    #else
    SLICE_SUBCASE(case21, array_cs_fb, slice0, slice1);
    SLICE_SUBCASE(case21, array_cs_hb, slice0, slice1);
    SLICE_SUBCASE(case21, array_cs_db, slice0, slice1);

    SLICE_SUBCASE(case21, array_fs_fb, slice0, slice1);
    SLICE_SUBCASE(case21, array_fs_hb, slice0, slice1);
    SLICE_SUBCASE(case21, array_fs_db, slice0, slice1);

    SLICE_SUBCASE(case21, array_hs_fb, slice0, slice1);
    SLICE_SUBCASE(case21, array_hs_hb, slice0, slice1);
    SLICE_SUBCASE(case21, array_hs_db, slice0, slice1);

    SLICE_SUBCASE(case21, array_ds_fb, slice0, slice1);
    SLICE_SUBCASE(case21, array_ds_hb, slice0, slice1);
    SLICE_SUBCASE(case21, array_ds_db, slice0, slice1);

    SLICE_SUBCASE(case21, array_ls_fb, slice0, slice1);
    SLICE_SUBCASE(case21, array_ls_hb, slice0, slice1);
    SLICE_SUBCASE(case21, array_ls_db, slice0, slice1);
    #endif
}

TEST_CASE("slice(case22)" * doctest::test_suite("view::slice"))
{
    #if !defined(NMTOOLS_TESTING_GENERIC_NDARRAY)
    SLICE_SUBCASE(case22,   array, slice0, slice1);
    SLICE_SUBCASE(case22, array_a, slice0, slice1);
    SLICE_SUBCASE(case22, array_f, slice0, slice1);
    SLICE_SUBCASE(case22, array_d, slice0, slice1);
    SLICE_SUBCASE(case22, array_h, slice0, slice1);

    #else
    SLICE_SUBCASE(case22, array_cs_fb, slice0, slice1);
    SLICE_SUBCASE(case22, array_cs_hb, slice0, slice1);
    SLICE_SUBCASE(case22, array_cs_db, slice0, slice1);

    SLICE_SUBCASE(case22, array_fs_fb, slice0, slice1);
    SLICE_SUBCASE(case22, array_fs_hb, slice0, slice1);
    SLICE_SUBCASE(case22, array_fs_db, slice0, slice1);

    SLICE_SUBCASE(case22, array_hs_fb, slice0, slice1);
    SLICE_SUBCASE(case22, array_hs_hb, slice0, slice1);
    SLICE_SUBCASE(case22, array_hs_db, slice0, slice1);

    SLICE_SUBCASE(case22, array_ds_fb, slice0, slice1);
    SLICE_SUBCASE(case22, array_ds_hb, slice0, slice1);
    SLICE_SUBCASE(case22, array_ds_db, slice0, slice1);

    SLICE_SUBCASE(case22, array_ls_fb, slice0, slice1);
    SLICE_SUBCASE(case22, array_ls_hb, slice0, slice1);
    SLICE_SUBCASE(case22, array_ls_db, slice0, slice1);
    #endif
}

TEST_CASE("slice(case23)" * doctest::test_suite("view::slice"))
{
    #if !defined(NMTOOLS_TESTING_GENERIC_NDARRAY)
    SLICE_SUBCASE(case23,   array, slice0, slice1);
    SLICE_SUBCASE(case23, array_a, slice0, slice1);
    SLICE_SUBCASE(case23, array_f, slice0, slice1);
    SLICE_SUBCASE(case23, array_d, slice0, slice1);
    SLICE_SUBCASE(case23, array_h, slice0, slice1);

    #else
    SLICE_SUBCASE(case23, array_cs_fb, slice0, slice1);
    SLICE_SUBCASE(case23, array_cs_hb, slice0, slice1);
    SLICE_SUBCASE(case23, array_cs_db, slice0, slice1);

    SLICE_SUBCASE(case23, array_fs_fb, slice0, slice1);
    SLICE_SUBCASE(case23, array_fs_hb, slice0, slice1);
    SLICE_SUBCASE(case23, array_fs_db, slice0, slice1);

    SLICE_SUBCASE(case23, array_hs_fb, slice0, slice1);
    SLICE_SUBCASE(case23, array_hs_hb, slice0, slice1);
    SLICE_SUBCASE(case23, array_hs_db, slice0, slice1);

    SLICE_SUBCASE(case23, array_ds_fb, slice0, slice1);
    SLICE_SUBCASE(case23, array_ds_hb, slice0, slice1);
    SLICE_SUBCASE(case23, array_ds_db, slice0, slice1);

    SLICE_SUBCASE(case23, array_ls_fb, slice0, slice1);
    SLICE_SUBCASE(case23, array_ls_hb, slice0, slice1);
    SLICE_SUBCASE(case23, array_ls_db, slice0, slice1);
    #endif
}

TEST_CASE("slice(case24)" * doctest::test_suite("view::slice"))
{
    #if !defined(NMTOOLS_TESTING_GENERIC_NDARRAY)
    SLICE_SUBCASE(case24,   array, slice0, slice1);
    SLICE_SUBCASE(case24, array_a, slice0, slice1);
    SLICE_SUBCASE(case24, array_f, slice0, slice1);
    SLICE_SUBCASE(case24, array_d, slice0, slice1);
    SLICE_SUBCASE(case24, array_h, slice0, slice1);

    #else
    SLICE_SUBCASE(case24, array_cs_fb, slice0, slice1);
    SLICE_SUBCASE(case24, array_cs_hb, slice0, slice1);
    SLICE_SUBCASE(case24, array_cs_db, slice0, slice1);

    SLICE_SUBCASE(case24, array_fs_fb, slice0, slice1);
    SLICE_SUBCASE(case24, array_fs_hb, slice0, slice1);
    SLICE_SUBCASE(case24, array_fs_db, slice0, slice1);

    SLICE_SUBCASE(case24, array_hs_fb, slice0, slice1);
    SLICE_SUBCASE(case24, array_hs_hb, slice0, slice1);
    SLICE_SUBCASE(case24, array_hs_db, slice0, slice1);

    SLICE_SUBCASE(case24, array_ds_fb, slice0, slice1);
    SLICE_SUBCASE(case24, array_ds_hb, slice0, slice1);
    SLICE_SUBCASE(case24, array_ds_db, slice0, slice1);

    SLICE_SUBCASE(case24, array_ls_fb, slice0, slice1);
    SLICE_SUBCASE(case24, array_ls_hb, slice0, slice1);
    SLICE_SUBCASE(case24, array_ls_db, slice0, slice1);
    #endif
}

TEST_CASE("slice(case25)" * doctest::test_suite("view::slice"))
{
    #if !defined(NMTOOLS_TESTING_GENERIC_NDARRAY)
    SLICE_SUBCASE(case25,   array, slice0, slice1);
    SLICE_SUBCASE(case25, array_a, slice0, slice1);
    SLICE_SUBCASE(case25, array_f, slice0, slice1);
    SLICE_SUBCASE(case25, array_d, slice0, slice1);
    SLICE_SUBCASE(case25, array_h, slice0, slice1);

    #else
    SLICE_SUBCASE(case25, array_cs_fb, slice0, slice1);
    SLICE_SUBCASE(case25, array_cs_hb, slice0, slice1);
    SLICE_SUBCASE(case25, array_cs_db, slice0, slice1);

    SLICE_SUBCASE(case25, array_fs_fb, slice0, slice1);
    SLICE_SUBCASE(case25, array_fs_hb, slice0, slice1);
    SLICE_SUBCASE(case25, array_fs_db, slice0, slice1);

    SLICE_SUBCASE(case25, array_hs_fb, slice0, slice1);
    SLICE_SUBCASE(case25, array_hs_hb, slice0, slice1);
    SLICE_SUBCASE(case25, array_hs_db, slice0, slice1);

    SLICE_SUBCASE(case25, array_ds_fb, slice0, slice1);
    SLICE_SUBCASE(case25, array_ds_hb, slice0, slice1);
    SLICE_SUBCASE(case25, array_ds_db, slice0, slice1);

    SLICE_SUBCASE(case25, array_ls_fb, slice0, slice1);
    SLICE_SUBCASE(case25, array_ls_hb, slice0, slice1);
    SLICE_SUBCASE(case25, array_ls_db, slice0, slice1);
    #endif
}

TEST_CASE("slice(case26)" * doctest::test_suite("view::slice"))
{
    #if !defined(NMTOOLS_TESTING_GENERIC_NDARRAY)
    SLICE_SUBCASE(case26,   array, slice0, slice1);
    SLICE_SUBCASE(case26, array_a, slice0, slice1);
    SLICE_SUBCASE(case26, array_f, slice0, slice1);
    SLICE_SUBCASE(case26, array_d, slice0, slice1);
    SLICE_SUBCASE(case26, array_h, slice0, slice1);

    #else
    SLICE_SUBCASE(case26, array_cs_fb, slice0, slice1);
    SLICE_SUBCASE(case26, array_cs_hb, slice0, slice1);
    SLICE_SUBCASE(case26, array_cs_db, slice0, slice1);

    SLICE_SUBCASE(case26, array_fs_fb, slice0, slice1);
    SLICE_SUBCASE(case26, array_fs_hb, slice0, slice1);
    SLICE_SUBCASE(case26, array_fs_db, slice0, slice1);

    SLICE_SUBCASE(case26, array_hs_fb, slice0, slice1);
    SLICE_SUBCASE(case26, array_hs_hb, slice0, slice1);
    SLICE_SUBCASE(case26, array_hs_db, slice0, slice1);

    SLICE_SUBCASE(case26, array_ds_fb, slice0, slice1);
    SLICE_SUBCASE(case26, array_ds_hb, slice0, slice1);
    SLICE_SUBCASE(case26, array_ds_db, slice0, slice1);

    SLICE_SUBCASE(case26, array_ls_fb, slice0, slice1);
    SLICE_SUBCASE(case26, array_ls_hb, slice0, slice1);
    SLICE_SUBCASE(case26, array_ls_db, slice0, slice1);
    #endif
}

TEST_CASE("slice(case27)" * doctest::test_suite("view::slice"))
{
    #if !defined(NMTOOLS_TESTING_GENERIC_NDARRAY)
    SLICE_SUBCASE(case27,   array, slice0, slice1, slice2);
    SLICE_SUBCASE(case27, array_a, slice0, slice1, slice2);
    SLICE_SUBCASE(case27, array_f, slice0, slice1, slice2);
    SLICE_SUBCASE(case27, array_d, slice0, slice1, slice2);
    SLICE_SUBCASE(case27, array_h, slice0, slice1, slice2);

    #else
    SLICE_SUBCASE(case27, array_cs_fb, slice0, slice1, slice2);
    SLICE_SUBCASE(case27, array_cs_hb, slice0, slice1, slice2);
    SLICE_SUBCASE(case27, array_cs_db, slice0, slice1, slice2);

    SLICE_SUBCASE(case27, array_fs_fb, slice0, slice1, slice2);
    SLICE_SUBCASE(case27, array_fs_hb, slice0, slice1, slice2);
    SLICE_SUBCASE(case27, array_fs_db, slice0, slice1, slice2);

    SLICE_SUBCASE(case27, array_hs_fb, slice0, slice1, slice2);
    SLICE_SUBCASE(case27, array_hs_hb, slice0, slice1, slice2);
    SLICE_SUBCASE(case27, array_hs_db, slice0, slice1, slice2);

    SLICE_SUBCASE(case27, array_ds_fb, slice0, slice1, slice2);
    SLICE_SUBCASE(case27, array_ds_hb, slice0, slice1, slice2);
    SLICE_SUBCASE(case27, array_ds_db, slice0, slice1, slice2);

    SLICE_SUBCASE(case27, array_ls_fb, slice0, slice1, slice2);
    SLICE_SUBCASE(case27, array_ls_hb, slice0, slice1, slice2);
    SLICE_SUBCASE(case27, array_ls_db, slice0, slice1, slice2);
    #endif
}

TEST_CASE("slice(case28)" * doctest::test_suite("view::slice"))
{
    #if !defined(NMTOOLS_TESTING_GENERIC_NDARRAY)
    SLICE_SUBCASE(case28,   array, slice0, slice1);
    SLICE_SUBCASE(case28, array_a, slice0, slice1);
    SLICE_SUBCASE(case28, array_f, slice0, slice1);
    SLICE_SUBCASE(case28, array_d, slice0, slice1);
    SLICE_SUBCASE(case28, array_h, slice0, slice1);

    #else
    SLICE_SUBCASE(case28, array_cs_fb, slice0, slice1);
    SLICE_SUBCASE(case28, array_cs_hb, slice0, slice1);
    SLICE_SUBCASE(case28, array_cs_db, slice0, slice1);

    SLICE_SUBCASE(case28, array_fs_fb, slice0, slice1);
    SLICE_SUBCASE(case28, array_fs_hb, slice0, slice1);
    SLICE_SUBCASE(case28, array_fs_db, slice0, slice1);

    SLICE_SUBCASE(case28, array_hs_fb, slice0, slice1);
    SLICE_SUBCASE(case28, array_hs_hb, slice0, slice1);
    SLICE_SUBCASE(case28, array_hs_db, slice0, slice1);

    SLICE_SUBCASE(case28, array_ds_fb, slice0, slice1);
    SLICE_SUBCASE(case28, array_ds_hb, slice0, slice1);
    SLICE_SUBCASE(case28, array_ds_db, slice0, slice1);

    SLICE_SUBCASE(case28, array_ls_fb, slice0, slice1);
    SLICE_SUBCASE(case28, array_ls_hb, slice0, slice1);
    SLICE_SUBCASE(case28, array_ls_db, slice0, slice1);
    #endif
}

TEST_CASE("slice(case29)" * doctest::test_suite("view::slice"))
{
    #if !defined(NMTOOLS_TESTING_GENERIC_NDARRAY)
    SLICE_SUBCASE(case29,   array, slice0, slice1, slice2);
    SLICE_SUBCASE(case29, array_a, slice0, slice1, slice2);
    SLICE_SUBCASE(case29, array_f, slice0, slice1, slice2);
    SLICE_SUBCASE(case29, array_d, slice0, slice1, slice2);
    SLICE_SUBCASE(case29, array_h, slice0, slice1, slice2);

    #else
    SLICE_SUBCASE(case29, array_cs_fb, slice0, slice1, slice2);
    SLICE_SUBCASE(case29, array_cs_hb, slice0, slice1, slice2);
    SLICE_SUBCASE(case29, array_cs_db, slice0, slice1, slice2);

    SLICE_SUBCASE(case29, array_fs_fb, slice0, slice1, slice2);
    SLICE_SUBCASE(case29, array_fs_hb, slice0, slice1, slice2);
    SLICE_SUBCASE(case29, array_fs_db, slice0, slice1, slice2);

    SLICE_SUBCASE(case29, array_hs_fb, slice0, slice1, slice2);
    SLICE_SUBCASE(case29, array_hs_hb, slice0, slice1, slice2);
    SLICE_SUBCASE(case29, array_hs_db, slice0, slice1, slice2);

    SLICE_SUBCASE(case29, array_ds_fb, slice0, slice1, slice2);
    SLICE_SUBCASE(case29, array_ds_hb, slice0, slice1, slice2);
    SLICE_SUBCASE(case29, array_ds_db, slice0, slice1, slice2);

    SLICE_SUBCASE(case29, array_ls_fb, slice0, slice1, slice2);
    SLICE_SUBCASE(case29, array_ls_hb, slice0, slice1, slice2);
    SLICE_SUBCASE(case29, array_ls_db, slice0, slice1, slice2);
    #endif
}

TEST_CASE("slice(case30)" * doctest::test_suite("view::slice"))
{
    #if !defined(NMTOOLS_TESTING_GENERIC_NDARRAY)
    SLICE_SUBCASE(case30,   array, slice0, slice1, slice2);
    SLICE_SUBCASE(case30, array_a, slice0, slice1, slice2);
    SLICE_SUBCASE(case30, array_f, slice0, slice1, slice2);
    SLICE_SUBCASE(case30, array_d, slice0, slice1, slice2);
    SLICE_SUBCASE(case30, array_h, slice0, slice1, slice2);

    #else
    SLICE_SUBCASE(case30, array_cs_fb, slice0, slice1, slice2);
    SLICE_SUBCASE(case30, array_cs_hb, slice0, slice1, slice2);
    SLICE_SUBCASE(case30, array_cs_db, slice0, slice1, slice2);

    SLICE_SUBCASE(case30, array_fs_fb, slice0, slice1, slice2);
    SLICE_SUBCASE(case30, array_fs_hb, slice0, slice1, slice2);
    SLICE_SUBCASE(case30, array_fs_db, slice0, slice1, slice2);

    SLICE_SUBCASE(case30, array_hs_fb, slice0, slice1, slice2);
    SLICE_SUBCASE(case30, array_hs_hb, slice0, slice1, slice2);
    SLICE_SUBCASE(case30, array_hs_db, slice0, slice1, slice2);

    SLICE_SUBCASE(case30, array_ds_fb, slice0, slice1, slice2);
    SLICE_SUBCASE(case30, array_ds_hb, slice0, slice1, slice2);
    SLICE_SUBCASE(case30, array_ds_db, slice0, slice1, slice2);

    SLICE_SUBCASE(case30, array_ls_fb, slice0, slice1, slice2);
    SLICE_SUBCASE(case30, array_ls_hb, slice0, slice1, slice2);
    SLICE_SUBCASE(case30, array_ls_db, slice0, slice1, slice2);
    #endif
}

TEST_CASE("slice(case31)" * doctest::test_suite("view::slice"))
{
    #if !defined(NMTOOLS_TESTING_GENERIC_NDARRAY)
    SLICE_SUBCASE(case31,   array, slice0, slice1, slice2);
    SLICE_SUBCASE(case31, array_a, slice0, slice1, slice2);
    SLICE_SUBCASE(case31, array_f, slice0, slice1, slice2);
    SLICE_SUBCASE(case31, array_d, slice0, slice1, slice2);
    SLICE_SUBCASE(case31, array_h, slice0, slice1, slice2);

    #else
    SLICE_SUBCASE(case31, array_cs_fb, slice0, slice1, slice2);
    SLICE_SUBCASE(case31, array_cs_hb, slice0, slice1, slice2);
    SLICE_SUBCASE(case31, array_cs_db, slice0, slice1, slice2);

    SLICE_SUBCASE(case31, array_fs_fb, slice0, slice1, slice2);
    SLICE_SUBCASE(case31, array_fs_hb, slice0, slice1, slice2);
    SLICE_SUBCASE(case31, array_fs_db, slice0, slice1, slice2);

    SLICE_SUBCASE(case31, array_hs_fb, slice0, slice1, slice2);
    SLICE_SUBCASE(case31, array_hs_hb, slice0, slice1, slice2);
    SLICE_SUBCASE(case31, array_hs_db, slice0, slice1, slice2);

    SLICE_SUBCASE(case31, array_ds_fb, slice0, slice1, slice2);
    SLICE_SUBCASE(case31, array_ds_hb, slice0, slice1, slice2);
    SLICE_SUBCASE(case31, array_ds_db, slice0, slice1, slice2);

    SLICE_SUBCASE(case31, array_ls_fb, slice0, slice1, slice2);
    SLICE_SUBCASE(case31, array_ls_hb, slice0, slice1, slice2);
    SLICE_SUBCASE(case31, array_ls_db, slice0, slice1, slice2);
    #endif
}

TEST_CASE("slice(case32)" * doctest::test_suite("view::slice"))
{
    #if !defined(NMTOOLS_TESTING_GENERIC_NDARRAY)
    SLICE_SUBCASE(case32,   array, slice0, slice1, slice2);
    SLICE_SUBCASE(case32, array_a, slice0, slice1, slice2);
    SLICE_SUBCASE(case32, array_f, slice0, slice1, slice2);
    SLICE_SUBCASE(case32, array_d, slice0, slice1, slice2);
    SLICE_SUBCASE(case32, array_h, slice0, slice1, slice2);

    #else
    SLICE_SUBCASE(case32, array_cs_fb, slice0, slice1, slice2);
    SLICE_SUBCASE(case32, array_cs_hb, slice0, slice1, slice2);
    SLICE_SUBCASE(case32, array_cs_db, slice0, slice1, slice2);

    SLICE_SUBCASE(case32, array_fs_fb, slice0, slice1, slice2);
    SLICE_SUBCASE(case32, array_fs_hb, slice0, slice1, slice2);
    SLICE_SUBCASE(case32, array_fs_db, slice0, slice1, slice2);

    SLICE_SUBCASE(case32, array_hs_fb, slice0, slice1, slice2);
    SLICE_SUBCASE(case32, array_hs_hb, slice0, slice1, slice2);
    SLICE_SUBCASE(case32, array_hs_db, slice0, slice1, slice2);

    SLICE_SUBCASE(case32, array_ds_fb, slice0, slice1, slice2);
    SLICE_SUBCASE(case32, array_ds_hb, slice0, slice1, slice2);
    SLICE_SUBCASE(case32, array_ds_db, slice0, slice1, slice2);

    SLICE_SUBCASE(case32, array_ls_fb, slice0, slice1, slice2);
    SLICE_SUBCASE(case32, array_ls_hb, slice0, slice1, slice2);
    SLICE_SUBCASE(case32, array_ls_db, slice0, slice1, slice2);
    #endif
}

TEST_CASE("slice(case33)" * doctest::test_suite("view::slice"))
{
    #if !defined(NMTOOLS_TESTING_GENERIC_NDARRAY)
    SLICE_SUBCASE(case33,   array, slice0, slice1, slice2);
    SLICE_SUBCASE(case33, array_a, slice0, slice1, slice2);
    SLICE_SUBCASE(case33, array_f, slice0, slice1, slice2);
    SLICE_SUBCASE(case33, array_d, slice0, slice1, slice2);
    SLICE_SUBCASE(case33, array_h, slice0, slice1, slice2);

    #else
    SLICE_SUBCASE(case33, array_cs_fb, slice0, slice1, slice2);
    SLICE_SUBCASE(case33, array_cs_hb, slice0, slice1, slice2);
    SLICE_SUBCASE(case33, array_cs_db, slice0, slice1, slice2);

    SLICE_SUBCASE(case33, array_fs_fb, slice0, slice1, slice2);
    SLICE_SUBCASE(case33, array_fs_hb, slice0, slice1, slice2);
    SLICE_SUBCASE(case33, array_fs_db, slice0, slice1, slice2);

    SLICE_SUBCASE(case33, array_hs_fb, slice0, slice1, slice2);
    SLICE_SUBCASE(case33, array_hs_hb, slice0, slice1, slice2);
    SLICE_SUBCASE(case33, array_hs_db, slice0, slice1, slice2);

    SLICE_SUBCASE(case33, array_ds_fb, slice0, slice1, slice2);
    SLICE_SUBCASE(case33, array_ds_hb, slice0, slice1, slice2);
    SLICE_SUBCASE(case33, array_ds_db, slice0, slice1, slice2);

    SLICE_SUBCASE(case33, array_ls_fb, slice0, slice1, slice2);
    SLICE_SUBCASE(case33, array_ls_hb, slice0, slice1, slice2);
    SLICE_SUBCASE(case33, array_ls_db, slice0, slice1, slice2);
    #endif
}

TEST_CASE("slice(case34)" * doctest::test_suite("view::slice"))
{
    #if !defined(NMTOOLS_TESTING_GENERIC_NDARRAY)
    SLICE_SUBCASE(case34,   array, slice0, slice1);
    SLICE_SUBCASE(case34, array_a, slice0, slice1);
    SLICE_SUBCASE(case34, array_f, slice0, slice1);
    SLICE_SUBCASE(case34, array_d, slice0, slice1);
    SLICE_SUBCASE(case34, array_h, slice0, slice1);

    #else
    SLICE_SUBCASE(case34, array_cs_fb, slice0, slice1);
    SLICE_SUBCASE(case34, array_cs_hb, slice0, slice1);
    SLICE_SUBCASE(case34, array_cs_db, slice0, slice1);

    SLICE_SUBCASE(case34, array_fs_fb, slice0, slice1);
    SLICE_SUBCASE(case34, array_fs_hb, slice0, slice1);
    SLICE_SUBCASE(case34, array_fs_db, slice0, slice1);

    SLICE_SUBCASE(case34, array_hs_fb, slice0, slice1);
    SLICE_SUBCASE(case34, array_hs_hb, slice0, slice1);
    SLICE_SUBCASE(case34, array_hs_db, slice0, slice1);

    SLICE_SUBCASE(case34, array_ds_fb, slice0, slice1);
    SLICE_SUBCASE(case34, array_ds_hb, slice0, slice1);
    SLICE_SUBCASE(case34, array_ds_db, slice0, slice1);

    SLICE_SUBCASE(case34, array_ls_fb, slice0, slice1);
    SLICE_SUBCASE(case34, array_ls_hb, slice0, slice1);
    SLICE_SUBCASE(case34, array_ls_db, slice0, slice1);
    #endif
}

TEST_CASE("slice(case35)" * doctest::test_suite("view::slice"))
{
    #if !defined(NMTOOLS_TESTING_GENERIC_NDARRAY)
    SLICE_SUBCASE(case35,   array, slice0, slice1, slice2);
    SLICE_SUBCASE(case35, array_a, slice0, slice1, slice2);
    SLICE_SUBCASE(case35, array_f, slice0, slice1, slice2);
    SLICE_SUBCASE(case35, array_d, slice0, slice1, slice2);
    SLICE_SUBCASE(case35, array_h, slice0, slice1, slice2);

    #else
    SLICE_SUBCASE(case35, array_cs_fb, slice0, slice1, slice2);
    SLICE_SUBCASE(case35, array_cs_hb, slice0, slice1, slice2);
    SLICE_SUBCASE(case35, array_cs_db, slice0, slice1, slice2);

    SLICE_SUBCASE(case35, array_fs_fb, slice0, slice1, slice2);
    SLICE_SUBCASE(case35, array_fs_hb, slice0, slice1, slice2);
    SLICE_SUBCASE(case35, array_fs_db, slice0, slice1, slice2);

    SLICE_SUBCASE(case35, array_hs_fb, slice0, slice1, slice2);
    SLICE_SUBCASE(case35, array_hs_hb, slice0, slice1, slice2);
    SLICE_SUBCASE(case35, array_hs_db, slice0, slice1, slice2);

    SLICE_SUBCASE(case35, array_ds_fb, slice0, slice1, slice2);
    SLICE_SUBCASE(case35, array_ds_hb, slice0, slice1, slice2);
    SLICE_SUBCASE(case35, array_ds_db, slice0, slice1, slice2);

    SLICE_SUBCASE(case35, array_ls_fb, slice0, slice1, slice2);
    SLICE_SUBCASE(case35, array_ls_hb, slice0, slice1, slice2);
    SLICE_SUBCASE(case35, array_ls_db, slice0, slice1, slice2);
    #endif
}

TEST_CASE("slice(case36)" * doctest::test_suite("view::slice"))
{
    #if !defined(NMTOOLS_TESTING_GENERIC_NDARRAY)
    SLICE_SUBCASE(case36,   array, slice0, slice1, slice2);
    SLICE_SUBCASE(case36, array_a, slice0, slice1, slice2);
    SLICE_SUBCASE(case36, array_f, slice0, slice1, slice2);
    SLICE_SUBCASE(case36, array_d, slice0, slice1, slice2);
    SLICE_SUBCASE(case36, array_h, slice0, slice1, slice2);

    #else
    SLICE_SUBCASE(case36, array_cs_fb, slice0, slice1, slice2);
    SLICE_SUBCASE(case36, array_cs_hb, slice0, slice1, slice2);
    SLICE_SUBCASE(case36, array_cs_db, slice0, slice1, slice2);

    SLICE_SUBCASE(case36, array_fs_fb, slice0, slice1, slice2);
    SLICE_SUBCASE(case36, array_fs_hb, slice0, slice1, slice2);
    SLICE_SUBCASE(case36, array_fs_db, slice0, slice1, slice2);

    SLICE_SUBCASE(case36, array_hs_fb, slice0, slice1, slice2);
    SLICE_SUBCASE(case36, array_hs_hb, slice0, slice1, slice2);
    SLICE_SUBCASE(case36, array_hs_db, slice0, slice1, slice2);

    SLICE_SUBCASE(case36, array_ds_fb, slice0, slice1, slice2);
    SLICE_SUBCASE(case36, array_ds_hb, slice0, slice1, slice2);
    SLICE_SUBCASE(case36, array_ds_db, slice0, slice1, slice2);

    SLICE_SUBCASE(case36, array_ls_fb, slice0, slice1, slice2);
    SLICE_SUBCASE(case36, array_ls_hb, slice0, slice1, slice2);
    SLICE_SUBCASE(case36, array_ls_db, slice0, slice1, slice2);
    #endif
}

TEST_CASE("slice(case37)" * doctest::test_suite("view::slice"))
{
    #if !defined(NMTOOLS_TESTING_GENERIC_NDARRAY)
    SLICE_SUBCASE(case37,   array, slice0, slice1, slice2, slice3);
    SLICE_SUBCASE(case37, array_a, slice0, slice1, slice2, slice3);
    SLICE_SUBCASE(case37, array_f, slice0, slice1, slice2, slice3);
    SLICE_SUBCASE(case37, array_d, slice0, slice1, slice2, slice3);
    SLICE_SUBCASE(case37, array_h, slice0, slice1, slice2, slice3);

    #else
    SLICE_SUBCASE(case37, array_cs_fb, slice0, slice1, slice2, slice3);
    SLICE_SUBCASE(case37, array_cs_hb, slice0, slice1, slice2, slice3);
    SLICE_SUBCASE(case37, array_cs_db, slice0, slice1, slice2, slice3);

    SLICE_SUBCASE(case37, array_fs_fb, slice0, slice1, slice2, slice3);
    SLICE_SUBCASE(case37, array_fs_hb, slice0, slice1, slice2, slice3);
    SLICE_SUBCASE(case37, array_fs_db, slice0, slice1, slice2, slice3);

    SLICE_SUBCASE(case37, array_hs_fb, slice0, slice1, slice2, slice3);
    SLICE_SUBCASE(case37, array_hs_hb, slice0, slice1, slice2, slice3);
    SLICE_SUBCASE(case37, array_hs_db, slice0, slice1, slice2, slice3);

    SLICE_SUBCASE(case37, array_ds_fb, slice0, slice1, slice2, slice3);
    SLICE_SUBCASE(case37, array_ds_hb, slice0, slice1, slice2, slice3);
    SLICE_SUBCASE(case37, array_ds_db, slice0, slice1, slice2, slice3);

    SLICE_SUBCASE(case37, array_ls_fb, slice0, slice1, slice2, slice3);
    SLICE_SUBCASE(case37, array_ls_hb, slice0, slice1, slice2, slice3);
    SLICE_SUBCASE(case37, array_ls_db, slice0, slice1, slice2, slice3);
    #endif
}

TEST_CASE("slice(case38)" * doctest::test_suite("view::slice"))
{
    #if !defined(NMTOOLS_TESTING_GENERIC_NDARRAY)
    SLICE_SUBCASE(case38,   array, slice0, slice1, slice2, slice3);
    SLICE_SUBCASE(case38, array_a, slice0, slice1, slice2, slice3);
    SLICE_SUBCASE(case38, array_f, slice0, slice1, slice2, slice3);
    SLICE_SUBCASE(case38, array_d, slice0, slice1, slice2, slice3);
    SLICE_SUBCASE(case38, array_h, slice0, slice1, slice2, slice3);

    #else
    SLICE_SUBCASE(case38, array_cs_fb, slice0, slice1, slice2, slice3);
    SLICE_SUBCASE(case38, array_cs_hb, slice0, slice1, slice2, slice3);
    SLICE_SUBCASE(case38, array_cs_db, slice0, slice1, slice2, slice3);

    SLICE_SUBCASE(case38, array_fs_fb, slice0, slice1, slice2, slice3);
    SLICE_SUBCASE(case38, array_fs_hb, slice0, slice1, slice2, slice3);
    SLICE_SUBCASE(case38, array_fs_db, slice0, slice1, slice2, slice3);

    SLICE_SUBCASE(case38, array_hs_fb, slice0, slice1, slice2, slice3);
    SLICE_SUBCASE(case38, array_hs_hb, slice0, slice1, slice2, slice3);
    SLICE_SUBCASE(case38, array_hs_db, slice0, slice1, slice2, slice3);

    SLICE_SUBCASE(case38, array_ds_fb, slice0, slice1, slice2, slice3);
    SLICE_SUBCASE(case38, array_ds_hb, slice0, slice1, slice2, slice3);
    SLICE_SUBCASE(case38, array_ds_db, slice0, slice1, slice2, slice3);

    SLICE_SUBCASE(case38, array_ls_fb, slice0, slice1, slice2, slice3);
    SLICE_SUBCASE(case38, array_ls_hb, slice0, slice1, slice2, slice3);
    SLICE_SUBCASE(case38, array_ls_db, slice0, slice1, slice2, slice3);
    #endif
}

TEST_CASE("slice(case39)" * doctest::test_suite("view::slice"))
{
    #if !defined(NMTOOLS_TESTING_GENERIC_NDARRAY)
    SLICE_SUBCASE(case39,   array, slice0, slice1, slice2, slice3);
    SLICE_SUBCASE(case39, array_a, slice0, slice1, slice2, slice3);
    SLICE_SUBCASE(case39, array_f, slice0, slice1, slice2, slice3);
    SLICE_SUBCASE(case39, array_d, slice0, slice1, slice2, slice3);
    SLICE_SUBCASE(case39, array_h, slice0, slice1, slice2, slice3);

    #else
    SLICE_SUBCASE(case39, array_cs_fb, slice0, slice1, slice2, slice3);
    SLICE_SUBCASE(case39, array_cs_hb, slice0, slice1, slice2, slice3);
    SLICE_SUBCASE(case39, array_cs_db, slice0, slice1, slice2, slice3);

    SLICE_SUBCASE(case39, array_fs_fb, slice0, slice1, slice2, slice3);
    SLICE_SUBCASE(case39, array_fs_hb, slice0, slice1, slice2, slice3);
    SLICE_SUBCASE(case39, array_fs_db, slice0, slice1, slice2, slice3);

    SLICE_SUBCASE(case39, array_hs_fb, slice0, slice1, slice2, slice3);
    SLICE_SUBCASE(case39, array_hs_hb, slice0, slice1, slice2, slice3);
    SLICE_SUBCASE(case39, array_hs_db, slice0, slice1, slice2, slice3);

    SLICE_SUBCASE(case39, array_ds_fb, slice0, slice1, slice2, slice3);
    SLICE_SUBCASE(case39, array_ds_hb, slice0, slice1, slice2, slice3);
    SLICE_SUBCASE(case39, array_ds_db, slice0, slice1, slice2, slice3);

    SLICE_SUBCASE(case39, array_ls_fb, slice0, slice1, slice2, slice3);
    SLICE_SUBCASE(case39, array_ls_hb, slice0, slice1, slice2, slice3);
    SLICE_SUBCASE(case39, array_ls_db, slice0, slice1, slice2, slice3);
    #endif
}

TEST_CASE("slice(case40)" * doctest::test_suite("view::slice"))
{
    #if !defined(NMTOOLS_TESTING_GENERIC_NDARRAY)
    SLICE_SUBCASE(case40,   array, slice0, slice1, slice2, slice3);
    SLICE_SUBCASE(case40, array_a, slice0, slice1, slice2, slice3);
    SLICE_SUBCASE(case40, array_f, slice0, slice1, slice2, slice3);
    SLICE_SUBCASE(case40, array_d, slice0, slice1, slice2, slice3);
    SLICE_SUBCASE(case40, array_h, slice0, slice1, slice2, slice3);

    #else
    SLICE_SUBCASE(case40, array_cs_fb, slice0, slice1, slice2, slice3);
    SLICE_SUBCASE(case40, array_cs_hb, slice0, slice1, slice2, slice3);
    SLICE_SUBCASE(case40, array_cs_db, slice0, slice1, slice2, slice3);

    SLICE_SUBCASE(case40, array_fs_fb, slice0, slice1, slice2, slice3);
    SLICE_SUBCASE(case40, array_fs_hb, slice0, slice1, slice2, slice3);
    SLICE_SUBCASE(case40, array_fs_db, slice0, slice1, slice2, slice3);

    SLICE_SUBCASE(case40, array_hs_fb, slice0, slice1, slice2, slice3);
    SLICE_SUBCASE(case40, array_hs_hb, slice0, slice1, slice2, slice3);
    SLICE_SUBCASE(case40, array_hs_db, slice0, slice1, slice2, slice3);

    SLICE_SUBCASE(case40, array_ds_fb, slice0, slice1, slice2, slice3);
    SLICE_SUBCASE(case40, array_ds_hb, slice0, slice1, slice2, slice3);
    SLICE_SUBCASE(case40, array_ds_db, slice0, slice1, slice2, slice3);

    SLICE_SUBCASE(case40, array_ls_fb, slice0, slice1, slice2, slice3);
    SLICE_SUBCASE(case40, array_ls_hb, slice0, slice1, slice2, slice3);
    SLICE_SUBCASE(case40, array_ls_db, slice0, slice1, slice2, slice3);
    #endif
}

namespace meta = nmtools::meta;
namespace view = nmtools::view;

using nmtools_tuple;

#if 0
TEST_CASE("slice" * doctest::test_suite("view::slice"))
{
    SUBCASE("fixed_ndarray")
    {
        auto array  = na::fixed_ndarray{{1,2,3}};
        auto slice  = nmtools_tuple{nm::None,nm::None};
        auto sliced = view::slice(array,slice);
        using sliced_t = decltype(sliced);
        NMTOOLS_STATIC_CHECK_TRAIT( meta::is_ndarray, sliced_t );
    }
    SUBCASE("dynamic_ndarray")
    {
        auto array  = na::dynamic_ndarray({1,2,3});
        auto slice  = nmtools_tuple{nm::None,nm::None};
        auto sliced = view::slice(array,slice);
        using sliced_t = decltype(sliced);
        NMTOOLS_STATIC_CHECK_TRAIT( meta::is_ndarray, sliced_t );
    }
    SUBCASE("hybrid_ndarray")
    {
        auto array  = na::hybrid_ndarray({1,2,3});
        auto slice  = nmtools_tuple{nm::None,nm::None};
        auto sliced = view::slice(array,slice);
        using sliced_t = decltype(sliced);
        NMTOOLS_STATIC_CHECK_TRAIT( meta::is_ndarray, sliced_t );
    }
}
#endif

namespace testing::slice
{
    template <typename array_t>
    constexpr auto f(const array_t& array)
    {
        auto slice0 = nmtools_tuple{nm::None,nm::None};
        auto slice1 = nmtools_tuple{nm::None,nm::None};
        static_assert( !meta::is_view_v<array_t> );
        auto sliced = view::slice(array,slice0,slice1);
        // assert( sliced.array == &array );
        return sliced;
    }

    template <typename array_t>
    constexpr auto g(const array_t& array)
    {
        auto sliced = f(array);
        auto slice0 = nmtools_tuple{0,1};
        auto slice1 = nmtools_tuple{0,1};
        auto result = view::slice(sliced,slice0,slice1);
        // assert( sliced.array.array == &array );
        return result;
    }
}

TEST_CASE("slice" * doctest::test_suite("view::slice"))
{
    using testing::slice::f, testing::slice::g;
    {
        auto array = nmtools_array<nmtools_array<int,3>,2> {{
            {1,2,3},
            {4,5,6},
        }};
        auto sliced = f(array);
        int expected[2][3] = {
            {1,2,3},
            {4,5,6},
        };
        CHECK( &array == sliced.array );
        NMTOOLS_ASSERT_EQUAL( sliced, expected );
    }
    {
        auto array = nmtools_array<nmtools_array<int,3>,2> {{
            {1,2,3},
            {4,5,6},
        }};
        auto sliced = g(array);
        int expected[1][1] = {
            {1}
        };
        CHECK( &array == sliced.array.array );
        NMTOOLS_ASSERT_EQUAL( sliced, expected );
    }
    {
        int array[2][3] = {
            {1,2,3},
            {4,5,6},
        };
        auto sliced = view::slice(array, nmtools_tuple{0,1}, nmtools_tuple{0,1});
        int expected[1][1] = {
            {1}
        };
        NMTOOLS_ASSERT_EQUAL( sliced, expected );
    }
}

#define APPLY_SLICE_SUBCASE(case_name, ...) \
SUBCASE(#case_name) \
{ \
    NMTOOLS_TESTING_USE_CASE(array, slice, case_name); \
    using namespace args; \
    auto result = nmtools::view::apply_slice(__VA_ARGS__); \
    NMTOOLS_ASSERT_EQUAL( nmtools::shape(result), nmtools::shape(expect::result) ); \
    NMTOOLS_ASSERT_EQUAL( result, expect::result ); \
}

TEST_CASE("apply_slice(case1)" * doctest::test_suite("view::apply_slice"))
{
    #if !defined(NMTOOLS_TESTING_GENERIC_NDARRAY)
    APPLY_SLICE_SUBCASE(case1, array_d, dslices);
    APPLY_SLICE_SUBCASE(case1, array_d, hslices);
    APPLY_SLICE_SUBCASE(case1, array_d, aslices);

    APPLY_SLICE_SUBCASE(case1, array_h, dslices);
    APPLY_SLICE_SUBCASE(case1, array_h, hslices);
    APPLY_SLICE_SUBCASE(case1, array_h, aslices);

    APPLY_SLICE_SUBCASE(case1, array_a, dslices);
    APPLY_SLICE_SUBCASE(case1, array_a, hslices);
    APPLY_SLICE_SUBCASE(case1, array_a, aslices);

    #else
    APPLY_SLICE_SUBCASE(case1, array_cs_fb, dslices);
    APPLY_SLICE_SUBCASE(case1, array_cs_hb, dslices);
    APPLY_SLICE_SUBCASE(case1, array_cs_db, dslices);

    APPLY_SLICE_SUBCASE(case1, array_fs_fb, dslices);
    APPLY_SLICE_SUBCASE(case1, array_fs_hb, dslices);
    APPLY_SLICE_SUBCASE(case1, array_fs_db, dslices);

    APPLY_SLICE_SUBCASE(case1, array_hs_fb, dslices);
    APPLY_SLICE_SUBCASE(case1, array_hs_hb, dslices);
    APPLY_SLICE_SUBCASE(case1, array_hs_db, dslices);

    APPLY_SLICE_SUBCASE(case1, array_cs_fb, hslices);
    APPLY_SLICE_SUBCASE(case1, array_cs_hb, hslices);
    APPLY_SLICE_SUBCASE(case1, array_cs_db, hslices);

    APPLY_SLICE_SUBCASE(case1, array_fs_fb, hslices);
    APPLY_SLICE_SUBCASE(case1, array_fs_hb, hslices);
    APPLY_SLICE_SUBCASE(case1, array_fs_db, hslices);

    APPLY_SLICE_SUBCASE(case1, array_hs_fb, hslices);
    APPLY_SLICE_SUBCASE(case1, array_hs_hb, hslices);
    APPLY_SLICE_SUBCASE(case1, array_hs_db, hslices);

    APPLY_SLICE_SUBCASE(case1, array_cs_fb, aslices);
    APPLY_SLICE_SUBCASE(case1, array_cs_hb, aslices);
    APPLY_SLICE_SUBCASE(case1, array_cs_db, aslices);

    APPLY_SLICE_SUBCASE(case1, array_fs_fb, aslices);
    APPLY_SLICE_SUBCASE(case1, array_fs_hb, aslices);
    APPLY_SLICE_SUBCASE(case1, array_fs_db, aslices);

    APPLY_SLICE_SUBCASE(case1, array_hs_fb, aslices);
    APPLY_SLICE_SUBCASE(case1, array_hs_hb, aslices);
    APPLY_SLICE_SUBCASE(case1, array_hs_db, aslices);
    #endif
}

TEST_CASE("apply_slice(case2)" * doctest::test_suite("view::apply_slice"))
{
    #if !defined(NMTOOLS_TESTING_GENERIC_NDARRAY)
    APPLY_SLICE_SUBCASE(case2, array_d, dslices);
    APPLY_SLICE_SUBCASE(case2, array_d, hslices);
    APPLY_SLICE_SUBCASE(case2, array_d, aslices);

    APPLY_SLICE_SUBCASE(case2, array_h, dslices);
    APPLY_SLICE_SUBCASE(case2, array_h, hslices);
    APPLY_SLICE_SUBCASE(case2, array_h, aslices);

    APPLY_SLICE_SUBCASE(case2, array_a, dslices);
    APPLY_SLICE_SUBCASE(case2, array_a, hslices);
    APPLY_SLICE_SUBCASE(case2, array_a, aslices);

    #else
    APPLY_SLICE_SUBCASE(case2, array_cs_fb, dslices);
    APPLY_SLICE_SUBCASE(case2, array_cs_hb, dslices);
    APPLY_SLICE_SUBCASE(case2, array_cs_db, dslices);

    APPLY_SLICE_SUBCASE(case2, array_fs_fb, dslices);
    APPLY_SLICE_SUBCASE(case2, array_fs_hb, dslices);
    APPLY_SLICE_SUBCASE(case2, array_fs_db, dslices);

    APPLY_SLICE_SUBCASE(case2, array_hs_fb, dslices);
    APPLY_SLICE_SUBCASE(case2, array_hs_hb, dslices);
    APPLY_SLICE_SUBCASE(case2, array_hs_db, dslices);

    APPLY_SLICE_SUBCASE(case2, array_cs_fb, hslices);
    APPLY_SLICE_SUBCASE(case2, array_cs_hb, hslices);
    APPLY_SLICE_SUBCASE(case2, array_cs_db, hslices);

    APPLY_SLICE_SUBCASE(case2, array_fs_fb, hslices);
    APPLY_SLICE_SUBCASE(case2, array_fs_hb, hslices);
    APPLY_SLICE_SUBCASE(case2, array_fs_db, hslices);

    APPLY_SLICE_SUBCASE(case2, array_hs_fb, hslices);
    APPLY_SLICE_SUBCASE(case2, array_hs_hb, hslices);
    APPLY_SLICE_SUBCASE(case2, array_hs_db, hslices);

    APPLY_SLICE_SUBCASE(case2, array_cs_fb, aslices);
    APPLY_SLICE_SUBCASE(case2, array_cs_hb, aslices);
    APPLY_SLICE_SUBCASE(case2, array_cs_db, aslices);

    APPLY_SLICE_SUBCASE(case2, array_fs_fb, aslices);
    APPLY_SLICE_SUBCASE(case2, array_fs_hb, aslices);
    APPLY_SLICE_SUBCASE(case2, array_fs_db, aslices);

    APPLY_SLICE_SUBCASE(case2, array_hs_fb, aslices);
    APPLY_SLICE_SUBCASE(case2, array_hs_hb, aslices);
    APPLY_SLICE_SUBCASE(case2, array_hs_db, aslices);
    #endif
}

TEST_CASE("apply_slice(case3)" * doctest::test_suite("view::apply_slice"))
{
    #if !defined(NMTOOLS_TESTING_GENERIC_NDARRAY)
    APPLY_SLICE_SUBCASE(case3, array_d, dslices);
    APPLY_SLICE_SUBCASE(case3, array_d, hslices);
    APPLY_SLICE_SUBCASE(case3, array_d, aslices);

    APPLY_SLICE_SUBCASE(case3, array_h, dslices);
    APPLY_SLICE_SUBCASE(case3, array_h, hslices);
    APPLY_SLICE_SUBCASE(case3, array_h, aslices);

    APPLY_SLICE_SUBCASE(case3, array_a, dslices);
    APPLY_SLICE_SUBCASE(case3, array_a, hslices);
    APPLY_SLICE_SUBCASE(case3, array_a, aslices);
    #else
    APPLY_SLICE_SUBCASE(case3, array_cs_fb, dslices);
    APPLY_SLICE_SUBCASE(case3, array_cs_hb, dslices);
    APPLY_SLICE_SUBCASE(case3, array_cs_db, dslices);

    APPLY_SLICE_SUBCASE(case3, array_fs_fb, dslices);
    APPLY_SLICE_SUBCASE(case3, array_fs_hb, dslices);
    APPLY_SLICE_SUBCASE(case3, array_fs_db, dslices);

    APPLY_SLICE_SUBCASE(case3, array_hs_fb, dslices);
    APPLY_SLICE_SUBCASE(case3, array_hs_hb, dslices);
    APPLY_SLICE_SUBCASE(case3, array_hs_db, dslices);

    APPLY_SLICE_SUBCASE(case3, array_cs_fb, hslices);
    APPLY_SLICE_SUBCASE(case3, array_cs_hb, hslices);
    APPLY_SLICE_SUBCASE(case3, array_cs_db, hslices);

    APPLY_SLICE_SUBCASE(case3, array_fs_fb, hslices);
    APPLY_SLICE_SUBCASE(case3, array_fs_hb, hslices);
    APPLY_SLICE_SUBCASE(case3, array_fs_db, hslices);

    APPLY_SLICE_SUBCASE(case3, array_hs_fb, hslices);
    APPLY_SLICE_SUBCASE(case3, array_hs_hb, hslices);
    APPLY_SLICE_SUBCASE(case3, array_hs_db, hslices);

    APPLY_SLICE_SUBCASE(case3, array_cs_fb, aslices);
    APPLY_SLICE_SUBCASE(case3, array_cs_hb, aslices);
    APPLY_SLICE_SUBCASE(case3, array_cs_db, aslices);

    APPLY_SLICE_SUBCASE(case3, array_fs_fb, aslices);
    APPLY_SLICE_SUBCASE(case3, array_fs_hb, aslices);
    APPLY_SLICE_SUBCASE(case3, array_fs_db, aslices);

    APPLY_SLICE_SUBCASE(case3, array_hs_fb, aslices);
    APPLY_SLICE_SUBCASE(case3, array_hs_hb, aslices);
    APPLY_SLICE_SUBCASE(case3, array_hs_db, aslices);
    #endif
}

TEST_CASE("apply_slice(case4)" * doctest::test_suite("view::apply_slice"))
{
    #if !defined(NMTOOLS_TESTING_GENERIC_NDARRAY)
    APPLY_SLICE_SUBCASE(case4, array_d, dslices);
    // APPLY_SLICE_SUBCASE(case4, array_d, hslices);
    APPLY_SLICE_SUBCASE(case4, array_d, aslices);

    APPLY_SLICE_SUBCASE(case4, array_h, dslices);
    // APPLY_SLICE_SUBCASE(case4, array_h, hslices);
    APPLY_SLICE_SUBCASE(case4, array_h, aslices);

    APPLY_SLICE_SUBCASE(case4, array_a, dslices);
    // APPLY_SLICE_SUBCASE(case4, array_a, hslices);
    APPLY_SLICE_SUBCASE(case4, array_a, aslices);

    #else
    APPLY_SLICE_SUBCASE(case4, array_cs_fb, dslices);
    APPLY_SLICE_SUBCASE(case4, array_cs_hb, dslices);
    APPLY_SLICE_SUBCASE(case4, array_cs_db, dslices);

    APPLY_SLICE_SUBCASE(case4, array_fs_fb, dslices);
    APPLY_SLICE_SUBCASE(case4, array_fs_hb, dslices);
    APPLY_SLICE_SUBCASE(case4, array_fs_db, dslices);

    APPLY_SLICE_SUBCASE(case4, array_hs_fb, dslices);
    APPLY_SLICE_SUBCASE(case4, array_hs_hb, dslices);
    APPLY_SLICE_SUBCASE(case4, array_hs_db, dslices);

    // APPLY_SLICE_SUBCASE(case4, array_cs_fb, hslices);
    // APPLY_SLICE_SUBCASE(case4, array_cs_hb, hslices);
    // APPLY_SLICE_SUBCASE(case4, array_cs_db, hslices);

    // APPLY_SLICE_SUBCASE(case4, array_fs_fb, hslices);
    // APPLY_SLICE_SUBCASE(case4, array_fs_hb, hslices);
    // APPLY_SLICE_SUBCASE(case4, array_fs_db, hslices);

    // APPLY_SLICE_SUBCASE(case4, array_hs_fb, hslices);
    // APPLY_SLICE_SUBCASE(case4, array_hs_hb, hslices);
    // APPLY_SLICE_SUBCASE(case4, array_hs_db, hslices);

    APPLY_SLICE_SUBCASE(case4, array_cs_fb, aslices);
    APPLY_SLICE_SUBCASE(case4, array_cs_hb, aslices);
    APPLY_SLICE_SUBCASE(case4, array_cs_db, aslices);

    APPLY_SLICE_SUBCASE(case4, array_fs_fb, aslices);
    APPLY_SLICE_SUBCASE(case4, array_fs_hb, aslices);
    APPLY_SLICE_SUBCASE(case4, array_fs_db, aslices);

    APPLY_SLICE_SUBCASE(case4, array_hs_fb, aslices);
    APPLY_SLICE_SUBCASE(case4, array_hs_hb, aslices);
    APPLY_SLICE_SUBCASE(case4, array_hs_db, aslices);
    #endif
}

// TODO: fix runtime, shape zero at last axis
TEST_CASE("apply_slice(case4)" * doctest::test_suite("view::apply_slice") * doctest::skip(true))
{
    #if !defined(NMTOOLS_TESTING_GENERIC_NDARRAY)
    APPLY_SLICE_SUBCASE(case4, array_d, hslices);
    APPLY_SLICE_SUBCASE(case4, array_h, hslices);
    APPLY_SLICE_SUBCASE(case4, array_a, hslices);

    #else
    APPLY_SLICE_SUBCASE(case4, array_cs_fb, hslices);
    APPLY_SLICE_SUBCASE(case4, array_cs_hb, hslices);
    APPLY_SLICE_SUBCASE(case4, array_cs_db, hslices);

    APPLY_SLICE_SUBCASE(case4, array_fs_fb, hslices);
    APPLY_SLICE_SUBCASE(case4, array_fs_hb, hslices);
    APPLY_SLICE_SUBCASE(case4, array_fs_db, hslices);

    APPLY_SLICE_SUBCASE(case4, array_hs_fb, hslices);
    APPLY_SLICE_SUBCASE(case4, array_hs_hb, hslices);
    APPLY_SLICE_SUBCASE(case4, array_hs_db, hslices);
    #endif
}

TEST_CASE("apply_slice(case5)" * doctest::test_suite("view::apply_slice"))
{
    APPLY_SLICE_SUBCASE(case5, array_d, dslices);
    APPLY_SLICE_SUBCASE(case5, array_d, hslices);
    APPLY_SLICE_SUBCASE(case5, array_d, aslices);

    APPLY_SLICE_SUBCASE(case5, array_h, dslices);
    APPLY_SLICE_SUBCASE(case5, array_h, hslices);
    APPLY_SLICE_SUBCASE(case5, array_h, aslices);

    APPLY_SLICE_SUBCASE(case5, array_a, dslices);
    APPLY_SLICE_SUBCASE(case5, array_a, hslices);
    APPLY_SLICE_SUBCASE(case5, array_a, aslices);
}

TEST_CASE("apply_slice(case8)" * doctest::test_suite("view::apply_slice"))
{
    APPLY_SLICE_SUBCASE(case8, array_d, dslices);
    APPLY_SLICE_SUBCASE(case8, array_d, hslices);
    APPLY_SLICE_SUBCASE(case8, array_d, aslices);

    APPLY_SLICE_SUBCASE(case8, array_h, dslices);
    APPLY_SLICE_SUBCASE(case8, array_h, hslices);
    APPLY_SLICE_SUBCASE(case8, array_h, aslices);

    APPLY_SLICE_SUBCASE(case8, array_a, dslices);
    APPLY_SLICE_SUBCASE(case8, array_a, hslices);
    APPLY_SLICE_SUBCASE(case8, array_a, aslices);
}

TEST_CASE("apply_slice(case9)" * doctest::test_suite("view::apply_slice"))
{
    APPLY_SLICE_SUBCASE(case9, array_d, dslices);
    APPLY_SLICE_SUBCASE(case9, array_d, hslices);
    APPLY_SLICE_SUBCASE(case9, array_d, aslices);

    APPLY_SLICE_SUBCASE(case9, array_h, dslices);
    APPLY_SLICE_SUBCASE(case9, array_h, hslices);
    APPLY_SLICE_SUBCASE(case9, array_h, aslices);

    APPLY_SLICE_SUBCASE(case9, array_a, dslices);
    APPLY_SLICE_SUBCASE(case9, array_a, hslices);
    APPLY_SLICE_SUBCASE(case9, array_a, aslices);
}

TEST_CASE("apply_slice(case10)" * doctest::test_suite("view::apply_slice"))
{
    APPLY_SLICE_SUBCASE(case10, array_d, dslices);
    APPLY_SLICE_SUBCASE(case10, array_d, hslices);
    APPLY_SLICE_SUBCASE(case10, array_d, aslices);

    APPLY_SLICE_SUBCASE(case10, array_h, dslices);
    APPLY_SLICE_SUBCASE(case10, array_h, hslices);
    APPLY_SLICE_SUBCASE(case10, array_h, aslices);

    APPLY_SLICE_SUBCASE(case10, array_a, dslices);
    APPLY_SLICE_SUBCASE(case10, array_a, hslices);
    APPLY_SLICE_SUBCASE(case10, array_a, aslices);
}

TEST_CASE("apply_slice(case11)" * doctest::test_suite("view::apply_slice"))
{
    APPLY_SLICE_SUBCASE(case11, array_d, dslices);
    APPLY_SLICE_SUBCASE(case11, array_d, hslices);
    APPLY_SLICE_SUBCASE(case11, array_d, aslices);
    
    APPLY_SLICE_SUBCASE(case11, array_h, dslices);
    APPLY_SLICE_SUBCASE(case11, array_h, hslices);
    APPLY_SLICE_SUBCASE(case11, array_h, aslices);

    APPLY_SLICE_SUBCASE(case11, array_a, dslices);
    APPLY_SLICE_SUBCASE(case11, array_a, hslices);
    APPLY_SLICE_SUBCASE(case11, array_a, aslices);
}

TEST_CASE("apply_slice(case12)" * doctest::test_suite("view::apply_slice"))
{
    APPLY_SLICE_SUBCASE(case12, array_d, dslices);
    APPLY_SLICE_SUBCASE(case12, array_d, hslices);
    APPLY_SLICE_SUBCASE(case12, array_d, aslices);

    APPLY_SLICE_SUBCASE(case12, array_h, dslices);
    APPLY_SLICE_SUBCASE(case12, array_h, hslices);
    APPLY_SLICE_SUBCASE(case12, array_h, aslices);

    APPLY_SLICE_SUBCASE(case12, array_a, dslices);
    APPLY_SLICE_SUBCASE(case12, array_a, hslices);
    APPLY_SLICE_SUBCASE(case12, array_a, aslices);
}

TEST_CASE("apply_slice(case13)" * doctest::test_suite("view::apply_slice"))
{
    APPLY_SLICE_SUBCASE(case13, array_d, dslices);
    APPLY_SLICE_SUBCASE(case13, array_d, hslices);
    APPLY_SLICE_SUBCASE(case13, array_d, aslices);

    APPLY_SLICE_SUBCASE(case13, array_h, dslices);
    APPLY_SLICE_SUBCASE(case13, array_h, hslices);
    APPLY_SLICE_SUBCASE(case13, array_h, aslices);

    APPLY_SLICE_SUBCASE(case13, array_a, dslices);
    APPLY_SLICE_SUBCASE(case13, array_a, hslices);
    APPLY_SLICE_SUBCASE(case13, array_a, aslices);
}

TEST_CASE("apply_slice(case14)" * doctest::test_suite("view::apply_slice"))
{
    APPLY_SLICE_SUBCASE(case14, array_d, dslices);
    APPLY_SLICE_SUBCASE(case14, array_d, hslices);
    APPLY_SLICE_SUBCASE(case14, array_d, aslices);

    APPLY_SLICE_SUBCASE(case14, array_h, dslices);
    APPLY_SLICE_SUBCASE(case14, array_h, hslices);
    APPLY_SLICE_SUBCASE(case14, array_h, aslices);

    APPLY_SLICE_SUBCASE(case14, array_a, dslices);
    APPLY_SLICE_SUBCASE(case14, array_a, hslices);
    APPLY_SLICE_SUBCASE(case14, array_a, aslices);
}

TEST_CASE("apply_slice(case15)" * doctest::test_suite("view::apply_slice"))
{
    APPLY_SLICE_SUBCASE(case15, array_d, dslices);
    APPLY_SLICE_SUBCASE(case15, array_d, hslices);
    APPLY_SLICE_SUBCASE(case15, array_d, aslices);

    APPLY_SLICE_SUBCASE(case15, array_h, dslices);
    APPLY_SLICE_SUBCASE(case15, array_h, hslices);
    APPLY_SLICE_SUBCASE(case15, array_h, aslices);

    APPLY_SLICE_SUBCASE(case15, array_a, dslices);
    APPLY_SLICE_SUBCASE(case15, array_a, hslices);
    APPLY_SLICE_SUBCASE(case15, array_a, aslices);
}

TEST_CASE("apply_slice(case16)" * doctest::test_suite("view::apply_slice"))
{
    APPLY_SLICE_SUBCASE(case16, array_d, dslices);
    APPLY_SLICE_SUBCASE(case16, array_d, hslices);
    APPLY_SLICE_SUBCASE(case16, array_d, aslices);

    APPLY_SLICE_SUBCASE(case16, array_h, dslices);
    APPLY_SLICE_SUBCASE(case16, array_h, hslices);
    APPLY_SLICE_SUBCASE(case16, array_h, aslices);

    APPLY_SLICE_SUBCASE(case16, array_a, dslices);
    APPLY_SLICE_SUBCASE(case16, array_a, hslices);
    APPLY_SLICE_SUBCASE(case16, array_a, aslices);
}

TEST_CASE("apply_slice(case17)" * doctest::test_suite("view::apply_slice"))
{
    APPLY_SLICE_SUBCASE(case17, array_d, dslices);
    APPLY_SLICE_SUBCASE(case17, array_d, hslices);
    APPLY_SLICE_SUBCASE(case17, array_d, aslices);

    APPLY_SLICE_SUBCASE(case17, array_h, dslices);
    APPLY_SLICE_SUBCASE(case17, array_h, hslices);
    APPLY_SLICE_SUBCASE(case17, array_h, aslices);

    APPLY_SLICE_SUBCASE(case17, array_a, dslices);
    APPLY_SLICE_SUBCASE(case17, array_a, hslices);
    APPLY_SLICE_SUBCASE(case17, array_a, aslices);
}

TEST_CASE("apply_slice(case18)" * doctest::test_suite("view::apply_slice"))
{
    APPLY_SLICE_SUBCASE(case18, array_d, dslices);
    APPLY_SLICE_SUBCASE(case18, array_d, hslices);
    APPLY_SLICE_SUBCASE(case18, array_d, aslices);

    APPLY_SLICE_SUBCASE(case18, array_h, dslices);
    APPLY_SLICE_SUBCASE(case18, array_h, hslices);
    APPLY_SLICE_SUBCASE(case18, array_h, aslices);

    APPLY_SLICE_SUBCASE(case18, array_a, dslices);
    APPLY_SLICE_SUBCASE(case18, array_a, hslices);
    APPLY_SLICE_SUBCASE(case18, array_a, aslices);
}

TEST_CASE("apply_slice(case19)" * doctest::test_suite("view::apply_slice"))
{
    APPLY_SLICE_SUBCASE(case19, array_d, dslices);
    APPLY_SLICE_SUBCASE(case19, array_d, hslices);
    APPLY_SLICE_SUBCASE(case19, array_d, aslices);

    APPLY_SLICE_SUBCASE(case19, array_h, dslices);
    APPLY_SLICE_SUBCASE(case19, array_h, hslices);
    APPLY_SLICE_SUBCASE(case19, array_h, aslices);

    APPLY_SLICE_SUBCASE(case19, array_a, dslices);
    APPLY_SLICE_SUBCASE(case19, array_a, hslices);
    APPLY_SLICE_SUBCASE(case19, array_a, aslices);
}

TEST_CASE("apply_slice(case20)" * doctest::test_suite("view::apply_slice"))
{
    APPLY_SLICE_SUBCASE(case20, array_d, dslices);
    APPLY_SLICE_SUBCASE(case20, array_d, hslices);
    APPLY_SLICE_SUBCASE(case20, array_d, aslices);

    APPLY_SLICE_SUBCASE(case20, array_h, dslices);
    APPLY_SLICE_SUBCASE(case20, array_h, hslices);
    APPLY_SLICE_SUBCASE(case20, array_h, aslices);

    APPLY_SLICE_SUBCASE(case20, array_a, dslices);
    APPLY_SLICE_SUBCASE(case20, array_a, hslices);
    APPLY_SLICE_SUBCASE(case20, array_a, aslices);
}

TEST_CASE("apply_slice(case21)" * doctest::test_suite("view::apply_slice"))
{
    APPLY_SLICE_SUBCASE(case21, array_d, dslices);
    APPLY_SLICE_SUBCASE(case21, array_d, hslices);
    APPLY_SLICE_SUBCASE(case21, array_d, aslices);

    APPLY_SLICE_SUBCASE(case21, array_h, dslices);
    APPLY_SLICE_SUBCASE(case21, array_h, hslices);
    APPLY_SLICE_SUBCASE(case21, array_h, aslices);

    APPLY_SLICE_SUBCASE(case21, array_a, dslices);
    APPLY_SLICE_SUBCASE(case21, array_a, hslices);
    APPLY_SLICE_SUBCASE(case21, array_a, aslices);
}

TEST_CASE("apply_slice(case22)" * doctest::test_suite("view::apply_slice"))
{
    APPLY_SLICE_SUBCASE(case22, array_d, dslices);
    APPLY_SLICE_SUBCASE(case22, array_d, hslices);
    APPLY_SLICE_SUBCASE(case22, array_d, aslices);

    APPLY_SLICE_SUBCASE(case22, array_h, dslices);
    APPLY_SLICE_SUBCASE(case22, array_h, hslices);
    APPLY_SLICE_SUBCASE(case22, array_h, aslices);

    APPLY_SLICE_SUBCASE(case22, array_a, dslices);
    APPLY_SLICE_SUBCASE(case22, array_a, hslices);
    APPLY_SLICE_SUBCASE(case22, array_a, aslices);
}

TEST_CASE("apply_slice(case23)" * doctest::test_suite("view::apply_slice"))
{
    APPLY_SLICE_SUBCASE(case23, array_d, dslices);
    APPLY_SLICE_SUBCASE(case23, array_d, hslices);
    APPLY_SLICE_SUBCASE(case23, array_d, aslices);

    APPLY_SLICE_SUBCASE(case23, array_h, dslices);
    APPLY_SLICE_SUBCASE(case23, array_h, hslices);
    APPLY_SLICE_SUBCASE(case23, array_h, aslices);

    APPLY_SLICE_SUBCASE(case23, array_a, dslices);
    APPLY_SLICE_SUBCASE(case23, array_a, hslices);
    APPLY_SLICE_SUBCASE(case23, array_a, aslices);
}

TEST_CASE("apply_slice(case24)" * doctest::test_suite("view::apply_slice"))
{
    APPLY_SLICE_SUBCASE(case24, array_d, dslices);
    APPLY_SLICE_SUBCASE(case24, array_d, hslices);
    APPLY_SLICE_SUBCASE(case24, array_d, aslices);

    APPLY_SLICE_SUBCASE(case24, array_h, dslices);
    APPLY_SLICE_SUBCASE(case24, array_h, hslices);
    APPLY_SLICE_SUBCASE(case24, array_h, aslices);

    APPLY_SLICE_SUBCASE(case24, array_a, dslices);
    APPLY_SLICE_SUBCASE(case24, array_a, hslices);
    APPLY_SLICE_SUBCASE(case24, array_a, aslices);
}

TEST_CASE("apply_slice(case25)" * doctest::test_suite("view::apply_slice"))
{
    APPLY_SLICE_SUBCASE(case25, array_d, dslices);
    APPLY_SLICE_SUBCASE(case25, array_d, hslices);
    APPLY_SLICE_SUBCASE(case25, array_d, aslices);

    APPLY_SLICE_SUBCASE(case25, array_h, dslices);
    APPLY_SLICE_SUBCASE(case25, array_h, hslices);
    APPLY_SLICE_SUBCASE(case25, array_h, aslices);

    APPLY_SLICE_SUBCASE(case25, array_a, dslices);
    APPLY_SLICE_SUBCASE(case25, array_a, hslices);
    APPLY_SLICE_SUBCASE(case25, array_a, aslices);
}

TEST_CASE("apply_slice(case26)" * doctest::test_suite("view::apply_slice"))
{
    APPLY_SLICE_SUBCASE(case26, array_d, dslices);
    APPLY_SLICE_SUBCASE(case26, array_d, hslices);
    APPLY_SLICE_SUBCASE(case26, array_d, aslices);

    APPLY_SLICE_SUBCASE(case26, array_h, dslices);
    APPLY_SLICE_SUBCASE(case26, array_h, hslices);
    APPLY_SLICE_SUBCASE(case26, array_h, aslices);

    APPLY_SLICE_SUBCASE(case26, array_a, dslices);
    APPLY_SLICE_SUBCASE(case26, array_a, hslices);
    APPLY_SLICE_SUBCASE(case26, array_a, aslices);
}

TEST_CASE("apply_slice(case27)" * doctest::test_suite("view::apply_slice"))
{
    APPLY_SLICE_SUBCASE(case27, array_d, dslices);
    APPLY_SLICE_SUBCASE(case27, array_d, hslices);
    APPLY_SLICE_SUBCASE(case27, array_d, aslices);

    APPLY_SLICE_SUBCASE(case27, array_h, dslices);
    APPLY_SLICE_SUBCASE(case27, array_h, hslices);
    APPLY_SLICE_SUBCASE(case27, array_h, aslices);

    APPLY_SLICE_SUBCASE(case27, array_a, dslices);
    APPLY_SLICE_SUBCASE(case27, array_a, hslices);
    APPLY_SLICE_SUBCASE(case27, array_a, aslices);
}

TEST_CASE("apply_slice(case28)" * doctest::test_suite("view::apply_slice"))
{
    APPLY_SLICE_SUBCASE(case28, array_d, dslices);
    APPLY_SLICE_SUBCASE(case28, array_d, hslices);
    APPLY_SLICE_SUBCASE(case28, array_d, aslices);

    APPLY_SLICE_SUBCASE(case28, array_h, dslices);
    APPLY_SLICE_SUBCASE(case28, array_h, hslices);
    APPLY_SLICE_SUBCASE(case28, array_h, aslices);

    APPLY_SLICE_SUBCASE(case28, array_a, dslices);
    APPLY_SLICE_SUBCASE(case28, array_a, hslices);
    APPLY_SLICE_SUBCASE(case28, array_a, aslices);
}

TEST_CASE("apply_slice(case29)" * doctest::test_suite("view::apply_slice"))
{
    APPLY_SLICE_SUBCASE(case29, array_d, dslices);
    APPLY_SLICE_SUBCASE(case29, array_d, hslices);
    APPLY_SLICE_SUBCASE(case29, array_d, aslices);

    APPLY_SLICE_SUBCASE(case29, array_h, dslices);
    APPLY_SLICE_SUBCASE(case29, array_h, hslices);
    APPLY_SLICE_SUBCASE(case29, array_h, aslices);

    APPLY_SLICE_SUBCASE(case29, array_a, dslices);
    APPLY_SLICE_SUBCASE(case29, array_a, hslices);
    APPLY_SLICE_SUBCASE(case29, array_a, aslices);
}

TEST_CASE("apply_slice(case30)" * doctest::test_suite("view::apply_slice"))
{
    APPLY_SLICE_SUBCASE(case30, array_d, dslices);
    APPLY_SLICE_SUBCASE(case30, array_d, hslices);
    APPLY_SLICE_SUBCASE(case30, array_d, aslices);

    APPLY_SLICE_SUBCASE(case30, array_h, dslices);
    APPLY_SLICE_SUBCASE(case30, array_h, hslices);
    APPLY_SLICE_SUBCASE(case30, array_h, aslices);

    APPLY_SLICE_SUBCASE(case30, array_a, dslices);
    APPLY_SLICE_SUBCASE(case30, array_a, hslices);
    APPLY_SLICE_SUBCASE(case30, array_a, aslices);
}

TEST_CASE("apply_slice(case33)" * doctest::test_suite("view::apply_slice"))
{
    APPLY_SLICE_SUBCASE(case33, array_d, dslices);
    APPLY_SLICE_SUBCASE(case33, array_d, hslices);
    APPLY_SLICE_SUBCASE(case33, array_d, aslices);

    APPLY_SLICE_SUBCASE(case33, array_h, dslices);
    APPLY_SLICE_SUBCASE(case33, array_h, hslices);
    APPLY_SLICE_SUBCASE(case33, array_h, aslices);

    APPLY_SLICE_SUBCASE(case33, array_a, dslices);
    APPLY_SLICE_SUBCASE(case33, array_a, hslices);
    APPLY_SLICE_SUBCASE(case33, array_a, aslices);
}

TEST_CASE("apply_slice(case34)" * doctest::test_suite("view::apply_slice"))
{
    APPLY_SLICE_SUBCASE(case34, array_d, dslices);
    APPLY_SLICE_SUBCASE(case34, array_d, hslices);
    APPLY_SLICE_SUBCASE(case34, array_d, aslices);

    APPLY_SLICE_SUBCASE(case34, array_h, dslices);
    APPLY_SLICE_SUBCASE(case34, array_h, hslices);
    APPLY_SLICE_SUBCASE(case34, array_h, aslices);

    APPLY_SLICE_SUBCASE(case34, array_a, dslices);
    APPLY_SLICE_SUBCASE(case34, array_a, hslices);
    APPLY_SLICE_SUBCASE(case34, array_a, aslices);
}

TEST_CASE("apply_slice(case35)" * doctest::test_suite("view::apply_slice"))
{
    APPLY_SLICE_SUBCASE(case35, array_d, dslices);
    APPLY_SLICE_SUBCASE(case35, array_d, hslices);
    APPLY_SLICE_SUBCASE(case35, array_d, aslices);

    APPLY_SLICE_SUBCASE(case35, array_h, dslices);
    APPLY_SLICE_SUBCASE(case35, array_h, hslices);
    APPLY_SLICE_SUBCASE(case35, array_h, aslices);

    APPLY_SLICE_SUBCASE(case35, array_a, dslices);
    APPLY_SLICE_SUBCASE(case35, array_a, hslices);
    APPLY_SLICE_SUBCASE(case35, array_a, aslices);
}

TEST_CASE("apply_slice(case36)" * doctest::test_suite("view::apply_slice"))
{
    APPLY_SLICE_SUBCASE(case36, array_d, dslices);
    APPLY_SLICE_SUBCASE(case36, array_d, hslices);
    APPLY_SLICE_SUBCASE(case36, array_d, aslices);

    APPLY_SLICE_SUBCASE(case36, array_h, dslices);
    APPLY_SLICE_SUBCASE(case36, array_h, hslices);
    APPLY_SLICE_SUBCASE(case36, array_h, aslices);

    APPLY_SLICE_SUBCASE(case36, array_a, dslices);
    APPLY_SLICE_SUBCASE(case36, array_a, hslices);
    APPLY_SLICE_SUBCASE(case36, array_a, aslices);
}

TEST_CASE("apply_slice(case37)" * doctest::test_suite("view::apply_slice"))
{
    APPLY_SLICE_SUBCASE(case37, array_d, dslices);
    APPLY_SLICE_SUBCASE(case37, array_d, hslices);
    APPLY_SLICE_SUBCASE(case37, array_d, aslices);

    APPLY_SLICE_SUBCASE(case37, array_h, dslices);
    APPLY_SLICE_SUBCASE(case37, array_h, hslices);
    APPLY_SLICE_SUBCASE(case37, array_h, aslices);

    APPLY_SLICE_SUBCASE(case37, array_a, dslices);
    APPLY_SLICE_SUBCASE(case37, array_a, hslices);
    APPLY_SLICE_SUBCASE(case37, array_a, aslices);
}

TEST_CASE("apply_slice(case38)" * doctest::test_suite("view::apply_slice"))
{
    APPLY_SLICE_SUBCASE(case38, array_d, dslices);
    APPLY_SLICE_SUBCASE(case38, array_d, hslices);
    APPLY_SLICE_SUBCASE(case38, array_d, aslices);

    APPLY_SLICE_SUBCASE(case38, array_h, dslices);
    APPLY_SLICE_SUBCASE(case38, array_h, hslices);
    APPLY_SLICE_SUBCASE(case38, array_h, aslices);

    APPLY_SLICE_SUBCASE(case38, array_a, dslices);
    APPLY_SLICE_SUBCASE(case38, array_a, hslices);
    APPLY_SLICE_SUBCASE(case38, array_a, aslices);
}

TEST_CASE("apply_slice(case39)" * doctest::test_suite("view::apply_slice"))
{
    APPLY_SLICE_SUBCASE(case39, array_d, dslices);
    APPLY_SLICE_SUBCASE(case39, array_d, hslices);
    APPLY_SLICE_SUBCASE(case39, array_d, aslices);

    APPLY_SLICE_SUBCASE(case39, array_h, dslices);
    APPLY_SLICE_SUBCASE(case39, array_h, hslices);
    APPLY_SLICE_SUBCASE(case39, array_h, aslices);

    APPLY_SLICE_SUBCASE(case39, array_a, dslices);
    APPLY_SLICE_SUBCASE(case39, array_a, hslices);
    APPLY_SLICE_SUBCASE(case39, array_a, aslices);
}

TEST_CASE("apply_slice(case40)" * doctest::test_suite("view::apply_slice"))
{
    APPLY_SLICE_SUBCASE(case40, array_d, dslices);
    APPLY_SLICE_SUBCASE(case40, array_d, hslices);
    APPLY_SLICE_SUBCASE(case40, array_d, aslices);

    APPLY_SLICE_SUBCASE(case40, array_h, dslices);
    APPLY_SLICE_SUBCASE(case40, array_h, hslices);
    APPLY_SLICE_SUBCASE(case40, array_h, aslices);

    APPLY_SLICE_SUBCASE(case40, array_a, dslices);
    APPLY_SLICE_SUBCASE(case40, array_a, hslices);
    APPLY_SLICE_SUBCASE(case40, array_a, aslices);
}