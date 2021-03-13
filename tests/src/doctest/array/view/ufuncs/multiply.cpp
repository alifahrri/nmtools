#include "nmtools/array/view/ufuncs/multiply.hpp"
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

NMTOOLS_TESTING_DECLARE_CASE(view, multiply)
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
            {0, 1,  4},
            {0, 4, 10},
            {0, 7, 16},
        };
    }
}

#define RUN_multiply_impl(...) \
nm::view::multiply(__VA_ARGS__);

#ifdef NMTOOLS_TESTING_ENABLE_BENCHMARKS
#include "nmtools/benchmarks/bench.hpp"
using nm::benchmarks::TrackedBench;
// create immediately invoked lambda
// that packs multiply fn to callable lambda
#define RUN_multiply(case_name, ...) \
[](auto&&...args){ \
    auto title = std::string("multiply-") + #case_name; \
    auto name  = nm::testing::make_func_args("", args...); \
    auto fn    = [&](){ \
        return RUN_multiply_impl(args...); \
    }; \
    return TrackedBench::run(title, name, fn); \
}(__VA_ARGS__);
#else
// run normally without benchmarking, ignore case_name
#define RUN_multiply(case_name, ...) \
RUN_multiply_impl(__VA_ARGS__);
#endif // NMTOOLS_TESTING_ENABLE_BENCHMARKS

#define MULTIPLY_SUBCASE(case_name, ...) \
SUBCASE(#case_name) \
{ \
    NMTOOLS_TESTING_DECLARE_NS(view, multiply, case_name); \
    using namespace args; \
    auto result = RUN_multiply(case_name, __VA_ARGS__); \
    NMTOOLS_ASSERT_EQUAL( result.shape(), expect::shape ); \
    NMTOOLS_ASSERT_CLOSE( result, expect::result ); \
}

TEST_CASE("multiply(case1)" * doctest::test_suite("view::multiply"))
{
    MULTIPLY_SUBCASE( case1,   a,   b );
    MULTIPLY_SUBCASE( case1, a_a, b_a );
    MULTIPLY_SUBCASE( case1, a_v, b_v );
    MULTIPLY_SUBCASE( case1, a_f, b_f );
    MULTIPLY_SUBCASE( case1, a_d, b_d );
    MULTIPLY_SUBCASE( case1, a_h, b_h );
}

NMTOOLS_TESTING_DECLARE_CASE(view, reduce_multiply)
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
            { 0, 7},
            {16,27},
            {40,55},
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
            {  0,  15},
            {480, 693},
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
            }
        };
        int axis = 2;
        CAST_ARRAYS(a)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case3)
    {
        int shape[2] = {2,3};
        int result[2][3] = {
            { 0,  6,  20},
            {42, 72, 110},
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
            }
        };
        int axis[2] = {0,1};
        CAST_ARRAYS(a)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case4)
    {
        int shape[1] = {2};
        int result[2] = {0, 10395};
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
            }
        };
        int axis[2] = {0,2};
        CAST_ARRAYS(a)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case5)
    {
        int shape[1] = {3};
        int result[3] = { 0, 432, 2200};
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
            }
        };
        int axis[2] = {1,2};
        CAST_ARRAYS(a)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case6)
    {
        int shape[1] = {2};
        int result[2] = { 0, 332640};
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
            }
        };
        int axis[3] = {0,1,2};
        CAST_ARRAYS(a)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case7)
    {
        int shape[1] = {1};
        int result[1] = {0};
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
            }
        };
        int axis[2] = {1,2};
        auto dtype = uint32;
        auto initial = 256;
        CAST_ARRAYS(a)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case8)
    {
        int shape[1] = {2};
        int result[2] = {0,85155840};
    }
}

#define RUN_reduce_multiply_impl(...) \
nm::view::reduce_multiply(__VA_ARGS__);

#ifdef NMTOOLS_TESTING_ENABLE_BENCHMARKS
#include "nmtools/benchmarks/bench.hpp"
using nm::benchmarks::TrackedBench;
// create immediately invoked lambda
// that packs reduce_multiply fn to callable lambda
#define RUN_reduce_multiply(case_name, ...) \
[](auto&&...args){ \
    auto title = std::string("reduce_multiply-") + #case_name; \
    auto name  = nm::testing::make_func_args("", args...); \
    auto fn    = [&](){ \
        return RUN_reduce_multiply_impl(args...); \
    }; \
    return TrackedBench::run(title, name, fn); \
}(__VA_ARGS__);
#else
// run normally without benchmarking, ignore case_name
#define RUN_reduce_multiply(case_name, ...) \
RUN_reduce_multiply_impl(__VA_ARGS__);
#endif // NMTOOLS_TESTING_ENABLE_BENCHMARKS

#define REDUCE_MULTIPLY_SUBCASE(case_name, ...) \
SUBCASE(#case_name) \
{ \
    NMTOOLS_TESTING_DECLARE_NS(view, reduce_multiply, case_name); \
    using namespace args; \
    auto result = RUN_reduce_multiply(case_name, __VA_ARGS__); \
    NMTOOLS_ASSERT_EQUAL( result.shape(), expect::shape ); \
    NMTOOLS_ASSERT_CLOSE( result, expect::result ); \
}

TEST_CASE("reduce_multiply(case1)" * doctest::test_suite("view::reduce_multiply"))
{
    REDUCE_MULTIPLY_SUBCASE( case1,   a, axis );
    REDUCE_MULTIPLY_SUBCASE( case1, a_a, axis );
    REDUCE_MULTIPLY_SUBCASE( case1, a_v, axis );
    REDUCE_MULTIPLY_SUBCASE( case1, a_f, axis );
    // reduce doesnt work with dynamic ndarray for now
    // REDUCE_MULTIPLY_SUBCASE( case1, a_d, axis );
    REDUCE_MULTIPLY_SUBCASE( case1, a_h, axis );
}

TEST_CASE("reduce_multiply(case2)" * doctest::test_suite("view::reduce_multiply"))
{
    REDUCE_MULTIPLY_SUBCASE( case2,   a, axis );
    REDUCE_MULTIPLY_SUBCASE( case2, a_a, axis );
    REDUCE_MULTIPLY_SUBCASE( case2, a_v, axis );
    REDUCE_MULTIPLY_SUBCASE( case2, a_f, axis );
    REDUCE_MULTIPLY_SUBCASE( case2, a_h, axis );
}

TEST_CASE("reduce_multiply(case3)" * doctest::test_suite("view::reduce_multiply"))
{
    REDUCE_MULTIPLY_SUBCASE( case3,   a, axis );
    REDUCE_MULTIPLY_SUBCASE( case3, a_a, axis );
    REDUCE_MULTIPLY_SUBCASE( case3, a_v, axis );
    REDUCE_MULTIPLY_SUBCASE( case3, a_f, axis );
    REDUCE_MULTIPLY_SUBCASE( case3, a_h, axis );
}

TEST_CASE("reduce_multiply(case4)" * doctest::test_suite("view::reduce_multiply"))
{
    REDUCE_MULTIPLY_SUBCASE( case4,   a, axis );
    REDUCE_MULTIPLY_SUBCASE( case4, a_a, axis );
    REDUCE_MULTIPLY_SUBCASE( case4, a_v, axis );
    REDUCE_MULTIPLY_SUBCASE( case4, a_f, axis );
    REDUCE_MULTIPLY_SUBCASE( case4, a_h, axis );
}

TEST_CASE("reduce_multiply(case5)" * doctest::test_suite("view::reduce_multiply"))
{
    REDUCE_MULTIPLY_SUBCASE( case5,   a, axis );
    REDUCE_MULTIPLY_SUBCASE( case5, a_a, axis );
    REDUCE_MULTIPLY_SUBCASE( case5, a_v, axis );
    REDUCE_MULTIPLY_SUBCASE( case5, a_f, axis );
    REDUCE_MULTIPLY_SUBCASE( case5, a_h, axis );
}

TEST_CASE("reduce_multiply(case6)" * doctest::test_suite("view::reduce_multiply"))
{
    REDUCE_MULTIPLY_SUBCASE( case6,   a, axis );
    REDUCE_MULTIPLY_SUBCASE( case6, a_a, axis );
    REDUCE_MULTIPLY_SUBCASE( case6, a_v, axis );
    REDUCE_MULTIPLY_SUBCASE( case6, a_f, axis );
    REDUCE_MULTIPLY_SUBCASE( case6, a_h, axis );
}

// TEST_CASE("reduce_multiply(case7)" * doctest::test_suite("view::reduce_multiply"))
// {
//     REDUCE_MULTIPLY_SUBCASE( case7,   a, axis );
//     REDUCE_MULTIPLY_SUBCASE( case7, a_a, axis );
//     REDUCE_MULTIPLY_SUBCASE( case7, a_v, axis );
//     REDUCE_MULTIPLY_SUBCASE( case7, a_f, axis );
//     REDUCE_MULTIPLY_SUBCASE( case7, a_h, axis );
// }

TEST_CASE("reduce_multiply(case8)" * doctest::test_suite("view::reduce_multiply"))
{
    REDUCE_MULTIPLY_SUBCASE( case8,   a, axis, dtype, initial );
    REDUCE_MULTIPLY_SUBCASE( case8, a_a, axis, dtype, initial );
    REDUCE_MULTIPLY_SUBCASE( case8, a_v, axis, dtype, initial );
    REDUCE_MULTIPLY_SUBCASE( case8, a_f, axis, dtype, initial );
    REDUCE_MULTIPLY_SUBCASE( case8, a_h, axis, dtype, initial );
}