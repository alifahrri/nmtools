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

#include "nmtools/array/expand_dims.hpp"
#include "nmtools/testing/data/array/expand_dims.hpp"
#include "nmtools/testing/doctest.hpp"

#include <array>
#include <tuple>
#include <vector>

namespace nm = nmtools;
namespace na = nm::array;
namespace meta = nm::meta;

#define RUN_impl(...) \
nm::array::expand_dims(__VA_ARGS__);

#ifdef NMTOOLS_TESTING_ENABLE_BENCHMARKS
#include "nmtools/testing/benchmarks/bench.hpp"
using nm::benchmarks::TrackedBench;
// create immediately invoked lambda
// that packs expand_dims fn to callable lambda
#define RUN_expand_dims(case_name, ...) \
[](auto&&...args){ \
    auto title = std::string("expand_dims-") + #case_name; \
    auto name  = nm::testing::make_func_args("", args...); \
    auto fn    = [&](){ \
        return RUN_impl(args...); \
    }; \
    return TrackedBench::run(title, name, fn); \
}(__VA_ARGS__);
#else
// run normally without benchmarking, ignore case_name
#define RUN_expand_dims(case_name, ...) \
RUN_impl(__VA_ARGS__);
#endif // NMTOOLS_TESTING_ENABLE_BENCHMARKS

#define EXPAND_DIMS_SUBCASE(case_name, array, axis) \
SUBCASE(#case_name) \
{ \
    NMTOOLS_TESTING_USE_CASE(expand_dims, case_name); \
    auto array_ref = RUN_expand_dims(case_name, args::array, args::axis); \
    NMTOOLS_ASSERT_EQUAL( nm::shape(array_ref), expect::shape ); \
    NMTOOLS_ASSERT_CLOSE( array_ref, expect::expected ); \
}

TEST_CASE("expand_dims(case1)" * doctest::test_suite("array::expand_dims"))
{
    #if !defined(NMTOOLS_TESTING_GENERIC_NDARRAY)
    EXPAND_DIMS_SUBCASE( case1, array,   axis_a );
    EXPAND_DIMS_SUBCASE( case1, array_a, axis_a );
    EXPAND_DIMS_SUBCASE( case1, array_f, axis_a );
    EXPAND_DIMS_SUBCASE( case1, array_d, axis_a );
    EXPAND_DIMS_SUBCASE( case1, array_h, axis_a );

    #else
    EXPAND_DIMS_SUBCASE( case1, array_cs_fb, axis_a );
    EXPAND_DIMS_SUBCASE( case1, array_cs_hb, axis_a );
    EXPAND_DIMS_SUBCASE( case1, array_cs_db, axis_a );

    EXPAND_DIMS_SUBCASE( case1, array_fs_fb, axis_a );
    EXPAND_DIMS_SUBCASE( case1, array_fs_hb, axis_a );
    EXPAND_DIMS_SUBCASE( case1, array_fs_db, axis_a );

    EXPAND_DIMS_SUBCASE( case1, array_hs_fb, axis_a );
    EXPAND_DIMS_SUBCASE( case1, array_hs_hb, axis_a );
    EXPAND_DIMS_SUBCASE( case1, array_hs_db, axis_a );

    EXPAND_DIMS_SUBCASE( case1, array_ds_fb, axis_a );
    EXPAND_DIMS_SUBCASE( case1, array_ds_hb, axis_a );
    EXPAND_DIMS_SUBCASE( case1, array_ds_db, axis_a );

    EXPAND_DIMS_SUBCASE( case1, array_ls_fb, axis_a );
    EXPAND_DIMS_SUBCASE( case1, array_ls_hb, axis_a );
    EXPAND_DIMS_SUBCASE( case1, array_ls_db, axis_a );
    #endif
}

TEST_CASE("expand_dims(case2)" * doctest::test_suite("array::expand_dims"))
{
    #if !defined(NMTOOLS_TESTING_GENERIC_NDARRAY)
    EXPAND_DIMS_SUBCASE( case2, array,   axis );
    EXPAND_DIMS_SUBCASE( case2, array_a, axis );
    EXPAND_DIMS_SUBCASE( case2, array_f, axis );
    EXPAND_DIMS_SUBCASE( case2, array_d, axis );
    EXPAND_DIMS_SUBCASE( case2, array_h, axis );

    #else
    EXPAND_DIMS_SUBCASE( case2, array_cs_fb, axis );
    EXPAND_DIMS_SUBCASE( case2, array_cs_hb, axis );
    EXPAND_DIMS_SUBCASE( case2, array_cs_db, axis );

    EXPAND_DIMS_SUBCASE( case2, array_fs_fb, axis );
    EXPAND_DIMS_SUBCASE( case2, array_fs_hb, axis );
    EXPAND_DIMS_SUBCASE( case2, array_fs_db, axis );

    EXPAND_DIMS_SUBCASE( case2, array_hs_fb, axis );
    EXPAND_DIMS_SUBCASE( case2, array_hs_hb, axis );
    EXPAND_DIMS_SUBCASE( case2, array_hs_db, axis );

    EXPAND_DIMS_SUBCASE( case2, array_ds_fb, axis );
    EXPAND_DIMS_SUBCASE( case2, array_ds_hb, axis );
    EXPAND_DIMS_SUBCASE( case2, array_ds_db, axis );

    EXPAND_DIMS_SUBCASE( case2, array_ls_fb, axis );
    EXPAND_DIMS_SUBCASE( case2, array_ls_hb, axis );
    EXPAND_DIMS_SUBCASE( case2, array_ls_db, axis );
    #endif
}

TEST_CASE("expand_dims(case3)" * doctest::test_suite("array::expand_dims"))
{
    #if !defined(NMTOOLS_TESTING_GENERIC_NDARRAY)
    EXPAND_DIMS_SUBCASE( case3, array,   axis );
    EXPAND_DIMS_SUBCASE( case3, array_a, axis );
    EXPAND_DIMS_SUBCASE( case3, array_f, axis );
    EXPAND_DIMS_SUBCASE( case3, array_d, axis );
    EXPAND_DIMS_SUBCASE( case3, array_h, axis );

    #else
    EXPAND_DIMS_SUBCASE( case3, array_cs_fb, axis );
    EXPAND_DIMS_SUBCASE( case3, array_cs_hb, axis );
    EXPAND_DIMS_SUBCASE( case3, array_cs_db, axis );

    EXPAND_DIMS_SUBCASE( case3, array_fs_fb, axis );
    EXPAND_DIMS_SUBCASE( case3, array_fs_hb, axis );
    EXPAND_DIMS_SUBCASE( case3, array_fs_db, axis );

    EXPAND_DIMS_SUBCASE( case3, array_hs_fb, axis );
    EXPAND_DIMS_SUBCASE( case3, array_hs_hb, axis );
    EXPAND_DIMS_SUBCASE( case3, array_hs_db, axis );

    EXPAND_DIMS_SUBCASE( case3, array_ds_fb, axis );
    EXPAND_DIMS_SUBCASE( case3, array_ds_hb, axis );
    EXPAND_DIMS_SUBCASE( case3, array_ds_db, axis );

    EXPAND_DIMS_SUBCASE( case3, array_ls_fb, axis );
    EXPAND_DIMS_SUBCASE( case3, array_ls_hb, axis );
    EXPAND_DIMS_SUBCASE( case3, array_ls_db, axis );
    #endif
}

TEST_CASE("expand_dims(case4)" * doctest::test_suite("array::expand_dims"))
{
    #if !defined(NMTOOLS_TESTING_GENERIC_NDARRAY)
    EXPAND_DIMS_SUBCASE( case4, array,   axis_a );
    EXPAND_DIMS_SUBCASE( case4, array_a, axis_a );
    EXPAND_DIMS_SUBCASE( case4, array_f, axis_a );
    EXPAND_DIMS_SUBCASE( case4, array_d, axis_a );
    EXPAND_DIMS_SUBCASE( case4, array_h, axis_a );

    #else
    EXPAND_DIMS_SUBCASE( case4, array_cs_fb, axis_a );
    EXPAND_DIMS_SUBCASE( case4, array_cs_hb, axis_a );
    EXPAND_DIMS_SUBCASE( case4, array_cs_db, axis_a );

    EXPAND_DIMS_SUBCASE( case4, array_fs_fb, axis_a );
    EXPAND_DIMS_SUBCASE( case4, array_fs_hb, axis_a );
    EXPAND_DIMS_SUBCASE( case4, array_fs_db, axis_a );

    EXPAND_DIMS_SUBCASE( case4, array_hs_fb, axis_a );
    EXPAND_DIMS_SUBCASE( case4, array_hs_hb, axis_a );
    EXPAND_DIMS_SUBCASE( case4, array_hs_db, axis_a );

    EXPAND_DIMS_SUBCASE( case4, array_ds_fb, axis_a );
    EXPAND_DIMS_SUBCASE( case4, array_ds_hb, axis_a );
    EXPAND_DIMS_SUBCASE( case4, array_ds_db, axis_a );

    EXPAND_DIMS_SUBCASE( case4, array_ls_fb, axis_a );
    EXPAND_DIMS_SUBCASE( case4, array_ls_hb, axis_a );
    EXPAND_DIMS_SUBCASE( case4, array_ls_db, axis_a );
    #endif
}

TEST_CASE("expand_dims(case5)" * doctest::test_suite("array::expand_dims"))
{
    #if !defined(NMTOOLS_TESTING_GENERIC_NDARRAY)
    EXPAND_DIMS_SUBCASE( case5, array,   axis_a );
    EXPAND_DIMS_SUBCASE( case5, array_a, axis_a );
    EXPAND_DIMS_SUBCASE( case5, array_f, axis_a );
    EXPAND_DIMS_SUBCASE( case5, array_d, axis_a );
    EXPAND_DIMS_SUBCASE( case5, array_h, axis_a );

    #else
    EXPAND_DIMS_SUBCASE( case5, array_cs_fb, axis_a );
    EXPAND_DIMS_SUBCASE( case5, array_cs_hb, axis_a );
    EXPAND_DIMS_SUBCASE( case5, array_cs_db, axis_a );

    EXPAND_DIMS_SUBCASE( case5, array_fs_fb, axis_a );
    EXPAND_DIMS_SUBCASE( case5, array_fs_hb, axis_a );
    EXPAND_DIMS_SUBCASE( case5, array_fs_db, axis_a );

    EXPAND_DIMS_SUBCASE( case5, array_hs_fb, axis_a );
    EXPAND_DIMS_SUBCASE( case5, array_hs_hb, axis_a );
    EXPAND_DIMS_SUBCASE( case5, array_hs_db, axis_a );

    EXPAND_DIMS_SUBCASE( case5, array_ds_fb, axis_a );
    EXPAND_DIMS_SUBCASE( case5, array_ds_hb, axis_a );
    EXPAND_DIMS_SUBCASE( case5, array_ds_db, axis_a );

    EXPAND_DIMS_SUBCASE( case5, array_ls_fb, axis_a );
    EXPAND_DIMS_SUBCASE( case5, array_ls_hb, axis_a );
    EXPAND_DIMS_SUBCASE( case5, array_ls_db, axis_a );
    #endif
}

TEST_CASE("expand_dims(case6)" * doctest::test_suite("array::expand_dims"))
{
    #if !defined(NMTOOLS_TESTING_GENERIC_NDARRAY)
    EXPAND_DIMS_SUBCASE( case6, array,   axis );
    EXPAND_DIMS_SUBCASE( case6, array_a, axis );
    EXPAND_DIMS_SUBCASE( case6, array_f, axis );
    EXPAND_DIMS_SUBCASE( case6, array_d, axis );
    EXPAND_DIMS_SUBCASE( case6, array_h, axis );

    #else
    EXPAND_DIMS_SUBCASE( case6, array_cs_fb, axis );
    EXPAND_DIMS_SUBCASE( case6, array_cs_hb, axis );
    EXPAND_DIMS_SUBCASE( case6, array_cs_db, axis );

    EXPAND_DIMS_SUBCASE( case6, array_fs_fb, axis );
    EXPAND_DIMS_SUBCASE( case6, array_fs_hb, axis );
    EXPAND_DIMS_SUBCASE( case6, array_fs_db, axis );

    EXPAND_DIMS_SUBCASE( case6, array_hs_fb, axis );
    EXPAND_DIMS_SUBCASE( case6, array_hs_hb, axis );
    EXPAND_DIMS_SUBCASE( case6, array_hs_db, axis );

    EXPAND_DIMS_SUBCASE( case6, array_ds_fb, axis );
    EXPAND_DIMS_SUBCASE( case6, array_ds_hb, axis );
    EXPAND_DIMS_SUBCASE( case6, array_ds_db, axis );

    EXPAND_DIMS_SUBCASE( case6, array_ls_fb, axis );
    EXPAND_DIMS_SUBCASE( case6, array_ls_hb, axis );
    EXPAND_DIMS_SUBCASE( case6, array_ls_db, axis );
    #endif
}

TEST_CASE("expand_dims(case7)" * doctest::test_suite("array::expand_dims"))
{
    #if !defined(NMTOOLS_TESTING_GENERIC_NDARRAY)
    EXPAND_DIMS_SUBCASE( case7, array,   axis );
    EXPAND_DIMS_SUBCASE( case7, array_a, axis );
    EXPAND_DIMS_SUBCASE( case7, array_f, axis );
    EXPAND_DIMS_SUBCASE( case7, array_d, axis );
    EXPAND_DIMS_SUBCASE( case7, array_h, axis );

    #else
    EXPAND_DIMS_SUBCASE( case7, array_cs_fb, axis );
    EXPAND_DIMS_SUBCASE( case7, array_cs_hb, axis );
    EXPAND_DIMS_SUBCASE( case7, array_cs_db, axis );

    EXPAND_DIMS_SUBCASE( case7, array_fs_fb, axis );
    EXPAND_DIMS_SUBCASE( case7, array_fs_hb, axis );
    EXPAND_DIMS_SUBCASE( case7, array_fs_db, axis );

    EXPAND_DIMS_SUBCASE( case7, array_hs_fb, axis );
    EXPAND_DIMS_SUBCASE( case7, array_hs_hb, axis );
    EXPAND_DIMS_SUBCASE( case7, array_hs_db, axis );

    EXPAND_DIMS_SUBCASE( case7, array_ds_fb, axis );
    EXPAND_DIMS_SUBCASE( case7, array_ds_hb, axis );
    EXPAND_DIMS_SUBCASE( case7, array_ds_db, axis );

    EXPAND_DIMS_SUBCASE( case7, array_ls_fb, axis );
    EXPAND_DIMS_SUBCASE( case7, array_ls_hb, axis );
    EXPAND_DIMS_SUBCASE( case7, array_ls_db, axis );
    #endif
}

TEST_CASE("expand_dims(case8)" * doctest::test_suite("array::expand_dims"))
{
    #if !defined(NMTOOLS_TESTING_GENERIC_NDARRAY)
    EXPAND_DIMS_SUBCASE( case8, array,   axis );
    EXPAND_DIMS_SUBCASE( case8, array_a, axis );
    EXPAND_DIMS_SUBCASE( case8, array_f, axis );
    EXPAND_DIMS_SUBCASE( case8, array_d, axis );
    EXPAND_DIMS_SUBCASE( case8, array_h, axis );

    #else
    EXPAND_DIMS_SUBCASE( case8, array_cs_fb, axis );
    EXPAND_DIMS_SUBCASE( case8, array_cs_hb, axis );
    EXPAND_DIMS_SUBCASE( case8, array_cs_db, axis );

    EXPAND_DIMS_SUBCASE( case8, array_fs_fb, axis );
    EXPAND_DIMS_SUBCASE( case8, array_fs_hb, axis );
    EXPAND_DIMS_SUBCASE( case8, array_fs_db, axis );

    EXPAND_DIMS_SUBCASE( case8, array_hs_fb, axis );
    EXPAND_DIMS_SUBCASE( case8, array_hs_hb, axis );
    EXPAND_DIMS_SUBCASE( case8, array_hs_db, axis );

    EXPAND_DIMS_SUBCASE( case8, array_ds_fb, axis );
    EXPAND_DIMS_SUBCASE( case8, array_ds_hb, axis );
    EXPAND_DIMS_SUBCASE( case8, array_ds_db, axis );

    EXPAND_DIMS_SUBCASE( case8, array_ls_fb, axis );
    EXPAND_DIMS_SUBCASE( case8, array_ls_hb, axis );
    EXPAND_DIMS_SUBCASE( case8, array_ls_db, axis );
    #endif
}

TEST_CASE("expand_dims(case9)" * doctest::test_suite("array::expand_dims"))
{
    #if !defined(NMTOOLS_TESTING_GENERIC_NDARRAY)
    EXPAND_DIMS_SUBCASE( case9, array,   axis );
    EXPAND_DIMS_SUBCASE( case9, array_a, axis );
    EXPAND_DIMS_SUBCASE( case9, array_f, axis );
    EXPAND_DIMS_SUBCASE( case9, array_d, axis );
    EXPAND_DIMS_SUBCASE( case9, array_h, axis );

    #else
    EXPAND_DIMS_SUBCASE( case9, array_cs_fb, axis );
    EXPAND_DIMS_SUBCASE( case9, array_cs_hb, axis );
    EXPAND_DIMS_SUBCASE( case9, array_cs_db, axis );

    EXPAND_DIMS_SUBCASE( case9, array_fs_fb, axis );
    EXPAND_DIMS_SUBCASE( case9, array_fs_hb, axis );
    EXPAND_DIMS_SUBCASE( case9, array_fs_db, axis );

    EXPAND_DIMS_SUBCASE( case9, array_hs_fb, axis );
    EXPAND_DIMS_SUBCASE( case9, array_hs_hb, axis );
    EXPAND_DIMS_SUBCASE( case9, array_hs_db, axis );

    EXPAND_DIMS_SUBCASE( case9, array_ds_fb, axis );
    EXPAND_DIMS_SUBCASE( case9, array_ds_hb, axis );
    EXPAND_DIMS_SUBCASE( case9, array_ds_db, axis );

    EXPAND_DIMS_SUBCASE( case9, array_ls_fb, axis );
    EXPAND_DIMS_SUBCASE( case9, array_ls_hb, axis );
    EXPAND_DIMS_SUBCASE( case9, array_ls_db, axis );
    #endif
}

TEST_CASE("expand_dims(case10)" * doctest::test_suite("array::expand_dims"))
{
    #if !defined(NMTOOLS_TESTING_GENERIC_NDARRAY)
    EXPAND_DIMS_SUBCASE( case10, array,   axis_a );
    EXPAND_DIMS_SUBCASE( case10, array_a, axis_a );
    EXPAND_DIMS_SUBCASE( case10, array_f, axis_a );
    EXPAND_DIMS_SUBCASE( case10, array_d, axis_a );
    EXPAND_DIMS_SUBCASE( case10, array_h, axis_a );

    #else
    EXPAND_DIMS_SUBCASE( case10, array_cs_fb, axis_a );
    EXPAND_DIMS_SUBCASE( case10, array_cs_hb, axis_a );
    EXPAND_DIMS_SUBCASE( case10, array_cs_db, axis_a );

    EXPAND_DIMS_SUBCASE( case10, array_fs_fb, axis_a );
    EXPAND_DIMS_SUBCASE( case10, array_fs_hb, axis_a );
    EXPAND_DIMS_SUBCASE( case10, array_fs_db, axis_a );

    EXPAND_DIMS_SUBCASE( case10, array_hs_fb, axis_a );
    EXPAND_DIMS_SUBCASE( case10, array_hs_hb, axis_a );
    EXPAND_DIMS_SUBCASE( case10, array_hs_db, axis_a );

    EXPAND_DIMS_SUBCASE( case10, array_ds_fb, axis_a );
    EXPAND_DIMS_SUBCASE( case10, array_ds_hb, axis_a );
    EXPAND_DIMS_SUBCASE( case10, array_ds_db, axis_a );

    EXPAND_DIMS_SUBCASE( case10, array_ls_fb, axis_a );
    EXPAND_DIMS_SUBCASE( case10, array_ls_hb, axis_a );
    EXPAND_DIMS_SUBCASE( case10, array_ls_db, axis_a );
    #endif
}