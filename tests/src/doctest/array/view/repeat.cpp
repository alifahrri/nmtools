#include "nmtools/array/view/repeat.hpp"
#include "nmtools/array/ndarray/dynamic.hpp"
#include "nmtools/array/ndarray/hybrid.hpp"
#include "nmtools/array/ndarray/fixed.hpp"

#include "nmtools/constants.hpp"
#include "testing/doctest.hpp"

#include <vector>
#include <array>
#include <tuple>

namespace nm = nmtools;
namespace na = nm::array;
namespace view = nm::view;

NMTOOLS_TESTING_DECLARE_CASE(repeat_view)
{
    NMTOOLS_TESTING_DECLARE_ARGS(case1)
    {
        int array[2][2] = {{1,2},{3,4}};
        int repeats = 3;
        auto axis = None;
        auto array_a = cast<int>(array);
        auto array_v = cast<std::vector<std::vector<int>>>(array);
        auto array_d = cast<na::dynamic_ndarray<int>>(array);
        auto array_f = cast<na::fixed_ndarray<int,2,2>>(array);
        auto array_h = cast<na::hybrid_ndarray<int,4,2>>(array);
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case1)
    {
        int shape[1] = {12};
        int dim = 1;
        int result[12] = {1,1,1,2,2,2,3,3,3,4,4,4};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case2)
    {
        int array[2][2] = {{1,2},{3,4}};
        int repeats = 2;
        auto axis = 0;
        auto array_a = cast<int>(array);
        auto array_v = cast<std::vector<std::vector<int>>>(array);
        auto array_d = cast<na::dynamic_ndarray<int>>(array);
        auto array_f = cast<na::fixed_ndarray<int,2,2>>(array);
        auto array_h = cast<na::hybrid_ndarray<int,4,2>>(array);
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case2)
    {
        int shape[2] = {4,2};
        int dim = 2;
        int result[4][2] = {
            {1,2},
            {1,2},
            {3,4},
            {3,4}
        };
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case3)
    {
        int array[2][2] = {{1,2},{3,4}};
        int repeats = 2;
        auto axis = 1;
        auto array_a = cast<int>(array);
        auto array_v = cast<std::vector<std::vector<int>>>(array);
        auto array_d = cast<na::dynamic_ndarray<int>>(array);
        auto array_f = cast<na::fixed_ndarray<int,2,2>>(array);
        auto array_h = cast<na::hybrid_ndarray<int,4,2>>(array);
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case3)
    {
        int shape[2] = {2,4};
        int dim = 2;
        int result[2][4] = {
            {1,1,2,2},
            {3,3,4,4}
        };
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case4)
    {
        int array[2][2] = {{1,2},{3,4}};
        auto repeats = std::array{1,2};
        auto axis = 0;
        auto array_a = cast<int>(array);
        auto array_v = cast<std::vector<std::vector<int>>>(array);
        auto array_d = cast<na::dynamic_ndarray<int>>(array);
        auto array_f = cast<na::fixed_ndarray<int,2,2>>(array);
        auto array_h = cast<na::hybrid_ndarray<int,4,2>>(array);
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case4)
    {
        int shape[2] = {3,2};
        int dim = 2;
        int result[3][2] = {
            {1,2},
            {3,4},
            {3,4},
        };
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case5)
    {
        int array[2][2] = {{1,2},{3,4}};
        auto repeats = std::array{1,2};
        auto axis = 1;
        auto array_a = cast<int>(array);
        auto array_v = cast<std::vector<std::vector<int>>>(array);
        auto array_d = cast<na::dynamic_ndarray<int>>(array);
        auto array_f = cast<na::fixed_ndarray<int,2,2>>(array);
        auto array_h = cast<na::hybrid_ndarray<int,4,2>>(array);
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case5)
    {
        int shape[2] = {2,3};
        int dim = 2;
        int result[2][3] = {
            {1,2,2},
            {3,4,4}
        };
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case6)
    {
        int array[1][2][2] = {{{1,2},{3,4}}};
        auto repeats = 2;
        auto axis = 0;
        auto array_a = cast<int>(array);
        auto array_v = cast<std::vector<std::vector<std::vector<int>>>>(array);
        auto array_d = cast<na::dynamic_ndarray<int>>(array);
        auto array_f = cast<na::fixed_ndarray<int,1,2,2>>(array);
        auto array_h = cast<na::hybrid_ndarray<int,4,3>>(array);
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case6)
    {
        int shape[3] = {2,2,2};
        int dim = 3;
        int result[2][2][2] = {
            {
                {1,2},
                {3,4}
            },
            {
                {1,2},
                {3,4}
            },
        };
    }
}

#define REPEAT_SUBCASE(case_name, array, repeats, axis) \
SUBCASE(#case_name) \
{ \
    NMTOOLS_TESTING_DECLARE_NS(repeat_view, case_name); \
    auto array_view = view::repeat(args::array, args::repeats, args::axis); \
    NMTOOLS_ASSERT_EQUAL( array_view.shape(), expect::shape ); \
    NMTOOLS_ASSERT_EQUAL( array_view.dim(), expect::dim ); \
    NMTOOLS_ASSERT_CLOSE( array_view, expect::result ); \
}

TEST_CASE("repeat(array)" * doctest::test_suite("view::repeat"))
{
    REPEAT_SUBCASE(case1, array_a, repeats, axis);
    REPEAT_SUBCASE(case2, array_a, repeats, axis);
    REPEAT_SUBCASE(case3, array_a, repeats, axis);
    REPEAT_SUBCASE(case4, array_a, repeats, axis);
    REPEAT_SUBCASE(case5, array_a, repeats, axis);
    REPEAT_SUBCASE(case6, array_a, repeats, axis);
}

TEST_CASE("repeat(vector)" * doctest::test_suite("view::repeat"))
{
    REPEAT_SUBCASE(case1, array_v, repeats, axis);
    REPEAT_SUBCASE(case2, array_v, repeats, axis);
    REPEAT_SUBCASE(case3, array_v, repeats, axis);
    REPEAT_SUBCASE(case4, array_v, repeats, axis);
    REPEAT_SUBCASE(case5, array_v, repeats, axis);
    REPEAT_SUBCASE(case6, array_v, repeats, axis);
}

TEST_CASE("repeat(fixed_ndarray)" * doctest::test_suite("view::repeat"))
{
    REPEAT_SUBCASE(case1, array_f, repeats, axis);
    REPEAT_SUBCASE(case2, array_f, repeats, axis);
    REPEAT_SUBCASE(case3, array_f, repeats, axis);
    REPEAT_SUBCASE(case4, array_f, repeats, axis);
    REPEAT_SUBCASE(case5, array_f, repeats, axis);
    REPEAT_SUBCASE(case6, array_f, repeats, axis);
}

TEST_CASE("repeat(dynamic_ndarray)" * doctest::test_suite("view::repeat"))
{
    REPEAT_SUBCASE(case1, array_d, repeats, axis);
    REPEAT_SUBCASE(case2, array_d, repeats, axis);
    REPEAT_SUBCASE(case3, array_d, repeats, axis);
    REPEAT_SUBCASE(case4, array_d, repeats, axis);
    REPEAT_SUBCASE(case5, array_d, repeats, axis);
    REPEAT_SUBCASE(case6, array_d, repeats, axis);
}

TEST_CASE("repeat(hybrid_ndarray)" * doctest::test_suite("view::repeat"))
{
    REPEAT_SUBCASE(case1, array_h, repeats, axis);
    REPEAT_SUBCASE(case2, array_h, repeats, axis);
    REPEAT_SUBCASE(case3, array_h, repeats, axis);
    REPEAT_SUBCASE(case4, array_h, repeats, axis);
    REPEAT_SUBCASE(case5, array_h, repeats, axis);
    REPEAT_SUBCASE(case6, array_h, repeats, axis);
}