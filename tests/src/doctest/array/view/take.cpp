#include "nmtools/array/view/take.hpp"
#include "nmtools/array/ndarray/dynamic.hpp"
#include "nmtools/array/ndarray/hybrid.hpp"
#include "nmtools/array/ndarray/fixed.hpp"
#include "nmtools/testing/doctest.hpp"
#include "nmtools/constants.hpp"

namespace nm = nmtools;
namespace na = nm::array;
namespace kind = na::kind;

#define CAST_ARRAYS(name) \
auto name##_a = cast(name, kind::nested_arr); \
auto name##_v = cast(name, kind::nested_vec); \
auto name##_f = cast(name, kind::fixed); \
auto name##_d = cast(name, kind::dynamic); \
auto name##_h = cast(name, kind::hybrid); \

NMTOOLS_TESTING_DECLARE_CASE(view, take)
{
    NMTOOLS_TESTING_DECLARE_ARGS(case1)
    {
        int array[6] = {4, 3, 5, 7, 6, 8};
        int indices[3] = {0, 1, 4};
        int axis = 0;
        CAST_ARRAYS(array)
        CAST_ARRAYS(indices)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case1)
    {
        int result[3] = {4, 3, 6};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case2)
    {
        int array[2][5] = {
            {0,1,2,3,4},
            {5,6,7,8,9},
        };
        int indices[3] = {0,1,4};
        int axis = 1;
        CAST_ARRAYS(array)
        CAST_ARRAYS(indices)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case2)
    {
        int result[2][3] = {
            {0,1,4},
            {5,6,9},
        };
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case3)
    {
        int array[2][5] = {
            {0,1,2,3,4},
            {5,6,7,8,9},
        };
        int indices[1] = {1};
        int axis = 0;
        CAST_ARRAYS(array)
        CAST_ARRAYS(indices)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case3)
    {
        int result[1][5] = {
            {5,6,7,8,9},
        };
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case4)
    {
        int array[5][2] = {
            {0,5},
            {1,6},
            {2,7},
            {3,8},
            {4,9},
        };
        int indices[4] = {1,4,3,2};
        auto axis = None;
        CAST_ARRAYS(array)
        CAST_ARRAYS(indices)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case4)
    {
        int result[4] = {5,2,6,1};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case5)
    {
        int array[2][3][2] = {
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
        int indices[3] = {0,5,6};
        auto axis = None;
        CAST_ARRAYS(array)
        CAST_ARRAYS(indices)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case5)
    {
        int result[3] = {0,5,6};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case6)
    {
        int array[2][3][2] = {
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
        int indices[2] = {2,1};
        auto axis = 1;
        CAST_ARRAYS(array)
        CAST_ARRAYS(indices)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case6)
    {
        int result[2][2][2] = {
            {
                {4,5},
                {2,3},
            },
            {
                {10,11},
                { 8, 9},
            }
        };
    }
}

#define RUN_take_impl(...) \
nm::view::take(__VA_ARGS__);

#ifdef NMTOOLS_TESTING_ENABLE_BENCHMARKS
#include "nmtools/benchmarks/bench.hpp"
using nm::benchmarks::TrackedBench;
// create immediately invoked lambda
// that packs take fn to callable lambda
#define RUN_take(case_name, ...) \
[](auto&&...args){ \
    auto title = std::string("take-") + #case_name; \
    auto name  = nm::testing::make_func_args("", args...); \
    auto fn    = [&](){ \
        return RUN_take_impl(args...); \
    }; \
    return TrackedBench::run(title, name, fn); \
}(__VA_ARGS__);
#else
// run normally without benchmarking, ignore case_name
#define RUN_take(case_name, ...) \
RUN_take_impl(__VA_ARGS__);
#endif // NMTOOLS_TESTING_ENABLE_BENCHMARKS

#define TAKE_SUBCASE(case_name, ...) \
SUBCASE(#case_name) \
{ \
    NMTOOLS_TESTING_DECLARE_NS(view, take, case_name); \
    using namespace args; \
    auto result = RUN_take(case_name, __VA_ARGS__); \
    NMTOOLS_ASSERT_EQUAL( result, expect::result ); \
}

TEST_CASE("case1" * doctest::test_suite("view::take"))
{
    TAKE_SUBCASE( case1,   array,   indices, axis );
    TAKE_SUBCASE( case1, array_a, indices_a, axis );
    TAKE_SUBCASE( case1, array_v, indices_v, axis );
    TAKE_SUBCASE( case1, array_f, indices_f, axis );
    TAKE_SUBCASE( case1, array_d, indices_d, axis );
    TAKE_SUBCASE( case1, array_h, indices_h, axis );
}

TEST_CASE("case2" * doctest::test_suite("view::take"))
{
    TAKE_SUBCASE( case2,   array,   indices, axis );
    TAKE_SUBCASE( case2, array_a, indices_a, axis );
    TAKE_SUBCASE( case2, array_v, indices_v, axis );
    TAKE_SUBCASE( case2, array_f, indices_f, axis );
    TAKE_SUBCASE( case2, array_d, indices_d, axis );
    TAKE_SUBCASE( case2, array_h, indices_h, axis );
}

TEST_CASE("case3" * doctest::test_suite("view::take"))
{
    TAKE_SUBCASE( case3,   array,   indices, axis );
    TAKE_SUBCASE( case3, array_a, indices_a, axis );
    TAKE_SUBCASE( case3, array_v, indices_v, axis );
    TAKE_SUBCASE( case3, array_f, indices_f, axis );
    TAKE_SUBCASE( case3, array_d, indices_d, axis );
    TAKE_SUBCASE( case3, array_h, indices_h, axis );
}

TEST_CASE("case4" * doctest::test_suite("view::take"))
{
    TAKE_SUBCASE( case4,   array,   indices, axis );
    TAKE_SUBCASE( case4, array_a, indices_a, axis );
    TAKE_SUBCASE( case4, array_v, indices_v, axis );
    TAKE_SUBCASE( case4, array_f, indices_f, axis );
    TAKE_SUBCASE( case4, array_d, indices_d, axis );
    TAKE_SUBCASE( case4, array_h, indices_h, axis );
}

TEST_CASE("case5" * doctest::test_suite("view::take"))
{
    TAKE_SUBCASE( case5,   array,   indices, axis );
    TAKE_SUBCASE( case5, array_a, indices_a, axis );
    TAKE_SUBCASE( case5, array_v, indices_v, axis );
    TAKE_SUBCASE( case5, array_f, indices_f, axis );
    TAKE_SUBCASE( case5, array_d, indices_d, axis );
    TAKE_SUBCASE( case5, array_h, indices_h, axis );
}

TEST_CASE("case6" * doctest::test_suite("view::take"))
{
    TAKE_SUBCASE( case6,   array,   indices, axis );
    TAKE_SUBCASE( case6, array_a, indices_a, axis );
    TAKE_SUBCASE( case6, array_v, indices_v, axis );
    TAKE_SUBCASE( case6, array_f, indices_f, axis );
    TAKE_SUBCASE( case6, array_d, indices_d, axis );
    TAKE_SUBCASE( case6, array_h, indices_h, axis );
}