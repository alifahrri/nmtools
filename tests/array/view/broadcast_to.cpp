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

#include "nmtools/array/view/broadcast_to.hpp"
#include "nmtools/testing/data/array/broadcast_to.hpp"
#include "nmtools/testing/doctest.hpp"
#include "nmtools/constants.hpp"

#include <vector>
#include <array>
#include <tuple>

namespace nm = nmtools;
namespace na = nm::array;
namespace view = nm::view;

#define RUN_broadcast_to_impl(...) \
nm::view::broadcast_to(__VA_ARGS__);

#ifdef NMTOOLS_TESTING_ENABLE_BENCHMARKS
#include "nmtools/benchmarks/bench.hpp"
using nm::benchmarks::TrackedBench;
// create immediately invoked lambda
// that packs broadcast_to fn to callable lambda
#define RUN_broadcast_to(case_name, ...) \
[](auto&&...args){ \
    auto title = std::string("broadcast_to-") + #case_name; \
    auto name  = nm::testing::make_func_args("", args...); \
    auto fn    = [&](){ \
        return RUN_broadcast_to_impl(args...); \
    }; \
    return TrackedBench::run(title, name, fn); \
}(__VA_ARGS__);
#else
// run normally without benchmarking, ignore case_name
#define RUN_broadcast_to(case_name, ...) \
RUN_broadcast_to_impl(__VA_ARGS__);
#endif // NMTOOLS_TESTING_ENABLE_BENCHMARKS

#define BROADCAST_TO_SUBCASE(case_name, array, shape_, expected) \
SUBCASE(#case_name) \
{ \
    NMTOOLS_TESTING_DECLARE_NS(broadcast_to, case_name); \
    auto array_ref = RUN_broadcast_to(case_name, args::array,args::shape_); \
    NMTOOLS_ASSERT_EQUAL( nmtools::shape(array_ref), nmtools::shape(expect::expected) ); \
    NMTOOLS_ASSERT_CLOSE( array_ref, expect::expected ); \
}

TEST_CASE("broadcast_to(case1)" * doctest::test_suite("view::broadcast_to"))
{
    #if !defined(NMTOOLS_TESTING_GENERIC_NDARRAY)
    BROADCAST_TO_SUBCASE( case1, x_a, shape, expected );
    BROADCAST_TO_SUBCASE( case1, x_f, shape, expected );
    BROADCAST_TO_SUBCASE( case1, x_d, shape, expected );
    BROADCAST_TO_SUBCASE( case1, x_h, shape, expected );

    BROADCAST_TO_SUBCASE( case1, x_a, shape_ct, expected );
    BROADCAST_TO_SUBCASE( case1, x_f, shape_ct, expected );
    BROADCAST_TO_SUBCASE( case1, x_d, shape_ct, expected );
    BROADCAST_TO_SUBCASE( case1, x_h, shape_ct, expected );

    #else
    BROADCAST_TO_SUBCASE( case1, x_cs_fb, shape, expected );
    BROADCAST_TO_SUBCASE( case1, x_cs_hb, shape, expected );
    BROADCAST_TO_SUBCASE( case1, x_cs_db, shape, expected );

    BROADCAST_TO_SUBCASE( case1, x_cs_fb, shape_ct, expected );
    BROADCAST_TO_SUBCASE( case1, x_cs_hb, shape_ct, expected );
    BROADCAST_TO_SUBCASE( case1, x_cs_db, shape_ct, expected );

    BROADCAST_TO_SUBCASE( case1, x_fs_fb, shape, expected );
    BROADCAST_TO_SUBCASE( case1, x_fs_hb, shape, expected );
    BROADCAST_TO_SUBCASE( case1, x_fs_db, shape, expected );

    BROADCAST_TO_SUBCASE( case1, x_fs_fb, shape_ct, expected );
    BROADCAST_TO_SUBCASE( case1, x_fs_hb, shape_ct, expected );
    BROADCAST_TO_SUBCASE( case1, x_fs_db, shape_ct, expected );

    BROADCAST_TO_SUBCASE( case1, x_hs_fb, shape, expected );
    BROADCAST_TO_SUBCASE( case1, x_hs_hb, shape, expected );
    BROADCAST_TO_SUBCASE( case1, x_hs_db, shape, expected );

    BROADCAST_TO_SUBCASE( case1, x_fs_fb, shape_ct, expected );
    BROADCAST_TO_SUBCASE( case1, x_fs_hb, shape_ct, expected );
    BROADCAST_TO_SUBCASE( case1, x_fs_db, shape_ct, expected );

    BROADCAST_TO_SUBCASE( case1, x_ds_fb, shape, expected );
    BROADCAST_TO_SUBCASE( case1, x_ds_hb, shape, expected );
    BROADCAST_TO_SUBCASE( case1, x_ds_db, shape, expected );

    BROADCAST_TO_SUBCASE( case1, x_fs_fb, shape_ct, expected );
    BROADCAST_TO_SUBCASE( case1, x_fs_hb, shape_ct, expected );
    BROADCAST_TO_SUBCASE( case1, x_fs_db, shape_ct, expected );
    #endif
}

TEST_CASE("broadcast_to(case2)" * doctest::test_suite("view::broadcast_to"))
{
    #if !defined(NMTOOLS_TESTING_GENERIC_NDARRAY)
    BROADCAST_TO_SUBCASE( case2, x_a, shape, expected );
    BROADCAST_TO_SUBCASE( case2, x_f, shape, expected );
    BROADCAST_TO_SUBCASE( case2, x_d, shape, expected );
    BROADCAST_TO_SUBCASE( case2, x_h, shape, expected );

    BROADCAST_TO_SUBCASE( case2, x_a, shape_ct, expected );
    BROADCAST_TO_SUBCASE( case2, x_f, shape_ct, expected );
    BROADCAST_TO_SUBCASE( case2, x_d, shape_ct, expected );
    BROADCAST_TO_SUBCASE( case2, x_h, shape_ct, expected );

    #else
    BROADCAST_TO_SUBCASE( case1, x_cs_fb, shape, expected );
    BROADCAST_TO_SUBCASE( case1, x_cs_hb, shape, expected );
    BROADCAST_TO_SUBCASE( case1, x_cs_db, shape, expected );

    BROADCAST_TO_SUBCASE( case1, x_cs_fb, shape_ct, expected );
    BROADCAST_TO_SUBCASE( case1, x_cs_hb, shape_ct, expected );
    BROADCAST_TO_SUBCASE( case1, x_cs_db, shape_ct, expected );

    BROADCAST_TO_SUBCASE( case2, x_fs_fb, shape, expected );
    BROADCAST_TO_SUBCASE( case2, x_fs_hb, shape, expected );
    BROADCAST_TO_SUBCASE( case2, x_fs_db, shape, expected );

    BROADCAST_TO_SUBCASE( case1, x_cs_fb, shape_ct, expected );
    BROADCAST_TO_SUBCASE( case1, x_cs_hb, shape_ct, expected );
    BROADCAST_TO_SUBCASE( case1, x_cs_db, shape_ct, expected );

    BROADCAST_TO_SUBCASE( case2, x_hs_fb, shape, expected );
    BROADCAST_TO_SUBCASE( case2, x_hs_hb, shape, expected );
    BROADCAST_TO_SUBCASE( case2, x_hs_db, shape, expected );

    BROADCAST_TO_SUBCASE( case1, x_cs_fb, shape_ct, expected );
    BROADCAST_TO_SUBCASE( case1, x_cs_hb, shape_ct, expected );
    BROADCAST_TO_SUBCASE( case1, x_cs_db, shape_ct, expected );

    BROADCAST_TO_SUBCASE( case2, x_ds_fb, shape, expected );
    BROADCAST_TO_SUBCASE( case2, x_ds_hb, shape, expected );
    BROADCAST_TO_SUBCASE( case2, x_ds_db, shape, expected );

    BROADCAST_TO_SUBCASE( case2, x_ds_fb, shape_ct, expected );
    BROADCAST_TO_SUBCASE( case2, x_ds_hb, shape_ct, expected );
    BROADCAST_TO_SUBCASE( case2, x_ds_db, shape_ct, expected );
    #endif
}

TEST_CASE("broadcast_to(case3)" * doctest::test_suite("view::broadcast_to"))
{
    #if !defined(NMTOOLS_TESTING_GENERIC_NDARRAY)
    BROADCAST_TO_SUBCASE( case3, x_a, shape, expected );
    BROADCAST_TO_SUBCASE( case3, x_f, shape, expected );
    BROADCAST_TO_SUBCASE( case3, x_d, shape, expected );
    BROADCAST_TO_SUBCASE( case3, x_h, shape, expected );

    BROADCAST_TO_SUBCASE( case3, x_a, shape_ct, expected );
    BROADCAST_TO_SUBCASE( case3, x_f, shape_ct, expected );
    BROADCAST_TO_SUBCASE( case3, x_d, shape_ct, expected );
    BROADCAST_TO_SUBCASE( case3, x_h, shape_ct, expected );

    #else
    BROADCAST_TO_SUBCASE( case3, x_cs_fb, shape, expected );
    BROADCAST_TO_SUBCASE( case3, x_cs_hb, shape, expected );
    BROADCAST_TO_SUBCASE( case3, x_cs_db, shape, expected );

    BROADCAST_TO_SUBCASE( case3, x_cs_fb, shape_ct, expected );
    BROADCAST_TO_SUBCASE( case3, x_cs_hb, shape_ct, expected );
    BROADCAST_TO_SUBCASE( case3, x_cs_db, shape_ct, expected );

    BROADCAST_TO_SUBCASE( case3, x_fs_fb, shape, expected );
    BROADCAST_TO_SUBCASE( case3, x_fs_hb, shape, expected );
    BROADCAST_TO_SUBCASE( case3, x_fs_db, shape, expected );

    BROADCAST_TO_SUBCASE( case3, x_fs_fb, shape_ct, expected );
    BROADCAST_TO_SUBCASE( case3, x_fs_hb, shape_ct, expected );
    BROADCAST_TO_SUBCASE( case3, x_fs_db, shape_ct, expected );

    BROADCAST_TO_SUBCASE( case3, x_hs_fb, shape, expected );
    BROADCAST_TO_SUBCASE( case3, x_hs_hb, shape, expected );
    BROADCAST_TO_SUBCASE( case3, x_hs_db, shape, expected );

    // TODO: fix runtime
    // BROADCAST_TO_SUBCASE( case3, x_hs_fb, shape_ct, expected );
    // BROADCAST_TO_SUBCASE( case3, x_hs_hb, shape_ct, expected );
    // BROADCAST_TO_SUBCASE( case3, x_hs_db, shape_ct, expected );

    BROADCAST_TO_SUBCASE( case3, x_ds_fb, shape, expected );
    BROADCAST_TO_SUBCASE( case3, x_ds_hb, shape, expected );
    BROADCAST_TO_SUBCASE( case3, x_ds_db, shape, expected );

    BROADCAST_TO_SUBCASE( case3, x_ds_fb, shape_ct, expected );
    BROADCAST_TO_SUBCASE( case3, x_ds_hb, shape_ct, expected );
    BROADCAST_TO_SUBCASE( case3, x_ds_db, shape_ct, expected );
    #endif
}

TEST_CASE("broadcast_to(case4)" * doctest::test_suite("view::broadcast_to"))
{
    #if !defined(NMTOOLS_TESTING_GENERIC_NDARRAY)
    BROADCAST_TO_SUBCASE( case4, x_a, shape, expected );
    BROADCAST_TO_SUBCASE( case4, x_f, shape, expected );
    BROADCAST_TO_SUBCASE( case4, x_d, shape, expected );
    BROADCAST_TO_SUBCASE( case4, x_h, shape, expected );

    BROADCAST_TO_SUBCASE( case4, x_a, shape_ct, expected );
    BROADCAST_TO_SUBCASE( case4, x_f, shape_ct, expected );
    BROADCAST_TO_SUBCASE( case4, x_d, shape_ct, expected );
    BROADCAST_TO_SUBCASE( case4, x_h, shape_ct, expected );

    #else
    BROADCAST_TO_SUBCASE( case4, x_cs_fb, shape, expected );
    BROADCAST_TO_SUBCASE( case4, x_cs_hb, shape, expected );
    BROADCAST_TO_SUBCASE( case4, x_cs_db, shape, expected );

    BROADCAST_TO_SUBCASE( case4, x_cs_fb, shape_ct, expected );
    BROADCAST_TO_SUBCASE( case4, x_cs_hb, shape_ct, expected );
    BROADCAST_TO_SUBCASE( case4, x_cs_db, shape_ct, expected );

    BROADCAST_TO_SUBCASE( case4, x_fs_fb, shape, expected );
    BROADCAST_TO_SUBCASE( case4, x_fs_hb, shape, expected );
    BROADCAST_TO_SUBCASE( case4, x_fs_db, shape, expected );

    BROADCAST_TO_SUBCASE( case4, x_fs_fb, shape_ct, expected );
    BROADCAST_TO_SUBCASE( case4, x_fs_hb, shape_ct, expected );
    BROADCAST_TO_SUBCASE( case4, x_fs_db, shape_ct, expected );

    BROADCAST_TO_SUBCASE( case4, x_hs_fb, shape, expected );
    BROADCAST_TO_SUBCASE( case4, x_hs_hb, shape, expected );
    BROADCAST_TO_SUBCASE( case4, x_hs_db, shape, expected );

    BROADCAST_TO_SUBCASE( case4, x_hs_fb, shape_ct, expected );
    BROADCAST_TO_SUBCASE( case4, x_hs_hb, shape_ct, expected );
    BROADCAST_TO_SUBCASE( case4, x_hs_db, shape_ct, expected );

    BROADCAST_TO_SUBCASE( case4, x_ds_fb, shape, expected );
    BROADCAST_TO_SUBCASE( case4, x_ds_hb, shape, expected );
    BROADCAST_TO_SUBCASE( case4, x_ds_db, shape, expected );

    BROADCAST_TO_SUBCASE( case4, x_ds_fb, shape_ct, expected );
    BROADCAST_TO_SUBCASE( case4, x_ds_hb, shape_ct, expected );
    BROADCAST_TO_SUBCASE( case4, x_ds_db, shape_ct, expected );
    #endif
}

TEST_CASE("broadcast_to(case5)" * doctest::test_suite("view::broadcast_to"))
{
    #if !defined(NMTOOLS_TESTING_GENERIC_NDARRAY)
    BROADCAST_TO_SUBCASE( case5, x_a, shape, expected );
    BROADCAST_TO_SUBCASE( case5, x_f, shape, expected );
    BROADCAST_TO_SUBCASE( case5, x_d, shape, expected );
    BROADCAST_TO_SUBCASE( case5, x_h, shape, expected );

    BROADCAST_TO_SUBCASE( case5, x_a, shape_ct, expected );
    BROADCAST_TO_SUBCASE( case5, x_f, shape_ct, expected );
    BROADCAST_TO_SUBCASE( case5, x_d, shape_ct, expected );
    BROADCAST_TO_SUBCASE( case5, x_h, shape_ct, expected );

    #else
    BROADCAST_TO_SUBCASE( case5, x_cs_fb, shape, expected );
    BROADCAST_TO_SUBCASE( case5, x_cs_hb, shape, expected );
    BROADCAST_TO_SUBCASE( case5, x_cs_db, shape, expected );

    BROADCAST_TO_SUBCASE( case5, x_cs_fb, shape_ct, expected );
    BROADCAST_TO_SUBCASE( case5, x_cs_hb, shape_ct, expected );
    BROADCAST_TO_SUBCASE( case5, x_cs_db, shape_ct, expected );

    BROADCAST_TO_SUBCASE( case5, x_fs_fb, shape, expected );
    BROADCAST_TO_SUBCASE( case5, x_fs_hb, shape, expected );
    BROADCAST_TO_SUBCASE( case5, x_fs_db, shape, expected );

    BROADCAST_TO_SUBCASE( case5, x_fs_fb, shape_ct, expected );
    BROADCAST_TO_SUBCASE( case5, x_fs_hb, shape_ct, expected );
    BROADCAST_TO_SUBCASE( case5, x_fs_db, shape_ct, expected );

    BROADCAST_TO_SUBCASE( case5, x_hs_fb, shape, expected );
    BROADCAST_TO_SUBCASE( case5, x_hs_hb, shape, expected );
    BROADCAST_TO_SUBCASE( case5, x_hs_db, shape, expected );

    BROADCAST_TO_SUBCASE( case5, x_hs_fb, shape_ct, expected );
    BROADCAST_TO_SUBCASE( case5, x_hs_hb, shape_ct, expected );
    BROADCAST_TO_SUBCASE( case5, x_hs_db, shape_ct, expected );

    BROADCAST_TO_SUBCASE( case5, x_ds_fb, shape, expected );
    BROADCAST_TO_SUBCASE( case5, x_ds_hb, shape, expected );
    BROADCAST_TO_SUBCASE( case5, x_ds_db, shape, expected );

    BROADCAST_TO_SUBCASE( case5, x_ds_fb, shape_ct, expected );
    BROADCAST_TO_SUBCASE( case5, x_ds_hb, shape_ct, expected );
    BROADCAST_TO_SUBCASE( case5, x_ds_db, shape_ct, expected );
    #endif
}

TEST_CASE("broadcast_to(case6)" * doctest::test_suite("view::broadcast_to"))
{
    #if !defined(NMTOOLS_TESTING_GENERIC_NDARRAY)
    BROADCAST_TO_SUBCASE( case6, x_a, shape, expected );
    BROADCAST_TO_SUBCASE( case6, x_f, shape, expected );
    BROADCAST_TO_SUBCASE( case6, x_d, shape, expected );
    BROADCAST_TO_SUBCASE( case6, x_h, shape, expected );

    BROADCAST_TO_SUBCASE( case6, x_a, shape_ct, expected );
    BROADCAST_TO_SUBCASE( case6, x_f, shape_ct, expected );
    BROADCAST_TO_SUBCASE( case6, x_d, shape_ct, expected );
    BROADCAST_TO_SUBCASE( case6, x_h, shape_ct, expected );

    #else
    BROADCAST_TO_SUBCASE( case6, x_cs_fb, shape, expected );
    BROADCAST_TO_SUBCASE( case6, x_cs_hb, shape, expected );
    BROADCAST_TO_SUBCASE( case6, x_cs_db, shape, expected );

    BROADCAST_TO_SUBCASE( case6, x_cs_fb, shape_ct, expected );
    BROADCAST_TO_SUBCASE( case6, x_cs_hb, shape_ct, expected );
    BROADCAST_TO_SUBCASE( case6, x_cs_db, shape_ct, expected );

    BROADCAST_TO_SUBCASE( case6, x_fs_fb, shape, expected );
    BROADCAST_TO_SUBCASE( case6, x_fs_hb, shape, expected );
    BROADCAST_TO_SUBCASE( case6, x_fs_db, shape, expected );

    BROADCAST_TO_SUBCASE( case6, x_fs_fb, shape_ct, expected );
    BROADCAST_TO_SUBCASE( case6, x_fs_hb, shape_ct, expected );
    BROADCAST_TO_SUBCASE( case6, x_fs_db, shape_ct, expected );

    BROADCAST_TO_SUBCASE( case6, x_hs_fb, shape, expected );
    BROADCAST_TO_SUBCASE( case6, x_hs_hb, shape, expected );
    BROADCAST_TO_SUBCASE( case6, x_hs_db, shape, expected );

    BROADCAST_TO_SUBCASE( case6, x_hs_fb, shape_ct, expected );
    BROADCAST_TO_SUBCASE( case6, x_hs_hb, shape_ct, expected );
    BROADCAST_TO_SUBCASE( case6, x_hs_db, shape_ct, expected );

    BROADCAST_TO_SUBCASE( case6, x_ds_fb, shape, expected );
    BROADCAST_TO_SUBCASE( case6, x_ds_hb, shape, expected );
    BROADCAST_TO_SUBCASE( case6, x_ds_db, shape, expected );

    BROADCAST_TO_SUBCASE( case6, x_ds_fb, shape_ct, expected );
    BROADCAST_TO_SUBCASE( case6, x_ds_hb, shape_ct, expected );
    BROADCAST_TO_SUBCASE( case6, x_ds_db, shape_ct, expected );
    #endif
}

TEST_CASE("broadcast_to(case7)" * doctest::test_suite("view::broadcast_to"))
{
    #if !defined(NMTOOLS_TESTING_GENERIC_NDARRAY)
    BROADCAST_TO_SUBCASE( case7, x_a, shape, expected );
    BROADCAST_TO_SUBCASE( case7, x_f, shape, expected );
    BROADCAST_TO_SUBCASE( case7, x_d, shape, expected );
    BROADCAST_TO_SUBCASE( case7, x_h, shape, expected );

    BROADCAST_TO_SUBCASE( case7, x_a, shape_ct, expected );
    BROADCAST_TO_SUBCASE( case7, x_f, shape_ct, expected );
    BROADCAST_TO_SUBCASE( case7, x_d, shape_ct, expected );
    BROADCAST_TO_SUBCASE( case7, x_h, shape_ct, expected );

    #else
    BROADCAST_TO_SUBCASE( case7, x_cs_fb, shape, expected );
    BROADCAST_TO_SUBCASE( case7, x_cs_hb, shape, expected );
    BROADCAST_TO_SUBCASE( case7, x_cs_db, shape, expected );

    BROADCAST_TO_SUBCASE( case7, x_cs_fb, shape_ct, expected );
    BROADCAST_TO_SUBCASE( case7, x_cs_hb, shape_ct, expected );
    BROADCAST_TO_SUBCASE( case7, x_cs_db, shape_ct, expected );

    BROADCAST_TO_SUBCASE( case7, x_fs_fb, shape, expected );
    BROADCAST_TO_SUBCASE( case7, x_fs_hb, shape, expected );
    BROADCAST_TO_SUBCASE( case7, x_fs_db, shape, expected );

    BROADCAST_TO_SUBCASE( case7, x_fs_fb, shape_ct, expected );
    BROADCAST_TO_SUBCASE( case7, x_fs_hb, shape_ct, expected );
    BROADCAST_TO_SUBCASE( case7, x_fs_db, shape_ct, expected );

    BROADCAST_TO_SUBCASE( case7, x_hs_fb, shape, expected );
    BROADCAST_TO_SUBCASE( case7, x_hs_hb, shape, expected );
    BROADCAST_TO_SUBCASE( case7, x_hs_db, shape, expected );

    BROADCAST_TO_SUBCASE( case7, x_hs_fb, shape_ct, expected );
    BROADCAST_TO_SUBCASE( case7, x_hs_hb, shape_ct, expected );
    BROADCAST_TO_SUBCASE( case7, x_hs_db, shape_ct, expected );

    BROADCAST_TO_SUBCASE( case7, x_ds_fb, shape, expected );
    BROADCAST_TO_SUBCASE( case7, x_ds_hb, shape, expected );
    BROADCAST_TO_SUBCASE( case7, x_ds_db, shape, expected );

    BROADCAST_TO_SUBCASE( case7, x_ds_fb, shape_ct, expected );
    BROADCAST_TO_SUBCASE( case7, x_ds_hb, shape_ct, expected );
    BROADCAST_TO_SUBCASE( case7, x_ds_db, shape_ct, expected );
    #endif
}

TEST_CASE("broadcast_to(case8)" * doctest::test_suite("view::broadcast_to"))
{
    #if !defined(NMTOOLS_TESTING_GENERIC_NDARRAY)
    BROADCAST_TO_SUBCASE( case8, x_a, shape, expected );
    BROADCAST_TO_SUBCASE( case8, x_f, shape, expected );
    BROADCAST_TO_SUBCASE( case8, x_d, shape, expected );
    BROADCAST_TO_SUBCASE( case8, x_h, shape, expected );

    BROADCAST_TO_SUBCASE( case8, x_a, shape_ct, expected );
    BROADCAST_TO_SUBCASE( case8, x_f, shape_ct, expected );
    BROADCAST_TO_SUBCASE( case8, x_d, shape_ct, expected );
    BROADCAST_TO_SUBCASE( case8, x_h, shape_ct, expected );

    #else
    BROADCAST_TO_SUBCASE( case8, x_cs_fb, shape, expected );
    BROADCAST_TO_SUBCASE( case8, x_cs_hb, shape, expected );
    BROADCAST_TO_SUBCASE( case8, x_cs_db, shape, expected );

    BROADCAST_TO_SUBCASE( case8, x_cs_fb, shape_ct, expected );
    BROADCAST_TO_SUBCASE( case8, x_cs_hb, shape_ct, expected );
    BROADCAST_TO_SUBCASE( case8, x_cs_db, shape_ct, expected );

    BROADCAST_TO_SUBCASE( case8, x_fs_fb, shape, expected );
    BROADCAST_TO_SUBCASE( case8, x_fs_hb, shape, expected );
    BROADCAST_TO_SUBCASE( case8, x_fs_db, shape, expected );

    BROADCAST_TO_SUBCASE( case8, x_fs_fb, shape_ct, expected );
    BROADCAST_TO_SUBCASE( case8, x_fs_hb, shape_ct, expected );
    BROADCAST_TO_SUBCASE( case8, x_fs_db, shape_ct, expected );

    BROADCAST_TO_SUBCASE( case8, x_hs_fb, shape, expected );
    BROADCAST_TO_SUBCASE( case8, x_hs_hb, shape, expected );
    BROADCAST_TO_SUBCASE( case8, x_hs_db, shape, expected );

    // TODO: fix runtime
    // BROADCAST_TO_SUBCASE( case8, x_hs_fb, shape_ct, expected );
    // BROADCAST_TO_SUBCASE( case8, x_hs_hb, shape_ct, expected );
    // BROADCAST_TO_SUBCASE( case8, x_hs_db, shape_ct, expected );

    BROADCAST_TO_SUBCASE( case8, x_ds_fb, shape, expected );
    BROADCAST_TO_SUBCASE( case8, x_ds_hb, shape, expected );
    BROADCAST_TO_SUBCASE( case8, x_ds_db, shape, expected );

    BROADCAST_TO_SUBCASE( case8, x_ds_fb, shape_ct, expected );
    BROADCAST_TO_SUBCASE( case8, x_ds_hb, shape_ct, expected );
    BROADCAST_TO_SUBCASE( case8, x_ds_db, shape_ct, expected );
    #endif
}

TEST_CASE("broadcast_to(case9)" * doctest::test_suite("view::broadcast_to"))
{
    #if !defined(NMTOOLS_TESTING_GENERIC_NDARRAY)
    BROADCAST_TO_SUBCASE( case9, x_a, shape, expected );
    BROADCAST_TO_SUBCASE( case9, x_f, shape, expected );
    BROADCAST_TO_SUBCASE( case9, x_d, shape, expected );
    BROADCAST_TO_SUBCASE( case9, x_h, shape, expected );

    BROADCAST_TO_SUBCASE( case9, x_a, shape_ct, expected );
    BROADCAST_TO_SUBCASE( case9, x_f, shape_ct, expected );
    BROADCAST_TO_SUBCASE( case9, x_d, shape_ct, expected );
    BROADCAST_TO_SUBCASE( case9, x_h, shape_ct, expected );

    #else
    BROADCAST_TO_SUBCASE( case9, x_cs_fb, shape, expected );
    BROADCAST_TO_SUBCASE( case9, x_cs_hb, shape, expected );
    BROADCAST_TO_SUBCASE( case9, x_cs_db, shape, expected );

    BROADCAST_TO_SUBCASE( case9, x_cs_fb, shape_ct, expected );
    BROADCAST_TO_SUBCASE( case9, x_cs_hb, shape_ct, expected );
    BROADCAST_TO_SUBCASE( case9, x_cs_db, shape_ct, expected );

    BROADCAST_TO_SUBCASE( case9, x_fs_fb, shape, expected );
    BROADCAST_TO_SUBCASE( case9, x_fs_hb, shape, expected );
    BROADCAST_TO_SUBCASE( case9, x_fs_db, shape, expected );

    BROADCAST_TO_SUBCASE( case9, x_fs_fb, shape_ct, expected );
    BROADCAST_TO_SUBCASE( case9, x_fs_hb, shape_ct, expected );
    BROADCAST_TO_SUBCASE( case9, x_fs_db, shape_ct, expected );

    BROADCAST_TO_SUBCASE( case9, x_hs_fb, shape, expected );
    BROADCAST_TO_SUBCASE( case9, x_hs_hb, shape, expected );
    BROADCAST_TO_SUBCASE( case9, x_hs_db, shape, expected );

    BROADCAST_TO_SUBCASE( case9, x_hs_fb, shape_ct, expected );
    BROADCAST_TO_SUBCASE( case9, x_hs_hb, shape_ct, expected );
    BROADCAST_TO_SUBCASE( case9, x_hs_db, shape_ct, expected );

    BROADCAST_TO_SUBCASE( case9, x_ds_fb, shape, expected );
    BROADCAST_TO_SUBCASE( case9, x_ds_hb, shape, expected );
    BROADCAST_TO_SUBCASE( case9, x_ds_db, shape, expected );

    BROADCAST_TO_SUBCASE( case9, x_ds_fb, shape_ct, expected );
    BROADCAST_TO_SUBCASE( case9, x_ds_hb, shape_ct, expected );
    BROADCAST_TO_SUBCASE( case9, x_ds_db, shape_ct, expected );
    #endif
}

TEST_CASE("broadcast_to(case10)" * doctest::test_suite("view::broadcast_to"))
{
    BROADCAST_TO_SUBCASE( case10, x, shape, expected );
}

TEST_CASE("broadcast_to(case11)" * doctest::test_suite("view::broadcast_to"))
{
    BROADCAST_TO_SUBCASE( case11, x, shape, expected );
}


// the following tests are to make sure it is safe to 
// return the view itself as long as it doesn't outlive
// the referenced array

template <typename array_t>
auto f(const array_t& array)
{
    return view::broadcast_to(array, std::array{1,1,3});
}

template <typename array_t>
auto g(const array_t& array)
{
    auto a = f(array);
    return view::broadcast_to(a, std::array{1,1,1,3});
}

TEST_CASE("broadcast_to" * doctest::test_suite("view::broadcast_to"))
{
    SUBCASE("one function")
    {
        // std::array
        {
            auto array = std::array{1,2,3};
            auto broacasted = f(array);
            int expected[1][1][3] = {
                {
                    {1,2,3}
                }
            };
            NMTOOLS_ASSERT_EQUAL( broacasted, expected );
        }
        // raw array
        {
            int array[3] = {1,2,3};
            auto broacasted = f(array);
            int expected[1][1][3] = {
                {
                    {1,2,3}
                }
            };
            NMTOOLS_ASSERT_EQUAL( broacasted, expected );
        }
    }
    SUBCASE("two function")
    {
        // std::array
        {
            auto array = std::array{1,2,3};
            auto broacasted = g(array);
            int expected[1][1][1][3] = {
                {
                    {
                        {1,2,3}
                    }
                }
            };
            NMTOOLS_ASSERT_EQUAL( broacasted.shape(), nm::shape(expected) );
            NMTOOLS_ASSERT_EQUAL( broacasted, expected );
        }

        // raw array
        {
            int array[3] = {1,2,3};
            auto broacasted = g(array);
            int expected[1][1][1][3] = {
                {
                    {
                        {1,2,3}
                    }
                }
            };
            NMTOOLS_ASSERT_EQUAL( broacasted.shape(), nm::shape(expected) );
            NMTOOLS_ASSERT_EQUAL( broacasted, expected );
        }
    }
}

// TODO: move to meta (?)
TEST_CASE("broadcast_to(traits)"  * doctest::test_suite("view::broadcast_to"))
{
    using namespace nmtools::literals;
    namespace meta = nmtools::meta;
    SUBCASE("is_ndarray")
    {
        {
            auto x = std::vector{1,2,3};
            auto shape = std::tuple{1_ct,2_ct,3_ct};
            auto broadcasted    = view::broadcast_to(x,shape);
            using broadcasted_t = decltype(broadcasted);
            NMTOOLS_STATIC_CHECK_TRAIT( meta::is_ndarray, broadcasted_t );
        }
    }
    SUBCASE("is_hybrid_ndarray")
    {
        {
            // broadcast_to view can't be hybrid_ndarray for now
            auto x = na::hybrid_ndarray({1,2,3});
            auto shape = std::array{1,2,3};
            auto broadcasted    = view::broadcast_to(x,shape);
            using broadcasted_t = decltype(broadcasted);
            NMTOOLS_STATIC_CHECK_TRAIT_FALSE( meta::is_hybrid_ndarray, broadcasted_t );
        }
    }
    SUBCASE("is_fixed_size_ndarray")
    {
        {
            int  x[3] = {1,2,3};
            auto shape = std::tuple{1_ct,2_ct,3_ct};
            auto broadcasted = view::broadcast_to(x,shape);
            using broadcasted_t = decltype(broadcasted);
            NMTOOLS_ASSERT_EQUAL( meta::is_fixed_size_ndarray_v<broadcasted_t>, true );
        }
        {
            int  x[3] = {1,2,3};
            auto shape = std::vector{1,2,3};
            auto broadcasted = view::broadcast_to(x,shape);
            using broadcasted_t = decltype(broadcasted);
            NMTOOLS_STATIC_CHECK_TRAIT_FALSE( meta::is_fixed_size_ndarray, broadcasted_t );
        }
    }
    SUBCASE("is_dynamic_ndarray")
    {
        {
            auto x     = std::vector{1,2,3};
            auto shape = std::vector{1,2,3};
            auto broadcasted    = view::broadcast_to(x,shape);
            using broadcasted_t = decltype(broadcasted);
            NMTOOLS_STATIC_CHECK_TRAIT( meta::is_dynamic_ndarray, broadcasted_t );
        }
        {
            auto x     = std::vector{1,2,3};
            auto shape = std::tuple{1_ct,2_ct,3_ct};
            auto broadcasted    = view::broadcast_to(x,shape);
            using broadcasted_t = decltype(broadcasted);
            NMTOOLS_STATIC_CHECK_TRAIT_FALSE( meta::is_dynamic_ndarray, broadcasted_t );
        }
    }
    SUBCASE("is_fixed_dim_ndarray")
    {
        {
            auto x     = std::vector{1,2,3};
            auto shape = std::vector{1,2,3};
            auto broadcasted    = view::broadcast_to(x,shape);
            using broadcasted_t = decltype(broadcasted);
            NMTOOLS_STATIC_CHECK_TRAIT_FALSE( meta::is_fixed_dim_ndarray, broadcasted_t );
        }
        {
            auto x     = std::vector{1,2,3};
            auto shape = std::tuple{1_ct,2_ct,3_ct};
            auto broadcasted    = view::broadcast_to(x,shape);
            using broadcasted_t = decltype(broadcasted);
            NMTOOLS_STATIC_CHECK_TRAIT( meta::is_fixed_dim_ndarray, broadcasted_t );
        }
    }
    // this use assert
    // SUBCASE("is_fixed_size_ndarray(2)")
    // {
    //     int x[3] = {1,2,3};
    //     // cant do this here, will assert
    //     // auto shape = std::tuple{1_ct,3_ct,2_ct};
    //     auto shape = std::tuple{1,3,2};
    //     auto broadcasted = view::broadcast_to(x,shape);
    //     using broadcasted_t = decltype(broadcasted);
    //     NMTOOLS_ASSERT_EQUAL( meta::is_fixed_size_ndarray_v<broadcasted_t>, false );
    // }
}