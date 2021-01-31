#include "nmtools/array/index/shape_tile.hpp"
#include "nmtools/array/ndarray/dynamic.hpp"
#include "nmtools/array/ndarray/hybrid.hpp"
#include "nmtools/array/ndarray/fixed.hpp"

#include "testing/doctest.hpp"

#include <vector>
#include <array>
#include <tuple>

namespace nm = nmtools;

NMTOOLS_TESTING_DECLARE_CASE(shape_tile)
{
    NMTOOLS_TESTING_DECLARE_ARGS(case1)
    {
        int shape[1] = {3};
        int reps[1] = {2};
        auto shape_a = cast<int>(shape);
        auto reps_a  = cast<int>(reps);
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case1)
    {
        int result[1] = {6};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case2)
    {
        int shape[1] = {3};
        int reps[2]  = {2,2};
        auto shape_a = cast<int>(shape);
        auto reps_a  = cast<int>(reps);
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case2)
    {
        int result[2] = {2,6};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case3)
    {
        int shape[1] = {3};
        int reps[3]  = {2,1,2};
        auto shape_a = cast<int>(shape);
        auto reps_a  = cast<int>(reps);
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case3)
    {
        int result[3] = {2,1,6};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case4)
    {
        int shape[1] = {3};
        int reps[2]  = {2,1};
        auto shape_a = cast<int>(shape);
        auto reps_a  = cast<int>(reps);
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case4)
    {
        int result[2] = {2,3};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case5)
    {
        int shape[3] = {2,1,4};
        int reps[2]  = {2,2};
        auto shape_a = cast<int>(shape);
        auto reps_a  = cast<int>(reps);
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case5)
    {
        int result[3] = {2,2,8};
    }
}

#define SHAPE_TILE_SUBCASE(case_name,shape,reps) \
SUBCASE(#case_name) \
{ \
    NMTOOLS_TESTING_DECLARE_NS( shape_tile, case_name ); \
    auto result = nm::index::shape_tile(args::shape,args::reps); \
    NMTOOLS_ASSERT_EQUAL( result, expect:: result ); \
}

TEST_CASE("shape_tile(array)" * doctest::test_suite("index::shape_tile"))
{
    SHAPE_TILE_SUBCASE( case1, shape_a, reps_a );
    SHAPE_TILE_SUBCASE( case2, shape_a, reps_a );
    SHAPE_TILE_SUBCASE( case3, shape_a, reps_a );
    SHAPE_TILE_SUBCASE( case4, shape_a, reps_a );
    SHAPE_TILE_SUBCASE( case5, shape_a, reps_a );
}