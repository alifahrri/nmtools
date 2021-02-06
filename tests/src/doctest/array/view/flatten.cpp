/**
 * @file flatten.cpp
 * @author Fahri Ali Rahman (ali.rahman.fahri@gmail.com)
 * @brief test file for flatten view
 * @date 2020-10-29
 * 
 * @copyright Copyright (c) 2020
 * 
 */

#include "nmtools/array/fixed.hpp"
#include "nmtools/array/dynamic.hpp"
#include "nmtools/array/view.hpp"
#include "nmtools/utils/isclose.hpp"
#include "nmtools/utils/isequal.hpp"
#include "testing/doctest.hpp"

#include <array>
#include <vector>

namespace nm = nmtools;
namespace na = nm::array;
namespace view = nm::view;
namespace meta = nm::meta;
namespace kind = na::kind;

NMTOOLS_TESTING_DECLARE_CASE(flatten)
{
    NMTOOLS_TESTING_DECLARE_ARGS(case1)
    {
        double array[3] = {1.,2.,3.};
        auto array_a = cast<double>(array);
        auto array_v = cast(array,kind::nested_vec);
        auto array_f = cast(array,kind::fixed);
        auto array_d = cast(array,kind::dynamic);
        auto array_h = cast(array,kind::hybrid);
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case1)
    {
        int shape_[1] = {3};
        auto shape = cast<int>(shape_);
        double expected[3] = {1,2,3};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case2)
    {
        double array[2][3] = {
            {1.,2.,3.},
            {3.,4.,5.},
        };
        auto array_a = cast<double>(array);
        auto array_v = cast(array,kind::nested_vec);
        auto array_f = cast(array,kind::fixed);
        auto array_d = cast(array,kind::dynamic);
        auto array_h = cast(array,kind::hybrid);
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case2)
    {
        int shape_[1] = {6};
        auto shape = cast<int>(shape_);
        double expected[6] = {1,2,3,3,4,5};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case3)
    {
        double array[2][3][1] = {
            {{1.},{2.},{3.}},
            {{3.},{4.},{5.}},
        };
        auto array_a = cast<double>(array);
        auto array_v = cast(array,kind::nested_vec);
        auto array_f = cast(array,kind::fixed);
        auto array_d = cast(array,kind::dynamic);
        auto array_h = cast(array,kind::hybrid);
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case3)
    {
        int shape_[1] = {6};
        auto shape = cast<int>(shape_);
        double expected[6] = {1,2,3,3,4,5};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case4)
    {
        double array[2][3][2] = {
            {
                {1.,6.},
                {2.,7.},
                {3.,8.}
            },
            {
                {3.,9.},
                {4.,10.},
                {5.,11.}
            },
        };
        auto array_a = cast<double>(array);
        auto array_v = cast(array,kind::nested_vec);
        auto array_f = cast(array,kind::fixed);
        auto array_d = cast(array,kind::dynamic);
        auto array_h = cast(array,kind::hybrid);
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case4)
    {
        // isequal doesnt support tuple and raw yet
        int shape_[1] = {12};
        auto shape = cast<int>(shape_);
        double expected[12] = {1,6,2,7,3,8,3,9,4,10,5,11};
    }
}

#define FLATTEN_SUBCASE(case_name, array) \
SUBCASE(#case_name) \
{ \
    NMTOOLS_TESTING_DECLARE_NS(flatten,case_name); \
    auto array_ref = view::flatten(args::array); \
    NMTOOLS_ASSERT_EQUAL( array_ref.shape(), expect::shape ); \
    NMTOOLS_ASSERT_CLOSE( array_ref, expect::expected ); \
}

TEST_CASE("flatten(raw)" * doctest::test_suite("view::flatten"))
{
    FLATTEN_SUBCASE( case1, array );
    FLATTEN_SUBCASE( case2, array );
    FLATTEN_SUBCASE( case3, array );
    FLATTEN_SUBCASE( case4, array );
}

TEST_CASE("flatten(array)" * doctest::test_suite("view::flatten"))
{
    FLATTEN_SUBCASE( case1, array_a );
    FLATTEN_SUBCASE( case2, array_a );
    FLATTEN_SUBCASE( case3, array_a );
    FLATTEN_SUBCASE( case4, array_a );
}

TEST_CASE("flatten(vector)" * doctest::test_suite("view::flatten"))
{
    FLATTEN_SUBCASE( case1, array_v );
    FLATTEN_SUBCASE( case2, array_v );
    FLATTEN_SUBCASE( case3, array_v );
    FLATTEN_SUBCASE( case4, array_v );
}

TEST_CASE("flatten(fixed_ndarray)" * doctest::test_suite("view::flatten"))
{
    FLATTEN_SUBCASE( case1, array_f );
    FLATTEN_SUBCASE( case2, array_f );
    FLATTEN_SUBCASE( case3, array_f );
    FLATTEN_SUBCASE( case4, array_f );
}

TEST_CASE("flatten(dynamic_ndarray)" * doctest::test_suite("view::flatten"))
{
    FLATTEN_SUBCASE( case1, array_d );
    FLATTEN_SUBCASE( case2, array_d );
    FLATTEN_SUBCASE( case3, array_d );
    FLATTEN_SUBCASE( case4, array_d );
}

TEST_CASE("flatten(hybrid_ndarray)" * doctest::test_suite("view::flatten"))
{
    FLATTEN_SUBCASE( case1, array_h );
    FLATTEN_SUBCASE( case2, array_h );
    FLATTEN_SUBCASE( case3, array_h );
    FLATTEN_SUBCASE( case4, array_h );
}