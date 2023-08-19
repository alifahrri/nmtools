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

#include "nmtools/array/view/transpose.hpp"
#include "nmtools/constants.hpp"
#include "nmtools/testing/data/array/transpose.hpp"
#include "nmtools/testing/doctest.hpp"

#include <array>
#include <vector>

namespace nm = nmtools;
namespace na = nm::array;
namespace view = nm::view;

#define TRANSPOSE_SUBCASE(case_name, array, axes) \
SUBCASE(#case_name) \
{ \
    NMTOOLS_TESTING_DECLARE_NS( transpose, case_name ); \
    auto array_ref = view::transpose(args::array, args::axes); \
    NMTOOLS_ASSERT_EQUAL( nmtools::shape(array_ref), nmtools::shape(expect::expected) ); \
    NMTOOLS_ASSERT_CLOSE( array_ref, expect::expected ); \
}

TEST_CASE("transpose(case1)" * doctest::test_suite("view::transpose"))
{
    #if !defined(NMTOOLS_TESTING_GENERIC_NDARRAY)
    #else
    TRANSPOSE_SUBCASE( case1, array_cs_fb, axes_a );
    TRANSPOSE_SUBCASE( case1, array_cs_hb, axes_a );
    TRANSPOSE_SUBCASE( case1, array_cs_db, axes_a );

    TRANSPOSE_SUBCASE( case1, array_fs_fb, axes_a );
    TRANSPOSE_SUBCASE( case1, array_fs_hb, axes_a );
    TRANSPOSE_SUBCASE( case1, array_fs_db, axes_a );

    TRANSPOSE_SUBCASE( case1, array_hs_fb, axes_a );
    TRANSPOSE_SUBCASE( case1, array_hs_hb, axes_a );
    TRANSPOSE_SUBCASE( case1, array_hs_db, axes_a );

    TRANSPOSE_SUBCASE( case1, array_ds_fb, axes_a );
    TRANSPOSE_SUBCASE( case1, array_ds_hb, axes_a );
    TRANSPOSE_SUBCASE( case1, array_ds_db, axes_a );

    TRANSPOSE_SUBCASE( case1, array_ls_fb, axes_a );
    TRANSPOSE_SUBCASE( case1, array_ls_hb, axes_a );
    TRANSPOSE_SUBCASE( case1, array_ls_db, axes_a );
    #endif
}

TEST_CASE("transpose(case2)" * doctest::test_suite("view::transpose"))
{
    #if !defined(NMTOOLS_TESTING_GENERIC_NDARRAY)
    #else
    TRANSPOSE_SUBCASE( case2, array_cs_fb, axes_a );
    TRANSPOSE_SUBCASE( case2, array_cs_hb, axes_a );
    TRANSPOSE_SUBCASE( case2, array_cs_db, axes_a );

    TRANSPOSE_SUBCASE( case2, array_fs_fb, axes_a );
    TRANSPOSE_SUBCASE( case2, array_fs_hb, axes_a );
    TRANSPOSE_SUBCASE( case2, array_fs_db, axes_a );

    TRANSPOSE_SUBCASE( case2, array_hs_fb, axes_a );
    TRANSPOSE_SUBCASE( case2, array_hs_hb, axes_a );
    TRANSPOSE_SUBCASE( case2, array_hs_db, axes_a );

    TRANSPOSE_SUBCASE( case2, array_ds_fb, axes_a );
    TRANSPOSE_SUBCASE( case2, array_ds_hb, axes_a );
    TRANSPOSE_SUBCASE( case2, array_ds_db, axes_a );

    TRANSPOSE_SUBCASE( case2, array_ls_fb, axes_a );
    TRANSPOSE_SUBCASE( case2, array_ls_hb, axes_a );
    TRANSPOSE_SUBCASE( case2, array_ls_db, axes_a );
    #endif
}

TEST_CASE("transpose(case3)" * doctest::test_suite("view::transpose"))
{
    #if !defined(NMTOOLS_TESTING_GENERIC_NDARRAY)
    #else
    TRANSPOSE_SUBCASE( case3, array_cs_fb, axes_a );
    TRANSPOSE_SUBCASE( case3, array_cs_hb, axes_a );
    TRANSPOSE_SUBCASE( case3, array_cs_db, axes_a );

    TRANSPOSE_SUBCASE( case3, array_fs_fb, axes_a );
    TRANSPOSE_SUBCASE( case3, array_fs_hb, axes_a );
    TRANSPOSE_SUBCASE( case3, array_fs_db, axes_a );

    TRANSPOSE_SUBCASE( case3, array_hs_fb, axes_a );
    TRANSPOSE_SUBCASE( case3, array_hs_hb, axes_a );
    TRANSPOSE_SUBCASE( case3, array_hs_db, axes_a );

    TRANSPOSE_SUBCASE( case3, array_ds_fb, axes_a );
    TRANSPOSE_SUBCASE( case3, array_ds_hb, axes_a );
    TRANSPOSE_SUBCASE( case3, array_ds_db, axes_a );

    TRANSPOSE_SUBCASE( case3, array_ls_fb, axes_a );
    TRANSPOSE_SUBCASE( case3, array_ls_hb, axes_a );
    TRANSPOSE_SUBCASE( case3, array_ls_db, axes_a );
    #endif
}

TEST_CASE("transpose(case4)" * doctest::test_suite("view::transpose"))
{
    #if !defined(NMTOOLS_TESTING_GENERIC_NDARRAY)
    #else
    TRANSPOSE_SUBCASE( case4, array_cs_fb, axes_a );
    TRANSPOSE_SUBCASE( case4, array_cs_hb, axes_a );
    TRANSPOSE_SUBCASE( case4, array_cs_db, axes_a );

    TRANSPOSE_SUBCASE( case4, array_fs_fb, axes_a );
    TRANSPOSE_SUBCASE( case4, array_fs_hb, axes_a );
    TRANSPOSE_SUBCASE( case4, array_fs_db, axes_a );

    TRANSPOSE_SUBCASE( case4, array_hs_fb, axes_a );
    TRANSPOSE_SUBCASE( case4, array_hs_hb, axes_a );
    TRANSPOSE_SUBCASE( case4, array_hs_db, axes_a );

    TRANSPOSE_SUBCASE( case4, array_ds_fb, axes_a );
    TRANSPOSE_SUBCASE( case4, array_ds_hb, axes_a );
    TRANSPOSE_SUBCASE( case4, array_ds_db, axes_a );

    TRANSPOSE_SUBCASE( case4, array_ls_fb, axes_a );
    TRANSPOSE_SUBCASE( case4, array_ls_hb, axes_a );
    TRANSPOSE_SUBCASE( case4, array_ls_db, axes_a );
    #endif
}

TEST_CASE("transpose(case5)" * doctest::test_suite("view::transpose"))
{
    #if !defined(NMTOOLS_TESTING_GENERIC_NDARRAY)
    #else
    TRANSPOSE_SUBCASE( case5, array_cs_fb, axes_a );
    TRANSPOSE_SUBCASE( case5, array_cs_hb, axes_a );
    TRANSPOSE_SUBCASE( case5, array_cs_db, axes_a );

    TRANSPOSE_SUBCASE( case5, array_fs_fb, axes_a );
    TRANSPOSE_SUBCASE( case5, array_fs_hb, axes_a );
    TRANSPOSE_SUBCASE( case5, array_fs_db, axes_a );

    TRANSPOSE_SUBCASE( case5, array_hs_fb, axes_a );
    TRANSPOSE_SUBCASE( case5, array_hs_hb, axes_a );
    TRANSPOSE_SUBCASE( case5, array_hs_db, axes_a );

    TRANSPOSE_SUBCASE( case5, array_ds_fb, axes_a );
    TRANSPOSE_SUBCASE( case5, array_ds_hb, axes_a );
    TRANSPOSE_SUBCASE( case5, array_ds_db, axes_a );

    TRANSPOSE_SUBCASE( case5, array_ls_fb, axes_a );
    TRANSPOSE_SUBCASE( case5, array_ls_hb, axes_a );
    TRANSPOSE_SUBCASE( case5, array_ls_db, axes_a );
    #endif
}

TEST_CASE("transpose(case6)" * doctest::test_suite("view::transpose"))
{
    #if !defined(NMTOOLS_TESTING_GENERIC_NDARRAY)
    #else
    TRANSPOSE_SUBCASE( case6, array_cs_fb, axes_a );
    TRANSPOSE_SUBCASE( case6, array_cs_hb, axes_a );
    TRANSPOSE_SUBCASE( case6, array_cs_db, axes_a );

    TRANSPOSE_SUBCASE( case6, array_fs_fb, axes_a );
    TRANSPOSE_SUBCASE( case6, array_fs_hb, axes_a );
    TRANSPOSE_SUBCASE( case6, array_fs_db, axes_a );

    TRANSPOSE_SUBCASE( case6, array_hs_fb, axes_a );
    TRANSPOSE_SUBCASE( case6, array_hs_hb, axes_a );
    TRANSPOSE_SUBCASE( case6, array_hs_db, axes_a );

    TRANSPOSE_SUBCASE( case6, array_ds_fb, axes_a );
    TRANSPOSE_SUBCASE( case6, array_ds_hb, axes_a );
    TRANSPOSE_SUBCASE( case6, array_ds_db, axes_a );

    TRANSPOSE_SUBCASE( case6, array_ls_fb, axes_a );
    TRANSPOSE_SUBCASE( case6, array_ls_hb, axes_a );
    TRANSPOSE_SUBCASE( case6, array_ls_db, axes_a );
    #endif
}

TEST_CASE("transpose(case7)" * doctest::test_suite("view::transpose"))
{
    #if !defined(NMTOOLS_TESTING_GENERIC_NDARRAY)
    #else
    TRANSPOSE_SUBCASE( case7, array_cs_fb, axes_a );
    TRANSPOSE_SUBCASE( case7, array_cs_hb, axes_a );
    TRANSPOSE_SUBCASE( case7, array_cs_db, axes_a );

    TRANSPOSE_SUBCASE( case7, array_fs_fb, axes_a );
    TRANSPOSE_SUBCASE( case7, array_fs_hb, axes_a );
    TRANSPOSE_SUBCASE( case7, array_fs_db, axes_a );

    TRANSPOSE_SUBCASE( case7, array_hs_fb, axes_a );
    TRANSPOSE_SUBCASE( case7, array_hs_hb, axes_a );
    TRANSPOSE_SUBCASE( case7, array_hs_db, axes_a );

    TRANSPOSE_SUBCASE( case7, array_ds_fb, axes_a );
    TRANSPOSE_SUBCASE( case7, array_ds_hb, axes_a );
    TRANSPOSE_SUBCASE( case7, array_ds_db, axes_a );

    TRANSPOSE_SUBCASE( case7, array_ls_fb, axes_a );
    TRANSPOSE_SUBCASE( case7, array_ls_hb, axes_a );
    TRANSPOSE_SUBCASE( case7, array_ls_db, axes_a );
    #endif
}

TEST_CASE("transpose(case8)" * doctest::test_suite("view::transpose"))
{
    #if !defined(NMTOOLS_TESTING_GENERIC_NDARRAY)
    #else
    TRANSPOSE_SUBCASE( case8, array_cs_fb, axes_a );
    TRANSPOSE_SUBCASE( case8, array_cs_hb, axes_a );
    TRANSPOSE_SUBCASE( case8, array_cs_db, axes_a );

    TRANSPOSE_SUBCASE( case8, array_fs_fb, axes_a );
    TRANSPOSE_SUBCASE( case8, array_fs_hb, axes_a );
    TRANSPOSE_SUBCASE( case8, array_fs_db, axes_a );

    TRANSPOSE_SUBCASE( case8, array_hs_fb, axes_a );
    TRANSPOSE_SUBCASE( case8, array_hs_hb, axes_a );
    TRANSPOSE_SUBCASE( case8, array_hs_db, axes_a );

    TRANSPOSE_SUBCASE( case8, array_ds_fb, axes_a );
    TRANSPOSE_SUBCASE( case8, array_ds_hb, axes_a );
    TRANSPOSE_SUBCASE( case8, array_ds_db, axes_a );

    TRANSPOSE_SUBCASE( case8, array_ls_fb, axes_a );
    TRANSPOSE_SUBCASE( case8, array_ls_hb, axes_a );
    TRANSPOSE_SUBCASE( case8, array_ls_db, axes_a );
    #endif
}

TEST_CASE("transpose(case9)" * doctest::test_suite("view::transpose"))
{
    #if !defined(NMTOOLS_TESTING_GENERIC_NDARRAY)
    #else
    TRANSPOSE_SUBCASE( case9, array_cs_fb, axes_a );
    TRANSPOSE_SUBCASE( case9, array_cs_hb, axes_a );
    TRANSPOSE_SUBCASE( case9, array_cs_db, axes_a );

    TRANSPOSE_SUBCASE( case9, array_fs_fb, axes_a );
    TRANSPOSE_SUBCASE( case9, array_fs_hb, axes_a );
    TRANSPOSE_SUBCASE( case9, array_fs_db, axes_a );

    TRANSPOSE_SUBCASE( case9, array_hs_fb, axes_a );
    TRANSPOSE_SUBCASE( case9, array_hs_hb, axes_a );
    TRANSPOSE_SUBCASE( case9, array_hs_db, axes_a );

    TRANSPOSE_SUBCASE( case9, array_ds_fb, axes_a );
    TRANSPOSE_SUBCASE( case9, array_ds_hb, axes_a );
    TRANSPOSE_SUBCASE( case9, array_ds_db, axes_a );

    TRANSPOSE_SUBCASE( case9, array_ls_fb, axes_a );
    TRANSPOSE_SUBCASE( case9, array_ls_hb, axes_a );
    TRANSPOSE_SUBCASE( case9, array_ls_db, axes_a );
    #endif
}

TEST_CASE("transpose(case10)" * doctest::test_suite("view::transpose"))
{
    #if !defined(NMTOOLS_TESTING_GENERIC_NDARRAY)
    #else
    TRANSPOSE_SUBCASE( case10, array_cs_fb, axes_a );
    TRANSPOSE_SUBCASE( case10, array_cs_hb, axes_a );
    TRANSPOSE_SUBCASE( case10, array_cs_db, axes_a );

    TRANSPOSE_SUBCASE( case10, array_fs_fb, axes_a );
    TRANSPOSE_SUBCASE( case10, array_fs_hb, axes_a );
    TRANSPOSE_SUBCASE( case10, array_fs_db, axes_a );

    TRANSPOSE_SUBCASE( case10, array_hs_fb, axes_a );
    TRANSPOSE_SUBCASE( case10, array_hs_hb, axes_a );
    TRANSPOSE_SUBCASE( case10, array_hs_db, axes_a );

    TRANSPOSE_SUBCASE( case10, array_ds_fb, axes_a );
    TRANSPOSE_SUBCASE( case10, array_ds_hb, axes_a );
    TRANSPOSE_SUBCASE( case10, array_ds_db, axes_a );

    TRANSPOSE_SUBCASE( case10, array_ls_fb, axes_a );
    TRANSPOSE_SUBCASE( case10, array_ls_hb, axes_a );
    TRANSPOSE_SUBCASE( case10, array_ls_db, axes_a );

    TRANSPOSE_SUBCASE( case10, array_cs_fb, axes_f );
    TRANSPOSE_SUBCASE( case10, array_cs_hb, axes_f );
    TRANSPOSE_SUBCASE( case10, array_cs_db, axes_f );

    TRANSPOSE_SUBCASE( case10, array_fs_fb, axes_f );
    TRANSPOSE_SUBCASE( case10, array_fs_hb, axes_f );
    TRANSPOSE_SUBCASE( case10, array_fs_db, axes_f );

    TRANSPOSE_SUBCASE( case10, array_hs_fb, axes_f );
    TRANSPOSE_SUBCASE( case10, array_hs_hb, axes_f );
    TRANSPOSE_SUBCASE( case10, array_hs_db, axes_f );

    TRANSPOSE_SUBCASE( case10, array_ds_fb, axes_f );
    TRANSPOSE_SUBCASE( case10, array_ds_hb, axes_f );
    TRANSPOSE_SUBCASE( case10, array_ds_db, axes_f );

    TRANSPOSE_SUBCASE( case10, array_ls_fb, axes_f );
    TRANSPOSE_SUBCASE( case10, array_ls_hb, axes_f );
    TRANSPOSE_SUBCASE( case10, array_ls_db, axes_f );

    TRANSPOSE_SUBCASE( case10, array_cs_fb, axes_h );
    TRANSPOSE_SUBCASE( case10, array_cs_hb, axes_h );
    TRANSPOSE_SUBCASE( case10, array_cs_db, axes_h );

    TRANSPOSE_SUBCASE( case10, array_fs_fb, axes_h );
    TRANSPOSE_SUBCASE( case10, array_fs_hb, axes_h );
    TRANSPOSE_SUBCASE( case10, array_fs_db, axes_h );

    TRANSPOSE_SUBCASE( case10, array_hs_fb, axes_h );
    TRANSPOSE_SUBCASE( case10, array_hs_hb, axes_h );
    TRANSPOSE_SUBCASE( case10, array_hs_db, axes_h );

    TRANSPOSE_SUBCASE( case10, array_ds_fb, axes_h );
    TRANSPOSE_SUBCASE( case10, array_ds_hb, axes_h );
    TRANSPOSE_SUBCASE( case10, array_ds_db, axes_h );

    TRANSPOSE_SUBCASE( case10, array_ls_fb, axes_h );
    TRANSPOSE_SUBCASE( case10, array_ls_hb, axes_h );
    TRANSPOSE_SUBCASE( case10, array_ls_db, axes_h );

    TRANSPOSE_SUBCASE( case10, array_cs_fb, axes_v );
    TRANSPOSE_SUBCASE( case10, array_cs_hb, axes_v );
    TRANSPOSE_SUBCASE( case10, array_cs_db, axes_v );

    TRANSPOSE_SUBCASE( case10, array_fs_fb, axes_v );
    TRANSPOSE_SUBCASE( case10, array_fs_hb, axes_v );
    TRANSPOSE_SUBCASE( case10, array_fs_db, axes_v );

    TRANSPOSE_SUBCASE( case10, array_hs_fb, axes_v );
    TRANSPOSE_SUBCASE( case10, array_hs_hb, axes_v );
    TRANSPOSE_SUBCASE( case10, array_hs_db, axes_v );

    TRANSPOSE_SUBCASE( case10, array_ds_fb, axes_v );
    TRANSPOSE_SUBCASE( case10, array_ds_hb, axes_v );
    TRANSPOSE_SUBCASE( case10, array_ds_db, axes_v );

    TRANSPOSE_SUBCASE( case10, array_ls_fb, axes_v );
    TRANSPOSE_SUBCASE( case10, array_ls_hb, axes_v );
    TRANSPOSE_SUBCASE( case10, array_ls_db, axes_v );

    TRANSPOSE_SUBCASE( case10, array_cs_fb, axes_ct );
    TRANSPOSE_SUBCASE( case10, array_cs_hb, axes_ct );
    TRANSPOSE_SUBCASE( case10, array_cs_db, axes_ct );

    TRANSPOSE_SUBCASE( case10, array_fs_fb, axes_ct );
    TRANSPOSE_SUBCASE( case10, array_fs_hb, axes_ct );
    TRANSPOSE_SUBCASE( case10, array_fs_db, axes_ct );

    TRANSPOSE_SUBCASE( case10, array_hs_fb, axes_ct );
    TRANSPOSE_SUBCASE( case10, array_hs_hb, axes_ct );
    TRANSPOSE_SUBCASE( case10, array_hs_db, axes_ct );

    TRANSPOSE_SUBCASE( case10, array_ds_fb, axes_ct );
    TRANSPOSE_SUBCASE( case10, array_ds_hb, axes_ct );
    TRANSPOSE_SUBCASE( case10, array_ds_db, axes_ct );

    TRANSPOSE_SUBCASE( case10, array_ls_fb, axes_ct );
    TRANSPOSE_SUBCASE( case10, array_ls_hb, axes_ct );
    TRANSPOSE_SUBCASE( case10, array_ls_db, axes_ct );

    TRANSPOSE_SUBCASE( case10, array_cs_fb, axes_cl );
    TRANSPOSE_SUBCASE( case10, array_cs_hb, axes_cl );
    TRANSPOSE_SUBCASE( case10, array_cs_db, axes_cl );

    TRANSPOSE_SUBCASE( case10, array_fs_fb, axes_cl );
    TRANSPOSE_SUBCASE( case10, array_fs_hb, axes_cl );
    TRANSPOSE_SUBCASE( case10, array_fs_db, axes_cl );

    TRANSPOSE_SUBCASE( case10, array_hs_fb, axes_cl );
    TRANSPOSE_SUBCASE( case10, array_hs_hb, axes_cl );
    TRANSPOSE_SUBCASE( case10, array_hs_db, axes_cl );

    TRANSPOSE_SUBCASE( case10, array_ds_fb, axes_cl );
    TRANSPOSE_SUBCASE( case10, array_ds_hb, axes_cl );
    TRANSPOSE_SUBCASE( case10, array_ds_db, axes_cl );

    TRANSPOSE_SUBCASE( case10, array_ls_fb, axes_cl );
    TRANSPOSE_SUBCASE( case10, array_ls_hb, axes_cl );
    TRANSPOSE_SUBCASE( case10, array_ls_db, axes_cl );
    #endif
}

TEST_CASE("transpose(array)" * doctest::test_suite("view::transpose"))
{
    #if !defined(NMTOOLS_TESTING_GENERIC_NDARRAY)
    TRANSPOSE_SUBCASE( case1, array_a, axes_a );
    TRANSPOSE_SUBCASE( case2, array_a, axes_a );
    TRANSPOSE_SUBCASE( case3, array_a, axes_a );
    TRANSPOSE_SUBCASE( case4, array_a, axes_a );
    TRANSPOSE_SUBCASE( case5, array_a, axes_a );
    TRANSPOSE_SUBCASE( case6, array_a, axes_a );
    TRANSPOSE_SUBCASE( case7, array_a, axes_a );
    TRANSPOSE_SUBCASE( case8, array_a, axes_a );
    TRANSPOSE_SUBCASE( case9, array_a, axes_a );
    TRANSPOSE_SUBCASE( case10, array_a, axes_a );

    TRANSPOSE_SUBCASE( case1, array_a, axes_ct );
    TRANSPOSE_SUBCASE( case2, array_a, axes_ct );
    TRANSPOSE_SUBCASE( case3, array_a, axes_ct );
    TRANSPOSE_SUBCASE( case4, array_a, axes_ct );
    TRANSPOSE_SUBCASE( case5, array_a, axes_ct );
    TRANSPOSE_SUBCASE( case6, array_a, axes_ct );
    TRANSPOSE_SUBCASE( case7, array_a, axes_ct );
    TRANSPOSE_SUBCASE( case8, array_a, axes_ct );
    TRANSPOSE_SUBCASE( case9, array_a, axes_ct );
    TRANSPOSE_SUBCASE( case10, array_a, axes_ct );
    #else
    #endif
}

TEST_CASE("transpose(fixed_ndarray)" * doctest::test_suite("view::transpose"))
{
    #if !defined(NMTOOLS_TESTING_GENERIC_NDARRAY)
    TRANSPOSE_SUBCASE( case1, array_f, axes_a );
    TRANSPOSE_SUBCASE( case2, array_f, axes_a );
    TRANSPOSE_SUBCASE( case3, array_f, axes_a );
    TRANSPOSE_SUBCASE( case4, array_f, axes_a );
    TRANSPOSE_SUBCASE( case5, array_f, axes_a );
    TRANSPOSE_SUBCASE( case6, array_f, axes_a );
    TRANSPOSE_SUBCASE( case7, array_f, axes_a );
    TRANSPOSE_SUBCASE( case8, array_f, axes_a );
    TRANSPOSE_SUBCASE( case9, array_f, axes_a );
    TRANSPOSE_SUBCASE( case10, array_f, axes_a );

    TRANSPOSE_SUBCASE( case1, array_f, axes_ct );
    TRANSPOSE_SUBCASE( case2, array_f, axes_ct );
    TRANSPOSE_SUBCASE( case3, array_f, axes_ct );
    TRANSPOSE_SUBCASE( case4, array_f, axes_ct );
    TRANSPOSE_SUBCASE( case5, array_f, axes_ct );
    TRANSPOSE_SUBCASE( case6, array_f, axes_ct );
    TRANSPOSE_SUBCASE( case7, array_f, axes_ct );
    TRANSPOSE_SUBCASE( case8, array_f, axes_ct );
    TRANSPOSE_SUBCASE( case9, array_f, axes_ct );
    TRANSPOSE_SUBCASE( case10, array_f, axes_ct );
    #else
    #endif
}

TEST_CASE("transpose(hybrid_ndarray)" * doctest::test_suite("view::transpose"))
{
    #if !defined(NMTOOLS_TESTING_GENERIC_NDARRAY)
    TRANSPOSE_SUBCASE( case1, array_h, axes_a );
    TRANSPOSE_SUBCASE( case2, array_h, axes_a );
    TRANSPOSE_SUBCASE( case3, array_h, axes_a );
    TRANSPOSE_SUBCASE( case4, array_h, axes_a );
    TRANSPOSE_SUBCASE( case5, array_h, axes_a );
    TRANSPOSE_SUBCASE( case6, array_h, axes_a );
    TRANSPOSE_SUBCASE( case7, array_h, axes_a );
    TRANSPOSE_SUBCASE( case8, array_h, axes_a );
    TRANSPOSE_SUBCASE( case9, array_h, axes_a );
    TRANSPOSE_SUBCASE( case10, array_h, axes_a );
    #else
    #endif
}

TEST_CASE("transpose(dynamic_ndarray)" * doctest::test_suite("view::transpose"))
{
    #if !defined(NMTOOLS_TESTING_GENERIC_NDARRAY)
    TRANSPOSE_SUBCASE( case1, array_d, axes_a );
    TRANSPOSE_SUBCASE( case2, array_d, axes_a );
    TRANSPOSE_SUBCASE( case3, array_d, axes_a );
    TRANSPOSE_SUBCASE( case4, array_d, axes_a );
    TRANSPOSE_SUBCASE( case5, array_d, axes_a );
    TRANSPOSE_SUBCASE( case6, array_d, axes_a );
    TRANSPOSE_SUBCASE( case7, array_d, axes_a );
    TRANSPOSE_SUBCASE( case8, array_d, axes_a );
    TRANSPOSE_SUBCASE( case9, array_d, axes_a );
    TRANSPOSE_SUBCASE( case10, array_d, axes_a );

    TRANSPOSE_SUBCASE( case1, array_d, axes_v );
    TRANSPOSE_SUBCASE( case2, array_d, axes_v );
    TRANSPOSE_SUBCASE( case3, array_d, axes_v );
    TRANSPOSE_SUBCASE( case4, array_d, axes_v );
    TRANSPOSE_SUBCASE( case5, array_d, axes_v );
    TRANSPOSE_SUBCASE( case6, array_d, axes_v );
    TRANSPOSE_SUBCASE( case7, array_d, axes_v );
    TRANSPOSE_SUBCASE( case8, array_d, axes_v );
    TRANSPOSE_SUBCASE( case9, array_d, axes_v );
    TRANSPOSE_SUBCASE( case10, array_d, axes_v );
    #else
    #endif
}