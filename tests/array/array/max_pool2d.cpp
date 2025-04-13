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

#include "nmtools/testing/data/array/pooling.hpp"
#include "nmtools/array/pooling.hpp"
#include "nmtools/testing/doctest.hpp"

namespace nm = nmtools;
namespace na = nm::array;

#define MAX_POOL2D_SUBCASE(case_name, ...) \
SUBCASE(#case_name) \
{ \
    NMTOOLS_TESTING_USE_CASE(array, max_pool2d, case_name); \
    using namespace args; \
    auto result = na::max_pool2d(__VA_ARGS__); \
    NMTOOLS_ASSERT_CLOSE( nm::shape(result), nm::shape(expect::result) ); \
    NMTOOLS_ASSERT_CLOSE( result, expect::result ); \
}

TEST_CASE("max_pool2d(case1)" * doctest::test_suite("array::max_pool2d"))
{
    #if !defined(NMTOOLS_TESTING_GENERIC_NDARRAY)
    MAX_POOL2D_SUBCASE( case1, array, kernel_size, stride, padding, dilation, ceil_mode );
    MAX_POOL2D_SUBCASE( case1, array_a, kernel_size_a, stride_a, padding, dilation, ceil_mode );
    MAX_POOL2D_SUBCASE( case1, array_f, kernel_size_f, stride_f, padding, dilation, ceil_mode );
    MAX_POOL2D_SUBCASE( case1, array_h, kernel_size_h, stride_h, padding, dilation, ceil_mode );

    #else
    MAX_POOL2D_SUBCASE( case1, array_cs_fb, kernel_size, stride, padding, dilation, ceil_mode );
    MAX_POOL2D_SUBCASE( case1, array_cs_hb, kernel_size, stride, padding, dilation, ceil_mode );
    MAX_POOL2D_SUBCASE( case1, array_cs_db, kernel_size, stride, padding, dilation, ceil_mode );

    MAX_POOL2D_SUBCASE( case1, array_fs_fb, kernel_size, stride, padding, dilation, ceil_mode );
    MAX_POOL2D_SUBCASE( case1, array_fs_hb, kernel_size, stride, padding, dilation, ceil_mode );
    MAX_POOL2D_SUBCASE( case1, array_fs_db, kernel_size, stride, padding, dilation, ceil_mode );

    MAX_POOL2D_SUBCASE( case1, array_hs_fb, kernel_size, stride, padding, dilation, ceil_mode );
    MAX_POOL2D_SUBCASE( case1, array_hs_hb, kernel_size, stride, padding, dilation, ceil_mode );
    MAX_POOL2D_SUBCASE( case1, array_hs_db, kernel_size, stride, padding, dilation, ceil_mode );

    MAX_POOL2D_SUBCASE( case1, array_ds_fb, kernel_size, stride, padding, dilation, ceil_mode );
    MAX_POOL2D_SUBCASE( case1, array_ds_hb, kernel_size, stride, padding, dilation, ceil_mode );
    MAX_POOL2D_SUBCASE( case1, array_ds_db, kernel_size, stride, padding, dilation, ceil_mode );

    MAX_POOL2D_SUBCASE( case1, array_ls_fb, kernel_size, stride, padding, dilation, ceil_mode );
    MAX_POOL2D_SUBCASE( case1, array_ls_hb, kernel_size, stride, padding, dilation, ceil_mode );
    MAX_POOL2D_SUBCASE( case1, array_ls_db, kernel_size, stride, padding, dilation, ceil_mode );
    #endif
}

TEST_CASE("max_pool2d(case1b)" * doctest::test_suite("array::max_pool2d"))
{
    #if !defined(NMTOOLS_TESTING_GENERIC_NDARRAY)
    MAX_POOL2D_SUBCASE( case1b, array, kernel_size, stride, padding, dilation, ceil_mode );
    MAX_POOL2D_SUBCASE( case1b, array_a, kernel_size_a, stride_a, padding, dilation, ceil_mode );
    MAX_POOL2D_SUBCASE( case1b, array_f, kernel_size_f, stride_f, padding, dilation, ceil_mode );
    MAX_POOL2D_SUBCASE( case1b, array_h, kernel_size_h, stride_h, padding, dilation, ceil_mode );

    #else
    MAX_POOL2D_SUBCASE( case1b, array_cs_fb, kernel_size, stride, padding, dilation, ceil_mode );
    MAX_POOL2D_SUBCASE( case1b, array_cs_hb, kernel_size, stride, padding, dilation, ceil_mode );
    MAX_POOL2D_SUBCASE( case1b, array_cs_db, kernel_size, stride, padding, dilation, ceil_mode );

    MAX_POOL2D_SUBCASE( case1b, array_fs_fb, kernel_size, stride, padding, dilation, ceil_mode );
    MAX_POOL2D_SUBCASE( case1b, array_fs_hb, kernel_size, stride, padding, dilation, ceil_mode );
    MAX_POOL2D_SUBCASE( case1b, array_fs_db, kernel_size, stride, padding, dilation, ceil_mode );

    MAX_POOL2D_SUBCASE( case1b, array_hs_fb, kernel_size, stride, padding, dilation, ceil_mode );
    MAX_POOL2D_SUBCASE( case1b, array_hs_hb, kernel_size, stride, padding, dilation, ceil_mode );
    MAX_POOL2D_SUBCASE( case1b, array_hs_db, kernel_size, stride, padding, dilation, ceil_mode );

    MAX_POOL2D_SUBCASE( case1b, array_ds_fb, kernel_size, stride, padding, dilation, ceil_mode );
    MAX_POOL2D_SUBCASE( case1b, array_ds_hb, kernel_size, stride, padding, dilation, ceil_mode );
    MAX_POOL2D_SUBCASE( case1b, array_ds_db, kernel_size, stride, padding, dilation, ceil_mode );

    MAX_POOL2D_SUBCASE( case1b, array_ls_fb, kernel_size, stride, padding, dilation, ceil_mode );
    MAX_POOL2D_SUBCASE( case1b, array_ls_hb, kernel_size, stride, padding, dilation, ceil_mode );
    MAX_POOL2D_SUBCASE( case1b, array_ls_db, kernel_size, stride, padding, dilation, ceil_mode );
    #endif
}

TEST_CASE("max_pool2d(case1c)" * doctest::test_suite("array::max_pool2d"))
{
    #if !defined(NMTOOLS_TESTING_GENERIC_NDARRAY)
    MAX_POOL2D_SUBCASE( case1c, array, kernel_size, stride, padding, dilation, ceil_mode );
    MAX_POOL2D_SUBCASE( case1c, array_a, kernel_size_a, stride_a, padding, dilation, ceil_mode );
    MAX_POOL2D_SUBCASE( case1c, array_f, kernel_size_f, stride_f, padding, dilation, ceil_mode );
    MAX_POOL2D_SUBCASE( case1c, array_h, kernel_size_h, stride_h, padding, dilation, ceil_mode );

    #else
    MAX_POOL2D_SUBCASE( case1c, array_cs_fb, kernel_size, stride, padding, dilation, ceil_mode );
    MAX_POOL2D_SUBCASE( case1c, array_cs_hb, kernel_size, stride, padding, dilation, ceil_mode );
    MAX_POOL2D_SUBCASE( case1c, array_cs_db, kernel_size, stride, padding, dilation, ceil_mode );

    MAX_POOL2D_SUBCASE( case1c, array_fs_fb, kernel_size, stride, padding, dilation, ceil_mode );
    MAX_POOL2D_SUBCASE( case1c, array_fs_hb, kernel_size, stride, padding, dilation, ceil_mode );
    MAX_POOL2D_SUBCASE( case1c, array_fs_db, kernel_size, stride, padding, dilation, ceil_mode );

    MAX_POOL2D_SUBCASE( case1c, array_hs_fb, kernel_size, stride, padding, dilation, ceil_mode );
    MAX_POOL2D_SUBCASE( case1c, array_hs_hb, kernel_size, stride, padding, dilation, ceil_mode );
    MAX_POOL2D_SUBCASE( case1c, array_hs_db, kernel_size, stride, padding, dilation, ceil_mode );

    MAX_POOL2D_SUBCASE( case1c, array_ds_fb, kernel_size, stride, padding, dilation, ceil_mode );
    MAX_POOL2D_SUBCASE( case1c, array_ds_hb, kernel_size, stride, padding, dilation, ceil_mode );
    MAX_POOL2D_SUBCASE( case1c, array_ds_db, kernel_size, stride, padding, dilation, ceil_mode );

    MAX_POOL2D_SUBCASE( case1c, array_ls_fb, kernel_size, stride, padding, dilation, ceil_mode );
    MAX_POOL2D_SUBCASE( case1c, array_ls_hb, kernel_size, stride, padding, dilation, ceil_mode );
    MAX_POOL2D_SUBCASE( case1c, array_ls_db, kernel_size, stride, padding, dilation, ceil_mode );
    #endif
}

TEST_CASE("max_pool2d(case2)" * doctest::test_suite("array::max_pool2d"))
{
    #if !defined(NMTOOLS_TESTING_GENERIC_NDARRAY)
    MAX_POOL2D_SUBCASE( case2, array, kernel_size, stride, padding, dilation, ceil_mode );
    MAX_POOL2D_SUBCASE( case2, array_a, kernel_size_a, stride_a, padding, dilation, ceil_mode );
    MAX_POOL2D_SUBCASE( case2, array_f, kernel_size_f, stride_f, padding, dilation, ceil_mode );
    MAX_POOL2D_SUBCASE( case2, array_h, kernel_size_h, stride_h, padding, dilation, ceil_mode );

    #else
    MAX_POOL2D_SUBCASE( case2, array_cs_fb, kernel_size, stride, padding, dilation, ceil_mode );
    MAX_POOL2D_SUBCASE( case2, array_cs_hb, kernel_size, stride, padding, dilation, ceil_mode );
    MAX_POOL2D_SUBCASE( case2, array_cs_db, kernel_size, stride, padding, dilation, ceil_mode );

    MAX_POOL2D_SUBCASE( case2, array_fs_fb, kernel_size, stride, padding, dilation, ceil_mode );
    MAX_POOL2D_SUBCASE( case2, array_fs_hb, kernel_size, stride, padding, dilation, ceil_mode );
    MAX_POOL2D_SUBCASE( case2, array_fs_db, kernel_size, stride, padding, dilation, ceil_mode );

    MAX_POOL2D_SUBCASE( case2, array_hs_fb, kernel_size, stride, padding, dilation, ceil_mode );
    MAX_POOL2D_SUBCASE( case2, array_hs_hb, kernel_size, stride, padding, dilation, ceil_mode );
    MAX_POOL2D_SUBCASE( case2, array_hs_db, kernel_size, stride, padding, dilation, ceil_mode );

    MAX_POOL2D_SUBCASE( case2, array_ds_fb, kernel_size, stride, padding, dilation, ceil_mode );
    MAX_POOL2D_SUBCASE( case2, array_ds_hb, kernel_size, stride, padding, dilation, ceil_mode );
    MAX_POOL2D_SUBCASE( case2, array_ds_db, kernel_size, stride, padding, dilation, ceil_mode );

    MAX_POOL2D_SUBCASE( case2, array_ls_fb, kernel_size, stride, padding, dilation, ceil_mode );
    MAX_POOL2D_SUBCASE( case2, array_ls_hb, kernel_size, stride, padding, dilation, ceil_mode );
    MAX_POOL2D_SUBCASE( case2, array_ls_db, kernel_size, stride, padding, dilation, ceil_mode );
    #endif
}

TEST_CASE("max_pool2d(case3)" * doctest::test_suite("array::max_pool2d"))
{
    #if !defined(NMTOOLS_TESTING_GENERIC_NDARRAY)
    MAX_POOL2D_SUBCASE( case3, array, kernel_size, stride, padding, dilation, ceil_mode );
    MAX_POOL2D_SUBCASE( case3, array_a, kernel_size_a, stride_a, padding, dilation, ceil_mode );
    MAX_POOL2D_SUBCASE( case3, array_f, kernel_size_f, stride_f, padding, dilation, ceil_mode );
    MAX_POOL2D_SUBCASE( case3, array_h, kernel_size_h, stride_h, padding, dilation, ceil_mode );

    #else
    MAX_POOL2D_SUBCASE( case3, array_cs_fb, kernel_size, stride, padding, dilation, ceil_mode );
    MAX_POOL2D_SUBCASE( case3, array_cs_hb, kernel_size, stride, padding, dilation, ceil_mode );
    MAX_POOL2D_SUBCASE( case3, array_cs_db, kernel_size, stride, padding, dilation, ceil_mode );

    MAX_POOL2D_SUBCASE( case3, array_fs_fb, kernel_size, stride, padding, dilation, ceil_mode );
    MAX_POOL2D_SUBCASE( case3, array_fs_hb, kernel_size, stride, padding, dilation, ceil_mode );
    MAX_POOL2D_SUBCASE( case3, array_fs_db, kernel_size, stride, padding, dilation, ceil_mode );

    MAX_POOL2D_SUBCASE( case3, array_hs_fb, kernel_size, stride, padding, dilation, ceil_mode );
    MAX_POOL2D_SUBCASE( case3, array_hs_hb, kernel_size, stride, padding, dilation, ceil_mode );
    MAX_POOL2D_SUBCASE( case3, array_hs_db, kernel_size, stride, padding, dilation, ceil_mode );

    MAX_POOL2D_SUBCASE( case3, array_ds_fb, kernel_size, stride, padding, dilation, ceil_mode );
    MAX_POOL2D_SUBCASE( case3, array_ds_hb, kernel_size, stride, padding, dilation, ceil_mode );
    MAX_POOL2D_SUBCASE( case3, array_ds_db, kernel_size, stride, padding, dilation, ceil_mode );

    MAX_POOL2D_SUBCASE( case3, array_ls_fb, kernel_size, stride, padding, dilation, ceil_mode );
    MAX_POOL2D_SUBCASE( case3, array_ls_hb, kernel_size, stride, padding, dilation, ceil_mode );
    MAX_POOL2D_SUBCASE( case3, array_ls_db, kernel_size, stride, padding, dilation, ceil_mode );
    #endif
}

TEST_CASE("max_pool2d(case4)" * doctest::test_suite("array::max_pool2d"))
{
    #if !defined(NMTOOLS_TESTING_GENERIC_NDARRAY)
    MAX_POOL2D_SUBCASE( case4, array, kernel_size, stride, padding, dilation, ceil_mode );
    MAX_POOL2D_SUBCASE( case4, array_a, kernel_size_a, stride_a, padding, dilation, ceil_mode );
    MAX_POOL2D_SUBCASE( case4, array_f, kernel_size_f, stride_f, padding, dilation, ceil_mode );
    MAX_POOL2D_SUBCASE( case4, array_h, kernel_size_h, stride_h, padding, dilation, ceil_mode );

    #else
    MAX_POOL2D_SUBCASE( case4, array_cs_fb, kernel_size, stride, padding, dilation, ceil_mode );
    MAX_POOL2D_SUBCASE( case4, array_cs_hb, kernel_size, stride, padding, dilation, ceil_mode );
    MAX_POOL2D_SUBCASE( case4, array_cs_db, kernel_size, stride, padding, dilation, ceil_mode );

    MAX_POOL2D_SUBCASE( case4, array_fs_fb, kernel_size, stride, padding, dilation, ceil_mode );
    MAX_POOL2D_SUBCASE( case4, array_fs_hb, kernel_size, stride, padding, dilation, ceil_mode );
    MAX_POOL2D_SUBCASE( case4, array_fs_db, kernel_size, stride, padding, dilation, ceil_mode );

    MAX_POOL2D_SUBCASE( case4, array_hs_fb, kernel_size, stride, padding, dilation, ceil_mode );
    MAX_POOL2D_SUBCASE( case4, array_hs_hb, kernel_size, stride, padding, dilation, ceil_mode );
    MAX_POOL2D_SUBCASE( case4, array_hs_db, kernel_size, stride, padding, dilation, ceil_mode );

    MAX_POOL2D_SUBCASE( case4, array_ds_fb, kernel_size, stride, padding, dilation, ceil_mode );
    MAX_POOL2D_SUBCASE( case4, array_ds_hb, kernel_size, stride, padding, dilation, ceil_mode );
    MAX_POOL2D_SUBCASE( case4, array_ds_db, kernel_size, stride, padding, dilation, ceil_mode );

    MAX_POOL2D_SUBCASE( case4, array_ls_fb, kernel_size, stride, padding, dilation, ceil_mode );
    MAX_POOL2D_SUBCASE( case4, array_ls_hb, kernel_size, stride, padding, dilation, ceil_mode );
    MAX_POOL2D_SUBCASE( case4, array_ls_db, kernel_size, stride, padding, dilation, ceil_mode );
    #endif
}

TEST_CASE("max_pool2d(case5)" * doctest::test_suite("array::max_pool2d"))
{
    #if !defined(NMTOOLS_TESTING_GENERIC_NDARRAY)
    MAX_POOL2D_SUBCASE( case5, array, kernel_size, stride, padding, dilation, ceil_mode );
    MAX_POOL2D_SUBCASE( case5, array_a, kernel_size_a, stride_a, padding, dilation, ceil_mode );
    MAX_POOL2D_SUBCASE( case5, array_f, kernel_size_f, stride_f, padding, dilation, ceil_mode );
    MAX_POOL2D_SUBCASE( case5, array_h, kernel_size_h, stride_h, padding, dilation, ceil_mode );

    #else
    MAX_POOL2D_SUBCASE( case5, array_cs_fb, kernel_size, stride, padding, dilation, ceil_mode );
    MAX_POOL2D_SUBCASE( case5, array_cs_hb, kernel_size, stride, padding, dilation, ceil_mode );
    MAX_POOL2D_SUBCASE( case5, array_cs_db, kernel_size, stride, padding, dilation, ceil_mode );

    MAX_POOL2D_SUBCASE( case5, array_fs_fb, kernel_size, stride, padding, dilation, ceil_mode );
    MAX_POOL2D_SUBCASE( case5, array_fs_hb, kernel_size, stride, padding, dilation, ceil_mode );
    MAX_POOL2D_SUBCASE( case5, array_fs_db, kernel_size, stride, padding, dilation, ceil_mode );

    MAX_POOL2D_SUBCASE( case5, array_hs_fb, kernel_size, stride, padding, dilation, ceil_mode );
    MAX_POOL2D_SUBCASE( case5, array_hs_hb, kernel_size, stride, padding, dilation, ceil_mode );
    MAX_POOL2D_SUBCASE( case5, array_hs_db, kernel_size, stride, padding, dilation, ceil_mode );

    MAX_POOL2D_SUBCASE( case5, array_ds_fb, kernel_size, stride, padding, dilation, ceil_mode );
    MAX_POOL2D_SUBCASE( case5, array_ds_hb, kernel_size, stride, padding, dilation, ceil_mode );
    MAX_POOL2D_SUBCASE( case5, array_ds_db, kernel_size, stride, padding, dilation, ceil_mode );

    MAX_POOL2D_SUBCASE( case5, array_ls_fb, kernel_size, stride, padding, dilation, ceil_mode );
    MAX_POOL2D_SUBCASE( case5, array_ls_hb, kernel_size, stride, padding, dilation, ceil_mode );
    MAX_POOL2D_SUBCASE( case5, array_ls_db, kernel_size, stride, padding, dilation, ceil_mode );
    #endif
}

TEST_CASE("max_pool2d(case5)" * doctest::test_suite("array::max_pool2d"))
{
    #if !defined(NMTOOLS_TESTING_GENERIC_NDARRAY)
    MAX_POOL2D_SUBCASE( case5, array, kernel_size, stride, padding, dilation, ceil_mode );
    MAX_POOL2D_SUBCASE( case5, array_a, kernel_size_a, stride_a, padding, dilation, ceil_mode );
    MAX_POOL2D_SUBCASE( case5, array_f, kernel_size_f, stride_f, padding, dilation, ceil_mode );
    MAX_POOL2D_SUBCASE( case5, array_h, kernel_size_h, stride_h, padding, dilation, ceil_mode );

    #else
    MAX_POOL2D_SUBCASE( case5, array_cs_fb, kernel_size, stride, padding, dilation, ceil_mode );
    MAX_POOL2D_SUBCASE( case5, array_cs_hb, kernel_size, stride, padding, dilation, ceil_mode );
    MAX_POOL2D_SUBCASE( case5, array_cs_db, kernel_size, stride, padding, dilation, ceil_mode );

    MAX_POOL2D_SUBCASE( case5, array_fs_fb, kernel_size, stride, padding, dilation, ceil_mode );
    MAX_POOL2D_SUBCASE( case5, array_fs_hb, kernel_size, stride, padding, dilation, ceil_mode );
    MAX_POOL2D_SUBCASE( case5, array_fs_db, kernel_size, stride, padding, dilation, ceil_mode );

    MAX_POOL2D_SUBCASE( case5, array_hs_fb, kernel_size, stride, padding, dilation, ceil_mode );
    MAX_POOL2D_SUBCASE( case5, array_hs_hb, kernel_size, stride, padding, dilation, ceil_mode );
    MAX_POOL2D_SUBCASE( case5, array_hs_db, kernel_size, stride, padding, dilation, ceil_mode );

    MAX_POOL2D_SUBCASE( case5, array_ds_fb, kernel_size, stride, padding, dilation, ceil_mode );
    MAX_POOL2D_SUBCASE( case5, array_ds_hb, kernel_size, stride, padding, dilation, ceil_mode );
    MAX_POOL2D_SUBCASE( case5, array_ds_db, kernel_size, stride, padding, dilation, ceil_mode );

    MAX_POOL2D_SUBCASE( case5, array_ls_fb, kernel_size, stride, padding, dilation, ceil_mode );
    MAX_POOL2D_SUBCASE( case5, array_ls_hb, kernel_size, stride, padding, dilation, ceil_mode );
    MAX_POOL2D_SUBCASE( case5, array_ls_db, kernel_size, stride, padding, dilation, ceil_mode );
    #endif
}

TEST_CASE("max_pool2d(case6)" * doctest::test_suite("array::max_pool2d"))
{
    #if !defined(NMTOOLS_TESTING_GENERIC_NDARRAY)
    MAX_POOL2D_SUBCASE( case6, array, kernel_size, stride, padding, dilation, ceil_mode );
    MAX_POOL2D_SUBCASE( case6, array_a, kernel_size_a, stride_a, padding, dilation, ceil_mode );
    MAX_POOL2D_SUBCASE( case6, array_f, kernel_size_f, stride_f, padding, dilation, ceil_mode );
    MAX_POOL2D_SUBCASE( case6, array_h, kernel_size_h, stride_h, padding, dilation, ceil_mode );

    #else
    MAX_POOL2D_SUBCASE( case6, array_cs_fb, kernel_size, stride, padding, dilation, ceil_mode );
    MAX_POOL2D_SUBCASE( case6, array_cs_hb, kernel_size, stride, padding, dilation, ceil_mode );
    MAX_POOL2D_SUBCASE( case6, array_cs_db, kernel_size, stride, padding, dilation, ceil_mode );

    MAX_POOL2D_SUBCASE( case6, array_fs_fb, kernel_size, stride, padding, dilation, ceil_mode );
    MAX_POOL2D_SUBCASE( case6, array_fs_hb, kernel_size, stride, padding, dilation, ceil_mode );
    MAX_POOL2D_SUBCASE( case6, array_fs_db, kernel_size, stride, padding, dilation, ceil_mode );

    MAX_POOL2D_SUBCASE( case6, array_hs_fb, kernel_size, stride, padding, dilation, ceil_mode );
    MAX_POOL2D_SUBCASE( case6, array_hs_hb, kernel_size, stride, padding, dilation, ceil_mode );
    MAX_POOL2D_SUBCASE( case6, array_hs_db, kernel_size, stride, padding, dilation, ceil_mode );

    MAX_POOL2D_SUBCASE( case6, array_ds_fb, kernel_size, stride, padding, dilation, ceil_mode );
    MAX_POOL2D_SUBCASE( case6, array_ds_hb, kernel_size, stride, padding, dilation, ceil_mode );
    MAX_POOL2D_SUBCASE( case6, array_ds_db, kernel_size, stride, padding, dilation, ceil_mode );

    MAX_POOL2D_SUBCASE( case6, array_ls_fb, kernel_size, stride, padding, dilation, ceil_mode );
    MAX_POOL2D_SUBCASE( case6, array_ls_hb, kernel_size, stride, padding, dilation, ceil_mode );
    MAX_POOL2D_SUBCASE( case6, array_ls_db, kernel_size, stride, padding, dilation, ceil_mode );
    #endif
}

TEST_CASE("max_pool2d(case7)" * doctest::test_suite("array::max_pool2d"))
{
    #if !defined(NMTOOLS_TESTING_GENERIC_NDARRAY)
    MAX_POOL2D_SUBCASE( case7, array, kernel_size, stride, padding, dilation, ceil_mode );
    MAX_POOL2D_SUBCASE( case7, array_a, kernel_size_a, stride_a, padding, dilation, ceil_mode );
    MAX_POOL2D_SUBCASE( case7, array_f, kernel_size_f, stride_f, padding, dilation, ceil_mode );
    MAX_POOL2D_SUBCASE( case7, array_h, kernel_size_h, stride_h, padding, dilation, ceil_mode );

    #else
    MAX_POOL2D_SUBCASE( case7, array_cs_fb, kernel_size, stride, padding, dilation, ceil_mode );
    MAX_POOL2D_SUBCASE( case7, array_cs_hb, kernel_size, stride, padding, dilation, ceil_mode );
    MAX_POOL2D_SUBCASE( case7, array_cs_db, kernel_size, stride, padding, dilation, ceil_mode );

    MAX_POOL2D_SUBCASE( case7, array_fs_fb, kernel_size, stride, padding, dilation, ceil_mode );
    MAX_POOL2D_SUBCASE( case7, array_fs_hb, kernel_size, stride, padding, dilation, ceil_mode );
    MAX_POOL2D_SUBCASE( case7, array_fs_db, kernel_size, stride, padding, dilation, ceil_mode );

    MAX_POOL2D_SUBCASE( case7, array_hs_fb, kernel_size, stride, padding, dilation, ceil_mode );
    MAX_POOL2D_SUBCASE( case7, array_hs_hb, kernel_size, stride, padding, dilation, ceil_mode );
    MAX_POOL2D_SUBCASE( case7, array_hs_db, kernel_size, stride, padding, dilation, ceil_mode );

    MAX_POOL2D_SUBCASE( case7, array_ds_fb, kernel_size, stride, padding, dilation, ceil_mode );
    MAX_POOL2D_SUBCASE( case7, array_ds_hb, kernel_size, stride, padding, dilation, ceil_mode );
    MAX_POOL2D_SUBCASE( case7, array_ds_db, kernel_size, stride, padding, dilation, ceil_mode );

    MAX_POOL2D_SUBCASE( case7, array_ls_fb, kernel_size, stride, padding, dilation, ceil_mode );
    MAX_POOL2D_SUBCASE( case7, array_ls_hb, kernel_size, stride, padding, dilation, ceil_mode );
    MAX_POOL2D_SUBCASE( case7, array_ls_db, kernel_size, stride, padding, dilation, ceil_mode );
    #endif
}

TEST_CASE("max_pool2d(case8)" * doctest::test_suite("array::max_pool2d"))
{
    #if !defined(NMTOOLS_TESTING_GENERIC_NDARRAY)
    MAX_POOL2D_SUBCASE( case8, array, kernel_size, stride, padding, dilation, ceil_mode );
    MAX_POOL2D_SUBCASE( case8, array_a, kernel_size_a, stride_a, padding, dilation, ceil_mode );
    MAX_POOL2D_SUBCASE( case8, array_f, kernel_size_f, stride_f, padding, dilation, ceil_mode );
    MAX_POOL2D_SUBCASE( case8, array_h, kernel_size_h, stride_h, padding, dilation, ceil_mode );

    #else
    MAX_POOL2D_SUBCASE( case8, array_cs_fb, kernel_size, stride, padding, dilation, ceil_mode );
    MAX_POOL2D_SUBCASE( case8, array_cs_hb, kernel_size, stride, padding, dilation, ceil_mode );
    MAX_POOL2D_SUBCASE( case8, array_cs_db, kernel_size, stride, padding, dilation, ceil_mode );

    MAX_POOL2D_SUBCASE( case8, array_fs_fb, kernel_size, stride, padding, dilation, ceil_mode );
    MAX_POOL2D_SUBCASE( case8, array_fs_hb, kernel_size, stride, padding, dilation, ceil_mode );
    MAX_POOL2D_SUBCASE( case8, array_fs_db, kernel_size, stride, padding, dilation, ceil_mode );

    MAX_POOL2D_SUBCASE( case8, array_hs_fb, kernel_size, stride, padding, dilation, ceil_mode );
    MAX_POOL2D_SUBCASE( case8, array_hs_hb, kernel_size, stride, padding, dilation, ceil_mode );
    MAX_POOL2D_SUBCASE( case8, array_hs_db, kernel_size, stride, padding, dilation, ceil_mode );

    MAX_POOL2D_SUBCASE( case8, array_ds_fb, kernel_size, stride, padding, dilation, ceil_mode );
    MAX_POOL2D_SUBCASE( case8, array_ds_hb, kernel_size, stride, padding, dilation, ceil_mode );
    MAX_POOL2D_SUBCASE( case8, array_ds_db, kernel_size, stride, padding, dilation, ceil_mode );

    MAX_POOL2D_SUBCASE( case8, array_ls_fb, kernel_size, stride, padding, dilation, ceil_mode );
    MAX_POOL2D_SUBCASE( case8, array_ls_hb, kernel_size, stride, padding, dilation, ceil_mode );
    MAX_POOL2D_SUBCASE( case8, array_ls_db, kernel_size, stride, padding, dilation, ceil_mode );
    #endif
}

TEST_CASE("max_pool2d(case9)" * doctest::test_suite("array::max_pool2d"))
{
    #if !defined(NMTOOLS_TESTING_GENERIC_NDARRAY)
    MAX_POOL2D_SUBCASE( case9, array, kernel_size, stride, padding, dilation, ceil_mode );
    MAX_POOL2D_SUBCASE( case9, array_a, kernel_size_a, stride_a, padding, dilation, ceil_mode );
    MAX_POOL2D_SUBCASE( case9, array_f, kernel_size_f, stride_f, padding, dilation, ceil_mode );
    MAX_POOL2D_SUBCASE( case9, array_h, kernel_size_h, stride_h, padding, dilation, ceil_mode );

    #else
    MAX_POOL2D_SUBCASE( case9, array_cs_fb, kernel_size, stride, padding, dilation, ceil_mode );
    MAX_POOL2D_SUBCASE( case9, array_cs_hb, kernel_size, stride, padding, dilation, ceil_mode );
    MAX_POOL2D_SUBCASE( case9, array_cs_db, kernel_size, stride, padding, dilation, ceil_mode );

    MAX_POOL2D_SUBCASE( case9, array_fs_fb, kernel_size, stride, padding, dilation, ceil_mode );
    MAX_POOL2D_SUBCASE( case9, array_fs_hb, kernel_size, stride, padding, dilation, ceil_mode );
    MAX_POOL2D_SUBCASE( case9, array_fs_db, kernel_size, stride, padding, dilation, ceil_mode );

    MAX_POOL2D_SUBCASE( case9, array_hs_fb, kernel_size, stride, padding, dilation, ceil_mode );
    MAX_POOL2D_SUBCASE( case9, array_hs_hb, kernel_size, stride, padding, dilation, ceil_mode );
    MAX_POOL2D_SUBCASE( case9, array_hs_db, kernel_size, stride, padding, dilation, ceil_mode );

    MAX_POOL2D_SUBCASE( case9, array_ds_fb, kernel_size, stride, padding, dilation, ceil_mode );
    MAX_POOL2D_SUBCASE( case9, array_ds_hb, kernel_size, stride, padding, dilation, ceil_mode );
    MAX_POOL2D_SUBCASE( case9, array_ds_db, kernel_size, stride, padding, dilation, ceil_mode );

    MAX_POOL2D_SUBCASE( case9, array_ls_fb, kernel_size, stride, padding, dilation, ceil_mode );
    MAX_POOL2D_SUBCASE( case9, array_ls_hb, kernel_size, stride, padding, dilation, ceil_mode );
    MAX_POOL2D_SUBCASE( case9, array_ls_db, kernel_size, stride, padding, dilation, ceil_mode );
    #endif
}

TEST_CASE("max_pool2d(case10)" * doctest::test_suite("array::max_pool2d"))
{
    #if !defined(NMTOOLS_TESTING_GENERIC_NDARRAY)
    MAX_POOL2D_SUBCASE( case10, array, kernel_size, stride, padding, dilation, ceil_mode );
    MAX_POOL2D_SUBCASE( case10, array_a, kernel_size_a, stride_a, padding, dilation, ceil_mode );
    MAX_POOL2D_SUBCASE( case10, array_f, kernel_size_f, stride_f, padding, dilation, ceil_mode );
    MAX_POOL2D_SUBCASE( case10, array_h, kernel_size_h, stride_h, padding, dilation, ceil_mode );

    #else
    MAX_POOL2D_SUBCASE( case10, array_cs_fb, kernel_size, stride, padding, dilation, ceil_mode );
    MAX_POOL2D_SUBCASE( case10, array_cs_hb, kernel_size, stride, padding, dilation, ceil_mode );
    MAX_POOL2D_SUBCASE( case10, array_cs_db, kernel_size, stride, padding, dilation, ceil_mode );

    MAX_POOL2D_SUBCASE( case10, array_fs_fb, kernel_size, stride, padding, dilation, ceil_mode );
    MAX_POOL2D_SUBCASE( case10, array_fs_hb, kernel_size, stride, padding, dilation, ceil_mode );
    MAX_POOL2D_SUBCASE( case10, array_fs_db, kernel_size, stride, padding, dilation, ceil_mode );

    MAX_POOL2D_SUBCASE( case10, array_hs_fb, kernel_size, stride, padding, dilation, ceil_mode );
    MAX_POOL2D_SUBCASE( case10, array_hs_hb, kernel_size, stride, padding, dilation, ceil_mode );
    MAX_POOL2D_SUBCASE( case10, array_hs_db, kernel_size, stride, padding, dilation, ceil_mode );

    MAX_POOL2D_SUBCASE( case10, array_ds_fb, kernel_size, stride, padding, dilation, ceil_mode );
    MAX_POOL2D_SUBCASE( case10, array_ds_hb, kernel_size, stride, padding, dilation, ceil_mode );
    MAX_POOL2D_SUBCASE( case10, array_ds_db, kernel_size, stride, padding, dilation, ceil_mode );

    MAX_POOL2D_SUBCASE( case10, array_ls_fb, kernel_size, stride, padding, dilation, ceil_mode );
    MAX_POOL2D_SUBCASE( case10, array_ls_hb, kernel_size, stride, padding, dilation, ceil_mode );
    MAX_POOL2D_SUBCASE( case10, array_ls_db, kernel_size, stride, padding, dilation, ceil_mode );
    #endif
}

TEST_CASE("max_pool2d(case10b)" * doctest::test_suite("array::max_pool2d"))
{
    #if !defined(NMTOOLS_TESTING_GENERIC_NDARRAY)
    MAX_POOL2D_SUBCASE( case10b, array, kernel_size, stride, padding, dilation, ceil_mode );
    MAX_POOL2D_SUBCASE( case10b, array_a, kernel_size_a, stride_a, padding, dilation, ceil_mode );
    MAX_POOL2D_SUBCASE( case10b, array_f, kernel_size_f, stride_f, padding, dilation, ceil_mode );
    MAX_POOL2D_SUBCASE( case10b, array_h, kernel_size_h, stride_h, padding, dilation, ceil_mode );

    #else
    MAX_POOL2D_SUBCASE( case10b, array_cs_fb, kernel_size, stride, padding, dilation, ceil_mode );
    MAX_POOL2D_SUBCASE( case10b, array_cs_hb, kernel_size, stride, padding, dilation, ceil_mode );
    MAX_POOL2D_SUBCASE( case10b, array_cs_db, kernel_size, stride, padding, dilation, ceil_mode );

    MAX_POOL2D_SUBCASE( case10b, array_fs_fb, kernel_size, stride, padding, dilation, ceil_mode );
    MAX_POOL2D_SUBCASE( case10b, array_fs_hb, kernel_size, stride, padding, dilation, ceil_mode );
    MAX_POOL2D_SUBCASE( case10b, array_fs_db, kernel_size, stride, padding, dilation, ceil_mode );

    MAX_POOL2D_SUBCASE( case10b, array_hs_fb, kernel_size, stride, padding, dilation, ceil_mode );
    MAX_POOL2D_SUBCASE( case10b, array_hs_hb, kernel_size, stride, padding, dilation, ceil_mode );
    MAX_POOL2D_SUBCASE( case10b, array_hs_db, kernel_size, stride, padding, dilation, ceil_mode );

    MAX_POOL2D_SUBCASE( case10b, array_ds_fb, kernel_size, stride, padding, dilation, ceil_mode );
    MAX_POOL2D_SUBCASE( case10b, array_ds_hb, kernel_size, stride, padding, dilation, ceil_mode );
    MAX_POOL2D_SUBCASE( case10b, array_ds_db, kernel_size, stride, padding, dilation, ceil_mode );

    MAX_POOL2D_SUBCASE( case10b, array_ls_fb, kernel_size, stride, padding, dilation, ceil_mode );
    MAX_POOL2D_SUBCASE( case10b, array_ls_hb, kernel_size, stride, padding, dilation, ceil_mode );
    MAX_POOL2D_SUBCASE( case10b, array_ls_db, kernel_size, stride, padding, dilation, ceil_mode );
    #endif
}

TEST_CASE("max_pool2d(case10c)" * doctest::test_suite("array::max_pool2d"))
{
    #if !defined(NMTOOLS_TESTING_GENERIC_NDARRAY)
    MAX_POOL2D_SUBCASE( case10c, array, kernel_size, stride, padding, dilation, ceil_mode );
    MAX_POOL2D_SUBCASE( case10c, array_a, kernel_size_a, stride_a, padding, dilation, ceil_mode );
    MAX_POOL2D_SUBCASE( case10c, array_f, kernel_size_f, stride_f, padding, dilation, ceil_mode );
    MAX_POOL2D_SUBCASE( case10c, array_h, kernel_size_h, stride_h, padding, dilation, ceil_mode );

    #else
    MAX_POOL2D_SUBCASE( case10c, array_cs_fb, kernel_size, stride, padding, dilation, ceil_mode );
    MAX_POOL2D_SUBCASE( case10c, array_cs_hb, kernel_size, stride, padding, dilation, ceil_mode );
    MAX_POOL2D_SUBCASE( case10c, array_cs_db, kernel_size, stride, padding, dilation, ceil_mode );

    MAX_POOL2D_SUBCASE( case10c, array_fs_fb, kernel_size, stride, padding, dilation, ceil_mode );
    MAX_POOL2D_SUBCASE( case10c, array_fs_hb, kernel_size, stride, padding, dilation, ceil_mode );
    MAX_POOL2D_SUBCASE( case10c, array_fs_db, kernel_size, stride, padding, dilation, ceil_mode );

    MAX_POOL2D_SUBCASE( case10c, array_hs_fb, kernel_size, stride, padding, dilation, ceil_mode );
    MAX_POOL2D_SUBCASE( case10c, array_hs_hb, kernel_size, stride, padding, dilation, ceil_mode );
    MAX_POOL2D_SUBCASE( case10c, array_hs_db, kernel_size, stride, padding, dilation, ceil_mode );

    MAX_POOL2D_SUBCASE( case10c, array_ds_fb, kernel_size, stride, padding, dilation, ceil_mode );
    MAX_POOL2D_SUBCASE( case10c, array_ds_hb, kernel_size, stride, padding, dilation, ceil_mode );
    MAX_POOL2D_SUBCASE( case10c, array_ds_db, kernel_size, stride, padding, dilation, ceil_mode );

    MAX_POOL2D_SUBCASE( case10c, array_ls_fb, kernel_size, stride, padding, dilation, ceil_mode );
    MAX_POOL2D_SUBCASE( case10c, array_ls_hb, kernel_size, stride, padding, dilation, ceil_mode );
    MAX_POOL2D_SUBCASE( case10c, array_ls_db, kernel_size, stride, padding, dilation, ceil_mode );
    #endif
}

TEST_CASE("max_pool2d(case11)" * doctest::test_suite("array::max_pool2d"))
{
    #if !defined(NMTOOLS_TESTING_GENERIC_NDARRAY)
    MAX_POOL2D_SUBCASE( case11, array, kernel_size, stride, padding, dilation, ceil_mode );
    MAX_POOL2D_SUBCASE( case11, array_a, kernel_size_a, stride_a, padding, dilation, ceil_mode );
    MAX_POOL2D_SUBCASE( case11, array_f, kernel_size_f, stride_f, padding, dilation, ceil_mode );
    MAX_POOL2D_SUBCASE( case11, array_h, kernel_size_h, stride_h, padding, dilation, ceil_mode );

    #else
    MAX_POOL2D_SUBCASE( case11, array_cs_fb, kernel_size, stride, padding, dilation, ceil_mode );
    MAX_POOL2D_SUBCASE( case11, array_cs_hb, kernel_size, stride, padding, dilation, ceil_mode );
    MAX_POOL2D_SUBCASE( case11, array_cs_db, kernel_size, stride, padding, dilation, ceil_mode );

    MAX_POOL2D_SUBCASE( case11, array_fs_fb, kernel_size, stride, padding, dilation, ceil_mode );
    MAX_POOL2D_SUBCASE( case11, array_fs_hb, kernel_size, stride, padding, dilation, ceil_mode );
    MAX_POOL2D_SUBCASE( case11, array_fs_db, kernel_size, stride, padding, dilation, ceil_mode );

    MAX_POOL2D_SUBCASE( case11, array_hs_fb, kernel_size, stride, padding, dilation, ceil_mode );
    MAX_POOL2D_SUBCASE( case11, array_hs_hb, kernel_size, stride, padding, dilation, ceil_mode );
    MAX_POOL2D_SUBCASE( case11, array_hs_db, kernel_size, stride, padding, dilation, ceil_mode );

    MAX_POOL2D_SUBCASE( case11, array_ds_fb, kernel_size, stride, padding, dilation, ceil_mode );
    MAX_POOL2D_SUBCASE( case11, array_ds_hb, kernel_size, stride, padding, dilation, ceil_mode );
    MAX_POOL2D_SUBCASE( case11, array_ds_db, kernel_size, stride, padding, dilation, ceil_mode );

    MAX_POOL2D_SUBCASE( case11, array_ls_fb, kernel_size, stride, padding, dilation, ceil_mode );
    MAX_POOL2D_SUBCASE( case11, array_ls_hb, kernel_size, stride, padding, dilation, ceil_mode );
    MAX_POOL2D_SUBCASE( case11, array_ls_db, kernel_size, stride, padding, dilation, ceil_mode );
    #endif
}

TEST_CASE("max_pool2d(case11b)" * doctest::test_suite("array::max_pool2d"))
{
    #if !defined(NMTOOLS_TESTING_GENERIC_NDARRAY)
    MAX_POOL2D_SUBCASE( case11b, array, kernel_size, stride, padding, dilation, ceil_mode );
    MAX_POOL2D_SUBCASE( case11b, array_a, kernel_size_a, stride_a, padding, dilation, ceil_mode );
    MAX_POOL2D_SUBCASE( case11b, array_f, kernel_size_f, stride_f, padding, dilation, ceil_mode );
    MAX_POOL2D_SUBCASE( case11b, array_h, kernel_size_h, stride_h, padding, dilation, ceil_mode );

    #else
    MAX_POOL2D_SUBCASE( case11b, array_cs_fb, kernel_size, stride, padding, dilation, ceil_mode );
    MAX_POOL2D_SUBCASE( case11b, array_cs_hb, kernel_size, stride, padding, dilation, ceil_mode );
    MAX_POOL2D_SUBCASE( case11b, array_cs_db, kernel_size, stride, padding, dilation, ceil_mode );

    MAX_POOL2D_SUBCASE( case11b, array_fs_fb, kernel_size, stride, padding, dilation, ceil_mode );
    MAX_POOL2D_SUBCASE( case11b, array_fs_hb, kernel_size, stride, padding, dilation, ceil_mode );
    MAX_POOL2D_SUBCASE( case11b, array_fs_db, kernel_size, stride, padding, dilation, ceil_mode );

    MAX_POOL2D_SUBCASE( case11b, array_hs_fb, kernel_size, stride, padding, dilation, ceil_mode );
    MAX_POOL2D_SUBCASE( case11b, array_hs_hb, kernel_size, stride, padding, dilation, ceil_mode );
    MAX_POOL2D_SUBCASE( case11b, array_hs_db, kernel_size, stride, padding, dilation, ceil_mode );

    MAX_POOL2D_SUBCASE( case11b, array_ds_fb, kernel_size, stride, padding, dilation, ceil_mode );
    MAX_POOL2D_SUBCASE( case11b, array_ds_hb, kernel_size, stride, padding, dilation, ceil_mode );
    MAX_POOL2D_SUBCASE( case11b, array_ds_db, kernel_size, stride, padding, dilation, ceil_mode );

    MAX_POOL2D_SUBCASE( case11b, array_ls_fb, kernel_size, stride, padding, dilation, ceil_mode );
    MAX_POOL2D_SUBCASE( case11b, array_ls_hb, kernel_size, stride, padding, dilation, ceil_mode );
    MAX_POOL2D_SUBCASE( case11b, array_ls_db, kernel_size, stride, padding, dilation, ceil_mode );
    #endif
}

TEST_CASE("max_pool2d(case11c)" * doctest::test_suite("array::max_pool2d"))
{
    #if !defined(NMTOOLS_TESTING_GENERIC_NDARRAY)
    MAX_POOL2D_SUBCASE( case11c, array, kernel_size, stride, padding, dilation, ceil_mode );
    MAX_POOL2D_SUBCASE( case11c, array_a, kernel_size_a, stride_a, padding, dilation, ceil_mode );
    MAX_POOL2D_SUBCASE( case11c, array_f, kernel_size_f, stride_f, padding, dilation, ceil_mode );
    MAX_POOL2D_SUBCASE( case11c, array_h, kernel_size_h, stride_h, padding, dilation, ceil_mode );

    #else
    MAX_POOL2D_SUBCASE( case11c, array_cs_fb, kernel_size, stride, padding, dilation, ceil_mode );
    MAX_POOL2D_SUBCASE( case11c, array_cs_hb, kernel_size, stride, padding, dilation, ceil_mode );
    MAX_POOL2D_SUBCASE( case11c, array_cs_db, kernel_size, stride, padding, dilation, ceil_mode );

    MAX_POOL2D_SUBCASE( case11c, array_fs_fb, kernel_size, stride, padding, dilation, ceil_mode );
    MAX_POOL2D_SUBCASE( case11c, array_fs_hb, kernel_size, stride, padding, dilation, ceil_mode );
    MAX_POOL2D_SUBCASE( case11c, array_fs_db, kernel_size, stride, padding, dilation, ceil_mode );

    MAX_POOL2D_SUBCASE( case11c, array_hs_fb, kernel_size, stride, padding, dilation, ceil_mode );
    MAX_POOL2D_SUBCASE( case11c, array_hs_hb, kernel_size, stride, padding, dilation, ceil_mode );
    MAX_POOL2D_SUBCASE( case11c, array_hs_db, kernel_size, stride, padding, dilation, ceil_mode );

    MAX_POOL2D_SUBCASE( case11c, array_ds_fb, kernel_size, stride, padding, dilation, ceil_mode );
    MAX_POOL2D_SUBCASE( case11c, array_ds_hb, kernel_size, stride, padding, dilation, ceil_mode );
    MAX_POOL2D_SUBCASE( case11c, array_ds_db, kernel_size, stride, padding, dilation, ceil_mode );

    MAX_POOL2D_SUBCASE( case11c, array_ls_fb, kernel_size, stride, padding, dilation, ceil_mode );
    MAX_POOL2D_SUBCASE( case11c, array_ls_hb, kernel_size, stride, padding, dilation, ceil_mode );
    MAX_POOL2D_SUBCASE( case11c, array_ls_db, kernel_size, stride, padding, dilation, ceil_mode );
    #endif
}

TEST_CASE("max_pool2d(case12)" * doctest::test_suite("array::max_pool2d"))
{
    #if !defined(NMTOOLS_TESTING_GENERIC_NDARRAY)
    MAX_POOL2D_SUBCASE( case12, array, kernel_size, stride, padding, dilation, ceil_mode );
    MAX_POOL2D_SUBCASE( case12, array_a, kernel_size_a, stride_a, padding, dilation, ceil_mode );
    MAX_POOL2D_SUBCASE( case12, array_f, kernel_size_f, stride_f, padding, dilation, ceil_mode );
    MAX_POOL2D_SUBCASE( case12, array_h, kernel_size_h, stride_h, padding, dilation, ceil_mode );

    #else
    MAX_POOL2D_SUBCASE( case12, array_cs_fb, kernel_size, stride, padding, dilation, ceil_mode );
    MAX_POOL2D_SUBCASE( case12, array_cs_hb, kernel_size, stride, padding, dilation, ceil_mode );
    MAX_POOL2D_SUBCASE( case12, array_cs_db, kernel_size, stride, padding, dilation, ceil_mode );

    MAX_POOL2D_SUBCASE( case12, array_fs_fb, kernel_size, stride, padding, dilation, ceil_mode );
    MAX_POOL2D_SUBCASE( case12, array_fs_hb, kernel_size, stride, padding, dilation, ceil_mode );
    MAX_POOL2D_SUBCASE( case12, array_fs_db, kernel_size, stride, padding, dilation, ceil_mode );

    MAX_POOL2D_SUBCASE( case12, array_hs_fb, kernel_size, stride, padding, dilation, ceil_mode );
    MAX_POOL2D_SUBCASE( case12, array_hs_hb, kernel_size, stride, padding, dilation, ceil_mode );
    MAX_POOL2D_SUBCASE( case12, array_hs_db, kernel_size, stride, padding, dilation, ceil_mode );

    MAX_POOL2D_SUBCASE( case12, array_ds_fb, kernel_size, stride, padding, dilation, ceil_mode );
    MAX_POOL2D_SUBCASE( case12, array_ds_hb, kernel_size, stride, padding, dilation, ceil_mode );
    MAX_POOL2D_SUBCASE( case12, array_ds_db, kernel_size, stride, padding, dilation, ceil_mode );

    MAX_POOL2D_SUBCASE( case12, array_ls_fb, kernel_size, stride, padding, dilation, ceil_mode );
    MAX_POOL2D_SUBCASE( case12, array_ls_hb, kernel_size, stride, padding, dilation, ceil_mode );
    MAX_POOL2D_SUBCASE( case12, array_ls_db, kernel_size, stride, padding, dilation, ceil_mode );
    #endif
}

TEST_CASE("max_pool2d(case12b)" * doctest::test_suite("array::max_pool2d"))
{
    #if !defined(NMTOOLS_TESTING_GENERIC_NDARRAY)
    MAX_POOL2D_SUBCASE( case12b, array, kernel_size, stride, padding, dilation, ceil_mode );
    MAX_POOL2D_SUBCASE( case12b, array_a, kernel_size_a, stride_a, padding, dilation, ceil_mode );
    MAX_POOL2D_SUBCASE( case12b, array_f, kernel_size_f, stride_f, padding, dilation, ceil_mode );
    MAX_POOL2D_SUBCASE( case12b, array_h, kernel_size_h, stride_h, padding, dilation, ceil_mode );

    #else
    MAX_POOL2D_SUBCASE( case12b, array_cs_fb, kernel_size, stride, padding, dilation, ceil_mode );
    MAX_POOL2D_SUBCASE( case12b, array_cs_hb, kernel_size, stride, padding, dilation, ceil_mode );
    MAX_POOL2D_SUBCASE( case12b, array_cs_db, kernel_size, stride, padding, dilation, ceil_mode );

    MAX_POOL2D_SUBCASE( case12b, array_fs_fb, kernel_size, stride, padding, dilation, ceil_mode );
    MAX_POOL2D_SUBCASE( case12b, array_fs_hb, kernel_size, stride, padding, dilation, ceil_mode );
    MAX_POOL2D_SUBCASE( case12b, array_fs_db, kernel_size, stride, padding, dilation, ceil_mode );

    MAX_POOL2D_SUBCASE( case12b, array_hs_fb, kernel_size, stride, padding, dilation, ceil_mode );
    MAX_POOL2D_SUBCASE( case12b, array_hs_hb, kernel_size, stride, padding, dilation, ceil_mode );
    MAX_POOL2D_SUBCASE( case12b, array_hs_db, kernel_size, stride, padding, dilation, ceil_mode );

    MAX_POOL2D_SUBCASE( case12b, array_ds_fb, kernel_size, stride, padding, dilation, ceil_mode );
    MAX_POOL2D_SUBCASE( case12b, array_ds_hb, kernel_size, stride, padding, dilation, ceil_mode );
    MAX_POOL2D_SUBCASE( case12b, array_ds_db, kernel_size, stride, padding, dilation, ceil_mode );

    MAX_POOL2D_SUBCASE( case12b, array_ls_fb, kernel_size, stride, padding, dilation, ceil_mode );
    MAX_POOL2D_SUBCASE( case12b, array_ls_hb, kernel_size, stride, padding, dilation, ceil_mode );
    MAX_POOL2D_SUBCASE( case12b, array_ls_db, kernel_size, stride, padding, dilation, ceil_mode );
    #endif
}

TEST_CASE("max_pool2d(case12c)" * doctest::test_suite("array::max_pool2d"))
{
    #if !defined(NMTOOLS_TESTING_GENERIC_NDARRAY)
    MAX_POOL2D_SUBCASE( case12c, array, kernel_size, stride, padding, dilation, ceil_mode );
    MAX_POOL2D_SUBCASE( case12c, array_a, kernel_size_a, stride_a, padding, dilation, ceil_mode );
    MAX_POOL2D_SUBCASE( case12c, array_f, kernel_size_f, stride_f, padding, dilation, ceil_mode );
    MAX_POOL2D_SUBCASE( case12c, array_h, kernel_size_h, stride_h, padding, dilation, ceil_mode );

    #else
    MAX_POOL2D_SUBCASE( case12c, array_cs_fb, kernel_size, stride, padding, dilation, ceil_mode );
    MAX_POOL2D_SUBCASE( case12c, array_cs_hb, kernel_size, stride, padding, dilation, ceil_mode );
    MAX_POOL2D_SUBCASE( case12c, array_cs_db, kernel_size, stride, padding, dilation, ceil_mode );

    MAX_POOL2D_SUBCASE( case12c, array_fs_fb, kernel_size, stride, padding, dilation, ceil_mode );
    MAX_POOL2D_SUBCASE( case12c, array_fs_hb, kernel_size, stride, padding, dilation, ceil_mode );
    MAX_POOL2D_SUBCASE( case12c, array_fs_db, kernel_size, stride, padding, dilation, ceil_mode );

    MAX_POOL2D_SUBCASE( case12c, array_hs_fb, kernel_size, stride, padding, dilation, ceil_mode );
    MAX_POOL2D_SUBCASE( case12c, array_hs_hb, kernel_size, stride, padding, dilation, ceil_mode );
    MAX_POOL2D_SUBCASE( case12c, array_hs_db, kernel_size, stride, padding, dilation, ceil_mode );

    MAX_POOL2D_SUBCASE( case12c, array_ds_fb, kernel_size, stride, padding, dilation, ceil_mode );
    MAX_POOL2D_SUBCASE( case12c, array_ds_hb, kernel_size, stride, padding, dilation, ceil_mode );
    MAX_POOL2D_SUBCASE( case12c, array_ds_db, kernel_size, stride, padding, dilation, ceil_mode );

    MAX_POOL2D_SUBCASE( case12c, array_ls_fb, kernel_size, stride, padding, dilation, ceil_mode );
    MAX_POOL2D_SUBCASE( case12c, array_ls_hb, kernel_size, stride, padding, dilation, ceil_mode );
    MAX_POOL2D_SUBCASE( case12c, array_ls_db, kernel_size, stride, padding, dilation, ceil_mode );
    #endif
}

TEST_CASE("max_pool2d(case12d)" * doctest::test_suite("array::max_pool2d"))
{
    #if !defined(NMTOOLS_TESTING_GENERIC_NDARRAY)
    MAX_POOL2D_SUBCASE( case12d, array, kernel_size, stride, padding, dilation, ceil_mode );
    MAX_POOL2D_SUBCASE( case12d, array_a, kernel_size_a, stride_a, padding, dilation, ceil_mode );
    MAX_POOL2D_SUBCASE( case12d, array_f, kernel_size_f, stride_f, padding, dilation, ceil_mode );
    MAX_POOL2D_SUBCASE( case12d, array_h, kernel_size_h, stride_h, padding, dilation, ceil_mode );

    #else
    MAX_POOL2D_SUBCASE( case12d, array_cs_fb, kernel_size, stride, padding, dilation, ceil_mode );
    MAX_POOL2D_SUBCASE( case12d, array_cs_hb, kernel_size, stride, padding, dilation, ceil_mode );
    MAX_POOL2D_SUBCASE( case12d, array_cs_db, kernel_size, stride, padding, dilation, ceil_mode );

    MAX_POOL2D_SUBCASE( case12d, array_fs_fb, kernel_size, stride, padding, dilation, ceil_mode );
    MAX_POOL2D_SUBCASE( case12d, array_fs_hb, kernel_size, stride, padding, dilation, ceil_mode );
    MAX_POOL2D_SUBCASE( case12d, array_fs_db, kernel_size, stride, padding, dilation, ceil_mode );

    MAX_POOL2D_SUBCASE( case12d, array_hs_fb, kernel_size, stride, padding, dilation, ceil_mode );
    MAX_POOL2D_SUBCASE( case12d, array_hs_hb, kernel_size, stride, padding, dilation, ceil_mode );
    MAX_POOL2D_SUBCASE( case12d, array_hs_db, kernel_size, stride, padding, dilation, ceil_mode );

    MAX_POOL2D_SUBCASE( case12d, array_ds_fb, kernel_size, stride, padding, dilation, ceil_mode );
    MAX_POOL2D_SUBCASE( case12d, array_ds_hb, kernel_size, stride, padding, dilation, ceil_mode );
    MAX_POOL2D_SUBCASE( case12d, array_ds_db, kernel_size, stride, padding, dilation, ceil_mode );

    MAX_POOL2D_SUBCASE( case12d, array_ls_fb, kernel_size, stride, padding, dilation, ceil_mode );
    MAX_POOL2D_SUBCASE( case12d, array_ls_hb, kernel_size, stride, padding, dilation, ceil_mode );
    MAX_POOL2D_SUBCASE( case12d, array_ls_db, kernel_size, stride, padding, dilation, ceil_mode );
    #endif
}

TEST_CASE("max_pool2d(case12e)" * doctest::test_suite("array::max_pool2d"))
{
    #if !defined(NMTOOLS_TESTING_GENERIC_NDARRAY)
    MAX_POOL2D_SUBCASE( case12e, array, kernel_size, stride, padding, dilation, ceil_mode );
    MAX_POOL2D_SUBCASE( case12e, array_a, kernel_size_a, stride_a, padding, dilation, ceil_mode );
    MAX_POOL2D_SUBCASE( case12e, array_f, kernel_size_f, stride_f, padding, dilation, ceil_mode );
    MAX_POOL2D_SUBCASE( case12e, array_h, kernel_size_h, stride_h, padding, dilation, ceil_mode );

    #else
    MAX_POOL2D_SUBCASE( case12e, array_cs_fb, kernel_size, stride, padding, dilation, ceil_mode );
    MAX_POOL2D_SUBCASE( case12e, array_cs_hb, kernel_size, stride, padding, dilation, ceil_mode );
    MAX_POOL2D_SUBCASE( case12e, array_cs_db, kernel_size, stride, padding, dilation, ceil_mode );

    MAX_POOL2D_SUBCASE( case12e, array_fs_fb, kernel_size, stride, padding, dilation, ceil_mode );
    MAX_POOL2D_SUBCASE( case12e, array_fs_hb, kernel_size, stride, padding, dilation, ceil_mode );
    MAX_POOL2D_SUBCASE( case12e, array_fs_db, kernel_size, stride, padding, dilation, ceil_mode );

    MAX_POOL2D_SUBCASE( case12e, array_hs_fb, kernel_size, stride, padding, dilation, ceil_mode );
    MAX_POOL2D_SUBCASE( case12e, array_hs_hb, kernel_size, stride, padding, dilation, ceil_mode );
    MAX_POOL2D_SUBCASE( case12e, array_hs_db, kernel_size, stride, padding, dilation, ceil_mode );

    MAX_POOL2D_SUBCASE( case12e, array_ds_fb, kernel_size, stride, padding, dilation, ceil_mode );
    MAX_POOL2D_SUBCASE( case12e, array_ds_hb, kernel_size, stride, padding, dilation, ceil_mode );
    MAX_POOL2D_SUBCASE( case12e, array_ds_db, kernel_size, stride, padding, dilation, ceil_mode );

    MAX_POOL2D_SUBCASE( case12e, array_ls_fb, kernel_size, stride, padding, dilation, ceil_mode );
    MAX_POOL2D_SUBCASE( case12e, array_ls_hb, kernel_size, stride, padding, dilation, ceil_mode );
    MAX_POOL2D_SUBCASE( case12e, array_ls_db, kernel_size, stride, padding, dilation, ceil_mode );
    #endif
}

TEST_CASE("max_pool2d(case12f)" * doctest::test_suite("array::max_pool2d"))
{
    #if !defined(NMTOOLS_TESTING_GENERIC_NDARRAY)
    MAX_POOL2D_SUBCASE( case12f, array, kernel_size, stride, padding, dilation, ceil_mode );
    MAX_POOL2D_SUBCASE( case12f, array_a, kernel_size_a, stride_a, padding, dilation, ceil_mode );
    MAX_POOL2D_SUBCASE( case12f, array_f, kernel_size_f, stride_f, padding, dilation, ceil_mode );
    MAX_POOL2D_SUBCASE( case12f, array_h, kernel_size_h, stride_h, padding, dilation, ceil_mode );

    #else
    MAX_POOL2D_SUBCASE( case12f, array_cs_fb, kernel_size, stride, padding, dilation, ceil_mode );
    MAX_POOL2D_SUBCASE( case12f, array_cs_hb, kernel_size, stride, padding, dilation, ceil_mode );
    MAX_POOL2D_SUBCASE( case12f, array_cs_db, kernel_size, stride, padding, dilation, ceil_mode );

    MAX_POOL2D_SUBCASE( case12f, array_fs_fb, kernel_size, stride, padding, dilation, ceil_mode );
    MAX_POOL2D_SUBCASE( case12f, array_fs_hb, kernel_size, stride, padding, dilation, ceil_mode );
    MAX_POOL2D_SUBCASE( case12f, array_fs_db, kernel_size, stride, padding, dilation, ceil_mode );

    MAX_POOL2D_SUBCASE( case12f, array_hs_fb, kernel_size, stride, padding, dilation, ceil_mode );
    MAX_POOL2D_SUBCASE( case12f, array_hs_hb, kernel_size, stride, padding, dilation, ceil_mode );
    MAX_POOL2D_SUBCASE( case12f, array_hs_db, kernel_size, stride, padding, dilation, ceil_mode );

    MAX_POOL2D_SUBCASE( case12f, array_ds_fb, kernel_size, stride, padding, dilation, ceil_mode );
    MAX_POOL2D_SUBCASE( case12f, array_ds_hb, kernel_size, stride, padding, dilation, ceil_mode );
    MAX_POOL2D_SUBCASE( case12f, array_ds_db, kernel_size, stride, padding, dilation, ceil_mode );

    MAX_POOL2D_SUBCASE( case12f, array_ls_fb, kernel_size, stride, padding, dilation, ceil_mode );
    MAX_POOL2D_SUBCASE( case12f, array_ls_hb, kernel_size, stride, padding, dilation, ceil_mode );
    MAX_POOL2D_SUBCASE( case12f, array_ls_db, kernel_size, stride, padding, dilation, ceil_mode );
    #endif
}

TEST_CASE("max_pool2d(case13)" * doctest::test_suite("array::max_pool2d"))
{
    #if !defined(NMTOOLS_TESTING_GENERIC_NDARRAY)
    MAX_POOL2D_SUBCASE( case13, array, kernel_size, stride, padding, dilation, ceil_mode );
    MAX_POOL2D_SUBCASE( case13, array_a, kernel_size_a, stride_a, padding, dilation, ceil_mode );
    MAX_POOL2D_SUBCASE( case13, array_f, kernel_size_f, stride_f, padding, dilation, ceil_mode );
    MAX_POOL2D_SUBCASE( case13, array_h, kernel_size_h, stride_h, padding, dilation, ceil_mode );

    #else
    MAX_POOL2D_SUBCASE( case13, array_cs_fb, kernel_size, stride, padding, dilation, ceil_mode );
    MAX_POOL2D_SUBCASE( case13, array_cs_hb, kernel_size, stride, padding, dilation, ceil_mode );
    MAX_POOL2D_SUBCASE( case13, array_cs_db, kernel_size, stride, padding, dilation, ceil_mode );

    MAX_POOL2D_SUBCASE( case13, array_fs_fb, kernel_size, stride, padding, dilation, ceil_mode );
    MAX_POOL2D_SUBCASE( case13, array_fs_hb, kernel_size, stride, padding, dilation, ceil_mode );
    MAX_POOL2D_SUBCASE( case13, array_fs_db, kernel_size, stride, padding, dilation, ceil_mode );

    MAX_POOL2D_SUBCASE( case13, array_hs_fb, kernel_size, stride, padding, dilation, ceil_mode );
    MAX_POOL2D_SUBCASE( case13, array_hs_hb, kernel_size, stride, padding, dilation, ceil_mode );
    MAX_POOL2D_SUBCASE( case13, array_hs_db, kernel_size, stride, padding, dilation, ceil_mode );

    MAX_POOL2D_SUBCASE( case13, array_ds_fb, kernel_size, stride, padding, dilation, ceil_mode );
    MAX_POOL2D_SUBCASE( case13, array_ds_hb, kernel_size, stride, padding, dilation, ceil_mode );
    MAX_POOL2D_SUBCASE( case13, array_ds_db, kernel_size, stride, padding, dilation, ceil_mode );

    MAX_POOL2D_SUBCASE( case13, array_ls_fb, kernel_size, stride, padding, dilation, ceil_mode );
    MAX_POOL2D_SUBCASE( case13, array_ls_hb, kernel_size, stride, padding, dilation, ceil_mode );
    MAX_POOL2D_SUBCASE( case13, array_ls_db, kernel_size, stride, padding, dilation, ceil_mode );
    #endif
}

TEST_CASE("max_pool2d(case14)" * doctest::test_suite("array::max_pool2d"))
{
    #if !defined(NMTOOLS_TESTING_GENERIC_NDARRAY)
    MAX_POOL2D_SUBCASE( case14, array, kernel_size, stride, padding, dilation, ceil_mode );
    MAX_POOL2D_SUBCASE( case14, array_a, kernel_size_a, stride_a, padding, dilation, ceil_mode );
    MAX_POOL2D_SUBCASE( case14, array_f, kernel_size_f, stride_f, padding, dilation, ceil_mode );
    MAX_POOL2D_SUBCASE( case14, array_h, kernel_size_h, stride_h, padding, dilation, ceil_mode );

    #else
    MAX_POOL2D_SUBCASE( case14, array_cs_fb, kernel_size, stride, padding, dilation, ceil_mode );
    MAX_POOL2D_SUBCASE( case14, array_cs_hb, kernel_size, stride, padding, dilation, ceil_mode );
    MAX_POOL2D_SUBCASE( case14, array_cs_db, kernel_size, stride, padding, dilation, ceil_mode );

    MAX_POOL2D_SUBCASE( case14, array_fs_fb, kernel_size, stride, padding, dilation, ceil_mode );
    MAX_POOL2D_SUBCASE( case14, array_fs_hb, kernel_size, stride, padding, dilation, ceil_mode );
    MAX_POOL2D_SUBCASE( case14, array_fs_db, kernel_size, stride, padding, dilation, ceil_mode );

    MAX_POOL2D_SUBCASE( case14, array_hs_fb, kernel_size, stride, padding, dilation, ceil_mode );
    MAX_POOL2D_SUBCASE( case14, array_hs_hb, kernel_size, stride, padding, dilation, ceil_mode );
    MAX_POOL2D_SUBCASE( case14, array_hs_db, kernel_size, stride, padding, dilation, ceil_mode );

    MAX_POOL2D_SUBCASE( case14, array_ds_fb, kernel_size, stride, padding, dilation, ceil_mode );
    MAX_POOL2D_SUBCASE( case14, array_ds_hb, kernel_size, stride, padding, dilation, ceil_mode );
    MAX_POOL2D_SUBCASE( case14, array_ds_db, kernel_size, stride, padding, dilation, ceil_mode );

    MAX_POOL2D_SUBCASE( case14, array_ls_fb, kernel_size, stride, padding, dilation, ceil_mode );
    MAX_POOL2D_SUBCASE( case14, array_ls_hb, kernel_size, stride, padding, dilation, ceil_mode );
    MAX_POOL2D_SUBCASE( case14, array_ls_db, kernel_size, stride, padding, dilation, ceil_mode );
    #endif
}

TEST_CASE("max_pool2d(case14b)" * doctest::test_suite("array::max_pool2d"))
{
    #if !defined(NMTOOLS_TESTING_GENERIC_NDARRAY)
    MAX_POOL2D_SUBCASE( case14b, array, kernel_size, stride, padding, dilation, ceil_mode );
    MAX_POOL2D_SUBCASE( case14b, array_a, kernel_size_a, stride_a, padding, dilation, ceil_mode );
    MAX_POOL2D_SUBCASE( case14b, array_f, kernel_size_f, stride_f, padding, dilation, ceil_mode );
    MAX_POOL2D_SUBCASE( case14b, array_h, kernel_size_h, stride_h, padding, dilation, ceil_mode );

    #else
    MAX_POOL2D_SUBCASE( case14b, array_cs_fb, kernel_size, stride, padding, dilation, ceil_mode );
    MAX_POOL2D_SUBCASE( case14b, array_cs_hb, kernel_size, stride, padding, dilation, ceil_mode );
    MAX_POOL2D_SUBCASE( case14b, array_cs_db, kernel_size, stride, padding, dilation, ceil_mode );

    MAX_POOL2D_SUBCASE( case14b, array_fs_fb, kernel_size, stride, padding, dilation, ceil_mode );
    MAX_POOL2D_SUBCASE( case14b, array_fs_hb, kernel_size, stride, padding, dilation, ceil_mode );
    MAX_POOL2D_SUBCASE( case14b, array_fs_db, kernel_size, stride, padding, dilation, ceil_mode );

    MAX_POOL2D_SUBCASE( case14b, array_hs_fb, kernel_size, stride, padding, dilation, ceil_mode );
    MAX_POOL2D_SUBCASE( case14b, array_hs_hb, kernel_size, stride, padding, dilation, ceil_mode );
    MAX_POOL2D_SUBCASE( case14b, array_hs_db, kernel_size, stride, padding, dilation, ceil_mode );

    MAX_POOL2D_SUBCASE( case14b, array_ds_fb, kernel_size, stride, padding, dilation, ceil_mode );
    MAX_POOL2D_SUBCASE( case14b, array_ds_hb, kernel_size, stride, padding, dilation, ceil_mode );
    MAX_POOL2D_SUBCASE( case14b, array_ds_db, kernel_size, stride, padding, dilation, ceil_mode );

    MAX_POOL2D_SUBCASE( case14b, array_ls_fb, kernel_size, stride, padding, dilation, ceil_mode );
    MAX_POOL2D_SUBCASE( case14b, array_ls_hb, kernel_size, stride, padding, dilation, ceil_mode );
    MAX_POOL2D_SUBCASE( case14b, array_ls_db, kernel_size, stride, padding, dilation, ceil_mode );
    #endif
}

TEST_CASE("max_pool2d(case14c)" * doctest::test_suite("array::max_pool2d"))
{
    #if !defined(NMTOOLS_TESTING_GENERIC_NDARRAY)
    MAX_POOL2D_SUBCASE( case14c, array, kernel_size, stride, padding, dilation, ceil_mode );
    MAX_POOL2D_SUBCASE( case14c, array_a, kernel_size_a, stride, padding, dilation, ceil_mode );
    MAX_POOL2D_SUBCASE( case14c, array_f, kernel_size_f, stride, padding, dilation, ceil_mode );
    MAX_POOL2D_SUBCASE( case14c, array_h, kernel_size_h, stride, padding, dilation, ceil_mode );

    #else
    MAX_POOL2D_SUBCASE( case14c, array_cs_fb, kernel_size, stride, padding, dilation, ceil_mode );
    MAX_POOL2D_SUBCASE( case14c, array_cs_hb, kernel_size, stride, padding, dilation, ceil_mode );
    MAX_POOL2D_SUBCASE( case14c, array_cs_db, kernel_size, stride, padding, dilation, ceil_mode );

    MAX_POOL2D_SUBCASE( case14c, array_fs_fb, kernel_size, stride, padding, dilation, ceil_mode );
    MAX_POOL2D_SUBCASE( case14c, array_fs_hb, kernel_size, stride, padding, dilation, ceil_mode );
    MAX_POOL2D_SUBCASE( case14c, array_fs_db, kernel_size, stride, padding, dilation, ceil_mode );

    MAX_POOL2D_SUBCASE( case14c, array_hs_fb, kernel_size, stride, padding, dilation, ceil_mode );
    MAX_POOL2D_SUBCASE( case14c, array_hs_hb, kernel_size, stride, padding, dilation, ceil_mode );
    MAX_POOL2D_SUBCASE( case14c, array_hs_db, kernel_size, stride, padding, dilation, ceil_mode );

    MAX_POOL2D_SUBCASE( case14c, array_ds_fb, kernel_size, stride, padding, dilation, ceil_mode );
    MAX_POOL2D_SUBCASE( case14c, array_ds_hb, kernel_size, stride, padding, dilation, ceil_mode );
    MAX_POOL2D_SUBCASE( case14c, array_ds_db, kernel_size, stride, padding, dilation, ceil_mode );

    MAX_POOL2D_SUBCASE( case14c, array_ls_fb, kernel_size, stride, padding, dilation, ceil_mode );
    MAX_POOL2D_SUBCASE( case14c, array_ls_hb, kernel_size, stride, padding, dilation, ceil_mode );
    MAX_POOL2D_SUBCASE( case14c, array_ls_db, kernel_size, stride, padding, dilation, ceil_mode );
    #endif
}

TEST_CASE("max_pool2d(case14d)" * doctest::test_suite("array::max_pool2d"))
{
    #if !defined(NMTOOLS_TESTING_GENERIC_NDARRAY)
    MAX_POOL2D_SUBCASE( case14d, array, kernel_size, stride, padding, dilation, ceil_mode );
    MAX_POOL2D_SUBCASE( case14d, array_a, kernel_size_a, stride, padding, dilation, ceil_mode );
    MAX_POOL2D_SUBCASE( case14d, array_f, kernel_size_f, stride, padding, dilation, ceil_mode );
    MAX_POOL2D_SUBCASE( case14d, array_h, kernel_size_h, stride, padding, dilation, ceil_mode );

    #else
    MAX_POOL2D_SUBCASE( case14d, array_cs_fb, kernel_size, stride, padding, dilation, ceil_mode );
    MAX_POOL2D_SUBCASE( case14d, array_cs_hb, kernel_size, stride, padding, dilation, ceil_mode );
    MAX_POOL2D_SUBCASE( case14d, array_cs_db, kernel_size, stride, padding, dilation, ceil_mode );

    MAX_POOL2D_SUBCASE( case14d, array_fs_fb, kernel_size, stride, padding, dilation, ceil_mode );
    MAX_POOL2D_SUBCASE( case14d, array_fs_hb, kernel_size, stride, padding, dilation, ceil_mode );
    MAX_POOL2D_SUBCASE( case14d, array_fs_db, kernel_size, stride, padding, dilation, ceil_mode );

    MAX_POOL2D_SUBCASE( case14d, array_hs_fb, kernel_size, stride, padding, dilation, ceil_mode );
    MAX_POOL2D_SUBCASE( case14d, array_hs_hb, kernel_size, stride, padding, dilation, ceil_mode );
    MAX_POOL2D_SUBCASE( case14d, array_hs_db, kernel_size, stride, padding, dilation, ceil_mode );

    MAX_POOL2D_SUBCASE( case14d, array_ds_fb, kernel_size, stride, padding, dilation, ceil_mode );
    MAX_POOL2D_SUBCASE( case14d, array_ds_hb, kernel_size, stride, padding, dilation, ceil_mode );
    MAX_POOL2D_SUBCASE( case14d, array_ds_db, kernel_size, stride, padding, dilation, ceil_mode );

    MAX_POOL2D_SUBCASE( case14d, array_ls_fb, kernel_size, stride, padding, dilation, ceil_mode );
    MAX_POOL2D_SUBCASE( case14d, array_ls_hb, kernel_size, stride, padding, dilation, ceil_mode );
    MAX_POOL2D_SUBCASE( case14d, array_ls_db, kernel_size, stride, padding, dilation, ceil_mode );
    #endif
}

TEST_CASE("max_pool2d(case15)" * doctest::test_suite("array::max_pool2d"))
{
    #if !defined(NMTOOLS_TESTING_GENERIC_NDARRAY)
    MAX_POOL2D_SUBCASE( case15, array, kernel_size, stride, padding, dilation, ceil_mode );
    MAX_POOL2D_SUBCASE( case15, array_a, kernel_size_a, stride_a, padding, dilation, ceil_mode );
    MAX_POOL2D_SUBCASE( case15, array_f, kernel_size_f, stride_f, padding, dilation, ceil_mode );
    MAX_POOL2D_SUBCASE( case15, array_h, kernel_size_h, stride_h, padding, dilation, ceil_mode );

    #else
    MAX_POOL2D_SUBCASE( case15, array_cs_fb, kernel_size, stride, padding, dilation, ceil_mode );
    MAX_POOL2D_SUBCASE( case15, array_cs_hb, kernel_size, stride, padding, dilation, ceil_mode );
    MAX_POOL2D_SUBCASE( case15, array_cs_db, kernel_size, stride, padding, dilation, ceil_mode );

    MAX_POOL2D_SUBCASE( case15, array_fs_fb, kernel_size, stride, padding, dilation, ceil_mode );
    MAX_POOL2D_SUBCASE( case15, array_fs_hb, kernel_size, stride, padding, dilation, ceil_mode );
    MAX_POOL2D_SUBCASE( case15, array_fs_db, kernel_size, stride, padding, dilation, ceil_mode );

    MAX_POOL2D_SUBCASE( case15, array_hs_fb, kernel_size, stride, padding, dilation, ceil_mode );
    MAX_POOL2D_SUBCASE( case15, array_hs_hb, kernel_size, stride, padding, dilation, ceil_mode );
    MAX_POOL2D_SUBCASE( case15, array_hs_db, kernel_size, stride, padding, dilation, ceil_mode );

    MAX_POOL2D_SUBCASE( case15, array_ds_fb, kernel_size, stride, padding, dilation, ceil_mode );
    MAX_POOL2D_SUBCASE( case15, array_ds_hb, kernel_size, stride, padding, dilation, ceil_mode );
    MAX_POOL2D_SUBCASE( case15, array_ds_db, kernel_size, stride, padding, dilation, ceil_mode );

    MAX_POOL2D_SUBCASE( case15, array_ls_fb, kernel_size, stride, padding, dilation, ceil_mode );
    MAX_POOL2D_SUBCASE( case15, array_ls_hb, kernel_size, stride, padding, dilation, ceil_mode );
    MAX_POOL2D_SUBCASE( case15, array_ls_db, kernel_size, stride, padding, dilation, ceil_mode );
    #endif
}

TEST_CASE("max_pool2d(case16)" * doctest::test_suite("array::max_pool2d"))
{
    #if !defined(NMTOOLS_TESTING_GENERIC_NDARRAY)
    MAX_POOL2D_SUBCASE( case16, array, kernel_size, stride, padding, dilation, ceil_mode );
    MAX_POOL2D_SUBCASE( case16, array_a, kernel_size_a, stride_a, padding, dilation, ceil_mode );
    MAX_POOL2D_SUBCASE( case16, array_f, kernel_size_f, stride_f, padding, dilation, ceil_mode );
    MAX_POOL2D_SUBCASE( case16, array_h, kernel_size_h, stride_h, padding, dilation, ceil_mode );

    #else
    MAX_POOL2D_SUBCASE( case16, array_cs_fb, kernel_size, stride, padding, dilation, ceil_mode );
    MAX_POOL2D_SUBCASE( case16, array_cs_hb, kernel_size, stride, padding, dilation, ceil_mode );
    MAX_POOL2D_SUBCASE( case16, array_cs_db, kernel_size, stride, padding, dilation, ceil_mode );

    MAX_POOL2D_SUBCASE( case16, array_fs_fb, kernel_size, stride, padding, dilation, ceil_mode );
    MAX_POOL2D_SUBCASE( case16, array_fs_hb, kernel_size, stride, padding, dilation, ceil_mode );
    MAX_POOL2D_SUBCASE( case16, array_fs_db, kernel_size, stride, padding, dilation, ceil_mode );

    MAX_POOL2D_SUBCASE( case16, array_hs_fb, kernel_size, stride, padding, dilation, ceil_mode );
    MAX_POOL2D_SUBCASE( case16, array_hs_hb, kernel_size, stride, padding, dilation, ceil_mode );
    MAX_POOL2D_SUBCASE( case16, array_hs_db, kernel_size, stride, padding, dilation, ceil_mode );

    MAX_POOL2D_SUBCASE( case16, array_ds_fb, kernel_size, stride, padding, dilation, ceil_mode );
    MAX_POOL2D_SUBCASE( case16, array_ds_hb, kernel_size, stride, padding, dilation, ceil_mode );
    MAX_POOL2D_SUBCASE( case16, array_ds_db, kernel_size, stride, padding, dilation, ceil_mode );

    MAX_POOL2D_SUBCASE( case16, array_ls_fb, kernel_size, stride, padding, dilation, ceil_mode );
    MAX_POOL2D_SUBCASE( case16, array_ls_hb, kernel_size, stride, padding, dilation, ceil_mode );
    MAX_POOL2D_SUBCASE( case16, array_ls_db, kernel_size, stride, padding, dilation, ceil_mode );
    #endif
}

TEST_CASE("max_pool2d(case17)" * doctest::test_suite("array::max_pool2d"))
{
    #if !defined(NMTOOLS_TESTING_GENERIC_NDARRAY)
    MAX_POOL2D_SUBCASE( case17, array, kernel_size, stride, padding, dilation, ceil_mode );
    MAX_POOL2D_SUBCASE( case17, array_a, kernel_size_a, stride_a, padding, dilation, ceil_mode );
    MAX_POOL2D_SUBCASE( case17, array_f, kernel_size_f, stride_f, padding, dilation, ceil_mode );
    MAX_POOL2D_SUBCASE( case17, array_h, kernel_size_h, stride_h, padding, dilation, ceil_mode );

    #else
    MAX_POOL2D_SUBCASE( case17, array_cs_fb, kernel_size, stride, padding, dilation, ceil_mode );
    MAX_POOL2D_SUBCASE( case17, array_cs_hb, kernel_size, stride, padding, dilation, ceil_mode );
    MAX_POOL2D_SUBCASE( case17, array_cs_db, kernel_size, stride, padding, dilation, ceil_mode );

    MAX_POOL2D_SUBCASE( case17, array_fs_fb, kernel_size, stride, padding, dilation, ceil_mode );
    MAX_POOL2D_SUBCASE( case17, array_fs_hb, kernel_size, stride, padding, dilation, ceil_mode );
    MAX_POOL2D_SUBCASE( case17, array_fs_db, kernel_size, stride, padding, dilation, ceil_mode );

    MAX_POOL2D_SUBCASE( case17, array_hs_fb, kernel_size, stride, padding, dilation, ceil_mode );
    MAX_POOL2D_SUBCASE( case17, array_hs_hb, kernel_size, stride, padding, dilation, ceil_mode );
    MAX_POOL2D_SUBCASE( case17, array_hs_db, kernel_size, stride, padding, dilation, ceil_mode );

    MAX_POOL2D_SUBCASE( case17, array_ds_fb, kernel_size, stride, padding, dilation, ceil_mode );
    MAX_POOL2D_SUBCASE( case17, array_ds_hb, kernel_size, stride, padding, dilation, ceil_mode );
    MAX_POOL2D_SUBCASE( case17, array_ds_db, kernel_size, stride, padding, dilation, ceil_mode );

    MAX_POOL2D_SUBCASE( case17, array_ls_fb, kernel_size, stride, padding, dilation, ceil_mode );
    MAX_POOL2D_SUBCASE( case17, array_ls_hb, kernel_size, stride, padding, dilation, ceil_mode );
    MAX_POOL2D_SUBCASE( case17, array_ls_db, kernel_size, stride, padding, dilation, ceil_mode );
    #endif
}

TEST_CASE("max_pool2d(case18)" * doctest::test_suite("array::max_pool2d"))
{
    #if !defined(NMTOOLS_TESTING_GENERIC_NDARRAY)
    MAX_POOL2D_SUBCASE( case18, array, kernel_size, stride, padding, dilation, ceil_mode );
    MAX_POOL2D_SUBCASE( case18, array_a, kernel_size_a, stride_a, padding, dilation, ceil_mode );
    MAX_POOL2D_SUBCASE( case18, array_f, kernel_size_f, stride_f, padding, dilation, ceil_mode );
    MAX_POOL2D_SUBCASE( case18, array_h, kernel_size_h, stride_h, padding, dilation, ceil_mode );

    #else
    MAX_POOL2D_SUBCASE( case18, array_cs_fb, kernel_size, stride, padding, dilation, ceil_mode );
    MAX_POOL2D_SUBCASE( case18, array_cs_hb, kernel_size, stride, padding, dilation, ceil_mode );
    MAX_POOL2D_SUBCASE( case18, array_cs_db, kernel_size, stride, padding, dilation, ceil_mode );

    MAX_POOL2D_SUBCASE( case18, array_fs_fb, kernel_size, stride, padding, dilation, ceil_mode );
    MAX_POOL2D_SUBCASE( case18, array_fs_hb, kernel_size, stride, padding, dilation, ceil_mode );
    MAX_POOL2D_SUBCASE( case18, array_fs_db, kernel_size, stride, padding, dilation, ceil_mode );

    MAX_POOL2D_SUBCASE( case18, array_hs_fb, kernel_size, stride, padding, dilation, ceil_mode );
    MAX_POOL2D_SUBCASE( case18, array_hs_hb, kernel_size, stride, padding, dilation, ceil_mode );
    MAX_POOL2D_SUBCASE( case18, array_hs_db, kernel_size, stride, padding, dilation, ceil_mode );

    MAX_POOL2D_SUBCASE( case18, array_ds_fb, kernel_size, stride, padding, dilation, ceil_mode );
    MAX_POOL2D_SUBCASE( case18, array_ds_hb, kernel_size, stride, padding, dilation, ceil_mode );
    MAX_POOL2D_SUBCASE( case18, array_ds_db, kernel_size, stride, padding, dilation, ceil_mode );

    MAX_POOL2D_SUBCASE( case18, array_ls_fb, kernel_size, stride, padding, dilation, ceil_mode );
    MAX_POOL2D_SUBCASE( case18, array_ls_hb, kernel_size, stride, padding, dilation, ceil_mode );
    MAX_POOL2D_SUBCASE( case18, array_ls_db, kernel_size, stride, padding, dilation, ceil_mode );
    #endif
}

TEST_CASE("max_pool2d(case19)" * doctest::test_suite("array::max_pool2d"))
{
    #if !defined(NMTOOLS_TESTING_GENERIC_NDARRAY)
    MAX_POOL2D_SUBCASE( case19, array, kernel_size, stride, padding, dilation, ceil_mode );
    MAX_POOL2D_SUBCASE( case19, array_a, kernel_size_a, stride_a, padding_a, dilation_a, ceil_mode );
    MAX_POOL2D_SUBCASE( case19, array_f, kernel_size_f, stride_f, padding_f, dilation_f, ceil_mode );
    MAX_POOL2D_SUBCASE( case19, array_h, kernel_size_h, stride_h, padding_h, dilation_h, ceil_mode );

    #else
    MAX_POOL2D_SUBCASE( case19, array_cs_fb, kernel_size, stride, padding, dilation, ceil_mode );
    MAX_POOL2D_SUBCASE( case19, array_cs_hb, kernel_size, stride, padding, dilation, ceil_mode );
    MAX_POOL2D_SUBCASE( case19, array_cs_db, kernel_size, stride, padding, dilation, ceil_mode );

    MAX_POOL2D_SUBCASE( case19, array_fs_fb, kernel_size, stride, padding, dilation, ceil_mode );
    MAX_POOL2D_SUBCASE( case19, array_fs_hb, kernel_size, stride, padding, dilation, ceil_mode );
    MAX_POOL2D_SUBCASE( case19, array_fs_db, kernel_size, stride, padding, dilation, ceil_mode );

    MAX_POOL2D_SUBCASE( case19, array_hs_fb, kernel_size, stride, padding, dilation, ceil_mode );
    MAX_POOL2D_SUBCASE( case19, array_hs_hb, kernel_size, stride, padding, dilation, ceil_mode );
    MAX_POOL2D_SUBCASE( case19, array_hs_db, kernel_size, stride, padding, dilation, ceil_mode );

    MAX_POOL2D_SUBCASE( case19, array_ds_fb, kernel_size, stride, padding, dilation, ceil_mode );
    MAX_POOL2D_SUBCASE( case19, array_ds_hb, kernel_size, stride, padding, dilation, ceil_mode );
    MAX_POOL2D_SUBCASE( case19, array_ds_db, kernel_size, stride, padding, dilation, ceil_mode );

    MAX_POOL2D_SUBCASE( case19, array_ls_fb, kernel_size, stride, padding, dilation, ceil_mode );
    MAX_POOL2D_SUBCASE( case19, array_ls_hb, kernel_size, stride, padding, dilation, ceil_mode );
    MAX_POOL2D_SUBCASE( case19, array_ls_db, kernel_size, stride, padding, dilation, ceil_mode );
    #endif
}

TEST_CASE("max_pool2d(case20)" * doctest::test_suite("array::max_pool2d"))
{
    #if !defined(NMTOOLS_TESTING_GENERIC_NDARRAY)
    MAX_POOL2D_SUBCASE( case20, array, kernel_size, stride, padding, dilation, ceil_mode );
    MAX_POOL2D_SUBCASE( case20, array_a, kernel_size_a, stride_a, padding_a, dilation_a, ceil_mode );
    MAX_POOL2D_SUBCASE( case20, array_f, kernel_size_f, stride_f, padding_f, dilation_f, ceil_mode );
    MAX_POOL2D_SUBCASE( case20, array_h, kernel_size_h, stride_h, padding_h, dilation_h, ceil_mode );

    #else
    MAX_POOL2D_SUBCASE( case20, array_cs_fb, kernel_size, stride, padding, dilation, ceil_mode );
    MAX_POOL2D_SUBCASE( case20, array_cs_hb, kernel_size, stride, padding, dilation, ceil_mode );
    MAX_POOL2D_SUBCASE( case20, array_cs_db, kernel_size, stride, padding, dilation, ceil_mode );

    MAX_POOL2D_SUBCASE( case20, array_fs_fb, kernel_size, stride, padding, dilation, ceil_mode );
    MAX_POOL2D_SUBCASE( case20, array_fs_hb, kernel_size, stride, padding, dilation, ceil_mode );
    MAX_POOL2D_SUBCASE( case20, array_fs_db, kernel_size, stride, padding, dilation, ceil_mode );

    MAX_POOL2D_SUBCASE( case20, array_hs_fb, kernel_size, stride, padding, dilation, ceil_mode );
    MAX_POOL2D_SUBCASE( case20, array_hs_hb, kernel_size, stride, padding, dilation, ceil_mode );
    MAX_POOL2D_SUBCASE( case20, array_hs_db, kernel_size, stride, padding, dilation, ceil_mode );

    MAX_POOL2D_SUBCASE( case20, array_ds_fb, kernel_size, stride, padding, dilation, ceil_mode );
    MAX_POOL2D_SUBCASE( case20, array_ds_hb, kernel_size, stride, padding, dilation, ceil_mode );
    MAX_POOL2D_SUBCASE( case20, array_ds_db, kernel_size, stride, padding, dilation, ceil_mode );

    MAX_POOL2D_SUBCASE( case20, array_ls_fb, kernel_size, stride, padding, dilation, ceil_mode );
    MAX_POOL2D_SUBCASE( case20, array_ls_hb, kernel_size, stride, padding, dilation, ceil_mode );
    MAX_POOL2D_SUBCASE( case20, array_ls_db, kernel_size, stride, padding, dilation, ceil_mode );
    #endif
}

TEST_CASE("max_pool2d(case21)" * doctest::test_suite("array::max_pool2d"))
{
    #if !defined(NMTOOLS_TESTING_GENERIC_NDARRAY)
    MAX_POOL2D_SUBCASE( case21, array, kernel_size, stride, padding, dilation, ceil_mode );
    MAX_POOL2D_SUBCASE( case21, array_a, kernel_size_a, stride_a, padding_a, dilation_a, ceil_mode );
    MAX_POOL2D_SUBCASE( case21, array_f, kernel_size_f, stride_f, padding_f, dilation_f, ceil_mode );
    MAX_POOL2D_SUBCASE( case21, array_h, kernel_size_h, stride_h, padding_h, dilation_h, ceil_mode );

    #else
    MAX_POOL2D_SUBCASE( case21, array_cs_fb, kernel_size, stride, padding, dilation, ceil_mode );
    MAX_POOL2D_SUBCASE( case21, array_cs_hb, kernel_size, stride, padding, dilation, ceil_mode );
    MAX_POOL2D_SUBCASE( case21, array_cs_db, kernel_size, stride, padding, dilation, ceil_mode );

    MAX_POOL2D_SUBCASE( case21, array_fs_fb, kernel_size, stride, padding, dilation, ceil_mode );
    MAX_POOL2D_SUBCASE( case21, array_fs_hb, kernel_size, stride, padding, dilation, ceil_mode );
    MAX_POOL2D_SUBCASE( case21, array_fs_db, kernel_size, stride, padding, dilation, ceil_mode );

    MAX_POOL2D_SUBCASE( case21, array_hs_fb, kernel_size, stride, padding, dilation, ceil_mode );
    MAX_POOL2D_SUBCASE( case21, array_hs_hb, kernel_size, stride, padding, dilation, ceil_mode );
    MAX_POOL2D_SUBCASE( case21, array_hs_db, kernel_size, stride, padding, dilation, ceil_mode );

    MAX_POOL2D_SUBCASE( case21, array_ds_fb, kernel_size, stride, padding, dilation, ceil_mode );
    MAX_POOL2D_SUBCASE( case21, array_ds_hb, kernel_size, stride, padding, dilation, ceil_mode );
    MAX_POOL2D_SUBCASE( case21, array_ds_db, kernel_size, stride, padding, dilation, ceil_mode );

    MAX_POOL2D_SUBCASE( case21, array_ls_fb, kernel_size, stride, padding, dilation, ceil_mode );
    MAX_POOL2D_SUBCASE( case21, array_ls_hb, kernel_size, stride, padding, dilation, ceil_mode );
    MAX_POOL2D_SUBCASE( case21, array_ls_db, kernel_size, stride, padding, dilation, ceil_mode );
    #endif
}

TEST_CASE("max_pool2d(case22)" * doctest::test_suite("array::max_pool2d"))
{
    #if !defined(NMTOOLS_TESTING_GENERIC_NDARRAY)
    MAX_POOL2D_SUBCASE( case22, array, kernel_size, stride, padding, dilation, ceil_mode );
    MAX_POOL2D_SUBCASE( case22, array_a, kernel_size_a, stride_a, padding_a, dilation_a, ceil_mode );
    MAX_POOL2D_SUBCASE( case22, array_f, kernel_size_f, stride_f, padding_f, dilation_f, ceil_mode );
    MAX_POOL2D_SUBCASE( case22, array_h, kernel_size_h, stride_h, padding_h, dilation_h, ceil_mode );

    #else
    MAX_POOL2D_SUBCASE( case22, array_cs_fb, kernel_size, stride, padding, dilation, ceil_mode );
    MAX_POOL2D_SUBCASE( case22, array_cs_hb, kernel_size, stride, padding, dilation, ceil_mode );
    MAX_POOL2D_SUBCASE( case22, array_cs_db, kernel_size, stride, padding, dilation, ceil_mode );

    MAX_POOL2D_SUBCASE( case22, array_fs_fb, kernel_size, stride, padding, dilation, ceil_mode );
    MAX_POOL2D_SUBCASE( case22, array_fs_hb, kernel_size, stride, padding, dilation, ceil_mode );
    MAX_POOL2D_SUBCASE( case22, array_fs_db, kernel_size, stride, padding, dilation, ceil_mode );

    MAX_POOL2D_SUBCASE( case22, array_hs_fb, kernel_size, stride, padding, dilation, ceil_mode );
    MAX_POOL2D_SUBCASE( case22, array_hs_hb, kernel_size, stride, padding, dilation, ceil_mode );
    MAX_POOL2D_SUBCASE( case22, array_hs_db, kernel_size, stride, padding, dilation, ceil_mode );

    MAX_POOL2D_SUBCASE( case22, array_ds_fb, kernel_size, stride, padding, dilation, ceil_mode );
    MAX_POOL2D_SUBCASE( case22, array_ds_hb, kernel_size, stride, padding, dilation, ceil_mode );
    MAX_POOL2D_SUBCASE( case22, array_ds_db, kernel_size, stride, padding, dilation, ceil_mode );

    MAX_POOL2D_SUBCASE( case22, array_ls_fb, kernel_size, stride, padding, dilation, ceil_mode );
    MAX_POOL2D_SUBCASE( case22, array_ls_hb, kernel_size, stride, padding, dilation, ceil_mode );
    MAX_POOL2D_SUBCASE( case22, array_ls_db, kernel_size, stride, padding, dilation, ceil_mode );
    #endif
}