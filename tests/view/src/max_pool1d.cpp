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

#include "nmtools/array/pooling.hpp"
#include "nmtools/testing/data/array/max_pool1d.hpp"
#include "nmtools/testing/doctest.hpp"

#define MAX_POOL1D_SUBCASE(case_name, ...) \
SUBCASE(#case_name) \
{ \
    NMTOOLS_TESTING_USE_CASE(array, max_pool1d, case_name); \
    using namespace args; \
    auto result = nmtools::view::max_pool1d(__VA_ARGS__); \
    NMTOOLS_ASSERT_EQUAL( nmtools::shape(result), nmtools::shape(expect::result) ); \
    NMTOOLS_ASSERT_CLOSE( result, expect::result ); \
}

#if 1
TEST_CASE("max_pool1d(case1)" * doctest::test_suite("view::max_pool1d"))
{
    #if !defined(NMTOOLS_TESTING_GENERIC_NDARRAY)
    MAX_POOL1D_SUBCASE( case1, array, kernel_size, stride, padding, dilation, ceil_mode );
    MAX_POOL1D_SUBCASE( case1, array_a, kernel_size, stride, padding, dilation, ceil_mode );
    MAX_POOL1D_SUBCASE( case1, array_f, kernel_size, stride, padding, dilation, ceil_mode );
    MAX_POOL1D_SUBCASE( case1, array_h, kernel_size, stride, padding, dilation, ceil_mode );
    MAX_POOL1D_SUBCASE( case1, array_d, kernel_size, stride, padding, dilation, ceil_mode );
    #else
    MAX_POOL1D_SUBCASE( case1, array_cs_fb, kernel_size, stride, padding, dilation, ceil_mode );
    MAX_POOL1D_SUBCASE( case1, array_fs_fb, kernel_size, stride, padding, dilation, ceil_mode );
    MAX_POOL1D_SUBCASE( case1, array_hs_fb, kernel_size, stride, padding, dilation, ceil_mode );
    MAX_POOL1D_SUBCASE( case1, array_ds_fb, kernel_size, stride, padding, dilation, ceil_mode );
    MAX_POOL1D_SUBCASE( case1, array_ls_fb, kernel_size, stride, padding, dilation, ceil_mode );

    MAX_POOL1D_SUBCASE( case1, array_cs_hb, kernel_size, stride, padding, dilation, ceil_mode );
    MAX_POOL1D_SUBCASE( case1, array_fs_hb, kernel_size, stride, padding, dilation, ceil_mode );
    MAX_POOL1D_SUBCASE( case1, array_hs_hb, kernel_size, stride, padding, dilation, ceil_mode );
    MAX_POOL1D_SUBCASE( case1, array_ds_hb, kernel_size, stride, padding, dilation, ceil_mode );
    MAX_POOL1D_SUBCASE( case1, array_ls_hb, kernel_size, stride, padding, dilation, ceil_mode );

    MAX_POOL1D_SUBCASE( case1, array_cs_db, kernel_size, stride, padding, dilation, ceil_mode );
    MAX_POOL1D_SUBCASE( case1, array_fs_db, kernel_size, stride, padding, dilation, ceil_mode );
    MAX_POOL1D_SUBCASE( case1, array_hs_db, kernel_size, stride, padding, dilation, ceil_mode );
    MAX_POOL1D_SUBCASE( case1, array_ds_db, kernel_size, stride, padding, dilation, ceil_mode );
    MAX_POOL1D_SUBCASE( case1, array_ls_db, kernel_size, stride, padding, dilation, ceil_mode );
    #endif
}
#endif

TEST_CASE("max_pool1d(case1b)" * doctest::test_suite("view::max_pool1d"))
{
    #if !defined(NMTOOLS_TESTING_GENERIC_NDARRAY)
    MAX_POOL1D_SUBCASE( case1b, array, kernel_size, stride, padding, dilation, ceil_mode );
    MAX_POOL1D_SUBCASE( case1b, array_a, kernel_size, stride, padding, dilation, ceil_mode );
    MAX_POOL1D_SUBCASE( case1b, array_f, kernel_size, stride, padding, dilation, ceil_mode );
    MAX_POOL1D_SUBCASE( case1b, array_h, kernel_size, stride, padding, dilation, ceil_mode );
    MAX_POOL1D_SUBCASE( case1b, array_d, kernel_size, stride, padding, dilation, ceil_mode );
    #else
    MAX_POOL1D_SUBCASE( case1b, array_cs_fb, kernel_size, stride, padding, dilation, ceil_mode );
    MAX_POOL1D_SUBCASE( case1b, array_fs_fb, kernel_size, stride, padding, dilation, ceil_mode );
    MAX_POOL1D_SUBCASE( case1b, array_hs_fb, kernel_size, stride, padding, dilation, ceil_mode );
    MAX_POOL1D_SUBCASE( case1b, array_ds_fb, kernel_size, stride, padding, dilation, ceil_mode );
    MAX_POOL1D_SUBCASE( case1b, array_ls_fb, kernel_size, stride, padding, dilation, ceil_mode );

    MAX_POOL1D_SUBCASE( case1b, array_cs_hb, kernel_size, stride, padding, dilation, ceil_mode );
    MAX_POOL1D_SUBCASE( case1b, array_fs_hb, kernel_size, stride, padding, dilation, ceil_mode );
    MAX_POOL1D_SUBCASE( case1b, array_hs_hb, kernel_size, stride, padding, dilation, ceil_mode );
    MAX_POOL1D_SUBCASE( case1b, array_ds_hb, kernel_size, stride, padding, dilation, ceil_mode );
    MAX_POOL1D_SUBCASE( case1b, array_ls_hb, kernel_size, stride, padding, dilation, ceil_mode );

    MAX_POOL1D_SUBCASE( case1b, array_cs_db, kernel_size, stride, padding, dilation, ceil_mode );
    MAX_POOL1D_SUBCASE( case1b, array_fs_db, kernel_size, stride, padding, dilation, ceil_mode );
    MAX_POOL1D_SUBCASE( case1b, array_hs_db, kernel_size, stride, padding, dilation, ceil_mode );
    MAX_POOL1D_SUBCASE( case1b, array_ds_db, kernel_size, stride, padding, dilation, ceil_mode );
    MAX_POOL1D_SUBCASE( case1b, array_ls_db, kernel_size, stride, padding, dilation, ceil_mode );
    #endif
}

#if 1
TEST_CASE("max_pool1d(case2)" * doctest::test_suite("view::max_pool1d"))
{
    #if !defined(NMTOOLS_TESTING_GENERIC_NDARRAY)
    MAX_POOL1D_SUBCASE( case2, array, kernel_size, stride, padding, dilation, ceil_mode );
    MAX_POOL1D_SUBCASE( case2, array_a, kernel_size, stride, padding, dilation, ceil_mode );
    MAX_POOL1D_SUBCASE( case2, array_f, kernel_size, stride, padding, dilation, ceil_mode );
    MAX_POOL1D_SUBCASE( case2, array_h, kernel_size, stride, padding, dilation, ceil_mode );
    MAX_POOL1D_SUBCASE( case2, array_d, kernel_size, stride, padding, dilation, ceil_mode );
    #else
    MAX_POOL1D_SUBCASE( case2, array_cs_fb, kernel_size, stride, padding, dilation, ceil_mode );
    MAX_POOL1D_SUBCASE( case2, array_fs_fb, kernel_size, stride, padding, dilation, ceil_mode );
    MAX_POOL1D_SUBCASE( case2, array_hs_fb, kernel_size, stride, padding, dilation, ceil_mode );
    MAX_POOL1D_SUBCASE( case2, array_ds_fb, kernel_size, stride, padding, dilation, ceil_mode );
    MAX_POOL1D_SUBCASE( case2, array_ls_fb, kernel_size, stride, padding, dilation, ceil_mode );

    MAX_POOL1D_SUBCASE( case2, array_cs_hb, kernel_size, stride, padding, dilation, ceil_mode );
    MAX_POOL1D_SUBCASE( case2, array_fs_hb, kernel_size, stride, padding, dilation, ceil_mode );
    MAX_POOL1D_SUBCASE( case2, array_hs_hb, kernel_size, stride, padding, dilation, ceil_mode );
    MAX_POOL1D_SUBCASE( case2, array_ds_hb, kernel_size, stride, padding, dilation, ceil_mode );
    MAX_POOL1D_SUBCASE( case2, array_ls_hb, kernel_size, stride, padding, dilation, ceil_mode );

    MAX_POOL1D_SUBCASE( case2, array_cs_db, kernel_size, stride, padding, dilation, ceil_mode );
    MAX_POOL1D_SUBCASE( case2, array_fs_db, kernel_size, stride, padding, dilation, ceil_mode );
    MAX_POOL1D_SUBCASE( case2, array_hs_db, kernel_size, stride, padding, dilation, ceil_mode );
    MAX_POOL1D_SUBCASE( case2, array_ds_db, kernel_size, stride, padding, dilation, ceil_mode );
    MAX_POOL1D_SUBCASE( case2, array_ls_db, kernel_size, stride, padding, dilation, ceil_mode );
    #endif
}
#endif

TEST_CASE("max_pool1d(case2b)" * doctest::test_suite("view::max_pool1d"))
{
    #if !defined(NMTOOLS_TESTING_GENERIC_NDARRAY)
    MAX_POOL1D_SUBCASE( case2b, array, kernel_size, stride, padding, dilation, ceil_mode );
    MAX_POOL1D_SUBCASE( case2b, array_a, kernel_size, stride, padding, dilation, ceil_mode );
    MAX_POOL1D_SUBCASE( case2b, array_f, kernel_size, stride, padding, dilation, ceil_mode );
    MAX_POOL1D_SUBCASE( case2b, array_h, kernel_size, stride, padding, dilation, ceil_mode );
    MAX_POOL1D_SUBCASE( case2b, array_d, kernel_size, stride, padding, dilation, ceil_mode );
    #else
    MAX_POOL1D_SUBCASE( case2b, array_cs_fb, kernel_size, stride, padding, dilation, ceil_mode );
    MAX_POOL1D_SUBCASE( case2b, array_fs_fb, kernel_size, stride, padding, dilation, ceil_mode );
    MAX_POOL1D_SUBCASE( case2b, array_hs_fb, kernel_size, stride, padding, dilation, ceil_mode );
    MAX_POOL1D_SUBCASE( case2b, array_ds_fb, kernel_size, stride, padding, dilation, ceil_mode );
    MAX_POOL1D_SUBCASE( case2b, array_ls_fb, kernel_size, stride, padding, dilation, ceil_mode );

    MAX_POOL1D_SUBCASE( case2b, array_cs_hb, kernel_size, stride, padding, dilation, ceil_mode );
    MAX_POOL1D_SUBCASE( case2b, array_fs_hb, kernel_size, stride, padding, dilation, ceil_mode );
    MAX_POOL1D_SUBCASE( case2b, array_hs_hb, kernel_size, stride, padding, dilation, ceil_mode );
    MAX_POOL1D_SUBCASE( case2b, array_ds_hb, kernel_size, stride, padding, dilation, ceil_mode );
    MAX_POOL1D_SUBCASE( case2b, array_ls_hb, kernel_size, stride, padding, dilation, ceil_mode );

    MAX_POOL1D_SUBCASE( case2b, array_cs_db, kernel_size, stride, padding, dilation, ceil_mode );
    MAX_POOL1D_SUBCASE( case2b, array_fs_db, kernel_size, stride, padding, dilation, ceil_mode );
    MAX_POOL1D_SUBCASE( case2b, array_hs_db, kernel_size, stride, padding, dilation, ceil_mode );
    MAX_POOL1D_SUBCASE( case2b, array_ds_db, kernel_size, stride, padding, dilation, ceil_mode );
    MAX_POOL1D_SUBCASE( case2b, array_ls_db, kernel_size, stride, padding, dilation, ceil_mode );
    #endif
}

#if 1
TEST_CASE("max_pool1d(case3)" * doctest::test_suite("view::max_pool1d"))
{
    #if !defined(NMTOOLS_TESTING_GENERIC_NDARRAY)
    MAX_POOL1D_SUBCASE( case3, array, kernel_size, stride, padding, dilation, ceil_mode );
    MAX_POOL1D_SUBCASE( case3, array_a, kernel_size, stride, padding, dilation, ceil_mode );
    MAX_POOL1D_SUBCASE( case3, array_f, kernel_size, stride, padding, dilation, ceil_mode );
    MAX_POOL1D_SUBCASE( case3, array_h, kernel_size, stride, padding, dilation, ceil_mode );
    MAX_POOL1D_SUBCASE( case3, array_d, kernel_size, stride, padding, dilation, ceil_mode );
    #else
    MAX_POOL1D_SUBCASE( case3, array_cs_fb, kernel_size, stride, padding, dilation, ceil_mode );
    MAX_POOL1D_SUBCASE( case3, array_fs_fb, kernel_size, stride, padding, dilation, ceil_mode );
    MAX_POOL1D_SUBCASE( case3, array_hs_fb, kernel_size, stride, padding, dilation, ceil_mode );
    MAX_POOL1D_SUBCASE( case3, array_ds_fb, kernel_size, stride, padding, dilation, ceil_mode );
    MAX_POOL1D_SUBCASE( case3, array_ls_fb, kernel_size, stride, padding, dilation, ceil_mode );

    MAX_POOL1D_SUBCASE( case3, array_cs_hb, kernel_size, stride, padding, dilation, ceil_mode );
    MAX_POOL1D_SUBCASE( case3, array_fs_hb, kernel_size, stride, padding, dilation, ceil_mode );
    MAX_POOL1D_SUBCASE( case3, array_hs_hb, kernel_size, stride, padding, dilation, ceil_mode );
    MAX_POOL1D_SUBCASE( case3, array_ds_hb, kernel_size, stride, padding, dilation, ceil_mode );
    MAX_POOL1D_SUBCASE( case3, array_ls_hb, kernel_size, stride, padding, dilation, ceil_mode );

    MAX_POOL1D_SUBCASE( case3, array_cs_db, kernel_size, stride, padding, dilation, ceil_mode );
    MAX_POOL1D_SUBCASE( case3, array_fs_db, kernel_size, stride, padding, dilation, ceil_mode );
    MAX_POOL1D_SUBCASE( case3, array_hs_db, kernel_size, stride, padding, dilation, ceil_mode );
    MAX_POOL1D_SUBCASE( case3, array_ds_db, kernel_size, stride, padding, dilation, ceil_mode );
    MAX_POOL1D_SUBCASE( case3, array_ls_db, kernel_size, stride, padding, dilation, ceil_mode );
    #endif
}
#endif

TEST_CASE("max_pool1d(case3b)" * doctest::test_suite("view::max_pool1d"))
{
    #if !defined(NMTOOLS_TESTING_GENERIC_NDARRAY)
    MAX_POOL1D_SUBCASE( case3b, array, kernel_size, stride, padding, dilation, ceil_mode );
    MAX_POOL1D_SUBCASE( case3b, array_a, kernel_size, stride, padding, dilation, ceil_mode );
    MAX_POOL1D_SUBCASE( case3b, array_f, kernel_size, stride, padding, dilation, ceil_mode );
    MAX_POOL1D_SUBCASE( case3b, array_h, kernel_size, stride, padding, dilation, ceil_mode );
    MAX_POOL1D_SUBCASE( case3b, array_d, kernel_size, stride, padding, dilation, ceil_mode );
    #else
    MAX_POOL1D_SUBCASE( case3b, array_cs_fb, kernel_size, stride, padding, dilation, ceil_mode );
    MAX_POOL1D_SUBCASE( case3b, array_fs_fb, kernel_size, stride, padding, dilation, ceil_mode );
    MAX_POOL1D_SUBCASE( case3b, array_hs_fb, kernel_size, stride, padding, dilation, ceil_mode );
    MAX_POOL1D_SUBCASE( case3b, array_ds_fb, kernel_size, stride, padding, dilation, ceil_mode );
    MAX_POOL1D_SUBCASE( case3b, array_ls_fb, kernel_size, stride, padding, dilation, ceil_mode );

    MAX_POOL1D_SUBCASE( case3b, array_cs_hb, kernel_size, stride, padding, dilation, ceil_mode );
    MAX_POOL1D_SUBCASE( case3b, array_fs_hb, kernel_size, stride, padding, dilation, ceil_mode );
    MAX_POOL1D_SUBCASE( case3b, array_hs_hb, kernel_size, stride, padding, dilation, ceil_mode );
    MAX_POOL1D_SUBCASE( case3b, array_ds_hb, kernel_size, stride, padding, dilation, ceil_mode );
    MAX_POOL1D_SUBCASE( case3b, array_ls_hb, kernel_size, stride, padding, dilation, ceil_mode );

    MAX_POOL1D_SUBCASE( case3b, array_cs_db, kernel_size, stride, padding, dilation, ceil_mode );
    MAX_POOL1D_SUBCASE( case3b, array_fs_db, kernel_size, stride, padding, dilation, ceil_mode );
    MAX_POOL1D_SUBCASE( case3b, array_hs_db, kernel_size, stride, padding, dilation, ceil_mode );
    MAX_POOL1D_SUBCASE( case3b, array_ds_db, kernel_size, stride, padding, dilation, ceil_mode );
    MAX_POOL1D_SUBCASE( case3b, array_ls_db, kernel_size, stride, padding, dilation, ceil_mode );
    #endif
}

#if 1
TEST_CASE("max_pool1d(case4)" * doctest::test_suite("view::max_pool1d"))
{
    #if !defined(NMTOOLS_TESTING_GENERIC_NDARRAY)
    MAX_POOL1D_SUBCASE( case4, array, kernel_size, stride, padding, dilation, ceil_mode );
    MAX_POOL1D_SUBCASE( case4, array_a, kernel_size, stride, padding, dilation, ceil_mode );
    MAX_POOL1D_SUBCASE( case4, array_f, kernel_size, stride, padding, dilation, ceil_mode );
    MAX_POOL1D_SUBCASE( case4, array_h, kernel_size, stride, padding, dilation, ceil_mode );
    MAX_POOL1D_SUBCASE( case4, array_d, kernel_size, stride, padding, dilation, ceil_mode );
    #else
    MAX_POOL1D_SUBCASE( case4, array_cs_fb, kernel_size, stride, padding, dilation, ceil_mode );
    MAX_POOL1D_SUBCASE( case4, array_fs_fb, kernel_size, stride, padding, dilation, ceil_mode );
    MAX_POOL1D_SUBCASE( case4, array_hs_fb, kernel_size, stride, padding, dilation, ceil_mode );
    MAX_POOL1D_SUBCASE( case4, array_ds_fb, kernel_size, stride, padding, dilation, ceil_mode );
    MAX_POOL1D_SUBCASE( case4, array_ls_fb, kernel_size, stride, padding, dilation, ceil_mode );

    MAX_POOL1D_SUBCASE( case4, array_cs_hb, kernel_size, stride, padding, dilation, ceil_mode );
    MAX_POOL1D_SUBCASE( case4, array_fs_hb, kernel_size, stride, padding, dilation, ceil_mode );
    MAX_POOL1D_SUBCASE( case4, array_hs_hb, kernel_size, stride, padding, dilation, ceil_mode );
    MAX_POOL1D_SUBCASE( case4, array_ds_hb, kernel_size, stride, padding, dilation, ceil_mode );
    MAX_POOL1D_SUBCASE( case4, array_ls_hb, kernel_size, stride, padding, dilation, ceil_mode );

    MAX_POOL1D_SUBCASE( case4, array_cs_db, kernel_size, stride, padding, dilation, ceil_mode );
    MAX_POOL1D_SUBCASE( case4, array_fs_db, kernel_size, stride, padding, dilation, ceil_mode );
    MAX_POOL1D_SUBCASE( case4, array_hs_db, kernel_size, stride, padding, dilation, ceil_mode );
    MAX_POOL1D_SUBCASE( case4, array_ds_db, kernel_size, stride, padding, dilation, ceil_mode );
    MAX_POOL1D_SUBCASE( case4, array_ls_db, kernel_size, stride, padding, dilation, ceil_mode );
    #endif
}
#endif

TEST_CASE("max_pool1d(case4b)" * doctest::test_suite("view::max_pool1d"))
{
    #if !defined(NMTOOLS_TESTING_GENERIC_NDARRAY)
    MAX_POOL1D_SUBCASE( case4b, array, kernel_size, stride, padding, dilation, ceil_mode );
    MAX_POOL1D_SUBCASE( case4b, array_a, kernel_size, stride, padding, dilation, ceil_mode );
    MAX_POOL1D_SUBCASE( case4b, array_f, kernel_size, stride, padding, dilation, ceil_mode );
    MAX_POOL1D_SUBCASE( case4b, array_h, kernel_size, stride, padding, dilation, ceil_mode );
    MAX_POOL1D_SUBCASE( case4b, array_d, kernel_size, stride, padding, dilation, ceil_mode );
    #else
    MAX_POOL1D_SUBCASE( case4b, array_cs_fb, kernel_size, stride, padding, dilation, ceil_mode );
    MAX_POOL1D_SUBCASE( case4b, array_fs_fb, kernel_size, stride, padding, dilation, ceil_mode );
    MAX_POOL1D_SUBCASE( case4b, array_hs_fb, kernel_size, stride, padding, dilation, ceil_mode );
    MAX_POOL1D_SUBCASE( case4b, array_ds_fb, kernel_size, stride, padding, dilation, ceil_mode );
    MAX_POOL1D_SUBCASE( case4b, array_ls_fb, kernel_size, stride, padding, dilation, ceil_mode );

    MAX_POOL1D_SUBCASE( case4b, array_cs_hb, kernel_size, stride, padding, dilation, ceil_mode );
    MAX_POOL1D_SUBCASE( case4b, array_fs_hb, kernel_size, stride, padding, dilation, ceil_mode );
    MAX_POOL1D_SUBCASE( case4b, array_hs_hb, kernel_size, stride, padding, dilation, ceil_mode );
    MAX_POOL1D_SUBCASE( case4b, array_ds_hb, kernel_size, stride, padding, dilation, ceil_mode );
    MAX_POOL1D_SUBCASE( case4b, array_ls_hb, kernel_size, stride, padding, dilation, ceil_mode );

    MAX_POOL1D_SUBCASE( case4b, array_cs_db, kernel_size, stride, padding, dilation, ceil_mode );
    MAX_POOL1D_SUBCASE( case4b, array_fs_db, kernel_size, stride, padding, dilation, ceil_mode );
    MAX_POOL1D_SUBCASE( case4b, array_hs_db, kernel_size, stride, padding, dilation, ceil_mode );
    MAX_POOL1D_SUBCASE( case4b, array_ds_db, kernel_size, stride, padding, dilation, ceil_mode );
    MAX_POOL1D_SUBCASE( case4b, array_ls_db, kernel_size, stride, padding, dilation, ceil_mode );
    #endif
}

#if 1
TEST_CASE("max_pool1d(case5)" * doctest::test_suite("view::max_pool1d"))
{
    #if !defined(NMTOOLS_TESTING_GENERIC_NDARRAY)
    MAX_POOL1D_SUBCASE( case5, array, kernel_size, stride, padding, dilation, ceil_mode );
    MAX_POOL1D_SUBCASE( case5, array_a, kernel_size, stride, padding, dilation, ceil_mode );
    MAX_POOL1D_SUBCASE( case5, array_f, kernel_size, stride, padding, dilation, ceil_mode );
    MAX_POOL1D_SUBCASE( case5, array_h, kernel_size, stride, padding, dilation, ceil_mode );
    MAX_POOL1D_SUBCASE( case5, array_d, kernel_size, stride, padding, dilation, ceil_mode );
    #else
    MAX_POOL1D_SUBCASE( case5, array_cs_fb, kernel_size, stride, padding, dilation, ceil_mode );
    MAX_POOL1D_SUBCASE( case5, array_fs_fb, kernel_size, stride, padding, dilation, ceil_mode );
    MAX_POOL1D_SUBCASE( case5, array_hs_fb, kernel_size, stride, padding, dilation, ceil_mode );
    MAX_POOL1D_SUBCASE( case5, array_ds_fb, kernel_size, stride, padding, dilation, ceil_mode );
    MAX_POOL1D_SUBCASE( case5, array_ls_fb, kernel_size, stride, padding, dilation, ceil_mode );

    MAX_POOL1D_SUBCASE( case5, array_cs_hb, kernel_size, stride, padding, dilation, ceil_mode );
    MAX_POOL1D_SUBCASE( case5, array_fs_hb, kernel_size, stride, padding, dilation, ceil_mode );
    MAX_POOL1D_SUBCASE( case5, array_hs_hb, kernel_size, stride, padding, dilation, ceil_mode );
    MAX_POOL1D_SUBCASE( case5, array_ds_hb, kernel_size, stride, padding, dilation, ceil_mode );
    MAX_POOL1D_SUBCASE( case5, array_ls_hb, kernel_size, stride, padding, dilation, ceil_mode );

    MAX_POOL1D_SUBCASE( case5, array_cs_db, kernel_size, stride, padding, dilation, ceil_mode );
    MAX_POOL1D_SUBCASE( case5, array_fs_db, kernel_size, stride, padding, dilation, ceil_mode );
    MAX_POOL1D_SUBCASE( case5, array_hs_db, kernel_size, stride, padding, dilation, ceil_mode );
    MAX_POOL1D_SUBCASE( case5, array_ds_db, kernel_size, stride, padding, dilation, ceil_mode );
    MAX_POOL1D_SUBCASE( case5, array_ls_db, kernel_size, stride, padding, dilation, ceil_mode );
    #endif
}
#endif

TEST_CASE("max_pool1d(case5b)" * doctest::test_suite("view::max_pool1d"))
{
    #if !defined(NMTOOLS_TESTING_GENERIC_NDARRAY)
    MAX_POOL1D_SUBCASE( case5b, array, kernel_size, stride, padding, dilation, ceil_mode );
    MAX_POOL1D_SUBCASE( case5b, array_a, kernel_size, stride, padding, dilation, ceil_mode );
    MAX_POOL1D_SUBCASE( case5b, array_f, kernel_size, stride, padding, dilation, ceil_mode );
    MAX_POOL1D_SUBCASE( case5b, array_h, kernel_size, stride, padding, dilation, ceil_mode );
    MAX_POOL1D_SUBCASE( case5b, array_d, kernel_size, stride, padding, dilation, ceil_mode );
    #else
    MAX_POOL1D_SUBCASE( case5b, array_cs_fb, kernel_size, stride, padding, dilation, ceil_mode );
    MAX_POOL1D_SUBCASE( case5b, array_fs_fb, kernel_size, stride, padding, dilation, ceil_mode );
    MAX_POOL1D_SUBCASE( case5b, array_hs_fb, kernel_size, stride, padding, dilation, ceil_mode );
    MAX_POOL1D_SUBCASE( case5b, array_ds_fb, kernel_size, stride, padding, dilation, ceil_mode );
    MAX_POOL1D_SUBCASE( case5b, array_ls_fb, kernel_size, stride, padding, dilation, ceil_mode );

    MAX_POOL1D_SUBCASE( case5b, array_cs_hb, kernel_size, stride, padding, dilation, ceil_mode );
    MAX_POOL1D_SUBCASE( case5b, array_fs_hb, kernel_size, stride, padding, dilation, ceil_mode );
    MAX_POOL1D_SUBCASE( case5b, array_hs_hb, kernel_size, stride, padding, dilation, ceil_mode );
    MAX_POOL1D_SUBCASE( case5b, array_ds_hb, kernel_size, stride, padding, dilation, ceil_mode );
    MAX_POOL1D_SUBCASE( case5b, array_ls_hb, kernel_size, stride, padding, dilation, ceil_mode );

    MAX_POOL1D_SUBCASE( case5b, array_cs_db, kernel_size, stride, padding, dilation, ceil_mode );
    MAX_POOL1D_SUBCASE( case5b, array_fs_db, kernel_size, stride, padding, dilation, ceil_mode );
    MAX_POOL1D_SUBCASE( case5b, array_hs_db, kernel_size, stride, padding, dilation, ceil_mode );
    MAX_POOL1D_SUBCASE( case5b, array_ds_db, kernel_size, stride, padding, dilation, ceil_mode );
    MAX_POOL1D_SUBCASE( case5b, array_ls_db, kernel_size, stride, padding, dilation, ceil_mode );
    #endif
}

#if 1
TEST_CASE("max_pool1d(case6)" * doctest::test_suite("view::max_pool1d"))
{
    #if !defined(NMTOOLS_TESTING_GENERIC_NDARRAY)
    MAX_POOL1D_SUBCASE( case6, array, kernel_size, stride, padding, dilation, ceil_mode );
    MAX_POOL1D_SUBCASE( case6, array_a, kernel_size, stride, padding, dilation, ceil_mode );
    MAX_POOL1D_SUBCASE( case6, array_f, kernel_size, stride, padding, dilation, ceil_mode );
    MAX_POOL1D_SUBCASE( case6, array_h, kernel_size, stride, padding, dilation, ceil_mode );
    MAX_POOL1D_SUBCASE( case6, array_d, kernel_size, stride, padding, dilation, ceil_mode );
    #else
    MAX_POOL1D_SUBCASE( case6, array_cs_fb, kernel_size, stride, padding, dilation, ceil_mode );
    MAX_POOL1D_SUBCASE( case6, array_fs_fb, kernel_size, stride, padding, dilation, ceil_mode );
    MAX_POOL1D_SUBCASE( case6, array_hs_fb, kernel_size, stride, padding, dilation, ceil_mode );
    MAX_POOL1D_SUBCASE( case6, array_ds_fb, kernel_size, stride, padding, dilation, ceil_mode );
    MAX_POOL1D_SUBCASE( case6, array_ls_fb, kernel_size, stride, padding, dilation, ceil_mode );

    MAX_POOL1D_SUBCASE( case6, array_cs_hb, kernel_size, stride, padding, dilation, ceil_mode );
    MAX_POOL1D_SUBCASE( case6, array_fs_hb, kernel_size, stride, padding, dilation, ceil_mode );
    MAX_POOL1D_SUBCASE( case6, array_hs_hb, kernel_size, stride, padding, dilation, ceil_mode );
    MAX_POOL1D_SUBCASE( case6, array_ds_hb, kernel_size, stride, padding, dilation, ceil_mode );
    MAX_POOL1D_SUBCASE( case6, array_ls_hb, kernel_size, stride, padding, dilation, ceil_mode );

    MAX_POOL1D_SUBCASE( case6, array_cs_db, kernel_size, stride, padding, dilation, ceil_mode );
    MAX_POOL1D_SUBCASE( case6, array_fs_db, kernel_size, stride, padding, dilation, ceil_mode );
    MAX_POOL1D_SUBCASE( case6, array_hs_db, kernel_size, stride, padding, dilation, ceil_mode );
    MAX_POOL1D_SUBCASE( case6, array_ds_db, kernel_size, stride, padding, dilation, ceil_mode );
    MAX_POOL1D_SUBCASE( case6, array_ls_db, kernel_size, stride, padding, dilation, ceil_mode );
    #endif
}
#endif

TEST_CASE("max_pool1d(case6b)" * doctest::test_suite("view::max_pool1d"))
{
    #if !defined(NMTOOLS_TESTING_GENERIC_NDARRAY)
    MAX_POOL1D_SUBCASE( case6b, array, kernel_size, stride, padding, dilation, ceil_mode );
    MAX_POOL1D_SUBCASE( case6b, array_a, kernel_size, stride, padding, dilation, ceil_mode );
    MAX_POOL1D_SUBCASE( case6b, array_f, kernel_size, stride, padding, dilation, ceil_mode );
    MAX_POOL1D_SUBCASE( case6b, array_h, kernel_size, stride, padding, dilation, ceil_mode );
    MAX_POOL1D_SUBCASE( case6b, array_d, kernel_size, stride, padding, dilation, ceil_mode );
    #else
    MAX_POOL1D_SUBCASE( case6b, array_cs_fb, kernel_size, stride, padding, dilation, ceil_mode );
    MAX_POOL1D_SUBCASE( case6b, array_fs_fb, kernel_size, stride, padding, dilation, ceil_mode );
    MAX_POOL1D_SUBCASE( case6b, array_hs_fb, kernel_size, stride, padding, dilation, ceil_mode );
    MAX_POOL1D_SUBCASE( case6b, array_ds_fb, kernel_size, stride, padding, dilation, ceil_mode );
    MAX_POOL1D_SUBCASE( case6b, array_ls_fb, kernel_size, stride, padding, dilation, ceil_mode );

    MAX_POOL1D_SUBCASE( case6b, array_cs_hb, kernel_size, stride, padding, dilation, ceil_mode );
    MAX_POOL1D_SUBCASE( case6b, array_fs_hb, kernel_size, stride, padding, dilation, ceil_mode );
    MAX_POOL1D_SUBCASE( case6b, array_hs_hb, kernel_size, stride, padding, dilation, ceil_mode );
    MAX_POOL1D_SUBCASE( case6b, array_ds_hb, kernel_size, stride, padding, dilation, ceil_mode );
    MAX_POOL1D_SUBCASE( case6b, array_ls_hb, kernel_size, stride, padding, dilation, ceil_mode );

    MAX_POOL1D_SUBCASE( case6b, array_cs_db, kernel_size, stride, padding, dilation, ceil_mode );
    MAX_POOL1D_SUBCASE( case6b, array_fs_db, kernel_size, stride, padding, dilation, ceil_mode );
    MAX_POOL1D_SUBCASE( case6b, array_hs_db, kernel_size, stride, padding, dilation, ceil_mode );
    MAX_POOL1D_SUBCASE( case6b, array_ds_db, kernel_size, stride, padding, dilation, ceil_mode );
    MAX_POOL1D_SUBCASE( case6b, array_ls_db, kernel_size, stride, padding, dilation, ceil_mode );
    #endif
}

// resulting shape different from pytorch
// TODO: fix or revisit
TEST_CASE("max_pool1d(case7)" * doctest::test_suite("view::max_pool1d") * doctest::skip())
{
    #if !defined(NMTOOLS_TESTING_GENERIC_NDARRAY)
    MAX_POOL1D_SUBCASE( case7, array, kernel_size, stride, padding, dilation, ceil_mode );
    MAX_POOL1D_SUBCASE( case7, array_a, kernel_size, stride, padding, dilation, ceil_mode );
    MAX_POOL1D_SUBCASE( case7, array_f, kernel_size, stride, padding, dilation, ceil_mode );
    MAX_POOL1D_SUBCASE( case7, array_h, kernel_size, stride, padding, dilation, ceil_mode );
    MAX_POOL1D_SUBCASE( case7, array_d, kernel_size, stride, padding, dilation, ceil_mode );
    #else
    MAX_POOL1D_SUBCASE( case7, array_cs_fb, kernel_size, stride, padding, dilation, ceil_mode );
    MAX_POOL1D_SUBCASE( case7, array_fs_fb, kernel_size, stride, padding, dilation, ceil_mode );
    MAX_POOL1D_SUBCASE( case7, array_hs_fb, kernel_size, stride, padding, dilation, ceil_mode );
    MAX_POOL1D_SUBCASE( case7, array_ds_fb, kernel_size, stride, padding, dilation, ceil_mode );
    MAX_POOL1D_SUBCASE( case7, array_ls_fb, kernel_size, stride, padding, dilation, ceil_mode );

    MAX_POOL1D_SUBCASE( case7, array_cs_hb, kernel_size, stride, padding, dilation, ceil_mode );
    MAX_POOL1D_SUBCASE( case7, array_fs_hb, kernel_size, stride, padding, dilation, ceil_mode );
    MAX_POOL1D_SUBCASE( case7, array_hs_hb, kernel_size, stride, padding, dilation, ceil_mode );
    MAX_POOL1D_SUBCASE( case7, array_ds_hb, kernel_size, stride, padding, dilation, ceil_mode );
    MAX_POOL1D_SUBCASE( case7, array_ls_hb, kernel_size, stride, padding, dilation, ceil_mode );

    MAX_POOL1D_SUBCASE( case7, array_cs_db, kernel_size, stride, padding, dilation, ceil_mode );
    MAX_POOL1D_SUBCASE( case7, array_fs_db, kernel_size, stride, padding, dilation, ceil_mode );
    MAX_POOL1D_SUBCASE( case7, array_hs_db, kernel_size, stride, padding, dilation, ceil_mode );
    MAX_POOL1D_SUBCASE( case7, array_ds_db, kernel_size, stride, padding, dilation, ceil_mode );
    MAX_POOL1D_SUBCASE( case7, array_ls_db, kernel_size, stride, padding, dilation, ceil_mode );
    #endif
}

TEST_CASE("max_pool1d(case8)" * doctest::test_suite("view::max_pool1d"))
{
    #if !defined(NMTOOLS_TESTING_GENERIC_NDARRAY)
    MAX_POOL1D_SUBCASE( case8, array, kernel_size, stride, padding, dilation, ceil_mode );
    MAX_POOL1D_SUBCASE( case8, array_a, kernel_size, stride, padding, dilation, ceil_mode );
    MAX_POOL1D_SUBCASE( case8, array_f, kernel_size, stride, padding, dilation, ceil_mode );
    MAX_POOL1D_SUBCASE( case8, array_h, kernel_size, stride, padding, dilation, ceil_mode );
    MAX_POOL1D_SUBCASE( case8, array_d, kernel_size, stride, padding, dilation, ceil_mode );
    #else
    MAX_POOL1D_SUBCASE( case8, array_cs_fb, kernel_size, stride, padding, dilation, ceil_mode );
    MAX_POOL1D_SUBCASE( case8, array_fs_fb, kernel_size, stride, padding, dilation, ceil_mode );
    MAX_POOL1D_SUBCASE( case8, array_hs_fb, kernel_size, stride, padding, dilation, ceil_mode );
    MAX_POOL1D_SUBCASE( case8, array_ds_fb, kernel_size, stride, padding, dilation, ceil_mode );
    MAX_POOL1D_SUBCASE( case8, array_ls_fb, kernel_size, stride, padding, dilation, ceil_mode );

    MAX_POOL1D_SUBCASE( case8, array_cs_hb, kernel_size, stride, padding, dilation, ceil_mode );
    MAX_POOL1D_SUBCASE( case8, array_fs_hb, kernel_size, stride, padding, dilation, ceil_mode );
    MAX_POOL1D_SUBCASE( case8, array_hs_hb, kernel_size, stride, padding, dilation, ceil_mode );
    MAX_POOL1D_SUBCASE( case8, array_ds_hb, kernel_size, stride, padding, dilation, ceil_mode );
    MAX_POOL1D_SUBCASE( case8, array_ls_hb, kernel_size, stride, padding, dilation, ceil_mode );

    MAX_POOL1D_SUBCASE( case8, array_cs_db, kernel_size, stride, padding, dilation, ceil_mode );
    MAX_POOL1D_SUBCASE( case8, array_fs_db, kernel_size, stride, padding, dilation, ceil_mode );
    MAX_POOL1D_SUBCASE( case8, array_hs_db, kernel_size, stride, padding, dilation, ceil_mode );
    MAX_POOL1D_SUBCASE( case8, array_ds_db, kernel_size, stride, padding, dilation, ceil_mode );
    MAX_POOL1D_SUBCASE( case8, array_ls_db, kernel_size, stride, padding, dilation, ceil_mode );
    #endif
}

TEST_CASE("max_pool1d(case9)" * doctest::test_suite("view::max_pool1d"))
{
    #if !defined(NMTOOLS_TESTING_GENERIC_NDARRAY)
    MAX_POOL1D_SUBCASE( case9, array, kernel_size, stride, padding, dilation, ceil_mode );
    MAX_POOL1D_SUBCASE( case9, array_a, kernel_size, stride, padding, dilation, ceil_mode );
    MAX_POOL1D_SUBCASE( case9, array_f, kernel_size, stride, padding, dilation, ceil_mode );
    MAX_POOL1D_SUBCASE( case9, array_h, kernel_size, stride, padding, dilation, ceil_mode );
    MAX_POOL1D_SUBCASE( case9, array_d, kernel_size, stride, padding, dilation, ceil_mode );
    #else
    MAX_POOL1D_SUBCASE( case9, array_cs_fb, kernel_size, stride, padding, dilation, ceil_mode );
    MAX_POOL1D_SUBCASE( case9, array_fs_fb, kernel_size, stride, padding, dilation, ceil_mode );
    MAX_POOL1D_SUBCASE( case9, array_hs_fb, kernel_size, stride, padding, dilation, ceil_mode );
    MAX_POOL1D_SUBCASE( case9, array_ds_fb, kernel_size, stride, padding, dilation, ceil_mode );
    MAX_POOL1D_SUBCASE( case9, array_ls_fb, kernel_size, stride, padding, dilation, ceil_mode );

    MAX_POOL1D_SUBCASE( case9, array_cs_hb, kernel_size, stride, padding, dilation, ceil_mode );
    MAX_POOL1D_SUBCASE( case9, array_fs_hb, kernel_size, stride, padding, dilation, ceil_mode );
    MAX_POOL1D_SUBCASE( case9, array_hs_hb, kernel_size, stride, padding, dilation, ceil_mode );
    MAX_POOL1D_SUBCASE( case9, array_ds_hb, kernel_size, stride, padding, dilation, ceil_mode );
    MAX_POOL1D_SUBCASE( case9, array_ls_hb, kernel_size, stride, padding, dilation, ceil_mode );

    MAX_POOL1D_SUBCASE( case9, array_cs_db, kernel_size, stride, padding, dilation, ceil_mode );
    MAX_POOL1D_SUBCASE( case9, array_fs_db, kernel_size, stride, padding, dilation, ceil_mode );
    MAX_POOL1D_SUBCASE( case9, array_hs_db, kernel_size, stride, padding, dilation, ceil_mode );
    MAX_POOL1D_SUBCASE( case9, array_ds_db, kernel_size, stride, padding, dilation, ceil_mode );
    MAX_POOL1D_SUBCASE( case9, array_ls_db, kernel_size, stride, padding, dilation, ceil_mode );
    #endif
}

TEST_CASE("max_pool1d(case10)" * doctest::test_suite("view::max_pool1d"))
{
    #if !defined(NMTOOLS_TESTING_GENERIC_NDARRAY)
    MAX_POOL1D_SUBCASE( case10, array, kernel_size, stride, padding, dilation, ceil_mode );
    MAX_POOL1D_SUBCASE( case10, array_a, kernel_size, stride, padding, dilation, ceil_mode );
    MAX_POOL1D_SUBCASE( case10, array_f, kernel_size, stride, padding, dilation, ceil_mode );
    MAX_POOL1D_SUBCASE( case10, array_h, kernel_size, stride, padding, dilation, ceil_mode );
    MAX_POOL1D_SUBCASE( case10, array_d, kernel_size, stride, padding, dilation, ceil_mode );
    #else
    MAX_POOL1D_SUBCASE( case10, array_cs_fb, kernel_size, stride, padding, dilation, ceil_mode );
    MAX_POOL1D_SUBCASE( case10, array_fs_fb, kernel_size, stride, padding, dilation, ceil_mode );
    MAX_POOL1D_SUBCASE( case10, array_hs_fb, kernel_size, stride, padding, dilation, ceil_mode );
    MAX_POOL1D_SUBCASE( case10, array_ds_fb, kernel_size, stride, padding, dilation, ceil_mode );
    MAX_POOL1D_SUBCASE( case10, array_ls_fb, kernel_size, stride, padding, dilation, ceil_mode );

    MAX_POOL1D_SUBCASE( case10, array_cs_hb, kernel_size, stride, padding, dilation, ceil_mode );
    MAX_POOL1D_SUBCASE( case10, array_fs_hb, kernel_size, stride, padding, dilation, ceil_mode );
    MAX_POOL1D_SUBCASE( case10, array_hs_hb, kernel_size, stride, padding, dilation, ceil_mode );
    MAX_POOL1D_SUBCASE( case10, array_ds_hb, kernel_size, stride, padding, dilation, ceil_mode );
    MAX_POOL1D_SUBCASE( case10, array_ls_hb, kernel_size, stride, padding, dilation, ceil_mode );

    MAX_POOL1D_SUBCASE( case10, array_cs_db, kernel_size, stride, padding, dilation, ceil_mode );
    MAX_POOL1D_SUBCASE( case10, array_fs_db, kernel_size, stride, padding, dilation, ceil_mode );
    MAX_POOL1D_SUBCASE( case10, array_hs_db, kernel_size, stride, padding, dilation, ceil_mode );
    MAX_POOL1D_SUBCASE( case10, array_ds_db, kernel_size, stride, padding, dilation, ceil_mode );
    MAX_POOL1D_SUBCASE( case10, array_ls_db, kernel_size, stride, padding, dilation, ceil_mode );
    #endif
}

// resulting shape different from pytorch
// TODO: fix or revisit
TEST_CASE("max_pool1d(case11)" * doctest::test_suite("view::max_pool1d") * doctest::skip())
{
    #if !defined(NMTOOLS_TESTING_GENERIC_NDARRAY)
    MAX_POOL1D_SUBCASE( case11, array, kernel_size, stride, padding, dilation, ceil_mode );
    MAX_POOL1D_SUBCASE( case11, array_a, kernel_size, stride, padding, dilation, ceil_mode );
    MAX_POOL1D_SUBCASE( case11, array_f, kernel_size, stride, padding, dilation, ceil_mode );
    MAX_POOL1D_SUBCASE( case11, array_h, kernel_size, stride, padding, dilation, ceil_mode );
    MAX_POOL1D_SUBCASE( case11, array_d, kernel_size, stride, padding, dilation, ceil_mode );
    #else
    MAX_POOL1D_SUBCASE( case11, array_cs_fb, kernel_size, stride, padding, dilation, ceil_mode );
    MAX_POOL1D_SUBCASE( case11, array_fs_fb, kernel_size, stride, padding, dilation, ceil_mode );
    MAX_POOL1D_SUBCASE( case11, array_hs_fb, kernel_size, stride, padding, dilation, ceil_mode );
    MAX_POOL1D_SUBCASE( case11, array_ds_fb, kernel_size, stride, padding, dilation, ceil_mode );
    MAX_POOL1D_SUBCASE( case11, array_ls_fb, kernel_size, stride, padding, dilation, ceil_mode );

    MAX_POOL1D_SUBCASE( case11, array_cs_hb, kernel_size, stride, padding, dilation, ceil_mode );
    MAX_POOL1D_SUBCASE( case11, array_fs_hb, kernel_size, stride, padding, dilation, ceil_mode );
    MAX_POOL1D_SUBCASE( case11, array_hs_hb, kernel_size, stride, padding, dilation, ceil_mode );
    MAX_POOL1D_SUBCASE( case11, array_ds_hb, kernel_size, stride, padding, dilation, ceil_mode );
    MAX_POOL1D_SUBCASE( case11, array_ls_hb, kernel_size, stride, padding, dilation, ceil_mode );

    MAX_POOL1D_SUBCASE( case11, array_cs_db, kernel_size, stride, padding, dilation, ceil_mode );
    MAX_POOL1D_SUBCASE( case11, array_fs_db, kernel_size, stride, padding, dilation, ceil_mode );
    MAX_POOL1D_SUBCASE( case11, array_hs_db, kernel_size, stride, padding, dilation, ceil_mode );
    MAX_POOL1D_SUBCASE( case11, array_ds_db, kernel_size, stride, padding, dilation, ceil_mode );
    MAX_POOL1D_SUBCASE( case11, array_ls_db, kernel_size, stride, padding, dilation, ceil_mode );
    #endif
}

TEST_CASE("max_pool1d(case12)" * doctest::test_suite("view::max_pool1d"))
{
    #if !defined(NMTOOLS_TESTING_GENERIC_NDARRAY)
    MAX_POOL1D_SUBCASE( case12, array, kernel_size, stride, padding, dilation, ceil_mode );
    MAX_POOL1D_SUBCASE( case12, array_a, kernel_size, stride, padding, dilation, ceil_mode );
    MAX_POOL1D_SUBCASE( case12, array_f, kernel_size, stride, padding, dilation, ceil_mode );
    MAX_POOL1D_SUBCASE( case12, array_h, kernel_size, stride, padding, dilation, ceil_mode );
    MAX_POOL1D_SUBCASE( case12, array_d, kernel_size, stride, padding, dilation, ceil_mode );
    #else
    MAX_POOL1D_SUBCASE( case12, array_cs_fb, kernel_size, stride, padding, dilation, ceil_mode );
    MAX_POOL1D_SUBCASE( case12, array_fs_fb, kernel_size, stride, padding, dilation, ceil_mode );
    MAX_POOL1D_SUBCASE( case12, array_hs_fb, kernel_size, stride, padding, dilation, ceil_mode );
    MAX_POOL1D_SUBCASE( case12, array_ds_fb, kernel_size, stride, padding, dilation, ceil_mode );
    MAX_POOL1D_SUBCASE( case12, array_ls_fb, kernel_size, stride, padding, dilation, ceil_mode );

    MAX_POOL1D_SUBCASE( case12, array_cs_hb, kernel_size, stride, padding, dilation, ceil_mode );
    MAX_POOL1D_SUBCASE( case12, array_fs_hb, kernel_size, stride, padding, dilation, ceil_mode );
    MAX_POOL1D_SUBCASE( case12, array_hs_hb, kernel_size, stride, padding, dilation, ceil_mode );
    MAX_POOL1D_SUBCASE( case12, array_ds_hb, kernel_size, stride, padding, dilation, ceil_mode );
    MAX_POOL1D_SUBCASE( case12, array_ls_hb, kernel_size, stride, padding, dilation, ceil_mode );

    MAX_POOL1D_SUBCASE( case12, array_cs_db, kernel_size, stride, padding, dilation, ceil_mode );
    MAX_POOL1D_SUBCASE( case12, array_fs_db, kernel_size, stride, padding, dilation, ceil_mode );
    MAX_POOL1D_SUBCASE( case12, array_hs_db, kernel_size, stride, padding, dilation, ceil_mode );
    MAX_POOL1D_SUBCASE( case12, array_ds_db, kernel_size, stride, padding, dilation, ceil_mode );
    MAX_POOL1D_SUBCASE( case12, array_ls_db, kernel_size, stride, padding, dilation, ceil_mode );
    #endif
}

TEST_CASE("max_pool1d(case13)" * doctest::test_suite("view::max_pool1d"))
{
    #if !defined(NMTOOLS_TESTING_GENERIC_NDARRAY)
    MAX_POOL1D_SUBCASE( case13, array, kernel_size, stride, padding, dilation, ceil_mode );
    MAX_POOL1D_SUBCASE( case13, array_a, kernel_size, stride, padding, dilation, ceil_mode );
    MAX_POOL1D_SUBCASE( case13, array_f, kernel_size, stride, padding, dilation, ceil_mode );
    MAX_POOL1D_SUBCASE( case13, array_h, kernel_size, stride, padding, dilation, ceil_mode );
    MAX_POOL1D_SUBCASE( case13, array_d, kernel_size, stride, padding, dilation, ceil_mode );
    #else
    MAX_POOL1D_SUBCASE( case13, array_cs_fb, kernel_size, stride, padding, dilation, ceil_mode );
    MAX_POOL1D_SUBCASE( case13, array_fs_fb, kernel_size, stride, padding, dilation, ceil_mode );
    MAX_POOL1D_SUBCASE( case13, array_hs_fb, kernel_size, stride, padding, dilation, ceil_mode );
    MAX_POOL1D_SUBCASE( case13, array_ds_fb, kernel_size, stride, padding, dilation, ceil_mode );
    MAX_POOL1D_SUBCASE( case13, array_ls_fb, kernel_size, stride, padding, dilation, ceil_mode );

    MAX_POOL1D_SUBCASE( case13, array_cs_hb, kernel_size, stride, padding, dilation, ceil_mode );
    MAX_POOL1D_SUBCASE( case13, array_fs_hb, kernel_size, stride, padding, dilation, ceil_mode );
    MAX_POOL1D_SUBCASE( case13, array_hs_hb, kernel_size, stride, padding, dilation, ceil_mode );
    MAX_POOL1D_SUBCASE( case13, array_ds_hb, kernel_size, stride, padding, dilation, ceil_mode );
    MAX_POOL1D_SUBCASE( case13, array_ls_hb, kernel_size, stride, padding, dilation, ceil_mode );

    MAX_POOL1D_SUBCASE( case13, array_cs_db, kernel_size, stride, padding, dilation, ceil_mode );
    MAX_POOL1D_SUBCASE( case13, array_fs_db, kernel_size, stride, padding, dilation, ceil_mode );
    MAX_POOL1D_SUBCASE( case13, array_hs_db, kernel_size, stride, padding, dilation, ceil_mode );
    MAX_POOL1D_SUBCASE( case13, array_ds_db, kernel_size, stride, padding, dilation, ceil_mode );
    MAX_POOL1D_SUBCASE( case13, array_ls_db, kernel_size, stride, padding, dilation, ceil_mode );
    #endif
}

TEST_CASE("max_pool1d(case14)" * doctest::test_suite("view::max_pool1d"))
{
    #if !defined(NMTOOLS_TESTING_GENERIC_NDARRAY)
    MAX_POOL1D_SUBCASE( case14, array, kernel_size, stride, padding, dilation, ceil_mode );
    MAX_POOL1D_SUBCASE( case14, array_a, kernel_size, stride, padding, dilation, ceil_mode );
    MAX_POOL1D_SUBCASE( case14, array_f, kernel_size, stride, padding, dilation, ceil_mode );
    MAX_POOL1D_SUBCASE( case14, array_h, kernel_size, stride, padding, dilation, ceil_mode );
    MAX_POOL1D_SUBCASE( case14, array_d, kernel_size, stride, padding, dilation, ceil_mode );
    #else
    MAX_POOL1D_SUBCASE( case14, array_cs_fb, kernel_size, stride, padding, dilation, ceil_mode );
    MAX_POOL1D_SUBCASE( case14, array_fs_fb, kernel_size, stride, padding, dilation, ceil_mode );
    MAX_POOL1D_SUBCASE( case14, array_hs_fb, kernel_size, stride, padding, dilation, ceil_mode );
    MAX_POOL1D_SUBCASE( case14, array_ds_fb, kernel_size, stride, padding, dilation, ceil_mode );
    MAX_POOL1D_SUBCASE( case14, array_ls_fb, kernel_size, stride, padding, dilation, ceil_mode );

    MAX_POOL1D_SUBCASE( case14, array_cs_hb, kernel_size, stride, padding, dilation, ceil_mode );
    MAX_POOL1D_SUBCASE( case14, array_fs_hb, kernel_size, stride, padding, dilation, ceil_mode );
    MAX_POOL1D_SUBCASE( case14, array_hs_hb, kernel_size, stride, padding, dilation, ceil_mode );
    MAX_POOL1D_SUBCASE( case14, array_ds_hb, kernel_size, stride, padding, dilation, ceil_mode );
    MAX_POOL1D_SUBCASE( case14, array_ls_hb, kernel_size, stride, padding, dilation, ceil_mode );

    MAX_POOL1D_SUBCASE( case14, array_cs_db, kernel_size, stride, padding, dilation, ceil_mode );
    MAX_POOL1D_SUBCASE( case14, array_fs_db, kernel_size, stride, padding, dilation, ceil_mode );
    MAX_POOL1D_SUBCASE( case14, array_hs_db, kernel_size, stride, padding, dilation, ceil_mode );
    MAX_POOL1D_SUBCASE( case14, array_ds_db, kernel_size, stride, padding, dilation, ceil_mode );
    MAX_POOL1D_SUBCASE( case14, array_ls_db, kernel_size, stride, padding, dilation, ceil_mode );
    #endif
}