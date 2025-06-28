#if defined(NMTOOLS_TESTING_GENERIC_NDARRAY)
#define NMTOOLS_CAST_ARRAYS_EXTRA(name) \
inline auto name##_cs_fb = nmtools::cast(name, nmtools::kind::ndarray_cs_fb); \
inline auto name##_cs_hb = nmtools::cast(name, nmtools::kind::ndarray_cs_hb); \
inline auto name##_cs_db = nmtools::cast(name, nmtools::kind::ndarray_cs_db); \
inline auto name##_fs_fb = nmtools::cast(name, nmtools::kind::ndarray_fs_fb); \
inline auto name##_fs_hb = nmtools::cast(name, nmtools::kind::ndarray_fs_hb); \
inline auto name##_fs_db = nmtools::cast(name, nmtools::kind::ndarray_fs_db); \
inline auto name##_hs_fb = nmtools::cast(name, nmtools::kind::ndarray_hs_fb); \
inline auto name##_hs_hb = nmtools::cast(name, nmtools::kind::ndarray_hs_hb); \
inline auto name##_hs_db = nmtools::cast(name, nmtools::kind::ndarray_hs_db); \
inline auto name##_ds_fb = nmtools::cast(name, nmtools::kind::ndarray_ds_fb); \
inline auto name##_ds_hb = nmtools::cast(name, nmtools::kind::ndarray_ds_hb); \
inline auto name##_ds_db = nmtools::cast(name, nmtools::kind::ndarray_ds_db); \
inline auto name##_ls_fb = nmtools::cast(name, nmtools::kind::ndarray_ls_fb); \
inline auto name##_ls_hb = nmtools::cast(name, nmtools::kind::ndarray_ls_hb); \
inline auto name##_ls_db = nmtools::cast(name, nmtools::kind::ndarray_ls_db);
#endif

#include "nmtools/array/where.hpp"
#include "nmtools/testing/doctest.hpp"
#include "nmtools/testing/data/array/where.hpp"

#define WHERE_SUBCASE(case_name,condition,x,y) \
SUBCASE(#case_name) \
{ \
    NMTOOLS_TESTING_USE_CASE( view, where, case_name ); \
    auto array_view = nmtools::view::where( args::condition, args::x, args::y ); \
    NMTOOLS_ASSERT_EQUAL( nmtools::dim(array_view), expect::dim ); \
    NMTOOLS_ASSERT_EQUAL( nmtools::shape(array_view), expect::shape ); \
    NMTOOLS_ASSERT_CLOSE( array_view, expect::result ); \
}

TEST_CASE("where(case1)" * doctest::test_suite("view::where"))
{
    #if !defined(NMTOOLS_TESTING_GENERIC_NDARRAY)
    WHERE_SUBCASE(case1, condition,   x,   y  );
    WHERE_SUBCASE(case1, condition_a, x_a, y_a);
    WHERE_SUBCASE(case1, condition_f, x_f, y_f);
    WHERE_SUBCASE(case1, condition_d, x_d, y_d);
    WHERE_SUBCASE(case1, condition_h, x_h, y_h);
    
    #else
    WHERE_SUBCASE(case1, condition_cs_fb, x_cs_fb, y_cs_fb);
    WHERE_SUBCASE(case1, condition_cs_hb, x_cs_hb, y_cs_hb);
    WHERE_SUBCASE(case1, condition_cs_db, x_cs_db, y_cs_db);

    WHERE_SUBCASE(case1, condition_fs_fb, x_fs_fb, y_fs_fb);
    WHERE_SUBCASE(case1, condition_fs_hb, x_fs_hb, y_fs_hb);
    WHERE_SUBCASE(case1, condition_fs_db, x_fs_db, y_fs_db);

    WHERE_SUBCASE(case1, condition_hs_fb, x_hs_fb, y_hs_fb);
    WHERE_SUBCASE(case1, condition_hs_hb, x_hs_hb, y_hs_hb);
    WHERE_SUBCASE(case1, condition_hs_db, x_hs_db, y_hs_db);

    WHERE_SUBCASE(case1, condition_ds_fb, x_ds_fb, y_ds_fb);
    WHERE_SUBCASE(case1, condition_ds_hb, x_ds_hb, y_ds_hb);
    WHERE_SUBCASE(case1, condition_ds_db, x_ds_db, y_ds_db);

    WHERE_SUBCASE(case1, condition_ls_fb, x_ls_fb, y_ls_fb);
    WHERE_SUBCASE(case1, condition_ls_hb, x_ls_hb, y_ls_hb);
    WHERE_SUBCASE(case1, condition_ls_db, x_ls_db, y_ls_db);
    #endif
}

TEST_CASE("where(case2)" * doctest::test_suite("view::where"))
{
    #if !defined(NMTOOLS_TESTING_GENERIC_NDARRAY)
    WHERE_SUBCASE(case2, condition,   x,   y  );
    WHERE_SUBCASE(case2, condition_a, x_a, y_a);
    WHERE_SUBCASE(case2, condition_f, x_f, y_f);
    WHERE_SUBCASE(case2, condition_d, x_d, y_d);
    WHERE_SUBCASE(case2, condition_h, x_h, y_h);

    #else
    WHERE_SUBCASE(case2, condition_cs_fb, x_cs_fb, y_cs_fb);
    WHERE_SUBCASE(case2, condition_cs_hb, x_cs_hb, y_cs_hb);
    WHERE_SUBCASE(case2, condition_cs_db, x_cs_db, y_cs_db);

    WHERE_SUBCASE(case2, condition_fs_fb, x_fs_fb, y_fs_fb);
    WHERE_SUBCASE(case2, condition_fs_hb, x_fs_hb, y_fs_hb);
    WHERE_SUBCASE(case2, condition_fs_db, x_fs_db, y_fs_db);

    WHERE_SUBCASE(case2, condition_hs_fb, x_hs_fb, y_hs_fb);
    WHERE_SUBCASE(case2, condition_hs_hb, x_hs_hb, y_hs_hb);
    WHERE_SUBCASE(case2, condition_hs_db, x_hs_db, y_hs_db);

    WHERE_SUBCASE(case2, condition_ds_fb, x_ds_fb, y_ds_fb);
    WHERE_SUBCASE(case2, condition_ds_hb, x_ds_hb, y_ds_hb);
    WHERE_SUBCASE(case2, condition_ds_db, x_ds_db, y_ds_db);

    WHERE_SUBCASE(case2, condition_ls_fb, x_ls_fb, y_ls_fb);
    WHERE_SUBCASE(case2, condition_ls_hb, x_ls_hb, y_ls_hb);
    WHERE_SUBCASE(case2, condition_ls_db, x_ls_db, y_ls_db);
    #endif
}

TEST_CASE("where(case3)" * doctest::test_suite("view::where"))
{
    #if !defined(NMTOOLS_TESTING_GENERIC_NDARRAY)
    WHERE_SUBCASE(case3, condition,   x,   y  );
    WHERE_SUBCASE(case3, condition_a, x_a, y_a);
    WHERE_SUBCASE(case3, condition_f, x_f, y_f);
    WHERE_SUBCASE(case3, condition_d, x_d, y_d);
    WHERE_SUBCASE(case3, condition_h, x_h, y_h);

    #else
    WHERE_SUBCASE(case3, condition_cs_fb, x_cs_fb, y_cs_fb);
    WHERE_SUBCASE(case3, condition_cs_hb, x_cs_hb, y_cs_hb);
    WHERE_SUBCASE(case3, condition_cs_db, x_cs_db, y_cs_db);

    WHERE_SUBCASE(case3, condition_fs_fb, x_fs_fb, y_fs_fb);
    WHERE_SUBCASE(case3, condition_fs_hb, x_fs_hb, y_fs_hb);
    WHERE_SUBCASE(case3, condition_fs_db, x_fs_db, y_fs_db);

    WHERE_SUBCASE(case3, condition_hs_fb, x_hs_fb, y_hs_fb);
    WHERE_SUBCASE(case3, condition_hs_hb, x_hs_hb, y_hs_hb);
    WHERE_SUBCASE(case3, condition_hs_db, x_hs_db, y_hs_db);

    WHERE_SUBCASE(case3, condition_ds_fb, x_ds_fb, y_ds_fb);
    WHERE_SUBCASE(case3, condition_ds_hb, x_ds_hb, y_ds_hb);
    WHERE_SUBCASE(case3, condition_ds_db, x_ds_db, y_ds_db);

    WHERE_SUBCASE(case3, condition_ds_fb, x_ls_fb, y_ls_fb);
    WHERE_SUBCASE(case3, condition_ds_hb, x_ls_hb, y_ls_hb);
    WHERE_SUBCASE(case3, condition_ds_db, x_ls_db, y_ls_db);
    #endif
}