#include "nmtools/array/view/ufuncs/fmax.hpp"
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

NMTOOLS_TESTING_DECLARE_CASE(view, fmax)
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
            {std::fmax(0.f,0.F),std::fmax(1.f,1.f),std::fmax(2.f,NAN)},
            {std::fmax(3.f,0.F),std::fmax(4.f,1.f),std::fmax(5.f,NAN)},
            {std::fmax(6.f,0.F),std::fmax(7.f,1.f),std::fmax(8.f,NAN)},
        };
    }
}

#define RUN_fmax_impl(...) \
nm::view::fmax(__VA_ARGS__);

#ifdef NMTOOLS_TESTING_ENABLE_BENCHMARKS
#include "nmtools/benchmarks/bench.hpp"
using nm::benchmarks::TrackedBench;
// create immediately invoked lambda
// that packs fmax fn to callable lambda
#define RUN_fmax(case_name, ...) \
[](auto&&...args){ \
    auto title = std::string("fmax-") + #case_name; \
    auto name  = nm::testing::make_func_args("", args...); \
    auto fn    = [&](){ \
        return RUN_fmax_impl(args...); \
    }; \
    return TrackedBench::run(title, name, fn); \
}(__VA_ARGS__);
#else
// run normally without benchmarking, ignore case_name
#define RUN_fmax(case_name, ...) \
RUN_fmax_impl(__VA_ARGS__);
#endif // NMTOOLS_TESTING_ENABLE_BENCHMARKS

#define FMAX_SUBCASE(case_name, ...) \
SUBCASE(#case_name) \
{ \
    NMTOOLS_TESTING_DECLARE_NS(view, fmax, case_name); \
    using namespace args; \
    auto result = RUN_fmax(case_name, __VA_ARGS__); \
    NMTOOLS_ASSERT_EQUAL( result.shape(), expect::shape ); \
    NMTOOLS_ASSERT_CLOSE( result, expect::result ); \
}

TEST_CASE("fmax(case1)" * doctest::test_suite("view::fmax"))
{
    FMAX_SUBCASE( case1,   a,   b );
    FMAX_SUBCASE( case1, a_a, b_a );
    FMAX_SUBCASE( case1, a_v, b_v );
    FMAX_SUBCASE( case1, a_f, b_f );
    FMAX_SUBCASE( case1, a_d, b_d );
    FMAX_SUBCASE( case1, a_h, b_h );
}

NMTOOLS_TESTING_DECLARE_CASE(view, reduce_fmax)
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
            { 6, 7},
            { 8, 9},
            {10,11},
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
            { 4, 5},
            {10,11},
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
            {1, 3,  5},
            {7, 9, 11},
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
        float result[2] = {10,11};
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
        float result[3] = {7,9,11};
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
        float result[2] = {5,11};
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
        int axis[2] = {1,2};
        auto dtype = float32;
        auto initial = 512;
        CAST_ARRAYS(a)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case7)
    {
        int shape[1] = {2};
        float result[2] = {512,512};
    }
}

#define RUN_reduce_fmax_impl(...) \
nm::view::reduce_fmax(__VA_ARGS__);

#ifdef NMTOOLS_TESTING_ENABLE_BENCHMARKS
#include "nmtools/benchmarks/bench.hpp"
using nm::benchmarks::TrackedBench;
// create immediately invoked lambda
// that packs reduce_fmax fn to callable lambda
#define RUN_reduce_fmax(case_name, ...) \
[](auto&&...args){ \
    auto title = std::string("reduce_fmax-") + #case_name; \
    auto name  = nm::testing::make_func_args("", args...); \
    auto fn    = [&](){ \
        return RUN_reduce_fmax_impl(args...); \
    }; \
    return TrackedBench::run(title, name, fn); \
}(__VA_ARGS__);
#else
// run normally without benchmarking, ignore case_name
#define RUN_reduce_fmax(case_name, ...) \
RUN_reduce_fmax_impl(__VA_ARGS__);
#endif // NMTOOLS_TESTING_ENABLE_BENCHMARKS

#define REDUCE_FMAX_SUBCASE(case_name, ...) \
SUBCASE(#case_name) \
{ \
    NMTOOLS_TESTING_DECLARE_NS(view, reduce_fmax, case_name); \
    using namespace args; \
    auto result = RUN_reduce_fmax(case_name, __VA_ARGS__); \
    NMTOOLS_ASSERT_EQUAL( result.shape(), expect::shape ); \
    NMTOOLS_ASSERT_CLOSE( result, expect::result ); \
}

TEST_CASE("reduce_fmax(case1)" * doctest::test_suite("view::reduce_fmax"))
{
    REDUCE_FMAX_SUBCASE( case1,   a, axis );
    REDUCE_FMAX_SUBCASE( case1, a_a, axis );
    REDUCE_FMAX_SUBCASE( case1, a_v, axis );
    REDUCE_FMAX_SUBCASE( case1, a_f, axis );
    // dynamic dim array not supported yet
    // REDUCE_FMAX_SUBCASE( case1, a_d, axis );
    REDUCE_FMAX_SUBCASE( case1, a_f, axis );
}

TEST_CASE("reduce_fmax(case2)" * doctest::test_suite("view::reduce_fmax"))
{
    REDUCE_FMAX_SUBCASE( case2,   a, axis );
    REDUCE_FMAX_SUBCASE( case2, a_a, axis );
    REDUCE_FMAX_SUBCASE( case2, a_v, axis );
    REDUCE_FMAX_SUBCASE( case2, a_f, axis );
    // dynamic dim array not supported yet
    // REDUCE_FMAX_SUBCASE( case2, a_d, axis );
    REDUCE_FMAX_SUBCASE( case2, a_f, axis );
}

TEST_CASE("reduce_fmax(case3)" * doctest::test_suite("view::reduce_fmax"))
{
    REDUCE_FMAX_SUBCASE( case3,   a, axis );
    REDUCE_FMAX_SUBCASE( case3, a_a, axis );
    REDUCE_FMAX_SUBCASE( case3, a_v, axis );
    REDUCE_FMAX_SUBCASE( case3, a_f, axis );
    // dynamic dim array not supported yet
    // REDUCE_FMAX_SUBCASE( case3, a_d, axis );
    REDUCE_FMAX_SUBCASE( case3, a_f, axis );
}

TEST_CASE("reduce_fmax(case4)" * doctest::test_suite("view::reduce_fmax"))
{
    REDUCE_FMAX_SUBCASE( case4,   a, axis );
    REDUCE_FMAX_SUBCASE( case4, a_a, axis );
    REDUCE_FMAX_SUBCASE( case4, a_v, axis );
    REDUCE_FMAX_SUBCASE( case4, a_f, axis );
    // dynamic dim array not supported yet
    // REDUCE_FMAX_SUBCASE( case4, a_d, axis );
    REDUCE_FMAX_SUBCASE( case4, a_f, axis );
}

TEST_CASE("reduce_fmax(case5)" * doctest::test_suite("view::reduce_fmax"))
{
    REDUCE_FMAX_SUBCASE( case5,   a, axis );
    REDUCE_FMAX_SUBCASE( case5, a_a, axis );
    REDUCE_FMAX_SUBCASE( case5, a_v, axis );
    REDUCE_FMAX_SUBCASE( case5, a_f, axis );
    // dynamic dim array not supported yet
    // REDUCE_FMAX_SUBCASE( case5, a_d, axis );
    REDUCE_FMAX_SUBCASE( case5, a_f, axis );
}

TEST_CASE("reduce_fmax(case6)" * doctest::test_suite("view::reduce_fmax"))
{
    REDUCE_FMAX_SUBCASE( case6,   a, axis );
    REDUCE_FMAX_SUBCASE( case6, a_a, axis );
    REDUCE_FMAX_SUBCASE( case6, a_v, axis );
    REDUCE_FMAX_SUBCASE( case6, a_f, axis );
    // dynamic dim array not supported yet
    // REDUCE_FMAX_SUBCASE( case6, a_d, axis );
    REDUCE_FMAX_SUBCASE( case6, a_f, axis );
}

TEST_CASE("reduce_fmax(case7)" * doctest::test_suite("view::reduce_fmax"))
{
    REDUCE_FMAX_SUBCASE( case7,   a, axis, dtype, initial );
    REDUCE_FMAX_SUBCASE( case7, a_a, axis, dtype, initial );
    REDUCE_FMAX_SUBCASE( case7, a_v, axis, dtype, initial );
    REDUCE_FMAX_SUBCASE( case7, a_f, axis, dtype, initial );
    REDUCE_FMAX_SUBCASE( case7, a_f, axis, dtype, initial );
}