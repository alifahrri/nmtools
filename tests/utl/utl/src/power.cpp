#include "nmtools/utl/power.hpp"
#include "nmtools/testing/doctest.hpp"

// TODO: increase precision
#undef NMTOOLS_TESTING_PRECISION
#define NMTOOLS_TESTING_PRECISION (1e-3)

NMTOOLS_TESTING_DECLARE_CASE(utl,taylor_cos)
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
    NMTOOLS_TESTING_USE_CASE(utl,taylor_cos,case_name); \
    using namespace args; \
    auto result = nmtools::utl::taylor_cos(__VA_ARGS__); \
    auto expected = expect::expected; \
    NMTOOLS_ASSERT_CLOSE( result, expected ); \
    expected = std::cos(__VA_ARGS__); \
    NMTOOLS_ASSERT_CLOSE( result, expected ); \
}

TEST_CASE("taylor_cos(case1)" * doctest::test_suite("utl"))
{
    TAYLOR_COS_SUBCASE( case1, x );
}

TEST_CASE("taylor_cos(case2)" * doctest::test_suite("utl"))
{
    TAYLOR_COS_SUBCASE( case2, x );
}

TEST_CASE("taylor_cos(case3)" * doctest::test_suite("utl"))
{
    TAYLOR_COS_SUBCASE( case3, x );
}

TEST_CASE("taylor_cos(case4)" * doctest::test_suite("utl"))
{
    TAYLOR_COS_SUBCASE( case4, x );
}

TEST_CASE("taylor_cos(case5)" * doctest::test_suite("utl"))
{
    TAYLOR_COS_SUBCASE( case5, x );
}

TEST_CASE("taylor_cos(case6)" * doctest::test_suite("utl"))
{
    TAYLOR_COS_SUBCASE( case6, x );
}

TEST_CASE("taylor_cos(case7)" * doctest::test_suite("utl"))
{
    TAYLOR_COS_SUBCASE( case7, x );
}

NMTOOLS_TESTING_DECLARE_CASE(utl,taylor_sin)
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
    NMTOOLS_TESTING_USE_CASE(utl,taylor_sin,case_name); \
    using namespace args; \
    auto result = nmtools::utl::taylor_sin(__VA_ARGS__); \
    auto expected = expect::expected; \
    NMTOOLS_ASSERT_CLOSE( result, expected ); \
    expected = std::sin(__VA_ARGS__); \
    NMTOOLS_ASSERT_CLOSE( result, expected ); \
}

TEST_CASE("taylor_sin(case1)" * doctest::test_suite("utl"))
{
    TAYLOR_SIN_SUBCASE( case1, x );
}

TEST_CASE("taylor_sin(case2)" * doctest::test_suite("utl"))
{
    TAYLOR_SIN_SUBCASE( case2, x );
}

TEST_CASE("taylor_sin(case3)" * doctest::test_suite("utl"))
{
    TAYLOR_SIN_SUBCASE( case3, x );
}

TEST_CASE("taylor_sin(case4)" * doctest::test_suite("utl"))
{
    TAYLOR_SIN_SUBCASE( case4, x );
}

TEST_CASE("taylor_sin(case5)" * doctest::test_suite("utl"))
{
    TAYLOR_SIN_SUBCASE( case5, x );
}

TEST_CASE("taylor_sin(case6)" * doctest::test_suite("utl"))
{
    TAYLOR_SIN_SUBCASE( case6, x );
}

TEST_CASE("taylor_sin(case7)" * doctest::test_suite("utl"))
{
    TAYLOR_SIN_SUBCASE( case7, x );
}

NMTOOLS_TESTING_DECLARE_CASE(utl,taylor_exp)
{
    NMTOOLS_TESTING_DECLARE_ARGS(case1)
    {
        auto x = 0.0f;
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case1)
    {
        auto expected = std::exp(args::x);
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case2)
    {
        auto x = 0.1f;
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case2)
    {
        auto expected = std::exp(args::x);
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case3)
    {
        auto x = -0.1f;
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case3)
    {
        auto expected = std::exp(args::x);
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case4)
    {
        auto x = 0.5f;
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case4)
    {
        auto expected = std::exp(args::x);
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case5)
    {
        auto x = -0.5f;
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case5)
    {
        auto expected = std::exp(args::x);
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case6)
    {
        auto x = 1.0f;
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case6)
    {
        auto expected = std::exp(args::x);
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case7)
    {
        auto x = -1.0f;
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case7)
    {
        auto expected = std::exp(args::x);
    }
}

#define TAYLOR_EXP_SUBCASE(case_name, ...) \
SUBCASE(#case_name) \
{ \
    NMTOOLS_TESTING_USE_CASE(utl,taylor_exp,case_name); \
    using namespace args; \
    auto result = nmtools::utl::taylor_exp(__VA_ARGS__); \
    auto expected = expect::expected; \
    NMTOOLS_ASSERT_CLOSE( result, expected ); \
    expected = std::exp(__VA_ARGS__); \
    NMTOOLS_ASSERT_CLOSE( result, expected ); \
}

TEST_CASE("taylor_exp(case1)" * doctest::test_suite("utl"))
{
    TAYLOR_EXP_SUBCASE( case1, x );
}

TEST_CASE("taylor_exp(case2)" * doctest::test_suite("utl"))
{
    TAYLOR_EXP_SUBCASE( case2, x );
}

TEST_CASE("taylor_exp(case3)" * doctest::test_suite("utl"))
{
    TAYLOR_EXP_SUBCASE( case3, x );
}

TEST_CASE("taylor_exp(case4)" * doctest::test_suite("utl"))
{
    TAYLOR_EXP_SUBCASE( case4, x );
}

TEST_CASE("taylor_exp(case5)" * doctest::test_suite("utl"))
{
    TAYLOR_EXP_SUBCASE( case5, x );
}

TEST_CASE("taylor_exp(case6)" * doctest::test_suite("utl"))
{
    TAYLOR_EXP_SUBCASE( case6, x );
}

TEST_CASE("taylor_exp(case7)" * doctest::test_suite("utl"))
{
    TAYLOR_EXP_SUBCASE( case7, x );
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

NMTOOLS_TESTING_DECLARE_CASE(utl,log_series)
{
    NMTOOLS_TESTING_DECLARE_ARGS(case1)
    {
        auto x = 0.001f;
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case1)
    {
        auto expected = std::log(args::x);
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case2)
    {
        auto x = 0.5f;
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case2)
    {
        auto expected = std::log(args::x);
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case3)
    {
        auto x = 1.0f;
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case3)
    {
        auto expected = std::log(args::x);
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case4)
    {
        auto x = nmtools::utl::e_v<float>;
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case4)
    {
        auto expected = std::log(args::x);
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case5)
    {
        auto x = 10.f;
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case5)
    {
        auto expected = std::log(args::x);
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case6)
    {
        auto x = 100.f;
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case6)
    {
        auto expected = std::log(args::x);
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case7)
    {
        auto x = 1000000.f;
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case7)
    {
        auto expected = std::log(args::x);
    }
}

#define LOG_SERIES_SUBCASE(case_name,...) \
SUBCASE(#case_name) \
{ \
    NMTOOLS_TESTING_USE_CASE(utl,log_series,case_name); \
    using namespace args; \
    auto result = nmtools::utl::log_series(__VA_ARGS__); \
    NMTOOLS_ASSERT_CLOSE( result, expect::expected ); \
}

TEST_CASE("log_series(case1)" * doctest::test_suite("utl"))
{
    LOG_SERIES_SUBCASE( case1, x );
}

TEST_CASE("log_series(case2)" * doctest::test_suite("utl"))
{
    LOG_SERIES_SUBCASE( case2, x );
}

TEST_CASE("log_series(case3)" * doctest::test_suite("utl"))
{
    LOG_SERIES_SUBCASE( case3, x );
}

TEST_CASE("log_series(case4)" * doctest::test_suite("utl"))
{
    LOG_SERIES_SUBCASE( case4, x );
}

TEST_CASE("log_series(case5)" * doctest::test_suite("utl"))
{
    LOG_SERIES_SUBCASE( case5, x );
}

TEST_CASE("log_series(case6)" * doctest::test_suite("utl"))
{
    LOG_SERIES_SUBCASE( case6, x );
}

TEST_CASE("log_series(case7)" * doctest::test_suite("utl"))
{
    LOG_SERIES_SUBCASE( case7, x );
}

NMTOOLS_TESTING_DECLARE_CASE(utl,log2_series)
{
    NMTOOLS_TESTING_DECLARE_ARGS(case1)
    {
        auto x = 0.125f;
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case1)
    {
        auto expected = std::log2(args::x);
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case2)
    {
        auto x = 0.5f;
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case2)
    {
        auto expected = std::log2(args::x);
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case3)
    {
        auto x = 1.0f;
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case3)
    {
        auto expected = std::log2(args::x);
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case4)
    {
        auto x = 2.0f;
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case4)
    {
        auto expected = std::log2(args::x);
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case5)
    {
        auto x = 10.0f;
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case5)
    {
        auto expected = std::log2(args::x);
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case6)
    {
        auto x = 1024.f;
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case6)
    {
        auto expected = std::log2(args::x);
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case7)
    {
        auto x = 65536.5f;
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case7)
    {
        auto expected = std::log2(args::x);
    }
}

#define LOG2_SERIES_SUBCASE(case_name, ...) \
SUBCASE(#case_name) \
{ \
    NMTOOLS_TESTING_USE_CASE(utl,log2_series,case_name); \
    using namespace args; \
    auto result = nmtools::utl::log2_series(__VA_ARGS__); \
    NMTOOLS_ASSERT_CLOSE( result, expect::expected ); \
}

TEST_CASE("log2_series(case1)" * doctest::test_suite("utl"))
{
    LOG2_SERIES_SUBCASE( case1, x );
}

TEST_CASE("log2_series(case2)" * doctest::test_suite("utl"))
{
    LOG2_SERIES_SUBCASE( case2, x );
}

TEST_CASE("log2_series(case3)" * doctest::test_suite("utl"))
{
    LOG2_SERIES_SUBCASE( case3, x );
}

TEST_CASE("log2_series(case4)" * doctest::test_suite("utl"))
{
    LOG2_SERIES_SUBCASE( case4, x );
}

TEST_CASE("log2_series(case5)" * doctest::test_suite("utl"))
{
    LOG2_SERIES_SUBCASE( case5, x );
}

TEST_CASE("log2_series(case6)" * doctest::test_suite("utl"))
{
    LOG2_SERIES_SUBCASE( case6, x );
}

TEST_CASE("log2_series(case7)" * doctest::test_suite("utl"))
{
    LOG2_SERIES_SUBCASE( case7, x );
}