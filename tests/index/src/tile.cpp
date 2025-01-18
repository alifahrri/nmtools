#include "nmtools/array/index/tile.hpp"
#include "nmtools/ndarray.hpp"

#include "nmtools/testing/doctest.hpp"

namespace nm = nmtools;
namespace na = nm::array;

using namespace nmtools::literals;

NMTOOLS_TESTING_DECLARE_CASE(shape_tile)
{
    NMTOOLS_TESTING_DECLARE_ARGS(case1)
    {
        inline int shape[1] = {3};
        inline int reps[1] = {2};
        inline auto shape_ct = nmtools_tuple{3_ct};
        inline auto reps_ct  = nmtools_tuple{2_ct};
        inline auto shape_cl = to_clipped(shape_ct);
        inline auto reps_cl  = to_clipped(reps_ct);
        NMTOOLS_CAST_INDEX_ARRAYS(shape)
        NMTOOLS_CAST_INDEX_ARRAYS(reps)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case1)
    {
        int result[1] = {6};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case2)
    {
        inline int shape[1]  = {3};
        inline int reps[2]   = {2,2};
        inline auto shape_ct = nmtools_tuple{3_ct};
        inline auto reps_ct  = nmtools_tuple{2_ct,2_ct};
        inline auto shape_cl = to_clipped(shape_ct);
        inline auto reps_cl  = to_clipped(reps_ct);
        NMTOOLS_CAST_INDEX_ARRAYS(shape)
        NMTOOLS_CAST_INDEX_ARRAYS(reps)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case2)
    {
        int result[2] = {2,6};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case3)
    {
        int shape[1] = {3};
        int reps[3]  = {2,1,2};
        inline auto shape_ct = nmtools_tuple{3_ct};
        inline auto reps_ct  = nmtools_tuple{2_ct,1_ct,2_ct};
        inline auto shape_cl = to_clipped(shape_ct);
        inline auto reps_cl  = to_clipped(reps_ct);
        NMTOOLS_CAST_INDEX_ARRAYS(shape)
        NMTOOLS_CAST_INDEX_ARRAYS(reps)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case3)
    {
        int result[3] = {2,1,6};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case4)
    {
        int shape[1] = {3};
        int reps[2]  = {2,1};
        inline auto shape_ct = nmtools_tuple{3_ct};
        inline auto reps_ct  = nmtools_tuple{2_ct,1_ct};
        inline auto shape_cl = to_clipped(shape_ct);
        inline auto reps_cl  = to_clipped(reps_ct);
        NMTOOLS_CAST_INDEX_ARRAYS(shape)
        NMTOOLS_CAST_INDEX_ARRAYS(reps)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case4)
    {
        int result[2] = {2,3};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case5)
    {
        int shape[3] = {2,1,4};
        int reps[2]  = {2,2};
        inline auto shape_ct = nmtools_tuple{2_ct,1_ct,4_ct};
        inline auto reps_ct  = nmtools_tuple{2_ct,2_ct};
        inline auto shape_cl = to_clipped(shape_ct);
        inline auto reps_cl  = to_clipped(reps_ct);
        NMTOOLS_CAST_INDEX_ARRAYS(shape)
        NMTOOLS_CAST_INDEX_ARRAYS(reps)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case5)
    {
        int result[3] = {2,2,8};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case6)
    {
        int8_t shape[3] = {2,1,4};
        int8_t reps[2]  = {2,2};
        inline auto shape_ct = nmtools_tuple{2_ct,1_ct,4_ct};
        inline auto reps_ct  = nmtools_tuple{2_ct,2_ct};
        inline auto shape_cl = to_clipped(shape_ct);
        inline auto reps_cl  = to_clipped(reps_ct);
        NMTOOLS_CAST_INDEX_ARRAYS(shape)
        NMTOOLS_CAST_INDEX_ARRAYS(reps)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case6)
    {
        int result[3] = {2,2,8};
    }
}

NMTOOLS_TESTING_DECLARE_CASE(constexpr_shape_tile)
{
    NMTOOLS_TESTING_DECLARE_ARGS(case1)
    {
        constexpr inline int shape[1] = {3};
        constexpr inline int reps[1] = {2};
        constexpr inline auto shape_ct = nmtools_tuple{3_ct};
        constexpr inline auto reps_ct  = nmtools_tuple{2_ct};
        constexpr inline auto shape_cl = to_clipped(shape_ct);
        constexpr inline auto reps_cl  = to_clipped(reps_ct);
        NMTOOLS_CONSTEXPR_CAST_ARRAYS(shape)
        NMTOOLS_CONSTEXPR_CAST_ARRAYS(reps)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case1)
    {
        constexpr inline int result[1] = {6};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case2)
    {
        constexpr inline int shape[1]  = {3};
        constexpr inline int reps[2]   = {2,2};
        constexpr inline auto shape_ct = nmtools_tuple{3_ct};
        constexpr inline auto reps_ct  = nmtools_tuple{2_ct,2_ct};
        constexpr inline auto shape_cl = to_clipped(shape_ct);
        constexpr inline auto reps_cl  = to_clipped(reps_ct);
        NMTOOLS_CONSTEXPR_CAST_ARRAYS(shape)
        NMTOOLS_CONSTEXPR_CAST_ARRAYS(reps)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case2)
    {
        constexpr int result[2] = {2,6};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case3)
    {
        constexpr inline int shape[1]  = {3};
        constexpr inline int reps[3]   = {2,1,2};
        constexpr inline auto shape_ct = nmtools_tuple{3_ct};
        constexpr inline auto reps_ct  = nmtools_tuple{2_ct,1_ct,2_ct};
        constexpr inline auto shape_cl = to_clipped(shape_ct);
        constexpr inline auto reps_cl  = to_clipped(reps_ct);
        NMTOOLS_CONSTEXPR_CAST_ARRAYS(shape)
        NMTOOLS_CONSTEXPR_CAST_ARRAYS(reps)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case3)
    {
        constexpr int result[3] = {2,1,6};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case4)
    {
        constexpr inline int shape[1] = {3};
        constexpr inline int reps[2]  = {2,1};
        constexpr inline auto shape_ct = nmtools_tuple{3_ct};
        constexpr inline auto reps_ct  = nmtools_tuple{2_ct,1_ct};
        constexpr inline auto shape_cl = to_clipped(shape_ct);
        constexpr inline auto reps_cl  = to_clipped(reps_ct);
        NMTOOLS_CONSTEXPR_CAST_ARRAYS(shape)
        NMTOOLS_CONSTEXPR_CAST_ARRAYS(reps)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case4)
    {
        constexpr int result[2] = {2,3};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case5)
    {
        constexpr inline int shape[3]  = {2,1,4};
        constexpr inline int reps[2]   = {2,2};
        constexpr inline auto shape_ct = nmtools_tuple{2_ct,1_ct,4_ct};
        constexpr inline auto reps_ct  = nmtools_tuple{2_ct,2_ct};
        constexpr inline auto shape_cl = to_clipped(shape_ct);
        constexpr inline auto reps_cl  = to_clipped(reps_ct);
        NMTOOLS_CONSTEXPR_CAST_ARRAYS(shape)
        NMTOOLS_CONSTEXPR_CAST_ARRAYS(reps)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case5)
    {
        constexpr int result[3] = {2,2,8};
    }
}

#define RUN_shape_tile_impl(...) \
nm::index::shape_tile(__VA_ARGS__);

#ifdef NMTOOLS_TESTING_ENABLE_BENCHMARKS
#include "nmtools/testing/benchmarks/bench.hpp"
using nm::benchmarks::TrackedBench;
// create immediately invoked lambda
// that packs shape_tile fn to callable lambda
#define RUN_shape_tile(case_name, ...) \
[](auto&&...args){ \
    auto title = std::string("shape_tile-") + #case_name; \
    auto name  = nm::testing::make_func_args("", args...); \
    auto fn    = [&](){ \
        return RUN_shape_tile_impl(args...); \
    }; \
    return TrackedBench::run(title, name, fn); \
}(__VA_ARGS__);
#else
// run normally without benchmarking, ignore case_name
#define RUN_shape_tile(case_name, ...) \
RUN_shape_tile_impl(__VA_ARGS__);
#endif // NMTOOLS_TESTING_ENABLE_BENCHMARKS

#define SHAPE_TILE_SUBCASE(case_name,shape,reps) \
SUBCASE(#case_name) \
{ \
    NMTOOLS_TESTING_USE_CASE( shape_tile, case_name ); \
    auto result = RUN_shape_tile( case_name, args::shape,args::reps ); \
    NMTOOLS_ASSERT_EQUAL( result, expect:: result ); \
}

#define CONSTEXPR_SHAPE_TILE_SUBCASE(case_name,shape,reps) \
SUBCASE(#case_name) \
{ \
    NMTOOLS_TESTING_USE_CASE( constexpr_shape_tile, case_name ); \
    constexpr auto result = RUN_shape_tile_impl( args::shape,args::reps ); \
    NMTOOLS_ASSERT_EQUAL( result, expect:: result ); \
}

TEST_CASE("shape_tile(case1)" * doctest::test_suite("index::shape_tile"))
{
    SHAPE_TILE_SUBCASE( case1, shape, reps );
    SHAPE_TILE_SUBCASE( case1, shape_a, reps_a );
    SHAPE_TILE_SUBCASE( case1, shape_v, reps_v );
    SHAPE_TILE_SUBCASE( case1, shape_f, reps_f );
    SHAPE_TILE_SUBCASE( case1, shape_h, reps_h );

    SHAPE_TILE_SUBCASE( case1, shape_ct, reps_ct );
    SHAPE_TILE_SUBCASE( case1, shape_ct, reps_cl );
    SHAPE_TILE_SUBCASE( case1, shape_ct, reps_a );
    SHAPE_TILE_SUBCASE( case1, shape_ct, reps_v );
    SHAPE_TILE_SUBCASE( case1, shape_ct, reps_f );
    SHAPE_TILE_SUBCASE( case1, shape_ct, reps_h );

    SHAPE_TILE_SUBCASE( case1, shape_cl, reps_cl );
    SHAPE_TILE_SUBCASE( case1, shape_cl, reps_ct );
    SHAPE_TILE_SUBCASE( case1, shape_cl, reps_a );
    SHAPE_TILE_SUBCASE( case1, shape_cl, reps_v );
    SHAPE_TILE_SUBCASE( case1, shape_cl, reps_f );
    SHAPE_TILE_SUBCASE( case1, shape_cl, reps_h );
}

TEST_CASE("shape_tile(case2)" * doctest::test_suite("index::shape_tile"))
{
    SHAPE_TILE_SUBCASE( case2, shape, reps );
    SHAPE_TILE_SUBCASE( case2, shape_a, reps_a );
    SHAPE_TILE_SUBCASE( case2, shape_v, reps_v );
    SHAPE_TILE_SUBCASE( case2, shape_f, reps_f );
    SHAPE_TILE_SUBCASE( case2, shape_h, reps_h );

    SHAPE_TILE_SUBCASE( case2, shape_ct, reps_ct );
    SHAPE_TILE_SUBCASE( case2, shape_ct, reps_cl );
    SHAPE_TILE_SUBCASE( case2, shape_ct, reps_a );
    SHAPE_TILE_SUBCASE( case2, shape_ct, reps_v );
    SHAPE_TILE_SUBCASE( case2, shape_ct, reps_f );
    SHAPE_TILE_SUBCASE( case2, shape_ct, reps_h );

    SHAPE_TILE_SUBCASE( case2, shape_cl, reps_cl );
    SHAPE_TILE_SUBCASE( case2, shape_cl, reps_ct );
    SHAPE_TILE_SUBCASE( case2, shape_cl, reps_a );
    SHAPE_TILE_SUBCASE( case2, shape_cl, reps_v );
    SHAPE_TILE_SUBCASE( case2, shape_cl, reps_f );
    SHAPE_TILE_SUBCASE( case2, shape_cl, reps_h );
}

TEST_CASE("shape_tile(case3)" * doctest::test_suite("index::shape_tile"))
{
    SHAPE_TILE_SUBCASE( case3, shape, reps );
    SHAPE_TILE_SUBCASE( case3, shape_a, reps_a );
    SHAPE_TILE_SUBCASE( case3, shape_v, reps_v );
    SHAPE_TILE_SUBCASE( case3, shape_f, reps_f );
    SHAPE_TILE_SUBCASE( case3, shape_h, reps_h );

    SHAPE_TILE_SUBCASE( case3, shape_ct, reps_ct );
    SHAPE_TILE_SUBCASE( case3, shape_ct, reps_cl );
    SHAPE_TILE_SUBCASE( case3, shape_ct, reps_a );
    SHAPE_TILE_SUBCASE( case3, shape_ct, reps_v );
    SHAPE_TILE_SUBCASE( case3, shape_ct, reps_f );
    SHAPE_TILE_SUBCASE( case3, shape_ct, reps_h );

    SHAPE_TILE_SUBCASE( case3, shape_cl, reps_cl );
    SHAPE_TILE_SUBCASE( case3, shape_cl, reps_ct );
    SHAPE_TILE_SUBCASE( case3, shape_cl, reps_a );
    SHAPE_TILE_SUBCASE( case3, shape_cl, reps_v );
    SHAPE_TILE_SUBCASE( case3, shape_cl, reps_f );
    SHAPE_TILE_SUBCASE( case3, shape_cl, reps_h );
}

TEST_CASE("shape_tile(case4)" * doctest::test_suite("index::shape_tile"))
{
    SHAPE_TILE_SUBCASE( case4, shape, reps );
    SHAPE_TILE_SUBCASE( case4, shape_a, reps_a );
    SHAPE_TILE_SUBCASE( case4, shape_v, reps_v );
    SHAPE_TILE_SUBCASE( case4, shape_f, reps_f );
    SHAPE_TILE_SUBCASE( case4, shape_h, reps_h );

    SHAPE_TILE_SUBCASE( case4, shape_ct, reps_ct );
    SHAPE_TILE_SUBCASE( case4, shape_ct, reps_cl );
    SHAPE_TILE_SUBCASE( case4, shape_ct, reps_a );
    SHAPE_TILE_SUBCASE( case4, shape_ct, reps_v );
    SHAPE_TILE_SUBCASE( case4, shape_ct, reps_f );
    SHAPE_TILE_SUBCASE( case4, shape_ct, reps_h );

    SHAPE_TILE_SUBCASE( case4, shape_cl, reps_cl );
    SHAPE_TILE_SUBCASE( case4, shape_cl, reps_ct );
    SHAPE_TILE_SUBCASE( case4, shape_cl, reps_a );
    SHAPE_TILE_SUBCASE( case4, shape_cl, reps_v );
    SHAPE_TILE_SUBCASE( case4, shape_cl, reps_f );
    SHAPE_TILE_SUBCASE( case4, shape_cl, reps_h );
}

TEST_CASE("shape_tile(case5)" * doctest::test_suite("index::shape_tile"))
{
    SHAPE_TILE_SUBCASE( case5, shape, reps );
    SHAPE_TILE_SUBCASE( case5, shape_a, reps_a );
    SHAPE_TILE_SUBCASE( case5, shape_v, reps_v );
    SHAPE_TILE_SUBCASE( case5, shape_f, reps_f );
    SHAPE_TILE_SUBCASE( case5, shape_h, reps_h );

    SHAPE_TILE_SUBCASE( case5, shape_ct, reps_ct );
    SHAPE_TILE_SUBCASE( case5, shape_ct, reps_cl );
    SHAPE_TILE_SUBCASE( case5, shape_ct, reps_a );
    SHAPE_TILE_SUBCASE( case5, shape_ct, reps_v );
    SHAPE_TILE_SUBCASE( case5, shape_ct, reps_f );
    SHAPE_TILE_SUBCASE( case5, shape_ct, reps_h );

    SHAPE_TILE_SUBCASE( case5, shape_cl, reps_cl );
    SHAPE_TILE_SUBCASE( case5, shape_cl, reps_ct );
    SHAPE_TILE_SUBCASE( case5, shape_cl, reps_a );
    SHAPE_TILE_SUBCASE( case5, shape_cl, reps_v );
    SHAPE_TILE_SUBCASE( case5, shape_cl, reps_f );
    SHAPE_TILE_SUBCASE( case5, shape_cl, reps_h );
}

TEST_CASE("shape_tile(case6)" * doctest::test_suite("index::shape_tile"))
{
    SHAPE_TILE_SUBCASE( case6, shape, reps );
    SHAPE_TILE_SUBCASE( case6, shape_a, reps_a );
    SHAPE_TILE_SUBCASE( case6, shape_v, reps_v );
    SHAPE_TILE_SUBCASE( case6, shape_f, reps_f );
    SHAPE_TILE_SUBCASE( case6, shape_h, reps_h );

    SHAPE_TILE_SUBCASE( case6, shape_ct, reps_ct );
    SHAPE_TILE_SUBCASE( case6, shape_ct, reps_cl );
    SHAPE_TILE_SUBCASE( case6, shape_ct, reps_a );
    SHAPE_TILE_SUBCASE( case6, shape_ct, reps_v );
    SHAPE_TILE_SUBCASE( case6, shape_ct, reps_f );
    SHAPE_TILE_SUBCASE( case6, shape_ct, reps_h );

    SHAPE_TILE_SUBCASE( case6, shape_cl, reps_cl );
    SHAPE_TILE_SUBCASE( case6, shape_cl, reps_ct );
    SHAPE_TILE_SUBCASE( case6, shape_cl, reps_a );
    SHAPE_TILE_SUBCASE( case6, shape_cl, reps_v );
    SHAPE_TILE_SUBCASE( case6, shape_cl, reps_f );
    SHAPE_TILE_SUBCASE( case6, shape_cl, reps_h );
}


TEST_CASE("shape_tile(case1)" * doctest::test_suite("index::constexpr_shape_tile"))
{
    CONSTEXPR_SHAPE_TILE_SUBCASE( case1, shape, reps );
    CONSTEXPR_SHAPE_TILE_SUBCASE( case1, shape_a, reps_a );
    CONSTEXPR_SHAPE_TILE_SUBCASE( case1, shape_f, reps_f );
    CONSTEXPR_SHAPE_TILE_SUBCASE( case1, shape_h, reps_h );

    CONSTEXPR_SHAPE_TILE_SUBCASE( case1, shape_ct, reps_ct );
}

TEST_CASE("shape_tile(case2)" * doctest::test_suite("index::constexpr_shape_tile"))
{
    CONSTEXPR_SHAPE_TILE_SUBCASE( case2, shape, reps );
    CONSTEXPR_SHAPE_TILE_SUBCASE( case2, shape_a, reps_a );
    CONSTEXPR_SHAPE_TILE_SUBCASE( case2, shape_f, reps_f );
    CONSTEXPR_SHAPE_TILE_SUBCASE( case2, shape_h, reps_h );

    CONSTEXPR_SHAPE_TILE_SUBCASE( case2, shape_ct, reps_ct );
}

TEST_CASE("shape_tile(case3)" * doctest::test_suite("index::constexpr_shape_tile"))
{
    CONSTEXPR_SHAPE_TILE_SUBCASE( case3, shape, reps );
    CONSTEXPR_SHAPE_TILE_SUBCASE( case3, shape_a, reps_a );
    CONSTEXPR_SHAPE_TILE_SUBCASE( case3, shape_f, reps_f );
    CONSTEXPR_SHAPE_TILE_SUBCASE( case3, shape_h, reps_h );

    CONSTEXPR_SHAPE_TILE_SUBCASE( case4, shape_ct, reps_ct );
}

TEST_CASE("shape_tile(case4)" * doctest::test_suite("index::constexpr_shape_tile"))
{
    CONSTEXPR_SHAPE_TILE_SUBCASE( case4, shape, reps );
    CONSTEXPR_SHAPE_TILE_SUBCASE( case4, shape_a, reps_a );
    CONSTEXPR_SHAPE_TILE_SUBCASE( case4, shape_f, reps_f );
    CONSTEXPR_SHAPE_TILE_SUBCASE( case4, shape_h, reps_h );

    CONSTEXPR_SHAPE_TILE_SUBCASE( case4, shape_ct, reps_ct );
}

TEST_CASE("shape_tile(case5)" * doctest::test_suite("index::constexpr_shape_tile"))
{
    CONSTEXPR_SHAPE_TILE_SUBCASE( case5, shape, reps );
    CONSTEXPR_SHAPE_TILE_SUBCASE( case5, shape_a, reps_a );
    CONSTEXPR_SHAPE_TILE_SUBCASE( case5, shape_f, reps_f );
    CONSTEXPR_SHAPE_TILE_SUBCASE( case5, shape_h, reps_h );

    CONSTEXPR_SHAPE_TILE_SUBCASE( case5, shape_ct, reps_ct );
}

#include "nmtools/array/index/tile.hpp"
#include "nmtools/ndarray.hpp"

#include "nmtools/testing/doctest.hpp"

namespace nm = nmtools;
namespace na = nm::array;
namespace kind = na::kind;

NMTOOLS_TESTING_DECLARE_CASE(tile)
{
    NMTOOLS_TESTING_DECLARE_ARGS(case1)
    {
        int shape[1] = {3};
        int reps[2]  = {2,2};
        int indices[2] = {1,5};
        NMTOOLS_CAST_INDEX_ARRAYS(shape)
        NMTOOLS_CAST_INDEX_ARRAYS(reps)
        NMTOOLS_CAST_INDEX_ARRAYS(indices)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case1)
    {
        int result[1] = {2};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case2)
    {
        int shape[1] = {3};
        int reps[2]  = {2,2};
        int indices[2] = {0,4};
        NMTOOLS_CAST_INDEX_ARRAYS(shape)
        NMTOOLS_CAST_INDEX_ARRAYS(reps)
        NMTOOLS_CAST_INDEX_ARRAYS(indices)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case2)
    {
        int result[1] = {1};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case3)
    {
        int shape[1] = {3};
        int reps[2]  = {2,2};
        int indices[2] = {1,3};
        NMTOOLS_CAST_INDEX_ARRAYS(shape)
        NMTOOLS_CAST_INDEX_ARRAYS(reps)
        NMTOOLS_CAST_INDEX_ARRAYS(indices)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case3)
    {
        int result[1] = {0};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case4)
    {
        int shape[1] = {3};
        int reps[2]  = {2,2};
        int indices[2] = {0,2};
        NMTOOLS_CAST_INDEX_ARRAYS(shape)
        NMTOOLS_CAST_INDEX_ARRAYS(reps)
        NMTOOLS_CAST_INDEX_ARRAYS(indices)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case4)
    {
        int result[1] = {2};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case5)
    {
        int shape[1] = {3};
        int reps[2]  = {2,2};
        int indices[2] = {1,1};
        NMTOOLS_CAST_INDEX_ARRAYS(shape)
        NMTOOLS_CAST_INDEX_ARRAYS(reps)
        NMTOOLS_CAST_INDEX_ARRAYS(indices)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case5)
    {
        int result[1] = {1};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case6)
    {
        int shape[3] = {2,1,4};
        int reps[2]  = {2,2};
        int indices[3] = {0,1,7};
        NMTOOLS_CAST_INDEX_ARRAYS(shape)
        NMTOOLS_CAST_INDEX_ARRAYS(reps)
        NMTOOLS_CAST_INDEX_ARRAYS(indices)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case6)
    {
        int result[3] = {0,0,3};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case7)
    {
        int shape[3] = {2,1,4};
        int reps[2]  = {2,2};
        int indices[3] = {1,0,4};
        NMTOOLS_CAST_INDEX_ARRAYS(shape)
        NMTOOLS_CAST_INDEX_ARRAYS(reps)
        NMTOOLS_CAST_INDEX_ARRAYS(indices)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case7)
    {
        int result[3] = {1,0,0};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case8)
    {
        int shape[3] = {2,1,4};
        int reps[2]  = {2,2};
        int indices[3] = {0,1,3};
        NMTOOLS_CAST_INDEX_ARRAYS(shape)
        NMTOOLS_CAST_INDEX_ARRAYS(reps)
        NMTOOLS_CAST_INDEX_ARRAYS(indices)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case8)
    {
        int result[3] = {0,0,3};
    }
}

#define RUN_impl(...) \
nm::index::tile(__VA_ARGS__);

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

#define TILE_SUBCASE(case_name, shape, reps, indices) \
SUBCASE(#case_name) \
{ \
    NMTOOLS_TESTING_USE_CASE(tile, case_name) \
    auto result = RUN_tile(case_name, args::shape, args::reps, args::indices); \
    NMTOOLS_ASSERT_EQUAL( result, expect::result ); \
}

TEST_CASE("tile(case1)" * doctest::test_suite("index::tile"))
{
    TILE_SUBCASE( case1, shape, reps, indices );
    TILE_SUBCASE( case1, shape_a, reps_a, indices_a );
    TILE_SUBCASE( case1, shape_f, reps_f, indices_f );
    TILE_SUBCASE( case1, shape_v, reps_v, indices_v );
    TILE_SUBCASE( case1, shape_h, reps_h, indices_h );
}

TEST_CASE("tile(case2)" * doctest::test_suite("index::tile"))
{
    TILE_SUBCASE( case2, shape, reps, indices );
    TILE_SUBCASE( case2, shape_a, reps_a, indices_a );
    TILE_SUBCASE( case2, shape_f, reps_f, indices_f );
    TILE_SUBCASE( case2, shape_v, reps_v, indices_v );
    TILE_SUBCASE( case2, shape_h, reps_h, indices_h );
}

TEST_CASE("tile(case3)" * doctest::test_suite("index::tile"))
{
    TILE_SUBCASE( case3, shape, reps, indices );
    TILE_SUBCASE( case3, shape_a, reps_a, indices_a );
    TILE_SUBCASE( case3, shape_f, reps_f, indices_f );
    TILE_SUBCASE( case3, shape_v, reps_v, indices_v );
    TILE_SUBCASE( case3, shape_h, reps_h, indices_h );
}

TEST_CASE("tile(case4)" * doctest::test_suite("index::tile"))
{
    TILE_SUBCASE( case4, shape, reps, indices );
    TILE_SUBCASE( case4, shape_a, reps_a, indices_a );
    TILE_SUBCASE( case4, shape_f, reps_f, indices_f );
    TILE_SUBCASE( case4, shape_v, reps_v, indices_v );
    TILE_SUBCASE( case4, shape_h, reps_h, indices_h );
}

TEST_CASE("tile(case5)" * doctest::test_suite("index::tile"))
{
    TILE_SUBCASE( case5, shape, reps, indices );
    TILE_SUBCASE( case5, shape_a, reps_a, indices_a );
    TILE_SUBCASE( case5, shape_f, reps_f, indices_f );
    TILE_SUBCASE( case5, shape_v, reps_v, indices_v );
    TILE_SUBCASE( case5, shape_h, reps_h, indices_h );
}

TEST_CASE("tile(case6)" * doctest::test_suite("index::tile"))
{
    TILE_SUBCASE( case6, shape, reps, indices );
    TILE_SUBCASE( case6, shape_a, reps_a, indices_a );
    TILE_SUBCASE( case6, shape_f, reps_f, indices_f );
    TILE_SUBCASE( case6, shape_v, reps_v, indices_v );
    TILE_SUBCASE( case6, shape_h, reps_h, indices_h );
}

TEST_CASE("tile(case7)" * doctest::test_suite("index::tile"))
{
    TILE_SUBCASE( case7, shape, reps, indices );
    TILE_SUBCASE( case7, shape_a, reps_a, indices_a );
    TILE_SUBCASE( case7, shape_f, reps_f, indices_f );
    TILE_SUBCASE( case7, shape_v, reps_v, indices_v );
    TILE_SUBCASE( case7, shape_h, reps_h, indices_h );
}

TEST_CASE("tile(case8)" * doctest::test_suite("index::tile"))
{
    TILE_SUBCASE( case8, shape, reps, indices );
    TILE_SUBCASE( case8, shape_a, reps_a, indices_a );
    TILE_SUBCASE( case8, shape_f, reps_f, indices_f );
    TILE_SUBCASE( case8, shape_v, reps_v, indices_v );
    TILE_SUBCASE( case8, shape_h, reps_h, indices_h );
}