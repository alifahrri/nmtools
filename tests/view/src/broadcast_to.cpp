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

#include "nmtools/array/broadcast_to.hpp"
#include "nmtools/testing/data/array/broadcast_to.hpp"
#include "nmtools/testing/doctest.hpp"
#include "nmtools/constants.hpp"

namespace nm = nmtools;
namespace na = nmtools;
namespace view = nm::view;

#define BROADCAST_TO_SUBCASE(case_name, array, shape_, expected) \
SUBCASE(#case_name) \
{ \
    NMTOOLS_TESTING_USE_CASE(broadcast_to, case_name); \
    auto array_ref = view::broadcast_to(args::array,args::shape_); \
    NMTOOLS_ASSERT_EQUAL( nmtools::shape(array_ref), nmtools::shape(expect::expected) ); \
    NMTOOLS_ASSERT_CLOSE( array_ref, expect::expected ); \
}

TEST_CASE("broadcast_to(case1)" * doctest::test_suite("view::broadcast_to"))
{
    #if !defined(NMTOOLS_TESTING_GENERIC_NDARRAY)
    BROADCAST_TO_SUBCASE( case1, x_a, shape, expected );
    BROADCAST_TO_SUBCASE( case1, x_f, shape, expected );
    BROADCAST_TO_SUBCASE( case1, x_d, shape, expected );
    BROADCAST_TO_SUBCASE( case1, x_h, shape, expected );

    BROADCAST_TO_SUBCASE( case1, x_a, shape_ct, expected );
    BROADCAST_TO_SUBCASE( case1, x_f, shape_ct, expected );
    BROADCAST_TO_SUBCASE( case1, x_d, shape_ct, expected );
    BROADCAST_TO_SUBCASE( case1, x_h, shape_ct, expected );

    BROADCAST_TO_SUBCASE( case1, x_a, shape_cl, expected );
    BROADCAST_TO_SUBCASE( case1, x_f, shape_cl, expected );
    BROADCAST_TO_SUBCASE( case1, x_d, shape_cl, expected );
    BROADCAST_TO_SUBCASE( case1, x_h, shape_cl, expected );

    #else
    BROADCAST_TO_SUBCASE( case1, x_cs_fb, shape, expected );
    BROADCAST_TO_SUBCASE( case1, x_cs_hb, shape, expected );
    BROADCAST_TO_SUBCASE( case1, x_cs_db, shape, expected );

    BROADCAST_TO_SUBCASE( case1, x_cs_fb, shape_ct, expected );
    BROADCAST_TO_SUBCASE( case1, x_cs_hb, shape_ct, expected );
    BROADCAST_TO_SUBCASE( case1, x_cs_db, shape_ct, expected );

    BROADCAST_TO_SUBCASE( case1, x_cs_fb, shape_cl, expected );
    BROADCAST_TO_SUBCASE( case1, x_cs_hb, shape_cl, expected );
    BROADCAST_TO_SUBCASE( case1, x_cs_db, shape_cl, expected );

    BROADCAST_TO_SUBCASE( case1, x_fs_fb, shape, expected );
    BROADCAST_TO_SUBCASE( case1, x_fs_hb, shape, expected );
    BROADCAST_TO_SUBCASE( case1, x_fs_db, shape, expected );

    BROADCAST_TO_SUBCASE( case1, x_fs_fb, shape_ct, expected );
    BROADCAST_TO_SUBCASE( case1, x_fs_hb, shape_ct, expected );
    BROADCAST_TO_SUBCASE( case1, x_fs_db, shape_ct, expected );

    BROADCAST_TO_SUBCASE( case1, x_fs_fb, shape_cl, expected );
    BROADCAST_TO_SUBCASE( case1, x_fs_hb, shape_cl, expected );
    BROADCAST_TO_SUBCASE( case1, x_fs_db, shape_cl, expected );

    BROADCAST_TO_SUBCASE( case1, x_hs_fb, shape, expected );
    BROADCAST_TO_SUBCASE( case1, x_hs_hb, shape, expected );
    BROADCAST_TO_SUBCASE( case1, x_hs_db, shape, expected );

    BROADCAST_TO_SUBCASE( case1, x_hs_fb, shape_ct, expected );
    BROADCAST_TO_SUBCASE( case1, x_hs_hb, shape_ct, expected );
    BROADCAST_TO_SUBCASE( case1, x_hs_db, shape_ct, expected );

    BROADCAST_TO_SUBCASE( case1, x_hs_fb, shape_cl, expected );
    BROADCAST_TO_SUBCASE( case1, x_hs_hb, shape_cl, expected );
    BROADCAST_TO_SUBCASE( case1, x_hs_db, shape_cl, expected );

    BROADCAST_TO_SUBCASE( case1, x_ds_fb, shape, expected );
    BROADCAST_TO_SUBCASE( case1, x_ds_hb, shape, expected );
    BROADCAST_TO_SUBCASE( case1, x_ds_db, shape, expected );

    BROADCAST_TO_SUBCASE( case1, x_ds_fb, shape_ct, expected );
    BROADCAST_TO_SUBCASE( case1, x_ds_hb, shape_ct, expected );
    BROADCAST_TO_SUBCASE( case1, x_ds_db, shape_ct, expected );

    BROADCAST_TO_SUBCASE( case1, x_ds_fb, shape_cl, expected );
    BROADCAST_TO_SUBCASE( case1, x_ds_hb, shape_cl, expected );
    BROADCAST_TO_SUBCASE( case1, x_ds_db, shape_cl, expected );

    BROADCAST_TO_SUBCASE( case1, x_ls_fb, shape, expected );
    BROADCAST_TO_SUBCASE( case1, x_ls_hb, shape, expected );
    BROADCAST_TO_SUBCASE( case1, x_ls_db, shape, expected );

    BROADCAST_TO_SUBCASE( case1, x_ls_fb, shape_ct, expected );
    BROADCAST_TO_SUBCASE( case1, x_ls_hb, shape_ct, expected );
    BROADCAST_TO_SUBCASE( case1, x_ls_db, shape_ct, expected );

    BROADCAST_TO_SUBCASE( case1, x_ls_fb, shape_cl, expected );
    BROADCAST_TO_SUBCASE( case1, x_ls_hb, shape_cl, expected );
    BROADCAST_TO_SUBCASE( case1, x_ls_db, shape_cl, expected );
    #endif
}

TEST_CASE("broadcast_to(case2)" * doctest::test_suite("view::broadcast_to"))
{
    #if !defined(NMTOOLS_TESTING_GENERIC_NDARRAY)
    BROADCAST_TO_SUBCASE( case2, x_a, shape, expected );
    BROADCAST_TO_SUBCASE( case2, x_f, shape, expected );
    BROADCAST_TO_SUBCASE( case2, x_d, shape, expected );
    BROADCAST_TO_SUBCASE( case2, x_h, shape, expected );

    BROADCAST_TO_SUBCASE( case2, x_a, shape_ct, expected );
    BROADCAST_TO_SUBCASE( case2, x_f, shape_ct, expected );
    BROADCAST_TO_SUBCASE( case2, x_d, shape_ct, expected );
    BROADCAST_TO_SUBCASE( case2, x_h, shape_ct, expected );

    BROADCAST_TO_SUBCASE( case2, x_a, shape_cl, expected );
    BROADCAST_TO_SUBCASE( case2, x_f, shape_cl, expected );
    BROADCAST_TO_SUBCASE( case2, x_d, shape_cl, expected );
    BROADCAST_TO_SUBCASE( case2, x_h, shape_cl, expected );

    #else
    BROADCAST_TO_SUBCASE( case1, x_cs_fb, shape, expected );
    BROADCAST_TO_SUBCASE( case1, x_cs_hb, shape, expected );
    BROADCAST_TO_SUBCASE( case1, x_cs_db, shape, expected );

    BROADCAST_TO_SUBCASE( case1, x_cs_fb, shape_ct, expected );
    BROADCAST_TO_SUBCASE( case1, x_cs_hb, shape_ct, expected );
    BROADCAST_TO_SUBCASE( case1, x_cs_db, shape_ct, expected );

    BROADCAST_TO_SUBCASE( case1, x_cs_fb, shape_cl, expected );
    BROADCAST_TO_SUBCASE( case1, x_cs_hb, shape_cl, expected );
    BROADCAST_TO_SUBCASE( case1, x_cs_db, shape_cl, expected );

    BROADCAST_TO_SUBCASE( case2, x_fs_fb, shape, expected );
    BROADCAST_TO_SUBCASE( case2, x_fs_hb, shape, expected );
    BROADCAST_TO_SUBCASE( case2, x_fs_db, shape, expected );

    BROADCAST_TO_SUBCASE( case1, x_fs_fb, shape_ct, expected );
    BROADCAST_TO_SUBCASE( case1, x_fs_hb, shape_ct, expected );
    BROADCAST_TO_SUBCASE( case1, x_fs_db, shape_ct, expected );

    BROADCAST_TO_SUBCASE( case1, x_fs_fb, shape_cl, expected );
    BROADCAST_TO_SUBCASE( case1, x_fs_hb, shape_cl, expected );
    BROADCAST_TO_SUBCASE( case1, x_fs_db, shape_cl, expected );

    BROADCAST_TO_SUBCASE( case2, x_hs_fb, shape, expected );
    BROADCAST_TO_SUBCASE( case2, x_hs_hb, shape, expected );
    BROADCAST_TO_SUBCASE( case2, x_hs_db, shape, expected );

    BROADCAST_TO_SUBCASE( case1, x_hs_fb, shape_ct, expected );
    BROADCAST_TO_SUBCASE( case1, x_hs_hb, shape_ct, expected );
    BROADCAST_TO_SUBCASE( case1, x_hs_db, shape_ct, expected );

    BROADCAST_TO_SUBCASE( case1, x_hs_fb, shape_cl, expected );
    BROADCAST_TO_SUBCASE( case1, x_hs_hb, shape_cl, expected );
    BROADCAST_TO_SUBCASE( case1, x_hs_db, shape_cl, expected );

    BROADCAST_TO_SUBCASE( case2, x_ds_fb, shape, expected );
    BROADCAST_TO_SUBCASE( case2, x_ds_hb, shape, expected );
    BROADCAST_TO_SUBCASE( case2, x_ds_db, shape, expected );

    BROADCAST_TO_SUBCASE( case2, x_ds_fb, shape_ct, expected );
    BROADCAST_TO_SUBCASE( case2, x_ds_hb, shape_ct, expected );
    BROADCAST_TO_SUBCASE( case2, x_ds_db, shape_ct, expected );

    BROADCAST_TO_SUBCASE( case2, x_ds_fb, shape_cl, expected );
    BROADCAST_TO_SUBCASE( case2, x_ds_hb, shape_cl, expected );
    BROADCAST_TO_SUBCASE( case2, x_ds_db, shape_cl, expected );

    BROADCAST_TO_SUBCASE( case2, x_ls_fb, shape, expected );
    BROADCAST_TO_SUBCASE( case2, x_ls_hb, shape, expected );
    BROADCAST_TO_SUBCASE( case2, x_ls_db, shape, expected );

    BROADCAST_TO_SUBCASE( case2, x_ls_fb, shape_ct, expected );
    BROADCAST_TO_SUBCASE( case2, x_ls_hb, shape_ct, expected );
    BROADCAST_TO_SUBCASE( case2, x_ls_db, shape_ct, expected );

    BROADCAST_TO_SUBCASE( case2, x_ls_fb, shape_cl, expected );
    BROADCAST_TO_SUBCASE( case2, x_ls_hb, shape_cl, expected );
    BROADCAST_TO_SUBCASE( case2, x_ls_db, shape_cl, expected );
    #endif
}

TEST_CASE("broadcast_to(case3)" * doctest::test_suite("view::broadcast_to"))
{
    #if !defined(NMTOOLS_TESTING_GENERIC_NDARRAY)
    BROADCAST_TO_SUBCASE( case3, x_a, shape, expected );
    BROADCAST_TO_SUBCASE( case3, x_f, shape, expected );
    BROADCAST_TO_SUBCASE( case3, x_d, shape, expected );
    BROADCAST_TO_SUBCASE( case3, x_h, shape, expected );

    BROADCAST_TO_SUBCASE( case3, x_a, shape_ct, expected );
    BROADCAST_TO_SUBCASE( case3, x_f, shape_ct, expected );
    BROADCAST_TO_SUBCASE( case3, x_d, shape_ct, expected );
    BROADCAST_TO_SUBCASE( case3, x_h, shape_ct, expected );

    BROADCAST_TO_SUBCASE( case3, x_a, shape_cl, expected );
    BROADCAST_TO_SUBCASE( case3, x_f, shape_cl, expected );
    BROADCAST_TO_SUBCASE( case3, x_d, shape_cl, expected );
    BROADCAST_TO_SUBCASE( case3, x_h, shape_cl, expected );

    #else
    BROADCAST_TO_SUBCASE( case3, x_cs_fb, shape, expected );
    BROADCAST_TO_SUBCASE( case3, x_cs_hb, shape, expected );
    BROADCAST_TO_SUBCASE( case3, x_cs_db, shape, expected );

    BROADCAST_TO_SUBCASE( case3, x_cs_fb, shape_ct, expected );
    BROADCAST_TO_SUBCASE( case3, x_cs_hb, shape_ct, expected );
    BROADCAST_TO_SUBCASE( case3, x_cs_db, shape_ct, expected );

    BROADCAST_TO_SUBCASE( case3, x_cs_fb, shape_cl, expected );
    BROADCAST_TO_SUBCASE( case3, x_cs_hb, shape_cl, expected );
    BROADCAST_TO_SUBCASE( case3, x_cs_db, shape_cl, expected );

    BROADCAST_TO_SUBCASE( case3, x_fs_fb, shape, expected );
    BROADCAST_TO_SUBCASE( case3, x_fs_hb, shape, expected );
    BROADCAST_TO_SUBCASE( case3, x_fs_db, shape, expected );

    BROADCAST_TO_SUBCASE( case3, x_fs_fb, shape_ct, expected );
    BROADCAST_TO_SUBCASE( case3, x_fs_hb, shape_ct, expected );
    BROADCAST_TO_SUBCASE( case3, x_fs_db, shape_ct, expected );

    BROADCAST_TO_SUBCASE( case3, x_fs_fb, shape_cl, expected );
    BROADCAST_TO_SUBCASE( case3, x_fs_hb, shape_cl, expected );
    BROADCAST_TO_SUBCASE( case3, x_fs_db, shape_cl, expected );

    BROADCAST_TO_SUBCASE( case3, x_hs_fb, shape, expected );
    BROADCAST_TO_SUBCASE( case3, x_hs_hb, shape, expected );
    BROADCAST_TO_SUBCASE( case3, x_hs_db, shape, expected );

    BROADCAST_TO_SUBCASE( case3, x_hs_fb, shape_ct, expected );
    BROADCAST_TO_SUBCASE( case3, x_hs_hb, shape_ct, expected );
    BROADCAST_TO_SUBCASE( case3, x_hs_db, shape_ct, expected );

    BROADCAST_TO_SUBCASE( case3, x_hs_fb, shape_cl, expected );
    BROADCAST_TO_SUBCASE( case3, x_hs_hb, shape_cl, expected );
    BROADCAST_TO_SUBCASE( case3, x_hs_db, shape_cl, expected );

    BROADCAST_TO_SUBCASE( case3, x_ds_fb, shape, expected );
    BROADCAST_TO_SUBCASE( case3, x_ds_hb, shape, expected );
    BROADCAST_TO_SUBCASE( case3, x_ds_db, shape, expected );

    BROADCAST_TO_SUBCASE( case3, x_ds_fb, shape_ct, expected );
    BROADCAST_TO_SUBCASE( case3, x_ds_hb, shape_ct, expected );
    BROADCAST_TO_SUBCASE( case3, x_ds_db, shape_ct, expected );

    BROADCAST_TO_SUBCASE( case3, x_ds_fb, shape_cl, expected );
    BROADCAST_TO_SUBCASE( case3, x_ds_hb, shape_cl, expected );
    BROADCAST_TO_SUBCASE( case3, x_ds_db, shape_cl, expected );

    BROADCAST_TO_SUBCASE( case3, x_ls_fb, shape, expected );
    BROADCAST_TO_SUBCASE( case3, x_ls_hb, shape, expected );
    BROADCAST_TO_SUBCASE( case3, x_ls_db, shape, expected );

    BROADCAST_TO_SUBCASE( case3, x_ls_fb, shape_ct, expected );
    BROADCAST_TO_SUBCASE( case3, x_ls_hb, shape_ct, expected );
    BROADCAST_TO_SUBCASE( case3, x_ls_db, shape_ct, expected );

    BROADCAST_TO_SUBCASE( case3, x_ls_fb, shape_cl, expected );
    BROADCAST_TO_SUBCASE( case3, x_ls_hb, shape_cl, expected );
    BROADCAST_TO_SUBCASE( case3, x_ls_db, shape_cl, expected );
    #endif
}

TEST_CASE("broadcast_to(case4)" * doctest::test_suite("view::broadcast_to"))
{
    #if !defined(NMTOOLS_TESTING_GENERIC_NDARRAY)
    BROADCAST_TO_SUBCASE( case4, x_a, shape, expected );
    BROADCAST_TO_SUBCASE( case4, x_f, shape, expected );
    BROADCAST_TO_SUBCASE( case4, x_d, shape, expected );
    BROADCAST_TO_SUBCASE( case4, x_h, shape, expected );

    BROADCAST_TO_SUBCASE( case4, x_a, shape_ct, expected );
    BROADCAST_TO_SUBCASE( case4, x_f, shape_ct, expected );
    BROADCAST_TO_SUBCASE( case4, x_d, shape_ct, expected );
    BROADCAST_TO_SUBCASE( case4, x_h, shape_ct, expected );

    BROADCAST_TO_SUBCASE( case4, x_a, shape_cl, expected );
    BROADCAST_TO_SUBCASE( case4, x_f, shape_cl, expected );
    BROADCAST_TO_SUBCASE( case4, x_d, shape_cl, expected );
    BROADCAST_TO_SUBCASE( case4, x_h, shape_cl, expected );

    #else
    BROADCAST_TO_SUBCASE( case4, x_cs_fb, shape, expected );
    BROADCAST_TO_SUBCASE( case4, x_cs_hb, shape, expected );
    BROADCAST_TO_SUBCASE( case4, x_cs_db, shape, expected );

    BROADCAST_TO_SUBCASE( case4, x_cs_fb, shape_ct, expected );
    BROADCAST_TO_SUBCASE( case4, x_cs_hb, shape_ct, expected );
    BROADCAST_TO_SUBCASE( case4, x_cs_db, shape_ct, expected );

    BROADCAST_TO_SUBCASE( case4, x_cs_fb, shape_cl, expected );
    BROADCAST_TO_SUBCASE( case4, x_cs_hb, shape_cl, expected );
    BROADCAST_TO_SUBCASE( case4, x_cs_db, shape_cl, expected );

    BROADCAST_TO_SUBCASE( case4, x_fs_fb, shape, expected );
    BROADCAST_TO_SUBCASE( case4, x_fs_hb, shape, expected );
    BROADCAST_TO_SUBCASE( case4, x_fs_db, shape, expected );

    BROADCAST_TO_SUBCASE( case4, x_fs_fb, shape_ct, expected );
    BROADCAST_TO_SUBCASE( case4, x_fs_hb, shape_ct, expected );
    BROADCAST_TO_SUBCASE( case4, x_fs_db, shape_ct, expected );

    BROADCAST_TO_SUBCASE( case4, x_fs_fb, shape_cl, expected );
    BROADCAST_TO_SUBCASE( case4, x_fs_hb, shape_cl, expected );
    BROADCAST_TO_SUBCASE( case4, x_fs_db, shape_cl, expected );

    BROADCAST_TO_SUBCASE( case4, x_hs_fb, shape, expected );
    BROADCAST_TO_SUBCASE( case4, x_hs_hb, shape, expected );
    BROADCAST_TO_SUBCASE( case4, x_hs_db, shape, expected );

    BROADCAST_TO_SUBCASE( case4, x_hs_fb, shape_ct, expected );
    BROADCAST_TO_SUBCASE( case4, x_hs_hb, shape_ct, expected );
    BROADCAST_TO_SUBCASE( case4, x_hs_db, shape_ct, expected );

    BROADCAST_TO_SUBCASE( case4, x_hs_fb, shape_cl, expected );
    BROADCAST_TO_SUBCASE( case4, x_hs_hb, shape_cl, expected );
    BROADCAST_TO_SUBCASE( case4, x_hs_db, shape_cl, expected );

    BROADCAST_TO_SUBCASE( case4, x_ds_fb, shape, expected );
    BROADCAST_TO_SUBCASE( case4, x_ds_hb, shape, expected );
    BROADCAST_TO_SUBCASE( case4, x_ds_db, shape, expected );

    BROADCAST_TO_SUBCASE( case4, x_ds_fb, shape_ct, expected );
    BROADCAST_TO_SUBCASE( case4, x_ds_hb, shape_ct, expected );
    BROADCAST_TO_SUBCASE( case4, x_ds_db, shape_ct, expected );

    BROADCAST_TO_SUBCASE( case4, x_ds_fb, shape_cl, expected );
    BROADCAST_TO_SUBCASE( case4, x_ds_hb, shape_cl, expected );
    BROADCAST_TO_SUBCASE( case4, x_ds_db, shape_cl, expected );

    BROADCAST_TO_SUBCASE( case4, x_ls_fb, shape, expected );
    BROADCAST_TO_SUBCASE( case4, x_ls_hb, shape, expected );
    BROADCAST_TO_SUBCASE( case4, x_ls_db, shape, expected );

    BROADCAST_TO_SUBCASE( case4, x_ls_fb, shape_ct, expected );
    BROADCAST_TO_SUBCASE( case4, x_ls_hb, shape_ct, expected );
    BROADCAST_TO_SUBCASE( case4, x_ls_db, shape_ct, expected );

    BROADCAST_TO_SUBCASE( case4, x_ls_fb, shape_cl, expected );
    BROADCAST_TO_SUBCASE( case4, x_ls_hb, shape_cl, expected );
    BROADCAST_TO_SUBCASE( case4, x_ls_db, shape_cl, expected );
    #endif
}

TEST_CASE("broadcast_to(case5)" * doctest::test_suite("view::broadcast_to"))
{
    #if !defined(NMTOOLS_TESTING_GENERIC_NDARRAY)
    BROADCAST_TO_SUBCASE( case5, x_a, shape, expected );
    BROADCAST_TO_SUBCASE( case5, x_f, shape, expected );
    BROADCAST_TO_SUBCASE( case5, x_d, shape, expected );
    BROADCAST_TO_SUBCASE( case5, x_h, shape, expected );

    BROADCAST_TO_SUBCASE( case5, x_a, shape_ct, expected );
    BROADCAST_TO_SUBCASE( case5, x_f, shape_ct, expected );
    BROADCAST_TO_SUBCASE( case5, x_d, shape_ct, expected );
    BROADCAST_TO_SUBCASE( case5, x_h, shape_ct, expected );

    BROADCAST_TO_SUBCASE( case5, x_a, shape_cl, expected );
    BROADCAST_TO_SUBCASE( case5, x_f, shape_cl, expected );
    BROADCAST_TO_SUBCASE( case5, x_d, shape_cl, expected );
    BROADCAST_TO_SUBCASE( case5, x_h, shape_cl, expected );

    #else
    BROADCAST_TO_SUBCASE( case5, x_cs_fb, shape, expected );
    BROADCAST_TO_SUBCASE( case5, x_cs_hb, shape, expected );
    BROADCAST_TO_SUBCASE( case5, x_cs_db, shape, expected );

    BROADCAST_TO_SUBCASE( case5, x_cs_fb, shape_ct, expected );
    BROADCAST_TO_SUBCASE( case5, x_cs_hb, shape_ct, expected );
    BROADCAST_TO_SUBCASE( case5, x_cs_db, shape_ct, expected );

    BROADCAST_TO_SUBCASE( case5, x_cs_fb, shape_cl, expected );
    BROADCAST_TO_SUBCASE( case5, x_cs_hb, shape_cl, expected );
    BROADCAST_TO_SUBCASE( case5, x_cs_db, shape_cl, expected );

    BROADCAST_TO_SUBCASE( case5, x_fs_fb, shape, expected );
    BROADCAST_TO_SUBCASE( case5, x_fs_hb, shape, expected );
    BROADCAST_TO_SUBCASE( case5, x_fs_db, shape, expected );

    BROADCAST_TO_SUBCASE( case5, x_fs_fb, shape_ct, expected );
    BROADCAST_TO_SUBCASE( case5, x_fs_hb, shape_ct, expected );
    BROADCAST_TO_SUBCASE( case5, x_fs_db, shape_ct, expected );

    BROADCAST_TO_SUBCASE( case5, x_fs_fb, shape_cl, expected );
    BROADCAST_TO_SUBCASE( case5, x_fs_hb, shape_cl, expected );
    BROADCAST_TO_SUBCASE( case5, x_fs_db, shape_cl, expected );

    BROADCAST_TO_SUBCASE( case5, x_hs_fb, shape, expected );
    BROADCAST_TO_SUBCASE( case5, x_hs_hb, shape, expected );
    BROADCAST_TO_SUBCASE( case5, x_hs_db, shape, expected );

    BROADCAST_TO_SUBCASE( case5, x_hs_fb, shape_ct, expected );
    BROADCAST_TO_SUBCASE( case5, x_hs_hb, shape_ct, expected );
    BROADCAST_TO_SUBCASE( case5, x_hs_db, shape_ct, expected );

    BROADCAST_TO_SUBCASE( case5, x_hs_fb, shape_cl, expected );
    BROADCAST_TO_SUBCASE( case5, x_hs_hb, shape_cl, expected );
    BROADCAST_TO_SUBCASE( case5, x_hs_db, shape_cl, expected );

    BROADCAST_TO_SUBCASE( case5, x_ds_fb, shape, expected );
    BROADCAST_TO_SUBCASE( case5, x_ds_hb, shape, expected );
    BROADCAST_TO_SUBCASE( case5, x_ds_db, shape, expected );

    BROADCAST_TO_SUBCASE( case5, x_ds_fb, shape_ct, expected );
    BROADCAST_TO_SUBCASE( case5, x_ds_hb, shape_ct, expected );
    BROADCAST_TO_SUBCASE( case5, x_ds_db, shape_ct, expected );

    BROADCAST_TO_SUBCASE( case5, x_ds_fb, shape_cl, expected );
    BROADCAST_TO_SUBCASE( case5, x_ds_hb, shape_cl, expected );
    BROADCAST_TO_SUBCASE( case5, x_ds_db, shape_cl, expected );

    BROADCAST_TO_SUBCASE( case5, x_ls_fb, shape, expected );
    BROADCAST_TO_SUBCASE( case5, x_ls_hb, shape, expected );
    BROADCAST_TO_SUBCASE( case5, x_ls_db, shape, expected );

    BROADCAST_TO_SUBCASE( case5, x_ls_fb, shape_ct, expected );
    BROADCAST_TO_SUBCASE( case5, x_ls_hb, shape_ct, expected );
    BROADCAST_TO_SUBCASE( case5, x_ls_db, shape_ct, expected );

    BROADCAST_TO_SUBCASE( case5, x_ls_fb, shape_cl, expected );
    BROADCAST_TO_SUBCASE( case5, x_ls_hb, shape_cl, expected );
    BROADCAST_TO_SUBCASE( case5, x_ls_db, shape_cl, expected );
    #endif
}

TEST_CASE("broadcast_to(case6)" * doctest::test_suite("view::broadcast_to"))
{
    #if !defined(NMTOOLS_TESTING_GENERIC_NDARRAY)
    BROADCAST_TO_SUBCASE( case6, x_a, shape, expected );
    BROADCAST_TO_SUBCASE( case6, x_f, shape, expected );
    BROADCAST_TO_SUBCASE( case6, x_d, shape, expected );
    BROADCAST_TO_SUBCASE( case6, x_h, shape, expected );

    BROADCAST_TO_SUBCASE( case6, x_a, shape_ct, expected );
    BROADCAST_TO_SUBCASE( case6, x_f, shape_ct, expected );
    BROADCAST_TO_SUBCASE( case6, x_d, shape_ct, expected );
    BROADCAST_TO_SUBCASE( case6, x_h, shape_ct, expected );

    BROADCAST_TO_SUBCASE( case6, x_a, shape_cl, expected );
    BROADCAST_TO_SUBCASE( case6, x_f, shape_cl, expected );
    BROADCAST_TO_SUBCASE( case6, x_d, shape_cl, expected );
    BROADCAST_TO_SUBCASE( case6, x_h, shape_cl, expected );

    #else
    BROADCAST_TO_SUBCASE( case6, x_cs_fb, shape, expected );
    BROADCAST_TO_SUBCASE( case6, x_cs_hb, shape, expected );
    BROADCAST_TO_SUBCASE( case6, x_cs_db, shape, expected );

    BROADCAST_TO_SUBCASE( case6, x_cs_fb, shape_ct, expected );
    BROADCAST_TO_SUBCASE( case6, x_cs_hb, shape_ct, expected );
    BROADCAST_TO_SUBCASE( case6, x_cs_db, shape_ct, expected );

    BROADCAST_TO_SUBCASE( case6, x_cs_fb, shape_cl, expected );
    BROADCAST_TO_SUBCASE( case6, x_cs_hb, shape_cl, expected );
    BROADCAST_TO_SUBCASE( case6, x_cs_db, shape_cl, expected );

    BROADCAST_TO_SUBCASE( case6, x_fs_fb, shape, expected );
    BROADCAST_TO_SUBCASE( case6, x_fs_hb, shape, expected );
    BROADCAST_TO_SUBCASE( case6, x_fs_db, shape, expected );

    BROADCAST_TO_SUBCASE( case6, x_fs_fb, shape_ct, expected );
    BROADCAST_TO_SUBCASE( case6, x_fs_hb, shape_ct, expected );
    BROADCAST_TO_SUBCASE( case6, x_fs_db, shape_ct, expected );

    BROADCAST_TO_SUBCASE( case6, x_fs_fb, shape_cl, expected );
    BROADCAST_TO_SUBCASE( case6, x_fs_hb, shape_cl, expected );
    BROADCAST_TO_SUBCASE( case6, x_fs_db, shape_cl, expected );

    BROADCAST_TO_SUBCASE( case6, x_hs_fb, shape, expected );
    BROADCAST_TO_SUBCASE( case6, x_hs_hb, shape, expected );
    BROADCAST_TO_SUBCASE( case6, x_hs_db, shape, expected );

    BROADCAST_TO_SUBCASE( case6, x_hs_fb, shape_ct, expected );
    BROADCAST_TO_SUBCASE( case6, x_hs_hb, shape_ct, expected );
    BROADCAST_TO_SUBCASE( case6, x_hs_db, shape_ct, expected );

    BROADCAST_TO_SUBCASE( case6, x_hs_fb, shape_cl, expected );
    BROADCAST_TO_SUBCASE( case6, x_hs_hb, shape_cl, expected );
    BROADCAST_TO_SUBCASE( case6, x_hs_db, shape_cl, expected );

    BROADCAST_TO_SUBCASE( case6, x_ds_fb, shape, expected );
    BROADCAST_TO_SUBCASE( case6, x_ds_hb, shape, expected );
    BROADCAST_TO_SUBCASE( case6, x_ds_db, shape, expected );

    BROADCAST_TO_SUBCASE( case6, x_ds_fb, shape_ct, expected );
    BROADCAST_TO_SUBCASE( case6, x_ds_hb, shape_ct, expected );
    BROADCAST_TO_SUBCASE( case6, x_ds_db, shape_ct, expected );

    BROADCAST_TO_SUBCASE( case6, x_ds_fb, shape_cl, expected );
    BROADCAST_TO_SUBCASE( case6, x_ds_hb, shape_cl, expected );
    BROADCAST_TO_SUBCASE( case6, x_ds_db, shape_cl, expected );

    BROADCAST_TO_SUBCASE( case6, x_ls_fb, shape, expected );
    BROADCAST_TO_SUBCASE( case6, x_ls_hb, shape, expected );
    BROADCAST_TO_SUBCASE( case6, x_ls_db, shape, expected );

    BROADCAST_TO_SUBCASE( case6, x_ls_fb, shape_ct, expected );
    BROADCAST_TO_SUBCASE( case6, x_ls_hb, shape_ct, expected );
    BROADCAST_TO_SUBCASE( case6, x_ls_db, shape_ct, expected );

    BROADCAST_TO_SUBCASE( case6, x_ls_fb, shape_cl, expected );
    BROADCAST_TO_SUBCASE( case6, x_ls_hb, shape_cl, expected );
    BROADCAST_TO_SUBCASE( case6, x_ls_db, shape_cl, expected );
    #endif
}

TEST_CASE("broadcast_to(case7)" * doctest::test_suite("view::broadcast_to"))
{
    #if !defined(NMTOOLS_TESTING_GENERIC_NDARRAY)
    BROADCAST_TO_SUBCASE( case7, x_a, shape, expected );
    BROADCAST_TO_SUBCASE( case7, x_f, shape, expected );
    BROADCAST_TO_SUBCASE( case7, x_d, shape, expected );
    BROADCAST_TO_SUBCASE( case7, x_h, shape, expected );

    BROADCAST_TO_SUBCASE( case7, x_a, shape_ct, expected );
    BROADCAST_TO_SUBCASE( case7, x_f, shape_ct, expected );
    BROADCAST_TO_SUBCASE( case7, x_d, shape_ct, expected );
    BROADCAST_TO_SUBCASE( case7, x_h, shape_ct, expected );

    BROADCAST_TO_SUBCASE( case7, x_a, shape_cl, expected );
    BROADCAST_TO_SUBCASE( case7, x_f, shape_cl, expected );
    BROADCAST_TO_SUBCASE( case7, x_d, shape_cl, expected );
    BROADCAST_TO_SUBCASE( case7, x_h, shape_cl, expected );

    #else
    BROADCAST_TO_SUBCASE( case7, x_cs_fb, shape, expected );
    BROADCAST_TO_SUBCASE( case7, x_cs_hb, shape, expected );
    BROADCAST_TO_SUBCASE( case7, x_cs_db, shape, expected );

    BROADCAST_TO_SUBCASE( case7, x_cs_fb, shape_ct, expected );
    BROADCAST_TO_SUBCASE( case7, x_cs_hb, shape_ct, expected );
    BROADCAST_TO_SUBCASE( case7, x_cs_db, shape_ct, expected );

    BROADCAST_TO_SUBCASE( case7, x_cs_fb, shape_cl, expected );
    BROADCAST_TO_SUBCASE( case7, x_cs_hb, shape_cl, expected );
    BROADCAST_TO_SUBCASE( case7, x_cs_db, shape_cl, expected );

    BROADCAST_TO_SUBCASE( case7, x_fs_fb, shape, expected );
    BROADCAST_TO_SUBCASE( case7, x_fs_hb, shape, expected );
    BROADCAST_TO_SUBCASE( case7, x_fs_db, shape, expected );

    BROADCAST_TO_SUBCASE( case7, x_fs_fb, shape_ct, expected );
    BROADCAST_TO_SUBCASE( case7, x_fs_hb, shape_ct, expected );
    BROADCAST_TO_SUBCASE( case7, x_fs_db, shape_ct, expected );

    BROADCAST_TO_SUBCASE( case7, x_fs_fb, shape_cl, expected );
    BROADCAST_TO_SUBCASE( case7, x_fs_hb, shape_cl, expected );
    BROADCAST_TO_SUBCASE( case7, x_fs_db, shape_cl, expected );

    BROADCAST_TO_SUBCASE( case7, x_hs_fb, shape, expected );
    BROADCAST_TO_SUBCASE( case7, x_hs_hb, shape, expected );
    BROADCAST_TO_SUBCASE( case7, x_hs_db, shape, expected );

    BROADCAST_TO_SUBCASE( case7, x_hs_fb, shape_ct, expected );
    BROADCAST_TO_SUBCASE( case7, x_hs_hb, shape_ct, expected );
    BROADCAST_TO_SUBCASE( case7, x_hs_db, shape_ct, expected );

    BROADCAST_TO_SUBCASE( case7, x_hs_fb, shape_cl, expected );
    BROADCAST_TO_SUBCASE( case7, x_hs_hb, shape_cl, expected );
    BROADCAST_TO_SUBCASE( case7, x_hs_db, shape_cl, expected );

    BROADCAST_TO_SUBCASE( case7, x_ds_fb, shape, expected );
    BROADCAST_TO_SUBCASE( case7, x_ds_hb, shape, expected );
    BROADCAST_TO_SUBCASE( case7, x_ds_db, shape, expected );

    BROADCAST_TO_SUBCASE( case7, x_ds_fb, shape_ct, expected );
    BROADCAST_TO_SUBCASE( case7, x_ds_hb, shape_ct, expected );
    BROADCAST_TO_SUBCASE( case7, x_ds_db, shape_ct, expected );

    BROADCAST_TO_SUBCASE( case7, x_ds_fb, shape_cl, expected );
    BROADCAST_TO_SUBCASE( case7, x_ds_hb, shape_cl, expected );
    BROADCAST_TO_SUBCASE( case7, x_ds_db, shape_cl, expected );

    BROADCAST_TO_SUBCASE( case7, x_ls_fb, shape, expected );
    BROADCAST_TO_SUBCASE( case7, x_ls_hb, shape, expected );
    BROADCAST_TO_SUBCASE( case7, x_ls_db, shape, expected );

    BROADCAST_TO_SUBCASE( case7, x_ls_fb, shape_ct, expected );
    BROADCAST_TO_SUBCASE( case7, x_ls_hb, shape_ct, expected );
    BROADCAST_TO_SUBCASE( case7, x_ls_db, shape_ct, expected );

    BROADCAST_TO_SUBCASE( case7, x_ls_fb, shape_cl, expected );
    BROADCAST_TO_SUBCASE( case7, x_ls_hb, shape_cl, expected );
    BROADCAST_TO_SUBCASE( case7, x_ls_db, shape_cl, expected );
    #endif
}

TEST_CASE("broadcast_to(case8)" * doctest::test_suite("view::broadcast_to"))
{
    #if !defined(NMTOOLS_TESTING_GENERIC_NDARRAY)
    BROADCAST_TO_SUBCASE( case8, x_a, shape, expected );
    BROADCAST_TO_SUBCASE( case8, x_f, shape, expected );
    BROADCAST_TO_SUBCASE( case8, x_d, shape, expected );
    BROADCAST_TO_SUBCASE( case8, x_h, shape, expected );

    BROADCAST_TO_SUBCASE( case8, x_a, shape_ct, expected );
    BROADCAST_TO_SUBCASE( case8, x_f, shape_ct, expected );
    BROADCAST_TO_SUBCASE( case8, x_d, shape_ct, expected );
    BROADCAST_TO_SUBCASE( case8, x_h, shape_ct, expected );

    BROADCAST_TO_SUBCASE( case8, x_a, shape_cl, expected );
    BROADCAST_TO_SUBCASE( case8, x_f, shape_cl, expected );
    BROADCAST_TO_SUBCASE( case8, x_d, shape_cl, expected );
    BROADCAST_TO_SUBCASE( case8, x_h, shape_cl, expected );

    #else
    BROADCAST_TO_SUBCASE( case8, x_cs_fb, shape, expected );
    BROADCAST_TO_SUBCASE( case8, x_cs_hb, shape, expected );
    BROADCAST_TO_SUBCASE( case8, x_cs_db, shape, expected );

    BROADCAST_TO_SUBCASE( case8, x_cs_fb, shape_ct, expected );
    BROADCAST_TO_SUBCASE( case8, x_cs_hb, shape_ct, expected );
    BROADCAST_TO_SUBCASE( case8, x_cs_db, shape_ct, expected );

    BROADCAST_TO_SUBCASE( case8, x_cs_fb, shape_cl, expected );
    BROADCAST_TO_SUBCASE( case8, x_cs_hb, shape_cl, expected );
    BROADCAST_TO_SUBCASE( case8, x_cs_db, shape_cl, expected );

    BROADCAST_TO_SUBCASE( case8, x_fs_fb, shape, expected );
    BROADCAST_TO_SUBCASE( case8, x_fs_hb, shape, expected );
    BROADCAST_TO_SUBCASE( case8, x_fs_db, shape, expected );

    BROADCAST_TO_SUBCASE( case8, x_fs_fb, shape_ct, expected );
    BROADCAST_TO_SUBCASE( case8, x_fs_hb, shape_ct, expected );
    BROADCAST_TO_SUBCASE( case8, x_fs_db, shape_ct, expected );

    BROADCAST_TO_SUBCASE( case8, x_fs_fb, shape_cl, expected );
    BROADCAST_TO_SUBCASE( case8, x_fs_hb, shape_cl, expected );
    BROADCAST_TO_SUBCASE( case8, x_fs_db, shape_cl, expected );

    BROADCAST_TO_SUBCASE( case8, x_hs_fb, shape, expected );
    BROADCAST_TO_SUBCASE( case8, x_hs_hb, shape, expected );
    BROADCAST_TO_SUBCASE( case8, x_hs_db, shape, expected );

    BROADCAST_TO_SUBCASE( case8, x_hs_fb, shape_ct, expected );
    BROADCAST_TO_SUBCASE( case8, x_hs_hb, shape_ct, expected );
    BROADCAST_TO_SUBCASE( case8, x_hs_db, shape_ct, expected );

    BROADCAST_TO_SUBCASE( case8, x_hs_fb, shape_cl, expected );
    BROADCAST_TO_SUBCASE( case8, x_hs_hb, shape_cl, expected );
    BROADCAST_TO_SUBCASE( case8, x_hs_db, shape_cl, expected );

    BROADCAST_TO_SUBCASE( case8, x_ds_fb, shape, expected );
    BROADCAST_TO_SUBCASE( case8, x_ds_hb, shape, expected );
    BROADCAST_TO_SUBCASE( case8, x_ds_db, shape, expected );

    BROADCAST_TO_SUBCASE( case8, x_ds_fb, shape_ct, expected );
    BROADCAST_TO_SUBCASE( case8, x_ds_hb, shape_ct, expected );
    BROADCAST_TO_SUBCASE( case8, x_ds_db, shape_ct, expected );

    BROADCAST_TO_SUBCASE( case8, x_ds_fb, shape_cl, expected );
    BROADCAST_TO_SUBCASE( case8, x_ds_hb, shape_cl, expected );
    BROADCAST_TO_SUBCASE( case8, x_ds_db, shape_cl, expected );

    BROADCAST_TO_SUBCASE( case8, x_ls_fb, shape, expected );
    BROADCAST_TO_SUBCASE( case8, x_ls_hb, shape, expected );
    BROADCAST_TO_SUBCASE( case8, x_ls_db, shape, expected );

    BROADCAST_TO_SUBCASE( case8, x_ls_fb, shape_ct, expected );
    BROADCAST_TO_SUBCASE( case8, x_ls_hb, shape_ct, expected );
    BROADCAST_TO_SUBCASE( case8, x_ls_db, shape_ct, expected );

    BROADCAST_TO_SUBCASE( case8, x_ls_fb, shape_cl, expected );
    BROADCAST_TO_SUBCASE( case8, x_ls_hb, shape_cl, expected );
    BROADCAST_TO_SUBCASE( case8, x_ls_db, shape_cl, expected );
    #endif
}

TEST_CASE("broadcast_to(case9)" * doctest::test_suite("view::broadcast_to"))
{
    #if !defined(NMTOOLS_TESTING_GENERIC_NDARRAY)
    BROADCAST_TO_SUBCASE( case9, x_a, shape, expected );
    BROADCAST_TO_SUBCASE( case9, x_f, shape, expected );
    BROADCAST_TO_SUBCASE( case9, x_d, shape, expected );
    BROADCAST_TO_SUBCASE( case9, x_h, shape, expected );

    BROADCAST_TO_SUBCASE( case9, x_a, shape_ct, expected );
    BROADCAST_TO_SUBCASE( case9, x_f, shape_ct, expected );
    BROADCAST_TO_SUBCASE( case9, x_d, shape_ct, expected );
    BROADCAST_TO_SUBCASE( case9, x_h, shape_ct, expected );

    BROADCAST_TO_SUBCASE( case9, x_a, shape_cl, expected );
    BROADCAST_TO_SUBCASE( case9, x_f, shape_cl, expected );
    BROADCAST_TO_SUBCASE( case9, x_d, shape_cl, expected );
    BROADCAST_TO_SUBCASE( case9, x_h, shape_cl, expected );

    #else
    BROADCAST_TO_SUBCASE( case9, x_cs_fb, shape, expected );
    BROADCAST_TO_SUBCASE( case9, x_cs_hb, shape, expected );
    BROADCAST_TO_SUBCASE( case9, x_cs_db, shape, expected );

    BROADCAST_TO_SUBCASE( case9, x_cs_fb, shape_ct, expected );
    BROADCAST_TO_SUBCASE( case9, x_cs_hb, shape_ct, expected );
    BROADCAST_TO_SUBCASE( case9, x_cs_db, shape_ct, expected );

    BROADCAST_TO_SUBCASE( case9, x_cs_fb, shape_cl, expected );
    BROADCAST_TO_SUBCASE( case9, x_cs_hb, shape_cl, expected );
    BROADCAST_TO_SUBCASE( case9, x_cs_db, shape_cl, expected );

    BROADCAST_TO_SUBCASE( case9, x_fs_fb, shape, expected );
    BROADCAST_TO_SUBCASE( case9, x_fs_hb, shape, expected );
    BROADCAST_TO_SUBCASE( case9, x_fs_db, shape, expected );

    BROADCAST_TO_SUBCASE( case9, x_fs_fb, shape_ct, expected );
    BROADCAST_TO_SUBCASE( case9, x_fs_hb, shape_ct, expected );
    BROADCAST_TO_SUBCASE( case9, x_fs_db, shape_ct, expected );

    BROADCAST_TO_SUBCASE( case9, x_fs_fb, shape_cl, expected );
    BROADCAST_TO_SUBCASE( case9, x_fs_hb, shape_cl, expected );
    BROADCAST_TO_SUBCASE( case9, x_fs_db, shape_cl, expected );

    BROADCAST_TO_SUBCASE( case9, x_hs_fb, shape, expected );
    BROADCAST_TO_SUBCASE( case9, x_hs_hb, shape, expected );
    BROADCAST_TO_SUBCASE( case9, x_hs_db, shape, expected );

    BROADCAST_TO_SUBCASE( case9, x_hs_fb, shape_ct, expected );
    BROADCAST_TO_SUBCASE( case9, x_hs_hb, shape_ct, expected );
    BROADCAST_TO_SUBCASE( case9, x_hs_db, shape_ct, expected );

    BROADCAST_TO_SUBCASE( case9, x_hs_fb, shape_cl, expected );
    BROADCAST_TO_SUBCASE( case9, x_hs_hb, shape_cl, expected );
    BROADCAST_TO_SUBCASE( case9, x_hs_db, shape_cl, expected );

    BROADCAST_TO_SUBCASE( case9, x_ds_fb, shape, expected );
    BROADCAST_TO_SUBCASE( case9, x_ds_hb, shape, expected );
    BROADCAST_TO_SUBCASE( case9, x_ds_db, shape, expected );

    BROADCAST_TO_SUBCASE( case9, x_ds_fb, shape_ct, expected );
    BROADCAST_TO_SUBCASE( case9, x_ds_hb, shape_ct, expected );
    BROADCAST_TO_SUBCASE( case9, x_ds_db, shape_ct, expected );

    BROADCAST_TO_SUBCASE( case9, x_ds_fb, shape_cl, expected );
    BROADCAST_TO_SUBCASE( case9, x_ds_hb, shape_cl, expected );
    BROADCAST_TO_SUBCASE( case9, x_ds_db, shape_cl, expected );

    BROADCAST_TO_SUBCASE( case9, x_ls_fb, shape, expected );
    BROADCAST_TO_SUBCASE( case9, x_ls_hb, shape, expected );
    BROADCAST_TO_SUBCASE( case9, x_ls_db, shape, expected );

    BROADCAST_TO_SUBCASE( case9, x_ls_fb, shape_ct, expected );
    BROADCAST_TO_SUBCASE( case9, x_ls_hb, shape_ct, expected );
    BROADCAST_TO_SUBCASE( case9, x_ls_db, shape_ct, expected );

    BROADCAST_TO_SUBCASE( case9, x_ls_fb, shape_cl, expected );
    BROADCAST_TO_SUBCASE( case9, x_ls_hb, shape_cl, expected );
    BROADCAST_TO_SUBCASE( case9, x_ls_db, shape_cl, expected );
    #endif
}

TEST_CASE("broadcast_to(case10)" * doctest::test_suite("view::broadcast_to"))
{
    BROADCAST_TO_SUBCASE( case10, x, shape, expected );
}

TEST_CASE("broadcast_to(case11)" * doctest::test_suite("view::broadcast_to"))
{
    BROADCAST_TO_SUBCASE( case11, x, shape, expected );
}


// the following tests are to make sure it is safe to 
// return the view itself as long as it doesn't outlive
// the referenced array

template <typename array_t>
auto f(const array_t& array)
{
    return view::broadcast_to(array, nmtools_array{1,1,3});
}

template <typename array_t>
auto g(const array_t& array)
{
    auto a = f(array);
    return view::broadcast_to(a, nmtools_array{1,1,1,3});
}

TEST_CASE("broadcast_to" * doctest::test_suite("view::broadcast_to"))
{
    SUBCASE("one function")
    {
        // nmtools_array
        {
            auto array = nmtools_array{1,2,3};
            auto broacasted = f(array);
            int expected[1][1][3] = {
                {
                    {1,2,3}
                }
            };
            NMTOOLS_ASSERT_EQUAL( broacasted, expected );
        }
        // raw array
        {
            int array[3] = {1,2,3};
            auto broacasted = f(array);
            int expected[1][1][3] = {
                {
                    {1,2,3}
                }
            };
            NMTOOLS_ASSERT_EQUAL( broacasted, expected );
        }
    }
    SUBCASE("two function")
    {
        // nmtools_array
        {
            auto array = nmtools_array{1,2,3};
            auto broacasted = g(array);
            int expected[1][1][1][3] = {
                {
                    {
                        {1,2,3}
                    }
                }
            };
            NMTOOLS_ASSERT_EQUAL( nmtools::shape(broacasted), nm::shape(expected) );
            NMTOOLS_ASSERT_EQUAL( broacasted, expected );
        }

        // raw array
        {
            int array[3] = {1,2,3};
            auto broacasted = g(array);
            int expected[1][1][1][3] = {
                {
                    {
                        {1,2,3}
                    }
                }
            };
            NMTOOLS_ASSERT_EQUAL( nmtools::shape(broacasted), nm::shape(expected) );
            NMTOOLS_ASSERT_EQUAL( broacasted, expected );
        }
    }
}