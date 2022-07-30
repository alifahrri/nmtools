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

#include "nmtools/array/view/where.hpp"
#include "nmtools/testing/doctest.hpp"
#include "nmtools/testing/data/array/where.hpp"

#include <array>
#include <vector>

#define RUN_impl(...) \
nm::view::where(__VA_ARGS__);

#ifdef NMTOOLS_TESTING_ENABLE_BENCHMARKS
#include "nmtools/benchmarks/bench.hpp"
using nm::benchmarks::TrackedBench;
// create immediately invoked lambda
// that packs where fn to callable lambda
#define RUN_where(case_name, ...) \
[](auto&&...args){ \
    auto title = std::string("where-") + #case_name; \
    auto name  = nm::testing::make_func_args("", args...); \
    auto fn    = [&](){ \
        return RUN_impl(args...); \
    }; \
    return TrackedBench::run(title, name, fn); \
}(__VA_ARGS__);
#else
// run normally without benchmarking, ignore case_name
#define RUN_where(case_name, ...) \
RUN_impl(__VA_ARGS__);
#endif // NMTOOLS_TESTING_ENABLE_BENCHMARKS

#define TILE_WHERE_SUBCASE(case_name,condition,x,y) \
SUBCASE(#case_name) \
{ \
    NMTOOLS_TESTING_DECLARE_NS( view, where, case_name ); \
    auto array_view = RUN_where( case_name, args::condition, args::x, args::y ); \
    NMTOOLS_ASSERT_EQUAL( array_view.dim(), expect::dim ); \
    NMTOOLS_ASSERT_EQUAL( array_view.shape(), expect::shape ); \
    NMTOOLS_ASSERT_CLOSE( array_view, expect::result ); \
}

TEST_CASE("where(case1)" * doctest::test_suite("view::where"))
{
    #if !defined(NMTOOLS_TESTING_GENERIC_NDARRAY)
    TILE_WHERE_SUBCASE(case1, condition,   x,   y  );
    TILE_WHERE_SUBCASE(case1, condition_a, x_a, y_a);
    TILE_WHERE_SUBCASE(case1, condition_f, x_f, y_f);
    TILE_WHERE_SUBCASE(case1, condition_d, x_d, y_d);
    TILE_WHERE_SUBCASE(case1, condition_h, x_h, y_h);
    
    #else
    TILE_WHERE_SUBCASE(case1, condition_cs_fb, x_cs_fb, y_cs_fb);
    TILE_WHERE_SUBCASE(case1, condition_cs_hb, x_cs_hb, y_cs_hb);
    TILE_WHERE_SUBCASE(case1, condition_cs_db, x_cs_db, y_cs_db);

    TILE_WHERE_SUBCASE(case1, condition_fs_fb, x_fs_fb, y_fs_fb);
    TILE_WHERE_SUBCASE(case1, condition_fs_hb, x_fs_hb, y_fs_hb);
    TILE_WHERE_SUBCASE(case1, condition_fs_db, x_fs_db, y_fs_db);

    TILE_WHERE_SUBCASE(case1, condition_hs_fb, x_hs_fb, y_hs_fb);
    TILE_WHERE_SUBCASE(case1, condition_hs_hb, x_hs_hb, y_hs_hb);
    TILE_WHERE_SUBCASE(case1, condition_hs_db, x_hs_db, y_hs_db);

    TILE_WHERE_SUBCASE(case1, condition_ds_fb, x_ds_fb, y_ds_fb);
    TILE_WHERE_SUBCASE(case1, condition_ds_hb, x_ds_hb, y_ds_hb);
    TILE_WHERE_SUBCASE(case1, condition_ds_db, x_ds_db, y_ds_db);
    #endif
}

TEST_CASE("where(case2)" * doctest::test_suite("view::where"))
{
    #if !defined(NMTOOLS_TESTING_GENERIC_NDARRAY)
    TILE_WHERE_SUBCASE(case2, condition,   x,   y  );
    TILE_WHERE_SUBCASE(case2, condition_a, x_a, y_a);
    TILE_WHERE_SUBCASE(case2, condition_f, x_f, y_f);
    TILE_WHERE_SUBCASE(case2, condition_d, x_d, y_d);
    TILE_WHERE_SUBCASE(case2, condition_h, x_h, y_h);

    #else
    TILE_WHERE_SUBCASE(case2, condition_cs_fb, x_cs_fb, y_cs_fb);
    TILE_WHERE_SUBCASE(case2, condition_cs_hb, x_cs_hb, y_cs_hb);
    TILE_WHERE_SUBCASE(case2, condition_cs_db, x_cs_db, y_cs_db);

    TILE_WHERE_SUBCASE(case2, condition_fs_fb, x_fs_fb, y_fs_fb);
    TILE_WHERE_SUBCASE(case2, condition_fs_hb, x_fs_hb, y_fs_hb);
    TILE_WHERE_SUBCASE(case2, condition_fs_db, x_fs_db, y_fs_db);

    TILE_WHERE_SUBCASE(case2, condition_hs_fb, x_hs_fb, y_hs_fb);
    TILE_WHERE_SUBCASE(case2, condition_hs_hb, x_hs_hb, y_hs_hb);
    TILE_WHERE_SUBCASE(case2, condition_hs_db, x_hs_db, y_hs_db);

    TILE_WHERE_SUBCASE(case2, condition_ds_fb, x_ds_fb, y_ds_fb);
    TILE_WHERE_SUBCASE(case2, condition_ds_hb, x_ds_hb, y_ds_hb);
    TILE_WHERE_SUBCASE(case2, condition_ds_db, x_ds_db, y_ds_db);
    #endif
}

TEST_CASE("where(case3)" * doctest::test_suite("view::where"))
{
    #if !defined(NMTOOLS_TESTING_GENERIC_NDARRAY)
    TILE_WHERE_SUBCASE(case3, condition,   x,   y  );
    TILE_WHERE_SUBCASE(case3, condition_a, x_a, y_a);
    TILE_WHERE_SUBCASE(case3, condition_f, x_f, y_f);
    TILE_WHERE_SUBCASE(case3, condition_d, x_d, y_d);
    TILE_WHERE_SUBCASE(case3, condition_h, x_h, y_h);

    #else
    TILE_WHERE_SUBCASE(case3, condition_cs_fb, x_cs_fb, y_cs_fb);
    TILE_WHERE_SUBCASE(case3, condition_cs_hb, x_cs_hb, y_cs_hb);
    TILE_WHERE_SUBCASE(case3, condition_cs_db, x_cs_db, y_cs_db);

    TILE_WHERE_SUBCASE(case3, condition_fs_fb, x_fs_fb, y_fs_fb);
    TILE_WHERE_SUBCASE(case3, condition_fs_hb, x_fs_hb, y_fs_hb);
    TILE_WHERE_SUBCASE(case3, condition_fs_db, x_fs_db, y_fs_db);

    TILE_WHERE_SUBCASE(case3, condition_hs_fb, x_hs_fb, y_hs_fb);
    TILE_WHERE_SUBCASE(case3, condition_hs_hb, x_hs_hb, y_hs_hb);
    TILE_WHERE_SUBCASE(case3, condition_hs_db, x_hs_db, y_hs_db);

    TILE_WHERE_SUBCASE(case3, condition_ds_fb, x_ds_fb, y_ds_fb);
    TILE_WHERE_SUBCASE(case3, condition_ds_hb, x_ds_hb, y_ds_hb);
    TILE_WHERE_SUBCASE(case3, condition_ds_db, x_ds_db, y_ds_db);
    #endif
}