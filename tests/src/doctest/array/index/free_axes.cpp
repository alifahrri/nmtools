#include "nmtools/array/index/free_axes.hpp"
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

NMTOOLS_TESTING_DECLARE_CASE(free_axes)
{
    NMTOOLS_TESTING_DECLARE_ARGS(case1)
    {
        int a[2] = {5,4};
        int b[1] = {1};
        auto a_vector = cast<std::vector<int>>(a);
        auto b_vector = cast<std::vector<int>>(b);
        auto a_array  = cast<std::array<int,2>>(a);
        auto b_array  = cast<std::array<int,1>>(b);
        auto a_fixed_vector   = cast<na::fixed_vector<int,2>>(a);
        auto b_fixed_vector   = cast<na::fixed_vector<int,1>>(b);
        auto a_dynamic_vector = cast<na::dynamic_vector<int>>(a);
        auto b_dynamic_vector = cast<na::dynamic_vector<int>>(b);
        auto a_hybrid_ndarray = cast<na::hybrid_ndarray<int,2,1>>(a);
        auto b_hybrid_ndarray = cast<na::hybrid_ndarray<int,1,1>>(b);
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case1)
    {
        bool x[2] = {true, true};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case2)
    {
        int a[2] = {5,4};
        int b[1] = {4};
        auto a_vector = cast<std::vector<int>>(a);
        auto b_vector = cast<std::vector<int>>(b);
        auto a_array  = cast<std::array<int,2>>(a);
        auto b_array  = cast<std::array<int,1>>(b);
        auto a_fixed_vector   = cast<na::fixed_vector<int,2>>(a);
        auto b_fixed_vector   = cast<na::fixed_vector<int,1>>(b);
        auto a_dynamic_vector = cast<na::dynamic_vector<int>>(a);
        auto b_dynamic_vector = cast<na::dynamic_vector<int>>(b);
        auto a_hybrid_ndarray = cast<na::hybrid_ndarray<int,2,1>>(a);
        auto b_hybrid_ndarray = cast<na::hybrid_ndarray<int,1,1>>(b);
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case2)
    {
        bool x[2] = {true, false};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case3)
    {
        int a[4] = {8,7,6,5};
        int b[3] = {7,1,5};
        auto a_vector = cast<std::vector<int>>(a);
        auto b_vector = cast<std::vector<int>>(b);
        auto a_array  = cast<std::array<int,4>>(a);
        auto b_array  = cast<std::array<int,3>>(b);
        auto a_fixed_vector   = cast<na::fixed_vector<int,4>>(a);
        auto b_fixed_vector   = cast<na::fixed_vector<int,3>>(b);
        auto a_dynamic_vector = cast<na::dynamic_vector<int>>(a);
        auto b_dynamic_vector = cast<na::dynamic_vector<int>>(b);
        auto a_hybrid_ndarray = cast<na::hybrid_ndarray<int,4,1>>(a);
        auto b_hybrid_ndarray = cast<na::hybrid_ndarray<int,3,1>>(b);
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case3)
    {
        bool x[4] = {true, false, true, false};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case4)
    {
        int a[4] = {8,7,6,5};
        int b[4] = {8,1,5,1};
        auto a_vector = cast<std::vector<int>>(a);
        auto b_vector = cast<std::vector<int>>(b);
        auto a_array  = cast<std::array<int,4>>(a);
        auto b_array  = cast<std::array<int,4>>(b);
        auto a_fixed_vector   = cast<na::fixed_vector<int,4>>(a);
        auto b_fixed_vector   = cast<na::fixed_vector<int,4>>(b);
        auto a_dynamic_vector = cast<na::dynamic_vector<int>>(a);
        auto b_dynamic_vector = cast<na::dynamic_vector<int>>(b);
        auto a_hybrid_ndarray = cast<na::hybrid_ndarray<int,4,1>>(a);
        auto b_hybrid_ndarray = cast<na::hybrid_ndarray<int,4,1>>(b);
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case4)
    {
        bool x[4] = {false, true, false, true};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case5)
    {
        int a[3] = {256,256,3};
        int b[1] = {3};
        auto a_vector = cast<std::vector<int>>(a);
        auto b_vector = cast<std::vector<int>>(b);
        auto a_array  = cast<std::array<int,3>>(a);
        auto b_array  = cast<std::array<int,1>>(b);
        auto a_fixed_vector   = cast<na::fixed_vector<int,3>>(a);
        auto b_fixed_vector   = cast<na::fixed_vector<int,1>>(b);
        auto a_dynamic_vector = cast<na::dynamic_vector<int>>(a);
        auto b_dynamic_vector = cast<na::dynamic_vector<int>>(b);
        auto a_hybrid_ndarray = cast<na::hybrid_ndarray<int,3,1>>(a);
        auto b_hybrid_ndarray = cast<na::hybrid_ndarray<int,1,1>>(b);
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

#define FREE_AXES_SUBCASE(case_name, a, b) \
SUBCASE(#case_name) \
{ \
    NMTOOLS_TESTING_DECLARE_NS(free_axes, case_name); \
    auto result = nm::index::free_axes(args::a, args::b); \
    NMTOOLS_ASSERT_EQUAL(result, expect::x); \
}

TEST_CASE("free_axes(vector)" * doctest::test_suite("index::free_axes"))
{
    FREE_AXES_SUBCASE(case1, a_vector, b_vector);
    FREE_AXES_SUBCASE(case2, a_vector, b_vector);
    FREE_AXES_SUBCASE(case3, a_vector, b_vector);
    FREE_AXES_SUBCASE(case4, a_vector, b_vector);
    FREE_AXES_SUBCASE(case5, a_vector, b_vector);
}

TEST_CASE("free_axes(array)" * doctest::test_suite("index::free_axes"))
{
    FREE_AXES_SUBCASE(case1, a_array, b_array);
    FREE_AXES_SUBCASE(case2, a_array, b_array);
    FREE_AXES_SUBCASE(case3, a_array, b_array);
    FREE_AXES_SUBCASE(case4, a_array, b_array);
    FREE_AXES_SUBCASE(case5, a_array, b_array);
}

TEST_CASE("free_axes(fixed_vector)" * doctest::test_suite("index::free_axes"))
{
    FREE_AXES_SUBCASE(case1, a_fixed_vector, b_fixed_vector);
    FREE_AXES_SUBCASE(case2, a_fixed_vector, b_fixed_vector);
    FREE_AXES_SUBCASE(case3, a_fixed_vector, b_fixed_vector);
    FREE_AXES_SUBCASE(case4, a_fixed_vector, b_fixed_vector);
    FREE_AXES_SUBCASE(case5, a_fixed_vector, b_fixed_vector);
}

TEST_CASE("free_axes(dynamic_vector)" * doctest::test_suite("index::free_axes"))
{
    FREE_AXES_SUBCASE(case1, a_dynamic_vector, b_dynamic_vector);
    FREE_AXES_SUBCASE(case2, a_dynamic_vector, b_dynamic_vector);
    FREE_AXES_SUBCASE(case3, a_dynamic_vector, b_dynamic_vector);
    FREE_AXES_SUBCASE(case4, a_dynamic_vector, b_dynamic_vector);
    FREE_AXES_SUBCASE(case5, a_dynamic_vector, b_dynamic_vector);
}

TEST_CASE("free_axes(hybrid_ndarray)" * doctest::test_suite("index::free_axes"))
{
    FREE_AXES_SUBCASE(case1, a_hybrid_ndarray, b_hybrid_ndarray);
    FREE_AXES_SUBCASE(case2, a_hybrid_ndarray, b_hybrid_ndarray);
    FREE_AXES_SUBCASE(case3, a_hybrid_ndarray, b_hybrid_ndarray);
    FREE_AXES_SUBCASE(case4, a_hybrid_ndarray, b_hybrid_ndarray);
    FREE_AXES_SUBCASE(case5, a_hybrid_ndarray, b_hybrid_ndarray);
}