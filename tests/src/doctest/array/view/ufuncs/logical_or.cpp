#include "nmtools/array/view/ufuncs/logical_or.hpp"
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

NMTOOLS_TESTING_DECLARE_CASE(view, logical_or)
{
    NMTOOLS_TESTING_DECLARE_ARGS(case1)
    {
        bool a[3][3] = {
            { true, false,  true},
            {false,  true, false},
            { true, false,  true},
        };
        bool b[3] = {false,true,true};
        CAST_ARRAYS(a)
        CAST_ARRAYS(b)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case1)
    {
        int shape[2] = {3,3};
        bool result[3][3] = {
            { true || false, false || true,  true || true},
            {false || false,  true || true, false || true},
            { true || false, false || true,  true || true},
        };
    }
}

#define RUN_logical_or_impl(...) \
nm::view::logical_or(__VA_ARGS__);

#ifdef NMTOOLS_TESTING_ENABLE_BENCHMARKS
#include "nmtools/benchmarks/bench.hpp"
using nm::benchmarks::TrackedBench;
// create immediately invoked lambda
// that packs logical_or fn to callable lambda
#define RUN_logical_or(case_name, ...) \
[](auto&&...args){ \
    auto title = std::string("logical_or-") + #case_name; \
    auto name  = nm::testing::make_func_args("", args...); \
    auto fn    = [&](){ \
        return RUN_logical_or_impl(args...); \
    }; \
    return TrackedBench::run(title, name, fn); \
}(__VA_ARGS__);
#else
// run normally without benchmarking, ignore case_name
#define RUN_logical_or(case_name, ...) \
RUN_logical_or_impl(__VA_ARGS__);
#endif // NMTOOLS_TESTING_ENABLE_BENCHMARKS

#define LOGICAL_OR_SUBCASE(case_name, ...) \
SUBCASE(#case_name) \
{ \
    NMTOOLS_TESTING_DECLARE_NS(view, logical_or, case_name); \
    using namespace args; \
    auto result = RUN_logical_or(case_name, __VA_ARGS__); \
    NMTOOLS_ASSERT_EQUAL( result.shape(), expect::shape ); \
    NMTOOLS_ASSERT_CLOSE( result, expect::result ); \
}

TEST_CASE("logical_or(case1)" * doctest::test_suite("view::logical_or"))
{
    LOGICAL_OR_SUBCASE( case1,   a,   b );
    LOGICAL_OR_SUBCASE( case1, a_a, b_a );
    LOGICAL_OR_SUBCASE( case1, a_v, b_v );
    LOGICAL_OR_SUBCASE( case1, a_f, b_f );
    LOGICAL_OR_SUBCASE( case1, a_d, b_d );
    LOGICAL_OR_SUBCASE( case1, a_h, b_h );
}


NMTOOLS_TESTING_DECLARE_CASE(view, reduce_logical_or)
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
        bool result[3][2] = {
            { true, true},
            { true, true},
            { true, true},
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
        bool result[2][2] = {
            { true, true},
            { true, true},
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
        bool result[2][3] = {
            { true, true, true},
            { true, true, true},
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
        bool result[2] = { true, true};
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
        bool result[3] = { true, true, true};
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
        bool result[2] = { true,true};
    }
}

#define RUN_reduce_logical_or_impl(...) \
nm::view::reduce_logical_or(__VA_ARGS__);

#ifdef NMTOOLS_TESTING_ENABLE_BENCHMARKS
#include "nmtools/benchmarks/bench.hpp"
using nm::benchmarks::TrackedBench;
// create immediately invoked lambda
// that packs reduce_logical_or fn to callable lambda
#define RUN_reduce_logical_or(case_name, ...) \
[](auto&&...args){ \
    auto title = std::string("reduce_logical_or-") + #case_name; \
    auto name  = nm::testing::make_func_args("", args...); \
    auto fn    = [&](){ \
        return RUN_reduce_logical_or_impl(args...); \
    }; \
    return TrackedBench::run(title, name, fn); \
}(__VA_ARGS__);
#else
// run normally without benchmarking, ignore case_name
#define RUN_reduce_logical_or(case_name, ...) \
RUN_reduce_logical_or_impl(__VA_ARGS__);
#endif // NMTOOLS_TESTING_ENABLE_BENCHMARKS

#define REDUCE_LOGICAL_OR_SUBCASE(case_name, ...) \
SUBCASE(#case_name) \
{ \
    NMTOOLS_TESTING_DECLARE_NS(view, reduce_logical_or, case_name); \
    using namespace args; \
    auto result = RUN_reduce_logical_or(case_name, __VA_ARGS__); \
    NMTOOLS_ASSERT_EQUAL( result.shape(), expect::shape ); \
    NMTOOLS_ASSERT_CLOSE( result, expect::result ); \
}

TEST_CASE("reduce_logical_or(case1)" * doctest::test_suite("view::reduce_logical_or"))
{
    REDUCE_LOGICAL_OR_SUBCASE( case1,   a, axis );
    REDUCE_LOGICAL_OR_SUBCASE( case1, a_a, axis );
    REDUCE_LOGICAL_OR_SUBCASE( case1, a_v, axis );
    REDUCE_LOGICAL_OR_SUBCASE( case1, a_f, axis );
    // dynamic dim array not supported yet
    // REDUCE_LOGICAL_OR_SUBCASE( case1, a_d, axis );
    REDUCE_LOGICAL_OR_SUBCASE( case1, a_f, axis );
}

TEST_CASE("reduce_logical_or(case2)" * doctest::test_suite("view::reduce_logical_or"))
{
    REDUCE_LOGICAL_OR_SUBCASE( case2,   a, axis );
    REDUCE_LOGICAL_OR_SUBCASE( case2, a_a, axis );
    REDUCE_LOGICAL_OR_SUBCASE( case2, a_v, axis );
    REDUCE_LOGICAL_OR_SUBCASE( case2, a_f, axis );
    // dynamic dim array not supported yet
    // REDUCE_LOGICAL_OR_SUBCASE( case2, a_d, axis );
    REDUCE_LOGICAL_OR_SUBCASE( case2, a_f, axis );
}

TEST_CASE("reduce_logical_or(case3)" * doctest::test_suite("view::reduce_logical_or"))
{
    REDUCE_LOGICAL_OR_SUBCASE( case3,   a, axis );
    REDUCE_LOGICAL_OR_SUBCASE( case3, a_a, axis );
    REDUCE_LOGICAL_OR_SUBCASE( case3, a_v, axis );
    REDUCE_LOGICAL_OR_SUBCASE( case3, a_f, axis );
    // dynamic dim array not supported yet
    // REDUCE_LOGICAL_OR_SUBCASE( case3, a_d, axis );
    REDUCE_LOGICAL_OR_SUBCASE( case3, a_f, axis );
}

TEST_CASE("reduce_logical_or(case4)" * doctest::test_suite("view::reduce_logical_or"))
{
    REDUCE_LOGICAL_OR_SUBCASE( case4,   a, axis );
    REDUCE_LOGICAL_OR_SUBCASE( case4, a_a, axis );
    REDUCE_LOGICAL_OR_SUBCASE( case4, a_v, axis );
    REDUCE_LOGICAL_OR_SUBCASE( case4, a_f, axis );
    // dynamic dim array not supported yet
    // REDUCE_LOGICAL_OR_SUBCASE( case4, a_d, axis );
    REDUCE_LOGICAL_OR_SUBCASE( case4, a_f, axis );
}

TEST_CASE("reduce_logical_or(case5)" * doctest::test_suite("view::reduce_logical_or"))
{
    REDUCE_LOGICAL_OR_SUBCASE( case5,   a, axis );
    REDUCE_LOGICAL_OR_SUBCASE( case5, a_a, axis );
    REDUCE_LOGICAL_OR_SUBCASE( case5, a_v, axis );
    REDUCE_LOGICAL_OR_SUBCASE( case5, a_f, axis );
    // dynamic dim array not supported yet
    // REDUCE_LOGICAL_OR_SUBCASE( case5, a_d, axis );
    REDUCE_LOGICAL_OR_SUBCASE( case5, a_f, axis );
}

TEST_CASE("reduce_logical_or(case6)" * doctest::test_suite("view::reduce_logical_or"))
{
    REDUCE_LOGICAL_OR_SUBCASE( case6,   a, axis );
    REDUCE_LOGICAL_OR_SUBCASE( case6, a_a, axis );
    REDUCE_LOGICAL_OR_SUBCASE( case6, a_v, axis );
    REDUCE_LOGICAL_OR_SUBCASE( case6, a_f, axis );
    // dynamic dim array not supported yet
    // REDUCE_LOGICAL_OR_SUBCASE( case6, a_d, axis );
    REDUCE_LOGICAL_OR_SUBCASE( case6, a_f, axis );
}