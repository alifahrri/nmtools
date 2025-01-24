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

#include "nmtools/array/transpose.hpp"
#include "nmtools/testing/doctest.hpp"
#include "nmtools/evaluator/sycl.hpp"
#include "nmtools/testing/data/array/transpose.hpp"

namespace nm = nmtools;
namespace na = nm::array;

#define TRANSPOSE_SUBCASE(case_name, ...) \
SUBCASE(#case_name) \
{ \
    NMTOOLS_TESTING_USE_CASE(transpose, case_name); \
    using namespace args; \
    auto result = na::transpose(__VA_ARGS__, na::sycl::default_context()); \
    auto expect = na::transpose(__VA_ARGS__); \
    NMTOOLS_ASSERT_EQUAL( nm::shape(result), nm::shape(expect) ); \
    NMTOOLS_ASSERT_CLOSE( result, expect ); \
}

TEST_CASE("transpose(case1)" * doctest::test_suite("array::transpose"))
{
    // TRANSPOSE_SUBCASE(case1, array, axes_a);
    // TRANSPOSE_SUBCASE(case1, array_a, axes_a);
    // TRANSPOSE_SUBCASE(case1, array_f, axes_a);
    // TRANSPOSE_SUBCASE(case1, array_h, axes_a);
    // TRANSPOSE_SUBCASE(case1, array_d, axes_a);

    TRANSPOSE_SUBCASE(case1, array_cs_fb, axes_a);
    TRANSPOSE_SUBCASE(case1, array_cs_hb, axes_a);
    TRANSPOSE_SUBCASE(case1, array_cs_db, axes_a);

    TRANSPOSE_SUBCASE(case1, array_fs_fb, axes_a);
    TRANSPOSE_SUBCASE(case1, array_fs_hb, axes_a);
    TRANSPOSE_SUBCASE(case1, array_fs_db, axes_a);

    TRANSPOSE_SUBCASE(case1, array_hs_fb, axes_a);
    TRANSPOSE_SUBCASE(case1, array_hs_hb, axes_a);
    TRANSPOSE_SUBCASE(case1, array_hs_db, axes_a);

    TRANSPOSE_SUBCASE(case1, array_ds_fb, axes_a);
    TRANSPOSE_SUBCASE(case1, array_ds_hb, axes_a);
    TRANSPOSE_SUBCASE(case1, array_ds_db, axes_a);

    TRANSPOSE_SUBCASE(case1, array_ls_fb, axes_a);
    TRANSPOSE_SUBCASE(case1, array_ls_hb, axes_a);
    TRANSPOSE_SUBCASE(case1, array_ls_db, axes_a);
}

TEST_CASE("transpose(case2)" * doctest::test_suite("array::transpose"))
{
    // TRANSPOSE_SUBCASE(case2, array, axes_a);
    // TRANSPOSE_SUBCASE(case2, array_a, axes_a);
    // TRANSPOSE_SUBCASE(case2, array_f, axes_a);
    // TRANSPOSE_SUBCASE(case2, array_h, axes_a);
    // TRANSPOSE_SUBCASE(case2, array_d, axes_a);

    TRANSPOSE_SUBCASE(case2, array_cs_fb, axes_a);
    TRANSPOSE_SUBCASE(case2, array_cs_hb, axes_a);
    TRANSPOSE_SUBCASE(case2, array_cs_db, axes_a);

    TRANSPOSE_SUBCASE(case2, array_fs_fb, axes_a);
    TRANSPOSE_SUBCASE(case2, array_fs_hb, axes_a);
    TRANSPOSE_SUBCASE(case2, array_fs_db, axes_a);

    TRANSPOSE_SUBCASE(case2, array_hs_fb, axes_a);
    TRANSPOSE_SUBCASE(case2, array_hs_hb, axes_a);
    TRANSPOSE_SUBCASE(case2, array_hs_db, axes_a);

    // TODO: fix for sycl kernel (opencl/cuda)
    #if 0
    TRANSPOSE_SUBCASE(case2, array_ds_fb, axes_a);
    TRANSPOSE_SUBCASE(case2, array_ds_hb, axes_a);
    TRANSPOSE_SUBCASE(case2, array_ds_db, axes_a);
    #endif

    TRANSPOSE_SUBCASE(case2, array_ls_fb, axes_a);
    TRANSPOSE_SUBCASE(case2, array_ls_hb, axes_a);
    TRANSPOSE_SUBCASE(case2, array_ls_db, axes_a);
}

// TODO: fix test case
TEST_CASE("transpose(case3)" * doctest::test_suite("array::transpose") * doctest::skip() * doctest::may_fail())
{
    // TRANSPOSE_SUBCASE(case3, array, axes_a);
    // TRANSPOSE_SUBCASE(case3, array_a, axes_a);
    // TRANSPOSE_SUBCASE(case3, array_f, axes_a);
    // TRANSPOSE_SUBCASE(case3, array_h, axes_a);
    // TRANSPOSE_SUBCASE(case3, array_d, axes_a);

    TRANSPOSE_SUBCASE(case3, array_cs_fb, axes_a);
    TRANSPOSE_SUBCASE(case3, array_cs_hb, axes_a);
    TRANSPOSE_SUBCASE(case3, array_cs_db, axes_a);

    TRANSPOSE_SUBCASE(case3, array_fs_fb, axes_a);
    TRANSPOSE_SUBCASE(case3, array_fs_hb, axes_a);
    TRANSPOSE_SUBCASE(case3, array_fs_db, axes_a);

    TRANSPOSE_SUBCASE(case3, array_hs_fb, axes_a);
    TRANSPOSE_SUBCASE(case3, array_hs_hb, axes_a);
    TRANSPOSE_SUBCASE(case3, array_hs_db, axes_a);

    TRANSPOSE_SUBCASE(case3, array_ds_fb, axes_a);
    TRANSPOSE_SUBCASE(case3, array_ds_hb, axes_a);
    TRANSPOSE_SUBCASE(case3, array_ds_db, axes_a);

    TRANSPOSE_SUBCASE(case3, array_ls_fb, axes_a);
    TRANSPOSE_SUBCASE(case3, array_ls_hb, axes_a);
    TRANSPOSE_SUBCASE(case3, array_ls_db, axes_a);
}

TEST_CASE("transpose(case4)" * doctest::test_suite("array::transpose"))
{
    // TRANSPOSE_SUBCASE(case4, array, axes_a);
    // TRANSPOSE_SUBCASE(case4, array_a, axes_a);
    // TRANSPOSE_SUBCASE(case4, array_f, axes_a);
    // TRANSPOSE_SUBCASE(case4, array_h, axes_a);
    // TRANSPOSE_SUBCASE(case4, array_d, axes_a);

    TRANSPOSE_SUBCASE(case4, array_cs_fb, axes_a);
    TRANSPOSE_SUBCASE(case4, array_cs_hb, axes_a);
    TRANSPOSE_SUBCASE(case4, array_cs_db, axes_a);

    TRANSPOSE_SUBCASE(case4, array_fs_fb, axes_a);
    TRANSPOSE_SUBCASE(case4, array_fs_hb, axes_a);
    TRANSPOSE_SUBCASE(case4, array_fs_db, axes_a);

    TRANSPOSE_SUBCASE(case4, array_hs_fb, axes_a);
    TRANSPOSE_SUBCASE(case4, array_hs_hb, axes_a);
    TRANSPOSE_SUBCASE(case4, array_hs_db, axes_a);

    TRANSPOSE_SUBCASE(case4, array_ds_fb, axes_a);
    TRANSPOSE_SUBCASE(case4, array_ds_hb, axes_a);
    TRANSPOSE_SUBCASE(case4, array_ds_db, axes_a);

    TRANSPOSE_SUBCASE(case4, array_ls_fb, axes_a);
    TRANSPOSE_SUBCASE(case4, array_ls_hb, axes_a);
    TRANSPOSE_SUBCASE(case4, array_ls_db, axes_a);
}

TEST_CASE("transpose(case5)" * doctest::test_suite("array::transpose"))
{
    // TRANSPOSE_SUBCASE(case5, array, axes_a);
    // TRANSPOSE_SUBCASE(case5, array_a, axes_a);
    // TRANSPOSE_SUBCASE(case5, array_f, axes_a);
    // TRANSPOSE_SUBCASE(case5, array_h, axes_a);
    // TRANSPOSE_SUBCASE(case5, array_d, axes_a);

    TRANSPOSE_SUBCASE(case5, array_cs_fb, axes_a);
    TRANSPOSE_SUBCASE(case5, array_cs_hb, axes_a);
    TRANSPOSE_SUBCASE(case5, array_cs_db, axes_a);

    TRANSPOSE_SUBCASE(case5, array_fs_fb, axes_a);
    TRANSPOSE_SUBCASE(case5, array_fs_hb, axes_a);
    TRANSPOSE_SUBCASE(case5, array_fs_db, axes_a);

    TRANSPOSE_SUBCASE(case5, array_hs_fb, axes_a);
    TRANSPOSE_SUBCASE(case5, array_hs_hb, axes_a);
    TRANSPOSE_SUBCASE(case5, array_hs_db, axes_a);

    TRANSPOSE_SUBCASE(case5, array_ds_fb, axes_a);
    TRANSPOSE_SUBCASE(case5, array_ds_hb, axes_a);
    TRANSPOSE_SUBCASE(case5, array_ds_db, axes_a);

    TRANSPOSE_SUBCASE(case5, array_ls_fb, axes_a);
    TRANSPOSE_SUBCASE(case5, array_ls_hb, axes_a);
    TRANSPOSE_SUBCASE(case5, array_ls_db, axes_a);
}

TEST_CASE("transpose(case6)" * doctest::test_suite("array::transpose"))
{
    // TRANSPOSE_SUBCASE(case6, array, axes_a);
    // TRANSPOSE_SUBCASE(case6, array_a, axes_a);
    // TRANSPOSE_SUBCASE(case6, array_f, axes_a);
    // TRANSPOSE_SUBCASE(case6, array_h, axes_a);
    // TRANSPOSE_SUBCASE(case6, array_d, axes_a);

    TRANSPOSE_SUBCASE(case6, array_cs_fb, axes_a);
    TRANSPOSE_SUBCASE(case6, array_cs_hb, axes_a);
    TRANSPOSE_SUBCASE(case6, array_cs_db, axes_a);

    TRANSPOSE_SUBCASE(case6, array_fs_fb, axes_a);
    TRANSPOSE_SUBCASE(case6, array_fs_hb, axes_a);
    TRANSPOSE_SUBCASE(case6, array_fs_db, axes_a);

    TRANSPOSE_SUBCASE(case6, array_hs_fb, axes_a);
    TRANSPOSE_SUBCASE(case6, array_hs_hb, axes_a);
    TRANSPOSE_SUBCASE(case6, array_hs_db, axes_a);

    TRANSPOSE_SUBCASE(case6, array_ds_fb, axes_a);
    TRANSPOSE_SUBCASE(case6, array_ds_hb, axes_a);
    TRANSPOSE_SUBCASE(case6, array_ds_db, axes_a);

    TRANSPOSE_SUBCASE(case6, array_ls_fb, axes_a);
    TRANSPOSE_SUBCASE(case6, array_ls_hb, axes_a);
    TRANSPOSE_SUBCASE(case6, array_ls_db, axes_a);
}

TEST_CASE("transpose(case7)" * doctest::test_suite("array::transpose"))
{
    // TRANSPOSE_SUBCASE(case7, array, axes_a);
    // TRANSPOSE_SUBCASE(case7, array_a, axes_a);
    // TRANSPOSE_SUBCASE(case7, array_f, axes_a);
    // TRANSPOSE_SUBCASE(case7, array_h, axes_a);
    // TRANSPOSE_SUBCASE(case7, array_d, axes_a);

    TRANSPOSE_SUBCASE(case7, array_cs_fb, axes_a);
    TRANSPOSE_SUBCASE(case7, array_cs_hb, axes_a);
    TRANSPOSE_SUBCASE(case7, array_cs_db, axes_a);

    TRANSPOSE_SUBCASE(case7, array_fs_fb, axes_a);
    TRANSPOSE_SUBCASE(case7, array_fs_hb, axes_a);
    TRANSPOSE_SUBCASE(case7, array_fs_db, axes_a);

    TRANSPOSE_SUBCASE(case7, array_hs_fb, axes_a);
    TRANSPOSE_SUBCASE(case7, array_hs_hb, axes_a);
    TRANSPOSE_SUBCASE(case7, array_hs_db, axes_a);

    TRANSPOSE_SUBCASE(case7, array_ds_fb, axes_a);
    TRANSPOSE_SUBCASE(case7, array_ds_hb, axes_a);
    TRANSPOSE_SUBCASE(case7, array_ds_db, axes_a);

    TRANSPOSE_SUBCASE(case7, array_ls_fb, axes_a);
    TRANSPOSE_SUBCASE(case7, array_ls_hb, axes_a);
    TRANSPOSE_SUBCASE(case7, array_ls_db, axes_a);
}

TEST_CASE("transpose(case8)" * doctest::test_suite("array::transpose"))
{
    // TRANSPOSE_SUBCASE(case8, array, axes_a);
    // TRANSPOSE_SUBCASE(case8, array_a, axes_a);
    // TRANSPOSE_SUBCASE(case8, array_f, axes_a);
    // TRANSPOSE_SUBCASE(case8, array_h, axes_a);
    // TRANSPOSE_SUBCASE(case8, array_d, axes_a);

    TRANSPOSE_SUBCASE(case8, array_cs_fb, axes_a);
    TRANSPOSE_SUBCASE(case8, array_cs_hb, axes_a);
    TRANSPOSE_SUBCASE(case8, array_cs_db, axes_a);

    TRANSPOSE_SUBCASE(case8, array_fs_fb, axes_a);
    TRANSPOSE_SUBCASE(case8, array_fs_hb, axes_a);
    TRANSPOSE_SUBCASE(case8, array_fs_db, axes_a);

    TRANSPOSE_SUBCASE(case8, array_hs_fb, axes_a);
    TRANSPOSE_SUBCASE(case8, array_hs_hb, axes_a);
    TRANSPOSE_SUBCASE(case8, array_hs_db, axes_a);

    TRANSPOSE_SUBCASE(case8, array_ds_fb, axes_a);
    TRANSPOSE_SUBCASE(case8, array_ds_hb, axes_a);
    TRANSPOSE_SUBCASE(case8, array_ds_db, axes_a);

    TRANSPOSE_SUBCASE(case8, array_ls_fb, axes_a);
    TRANSPOSE_SUBCASE(case8, array_ls_hb, axes_a);
    TRANSPOSE_SUBCASE(case8, array_ls_db, axes_a);
}

TEST_CASE("transpose(case9)" * doctest::test_suite("array::transpose"))
{
    // TRANSPOSE_SUBCASE(case9, array, axes_a);
    // TRANSPOSE_SUBCASE(case9, array_a, axes_a);
    // TRANSPOSE_SUBCASE(case9, array_f, axes_a);
    // TRANSPOSE_SUBCASE(case9, array_h, axes_a);
    // TRANSPOSE_SUBCASE(case9, array_d, axes_a);

    TRANSPOSE_SUBCASE(case9, array_cs_fb, axes_a);
    TRANSPOSE_SUBCASE(case9, array_cs_hb, axes_a);
    TRANSPOSE_SUBCASE(case9, array_cs_db, axes_a);

    TRANSPOSE_SUBCASE(case9, array_fs_fb, axes_a);
    TRANSPOSE_SUBCASE(case9, array_fs_hb, axes_a);
    TRANSPOSE_SUBCASE(case9, array_fs_db, axes_a);

    TRANSPOSE_SUBCASE(case9, array_hs_fb, axes_a);
    TRANSPOSE_SUBCASE(case9, array_hs_hb, axes_a);
    TRANSPOSE_SUBCASE(case9, array_hs_db, axes_a);

    TRANSPOSE_SUBCASE(case9, array_ds_fb, axes_a);
    TRANSPOSE_SUBCASE(case9, array_ds_hb, axes_a);
    TRANSPOSE_SUBCASE(case9, array_ds_db, axes_a);

    TRANSPOSE_SUBCASE(case9, array_ls_fb, axes_a);
    TRANSPOSE_SUBCASE(case9, array_ls_hb, axes_a);
    TRANSPOSE_SUBCASE(case9, array_ls_db, axes_a);
}