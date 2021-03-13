#include "nmtools/array/view/ufuncs/right_shift.hpp"
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

NMTOOLS_TESTING_DECLARE_CASE(view, right_shift)
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
            {0 >> 0, 1 >> 1, 2 >> 2},
            {3 >> 0, 4 >> 1, 5 >> 2},
            {6 >> 0, 7 >> 1, 8 >> 2},
        };
    }
}

#define RUN_right_shift_impl(...) \
nm::view::right_shift(__VA_ARGS__);

#ifdef NMTOOLS_TESTING_ENABLE_BENCHMARKS
#include "nmtools/benchmarks/bench.hpp"
using nm::benchmarks::TrackedBench;
// create immediately invoked lambda
// that packs right_shift fn to callable lambda
#define RUN_right_shift(case_name, ...) \
[](auto&&...args){ \
    auto title = std::string("right_shift-") + #case_name; \
    auto name  = nm::testing::make_func_args("", args...); \
    auto fn    = [&](){ \
        return RUN_right_shift_impl(args...); \
    }; \
    return TrackedBench::run(title, name, fn); \
}(__VA_ARGS__);
#else
// run normally without benchmarking, ignore case_name
#define RUN_right_shift(case_name, ...) \
RUN_right_shift_impl(__VA_ARGS__);
#endif // NMTOOLS_TESTING_ENABLE_BENCHMARKS

#define RIGHT_SHIFT_SUBCASE(case_name, ...) \
SUBCASE(#case_name) \
{ \
    NMTOOLS_TESTING_DECLARE_NS(view, right_shift, case_name); \
    using namespace args; \
    auto result = RUN_right_shift(case_name, __VA_ARGS__); \
    NMTOOLS_ASSERT_EQUAL( result.shape(), expect::shape ); \
    NMTOOLS_ASSERT_CLOSE( result, expect::result ); \
}

TEST_CASE("right_shift(case1)" * doctest::test_suite("view::right_shift"))
{
    RIGHT_SHIFT_SUBCASE( case1,   a,   b );
    RIGHT_SHIFT_SUBCASE( case1, a_a, b_a );
    RIGHT_SHIFT_SUBCASE( case1, a_v, b_v );
    RIGHT_SHIFT_SUBCASE( case1, a_f, b_f );
    RIGHT_SHIFT_SUBCASE( case1, a_d, b_d );
    RIGHT_SHIFT_SUBCASE( case1, a_h, b_h );
}

NMTOOLS_TESTING_DECLARE_CASE(view, reduce_right_shift)
{
    NMTOOLS_TESTING_DECLARE_ARGS(case1)
    {
        int a[2][3][2] = {
            {
                {11,10},
                { 9, 8},
                { 7, 6},
            },
            {
                {5,4},
                {3,2},
                {1,0},
            },
        };
        int axis = 0;
        CAST_ARRAYS(a)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case1)
    {
        int shape[2] = {3,2};
        int result[3][2] = {
            {0,0},
            {1,2},
            {3,6},
        };
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case2)
    {
        int a[2][3][2] = {
            {
                {11,10},
                { 9, 8},
                { 7, 6},
            },
            {
                {5,4},
                {3,2},
                {1,0},
            },
        };
        int axis = 1;
        CAST_ARRAYS(a)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case2)
    {
        int shape[2] = {2,2};
        int result[2][2] = {
            {0,0},
            {0,1},
        };
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case3)
    {
        int a[2][3][2] = {
            {
                {11,10},
                { 9, 8},
                { 7, 6},
            },
            {
                {5,4},
                {3,2},
                {1,0},
            },
        };
        int axis = 2;
        CAST_ARRAYS(a)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case3)
    {
        int shape[2] = {2,3};
        int result[2][3] = {
            {0,0,0},
            {0,0,1},
        };
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case4)
    {
        int a[2][3][2] = {
            {
                {11,10},
                { 9, 8},
                { 7, 6},
            },
            {
                {5,4},
                {3,2},
                {1,0},
            },
        };
        int axis = 2;
        auto dtype = int32;
        auto initial = 256;
        CAST_ARRAYS(a)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case4)
    {
        int shape[2] = {2,3};
        int result[2][3] = {
            { 0,0,  0},
            { 0,8,128},
        };
    }
}

#define RUN_reduce_right_shift_impl(...) \
nm::view::reduce_right_shift(__VA_ARGS__);

#ifdef NMTOOLS_TESTING_ENABLE_BENCHMARKS
#include "nmtools/benchmarks/bench.hpp"
using nm::benchmarks::TrackedBench;
// create immediately invoked lambda
// that packs reduce_right_shift fn to callable lambda
#define RUN_reduce_right_shift(case_name, ...) \
[](auto&&...args){ \
    auto title = std::string("reduce_right_shift-") + #case_name; \
    auto name  = nm::testing::make_func_args("", args...); \
    auto fn    = [&](){ \
        return RUN_reduce_right_shift_impl(args...); \
    }; \
    return TrackedBench::run(title, name, fn); \
}(__VA_ARGS__);
#else
// run normally without benchmarking, ignore case_name
#define RUN_reduce_right_shift(case_name, ...) \
RUN_reduce_right_shift_impl(__VA_ARGS__);
#endif // NMTOOLS_TESTING_ENABLE_BENCHMARKS

#define REDUCE_RIGHT_SHIFT_SUBCASE(case_name, ...) \
SUBCASE(#case_name) \
{ \
    NMTOOLS_TESTING_DECLARE_NS(view, reduce_right_shift, case_name); \
    using namespace args; \
    auto result = RUN_reduce_right_shift(case_name, __VA_ARGS__); \
    NMTOOLS_ASSERT_EQUAL( result.shape(), expect::shape ); \
    NMTOOLS_ASSERT_CLOSE( result, expect::result ); \
}

TEST_CASE("reduce_right_shift(case1)" * doctest::test_suite("view::reduce_right_shift"))
{
    REDUCE_RIGHT_SHIFT_SUBCASE( case1,   a, axis );
    REDUCE_RIGHT_SHIFT_SUBCASE( case1, a_a, axis );
    REDUCE_RIGHT_SHIFT_SUBCASE( case1, a_v, axis );
    REDUCE_RIGHT_SHIFT_SUBCASE( case1, a_f, axis );
    // dynamic dim array not supported yet
    // REDUCE_RIGHT_SHIFT_SUBCASE( case1, a_d, axis );
    REDUCE_RIGHT_SHIFT_SUBCASE( case1, a_h, axis );
}

TEST_CASE("reduce_right_shift(case2)" * doctest::test_suite("view::reduce_right_shift"))
{
    REDUCE_RIGHT_SHIFT_SUBCASE( case2,   a, axis );
    REDUCE_RIGHT_SHIFT_SUBCASE( case2, a_a, axis );
    REDUCE_RIGHT_SHIFT_SUBCASE( case2, a_v, axis );
    REDUCE_RIGHT_SHIFT_SUBCASE( case2, a_f, axis );
    // dynamic dim array not supported yet
    // REDUCE_RIGHT_SHIFT_SUBCASE( case2, a_d, axis );
    REDUCE_RIGHT_SHIFT_SUBCASE( case2, a_h, axis );
}

TEST_CASE("reduce_right_shift(case3)" * doctest::test_suite("view::reduce_right_shift"))
{
    REDUCE_RIGHT_SHIFT_SUBCASE( case3,   a, axis );
    REDUCE_RIGHT_SHIFT_SUBCASE( case3, a_a, axis );
    REDUCE_RIGHT_SHIFT_SUBCASE( case3, a_v, axis );
    REDUCE_RIGHT_SHIFT_SUBCASE( case3, a_f, axis );
    // dynamic dim array not supported yet
    // REDUCE_RIGHT_SHIFT_SUBCASE( case3, a_d, axis );
    REDUCE_RIGHT_SHIFT_SUBCASE( case3, a_h, axis );
}

TEST_CASE("reduce_right_shift(case4)" * doctest::test_suite("view::reduce_right_shift"))
{
    REDUCE_RIGHT_SHIFT_SUBCASE( case4,   a, axis, dtype, initial );
    REDUCE_RIGHT_SHIFT_SUBCASE( case4, a_a, axis, dtype, initial );
    REDUCE_RIGHT_SHIFT_SUBCASE( case4, a_v, axis, dtype, initial );
    REDUCE_RIGHT_SHIFT_SUBCASE( case4, a_f, axis, dtype, initial );
    REDUCE_RIGHT_SHIFT_SUBCASE( case4, a_h, axis, dtype, initial );
}