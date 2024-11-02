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

#include "nmtools/array/array/tile.hpp"
#include "nmtools/testing/data/array/tile.hpp"

#include "nmtools/testing/doctest.hpp"

namespace nm = nmtools;
namespace na = nm::array;

#define RUN_impl(...) \
nm::array::tile(__VA_ARGS__);

#ifdef NMTOOLS_TESTING_ENABLE_BENCHMARKS
#include "nmtools/testing/benchmarks/bench.hpp"
using nm::benchmarks::TrackedBench;
// create immediately invoked lambda
// that packs tile fn to callable lambda
#define RUN_tile(case_name, ...) \
[](auto&&...args){ \
    auto title = std::string("tile-") + #case_name; \
    auto name  = nm::testing::make_func_args("", args...); \
    auto fn    = [&](){ \
        return RUN_impl(args...); \
    }; \
    return TrackedBench::run(title, name, fn); \
}(__VA_ARGS__);
#else
// run normally without benchmarking, ignore case_name
#define RUN_tile(case_name, ...) \
RUN_impl(__VA_ARGS__);
#endif // NMTOOLS_TESTING_ENABLE_BENCHMARKS

#define TILE_ARRAY_SUBCASE(case_name,array,reps) \
SUBCASE(#case_name) \
{ \
    NMTOOLS_TESTING_USE_CASE( view, tile, case_name ); \
    auto array_array = RUN_tile( case_name, args::array, args::reps ); \
    NMTOOLS_ASSERT_EQUAL( nm::dim(array_array), expect::dim ); \
    NMTOOLS_ASSERT_EQUAL( nm::shape(array_array), expect::shape ); \
    NMTOOLS_ASSERT_CLOSE( array_array, expect::result ); \
}

TEST_CASE("tile(case1)" * doctest::test_suite("array::tile"))
{
    #if !defined(NMTOOLS_TESTING_GENERIC_NDARRAY)
    TILE_ARRAY_SUBCASE( case1, array_a, reps_a );
    TILE_ARRAY_SUBCASE( case1, array_f, reps_a );
    TILE_ARRAY_SUBCASE( case1, array_d, reps_a );
    TILE_ARRAY_SUBCASE( case1, array_h, reps_a );

    #else
    TILE_ARRAY_SUBCASE( case1, array_cs_fb, reps_a );
    TILE_ARRAY_SUBCASE( case1, array_cs_hb, reps_a );
    TILE_ARRAY_SUBCASE( case1, array_cs_db, reps_a );

    TILE_ARRAY_SUBCASE( case1, array_fs_fb, reps_a );
    TILE_ARRAY_SUBCASE( case1, array_fs_hb, reps_a );
    TILE_ARRAY_SUBCASE( case1, array_fs_db, reps_a );

    TILE_ARRAY_SUBCASE( case1, array_hs_fb, reps_a );
    TILE_ARRAY_SUBCASE( case1, array_hs_hb, reps_a );
    TILE_ARRAY_SUBCASE( case1, array_hs_db, reps_a );

    TILE_ARRAY_SUBCASE( case1, array_ds_fb, reps_a );
    TILE_ARRAY_SUBCASE( case1, array_ds_hb, reps_a );
    TILE_ARRAY_SUBCASE( case1, array_ds_db, reps_a );

    TILE_ARRAY_SUBCASE( case1, array_ls_fb, reps_a );
    TILE_ARRAY_SUBCASE( case1, array_ls_hb, reps_a );
    TILE_ARRAY_SUBCASE( case1, array_ls_db, reps_a );

    TILE_ARRAY_SUBCASE( case1, array_cs_fb, reps_ct );
    TILE_ARRAY_SUBCASE( case1, array_cs_hb, reps_ct );
    TILE_ARRAY_SUBCASE( case1, array_cs_db, reps_ct );

    TILE_ARRAY_SUBCASE( case1, array_fs_fb, reps_ct );
    TILE_ARRAY_SUBCASE( case1, array_fs_hb, reps_ct );
    TILE_ARRAY_SUBCASE( case1, array_fs_db, reps_ct );

    TILE_ARRAY_SUBCASE( case1, array_hs_fb, reps_ct );
    TILE_ARRAY_SUBCASE( case1, array_hs_hb, reps_ct );
    TILE_ARRAY_SUBCASE( case1, array_hs_db, reps_ct );

    TILE_ARRAY_SUBCASE( case1, array_ds_fb, reps_ct );
    TILE_ARRAY_SUBCASE( case1, array_ds_hb, reps_ct );
    TILE_ARRAY_SUBCASE( case1, array_ds_db, reps_ct );

    TILE_ARRAY_SUBCASE( case1, array_ls_fb, reps_ct );
    TILE_ARRAY_SUBCASE( case1, array_ls_hb, reps_ct );
    TILE_ARRAY_SUBCASE( case1, array_ls_db, reps_ct );

    TILE_ARRAY_SUBCASE( case1, array_cs_fb, reps_cl );
    TILE_ARRAY_SUBCASE( case1, array_cs_hb, reps_cl );
    TILE_ARRAY_SUBCASE( case1, array_cs_db, reps_cl );

    TILE_ARRAY_SUBCASE( case1, array_fs_fb, reps_cl );
    TILE_ARRAY_SUBCASE( case1, array_fs_hb, reps_cl );
    TILE_ARRAY_SUBCASE( case1, array_fs_db, reps_cl );

    TILE_ARRAY_SUBCASE( case1, array_hs_fb, reps_cl );
    TILE_ARRAY_SUBCASE( case1, array_hs_hb, reps_cl );
    TILE_ARRAY_SUBCASE( case1, array_hs_db, reps_cl );

    TILE_ARRAY_SUBCASE( case1, array_ds_fb, reps_cl );
    TILE_ARRAY_SUBCASE( case1, array_ds_hb, reps_cl );
    TILE_ARRAY_SUBCASE( case1, array_ds_db, reps_cl );

    TILE_ARRAY_SUBCASE( case1, array_ls_fb, reps_cl );
    TILE_ARRAY_SUBCASE( case1, array_ls_hb, reps_cl );
    TILE_ARRAY_SUBCASE( case1, array_ls_db, reps_cl );
    #endif
}

TEST_CASE("tile(case2)" * doctest::test_suite("array::tile"))
{
    #if !defined(NMTOOLS_TESTING_GENERIC_NDARRAY)
    TILE_ARRAY_SUBCASE( case2, array_a, reps_a );
    TILE_ARRAY_SUBCASE( case2, array_f, reps_a );
    TILE_ARRAY_SUBCASE( case2, array_d, reps_a );
    TILE_ARRAY_SUBCASE( case2, array_h, reps_a );

    #else
    TILE_ARRAY_SUBCASE( case2, array_cs_fb, reps_a );
    TILE_ARRAY_SUBCASE( case2, array_cs_hb, reps_a );
    TILE_ARRAY_SUBCASE( case2, array_cs_db, reps_a );

    TILE_ARRAY_SUBCASE( case2, array_fs_fb, reps_a );
    TILE_ARRAY_SUBCASE( case2, array_fs_hb, reps_a );
    TILE_ARRAY_SUBCASE( case2, array_fs_db, reps_a );

    TILE_ARRAY_SUBCASE( case2, array_hs_fb, reps_a );
    TILE_ARRAY_SUBCASE( case2, array_hs_hb, reps_a );
    TILE_ARRAY_SUBCASE( case2, array_hs_db, reps_a );

    TILE_ARRAY_SUBCASE( case2, array_ds_fb, reps_a );
    TILE_ARRAY_SUBCASE( case2, array_ds_hb, reps_a );
    TILE_ARRAY_SUBCASE( case2, array_ds_db, reps_a );

    TILE_ARRAY_SUBCASE( case2, array_ls_fb, reps_a );
    TILE_ARRAY_SUBCASE( case2, array_ls_hb, reps_a );
    TILE_ARRAY_SUBCASE( case2, array_ls_db, reps_a );

    TILE_ARRAY_SUBCASE( case2, array_cs_fb, reps_ct );
    TILE_ARRAY_SUBCASE( case2, array_cs_hb, reps_ct );
    TILE_ARRAY_SUBCASE( case2, array_cs_db, reps_ct );

    TILE_ARRAY_SUBCASE( case2, array_fs_fb, reps_ct );
    TILE_ARRAY_SUBCASE( case2, array_fs_hb, reps_ct );
    TILE_ARRAY_SUBCASE( case2, array_fs_db, reps_ct );

    TILE_ARRAY_SUBCASE( case2, array_hs_fb, reps_ct );
    TILE_ARRAY_SUBCASE( case2, array_hs_hb, reps_ct );
    TILE_ARRAY_SUBCASE( case2, array_hs_db, reps_ct );

    TILE_ARRAY_SUBCASE( case2, array_ds_fb, reps_ct );
    TILE_ARRAY_SUBCASE( case2, array_ds_hb, reps_ct );
    TILE_ARRAY_SUBCASE( case2, array_ds_db, reps_ct );

    TILE_ARRAY_SUBCASE( case2, array_ls_fb, reps_ct );
    TILE_ARRAY_SUBCASE( case2, array_ls_hb, reps_ct );
    TILE_ARRAY_SUBCASE( case2, array_ls_db, reps_ct );

    TILE_ARRAY_SUBCASE( case2, array_cs_fb, reps_cl );
    TILE_ARRAY_SUBCASE( case2, array_cs_hb, reps_cl );
    TILE_ARRAY_SUBCASE( case2, array_cs_db, reps_cl );

    TILE_ARRAY_SUBCASE( case2, array_fs_fb, reps_cl );
    TILE_ARRAY_SUBCASE( case2, array_fs_hb, reps_cl );
    TILE_ARRAY_SUBCASE( case2, array_fs_db, reps_cl );

    TILE_ARRAY_SUBCASE( case2, array_hs_fb, reps_cl );
    TILE_ARRAY_SUBCASE( case2, array_hs_hb, reps_cl );
    TILE_ARRAY_SUBCASE( case2, array_hs_db, reps_cl );

    TILE_ARRAY_SUBCASE( case2, array_ds_fb, reps_cl );
    TILE_ARRAY_SUBCASE( case2, array_ds_hb, reps_cl );
    TILE_ARRAY_SUBCASE( case2, array_ds_db, reps_cl );

    TILE_ARRAY_SUBCASE( case2, array_ls_fb, reps_cl );
    TILE_ARRAY_SUBCASE( case2, array_ls_hb, reps_cl );
    TILE_ARRAY_SUBCASE( case2, array_ls_db, reps_cl );
    #endif
}


TEST_CASE("tile(case3)" * doctest::test_suite("array::tile"))
{
    #if !defined(NMTOOLS_TESTING_GENERIC_NDARRAY)
    TILE_ARRAY_SUBCASE( case3, array_a, reps_a );
    TILE_ARRAY_SUBCASE( case3, array_f, reps_a );
    TILE_ARRAY_SUBCASE( case3, array_d, reps_a );
    TILE_ARRAY_SUBCASE( case3, array_h, reps_a );

    #else
    TILE_ARRAY_SUBCASE( case3, array_cs_fb, reps_a );
    TILE_ARRAY_SUBCASE( case3, array_cs_hb, reps_a );
    TILE_ARRAY_SUBCASE( case3, array_cs_db, reps_a );

    TILE_ARRAY_SUBCASE( case3, array_fs_fb, reps_a );
    TILE_ARRAY_SUBCASE( case3, array_fs_hb, reps_a );
    TILE_ARRAY_SUBCASE( case3, array_fs_db, reps_a );

    TILE_ARRAY_SUBCASE( case3, array_hs_fb, reps_a );
    TILE_ARRAY_SUBCASE( case3, array_hs_hb, reps_a );
    TILE_ARRAY_SUBCASE( case3, array_hs_db, reps_a );

    TILE_ARRAY_SUBCASE( case3, array_ds_fb, reps_a );
    TILE_ARRAY_SUBCASE( case3, array_ds_hb, reps_a );
    TILE_ARRAY_SUBCASE( case3, array_ds_db, reps_a );

    TILE_ARRAY_SUBCASE( case3, array_ls_fb, reps_a );
    TILE_ARRAY_SUBCASE( case3, array_ls_hb, reps_a );
    TILE_ARRAY_SUBCASE( case3, array_ls_db, reps_a );

    TILE_ARRAY_SUBCASE( case3, array_cs_fb, reps_ct );
    TILE_ARRAY_SUBCASE( case3, array_cs_hb, reps_ct );
    TILE_ARRAY_SUBCASE( case3, array_cs_db, reps_ct );

    TILE_ARRAY_SUBCASE( case3, array_fs_fb, reps_ct );
    TILE_ARRAY_SUBCASE( case3, array_fs_hb, reps_ct );
    TILE_ARRAY_SUBCASE( case3, array_fs_db, reps_ct );

    TILE_ARRAY_SUBCASE( case3, array_hs_fb, reps_ct );
    TILE_ARRAY_SUBCASE( case3, array_hs_hb, reps_ct );
    TILE_ARRAY_SUBCASE( case3, array_hs_db, reps_ct );

    TILE_ARRAY_SUBCASE( case3, array_ds_fb, reps_ct );
    TILE_ARRAY_SUBCASE( case3, array_ds_hb, reps_ct );
    TILE_ARRAY_SUBCASE( case3, array_ds_db, reps_ct );

    TILE_ARRAY_SUBCASE( case3, array_ls_fb, reps_ct );
    TILE_ARRAY_SUBCASE( case3, array_ls_hb, reps_ct );
    TILE_ARRAY_SUBCASE( case3, array_ls_db, reps_ct );

    TILE_ARRAY_SUBCASE( case3, array_cs_fb, reps_cl );
    TILE_ARRAY_SUBCASE( case3, array_cs_hb, reps_cl );
    TILE_ARRAY_SUBCASE( case3, array_cs_db, reps_cl );

    TILE_ARRAY_SUBCASE( case3, array_fs_fb, reps_cl );
    TILE_ARRAY_SUBCASE( case3, array_fs_hb, reps_cl );
    TILE_ARRAY_SUBCASE( case3, array_fs_db, reps_cl );

    TILE_ARRAY_SUBCASE( case3, array_hs_fb, reps_cl );
    TILE_ARRAY_SUBCASE( case3, array_hs_hb, reps_cl );
    TILE_ARRAY_SUBCASE( case3, array_hs_db, reps_cl );

    TILE_ARRAY_SUBCASE( case3, array_ds_fb, reps_cl );
    TILE_ARRAY_SUBCASE( case3, array_ds_hb, reps_cl );
    TILE_ARRAY_SUBCASE( case3, array_ds_db, reps_cl );

    TILE_ARRAY_SUBCASE( case3, array_ls_fb, reps_cl );
    TILE_ARRAY_SUBCASE( case3, array_ls_hb, reps_cl );
    TILE_ARRAY_SUBCASE( case3, array_ls_db, reps_cl );
    #endif
}

TEST_CASE("tile(case4)" * doctest::test_suite("array::tile"))
{
    #if !defined(NMTOOLS_TESTING_GENERIC_NDARRAY)
    TILE_ARRAY_SUBCASE( case4, array_a, reps_a );
    TILE_ARRAY_SUBCASE( case4, array_f, reps_a );
    TILE_ARRAY_SUBCASE( case4, array_d, reps_a );
    TILE_ARRAY_SUBCASE( case4, array_h, reps_a );

    #else
    TILE_ARRAY_SUBCASE( case4, array_cs_fb, reps_a );
    TILE_ARRAY_SUBCASE( case4, array_cs_hb, reps_a );
    TILE_ARRAY_SUBCASE( case4, array_cs_db, reps_a );

    TILE_ARRAY_SUBCASE( case4, array_fs_fb, reps_a );
    TILE_ARRAY_SUBCASE( case4, array_fs_hb, reps_a );
    TILE_ARRAY_SUBCASE( case4, array_fs_db, reps_a );

    TILE_ARRAY_SUBCASE( case4, array_hs_fb, reps_a );
    TILE_ARRAY_SUBCASE( case4, array_hs_hb, reps_a );
    TILE_ARRAY_SUBCASE( case4, array_hs_db, reps_a );

    TILE_ARRAY_SUBCASE( case4, array_ds_fb, reps_a );
    TILE_ARRAY_SUBCASE( case4, array_ds_hb, reps_a );
    TILE_ARRAY_SUBCASE( case4, array_ds_db, reps_a );

    TILE_ARRAY_SUBCASE( case4, array_ls_fb, reps_a );
    TILE_ARRAY_SUBCASE( case4, array_ls_hb, reps_a );
    TILE_ARRAY_SUBCASE( case4, array_ls_db, reps_a );

    TILE_ARRAY_SUBCASE( case4, array_cs_fb, reps_ct );
    TILE_ARRAY_SUBCASE( case4, array_cs_hb, reps_ct );
    TILE_ARRAY_SUBCASE( case4, array_cs_db, reps_ct );

    TILE_ARRAY_SUBCASE( case4, array_fs_fb, reps_ct );
    TILE_ARRAY_SUBCASE( case4, array_fs_hb, reps_ct );
    TILE_ARRAY_SUBCASE( case4, array_fs_db, reps_ct );

    TILE_ARRAY_SUBCASE( case4, array_hs_fb, reps_ct );
    TILE_ARRAY_SUBCASE( case4, array_hs_hb, reps_ct );
    TILE_ARRAY_SUBCASE( case4, array_hs_db, reps_ct );

    TILE_ARRAY_SUBCASE( case4, array_ds_fb, reps_ct );
    TILE_ARRAY_SUBCASE( case4, array_ds_hb, reps_ct );
    TILE_ARRAY_SUBCASE( case4, array_ds_db, reps_ct );

    TILE_ARRAY_SUBCASE( case4, array_ls_fb, reps_ct );
    TILE_ARRAY_SUBCASE( case4, array_ls_hb, reps_ct );
    TILE_ARRAY_SUBCASE( case4, array_ls_db, reps_ct );

    TILE_ARRAY_SUBCASE( case4, array_cs_fb, reps_cl );
    TILE_ARRAY_SUBCASE( case4, array_cs_hb, reps_cl );
    TILE_ARRAY_SUBCASE( case4, array_cs_db, reps_cl );

    TILE_ARRAY_SUBCASE( case4, array_fs_fb, reps_cl );
    TILE_ARRAY_SUBCASE( case4, array_fs_hb, reps_cl );
    TILE_ARRAY_SUBCASE( case4, array_fs_db, reps_cl );

    TILE_ARRAY_SUBCASE( case4, array_hs_fb, reps_cl );
    TILE_ARRAY_SUBCASE( case4, array_hs_hb, reps_cl );
    TILE_ARRAY_SUBCASE( case4, array_hs_db, reps_cl );

    TILE_ARRAY_SUBCASE( case4, array_ds_fb, reps_cl );
    TILE_ARRAY_SUBCASE( case4, array_ds_hb, reps_cl );
    TILE_ARRAY_SUBCASE( case4, array_ds_db, reps_cl );

    TILE_ARRAY_SUBCASE( case4, array_ls_fb, reps_cl );
    TILE_ARRAY_SUBCASE( case4, array_ls_hb, reps_cl );
    TILE_ARRAY_SUBCASE( case4, array_ls_db, reps_cl );
    #endif
}

TEST_CASE("tile(case5)" * doctest::test_suite("array::tile"))
{
    #if !defined(NMTOOLS_TESTING_GENERIC_NDARRAY)
    TILE_ARRAY_SUBCASE( case5, array_a, reps_a );
    TILE_ARRAY_SUBCASE( case5, array_f, reps_a );
    TILE_ARRAY_SUBCASE( case5, array_d, reps_a );
    TILE_ARRAY_SUBCASE( case5, array_h, reps_a );

    #else
    TILE_ARRAY_SUBCASE( case5, array_cs_fb, reps_a );
    TILE_ARRAY_SUBCASE( case5, array_cs_hb, reps_a );
    TILE_ARRAY_SUBCASE( case5, array_cs_db, reps_a );

    TILE_ARRAY_SUBCASE( case5, array_fs_fb, reps_a );
    TILE_ARRAY_SUBCASE( case5, array_fs_hb, reps_a );
    TILE_ARRAY_SUBCASE( case5, array_fs_db, reps_a );

    TILE_ARRAY_SUBCASE( case5, array_hs_fb, reps_a );
    TILE_ARRAY_SUBCASE( case5, array_hs_hb, reps_a );
    TILE_ARRAY_SUBCASE( case5, array_hs_db, reps_a );

    TILE_ARRAY_SUBCASE( case5, array_ds_fb, reps_a );
    TILE_ARRAY_SUBCASE( case5, array_ds_hb, reps_a );
    TILE_ARRAY_SUBCASE( case5, array_ds_db, reps_a );

    TILE_ARRAY_SUBCASE( case5, array_ls_fb, reps_a );
    TILE_ARRAY_SUBCASE( case5, array_ls_hb, reps_a );
    TILE_ARRAY_SUBCASE( case5, array_ls_db, reps_a );

    TILE_ARRAY_SUBCASE( case5, array_cs_fb, reps_ct );
    TILE_ARRAY_SUBCASE( case5, array_cs_hb, reps_ct );
    TILE_ARRAY_SUBCASE( case5, array_cs_db, reps_ct );

    TILE_ARRAY_SUBCASE( case5, array_fs_fb, reps_ct );
    TILE_ARRAY_SUBCASE( case5, array_fs_hb, reps_ct );
    TILE_ARRAY_SUBCASE( case5, array_fs_db, reps_ct );

    TILE_ARRAY_SUBCASE( case5, array_hs_fb, reps_ct );
    TILE_ARRAY_SUBCASE( case5, array_hs_hb, reps_ct );
    TILE_ARRAY_SUBCASE( case5, array_hs_db, reps_ct );

    TILE_ARRAY_SUBCASE( case5, array_ds_fb, reps_ct );
    TILE_ARRAY_SUBCASE( case5, array_ds_hb, reps_ct );
    TILE_ARRAY_SUBCASE( case5, array_ds_db, reps_ct );

    TILE_ARRAY_SUBCASE( case5, array_ls_fb, reps_ct );
    TILE_ARRAY_SUBCASE( case5, array_ls_hb, reps_ct );
    TILE_ARRAY_SUBCASE( case5, array_ls_db, reps_ct );

    TILE_ARRAY_SUBCASE( case5, array_cs_fb, reps_cl );
    TILE_ARRAY_SUBCASE( case5, array_cs_hb, reps_cl );
    TILE_ARRAY_SUBCASE( case5, array_cs_db, reps_cl );

    TILE_ARRAY_SUBCASE( case5, array_fs_fb, reps_cl );
    TILE_ARRAY_SUBCASE( case5, array_fs_hb, reps_cl );
    TILE_ARRAY_SUBCASE( case5, array_fs_db, reps_cl );

    TILE_ARRAY_SUBCASE( case5, array_hs_fb, reps_cl );
    TILE_ARRAY_SUBCASE( case5, array_hs_hb, reps_cl );
    TILE_ARRAY_SUBCASE( case5, array_hs_db, reps_cl );

    TILE_ARRAY_SUBCASE( case5, array_ds_fb, reps_cl );
    TILE_ARRAY_SUBCASE( case5, array_ds_hb, reps_cl );
    TILE_ARRAY_SUBCASE( case5, array_ds_db, reps_cl );

    TILE_ARRAY_SUBCASE( case5, array_ls_fb, reps_cl );
    TILE_ARRAY_SUBCASE( case5, array_ls_hb, reps_cl );
    TILE_ARRAY_SUBCASE( case5, array_ls_db, reps_cl );
    #endif
}