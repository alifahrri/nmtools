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

#include "nmtools/array/matmul.hpp"
#include "nmtools/testing/data/array/matmul.hpp"
#include "nmtools/testing/doctest.hpp"

#define MATMUL_SUBCASE(case_name, ...) \
SUBCASE(#case_name) \
{ \
    NMTOOLS_TESTING_USE_CASE(array, matmul, case_name); \
    using namespace args; \
    auto result = nmtools::view::matmulv2(__VA_ARGS__); \
    NMTOOLS_ASSERT_EQUAL( nmtools::shape(result), nmtools::shape(expect::result) ); \
    NMTOOLS_ASSERT_EQUAL( result, expect::result ); \
}

TEST_CASE("matmul(case1)" * doctest::test_suite("view::matmul"))
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

TEST_CASE("matmul(case2)" * doctest::test_suite("view::matmul"))
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

#define MATMULV2_SUBCASE(case_name, ...) \
SUBCASE(#case_name) \
{ \
    NMTOOLS_TESTING_USE_CASE(array, matmul, case_name); \
    using namespace args; \
    auto result = nmtools::view::matmulv2(__VA_ARGS__); \
    NMTOOLS_ASSERT_EQUAL( nmtools::shape(result), nmtools::shape(expect::result) ); \
    NMTOOLS_ASSERT_EQUAL( result, expect::result ); \
}

TEST_CASE("matmul(case1a)" * doctest::test_suite("view::matmulv2"))
{
    MATMULV2_SUBCASE( case1a, lhs, rhs );
    MATMULV2_SUBCASE( case1a, lhs_a, rhs_a );
    MATMULV2_SUBCASE( case1a, lhs_f, rhs_f );
    MATMULV2_SUBCASE( case1a, lhs_h, rhs_h );
    // MATMULV2_SUBCASE( case1a, lhs_d, rhs_d );
}

TEST_CASE("matmul(case1b)" * doctest::test_suite("view::matmulv2"))
{
    MATMULV2_SUBCASE( case1b, lhs, rhs );
    MATMULV2_SUBCASE( case1b, lhs_a, rhs_a );
    MATMULV2_SUBCASE( case1b, lhs_f, rhs_f );
    MATMULV2_SUBCASE( case1b, lhs_h, rhs_h );
    MATMULV2_SUBCASE( case1b, lhs_d, rhs_d );
}

TEST_CASE("matmul(case1c)" * doctest::test_suite("view::matmulv2"))
{
    MATMULV2_SUBCASE( case1c, lhs, rhs );
    MATMULV2_SUBCASE( case1c, lhs_a, rhs_a );
    MATMULV2_SUBCASE( case1c, lhs_f, rhs_f );
    MATMULV2_SUBCASE( case1c, lhs_h, rhs_h );
    MATMULV2_SUBCASE( case1c, lhs_d, rhs_d );
}

TEST_CASE("matmul(case1d)" * doctest::test_suite("view::matmulv2"))
{
    MATMULV2_SUBCASE( case1d, lhs, rhs );
    MATMULV2_SUBCASE( case1d, lhs_a, rhs_a );
    MATMULV2_SUBCASE( case1d, lhs_f, rhs_f );
    MATMULV2_SUBCASE( case1d, lhs_h, rhs_h );
    MATMULV2_SUBCASE( case1d, lhs_d, rhs_d );
}

TEST_CASE("matmul(case2a)" * doctest::test_suite("view::matmulv2"))
{
    MATMULV2_SUBCASE( case2a, lhs, rhs );
    MATMULV2_SUBCASE( case2a, lhs_a, rhs_a );
    MATMULV2_SUBCASE( case2a, lhs_f, rhs_f );
    MATMULV2_SUBCASE( case2a, lhs_h, rhs_h );
    MATMULV2_SUBCASE( case2a, lhs_d, rhs_d );
}

TEST_CASE("matmul(case2b)" * doctest::test_suite("view::matmulv2"))
{
    MATMULV2_SUBCASE( case2b, lhs, rhs );
    MATMULV2_SUBCASE( case2b, lhs_a, rhs_a );
    MATMULV2_SUBCASE( case2b, lhs_f, rhs_f );
    MATMULV2_SUBCASE( case2b, lhs_h, rhs_h );
    MATMULV2_SUBCASE( case2b, lhs_d, rhs_d );
}

TEST_CASE("matmul(case2c)" * doctest::test_suite("view::matmulv2"))
{
    MATMULV2_SUBCASE( case2c, lhs, rhs );
    MATMULV2_SUBCASE( case2c, lhs_a, rhs_a );
    MATMULV2_SUBCASE( case2c, lhs_f, rhs_f );
    MATMULV2_SUBCASE( case2c, lhs_h, rhs_h );
    MATMULV2_SUBCASE( case2c, lhs_d, rhs_d );
}

TEST_CASE("matmul(case2d)" * doctest::test_suite("view::matmulv2"))
{
    MATMULV2_SUBCASE( case2d, lhs, rhs );
    MATMULV2_SUBCASE( case2d, lhs_a, rhs_a );
    MATMULV2_SUBCASE( case2d, lhs_f, rhs_f );
    MATMULV2_SUBCASE( case2d, lhs_h, rhs_h );
    MATMULV2_SUBCASE( case2d, lhs_d, rhs_d );
}

TEST_CASE("matmul(case3a)" * doctest::test_suite("view::matmulv2"))
{
    MATMULV2_SUBCASE( case3a, lhs, rhs );
    MATMULV2_SUBCASE( case3a, lhs_a, rhs_a );
    MATMULV2_SUBCASE( case3a, lhs_f, rhs_f );
    MATMULV2_SUBCASE( case3a, lhs_h, rhs_h );
    MATMULV2_SUBCASE( case3a, lhs_d, rhs_d );
}

TEST_CASE("matmul(case3b)" * doctest::test_suite("view::matmulv2"))
{
    MATMULV2_SUBCASE( case3b, lhs, rhs );
    MATMULV2_SUBCASE( case3b, lhs_a, rhs_a );
    MATMULV2_SUBCASE( case3b, lhs_f, rhs_f );
    MATMULV2_SUBCASE( case3b, lhs_h, rhs_h );
    MATMULV2_SUBCASE( case3b, lhs_d, rhs_d );
}

TEST_CASE("matmul(case3c)" * doctest::test_suite("view::matmulv2"))
{
    MATMULV2_SUBCASE( case3c, lhs, rhs );
    MATMULV2_SUBCASE( case3c, lhs_a, rhs_a );
    MATMULV2_SUBCASE( case3c, lhs_f, rhs_f );
    MATMULV2_SUBCASE( case3c, lhs_h, rhs_h );
    MATMULV2_SUBCASE( case3c, lhs_d, rhs_d );
}

TEST_CASE("matmul(case3d)" * doctest::test_suite("view::matmulv2"))
{
    MATMULV2_SUBCASE( case3d, lhs, rhs );
    MATMULV2_SUBCASE( case3d, lhs_a, rhs_a );
    MATMULV2_SUBCASE( case3d, lhs_f, rhs_f );
    MATMULV2_SUBCASE( case3d, lhs_h, rhs_h );
    MATMULV2_SUBCASE( case3d, lhs_d, rhs_d );
}