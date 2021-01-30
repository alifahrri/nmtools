#include "nmtools/array/index/repeat.hpp"
#include "nmtools/array/index/as_tuple.hpp"
#include "nmtools/meta.hpp"

#include "testing/doctest.hpp"

#include <vector>
#include <array>
#include <tuple>

namespace nm = nmtools;

NMTOOLS_TESTING_DECLARE_CASE(repeat)
{
    NMTOOLS_TESTING_DECLARE_ARGS(case1)
    {
        int shape[2] = {2,2};
        int indices  = 7;
        int repeats  = 2;
        auto axis = None;
        auto shape_a = cast<int>(shape);
        auto shape_v = cast<std::vector<int>>(shape);
        auto shape_t = index::as_tuple(shape_a);
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case1)
    {
        int result[2] = {1,1};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case2)
    {
        int shape[2] = {2,2};
        int indices  = 6;
        int repeats  = 2;
        auto axis = None;
        auto shape_a = cast<int>(shape);
        auto shape_v = cast<std::vector<int>>(shape);
        auto shape_t = index::as_tuple(shape_a);
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case2)
    {
        int result[2] = {1,1};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case3)
    {
        int shape[2] = {2,2};
        int indices  = 5;
        int repeats  = 2;
        auto axis = None;
        auto shape_a = cast<int>(shape);
        auto shape_v = cast<std::vector<int>>(shape);
        auto shape_t = index::as_tuple(shape_a);
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case3)
    {
        int result[2] = {1,0};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case4)
    {
        int shape[2]   = {2,2};
        int indices[2] = {5,0};
        int repeats  = 3;
        auto axis    = 0;
        auto shape_a = cast<int>(shape);
        auto shape_v = cast<std::vector<int>>(shape);
        auto shape_t = index::as_tuple(shape_a);
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case4)
    {
        int result[2] = {1,0};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case5)
    {
        int shape[2]   = {2,2};
        int indices[2] = {5,1};
        int repeats  = 3;
        auto axis    = 0;
        auto shape_a = cast<int>(shape);
        auto shape_v = cast<std::vector<int>>(shape);
        auto shape_t = index::as_tuple(shape_a);
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case5)
    {
        int result[2] = {1,1};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case6)
    {
        int shape[2]   = {2,2};
        int indices[2] = {2,0};
        int repeats[2] = {1,2};
        auto axis    = 0;
        auto shape_a = cast<int>(shape);
        auto shape_v = cast<std::vector<int>>(shape);
        auto shape_t = index::as_tuple(shape_a);
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case6)
    {
        int result[2] = {1,0};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case7)
    {
        int shape[2]   = {2,2};
        int indices[2] = {1,0};
        int repeats[2] = {1,2};
        auto axis    = 0;
        auto shape_a = cast<int>(shape);
        auto shape_v = cast<std::vector<int>>(shape);
        auto shape_t = index::as_tuple(shape_a);
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case7)
    {
        int result[2] = {1,0};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case8)
    {
        int shape[2]   = {2,2};
        int indices[2] = {0,0};
        int repeats[2] = {1,2};
        auto axis    = 0;
        auto shape_a = cast<int>(shape);
        auto shape_v = cast<std::vector<int>>(shape);
        auto shape_t = index::as_tuple(shape_a);
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case8)
    {
        int result[2] = {0,0};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case9)
    {
        int shape[2]   = {2,2};
        int indices[2] = {0,0};
        int repeats[2] = {1,2};
        auto axis    = 1;
        auto shape_a = cast<int>(shape);
        auto shape_v = cast<std::vector<int>>(shape);
        auto shape_t = index::as_tuple(shape_a);
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case9)
    {
        int result[2] = {0,0};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case10)
    {
        int shape[2]   = {2,2};
        int indices[2] = {0,1};
        int repeats[2] = {1,2};
        auto axis    = 1;
        auto shape_a = cast<int>(shape);
        auto shape_v = cast<std::vector<int>>(shape);
        auto shape_t = index::as_tuple(shape_a);
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case10)
    {
        int result[2] = {0,1};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case11)
    {
        int shape[2]   = {2,2};
        int indices[2] = {1,2};
        int repeats[2] = {1,2};
        auto axis    = 1;
        auto shape_a = cast<int>(shape);
        auto shape_v = cast<std::vector<int>>(shape);
        auto shape_t = index::as_tuple(shape_a);
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case11)
    {
        int result[2] = {1,1};
    }
}

#define REPEAT_SUBCASE(case_name, shape, indices, repeats, axis) \
SUBCASE(#case_name) \
{ \
    NMTOOLS_TESTING_DECLARE_NS(repeat, case_name); \
    auto result = nm::index::repeat(args::shape, args::indices, args::repeats, args::axis); \
    NMTOOLS_ASSERT_EQUAL( result, expect::result ); \
}

TEST_CASE("repeat(vector)" * doctest::test_suite("index::repeat"))
{
    REPEAT_SUBCASE(case1, shape_v, indices, repeats, axis);
    REPEAT_SUBCASE(case2, shape_v, indices, repeats, axis);
    REPEAT_SUBCASE(case3, shape_v, indices, repeats, axis);
    REPEAT_SUBCASE(case4, shape_v, indices, repeats, axis);
    REPEAT_SUBCASE(case5, shape_v, indices, repeats, axis);
    REPEAT_SUBCASE(case6, shape_v, indices, repeats, axis);
    REPEAT_SUBCASE(case7, shape_v, indices, repeats, axis);
    REPEAT_SUBCASE(case8, shape_v, indices, repeats, axis);
    REPEAT_SUBCASE(case9, shape_v, indices, repeats, axis);
    REPEAT_SUBCASE(case10, shape_v, indices, repeats, axis);
    REPEAT_SUBCASE(case11, shape_v, indices, repeats, axis);
}

TEST_CASE("repeat(array)" * doctest::test_suite("index::repeat"))
{
    REPEAT_SUBCASE(case1, shape_a, indices, repeats, axis);
    REPEAT_SUBCASE(case2, shape_a, indices, repeats, axis);
    REPEAT_SUBCASE(case3, shape_a, indices, repeats, axis);
    REPEAT_SUBCASE(case4, shape_a, indices, repeats, axis);
    REPEAT_SUBCASE(case5, shape_a, indices, repeats, axis);
    REPEAT_SUBCASE(case6, shape_a, indices, repeats, axis);
    REPEAT_SUBCASE(case7, shape_a, indices, repeats, axis);
    REPEAT_SUBCASE(case8, shape_a, indices, repeats, axis);
    REPEAT_SUBCASE(case9, shape_a, indices, repeats, axis);
    REPEAT_SUBCASE(case10, shape_a, indices, repeats, axis);
    REPEAT_SUBCASE(case11, shape_a, indices, repeats, axis);
}