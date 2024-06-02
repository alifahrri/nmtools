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

#include "nmtools/array/array/slice.hpp"
#include "nmtools/testing/doctest.hpp"
#include "nmtools/array/eval/hip.hpp"
#include "nmtools/utils/apply_isclose.hpp"

#if not(defined(__CUDA__) && defined(__CUDA_ARCH__))
#include "nmtools/testing/data/array/slice.hpp"
#endif

namespace nm = nmtools;
namespace na = nm::array;
namespace hip = na::hip;

#define NMTOOLS_ASSERT_APPLY_CLOSE(result,expect) \
CHECK_MESSAGE(nmtools::utils::apply_isclose(result,expect), \
    (   \
        std::string{} \
        + "\n\tActual  : " + STRINGIFY(result) \
        + "\n\tExpected: " + STRINGIFY(expect) \
    )   \
);

#define SLICE_SUBCASE(case_name, a, ...) \
SUBCASE(#case_name) \
{ \
    NMTOOLS_TESTING_USE_CASE(array, slice, case_name); \
    using namespace args; \
    auto result = na::apply_slice(a, nmtools_tuple{__VA_ARGS__}, hip::default_context()); \
    auto expect = na::apply_slice(a, nmtools_tuple{__VA_ARGS__}); \
    NMTOOLS_ASSERT_APPLY_CLOSE( result, expect ); \
}

#if not(defined(__CUDA__) && defined(__CUDA_ARCH__))
TEST_CASE("slice(case1)" * doctest::test_suite("array::slice"))
{
    // TODO: support data() for the following arrays
    // SLICE_SUBCASE(case1,   array, slice0, slice1, slice2);
    // SLICE_SUBCASE(case1, array_a, slice0, slice1, slice2);
    // SLICE_SUBCASE(case1, array_f, slice0, slice1, slice2);
    // SLICE_SUBCASE(case1, array_d, slice0, slice1, slice2);
    // SLICE_SUBCASE(case1, array_h, slice0, slice1, slice2);

    SLICE_SUBCASE(case1, array_fs_fb, slice0, slice1, slice2);
    SLICE_SUBCASE(case1, array_fs_hb, slice0, slice1, slice2);
    SLICE_SUBCASE(case1, array_fs_db, slice0, slice1, slice2);

    SLICE_SUBCASE(case1, array_hs_fb, slice0, slice1, slice2);
    SLICE_SUBCASE(case1, array_hs_hb, slice0, slice1, slice2);
    SLICE_SUBCASE(case1, array_hs_db, slice0, slice1, slice2);

    SLICE_SUBCASE(case1, array_ds_fb, slice0, slice1, slice2);
    SLICE_SUBCASE(case1, array_ds_hb, slice0, slice1, slice2);
    SLICE_SUBCASE(case1, array_ds_db, slice0, slice1, slice2);
}

TEST_CASE("slice(case2)" * doctest::test_suite("array::slice"))
{
    // TODO: support data() for the following arrays
    // SLICE_SUBCASE(case2,   array, slice0, slice1, slice2);
    // SLICE_SUBCASE(case2, array_a, slice0, slice1, slice2);
    // SLICE_SUBCASE(case2, array_f, slice0, slice1, slice2);
    // SLICE_SUBCASE(case2, array_d, slice0, slice1, slice2);
    // SLICE_SUBCASE(case2, array_h, slice0, slice1, slice2);

    SLICE_SUBCASE(case2, array_fs_fb, slice0, slice1, slice2);
    SLICE_SUBCASE(case2, array_fs_hb, slice0, slice1, slice2);
    SLICE_SUBCASE(case2, array_fs_db, slice0, slice1, slice2);

    SLICE_SUBCASE(case2, array_hs_fb, slice0, slice1, slice2);
    SLICE_SUBCASE(case2, array_hs_hb, slice0, slice1, slice2);
    SLICE_SUBCASE(case2, array_hs_db, slice0, slice1, slice2);

    SLICE_SUBCASE(case2, array_ds_fb, slice0, slice1, slice2);
    SLICE_SUBCASE(case2, array_ds_hb, slice0, slice1, slice2);
    SLICE_SUBCASE(case2, array_ds_db, slice0, slice1, slice2);
}

TEST_CASE("slice(case3)" * doctest::test_suite("array::slice"))
{
    // TODO: support data() for the following arrays
    // SLICE_SUBCASE(case3,   array, slice0, slice1, slice2);
    // SLICE_SUBCASE(case3, array_a, slice0, slice1, slice2);
    // SLICE_SUBCASE(case3, array_f, slice0, slice1, slice2);
    // SLICE_SUBCASE(case3, array_d, slice0, slice1, slice2);
    // SLICE_SUBCASE(case3, array_h, slice0, slice1, slice2);

    SLICE_SUBCASE(case3, array_fs_fb, slice0, slice1, slice2);
    SLICE_SUBCASE(case3, array_fs_hb, slice0, slice1, slice2);
    SLICE_SUBCASE(case3, array_fs_db, slice0, slice1, slice2);

    SLICE_SUBCASE(case3, array_hs_fb, slice0, slice1, slice2);
    SLICE_SUBCASE(case3, array_hs_hb, slice0, slice1, slice2);
    SLICE_SUBCASE(case3, array_hs_db, slice0, slice1, slice2);

    SLICE_SUBCASE(case3, array_ds_fb, slice0, slice1, slice2);
    SLICE_SUBCASE(case3, array_ds_hb, slice0, slice1, slice2);
    SLICE_SUBCASE(case3, array_ds_db, slice0, slice1, slice2);
}

TEST_CASE("slice(case4)" * doctest::test_suite("array::slice"))
{
    // TODO: support data() for the following arrays
    // SLICE_SUBCASE(case4,   array, slice0, slice1, slice2);
    // SLICE_SUBCASE(case4, array_a, slice0, slice1, slice2);
    // SLICE_SUBCASE(case4, array_f, slice0, slice1, slice2);
    // SLICE_SUBCASE(case4, array_d, slice0, slice1, slice2);
    // SLICE_SUBCASE(case4, array_h, slice0, slice1, slice2);

    SLICE_SUBCASE(case4, array_fs_fb, slice0, slice1, slice2);
    SLICE_SUBCASE(case4, array_fs_hb, slice0, slice1, slice2);
    SLICE_SUBCASE(case4, array_fs_db, slice0, slice1, slice2);

    SLICE_SUBCASE(case4, array_hs_fb, slice0, slice1, slice2);
    SLICE_SUBCASE(case4, array_hs_hb, slice0, slice1, slice2);
    SLICE_SUBCASE(case4, array_hs_db, slice0, slice1, slice2);

    SLICE_SUBCASE(case4, array_ds_fb, slice0, slice1, slice2);
    SLICE_SUBCASE(case4, array_ds_hb, slice0, slice1, slice2);
    SLICE_SUBCASE(case4, array_ds_db, slice0, slice1, slice2);
}

TEST_CASE("slice(case5)" * doctest::test_suite("array::slice"))
{
    // TODO: support data() for the following arrays
    // SLICE_SUBCASE(case5,   array, slice0, slice1, slice2);
    // SLICE_SUBCASE(case5, array_a, slice0, slice1, slice2);
    // SLICE_SUBCASE(case5, array_f, slice0, slice1, slice2);
    // SLICE_SUBCASE(case5, array_d, slice0, slice1, slice2);
    // SLICE_SUBCASE(case5, array_h, slice0, slice1, slice2);

    SLICE_SUBCASE(case5, array_fs_fb, slice0, slice1, slice2);
    SLICE_SUBCASE(case5, array_fs_hb, slice0, slice1, slice2);
    SLICE_SUBCASE(case5, array_fs_db, slice0, slice1, slice2);

    SLICE_SUBCASE(case5, array_hs_fb, slice0, slice1, slice2);
    SLICE_SUBCASE(case5, array_hs_hb, slice0, slice1, slice2);
    SLICE_SUBCASE(case5, array_hs_db, slice0, slice1, slice2);

    SLICE_SUBCASE(case5, array_ds_fb, slice0, slice1, slice2);
    SLICE_SUBCASE(case5, array_ds_hb, slice0, slice1, slice2);
    SLICE_SUBCASE(case5, array_ds_db, slice0, slice1, slice2);
}

TEST_CASE("slice(case6)" * doctest::test_suite("array::slice"))
{
    // TODO: support data() for the following arrays
    // SLICE_SUBCASE(case6,   array, slice0, slice1, slice2);
    // SLICE_SUBCASE(case6, array_a, slice0, slice1, slice2);
    // SLICE_SUBCASE(case6, array_f, slice0, slice1, slice2);
    // SLICE_SUBCASE(case6, array_d, slice0, slice1, slice2);
    // SLICE_SUBCASE(case6, array_h, slice0, slice1, slice2);

    SLICE_SUBCASE(case6, array_fs_fb, slice0, slice1, slice2);
    SLICE_SUBCASE(case6, array_fs_hb, slice0, slice1, slice2);
    SLICE_SUBCASE(case6, array_fs_db, slice0, slice1, slice2);

    SLICE_SUBCASE(case6, array_hs_fb, slice0, slice1, slice2);
    SLICE_SUBCASE(case6, array_hs_hb, slice0, slice1, slice2);
    SLICE_SUBCASE(case6, array_hs_db, slice0, slice1, slice2);

    SLICE_SUBCASE(case6, array_ds_fb, slice0, slice1, slice2);
    SLICE_SUBCASE(case6, array_ds_hb, slice0, slice1, slice2);
    SLICE_SUBCASE(case6, array_ds_db, slice0, slice1, slice2);
}

TEST_CASE("slice(case7)" * doctest::test_suite("array::slice"))
{
    // TODO: support data() for the following arrays
    // SLICE_SUBCASE(case7,   array, slice0, slice1, slice2);
    // SLICE_SUBCASE(case7, array_a, slice0, slice1, slice2);
    // SLICE_SUBCASE(case7, array_f, slice0, slice1, slice2);
    // SLICE_SUBCASE(case7, array_d, slice0, slice1, slice2);
    // SLICE_SUBCASE(case7, array_h, slice0, slice1, slice2);

    SLICE_SUBCASE(case7, array_fs_fb, slice0, slice1, slice2);
    SLICE_SUBCASE(case7, array_fs_hb, slice0, slice1, slice2);
    SLICE_SUBCASE(case7, array_fs_db, slice0, slice1, slice2);

    SLICE_SUBCASE(case7, array_hs_fb, slice0, slice1, slice2);
    SLICE_SUBCASE(case7, array_hs_hb, slice0, slice1, slice2);
    SLICE_SUBCASE(case7, array_hs_db, slice0, slice1, slice2);

    SLICE_SUBCASE(case7, array_ds_fb, slice0, slice1, slice2);
    SLICE_SUBCASE(case7, array_ds_hb, slice0, slice1, slice2);
    SLICE_SUBCASE(case7, array_ds_db, slice0, slice1, slice2);
}

TEST_CASE("slice(case8)" * doctest::test_suite("array::slice"))
{
    // TODO: support data() for the following arrays
    // SLICE_SUBCASE(case8,   array, slice0, slice1, slice2);
    // SLICE_SUBCASE(case8, array_a, slice0, slice1, slice2);
    // SLICE_SUBCASE(case8, array_f, slice0, slice1, slice2);
    // SLICE_SUBCASE(case8, array_d, slice0, slice1, slice2);
    // SLICE_SUBCASE(case8, array_h, slice0, slice1, slice2);

    SLICE_SUBCASE(case8, array_fs_fb, slice0, slice1, slice2);
    SLICE_SUBCASE(case8, array_fs_hb, slice0, slice1, slice2);
    SLICE_SUBCASE(case8, array_fs_db, slice0, slice1, slice2);

    SLICE_SUBCASE(case8, array_hs_fb, slice0, slice1, slice2);
    SLICE_SUBCASE(case8, array_hs_hb, slice0, slice1, slice2);
    SLICE_SUBCASE(case8, array_hs_db, slice0, slice1, slice2);

    SLICE_SUBCASE(case8, array_ds_fb, slice0, slice1, slice2);
    SLICE_SUBCASE(case8, array_ds_hb, slice0, slice1, slice2);
    SLICE_SUBCASE(case8, array_ds_db, slice0, slice1, slice2);
}

TEST_CASE("slice(case9)" * doctest::test_suite("array::slice"))
{
    // TODO: support data() for the following arrays
    // SLICE_SUBCASE(case9,   array, slice0, slice1, slice2);
    // SLICE_SUBCASE(case9, array_a, slice0, slice1, slice2);
    // SLICE_SUBCASE(case9, array_f, slice0, slice1, slice2);
    // SLICE_SUBCASE(case9, array_d, slice0, slice1, slice2);
    // SLICE_SUBCASE(case9, array_h, slice0, slice1, slice2);

    SLICE_SUBCASE(case9, array_fs_fb, slice0, slice1, slice2);
    SLICE_SUBCASE(case9, array_fs_hb, slice0, slice1, slice2);
    SLICE_SUBCASE(case9, array_fs_db, slice0, slice1, slice2);

    SLICE_SUBCASE(case9, array_hs_fb, slice0, slice1, slice2);
    SLICE_SUBCASE(case9, array_hs_hb, slice0, slice1, slice2);
    SLICE_SUBCASE(case9, array_hs_db, slice0, slice1, slice2);

    SLICE_SUBCASE(case9, array_ds_fb, slice0, slice1, slice2);
    SLICE_SUBCASE(case9, array_ds_hb, slice0, slice1, slice2);
    SLICE_SUBCASE(case9, array_ds_db, slice0, slice1, slice2);
}

TEST_CASE("slice(case10)" * doctest::test_suite("array::slice"))
{
    // TODO: support data() for the following arrays
    // SLICE_SUBCASE(case10,   array, slice0, slice1, slice2);
    // SLICE_SUBCASE(case10, array_a, slice0, slice1, slice2);
    // SLICE_SUBCASE(case10, array_f, slice0, slice1, slice2);
    // SLICE_SUBCASE(case10, array_d, slice0, slice1, slice2);
    // SLICE_SUBCASE(case10, array_h, slice0, slice1, slice2);

    SLICE_SUBCASE(case10, array_fs_fb, slice0, slice1, slice2);
    SLICE_SUBCASE(case10, array_fs_hb, slice0, slice1, slice2);
    SLICE_SUBCASE(case10, array_fs_db, slice0, slice1, slice2);

    SLICE_SUBCASE(case10, array_hs_fb, slice0, slice1, slice2);
    SLICE_SUBCASE(case10, array_hs_hb, slice0, slice1, slice2);
    SLICE_SUBCASE(case10, array_hs_db, slice0, slice1, slice2);

    SLICE_SUBCASE(case10, array_ds_fb, slice0, slice1, slice2);
    SLICE_SUBCASE(case10, array_ds_hb, slice0, slice1, slice2);
    SLICE_SUBCASE(case10, array_ds_db, slice0, slice1, slice2);
}
#endif