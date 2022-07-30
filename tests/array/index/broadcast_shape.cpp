#include "nmtools/array/index/broadcast_shape.hpp"
#include "nmtools/array/ndarray.hpp"
#include "nmtools/array/index/as_tuple.hpp"
#include "nmtools/testing/doctest.hpp"

namespace nm = nmtools;
namespace na = nm::array;
namespace meta = nm::meta;
namespace kind = na::kind;

NMTOOLS_TESTING_DECLARE_CASE(broadcast_shape)
{
    NMTOOLS_TESTING_DECLARE_ARGS(case1)
    {
        int a[2] = {5,4};
        int b[1] = {1};
        NMTOOLS_CAST_INDEX_ARRAYS(a)
        NMTOOLS_CAST_INDEX_ARRAYS(b)
        // auto a_t = nm::index::as_tuple(a_a);
        // auto b_t = nm::index::as_tuple(b_a);
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case1)
    {
        bool success = true;
        int expected[2] = {5,4};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case2)
    {
        int a[1] = {1};
        int b[2] = {5,4};
        NMTOOLS_CAST_INDEX_ARRAYS(a)
        NMTOOLS_CAST_INDEX_ARRAYS(b)
        // auto a_t = nm::index::as_tuple(a_a);
        // auto b_t = nm::index::as_tuple(b_a);
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case2)
    {
        bool success = true;
        int expected[2] = {5,4};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case3)
    {
        int a[1] = {4};
        int b[2] = {5,4};
        NMTOOLS_CAST_INDEX_ARRAYS(a)
        NMTOOLS_CAST_INDEX_ARRAYS(b)
        // auto a_t = nm::index::as_tuple(a_a);
        // auto b_t = nm::index::as_tuple(b_a);
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case3)
    {
        bool success = true;
        int expected[2] = {5,4};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case4)
    {
        int a[4] = {8,1,6,1};
        int b[3] = {7,1,5};
        NMTOOLS_CAST_INDEX_ARRAYS(a)
        NMTOOLS_CAST_INDEX_ARRAYS(b)
        // auto a_t = nm::index::as_tuple(a_a);
        // auto b_t = nm::index::as_tuple(b_a);
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case4)
    {
        bool success = true;
        int expected[4] = {8,7,6,5};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case5)
    {
        int a[3] = {256,256,3};
        int b[1] = {3};
        NMTOOLS_CAST_INDEX_ARRAYS(a)
        NMTOOLS_CAST_INDEX_ARRAYS(b)
        // auto a_t = nm::index::as_tuple(a_a);
        // auto b_t = nm::index::as_tuple(b_a);
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case5)
    {
        bool success = true;
        int expected[3] = {256,256,3};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case6)
    {
        int a[1] = {5};
        int b[2] = {5,4};
        NMTOOLS_CAST_INDEX_ARRAYS(a)
        NMTOOLS_CAST_INDEX_ARRAYS(b)
        // auto a_t = nm::index::as_tuple(a_a);
        // auto b_t = nm::index::as_tuple(b_a);
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case6)
    {
        bool success = false;
        int expected[2] = {0,0};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case7)
    {
        int a[2] = {2,1};
        int b[3] = {8,4,3};
        NMTOOLS_CAST_INDEX_ARRAYS(a)
        NMTOOLS_CAST_INDEX_ARRAYS(b)
        // auto a_t = nm::index::as_tuple(a_a);
        // auto b_t = nm::index::as_tuple(b_a);
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case7)
    {
        bool success = false;
        int expected[3] = {0,0,0};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case8)
    {
        int a[2] = {4,1};
        int b[3] = {8,1,3};
        int c[1] = {3};
        NMTOOLS_CAST_INDEX_ARRAYS(a)
        NMTOOLS_CAST_INDEX_ARRAYS(b)
        NMTOOLS_CAST_INDEX_ARRAYS(c)
        // auto a_t = nm::index::as_tuple(a_a);
        // auto b_t = nm::index::as_tuple(b_a);
        auto c_t = nm::index::as_tuple(c_a);
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case8)
    {
        bool success = true;
        int expected[3] = {8,4,3};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case9)
    {
        int a[2] = {4,1};
        int b[3] = {8,2,3};
        int c[1] = {3};
        NMTOOLS_CAST_INDEX_ARRAYS(a)
        NMTOOLS_CAST_INDEX_ARRAYS(b)
        NMTOOLS_CAST_INDEX_ARRAYS(c)
        // auto a_t = nm::index::as_tuple(a_a);
        // auto b_t = nm::index::as_tuple(b_a);
        auto c_t = nm::index::as_tuple(c_a);
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case9)
    {
        bool success = false;
        int expected[3] = {8,4,3};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case10)
    {
        int a[2] = {4,1};
        int b[3] = {8,1,3};
        int c[1] = {3};
        int d[6] = {2,2,3,1,4,1};
        NMTOOLS_CAST_INDEX_ARRAYS(a)
        NMTOOLS_CAST_INDEX_ARRAYS(b)
        NMTOOLS_CAST_INDEX_ARRAYS(c)
        NMTOOLS_CAST_INDEX_ARRAYS(d)
        // auto a_t = nm::index::as_tuple(a_a);
        // auto b_t = nm::index::as_tuple(b_a);
        auto c_t = nm::index::as_tuple(c_a);
        auto d_t = nm::index::as_tuple(d_a);
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case10)
    {
        bool success = true;
        int expected[6] = {2,2,3,8,4,3};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case11)
    {
        int a[2] =         {4,1};
        int b[3] =       {8,1,3};
        int c[1] =           {3};
        int d[6] = {2,2,3,1,4,1};
        int e[1] =           {1};
        int f[4] =     {3,1,4,1};
        int g[6] = {2,1,1,1,1,1};
        NMTOOLS_CAST_INDEX_ARRAYS(a)
        NMTOOLS_CAST_INDEX_ARRAYS(b)
        NMTOOLS_CAST_INDEX_ARRAYS(c)
        NMTOOLS_CAST_INDEX_ARRAYS(d)
        NMTOOLS_CAST_INDEX_ARRAYS(e)
        NMTOOLS_CAST_INDEX_ARRAYS(f)
        NMTOOLS_CAST_INDEX_ARRAYS(g)
        // auto a_t = nm::index::as_tuple(a_a);
        // auto b_t = nm::index::as_tuple(b_a);
        auto c_t = nm::index::as_tuple(c_a);
        auto d_t = nm::index::as_tuple(d_a);
        auto e_t = nm::index::as_tuple(e_a);
        auto f_t = nm::index::as_tuple(f_a);
        auto g_t = nm::index::as_tuple(g_a);
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case11)
    {
        bool success = true;
        int expected[6] = {2,2,3,8,4,3};
    }
}

#define RUN_impl(...) \
nm::index::broadcast_shape(__VA_ARGS__);

#ifdef NMTOOLS_TESTING_ENABLE_BENCHMARKS
#include "nmtools/benchmarks/bench.hpp"
using nm::benchmarks::TrackedBench;
// create immediately invoked lambda
// that packs broadcast_shape fn to callable lambda
#define RUN_broadcast_shape(case_name, ...) \
[](auto&&...args){ \
    auto title = std::string("broadcast_shape-") + #case_name; \
    auto name  = nm::testing::make_func_args("", args...); \
    auto fn    = [&](){ \
        return RUN_impl(args...); \
    }; \
    return TrackedBench::run(title, name, fn); \
}(__VA_ARGS__);
#else
// run normally without benchmarking, ignore case_name
#define RUN_broadcast_shape(case_name, ...) \
RUN_impl(__VA_ARGS__);
#endif // NMTOOLS_TESTING_ENABLE_BENCHMARKS

// @note clang refuses to compile structured binding for this expr
#ifndef __clang__
#define BROADCAST_SHAPE_SUBCASE(case_name, ...) \
SUBCASE(#case_name) \
{ \
    NMTOOLS_TESTING_DECLARE_NS(broadcast_shape, case_name); \
    using namespace args; \
    const auto [success, newshape] = RUN_broadcast_shape(case_name,__VA_ARGS__); \
    NMTOOLS_ASSERT_EQUAL( success, expect::success ); \
    if (expect::success) \
        NMTOOLS_ASSERT_EQUAL( newshape, expect::expected ); \
}
#else
#define BROADCAST_SHAPE_SUBCASE(case_name, ...) \
SUBCASE(#case_name) \
{ \
    NMTOOLS_TESTING_DECLARE_NS(broadcast_shape, case_name); \
    using namespace args; \
    auto results  = RUN_broadcast_shape(case_name,__VA_ARGS__); \
    auto success  = nmtools::get<0>(results); \
    auto newshape = nmtools::get<1>(results); \
    NMTOOLS_ASSERT_EQUAL( success, expect::success ); \
    if (expect::success) \
        NMTOOLS_ASSERT_EQUAL( newshape, expect::expected ); \
}
#endif

TEST_CASE("broadcast_shape(case1)" * doctest::test_suite("index::broadcast_shape"))
{
    BROADCAST_SHAPE_SUBCASE(case1, a_a, b_a);
    // BROADCAST_SHAPE_SUBCASE(case1, a_t, b_t);
    BROADCAST_SHAPE_SUBCASE(case1, a_v, b_v);
    BROADCAST_SHAPE_SUBCASE(case1, a_h, b_h);

    // BROADCAST_SHAPE_SUBCASE(case1, a_t, b_a);
    BROADCAST_SHAPE_SUBCASE(case1, a_v, b_a);
    BROADCAST_SHAPE_SUBCASE(case1, a_h, b_a);

    BROADCAST_SHAPE_SUBCASE(case1, a_a, b_v);
    // BROADCAST_SHAPE_SUBCASE(case1, a_t, b_v);
    BROADCAST_SHAPE_SUBCASE(case1, a_h, b_v);

    // BROADCAST_SHAPE_SUBCASE(case1, a_a, b_t);
    // BROADCAST_SHAPE_SUBCASE(case1, a_v, b_t);
    // BROADCAST_SHAPE_SUBCASE(case1, a_h, b_t);

    BROADCAST_SHAPE_SUBCASE(case1, a_a, b_h);
    // BROADCAST_SHAPE_SUBCASE(case1, a_t, b_h);
    BROADCAST_SHAPE_SUBCASE(case1, a_v, b_h);
}

TEST_CASE("broadcast_shape(case2)" * doctest::test_suite("index::broadcast_shape"))
{
    BROADCAST_SHAPE_SUBCASE(case2, a_a, b_a);
    // BROADCAST_SHAPE_SUBCASE(case2, a_t, b_t);
    BROADCAST_SHAPE_SUBCASE(case2, a_v, b_v);
    BROADCAST_SHAPE_SUBCASE(case2, a_h, b_h);

    // BROADCAST_SHAPE_SUBCASE(case2, a_t, b_a);
    BROADCAST_SHAPE_SUBCASE(case2, a_v, b_a);
    BROADCAST_SHAPE_SUBCASE(case2, a_h, b_a);

    BROADCAST_SHAPE_SUBCASE(case2, a_a, b_v);
    // BROADCAST_SHAPE_SUBCASE(case2, a_t, b_v);
    BROADCAST_SHAPE_SUBCASE(case2, a_h, b_v);

    // BROADCAST_SHAPE_SUBCASE(case2, a_a, b_t);
    // BROADCAST_SHAPE_SUBCASE(case2, a_v, b_t);
    // BROADCAST_SHAPE_SUBCASE(case2, a_h, b_t);

    BROADCAST_SHAPE_SUBCASE(case2, a_a, b_h);
    // BROADCAST_SHAPE_SUBCASE(case2, a_t, b_h);
    BROADCAST_SHAPE_SUBCASE(case2, a_v, b_h);
}

TEST_CASE("broadcast_shape(case3)" * doctest::test_suite("index::broadcast_shape"))
{
    BROADCAST_SHAPE_SUBCASE(case3, a_a, b_a);
    // BROADCAST_SHAPE_SUBCASE(case3, a_t, b_t);
    BROADCAST_SHAPE_SUBCASE(case3, a_v, b_v);
    BROADCAST_SHAPE_SUBCASE(case3, a_h, b_h);

    // BROADCAST_SHAPE_SUBCASE(case3, a_t, b_a);
    BROADCAST_SHAPE_SUBCASE(case3, a_v, b_a);
    BROADCAST_SHAPE_SUBCASE(case3, a_h, b_a);

    BROADCAST_SHAPE_SUBCASE(case3, a_a, b_v);
    // BROADCAST_SHAPE_SUBCASE(case3, a_t, b_v);
    BROADCAST_SHAPE_SUBCASE(case3, a_h, b_v);

    // BROADCAST_SHAPE_SUBCASE(case3, a_a, b_t);
    // BROADCAST_SHAPE_SUBCASE(case3, a_v, b_t);
    // BROADCAST_SHAPE_SUBCASE(case3, a_h, b_t);

    BROADCAST_SHAPE_SUBCASE(case3, a_a, b_h);
    // BROADCAST_SHAPE_SUBCASE(case3, a_t, b_h);
    BROADCAST_SHAPE_SUBCASE(case3, a_v, b_h);
}

TEST_CASE("broadcast_shape(case4)" * doctest::test_suite("index::broadcast_shape"))
{
    BROADCAST_SHAPE_SUBCASE(case4, a_a, b_a);
    // BROADCAST_SHAPE_SUBCASE(case4, a_t, b_t);
    BROADCAST_SHAPE_SUBCASE(case4, a_v, b_v);
    BROADCAST_SHAPE_SUBCASE(case4, a_h, b_h);

    // BROADCAST_SHAPE_SUBCASE(case4, a_t, b_a);
    BROADCAST_SHAPE_SUBCASE(case4, a_v, b_a);
    BROADCAST_SHAPE_SUBCASE(case4, a_h, b_a);

    BROADCAST_SHAPE_SUBCASE(case4, a_a, b_v);
    // BROADCAST_SHAPE_SUBCASE(case4, a_t, b_v);
    BROADCAST_SHAPE_SUBCASE(case4, a_h, b_v);

    // BROADCAST_SHAPE_SUBCASE(case4, a_a, b_t);
    // BROADCAST_SHAPE_SUBCASE(case4, a_v, b_t);
    // BROADCAST_SHAPE_SUBCASE(case4, a_h, b_t);

    BROADCAST_SHAPE_SUBCASE(case4, a_a, b_h);
    // BROADCAST_SHAPE_SUBCASE(case4, a_t, b_h);
    BROADCAST_SHAPE_SUBCASE(case4, a_v, b_h);
}

TEST_CASE("broadcast_shape(case5)" * doctest::test_suite("index::broadcast_shape"))
{
    BROADCAST_SHAPE_SUBCASE(case5, a_a, b_a);
    // BROADCAST_SHAPE_SUBCASE(case5, a_t, b_t);
    BROADCAST_SHAPE_SUBCASE(case5, a_v, b_v);
    BROADCAST_SHAPE_SUBCASE(case5, a_h, b_h);

    // BROADCAST_SHAPE_SUBCASE(case5, a_t, b_a);
    BROADCAST_SHAPE_SUBCASE(case5, a_v, b_a);
    BROADCAST_SHAPE_SUBCASE(case5, a_h, b_a);

    BROADCAST_SHAPE_SUBCASE(case5, a_a, b_v);
    // BROADCAST_SHAPE_SUBCASE(case5, a_t, b_v);
    BROADCAST_SHAPE_SUBCASE(case5, a_h, b_v);

    // BROADCAST_SHAPE_SUBCASE(case5, a_a, b_t);
    // BROADCAST_SHAPE_SUBCASE(case5, a_v, b_t);
    // BROADCAST_SHAPE_SUBCASE(case5, a_h, b_t);

    BROADCAST_SHAPE_SUBCASE(case5, a_a, b_h);
    // BROADCAST_SHAPE_SUBCASE(case5, a_t, b_h);
    BROADCAST_SHAPE_SUBCASE(case5, a_v, b_h);
}

TEST_CASE("broadcast_shape(case6)" * doctest::test_suite("index::broadcast_shape"))
{
    BROADCAST_SHAPE_SUBCASE(case6, a_a, b_a);
    // BROADCAST_SHAPE_SUBCASE(case6, a_t, b_t);
    BROADCAST_SHAPE_SUBCASE(case6, a_v, b_v);
    BROADCAST_SHAPE_SUBCASE(case6, a_h, b_h);

    // BROADCAST_SHAPE_SUBCASE(case6, a_t, b_a);
    BROADCAST_SHAPE_SUBCASE(case6, a_v, b_a);
    BROADCAST_SHAPE_SUBCASE(case6, a_h, b_a);

    BROADCAST_SHAPE_SUBCASE(case6, a_a, b_v);
    // BROADCAST_SHAPE_SUBCASE(case6, a_t, b_v);
    BROADCAST_SHAPE_SUBCASE(case6, a_h, b_v);

    // BROADCAST_SHAPE_SUBCASE(case6, a_a, b_t);
    // BROADCAST_SHAPE_SUBCASE(case6, a_v, b_t);
    // BROADCAST_SHAPE_SUBCASE(case6, a_h, b_t);

    BROADCAST_SHAPE_SUBCASE(case6, a_a, b_h);
    // BROADCAST_SHAPE_SUBCASE(case6, a_t, b_h);
    BROADCAST_SHAPE_SUBCASE(case6, a_v, b_h);
}

TEST_CASE("broadcast_shape(case7)" * doctest::test_suite("index::broadcast_shape"))
{
    BROADCAST_SHAPE_SUBCASE(case7, a_a, b_a);
    // BROADCAST_SHAPE_SUBCASE(case7, a_t, b_t);
    BROADCAST_SHAPE_SUBCASE(case7, a_v, b_v);
    BROADCAST_SHAPE_SUBCASE(case7, a_h, b_h);

    // BROADCAST_SHAPE_SUBCASE(case7, a_t, b_a);
    BROADCAST_SHAPE_SUBCASE(case7, a_v, b_a);
    BROADCAST_SHAPE_SUBCASE(case7, a_h, b_a);

    BROADCAST_SHAPE_SUBCASE(case7, a_a, b_v);
    // BROADCAST_SHAPE_SUBCASE(case7, a_t, b_v);
    BROADCAST_SHAPE_SUBCASE(case7, a_h, b_v);

    // BROADCAST_SHAPE_SUBCASE(case7, a_a, b_t);
    // BROADCAST_SHAPE_SUBCASE(case7, a_v, b_t);
    // BROADCAST_SHAPE_SUBCASE(case7, a_h, b_t);

    BROADCAST_SHAPE_SUBCASE(case7, a_a, b_h);
    // BROADCAST_SHAPE_SUBCASE(case7, a_t, b_h);
    BROADCAST_SHAPE_SUBCASE(case7, a_v, b_h);
}

TEST_CASE("broadcast_shape(case8)" * doctest::test_suite("index::broadcast_shape"))
{
    BROADCAST_SHAPE_SUBCASE(case8, a_a, b_a, c_a);
    // BROADCAST_SHAPE_SUBCASE(case8, a_t, b_t, c_a);
    BROADCAST_SHAPE_SUBCASE(case8, a_v, b_v, c_a);
    BROADCAST_SHAPE_SUBCASE(case8, a_h, b_h, c_a);

    // BROADCAST_SHAPE_SUBCASE(case8, a_t, b_a, c_a);
    BROADCAST_SHAPE_SUBCASE(case8, a_v, b_a, c_a);
    BROADCAST_SHAPE_SUBCASE(case8, a_h, b_a, c_a);

    BROADCAST_SHAPE_SUBCASE(case8, a_a, b_v, c_a);
    // BROADCAST_SHAPE_SUBCASE(case8, a_t, b_v, c_a);
    BROADCAST_SHAPE_SUBCASE(case8, a_h, b_v, c_a);

    // BROADCAST_SHAPE_SUBCASE(case8, a_a, b_t, c_a);
    // BROADCAST_SHAPE_SUBCASE(case8, a_v, b_t, c_a);
    // BROADCAST_SHAPE_SUBCASE(case8, a_h, b_t, c_a);

    BROADCAST_SHAPE_SUBCASE(case8, a_a, b_h, c_a);
    // BROADCAST_SHAPE_SUBCASE(case8, a_t, b_h, c_a);
    BROADCAST_SHAPE_SUBCASE(case8, a_v, b_h, c_a);

    //
    // BROADCAST_SHAPE_SUBCASE(case8, a_t, b_t, c_a);
    BROADCAST_SHAPE_SUBCASE(case8, a_v, b_v, c_a);
    BROADCAST_SHAPE_SUBCASE(case8, a_h, b_h, c_a);

    // BROADCAST_SHAPE_SUBCASE(case8, a_t, b_a, c_a);
    BROADCAST_SHAPE_SUBCASE(case8, a_v, b_a, c_a);
    BROADCAST_SHAPE_SUBCASE(case8, a_h, b_a, c_a);

    BROADCAST_SHAPE_SUBCASE(case8, a_a, b_v, c_a);
    // BROADCAST_SHAPE_SUBCASE(case8, a_t, b_v, c_a);
    BROADCAST_SHAPE_SUBCASE(case8, a_h, b_v, c_a);

    // BROADCAST_SHAPE_SUBCASE(case8, a_a, b_t, c_a);
    // BROADCAST_SHAPE_SUBCASE(case8, a_v, b_t, c_a);
    // BROADCAST_SHAPE_SUBCASE(case8, a_h, b_t, c_a);

    BROADCAST_SHAPE_SUBCASE(case8, a_a, b_h, c_a);
    // BROADCAST_SHAPE_SUBCASE(case8, a_t, b_h, c_a);
    BROADCAST_SHAPE_SUBCASE(case8, a_v, b_h, c_a);
}

TEST_CASE("broadcast_shape(case9)" * doctest::test_suite("index::broadcast_shape"))
{
    BROADCAST_SHAPE_SUBCASE(case9, a_a, b_a, c_a);
    // BROADCAST_SHAPE_SUBCASE(case9, a_t, b_t, c_a);
    BROADCAST_SHAPE_SUBCASE(case9, a_v, b_v, c_a);
    BROADCAST_SHAPE_SUBCASE(case9, a_h, b_h, c_a);

    // BROADCAST_SHAPE_SUBCASE(case9, a_t, b_a, c_a);
    BROADCAST_SHAPE_SUBCASE(case9, a_v, b_a, c_a);
    BROADCAST_SHAPE_SUBCASE(case9, a_h, b_a, c_a);

    BROADCAST_SHAPE_SUBCASE(case9, a_a, b_v, c_a);
    // BROADCAST_SHAPE_SUBCASE(case9, a_t, b_v, c_a);
    BROADCAST_SHAPE_SUBCASE(case9, a_h, b_v, c_a);

    // BROADCAST_SHAPE_SUBCASE(case9, a_a, b_t, c_a);
    // BROADCAST_SHAPE_SUBCASE(case9, a_v, b_t, c_a);
    // BROADCAST_SHAPE_SUBCASE(case9, a_h, b_t, c_a);

    BROADCAST_SHAPE_SUBCASE(case9, a_a, b_h, c_a);
    // BROADCAST_SHAPE_SUBCASE(case9, a_t, b_h, c_a);
    BROADCAST_SHAPE_SUBCASE(case9, a_v, b_h, c_a);

    //
    // BROADCAST_SHAPE_SUBCASE(case9, a_t, b_t, c_a);
    BROADCAST_SHAPE_SUBCASE(case9, a_v, b_v, c_a);
    BROADCAST_SHAPE_SUBCASE(case9, a_h, b_h, c_a);

    // BROADCAST_SHAPE_SUBCASE(case9, a_t, b_a, c_a);
    BROADCAST_SHAPE_SUBCASE(case9, a_v, b_a, c_a);
    BROADCAST_SHAPE_SUBCASE(case9, a_h, b_a, c_a);

    BROADCAST_SHAPE_SUBCASE(case9, a_a, b_v, c_a);
    // BROADCAST_SHAPE_SUBCASE(case9, a_t, b_v, c_a);
    BROADCAST_SHAPE_SUBCASE(case9, a_h, b_v, c_a);

    // BROADCAST_SHAPE_SUBCASE(case9, a_a, b_t, c_a);
    // BROADCAST_SHAPE_SUBCASE(case9, a_v, b_t, c_a);
    // BROADCAST_SHAPE_SUBCASE(case9, a_h, b_t, c_a);

    BROADCAST_SHAPE_SUBCASE(case9, a_a, b_h, c_a);
    // BROADCAST_SHAPE_SUBCASE(case9, a_t, b_h, c_a);
    BROADCAST_SHAPE_SUBCASE(case9, a_v, b_h, c_a);
}

TEST_CASE("broadcast_shape(case10)" * doctest::test_suite("index::broadcast_shape"))
{
    BROADCAST_SHAPE_SUBCASE(case10, a_a, b_a, c_a, d_a);
    // BROADCAST_SHAPE_SUBCASE(case10, a_t, b_t, c_a, d_a);
    BROADCAST_SHAPE_SUBCASE(case10, a_v, b_v, c_a, d_a);
    BROADCAST_SHAPE_SUBCASE(case10, a_h, b_h, c_a, d_a);

    // BROADCAST_SHAPE_SUBCASE(case10, a_t, b_a, c_a, d_a);
    BROADCAST_SHAPE_SUBCASE(case10, a_v, b_a, c_a, d_a);
    BROADCAST_SHAPE_SUBCASE(case10, a_h, b_a, c_a, d_a);

    BROADCAST_SHAPE_SUBCASE(case10, a_a, b_v, c_a, d_a);
    // BROADCAST_SHAPE_SUBCASE(case10, a_t, b_v, c_a, d_a);
    BROADCAST_SHAPE_SUBCASE(case10, a_h, b_v, c_a, d_a);

    // BROADCAST_SHAPE_SUBCASE(case10, a_a, b_t, c_a, d_a);
    // BROADCAST_SHAPE_SUBCASE(case10, a_v, b_t, c_a, d_a);
    // BROADCAST_SHAPE_SUBCASE(case10, a_h, b_t, c_a, d_a);

    BROADCAST_SHAPE_SUBCASE(case10, a_a, b_h, c_a, d_a);
    // BROADCAST_SHAPE_SUBCASE(case10, a_t, b_h, c_a, d_a);
    BROADCAST_SHAPE_SUBCASE(case10, a_v, b_h, c_a, d_a);

    //
    // BROADCAST_SHAPE_SUBCASE(case10, a_t, b_t, c_a, d_a);
    BROADCAST_SHAPE_SUBCASE(case10, a_v, b_v, c_a, d_a);
    BROADCAST_SHAPE_SUBCASE(case10, a_h, b_h, c_a, d_a);

    // BROADCAST_SHAPE_SUBCASE(case10, a_t, b_a, c_a, d_a);
    BROADCAST_SHAPE_SUBCASE(case10, a_v, b_a, c_a, d_a);
    BROADCAST_SHAPE_SUBCASE(case10, a_h, b_a, c_a, d_a);

    BROADCAST_SHAPE_SUBCASE(case10, a_a, b_v, c_a, d_a);
    // BROADCAST_SHAPE_SUBCASE(case10, a_t, b_v, c_a, d_a);
    BROADCAST_SHAPE_SUBCASE(case10, a_h, b_v, c_a, d_a);

    // BROADCAST_SHAPE_SUBCASE(case10, a_a, b_t, c_a, d_a);
    // BROADCAST_SHAPE_SUBCASE(case10, a_v, b_t, c_a, d_a);
    // BROADCAST_SHAPE_SUBCASE(case10, a_h, b_t, c_a, d_a);

    BROADCAST_SHAPE_SUBCASE(case10, a_a, b_h, c_a, d_a);
    // BROADCAST_SHAPE_SUBCASE(case10, a_t, b_h, c_a, d_a);
    BROADCAST_SHAPE_SUBCASE(case10, a_v, b_h, c_a, d_a);
}

TEST_CASE("broadcast_shape(case11)" * doctest::test_suite("index::broadcast_shape"))
{
    BROADCAST_SHAPE_SUBCASE(case11, a_a, b_a, c_a, d_a, e_a, f_a, g_a);
    // BROADCAST_SHAPE_SUBCASE(case11, a_t, b_t, c_a, d_a, e_a, f_a, g_a);
    BROADCAST_SHAPE_SUBCASE(case11, a_v, b_v, c_a, d_a, e_a, f_a, g_a);
    BROADCAST_SHAPE_SUBCASE(case11, a_h, b_h, c_a, d_a, e_a, f_a, g_a);

    // BROADCAST_SHAPE_SUBCASE(case11, a_t, b_a, c_a, d_a, e_a, f_a, g_a);
    BROADCAST_SHAPE_SUBCASE(case11, a_v, b_a, c_a, d_a, e_a, f_a, g_a);
    BROADCAST_SHAPE_SUBCASE(case11, a_h, b_a, c_a, d_a, e_a, f_a, g_a);

    BROADCAST_SHAPE_SUBCASE(case11, a_a, b_v, c_a, d_a, e_a, f_a, g_a);
    // BROADCAST_SHAPE_SUBCASE(case11, a_t, b_v, c_a, d_a, e_a, f_a, g_a);
    BROADCAST_SHAPE_SUBCASE(case11, a_h, b_v, c_a, d_a, e_a, f_a, g_a);

    // BROADCAST_SHAPE_SUBCASE(case11, a_a, b_t, c_a, d_a, e_a, f_a, g_a);
    // BROADCAST_SHAPE_SUBCASE(case11, a_v, b_t, c_a, d_a, e_a, f_a, g_a);
    // BROADCAST_SHAPE_SUBCASE(case11, a_h, b_t, c_a, d_a, e_a, f_a, g_a);

    BROADCAST_SHAPE_SUBCASE(case11, a_a, b_h, c_a, d_a, e_a, f_a, g_a);
    // BROADCAST_SHAPE_SUBCASE(case11, a_t, b_h, c_a, d_a, e_a, f_a, g_a);
    BROADCAST_SHAPE_SUBCASE(case11, a_v, b_h, c_a, d_a, e_a, f_a, g_a);

    //
    // BROADCAST_SHAPE_SUBCASE(case11, a_t, b_t, c_a, d_a, e_a, f_a, g_a);
    BROADCAST_SHAPE_SUBCASE(case11, a_v, b_v, c_a, d_a, e_a, f_a, g_a);
    BROADCAST_SHAPE_SUBCASE(case11, a_h, b_h, c_a, d_a, e_a, f_a, g_a);

    // BROADCAST_SHAPE_SUBCASE(case11, a_t, b_a, c_a, d_a, e_a, f_a, g_a);
    BROADCAST_SHAPE_SUBCASE(case11, a_v, b_a, c_a, d_a, e_a, f_a, g_a);
    BROADCAST_SHAPE_SUBCASE(case11, a_h, b_a, c_a, d_a, e_a, f_a, g_a);

    BROADCAST_SHAPE_SUBCASE(case11, a_a, b_v, c_a, d_a, e_a, f_a, g_a);
    // BROADCAST_SHAPE_SUBCASE(case11, a_t, b_v, c_a, d_a, e_a, f_a, g_a);
    BROADCAST_SHAPE_SUBCASE(case11, a_h, b_v, c_a, d_a, e_a, f_a, g_a);

    // BROADCAST_SHAPE_SUBCASE(case11, a_a, b_t, c_a, d_a, e_a, f_a, g_a);
    // BROADCAST_SHAPE_SUBCASE(case11, a_v, b_t, c_a, d_a, e_a, f_a, g_a);
    // BROADCAST_SHAPE_SUBCASE(case11, a_h, b_t, c_a, d_a, e_a, f_a, g_a);

    BROADCAST_SHAPE_SUBCASE(case11, a_a, b_h, c_a, d_a, e_a, f_a, g_a);
    // BROADCAST_SHAPE_SUBCASE(case11, a_t, b_h, c_a, d_a, e_a, f_a, g_a);
    BROADCAST_SHAPE_SUBCASE(case11, a_v, b_h, c_a, d_a, e_a, f_a, g_a);
}

TEST_CASE("broadcast_shape(constexpr)" * doctest::test_suite("index::broadcast_shape"))
{
    {
        constexpr int a[2] = {4,1};
        constexpr int b[3] = {8,1,3};
        constexpr int c[1] = {3};
        constexpr int d[6] = {2,2,3,1,4,1};
        constexpr int expected[6] = {2,2,3,8,4,3};
        constexpr auto broadcasted = nm::index::broadcast_shape(a,b,c,d);
        [[maybe_unused]] constexpr auto success = nm::get<0>(broadcasted);
        [[maybe_unused]] constexpr auto shape   = nm::get<1>(broadcasted);
        NMTOOLS_STATIC_ASSERT( success );
        NMTOOLS_STATIC_ASSERT_EQUAL( shape, expected );
    }
}