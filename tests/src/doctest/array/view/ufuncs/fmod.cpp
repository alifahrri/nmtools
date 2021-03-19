#include "nmtools/array/view/ufuncs/fmod.hpp"
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

NMTOOLS_TESTING_DECLARE_CASE(view, fmod)
{
    NMTOOLS_TESTING_DECLARE_ARGS(case1)
    {
        float a[3][3] = {
            {1.0,2.1,3.2},
            {1.3,2.4,3.5},
            {1.6,2.7,3.8},
        };
        float b[3] = {1.f,2.f,3.f};
        CAST_ARRAYS(a)
        CAST_ARRAYS(b)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case1)
    {
        int shape[2] = {3,3};
        float result[3][3] = {
            {std::fmod(1.0f,1.f),std::fmod(2.1f,2.f),std::fmod(3.2f,3.f)},
            {std::fmod(1.3f,1.f),std::fmod(2.4f,2.f),std::fmod(3.5f,3.f)},
            {std::fmod(1.6f,1.f),std::fmod(2.7f,2.f),std::fmod(3.8f,3.f)},
        };
    }
}

#define RUN_fmod_impl(...) \
nm::view::fmod(__VA_ARGS__);

#ifdef NMTOOLS_TESTING_ENABLE_BENCHMARKS
#include "nmtools/benchmarks/bench.hpp"
using nm::benchmarks::TrackedBench;
// create immediately invoked lambda
// that packs fmod fn to callable lambda
#define RUN_fmod(case_name, ...) \
[](auto&&...args){ \
    auto title = std::string("fmod-") + #case_name; \
    auto name  = nm::testing::make_func_args("", args...); \
    auto fn    = [&](){ \
        return RUN_fmod_impl(args...); \
    }; \
    return TrackedBench::run(title, name, fn); \
}(__VA_ARGS__);
#else
// run normally without benchmarking, ignore case_name
#define RUN_fmod(case_name, ...) \
RUN_fmod_impl(__VA_ARGS__);
#endif // NMTOOLS_TESTING_ENABLE_BENCHMARKS

#define FMOD_SUBCASE(case_name, ...) \
SUBCASE(#case_name) \
{ \
    NMTOOLS_TESTING_DECLARE_NS(view, fmod, case_name); \
    using namespace args; \
    auto result = RUN_fmod(case_name, __VA_ARGS__); \
    NMTOOLS_ASSERT_EQUAL( result.shape(), expect::shape ); \
    NMTOOLS_ASSERT_CLOSE( result, expect::result ); \
}

TEST_CASE("fmod(case1)" * doctest::test_suite("view::fmod"))
{
    FMOD_SUBCASE( case1,   a,   b );
    FMOD_SUBCASE( case1, a_a, b_a );
    FMOD_SUBCASE( case1, a_v, b_v );
    FMOD_SUBCASE( case1, a_f, b_f );
    FMOD_SUBCASE( case1, a_d, b_d );
    FMOD_SUBCASE( case1, a_h, b_h );
}

NMTOOLS_TESTING_DECLARE_CASE(view, reduce_fmod)
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
                {1,1},
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
        auto dtype = float64;
        auto initial = 5;
        CAST_ARRAYS(a)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case4)
    {
        int shape[2] = {2,3};
        float result[2][3] = {
            {0,1,1},
            {5,5,5},
        };
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
        int axis = 0;
        auto dtype = None;
        auto initial = None;
        auto keepdims = True;
        CAST_ARRAYS(a)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case5)
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
        int axis = 1;
        auto dtype = None;
        auto initial = None;
        auto keepdims = False;
        CAST_ARRAYS(a)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case6)
    {
        int shape[2] = {2,2};
        float result[2][2] = {
            {0,1},
            {6,7},
        };
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
        int axis = 2;
        auto dtype = None;
        auto initial = None;
        auto keepdims = true;
        CAST_ARRAYS(a)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case7)
    {
        int shape[3] = {2,3,1};
        float result[2][3][1] = {
            {{0},{2},{ 4}},
            {{6},{8},{10}},
        };
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case8)
    {
        float a[2][3][2] = {
            {
                {1,1},
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
        auto dtype = float64;
        auto initial = 5;
        auto keepdims = false;
        CAST_ARRAYS(a)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case8)
    {
        int shape[2] = {2,3};
        float result[2][3] = {
            {0,1,1},
            {5,5,5},
        };
    }
}

#define RUN_reduce_fmod_impl(...) \
nm::view::reduce_fmod(__VA_ARGS__);

#ifdef NMTOOLS_TESTING_ENABLE_BENCHMARKS
#include "nmtools/benchmarks/bench.hpp"
using nm::benchmarks::TrackedBench;
// create immediately invoked lambda
// that packs reduce_fmod fn to callable lambda
#define RUN_reduce_fmod(case_name, ...) \
[](auto&&...args){ \
    auto title = std::string("reduce_fmod-") + #case_name; \
    auto name  = nm::testing::make_func_args("", args...); \
    auto fn    = [&](){ \
        return RUN_reduce_fmod_impl(args...); \
    }; \
    return TrackedBench::run(title, name, fn); \
}(__VA_ARGS__);
#else
// run normally without benchmarking, ignore case_name
#define RUN_reduce_fmod(case_name, ...) \
RUN_reduce_fmod_impl(__VA_ARGS__);
#endif // NMTOOLS_TESTING_ENABLE_BENCHMARKS

#define REDUCE_FMOD_SUBCASE(case_name, ...) \
SUBCASE(#case_name) \
{ \
    NMTOOLS_TESTING_DECLARE_NS(view, reduce_fmod, case_name); \
    using namespace args; \
    auto result = RUN_reduce_fmod(case_name, __VA_ARGS__); \
    NMTOOLS_ASSERT_EQUAL( result.shape(), expect::shape ); \
    NMTOOLS_ASSERT_CLOSE( result, expect::result ); \
}

TEST_CASE("reduce_fmod(case1)" * doctest::test_suite("view::reduce_fmod"))
{
    REDUCE_FMOD_SUBCASE( case1,   a, axis );
    REDUCE_FMOD_SUBCASE( case1, a_a, axis );
    REDUCE_FMOD_SUBCASE( case1, a_v, axis );
    REDUCE_FMOD_SUBCASE( case1, a_f, axis );
    // dynamic dim array not supported yet
    // REDUCE_FMOD_SUBCASE( case1, a_d, axis );
    REDUCE_FMOD_SUBCASE( case1, a_f, axis );
}

TEST_CASE("reduce_fmod(case2)" * doctest::test_suite("view::reduce_fmod"))
{
    REDUCE_FMOD_SUBCASE( case2,   a, axis );
    REDUCE_FMOD_SUBCASE( case2, a_a, axis );
    REDUCE_FMOD_SUBCASE( case2, a_v, axis );
    REDUCE_FMOD_SUBCASE( case2, a_f, axis );
    // dynamic dim array not supported yet
    // REDUCE_FMOD_SUBCASE( case2, a_d, axis );
    REDUCE_FMOD_SUBCASE( case2, a_f, axis );
}

TEST_CASE("reduce_fmod(case3)" * doctest::test_suite("view::reduce_fmod"))
{
    REDUCE_FMOD_SUBCASE( case3,   a, axis );
    REDUCE_FMOD_SUBCASE( case3, a_a, axis );
    REDUCE_FMOD_SUBCASE( case3, a_v, axis );
    REDUCE_FMOD_SUBCASE( case3, a_f, axis );
    // dynamic dim array not supported yet
    // REDUCE_FMOD_SUBCASE( case3, a_d, axis );
    REDUCE_FMOD_SUBCASE( case3, a_f, axis );
}

TEST_CASE("reduce_fmod(case4)" * doctest::test_suite("view::reduce_fmod"))
{
    REDUCE_FMOD_SUBCASE( case4,   a, axis, dtype, initial );
    REDUCE_FMOD_SUBCASE( case4, a_a, axis, dtype, initial );
    REDUCE_FMOD_SUBCASE( case4, a_v, axis, dtype, initial );
    REDUCE_FMOD_SUBCASE( case4, a_f, axis, dtype, initial );
    REDUCE_FMOD_SUBCASE( case4, a_f, axis, dtype, initial );
}

TEST_CASE("reduce_fmod(case5)" * doctest::test_suite("view::reduce_fmod"))
{
    REDUCE_FMOD_SUBCASE( case5,   a, axis, dtype, initial, keepdims );
    REDUCE_FMOD_SUBCASE( case5, a_a, axis, dtype, initial, keepdims );
    REDUCE_FMOD_SUBCASE( case5, a_v, axis, dtype, initial, keepdims );
    REDUCE_FMOD_SUBCASE( case5, a_f, axis, dtype, initial, keepdims );
    REDUCE_FMOD_SUBCASE( case5, a_f, axis, dtype, initial, keepdims );
}

TEST_CASE("reduce_fmod(case6)" * doctest::test_suite("view::reduce_fmod"))
{
    REDUCE_FMOD_SUBCASE( case6,   a, axis, dtype, initial, keepdims );
    REDUCE_FMOD_SUBCASE( case6, a_a, axis, dtype, initial, keepdims );
    REDUCE_FMOD_SUBCASE( case6, a_v, axis, dtype, initial, keepdims );
    REDUCE_FMOD_SUBCASE( case6, a_f, axis, dtype, initial, keepdims );
    REDUCE_FMOD_SUBCASE( case6, a_f, axis, dtype, initial, keepdims );
}

TEST_CASE("reduce_fmod(case7)" * doctest::test_suite("view::reduce_fmod"))
{
    REDUCE_FMOD_SUBCASE( case7,   a, axis, dtype, initial, keepdims );
    REDUCE_FMOD_SUBCASE( case7, a_a, axis, dtype, initial, keepdims );
    REDUCE_FMOD_SUBCASE( case7, a_v, axis, dtype, initial, keepdims );
    REDUCE_FMOD_SUBCASE( case7, a_f, axis, dtype, initial, keepdims );
    REDUCE_FMOD_SUBCASE( case7, a_f, axis, dtype, initial, keepdims );
}

TEST_CASE("reduce_fmod(case8)" * doctest::test_suite("view::reduce_fmod"))
{
    REDUCE_FMOD_SUBCASE( case8,   a, axis, dtype, initial, keepdims );
    REDUCE_FMOD_SUBCASE( case8, a_a, axis, dtype, initial, keepdims );
    REDUCE_FMOD_SUBCASE( case8, a_v, axis, dtype, initial, keepdims );
    REDUCE_FMOD_SUBCASE( case8, a_f, axis, dtype, initial, keepdims );
    REDUCE_FMOD_SUBCASE( case8, a_f, axis, dtype, initial, keepdims );
}


NMTOOLS_TESTING_DECLARE_CASE(view, accumulate_fmod)
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

#define RUN_accumulate_fmod_impl(...) \
nm::view::accumulate_fmod(__VA_ARGS__);

#ifdef NMTOOLS_TESTING_ENABLE_BENCHMARKS
#include "nmtools/benchmarks/bench.hpp"
using nm::benchmarks::TrackedBench;
// create immediately invoked lambda
// that packs accumulate_fmod fn to callable lambda
#define RUN_accumulate_fmod(case_name, ...) \
[](auto&&...args){ \
    auto title = std::string("accumulate_fmod-") + #case_name; \
    auto name  = nm::testing::make_func_args("", args...); \
    auto fn    = [&](){ \
        return RUN_accumulate_fmod_impl(args...); \
    }; \
    return TrackedBench::run(title, name, fn); \
}(__VA_ARGS__);
#else
// run normally without benchmarking, ignore case_name
#define RUN_accumulate_fmod(case_name, ...) \
RUN_accumulate_fmod_impl(__VA_ARGS__);
#endif // NMTOOLS_TESTING_ENABLE_BENCHMARKS

#define ACCUMULATE_FMOD_SUBCASE(case_name, ...) \
SUBCASE(#case_name) \
{ \
    NMTOOLS_TESTING_DECLARE_NS(view, accumulate_fmod, case_name); \
    using namespace args; \
    auto result = RUN_accumulate_fmod(case_name, __VA_ARGS__); \
    NMTOOLS_ASSERT_EQUAL( result.shape(), expect::shape ); \
    NMTOOLS_ASSERT_CLOSE( result, expect::result ); \
}

TEST_CASE("accumulate_fmod(case1)" * doctest::test_suite("view::accumulate_fmod"))
{
    ACCUMULATE_FMOD_SUBCASE( case1,   a, axis );
    ACCUMULATE_FMOD_SUBCASE( case1, a_a, axis );
    ACCUMULATE_FMOD_SUBCASE( case1, a_v, axis );
    ACCUMULATE_FMOD_SUBCASE( case1, a_f, axis );
    // dynamic dim array not supported yet
    // ACCUMULATE_FMOD_SUBCASE( case1, a_d, axis );
    ACCUMULATE_FMOD_SUBCASE( case1, a_f, axis );
}

TEST_CASE("accumulate_fmod(case2)" * doctest::test_suite("view::accumulate_fmod"))
{
    ACCUMULATE_FMOD_SUBCASE( case2,   a, axis );
    ACCUMULATE_FMOD_SUBCASE( case2, a_a, axis );
    ACCUMULATE_FMOD_SUBCASE( case2, a_v, axis );
    ACCUMULATE_FMOD_SUBCASE( case2, a_f, axis );
    // dynamic dim array not supported yet
    // ACCUMULATE_FMOD_SUBCASE( case2, a_d, axis );
    ACCUMULATE_FMOD_SUBCASE( case2, a_f, axis );
}

TEST_CASE("accumulate_fmod(case3)" * doctest::test_suite("view::accumulate_fmod"))
{
    ACCUMULATE_FMOD_SUBCASE( case3,   a, axis );
    ACCUMULATE_FMOD_SUBCASE( case3, a_a, axis );
    ACCUMULATE_FMOD_SUBCASE( case3, a_v, axis );
    ACCUMULATE_FMOD_SUBCASE( case3, a_f, axis );
    // dynamic dim array not supported yet
    // ACCUMULATE_FMOD_SUBCASE( case3, a_d, axis );
    ACCUMULATE_FMOD_SUBCASE( case3, a_f, axis );
}

NMTOOLS_TESTING_DECLARE_CASE(view, outer_fmod)
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

#define RUN_outer_fmod_impl(...) \
nm::view::outer_fmod(__VA_ARGS__);

#ifdef NMTOOLS_TESTING_ENABLE_BENCHMARKS
#include "nmtools/benchmarks/bench.hpp"
using nm::benchmarks::TrackedBench;
// create immediately invoked lambda
// that packs outer_fmod fn to callable lambda
#define RUN_outer_fmod(case_name, ...) \
[](auto&&...args){ \
    auto title = std::string("outer_fmod-") + #case_name; \
    auto name  = nm::testing::make_func_args("", args...); \
    auto fn    = [&](){ \
        return RUN_outer_fmod_impl(args...); \
    }; \
    return TrackedBench::run(title, name, fn); \
}(__VA_ARGS__);
#else
// run normally without benchmarking, ignore case_name
#define RUN_outer_fmod(case_name, ...) \
RUN_outer_fmod_impl(__VA_ARGS__);
#endif // NMTOOLS_TESTING_ENABLE_BENCHMARKS

#define OUTER_FMOD_SUBCASE(case_name, ...) \
SUBCASE(#case_name) \
{ \
    NMTOOLS_TESTING_DECLARE_NS(view, outer_fmod, case_name); \
    using namespace args; \
    auto result = RUN_outer_fmod(case_name, __VA_ARGS__); \
    NMTOOLS_ASSERT_EQUAL( result.shape(), expect::shape ); \
    NMTOOLS_ASSERT_CLOSE( result, expect::result ); \
}

TEST_CASE("outer_fmod(case1)" * doctest::test_suite("view::outer_fmod"))
{
    OUTER_FMOD_SUBCASE( case1,   a,   b );
    OUTER_FMOD_SUBCASE( case1, a_a, b_a );
    OUTER_FMOD_SUBCASE( case1, a_v, b_v );
    OUTER_FMOD_SUBCASE( case1, a_f, b_f );
    OUTER_FMOD_SUBCASE( case1, a_d, b_d );
    OUTER_FMOD_SUBCASE( case1, a_h, b_h );
}