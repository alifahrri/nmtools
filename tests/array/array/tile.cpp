#include "nmtools/array/array/tile.hpp"
#include "nmtools/testing/data/array/tile.hpp"

#include "nmtools/testing/doctest.hpp"

#include <vector>
#include <array>
#include <tuple>

namespace nm = nmtools;
namespace na = nm::array;

#define RUN_impl(...) \
nm::array::tile(__VA_ARGS__);

#ifdef NMTOOLS_TESTING_ENABLE_BENCHMARKS
#include "nmtools/benchmarks/bench.hpp"
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
    NMTOOLS_TESTING_DECLARE_NS( view, tile, case_name ); \
    auto array_array = RUN_tile( case_name, args::array, args::reps ); \
    NMTOOLS_ASSERT_EQUAL( nm::dim(array_array), expect::dim ); \
    NMTOOLS_ASSERT_EQUAL( nm::shape(array_array), expect::shape ); \
    NMTOOLS_ASSERT_CLOSE( array_array, expect::result ); \
}

TEST_CASE("tile(case1)" * doctest::test_suite("array::tile"))
{
    TILE_ARRAY_SUBCASE( case1, array_a, reps_a );
    TILE_ARRAY_SUBCASE( case1, array_f, reps_a );
    TILE_ARRAY_SUBCASE( case1, array_d, reps_a );
    TILE_ARRAY_SUBCASE( case1, array_h, reps_a );
}

TEST_CASE("tile(case2)" * doctest::test_suite("array::tile"))
{
    TILE_ARRAY_SUBCASE( case2, array_a, reps_a );
    TILE_ARRAY_SUBCASE( case2, array_f, reps_a );
    TILE_ARRAY_SUBCASE( case2, array_d, reps_a );
    TILE_ARRAY_SUBCASE( case2, array_h, reps_a );
}


TEST_CASE("tile(case3)" * doctest::test_suite("array::tile"))
{
    TILE_ARRAY_SUBCASE( case3, array_a, reps_a );
    TILE_ARRAY_SUBCASE( case3, array_f, reps_a );
    TILE_ARRAY_SUBCASE( case3, array_d, reps_a );
    TILE_ARRAY_SUBCASE( case3, array_h, reps_a );
}

TEST_CASE("tile(case4)" * doctest::test_suite("array::tile"))
{
    TILE_ARRAY_SUBCASE( case4, array_a, reps_a );
    TILE_ARRAY_SUBCASE( case4, array_f, reps_a );
    TILE_ARRAY_SUBCASE( case4, array_d, reps_a );
    TILE_ARRAY_SUBCASE( case4, array_h, reps_a );
}

TEST_CASE("tile(case5)" * doctest::test_suite("array::tile"))
{
    TILE_ARRAY_SUBCASE( case5, array_a, reps_a );
    TILE_ARRAY_SUBCASE( case5, array_f, reps_a );
    TILE_ARRAY_SUBCASE( case5, array_d, reps_a );
    TILE_ARRAY_SUBCASE( case5, array_h, reps_a );
}