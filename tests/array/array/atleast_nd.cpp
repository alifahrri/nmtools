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

#include "nmtools/array/array/atleast_nd.hpp"
#include "nmtools/testing/data/array/atleast_nd.hpp"
#include "nmtools/testing/doctest.hpp"

#define ATLEAST_ND_SUBCASE(case_name, ...) \
SUBCASE(#case_name) \
{ \
    NMTOOLS_TESTING_USE_CASE(array, atleast_nd, case_name); \
    using namespace args; \
    auto result = nmtools::array::atleast_nd(__VA_ARGS__); \
    NMTOOLS_ASSERT_EQUAL( nmtools::dim(result), expect::dim ); \
    NMTOOLS_ASSERT_EQUAL( nmtools::shape(result), expect::shape ); \
    NMTOOLS_ASSERT_CLOSE( result, expect::result ); \
}

TEST_CASE("atleast_nd(case1)" * doctest::test_suite("array::atleast_nd"))
{
    ATLEAST_ND_SUBCASE( case1, a, nd );
}

TEST_CASE("atleast_nd(case2)" * doctest::test_suite("array::atleast_nd"))
{
    #if !defined(NMTOOLS_TESTING_GENERIC_NDARRAY)
    ATLEAST_ND_SUBCASE( case2, a, nd );
    ATLEAST_ND_SUBCASE( case2, a_a, nd );
    ATLEAST_ND_SUBCASE( case2, a_f, nd );
    ATLEAST_ND_SUBCASE( case2, a_d, nd );
    ATLEAST_ND_SUBCASE( case2, a_h, nd );

    #else
    ATLEAST_ND_SUBCASE( case2, a_cs_fb, nd );
    ATLEAST_ND_SUBCASE( case2, a_cs_hb, nd );
    ATLEAST_ND_SUBCASE( case2, a_cs_db, nd );

    ATLEAST_ND_SUBCASE( case2, a_fs_fb, nd );
    ATLEAST_ND_SUBCASE( case2, a_fs_hb, nd );
    ATLEAST_ND_SUBCASE( case2, a_fs_db, nd );

    ATLEAST_ND_SUBCASE( case2, a_hs_fb, nd );
    ATLEAST_ND_SUBCASE( case2, a_hs_hb, nd );
    ATLEAST_ND_SUBCASE( case2, a_hs_db, nd );

    ATLEAST_ND_SUBCASE( case2, a_ds_fb, nd );
    ATLEAST_ND_SUBCASE( case2, a_ds_hb, nd );
    ATLEAST_ND_SUBCASE( case2, a_ds_db, nd );

    ATLEAST_ND_SUBCASE( case2, a_ls_fb, nd );
    ATLEAST_ND_SUBCASE( case2, a_ls_hb, nd );
    ATLEAST_ND_SUBCASE( case2, a_ls_db, nd );
    #endif
}

TEST_CASE("atleast_nd(case3)" * doctest::test_suite("array::atleast_nd"))
{
    #if !defined(NMTOOLS_TESTING_GENERIC_NDARRAY)
    ATLEAST_ND_SUBCASE( case3, a, nd );
    ATLEAST_ND_SUBCASE( case3, a_a, nd );
    ATLEAST_ND_SUBCASE( case3, a_f, nd );
    ATLEAST_ND_SUBCASE( case3, a_d, nd );
    ATLEAST_ND_SUBCASE( case3, a_h, nd );
   
    #else
    ATLEAST_ND_SUBCASE( case3, a_cs_fb, nd );
    ATLEAST_ND_SUBCASE( case3, a_cs_hb, nd );
    ATLEAST_ND_SUBCASE( case3, a_cs_db, nd );

    ATLEAST_ND_SUBCASE( case3, a_fs_fb, nd );
    ATLEAST_ND_SUBCASE( case3, a_fs_hb, nd );
    ATLEAST_ND_SUBCASE( case3, a_fs_db, nd );

    ATLEAST_ND_SUBCASE( case3, a_hs_fb, nd );
    ATLEAST_ND_SUBCASE( case3, a_hs_hb, nd );
    ATLEAST_ND_SUBCASE( case3, a_hs_db, nd );

    ATLEAST_ND_SUBCASE( case3, a_ds_fb, nd );
    ATLEAST_ND_SUBCASE( case3, a_ds_hb, nd );
    ATLEAST_ND_SUBCASE( case3, a_ds_db, nd );

    ATLEAST_ND_SUBCASE( case3, a_ls_fb, nd );
    ATLEAST_ND_SUBCASE( case3, a_ls_hb, nd );
    ATLEAST_ND_SUBCASE( case3, a_ls_db, nd );
    #endif
}

TEST_CASE("atleast_nd(case4)" * doctest::test_suite("array::atleast_nd"))
{
    #if !defined(NMTOOLS_TESTING_GENERIC_NDARRAY)
    ATLEAST_ND_SUBCASE( case4, a, nd );
    ATLEAST_ND_SUBCASE( case4, a_a, nd );
    ATLEAST_ND_SUBCASE( case4, a_f, nd );
    ATLEAST_ND_SUBCASE( case4, a_d, nd );
    ATLEAST_ND_SUBCASE( case4, a_h, nd );

    #else
    ATLEAST_ND_SUBCASE( case4, a_cs_fb, nd );
    ATLEAST_ND_SUBCASE( case4, a_cs_hb, nd );
    ATLEAST_ND_SUBCASE( case4, a_cs_db, nd );

    ATLEAST_ND_SUBCASE( case4, a_fs_fb, nd );
    ATLEAST_ND_SUBCASE( case4, a_fs_hb, nd );
    ATLEAST_ND_SUBCASE( case4, a_fs_db, nd );

    ATLEAST_ND_SUBCASE( case4, a_hs_fb, nd );
    ATLEAST_ND_SUBCASE( case4, a_hs_hb, nd );
    ATLEAST_ND_SUBCASE( case4, a_hs_db, nd );

    ATLEAST_ND_SUBCASE( case4, a_ds_fb, nd );
    ATLEAST_ND_SUBCASE( case4, a_ds_hb, nd );
    ATLEAST_ND_SUBCASE( case4, a_ds_db, nd );

    ATLEAST_ND_SUBCASE( case4, a_ls_fb, nd );
    ATLEAST_ND_SUBCASE( case4, a_ls_hb, nd );
    ATLEAST_ND_SUBCASE( case4, a_ls_db, nd );
    #endif
}

TEST_CASE("atleast_nd(case5)" * doctest::test_suite("array::atleast_nd"))
{
    #if !defined(NMTOOLS_TESTING_GENERIC_NDARRAY)
    ATLEAST_ND_SUBCASE( case5, a, nd );
    ATLEAST_ND_SUBCASE( case5, a_a, nd );
    ATLEAST_ND_SUBCASE( case5, a_f, nd );
    ATLEAST_ND_SUBCASE( case5, a_d, nd );
    ATLEAST_ND_SUBCASE( case5, a_h, nd );
   
    #else
    ATLEAST_ND_SUBCASE( case5, a_cs_fb, nd );
    ATLEAST_ND_SUBCASE( case5, a_cs_hb, nd );
    ATLEAST_ND_SUBCASE( case5, a_cs_db, nd );

    ATLEAST_ND_SUBCASE( case5, a_fs_fb, nd );
    ATLEAST_ND_SUBCASE( case5, a_fs_hb, nd );
    ATLEAST_ND_SUBCASE( case5, a_fs_db, nd );

    ATLEAST_ND_SUBCASE( case5, a_hs_fb, nd );
    ATLEAST_ND_SUBCASE( case5, a_hs_hb, nd );
    ATLEAST_ND_SUBCASE( case5, a_hs_db, nd );

    ATLEAST_ND_SUBCASE( case5, a_ds_fb, nd );
    ATLEAST_ND_SUBCASE( case5, a_ds_hb, nd );
    ATLEAST_ND_SUBCASE( case5, a_ds_db, nd );

    ATLEAST_ND_SUBCASE( case5, a_ls_fb, nd );
    ATLEAST_ND_SUBCASE( case5, a_ls_hb, nd );
    ATLEAST_ND_SUBCASE( case5, a_ls_db, nd );
    #endif
}