#include "nmtools/array/view/squeeze.hpp"
#include "nmtools/array/fixed.hpp"
#include "nmtools/array/dynamic.hpp"
#include "testing/doctest.hpp"

#include <array>
#include <tuple>
#include <vector>

namespace nm = nmtools;
namespace na = nm::array;
namespace meta = nm::meta;
namespace view = nm::view;
namespace kind = na::kind;

NMTOOLS_TESTING_DECLARE_CASE(squeeze)
{
    NMTOOLS_TESTING_DECLARE_ARGS(case1)
    {
        double array[6] = {1,2,3,4,5,6};
        auto array_a = cast<double>(array);
        auto array_v = cast(array,kind::nested_vec);
        auto array_d = cast(array,kind::dynamic);
        auto array_f = cast(array,kind::fixed);
        auto array_h = cast(array,kind::hybrid);
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case1)
    {
        int shape_[1] = {6};
        auto shape = cast<int>(shape_);
        double expected[6] = {1,2,3,4,5,6};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case2)
    {
        double array[6][1] = {
            {1},
            {2},
            {3},
            {4},
            {5},
            {6},
        };
        auto array_a = cast<double>(array);
        auto array_v = cast(array,kind::nested_vec);
        auto array_d = cast(array,kind::dynamic);
        auto array_f = cast(array,kind::fixed);
        auto array_h = cast(array,kind::hybrid);
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case2)
    {
        int shape_[1] = {6};
        auto shape = cast<int>(shape_);
        double expected[6] = {1,2,3,4,5,6};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case3)
    {
        double array[6][2] = {
            {1,1},
            {2,2},
            {3,3},
            {4,4},
            {5,5},
            {6,6},
        };
        auto array_a = cast<double>(array);
        auto array_v = cast(array,kind::nested_vec);
        auto array_d = cast(array,kind::dynamic);
        auto array_f = cast(array,kind::fixed);
        auto array_h = cast(array,kind::hybrid);
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case3)
    {
        int shape_[2] = {6,2};
        auto shape = cast<int>(shape_);
        double expected[6][2] = {
            {1,1},
            {2,2},
            {3,3},
            {4,4},
            {5,5},
            {6,6},
        };
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case4)
    {
        double array[1][6] = {
            {1,2,3,4,5,6}
        };
        auto array_a = cast<double>(array);
        auto array_v = cast(array,kind::nested_vec);
        auto array_d = cast(array,kind::dynamic);
        auto array_f = cast(array,kind::fixed);
        auto array_h = cast(array,kind::hybrid);
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case4)
    {
        int shape_[1] = {6};
        auto shape = cast<int>(shape_);
        double expected[6] = {1,2,3,4,5,6};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case5)
    {
        double array[6][1][1] = {
            {
                {1}
            },
            {
                {2}
            },
            {
                {3}
            },
            {
                {4}
            },
            {
                {5}
            },
            {
                {6}
            }
        };
        auto array_a = cast<double>(array);
        auto array_v = cast(array,kind::nested_vec);
        auto array_d = cast(array,kind::dynamic);
        auto array_f = cast(array,kind::fixed);
        auto array_h = cast(array,kind::hybrid);
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case5)
    {
        int shape_[1] = {6};
        auto shape = cast<int>(shape_);
        double expected[6] = {1,2,3,4,5,6};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case6)
    {
        double array[1][6][1] = {
            {
                {1},
                {2},
                {3},
                {4},
                {5},
                {6}
            }
        };
        auto array_a = cast<double>(array);
        auto array_v = cast(array,kind::nested_vec);
        auto array_d = cast(array,kind::dynamic);
        auto array_f = cast(array,kind::fixed);
        auto array_h = cast(array,kind::hybrid);
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case6)
    {
        int shape_[1] = {6};
        auto shape = cast<int>(shape_);
        double expected[6] = {1,2,3,4,5,6};
    }
}

#define SQUEEZE_SUBCASE(case_name, array) \
SUBCASE(#case_name) \
{ \
    NMTOOLS_TESTING_DECLARE_NS(squeeze, case_name) \
    auto array_ref = view::squeeze(args::array); \
    NMTOOLS_ASSERT_EQUAL( array_ref.shape(), expect::shape ); \
    NMTOOLS_ASSERT_CLOSE( array_ref, expect::expected ); \
}

TEST_CASE("squeeze(raw)" * doctest::test_suite("view::squeeze"))
{
    SQUEEZE_SUBCASE( case1, array );
    SQUEEZE_SUBCASE( case2, array );
    SQUEEZE_SUBCASE( case3, array );
    SQUEEZE_SUBCASE( case4, array );
    SQUEEZE_SUBCASE( case5, array );
    SQUEEZE_SUBCASE( case6, array ); 
}

TEST_CASE("squeeze(array)" * doctest::test_suite("view::squeeze"))
{
    SQUEEZE_SUBCASE( case1, array_a );
    SQUEEZE_SUBCASE( case2, array_a );
    SQUEEZE_SUBCASE( case3, array_a );
    SQUEEZE_SUBCASE( case4, array_a );
    SQUEEZE_SUBCASE( case5, array_a );
    SQUEEZE_SUBCASE( case6, array_a ); 
}

TEST_CASE("squeeze(vector)" * doctest::test_suite("view::squeeze"))
{
    SQUEEZE_SUBCASE( case1, array_v );
    SQUEEZE_SUBCASE( case2, array_v );
    SQUEEZE_SUBCASE( case3, array_v );
    SQUEEZE_SUBCASE( case4, array_v );
    SQUEEZE_SUBCASE( case5, array_v );
    SQUEEZE_SUBCASE( case6, array_v ); 
}

TEST_CASE("squeeze(fixed_ndarray)" * doctest::test_suite("view::squeeze"))
{
    SQUEEZE_SUBCASE( case1, array_f );
    SQUEEZE_SUBCASE( case2, array_f );
    SQUEEZE_SUBCASE( case3, array_f );
    SQUEEZE_SUBCASE( case4, array_f );
    SQUEEZE_SUBCASE( case5, array_f );
    SQUEEZE_SUBCASE( case6, array_f ); 
}

TEST_CASE("squeeze(dynamic_ndarray)" * doctest::test_suite("view::squeeze"))
{
    SQUEEZE_SUBCASE( case1, array_d );
    SQUEEZE_SUBCASE( case2, array_d );
    SQUEEZE_SUBCASE( case3, array_d );
    SQUEEZE_SUBCASE( case4, array_d );
    SQUEEZE_SUBCASE( case5, array_d );
    SQUEEZE_SUBCASE( case6, array_d ); 
}

TEST_CASE("squeeze(hybrid_ndarray)" * doctest::test_suite("view::squeeze"))
{
    SQUEEZE_SUBCASE( case1, array_h );
    SQUEEZE_SUBCASE( case2, array_h );
    SQUEEZE_SUBCASE( case3, array_h );
    SQUEEZE_SUBCASE( case4, array_h );
    SQUEEZE_SUBCASE( case5, array_h );
    SQUEEZE_SUBCASE( case6, array_h ); 
}