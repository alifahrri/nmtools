#include "nmtools/array/view/ufuncs/subtract.hpp"
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

NMTOOLS_TESTING_DECLARE_CASE(view, subtract)
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
            {0, 0, 0},
            {3, 3, 3},
            {6, 6, 6},
        };
    }
}

#define RUN_subtract_impl(...) \
nm::view::subtract(__VA_ARGS__);

#ifdef NMTOOLS_TESTING_ENABLE_BENCHMARKS
#include "nmtools/benchmarks/bench.hpp"
using nm::benchmarks::TrackedBench;
// create immediately invoked lambda
// that packs subtract fn to callable lambda
#define RUN_subtract(case_name, ...) \
[](auto&&...args){ \
    auto title = std::string("subtract-") + #case_name; \
    auto name  = nm::testing::make_func_args("", args...); \
    auto fn    = [&](){ \
        return RUN_subtract_impl(args...); \
    }; \
    return TrackedBench::run(title, name, fn); \
}(__VA_ARGS__);
#else
// run normally without benchmarking, ignore case_name
#define RUN_subtract(case_name, ...) \
RUN_subtract_impl(__VA_ARGS__);
#endif // NMTOOLS_TESTING_ENABLE_BENCHMARKS

#define SUBTRACT_SUBCASE(case_name, ...) \
SUBCASE(#case_name) \
{ \
    NMTOOLS_TESTING_DECLARE_NS(view, subtract, case_name); \
    using namespace args; \
    auto result = RUN_subtract(case_name, __VA_ARGS__); \
    NMTOOLS_ASSERT_EQUAL( result.shape(), expect::shape ); \
    NMTOOLS_ASSERT_CLOSE( result, expect::result ); \
}

TEST_CASE("subtract(case1)" * doctest::test_suite("view::subtract"))
{
    SUBTRACT_SUBCASE( case1,   a,   b );
    SUBTRACT_SUBCASE( case1, a_a, b_a );
    SUBTRACT_SUBCASE( case1, a_v, b_v );
    SUBTRACT_SUBCASE( case1, a_f, b_f );
    SUBTRACT_SUBCASE( case1, a_d, b_d );
    SUBTRACT_SUBCASE( case1, a_h, b_h );
}

NMTOOLS_TESTING_DECLARE_CASE(view, reduce_subtract)
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
            {-6,-6},
            {-6,-6},
            {-6,-6},
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
            { -6, -7},
            {-12,-13},
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
            {-1,-1,-1},
            {-1,-1,-1},
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
        auto dtype = int32;
        auto initial = 256;
        CAST_ARRAYS(a)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case4)
    {
        int shape[2] = {2,3};
        int result[2][3] = {
            {255,251,247},
            {243,239,235},
        };
    }
}

#define RUN_reduce_subtract_impl(...) \
nm::view::reduce_subtract(__VA_ARGS__);

#ifdef NMTOOLS_TESTING_ENABLE_BENCHMARKS
#include "nmtools/benchmarks/bench.hpp"
using nm::benchmarks::TrackedBench;
// create immediately invoked lambda
// that packs reduce_subtract fn to callable lambda
#define RUN_reduce_subtract(case_name, ...) \
[](auto&&...args){ \
    auto title = std::string("reduce_subtract-") + #case_name; \
    auto name  = nm::testing::make_func_args("", args...); \
    auto fn    = [&](){ \
        return RUN_reduce_subtract_impl(args...); \
    }; \
    return TrackedBench::run(title, name, fn); \
}(__VA_ARGS__);
#else
// run normally without benchmarking, ignore case_name
#define RUN_reduce_subtract(case_name, ...) \
RUN_reduce_subtract_impl(__VA_ARGS__);
#endif // NMTOOLS_TESTING_ENABLE_BENCHMARKS

#define REDUCE_SUBTRACT_SUBCASE(case_name, ...) \
SUBCASE(#case_name) \
{ \
    NMTOOLS_TESTING_DECLARE_NS(view, reduce_subtract, case_name); \
    using namespace args; \
    auto result = RUN_reduce_subtract(case_name, __VA_ARGS__); \
    NMTOOLS_ASSERT_EQUAL( result.shape(), expect::shape ); \
    NMTOOLS_ASSERT_CLOSE( result, expect::result ); \
}

TEST_CASE("reduce_subtract(case1)" * doctest::test_suite("view::reduce_subtract"))
{
    REDUCE_SUBTRACT_SUBCASE( case1,   a, axis );
    REDUCE_SUBTRACT_SUBCASE( case1, a_a, axis );
    REDUCE_SUBTRACT_SUBCASE( case1, a_v, axis );
    REDUCE_SUBTRACT_SUBCASE( case1, a_f, axis );
    // dynamic dim array not supported yet
    // REDUCE_SUBTRACT_SUBCASE( case1, a_d, axis );
    REDUCE_SUBTRACT_SUBCASE( case1, a_f, axis );
}

TEST_CASE("reduce_subtract(case2)" * doctest::test_suite("view::reduce_subtract"))
{
    REDUCE_SUBTRACT_SUBCASE( case2,   a, axis );
    REDUCE_SUBTRACT_SUBCASE( case2, a_a, axis );
    REDUCE_SUBTRACT_SUBCASE( case2, a_v, axis );
    REDUCE_SUBTRACT_SUBCASE( case2, a_f, axis );
    // dynamic dim array not supported yet
    // REDUCE_SUBTRACT_SUBCASE( case2, a_d, axis );
    REDUCE_SUBTRACT_SUBCASE( case2, a_f, axis );
}

TEST_CASE("reduce_subtract(case3)" * doctest::test_suite("view::reduce_subtract"))
{
    REDUCE_SUBTRACT_SUBCASE( case3,   a, axis );
    REDUCE_SUBTRACT_SUBCASE( case3, a_a, axis );
    REDUCE_SUBTRACT_SUBCASE( case3, a_v, axis );
    REDUCE_SUBTRACT_SUBCASE( case3, a_f, axis );
    // dynamic dim array not supported yet
    // REDUCE_SUBTRACT_SUBCASE( case3, a_d, axis );
    REDUCE_SUBTRACT_SUBCASE( case3, a_f, axis );
}

TEST_CASE("reduce_subtract(case4)" * doctest::test_suite("view::reduce_subtract"))
{
    REDUCE_SUBTRACT_SUBCASE( case4,   a, axis, dtype, initial );
    REDUCE_SUBTRACT_SUBCASE( case4, a_a, axis, dtype, initial );
    REDUCE_SUBTRACT_SUBCASE( case4, a_v, axis, dtype, initial );
    REDUCE_SUBTRACT_SUBCASE( case4, a_f, axis, dtype, initial );
    REDUCE_SUBTRACT_SUBCASE( case4, a_f, axis, dtype, initial );
}