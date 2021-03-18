#include "nmtools/array/view/ufuncs/maximum.hpp"
#include "nmtools/array/ndarray/dynamic.hpp"
#include "nmtools/array/ndarray/hybrid.hpp"
#include "nmtools/array/ndarray/fixed.hpp"
#include "nmtools/testing/doctest.hpp"

#include <vector>
#include <array>
#include <algorithm> // std::max

namespace nm = nmtools;
namespace na = nm::array;
namespace view = nm::view;
namespace kind = na::kind;

#define CAST_ARRAYS(name) \
auto name##_a = cast(name, kind::nested_arr); \
auto name##_v = cast(name, kind::nested_vec); \
auto name##_f = cast(name, kind::fixed); \
auto name##_d = cast(name, kind::dynamic); \
auto name##_h = cast(name, kind::hybrid); \

NMTOOLS_TESTING_DECLARE_CASE(view, maximum)
{
    NMTOOLS_TESTING_DECLARE_ARGS(case1)
    {
        int a[3][3] = {
            {0,1,2},
            {3,4,5},
            {6,7,8},
        };
        int b[3] = {0,1,2};
        CAST_ARRAYS(a)
        CAST_ARRAYS(b)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case1)
    {
        int shape[2] = {3,3};
        int result[3][3] = {
            {std::max(0,0),std::max(1,1),std::max(2,2)},
            {std::max(3,0),std::max(4,1),std::max(5,2)},
            {std::max(6,0),std::max(7,1),std::max(8,2)},
        };
    }
}

#define RUN_maximum_impl(...) \
nm::view::maximum(__VA_ARGS__);

#ifdef NMTOOLS_TESTING_ENABLE_BENCHMARKS
#include "nmtools/benchmarks/bench.hpp"
using nm::benchmarks::TrackedBench;
// create immediately invoked lambda
// that packs maximum fn to callable lambda
#define RUN_maximum(case_name, ...) \
[](auto&&...args){ \
    auto title = std::string("maximum-") + #case_name; \
    auto name  = nm::testing::make_func_args("", args...); \
    auto fn    = [&](){ \
        return RUN_maximum_impl(args...); \
    }; \
    return TrackedBench::run(title, name, fn); \
}(__VA_ARGS__);
#else
// run normally without benchmarking, ignore case_name
#define RUN_maximum(case_name, ...) \
RUN_maximum_impl(__VA_ARGS__);
#endif // NMTOOLS_TESTING_ENABLE_BENCHMARKS

#define MAXIMUM_SUBCASE(case_name, ...) \
SUBCASE(#case_name) \
{ \
    NMTOOLS_TESTING_DECLARE_NS(view, maximum, case_name); \
    using namespace args; \
    auto result = RUN_maximum(case_name, __VA_ARGS__); \
    NMTOOLS_ASSERT_EQUAL( result.shape(), expect::shape ); \
    NMTOOLS_ASSERT_CLOSE( result, expect::result ); \
}

TEST_CASE("maximum(case1)" * doctest::test_suite("view::maximum"))
{
    MAXIMUM_SUBCASE( case1,   a,   b );
    MAXIMUM_SUBCASE( case1, a_a, b_a );
    MAXIMUM_SUBCASE( case1, a_v, b_v );
    MAXIMUM_SUBCASE( case1, a_f, b_f );
    MAXIMUM_SUBCASE( case1, a_d, b_d );
    MAXIMUM_SUBCASE( case1, a_h, b_h );
}

NMTOOLS_TESTING_DECLARE_CASE(view, reduce_maximum)
{
    NMTOOLS_TESTING_DECLARE_ARGS(case1)
    {
        int a[2][3][2] = {
            {
                {0,1},
                {2,3},
                {4,5},
            },
            {
                { 6, 7},
                { 8, 9},
                {10,11},
            },
        };
        int axis = 0;
        CAST_ARRAYS(a)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case1)
    {
        int shape[2] = {3,2};
        int result[3][2] = {
            { 6, 7},
            { 8, 9},
            {10,11},
        };
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case2)
    {
        int a[2][3][2] = {
            {
                {0,1},
                {2,3},
                {4,5},
            },
            {
                { 6, 7},
                { 8, 9},
                {10,11},
            },
        };
        int axis = 1;
        CAST_ARRAYS(a)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case2)
    {
        int shape[2] = {2,2};
        int result[2][2] = {
            { 4, 5},
            {10,11},
        };
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case3)
    {
        int a[2][3][2] = {
            {
                {0,1},
                {2,3},
                {4,5},
            },
            {
                { 6, 7},
                { 8, 9},
                {10,11},
            },
        };
        int axis = 2;
        CAST_ARRAYS(a)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case3)
    {
        int shape[2] = {2,3};
        int result[2][3] = {
            {1,3, 5},
            {7,9,11},
        };
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case4)
    {
        int a[2][3][2] = {
            {
                {0,1},
                {2,3},
                {4,5},
            },
            {
                { 6, 7},
                { 8, 9},
                {10,11},
            },
        };
        int axis[2] = {0,1};
        CAST_ARRAYS(a)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case4)
    {
        int shape[1] = {2};
        int result[2] = {10,11};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case5)
    {
        int a[2][3][2] = {
            {
                {0,1},
                {2,3},
                {4,5},
            },
            {
                { 6, 7},
                { 8, 9},
                {10,11},
            },
        };
        int axis[2] = {0,2};
        CAST_ARRAYS(a)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case5)
    {
        int shape[1] = {3};
        int result[3] = {7,9,11};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case6)
    {
        int a[2][3][2] = {
            {
                {0,1},
                {2,3},
                {4,5},
            },
            {
                { 6, 7},
                { 8, 9},
                {10,11},
            },
        };
        int axis[2] = {1,2};
        CAST_ARRAYS(a)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case6)
    {
        int shape[1] = {2};
        int result[2] = {5,11};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case7)
    {
        uint8_t a[2][3][2] = {
            {
                {0,1},
                {2,3},
                {4,5},
            },
            {
                { 6, 7},
                { 8, 9},
                {10,11},
            },
        };
        int axis[2]  = {1,2};
        auto dtype   = int32;
        auto initial = 256;
        CAST_ARRAYS(a)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case7)
    {
        int shape[1] = {2};
        int result[2] = {256,256};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case8)
    {
        int a[2][3][2] = {
            {
                {0,1},
                {2,3},
                {4,5},
            },
            {
                { 6, 7},
                { 8, 9},
                {10,11},
            },
        };
        int axis = 0;
        auto dtype = None;
        auto initial = None;
        auto keepdims = True;
        CAST_ARRAYS(a)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case8)
    {
        int shape[3] = {1,3,2};
        int result[1][3][2] = {
            {
                { 6, 7},
                { 8, 9},
                {10,11},
            }
        };
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case9)
    {
        int a[2][3][2] = {
            {
                {0,1},
                {2,3},
                {4,5},
            },
            {
                { 6, 7},
                { 8, 9},
                {10,11},
            },
        };
        int axis = 1;
        auto dtype = None;
        auto initial = None;
        auto keepdims = False;
        CAST_ARRAYS(a)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case9)
    {
        int shape[2] = {2,2};
        int result[2][2] = {
            { 4, 5},
            {10,11},
        };
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case10)
    {
        int a[2][3][2] = {
            {
                {0,1},
                {2,3},
                {4,5},
            },
            {
                { 6, 7},
                { 8, 9},
                {10,11},
            },
        };
        int axis = 2;
        auto dtype = None;
        auto initial = None;
        auto keepdims = true;
        CAST_ARRAYS(a)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case10)
    {
        int shape[3] = {2,3,1};
        int result[2][3][1] = {
            {{1},{3},{ 5}},
            {{7},{9},{11}},
        };
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case11)
    {
        int a[2][3][2] = {
            {
                {0,1},
                {2,3},
                {4,5},
            },
            {
                { 6, 7},
                { 8, 9},
                {10,11},
            },
        };
        int axis[2] = {0,1};
        auto dtype = None;
        auto initial = None;
        auto keepdims = false;
        CAST_ARRAYS(a)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case11)
    {
        int shape[1] = {2};
        int result[2] = {10,11};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case12)
    {
        int a[2][3][2] = {
            {
                {0,1},
                {2,3},
                {4,5},
            },
            {
                { 6, 7},
                { 8, 9},
                {10,11},
            },
        };
        int axis[2] = {0,2};
        auto dtype = None;
        auto initial = None;
        auto keepdims = true;
        CAST_ARRAYS(a)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case12)
    {
        int shape[3] = {1,3,1};
        int result[1][3][1] = {
            {
                {7},
                {9},
                {11}
            }
        };
    }

}

#define RUN_reduce_maximum_impl(...) \
nm::view::reduce_maximum(__VA_ARGS__);

#ifdef NMTOOLS_TESTING_ENABLE_BENCHMARKS
#include "nmtools/benchmarks/bench.hpp"
using nm::benchmarks::TrackedBench;
// create immediately invoked lambda
// that packs reduce_maximum fn to callable lambda
#define RUN_reduce_maximum(case_name, ...) \
[](auto&&...args){ \
    auto title = std::string("reduce_maximum-") + #case_name; \
    auto name  = nm::testing::make_func_args("", args...); \
    auto fn    = [&](){ \
        return RUN_reduce_maximum_impl(args...); \
    }; \
    return TrackedBench::run(title, name, fn); \
}(__VA_ARGS__);
#else
// run normally without benchmarking, ignore case_name
#define RUN_reduce_maximum(case_name, ...) \
RUN_reduce_maximum_impl(__VA_ARGS__);
#endif // NMTOOLS_TESTING_ENABLE_BENCHMARKS

#define REDUCE_MAXIMUM_SUBCASE(case_name, ...) \
SUBCASE(#case_name) \
{ \
    NMTOOLS_TESTING_DECLARE_NS(view, reduce_maximum, case_name); \
    using namespace args; \
    auto result = RUN_reduce_maximum(case_name, __VA_ARGS__); \
    NMTOOLS_ASSERT_EQUAL( result.shape(), expect::shape ); \
    NMTOOLS_ASSERT_CLOSE( result, expect::result ); \
}

TEST_CASE("reduce_maximum(case1)" * doctest::test_suite("view::reduce_maximum"))
{
    REDUCE_MAXIMUM_SUBCASE( case1,   a, axis );
    REDUCE_MAXIMUM_SUBCASE( case1, a_a, axis );
    REDUCE_MAXIMUM_SUBCASE( case1, a_v, axis );
    REDUCE_MAXIMUM_SUBCASE( case1, a_f, axis );
    // dynamic dim array not supported yet
    // REDUCE_MAXIMUM_SUBCASE( case1, a_d, axis );
    REDUCE_MAXIMUM_SUBCASE( case1, a_h, axis );
}

TEST_CASE("reduce_maximum(case2)" * doctest::test_suite("view::reduce_maximum"))
{
    REDUCE_MAXIMUM_SUBCASE( case2,   a, axis );
    REDUCE_MAXIMUM_SUBCASE( case2, a_a, axis );
    REDUCE_MAXIMUM_SUBCASE( case2, a_v, axis );
    REDUCE_MAXIMUM_SUBCASE( case2, a_f, axis );
    // dynamic dim array not supported yet
    // REDUCE_MAXIMUM_SUBCASE( case2, a_d, axis );
    REDUCE_MAXIMUM_SUBCASE( case2, a_h, axis );
}

TEST_CASE("reduce_maximum(case3)" * doctest::test_suite("view::reduce_maximum"))
{
    REDUCE_MAXIMUM_SUBCASE( case3,   a, axis );
    REDUCE_MAXIMUM_SUBCASE( case3, a_a, axis );
    REDUCE_MAXIMUM_SUBCASE( case3, a_v, axis );
    REDUCE_MAXIMUM_SUBCASE( case3, a_f, axis );
    // dynamic dim array not supported yet
    // REDUCE_MAXIMUM_SUBCASE( case3, a_d, axis );
    REDUCE_MAXIMUM_SUBCASE( case3, a_h, axis );
}

TEST_CASE("reduce_maximum(case4)" * doctest::test_suite("view::reduce_maximum"))
{
    REDUCE_MAXIMUM_SUBCASE( case4,   a, axis );
    REDUCE_MAXIMUM_SUBCASE( case4, a_a, axis );
    REDUCE_MAXIMUM_SUBCASE( case4, a_v, axis );
    REDUCE_MAXIMUM_SUBCASE( case4, a_f, axis );
    // dynamic dim array not supported yet
    // REDUCE_MAXIMUM_SUBCASE( case4, a_d, axis );
    REDUCE_MAXIMUM_SUBCASE( case4, a_h, axis );
}

TEST_CASE("reduce_maximum(case5)" * doctest::test_suite("view::reduce_maximum"))
{
    REDUCE_MAXIMUM_SUBCASE( case5,   a, axis );
    REDUCE_MAXIMUM_SUBCASE( case5, a_a, axis );
    REDUCE_MAXIMUM_SUBCASE( case5, a_v, axis );
    REDUCE_MAXIMUM_SUBCASE( case5, a_f, axis );
    // dynamic dim array not supported yet
    // REDUCE_MAXIMUM_SUBCASE( case5, a_d, axis );
    REDUCE_MAXIMUM_SUBCASE( case5, a_h, axis );
}

TEST_CASE("reduce_maximum(case6)" * doctest::test_suite("view::reduce_maximum"))
{
    REDUCE_MAXIMUM_SUBCASE( case6,   a, axis );
    REDUCE_MAXIMUM_SUBCASE( case6, a_a, axis );
    REDUCE_MAXIMUM_SUBCASE( case6, a_v, axis );
    REDUCE_MAXIMUM_SUBCASE( case6, a_f, axis );
    // dynamic dim array not supported yet
    // REDUCE_MAXIMUM_SUBCASE( case6, a_d, axis );
    REDUCE_MAXIMUM_SUBCASE( case6, a_h, axis );
}

TEST_CASE("reduce_maximum(case7)" * doctest::test_suite("view::reduce_maximum"))
{
    REDUCE_MAXIMUM_SUBCASE( case7,   a, axis, dtype, initial );
    REDUCE_MAXIMUM_SUBCASE( case7, a_a, axis, dtype, initial );
    REDUCE_MAXIMUM_SUBCASE( case7, a_v, axis, dtype, initial );
    REDUCE_MAXIMUM_SUBCASE( case7, a_f, axis, dtype, initial );
    REDUCE_MAXIMUM_SUBCASE( case7, a_h, axis, dtype, initial );
}

TEST_CASE("reduce_maximum(case8)" * doctest::test_suite("view::reduce_maximum"))
{
    REDUCE_MAXIMUM_SUBCASE( case8,   a, axis, dtype, initial, keepdims );
    REDUCE_MAXIMUM_SUBCASE( case8, a_a, axis, dtype, initial, keepdims );
    REDUCE_MAXIMUM_SUBCASE( case8, a_v, axis, dtype, initial, keepdims );
    REDUCE_MAXIMUM_SUBCASE( case8, a_f, axis, dtype, initial, keepdims );
    REDUCE_MAXIMUM_SUBCASE( case8, a_h, axis, dtype, initial, keepdims );
}

TEST_CASE("reduce_maximum(case9)" * doctest::test_suite("view::reduce_maximum"))
{
    REDUCE_MAXIMUM_SUBCASE( case9,   a, axis, dtype, initial, keepdims );
    REDUCE_MAXIMUM_SUBCASE( case9, a_a, axis, dtype, initial, keepdims );
    REDUCE_MAXIMUM_SUBCASE( case9, a_v, axis, dtype, initial, keepdims );
    REDUCE_MAXIMUM_SUBCASE( case9, a_f, axis, dtype, initial, keepdims );
    REDUCE_MAXIMUM_SUBCASE( case9, a_h, axis, dtype, initial, keepdims );
}

TEST_CASE("reduce_maximum(case10)" * doctest::test_suite("view::reduce_maximum"))
{
    REDUCE_MAXIMUM_SUBCASE( case10,   a, axis, dtype, initial, keepdims );
    REDUCE_MAXIMUM_SUBCASE( case10, a_a, axis, dtype, initial, keepdims );
    REDUCE_MAXIMUM_SUBCASE( case10, a_v, axis, dtype, initial, keepdims );
    REDUCE_MAXIMUM_SUBCASE( case10, a_f, axis, dtype, initial, keepdims );
    REDUCE_MAXIMUM_SUBCASE( case10, a_h, axis, dtype, initial, keepdims );
}

TEST_CASE("reduce_maximum(case11)" * doctest::test_suite("view::reduce_maximum"))
{
    REDUCE_MAXIMUM_SUBCASE( case11,   a, axis, dtype, initial, keepdims );
    REDUCE_MAXIMUM_SUBCASE( case11, a_a, axis, dtype, initial, keepdims );
    REDUCE_MAXIMUM_SUBCASE( case11, a_v, axis, dtype, initial, keepdims );
    REDUCE_MAXIMUM_SUBCASE( case11, a_f, axis, dtype, initial, keepdims );
    REDUCE_MAXIMUM_SUBCASE( case11, a_h, axis, dtype, initial, keepdims );
}

TEST_CASE("reduce_maximum(case12)" * doctest::test_suite("view::reduce_maximum"))
{
    REDUCE_MAXIMUM_SUBCASE( case12,   a, axis, dtype, initial, keepdims );
    REDUCE_MAXIMUM_SUBCASE( case12, a_a, axis, dtype, initial, keepdims );
    REDUCE_MAXIMUM_SUBCASE( case12, a_v, axis, dtype, initial, keepdims );
    REDUCE_MAXIMUM_SUBCASE( case12, a_f, axis, dtype, initial, keepdims );
    REDUCE_MAXIMUM_SUBCASE( case12, a_h, axis, dtype, initial, keepdims );
}

NMTOOLS_TESTING_DECLARE_CASE(view, accumulate_maximum)
{
    NMTOOLS_TESTING_DECLARE_ARGS(case1)
    {
        float a[2][3][2] = {
            {
                {0,1},
                {2,3},
                {4,5},
            },
            {
                { 6, 7},
                { 8, 9},
                {10,11},
            },
        };
        int axis = 0;
        CAST_ARRAYS(a)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case1)
    {
        int shape[3] = {2,3,2};
        float result[2][3][2] = {
            {
                {0,1},
                {2,3},
                {4,5},
            },
            {
                { 6, 7},
                { 8, 9},
                {10,11},
            },
        };
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case2)
    {
        float a[2][3][2] = {
            {
                {0,1},
                {2,3},
                {4,5},
            },
            {
                { 6, 7},
                { 8, 9},
                {10,11},
            },
        };
        int axis = 1;
        CAST_ARRAYS(a)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case2)
    {
        int shape[3] = {2,3,2};
        float result[2][3][2] = {
            {
                {0,1},
                {2,3},
                {4,5},
            },
            {
                { 6, 7},
                { 8, 9},
                {10,11},
            },
        };
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case3)
    {
        float a[2][3][2] = {
            {
                {0,1},
                {2,3},
                {4,5},
            },
            {
                { 6, 7},
                { 8, 9},
                {10,11},
            },
        };
        int axis = 2;
        CAST_ARRAYS(a)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case3)
    {
        int shape[3] = {2,3,2};
        float result[2][3][2] = {
            {
                {0,1},
                {2,3},
                {4,5},
            },
            {
                { 6, 7},
                { 8, 9},
                {10,11},
            },
        };
    }
}

#define RUN_accumulate_maximum_impl(...) \
nm::view::accumulate_maximum(__VA_ARGS__);

#ifdef NMTOOLS_TESTING_ENABLE_BENCHMARKS
#include "nmtools/benchmarks/bench.hpp"
using nm::benchmarks::TrackedBench;
// create immediately invoked lambda
// that packs accumulate_maximum fn to callable lambda
#define RUN_accumulate_maximum(case_name, ...) \
[](auto&&...args){ \
    auto title = std::string("accumulate_maximum-") + #case_name; \
    auto name  = nm::testing::make_func_args("", args...); \
    auto fn    = [&](){ \
        return RUN_accumulate_maximum_impl(args...); \
    }; \
    return TrackedBench::run(title, name, fn); \
}(__VA_ARGS__);
#else
// run normally without benchmarking, ignore case_name
#define RUN_accumulate_maximum(case_name, ...) \
RUN_accumulate_maximum_impl(__VA_ARGS__);
#endif // NMTOOLS_TESTING_ENABLE_BENCHMARKS

#define ACCUMULATE_MAXIMUM_SUBCASE(case_name, ...) \
SUBCASE(#case_name) \
{ \
    NMTOOLS_TESTING_DECLARE_NS(view, accumulate_maximum, case_name); \
    using namespace args; \
    auto result = RUN_accumulate_maximum(case_name, __VA_ARGS__); \
    NMTOOLS_ASSERT_EQUAL( result.shape(), expect::shape ); \
    NMTOOLS_ASSERT_CLOSE( result, expect::result ); \
}

TEST_CASE("accumulate_maximum(case1)" * doctest::test_suite("view::accumulate_maximum"))
{
    ACCUMULATE_MAXIMUM_SUBCASE( case1,   a, axis );
    ACCUMULATE_MAXIMUM_SUBCASE( case1, a_a, axis );
    ACCUMULATE_MAXIMUM_SUBCASE( case1, a_v, axis );
    ACCUMULATE_MAXIMUM_SUBCASE( case1, a_f, axis );
    // dynamic dim array not supported yet
    // ACCUMULATE_MAXIMUM_SUBCASE( case1, a_d, axis );
    ACCUMULATE_MAXIMUM_SUBCASE( case1, a_f, axis );
}

TEST_CASE("accumulate_maximum(case2)" * doctest::test_suite("view::accumulate_maximum"))
{
    ACCUMULATE_MAXIMUM_SUBCASE( case2,   a, axis );
    ACCUMULATE_MAXIMUM_SUBCASE( case2, a_a, axis );
    ACCUMULATE_MAXIMUM_SUBCASE( case2, a_v, axis );
    ACCUMULATE_MAXIMUM_SUBCASE( case2, a_f, axis );
    // dynamic dim array not supported yet
    // ACCUMULATE_MAXIMUM_SUBCASE( case2, a_d, axis );
    ACCUMULATE_MAXIMUM_SUBCASE( case2, a_f, axis );
}

TEST_CASE("accumulate_maximum(case3)" * doctest::test_suite("view::accumulate_maximum"))
{
    ACCUMULATE_MAXIMUM_SUBCASE( case3,   a, axis );
    ACCUMULATE_MAXIMUM_SUBCASE( case3, a_a, axis );
    ACCUMULATE_MAXIMUM_SUBCASE( case3, a_v, axis );
    ACCUMULATE_MAXIMUM_SUBCASE( case3, a_f, axis );
    // dynamic dim array not supported yet
    // ACCUMULATE_MAXIMUM_SUBCASE( case3, a_d, axis );
    ACCUMULATE_MAXIMUM_SUBCASE( case3, a_f, axis );
}