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

#include "nmtools/array/array/matmul.hpp"
#include "nmtools/testing/data/array/matmul.hpp"
#include "nmtools/testing/doctest.hpp"

#define MATMUL_SUBCASE(case_name, ...) \
SUBCASE(#case_name) \
{ \
    NMTOOLS_TESTING_DECLARE_NS(array, matmul, case_name); \
    using namespace args; \
    auto result = nmtools::array::matmul(__VA_ARGS__); \
    NMTOOLS_ASSERT_EQUAL( nmtools::shape(result), nmtools::shape(expect::result) ); \
    NMTOOLS_ASSERT_EQUAL( result, expect::result ); \
}

TEST_CASE("matmul(case1)" * doctest::test_suite("array::matmul"))
{
    #if !defined(NMTOOLS_TESTING_GENERIC_NDARRAY)
    MATMUL_SUBCASE( case1, lhs, rhs );
    MATMUL_SUBCASE( case1, lhs_a, rhs_a );
    MATMUL_SUBCASE( case1, lhs_f, rhs_f );
    MATMUL_SUBCASE( case1, lhs_h, rhs_h );
    MATMUL_SUBCASE( case1, lhs_d, rhs_d );

    #else
    MATMUL_SUBCASE( case1, lhs_cs_fb, rhs_cs_fb );
    MATMUL_SUBCASE( case1, lhs_cs_hb, rhs_cs_hb );
    MATMUL_SUBCASE( case1, lhs_cs_db, rhs_cs_db );

    MATMUL_SUBCASE( case1, lhs_fs_fb, rhs_fs_fb );
    MATMUL_SUBCASE( case1, lhs_fs_hb, rhs_fs_hb );
    MATMUL_SUBCASE( case1, lhs_fs_db, rhs_fs_db );

    MATMUL_SUBCASE( case1, lhs_hs_fb, rhs_hs_fb );
    MATMUL_SUBCASE( case1, lhs_hs_hb, rhs_hs_hb );
    MATMUL_SUBCASE( case1, lhs_hs_db, rhs_hs_db );

    MATMUL_SUBCASE( case1, lhs_ds_fb, rhs_ds_fb );
    MATMUL_SUBCASE( case1, lhs_ds_hb, rhs_ds_hb );
    MATMUL_SUBCASE( case1, lhs_ds_db, rhs_ds_db );

    MATMUL_SUBCASE( case1, lhs_ls_fb, rhs_ls_fb );
    MATMUL_SUBCASE( case1, lhs_ls_hb, rhs_ls_hb );
    MATMUL_SUBCASE( case1, lhs_ls_db, rhs_ls_db );

    MATMUL_SUBCASE( case1, lhs_fs_fb, rhs_cs_fb );
    MATMUL_SUBCASE( case1, lhs_fs_hb, rhs_cs_hb );
    MATMUL_SUBCASE( case1, lhs_fs_db, rhs_cs_db );

    MATMUL_SUBCASE( case1, lhs_hs_fb, rhs_cs_fb );
    MATMUL_SUBCASE( case1, lhs_hs_hb, rhs_cs_hb );
    MATMUL_SUBCASE( case1, lhs_hs_db, rhs_cs_db );

    MATMUL_SUBCASE( case1, lhs_ds_fb, rhs_cs_fb );
    MATMUL_SUBCASE( case1, lhs_ds_hb, rhs_cs_hb );
    MATMUL_SUBCASE( case1, lhs_ds_db, rhs_cs_db );

    MATMUL_SUBCASE( case1, lhs_ls_fb, rhs_cs_fb );
    MATMUL_SUBCASE( case1, lhs_ls_hb, rhs_cs_hb );
    MATMUL_SUBCASE( case1, lhs_ls_db, rhs_cs_db );

    MATMUL_SUBCASE( case1, lhs_cs_fb, rhs_fs_fb );
    MATMUL_SUBCASE( case1, lhs_cs_hb, rhs_fs_hb );
    MATMUL_SUBCASE( case1, lhs_cs_db, rhs_fs_db );

    MATMUL_SUBCASE( case1, lhs_hs_fb, rhs_fs_fb );
    MATMUL_SUBCASE( case1, lhs_hs_hb, rhs_fs_hb );
    MATMUL_SUBCASE( case1, lhs_hs_db, rhs_fs_db );

    MATMUL_SUBCASE( case1, lhs_ds_fb, rhs_fs_fb );
    MATMUL_SUBCASE( case1, lhs_ds_hb, rhs_fs_hb );
    MATMUL_SUBCASE( case1, lhs_ds_db, rhs_fs_db );

    MATMUL_SUBCASE( case1, lhs_ls_fb, rhs_fs_fb );
    MATMUL_SUBCASE( case1, lhs_ls_hb, rhs_fs_hb );
    MATMUL_SUBCASE( case1, lhs_ls_db, rhs_fs_db );

    MATMUL_SUBCASE( case1, lhs_cs_fb, rhs_hs_fb );
    MATMUL_SUBCASE( case1, lhs_cs_hb, rhs_hs_hb );
    MATMUL_SUBCASE( case1, lhs_cs_db, rhs_hs_db );

    MATMUL_SUBCASE( case1, lhs_fs_fb, rhs_hs_fb );
    MATMUL_SUBCASE( case1, lhs_fs_hb, rhs_hs_hb );
    MATMUL_SUBCASE( case1, lhs_fs_db, rhs_hs_db );

    MATMUL_SUBCASE( case1, lhs_ds_fb, rhs_hs_fb );
    MATMUL_SUBCASE( case1, lhs_ds_hb, rhs_hs_hb );
    MATMUL_SUBCASE( case1, lhs_ds_db, rhs_hs_db );

    MATMUL_SUBCASE( case1, lhs_ls_fb, rhs_hs_fb );
    MATMUL_SUBCASE( case1, lhs_ls_hb, rhs_hs_hb );
    MATMUL_SUBCASE( case1, lhs_ls_db, rhs_hs_db );
    #endif
}

TEST_CASE("matmul(case2)" * doctest::test_suite("array::matmul"))
{
    #if !defined(NMTOOLS_TESTING_GENERIC_NDARRAY)
    MATMUL_SUBCASE( case2, lhs, rhs );
    MATMUL_SUBCASE( case2, lhs_a, rhs_a );
    MATMUL_SUBCASE( case2, lhs_f, rhs_f );
    MATMUL_SUBCASE( case2, lhs_h, rhs_h );
    MATMUL_SUBCASE( case2, lhs_d, rhs_d );

    #else
    MATMUL_SUBCASE( case2, lhs_cs_fb, rhs_cs_fb );
    MATMUL_SUBCASE( case2, lhs_cs_hb, rhs_cs_hb );
    MATMUL_SUBCASE( case2, lhs_cs_db, rhs_cs_db );

    MATMUL_SUBCASE( case2, lhs_fs_fb, rhs_fs_fb );
    MATMUL_SUBCASE( case2, lhs_fs_hb, rhs_fs_hb );
    MATMUL_SUBCASE( case2, lhs_fs_db, rhs_fs_db );

    MATMUL_SUBCASE( case2, lhs_hs_fb, rhs_hs_fb );
    MATMUL_SUBCASE( case2, lhs_hs_hb, rhs_hs_hb );
    MATMUL_SUBCASE( case2, lhs_hs_db, rhs_hs_db );

    MATMUL_SUBCASE( case2, lhs_ds_fb, rhs_ds_fb );
    MATMUL_SUBCASE( case2, lhs_ds_hb, rhs_ds_hb );
    MATMUL_SUBCASE( case2, lhs_ds_db, rhs_ds_db );

    MATMUL_SUBCASE( case2, lhs_ls_fb, rhs_ls_fb );
    MATMUL_SUBCASE( case2, lhs_ls_hb, rhs_ls_hb );
    MATMUL_SUBCASE( case2, lhs_ls_db, rhs_ls_db );

    MATMUL_SUBCASE( case2, lhs_fs_fb, rhs_cs_fb );
    MATMUL_SUBCASE( case2, lhs_fs_hb, rhs_cs_hb );
    MATMUL_SUBCASE( case2, lhs_fs_db, rhs_cs_db );

    MATMUL_SUBCASE( case2, lhs_hs_fb, rhs_cs_fb );
    MATMUL_SUBCASE( case2, lhs_hs_hb, rhs_cs_hb );
    MATMUL_SUBCASE( case2, lhs_hs_db, rhs_cs_db );

    MATMUL_SUBCASE( case2, lhs_ds_fb, rhs_cs_fb );
    MATMUL_SUBCASE( case2, lhs_ds_hb, rhs_cs_hb );
    MATMUL_SUBCASE( case2, lhs_ds_db, rhs_cs_db );

    MATMUL_SUBCASE( case2, lhs_ls_fb, rhs_cs_fb );
    MATMUL_SUBCASE( case2, lhs_ls_hb, rhs_cs_hb );
    MATMUL_SUBCASE( case2, lhs_ls_db, rhs_cs_db );

    MATMUL_SUBCASE( case2, lhs_cs_fb, rhs_fs_fb );
    MATMUL_SUBCASE( case2, lhs_cs_hb, rhs_fs_hb );
    MATMUL_SUBCASE( case2, lhs_cs_db, rhs_fs_db );

    MATMUL_SUBCASE( case2, lhs_hs_fb, rhs_fs_fb );
    MATMUL_SUBCASE( case2, lhs_hs_hb, rhs_fs_hb );
    MATMUL_SUBCASE( case2, lhs_hs_db, rhs_fs_db );

    MATMUL_SUBCASE( case2, lhs_ds_fb, rhs_fs_fb );
    MATMUL_SUBCASE( case2, lhs_ds_hb, rhs_fs_hb );
    MATMUL_SUBCASE( case2, lhs_ds_db, rhs_fs_db );

    MATMUL_SUBCASE( case2, lhs_ls_fb, rhs_fs_fb );
    MATMUL_SUBCASE( case2, lhs_ls_hb, rhs_fs_hb );
    MATMUL_SUBCASE( case2, lhs_ls_db, rhs_fs_db );

    MATMUL_SUBCASE( case2, lhs_cs_fb, rhs_hs_fb );
    MATMUL_SUBCASE( case2, lhs_cs_hb, rhs_hs_hb );
    MATMUL_SUBCASE( case2, lhs_cs_db, rhs_hs_db );

    MATMUL_SUBCASE( case2, lhs_fs_fb, rhs_hs_fb );
    MATMUL_SUBCASE( case2, lhs_fs_hb, rhs_hs_hb );
    MATMUL_SUBCASE( case2, lhs_fs_db, rhs_hs_db );

    MATMUL_SUBCASE( case2, lhs_ds_fb, rhs_hs_fb );
    MATMUL_SUBCASE( case2, lhs_ds_hb, rhs_hs_hb );
    MATMUL_SUBCASE( case2, lhs_ds_db, rhs_hs_db );

    MATMUL_SUBCASE( case2, lhs_ls_fb, rhs_hs_fb );
    MATMUL_SUBCASE( case2, lhs_ls_hb, rhs_hs_hb );
    MATMUL_SUBCASE( case2, lhs_ls_db, rhs_hs_db );
    #endif
}