#include "nmtools/array/index/broadcast_shape.hpp"
#include "nmtools/array/ndarray/hybrid.hpp"
#include "nmtools/array/index/as_tuple.hpp"
#include "testing/doctest.hpp"

#include <vector>
#include <array>
#include <tuple>

namespace nm = nmtools;
namespace na = nm::array;
namespace meta = nm::meta;

NMTOOLS_TESTING_DECLARE_CASE(broadcast_shape)
{
    NMTOOLS_TESTING_DECLARE_ARGS(case1)
    {
        int a[2] = {5,4};
        int b[1] = {1};
        auto a_v = cast<std::vector<int>>(a);
        auto b_v = cast<std::vector<int>>(b);
        auto a_a = cast<int>(a);
        auto b_a = cast<int>(b);
        auto a_h = cast<na::hybrid_ndarray<int,2,1>>(a);
        auto b_h = cast<na::hybrid_ndarray<int,1,1>>(b);
        auto a_t = nm::index::as_tuple(a_a);
        auto b_t = nm::index::as_tuple(b_a);
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
        auto a_v = cast<std::vector<int>>(a);
        auto b_v = cast<std::vector<int>>(b);
        auto a_a = cast<int>(a);
        auto b_a = cast<int>(b);
        auto a_h = cast<na::hybrid_ndarray<int,1,1>>(a);
        auto b_h = cast<na::hybrid_ndarray<int,2,1>>(b);
        auto a_t = nm::index::as_tuple(a_a);
        auto b_t = nm::index::as_tuple(b_a);
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
        auto a_v = cast<std::vector<int>>(a);
        auto b_v = cast<std::vector<int>>(b);
        auto a_a = cast<int>(a);
        auto b_a = cast<int>(b);
        auto a_h = cast<na::hybrid_ndarray<int,1,1>>(a);
        auto b_h = cast<na::hybrid_ndarray<int,2,1>>(b);
        auto a_t = nm::index::as_tuple(a_a);
        auto b_t = nm::index::as_tuple(b_a);
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
        auto a_v = cast<std::vector<int>>(a);
        auto b_v = cast<std::vector<int>>(b);
        auto a_a = cast<int>(a);
        auto b_a = cast<int>(b);
        auto a_h = cast<na::hybrid_ndarray<int,4,1>>(a);
        auto b_h = cast<na::hybrid_ndarray<int,3,1>>(b);
        auto a_t = nm::index::as_tuple(a_a);
        auto b_t = nm::index::as_tuple(b_a);
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
        auto a_v = cast<std::vector<int>>(a);
        auto b_v = cast<std::vector<int>>(b);
        auto a_a = cast<int>(a);
        auto b_a = cast<int>(b);
        auto a_h = cast<na::hybrid_ndarray<int,3,1>>(a);
        auto b_h = cast<na::hybrid_ndarray<int,1,1>>(b);
        auto a_t = nm::index::as_tuple(a_a);
        auto b_t = nm::index::as_tuple(b_a);
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
        auto a_v = cast<std::vector<int>>(a);
        auto b_v = cast<std::vector<int>>(b);
        auto a_a = cast<int>(a);
        auto b_a = cast<int>(b);
        auto a_h = cast<na::hybrid_ndarray<int,1,1>>(a);
        auto b_h = cast<na::hybrid_ndarray<int,2,1>>(b);
        auto a_t = nm::index::as_tuple(a_a);
        auto b_t = nm::index::as_tuple(b_a);
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
        auto a_v = cast<std::vector<int>>(a);
        auto b_v = cast<std::vector<int>>(b);
        auto a_a = cast<int>(a);
        auto b_a = cast<int>(b);
        auto a_h = cast<na::hybrid_ndarray<int,2,1>>(a);
        auto b_h = cast<na::hybrid_ndarray<int,3,1>>(b);
        auto a_t = nm::index::as_tuple(a_a);
        auto b_t = nm::index::as_tuple(b_a);
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case7)
    {
        bool success = false;
        int expected[3] = {0,0,0};
    }
}

// @note clang refuses to compile structured binding for this expr
#ifndef __clang__
#define BROADCAST_SHAPE_SUBCASE(case_name, a, b) \
SUBCASE(#case_name) \
{ \
    NMTOOLS_TESTING_DECLARE_NS(broadcast_shape, case_name); \
    auto [success, newshape] = nm::index::broadcast_shape(args::a,args::b); \
    NMTOOLS_ASSERT_EQUAL( success, expect::success ); \
    if (expect::success) \
        NMTOOLS_ASSERT_EQUAL( newshape, expect::expected ); \
}
#else
#define BROADCAST_SHAPE_SUBCASE(case_name, a, b) \
SUBCASE(#case_name) \
{ \
    NMTOOLS_TESTING_DECLARE_NS(broadcast_shape, case_name); \
    auto results  = nm::index::broadcast_shape(args::a,args::b); \
    auto success  = std::get<0>(results); \
    auto newshape = std::get<1>(results); \
    NMTOOLS_ASSERT_EQUAL( success, expect::success ); \
    if (expect::success) \
        NMTOOLS_ASSERT_EQUAL( newshape, expect::expected ); \
}
#endif

TEST_CASE("broadcast_shape(vector)" * doctest::test_suite("index::broadcast_shape"))
{
    BROADCAST_SHAPE_SUBCASE(case1, a_v, b_v);
    BROADCAST_SHAPE_SUBCASE(case2, a_v, b_v);
    BROADCAST_SHAPE_SUBCASE(case3, a_v, b_v);
    BROADCAST_SHAPE_SUBCASE(case4, a_v, b_v);
    BROADCAST_SHAPE_SUBCASE(case5, a_v, b_v);
    BROADCAST_SHAPE_SUBCASE(case6, a_v, b_v);
    BROADCAST_SHAPE_SUBCASE(case7, a_v, b_v);

    BROADCAST_SHAPE_SUBCASE(case1, a_v, b_a);
    BROADCAST_SHAPE_SUBCASE(case2, a_v, b_a);
    BROADCAST_SHAPE_SUBCASE(case3, a_v, b_a);
    BROADCAST_SHAPE_SUBCASE(case4, a_v, b_a);
    BROADCAST_SHAPE_SUBCASE(case5, a_v, b_a);
    BROADCAST_SHAPE_SUBCASE(case6, a_v, b_a);
    BROADCAST_SHAPE_SUBCASE(case7, a_v, b_a);

    BROADCAST_SHAPE_SUBCASE(case1, a_v, b_h);
    BROADCAST_SHAPE_SUBCASE(case2, a_v, b_h);
    BROADCAST_SHAPE_SUBCASE(case3, a_v, b_h);
    BROADCAST_SHAPE_SUBCASE(case4, a_v, b_h);
    BROADCAST_SHAPE_SUBCASE(case5, a_v, b_h);
    BROADCAST_SHAPE_SUBCASE(case6, a_v, b_h);
    BROADCAST_SHAPE_SUBCASE(case7, a_v, b_h);
}

TEST_CASE("broadcast_shape(array)" * doctest::test_suite("index::broadcast_shape"))
{
    BROADCAST_SHAPE_SUBCASE(case1, a_a, b_v);
    BROADCAST_SHAPE_SUBCASE(case2, a_a, b_v);
    BROADCAST_SHAPE_SUBCASE(case3, a_a, b_v);
    BROADCAST_SHAPE_SUBCASE(case4, a_a, b_v);
    BROADCAST_SHAPE_SUBCASE(case5, a_a, b_v);
    BROADCAST_SHAPE_SUBCASE(case6, a_a, b_v);
    BROADCAST_SHAPE_SUBCASE(case7, a_a, b_v);

    BROADCAST_SHAPE_SUBCASE(case1, a_a, b_a);
    BROADCAST_SHAPE_SUBCASE(case2, a_a, b_a);
    BROADCAST_SHAPE_SUBCASE(case3, a_a, b_a);
    BROADCAST_SHAPE_SUBCASE(case4, a_a, b_a);
    BROADCAST_SHAPE_SUBCASE(case5, a_a, b_a);
    BROADCAST_SHAPE_SUBCASE(case6, a_a, b_a);
    BROADCAST_SHAPE_SUBCASE(case7, a_a, b_a);

    BROADCAST_SHAPE_SUBCASE(case1, a_a, b_h);
    BROADCAST_SHAPE_SUBCASE(case2, a_a, b_h);
    BROADCAST_SHAPE_SUBCASE(case3, a_a, b_h);
    BROADCAST_SHAPE_SUBCASE(case4, a_a, b_h);
    BROADCAST_SHAPE_SUBCASE(case5, a_a, b_h);
    BROADCAST_SHAPE_SUBCASE(case6, a_a, b_h);
    BROADCAST_SHAPE_SUBCASE(case7, a_a, b_h);
}

TEST_CASE("broadcast_shape(tuple)" * doctest::test_suite("index::broadcast_shape"))
{
    BROADCAST_SHAPE_SUBCASE(case1, a_t, b_v);
    BROADCAST_SHAPE_SUBCASE(case2, a_t, b_v);
    BROADCAST_SHAPE_SUBCASE(case3, a_t, b_v);
    BROADCAST_SHAPE_SUBCASE(case4, a_t, b_v);
    BROADCAST_SHAPE_SUBCASE(case5, a_t, b_v);
    BROADCAST_SHAPE_SUBCASE(case6, a_t, b_v);
    BROADCAST_SHAPE_SUBCASE(case7, a_t, b_v);

    BROADCAST_SHAPE_SUBCASE(case1, a_t, b_a);
    BROADCAST_SHAPE_SUBCASE(case2, a_t, b_a);
    BROADCAST_SHAPE_SUBCASE(case3, a_t, b_a);
    BROADCAST_SHAPE_SUBCASE(case4, a_t, b_a);
    BROADCAST_SHAPE_SUBCASE(case5, a_t, b_a);
    BROADCAST_SHAPE_SUBCASE(case6, a_t, b_a);
    BROADCAST_SHAPE_SUBCASE(case7, a_t, b_a);

    BROADCAST_SHAPE_SUBCASE(case1, a_t, b_h);
    BROADCAST_SHAPE_SUBCASE(case2, a_t, b_h);
    BROADCAST_SHAPE_SUBCASE(case3, a_t, b_h);
    BROADCAST_SHAPE_SUBCASE(case4, a_t, b_h);
    BROADCAST_SHAPE_SUBCASE(case5, a_t, b_h);
    BROADCAST_SHAPE_SUBCASE(case6, a_t, b_h);
    BROADCAST_SHAPE_SUBCASE(case7, a_t, b_h);

    BROADCAST_SHAPE_SUBCASE(case1, a_t, b_t);
    BROADCAST_SHAPE_SUBCASE(case2, a_t, b_t);
    BROADCAST_SHAPE_SUBCASE(case3, a_t, b_t);
    BROADCAST_SHAPE_SUBCASE(case4, a_t, b_t);
    BROADCAST_SHAPE_SUBCASE(case5, a_t, b_t);
    BROADCAST_SHAPE_SUBCASE(case6, a_t, b_t);
    BROADCAST_SHAPE_SUBCASE(case7, a_t, b_t);
}

TEST_CASE("broadcast_shape(hybrid_ndarray)" * doctest::test_suite("index::broadcast_shape"))
{
    BROADCAST_SHAPE_SUBCASE(case1, a_h, b_v);
    BROADCAST_SHAPE_SUBCASE(case2, a_h, b_v);
    BROADCAST_SHAPE_SUBCASE(case3, a_h, b_v);
    BROADCAST_SHAPE_SUBCASE(case4, a_h, b_v);
    BROADCAST_SHAPE_SUBCASE(case5, a_h, b_v);
    BROADCAST_SHAPE_SUBCASE(case6, a_h, b_v);
    BROADCAST_SHAPE_SUBCASE(case7, a_h, b_v);

    BROADCAST_SHAPE_SUBCASE(case1, a_h, b_a);
    BROADCAST_SHAPE_SUBCASE(case2, a_h, b_a);
    BROADCAST_SHAPE_SUBCASE(case3, a_h, b_a);
    BROADCAST_SHAPE_SUBCASE(case4, a_h, b_a);
    BROADCAST_SHAPE_SUBCASE(case5, a_h, b_a);
    BROADCAST_SHAPE_SUBCASE(case6, a_h, b_a);
    BROADCAST_SHAPE_SUBCASE(case7, a_h, b_a);

    BROADCAST_SHAPE_SUBCASE(case1, a_h, b_h);
    BROADCAST_SHAPE_SUBCASE(case2, a_h, b_h);
    BROADCAST_SHAPE_SUBCASE(case3, a_h, b_h);
    BROADCAST_SHAPE_SUBCASE(case4, a_h, b_h);
    BROADCAST_SHAPE_SUBCASE(case5, a_h, b_h);
    BROADCAST_SHAPE_SUBCASE(case6, a_h, b_h);
    BROADCAST_SHAPE_SUBCASE(case7, a_h, b_h);
}