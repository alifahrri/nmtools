#include "nmtools/array/index/shape_repeat.hpp"
#include "nmtools/array/index/as_tuple.hpp"
#include "nmtools/array/ndarray/dynamic.hpp"
#include "nmtools/array/ndarray/hybrid.hpp"
#include "nmtools/array/ndarray/fixed.hpp"
#include "testing/doctest.hpp"

#include <vector>
#include <array>
#include <tuple>

namespace nm = nmtools;
namespace na = nm::array;

NMTOOLS_TESTING_DECLARE_CASE(shape_repeat)
{
    NMTOOLS_TESTING_DECLARE_ARGS(case1)
    {
        int shape[2] = {2,2};
        int repeats  = 3;
        auto axis    = None;
        auto shape_a = cast<int>(shape);
        auto shape_v = cast<std::vector<int>>(shape);
        auto shape_f = cast<na::fixed_vector<int,2>>(shape);
        auto shape_d = cast<na::dynamic_vector<int>>(shape);
        auto shape_h = cast<na::hybrid_ndarray<int,2,1>>(shape);
        auto shape_t = index::as_tuple(shape_a);
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case1)
    {
        int shape[1] = {12};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case2)
    {
        int shape[2] = {2,2};
        int repeats  = 3;
        auto axis    = 0;
        auto shape_a = cast<int>(shape);
        auto shape_v = cast<std::vector<int>>(shape);
        auto shape_f = cast<na::fixed_vector<int,2>>(shape);
        auto shape_d = cast<na::dynamic_vector<int>>(shape);
        auto shape_h = cast<na::hybrid_ndarray<int,2,1>>(shape);
        auto shape_t = index::as_tuple(shape_a);
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case2)
    {
        int shape[2] = {6,2};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case3)
    {
        int shape[2] = {2,2};
        int repeats  = 3;
        auto axis    = 1;
        auto shape_a = cast<int>(shape);
        auto shape_v = cast<std::vector<int>>(shape);
        auto shape_f = cast<na::fixed_vector<int,2>>(shape);
        auto shape_d = cast<na::dynamic_vector<int>>(shape);
        auto shape_h = cast<na::hybrid_ndarray<int,2,1>>(shape);
        auto shape_t = index::as_tuple(shape_a);
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case3)
    {
        int shape[2] = {2,6};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case4)
    {
        int shape[2]   = {2,2};
        int repeats[2] = {1,2};
        auto axis    = 1;
        auto shape_a = cast<int>(shape);
        auto shape_v = cast<std::vector<int>>(shape);
        auto shape_f = cast<na::fixed_vector<int,2>>(shape);
        auto shape_d = cast<na::dynamic_vector<int>>(shape);
        auto shape_h = cast<na::hybrid_ndarray<int,2,1>>(shape);
        auto shape_t = index::as_tuple(shape_a);
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case4)
    {
        int shape[2] = {2,3};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case5)
    {
        int shape[2]   = {2,2};
        int repeats[2] = {1,2};
        auto axis    = 0;
        auto shape_a = cast<int>(shape);
        auto shape_v = cast<std::vector<int>>(shape);
        auto shape_f = cast<na::fixed_vector<int,2>>(shape);
        auto shape_d = cast<na::dynamic_vector<int>>(shape);
        auto shape_h = cast<na::hybrid_ndarray<int,2,1>>(shape);
        auto shape_t = index::as_tuple(shape_a);
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case5)
    {
        int shape[2] = {3,2};
    }
}

#define SHAPE_REPEAT_SUBCASE(case_name,ashape,repeats,axis) \
SUBCASE(#case_name) \
{ \
    NMTOOLS_TESTING_DECLARE_NS(shape_repeat, case_name); \
    auto shape = nm::index::shape_repeat(args::ashape, args::repeats, args::axis); \
    NMTOOLS_ASSERT_EQUAL( shape, expect::shape ); \
}

TEST_CASE("shape_repeat(vector)" * doctest::test_suite("index::shape_repeat"))
{
    SHAPE_REPEAT_SUBCASE( case1, shape_v, repeats, axis );
    SHAPE_REPEAT_SUBCASE( case2, shape_v, repeats, axis );
    SHAPE_REPEAT_SUBCASE( case3, shape_v, repeats, axis );
    SHAPE_REPEAT_SUBCASE( case4, shape_v, repeats, axis );
    SHAPE_REPEAT_SUBCASE( case5, shape_v, repeats, axis );
}

TEST_CASE("shape_repeat(array)" * doctest::test_suite("index::shape_repeat"))
{
    SHAPE_REPEAT_SUBCASE( case1, shape_a, repeats, axis );
    SHAPE_REPEAT_SUBCASE( case2, shape_a, repeats, axis );
    SHAPE_REPEAT_SUBCASE( case3, shape_a, repeats, axis );
    SHAPE_REPEAT_SUBCASE( case4, shape_a, repeats, axis );
    SHAPE_REPEAT_SUBCASE( case5, shape_a, repeats, axis );
}

TEST_CASE("shape_repeat(fixed_vector)" * doctest::test_suite("index::shape_repeat"))
{
    SHAPE_REPEAT_SUBCASE( case1, shape_f, repeats, axis );
    SHAPE_REPEAT_SUBCASE( case2, shape_f, repeats, axis );
    SHAPE_REPEAT_SUBCASE( case3, shape_f, repeats, axis );
    SHAPE_REPEAT_SUBCASE( case4, shape_f, repeats, axis );
    SHAPE_REPEAT_SUBCASE( case5, shape_f, repeats, axis );
}

TEST_CASE("shape_repeat(dynamic_vector)" * doctest::test_suite("index::shape_repeat"))
{
    SHAPE_REPEAT_SUBCASE( case1, shape_d, repeats, axis );
    SHAPE_REPEAT_SUBCASE( case2, shape_d, repeats, axis );
    SHAPE_REPEAT_SUBCASE( case3, shape_d, repeats, axis );
    SHAPE_REPEAT_SUBCASE( case4, shape_d, repeats, axis );
    SHAPE_REPEAT_SUBCASE( case5, shape_d, repeats, axis );
}

TEST_CASE("shape_repeat(hybrid_vector)" * doctest::test_suite("index::shape_repeat"))
{
    SHAPE_REPEAT_SUBCASE( case1, shape_h, repeats, axis );
    SHAPE_REPEAT_SUBCASE( case2, shape_h, repeats, axis );
    SHAPE_REPEAT_SUBCASE( case3, shape_h, repeats, axis );
    SHAPE_REPEAT_SUBCASE( case4, shape_h, repeats, axis );
    SHAPE_REPEAT_SUBCASE( case5, shape_h, repeats, axis );
}

TEST_CASE("shape_repeat(tuple)" * doctest::test_suite("index::shape_repeat"))
{
    SHAPE_REPEAT_SUBCASE( case1, shape_t, repeats, axis );
    SHAPE_REPEAT_SUBCASE( case2, shape_t, repeats, axis );
    SHAPE_REPEAT_SUBCASE( case3, shape_t, repeats, axis );
    SHAPE_REPEAT_SUBCASE( case4, shape_t, repeats, axis );
    SHAPE_REPEAT_SUBCASE( case5, shape_t, repeats, axis );
}