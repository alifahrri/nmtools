#include "nmtools/utl/power.hpp"
#include "nmtools/testing/doctest.hpp"

// TODO: increase precision
#undef NMTOOLS_TESTING_PRECISION
#define NMTOOLS_TESTING_PRECISION (1e-3)

NMTOOLS_TESTING_DECLARE_CASE(utl,cos_maclaurin)
{
    NMTOOLS_TESTING_DECLARE_ARGS(case1)
    {
        auto x = 0.0f;
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case1)
    {
        auto expected = std::cos(args::x);
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case2)
    {
        auto x = 0.5f;
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case2)
    {
        auto expected = std::cos(args::x);
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case3)
    {
        auto x = 1.0f;
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case3)
    {
        auto expected = std::cos(args::x);
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case4)
    {
        auto x = 1.570796f;
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case4)
    {
        auto expected = std::cos(args::x);
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case5)
    {
        auto x = 3.141593f;
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case5)
    {
        auto expected = std::cos(args::x);
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case6)
    {
        auto x = -0.785398f;
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case6)
    {
        auto expected = std::cos(args::x);
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case7)
    {
        auto x = 6.283185f;
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case7)
    {
        auto expected = std::cos(args::x);
    }
}

#define TAYLOR_COS_SUBCASE(case_name, ...) \
SUBCASE(#case_name) \
{ \
    NMTOOLS_TESTING_USE_CASE(utl,cos_maclaurin,case_name); \
    using namespace args; \
    auto result = nmtools::utl::cos_maclaurin(__VA_ARGS__); \
    auto expected = expect::expected; \
    NMTOOLS_ASSERT_CLOSE( result, expected ); \
    expected = std::cos(__VA_ARGS__); \
    NMTOOLS_ASSERT_CLOSE( result, expected ); \
}

TEST_CASE("cos_maclaurin(case1)" * doctest::test_suite("utl"))
{
    TAYLOR_COS_SUBCASE( case1, x );
}

TEST_CASE("cos_maclaurin(case2)" * doctest::test_suite("utl"))
{
    TAYLOR_COS_SUBCASE( case2, x );
}

TEST_CASE("cos_maclaurin(case3)" * doctest::test_suite("utl"))
{
    TAYLOR_COS_SUBCASE( case3, x );
}

TEST_CASE("cos_maclaurin(case4)" * doctest::test_suite("utl"))
{
    TAYLOR_COS_SUBCASE( case4, x );
}

TEST_CASE("cos_maclaurin(case5)" * doctest::test_suite("utl"))
{
    TAYLOR_COS_SUBCASE( case5, x );
}

TEST_CASE("cos_maclaurin(case6)" * doctest::test_suite("utl"))
{
    TAYLOR_COS_SUBCASE( case6, x );
}

TEST_CASE("cos_maclaurin(case7)" * doctest::test_suite("utl"))
{
    TAYLOR_COS_SUBCASE( case7, x );
}

NMTOOLS_TESTING_DECLARE_CASE(utl,sin_maclaurin)
{
    NMTOOLS_TESTING_DECLARE_ARGS(case1)
    {
        auto x = 0.0f;
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case1)
    {
        auto expected = std::sin(args::x);
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case2)
    {
        auto x = 0.01f;
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case2)
    {
        auto expected = std::sin(args::x);
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case3)
    {
        auto x = 0.5f;
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case3)
    {
        auto expected = std::sin(args::x);
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case4)
    {
        auto x = 0.785398f;
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case4)
    {
        auto expected = std::sin(args::x);
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case5)
    {
        auto x = 1.570796f;
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case5)
    {
        auto expected = std::sin(args::x);
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case6)
    {
        auto x = 1.0f;
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case6)
    {
        auto expected = std::sin(args::x);
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case7)
    {
        auto x = 3.141593f;
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case7)
    {
        auto expected = std::sin(args::x);
    }
}

#define TAYLOR_SIN_SUBCASE(case_name, ...) \
SUBCASE(#case_name) \
{ \
    NMTOOLS_TESTING_USE_CASE(utl,sin_maclaurin,case_name); \
    using namespace args; \
    auto result = nmtools::utl::sin_maclaurin(__VA_ARGS__); \
    auto expected = expect::expected; \
    NMTOOLS_ASSERT_CLOSE( result, expected ); \
    expected = std::sin(__VA_ARGS__); \
    NMTOOLS_ASSERT_CLOSE( result, expected ); \
}

TEST_CASE("sin_maclaurin(case1)" * doctest::test_suite("utl"))
{
    TAYLOR_SIN_SUBCASE( case1, x );
}

TEST_CASE("sin_maclaurin(case2)" * doctest::test_suite("utl"))
{
    TAYLOR_SIN_SUBCASE( case2, x );
}

TEST_CASE("sin_maclaurin(case3)" * doctest::test_suite("utl"))
{
    TAYLOR_SIN_SUBCASE( case3, x );
}

TEST_CASE("sin_maclaurin(case4)" * doctest::test_suite("utl"))
{
    TAYLOR_SIN_SUBCASE( case4, x );
}

TEST_CASE("sin_maclaurin(case5)" * doctest::test_suite("utl"))
{
    TAYLOR_SIN_SUBCASE( case5, x );
}

TEST_CASE("sin_maclaurin(case6)" * doctest::test_suite("utl"))
{
    TAYLOR_SIN_SUBCASE( case6, x );
}

TEST_CASE("sin_maclaurin(case7)" * doctest::test_suite("utl"))
{
    TAYLOR_SIN_SUBCASE( case7, x );
}

NMTOOLS_TESTING_DECLARE_CASE(utl,exp2_pade)
{
    NMTOOLS_TESTING_DECLARE_ARGS(case1)
    {
        auto x = 0.0f;
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case1)
    {
        auto expected = std::exp2(args::x);
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case2)
    {
        auto x = 1.0f;
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case2)
    {
        auto expected = std::exp2(args::x);
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case3)
    {
        auto x = -1.0f;
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case3)
    {
        auto expected = std::exp2(args::x);
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case4)
    {
        auto x = 0.5f;
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case4)
    {
        auto expected = std::exp2(args::x);
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case5)
    {
        auto x = -0.4f;
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case5)
    {
        auto expected = std::exp2(args::x);
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case6)
    {
        auto x = 3.14159265f;
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case6)
    {
        auto expected = std::exp2(args::x);
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case7)
    {
        auto x = -7.8f;
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case7)
    {
        auto expected = std::exp2(args::x);
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case8)
    {
        auto x = 10.25f;
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case8)
    {
        auto expected = std::exp2(args::x);
    }
}

#define EXP2_PADE_SUBCASE(case_name, ...) \
SUBCASE(#case_name) \
{ \
    NMTOOLS_TESTING_USE_CASE( utl, exp2_pade, case_name ); \
    using namespace args; \
    auto result = nmtools::utl::exp2_pade(__VA_ARGS__); \
    NMTOOLS_ASSERT_CLOSE( result, expect::expected ); \
}

TEST_CASE("exp2_pade(case1)" * doctest::test_suite("utl"))
{
    EXP2_PADE_SUBCASE( case1, x );
}

TEST_CASE("exp2_pade(case2)" * doctest::test_suite("utl"))
{
    EXP2_PADE_SUBCASE( case2, x );
}

TEST_CASE("exp2_pade(case3)" * doctest::test_suite("utl"))
{
    EXP2_PADE_SUBCASE( case3, x );
}

TEST_CASE("exp2_pade(case4)" * doctest::test_suite("utl"))
{
    EXP2_PADE_SUBCASE( case4, x );
}

TEST_CASE("exp2_pade(case5)" * doctest::test_suite("utl"))
{
    EXP2_PADE_SUBCASE( case5, x );
}

TEST_CASE("exp2_pade(case6)" * doctest::test_suite("utl"))
{
    EXP2_PADE_SUBCASE( case6, x );
}

TEST_CASE("exp2_pade(case7)" * doctest::test_suite("utl"))
{
    EXP2_PADE_SUBCASE( case7, x );
}

TEST_CASE("exp2_pade(case8)" * doctest::test_suite("utl"))
{
    EXP2_PADE_SUBCASE( case8, x );
}

#define EXP2_MACLAURIN_SUBCASE(case_name, ...) \
SUBCASE(#case_name) \
{ \
    NMTOOLS_TESTING_USE_CASE( utl, exp2_pade, case_name ); \
    using namespace args; \
    auto result = nmtools::utl::exp2_maclaurin(__VA_ARGS__); \
    NMTOOLS_ASSERT_CLOSE( result, expect::expected ); \
}

TEST_CASE("exp2_maclaurin(case1)" * doctest::test_suite("utl"))
{
    EXP2_MACLAURIN_SUBCASE( case1, x );
}

TEST_CASE("exp2_maclaurin(case2)" * doctest::test_suite("utl"))
{
    EXP2_MACLAURIN_SUBCASE( case2, x );
}

TEST_CASE("exp2_maclaurin(case3)" * doctest::test_suite("utl"))
{
    EXP2_MACLAURIN_SUBCASE( case3, x );
}

TEST_CASE("exp2_maclaurin(case4)" * doctest::test_suite("utl"))
{
    EXP2_MACLAURIN_SUBCASE( case4, x );
}

TEST_CASE("exp2_maclaurin(case5)" * doctest::test_suite("utl"))
{
    EXP2_MACLAURIN_SUBCASE( case5, x );
}

TEST_CASE("exp2_maclaurin(case6)" * doctest::test_suite("utl"))
{
    EXP2_MACLAURIN_SUBCASE( case6, x );
}

TEST_CASE("exp2_maclaurin(case7)" * doctest::test_suite("utl"))
{
    EXP2_MACLAURIN_SUBCASE( case7, x );
}

TEST_CASE("exp2_maclaurin(case8)" * doctest::test_suite("utl"))
{
    EXP2_MACLAURIN_SUBCASE( case8, x );
}