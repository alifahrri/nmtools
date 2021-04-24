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

#define CAST_ARRAYS(name) \
inline auto name##_a = cast(name, kind::nested_arr); \
inline auto name##_v = cast(name, kind::nested_vec); \
inline auto name##_f = cast(name, kind::fixed); \
inline auto name##_d = cast(name, kind::dynamic); \
inline auto name##_h = cast(name, kind::hybrid); \

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
        CAST_ARRAYS(lhs)
        CAST_ARRAYS(rhs)
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
        CAST_ARRAYS(lhs)
        CAST_ARRAYS(rhs)
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
        CAST_ARRAYS(lhs)
        CAST_ARRAYS(rhs)
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
        CAST_ARRAYS(lhs)
        CAST_ARRAYS(rhs)
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
        CAST_ARRAYS(A)
        CAST_ARRAYS(B)
        CAST_ARRAYS(C)
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

    NMTOOLS_TESTING_DECLARE_ARGS(case6)
    {
        int lhs[1][3] = {
            {1,2,3}
        };
        int rhs = 6;
        CAST_ARRAYS(lhs)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case6)
    {
        int lhs[1][3] = {
            {1,2,3}
        };
        int rhs[1][3] = {
            {6,6,6}
        };
        auto shape = std::array{1,3};
        auto expected = std::tuple{cast<int>(lhs),cast<int>(rhs)};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case7)
    {
        int lhs = 6;
        int rhs[1][3] = {
            {1,2,3}
        };
        CAST_ARRAYS(rhs)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case7)
    {
        int lhs[1][3] = {
            {6,6,6}
        };
        int rhs[1][3] = {
            {1,2,3}
        };
        auto shape = std::array{1,3};
        auto expected = std::tuple{cast<int>(lhs),cast<int>(rhs)};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case8)
    {
        int lhs = 6;
        int rhs = 1;
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case8)
    {
        int lhs = 6;
        int rhs = 1;
        auto shape = None;
        auto expected = std::tuple{lhs,rhs};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case9)
    {
        int A = 6;
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
        CAST_ARRAYS(B)
        CAST_ARRAYS(C)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case9)
    {
        int A[2][2][3] = {
            {
                {6,6,6},
                {6,6,6},
            },
            {
                {6,6,6},
                {6,6,6},
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

TEST_CASE("broadcast_arrays(case6)" * doctest::test_suite("view::broadcast_arrays"))
{
    BROADCAST_ARRAYS_SUBCASE(case6, lhs_a, rhs );
    BROADCAST_ARRAYS_SUBCASE(case6, lhs_v, rhs );
    BROADCAST_ARRAYS_SUBCASE(case6, lhs_d, rhs );
    BROADCAST_ARRAYS_SUBCASE(case6, lhs_f, rhs );
    BROADCAST_ARRAYS_SUBCASE(case6, lhs_h, rhs );
}

TEST_CASE("broadcast_arrays(case7)" * doctest::test_suite("view::broadcast_arrays"))
{
    BROADCAST_ARRAYS_SUBCASE(case7, lhs, rhs_a );
    BROADCAST_ARRAYS_SUBCASE(case7, lhs, rhs_v );
    BROADCAST_ARRAYS_SUBCASE(case7, lhs, rhs_d );
    BROADCAST_ARRAYS_SUBCASE(case7, lhs, rhs_f );
    BROADCAST_ARRAYS_SUBCASE(case7, lhs, rhs_h );
}

TEST_CASE("broadcast_arrays(case8)" * doctest::test_suite("view::broadcast_arrays"))
{
    BROADCAST_ARRAYS_SUBCASE(case8, lhs, rhs);
}

TEST_CASE("broadcast_arrays(case9)" * doctest::test_suite("view::broadcast_arrays"))
{
    BROADCAST_ARRAYS_SUBCASE(case9, A, B_a, C_a );
    BROADCAST_ARRAYS_SUBCASE(case9, A, B_v, C_v );
    BROADCAST_ARRAYS_SUBCASE(case9, A, B_d, C_d );
    BROADCAST_ARRAYS_SUBCASE(case9, A, B_f, C_f );
    BROADCAST_ARRAYS_SUBCASE(case9, A, B_h, C_h );
}

NMTOOLS_TESTING_DECLARE_CASE(broadcast_arrays_constexpr)
{
    NMTOOLS_TESTING_DECLARE_ARGS(case1)
    {
        constexpr int A[1][3] = {
            {1,2,3}
        };
        constexpr int B[2][2][1] = {
            {
                {4},
                {5},
            },
            {
                {6},
                {7},
            },
        };
        constexpr int C[1][2][3] = {
            {
                { 8, 9,10},
                {11,12,13},
            }
        };
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case1)
    {
        constexpr int A[2][2][3] = {
            {
                {1,2,3},
                {1,2,3},
            },
            {
                {1,2,3},
                {1,2,3},
            },
        };
        constexpr int B[2][2][3] = {
            {
                {4,4,4},
                {5,5,5},
            },
            {
                {6,6,6},
                {7,7,7},
            }
        };
        constexpr int C[2][2][3] = {
            {
                { 8, 9,10},
                {11,12,13},
            },
            {
                { 8, 9,10},
                {11,12,13},
            }
        };
    }
}

#include "nmtools/array/eval.hpp"

template <typename output_t, typename first_t, typename second_t, typename third_t>
constexpr auto eval_broadcast_arrays(const first_t& A, const second_t& B, const third_t& C)
{
    auto [a,b,c] = view::broadcast_arrays(A,B,C);

    auto out_t = nm::meta::as_value<output_t>{};
    auto aout = na::eval(a,nm::None,out_t);
    auto bout = na::eval(b,nm::None,out_t);
    auto cout = na::eval(c,nm::None,out_t);

    return std::tuple{aout,bout,cout};
} // eval_broadcast_arrays

// skip constexpr test for emscripten for now, works for gcc & clang
#if !defined(__EMSCRIPTEN__) && !defined(__ANDROID__) && !defined(__arm__) && !defined(__MINGW32__)
TEST_CASE("broadcast_arrays(constexpr)" * doctest::test_suite("view::broadcast_arrays"))
{
    NMTOOLS_TESTING_DECLARE_NS(broadcast_arrays_constexpr, case1);
    using output_t = int[2][2][3];
    constexpr auto broadcasted = eval_broadcast_arrays<output_t>(args::A,args::B,args::C);
    constexpr auto A = std::get<0>(broadcasted);
    constexpr auto B = std::get<1>(broadcasted);
    constexpr auto C = std::get<2>(broadcasted);
    NMTOOLS_STATIC_ASSERT_CLOSE( A, expect::A );
    NMTOOLS_STATIC_ASSERT_CLOSE( B, expect::B );
    NMTOOLS_STATIC_ASSERT_CLOSE( C, expect::C );
}
#endif