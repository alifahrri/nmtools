#include "nmtools/array/index/free_axes.hpp"
#include "nmtools/array/ndarray/dynamic.hpp"
#include "nmtools/array/ndarray/hybrid.hpp"
#include "nmtools/array/ndarray/fixed.hpp"
#include "nmtools/testing/doctest.hpp"

#include <vector>
#include <array>
#include <tuple>

namespace nm = nmtools;
namespace na = nm::array;
namespace meta = nm::meta;
namespace kind = na::kind;

NMTOOLS_TESTING_DECLARE_CASE(free_axes)
{
    NMTOOLS_TESTING_DECLARE_ARGS(case1)
    {
        int a[2] = {5,4};
        int b[1] = {1};
        auto a_v = cast(a,kind::nested_vec);
        auto b_v = cast(b,kind::nested_vec);
        auto a_a = cast<int>(a);
        auto b_a = cast<int>(b);
        auto a_f = cast(a,kind::fixed);
        auto b_f = cast(b,kind::fixed);
        auto a_h = cast<na::hybrid_ndarray<int,2,1>>(a);
        auto b_h = cast<na::hybrid_ndarray<int,1,1>>(b);
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case1)
    {
        bool x[2] = {true, true};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case2)
    {
        int a[2] = {5,4};
        int b[1] = {4};
        auto a_v = cast(a,kind::nested_vec);
        auto b_v = cast(b,kind::nested_vec);
        auto a_a = cast<int>(a);
        auto b_a = cast<int>(b);
        auto a_f = cast(a,kind::fixed);
        auto b_f = cast(b,kind::fixed);
        auto a_h = cast<na::hybrid_ndarray<int,2,1>>(a);
        auto b_h = cast<na::hybrid_ndarray<int,1,1>>(b);
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case2)
    {
        bool x[2] = {true, false};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case3)
    {
        int a[4] = {8,7,6,5};
        int b[3] = {7,1,5};
        auto a_v = cast(a,kind::nested_vec);
        auto b_v = cast(b,kind::nested_vec);
        auto a_a = cast<int>(a);
        auto b_a = cast<int>(b);
        auto a_f = cast(a,kind::fixed);
        auto b_f = cast(b,kind::fixed);
        auto a_h = cast<na::hybrid_ndarray<int,4,1>>(a);
        auto b_h = cast<na::hybrid_ndarray<int,3,1>>(b);
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case3)
    {
        bool x[4] = {true, false, true, false};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case4)
    {
        int a[4] = {8,7,6,5};
        int b[4] = {8,1,5,1};
        auto a_v = cast(a,kind::nested_vec);
        auto b_v = cast(b,kind::nested_vec);
        auto a_a = cast<int>(a);
        auto b_a = cast<int>(b);
        auto a_f = cast(a,kind::fixed);
        auto b_f = cast(b,kind::fixed);
        auto a_h = cast<na::hybrid_ndarray<int,4,1>>(a);
        auto b_h = cast<na::hybrid_ndarray<int,4,1>>(b);
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case4)
    {
        bool x[4] = {false, true, false, true};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case5)
    {
        int a[3] = {256,256,3};
        int b[1] = {3};
        auto a_v = cast(a,kind::nested_vec);
        auto b_v = cast(b,kind::nested_vec);
        auto a_a = cast<int>(a);
        auto b_a = cast<int>(b);
        auto a_f = cast(a,kind::fixed);
        auto b_f = cast(b,kind::fixed);
        auto a_h = cast(a,kind::hybrid);
        auto b_h = cast(b,kind::hybrid);
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case5)
    {
        bool x[3] = {true, true, false};
    }
}

// TEST_CASE("free_axes(raw)" * doctest::test_suite("index::free_axes"))
// {
//     SUBCASE("case1")
//     {
//         NMTOOLS_TESTING_DECLARE_NS(free_axes, case1);
//         auto result = nm::index::free_axes(args::a,args::b);
//         NMTOOLS_ASSERT_EQUAL( result, expect::x );
//     }
// }

#define RUN_impl(...) \
nm::index::free_axes(__VA_ARGS__);

#ifdef NMTOOLS_TESTING_ENABLE_BENCHMARKS
#include "nmtools/benchmarks/bench.hpp"
using nm::benchmarks::TrackedBench;
// create immediately invoked lambda
// that packs free_axes fn to callable lambda
#define RUN_free_axes(case_name, ...) \
[](auto&&...args){ \
    auto title = std::string("free_axes-") + #case_name; \
    auto name  = nm::testing::make_func_args("", args...); \
    auto fn    = [&](){ \
        return RUN_impl(args...); \
    }; \
    /* doNotOptimizeAway doesnt work (complains on std::array) */ \
    return TrackedBench::run<false>(title, name, fn); \
}(__VA_ARGS__);
#else
// run normally without benchmarking, ignore case_name
#define RUN_free_axes(case_name, ...) \
RUN_impl(__VA_ARGS__);
#endif // NMTOOLS_TESTING_ENABLE_BENCHMARKS

#define FREE_AXES_SUBCASE(case_name, a, b) \
SUBCASE(#case_name) \
{ \
    NMTOOLS_TESTING_DECLARE_NS(free_axes, case_name); \
    auto result = RUN_free_axes(case_name, args::a, args::b); \
    NMTOOLS_ASSERT_EQUAL(result, expect::x); \
}

TEST_CASE("free_axes(case1)" * doctest::test_suite("index::free_axes"))
{
    FREE_AXES_SUBCASE(case1, a_a, b_a);
    FREE_AXES_SUBCASE(case1, a_v, b_v);
    FREE_AXES_SUBCASE(case1, a_f, b_f);
    FREE_AXES_SUBCASE(case1, a_h, b_h);
}

TEST_CASE("free_axes(case2)" * doctest::test_suite("index::free_axes"))
{
    FREE_AXES_SUBCASE(case2, a_a, b_a);
    FREE_AXES_SUBCASE(case2, a_v, b_v);
    FREE_AXES_SUBCASE(case2, a_f, b_f);
    FREE_AXES_SUBCASE(case2, a_h, b_h);
}

TEST_CASE("free_axes(case3)" * doctest::test_suite("index::free_axes"))
{
    FREE_AXES_SUBCASE(case3, a_a, b_a);
    FREE_AXES_SUBCASE(case3, a_v, b_v);
    FREE_AXES_SUBCASE(case3, a_f, b_f);
    FREE_AXES_SUBCASE(case3, a_h, b_h);
}

TEST_CASE("free_axes(case4)" * doctest::test_suite("index::free_axes"))
{
    FREE_AXES_SUBCASE(case4, a_a, b_a);
    FREE_AXES_SUBCASE(case4, a_v, b_v);
    FREE_AXES_SUBCASE(case4, a_f, b_f);
    FREE_AXES_SUBCASE(case4, a_h, b_h);
}

TEST_CASE("free_axes(case5)" * doctest::test_suite("index::free_axes"))
{
    FREE_AXES_SUBCASE(case5, a_a, b_a);
    FREE_AXES_SUBCASE(case5, a_v, b_v);
    FREE_AXES_SUBCASE(case5, a_f, b_f);
    FREE_AXES_SUBCASE(case5, a_h, b_h);
}