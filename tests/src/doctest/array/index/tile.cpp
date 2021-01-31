#include "nmtools/array/index/tile.hpp"
#include "nmtools/array/ndarray/dynamic.hpp"
#include "nmtools/array/ndarray/hybrid.hpp"
#include "nmtools/array/ndarray/fixed.hpp"

#include "testing/doctest.hpp"

#include <vector>
#include <array>
#include <tuple>

namespace nm = nmtools;

NMTOOLS_TESTING_DECLARE_CASE(tile)
{
    NMTOOLS_TESTING_DECLARE_ARGS(case1)
    {
        int shape[1] = {3};
        int reps[2]  = {2,2};
        int indices[2] = {1,5};
        auto shape_a   = cast<int>(shape);
        auto reps_a    = cast<int>(reps);
        auto indices_a = cast<int>(indices);
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
        auto shape_a   = cast<int>(shape);
        auto reps_a    = cast<int>(reps);
        auto indices_a = cast<int>(indices);
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
        auto shape_a   = cast<int>(shape);
        auto reps_a    = cast<int>(reps);
        auto indices_a = cast<int>(indices);
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
        auto shape_a   = cast<int>(shape);
        auto reps_a    = cast<int>(reps);
        auto indices_a = cast<int>(indices);
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
        auto shape_a   = cast<int>(shape);
        auto reps_a    = cast<int>(reps);
        auto indices_a = cast<int>(indices);
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
        auto shape_a   = cast<int>(shape);
        auto reps_a    = cast<int>(reps);
        auto indices_a = cast<int>(indices);
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
        auto shape_a   = cast<int>(shape);
        auto reps_a    = cast<int>(reps);
        auto indices_a = cast<int>(indices);
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
        auto shape_a   = cast<int>(shape);
        auto reps_a    = cast<int>(reps);
        auto indices_a = cast<int>(indices);
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case8)
    {
        int result[3] = {0,0,3};
    }
}

#define TILE_SUBCASE(case_name, shape, reps, indices) \
SUBCASE(#case_name) \
{ \
    NMTOOLS_TESTING_DECLARE_NS(tile, case_name) \
    auto result = nm::index::tile(args::shape, args::reps, args::indices); \
    NMTOOLS_ASSERT_EQUAL( result, expect::result ); \
}

TEST_CASE("tile(array)" * doctest::test_suite("index::tile"))
{
    TILE_SUBCASE( case1, shape_a, reps_a, indices_a );
    TILE_SUBCASE( case2, shape_a, reps_a, indices_a );
    TILE_SUBCASE( case3, shape_a, reps_a, indices_a );
    TILE_SUBCASE( case4, shape_a, reps_a, indices_a );
    TILE_SUBCASE( case5, shape_a, reps_a, indices_a );
    TILE_SUBCASE( case6, shape_a, reps_a, indices_a );
    TILE_SUBCASE( case7, shape_a, reps_a, indices_a );
    TILE_SUBCASE( case8, shape_a, reps_a, indices_a );
}