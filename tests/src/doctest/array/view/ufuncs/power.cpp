#include "nmtools/array/view/ufuncs/power.hpp"
#include "nmtools/array/ndarray/dynamic.hpp"
#include "nmtools/array/ndarray/hybrid.hpp"
#include "nmtools/array/ndarray/fixed.hpp"
#include "nmtools/testing/doctest.hpp"

#include <vector>
#include <array>
#include <tuple>

namespace nm = nmtools;
namespace na = nm::array;
namespace view = nm::view;
namespace kind = na::kind;
using std::tuple;

#define CAST_ARRAYS(name) \
auto name##_a = cast(name, kind::nested_arr); \
auto name##_v = cast(name, kind::nested_vec); \
auto name##_f = cast(name, kind::fixed); \
auto name##_d = cast(name, kind::dynamic); \
auto name##_h = cast(name, kind::hybrid); \

NMTOOLS_TESTING_DECLARE_CASE(view, power)
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
            {1, 1,  4},
            {1, 4, 25},
            {1, 7, 64},
        };
    }
}

#define RUN_power_impl(...) \
nm::view::power(__VA_ARGS__);

#ifdef NMTOOLS_TESTING_ENABLE_BENCHMARKS
#include "nmtools/benchmarks/bench.hpp"
using nm::benchmarks::TrackedBench;
// create immediately invoked lambda
// that packs power fn to callable lambda
#define RUN_power(case_name, ...) \
[](auto&&...args){ \
    auto title = std::string("power-") + #case_name; \
    auto name  = nm::testing::make_func_args("", args...); \
    auto fn    = [&](){ \
        return RUN_power_impl(args...); \
    }; \
    return TrackedBench::run(title, name, fn); \
}(__VA_ARGS__);
#else
// run normally without benchmarking, ignore case_name
#define RUN_power(case_name, ...) \
RUN_power_impl(__VA_ARGS__);
#endif // NMTOOLS_TESTING_ENABLE_BENCHMARKS

#define POWER_SUBCASE(case_name, ...) \
SUBCASE(#case_name) \
{ \
    NMTOOLS_TESTING_DECLARE_NS(view, power, case_name); \
    using namespace args; \
    auto result = RUN_power(case_name, __VA_ARGS__); \
    NMTOOLS_ASSERT_EQUAL( result.shape(), expect::shape ); \
    NMTOOLS_ASSERT_CLOSE( result, expect::result ); \
}

TEST_CASE("power(case1)" * doctest::test_suite("view::power"))
{
    POWER_SUBCASE( case1,   a,   b );
    POWER_SUBCASE( case1, a_a, b_a );
    POWER_SUBCASE( case1, a_v, b_v );
    POWER_SUBCASE( case1, a_f, b_f );
    POWER_SUBCASE( case1, a_d, b_d );
    POWER_SUBCASE( case1, a_h, b_h );
}

NMTOOLS_TESTING_DECLARE_CASE(view, reduce_power)
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
            {      0,       1},
            {    256,   19683},
            {1048576,48828125},
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
        auto dtype = float64;
        CAST_ARRAYS(a)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case2)
    {
        int shape[2] = {2,2};
        long double result[2][2] = {
            {0,1},
            {std::pow(std::pow(6,8),10),std::pow(std::pow(7,9),11)},
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
        // must provide dtype for correct result
        auto dtype = uint64;
        CAST_ARRAYS(a)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case3)
    {
        int shape[2] = {2,3};
        long int result[2][3] = {
            {     0,        8,        1024},
            {279936,134217728,100000000000},
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
        int axis = 2;
        auto dtype = None;
        auto initial = 1;
        CAST_ARRAYS(a)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case4)
    {
        int shape[2] = {2,3};
        int result[2][3] = {
            {1,1,1},
            {1,1,1},
        };
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
        int axis = 0;
        auto dtype = None;
        auto initial = 0;
        CAST_ARRAYS(a)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case5)
    {
        int shape[2] = {3,2};
        int result[3][2] = {
            {1,0},
            {0,0},
            {0,0},
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
                {      0,       1},
                {    256,   19683},
                {1048576,48828125},
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
        auto dtype = float64;
        auto initial = None;
        auto keepdims = False;
        CAST_ARRAYS(a)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case7)
    {
        int shape[2] = {2,2};
        long double result[2][2] = {
            {0,1},
            {std::pow(std::pow(6,8),10),std::pow(std::pow(7,9),11)},
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
        // must provide dtype for correct result
        auto dtype = uint64;
        auto initial = None;
        auto keepdims = true;
        CAST_ARRAYS(a)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case8)
    {
        int shape[3] = {2,3,1};
        long int result[2][3][1] = {
            {{     0},{        8},{        1024}},
            {{279936},{134217728},{100000000000}},
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
        int axis = 2;
        auto dtype = None;
        auto initial = 1;
        auto keepdims = false;
        CAST_ARRAYS(a)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case9)
    {
        int shape[2] = {2,3};
        int result[2][3] = {
            {1,1,1},
            {1,1,1},
        };
    }
}

#define RUN_reduce_power_impl(...) \
nm::view::reduce_power(__VA_ARGS__);

#ifdef NMTOOLS_TESTING_ENABLE_BENCHMARKS
#include "nmtools/benchmarks/bench.hpp"
using nm::benchmarks::TrackedBench;
// create immediately invoked lambda
// that packs reduce_power fn to callable lambda
#define RUN_reduce_power(case_name, ...) \
[](auto&&...args){ \
    auto title = std::string("reduce_power-") + #case_name; \
    auto name  = nm::testing::make_func_args("", args...); \
    auto fn    = [&](){ \
        return RUN_reduce_power_impl(args...); \
    }; \
    return TrackedBench::run(title, name, fn); \
}(__VA_ARGS__);
#else
// run normally without benchmarking, ignore case_name
#define RUN_reduce_power(case_name, ...) \
RUN_reduce_power_impl(__VA_ARGS__);
#endif // NMTOOLS_TESTING_ENABLE_BENCHMARKS

#define REDUCE_POWER_SUBCASE(case_name, ...) \
SUBCASE(#case_name) \
{ \
    NMTOOLS_TESTING_DECLARE_NS(view, reduce_power, case_name); \
    using namespace args; \
    auto result = RUN_reduce_power(case_name, __VA_ARGS__); \
    NMTOOLS_ASSERT_EQUAL( result.shape(), expect::shape ); \
    NMTOOLS_ASSERT_CLOSE( result, expect::result ); \
}

TEST_CASE("reduce_power(case1)" * doctest::test_suite("view::reduce_power"))
{
    REDUCE_POWER_SUBCASE( case1,   a, axis );
    REDUCE_POWER_SUBCASE( case1, a_a, axis );
    REDUCE_POWER_SUBCASE( case1, a_v, axis );
    REDUCE_POWER_SUBCASE( case1, a_f, axis );
    // dynamic dim array not supported yet
    // REDUCE_POWER_SUBCASE( case1, a_d, axis );
    REDUCE_POWER_SUBCASE( case1, a_f, axis );
}

// may fail, not yet figured out casting for this case,
// this case results in bigger number than case3
// while current (promoted) casting still works for case3
TEST_CASE("reduce_power(case2)" * doctest::test_suite("view::reduce_power") * doctest::may_fail(true))
{
    REDUCE_POWER_SUBCASE( case2,   a, axis, dtype );
    REDUCE_POWER_SUBCASE( case2, a_a, axis, dtype );
    REDUCE_POWER_SUBCASE( case2, a_v, axis, dtype );
    REDUCE_POWER_SUBCASE( case2, a_f, axis, dtype );
    // dynamic dim array not supported yet
    // REDUCE_POWER_SUBCASE( case2, a_d, axis, dtype );
    REDUCE_POWER_SUBCASE( case2, a_f, axis, dtype );
}

TEST_CASE("reduce_power(case3)" * doctest::test_suite("view::reduce_power"))
{
    REDUCE_POWER_SUBCASE( case3,   a, axis, dtype );
    REDUCE_POWER_SUBCASE( case3, a_a, axis, dtype );
    REDUCE_POWER_SUBCASE( case3, a_v, axis, dtype );
    REDUCE_POWER_SUBCASE( case3, a_f, axis, dtype );
    // dynamic dim array not supported yet
    // REDUCE_POWER_SUBCASE( case3, a_d, axis, dtype );
    REDUCE_POWER_SUBCASE( case3, a_f, axis, dtype );
}

TEST_CASE("reduce_power(case4)" * doctest::test_suite("view::reduce_power"))
{
    REDUCE_POWER_SUBCASE( case4,   a, axis, dtype, initial );
    REDUCE_POWER_SUBCASE( case4, a_a, axis, dtype, initial );
    REDUCE_POWER_SUBCASE( case4, a_v, axis, dtype, initial );
    REDUCE_POWER_SUBCASE( case4, a_f, axis, dtype, initial );
    REDUCE_POWER_SUBCASE( case4, a_f, axis, dtype, initial );
}

TEST_CASE("reduce_power(case5)" * doctest::test_suite("view::reduce_power"))
{
    REDUCE_POWER_SUBCASE( case5,   a, axis, dtype, initial );
    REDUCE_POWER_SUBCASE( case5, a_a, axis, dtype, initial );
    REDUCE_POWER_SUBCASE( case5, a_v, axis, dtype, initial );
    REDUCE_POWER_SUBCASE( case5, a_f, axis, dtype, initial );
    REDUCE_POWER_SUBCASE( case5, a_f, axis, dtype, initial );
}

TEST_CASE("reduce_power(case6)" * doctest::test_suite("view::reduce_power"))
{
    REDUCE_POWER_SUBCASE( case6,   a, axis, dtype, initial, keepdims );
    REDUCE_POWER_SUBCASE( case6, a_a, axis, dtype, initial, keepdims );
    REDUCE_POWER_SUBCASE( case6, a_v, axis, dtype, initial, keepdims );
    REDUCE_POWER_SUBCASE( case6, a_f, axis, dtype, initial, keepdims );
    REDUCE_POWER_SUBCASE( case6, a_f, axis, dtype, initial, keepdims );
}

TEST_CASE("reduce_power(case7)" * doctest::test_suite("view::reduce_power"))
{
    REDUCE_POWER_SUBCASE( case7,   a, axis, dtype, initial, keepdims );
    REDUCE_POWER_SUBCASE( case7, a_a, axis, dtype, initial, keepdims );
    REDUCE_POWER_SUBCASE( case7, a_v, axis, dtype, initial, keepdims );
    REDUCE_POWER_SUBCASE( case7, a_f, axis, dtype, initial, keepdims );
    REDUCE_POWER_SUBCASE( case7, a_f, axis, dtype, initial, keepdims );
}

TEST_CASE("reduce_power(case8)" * doctest::test_suite("view::reduce_power"))
{
    REDUCE_POWER_SUBCASE( case8,   a, axis, dtype, initial, keepdims );
    REDUCE_POWER_SUBCASE( case8, a_a, axis, dtype, initial, keepdims );
    REDUCE_POWER_SUBCASE( case8, a_v, axis, dtype, initial, keepdims );
    REDUCE_POWER_SUBCASE( case8, a_f, axis, dtype, initial, keepdims );
    REDUCE_POWER_SUBCASE( case8, a_f, axis, dtype, initial, keepdims );
}

TEST_CASE("reduce_power(case9)" * doctest::test_suite("view::reduce_power"))
{
    REDUCE_POWER_SUBCASE( case9,   a, axis, dtype, initial, keepdims );
    REDUCE_POWER_SUBCASE( case9, a_a, axis, dtype, initial, keepdims );
    REDUCE_POWER_SUBCASE( case9, a_v, axis, dtype, initial, keepdims );
    REDUCE_POWER_SUBCASE( case9, a_f, axis, dtype, initial, keepdims );
    REDUCE_POWER_SUBCASE( case9, a_f, axis, dtype, initial, keepdims );
}

NMTOOLS_TESTING_DECLARE_CASE(view, accumulate_power)
{
    NMTOOLS_TESTING_DECLARE_ARGS(case1)
    {
        long long int a[2][3][2] = {
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
        long long int result[2][3][2] = {
            {
                {0,1},
                {2,3},
                {4,5},
            },
            {
                {      0,       1},
                {    256,   19683},
                {1048576,48828125}
            }
        };
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case2)
    {
        long long int a[2][3][2] = {
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
    NMTOOLS_TESTING_DECLARE_EXPECT(case2)
    {
        int shape[3] = {2,3,2};
        long long int result[2][3][2] = {
            {
                {0,   0},
                {2,   8},
                {4,1024},
            },
            {
                { 6,      279936},
                { 8,   134217728},
                {10,100000000000}
            }
        };
    }
}

#define RUN_accumulate_power_impl(...) \
nm::view::accumulate_power(__VA_ARGS__);

#ifdef NMTOOLS_TESTING_ENABLE_BENCHMARKS
#include "nmtools/benchmarks/bench.hpp"
using nm::benchmarks::TrackedBench;
// create immediately invoked lambda
// that packs accumulate_power fn to callable lambda
#define RUN_accumulate_power(case_name, ...) \
[](auto&&...args){ \
    auto title = std::string("accumulate_power-") + #case_name; \
    auto name  = nm::testing::make_func_args("", args...); \
    auto fn    = [&](){ \
        return RUN_accumulate_power_impl(args...); \
    }; \
    return TrackedBench::run(title, name, fn); \
}(__VA_ARGS__);
#else
// run normally without benchmarking, ignore case_name
#define RUN_accumulate_power(case_name, ...) \
RUN_accumulate_power_impl(__VA_ARGS__);
#endif // NMTOOLS_TESTING_ENABLE_BENCHMARKS

#define ACCUMULATE_POWER_SUBCASE(case_name, ...) \
SUBCASE(#case_name) \
{ \
    NMTOOLS_TESTING_DECLARE_NS(view, accumulate_power, case_name); \
    using namespace args; \
    auto result = RUN_accumulate_power(case_name, __VA_ARGS__); \
    NMTOOLS_ASSERT_EQUAL( result.shape(), expect::shape ); \
    NMTOOLS_ASSERT_CLOSE( result, expect::result ); \
}

TEST_CASE("accumulate_power(case1)" * doctest::test_suite("view::accumulate_power"))
{
    ACCUMULATE_POWER_SUBCASE( case1,   a, axis );
    ACCUMULATE_POWER_SUBCASE( case1, a_a, axis );
    ACCUMULATE_POWER_SUBCASE( case1, a_v, axis );
    ACCUMULATE_POWER_SUBCASE( case1, a_f, axis );
    // dynamic dim array not supported yet
    // ACCUMULATE_POWER_SUBCASE( case1, a_d, axis );
    ACCUMULATE_POWER_SUBCASE( case1, a_f, axis );
}

TEST_CASE("accumulate_power(case2)" * doctest::test_suite("view::accumulate_power"))
{
    ACCUMULATE_POWER_SUBCASE( case2,   a, axis );
    ACCUMULATE_POWER_SUBCASE( case2, a_a, axis );
    ACCUMULATE_POWER_SUBCASE( case2, a_v, axis );
    ACCUMULATE_POWER_SUBCASE( case2, a_f, axis );
    // dynamic dim array not supported yet
    // ACCUMULATE_POWER_SUBCASE( case2, a_d, axis );
    ACCUMULATE_POWER_SUBCASE( case2, a_f, axis );
}


NMTOOLS_TESTING_DECLARE_CASE(view, outer_power)
{
    NMTOOLS_TESTING_DECLARE_ARGS(case1)
    {
        int a[2][3] = {
            {0,1,2},
            {3,4,5},
        };
        int b[3] = { 6,  7, 8};
        CAST_ARRAYS(a)
        CAST_ARRAYS(b)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case1)
    {
        int shape[3] = {2,3,3};
        int result[2][3][3] = \
       {{{     0,      0,      0},
        {     1,      1,      1},
        {    64,    128,    256}},

       {{   729,   2187,   6561},
        {  4096,  16384,  65536},
        { 15625,  78125, 390625}}};
    }
}

#define RUN_outer_power_impl(...) \
nm::view::outer_power(__VA_ARGS__);

#ifdef NMTOOLS_TESTING_ENABLE_BENCHMARKS
#include "nmtools/benchmarks/bench.hpp"
using nm::benchmarks::TrackedBench;
// create immediately invoked lambda
// that packs outer_power fn to callable lambda
#define RUN_outer_power(case_name, ...) \
[](auto&&...args){ \
    auto title = std::string("outer_power-") + #case_name; \
    auto name  = nm::testing::make_func_args("", args...); \
    auto fn    = [&](){ \
        return RUN_outer_power_impl(args...); \
    }; \
    return TrackedBench::run(title, name, fn); \
}(__VA_ARGS__);
#else
// run normally without benchmarking, ignore case_name
#define RUN_outer_power(case_name, ...) \
RUN_outer_power_impl(__VA_ARGS__);
#endif // NMTOOLS_TESTING_ENABLE_BENCHMARKS

#define OUTER_POWER_SUBCASE(case_name, ...) \
SUBCASE(#case_name) \
{ \
    NMTOOLS_TESTING_DECLARE_NS(view, outer_power, case_name); \
    using namespace args; \
    auto result = RUN_outer_power(case_name, __VA_ARGS__); \
    NMTOOLS_ASSERT_EQUAL( result.shape(), expect::shape ); \
    NMTOOLS_ASSERT_CLOSE( result, expect::result ); \
}

TEST_CASE("outer_power(case1)" * doctest::test_suite("view::outer_power"))
{
    OUTER_POWER_SUBCASE( case1,   a,   b );
    OUTER_POWER_SUBCASE( case1, a_a, b_a );
    OUTER_POWER_SUBCASE( case1, a_v, b_v );
    OUTER_POWER_SUBCASE( case1, a_f, b_f );
    OUTER_POWER_SUBCASE( case1, a_d, b_d );
    OUTER_POWER_SUBCASE( case1, a_h, b_h );
}