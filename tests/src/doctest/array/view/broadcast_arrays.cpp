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
        auto expected = std::tuple{cast<int>(lhs),cast<int>(rhs)};
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
        auto expected = std::tuple{cast<int>(lhs),cast<int>(rhs)};
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
        auto expected = std::tuple{cast<int>(lhs),cast<int>(rhs)};
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
        auto expected = std::tuple{cast<int>(lhs),cast<int>(rhs)};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case5)
    {
        int A[1][3] = {
            {1,2,3}
        };
        int B[2][2][1] = {
            {
                {4},
                {5},
            },
            {
                {6},
                {7},
            },
        };
        int C[1][2][3] = {
            {
                { 8, 9,10},
                {11,12,13},
            }
        };
        auto A_v = cast(A,kind::nested_vec);
        auto B_v = cast(B,kind::nested_vec);
        auto C_v = cast(C,kind::nested_vec);
        auto A_a = cast<int>(A);
        auto B_a = cast<int>(B);
        auto C_a = cast<int>(C);
        auto A_d = cast(A,kind::dynamic);
        auto B_d = cast(B,kind::dynamic);
        auto C_d = cast(C,kind::dynamic);
        auto A_f = cast(A,kind::fixed);
        auto B_f = cast(B,kind::fixed);
        auto C_f = cast(C,kind::fixed);
        auto A_h = cast(A,kind::hybrid);
        auto B_h = cast(B,kind::hybrid);
        auto C_h = cast(C,kind::hybrid);
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case5)
    {
        int A[2][2][3] = {
            {
                {1,2,3},
                {1,2,3},
            },
            {
                {1,2,3},
                {1,2,3},
            },
        };
        int B[2][2][3] = {
            {
                {4,4,4},
                {5,5,5},
            },
            {
                {6,6,6},
                {7,7,7},
            }
        };
        int C[2][2][3] = {
            {
                { 8, 9,10},
                {11,12,13},
            },
            {
                { 8, 9,10},
                {11,12,13},
            }
        };
        auto shape = std::array{2,2,3};
        auto expected = std::tuple{cast<int>(A),cast<int>(B),cast<int>(C)};
    }
}

#define RUN_impl(...) \
nm::view::broadcast_arrays(__VA_ARGS__);

#ifdef NMTOOLS_TESTING_ENABLE_BENCHMARKS
#include "nmtools/benchmarks/bench.hpp"
using nm::benchmarks::TrackedBench;
// create immediately invoked lambda
// that packs broadcast_arrays fn to callable lambda
#define RUN_broadcast_arrays(case_name, ...) \
[](auto&&...args){ \
    auto title = std::string("broadcast_arrays-") + #case_name; \
    auto name  = nm::testing::make_func_args("", args...); \
    auto fn    = [&](){ \
        return RUN_impl(args...); \
    }; \
    return TrackedBench::run(title, name, fn); \
}(__VA_ARGS__);
#else
// run normally without benchmarking, ignore case_name
#define RUN_broadcast_arrays(case_name, ...) \
RUN_impl(__VA_ARGS__);
#endif // NMTOOLS_TESTING_ENABLE_BENCHMARKS

#define BROADCAST_ARRAYS_SUBCASE(case_name, ...) \
SUBCASE(#case_name) \
{ \
    NMTOOLS_TESTING_DECLARE_NS(broadcast_arrays, case_name); \
    using namespace args; \
    auto results = RUN_broadcast_arrays(case_name, __VA_ARGS__); \
    constexpr auto N = std::tuple_size_v<decltype(results)>; \
    nm::meta::template_for<N>([&](auto index){ \
        constexpr auto i = decltype(index)::value; \
        auto array       = std::get<i>(results); \
        auto expected    = std::get<i>(expect::expected); \
        NMTOOLS_ASSERT_EQUAL( array.shape(), expect::shape ); \
        NMTOOLS_ASSERT_CLOSE( array, expected ); \
    }); \
}

TEST_CASE("broadcast_arrays(case1)" * doctest::test_suite("view::broadcast_arrays"))
{
    BROADCAST_ARRAYS_SUBCASE(case1, lhs_a, rhs_a );
    BROADCAST_ARRAYS_SUBCASE(case1, lhs_v, rhs_v );
    BROADCAST_ARRAYS_SUBCASE(case1, lhs_d, rhs_d );
    BROADCAST_ARRAYS_SUBCASE(case1, lhs_f, rhs_f );
    BROADCAST_ARRAYS_SUBCASE(case1, lhs_h, rhs_h );
}

TEST_CASE("broadcast_arrays(case2)" * doctest::test_suite("view::broadcast_arrays"))
{
    BROADCAST_ARRAYS_SUBCASE(case2, lhs_a, rhs_a );
    BROADCAST_ARRAYS_SUBCASE(case2, lhs_v, rhs_v );
    BROADCAST_ARRAYS_SUBCASE(case2, lhs_d, rhs_d );
    BROADCAST_ARRAYS_SUBCASE(case2, lhs_f, rhs_f );
    BROADCAST_ARRAYS_SUBCASE(case2, lhs_h, rhs_h );
}

TEST_CASE("broadcast_arrays(case3)" * doctest::test_suite("view::broadcast_arrays"))
{
    BROADCAST_ARRAYS_SUBCASE(case3, lhs_a, rhs_a );
    BROADCAST_ARRAYS_SUBCASE(case3, lhs_v, rhs_v );
    BROADCAST_ARRAYS_SUBCASE(case3, lhs_d, rhs_d );
    BROADCAST_ARRAYS_SUBCASE(case3, lhs_f, rhs_f );
    BROADCAST_ARRAYS_SUBCASE(case3, lhs_h, rhs_h );
}

TEST_CASE("broadcast_arrays(case4)" * doctest::test_suite("view::broadcast_arrays"))
{
    BROADCAST_ARRAYS_SUBCASE(case4, lhs_a, rhs_a );
    BROADCAST_ARRAYS_SUBCASE(case4, lhs_v, rhs_v );
    BROADCAST_ARRAYS_SUBCASE(case4, lhs_d, rhs_d );
    BROADCAST_ARRAYS_SUBCASE(case4, lhs_f, rhs_f );
    BROADCAST_ARRAYS_SUBCASE(case4, lhs_h, rhs_h );
}

TEST_CASE("broadcast_arrays(case5)" * doctest::test_suite("view::broadcast_arrays"))
{
    BROADCAST_ARRAYS_SUBCASE(case5, A_a, B_a, C_a );
    BROADCAST_ARRAYS_SUBCASE(case5, A_v, B_v, C_v );
    BROADCAST_ARRAYS_SUBCASE(case5, A_d, B_d, C_d );
    BROADCAST_ARRAYS_SUBCASE(case5, A_f, B_f, C_f );
    BROADCAST_ARRAYS_SUBCASE(case5, A_h, B_h, C_h );
}