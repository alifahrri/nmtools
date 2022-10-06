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
inline auto name##_ds_db = nmtools::cast(name, nmtools::array::kind::ndarray_ds_db);
#endif

#include "nmtools/array/array/concatenate.hpp"
#include "nmtools/testing/data/array/concatenate.hpp"

#include "nmtools/constants.hpp"
#include "nmtools/testing/doctest.hpp"

#include <vector>
#include <array>
#include <tuple>

namespace nm = nmtools;
namespace na = nm::array;

#define RUN_impl(...) \
nm::array::concatenate(__VA_ARGS__);

#ifdef NMTOOLS_TESTING_ENABLE_BENCHMARKS
#include "nmtools/benchmarks/bench.hpp"
using nm::benchmarks::TrackedBench;
// create immediately invoked lambda
// that packs concatenate fn to callable lambda
#define RUN_concatenate(case_name, ...) \
[](auto&&...args){ \
    auto title = std::string("concatenate-") + #case_name; \
    auto name  = nm::testing::make_func_args("", args...); \
    auto fn    = [&](){ \
        return RUN_impl(args...); \
    }; \
    return TrackedBench::run(title, name, fn); \
}(__VA_ARGS__);
#else
// run normally without benchmarking, ignore case_name
#define RUN_concatenate(case_name, ...) \
RUN_impl(__VA_ARGS__);
#endif // NMTOOLS_TESTING_ENABLE_BENCHMARKS

#define CONCATENATE_SUBCASE(case_name, lhs, rhs, axis) \
SUBCASE(#case_name) \
{ \
    NMTOOLS_TESTING_DECLARE_NS(view, concatenate, case_name); \
    auto array_ref = RUN_concatenate(case_name, args::lhs, args::rhs, args::axis); \
    NMTOOLS_ASSERT_EQUAL( nm::shape(array_ref), expect::shape ); \
    NMTOOLS_ASSERT_CLOSE( array_ref, expect::expected ); \
}


// @note not supported yet
// TEST_CASE("concatenate(raw)" * doctest::test_suite("array::concatenate"))
// {
//     CONCATENATE_SUBCASE(case1, lhs, rhs, axis);
// }

TEST_CASE("concatenate(case1)" * doctest::test_suite("array::concatenate"))
{
    #if !defined(NMTOOLS_TESTING_GENERIC_NDARRAY)
    CONCATENATE_SUBCASE(case1, lhs_a, rhs_a, axis);
    CONCATENATE_SUBCASE(case1, lhs_f, rhs_f, axis);
    CONCATENATE_SUBCASE(case1, lhs_d, rhs_d, axis);
    CONCATENATE_SUBCASE(case1, lhs_h, rhs_h, axis);

    #else
    CONCATENATE_SUBCASE(case1, lhs_cs_fb, rhs_cs_fb, axis);
    CONCATENATE_SUBCASE(case1, lhs_cs_hb, rhs_cs_hb, axis);
    CONCATENATE_SUBCASE(case1, lhs_cs_db, rhs_cs_db, axis);

    CONCATENATE_SUBCASE(case1, lhs_fs_fb, rhs_cs_fb, axis);
    CONCATENATE_SUBCASE(case1, lhs_fs_hb, rhs_cs_hb, axis);
    CONCATENATE_SUBCASE(case1, lhs_fs_db, rhs_cs_db, axis);

    CONCATENATE_SUBCASE(case1, lhs_hs_fb, rhs_cs_fb, axis);
    CONCATENATE_SUBCASE(case1, lhs_hs_hb, rhs_cs_hb, axis);
    CONCATENATE_SUBCASE(case1, lhs_hs_db, rhs_cs_db, axis);

    CONCATENATE_SUBCASE(case1, lhs_ds_fb, rhs_cs_fb, axis);
    CONCATENATE_SUBCASE(case1, lhs_ds_hb, rhs_cs_hb, axis);
    CONCATENATE_SUBCASE(case1, lhs_ds_db, rhs_cs_db, axis);
    #endif
}

TEST_CASE("concatenate(case2)" * doctest::test_suite("array::concatenate"))
{
    #if !defined(NMTOOLS_TESTING_GENERIC_NDARRAY)
    CONCATENATE_SUBCASE(case2, lhs_a, rhs_a, axis);
    CONCATENATE_SUBCASE(case2, lhs_f, rhs_f, axis);
    CONCATENATE_SUBCASE(case2, lhs_d, rhs_d, axis);
    CONCATENATE_SUBCASE(case2, lhs_h, rhs_h, axis);

    #else
    CONCATENATE_SUBCASE(case2, lhs_cs_fb, rhs_cs_fb, axis);
    CONCATENATE_SUBCASE(case2, lhs_cs_hb, rhs_cs_hb, axis);
    CONCATENATE_SUBCASE(case2, lhs_cs_db, rhs_cs_db, axis);

    CONCATENATE_SUBCASE(case2, lhs_fs_fb, rhs_cs_fb, axis);
    CONCATENATE_SUBCASE(case2, lhs_fs_hb, rhs_cs_hb, axis);
    CONCATENATE_SUBCASE(case2, lhs_fs_db, rhs_cs_db, axis);

    CONCATENATE_SUBCASE(case2, lhs_hs_fb, rhs_cs_fb, axis);
    CONCATENATE_SUBCASE(case2, lhs_hs_hb, rhs_cs_hb, axis);
    CONCATENATE_SUBCASE(case2, lhs_hs_db, rhs_cs_db, axis);

    CONCATENATE_SUBCASE(case2, lhs_ds_fb, rhs_cs_fb, axis);
    CONCATENATE_SUBCASE(case2, lhs_ds_hb, rhs_cs_hb, axis);
    CONCATENATE_SUBCASE(case2, lhs_ds_db, rhs_cs_db, axis);
    #endif
}

TEST_CASE("concatenate(case3)" * doctest::test_suite("array::concatenate"))
{
    #if !defined(NMTOOLS_TESTING_GENERIC_NDARRAY)
    CONCATENATE_SUBCASE(case3, lhs_a, rhs_a, axis);
    CONCATENATE_SUBCASE(case3, lhs_f, rhs_f, axis);
    CONCATENATE_SUBCASE(case3, lhs_d, rhs_d, axis);
    CONCATENATE_SUBCASE(case3, lhs_h, rhs_h, axis);

    #else
    CONCATENATE_SUBCASE(case3, lhs_cs_fb, rhs_cs_fb, axis);
    CONCATENATE_SUBCASE(case3, lhs_cs_hb, rhs_cs_hb, axis);
    CONCATENATE_SUBCASE(case3, lhs_cs_db, rhs_cs_db, axis);

    CONCATENATE_SUBCASE(case3, lhs_fs_fb, rhs_cs_fb, axis);
    CONCATENATE_SUBCASE(case3, lhs_fs_hb, rhs_cs_hb, axis);
    CONCATENATE_SUBCASE(case3, lhs_fs_db, rhs_cs_db, axis);

    CONCATENATE_SUBCASE(case3, lhs_hs_fb, rhs_cs_fb, axis);
    CONCATENATE_SUBCASE(case3, lhs_hs_hb, rhs_cs_hb, axis);
    CONCATENATE_SUBCASE(case3, lhs_hs_db, rhs_cs_db, axis);

    CONCATENATE_SUBCASE(case3, lhs_ds_fb, rhs_cs_fb, axis);
    CONCATENATE_SUBCASE(case3, lhs_ds_hb, rhs_cs_hb, axis);
    CONCATENATE_SUBCASE(case3, lhs_ds_db, rhs_cs_db, axis);
    #endif
}

TEST_CASE("concatenate(case4)" * doctest::test_suite("array::concatenate"))
{
    #if !defined(NMTOOLS_TESTING_GENERIC_NDARRAY)
    CONCATENATE_SUBCASE(case4, lhs_a, rhs_a, axis);
    CONCATENATE_SUBCASE(case4, lhs_f, rhs_f, axis);
    CONCATENATE_SUBCASE(case4, lhs_d, rhs_d, axis);
    CONCATENATE_SUBCASE(case4, lhs_h, rhs_h, axis);

    #else
    CONCATENATE_SUBCASE(case4, lhs_cs_fb, rhs_cs_fb, axis);
    CONCATENATE_SUBCASE(case4, lhs_cs_hb, rhs_cs_hb, axis);
    CONCATENATE_SUBCASE(case4, lhs_cs_db, rhs_cs_db, axis);

    CONCATENATE_SUBCASE(case4, lhs_fs_fb, rhs_cs_fb, axis);
    CONCATENATE_SUBCASE(case4, lhs_fs_hb, rhs_cs_hb, axis);
    CONCATENATE_SUBCASE(case4, lhs_fs_db, rhs_cs_db, axis);

    CONCATENATE_SUBCASE(case4, lhs_hs_fb, rhs_cs_fb, axis);
    CONCATENATE_SUBCASE(case4, lhs_hs_hb, rhs_cs_hb, axis);
    CONCATENATE_SUBCASE(case4, lhs_hs_db, rhs_cs_db, axis);

    CONCATENATE_SUBCASE(case4, lhs_ds_fb, rhs_cs_fb, axis);
    CONCATENATE_SUBCASE(case4, lhs_ds_hb, rhs_cs_hb, axis);
    CONCATENATE_SUBCASE(case4, lhs_ds_db, rhs_cs_db, axis);
    #endif
}