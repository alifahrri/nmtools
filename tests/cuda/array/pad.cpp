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

#include "nmtools/array/pad.hpp"
#include "nmtools/testing/doctest.hpp"
#include "nmtools/evaluator/cuda.hpp"
#include "nmtools/testing/data/array/pad.hpp"

namespace nm = nmtools;
namespace na = nmtools;
namespace cuda = na::cuda;

#define PAD_SUBCASE(case_name, ...) \
SUBCASE(#case_name) \
{ \
    NMTOOLS_TESTING_USE_CASE(array, pad, case_name); \
    using namespace args; \
    auto result = na::pad2(__VA_ARGS__, cuda::default_context()); \
    auto expect = na::pad2(__VA_ARGS__); \
    NMTOOLS_ASSERT_EQUAL( nm::shape(result), nm::shape(expect) ); \
    NMTOOLS_ASSERT_CLOSE( result, expect ); \
}

// TODO: fix compile, caused by refactoring pad to indexing view
#if 0

static float value = 0.0f;

TEST_CASE("pad(case1)" * doctest::test_suite("array::pad2"))
{
    // PAD_SUBCASE(case1, array, pads_a, value);
    // PAD_SUBCASE(case1, array_a, pads_a, value);
    // PAD_SUBCASE(case1, array_f, pads_a, value);
    // PAD_SUBCASE(case1, array_h, pads_a, value);
    // PAD_SUBCASE(case1, array_d, pads_a, value);

    // PAD_SUBCASE(case1, array_cs_fb, pads_a, value);
    // PAD_SUBCASE(case1, array_cs_hb, pads_a, value);
    // PAD_SUBCASE(case1, array_cs_db, pads_a, value);

    PAD_SUBCASE(case1, array_fs_fb, pads_a, value);
    PAD_SUBCASE(case1, array_fs_hb, pads_a, value);
    PAD_SUBCASE(case1, array_fs_db, pads_a, value);

    PAD_SUBCASE(case1, array_hs_fb, pads_a, value);
    PAD_SUBCASE(case1, array_hs_hb, pads_a, value);
    PAD_SUBCASE(case1, array_hs_db, pads_a, value);

    PAD_SUBCASE(case1, array_ds_fb, pads_a, value);
    PAD_SUBCASE(case1, array_ds_hb, pads_a, value);
    PAD_SUBCASE(case1, array_ds_db, pads_a, value);

    // PAD_SUBCASE(case1, array_ls_fb, pads_a, value);
    // PAD_SUBCASE(case1, array_ls_hb, pads_a, value);
    // PAD_SUBCASE(case1, array_ls_db, pads_a, value);
}

TEST_CASE("pad(case2)" * doctest::test_suite("array::pad2"))
{
    // PAD_SUBCASE(case2, array, pads_a, value);
    // PAD_SUBCASE(case2, array_a, pads_a, value);
    // PAD_SUBCASE(case2, array_f, pads_a, value);
    // PAD_SUBCASE(case2, array_h, pads_a, value);
    // PAD_SUBCASE(case2, array_d, pads_a, value);

    // PAD_SUBCASE(case2, array_cs_fb, pads_a, value);
    // PAD_SUBCASE(case2, array_cs_hb, pads_a, value);
    // PAD_SUBCASE(case2, array_cs_db, pads_a, value);

    PAD_SUBCASE(case2, array_fs_fb, pads_a, value);
    PAD_SUBCASE(case2, array_fs_hb, pads_a, value);
    PAD_SUBCASE(case2, array_fs_db, pads_a, value);

    PAD_SUBCASE(case2, array_hs_fb, pads_a, value);
    PAD_SUBCASE(case2, array_hs_hb, pads_a, value);
    PAD_SUBCASE(case2, array_hs_db, pads_a, value);

    PAD_SUBCASE(case2, array_ds_fb, pads_a, value);
    PAD_SUBCASE(case2, array_ds_hb, pads_a, value);
    PAD_SUBCASE(case2, array_ds_db, pads_a, value);

    // PAD_SUBCASE(case2, array_ls_fb, pads_a, value);
    // PAD_SUBCASE(case2, array_ls_hb, pads_a, value);
    // PAD_SUBCASE(case2, array_ls_db, pads_a, value);
}

TEST_CASE("pad(case3)" * doctest::test_suite("array::pad2"))
{
    // PAD_SUBCASE(case3, array, pads_a, value);
    // PAD_SUBCASE(case3, array_a, pads_a, value);
    // PAD_SUBCASE(case3, array_f, pads_a, value);
    // PAD_SUBCASE(case3, array_h, pads_a, value);
    // PAD_SUBCASE(case3, array_d, pads_a, value);

    // PAD_SUBCASE(case3, array_cs_fb, pads_a, value);
    // PAD_SUBCASE(case3, array_cs_hb, pads_a, value);
    // PAD_SUBCASE(case3, array_cs_db, pads_a, value);

    PAD_SUBCASE(case3, array_fs_fb, pads_a, value);
    PAD_SUBCASE(case3, array_fs_hb, pads_a, value);
    PAD_SUBCASE(case3, array_fs_db, pads_a, value);

    PAD_SUBCASE(case3, array_hs_fb, pads_a, value);
    PAD_SUBCASE(case3, array_hs_hb, pads_a, value);
    PAD_SUBCASE(case3, array_hs_db, pads_a, value);

    PAD_SUBCASE(case3, array_ds_fb, pads_a, value);
    PAD_SUBCASE(case3, array_ds_hb, pads_a, value);
    PAD_SUBCASE(case3, array_ds_db, pads_a, value);

    // PAD_SUBCASE(case3, array_ls_fb, pads_a, value);
    // PAD_SUBCASE(case3, array_ls_hb, pads_a, value);
    // PAD_SUBCASE(case3, array_ls_db, pads_a, value);
}

TEST_CASE("pad(case4)" * doctest::test_suite("array::pad2"))
{
    // PAD_SUBCASE(case4, array, pads_a, value);
    // PAD_SUBCASE(case4, array_a, pads_a, value);
    // PAD_SUBCASE(case4, array_f, pads_a, value);
    // PAD_SUBCASE(case4, array_h, pads_a, value);
    // PAD_SUBCASE(case4, array_d, pads_a, value);

    // PAD_SUBCASE(case4, array_cs_fb, pads_a, value);
    // PAD_SUBCASE(case4, array_cs_hb, pads_a, value);
    // PAD_SUBCASE(case4, array_cs_db, pads_a, value);

    PAD_SUBCASE(case4, array_fs_fb, pads_a, value);
    PAD_SUBCASE(case4, array_fs_hb, pads_a, value);
    PAD_SUBCASE(case4, array_fs_db, pads_a, value);

    PAD_SUBCASE(case4, array_hs_fb, pads_a, value);
    PAD_SUBCASE(case4, array_hs_hb, pads_a, value);
    PAD_SUBCASE(case4, array_hs_db, pads_a, value);

    PAD_SUBCASE(case4, array_ds_fb, pads_a, value);
    PAD_SUBCASE(case4, array_ds_hb, pads_a, value);
    PAD_SUBCASE(case4, array_ds_db, pads_a, value);

    // PAD_SUBCASE(case4, array_ls_fb, pads_a, value);
    // PAD_SUBCASE(case4, array_ls_hb, pads_a, value);
    // PAD_SUBCASE(case4, array_ls_db, pads_a, value);
}

TEST_CASE("pad(case5)" * doctest::test_suite("array::pad2"))
{
    // PAD_SUBCASE(case5, array, pads_a, value);
    // PAD_SUBCASE(case5, array_a, pads_a, value);
    // PAD_SUBCASE(case5, array_f, pads_a, value);
    // PAD_SUBCASE(case5, array_h, pads_a, value);
    // PAD_SUBCASE(case5, array_d, pads_a, value);

    // PAD_SUBCASE(case5, array_cs_fb, pads_a, value);
    // PAD_SUBCASE(case5, array_cs_hb, pads_a, value);
    // PAD_SUBCASE(case5, array_cs_db, pads_a, value);

    PAD_SUBCASE(case5, array_fs_fb, pads_a, value);
    PAD_SUBCASE(case5, array_fs_hb, pads_a, value);
    PAD_SUBCASE(case5, array_fs_db, pads_a, value);

    PAD_SUBCASE(case5, array_hs_fb, pads_a, value);
    PAD_SUBCASE(case5, array_hs_hb, pads_a, value);
    PAD_SUBCASE(case5, array_hs_db, pads_a, value);

    PAD_SUBCASE(case5, array_ds_fb, pads_a, value);
    PAD_SUBCASE(case5, array_ds_hb, pads_a, value);
    PAD_SUBCASE(case5, array_ds_db, pads_a, value);

    // PAD_SUBCASE(case5, array_ls_fb, pads_a, value);
    // PAD_SUBCASE(case5, array_ls_hb, pads_a, value);
    // PAD_SUBCASE(case5, array_ls_db, pads_a, value);
}
#endif