#include "nmtools/array/view/ufuncs/fmin.hpp"
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

NMTOOLS_TESTING_DECLARE_CASE(view, fmin)
{
    NMTOOLS_TESTING_DECLARE_ARGS(case1)
    {
        float a[3][3] = {
            {0,1,2},
            {3,4,5},
            {6,7,8},
        };
        float b[3] = {0.F,1,NAN};
        CAST_ARRAYS(a)
        CAST_ARRAYS(b)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case1)
    {
        int shape[2] = {3,3};
        float result[3][3] = {
            {std::fmin(0.f,0.F),std::fmin(1.f,1.f),std::fmin(2.f,NAN)},
            {std::fmin(3.f,0.F),std::fmin(4.f,1.f),std::fmin(5.f,NAN)},
            {std::fmin(6.f,0.F),std::fmin(7.f,1.f),std::fmin(8.f,NAN)},
        };
    }
}

#define RUN_fmin_impl(...) \
nm::view::fmin(__VA_ARGS__);

#ifdef NMTOOLS_TESTING_ENABLE_BENCHMARKS
#include "nmtools/benchmarks/bench.hpp"
using nm::benchmarks::TrackedBench;
// create immediately invoked lambda
// that packs fmin fn to callable lambda
#define RUN_fmin(case_name, ...) \
[](auto&&...args){ \
    auto title = std::string("fmin-") + #case_name; \
    auto name  = nm::testing::make_func_args("", args...); \
    auto fn    = [&](){ \
        return RUN_fmin_impl(args...); \
    }; \
    return TrackedBench::run(title, name, fn); \
}(__VA_ARGS__);
#else
// run normally without benchmarking, ignore case_name
#define RUN_fmin(case_name, ...) \
RUN_fmin_impl(__VA_ARGS__);
#endif // NMTOOLS_TESTING_ENABLE_BENCHMARKS

#define FMIN_SUBCASE(case_name, ...) \
SUBCASE(#case_name) \
{ \
    NMTOOLS_TESTING_DECLARE_NS(view, fmin, case_name); \
    using namespace args; \
    auto result = RUN_fmin(case_name, __VA_ARGS__); \
    NMTOOLS_ASSERT_EQUAL( result.shape(), expect::shape ); \
    NMTOOLS_ASSERT_CLOSE( result, expect::result ); \
}

TEST_CASE("fmin(case1)" * doctest::test_suite("view::fmin"))
{
    FMIN_SUBCASE( case1,   a,   b );
    FMIN_SUBCASE( case1, a_a, b_a );
    FMIN_SUBCASE( case1, a_v, b_v );
    FMIN_SUBCASE( case1, a_f, b_f );
    FMIN_SUBCASE( case1, a_d, b_d );
    FMIN_SUBCASE( case1, a_h, b_h );
}

NMTOOLS_TESTING_DECLARE_CASE(view, reduce_fmin)
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
        int shape[2] = {3,2};
        float result[3][2] = {
            {0,1},
            {2,3},
            {4,5},
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
        int shape[2] = {2,2};
        float result[2][2] = {
            {0,1},
            {6,7},
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
        int shape[2] = {2,3};
        float result[2][3] = {
            {0,2, 4},
            {6,8,10},
        };
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case4)
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
        int axis[2] = {0,1};
        CAST_ARRAYS(a)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case4)
    {
        int shape[1] = {2};
        float result[2] = {0,1};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case5)
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
        int axis[2] = {0,2};
        CAST_ARRAYS(a)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case5)
    {
        int shape[1] = {3};
        float result[3] = {0,2,4};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case6)
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
        int axis[2] = {1,2};
        CAST_ARRAYS(a)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case6)
    {
        int shape[1] = {2};
        float result[2] = {0,6};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case7)
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
        int axis[2] = {1,2};
        auto dtype = dtype_t<long int>{};
        auto initial = 5;
        CAST_ARRAYS(a)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case7)
    {
        int shape[1] = {2};
        long int result[2] = {0,5};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case8)
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
        auto dtype = None;
        auto initial = None;
        auto keepdims = True;
        CAST_ARRAYS(a)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case8)
    {
        int shape[3] = {1,3,2};
        float result[1][3][2] = {
            {
                {0,1},
                {2,3},
                {4,5},
            }
        };
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case9)
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
        auto dtype = None;
        auto initial = None;
        auto keepdims = False;
        CAST_ARRAYS(a)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case9)
    {
        int shape[2] = {2,2};
        float result[2][2] = {
            {0,1},
            {6,7},
        };
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case10)
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
        auto dtype = None;
        auto initial = None;
        auto keepdims = true;
        CAST_ARRAYS(a)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case10)
    {
        int shape[3] = {2,3,1};
        float result[2][3][1] = {
            {{0},{2},{ 4}},
            {{6},{8},{10}},
        };
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case11)
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
        int axis[2] = {0,1};
        auto dtype = None;
        auto initial = None;
        auto keepdims = false;
        CAST_ARRAYS(a)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case11)
    {
        int shape[1] = {2};
        float result[2] = {0,1};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case12)
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
        int axis[2] = {0,2};
        auto dtype = None;
        auto initial = None;
        auto keepdims = true;
        CAST_ARRAYS(a)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case12)
    {
        int shape[3] = {1,3,1};
        float result[1][3][1] = {
            {
                {0},
                {2},
                {4},
            },
        };
    }
}

#define RUN_reduce_fmin_impl(...) \
nm::view::reduce_fmin(__VA_ARGS__);

#ifdef NMTOOLS_TESTING_ENABLE_BENCHMARKS
#include "nmtools/benchmarks/bench.hpp"
using nm::benchmarks::TrackedBench;
// create immediately invoked lambda
// that packs reduce_fmin fn to callable lambda
#define RUN_reduce_fmin(case_name, ...) \
[](auto&&...args){ \
    auto title = std::string("reduce_fmin-") + #case_name; \
    auto name  = nm::testing::make_func_args("", args...); \
    auto fn    = [&](){ \
        return RUN_reduce_fmin_impl(args...); \
    }; \
    return TrackedBench::run(title, name, fn); \
}(__VA_ARGS__);
#else
// run normally without benchmarking, ignore case_name
#define RUN_reduce_fmin(case_name, ...) \
RUN_reduce_fmin_impl(__VA_ARGS__);
#endif // NMTOOLS_TESTING_ENABLE_BENCHMARKS

#define REDUCE_FMIN_SUBCASE(case_name, ...) \
SUBCASE(#case_name) \
{ \
    NMTOOLS_TESTING_DECLARE_NS(view, reduce_fmin, case_name); \
    using namespace args; \
    auto result = RUN_reduce_fmin(case_name, __VA_ARGS__); \
    NMTOOLS_ASSERT_EQUAL( result.shape(), expect::shape ); \
    NMTOOLS_ASSERT_CLOSE( result, expect::result ); \
}

TEST_CASE("reduce_fmin(case1)" * doctest::test_suite("view::reduce_fmin"))
{
    REDUCE_FMIN_SUBCASE( case1,   a, axis );
    REDUCE_FMIN_SUBCASE( case1, a_a, axis );
    REDUCE_FMIN_SUBCASE( case1, a_v, axis );
    REDUCE_FMIN_SUBCASE( case1, a_f, axis );
    // dynamic dim array not supported yet
    // REDUCE_FMIN_SUBCASE( case1, a_d, axis );
    REDUCE_FMIN_SUBCASE( case1, a_f, axis );
}

TEST_CASE("reduce_fmin(case2)" * doctest::test_suite("view::reduce_fmin"))
{
    REDUCE_FMIN_SUBCASE( case2,   a, axis );
    REDUCE_FMIN_SUBCASE( case2, a_a, axis );
    REDUCE_FMIN_SUBCASE( case2, a_v, axis );
    REDUCE_FMIN_SUBCASE( case2, a_f, axis );
    // dynamic dim array not supported yet
    // REDUCE_FMIN_SUBCASE( case2, a_d, axis );
    REDUCE_FMIN_SUBCASE( case2, a_f, axis );
}

TEST_CASE("reduce_fmin(case3)" * doctest::test_suite("view::reduce_fmin"))
{
    REDUCE_FMIN_SUBCASE( case3,   a, axis );
    REDUCE_FMIN_SUBCASE( case3, a_a, axis );
    REDUCE_FMIN_SUBCASE( case3, a_v, axis );
    REDUCE_FMIN_SUBCASE( case3, a_f, axis );
    // dynamic dim array not supported yet
    // REDUCE_FMIN_SUBCASE( case3, a_d, axis );
    REDUCE_FMIN_SUBCASE( case3, a_f, axis );
}

TEST_CASE("reduce_fmin(case4)" * doctest::test_suite("view::reduce_fmin"))
{
    REDUCE_FMIN_SUBCASE( case4,   a, axis );
    REDUCE_FMIN_SUBCASE( case4, a_a, axis );
    REDUCE_FMIN_SUBCASE( case4, a_v, axis );
    REDUCE_FMIN_SUBCASE( case4, a_f, axis );
    // dynamic dim array not supported yet
    // REDUCE_FMIN_SUBCASE( case4, a_d, axis );
    REDUCE_FMIN_SUBCASE( case4, a_f, axis );
}

TEST_CASE("reduce_fmin(case5)" * doctest::test_suite("view::reduce_fmin"))
{
    REDUCE_FMIN_SUBCASE( case5,   a, axis );
    REDUCE_FMIN_SUBCASE( case5, a_a, axis );
    REDUCE_FMIN_SUBCASE( case5, a_v, axis );
    REDUCE_FMIN_SUBCASE( case5, a_f, axis );
    // dynamic dim array not supported yet
    // REDUCE_FMIN_SUBCASE( case5, a_d, axis );
    REDUCE_FMIN_SUBCASE( case5, a_f, axis );
}

TEST_CASE("reduce_fmin(case6)" * doctest::test_suite("view::reduce_fmin"))
{
    REDUCE_FMIN_SUBCASE( case6,   a, axis );
    REDUCE_FMIN_SUBCASE( case6, a_a, axis );
    REDUCE_FMIN_SUBCASE( case6, a_v, axis );
    REDUCE_FMIN_SUBCASE( case6, a_f, axis );
    // dynamic dim array not supported yet
    // REDUCE_FMIN_SUBCASE( case6, a_d, axis );
    REDUCE_FMIN_SUBCASE( case6, a_f, axis );
}

TEST_CASE("reduce_fmin(case7)" * doctest::test_suite("view::reduce_fmin"))
{
    REDUCE_FMIN_SUBCASE( case7,   a, axis, dtype, initial );
    REDUCE_FMIN_SUBCASE( case7, a_a, axis, dtype, initial );
    REDUCE_FMIN_SUBCASE( case7, a_v, axis, dtype, initial );
    REDUCE_FMIN_SUBCASE( case7, a_f, axis, dtype, initial );
    REDUCE_FMIN_SUBCASE( case7, a_f, axis, dtype, initial );
}

TEST_CASE("reduce_fmin(case8)" * doctest::test_suite("view::reduce_fmin"))
{
    REDUCE_FMIN_SUBCASE( case8,   a, axis, dtype, initial, keepdims );
    REDUCE_FMIN_SUBCASE( case8, a_a, axis, dtype, initial, keepdims );
    REDUCE_FMIN_SUBCASE( case8, a_v, axis, dtype, initial, keepdims );
    REDUCE_FMIN_SUBCASE( case8, a_f, axis, dtype, initial, keepdims );
    REDUCE_FMIN_SUBCASE( case8, a_f, axis, dtype, initial, keepdims );
}

TEST_CASE("reduce_fmin(case9)" * doctest::test_suite("view::reduce_fmin"))
{
    REDUCE_FMIN_SUBCASE( case9,   a, axis, dtype, initial, keepdims );
    REDUCE_FMIN_SUBCASE( case9, a_a, axis, dtype, initial, keepdims );
    REDUCE_FMIN_SUBCASE( case9, a_v, axis, dtype, initial, keepdims );
    REDUCE_FMIN_SUBCASE( case9, a_f, axis, dtype, initial, keepdims );
    REDUCE_FMIN_SUBCASE( case9, a_f, axis, dtype, initial, keepdims );
}

TEST_CASE("reduce_fmin(case10)" * doctest::test_suite("view::reduce_fmin"))
{
    REDUCE_FMIN_SUBCASE( case10,   a, axis, dtype, initial, keepdims );
    REDUCE_FMIN_SUBCASE( case10, a_a, axis, dtype, initial, keepdims );
    REDUCE_FMIN_SUBCASE( case10, a_v, axis, dtype, initial, keepdims );
    REDUCE_FMIN_SUBCASE( case10, a_f, axis, dtype, initial, keepdims );
    REDUCE_FMIN_SUBCASE( case10, a_f, axis, dtype, initial, keepdims );
}

TEST_CASE("reduce_fmin(case11)" * doctest::test_suite("view::reduce_fmin"))
{
    REDUCE_FMIN_SUBCASE( case11,   a, axis, dtype, initial, keepdims );
    REDUCE_FMIN_SUBCASE( case11, a_a, axis, dtype, initial, keepdims );
    REDUCE_FMIN_SUBCASE( case11, a_v, axis, dtype, initial, keepdims );
    REDUCE_FMIN_SUBCASE( case11, a_f, axis, dtype, initial, keepdims );
    REDUCE_FMIN_SUBCASE( case11, a_f, axis, dtype, initial, keepdims );
}

TEST_CASE("reduce_fmin(case12)" * doctest::test_suite("view::reduce_fmin"))
{
    REDUCE_FMIN_SUBCASE( case12,   a, axis, dtype, initial, keepdims );
    REDUCE_FMIN_SUBCASE( case12, a_a, axis, dtype, initial, keepdims );
    REDUCE_FMIN_SUBCASE( case12, a_v, axis, dtype, initial, keepdims );
    REDUCE_FMIN_SUBCASE( case12, a_f, axis, dtype, initial, keepdims );
    REDUCE_FMIN_SUBCASE( case12, a_f, axis, dtype, initial, keepdims );
}

NMTOOLS_TESTING_DECLARE_CASE(view, accumulate_fmin)
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
                {0,1},
                {2,3},
                {4,5},
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
                {0,1},
                {0,1},
            },
            {
                {6,7},
                {6,7},
                {6,7},
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
                {0,0},
                {2,2},
                {4,4},
            },
            {
                { 6, 6},
                { 8, 8},
                {10,10},
            },
        };
    }
}

#define RUN_accumulate_fmin_impl(...) \
nm::view::accumulate_fmin(__VA_ARGS__);

#ifdef NMTOOLS_TESTING_ENABLE_BENCHMARKS
#include "nmtools/benchmarks/bench.hpp"
using nm::benchmarks::TrackedBench;
// create immediately invoked lambda
// that packs accumulate_fmin fn to callable lambda
#define RUN_accumulate_fmin(case_name, ...) \
[](auto&&...args){ \
    auto title = std::string("accumulate_fmin-") + #case_name; \
    auto name  = nm::testing::make_func_args("", args...); \
    auto fn    = [&](){ \
        return RUN_accumulate_fmin_impl(args...); \
    }; \
    return TrackedBench::run(title, name, fn); \
}(__VA_ARGS__);
#else
// run normally without benchmarking, ignore case_name
#define RUN_accumulate_fmin(case_name, ...) \
RUN_accumulate_fmin_impl(__VA_ARGS__);
#endif // NMTOOLS_TESTING_ENABLE_BENCHMARKS

#define ACCUMULATE_FMIN_SUBCASE(case_name, ...) \
SUBCASE(#case_name) \
{ \
    NMTOOLS_TESTING_DECLARE_NS(view, accumulate_fmin, case_name); \
    using namespace args; \
    auto result = RUN_accumulate_fmin(case_name, __VA_ARGS__); \
    NMTOOLS_ASSERT_EQUAL( result.shape(), expect::shape ); \
    NMTOOLS_ASSERT_CLOSE( result, expect::result ); \
}

TEST_CASE("accumulate_fmin(case1)" * doctest::test_suite("view::accumulate_fmin"))
{
    ACCUMULATE_FMIN_SUBCASE( case1,   a, axis );
    ACCUMULATE_FMIN_SUBCASE( case1, a_a, axis );
    ACCUMULATE_FMIN_SUBCASE( case1, a_v, axis );
    ACCUMULATE_FMIN_SUBCASE( case1, a_f, axis );
    // dynamic dim array not supported yet
    // ACCUMULATE_FMIN_SUBCASE( case1, a_d, axis );
    ACCUMULATE_FMIN_SUBCASE( case1, a_f, axis );
}

TEST_CASE("accumulate_fmin(case2)" * doctest::test_suite("view::accumulate_fmin"))
{
    ACCUMULATE_FMIN_SUBCASE( case2,   a, axis );
    ACCUMULATE_FMIN_SUBCASE( case2, a_a, axis );
    ACCUMULATE_FMIN_SUBCASE( case2, a_v, axis );
    ACCUMULATE_FMIN_SUBCASE( case2, a_f, axis );
    // dynamic dim array not supported yet
    // ACCUMULATE_FMIN_SUBCASE( case2, a_d, axis );
    ACCUMULATE_FMIN_SUBCASE( case2, a_f, axis );
}

TEST_CASE("accumulate_fmin(case3)" * doctest::test_suite("view::accumulate_fmin"))
{
    ACCUMULATE_FMIN_SUBCASE( case3,   a, axis );
    ACCUMULATE_FMIN_SUBCASE( case3, a_a, axis );
    ACCUMULATE_FMIN_SUBCASE( case3, a_v, axis );
    ACCUMULATE_FMIN_SUBCASE( case3, a_f, axis );
    // dynamic dim array not supported yet
    // ACCUMULATE_FMIN_SUBCASE( case3, a_d, axis );
    ACCUMULATE_FMIN_SUBCASE( case3, a_f, axis );
}

NMTOOLS_TESTING_DECLARE_CASE(view, outer_fmin)
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
       {{{0, 0, 0},
        {1, 1, 1},
        {2, 2, 2}},

       {{3, 3, 3},
        {4, 4, 4},
        {5, 5, 5}}};
    }
}

#define RUN_outer_fmin_impl(...) \
nm::view::outer_fmin(__VA_ARGS__);

#ifdef NMTOOLS_TESTING_ENABLE_BENCHMARKS
#include "nmtools/benchmarks/bench.hpp"
using nm::benchmarks::TrackedBench;
// create immediately invoked lambda
// that packs outer_fmin fn to callable lambda
#define RUN_outer_fmin(case_name, ...) \
[](auto&&...args){ \
    auto title = std::string("outer_fmin-") + #case_name; \
    auto name  = nm::testing::make_func_args("", args...); \
    auto fn    = [&](){ \
        return RUN_outer_fmin_impl(args...); \
    }; \
    return TrackedBench::run(title, name, fn); \
}(__VA_ARGS__);
#else
// run normally without benchmarking, ignore case_name
#define RUN_outer_fmin(case_name, ...) \
RUN_outer_fmin_impl(__VA_ARGS__);
#endif // NMTOOLS_TESTING_ENABLE_BENCHMARKS

#define OUTER_FMIN_SUBCASE(case_name, ...) \
SUBCASE(#case_name) \
{ \
    NMTOOLS_TESTING_DECLARE_NS(view, outer_fmin, case_name); \
    using namespace args; \
    auto result = RUN_outer_fmin(case_name, __VA_ARGS__); \
    NMTOOLS_ASSERT_EQUAL( result.shape(), expect::shape ); \
    NMTOOLS_ASSERT_CLOSE( result, expect::result ); \
}

TEST_CASE("outer_fmin(case1)" * doctest::test_suite("view::outer_fmin"))
{
    OUTER_FMIN_SUBCASE( case1,   a,   b );
    OUTER_FMIN_SUBCASE( case1, a_a, b_a );
    OUTER_FMIN_SUBCASE( case1, a_v, b_v );
    OUTER_FMIN_SUBCASE( case1, a_f, b_f );
    OUTER_FMIN_SUBCASE( case1, a_d, b_d );
    OUTER_FMIN_SUBCASE( case1, a_h, b_h );
}