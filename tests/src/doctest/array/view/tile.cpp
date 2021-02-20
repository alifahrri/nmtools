#include "nmtools/array/view/tile.hpp"
#include "nmtools/array/ndarray/dynamic.hpp"
#include "nmtools/array/ndarray/hybrid.hpp"
#include "nmtools/array/ndarray/fixed.hpp"

#include "testing/doctest.hpp"

#include <vector>
#include <array>
#include <tuple>

namespace nm = nmtools;
namespace na = nm::array;
namespace kind = na::kind;

NMTOOLS_TESTING_DECLARE_CASE(view, tile)
{
    NMTOOLS_TESTING_DECLARE_ARGS(case1)
    {
        int array[2][1][4] = {
            {
                {0,1,2,3},
            },
            {
                {4,5,6,7}
            }
        };
        int reps[2] = {2,2};
        auto array_a = cast<int>(array);
        auto reps_a  = cast<int>(reps);
        auto array_v = cast(array,kind::nested_vec);
        auto array_d = cast(array,kind::dynamic);
        auto array_f = cast(array,kind::fixed);
        auto array_h = cast(array,kind::hybrid);
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case1)
    {
        int dim = 3;
        int shape[3] = {2,2,8};
        int result[2][2][8] = {
            {
                {0,1,2,3,0,1,2,3},
                {0,1,2,3,0,1,2,3},
            },
            {
                {4,5,6,7,4,5,6,7},
                {4,5,6,7,4,5,6,7},
            }
        };
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case2)
    {
        int array[2][1][4] = {
            {
                {0,1,2,3},
            },
            {
                {4,5,6,7}
            }
        };
        int reps[3] = {2,1,2};
        auto array_a = cast<int>(array);
        auto reps_a  = cast<int>(reps);
        auto array_v = cast(array,kind::nested_vec);
        auto array_d = cast(array,kind::dynamic);
        auto array_f = cast(array,kind::fixed);
        auto array_h = cast(array,kind::hybrid);
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case2)
    {
        int dim = 3;
        int shape[3] = {4,1,8};
        int result[4][1][8] = {
            {
                {0,1,2,3,0,1,2,3},
            },
            {
                {4,5,6,7,4,5,6,7},
            },
            {
                {0,1,2,3,0,1,2,3},
            },
            {
                {4,5,6,7,4,5,6,7},
            }
        };
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case3)
    {
        int array[3] = {0,1,2};
        int reps[1]  = {2};
        auto array_a = cast<int>(array);
        auto reps_a  = cast<int>(reps);
        auto array_v = cast(array,kind::nested_vec);
        auto array_d = cast(array,kind::dynamic);
        auto array_f = cast(array,kind::fixed);
        auto array_h = cast(array,kind::hybrid);
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case3)
    {
        int dim = 1;
        int shape[1] = {6};
        int result[6] = {0,1,2,0,1,2};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case4)
    {
        int array[3] = {0,1,2};
        int reps[2]  = {1,2};
        auto array_a = cast<int>(array);
        auto reps_a  = cast<int>(reps);
        auto array_v = cast(array,kind::nested_vec);
        auto array_d = cast(array,kind::dynamic);
        auto array_f = cast(array,kind::fixed);
        auto array_h = cast(array,kind::hybrid);
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case4)
    {
        int dim = 2;
        int shape[2] = {1,6};
        int result[1][6] = {{0,1,2,0,1,2}};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case5)
    {
        int array[3] = {0,1,2};
        int reps[6]  = {2,1,1,1,1,1};
        auto array_a = cast<int>(array);
        auto reps_a  = cast<int>(reps);
        auto array_v = cast(array,kind::nested_vec);
        auto array_d = cast(array,kind::dynamic);
        auto array_f = cast(array,kind::fixed);
        auto array_h = cast(array,kind::hybrid);
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case5)
    {
        int dim = 6;
        int shape[6] = {2,1,1,1,1,3};
        int result[2][1][1][1][1][3] = {
            {{{{{0,1,2}}}}},
            {{{{{0,1,2}}}}},
        };
    }
}

#define RUN_impl(...) \
nm::view::tile(__VA_ARGS__);

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

#define TILE_VIEW_SUBCASE(case_name,array,reps) \
SUBCASE(#case_name) \
{ \
    NMTOOLS_TESTING_DECLARE_NS( view, tile, case_name ); \
    auto array_view = RUN_tile( case_name, args::array, args::reps ); \
    NMTOOLS_ASSERT_EQUAL( array_view.dim(), expect::dim ); \
    NMTOOLS_ASSERT_EQUAL( array_view.shape(), expect::shape ); \
    NMTOOLS_ASSERT_CLOSE( array_view, expect::result ); \
}

TEST_CASE("tile(case1)" * doctest::test_suite("view::tile"))
{
    TILE_VIEW_SUBCASE( case1, array_a, reps_a );
    TILE_VIEW_SUBCASE( case1, array_v, reps_a );
    TILE_VIEW_SUBCASE( case1, array_f, reps_a );
    TILE_VIEW_SUBCASE( case1, array_d, reps_a );
    TILE_VIEW_SUBCASE( case1, array_h, reps_a );
}

TEST_CASE("tile(case2)" * doctest::test_suite("view::tile"))
{
    TILE_VIEW_SUBCASE( case2, array_a, reps_a );
    TILE_VIEW_SUBCASE( case2, array_v, reps_a );
    TILE_VIEW_SUBCASE( case2, array_f, reps_a );
    TILE_VIEW_SUBCASE( case2, array_d, reps_a );
    TILE_VIEW_SUBCASE( case2, array_h, reps_a );
}


TEST_CASE("tile(case3)" * doctest::test_suite("view::tile"))
{
    TILE_VIEW_SUBCASE( case3, array_a, reps_a );
    TILE_VIEW_SUBCASE( case3, array_v, reps_a );
    TILE_VIEW_SUBCASE( case3, array_f, reps_a );
    TILE_VIEW_SUBCASE( case3, array_d, reps_a );
    TILE_VIEW_SUBCASE( case3, array_h, reps_a );
}

TEST_CASE("tile(case4)" * doctest::test_suite("view::tile"))
{
    TILE_VIEW_SUBCASE( case4, array_a, reps_a );
    TILE_VIEW_SUBCASE( case4, array_v, reps_a );
    TILE_VIEW_SUBCASE( case4, array_f, reps_a );
    TILE_VIEW_SUBCASE( case4, array_d, reps_a );
    TILE_VIEW_SUBCASE( case4, array_h, reps_a );
}

TEST_CASE("tile(case5)" * doctest::test_suite("view::tile"))
{
    TILE_VIEW_SUBCASE( case5, array_a, reps_a );
    TILE_VIEW_SUBCASE( case5, array_v, reps_a );
    TILE_VIEW_SUBCASE( case5, array_f, reps_a );
    TILE_VIEW_SUBCASE( case5, array_d, reps_a );
    TILE_VIEW_SUBCASE( case5, array_h, reps_a );
}