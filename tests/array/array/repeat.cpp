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

#include "nmtools/array/array/repeat.hpp"
#include "nmtools/testing/data/array/repeat.hpp"
#include "nmtools/constants.hpp"
#include "nmtools/testing/doctest.hpp"

namespace nm = nmtools;
namespace na = nm::array;

#define RUN_impl(...) \
nm::array::repeat(__VA_ARGS__);

#ifdef NMTOOLS_TESTING_ENABLE_BENCHMARKS
#include "nmtools/benchmarks/bench.hpp"
using nm::benchmarks::TrackedBench;
// create immediately invoked lambda
// that packs repeat fn to callable lambda
#define RUN_repeat(case_name, ...) \
[](auto&&...args){ \
    auto title = std::string("repeat-") + #case_name; \
    auto name  = nm::testing::make_func_args("", args...); \
    auto fn    = [&](){ \
        return RUN_impl(args...); \
    }; \
    return TrackedBench::run(title, name, fn); \
}(__VA_ARGS__);
#else
// run normally without benchmarking, ignore case_name
#define RUN_repeat(case_name, ...) \
RUN_impl(__VA_ARGS__);
#endif // NMTOOLS_TESTING_ENABLE_BENCHMARKS

#define REPEAT_SUBCASE(case_name, array_input, repeats, axis) \
SUBCASE(#case_name) \
{ \
    NMTOOLS_TESTING_DECLARE_NS(array, repeat, case_name); \
    auto array_array = RUN_repeat(case_name, args::array_input, args::repeats, args::axis); \
    NMTOOLS_ASSERT_EQUAL( nm::shape(array_array), expect::shape ); \
    NMTOOLS_ASSERT_EQUAL( nm::dim(array_array), expect::dim ); \
    NMTOOLS_ASSERT_CLOSE( array_array, expect::result ); \
}

TEST_CASE("repeat(case1)" * doctest::test_suite("array::repeat"))
{
    #if !defined(NMTOOLS_TESTING_GENERIC_NDARRAY)
    REPEAT_SUBCASE(case1, array_a, repeats, axis);
    REPEAT_SUBCASE(case1, array_f, repeats, axis);
    REPEAT_SUBCASE(case1, array_d, repeats, axis);
    REPEAT_SUBCASE(case1, array_h, repeats, axis);

    #else
    REPEAT_SUBCASE(case1, array_cs_fb, repeats, axis);
    REPEAT_SUBCASE(case1, array_cs_hb, repeats, axis);
    REPEAT_SUBCASE(case1, array_cs_db, repeats, axis);

    REPEAT_SUBCASE(case1, array_fs_fb, repeats, axis);
    REPEAT_SUBCASE(case1, array_fs_hb, repeats, axis);
    REPEAT_SUBCASE(case1, array_fs_db, repeats, axis);

    REPEAT_SUBCASE(case1, array_hs_fb, repeats, axis);
    REPEAT_SUBCASE(case1, array_hs_hb, repeats, axis);
    REPEAT_SUBCASE(case1, array_hs_db, repeats, axis);

    REPEAT_SUBCASE(case1, array_ds_fb, repeats, axis);
    REPEAT_SUBCASE(case1, array_ds_hb, repeats, axis);
    REPEAT_SUBCASE(case1, array_ds_db, repeats, axis);

    REPEAT_SUBCASE(case1, array_ls_fb, repeats, axis);
    REPEAT_SUBCASE(case1, array_ls_hb, repeats, axis);
    REPEAT_SUBCASE(case1, array_ls_db, repeats, axis);

    REPEAT_SUBCASE(case1, array_cs_fb, repeats_ct, axis);
    REPEAT_SUBCASE(case1, array_cs_hb, repeats_ct, axis);
    REPEAT_SUBCASE(case1, array_cs_db, repeats_ct, axis);

    REPEAT_SUBCASE(case1, array_fs_fb, repeats_ct, axis);
    REPEAT_SUBCASE(case1, array_fs_hb, repeats_ct, axis);
    REPEAT_SUBCASE(case1, array_fs_db, repeats_ct, axis);

    REPEAT_SUBCASE(case1, array_hs_fb, repeats_ct, axis);
    REPEAT_SUBCASE(case1, array_hs_hb, repeats_ct, axis);
    REPEAT_SUBCASE(case1, array_hs_db, repeats_ct, axis);

    REPEAT_SUBCASE(case1, array_ds_fb, repeats_ct, axis);
    REPEAT_SUBCASE(case1, array_ds_hb, repeats_ct, axis);
    REPEAT_SUBCASE(case1, array_ds_db, repeats_ct, axis);

    REPEAT_SUBCASE(case1, array_ls_fb, repeats_ct, axis);
    REPEAT_SUBCASE(case1, array_ls_hb, repeats_ct, axis);
    REPEAT_SUBCASE(case1, array_ls_db, repeats_ct, axis);
    #endif
}

TEST_CASE("repeat(case2)" * doctest::test_suite("array::repeat"))
{
    #if !defined(NMTOOLS_TESTING_GENERIC_NDARRAY)
    REPEAT_SUBCASE(case2, array_a, repeats, axis);
    REPEAT_SUBCASE(case2, array_f, repeats, axis);
    REPEAT_SUBCASE(case2, array_d, repeats, axis);
    REPEAT_SUBCASE(case2, array_h, repeats, axis);

    #else
    REPEAT_SUBCASE(case2, array_cs_fb, repeats, axis);
    REPEAT_SUBCASE(case2, array_cs_hb, repeats, axis);
    REPEAT_SUBCASE(case2, array_cs_db, repeats, axis);

    REPEAT_SUBCASE(case2, array_fs_fb, repeats, axis);
    REPEAT_SUBCASE(case2, array_fs_hb, repeats, axis);
    REPEAT_SUBCASE(case2, array_fs_db, repeats, axis);

    REPEAT_SUBCASE(case2, array_hs_fb, repeats, axis);
    REPEAT_SUBCASE(case2, array_hs_hb, repeats, axis);
    REPEAT_SUBCASE(case2, array_hs_db, repeats, axis);

    REPEAT_SUBCASE(case2, array_ds_fb, repeats, axis);
    REPEAT_SUBCASE(case2, array_ds_hb, repeats, axis);
    REPEAT_SUBCASE(case2, array_ds_db, repeats, axis);

    REPEAT_SUBCASE(case2, array_ls_fb, repeats, axis);
    REPEAT_SUBCASE(case2, array_ls_hb, repeats, axis);
    REPEAT_SUBCASE(case2, array_ls_db, repeats, axis);

    REPEAT_SUBCASE(case2, array_cs_fb, repeats_ct, axis_ct);
    REPEAT_SUBCASE(case2, array_cs_hb, repeats_ct, axis_ct);
    REPEAT_SUBCASE(case2, array_cs_db, repeats_ct, axis_ct);

    REPEAT_SUBCASE(case2, array_fs_fb, repeats_ct, axis_ct);
    REPEAT_SUBCASE(case2, array_fs_hb, repeats_ct, axis_ct);
    REPEAT_SUBCASE(case2, array_fs_db, repeats_ct, axis_ct);

    REPEAT_SUBCASE(case2, array_hs_fb, repeats_ct, axis_ct);
    REPEAT_SUBCASE(case2, array_hs_hb, repeats_ct, axis_ct);
    REPEAT_SUBCASE(case2, array_hs_db, repeats_ct, axis_ct);

    REPEAT_SUBCASE(case2, array_ds_fb, repeats_ct, axis_ct);
    REPEAT_SUBCASE(case2, array_ds_hb, repeats_ct, axis_ct);
    REPEAT_SUBCASE(case2, array_ds_db, repeats_ct, axis_ct);

    REPEAT_SUBCASE(case2, array_ls_fb, repeats_ct, axis_ct);
    REPEAT_SUBCASE(case2, array_ls_hb, repeats_ct, axis_ct);
    REPEAT_SUBCASE(case2, array_ls_db, repeats_ct, axis_ct);

    REPEAT_SUBCASE(case2, array_cs_fb, repeats, axis_ct);
    REPEAT_SUBCASE(case2, array_cs_hb, repeats, axis_ct);
    REPEAT_SUBCASE(case2, array_cs_db, repeats, axis_ct);

    REPEAT_SUBCASE(case2, array_fs_fb, repeats, axis_ct);
    REPEAT_SUBCASE(case2, array_fs_hb, repeats, axis_ct);
    REPEAT_SUBCASE(case2, array_fs_db, repeats, axis_ct);

    REPEAT_SUBCASE(case2, array_hs_fb, repeats, axis_ct);
    REPEAT_SUBCASE(case2, array_hs_hb, repeats, axis_ct);
    REPEAT_SUBCASE(case2, array_hs_db, repeats, axis_ct);

    REPEAT_SUBCASE(case2, array_ds_fb, repeats, axis_ct);
    REPEAT_SUBCASE(case2, array_ds_hb, repeats, axis_ct);
    REPEAT_SUBCASE(case2, array_ds_db, repeats, axis_ct);

    REPEAT_SUBCASE(case2, array_ls_fb, repeats, axis_ct);
    REPEAT_SUBCASE(case2, array_ls_hb, repeats, axis_ct);
    REPEAT_SUBCASE(case2, array_ls_db, repeats, axis_ct);
    #endif
}

TEST_CASE("repeat(case3)" * doctest::test_suite("array::repeat"))
{
    #if !defined(NMTOOLS_TESTING_GENERIC_NDARRAY)
    REPEAT_SUBCASE(case3, array_a, repeats, axis);
    REPEAT_SUBCASE(case3, array_f, repeats, axis);
    REPEAT_SUBCASE(case3, array_d, repeats, axis);
    REPEAT_SUBCASE(case3, array_h, repeats, axis);

    #else
    REPEAT_SUBCASE(case3, array_cs_fb, repeats, axis);
    REPEAT_SUBCASE(case3, array_cs_hb, repeats, axis);
    REPEAT_SUBCASE(case3, array_cs_db, repeats, axis);

    REPEAT_SUBCASE(case3, array_fs_fb, repeats, axis);
    REPEAT_SUBCASE(case3, array_fs_hb, repeats, axis);
    REPEAT_SUBCASE(case3, array_fs_db, repeats, axis);

    REPEAT_SUBCASE(case3, array_hs_fb, repeats, axis);
    REPEAT_SUBCASE(case3, array_hs_hb, repeats, axis);
    REPEAT_SUBCASE(case3, array_hs_db, repeats, axis);

    REPEAT_SUBCASE(case3, array_ds_fb, repeats, axis);
    REPEAT_SUBCASE(case3, array_ds_hb, repeats, axis);
    REPEAT_SUBCASE(case3, array_ds_db, repeats, axis);

    REPEAT_SUBCASE(case3, array_ls_fb, repeats, axis);
    REPEAT_SUBCASE(case3, array_ls_hb, repeats, axis);
    REPEAT_SUBCASE(case3, array_ls_db, repeats, axis);
    #endif
}

TEST_CASE("repeat(case4)" * doctest::test_suite("array::repeat"))
{
    #if !defined(NMTOOLS_TESTING_GENERIC_NDARRAY)
    REPEAT_SUBCASE(case4, array_a, repeats, axis);
    REPEAT_SUBCASE(case4, array_f, repeats, axis);
    REPEAT_SUBCASE(case4, array_d, repeats, axis);
    REPEAT_SUBCASE(case4, array_h, repeats, axis);

    #else
    REPEAT_SUBCASE(case4, array_cs_fb, repeats, axis);
    REPEAT_SUBCASE(case4, array_cs_hb, repeats, axis);
    REPEAT_SUBCASE(case4, array_cs_db, repeats, axis);

    REPEAT_SUBCASE(case4, array_fs_fb, repeats, axis);
    REPEAT_SUBCASE(case4, array_fs_hb, repeats, axis);
    REPEAT_SUBCASE(case4, array_fs_db, repeats, axis);

    REPEAT_SUBCASE(case4, array_hs_fb, repeats, axis);
    REPEAT_SUBCASE(case4, array_hs_hb, repeats, axis);
    REPEAT_SUBCASE(case4, array_hs_db, repeats, axis);

    REPEAT_SUBCASE(case4, array_ds_fb, repeats, axis);
    REPEAT_SUBCASE(case4, array_ds_hb, repeats, axis);
    REPEAT_SUBCASE(case4, array_ds_db, repeats, axis);

    REPEAT_SUBCASE(case4, array_ls_fb, repeats, axis);
    REPEAT_SUBCASE(case4, array_ls_hb, repeats, axis);
    REPEAT_SUBCASE(case4, array_ls_db, repeats, axis);

    REPEAT_SUBCASE(case4, array_cs_fb, repeats_ct, axis_ct);
    REPEAT_SUBCASE(case4, array_cs_hb, repeats_ct, axis_ct);
    REPEAT_SUBCASE(case4, array_cs_db, repeats_ct, axis_ct);

    REPEAT_SUBCASE(case4, array_fs_fb, repeats_ct, axis_ct);
    REPEAT_SUBCASE(case4, array_fs_hb, repeats_ct, axis_ct);
    REPEAT_SUBCASE(case4, array_fs_db, repeats_ct, axis_ct);

    REPEAT_SUBCASE(case4, array_hs_fb, repeats_ct, axis_ct);
    REPEAT_SUBCASE(case4, array_hs_hb, repeats_ct, axis_ct);
    REPEAT_SUBCASE(case4, array_hs_db, repeats_ct, axis_ct);

    REPEAT_SUBCASE(case4, array_ds_fb, repeats_ct, axis_ct);
    REPEAT_SUBCASE(case4, array_ds_hb, repeats_ct, axis_ct);
    REPEAT_SUBCASE(case4, array_ds_db, repeats_ct, axis_ct);

    REPEAT_SUBCASE(case4, array_ls_fb, repeats_ct, axis_ct);
    REPEAT_SUBCASE(case4, array_ls_hb, repeats_ct, axis_ct);
    REPEAT_SUBCASE(case4, array_ls_db, repeats_ct, axis_ct);

    REPEAT_SUBCASE(case4, array_cs_fb, repeats_ct, axis_ct);
    REPEAT_SUBCASE(case4, array_cs_hb, repeats_ct, axis_ct);
    REPEAT_SUBCASE(case4, array_cs_db, repeats_ct, axis_ct);

    REPEAT_SUBCASE(case4, array_fs_fb, repeats_ct, axis_ct);
    REPEAT_SUBCASE(case4, array_fs_hb, repeats_ct, axis_ct);
    REPEAT_SUBCASE(case4, array_fs_db, repeats_ct, axis_ct);

    REPEAT_SUBCASE(case4, array_hs_fb, repeats_ct, axis_ct);
    REPEAT_SUBCASE(case4, array_hs_hb, repeats_ct, axis_ct);
    REPEAT_SUBCASE(case4, array_hs_db, repeats_ct, axis_ct);

    REPEAT_SUBCASE(case4, array_ds_fb, repeats_ct, axis_ct);
    REPEAT_SUBCASE(case4, array_ds_hb, repeats_ct, axis_ct);
    REPEAT_SUBCASE(case4, array_ds_db, repeats_ct, axis_ct);

    REPEAT_SUBCASE(case4, array_ls_fb, repeats_ct, axis_ct);
    REPEAT_SUBCASE(case4, array_ls_hb, repeats_ct, axis_ct);
    REPEAT_SUBCASE(case4, array_ls_db, repeats_ct, axis_ct);

    REPEAT_SUBCASE(case4, array_cs_fb, repeats, axis_ct);
    REPEAT_SUBCASE(case4, array_cs_hb, repeats, axis_ct);
    REPEAT_SUBCASE(case4, array_cs_db, repeats, axis_ct);

    REPEAT_SUBCASE(case4, array_fs_fb, repeats, axis_ct);
    REPEAT_SUBCASE(case4, array_fs_hb, repeats, axis_ct);
    REPEAT_SUBCASE(case4, array_fs_db, repeats, axis_ct);

    REPEAT_SUBCASE(case4, array_hs_fb, repeats, axis_ct);
    REPEAT_SUBCASE(case4, array_hs_hb, repeats, axis_ct);
    REPEAT_SUBCASE(case4, array_hs_db, repeats, axis_ct);

    REPEAT_SUBCASE(case4, array_ds_fb, repeats, axis_ct);
    REPEAT_SUBCASE(case4, array_ds_hb, repeats, axis_ct);
    REPEAT_SUBCASE(case4, array_ds_db, repeats, axis_ct);

    REPEAT_SUBCASE(case4, array_ls_fb, repeats, axis_ct);
    REPEAT_SUBCASE(case4, array_ls_hb, repeats, axis_ct);
    REPEAT_SUBCASE(case4, array_ls_db, repeats, axis_ct);

    REPEAT_SUBCASE(case4, array_cs_fb, repeats_ct, axis);
    REPEAT_SUBCASE(case4, array_cs_hb, repeats_ct, axis);
    REPEAT_SUBCASE(case4, array_cs_db, repeats_ct, axis);

    REPEAT_SUBCASE(case4, array_fs_fb, repeats_ct, axis);
    REPEAT_SUBCASE(case4, array_fs_hb, repeats_ct, axis);
    REPEAT_SUBCASE(case4, array_fs_db, repeats_ct, axis);

    REPEAT_SUBCASE(case4, array_hs_fb, repeats_ct, axis);
    REPEAT_SUBCASE(case4, array_hs_hb, repeats_ct, axis);
    REPEAT_SUBCASE(case4, array_hs_db, repeats_ct, axis);

    REPEAT_SUBCASE(case4, array_ds_fb, repeats_ct, axis);
    REPEAT_SUBCASE(case4, array_ds_hb, repeats_ct, axis);
    REPEAT_SUBCASE(case4, array_ds_db, repeats_ct, axis);

    REPEAT_SUBCASE(case4, array_ls_fb, repeats_ct, axis);
    REPEAT_SUBCASE(case4, array_ls_hb, repeats_ct, axis);
    REPEAT_SUBCASE(case4, array_ls_db, repeats_ct, axis);

    ////////////////////////////////////////////////////

    REPEAT_SUBCASE(case4, array_cs_fb, repeats_cl, axis_cl);
    REPEAT_SUBCASE(case4, array_cs_hb, repeats_cl, axis_cl);
    REPEAT_SUBCASE(case4, array_cs_db, repeats_cl, axis_cl);

    REPEAT_SUBCASE(case4, array_fs_fb, repeats_cl, axis_cl);
    REPEAT_SUBCASE(case4, array_fs_hb, repeats_cl, axis_cl);
    REPEAT_SUBCASE(case4, array_fs_db, repeats_cl, axis_cl);

    REPEAT_SUBCASE(case4, array_hs_fb, repeats_cl, axis_ct);
    REPEAT_SUBCASE(case4, array_hs_hb, repeats_cl, axis_ct);
    REPEAT_SUBCASE(case4, array_hs_db, repeats_cl, axis_ct);

    REPEAT_SUBCASE(case4, array_ds_fb, repeats_cl, axis_cl);
    REPEAT_SUBCASE(case4, array_ds_hb, repeats_cl, axis_cl);
    REPEAT_SUBCASE(case4, array_ds_db, repeats_cl, axis_cl);

    REPEAT_SUBCASE(case4, array_ls_fb, repeats_cl, axis_cl);
    REPEAT_SUBCASE(case4, array_ls_hb, repeats_cl, axis_cl);
    REPEAT_SUBCASE(case4, array_ls_db, repeats_cl, axis_cl);

    REPEAT_SUBCASE(case4, array_cs_fb, repeats_cl, axis_cl);
    REPEAT_SUBCASE(case4, array_cs_hb, repeats_cl, axis_cl);
    REPEAT_SUBCASE(case4, array_cs_db, repeats_cl, axis_cl);

    REPEAT_SUBCASE(case4, array_fs_fb, repeats_cl, axis_cl);
    REPEAT_SUBCASE(case4, array_fs_hb, repeats_cl, axis_cl);
    REPEAT_SUBCASE(case4, array_fs_db, repeats_cl, axis_cl);

    REPEAT_SUBCASE(case4, array_hs_fb, repeats_cl, axis_cl);
    REPEAT_SUBCASE(case4, array_hs_hb, repeats_cl, axis_cl);
    REPEAT_SUBCASE(case4, array_hs_db, repeats_cl, axis_cl);

    REPEAT_SUBCASE(case4, array_ds_fb, repeats_cl, axis_cl);
    REPEAT_SUBCASE(case4, array_ds_hb, repeats_cl, axis_cl);
    REPEAT_SUBCASE(case4, array_ds_db, repeats_cl, axis_cl);

    REPEAT_SUBCASE(case4, array_ls_fb, repeats_cl, axis_cl);
    REPEAT_SUBCASE(case4, array_ls_hb, repeats_cl, axis_cl);
    REPEAT_SUBCASE(case4, array_ls_db, repeats_cl, axis_cl);

    REPEAT_SUBCASE(case4, array_cs_fb, repeats, axis_cl);
    REPEAT_SUBCASE(case4, array_cs_hb, repeats, axis_cl);
    REPEAT_SUBCASE(case4, array_cs_db, repeats, axis_cl);

    REPEAT_SUBCASE(case4, array_fs_fb, repeats, axis_cl);
    REPEAT_SUBCASE(case4, array_fs_hb, repeats, axis_cl);
    REPEAT_SUBCASE(case4, array_fs_db, repeats, axis_cl);

    REPEAT_SUBCASE(case4, array_hs_fb, repeats, axis_cl);
    REPEAT_SUBCASE(case4, array_hs_hb, repeats, axis_cl);
    REPEAT_SUBCASE(case4, array_hs_db, repeats, axis_cl);

    REPEAT_SUBCASE(case4, array_ds_fb, repeats, axis_cl);
    REPEAT_SUBCASE(case4, array_ds_hb, repeats, axis_cl);
    REPEAT_SUBCASE(case4, array_ds_db, repeats, axis_cl);

    REPEAT_SUBCASE(case4, array_ls_fb, repeats, axis_cl);
    REPEAT_SUBCASE(case4, array_ls_hb, repeats, axis_cl);
    REPEAT_SUBCASE(case4, array_ls_db, repeats, axis_cl);

    REPEAT_SUBCASE(case4, array_cs_fb, repeats_cl, axis);
    REPEAT_SUBCASE(case4, array_cs_hb, repeats_cl, axis);
    REPEAT_SUBCASE(case4, array_cs_db, repeats_cl, axis);

    REPEAT_SUBCASE(case4, array_fs_fb, repeats_cl, axis);
    REPEAT_SUBCASE(case4, array_fs_hb, repeats_cl, axis);
    REPEAT_SUBCASE(case4, array_fs_db, repeats_cl, axis);

    REPEAT_SUBCASE(case4, array_hs_fb, repeats_ct, axis);
    REPEAT_SUBCASE(case4, array_hs_hb, repeats_ct, axis);
    REPEAT_SUBCASE(case4, array_hs_db, repeats_ct, axis);

    REPEAT_SUBCASE(case4, array_ds_fb, repeats_cl, axis);
    REPEAT_SUBCASE(case4, array_ds_hb, repeats_cl, axis);
    REPEAT_SUBCASE(case4, array_ds_db, repeats_cl, axis);

    REPEAT_SUBCASE(case4, array_ls_fb, repeats_cl, axis);
    REPEAT_SUBCASE(case4, array_ls_hb, repeats_cl, axis);
    REPEAT_SUBCASE(case4, array_ls_db, repeats_cl, axis);
    #endif
}

TEST_CASE("repeat(case5)" * doctest::test_suite("array::repeat"))
{
    #if !defined(NMTOOLS_TESTING_GENERIC_NDARRAY)
    REPEAT_SUBCASE(case5, array_a, repeats, axis);
    REPEAT_SUBCASE(case5, array_f, repeats, axis);
    REPEAT_SUBCASE(case5, array_d, repeats, axis);
    REPEAT_SUBCASE(case5, array_h, repeats, axis);

    #else
    REPEAT_SUBCASE(case5, array_cs_fb, repeats, axis);
    REPEAT_SUBCASE(case5, array_cs_hb, repeats, axis);
    REPEAT_SUBCASE(case5, array_cs_db, repeats, axis);

    REPEAT_SUBCASE(case5, array_fs_fb, repeats, axis);
    REPEAT_SUBCASE(case5, array_fs_hb, repeats, axis);
    REPEAT_SUBCASE(case5, array_fs_db, repeats, axis);

    REPEAT_SUBCASE(case5, array_hs_fb, repeats, axis);
    REPEAT_SUBCASE(case5, array_hs_hb, repeats, axis);
    REPEAT_SUBCASE(case5, array_hs_db, repeats, axis);

    REPEAT_SUBCASE(case5, array_ds_fb, repeats, axis);
    REPEAT_SUBCASE(case5, array_ds_hb, repeats, axis);
    REPEAT_SUBCASE(case5, array_ds_db, repeats, axis);

    REPEAT_SUBCASE(case5, array_ls_fb, repeats, axis);
    REPEAT_SUBCASE(case5, array_ls_hb, repeats, axis);
    REPEAT_SUBCASE(case5, array_ls_db, repeats, axis);

    REPEAT_SUBCASE(case5, array_cs_fb, repeats_ct, axis_ct);
    REPEAT_SUBCASE(case5, array_cs_hb, repeats_ct, axis_ct);
    REPEAT_SUBCASE(case5, array_cs_db, repeats_ct, axis_ct);

    REPEAT_SUBCASE(case5, array_fs_fb, repeats_ct, axis_ct);
    REPEAT_SUBCASE(case5, array_fs_hb, repeats_ct, axis_ct);
    REPEAT_SUBCASE(case5, array_fs_db, repeats_ct, axis_ct);

    REPEAT_SUBCASE(case5, array_hs_fb, repeats_ct, axis_ct);
    REPEAT_SUBCASE(case5, array_hs_hb, repeats_ct, axis_ct);
    REPEAT_SUBCASE(case5, array_hs_db, repeats_ct, axis_ct);

    REPEAT_SUBCASE(case5, array_ds_fb, repeats_ct, axis_ct);
    REPEAT_SUBCASE(case5, array_ds_hb, repeats_ct, axis_ct);
    REPEAT_SUBCASE(case5, array_ds_db, repeats_ct, axis_ct);

    REPEAT_SUBCASE(case5, array_ls_fb, repeats_ct, axis_ct);
    REPEAT_SUBCASE(case5, array_ls_hb, repeats_ct, axis_ct);
    REPEAT_SUBCASE(case5, array_ls_db, repeats_ct, axis_ct);

    REPEAT_SUBCASE(case5, array_cs_fb, repeats_cl, axis_ct);
    REPEAT_SUBCASE(case5, array_cs_hb, repeats_cl, axis_ct);
    REPEAT_SUBCASE(case5, array_cs_db, repeats_cl, axis_ct);

    REPEAT_SUBCASE(case5, array_fs_fb, repeats_cl, axis_ct);
    REPEAT_SUBCASE(case5, array_fs_hb, repeats_cl, axis_ct);
    REPEAT_SUBCASE(case5, array_fs_db, repeats_cl, axis_ct);

    REPEAT_SUBCASE(case5, array_hs_fb, repeats_cl, axis_ct);
    REPEAT_SUBCASE(case5, array_hs_hb, repeats_cl, axis_ct);
    REPEAT_SUBCASE(case5, array_hs_db, repeats_cl, axis_ct);

    REPEAT_SUBCASE(case5, array_ds_fb, repeats_cl, axis_ct);
    REPEAT_SUBCASE(case5, array_ds_hb, repeats_cl, axis_ct);
    REPEAT_SUBCASE(case5, array_ds_db, repeats_cl, axis_ct);

    REPEAT_SUBCASE(case5, array_ls_fb, repeats_cl, axis_ct);
    REPEAT_SUBCASE(case5, array_ls_hb, repeats_cl, axis_ct);
    REPEAT_SUBCASE(case5, array_ls_db, repeats_cl, axis_ct);
    #endif
}

TEST_CASE("repeat(case6)" * doctest::test_suite("array::repeat"))
{
    #if !defined(NMTOOLS_TESTING_GENERIC_NDARRAY)
    REPEAT_SUBCASE(case6, array_a, repeats, axis);
    REPEAT_SUBCASE(case6, array_f, repeats, axis);
    REPEAT_SUBCASE(case6, array_d, repeats, axis);
    REPEAT_SUBCASE(case6, array_h, repeats, axis);

    #else
    REPEAT_SUBCASE(case6, array_cs_fb, repeats, axis);
    REPEAT_SUBCASE(case6, array_cs_hb, repeats, axis);
    REPEAT_SUBCASE(case6, array_cs_db, repeats, axis);

    REPEAT_SUBCASE(case6, array_fs_fb, repeats, axis);
    REPEAT_SUBCASE(case6, array_fs_hb, repeats, axis);
    REPEAT_SUBCASE(case6, array_fs_db, repeats, axis);

    REPEAT_SUBCASE(case6, array_hs_fb, repeats, axis);
    REPEAT_SUBCASE(case6, array_hs_hb, repeats, axis);
    REPEAT_SUBCASE(case6, array_hs_db, repeats, axis);

    REPEAT_SUBCASE(case6, array_ds_fb, repeats, axis);
    REPEAT_SUBCASE(case6, array_ds_hb, repeats, axis);
    REPEAT_SUBCASE(case6, array_ds_db, repeats, axis);

    REPEAT_SUBCASE(case6, array_ls_fb, repeats, axis);
    REPEAT_SUBCASE(case6, array_ls_hb, repeats, axis);
    REPEAT_SUBCASE(case6, array_ls_db, repeats, axis);
    #endif
}