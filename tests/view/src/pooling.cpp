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
namespace view = nmtools::view;

#define AVG_POOL2D_SUBCASE(case_name, ...) \
SUBCASE(#case_name) \
{ \
    NMTOOLS_TESTING_USE_CASE(array, avg_pool2d, case_name); \
    using namespace args; \
    auto result = view::avg_pool2d(__VA_ARGS__); \
    NMTOOLS_ASSERT_CLOSE( result, expect::result ); \
}

// TODO: fix
TEST_CASE("avg_pool2d(case1)" * doctest::test_suite("view::avg_pool2d") * doctest::skip())
{
    AVG_POOL2D_SUBCASE( case1, array, kernel_size, stride, padding, dilation, ceil_mode );
    AVG_POOL2D_SUBCASE( case1, array_a, kernel_size_a, stride_a, padding, dilation, ceil_mode );
    AVG_POOL2D_SUBCASE( case1, array_f, kernel_size_f, stride_f, padding, dilation, ceil_mode );
    AVG_POOL2D_SUBCASE( case1, array_h, kernel_size_h, stride_h, padding, dilation, ceil_mode );
}

// TODO: fix
TEST_CASE("avg_pool2d(case2)" * doctest::test_suite("view::avg_pool2d") * doctest::skip())
{
    AVG_POOL2D_SUBCASE( case2, array, kernel_size, stride, padding, dilation, ceil_mode );
    AVG_POOL2D_SUBCASE( case2, array_a, kernel_size_a, stride_a, padding, dilation, ceil_mode );
    AVG_POOL2D_SUBCASE( case2, array_f, kernel_size_f, stride_f, padding, dilation, ceil_mode );
    AVG_POOL2D_SUBCASE( case2, array_h, kernel_size_h, stride_h, padding, dilation, ceil_mode );
}

// TODO: fix
TEST_CASE("avg_pool2d(case3)" * doctest::test_suite("view::avg_pool2d") * doctest::skip())
{
    AVG_POOL2D_SUBCASE( case3, array, kernel_size, stride, padding, dilation, ceil_mode );
    AVG_POOL2D_SUBCASE( case3, array_a, kernel_size_a, stride_a, padding, dilation, ceil_mode );
    AVG_POOL2D_SUBCASE( case3, array_f, kernel_size_f, stride_f, padding, dilation, ceil_mode );
    AVG_POOL2D_SUBCASE( case3, array_h, kernel_size_h, stride_h, padding, dilation, ceil_mode );
}

// TODO: fix
TEST_CASE("avg_pool2d(case4)" * doctest::test_suite("view::avg_pool2d") * doctest::skip())
{
    AVG_POOL2D_SUBCASE( case4, array, kernel_size, stride, padding, dilation, ceil_mode );
    AVG_POOL2D_SUBCASE( case4, array_a, kernel_size_a, stride_a, padding, dilation, ceil_mode );
    AVG_POOL2D_SUBCASE( case4, array_f, kernel_size_f, stride_f, padding, dilation, ceil_mode );
    AVG_POOL2D_SUBCASE( case4, array_h, kernel_size_h, stride_h, padding, dilation, ceil_mode );
}

TEST_CASE("avg_pool2d(case5)" * doctest::test_suite("view::avg_pool2d"))
{
    AVG_POOL2D_SUBCASE( case5, array, kernel_size, stride, padding, dilation, ceil_mode );
    AVG_POOL2D_SUBCASE( case5, array_a, kernel_size_a, stride_a, padding, dilation, ceil_mode );
    AVG_POOL2D_SUBCASE( case5, array_f, kernel_size_f, stride_f, padding, dilation, ceil_mode );
    AVG_POOL2D_SUBCASE( case5, array_h, kernel_size_h, stride_h, padding, dilation, ceil_mode );
}

TEST_CASE("avg_pool2d(case6)" * doctest::test_suite("view::avg_pool2d"))
{
    AVG_POOL2D_SUBCASE( case6, array, kernel_size, stride, padding, dilation, ceil_mode );
    AVG_POOL2D_SUBCASE( case6, array_a, kernel_size_a, stride_a, padding, dilation, ceil_mode );
    AVG_POOL2D_SUBCASE( case6, array_f, kernel_size_f, stride_f, padding, dilation, ceil_mode );
    AVG_POOL2D_SUBCASE( case6, array_h, kernel_size_h, stride_h, padding, dilation, ceil_mode );
}

TEST_CASE("avg_pool2d(case7)" * doctest::test_suite("view::avg_pool2d"))
{
    AVG_POOL2D_SUBCASE( case7, array, kernel_size, stride, padding, dilation, ceil_mode );
    AVG_POOL2D_SUBCASE( case7, array_a, kernel_size_a, stride_a, padding, dilation, ceil_mode );
    AVG_POOL2D_SUBCASE( case7, array_f, kernel_size_f, stride_f, padding, dilation, ceil_mode );
    AVG_POOL2D_SUBCASE( case7, array_h, kernel_size_h, stride_h, padding, dilation, ceil_mode );
}


TEST_CASE("avg_pool2d(case8)" * doctest::test_suite("view::avg_pool2d"))
{
    AVG_POOL2D_SUBCASE( case8, array, kernel_size, stride, padding, dilation, ceil_mode );
    AVG_POOL2D_SUBCASE( case8, array_a, kernel_size_a, stride_a, padding, dilation, ceil_mode );
    AVG_POOL2D_SUBCASE( case8, array_f, kernel_size_f, stride_f, padding, dilation, ceil_mode );
    AVG_POOL2D_SUBCASE( case8, array_h, kernel_size_h, stride_h, padding, dilation, ceil_mode );
}


TEST_CASE("avg_pool2d(case9)" * doctest::test_suite("view::avg_pool2d"))
{
    AVG_POOL2D_SUBCASE( case9, array, kernel_size, stride, padding, dilation, ceil_mode );
    AVG_POOL2D_SUBCASE( case9, array_a, kernel_size_a, stride_a, padding, dilation, ceil_mode );
    AVG_POOL2D_SUBCASE( case9, array_f, kernel_size_f, stride_f, padding, dilation, ceil_mode );
    AVG_POOL2D_SUBCASE( case9, array_h, kernel_size_h, stride_h, padding, dilation, ceil_mode );
}


// TODO: fix
TEST_CASE("avg_pool2d(case10)" * doctest::test_suite("view::avg_pool2d") * doctest::skip())
{
    AVG_POOL2D_SUBCASE( case10, array, kernel_size, stride, padding, dilation, ceil_mode );
    AVG_POOL2D_SUBCASE( case10, array_a, kernel_size_a, stride_a, padding, dilation, ceil_mode );
    AVG_POOL2D_SUBCASE( case10, array_f, kernel_size_f, stride_f, padding, dilation, ceil_mode );
    AVG_POOL2D_SUBCASE( case10, array_h, kernel_size_h, stride_h, padding, dilation, ceil_mode );
}