#include "nmtools/array/view/broadcast_to.hpp"
#include "nmtools/array/ndarray/dynamic.hpp"
#include "nmtools/array/ndarray/hybrid.hpp"
#include "nmtools/array/ndarray/fixed.hpp"

#include "testing/doctest.hpp"

#include <vector>
#include <array>
#include <tuple>

namespace nm = nmtools;
namespace na = nm::array;
namespace view = nm::view;

NMTOOLS_TESTING_DECLARE_CASE(broadcast_to)
{
    NMTOOLS_TESTING_DECLARE_ARGS(case1)
    {
        int x[3] = {1,2,3};
        auto shape = std::array{1,3};
        auto x_v = cast<std::vector<int>>(x);
        auto x_a = cast<int>(x);
        auto x_d = cast<na::dynamic_ndarray<int>>(x);
        auto x_h = cast<na::hybrid_ndarray<int,3,1>>(x);
        auto x_f = cast<na::fixed_ndarray<int,3>>(x);
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case1)
    {
        int expected[1][3] = {
            {1,2,3}
        };
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case2)
    {
        int x[3] = {1,2,3};
        auto shape = std::array{3,3};
        auto x_v = cast<std::vector<int>>(x);
        auto x_a = cast<int>(x);
        auto x_d = cast<na::dynamic_ndarray<int>>(x);
        auto x_h = cast<na::hybrid_ndarray<int,3,1>>(x);
        auto x_f = cast<na::fixed_ndarray<int,3>>(x);
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case2)
    {
        int expected[3][3] = {
            {1,2,3},
            {1,2,3},
            {1,2,3}
        };
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case3)
    {
        int x[3] = {1,2,3};
        auto shape = std::array{2,3,3};
        auto x_v = cast<std::vector<int>>(x);
        auto x_a = cast<int>(x);
        auto x_d = cast<na::dynamic_ndarray<int>>(x);
        auto x_h = cast<na::hybrid_ndarray<int,3,1>>(x);
        auto x_f = cast<na::fixed_ndarray<int,3>>(x);
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case3)
    {
        int expected[2][3][3] = {
            {
                {1,2,3},
                {1,2,3},
                {1,2,3},
            },
            {
                {1,2,3},
                {1,2,3},
                {1,2,3},
            },
        };
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case4)
    {
        int x[3][1] = {
            {1},
            {2},
            {3}
        };
        auto shape = std::array{3,3};
        auto x_v = cast<std::vector<std::vector<int>>>(x);
        auto x_a = cast<int>(x);
        auto x_d = cast<na::dynamic_ndarray<int>>(x);
        auto x_h = cast<na::hybrid_ndarray<int,3,2>>(x);
        auto x_f = cast<na::fixed_ndarray<int,3,1>>(x);
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case4)
    {
        int expected[3][3] = {
            {1,1,1},
            {2,2,2},
            {3,3,3}
        };
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case5)
    {
        int x[3][1] = {
            {1},
            {2},
            {3}
        };
        auto shape = std::array{2,3,3};
        auto x_v = cast<std::vector<std::vector<int>>>(x);
        auto x_a = cast<int>(x);
        auto x_d = cast<na::dynamic_ndarray<int>>(x);
        auto x_h = cast<na::hybrid_ndarray<int,3,2>>(x);
        auto x_f = cast<na::fixed_ndarray<int,3,1>>(x);
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case5)
    {
        int expected[2][3][3] = {
            {
                {1,1,1},
                {2,2,2},
                {3,3,3}
            },
            {
                {1,1,1},
                {2,2,2},
                {3,3,3}
            },
        };
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case6)
    {
        int x[1][3] = {{1,2,3}};
        auto shape = std::array{1,3};
        auto x_v = cast<std::vector<std::vector<int>>>(x);
        auto x_a = cast<int>(x);
        auto x_d = cast<na::dynamic_ndarray<int>>(x);
        auto x_h = cast<na::hybrid_ndarray<int,3,2>>(x);
        auto x_f = cast<na::fixed_ndarray<int,1,3>>(x);
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case6)
    {
        int expected[1][3] = {
            {1,2,3}
        };
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case7)
    {
        int x[1][3] = {{1,2,3}};
        auto shape = std::array{3,3};
        auto x_v = cast<std::vector<std::vector<int>>>(x);
        auto x_a = cast<int>(x);
        auto x_d = cast<na::dynamic_ndarray<int>>(x);
        auto x_h = cast<na::hybrid_ndarray<int,3,2>>(x);
        auto x_f = cast<na::fixed_ndarray<int,1,3>>(x);
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case7)
    {
        int expected[3][3] = {
            {1,2,3},
            {1,2,3},
            {1,2,3}
        };
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case8)
    {
        int x[1][3] = {{1,2,3}};
        auto shape = std::array{2,3,3};
        auto x_v = cast<std::vector<std::vector<int>>>(x);
        auto x_a = cast<int>(x);
        auto x_d = cast<na::dynamic_ndarray<int>>(x);
        auto x_h = cast<na::hybrid_ndarray<int,3,2>>(x);
        auto x_f = cast<na::fixed_ndarray<int,1,3>>(x);
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case8)
    {
        int expected[2][3][3] = {
            {
                {1,2,3},
                {1,2,3},
                {1,2,3},
            },
            {
                {1,2,3},
                {1,2,3},
                {1,2,3},
            },
        };
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case9)
    {
        int x[2][1][3] = {
            {
                {1,2,3}
            },
            {
                {4,5,6}
            },
        };
        auto shape = std::array{2,3,3};
        auto x_v = cast<std::vector<std::vector<std::vector<int>>>>(x);
        auto x_a = cast<int>(x);
        auto x_d = cast<na::dynamic_ndarray<int>>(x);
        auto x_h = cast<na::hybrid_ndarray<int,6,3>>(x);
        auto x_f = cast<na::fixed_ndarray<int,2,1,3>>(x);
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case9)
    {
        int expected[2][3][3] = {
            {
                {1,2,3},
                {1,2,3},
                {1,2,3},
            },
            {
                {4,5,6},
                {4,5,6},
                {4,5,6},
            },
        };
    }
}

#define BROADCAST_TO_SUBCASE(case_name, array, shape, expected) \
SUBCASE(#case_name) \
{ \
    NMTOOLS_TESTING_DECLARE_NS(broadcast_to, case_name); \
    auto array_ref = view::broadcast_to(args::array,args::shape); \
    NMTOOLS_ASSERT_EQUAL( array_ref.shape(), args::shape ); \
    NMTOOLS_ASSERT_CLOSE( array_ref, expect::expected ); \
}

TEST_CASE("broadcast_to(vector)" * doctest::test_suite("view::broadcast_to"))
{
    BROADCAST_TO_SUBCASE( case1, x_v, shape, expected );
    BROADCAST_TO_SUBCASE( case2, x_v, shape, expected );
    BROADCAST_TO_SUBCASE( case3, x_v, shape, expected );
    BROADCAST_TO_SUBCASE( case4, x_v, shape, expected );
    BROADCAST_TO_SUBCASE( case5, x_v, shape, expected );
    BROADCAST_TO_SUBCASE( case6, x_v, shape, expected );
    BROADCAST_TO_SUBCASE( case7, x_v, shape, expected );
    BROADCAST_TO_SUBCASE( case8, x_v, shape, expected );
    BROADCAST_TO_SUBCASE( case9, x_v, shape, expected );
}

TEST_CASE("broadcast_to(array)" * doctest::test_suite("view::broadcast_to"))
{
    BROADCAST_TO_SUBCASE( case1, x_a, shape, expected );
    BROADCAST_TO_SUBCASE( case2, x_a, shape, expected );
    BROADCAST_TO_SUBCASE( case3, x_a, shape, expected );
    BROADCAST_TO_SUBCASE( case4, x_a, shape, expected );
    BROADCAST_TO_SUBCASE( case5, x_a, shape, expected );
    BROADCAST_TO_SUBCASE( case6, x_a, shape, expected );
    BROADCAST_TO_SUBCASE( case7, x_a, shape, expected );
    BROADCAST_TO_SUBCASE( case8, x_a, shape, expected );
    BROADCAST_TO_SUBCASE( case9, x_a, shape, expected );
}
 
TEST_CASE("broadcast_to(fixed_ndarray)" * doctest::test_suite("view::broadcast_to"))
{
    BROADCAST_TO_SUBCASE( case1, x_f, shape, expected );
    BROADCAST_TO_SUBCASE( case2, x_f, shape, expected );
    BROADCAST_TO_SUBCASE( case3, x_f, shape, expected );
    BROADCAST_TO_SUBCASE( case4, x_f, shape, expected );
    BROADCAST_TO_SUBCASE( case5, x_f, shape, expected );
    BROADCAST_TO_SUBCASE( case6, x_f, shape, expected );
    BROADCAST_TO_SUBCASE( case7, x_f, shape, expected );
    BROADCAST_TO_SUBCASE( case8, x_f, shape, expected );
    BROADCAST_TO_SUBCASE( case9, x_f, shape, expected );
}

TEST_CASE("broadcast_to(dynamic_ndarray)" * doctest::test_suite("view::broadcast_to"))
{
    BROADCAST_TO_SUBCASE( case1, x_d, shape, expected );
    BROADCAST_TO_SUBCASE( case2, x_d, shape, expected );
    BROADCAST_TO_SUBCASE( case3, x_d, shape, expected );
    BROADCAST_TO_SUBCASE( case4, x_d, shape, expected );
    BROADCAST_TO_SUBCASE( case5, x_d, shape, expected );
    BROADCAST_TO_SUBCASE( case6, x_d, shape, expected );
    BROADCAST_TO_SUBCASE( case7, x_d, shape, expected );
    BROADCAST_TO_SUBCASE( case8, x_d, shape, expected );
    BROADCAST_TO_SUBCASE( case9, x_d, shape, expected );
}

TEST_CASE("broadcast_to(hybrid_ndarray)" * doctest::test_suite("view::broadcast_to"))
{
    BROADCAST_TO_SUBCASE( case1, x_h, shape, expected );
    BROADCAST_TO_SUBCASE( case2, x_h, shape, expected );
    BROADCAST_TO_SUBCASE( case3, x_h, shape, expected );
    BROADCAST_TO_SUBCASE( case4, x_h, shape, expected );
    BROADCAST_TO_SUBCASE( case5, x_h, shape, expected );
    BROADCAST_TO_SUBCASE( case6, x_h, shape, expected );
    BROADCAST_TO_SUBCASE( case7, x_h, shape, expected );
    BROADCAST_TO_SUBCASE( case8, x_h, shape, expected );
    BROADCAST_TO_SUBCASE( case9, x_h, shape, expected );
}