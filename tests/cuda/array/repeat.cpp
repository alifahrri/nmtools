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

#include "nmtools/array/array/repeat.hpp"
#include "nmtools/testing/doctest.hpp"
#include "nmtools/array/eval/cuda.hpp"
#include "nmtools/testing/data/array/repeat.hpp"

namespace nm = nmtools;
namespace na = nm::array;
namespace cuda = na::cuda;

#define REPEAT_SUBCASE(case_name, ...) \
SUBCASE(#case_name) \
{ \
    NMTOOLS_TESTING_DECLARE_NS(array, repeat, case_name); \
    using namespace args; \
    auto result = na::repeat(__VA_ARGS__, cuda::default_context()); \
    auto expect = na::repeat(__VA_ARGS__); \
    NMTOOLS_ASSERT_EQUAL( nm::shape(result), nm::shape(expect) ); \
    NMTOOLS_ASSERT_CLOSE( result, expect ); \
}

TEST_CASE("repeat(case1)" * doctest::test_suite("array::repeat"))
{
    // REPEAT_SUBCASE(case1, array, repeats, axis);
    // REPEAT_SUBCASE(case1, array_a, repeats, axis);
    // REPEAT_SUBCASE(case1, array_f, repeats, axis);
    // REPEAT_SUBCASE(case1, array_h, repeats, axis);
    // REPEAT_SUBCASE(case1, array_d, repeats, axis);

    // REPEAT_SUBCASE(case1, array_cs_fb, repeats, axis);
    // REPEAT_SUBCASE(case1, array_cs_hb, repeats, axis);
    // REPEAT_SUBCASE(case1, array_cs_db, repeats, axis);

    REPEAT_SUBCASE(case1, array_fs_fb, repeats, axis);
    REPEAT_SUBCASE(case1, array_fs_hb, repeats, axis);
    REPEAT_SUBCASE(case1, array_fs_db, repeats, axis);

    REPEAT_SUBCASE(case1, array_hs_fb, repeats, axis);
    REPEAT_SUBCASE(case1, array_hs_hb, repeats, axis);
    REPEAT_SUBCASE(case1, array_hs_db, repeats, axis);

    REPEAT_SUBCASE(case1, array_ds_fb, repeats, axis);
    REPEAT_SUBCASE(case1, array_ds_hb, repeats, axis);
    REPEAT_SUBCASE(case1, array_ds_db, repeats, axis);

    // REPEAT_SUBCASE(case1, array_ls_fb, repeats, axis);
    // REPEAT_SUBCASE(case1, array_ls_hb, repeats, axis);
    // REPEAT_SUBCASE(case1, array_ls_db, repeats, axis);
}