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

#include "nmtools/array/reshape.hpp"
#include "nmtools/testing/data/array/reshape.hpp"
#include "nmtools/testing/doctest.hpp"

namespace nm = nmtools;
namespace na = nmtools;
namespace view = nm::view;
namespace meta = nm::meta;

#define RESHAPE_SUBCASE(case_name, ...) \
SUBCASE(#case_name) \
{ \
    NMTOOLS_TESTING_USE_CASE(reshape, case_name) \
    using namespace args; \
    auto result = view::reshape(__VA_ARGS__); \
    NMTOOLS_ASSERT_CLOSE( result, expect::expected ); \
}

TEST_CASE("reshape(case1)" * doctest::test_suite("view::reshape"))
{
    #if !defined(NMTOOLS_TESTING_GENERIC_NDARRAY)
    RESHAPE_SUBCASE(case1, array, newshape );
    RESHAPE_SUBCASE(case1, array_a, newshape_a );
    RESHAPE_SUBCASE(case1, array_f, newshape_a );
    RESHAPE_SUBCASE(case1, array_d, newshape_v );
    RESHAPE_SUBCASE(case1, array_h, newshape_h );

    RESHAPE_SUBCASE(case1, array, newshape_ct );
    RESHAPE_SUBCASE(case1, array_a, newshape_ct );
    RESHAPE_SUBCASE(case1, array_f, newshape_ct );
    RESHAPE_SUBCASE(case1, array_d, newshape_ct );
    RESHAPE_SUBCASE(case1, array_h, newshape_ct );

    #else
    RESHAPE_SUBCASE(case1, array_cs_fb, newshape_ct );
    RESHAPE_SUBCASE(case1, array_cs_hb, newshape_ct );
    RESHAPE_SUBCASE(case1, array_cs_db, newshape_ct );

    RESHAPE_SUBCASE(case1, array_fs_fb, newshape_ct );
    RESHAPE_SUBCASE(case1, array_fs_hb, newshape_ct );
    RESHAPE_SUBCASE(case1, array_fs_db, newshape_ct );

    RESHAPE_SUBCASE(case1, array_hs_fb, newshape_ct );
    RESHAPE_SUBCASE(case1, array_hs_hb, newshape_ct );
    RESHAPE_SUBCASE(case1, array_hs_db, newshape_ct );

    RESHAPE_SUBCASE(case1, array_ds_fb, newshape_ct );
    RESHAPE_SUBCASE(case1, array_ds_hb, newshape_ct );
    RESHAPE_SUBCASE(case1, array_ds_db, newshape_ct );

    RESHAPE_SUBCASE(case1, array_ls_fb, newshape_ct );
    RESHAPE_SUBCASE(case1, array_ls_hb, newshape_ct );
    RESHAPE_SUBCASE(case1, array_ls_db, newshape_ct );

    RESHAPE_SUBCASE(case1, array_cs_fb, newshape_a );
    RESHAPE_SUBCASE(case1, array_cs_hb, newshape_a );
    RESHAPE_SUBCASE(case1, array_cs_db, newshape_a );

    RESHAPE_SUBCASE(case1, array_fs_fb, newshape_a );
    RESHAPE_SUBCASE(case1, array_fs_hb, newshape_a );
    RESHAPE_SUBCASE(case1, array_fs_db, newshape_a );

    RESHAPE_SUBCASE(case1, array_hs_fb, newshape_a );
    RESHAPE_SUBCASE(case1, array_hs_hb, newshape_a );
    RESHAPE_SUBCASE(case1, array_hs_db, newshape_a );

    RESHAPE_SUBCASE(case1, array_ds_fb, newshape_a );
    RESHAPE_SUBCASE(case1, array_ds_hb, newshape_a );
    RESHAPE_SUBCASE(case1, array_ds_db, newshape_a );

    RESHAPE_SUBCASE(case1, array_ls_fb, newshape_a );
    RESHAPE_SUBCASE(case1, array_ls_hb, newshape_a );
    RESHAPE_SUBCASE(case1, array_ls_db, newshape_a );

    RESHAPE_SUBCASE(case1, array_cs_fb, newshape_cl );
    RESHAPE_SUBCASE(case1, array_cs_hb, newshape_cl );
    RESHAPE_SUBCASE(case1, array_cs_db, newshape_cl );

    RESHAPE_SUBCASE(case1, array_fs_fb, newshape_cl );
    RESHAPE_SUBCASE(case1, array_fs_hb, newshape_cl );
    RESHAPE_SUBCASE(case1, array_fs_db, newshape_cl );

    RESHAPE_SUBCASE(case1, array_hs_fb, newshape_cl );
    RESHAPE_SUBCASE(case1, array_hs_hb, newshape_cl );
    RESHAPE_SUBCASE(case1, array_hs_db, newshape_cl );

    RESHAPE_SUBCASE(case1, array_ds_fb, newshape_cl );
    RESHAPE_SUBCASE(case1, array_ds_hb, newshape_cl );
    RESHAPE_SUBCASE(case1, array_ds_db, newshape_cl );

    RESHAPE_SUBCASE(case1, array_ls_fb, newshape_cl );
    RESHAPE_SUBCASE(case1, array_ls_hb, newshape_cl );
    RESHAPE_SUBCASE(case1, array_ls_db, newshape_cl );
    #endif
}

TEST_CASE("reshape(case2)" * doctest::test_suite("view::reshape"))
{
    #if !defined(NMTOOLS_TESTING_GENERIC_NDARRAY)
    RESHAPE_SUBCASE(case2, array, newshape );
    RESHAPE_SUBCASE(case2, array_a, newshape_a );
    RESHAPE_SUBCASE(case2, array_f, newshape_a );
    RESHAPE_SUBCASE(case2, array_d, newshape_v );
    RESHAPE_SUBCASE(case2, array_h, newshape_h );

    RESHAPE_SUBCASE(case2, array, newshape_ct );
    RESHAPE_SUBCASE(case2, array_a, newshape_ct );
    RESHAPE_SUBCASE(case2, array_f, newshape_ct );
    RESHAPE_SUBCASE(case2, array_d, newshape_ct );
    RESHAPE_SUBCASE(case2, array_h, newshape_ct );

    #else
    RESHAPE_SUBCASE(case2, array_cs_fb, newshape_ct );
    RESHAPE_SUBCASE(case2, array_cs_hb, newshape_ct );
    RESHAPE_SUBCASE(case2, array_cs_db, newshape_ct );

    RESHAPE_SUBCASE(case2, array_fs_fb, newshape_ct );
    RESHAPE_SUBCASE(case2, array_fs_hb, newshape_ct );
    RESHAPE_SUBCASE(case2, array_fs_db, newshape_ct );

    RESHAPE_SUBCASE(case2, array_hs_fb, newshape_ct );
    RESHAPE_SUBCASE(case2, array_hs_hb, newshape_ct );
    RESHAPE_SUBCASE(case2, array_hs_db, newshape_ct );

    RESHAPE_SUBCASE(case2, array_ds_fb, newshape_ct );
    RESHAPE_SUBCASE(case2, array_ds_hb, newshape_ct );
    RESHAPE_SUBCASE(case2, array_ds_db, newshape_ct );

    RESHAPE_SUBCASE(case2, array_ls_fb, newshape_ct );
    RESHAPE_SUBCASE(case2, array_ls_hb, newshape_ct );
    RESHAPE_SUBCASE(case2, array_ls_db, newshape_ct );

    RESHAPE_SUBCASE(case2, array_cs_fb, newshape_a );
    RESHAPE_SUBCASE(case2, array_cs_hb, newshape_a );
    RESHAPE_SUBCASE(case2, array_cs_db, newshape_a );

    RESHAPE_SUBCASE(case2, array_fs_fb, newshape_a );
    RESHAPE_SUBCASE(case2, array_fs_hb, newshape_a );
    RESHAPE_SUBCASE(case2, array_fs_db, newshape_a );

    RESHAPE_SUBCASE(case2, array_hs_fb, newshape_a );
    RESHAPE_SUBCASE(case2, array_hs_hb, newshape_a );
    RESHAPE_SUBCASE(case2, array_hs_db, newshape_a );

    RESHAPE_SUBCASE(case2, array_ds_fb, newshape_a );
    RESHAPE_SUBCASE(case2, array_ds_hb, newshape_a );
    RESHAPE_SUBCASE(case2, array_ds_db, newshape_a );

    RESHAPE_SUBCASE(case2, array_ls_fb, newshape_a );
    RESHAPE_SUBCASE(case2, array_ls_hb, newshape_a );
    RESHAPE_SUBCASE(case2, array_ls_db, newshape_a );

    RESHAPE_SUBCASE(case2, array_cs_fb, newshape_cl );
    RESHAPE_SUBCASE(case2, array_cs_hb, newshape_cl );
    RESHAPE_SUBCASE(case2, array_cs_db, newshape_cl );

    RESHAPE_SUBCASE(case2, array_fs_fb, newshape_cl );
    RESHAPE_SUBCASE(case2, array_fs_hb, newshape_cl );
    RESHAPE_SUBCASE(case2, array_fs_db, newshape_cl );

    RESHAPE_SUBCASE(case2, array_hs_fb, newshape_cl );
    RESHAPE_SUBCASE(case2, array_hs_hb, newshape_cl );
    RESHAPE_SUBCASE(case2, array_hs_db, newshape_cl );

    RESHAPE_SUBCASE(case2, array_ds_fb, newshape_cl );
    RESHAPE_SUBCASE(case2, array_ds_hb, newshape_cl );
    RESHAPE_SUBCASE(case2, array_ds_db, newshape_cl );

    RESHAPE_SUBCASE(case2, array_ls_fb, newshape_cl );
    RESHAPE_SUBCASE(case2, array_ls_hb, newshape_cl );
    RESHAPE_SUBCASE(case2, array_ls_db, newshape_cl );
    #endif
}

TEST_CASE("reshape(case3)" * doctest::test_suite("view::reshape"))
{
    #if !defined(NMTOOLS_TESTING_GENERIC_NDARRAY)
    RESHAPE_SUBCASE(case3, array, newshape );
    RESHAPE_SUBCASE(case3, array_a, newshape_a );
    RESHAPE_SUBCASE(case3, array_f, newshape_a );
    RESHAPE_SUBCASE(case3, array_d, newshape_v );
    RESHAPE_SUBCASE(case3, array_h, newshape_h );

    #else
    RESHAPE_SUBCASE(case3, array, newshape_ct );
    RESHAPE_SUBCASE(case3, array_a, newshape_ct );
    RESHAPE_SUBCASE(case3, array_f, newshape_ct );
    RESHAPE_SUBCASE(case3, array_d, newshape_ct );
    RESHAPE_SUBCASE(case3, array_h, newshape_ct );

    RESHAPE_SUBCASE(case3, array_cs_fb, newshape_ct );
    RESHAPE_SUBCASE(case3, array_cs_hb, newshape_ct );
    RESHAPE_SUBCASE(case3, array_cs_db, newshape_ct );

    RESHAPE_SUBCASE(case3, array_fs_fb, newshape_ct );
    RESHAPE_SUBCASE(case3, array_fs_hb, newshape_ct );
    RESHAPE_SUBCASE(case3, array_fs_db, newshape_ct );

    RESHAPE_SUBCASE(case3, array_hs_fb, newshape_ct );
    RESHAPE_SUBCASE(case3, array_hs_hb, newshape_ct );
    RESHAPE_SUBCASE(case3, array_hs_db, newshape_ct );

    RESHAPE_SUBCASE(case3, array_ds_fb, newshape_ct );
    RESHAPE_SUBCASE(case3, array_ds_hb, newshape_ct );
    RESHAPE_SUBCASE(case3, array_ds_db, newshape_ct );

    RESHAPE_SUBCASE(case3, array_ls_fb, newshape_ct );
    RESHAPE_SUBCASE(case3, array_ls_hb, newshape_ct );
    RESHAPE_SUBCASE(case3, array_ls_db, newshape_ct );

    RESHAPE_SUBCASE(case3, array_cs_fb, newshape_a );
    RESHAPE_SUBCASE(case3, array_cs_hb, newshape_a );
    RESHAPE_SUBCASE(case3, array_cs_db, newshape_a );

    RESHAPE_SUBCASE(case3, array_fs_fb, newshape_a );
    RESHAPE_SUBCASE(case3, array_fs_hb, newshape_a );
    RESHAPE_SUBCASE(case3, array_fs_db, newshape_a );

    RESHAPE_SUBCASE(case3, array_hs_fb, newshape_a );
    RESHAPE_SUBCASE(case3, array_hs_hb, newshape_a );
    RESHAPE_SUBCASE(case3, array_hs_db, newshape_a );

    RESHAPE_SUBCASE(case3, array_ds_fb, newshape_a );
    RESHAPE_SUBCASE(case3, array_ds_hb, newshape_a );
    RESHAPE_SUBCASE(case3, array_ds_db, newshape_a );

    RESHAPE_SUBCASE(case3, array_ls_fb, newshape_a );
    RESHAPE_SUBCASE(case3, array_ls_hb, newshape_a );
    RESHAPE_SUBCASE(case3, array_ls_db, newshape_a );

    RESHAPE_SUBCASE(case3, array_cs_fb, newshape_cl );
    RESHAPE_SUBCASE(case3, array_cs_hb, newshape_cl );
    RESHAPE_SUBCASE(case3, array_cs_db, newshape_cl );

    RESHAPE_SUBCASE(case3, array_fs_fb, newshape_cl );
    RESHAPE_SUBCASE(case3, array_fs_hb, newshape_cl );
    RESHAPE_SUBCASE(case3, array_fs_db, newshape_cl );

    RESHAPE_SUBCASE(case3, array_hs_fb, newshape_cl );
    RESHAPE_SUBCASE(case3, array_hs_hb, newshape_cl );
    RESHAPE_SUBCASE(case3, array_hs_db, newshape_cl );

    RESHAPE_SUBCASE(case3, array_ds_fb, newshape_cl );
    RESHAPE_SUBCASE(case3, array_ds_hb, newshape_cl );
    RESHAPE_SUBCASE(case3, array_ds_db, newshape_cl );

    RESHAPE_SUBCASE(case3, array_ls_fb, newshape_cl );
    RESHAPE_SUBCASE(case3, array_ls_hb, newshape_cl );
    RESHAPE_SUBCASE(case3, array_ls_db, newshape_cl );
    #endif
}

TEST_CASE("reshape(case4)" * doctest::test_suite("view::reshape"))
{
    #if !defined(NMTOOLS_TESTING_GENERIC_NDARRAY)
    RESHAPE_SUBCASE(case4, array, newshape );
    RESHAPE_SUBCASE(case4, array_a, newshape_a );
    RESHAPE_SUBCASE(case4, array_f, newshape_a );
    RESHAPE_SUBCASE(case4, array_d, newshape_v );
    RESHAPE_SUBCASE(case4, array_h, newshape_h );

    RESHAPE_SUBCASE(case4, array, newshape_ct );
    RESHAPE_SUBCASE(case4, array_a, newshape_ct );
    RESHAPE_SUBCASE(case4, array_f, newshape_ct );
    RESHAPE_SUBCASE(case4, array_d, newshape_ct );
    RESHAPE_SUBCASE(case4, array_h, newshape_ct );

    #else
    RESHAPE_SUBCASE(case4, array_cs_fb, newshape_ct );
    RESHAPE_SUBCASE(case4, array_cs_hb, newshape_ct );
    RESHAPE_SUBCASE(case4, array_cs_db, newshape_ct );

    RESHAPE_SUBCASE(case4, array_fs_fb, newshape_ct );
    RESHAPE_SUBCASE(case4, array_fs_hb, newshape_ct );
    RESHAPE_SUBCASE(case4, array_fs_db, newshape_ct );

    RESHAPE_SUBCASE(case4, array_hs_fb, newshape_ct );
    RESHAPE_SUBCASE(case4, array_hs_hb, newshape_ct );
    RESHAPE_SUBCASE(case4, array_hs_db, newshape_ct );

    RESHAPE_SUBCASE(case4, array_ds_fb, newshape_ct );
    RESHAPE_SUBCASE(case4, array_ds_hb, newshape_ct );
    RESHAPE_SUBCASE(case4, array_ds_db, newshape_ct );

    RESHAPE_SUBCASE(case4, array_ls_fb, newshape_ct );
    RESHAPE_SUBCASE(case4, array_ls_hb, newshape_ct );
    RESHAPE_SUBCASE(case4, array_ls_db, newshape_ct );

    RESHAPE_SUBCASE(case4, array_cs_fb, newshape_a );
    RESHAPE_SUBCASE(case4, array_cs_hb, newshape_a );
    RESHAPE_SUBCASE(case4, array_cs_db, newshape_a );

    RESHAPE_SUBCASE(case4, array_fs_fb, newshape_a );
    RESHAPE_SUBCASE(case4, array_fs_hb, newshape_a );
    RESHAPE_SUBCASE(case4, array_fs_db, newshape_a );

    RESHAPE_SUBCASE(case4, array_hs_fb, newshape_a );
    RESHAPE_SUBCASE(case4, array_hs_hb, newshape_a );
    RESHAPE_SUBCASE(case4, array_hs_db, newshape_a );

    RESHAPE_SUBCASE(case4, array_ds_fb, newshape_a );
    RESHAPE_SUBCASE(case4, array_ds_hb, newshape_a );
    RESHAPE_SUBCASE(case4, array_ds_db, newshape_a );

    RESHAPE_SUBCASE(case4, array_ls_fb, newshape_a );
    RESHAPE_SUBCASE(case4, array_ls_hb, newshape_a );
    RESHAPE_SUBCASE(case4, array_ls_db, newshape_a );

    #if defined(__clang__)
    RESHAPE_SUBCASE(case4, array_cs_fb, newshape_cl );
    RESHAPE_SUBCASE(case4, array_cs_hb, newshape_cl );
    RESHAPE_SUBCASE(case4, array_cs_db, newshape_cl );

    RESHAPE_SUBCASE(case4, array_fs_fb, newshape_cl );
    RESHAPE_SUBCASE(case4, array_fs_hb, newshape_cl );
    RESHAPE_SUBCASE(case4, array_fs_db, newshape_cl );

    RESHAPE_SUBCASE(case4, array_hs_fb, newshape_cl );
    RESHAPE_SUBCASE(case4, array_hs_hb, newshape_cl );
    RESHAPE_SUBCASE(case4, array_hs_db, newshape_cl );

    RESHAPE_SUBCASE(case4, array_ds_fb, newshape_cl );
    RESHAPE_SUBCASE(case4, array_ds_hb, newshape_cl );
    RESHAPE_SUBCASE(case4, array_ds_db, newshape_cl );

    RESHAPE_SUBCASE(case4, array_ls_fb, newshape_cl );
    RESHAPE_SUBCASE(case4, array_ls_hb, newshape_cl );
    RESHAPE_SUBCASE(case4, array_ls_db, newshape_cl );
    #endif
    #endif
}

TEST_CASE("reshape(case5)" * doctest::test_suite("view::reshape"))
{
    #if !defined(NMTOOLS_TESTING_GENERIC_NDARRAY)
    RESHAPE_SUBCASE(case5, array, newshape );
    RESHAPE_SUBCASE(case5, array_a, newshape_a );
    RESHAPE_SUBCASE(case5, array_f, newshape_a );
    RESHAPE_SUBCASE(case5, array_d, newshape_v );
    RESHAPE_SUBCASE(case5, array_h, newshape_h );

    RESHAPE_SUBCASE(case5, array, newshape_ct );
    RESHAPE_SUBCASE(case5, array_a, newshape_ct );
    RESHAPE_SUBCASE(case5, array_f, newshape_ct );
    RESHAPE_SUBCASE(case5, array_d, newshape_ct );
    RESHAPE_SUBCASE(case5, array_h, newshape_ct );


    #else
    RESHAPE_SUBCASE(case5, array_cs_fb, newshape_ct );
    RESHAPE_SUBCASE(case5, array_cs_hb, newshape_ct );
    RESHAPE_SUBCASE(case5, array_cs_db, newshape_ct );

    RESHAPE_SUBCASE(case5, array_fs_fb, newshape_ct );
    RESHAPE_SUBCASE(case5, array_fs_hb, newshape_ct );
    RESHAPE_SUBCASE(case5, array_fs_db, newshape_ct );

    RESHAPE_SUBCASE(case5, array_hs_fb, newshape_ct );
    RESHAPE_SUBCASE(case5, array_hs_hb, newshape_ct );
    RESHAPE_SUBCASE(case5, array_hs_db, newshape_ct );

    RESHAPE_SUBCASE(case5, array_ds_fb, newshape_ct );
    RESHAPE_SUBCASE(case5, array_ds_hb, newshape_ct );
    RESHAPE_SUBCASE(case5, array_ds_db, newshape_ct );

    RESHAPE_SUBCASE(case5, array_ls_fb, newshape_ct );
    RESHAPE_SUBCASE(case5, array_ls_hb, newshape_ct );
    RESHAPE_SUBCASE(case5, array_ls_db, newshape_ct );

    RESHAPE_SUBCASE(case5, array_cs_fb, newshape_a );
    RESHAPE_SUBCASE(case5, array_cs_hb, newshape_a );
    RESHAPE_SUBCASE(case5, array_cs_db, newshape_a );

    RESHAPE_SUBCASE(case5, array_fs_fb, newshape_a );
    RESHAPE_SUBCASE(case5, array_fs_hb, newshape_a );
    RESHAPE_SUBCASE(case5, array_fs_db, newshape_a );

    RESHAPE_SUBCASE(case5, array_hs_fb, newshape_a );
    RESHAPE_SUBCASE(case5, array_hs_hb, newshape_a );
    RESHAPE_SUBCASE(case5, array_hs_db, newshape_a );

    RESHAPE_SUBCASE(case5, array_ds_fb, newshape_a );
    RESHAPE_SUBCASE(case5, array_ds_hb, newshape_a );
    RESHAPE_SUBCASE(case5, array_ds_db, newshape_a );

    RESHAPE_SUBCASE(case5, array_ls_fb, newshape_a );
    RESHAPE_SUBCASE(case5, array_ls_hb, newshape_a );
    RESHAPE_SUBCASE(case5, array_ls_db, newshape_a );

    #if defined(__clang__)
    RESHAPE_SUBCASE(case5, array_cs_fb, newshape_cl );
    RESHAPE_SUBCASE(case5, array_cs_hb, newshape_cl );
    RESHAPE_SUBCASE(case5, array_cs_db, newshape_cl );

    RESHAPE_SUBCASE(case5, array_fs_fb, newshape_cl );
    RESHAPE_SUBCASE(case5, array_fs_hb, newshape_cl );
    RESHAPE_SUBCASE(case5, array_fs_db, newshape_cl );

    RESHAPE_SUBCASE(case5, array_hs_fb, newshape_cl );
    RESHAPE_SUBCASE(case5, array_hs_hb, newshape_cl );
    RESHAPE_SUBCASE(case5, array_hs_db, newshape_cl );

    RESHAPE_SUBCASE(case5, array_ds_fb, newshape_cl );
    RESHAPE_SUBCASE(case5, array_ds_hb, newshape_cl );
    RESHAPE_SUBCASE(case5, array_ds_db, newshape_cl );

    RESHAPE_SUBCASE(case5, array_ls_fb, newshape_cl );
    RESHAPE_SUBCASE(case5, array_ls_hb, newshape_cl );
    RESHAPE_SUBCASE(case5, array_ls_db, newshape_cl );
    #endif
    #endif
}

// NOTE: currently reshape is not monadic
// TODO: support monadic error handling for reshape
#if 0
TEST_CASE("reshape(case6)" * doctest::test_suite("view::reshape"))
{
    RESHAPE_SUBCASE(case6, array, newshape );
    RESHAPE_SUBCASE(case6, array_a, newshape_a );
    RESHAPE_SUBCASE(case6, array_f, newshape_a );
    RESHAPE_SUBCASE(case6, array_d, newshape_v );
    RESHAPE_SUBCASE(case6, array_h, newshape_h );

    RESHAPE_SUBCASE(case6, array, newshape_ct );
    RESHAPE_SUBCASE(case6, array_a, newshape_ct );
    RESHAPE_SUBCASE(case6, array_f, newshape_ct );
    RESHAPE_SUBCASE(case6, array_d, newshape_ct );
    RESHAPE_SUBCASE(case6, array_h, newshape_ct );
}
#endif