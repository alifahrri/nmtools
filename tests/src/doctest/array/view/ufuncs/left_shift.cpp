#include "nmtools/array/view/ufuncs/left_shift.hpp"
#include "nmtools/array/ndarray/dynamic.hpp"
#include "nmtools/array/ndarray/hybrid.hpp"
#include "nmtools/array/ndarray/fixed.hpp"
#include "nmtools/testing/doctest.hpp"

#include <vector>
#include <array>

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

NMTOOLS_TESTING_DECLARE_CASE(view, left_shift)
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
            {0 << 0, 1 << 1, 2 << 2},
            {3 << 0, 4 << 1, 5 << 2},
            {6 << 0, 7 << 1, 8 << 2},
        };
    }
}

#define RUN_left_shift_impl(...) \
nm::view::left_shift(__VA_ARGS__);

#ifdef NMTOOLS_TESTING_ENABLE_BENCHMARKS
#include "nmtools/benchmarks/bench.hpp"
using nm::benchmarks::TrackedBench;
// create immediately invoked lambda
// that packs left_shift fn to callable lambda
#define RUN_left_shift(case_name, ...) \
[](auto&&...args){ \
    auto title = std::string("left_shift-") + #case_name; \
    auto name  = nm::testing::make_func_args("", args...); \
    auto fn    = [&](){ \
        return RUN_left_shift_impl(args...); \
    }; \
    return TrackedBench::run(title, name, fn); \
}(__VA_ARGS__);
#else
// run normally without benchmarking, ignore case_name
#define RUN_left_shift(case_name, ...) \
RUN_left_shift_impl(__VA_ARGS__);
#endif // NMTOOLS_TESTING_ENABLE_BENCHMARKS

#define LEFT_SHIFT_SUBCASE(case_name, ...) \
SUBCASE(#case_name) \
{ \
    NMTOOLS_TESTING_DECLARE_NS(view, left_shift, case_name); \
    using namespace args; \
    auto result = RUN_left_shift(case_name, __VA_ARGS__); \
    NMTOOLS_ASSERT_EQUAL( result.shape(), expect::shape ); \
    NMTOOLS_ASSERT_CLOSE( result, expect::result ); \
}

TEST_CASE("left_shift(case1)" * doctest::test_suite("view::left_shift"))
{
    LEFT_SHIFT_SUBCASE( case1,   a,   b );
    LEFT_SHIFT_SUBCASE( case1, a_a, b_a );
    LEFT_SHIFT_SUBCASE( case1, a_v, b_v );
    LEFT_SHIFT_SUBCASE( case1, a_f, b_f );
    LEFT_SHIFT_SUBCASE( case1, a_d, b_d );
    LEFT_SHIFT_SUBCASE( case1, a_h, b_h );
}

NMTOOLS_TESTING_DECLARE_CASE(view, reduce_left_shift)
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
            {   0,  128},
            { 512, 1536},
            {4096,10240},
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
            {      0,    256},
            {1572864,7340032},
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
            {  0,  16,  128},
            {768,4096,20480},
        };
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case4)
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
        int axis = 2;
        auto dtype = uint32;
        CAST_ARRAYS(a)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case4)
    {
        int shape[2] = {2,3};
        int result[2][3] = {
            {  0,  16,  128},
            {768,4096,20480},
        };
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case5)
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
        int axis = 2;
        auto dtype = uint32;
        auto initial = 2;
        CAST_ARRAYS(a)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case5)
    {
        int shape[2] = {2,3};
        int result[2][3] = {
            {    4,    64,   1024},
            {16384,262144,4194304},
        };
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
        int axis = 0;
        auto dtype = None;
        auto initial = None;
        auto keepdims = True;
        CAST_ARRAYS(a)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case6)
    {
        int shape[3] = {1,3,2};
        int result[1][3][2] = {
            {
                {   0,  128},
                { 512, 1536},
                {4096,10240},
            }
        };
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case7)
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
    NMTOOLS_TESTING_DECLARE_EXPECT(case7)
    {
        int shape[2] = {2,2};
        int result[2][2] = {
            {      0,    256},
            {1572864,7340032},
        };
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
        int axis = 2;
        auto dtype = None;
        auto initial = None;
        auto keepdims = true;
        CAST_ARRAYS(a)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case8)
    {
        int shape[3] = {2,3,1};
        int result[2][3][1] = {
            {{  0},{  16},{  128}},
            {{768},{4096},{20480}},
        };
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case9)
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
        int axis = 2;
        auto dtype = uint32;
        auto initial = None;
        auto keepdims = false;
        CAST_ARRAYS(a)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case9)
    {
        int shape[2] = {2,3};
        int result[2][3] = {
            {  0,  16,  128},
            {768,4096,20480},
        };
    }
}

#define RUN_reduce_left_shift_impl(...) \
nm::view::reduce_left_shift(__VA_ARGS__);

#ifdef NMTOOLS_TESTING_ENABLE_BENCHMARKS
#include "nmtools/benchmarks/bench.hpp"
using nm::benchmarks::TrackedBench;
// create immediately invoked lambda
// that packs reduce_left_shift fn to callable lambda
#define RUN_reduce_left_shift(case_name, ...) \
[](auto&&...args){ \
    auto title = std::string("reduce_left_shift-") + #case_name; \
    auto name  = nm::testing::make_func_args("", args...); \
    auto fn    = [&](){ \
        return RUN_reduce_left_shift_impl(args...); \
    }; \
    return TrackedBench::run(title, name, fn); \
}(__VA_ARGS__);
#else
// run normally without benchmarking, ignore case_name
#define RUN_reduce_left_shift(case_name, ...) \
RUN_reduce_left_shift_impl(__VA_ARGS__);
#endif // NMTOOLS_TESTING_ENABLE_BENCHMARKS

#define REDUCE_LEFT_SHIFT_SUBCASE(case_name, ...) \
SUBCASE(#case_name) \
{ \
    NMTOOLS_TESTING_DECLARE_NS(view, reduce_left_shift, case_name); \
    using namespace args; \
    auto result = RUN_reduce_left_shift(case_name, __VA_ARGS__); \
    NMTOOLS_ASSERT_EQUAL( result.shape(), expect::shape ); \
    NMTOOLS_ASSERT_CLOSE( result, expect::result ); \
}

TEST_CASE("reduce_left_shift(case1)" * doctest::test_suite("view::reduce_left_shift"))
{
    REDUCE_LEFT_SHIFT_SUBCASE( case1,   a, axis );
    REDUCE_LEFT_SHIFT_SUBCASE( case1, a_a, axis );
    REDUCE_LEFT_SHIFT_SUBCASE( case1, a_v, axis );
    REDUCE_LEFT_SHIFT_SUBCASE( case1, a_f, axis );
    REDUCE_LEFT_SHIFT_SUBCASE( case1, a_h, axis );
    // dynamic dim array not supported yet
    // REDUCE_LEFT_SHIFT_SUBCASE( case1, a_d, axis );
}

TEST_CASE("reduce_left_shift(case2)" * doctest::test_suite("view::reduce_left_shift"))
{
    REDUCE_LEFT_SHIFT_SUBCASE( case2,   a, axis );
    REDUCE_LEFT_SHIFT_SUBCASE( case2, a_a, axis );
    REDUCE_LEFT_SHIFT_SUBCASE( case2, a_v, axis );
    REDUCE_LEFT_SHIFT_SUBCASE( case2, a_f, axis );
    REDUCE_LEFT_SHIFT_SUBCASE( case2, a_h, axis );
    // dynamic dim array not supported yet
    // REDUCE_LEFT_SHIFT_SUBCASE( case2, a_d, axis );
}

TEST_CASE("reduce_left_shift(case3)" * doctest::test_suite("view::reduce_left_shift"))
{
    REDUCE_LEFT_SHIFT_SUBCASE( case3,   a, axis );
    REDUCE_LEFT_SHIFT_SUBCASE( case3, a_a, axis );
    REDUCE_LEFT_SHIFT_SUBCASE( case3, a_v, axis );
    REDUCE_LEFT_SHIFT_SUBCASE( case3, a_f, axis );
    REDUCE_LEFT_SHIFT_SUBCASE( case3, a_h, axis );
    // dynamic dim array not supported yet
    // REDUCE_LEFT_SHIFT_SUBCASE( case3, a_d, axis );
}

TEST_CASE("reduce_left_shift(case4)" * doctest::test_suite("view::reduce_left_shift"))
{
    REDUCE_LEFT_SHIFT_SUBCASE( case4,   a, axis, dtype );
    REDUCE_LEFT_SHIFT_SUBCASE( case4, a_a, axis, dtype );
    REDUCE_LEFT_SHIFT_SUBCASE( case4, a_v, axis, dtype );
    REDUCE_LEFT_SHIFT_SUBCASE( case4, a_f, axis, dtype );
    REDUCE_LEFT_SHIFT_SUBCASE( case4, a_h, axis, dtype );
}

TEST_CASE("reduce_left_shift(case5)" * doctest::test_suite("view::reduce_left_shift"))
{
    REDUCE_LEFT_SHIFT_SUBCASE( case5,   a, axis, dtype, initial );
    REDUCE_LEFT_SHIFT_SUBCASE( case5, a_a, axis, dtype, initial );
    REDUCE_LEFT_SHIFT_SUBCASE( case5, a_v, axis, dtype, initial );
    REDUCE_LEFT_SHIFT_SUBCASE( case5, a_f, axis, dtype, initial );
    REDUCE_LEFT_SHIFT_SUBCASE( case5, a_h, axis, dtype, initial );
}

TEST_CASE("reduce_left_shift(case6)" * doctest::test_suite("view::reduce_left_shift"))
{
    REDUCE_LEFT_SHIFT_SUBCASE( case6,   a, axis, dtype, initial, keepdims );
    REDUCE_LEFT_SHIFT_SUBCASE( case6, a_a, axis, dtype, initial, keepdims );
    REDUCE_LEFT_SHIFT_SUBCASE( case6, a_v, axis, dtype, initial, keepdims );
    REDUCE_LEFT_SHIFT_SUBCASE( case6, a_f, axis, dtype, initial, keepdims );
    REDUCE_LEFT_SHIFT_SUBCASE( case6, a_h, axis, dtype, initial, keepdims );
}

TEST_CASE("reduce_left_shift(case7)" * doctest::test_suite("view::reduce_left_shift"))
{
    REDUCE_LEFT_SHIFT_SUBCASE( case7,   a, axis, dtype, initial, keepdims );
    REDUCE_LEFT_SHIFT_SUBCASE( case7, a_a, axis, dtype, initial, keepdims );
    REDUCE_LEFT_SHIFT_SUBCASE( case7, a_v, axis, dtype, initial, keepdims );
    REDUCE_LEFT_SHIFT_SUBCASE( case7, a_f, axis, dtype, initial, keepdims );
    REDUCE_LEFT_SHIFT_SUBCASE( case7, a_h, axis, dtype, initial, keepdims );
}

TEST_CASE("reduce_left_shift(case8)" * doctest::test_suite("view::reduce_left_shift"))
{
    REDUCE_LEFT_SHIFT_SUBCASE( case8,   a, axis, dtype, initial, keepdims );
    REDUCE_LEFT_SHIFT_SUBCASE( case8, a_a, axis, dtype, initial, keepdims );
    REDUCE_LEFT_SHIFT_SUBCASE( case8, a_v, axis, dtype, initial, keepdims );
    REDUCE_LEFT_SHIFT_SUBCASE( case8, a_f, axis, dtype, initial, keepdims );
    REDUCE_LEFT_SHIFT_SUBCASE( case8, a_h, axis, dtype, initial, keepdims );
}

TEST_CASE("reduce_left_shift(case9)" * doctest::test_suite("view::reduce_left_shift"))
{
    REDUCE_LEFT_SHIFT_SUBCASE( case9,   a, axis, dtype, initial, keepdims );
    REDUCE_LEFT_SHIFT_SUBCASE( case9, a_a, axis, dtype, initial, keepdims );
    REDUCE_LEFT_SHIFT_SUBCASE( case9, a_v, axis, dtype, initial, keepdims );
    REDUCE_LEFT_SHIFT_SUBCASE( case9, a_f, axis, dtype, initial, keepdims );
    REDUCE_LEFT_SHIFT_SUBCASE( case9, a_h, axis, dtype, initial, keepdims );
}

NMTOOLS_TESTING_DECLARE_CASE(view, accumulate_left_shift)
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
        int axis = 2;
        CAST_ARRAYS(a)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case1)
    {
        int shape[3] = {2,3,2};
        int result[2][3][2] = {
            {
                {0,  0},
                {2, 16},
                {4,128},
            },
            {
                { 6,  768},
                { 8, 4096},
                {10,20480},
            }
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
        int shape[3] = {2,3,2};
        int result[2][3][2] = {
            {
                {0,  1},
                {0,  8},
                {0,256},
            },
            {
                {      6,      7},
                {   1536,   3584},
                {1572864,7340032},
            }
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
        int axis = 0;
        CAST_ARRAYS(a)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case3)
    {
        int shape[3] = {2,3,2};
        int result[2][3][2] = {
            {
                {0,1},
                {2,3},
                {4,5},
            },
            {
                {   0,  128},
                { 512, 1536},
                {4096,10240},
            }
        };
    }
}

#define RUN_accumulate_left_shift_impl(...) \
nm::view::accumulate_left_shift(__VA_ARGS__);

#ifdef NMTOOLS_TESTING_ENABLE_BENCHMARKS
#include "nmtools/benchmarks/bench.hpp"
using nm::benchmarks::TrackedBench;
// create immediately invoked lambda
// that packs accumulate_left_shift fn to callable lambda
#define RUN_accumulate_left_shift(case_name, ...) \
[](auto&&...args){ \
    auto title = std::string("accumulate_left_shift-") + #case_name; \
    auto name  = nm::testing::make_func_args("", args...); \
    auto fn    = [&](){ \
        return RUN_accumulate_left_shift_impl(args...); \
    }; \
    return TrackedBench::run(title, name, fn); \
}(__VA_ARGS__);
#else
// run normally without benchmarking, ignore case_name
#define RUN_accumulate_left_shift(case_name, ...) \
RUN_accumulate_left_shift_impl(__VA_ARGS__);
#endif // NMTOOLS_TESTING_ENABLE_BENCHMARKS

#define ACCUMULATE_LEFT_SHIFT_SUBCASE(case_name, ...) \
SUBCASE(#case_name) \
{ \
    NMTOOLS_TESTING_DECLARE_NS(view, accumulate_left_shift, case_name); \
    using namespace args; \
    auto result = RUN_accumulate_left_shift(case_name, __VA_ARGS__); \
    NMTOOLS_ASSERT_EQUAL( result.shape(), expect::shape ); \
    NMTOOLS_ASSERT_CLOSE( result, expect::result ); \
}

TEST_CASE("accumulate_left_shift(case1)" * doctest::test_suite("view::accumulate_left_shift"))
{
    ACCUMULATE_LEFT_SHIFT_SUBCASE( case1,   a, axis );
    ACCUMULATE_LEFT_SHIFT_SUBCASE( case1, a_a, axis );
    ACCUMULATE_LEFT_SHIFT_SUBCASE( case1, a_v, axis );
    ACCUMULATE_LEFT_SHIFT_SUBCASE( case1, a_f, axis );
    ACCUMULATE_LEFT_SHIFT_SUBCASE( case1, a_h, axis );
    // dynamic dim array not supported yet
    // ACCUMULATE_LEFT_SHIFT_SUBCASE( case1, a_d, axis );
}

TEST_CASE("accumulate_left_shift(case2)" * doctest::test_suite("view::accumulate_left_shift"))
{
    ACCUMULATE_LEFT_SHIFT_SUBCASE( case2,   a, axis );
    ACCUMULATE_LEFT_SHIFT_SUBCASE( case2, a_a, axis );
    ACCUMULATE_LEFT_SHIFT_SUBCASE( case2, a_v, axis );
    ACCUMULATE_LEFT_SHIFT_SUBCASE( case2, a_f, axis );
    ACCUMULATE_LEFT_SHIFT_SUBCASE( case2, a_h, axis );
    // dynamic dim array not supported yet
    // ACCUMULATE_LEFT_SHIFT_SUBCASE( case2, a_d, axis );
}

TEST_CASE("accumulate_left_shift(case3)" * doctest::test_suite("view::accumulate_left_shift"))
{
    ACCUMULATE_LEFT_SHIFT_SUBCASE( case3,   a, axis );
    ACCUMULATE_LEFT_SHIFT_SUBCASE( case3, a_a, axis );
    ACCUMULATE_LEFT_SHIFT_SUBCASE( case3, a_v, axis );
    ACCUMULATE_LEFT_SHIFT_SUBCASE( case3, a_f, axis );
    ACCUMULATE_LEFT_SHIFT_SUBCASE( case3, a_h, axis );
    // dynamic dim array not supported yet
    // ACCUMULATE_LEFT_SHIFT_SUBCASE( case3, a_d, axis );
}