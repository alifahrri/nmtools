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

#include "nmtools/array/pooling.hpp"
#include "nmtools/testing/doctest.hpp"
#include "nmtools/evaluator/hip.hpp"
#include "nmtools/testing/data/array/pooling.hpp"

namespace nm = nmtools;
namespace na = nmtools;

#define MAX_POOL2D_SUBCASE(case_name, ...) \
SUBCASE(#case_name) \
{ \
    NMTOOLS_TESTING_USE_CASE(array, max_pool2d, case_name); \
    using namespace args; \
    auto result = na::max_pool2d(__VA_ARGS__, na::hip::default_context()); \
    auto expect = na::max_pool2d(__VA_ARGS__); \
    NMTOOLS_ASSERT_EQUAL( nm::shape(result), nm::shape(expect) ); \
    NMTOOLS_ASSERT_CLOSE( result, expect ); \
}

#define AVG_POOL2D_SUBCASE(case_name, ...) \
SUBCASE(#case_name) \
{ \
    NMTOOLS_TESTING_USE_CASE(array, avg_pool2d, case_name); \
    using namespace args; \
    auto result = na::avg_pool2d(__VA_ARGS__, na::hip::default_context()); \
    auto expect = na::avg_pool2d(__VA_ARGS__); \
    NMTOOLS_ASSERT_EQUAL( nm::shape(result), nm::shape(expect) ); \
    NMTOOLS_ASSERT_CLOSE( result, expect ); \
}

TEST_CASE("max_pool2d(case1)" * doctest::test_suite("array::max_pool2d"))
{
    // MAX_POOL2D_SUBCASE(case1, array, kernel_size, stride, padding, dilation, ceil_mode);
    // MAX_POOL2D_SUBCASE(case1, array_a, kernel_size, stride, padding, dilation, ceil_mode);
    // MAX_POOL2D_SUBCASE(case1, array_f, kernel_size, stride, padding, dilation, ceil_mode);
    // MAX_POOL2D_SUBCASE(case1, array_h, kernel_size, stride, padding, dilation, ceil_mode);
    // MAX_POOL2D_SUBCASE(case1, array_d, kernel_size, stride, padding, dilation, ceil_mode);

    // MAX_POOL2D_SUBCASE(case1, array_cs_fb, kernel_size, stride, padding, dilation, ceil_mode);
    // MAX_POOL2D_SUBCASE(case1, array_cs_hb, kernel_size, stride, padding, dilation, ceil_mode);
    // MAX_POOL2D_SUBCASE(case1, array_cs_db, kernel_size, stride, padding, dilation, ceil_mode);

    MAX_POOL2D_SUBCASE(case1, array_fs_fb, kernel_size, stride, padding, dilation, ceil_mode);
    MAX_POOL2D_SUBCASE(case1, array_fs_hb, kernel_size, stride, padding, dilation, ceil_mode);
    MAX_POOL2D_SUBCASE(case1, array_fs_db, kernel_size, stride, padding, dilation, ceil_mode);

    MAX_POOL2D_SUBCASE(case1, array_hs_fb, kernel_size, stride, padding, dilation, ceil_mode);
    MAX_POOL2D_SUBCASE(case1, array_hs_hb, kernel_size, stride, padding, dilation, ceil_mode);
    MAX_POOL2D_SUBCASE(case1, array_hs_db, kernel_size, stride, padding, dilation, ceil_mode);

    // MAX_POOL2D_SUBCASE(case1, array_ls_fb, kernel_size, stride, padding, dilation, ceil_mode);
    // MAX_POOL2D_SUBCASE(case1, array_ls_hb, kernel_size, stride, padding, dilation, ceil_mode);
    // MAX_POOL2D_SUBCASE(case1, array_ls_db, kernel_size, stride, padding, dilation, ceil_mode);
}

TEST_CASE("max_pool2d(case1)" * doctest::test_suite("array::max_pool2d") * doctest::skip())
{
    MAX_POOL2D_SUBCASE(case1, array_ds_fb, kernel_size, stride, padding, dilation, ceil_mode);
    MAX_POOL2D_SUBCASE(case1, array_ds_hb, kernel_size, stride, padding, dilation, ceil_mode);
    MAX_POOL2D_SUBCASE(case1, array_ds_db, kernel_size, stride, padding, dilation, ceil_mode);
}

TEST_CASE("max_pool2d(case2)" * doctest::test_suite("array::max_pool2d"))
{
    // MAX_POOL2D_SUBCASE(case2, array, kernel_size, stride, padding, dilation, ceil_mode);
    // MAX_POOL2D_SUBCASE(case2, array_a, kernel_size, stride, padding, dilation, ceil_mode);
    // MAX_POOL2D_SUBCASE(case2, array_f, kernel_size, stride, padding, dilation, ceil_mode);
    // MAX_POOL2D_SUBCASE(case2, array_h, kernel_size, stride, padding, dilation, ceil_mode);
    // MAX_POOL2D_SUBCASE(case2, array_d, kernel_size, stride, padding, dilation, ceil_mode);

    // MAX_POOL2D_SUBCASE(case2, array_cs_fb, kernel_size, stride, padding, dilation, ceil_mode);
    // MAX_POOL2D_SUBCASE(case2, array_cs_hb, kernel_size, stride, padding, dilation, ceil_mode);
    // MAX_POOL2D_SUBCASE(case2, array_cs_db, kernel_size, stride, padding, dilation, ceil_mode);

    MAX_POOL2D_SUBCASE(case2, array_fs_fb, kernel_size, stride, padding, dilation, ceil_mode);
    MAX_POOL2D_SUBCASE(case2, array_fs_hb, kernel_size, stride, padding, dilation, ceil_mode);
    MAX_POOL2D_SUBCASE(case2, array_fs_db, kernel_size, stride, padding, dilation, ceil_mode);

    MAX_POOL2D_SUBCASE(case2, array_hs_fb, kernel_size, stride, padding, dilation, ceil_mode);
    MAX_POOL2D_SUBCASE(case2, array_hs_hb, kernel_size, stride, padding, dilation, ceil_mode);
    MAX_POOL2D_SUBCASE(case2, array_hs_db, kernel_size, stride, padding, dilation, ceil_mode);

    // MAX_POOL2D_SUBCASE(case2, array_ls_fb, kernel_size, stride, padding, dilation, ceil_mode);
    // MAX_POOL2D_SUBCASE(case2, array_ls_hb, kernel_size, stride, padding, dilation, ceil_mode);
    // MAX_POOL2D_SUBCASE(case2, array_ls_db, kernel_size, stride, padding, dilation, ceil_mode);
}

TEST_CASE("max_pool2d(case2)" * doctest::test_suite("array::max_pool2d") * doctest::skip())
{
    MAX_POOL2D_SUBCASE(case2, array_ds_fb, kernel_size, stride, padding, dilation, ceil_mode);
    MAX_POOL2D_SUBCASE(case2, array_ds_hb, kernel_size, stride, padding, dilation, ceil_mode);
    MAX_POOL2D_SUBCASE(case2, array_ds_db, kernel_size, stride, padding, dilation, ceil_mode);
}

TEST_CASE("max_pool2d(case3)" * doctest::test_suite("array::max_pool2d"))
{
    // MAX_POOL2D_SUBCASE(case3, array, kernel_size, stride, padding, dilation, ceil_mode);
    // MAX_POOL2D_SUBCASE(case3, array_a, kernel_size, stride, padding, dilation, ceil_mode);
    // MAX_POOL2D_SUBCASE(case3, array_f, kernel_size, stride, padding, dilation, ceil_mode);
    // MAX_POOL2D_SUBCASE(case3, array_h, kernel_size, stride, padding, dilation, ceil_mode);
    // MAX_POOL2D_SUBCASE(case3, array_d, kernel_size, stride, padding, dilation, ceil_mode);

    // MAX_POOL2D_SUBCASE(case3, array_cs_fb, kernel_size, stride, padding, dilation, ceil_mode);
    // MAX_POOL2D_SUBCASE(case3, array_cs_hb, kernel_size, stride, padding, dilation, ceil_mode);
    // MAX_POOL2D_SUBCASE(case3, array_cs_db, kernel_size, stride, padding, dilation, ceil_mode);

    MAX_POOL2D_SUBCASE(case3, array_fs_fb, kernel_size, stride, padding, dilation, ceil_mode);
    MAX_POOL2D_SUBCASE(case3, array_fs_hb, kernel_size, stride, padding, dilation, ceil_mode);
    MAX_POOL2D_SUBCASE(case3, array_fs_db, kernel_size, stride, padding, dilation, ceil_mode);

    MAX_POOL2D_SUBCASE(case3, array_hs_fb, kernel_size, stride, padding, dilation, ceil_mode);
    MAX_POOL2D_SUBCASE(case3, array_hs_hb, kernel_size, stride, padding, dilation, ceil_mode);
    MAX_POOL2D_SUBCASE(case3, array_hs_db, kernel_size, stride, padding, dilation, ceil_mode);

    // MAX_POOL2D_SUBCASE(case3, array_ls_fb, kernel_size, stride, padding, dilation, ceil_mode);
    // MAX_POOL2D_SUBCASE(case3, array_ls_hb, kernel_size, stride, padding, dilation, ceil_mode);
    // MAX_POOL2D_SUBCASE(case3, array_ls_db, kernel_size, stride, padding, dilation, ceil_mode);
}

TEST_CASE("max_pool2d(case3)" * doctest::test_suite("array::max_pool2d") * doctest::skip())
{
    MAX_POOL2D_SUBCASE(case3, array_ds_fb, kernel_size, stride, padding, dilation, ceil_mode);
    MAX_POOL2D_SUBCASE(case3, array_ds_hb, kernel_size, stride, padding, dilation, ceil_mode);
    MAX_POOL2D_SUBCASE(case3, array_ds_db, kernel_size, stride, padding, dilation, ceil_mode);
}

TEST_CASE("max_pool2d(case4)" * doctest::test_suite("array::max_pool2d"))
{
    // MAX_POOL2D_SUBCASE(case4, array, kernel_size, stride, padding, dilation, ceil_mode);
    // MAX_POOL2D_SUBCASE(case4, array_a, kernel_size, stride, padding, dilation, ceil_mode);
    // MAX_POOL2D_SUBCASE(case4, array_f, kernel_size, stride, padding, dilation, ceil_mode);
    // MAX_POOL2D_SUBCASE(case4, array_h, kernel_size, stride, padding, dilation, ceil_mode);
    // MAX_POOL2D_SUBCASE(case4, array_d, kernel_size, stride, padding, dilation, ceil_mode);

    // MAX_POOL2D_SUBCASE(case4, array_cs_fb, kernel_size, stride, padding, dilation, ceil_mode);
    // MAX_POOL2D_SUBCASE(case4, array_cs_hb, kernel_size, stride, padding, dilation, ceil_mode);
    // MAX_POOL2D_SUBCASE(case4, array_cs_db, kernel_size, stride, padding, dilation, ceil_mode);

    MAX_POOL2D_SUBCASE(case4, array_fs_fb, kernel_size, stride, padding, dilation, ceil_mode);
    MAX_POOL2D_SUBCASE(case4, array_fs_hb, kernel_size, stride, padding, dilation, ceil_mode);
    MAX_POOL2D_SUBCASE(case4, array_fs_db, kernel_size, stride, padding, dilation, ceil_mode);

    MAX_POOL2D_SUBCASE(case4, array_hs_fb, kernel_size, stride, padding, dilation, ceil_mode);
    MAX_POOL2D_SUBCASE(case4, array_hs_hb, kernel_size, stride, padding, dilation, ceil_mode);
    MAX_POOL2D_SUBCASE(case4, array_hs_db, kernel_size, stride, padding, dilation, ceil_mode);

    // MAX_POOL2D_SUBCASE(case4, array_ls_fb, kernel_size, stride, padding, dilation, ceil_mode);
    // MAX_POOL2D_SUBCASE(case4, array_ls_hb, kernel_size, stride, padding, dilation, ceil_mode);
    // MAX_POOL2D_SUBCASE(case4, array_ls_db, kernel_size, stride, padding, dilation, ceil_mode);
}

TEST_CASE("max_pool2d(case4)" * doctest::test_suite("array::max_pool2d") * doctest::skip())
{
    MAX_POOL2D_SUBCASE(case4, array_ds_fb, kernel_size, stride, padding, dilation, ceil_mode);
    MAX_POOL2D_SUBCASE(case4, array_ds_hb, kernel_size, stride, padding, dilation, ceil_mode);
    MAX_POOL2D_SUBCASE(case4, array_ds_db, kernel_size, stride, padding, dilation, ceil_mode);
}

TEST_CASE("max_pool2d(case5)" * doctest::test_suite("array::max_pool2d"))
{
    // MAX_POOL2D_SUBCASE(case5, array, kernel_size, stride, padding, dilation, ceil_mode);
    // MAX_POOL2D_SUBCASE(case5, array_a, kernel_size, stride, padding, dilation, ceil_mode);
    // MAX_POOL2D_SUBCASE(case5, array_f, kernel_size, stride, padding, dilation, ceil_mode);
    // MAX_POOL2D_SUBCASE(case5, array_h, kernel_size, stride, padding, dilation, ceil_mode);
    // MAX_POOL2D_SUBCASE(case5, array_d, kernel_size, stride, padding, dilation, ceil_mode);

    // MAX_POOL2D_SUBCASE(case5, array_cs_fb, kernel_size, stride, padding, dilation, ceil_mode);
    // MAX_POOL2D_SUBCASE(case5, array_cs_hb, kernel_size, stride, padding, dilation, ceil_mode);
    // MAX_POOL2D_SUBCASE(case5, array_cs_db, kernel_size, stride, padding, dilation, ceil_mode);

    MAX_POOL2D_SUBCASE(case5, array_fs_fb, kernel_size, stride, padding, dilation, ceil_mode);
    MAX_POOL2D_SUBCASE(case5, array_fs_hb, kernel_size, stride, padding, dilation, ceil_mode);
    MAX_POOL2D_SUBCASE(case5, array_fs_db, kernel_size, stride, padding, dilation, ceil_mode);

    MAX_POOL2D_SUBCASE(case5, array_hs_fb, kernel_size, stride, padding, dilation, ceil_mode);
    MAX_POOL2D_SUBCASE(case5, array_hs_hb, kernel_size, stride, padding, dilation, ceil_mode);
    MAX_POOL2D_SUBCASE(case5, array_hs_db, kernel_size, stride, padding, dilation, ceil_mode);

    // MAX_POOL2D_SUBCASE(case5, array_ls_fb, kernel_size, stride, padding, dilation, ceil_mode);
    // MAX_POOL2D_SUBCASE(case5, array_ls_hb, kernel_size, stride, padding, dilation, ceil_mode);
    // MAX_POOL2D_SUBCASE(case5, array_ls_db, kernel_size, stride, padding, dilation, ceil_mode);
}

TEST_CASE("max_pool2d(case5)" * doctest::test_suite("array::max_pool2d") * doctest::skip())
{
    MAX_POOL2D_SUBCASE(case5, array_ds_fb, kernel_size, stride, padding, dilation, ceil_mode);
    MAX_POOL2D_SUBCASE(case5, array_ds_hb, kernel_size, stride, padding, dilation, ceil_mode);
    MAX_POOL2D_SUBCASE(case5, array_ds_db, kernel_size, stride, padding, dilation, ceil_mode);
}

TEST_CASE("max_pool2d(case6)" * doctest::test_suite("array::max_pool2d"))
{
    // MAX_POOL2D_SUBCASE(case6, array, kernel_size, stride, padding, dilation, ceil_mode);
    // MAX_POOL2D_SUBCASE(case6, array_a, kernel_size, stride, padding, dilation, ceil_mode);
    // MAX_POOL2D_SUBCASE(case6, array_f, kernel_size, stride, padding, dilation, ceil_mode);
    // MAX_POOL2D_SUBCASE(case6, array_h, kernel_size, stride, padding, dilation, ceil_mode);
    // MAX_POOL2D_SUBCASE(case6, array_d, kernel_size, stride, padding, dilation, ceil_mode);

    // MAX_POOL2D_SUBCASE(case6, array_cs_fb, kernel_size, stride, padding, dilation, ceil_mode);
    // MAX_POOL2D_SUBCASE(case6, array_cs_hb, kernel_size, stride, padding, dilation, ceil_mode);
    // MAX_POOL2D_SUBCASE(case6, array_cs_db, kernel_size, stride, padding, dilation, ceil_mode);

    MAX_POOL2D_SUBCASE(case6, array_fs_fb, kernel_size, stride, padding, dilation, ceil_mode);
    MAX_POOL2D_SUBCASE(case6, array_fs_hb, kernel_size, stride, padding, dilation, ceil_mode);
    MAX_POOL2D_SUBCASE(case6, array_fs_db, kernel_size, stride, padding, dilation, ceil_mode);

    MAX_POOL2D_SUBCASE(case6, array_hs_fb, kernel_size, stride, padding, dilation, ceil_mode);
    MAX_POOL2D_SUBCASE(case6, array_hs_hb, kernel_size, stride, padding, dilation, ceil_mode);
    MAX_POOL2D_SUBCASE(case6, array_hs_db, kernel_size, stride, padding, dilation, ceil_mode);

    // MAX_POOL2D_SUBCASE(case6, array_ls_fb, kernel_size, stride, padding, dilation, ceil_mode);
    // MAX_POOL2D_SUBCASE(case6, array_ls_hb, kernel_size, stride, padding, dilation, ceil_mode);
    // MAX_POOL2D_SUBCASE(case6, array_ls_db, kernel_size, stride, padding, dilation, ceil_mode);
}

TEST_CASE("max_pool2d(case6)" * doctest::test_suite("array::max_pool2d") * doctest::skip())
{
    MAX_POOL2D_SUBCASE(case6, array_ds_fb, kernel_size, stride, padding, dilation, ceil_mode);
    MAX_POOL2D_SUBCASE(case6, array_ds_hb, kernel_size, stride, padding, dilation, ceil_mode);
    MAX_POOL2D_SUBCASE(case6, array_ds_db, kernel_size, stride, padding, dilation, ceil_mode);
}

TEST_CASE("max_pool2d(case7)" * doctest::test_suite("array::max_pool2d"))
{
    // MAX_POOL2D_SUBCASE(case7, array, kernel_size, stride, padding, dilation, ceil_mode);
    // MAX_POOL2D_SUBCASE(case7, array_a, kernel_size, stride, padding, dilation, ceil_mode);
    // MAX_POOL2D_SUBCASE(case7, array_f, kernel_size, stride, padding, dilation, ceil_mode);
    // MAX_POOL2D_SUBCASE(case7, array_h, kernel_size, stride, padding, dilation, ceil_mode);
    // MAX_POOL2D_SUBCASE(case7, array_d, kernel_size, stride, padding, dilation, ceil_mode);

    // MAX_POOL2D_SUBCASE(case7, array_cs_fb, kernel_size, stride, padding, dilation, ceil_mode);
    // MAX_POOL2D_SUBCASE(case7, array_cs_hb, kernel_size, stride, padding, dilation, ceil_mode);
    // MAX_POOL2D_SUBCASE(case7, array_cs_db, kernel_size, stride, padding, dilation, ceil_mode);

    MAX_POOL2D_SUBCASE(case7, array_fs_fb, kernel_size, stride, padding, dilation, ceil_mode);
    MAX_POOL2D_SUBCASE(case7, array_fs_hb, kernel_size, stride, padding, dilation, ceil_mode);
    MAX_POOL2D_SUBCASE(case7, array_fs_db, kernel_size, stride, padding, dilation, ceil_mode);

    MAX_POOL2D_SUBCASE(case7, array_hs_fb, kernel_size, stride, padding, dilation, ceil_mode);
    MAX_POOL2D_SUBCASE(case7, array_hs_hb, kernel_size, stride, padding, dilation, ceil_mode);
    MAX_POOL2D_SUBCASE(case7, array_hs_db, kernel_size, stride, padding, dilation, ceil_mode);

    // MAX_POOL2D_SUBCASE(case7, array_ls_fb, kernel_size, stride, padding, dilation, ceil_mode);
    // MAX_POOL2D_SUBCASE(case7, array_ls_hb, kernel_size, stride, padding, dilation, ceil_mode);
    // MAX_POOL2D_SUBCASE(case7, array_ls_db, kernel_size, stride, padding, dilation, ceil_mode);
}

TEST_CASE("max_pool2d(case7)" * doctest::test_suite("array::max_pool2d") * doctest::skip())
{
    MAX_POOL2D_SUBCASE(case7, array_ds_fb, kernel_size, stride, padding, dilation, ceil_mode);
    MAX_POOL2D_SUBCASE(case7, array_ds_hb, kernel_size, stride, padding, dilation, ceil_mode);
    MAX_POOL2D_SUBCASE(case7, array_ds_db, kernel_size, stride, padding, dilation, ceil_mode);
}

TEST_CASE("max_pool2d(case8)" * doctest::test_suite("array::max_pool2d"))
{
    // MAX_POOL2D_SUBCASE(case8, array, kernel_size, stride, padding, dilation, ceil_mode);
    // MAX_POOL2D_SUBCASE(case8, array_a, kernel_size, stride, padding, dilation, ceil_mode);
    // MAX_POOL2D_SUBCASE(case8, array_f, kernel_size, stride, padding, dilation, ceil_mode);
    // MAX_POOL2D_SUBCASE(case8, array_h, kernel_size, stride, padding, dilation, ceil_mode);
    // MAX_POOL2D_SUBCASE(case8, array_d, kernel_size, stride, padding, dilation, ceil_mode);

    // MAX_POOL2D_SUBCASE(case8, array_cs_fb, kernel_size, stride, padding, dilation, ceil_mode);
    // MAX_POOL2D_SUBCASE(case8, array_cs_hb, kernel_size, stride, padding, dilation, ceil_mode);
    // MAX_POOL2D_SUBCASE(case8, array_cs_db, kernel_size, stride, padding, dilation, ceil_mode);

    MAX_POOL2D_SUBCASE(case8, array_fs_fb, kernel_size, stride, padding, dilation, ceil_mode);
    MAX_POOL2D_SUBCASE(case8, array_fs_hb, kernel_size, stride, padding, dilation, ceil_mode);
    MAX_POOL2D_SUBCASE(case8, array_fs_db, kernel_size, stride, padding, dilation, ceil_mode);

    MAX_POOL2D_SUBCASE(case8, array_hs_fb, kernel_size, stride, padding, dilation, ceil_mode);
    MAX_POOL2D_SUBCASE(case8, array_hs_hb, kernel_size, stride, padding, dilation, ceil_mode);
    MAX_POOL2D_SUBCASE(case8, array_hs_db, kernel_size, stride, padding, dilation, ceil_mode);

    // MAX_POOL2D_SUBCASE(case8, array_ls_fb, kernel_size, stride, padding, dilation, ceil_mode);
    // MAX_POOL2D_SUBCASE(case8, array_ls_hb, kernel_size, stride, padding, dilation, ceil_mode);
    // MAX_POOL2D_SUBCASE(case8, array_ls_db, kernel_size, stride, padding, dilation, ceil_mode);
}

TEST_CASE("max_pool2d(case8)" * doctest::test_suite("array::max_pool2d") * doctest::skip())
{
    MAX_POOL2D_SUBCASE(case8, array_ds_fb, kernel_size, stride, padding, dilation, ceil_mode);
    MAX_POOL2D_SUBCASE(case8, array_ds_hb, kernel_size, stride, padding, dilation, ceil_mode);
    MAX_POOL2D_SUBCASE(case8, array_ds_db, kernel_size, stride, padding, dilation, ceil_mode);
}

TEST_CASE("max_pool2d(case9)" * doctest::test_suite("array::max_pool2d"))
{
    // MAX_POOL2D_SUBCASE(case9, array, kernel_size, stride, padding, dilation, ceil_mode);
    // MAX_POOL2D_SUBCASE(case9, array_a, kernel_size, stride, padding, dilation, ceil_mode);
    // MAX_POOL2D_SUBCASE(case9, array_f, kernel_size, stride, padding, dilation, ceil_mode);
    // MAX_POOL2D_SUBCASE(case9, array_h, kernel_size, stride, padding, dilation, ceil_mode);
    // MAX_POOL2D_SUBCASE(case9, array_d, kernel_size, stride, padding, dilation, ceil_mode);

    // MAX_POOL2D_SUBCASE(case9, array_cs_fb, kernel_size, stride, padding, dilation, ceil_mode);
    // MAX_POOL2D_SUBCASE(case9, array_cs_hb, kernel_size, stride, padding, dilation, ceil_mode);
    // MAX_POOL2D_SUBCASE(case9, array_cs_db, kernel_size, stride, padding, dilation, ceil_mode);

    MAX_POOL2D_SUBCASE(case9, array_fs_fb, kernel_size, stride, padding, dilation, ceil_mode);
    MAX_POOL2D_SUBCASE(case9, array_fs_hb, kernel_size, stride, padding, dilation, ceil_mode);
    MAX_POOL2D_SUBCASE(case9, array_fs_db, kernel_size, stride, padding, dilation, ceil_mode);

    MAX_POOL2D_SUBCASE(case9, array_hs_fb, kernel_size, stride, padding, dilation, ceil_mode);
    MAX_POOL2D_SUBCASE(case9, array_hs_hb, kernel_size, stride, padding, dilation, ceil_mode);
    MAX_POOL2D_SUBCASE(case9, array_hs_db, kernel_size, stride, padding, dilation, ceil_mode);

    // MAX_POOL2D_SUBCASE(case9, array_ls_fb, kernel_size, stride, padding, dilation, ceil_mode);
    // MAX_POOL2D_SUBCASE(case9, array_ls_hb, kernel_size, stride, padding, dilation, ceil_mode);
    // MAX_POOL2D_SUBCASE(case9, array_ls_db, kernel_size, stride, padding, dilation, ceil_mode);
}

TEST_CASE("max_pool2d(case9)" * doctest::test_suite("array::max_pool2d") * doctest::skip())
{
    MAX_POOL2D_SUBCASE(case9, array_ds_fb, kernel_size, stride, padding, dilation, ceil_mode);
    MAX_POOL2D_SUBCASE(case9, array_ds_hb, kernel_size, stride, padding, dilation, ceil_mode);
    MAX_POOL2D_SUBCASE(case9, array_ds_db, kernel_size, stride, padding, dilation, ceil_mode);
}

TEST_CASE("max_pool2d(case10)" * doctest::test_suite("array::max_pool2d"))
{
    // MAX_POOL2D_SUBCASE(case10, array, kernel_size, stride, padding, dilation, ceil_mode);
    // MAX_POOL2D_SUBCASE(case10, array_a, kernel_size, stride, padding, dilation, ceil_mode);
    // MAX_POOL2D_SUBCASE(case10, array_f, kernel_size, stride, padding, dilation, ceil_mode);
    // MAX_POOL2D_SUBCASE(case10, array_h, kernel_size, stride, padding, dilation, ceil_mode);
    // MAX_POOL2D_SUBCASE(case10, array_d, kernel_size, stride, padding, dilation, ceil_mode);

    // MAX_POOL2D_SUBCASE(case10, array_cs_fb, kernel_size, stride, padding, dilation, ceil_mode);
    // MAX_POOL2D_SUBCASE(case10, array_cs_hb, kernel_size, stride, padding, dilation, ceil_mode);
    // MAX_POOL2D_SUBCASE(case10, array_cs_db, kernel_size, stride, padding, dilation, ceil_mode);

    MAX_POOL2D_SUBCASE(case10, array_fs_fb, kernel_size, stride, padding, dilation, ceil_mode);
    MAX_POOL2D_SUBCASE(case10, array_fs_hb, kernel_size, stride, padding, dilation, ceil_mode);
    MAX_POOL2D_SUBCASE(case10, array_fs_db, kernel_size, stride, padding, dilation, ceil_mode);

    MAX_POOL2D_SUBCASE(case10, array_hs_fb, kernel_size, stride, padding, dilation, ceil_mode);
    MAX_POOL2D_SUBCASE(case10, array_hs_hb, kernel_size, stride, padding, dilation, ceil_mode);
    MAX_POOL2D_SUBCASE(case10, array_hs_db, kernel_size, stride, padding, dilation, ceil_mode);

    // MAX_POOL2D_SUBCASE(case10, array_ls_fb, kernel_size, stride, padding, dilation, ceil_mode);
    // MAX_POOL2D_SUBCASE(case10, array_ls_hb, kernel_size, stride, padding, dilation, ceil_mode);
    // MAX_POOL2D_SUBCASE(case10, array_ls_db, kernel_size, stride, padding, dilation, ceil_mode);
}

TEST_CASE("max_pool2d(case10)" * doctest::test_suite("array::max_pool2d") * doctest::skip())
{
    MAX_POOL2D_SUBCASE(case10, array_ds_fb, kernel_size, stride, padding, dilation, ceil_mode);
    MAX_POOL2D_SUBCASE(case10, array_ds_hb, kernel_size, stride, padding, dilation, ceil_mode);
    MAX_POOL2D_SUBCASE(case10, array_ds_db, kernel_size, stride, padding, dilation, ceil_mode);
}

//////////////////////////////////////////////////////////////////////////////////

TEST_CASE("avg_pool2d(case1)" * doctest::test_suite("array::avg_pool2d"))
{
    // AVG_POOL2D_SUBCASE(case1, array, kernel_size, stride, padding, dilation, ceil_mode);
    // AVG_POOL2D_SUBCASE(case1, array_a, kernel_size, stride, padding, dilation, ceil_mode);
    // AVG_POOL2D_SUBCASE(case1, array_f, kernel_size, stride, padding, dilation, ceil_mode);
    // AVG_POOL2D_SUBCASE(case1, array_h, kernel_size, stride, padding, dilation, ceil_mode);
    // AVG_POOL2D_SUBCASE(case1, array_d, kernel_size, stride, padding, dilation, ceil_mode);

    // AVG_POOL2D_SUBCASE(case1, array_cs_fb, kernel_size, stride, padding, dilation, ceil_mode);
    // AVG_POOL2D_SUBCASE(case1, array_cs_hb, kernel_size, stride, padding, dilation, ceil_mode);
    // AVG_POOL2D_SUBCASE(case1, array_cs_db, kernel_size, stride, padding, dilation, ceil_mode);

    AVG_POOL2D_SUBCASE(case1, array_fs_fb, kernel_size, stride, padding, dilation, ceil_mode);
    AVG_POOL2D_SUBCASE(case1, array_fs_hb, kernel_size, stride, padding, dilation, ceil_mode);
    AVG_POOL2D_SUBCASE(case1, array_fs_db, kernel_size, stride, padding, dilation, ceil_mode);

    AVG_POOL2D_SUBCASE(case1, array_hs_fb, kernel_size, stride, padding, dilation, ceil_mode);
    AVG_POOL2D_SUBCASE(case1, array_hs_hb, kernel_size, stride, padding, dilation, ceil_mode);
    AVG_POOL2D_SUBCASE(case1, array_hs_db, kernel_size, stride, padding, dilation, ceil_mode);

    // AVG_POOL2D_SUBCASE(case1, array_ls_fb, kernel_size, stride, padding, dilation, ceil_mode);
    // AVG_POOL2D_SUBCASE(case1, array_ls_hb, kernel_size, stride, padding, dilation, ceil_mode);
    // AVG_POOL2D_SUBCASE(case1, array_ls_db, kernel_size, stride, padding, dilation, ceil_mode);
}

TEST_CASE("avg_pool2d(case1)" * doctest::test_suite("array::avg_pool2d") * doctest::skip())
{
    AVG_POOL2D_SUBCASE(case1, array_ds_fb, kernel_size, stride, padding, dilation, ceil_mode);
    AVG_POOL2D_SUBCASE(case1, array_ds_hb, kernel_size, stride, padding, dilation, ceil_mode);
    AVG_POOL2D_SUBCASE(case1, array_ds_db, kernel_size, stride, padding, dilation, ceil_mode);
}

TEST_CASE("avg_pool2d(case2)" * doctest::test_suite("array::avg_pool2d"))
{
    // AVG_POOL2D_SUBCASE(case2, array, kernel_size, stride, padding, dilation, ceil_mode);
    // AVG_POOL2D_SUBCASE(case2, array_a, kernel_size, stride, padding, dilation, ceil_mode);
    // AVG_POOL2D_SUBCASE(case2, array_f, kernel_size, stride, padding, dilation, ceil_mode);
    // AVG_POOL2D_SUBCASE(case2, array_h, kernel_size, stride, padding, dilation, ceil_mode);
    // AVG_POOL2D_SUBCASE(case2, array_d, kernel_size, stride, padding, dilation, ceil_mode);

    // AVG_POOL2D_SUBCASE(case2, array_cs_fb, kernel_size, stride, padding, dilation, ceil_mode);
    // AVG_POOL2D_SUBCASE(case2, array_cs_hb, kernel_size, stride, padding, dilation, ceil_mode);
    // AVG_POOL2D_SUBCASE(case2, array_cs_db, kernel_size, stride, padding, dilation, ceil_mode);

    AVG_POOL2D_SUBCASE(case2, array_fs_fb, kernel_size, stride, padding, dilation, ceil_mode);
    AVG_POOL2D_SUBCASE(case2, array_fs_hb, kernel_size, stride, padding, dilation, ceil_mode);
    AVG_POOL2D_SUBCASE(case2, array_fs_db, kernel_size, stride, padding, dilation, ceil_mode);

    AVG_POOL2D_SUBCASE(case2, array_hs_fb, kernel_size, stride, padding, dilation, ceil_mode);
    AVG_POOL2D_SUBCASE(case2, array_hs_hb, kernel_size, stride, padding, dilation, ceil_mode);
    AVG_POOL2D_SUBCASE(case2, array_hs_db, kernel_size, stride, padding, dilation, ceil_mode);

    // AVG_POOL2D_SUBCASE(case2, array_ls_fb, kernel_size, stride, padding, dilation, ceil_mode);
    // AVG_POOL2D_SUBCASE(case2, array_ls_hb, kernel_size, stride, padding, dilation, ceil_mode);
    // AVG_POOL2D_SUBCASE(case2, array_ls_db, kernel_size, stride, padding, dilation, ceil_mode);
}

TEST_CASE("avg_pool2d(case2)" * doctest::test_suite("array::avg_pool2d") * doctest::skip())
{
    AVG_POOL2D_SUBCASE(case2, array_ds_fb, kernel_size, stride, padding, dilation, ceil_mode);
    AVG_POOL2D_SUBCASE(case2, array_ds_hb, kernel_size, stride, padding, dilation, ceil_mode);
    AVG_POOL2D_SUBCASE(case2, array_ds_db, kernel_size, stride, padding, dilation, ceil_mode);
}

TEST_CASE("avg_pool2d(case3)" * doctest::test_suite("array::avg_pool2d"))
{
    // AVG_POOL2D_SUBCASE(case3, array, kernel_size, stride, padding, dilation, ceil_mode);
    // AVG_POOL2D_SUBCASE(case3, array_a, kernel_size, stride, padding, dilation, ceil_mode);
    // AVG_POOL2D_SUBCASE(case3, array_f, kernel_size, stride, padding, dilation, ceil_mode);
    // AVG_POOL2D_SUBCASE(case3, array_h, kernel_size, stride, padding, dilation, ceil_mode);
    // AVG_POOL2D_SUBCASE(case3, array_d, kernel_size, stride, padding, dilation, ceil_mode);

    // AVG_POOL2D_SUBCASE(case3, array_cs_fb, kernel_size, stride, padding, dilation, ceil_mode);
    // AVG_POOL2D_SUBCASE(case3, array_cs_hb, kernel_size, stride, padding, dilation, ceil_mode);
    // AVG_POOL2D_SUBCASE(case3, array_cs_db, kernel_size, stride, padding, dilation, ceil_mode);

    AVG_POOL2D_SUBCASE(case3, array_fs_fb, kernel_size, stride, padding, dilation, ceil_mode);
    AVG_POOL2D_SUBCASE(case3, array_fs_hb, kernel_size, stride, padding, dilation, ceil_mode);
    AVG_POOL2D_SUBCASE(case3, array_fs_db, kernel_size, stride, padding, dilation, ceil_mode);

    AVG_POOL2D_SUBCASE(case3, array_hs_fb, kernel_size, stride, padding, dilation, ceil_mode);
    AVG_POOL2D_SUBCASE(case3, array_hs_hb, kernel_size, stride, padding, dilation, ceil_mode);
    AVG_POOL2D_SUBCASE(case3, array_hs_db, kernel_size, stride, padding, dilation, ceil_mode);

    // AVG_POOL2D_SUBCASE(case3, array_ls_fb, kernel_size, stride, padding, dilation, ceil_mode);
    // AVG_POOL2D_SUBCASE(case3, array_ls_hb, kernel_size, stride, padding, dilation, ceil_mode);
    // AVG_POOL2D_SUBCASE(case3, array_ls_db, kernel_size, stride, padding, dilation, ceil_mode);
}

TEST_CASE("avg_pool2d(case3)" * doctest::test_suite("array::avg_pool2d") * doctest::skip())
{
    AVG_POOL2D_SUBCASE(case3, array_ds_fb, kernel_size, stride, padding, dilation, ceil_mode);
    AVG_POOL2D_SUBCASE(case3, array_ds_hb, kernel_size, stride, padding, dilation, ceil_mode);
    AVG_POOL2D_SUBCASE(case3, array_ds_db, kernel_size, stride, padding, dilation, ceil_mode);
}

TEST_CASE("avg_pool2d(case4)" * doctest::test_suite("array::avg_pool2d"))
{
    // AVG_POOL2D_SUBCASE(case4, array, kernel_size, stride, padding, dilation, ceil_mode);
    // AVG_POOL2D_SUBCASE(case4, array_a, kernel_size, stride, padding, dilation, ceil_mode);
    // AVG_POOL2D_SUBCASE(case4, array_f, kernel_size, stride, padding, dilation, ceil_mode);
    // AVG_POOL2D_SUBCASE(case4, array_h, kernel_size, stride, padding, dilation, ceil_mode);
    // AVG_POOL2D_SUBCASE(case4, array_d, kernel_size, stride, padding, dilation, ceil_mode);

    // AVG_POOL2D_SUBCASE(case4, array_cs_fb, kernel_size, stride, padding, dilation, ceil_mode);
    // AVG_POOL2D_SUBCASE(case4, array_cs_hb, kernel_size, stride, padding, dilation, ceil_mode);
    // AVG_POOL2D_SUBCASE(case4, array_cs_db, kernel_size, stride, padding, dilation, ceil_mode);

    AVG_POOL2D_SUBCASE(case4, array_fs_fb, kernel_size, stride, padding, dilation, ceil_mode);
    AVG_POOL2D_SUBCASE(case4, array_fs_hb, kernel_size, stride, padding, dilation, ceil_mode);
    AVG_POOL2D_SUBCASE(case4, array_fs_db, kernel_size, stride, padding, dilation, ceil_mode);

    AVG_POOL2D_SUBCASE(case4, array_hs_fb, kernel_size, stride, padding, dilation, ceil_mode);
    AVG_POOL2D_SUBCASE(case4, array_hs_hb, kernel_size, stride, padding, dilation, ceil_mode);
    AVG_POOL2D_SUBCASE(case4, array_hs_db, kernel_size, stride, padding, dilation, ceil_mode);

    // AVG_POOL2D_SUBCASE(case4, array_ls_fb, kernel_size, stride, padding, dilation, ceil_mode);
    // AVG_POOL2D_SUBCASE(case4, array_ls_hb, kernel_size, stride, padding, dilation, ceil_mode);
    // AVG_POOL2D_SUBCASE(case4, array_ls_db, kernel_size, stride, padding, dilation, ceil_mode);
}

TEST_CASE("avg_pool2d(case4)" * doctest::test_suite("array::avg_pool2d") * doctest::skip())
{
    AVG_POOL2D_SUBCASE(case4, array_ds_fb, kernel_size, stride, padding, dilation, ceil_mode);
    AVG_POOL2D_SUBCASE(case4, array_ds_hb, kernel_size, stride, padding, dilation, ceil_mode);
    AVG_POOL2D_SUBCASE(case4, array_ds_db, kernel_size, stride, padding, dilation, ceil_mode);
}

TEST_CASE("avg_pool2d(case5)" * doctest::test_suite("array::avg_pool2d"))
{
    // AVG_POOL2D_SUBCASE(case5, array, kernel_size, stride, padding, dilation, ceil_mode);
    // AVG_POOL2D_SUBCASE(case5, array_a, kernel_size, stride, padding, dilation, ceil_mode);
    // AVG_POOL2D_SUBCASE(case5, array_f, kernel_size, stride, padding, dilation, ceil_mode);
    // AVG_POOL2D_SUBCASE(case5, array_h, kernel_size, stride, padding, dilation, ceil_mode);
    // AVG_POOL2D_SUBCASE(case5, array_d, kernel_size, stride, padding, dilation, ceil_mode);

    // AVG_POOL2D_SUBCASE(case5, array_cs_fb, kernel_size, stride, padding, dilation, ceil_mode);
    // AVG_POOL2D_SUBCASE(case5, array_cs_hb, kernel_size, stride, padding, dilation, ceil_mode);
    // AVG_POOL2D_SUBCASE(case5, array_cs_db, kernel_size, stride, padding, dilation, ceil_mode);

    AVG_POOL2D_SUBCASE(case5, array_fs_fb, kernel_size, stride, padding, dilation, ceil_mode);
    AVG_POOL2D_SUBCASE(case5, array_fs_hb, kernel_size, stride, padding, dilation, ceil_mode);
    AVG_POOL2D_SUBCASE(case5, array_fs_db, kernel_size, stride, padding, dilation, ceil_mode);

    AVG_POOL2D_SUBCASE(case5, array_hs_fb, kernel_size, stride, padding, dilation, ceil_mode);
    AVG_POOL2D_SUBCASE(case5, array_hs_hb, kernel_size, stride, padding, dilation, ceil_mode);
    AVG_POOL2D_SUBCASE(case5, array_hs_db, kernel_size, stride, padding, dilation, ceil_mode);

    // AVG_POOL2D_SUBCASE(case5, array_ls_fb, kernel_size, stride, padding, dilation, ceil_mode);
    // AVG_POOL2D_SUBCASE(case5, array_ls_hb, kernel_size, stride, padding, dilation, ceil_mode);
    // AVG_POOL2D_SUBCASE(case5, array_ls_db, kernel_size, stride, padding, dilation, ceil_mode);
}

TEST_CASE("avg_pool2d(case5)" * doctest::test_suite("array::avg_pool2d") * doctest::skip())
{
    AVG_POOL2D_SUBCASE(case5, array_ds_fb, kernel_size, stride, padding, dilation, ceil_mode);
    AVG_POOL2D_SUBCASE(case5, array_ds_hb, kernel_size, stride, padding, dilation, ceil_mode);
    AVG_POOL2D_SUBCASE(case5, array_ds_db, kernel_size, stride, padding, dilation, ceil_mode);
}

TEST_CASE("avg_pool2d(case6)" * doctest::test_suite("array::avg_pool2d"))
{
    // AVG_POOL2D_SUBCASE(case6, array, kernel_size, stride, padding, dilation, ceil_mode);
    // AVG_POOL2D_SUBCASE(case6, array_a, kernel_size, stride, padding, dilation, ceil_mode);
    // AVG_POOL2D_SUBCASE(case6, array_f, kernel_size, stride, padding, dilation, ceil_mode);
    // AVG_POOL2D_SUBCASE(case6, array_h, kernel_size, stride, padding, dilation, ceil_mode);
    // AVG_POOL2D_SUBCASE(case6, array_d, kernel_size, stride, padding, dilation, ceil_mode);

    // AVG_POOL2D_SUBCASE(case6, array_cs_fb, kernel_size, stride, padding, dilation, ceil_mode);
    // AVG_POOL2D_SUBCASE(case6, array_cs_hb, kernel_size, stride, padding, dilation, ceil_mode);
    // AVG_POOL2D_SUBCASE(case6, array_cs_db, kernel_size, stride, padding, dilation, ceil_mode);

    AVG_POOL2D_SUBCASE(case6, array_fs_fb, kernel_size, stride, padding, dilation, ceil_mode);
    AVG_POOL2D_SUBCASE(case6, array_fs_hb, kernel_size, stride, padding, dilation, ceil_mode);
    AVG_POOL2D_SUBCASE(case6, array_fs_db, kernel_size, stride, padding, dilation, ceil_mode);

    AVG_POOL2D_SUBCASE(case6, array_hs_fb, kernel_size, stride, padding, dilation, ceil_mode);
    AVG_POOL2D_SUBCASE(case6, array_hs_hb, kernel_size, stride, padding, dilation, ceil_mode);
    AVG_POOL2D_SUBCASE(case6, array_hs_db, kernel_size, stride, padding, dilation, ceil_mode);

    // AVG_POOL2D_SUBCASE(case6, array_ls_fb, kernel_size, stride, padding, dilation, ceil_mode);
    // AVG_POOL2D_SUBCASE(case6, array_ls_hb, kernel_size, stride, padding, dilation, ceil_mode);
    // AVG_POOL2D_SUBCASE(case6, array_ls_db, kernel_size, stride, padding, dilation, ceil_mode);
}

TEST_CASE("avg_pool2d(case6)" * doctest::test_suite("array::avg_pool2d") * doctest::skip())
{
    AVG_POOL2D_SUBCASE(case6, array_ds_fb, kernel_size, stride, padding, dilation, ceil_mode);
    AVG_POOL2D_SUBCASE(case6, array_ds_hb, kernel_size, stride, padding, dilation, ceil_mode);
    AVG_POOL2D_SUBCASE(case6, array_ds_db, kernel_size, stride, padding, dilation, ceil_mode);
}

TEST_CASE("avg_pool2d(case7)" * doctest::test_suite("array::avg_pool2d"))
{
    // AVG_POOL2D_SUBCASE(case7, array, kernel_size, stride, padding, dilation, ceil_mode);
    // AVG_POOL2D_SUBCASE(case7, array_a, kernel_size, stride, padding, dilation, ceil_mode);
    // AVG_POOL2D_SUBCASE(case7, array_f, kernel_size, stride, padding, dilation, ceil_mode);
    // AVG_POOL2D_SUBCASE(case7, array_h, kernel_size, stride, padding, dilation, ceil_mode);
    // AVG_POOL2D_SUBCASE(case7, array_d, kernel_size, stride, padding, dilation, ceil_mode);

    // AVG_POOL2D_SUBCASE(case7, array_cs_fb, kernel_size, stride, padding, dilation, ceil_mode);
    // AVG_POOL2D_SUBCASE(case7, array_cs_hb, kernel_size, stride, padding, dilation, ceil_mode);
    // AVG_POOL2D_SUBCASE(case7, array_cs_db, kernel_size, stride, padding, dilation, ceil_mode);

    AVG_POOL2D_SUBCASE(case7, array_fs_fb, kernel_size, stride, padding, dilation, ceil_mode);
    AVG_POOL2D_SUBCASE(case7, array_fs_hb, kernel_size, stride, padding, dilation, ceil_mode);
    AVG_POOL2D_SUBCASE(case7, array_fs_db, kernel_size, stride, padding, dilation, ceil_mode);

    AVG_POOL2D_SUBCASE(case7, array_hs_fb, kernel_size, stride, padding, dilation, ceil_mode);
    AVG_POOL2D_SUBCASE(case7, array_hs_hb, kernel_size, stride, padding, dilation, ceil_mode);
    AVG_POOL2D_SUBCASE(case7, array_hs_db, kernel_size, stride, padding, dilation, ceil_mode);

    // AVG_POOL2D_SUBCASE(case7, array_ls_fb, kernel_size, stride, padding, dilation, ceil_mode);
    // AVG_POOL2D_SUBCASE(case7, array_ls_hb, kernel_size, stride, padding, dilation, ceil_mode);
    // AVG_POOL2D_SUBCASE(case7, array_ls_db, kernel_size, stride, padding, dilation, ceil_mode);
}

TEST_CASE("avg_pool2d(case7)" * doctest::test_suite("array::avg_pool2d") * doctest::skip())
{
    AVG_POOL2D_SUBCASE(case7, array_ds_fb, kernel_size, stride, padding, dilation, ceil_mode);
    AVG_POOL2D_SUBCASE(case7, array_ds_hb, kernel_size, stride, padding, dilation, ceil_mode);
    AVG_POOL2D_SUBCASE(case7, array_ds_db, kernel_size, stride, padding, dilation, ceil_mode);
}

TEST_CASE("avg_pool2d(case8)" * doctest::test_suite("array::avg_pool2d"))
{
    // AVG_POOL2D_SUBCASE(case8, array, kernel_size, stride, padding, dilation, ceil_mode);
    // AVG_POOL2D_SUBCASE(case8, array_a, kernel_size, stride, padding, dilation, ceil_mode);
    // AVG_POOL2D_SUBCASE(case8, array_f, kernel_size, stride, padding, dilation, ceil_mode);
    // AVG_POOL2D_SUBCASE(case8, array_h, kernel_size, stride, padding, dilation, ceil_mode);
    // AVG_POOL2D_SUBCASE(case8, array_d, kernel_size, stride, padding, dilation, ceil_mode);

    // AVG_POOL2D_SUBCASE(case8, array_cs_fb, kernel_size, stride, padding, dilation, ceil_mode);
    // AVG_POOL2D_SUBCASE(case8, array_cs_hb, kernel_size, stride, padding, dilation, ceil_mode);
    // AVG_POOL2D_SUBCASE(case8, array_cs_db, kernel_size, stride, padding, dilation, ceil_mode);

    AVG_POOL2D_SUBCASE(case8, array_fs_fb, kernel_size, stride, padding, dilation, ceil_mode);
    AVG_POOL2D_SUBCASE(case8, array_fs_hb, kernel_size, stride, padding, dilation, ceil_mode);
    AVG_POOL2D_SUBCASE(case8, array_fs_db, kernel_size, stride, padding, dilation, ceil_mode);

    AVG_POOL2D_SUBCASE(case8, array_hs_fb, kernel_size, stride, padding, dilation, ceil_mode);
    AVG_POOL2D_SUBCASE(case8, array_hs_hb, kernel_size, stride, padding, dilation, ceil_mode);
    AVG_POOL2D_SUBCASE(case8, array_hs_db, kernel_size, stride, padding, dilation, ceil_mode);

    // AVG_POOL2D_SUBCASE(case8, array_ls_fb, kernel_size, stride, padding, dilation, ceil_mode);
    // AVG_POOL2D_SUBCASE(case8, array_ls_hb, kernel_size, stride, padding, dilation, ceil_mode);
    // AVG_POOL2D_SUBCASE(case8, array_ls_db, kernel_size, stride, padding, dilation, ceil_mode);
}

TEST_CASE("avg_pool2d(case8)" * doctest::test_suite("array::avg_pool2d") * doctest::skip())
{
    AVG_POOL2D_SUBCASE(case8, array_ds_fb, kernel_size, stride, padding, dilation, ceil_mode);
    AVG_POOL2D_SUBCASE(case8, array_ds_hb, kernel_size, stride, padding, dilation, ceil_mode);
    AVG_POOL2D_SUBCASE(case8, array_ds_db, kernel_size, stride, padding, dilation, ceil_mode);
}

TEST_CASE("avg_pool2d(case9)" * doctest::test_suite("array::avg_pool2d") * doctest::skip())
{
    // AVG_POOL2D_SUBCASE(case9, array, kernel_size, stride, padding, dilation, ceil_mode);
    // AVG_POOL2D_SUBCASE(case9, array_a, kernel_size, stride, padding, dilation, ceil_mode);
    // AVG_POOL2D_SUBCASE(case9, array_f, kernel_size, stride, padding, dilation, ceil_mode);
    // AVG_POOL2D_SUBCASE(case9, array_h, kernel_size, stride, padding, dilation, ceil_mode);
    // AVG_POOL2D_SUBCASE(case9, array_d, kernel_size, stride, padding, dilation, ceil_mode);

    // AVG_POOL2D_SUBCASE(case9, array_cs_fb, kernel_size, stride, padding, dilation, ceil_mode);
    // AVG_POOL2D_SUBCASE(case9, array_cs_hb, kernel_size, stride, padding, dilation, ceil_mode);
    // AVG_POOL2D_SUBCASE(case9, array_cs_db, kernel_size, stride, padding, dilation, ceil_mode);

    AVG_POOL2D_SUBCASE(case9, array_fs_fb, kernel_size, stride, padding, dilation, ceil_mode);
    AVG_POOL2D_SUBCASE(case9, array_fs_hb, kernel_size, stride, padding, dilation, ceil_mode);
    AVG_POOL2D_SUBCASE(case9, array_fs_db, kernel_size, stride, padding, dilation, ceil_mode);

    AVG_POOL2D_SUBCASE(case9, array_hs_fb, kernel_size, stride, padding, dilation, ceil_mode);
    AVG_POOL2D_SUBCASE(case9, array_hs_hb, kernel_size, stride, padding, dilation, ceil_mode);
    AVG_POOL2D_SUBCASE(case9, array_hs_db, kernel_size, stride, padding, dilation, ceil_mode);

    // AVG_POOL2D_SUBCASE(case9, array_ls_fb, kernel_size, stride, padding, dilation, ceil_mode);
    // AVG_POOL2D_SUBCASE(case9, array_ls_hb, kernel_size, stride, padding, dilation, ceil_mode);
    // AVG_POOL2D_SUBCASE(case9, array_ls_db, kernel_size, stride, padding, dilation, ceil_mode);
}

TEST_CASE("avg_pool2d(case9)" * doctest::test_suite("array::avg_pool2d") * doctest::skip())
{
    AVG_POOL2D_SUBCASE(case9, array_ds_fb, kernel_size, stride, padding, dilation, ceil_mode);
    AVG_POOL2D_SUBCASE(case9, array_ds_hb, kernel_size, stride, padding, dilation, ceil_mode);
    AVG_POOL2D_SUBCASE(case9, array_ds_db, kernel_size, stride, padding, dilation, ceil_mode);
}

TEST_CASE("avg_pool2d(case10)" * doctest::test_suite("array::avg_pool2d"))
{
    // AVG_POOL2D_SUBCASE(case10, array, kernel_size, stride, padding, dilation, ceil_mode);
    // AVG_POOL2D_SUBCASE(case10, array_a, kernel_size, stride, padding, dilation, ceil_mode);
    // AVG_POOL2D_SUBCASE(case10, array_f, kernel_size, stride, padding, dilation, ceil_mode);
    // AVG_POOL2D_SUBCASE(case10, array_h, kernel_size, stride, padding, dilation, ceil_mode);
    // AVG_POOL2D_SUBCASE(case10, array_d, kernel_size, stride, padding, dilation, ceil_mode);

    // AVG_POOL2D_SUBCASE(case10, array_cs_fb, kernel_size, stride, padding, dilation, ceil_mode);
    // AVG_POOL2D_SUBCASE(case10, array_cs_hb, kernel_size, stride, padding, dilation, ceil_mode);
    // AVG_POOL2D_SUBCASE(case10, array_cs_db, kernel_size, stride, padding, dilation, ceil_mode);

    AVG_POOL2D_SUBCASE(case10, array_fs_fb, kernel_size, stride, padding, dilation, ceil_mode);
    AVG_POOL2D_SUBCASE(case10, array_fs_hb, kernel_size, stride, padding, dilation, ceil_mode);
    AVG_POOL2D_SUBCASE(case10, array_fs_db, kernel_size, stride, padding, dilation, ceil_mode);

    AVG_POOL2D_SUBCASE(case10, array_hs_fb, kernel_size, stride, padding, dilation, ceil_mode);
    AVG_POOL2D_SUBCASE(case10, array_hs_hb, kernel_size, stride, padding, dilation, ceil_mode);
    AVG_POOL2D_SUBCASE(case10, array_hs_db, kernel_size, stride, padding, dilation, ceil_mode);

    // AVG_POOL2D_SUBCASE(case10, array_ls_fb, kernel_size, stride, padding, dilation, ceil_mode);
    // AVG_POOL2D_SUBCASE(case10, array_ls_hb, kernel_size, stride, padding, dilation, ceil_mode);
    // AVG_POOL2D_SUBCASE(case10, array_ls_db, kernel_size, stride, padding, dilation, ceil_mode);
}

TEST_CASE("avg_pool2d(case10)" * doctest::test_suite("array::avg_pool2d") * doctest::skip())
{
    AVG_POOL2D_SUBCASE(case10, array_ds_fb, kernel_size, stride, padding, dilation, ceil_mode);
    AVG_POOL2D_SUBCASE(case10, array_ds_hb, kernel_size, stride, padding, dilation, ceil_mode);
    AVG_POOL2D_SUBCASE(case10, array_ds_db, kernel_size, stride, padding, dilation, ceil_mode);
}