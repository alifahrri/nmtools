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

#include "nmtools/array/array/flip.hpp"
#include "nmtools/testing/doctest.hpp"
#include "nmtools/array/eval/sycl.hpp"
#include "nmtools/testing/data/array/flip.hpp"

namespace nm = nmtools;
namespace na = nm::array;

#define FLIP_SUBCASE(case_name, ...) \
SUBCASE(#case_name) \
{ \
    NMTOOLS_TESTING_DECLARE_NS(flip, case_name); \
    using namespace args; \
    auto result = na::flip(__VA_ARGS__, na::sycl::default_context()); \
    auto expect = na::flip(__VA_ARGS__); \
    NMTOOLS_ASSERT_EQUAL( nm::shape(result), nm::shape(expect) ); \
    NMTOOLS_ASSERT_CLOSE( result, expect ); \
}

// TODO: fix for sycl kernel (opencl/cuda), remove free/malloc in kernel code
TEST_CASE("flip(case1)" * doctest::test_suite("array::flip") * doctest::skip())
{
    // FLIP_SUBCASE(case1, array, axis);
    // FLIP_SUBCASE(case1, array_a, axis);
    // FLIP_SUBCASE(case1, array_f, axis);
    // FLIP_SUBCASE(case1, array_h, axis);
    // FLIP_SUBCASE(case1, array_d, axis);

    // FLIP_SUBCASE(case1, array_cs_fb, axis);
    // FLIP_SUBCASE(case1, array_cs_hb, axis);
    // FLIP_SUBCASE(case1, array_cs_db, axis);

    FLIP_SUBCASE(case1, array_fs_fb, axis);
    FLIP_SUBCASE(case1, array_fs_hb, axis);
    FLIP_SUBCASE(case1, array_fs_db, axis);

    FLIP_SUBCASE(case1, array_hs_fb, axis);
    FLIP_SUBCASE(case1, array_hs_hb, axis);
    FLIP_SUBCASE(case1, array_hs_db, axis);

    FLIP_SUBCASE(case1, array_ds_fb, axis);
    FLIP_SUBCASE(case1, array_ds_hb, axis);
    FLIP_SUBCASE(case1, array_ds_db, axis);

    // FLIP_SUBCASE(case1, array_ls_fb, axis);
    // FLIP_SUBCASE(case1, array_ls_hb, axis);
    // FLIP_SUBCASE(case1, array_ls_db, axis);
}

// TODO: fix for sycl kernel (opencl/cuda), remove free/malloc in kernel code
TEST_CASE("flip(case2)" * doctest::test_suite("array::flip") * doctest::skip())
{
    // FLIP_SUBCASE(case2, array, axis);
    // FLIP_SUBCASE(case2, array_a, axis);
    // FLIP_SUBCASE(case2, array_f, axis);
    // FLIP_SUBCASE(case2, array_h, axis);
    // FLIP_SUBCASE(case2, array_d, axis);

    // FLIP_SUBCASE(case2, array_cs_fb, axis);
    // FLIP_SUBCASE(case2, array_cs_hb, axis);
    // FLIP_SUBCASE(case2, array_cs_db, axis);

    FLIP_SUBCASE(case2, array_fs_fb, axis);
    FLIP_SUBCASE(case2, array_fs_hb, axis);
    FLIP_SUBCASE(case2, array_fs_db, axis);

    FLIP_SUBCASE(case2, array_hs_fb, axis);
    FLIP_SUBCASE(case2, array_hs_hb, axis);
    FLIP_SUBCASE(case2, array_hs_db, axis);

    FLIP_SUBCASE(case2, array_ds_fb, axis);
    FLIP_SUBCASE(case2, array_ds_hb, axis);
    FLIP_SUBCASE(case2, array_ds_db, axis);

    // FLIP_SUBCASE(case2, array_ls_fb, axis);
    // FLIP_SUBCASE(case2, array_ls_hb, axis);
    // FLIP_SUBCASE(case2, array_ls_db, axis);
}

// TODO: fix for sycl kernel (opencl/cuda), remove free/malloc in kernel code
TEST_CASE("flip(case3)" * doctest::test_suite("array::flip") * doctest::skip())
{
    // FLIP_SUBCASE(case3, array, axis);
    // FLIP_SUBCASE(case3, array_a, axis);
    // FLIP_SUBCASE(case3, array_f, axis);
    // FLIP_SUBCASE(case3, array_h, axis);
    // FLIP_SUBCASE(case3, array_d, axis);

    // FLIP_SUBCASE(case3, array_cs_fb, axis);
    // FLIP_SUBCASE(case3, array_cs_hb, axis);
    // FLIP_SUBCASE(case3, array_cs_db, axis);

    FLIP_SUBCASE(case3, array_fs_fb, axis);
    FLIP_SUBCASE(case3, array_fs_hb, axis);
    FLIP_SUBCASE(case3, array_fs_db, axis);

    FLIP_SUBCASE(case3, array_hs_fb, axis);
    FLIP_SUBCASE(case3, array_hs_hb, axis);
    FLIP_SUBCASE(case3, array_hs_db, axis);

    FLIP_SUBCASE(case3, array_ds_fb, axis);
    FLIP_SUBCASE(case3, array_ds_hb, axis);
    FLIP_SUBCASE(case3, array_ds_db, axis);

    // FLIP_SUBCASE(case3, array_ls_fb, axis);
    // FLIP_SUBCASE(case3, array_ls_hb, axis);
    // FLIP_SUBCASE(case3, array_ls_db, axis);
}

// TODO: fix for sycl kernel (opencl/cuda), remove free/malloc in kernel code
TEST_CASE("flip(case4)" * doctest::test_suite("array::flip") * doctest::skip())
{
    // FLIP_SUBCASE(case4, array, axis_a);
    // FLIP_SUBCASE(case4, array_a, axis_a);
    // FLIP_SUBCASE(case4, array_f, axis_a);
    // FLIP_SUBCASE(case4, array_h, axis_a);
    // FLIP_SUBCASE(case4, array_d, axis_a);

    // FLIP_SUBCASE(case4, array_cs_fb, axis_a);
    // FLIP_SUBCASE(case4, array_cs_hb, axis_a);
    // FLIP_SUBCASE(case4, array_cs_db, axis_a);

    FLIP_SUBCASE(case4, array_fs_fb, axis_a);
    FLIP_SUBCASE(case4, array_fs_hb, axis_a);
    FLIP_SUBCASE(case4, array_fs_db, axis_a);

    FLIP_SUBCASE(case4, array_hs_fb, axis_a);
    FLIP_SUBCASE(case4, array_hs_hb, axis_a);
    FLIP_SUBCASE(case4, array_hs_db, axis_a);

    FLIP_SUBCASE(case4, array_ds_fb, axis_a);
    FLIP_SUBCASE(case4, array_ds_hb, axis_a);
    FLIP_SUBCASE(case4, array_ds_db, axis_a);

    // FLIP_SUBCASE(case4, array_ls_fb, axis_a);
    // FLIP_SUBCASE(case4, array_ls_hb, axis_a);
    // FLIP_SUBCASE(case4, array_ls_db, axis_a);
}