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

#include "nmtools/array/atleast_1d.hpp"
#include "nmtools/testing/data/array/atleast_1d.hpp"
#include "nmtools/testing/doctest.hpp"

#define ATLEAST_1D_SUBCASE(case_name, ...) \
SUBCASE(#case_name) \
{ \
    NMTOOLS_TESTING_USE_CASE(array, atleast_1d, case_name); \
    using namespace args; \
    auto result = nmtools::atleast_1d(__VA_ARGS__); \
    NMTOOLS_ASSERT_CLOSE( result, expect::result ); \
}

TEST_CASE("atleast_1d(case1)" * doctest::test_suite("array::atleast_1d"))
{
    ATLEAST_1D_SUBCASE( case1, a );
}

TEST_CASE("atleast_1d(case2)" * doctest::test_suite("array::atleast_1d"))
{
    #if !defined(NMTOOLS_TESTING_GENERIC_NDARRAY)
    ATLEAST_1D_SUBCASE( case2, a );
    ATLEAST_1D_SUBCASE( case2, a_a );
    ATLEAST_1D_SUBCASE( case2, a_f );
    ATLEAST_1D_SUBCASE( case2, a_d );
    ATLEAST_1D_SUBCASE( case2, a_h );

    #else
    ATLEAST_1D_SUBCASE( case2, a_cs_fb );
    ATLEAST_1D_SUBCASE( case2, a_cs_hb );
    ATLEAST_1D_SUBCASE( case2, a_cs_db );

    ATLEAST_1D_SUBCASE( case2, a_fs_fb );
    ATLEAST_1D_SUBCASE( case2, a_fs_hb );
    ATLEAST_1D_SUBCASE( case2, a_fs_db );

    ATLEAST_1D_SUBCASE( case2, a_hs_fb );
    ATLEAST_1D_SUBCASE( case2, a_hs_hb );
    ATLEAST_1D_SUBCASE( case2, a_hs_db );

    ATLEAST_1D_SUBCASE( case2, a_ds_fb );
    ATLEAST_1D_SUBCASE( case2, a_ds_hb );
    ATLEAST_1D_SUBCASE( case2, a_ds_db );

    ATLEAST_1D_SUBCASE( case2, a_ls_fb );
    ATLEAST_1D_SUBCASE( case2, a_ls_hb );
    ATLEAST_1D_SUBCASE( case2, a_ls_db );

    #endif
}

TEST_CASE("atleast_1d(case3)" * doctest::test_suite("array::atleast_1d"))
{
    #if !defined(NMTOOLS_TESTING_GENERIC_NDARRAY)
    ATLEAST_1D_SUBCASE( case3, a );
    ATLEAST_1D_SUBCASE( case3, a_a );
    ATLEAST_1D_SUBCASE( case3, a_f );
    ATLEAST_1D_SUBCASE( case3, a_d );
    ATLEAST_1D_SUBCASE( case3, a_h );

    #else
    ATLEAST_1D_SUBCASE( case3, a_cs_fb );
    ATLEAST_1D_SUBCASE( case3, a_cs_hb );
    ATLEAST_1D_SUBCASE( case3, a_cs_db );

    ATLEAST_1D_SUBCASE( case3, a_fs_fb );
    ATLEAST_1D_SUBCASE( case3, a_fs_hb );
    ATLEAST_1D_SUBCASE( case3, a_fs_db );

    ATLEAST_1D_SUBCASE( case3, a_hs_fb );
    ATLEAST_1D_SUBCASE( case3, a_hs_hb );
    ATLEAST_1D_SUBCASE( case3, a_hs_db );

    ATLEAST_1D_SUBCASE( case3, a_ds_fb );
    ATLEAST_1D_SUBCASE( case3, a_ds_hb );
    ATLEAST_1D_SUBCASE( case3, a_ds_db );

    ATLEAST_1D_SUBCASE( case3, a_ls_fb );
    ATLEAST_1D_SUBCASE( case3, a_ls_hb );
    ATLEAST_1D_SUBCASE( case3, a_ls_db );
    #endif
}

TEST_CASE("atleast_1d(case4)" * doctest::test_suite("array::atleast_1d"))
{
    #if !defined(NMTOOLS_TESTING_GENERIC_NDARRAY)
    ATLEAST_1D_SUBCASE( case4, a );
    ATLEAST_1D_SUBCASE( case4, a_a );
    ATLEAST_1D_SUBCASE( case4, a_f );
    ATLEAST_1D_SUBCASE( case4, a_d );
    ATLEAST_1D_SUBCASE( case4, a_h );

    #else
    ATLEAST_1D_SUBCASE( case4, a_cs_fb );
    ATLEAST_1D_SUBCASE( case4, a_cs_hb );
    ATLEAST_1D_SUBCASE( case4, a_cs_db );

    ATLEAST_1D_SUBCASE( case4, a_fs_fb );
    ATLEAST_1D_SUBCASE( case4, a_fs_hb );
    ATLEAST_1D_SUBCASE( case4, a_fs_db );

    ATLEAST_1D_SUBCASE( case4, a_hs_fb );
    ATLEAST_1D_SUBCASE( case4, a_hs_hb );
    ATLEAST_1D_SUBCASE( case4, a_hs_db );

    ATLEAST_1D_SUBCASE( case4, a_ds_fb );
    ATLEAST_1D_SUBCASE( case4, a_ds_hb );
    ATLEAST_1D_SUBCASE( case4, a_ds_db );

    ATLEAST_1D_SUBCASE( case4, a_ls_fb );
    ATLEAST_1D_SUBCASE( case4, a_ls_hb );
    ATLEAST_1D_SUBCASE( case4, a_ls_db );
    #endif
}