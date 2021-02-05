#include "nmtools/array/view/broadcast_arrays.hpp"
#include "nmtools/array/ndarray/dynamic.hpp"
#include "nmtools/array/ndarray/hybrid.hpp"
#include "nmtools/array/ndarray/fixed.hpp"
#include "nmtools/array/kind.hpp"

#include "testing/doctest.hpp"

#include <vector>
#include <array>

namespace nm = nmtools;
namespace na = nm::array;
namespace view = nm::view;
namespace kind = na::kind;

NMTOOLS_TESTING_DECLARE_CASE(broadcast_arrays)
{
    NMTOOLS_TESTING_DECLARE_ARGS(case1)
    {
        int lhs[1][3] = {
            {1,2,3}
        };
        int rhs[2][1] = {
            {4},
            {5}
        };
        auto lhs_v = cast(lhs,kind::nested_vec);
        auto rhs_v = cast(rhs,kind::nested_vec);
        auto lhs_a = cast<int>(lhs);
        auto rhs_a = cast<int>(rhs);
        auto lhs_d = cast(lhs,kind::dynamic);
        auto rhs_d = cast(rhs,kind::dynamic);
        auto lhs_f = cast(lhs,kind::fixed);
        auto rhs_f = cast(rhs,kind::fixed);
        auto lhs_h = cast(lhs,kind::hybrid);
        auto rhs_h = cast(rhs,kind::hybrid);
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case1)
    {
        int lhs[2][3] = {
            {1,2,3},
            {1,2,3},
        };
        int rhs[2][3] = {
            {4,4,4},
            {5,5,5},
        };
        auto shape = std::array{2,3};
        auto expected = std::tuple{lhs,rhs};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case2)
    {
        int lhs[3] = {1,2,3};
        int rhs[2][1] = {
            {4},
            {5}
        };
        auto lhs_v = cast(lhs,kind::nested_vec);
        auto rhs_v = cast(rhs,kind::nested_vec);
        auto lhs_a = cast<int>(lhs);
        auto rhs_a = cast<int>(rhs);
        auto lhs_d = cast(lhs,kind::dynamic);
        auto rhs_d = cast(rhs,kind::dynamic);
        auto lhs_f = cast(lhs,kind::fixed);
        auto rhs_f = cast(rhs,kind::fixed);
        auto lhs_h = cast(lhs,kind::hybrid);
        auto rhs_h = cast(rhs,kind::hybrid);
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case2)
    {
        int lhs[2][3] = {
            {1,2,3},
            {1,2,3},
        };
        int rhs[2][3] = {
            {4,4,4},
            {5,5,5},
        };
        auto shape = std::array{2,3};
        auto expected = std::tuple{lhs,rhs};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case3)
    {
        int lhs[1][3] = {
            {1,2,3}
        };
        int rhs[1][2][1] = {
            {
                {4},
                {5}
            }
        };
        auto lhs_v = cast(lhs,kind::nested_vec);
        auto rhs_v = cast(rhs,kind::nested_vec);
        auto lhs_a = cast<int>(lhs);
        auto rhs_a = cast<int>(rhs);
        auto lhs_d = cast(lhs,kind::dynamic);
        auto rhs_d = cast(rhs,kind::dynamic);
        auto lhs_f = cast(lhs,kind::fixed);
        auto rhs_f = cast(rhs,kind::fixed);
        auto lhs_h = cast(lhs,kind::hybrid);
        auto rhs_h = cast(rhs,kind::hybrid);
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case3)
    {
        int lhs[1][2][3] = {
            {
                {1,2,3},
                {1,2,3},
            }
        };
        int rhs[1][2][3] = {
            {
                {4,4,4},
                {5,5,5},
            }
        };
        auto shape = std::array{1,2,3};
        auto expected = std::tuple{lhs,rhs};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case4)
    {
        int lhs[1][3] = {
            {1,2,3}
        };
        int rhs[2][2][1] = {
            {
                {4},
                {5},
            },
            {
                {6},
                {7},
            },
        };
        auto lhs_v = cast(lhs,kind::nested_vec);
        auto rhs_v = cast(rhs,kind::nested_vec);
        auto lhs_a = cast<int>(lhs);
        auto rhs_a = cast<int>(rhs);
        auto lhs_d = cast(lhs,kind::dynamic);
        auto rhs_d = cast(rhs,kind::dynamic);
        auto lhs_f = cast(lhs,kind::fixed);
        auto rhs_f = cast(rhs,kind::fixed);
        auto lhs_h = cast(lhs,kind::hybrid);
        auto rhs_h = cast(rhs,kind::hybrid);
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case4)
    {
        int lhs[2][2][3] = {
            {
                {1,2,3},
                {1,2,3},
            },
            {
                {1,2,3},
                {1,2,3},
            },
        };
        int rhs[2][2][3] = {
            {
                {4,4,4},
                {5,5,5},
            },
            {
                {6,6,6},
                {7,7,7},
            }
        };
        auto shape = std::array{2,2,3};
        auto expected = std::tuple{lhs,rhs};
    }
}

// @note clang refuses to compile structured binding for this expr
#ifndef __clang__
#define BROADCAST_ARRAYS_SUBCASE(case_name, left, right) \
SUBCASE(#case_name) \
{ \
    NMTOOLS_TESTING_DECLARE_NS(broadcast_arrays, case_name); \
    auto [lhs, rhs] = view::broadcast_arrays(args::left, args::right); \
    NMTOOLS_ASSERT_EQUAL( lhs.shape(), expect::shape ); \
    NMTOOLS_ASSERT_EQUAL( rhs.shape(), expect::shape ); \
    NMTOOLS_ASSERT_CLOSE( lhs, expect::lhs ); \
    NMTOOLS_ASSERT_CLOSE( rhs, expect::rhs ); \
}
#else
#define BROADCAST_ARRAYS_SUBCASE(case_name, left, right) \
SUBCASE(#case_name) \
{ \
    NMTOOLS_TESTING_DECLARE_NS(broadcast_arrays, case_name); \
    auto results = view::broadcast_arrays(args::left, args::right); \
    auto lhs = std::get<0>(results); \
    auto rhs = std::get<1>(results); \
    NMTOOLS_ASSERT_EQUAL( lhs.shape(), expect::shape ); \
    NMTOOLS_ASSERT_EQUAL( rhs.shape(), expect::shape ); \
    NMTOOLS_ASSERT_CLOSE( lhs, expect::lhs ); \
    NMTOOLS_ASSERT_CLOSE( rhs, expect::rhs ); \
}
#endif

TEST_CASE("broadcast_arrays(vector)" * doctest::test_suite("view::broadcast_arrays"))
{
    BROADCAST_ARRAYS_SUBCASE(case1, lhs_v, rhs_v );
    BROADCAST_ARRAYS_SUBCASE(case2, lhs_v, rhs_v );
    BROADCAST_ARRAYS_SUBCASE(case3, lhs_v, rhs_v );
    BROADCAST_ARRAYS_SUBCASE(case4, lhs_v, rhs_v );
}

TEST_CASE("broadcast_arrays(array)" * doctest::test_suite("view::broadcast_arrays"))
{
    BROADCAST_ARRAYS_SUBCASE(case1, lhs_a, rhs_a );
    BROADCAST_ARRAYS_SUBCASE(case2, lhs_a, rhs_a );
    BROADCAST_ARRAYS_SUBCASE(case3, lhs_a, rhs_a );
    BROADCAST_ARRAYS_SUBCASE(case4, lhs_a, rhs_a );
}

TEST_CASE("broadcast_arrays(dynamic_ndarray)" * doctest::test_suite("view::broadcast_arrays"))
{
    BROADCAST_ARRAYS_SUBCASE(case1, lhs_d, rhs_d );
    BROADCAST_ARRAYS_SUBCASE(case2, lhs_d, rhs_d );
    BROADCAST_ARRAYS_SUBCASE(case3, lhs_d, rhs_d );
    BROADCAST_ARRAYS_SUBCASE(case4, lhs_d, rhs_d );
}

TEST_CASE("broadcast_arrays(fixed_ndarray)" * doctest::test_suite("view::broadcast_arrays"))
{
    BROADCAST_ARRAYS_SUBCASE(case1, lhs_f, rhs_f );
    BROADCAST_ARRAYS_SUBCASE(case2, lhs_f, rhs_f );
    BROADCAST_ARRAYS_SUBCASE(case3, lhs_f, rhs_f );
    BROADCAST_ARRAYS_SUBCASE(case4, lhs_f, rhs_f );
}

TEST_CASE("broadcast_arrays(hybrid_ndarray)" * doctest::test_suite("view::broadcast_arrays"))
{
    BROADCAST_ARRAYS_SUBCASE(case1, lhs_h, rhs_h );
    BROADCAST_ARRAYS_SUBCASE(case2, lhs_h, rhs_h );
    BROADCAST_ARRAYS_SUBCASE(case3, lhs_f, rhs_f );
    BROADCAST_ARRAYS_SUBCASE(case4, lhs_f, rhs_f );
}