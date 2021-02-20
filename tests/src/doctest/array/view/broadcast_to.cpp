#include "nmtools/array/view/broadcast_to.hpp"
#include "nmtools/array/ndarray/dynamic.hpp"
#include "nmtools/array/ndarray/hybrid.hpp"
#include "nmtools/array/ndarray/fixed.hpp"
#include "nmtools/array/kind.hpp"

#include "testing/doctest.hpp"

#include <vector>
#include <array>
#include <tuple>

namespace nm = nmtools;
namespace na = nm::array;
namespace view = nm::view;
namespace kind = na::kind;

NMTOOLS_TESTING_DECLARE_CASE(broadcast_to)
{
    NMTOOLS_TESTING_DECLARE_ARGS(case1)
    {
        int x[3] = {1,2,3};
        auto shape = std::array{1,3};
        auto x_v = cast(x,kind::nested_vec);
        auto x_a = cast<int>(x);
        auto x_d = cast(x,kind::dynamic);
        auto x_h = cast(x,kind::hybrid);
        auto x_f = cast(x,kind::fixed);
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
        auto x_v = cast(x,kind::nested_vec);
        auto x_a = cast<int>(x);
        auto x_d = cast(x,kind::dynamic);
        auto x_h = cast(x,kind::hybrid);
        auto x_f = cast(x,kind::fixed);
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
        auto x_v = cast(x,kind::nested_vec);
        auto x_a = cast<int>(x);
        auto x_d = cast(x,kind::dynamic);
        auto x_h = cast(x,kind::hybrid);
        auto x_f = cast(x,kind::fixed);
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
        auto x_v = cast(x,kind::nested_vec);
        auto x_a = cast<int>(x);
        auto x_d = cast(x,kind::dynamic);
        auto x_h = cast(x,kind::hybrid);
        auto x_f = cast(x,kind::fixed);
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
        auto x_v = cast(x,kind::nested_vec);
        auto x_a = cast<int>(x);
        auto x_d = cast(x,kind::dynamic);
        auto x_h = cast(x,kind::hybrid);
        auto x_f = cast(x,kind::fixed);
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
        auto x_v = cast(x,kind::nested_vec);
        auto x_a = cast<int>(x);
        auto x_d = cast(x,kind::dynamic);
        auto x_h = cast(x,kind::hybrid);
        auto x_f = cast(x,kind::fixed);
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
        auto x_v = cast(x,kind::nested_vec);
        auto x_a = cast<int>(x);
        auto x_d = cast(x,kind::dynamic);
        auto x_h = cast(x,kind::hybrid);
        auto x_f = cast(x,kind::fixed);
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
        auto x_v = cast(x,kind::nested_vec);
        auto x_a = cast<int>(x);
        auto x_d = cast(x,kind::dynamic);
        auto x_h = cast(x,kind::hybrid);
        auto x_f = cast(x,kind::fixed);
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
        auto x_v = cast(x,kind::nested_vec);
        auto x_a = cast<int>(x);
        auto x_d = cast(x,kind::dynamic);
        auto x_h = cast(x,kind::hybrid);
        auto x_f = cast(x,kind::fixed);
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


#define RUN_impl(...) \
nm::view::broadcast_to(__VA_ARGS__);

#ifdef NMTOOLS_TESTING_ENABLE_BENCHMARKS
#include "nmtools/benchmarks/bench.hpp"
using nm::benchmarks::TrackedBench;
// create immediately invoked lambda
// that packs broadcast_to fn to callable lambda
#define RUN_broadcast_to(case_name, ...) \
[](auto&&...args){ \
    auto title = std::string("broadcast_to-") + #case_name; \
    auto name  = nm::testing::make_func_args("", args...); \
    auto fn    = [&](){ \
        return RUN_impl(args...); \
    }; \
    return TrackedBench::run(title, name, fn); \
}(__VA_ARGS__);
#else
// run normally without benchmarking, ignore case_name
#define RUN_broadcast_to(case_name, ...) \
RUN_impl(__VA_ARGS__);
#endif // NMTOOLS_TESTING_ENABLE_BENCHMARKS

#define BROADCAST_TO_SUBCASE(case_name, array, shape, expected) \
SUBCASE(#case_name) \
{ \
    NMTOOLS_TESTING_DECLARE_NS(broadcast_to, case_name); \
    auto array_ref = RUN_broadcast_to(case_name, args::array,args::shape); \
    NMTOOLS_ASSERT_EQUAL( array_ref.shape(), args::shape ); \
    NMTOOLS_ASSERT_CLOSE( array_ref, expect::expected ); \
}

TEST_CASE("broadcast_to(case1)" * doctest::test_suite("view::broadcast_to"))
{
    BROADCAST_TO_SUBCASE( case1, x_a, shape, expected );
    BROADCAST_TO_SUBCASE( case1, x_v, shape, expected );
    BROADCAST_TO_SUBCASE( case1, x_f, shape, expected );
    BROADCAST_TO_SUBCASE( case1, x_d, shape, expected );
    BROADCAST_TO_SUBCASE( case1, x_h, shape, expected );
}

TEST_CASE("broadcast_to(case2)" * doctest::test_suite("view::broadcast_to"))
{
    BROADCAST_TO_SUBCASE( case2, x_a, shape, expected );
    BROADCAST_TO_SUBCASE( case2, x_v, shape, expected );
    BROADCAST_TO_SUBCASE( case2, x_f, shape, expected );
    BROADCAST_TO_SUBCASE( case2, x_d, shape, expected );
    BROADCAST_TO_SUBCASE( case2, x_h, shape, expected );
}

TEST_CASE("broadcast_to(case3)" * doctest::test_suite("view::broadcast_to"))
{
    BROADCAST_TO_SUBCASE( case3, x_a, shape, expected );
    BROADCAST_TO_SUBCASE( case3, x_v, shape, expected );
    BROADCAST_TO_SUBCASE( case3, x_f, shape, expected );
    BROADCAST_TO_SUBCASE( case3, x_d, shape, expected );
    BROADCAST_TO_SUBCASE( case3, x_h, shape, expected );
}

TEST_CASE("broadcast_to(case4)" * doctest::test_suite("view::broadcast_to"))
{
    BROADCAST_TO_SUBCASE( case4, x_a, shape, expected );
    BROADCAST_TO_SUBCASE( case4, x_v, shape, expected );
    BROADCAST_TO_SUBCASE( case4, x_f, shape, expected );
    BROADCAST_TO_SUBCASE( case4, x_d, shape, expected );
    BROADCAST_TO_SUBCASE( case4, x_h, shape, expected );
}

TEST_CASE("broadcast_to(case5)" * doctest::test_suite("view::broadcast_to"))
{
    BROADCAST_TO_SUBCASE( case5, x_a, shape, expected );
    BROADCAST_TO_SUBCASE( case5, x_v, shape, expected );
    BROADCAST_TO_SUBCASE( case5, x_f, shape, expected );
    BROADCAST_TO_SUBCASE( case5, x_d, shape, expected );
    BROADCAST_TO_SUBCASE( case5, x_h, shape, expected );
}

TEST_CASE("broadcast_to(case6)" * doctest::test_suite("view::broadcast_to"))
{
    BROADCAST_TO_SUBCASE( case6, x_a, shape, expected );
    BROADCAST_TO_SUBCASE( case6, x_v, shape, expected );
    BROADCAST_TO_SUBCASE( case6, x_f, shape, expected );
    BROADCAST_TO_SUBCASE( case6, x_d, shape, expected );
    BROADCAST_TO_SUBCASE( case6, x_h, shape, expected );
}

TEST_CASE("broadcast_to(case7)" * doctest::test_suite("view::broadcast_to"))
{
    BROADCAST_TO_SUBCASE( case7, x_a, shape, expected );
    BROADCAST_TO_SUBCASE( case7, x_v, shape, expected );
    BROADCAST_TO_SUBCASE( case7, x_f, shape, expected );
    BROADCAST_TO_SUBCASE( case7, x_d, shape, expected );
    BROADCAST_TO_SUBCASE( case7, x_h, shape, expected );
}

TEST_CASE("broadcast_to(case8)" * doctest::test_suite("view::broadcast_to"))
{
    BROADCAST_TO_SUBCASE( case8, x_a, shape, expected );
    BROADCAST_TO_SUBCASE( case8, x_v, shape, expected );
    BROADCAST_TO_SUBCASE( case8, x_f, shape, expected );
    BROADCAST_TO_SUBCASE( case8, x_d, shape, expected );
    BROADCAST_TO_SUBCASE( case8, x_h, shape, expected );
}

TEST_CASE("broadcast_to(case9)" * doctest::test_suite("view::broadcast_to"))
{
    BROADCAST_TO_SUBCASE( case9, x_a, shape, expected );
    BROADCAST_TO_SUBCASE( case9, x_v, shape, expected );
    BROADCAST_TO_SUBCASE( case9, x_f, shape, expected );
    BROADCAST_TO_SUBCASE( case9, x_d, shape, expected );
    BROADCAST_TO_SUBCASE( case9, x_h, shape, expected );
}