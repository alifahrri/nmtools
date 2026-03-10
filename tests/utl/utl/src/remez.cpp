#include "nmtools/utl/remez.hpp"
#include "nmtools/testing/doctest.hpp"

// TODO: increase precision
#undef NMTOOLS_TESTING_PRECISION
#define NMTOOLS_TESTING_PRECISION (1e-3)

NMTOOLS_TESTING_DECLARE_CASE(utl,minimize_bounded)
{
    NMTOOLS_TESTING_DECLARE_ARGS(case1)
    {
        auto f = [](auto x){
            return (x-3)*(x-3) + 2;
        };
        auto lower_bound = 0.f;
        auto upper_bound = 10.f;
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case1)
    {
        auto expected = 3.f;
    }
}

#define MINIMIZE_BOUNDED_SUBCASE(case_name,...) \
SUBCASE(#case_name) \
{ \
    NMTOOLS_TESTING_USE_CASE(utl,minimize_bounded,case_name); \
    using namespace args; \
    auto result = nmtools::utl::minimize_bounded(__VA_ARGS__); \
    NMTOOLS_ASSERT_CLOSE( result, expect::expected ); \
}

TEST_CASE("minimize_bounded(case1)" * doctest::test_suite("utl"))
{
    MINIMIZE_BOUNDED_SUBCASE( case1, f, lower_bound, upper_bound );
}

using namespace nmtools::literals;

NMTOOLS_TESTING_DECLARE_CASE(utl,chebyshev_nodes)
{
    // --- Group 1: a = -1.f, b = 1.f ---

    NMTOOLS_TESTING_DECLARE_ARGS(case1)
    {
        auto a = -1.f;
        auto b = 1.f;
        auto n = 1;
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case1)
    {
        float expected[1] = {0.0f};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case2)
    {
        auto a = -1.f;
        auto b = 1.f;
        auto n = 2;
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case2)
    {
        float expected[2] = {-0.707107f, 0.707107f};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case3)
    {
        auto a = -1.f;
        auto b = 1.f;
        auto n = 3;
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case3)
    {
        float expected[3] = {-0.866025f, 0.0f, 0.866025f};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case4)
    {
        auto a = -1.f;
        auto b = 1.f;
        auto n = 4;
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case4)
    {
        float expected[4] = {-0.923880f, -0.382683f, 0.382683f, 0.923880f};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case5)
    {
        auto a = -1.f;
        auto b = 1.f;
        auto n = 1_ct;
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case5)
    {
        float expected[1] = {0.0f};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case6)
    {
        auto a = -1.f;
        auto b = 1.f;
        auto n = 2_ct;
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case6)
    {
        float expected[2] = {-0.707107f, 0.707107f};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case7)
    {
        auto a = -1.f;
        auto b = 1.f;
        auto n = 3_ct;
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case7)
    {
        float expected[3] = {-0.866025f, 0.0f, 0.866025f};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case8)
    {
        auto a = -1.f;
        auto b = 1.f;
        auto n = 4_ct;
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case8)
    {
        float expected[4] = {-0.923880f, -0.382683f, 0.382683f, 0.923880f};
    }


    // --- Group 2: a = 0.f, b = 10.f ---

    NMTOOLS_TESTING_DECLARE_ARGS(case9)
    {
        auto a = 0.f;
        auto b = 10.f;
        auto n = 2;
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case9)
    {
        float expected[2] = {1.464466f, 8.535534f};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case10)
    {
        auto a = 0.f;
        auto b = 10.f;
        auto n = 3;
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case10)
    {
        float expected[3] = {0.669872f, 5.0f, 9.330127f};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case11)
    {
        auto a = 0.f;
        auto b = 10.f;
        auto n = 2_ct;
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case11)
    {
        float expected[2] = {1.464466f, 8.535534f};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case12)
    {
        auto a = 0.f;
        auto b = 10.f;
        auto n = 3_ct;
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case12)
    {
        float expected[3] = {0.669872f, 5.0f, 9.330127f};
    }
}

#define CHEBYSHEV_NODES_SUBCASE(case_name, ...) \
SUBCASE(#case_name) \
{ \
    NMTOOLS_TESTING_USE_CASE(utl,chebyshev_nodes,case_name); \
    using namespace args; \
    auto result = nmtools::utl::chebyshev_nodes(__VA_ARGS__); \
    NMTOOLS_ASSERT_CLOSE( result, expect::expected ); \
}

TEST_CASE("chebyshev_nodes(case1)" * doctest::test_suite("utl"))
{
    CHEBYSHEV_NODES_SUBCASE( case1, a, b, n );
}

TEST_CASE("chebyshev_nodes(case2)" * doctest::test_suite("utl"))
{
    CHEBYSHEV_NODES_SUBCASE( case2, a, b, n );
}

TEST_CASE("chebyshev_nodes(case3)" * doctest::test_suite("utl"))
{
    CHEBYSHEV_NODES_SUBCASE( case3, a, b, n );
}

TEST_CASE("chebyshev_nodes(case4)" * doctest::test_suite("utl"))
{
    CHEBYSHEV_NODES_SUBCASE( case4, a, b, n );
}

TEST_CASE("chebyshev_nodes(case5)" * doctest::test_suite("utl"))
{
    CHEBYSHEV_NODES_SUBCASE( case5, a, b, n );
}

TEST_CASE("chebyshev_nodes(case6)" * doctest::test_suite("utl"))
{
    CHEBYSHEV_NODES_SUBCASE( case6, a, b, n );
}

TEST_CASE("chebyshev_nodes(case7)" * doctest::test_suite("utl"))
{
    CHEBYSHEV_NODES_SUBCASE( case7, a, b, n );
}

TEST_CASE("chebyshev_nodes(case8)" * doctest::test_suite("utl"))
{
    CHEBYSHEV_NODES_SUBCASE( case8, a, b, n );
}

TEST_CASE("chebyshev_nodes(case9)" * doctest::test_suite("utl"))
{
    CHEBYSHEV_NODES_SUBCASE( case9, a, b, n );
}

TEST_CASE("chebyshev_nodes(case10)" * doctest::test_suite("utl"))
{
    CHEBYSHEV_NODES_SUBCASE( case10, a, b, n );
}

TEST_CASE("chebyshev_nodes(case11)" * doctest::test_suite("utl"))
{
    CHEBYSHEV_NODES_SUBCASE( case11, a, b, n );
}

TEST_CASE("chebyshev_nodes(case12)" * doctest::test_suite("utl"))
{
    CHEBYSHEV_NODES_SUBCASE( case12, a, b, n );
}

NMTOOLS_TESTING_DECLARE_CASE(utl,linear_solve)
{
    namespace utl = nmtools::utl;

    // --- Group 1: Identity Matrix ---
    NMTOOLS_TESTING_DECLARE_ARGS(case1)
    {
        auto A = utl::array<utl::array<float,2>,2>{
            utl::array<float,2>{1.f,0.f},
            utl::array<float,2>{0.f,1.f},
        };
        auto b = utl::array<float,2>{5.f,10.f};
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case1)
    {
        auto expected = utl::array<float,2>{5.f,10.f};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case2)
    {
        auto A = [](){
            auto A = utl::vector<utl::array<float,2>>{};
            A.resize(2);
            A[0] = utl::array<float,2>{1.f,0.f};
            A[1] = utl::array<float,2>{0.f,1.f};
            return A;
        }();
        auto b = utl::array<float,2>{5.f,10.f};
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case2)
    {
        auto expected = utl::array<float,2>{5.f,10.f};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case3)
    {
        auto A = utl::array<utl::array<float,2>,2>{
            utl::array<float,2>{1.f,0.f},
            utl::array<float,2>{0.f,1.f},
        };
        auto b = [](){
            auto b = utl::vector<float>{};
            b.resize(2);
            b[0] = 5.f;
            b[1] = 10.f;
            return b;
        }();
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case3)
    {
        auto expected = utl::array<float,2>{5.f,10.f};
    }

    // --- Group 2: Regular 2x2 ---
    NMTOOLS_TESTING_DECLARE_ARGS(case4)
    {
        auto A = utl::array<utl::array<float,2>,2>{
            utl::array<float,2>{3.f,2.f},
            utl::array<float,2>{1.f,2.f},
        };
        auto b = utl::array<float,2>{18.f,10.f};
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case4)
    {
        auto expected = utl::array<float,2>{4.f,3.f};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case5)
    {
        auto A = [](){
            auto A = utl::vector<utl::array<float,2>>{};
            A.resize(2);
            A[0] = utl::array<float,2>{3.f,2.f};
            A[1] = utl::array<float,2>{1.f,2.f};
            return A;
        }();
        auto b = utl::array<float,2>{18.f,10.f};
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case5)
    {
        auto expected = utl::array<float,2>{4.f,3.f};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case6)
    {
        auto A = utl::array<utl::array<float,2>,2>{
            utl::array<float,2>{3.f,2.f},
            utl::array<float,2>{1.f,2.f},
        };
        auto b = [](){
            auto b = utl::vector<float>{};
            b.resize(2);
            b[0] = 18.f;
            b[1] = 10.f;
            return b;
        }();
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case6)
    {
        auto expected = utl::array<float,2>{4.f,3.f};
    }

    // --- Group 3: Near-Singular 2x2 ---
    NMTOOLS_TESTING_DECLARE_ARGS(case7)
    {
        auto A = utl::array<utl::array<float,2>,2>{
            utl::array<float,2>{1.f,1.f},
            utl::array<float,2>{1.f,1.00001f},
        };
        auto b = utl::array<float,2>{2.f,2.00001f};
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case7)
    {
        auto expected = utl::array<float,2>{1.f,1.f};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case8)
    {
        auto A = [](){
            auto A = utl::vector<utl::array<float,2>>{};
            A.resize(2);
            A[0] = utl::array<float,2>{1.f,1.f};
            A[1] = utl::array<float,2>{1.f,1.00001f};
            return A;
        }();
        auto b = utl::array<float,2>{2.f,2.00001f};
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case8)
    {
        auto expected = utl::array<float,2>{1.f,1.f};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case9)
    {
        auto A = utl::array<utl::array<float,2>,2>{
            utl::array<float,2>{1.f,1.f},
            utl::array<float,2>{1.f,1.00001f},
        };
        auto b = [](){
            auto b = utl::vector<float>{};
            b.resize(2);
            b[0] = 2.f;
            b[1] = 2.00001f;
            return b;
        }();
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case9)
    {
        auto expected = utl::array<float,2>{1.f,1.f};
    }

    // --- Group 4: Regular 3x3 ---
    NMTOOLS_TESTING_DECLARE_ARGS(case10)
    {
        auto A = utl::array<utl::array<float,3>,3>{
            utl::array<float,3>{1.f,0.f,1.f},
            utl::array<float,3>{1.f,1.f,-1.f},
            utl::array<float,3>{1.f,2.f,1.f},
        };
        auto b = utl::array<float,3>{1.f,2.f,5.f};
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case10)
    {
        auto expected = utl::array<float,3>{0.5f,2.f,0.5f};
    }
}

#define LINEAR_SOLVE_SUBCASE(case_name, ...) \
SUBCASE(#case_name) \
{ \
    NMTOOLS_TESTING_USE_CASE(utl,linear_solve,case_name); \
    using namespace args; \
    auto result = nmtools::utl::linear_solve(__VA_ARGS__); \
    NMTOOLS_ASSERT_CLOSE( result, expect::expected ); \
}

TEST_CASE("linear_solve(case1)" * doctest::test_suite("utl"))
{
    LINEAR_SOLVE_SUBCASE( case1, A, b );
}

TEST_CASE("linear_solve(case2)" * doctest::test_suite("utl"))
{
    LINEAR_SOLVE_SUBCASE( case2, A, b );
}

TEST_CASE("linear_solve(case3)" * doctest::test_suite("utl"))
{
    LINEAR_SOLVE_SUBCASE( case3, A, b );
}

TEST_CASE("linear_solve(case4)" * doctest::test_suite("utl"))
{
    LINEAR_SOLVE_SUBCASE( case4, A, b );
}

TEST_CASE("linear_solve(case5)" * doctest::test_suite("utl"))
{
    LINEAR_SOLVE_SUBCASE( case5, A, b );
}

TEST_CASE("linear_solve(case6)" * doctest::test_suite("utl"))
{
    LINEAR_SOLVE_SUBCASE( case6, A, b );
}

TEST_CASE("linear_solve(case7)" * doctest::test_suite("utl"))
{
    LINEAR_SOLVE_SUBCASE( case7, A, b );
}

TEST_CASE("linear_solve(case8)" * doctest::test_suite("utl"))
{
    LINEAR_SOLVE_SUBCASE( case8, A, b );
}

TEST_CASE("linear_solve(case9)" * doctest::test_suite("utl"))
{
    LINEAR_SOLVE_SUBCASE( case9, A, b );
}

TEST_CASE("linear_solve(case10)" * doctest::test_suite("utl"))
{
    LINEAR_SOLVE_SUBCASE( case10, A, b );
}

using namespace nmtools::literals;

NMTOOLS_TESTING_DECLARE_CASE(utl,solve_remez)
{
    namespace utl = nmtools::utl;

    // cos
    NMTOOLS_TESTING_DECLARE_ARGS(case1)
    {
        auto f = [](auto t){
            return utl::taylor_cos(utl::sqrt(utl::abs(t)));
        };
        auto a = 0.f;
        auto b = utl::pow(utl::pi_v<float> / 4, 2);
        auto degree = 4;
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case1)
    {
        auto expected = utl::array{1.000000f, -5.00000e-1f, 4.16666e-2f, -1.38888e-3f, 2.47998045e-4f, -2.72364189e-7};
    }

    // sin
    NMTOOLS_TESTING_DECLARE_ARGS(case2)
    {
        auto f = [](auto t){
            using T = decltype(t);
            if (utl::abs(t) < 1e-7) {
                return T(1.0);
            } else {
                return utl::taylor_sin(utl::sqrt(t)) / utl::sqrt(t);
            }
        };
        auto a = 0.f;
        auto b = utl::pow(utl::pi_v<float> / 4, 2);
        auto degree = 4;
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case2)
    {
        auto expected = utl::array{1.00000000e+00f, -1.66666667e-01f,  8.33333333e-03f, -1.98412647e-04f, 2.75555594e-06f, -2.47766355e-08f};
    }

    // exp2
    NMTOOLS_TESTING_DECLARE_ARGS(case3)
    {
        auto f = [](auto t){
            return utl::exp2_maclaurin(t);
        };
        auto a = -0.5f;
        auto b = 0.5f;
        auto degree = 5;
        auto num_iter = 15;
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case3)
    {
        auto expected = utl::array{
            1.0f
            , 0.6931471805599453f
            , 0.2402265069591007f
            , 0.05550410866482158f
            , 0.009618129107628477f
            , 0.0013333558146428443f
            , 0.0001540353039338161f
        };
    }

    // log
    NMTOOLS_TESTING_DECLARE_ARGS(case4)
    {
        auto f = [](auto t){
            return utl::log_maclaurin(t);
        };
        auto degree = 4;
        auto num_iter = 15;
        auto a = 0.0f;
        auto b = 1.0f/9.0f;
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case4)
    {
        auto expected = utl::array{
            0.9999999987443783
            , 0.33333360415948327
            , 0.1999830186936437
            , 0.14331782458362843
            , 0.10504168312762406
            , 0.1283550008650624
        };
    }
}

#define SOLVE_REMEZ_SUBCASE(case_name, ...) \
SUBCASE(#case_name) \
{ \
    NMTOOLS_TESTING_USE_CASE(utl,solve_remez,case_name); \
    using namespace args; \
    auto result = nmtools::utl::solve_remez(__VA_ARGS__); \
    NMTOOLS_ASSERT_EQUAL( nmtools::len(result), nmtools::len(expect::expected) ); \
    NMTOOLS_ASSERT_CLOSE( result, expect::expected ); \
}

#include <fenv.h>

// TODO: fix undefined behaviour, probably utl::vector
TEST_CASE("solve_remez(case1)" * doctest::test_suite("utl") * doctest::may_fail() * doctest::skip())
{
    // not available on emcc/windows
    #if !defined(__EMSCRIPTEN__) && !defined(__MINGW32__) && !defined(__MINGW32__)
    feenableexcept(FE_INVALID | FE_OVERFLOW | FE_DIVBYZERO);
    #endif

    SOLVE_REMEZ_SUBCASE( case1, f, a, b, degree );
}

TEST_CASE("solve_remez(case2)" * doctest::test_suite("utl") * doctest::may_fail() * doctest::skip())
{
    // not available on emcc/windows
    #if !defined(__EMSCRIPTEN__) && !defined(__MINGW32__) && !defined(__MINGW32__)
    feenableexcept(FE_INVALID | FE_OVERFLOW | FE_DIVBYZERO);
    #endif

    SOLVE_REMEZ_SUBCASE( case2, f, a, b, degree );
}

TEST_CASE("solve_remez(case3)" * doctest::test_suite("utl") * doctest::may_fail() * doctest::skip())
{
    // not available on emcc/windows
    #if !defined(__EMSCRIPTEN__) && !defined(__MINGW32__) && !defined(__MINGW32__)
    feenableexcept(FE_INVALID | FE_OVERFLOW | FE_DIVBYZERO);
    #endif

    SOLVE_REMEZ_SUBCASE( case3, f, a, b, degree, num_iter );
}

TEST_CASE("solve_remez(case4)" * doctest::test_suite("utl") * doctest::may_fail() * doctest::skip())
{
    // not available on emcc/windows
    #if !defined(__EMSCRIPTEN__) && !defined(__MINGW32__) && !defined(__MINGW32__)
    feenableexcept(FE_INVALID | FE_OVERFLOW | FE_DIVBYZERO);
    #endif

    SOLVE_REMEZ_SUBCASE( case4, f, a, b, degree, num_iter );
}