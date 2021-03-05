#include "nmtools/array/view/where.hpp"
#include "nmtools/array/ndarray/dynamic.hpp"
#include "nmtools/array/ndarray/hybrid.hpp"
#include "nmtools/array/ndarray/fixed.hpp"
#include "nmtools/testing/doctest.hpp"

#include <array>
#include <vector>

namespace nm = nmtools;
namespace na = nm::array;
namespace kind = na::kind;

NMTOOLS_TESTING_DECLARE_CASE(view, where)
{
    NMTOOLS_TESTING_DECLARE_ARGS(case1)
    {
        bool condition[10] = {true, true, true, true, true, false, false, false, false, false};
        int x[10] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
        int y[10] = {0,10,20,30,40,50,60,70,80,90};
        auto condition_a = cast<bool>(condition);
        auto condition_v = cast(condition, kind::nested_vec);
        auto condition_d = cast(condition, kind::dynamic);
        auto condition_f = cast(condition, kind::fixed);
        auto condition_h = cast(condition, kind::hybrid);
        auto x_a = cast<int>(x);
        auto x_v = cast(x, kind::nested_vec);
        auto x_d = cast(x, kind::dynamic);
        auto x_f = cast(x, kind::fixed);
        auto x_h = cast(x, kind::hybrid);
        auto y_a = cast<int>(y);
        auto y_v = cast(y, kind::nested_vec);
        auto y_d = cast(y, kind::dynamic);
        auto y_f = cast(y, kind::fixed);
        auto y_h = cast(y, kind::hybrid);
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case1)
    {
        int dim = 1;
        int shape[1] = {10};
        int result[10] = {0, 1, 2, 3, 4, 50, 60, 70, 80, 90};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case2)
    {
        bool condition[3][4] = {
            {false,  true,  true, true},
            {false, false,  true, true},
            {false, false, false, true},
        };
        int x[3][1] = {
            {0},
            {1},
            {2},
        };
        int y[1][4] = {{10,11,12,13}};
        auto condition_a = cast<bool>(condition);
        auto condition_v = cast(condition, kind::nested_vec);
        auto condition_d = cast(condition, kind::dynamic);
        auto condition_f = cast(condition, kind::fixed);
        auto condition_h = cast(condition, kind::hybrid);
        auto x_a = cast<int>(x);
        auto x_v = cast(x, kind::nested_vec);
        auto x_d = cast(x, kind::dynamic);
        auto x_f = cast(x, kind::fixed);
        auto x_h = cast(x, kind::hybrid);
        auto y_a = cast<int>(y);
        auto y_v = cast(y, kind::nested_vec);
        auto y_d = cast(y, kind::dynamic);
        auto y_f = cast(y, kind::fixed);
        auto y_h = cast(y, kind::hybrid);
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case2)
    {
        int dim = 2;
        int shape[2] = {3,4};
        int result[3][4] = {
            {10,  0,  0, 0},
            {10, 11,  1, 1},
            {10, 11, 12, 2},
        };
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case3)
    {
        bool condition[3][4] = {
            {false,  true,  true, true},
            {false, false,  true, true},
            {false, false, false, true},
        };
        int x[1][3][1] = {
            {
                {0},
                {1},
                {2},
            }
        };
        int y[1][4] = {{10,11,12,13}};
        auto condition_a = cast<bool>(condition);
        auto condition_v = cast(condition, kind::nested_vec);
        auto condition_d = cast(condition, kind::dynamic);
        auto condition_f = cast(condition, kind::fixed);
        auto condition_h = cast(condition, kind::hybrid);
        auto x_a = cast<int>(x);
        auto x_v = cast(x, kind::nested_vec);
        auto x_d = cast(x, kind::dynamic);
        auto x_f = cast(x, kind::fixed);
        auto x_h = cast(x, kind::hybrid);
        auto y_a = cast<int>(y);
        auto y_v = cast(y, kind::nested_vec);
        auto y_d = cast(y, kind::dynamic);
        auto y_f = cast(y, kind::fixed);
        auto y_h = cast(y, kind::hybrid);
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case3)
    {
        int dim = 3;
        int shape[3] = {1,3,4};
        int result[1][3][4] = {
            {
                {10,  0,  0, 0},
                {10, 11,  1, 1},
                {10, 11, 12, 2},
            }
        };
    }
}

#define RUN_impl(...) \
nm::view::where(__VA_ARGS__);

#ifdef NMTOOLS_TESTING_ENABLE_BENCHMARKS
#include "nmtools/benchmarks/bench.hpp"
using nm::benchmarks::TrackedBench;
// create immediately invoked lambda
// that packs where fn to callable lambda
#define RUN_where(case_name, ...) \
[](auto&&...args){ \
    auto title = std::string("where-") + #case_name; \
    auto name  = nm::testing::make_func_args("", args...); \
    auto fn    = [&](){ \
        return RUN_impl(args...); \
    }; \
    return TrackedBench::run(title, name, fn); \
}(__VA_ARGS__);
#else
// run normally without benchmarking, ignore case_name
#define RUN_where(case_name, ...) \
RUN_impl(__VA_ARGS__);
#endif // NMTOOLS_TESTING_ENABLE_BENCHMARKS

#define TILE_WHERE_SUBCASE(case_name,condition,x,y) \
SUBCASE(#case_name) \
{ \
    NMTOOLS_TESTING_DECLARE_NS( view, where, case_name ); \
    auto array_view = RUN_where( case_name, args::condition, args::x, args::y ); \
    NMTOOLS_ASSERT_EQUAL( array_view.dim(), expect::dim ); \
    NMTOOLS_ASSERT_EQUAL( array_view.shape(), expect::shape ); \
    NMTOOLS_ASSERT_CLOSE( array_view, expect::result ); \
}

TEST_CASE("where(case1)" * doctest::test_suite("view::where"))
{
    TILE_WHERE_SUBCASE(case1, condition,   x,   y  );
    TILE_WHERE_SUBCASE(case1, condition_a, x_a, y_a);
    TILE_WHERE_SUBCASE(case1, condition_v, x_v, y_v);
    TILE_WHERE_SUBCASE(case1, condition_f, x_f, y_f);
    TILE_WHERE_SUBCASE(case1, condition_d, x_d, y_d);
    TILE_WHERE_SUBCASE(case1, condition_h, x_h, y_h);
}

TEST_CASE("where(case2)" * doctest::test_suite("view::where"))
{
    TILE_WHERE_SUBCASE(case2, condition,   x,   y  );
    TILE_WHERE_SUBCASE(case2, condition_a, x_a, y_a);
    TILE_WHERE_SUBCASE(case2, condition_v, x_v, y_v);
    TILE_WHERE_SUBCASE(case2, condition_f, x_f, y_f);
    TILE_WHERE_SUBCASE(case2, condition_d, x_d, y_d);
    TILE_WHERE_SUBCASE(case2, condition_h, x_h, y_h);
}

TEST_CASE("where(case3)" * doctest::test_suite("view::where"))
{
    TILE_WHERE_SUBCASE(case3, condition,   x,   y  );
    TILE_WHERE_SUBCASE(case3, condition_a, x_a, y_a);
    TILE_WHERE_SUBCASE(case3, condition_v, x_v, y_v);
    TILE_WHERE_SUBCASE(case3, condition_f, x_f, y_f);
    TILE_WHERE_SUBCASE(case3, condition_d, x_d, y_d);
    TILE_WHERE_SUBCASE(case3, condition_h, x_h, y_h);
}