#include "nmtools/array/index/broadcast_to.hpp"
#include "nmtools/array/ndarray/dynamic.hpp"
#include "nmtools/array/ndarray/hybrid.hpp"
#include "nmtools/array/ndarray/fixed.hpp"
#include "testing/doctest.hpp"

#include <vector>
#include <array>
#include <tuple>

namespace nm = nmtools;
namespace na = nm::array;
namespace meta = nm::meta;

NMTOOLS_TESTING_DECLARE_CASE(broadcast_to)
{
    NMTOOLS_TESTING_DECLARE_ARGS(case1)
    {
        int ashape[2] = {3,1};
        int bshape[2] = {3,1};
        auto a_vector = cast<std::vector<int>>(ashape);
        auto b_vector = cast<std::vector<int>>(bshape);
        auto a_array  = cast<std::array<int,2>>(ashape);
        auto b_array  = cast<std::array<int,2>>(bshape);
        auto a_fixed_vector = cast<na::fixed_vector<int,2>>(ashape);
        auto b_fixed_vector = cast<na::fixed_vector<int,2>>(bshape);
        auto a_hybrid_ndarray = cast<na::hybrid_ndarray<int,2,1>>(ashape);
        auto b_hybrid_ndarray = cast<na::hybrid_ndarray<int,2,1>>(bshape);
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case1)
    {
        auto success = true;
        auto shape   = std::array{3,1};
        auto free    = std::array{false,false};
        auto results = std::tuple{success,shape,free};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case2)
    {
        int ashape[2] = {3,1};
        int bshape[2] = {3,3};
        auto a_vector = cast<std::vector<int>>(ashape);
        auto b_vector = cast<std::vector<int>>(bshape);
        auto a_array  = cast<std::array<int,2>>(ashape);
        auto b_array  = cast<std::array<int,2>>(bshape);
        auto a_fixed_vector = cast<na::fixed_vector<int,2>>(ashape);
        auto b_fixed_vector = cast<na::fixed_vector<int,2>>(bshape);
        auto a_hybrid_ndarray = cast<na::hybrid_ndarray<int,2,1>>(ashape);
        auto b_hybrid_ndarray = cast<na::hybrid_ndarray<int,2,1>>(bshape);
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case2)
    {
        auto success = true;
        auto shape   = std::array{3,3};
        auto free    = std::array{false,true};
        auto results = std::tuple{success,shape,free};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case3)
    {
        int ashape[2] = {3,1};
        int bshape[3] = {3,3,1};
        auto a_vector = cast<std::vector<int>>(ashape);
        auto b_vector = cast<std::vector<int>>(bshape);
        auto a_array  = cast<std::array<int,2>>(ashape);
        auto b_array  = cast<std::array<int,3>>(bshape);
        auto a_fixed_vector = cast<na::fixed_vector<int,2>>(ashape);
        auto b_fixed_vector = cast<na::fixed_vector<int,3>>(bshape);
        auto a_hybrid_ndarray = cast<na::hybrid_ndarray<int,2,1>>(ashape);
        auto b_hybrid_ndarray = cast<na::hybrid_ndarray<int,3,1>>(bshape);
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case3)
    {
        auto success = true;
        auto shape   = std::array{3,3,1};
        auto free    = std::array{true,false,false};
        auto results = std::tuple{success,shape,free};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case4)
    {
        int ashape[2] = {3,1};
        int bshape[3] = {3,3,6};
        auto a_vector = cast<std::vector<int>>(ashape);
        auto b_vector = cast<std::vector<int>>(bshape);
        auto a_array  = cast<std::array<int,2>>(ashape);
        auto b_array  = cast<std::array<int,3>>(bshape);
        auto a_fixed_vector = cast<na::fixed_vector<int,2>>(ashape);
        auto b_fixed_vector = cast<na::fixed_vector<int,3>>(bshape);
        auto a_hybrid_ndarray = cast<na::hybrid_ndarray<int,2,1>>(ashape);
        auto b_hybrid_ndarray = cast<na::hybrid_ndarray<int,3,1>>(bshape);
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case4)
    {
        auto success = true;
        auto shape   = std::array{3,3,6};
        auto free    = std::array{true,false,true};
        auto results = std::tuple{success,shape,free};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case5)
    {
        int ashape[2] = {3,1};
        int bshape[1] = {3};
        auto a_vector = cast<std::vector<int>>(ashape);
        auto b_vector = cast<std::vector<int>>(bshape);
        auto a_array  = cast<std::array<int,2>>(ashape);
        auto b_array  = cast<std::array<int,1>>(bshape);
        auto a_fixed_vector = cast<na::fixed_vector<int,2>>(ashape);
        auto b_fixed_vector = cast<na::fixed_vector<int,1>>(bshape);
        auto a_hybrid_ndarray = cast<na::hybrid_ndarray<int,2,1>>(ashape);
        auto b_hybrid_ndarray = cast<na::hybrid_ndarray<int,1,1>>(bshape);
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case5)
    {
        auto success = false;
        auto shape   = std::array{0};
        auto free    = std::array{false};
        auto results = std::tuple{success,shape,free};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case6)
    {
        int ashape[2] = {3,1};
        int bshape[3] = {3,6,6};
        auto a_vector = cast<std::vector<int>>(ashape);
        auto b_vector = cast<std::vector<int>>(bshape);
        auto a_array  = cast<std::array<int,2>>(ashape);
        auto b_array  = cast<std::array<int,3>>(bshape);
        auto a_fixed_vector = cast<na::fixed_vector<int,2>>(ashape);
        auto b_fixed_vector = cast<na::fixed_vector<int,3>>(bshape);
        auto a_hybrid_ndarray = cast<na::hybrid_ndarray<int,2,1>>(ashape);
        auto b_hybrid_ndarray = cast<na::hybrid_ndarray<int,3,1>>(bshape);
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case6)
    {
        auto success = false;
        auto shape   = std::array{0,0,6};
        auto free    = std::array{false,false,true};
        auto results = std::tuple{success,shape,free};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case7)
    {
        int ashape[2] = {3,1};
        int bshape[4] = {7,3,3,6};
        auto a_vector = cast<std::vector<int>>(ashape);
        auto b_vector = cast<std::vector<int>>(bshape);
        auto a_array  = cast<std::array<int,2>>(ashape);
        auto b_array  = cast<std::array<int,4>>(bshape);
        auto a_fixed_vector = cast<na::fixed_vector<int,2>>(ashape);
        auto b_fixed_vector = cast<na::fixed_vector<int,4>>(bshape);
        auto a_hybrid_ndarray = cast<na::hybrid_ndarray<int,2,1>>(ashape);
        auto b_hybrid_ndarray = cast<na::hybrid_ndarray<int,4,1>>(bshape);
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case7)
    {
        auto success = true;
        auto shape   = std::array{7,3,3,6};
        auto free    = std::array{true,true,false,true};
        auto results = std::tuple{success,shape,free};
    }
}

// @note clang refuses to compile structured binding for this expr
#ifndef __clang__
#define BROADCAST_TO_SUBCASE(case_name, ashape, bshape) \
SUBCASE(#case_name) \
{ \
    NMTOOLS_TESTING_DECLARE_NS(broadcast_to, case_name); \
    auto [success, shape, free] = nm::index::broadcast_to(args::ashape, args::bshape); \
    NMTOOLS_ASSERT_EQUAL( success, expect::success ); \
    NMTOOLS_ASSERT_EQUAL( shape, expect::shape ); \
    NMTOOLS_ASSERT_EQUAL( free, expect::free ); \
}
#else
#define BROADCAST_TO_SUBCASE(case_name, ashape, bshape) \
SUBCASE(#case_name) \
{ \
    NMTOOLS_TESTING_DECLARE_NS(broadcast_to, case_name); \
    auto results = nm::index::broadcast_to(args::ashape, args::bshape); \
    auto success = std::get<0>(results); \
    auto shape   = std::get<1>(results); \
    auto free    = std::get<2>(results); \
    NMTOOLS_ASSERT_EQUAL( success, expect::success ); \
    NMTOOLS_ASSERT_EQUAL( shape, expect::shape ); \
    NMTOOLS_ASSERT_EQUAL( free, expect::free ); \
}
#endif

TEST_CASE("broadcast_to(vector)" * doctest::test_suite("index::broadcast_to"))
{
    BROADCAST_TO_SUBCASE(case1, a_vector, b_vector);
    BROADCAST_TO_SUBCASE(case2, a_vector, b_vector);
    BROADCAST_TO_SUBCASE(case3, a_vector, b_vector);
    BROADCAST_TO_SUBCASE(case4, a_vector, b_vector);
    BROADCAST_TO_SUBCASE(case5, a_vector, b_vector);
    BROADCAST_TO_SUBCASE(case6, a_vector, b_vector);
    BROADCAST_TO_SUBCASE(case7, a_vector, b_vector);
}

TEST_CASE("broadcast_to(array)" * doctest::test_suite("index::broadcast_to"))
{
    BROADCAST_TO_SUBCASE(case1, a_array, b_array);
    BROADCAST_TO_SUBCASE(case2, a_array, b_array);
    BROADCAST_TO_SUBCASE(case3, a_array, b_array);
    BROADCAST_TO_SUBCASE(case4, a_array, b_array);
    BROADCAST_TO_SUBCASE(case5, a_array, b_array);
    BROADCAST_TO_SUBCASE(case6, a_array, b_array);
    BROADCAST_TO_SUBCASE(case7, a_array, b_array);
}

// TEST_CASE("broadcast_to(fixed_vector)" * doctest::test_suite("index::broadcast_to"))
// {
//     BROADCAST_TO_SUBCASE(case1, a_fixed_vector, b_fixed_vector);
//     BROADCAST_TO_SUBCASE(case2, a_fixed_vector, b_fixed_vector);
//     BROADCAST_TO_SUBCASE(case3, a_fixed_vector, b_fixed_vector);
//     BROADCAST_TO_SUBCASE(case4, a_fixed_vector, b_fixed_vector);
//     BROADCAST_TO_SUBCASE(case5, a_fixed_vector, b_fixed_vector);
//     BROADCAST_TO_SUBCASE(case6, a_fixed_vector, b_fixed_vector);
//     BROADCAST_TO_SUBCASE(case7, a_fixed_vector, b_fixed_vector);
// }

TEST_CASE("broadcast_to(hybrid_ndarray)" * doctest::test_suite("index::broadcast_to"))
{
    BROADCAST_TO_SUBCASE(case1, a_hybrid_ndarray, b_hybrid_ndarray);
    BROADCAST_TO_SUBCASE(case2, a_hybrid_ndarray, b_hybrid_ndarray);
    BROADCAST_TO_SUBCASE(case3, a_hybrid_ndarray, b_hybrid_ndarray);
    BROADCAST_TO_SUBCASE(case4, a_hybrid_ndarray, b_hybrid_ndarray);
    BROADCAST_TO_SUBCASE(case5, a_hybrid_ndarray, b_hybrid_ndarray);
    BROADCAST_TO_SUBCASE(case6, a_hybrid_ndarray, b_hybrid_ndarray);
    BROADCAST_TO_SUBCASE(case7, a_hybrid_ndarray, b_hybrid_ndarray);
}