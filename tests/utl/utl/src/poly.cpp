#include "nmtools/utl/poly.hpp"
#include "nmtools/testing/doctest.hpp"

// TODO: increase precision
#undef NMTOOLS_TESTING_PRECISION
#define NMTOOLS_TESTING_PRECISION (1e-7)

NMTOOLS_TESTING_DECLARE_CASE(utl,sin_poly)
{
    namespace utl = nmtools::utl;

    auto cos_coeffs = utl::array{1.000000f, -5.00000e-1f, 4.16666e-2f, -1.38888e-3f, 2.47998045e-4f, -2.72364189e-7};
    auto sin_coeffs = utl::array{1.000000f, -1.66667e-1f, 8.33333e-3f, -1.98412647e-4f, 2.75555594e-6f, -2.47766355e-8f};

    NMTOOLS_TESTING_DECLARE_ARGS(case1)
    {
        auto x = 0.0f;
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case1)
    {
        auto expected = std::sin(0.0f);
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case2)
    {
        auto x = 0.1f;
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case2)
    {
        auto expected = std::sin(0.1f);
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case3)
    {
        auto x = 0.2f;
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case3)
    {
        auto expected = std::sin(0.2f);
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case4)
    {
        auto x = 0.3f;
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case4)
    {
        auto expected = std::sin(0.3f);
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case5)
    {
        auto x = 0.4f;
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case5)
    {
        auto expected = std::sin(0.4f);
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case6)
    {
        auto x = 0.5f;
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case6)
    {
        auto expected = std::sin(0.5f);
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case7)
    {
        auto x = 0.785398; 
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case7)
    {
        auto expected = std::sin(0.785398f);
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case8)
    {
        auto x = 1.0f;
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case8)
    {
        auto expected = std::sin(1.0f);
    }
}

#define SIN_POLY_SUBCASE(case_name, ...) \
SUBCASE(#case_name) \
{ \
    using namespace nmtools::testing::data::utl::sin_poly; \
    NMTOOLS_TESTING_USE_CASE(utl,sin_poly,case_name); \
    using namespace args; \
    auto result = nmtools::utl::sin_poly(__VA_ARGS__); \
    NMTOOLS_ASSERT_CLOSE( result, expect::expected ); \
}

TEST_CASE("sin_poly(case1)" * doctest::test_suite("utl"))
{
    SIN_POLY_SUBCASE( case1, x, sin_coeffs, cos_coeffs );
}

TEST_CASE("sin_poly(case2)" * doctest::test_suite("utl"))
{
    SIN_POLY_SUBCASE( case2, x, sin_coeffs, cos_coeffs );
}

TEST_CASE("sin_poly(case3)" * doctest::test_suite("utl"))
{
    SIN_POLY_SUBCASE( case3, x, sin_coeffs, cos_coeffs );
}

TEST_CASE("sin_poly(case4)" * doctest::test_suite("utl"))
{
    SIN_POLY_SUBCASE( case4, x, sin_coeffs, cos_coeffs );
}

TEST_CASE("sin_poly(case5)" * doctest::test_suite("utl"))
{
    SIN_POLY_SUBCASE( case5, x, sin_coeffs, cos_coeffs );
}

TEST_CASE("sin_poly(case6)" * doctest::test_suite("utl"))
{
    SIN_POLY_SUBCASE( case6, x, sin_coeffs, cos_coeffs );
}

TEST_CASE("sin_poly(case7)" * doctest::test_suite("utl"))
{
    SIN_POLY_SUBCASE( case7, x, sin_coeffs, cos_coeffs );
}

TEST_CASE("sin_poly(case8)" * doctest::test_suite("utl"))
{
    SIN_POLY_SUBCASE( case8, x, sin_coeffs, cos_coeffs );
}

NMTOOLS_TESTING_DECLARE_CASE(utl,cos_poly)
{
    namespace utl = nmtools::utl;

    auto cos_coeffs = utl::array{1.000000f, -5.00000e-1f, 4.16666e-2f, -1.38888e-3f, 2.47998045e-4f, -2.72364189e-7};
    auto sin_coeffs = utl::array{1.000000f, -1.66667e-1f, 8.33333e-3f, -1.98412647e-4f, 2.75555594e-6f, -2.47766355e-8f};

    NMTOOLS_TESTING_DECLARE_ARGS(case1)
    {
        auto x = 0.0f;
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case1)
    {
        auto expected = std::cos(0.0f);
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case2)
    {
        auto x = 0.1f;
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case2)
    {
        auto expected = std::cos(0.1f);
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case3)
    {
        auto x = 0.2f;
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case3)
    {
        auto expected = std::cos(0.2f);
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case4)
    {
        auto x = 0.3f;
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case4)
    {
        auto expected = std::cos(0.3f);
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case5)
    {
        auto x = 0.4f;
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case5)
    {
        auto expected = std::cos(0.4f);
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case6)
    {
        auto x = 0.5f;
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case6)
    {
        auto expected = std::cos(0.5f);
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case7)
    {
        auto x = 0.785398; 
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case7)
    {
        auto expected = std::cos(0.785398f);
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case8)
    {
        auto x = 1.0f;
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case8)
    {
        auto expected = std::cos(1.0f);
    }
}

#define COS_POLY_SUBCASE(case_name, ...) \
SUBCASE(#case_name) \
{ \
    using namespace nmtools::testing::data::utl::cos_poly; \
    NMTOOLS_TESTING_USE_CASE(utl,cos_poly,case_name); \
    using namespace args; \
    auto result = nmtools::utl::cos_poly(__VA_ARGS__); \
    NMTOOLS_ASSERT_CLOSE( result, expect::expected ); \
}

TEST_CASE("cos_poly(case1)" * doctest::test_suite("utl"))
{
    COS_POLY_SUBCASE( case1, x, cos_coeffs, sin_coeffs );
}

TEST_CASE("cos_poly(case2)" * doctest::test_suite("utl"))
{
    COS_POLY_SUBCASE( case2, x, cos_coeffs, sin_coeffs );
}

TEST_CASE("cos_poly(case3)" * doctest::test_suite("utl"))
{
    COS_POLY_SUBCASE( case3, x, cos_coeffs, sin_coeffs );
}

TEST_CASE("cos_poly(case4)" * doctest::test_suite("utl"))
{
    COS_POLY_SUBCASE( case4, x, cos_coeffs, sin_coeffs );
}

TEST_CASE("cos_poly(case5)" * doctest::test_suite("utl"))
{
    COS_POLY_SUBCASE( case5, x, cos_coeffs, sin_coeffs );
}

TEST_CASE("cos_poly(case6)" * doctest::test_suite("utl"))
{
    COS_POLY_SUBCASE( case6, x, cos_coeffs, sin_coeffs );
}

TEST_CASE("cos_poly(case7)" * doctest::test_suite("utl"))
{
    COS_POLY_SUBCASE( case7, x, cos_coeffs, sin_coeffs );
}

TEST_CASE("cos_poly(case8)" * doctest::test_suite("utl"))
{
    COS_POLY_SUBCASE( case8, x, cos_coeffs, sin_coeffs );
}

NMTOOLS_TESTING_DECLARE_CASE(utl,exp2_poly)
{
    namespace utl = nmtools::utl;

    auto coeffs = utl::array{1.0f,0.6931471805599453f,0.2402265069591007f,0.05550410866482158f,0.009618129107628477f,0.0013333558146428443f,0.0001540353039338161f};

    NMTOOLS_TESTING_DECLARE_ARGS(case1)
    {
        auto x = 0.0f;
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case1)
    {
        auto expected = 1.0f;
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case2)
    {
        auto x = 1.0f;
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case2)
    {
        auto expected = 2.0f;
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case3)
    {
        auto x = -1.0f;
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case3)
    {
        auto expected = 0.5f;
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case4)
    {
        auto x = 0.5f;
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case4)
    {
        auto expected = 1.414213562373095e+00f;
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case5)
    {
        auto x = -0.4f;
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case5)
    {
        auto expected = 7.578582832551990e-01f;
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case6)
    {
        auto x = 5.3f;
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case6)
    {
        auto expected = 3.939662122703731e+01f;
    }


    NMTOOLS_TESTING_DECLARE_ARGS(case7)
    {
        auto x = -7.8f;
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case7)
    {
        auto expected = 4.487102949207168e-03f;
    }
}

#define EXP2_POLY_SUBCASE(case_name,...) \
SUBCASE(#case_name) \
{ \
    using namespace nmtools::testing::data::utl::exp2_poly; \
    NMTOOLS_TESTING_USE_CASE(utl,exp2_poly,case_name); \
    using namespace args; \
    auto result = nmtools::utl::exp2_poly(__VA_ARGS__); \
    NMTOOLS_ASSERT_CLOSE( result, expect::expected ); \
}

TEST_CASE("exp2_poly(case1)" * doctest::test_suite("utl"))
{
    EXP2_POLY_SUBCASE( case1, x, coeffs );
}

TEST_CASE("exp2_poly(case2)" * doctest::test_suite("utl"))
{
    EXP2_POLY_SUBCASE( case2, x, coeffs );
}

TEST_CASE("exp2_poly(case3)" * doctest::test_suite("utl"))
{
    EXP2_POLY_SUBCASE( case3, x, coeffs );
}

TEST_CASE("exp2_poly(case4)" * doctest::test_suite("utl"))
{
    EXP2_POLY_SUBCASE( case4, x, coeffs );
}

TEST_CASE("exp2_poly(case5)" * doctest::test_suite("utl"))
{
    EXP2_POLY_SUBCASE( case5, x, coeffs );
}

TEST_CASE("exp2_poly(case6)" * doctest::test_suite("utl"))
{
    EXP2_POLY_SUBCASE( case6, x, coeffs );
}

TEST_CASE("exp2_poly(case7)" * doctest::test_suite("utl"))
{
    EXP2_POLY_SUBCASE( case7, x, coeffs );
}

NMTOOLS_TESTING_DECLARE_CASE(utl,log_poly)
{
    namespace utl = nmtools::utl;

    auto coeffs = utl::array{
        1.0f,
        0.3333333333333333f,
        0.2000000000000000f,
        0.1428571428571428f,
        0.1111111111111111f
    };

    NMTOOLS_TESTING_DECLARE_ARGS(case1)
    {
        auto x = 0.001f;
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case1)
    {
        auto expected = std::log(0.001f);
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case2)
    {
        auto x = 0.5f;
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case2)
    {
        auto expected = std::log(0.5f);
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case3)
    {
        auto x = 1.0f;
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case3)
    {
        auto expected = std::log(1.0f);
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
        auto expected = std::log(10.f);
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case6)
    {
        auto x = 100.f;
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case6)
    {
        auto expected = std::log(100.f);
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case7)
    {
        auto x = 1000000.f;
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case7)
    {
        auto expected = std::log(1000000.f);
    }
}

#define LOG_POLY_SUBCASE(case_name,...) \
SUBCASE(#case_name) \
{ \
    using namespace nmtools::testing::data::utl::log_poly; \
    NMTOOLS_TESTING_USE_CASE( utl, log_poly, case_name ); \
    using namespace args; \
    auto result = nmtools::utl::log_poly(__VA_ARGS__); \
    NMTOOLS_ASSERT_CLOSE( result, expect::expected ); \
}

TEST_CASE("log_poly(case1)" * doctest::test_suite("utl"))
{
    LOG_POLY_SUBCASE( case1, x, coeffs );
}

TEST_CASE("log_poly(case2)" * doctest::test_suite("utl"))
{
    LOG_POLY_SUBCASE( case2, x, coeffs );
}

TEST_CASE("log_poly(case3)" * doctest::test_suite("utl"))
{
    LOG_POLY_SUBCASE( case3, x, coeffs );
}

TEST_CASE("log_poly(case4)" * doctest::test_suite("utl"))
{
    LOG_POLY_SUBCASE( case4, x, coeffs );
}

TEST_CASE("log_poly(case5)" * doctest::test_suite("utl"))
{
    LOG_POLY_SUBCASE( case5, x, coeffs );
}

TEST_CASE("log_poly(case6)" * doctest::test_suite("utl"))
{
    LOG_POLY_SUBCASE( case6, x, coeffs );
}

TEST_CASE("log_poly(case7)" * doctest::test_suite("utl"))
{
    LOG_POLY_SUBCASE( case7, x, coeffs );
}

NMTOOLS_TESTING_DECLARE_CASE(utl,cos)
{
    namespace utl = nmtools::utl;

    NMTOOLS_TESTING_DECLARE_ARGS(case1)
    {
        auto x = 0.0f;
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case1)
    {
        auto expected = std::cos(0.0f);
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case2)
    {
        auto x = 0.1f;
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case2)
    {
        auto expected = std::cos(0.1f);
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case3)
    {
        auto x = 0.2f;
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case3)
    {
        auto expected = std::cos(0.2f);
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case4)
    {
        auto x = 0.3f;
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case4)
    {
        auto expected = std::cos(0.3f);
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case5)
    {
        auto x = 0.4f;
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case5)
    {
        auto expected = std::cos(0.4f);
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case6)
    {
        auto x = 0.5f;
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case6)
    {
        auto expected = std::cos(0.5f);
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case7)
    {
        auto x = 0.785398f; 
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case7)
    {
        auto expected = std::cos(0.785398f);
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case8)
    {
        auto x = 1.0f;
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case8)
    {
        auto expected = std::cos(1.0f);
    }
}

#define COS_SUBCASE(case_name, ...) \
SUBCASE(#case_name) \
{ \
    NMTOOLS_TESTING_USE_CASE(utl,cos,case_name); \
    using namespace args; \
    auto result = nmtools::utl::cos(__VA_ARGS__); \
    NMTOOLS_ASSERT_CLOSE( result, expect::expected ); \
}

TEST_CASE("cos(case1)" * doctest::test_suite("utl"))
{
    COS_SUBCASE( case1, x );
}

TEST_CASE("cos(case2)" * doctest::test_suite("utl"))
{
    COS_SUBCASE( case2, x );
}

TEST_CASE("cos(case3)" * doctest::test_suite("utl"))
{
    COS_SUBCASE( case3, x );
}

TEST_CASE("cos(case4)" * doctest::test_suite("utl"))
{
    COS_SUBCASE( case4, x );
}

TEST_CASE("cos(case5)" * doctest::test_suite("utl"))
{
    COS_SUBCASE( case5, x );
}

TEST_CASE("cos(case6)" * doctest::test_suite("utl"))
{
    COS_SUBCASE( case6, x );
}

TEST_CASE("cos(case7)" * doctest::test_suite("utl"))
{
    COS_SUBCASE( case7, x );
}

TEST_CASE("cos(case8)" * doctest::test_suite("utl"))
{
    COS_SUBCASE( case8, x );
}

NMTOOLS_TESTING_DECLARE_CASE(utl,sin)
{
    namespace utl = nmtools::utl;

    auto cos_coeffs = utl::array{1.000000f, -5.00000e-1f, 4.16666e-2f, -1.38888e-3f, 2.47998045e-4f, -2.72364189e-7};
    auto sin_coeffs = utl::array{1.000000f, -1.66667e-1f, 8.33333e-3f, -1.98412647e-4f, 2.75555594e-6f, -2.47766355e-8f};

    NMTOOLS_TESTING_DECLARE_ARGS(case1)
    {
        auto x = 0.0f;
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case1)
    {
        auto expected = std::sin(0.0f);
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case2)
    {
        auto x = 0.1f;
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case2)
    {
        auto expected = std::sin(0.1f);
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case3)
    {
        auto x = 0.2f;
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case3)
    {
        auto expected = std::sin(0.2f);
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case4)
    {
        auto x = 0.3f;
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case4)
    {
        auto expected = std::sin(0.3f);
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case5)
    {
        auto x = 0.4f;
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case5)
    {
        auto expected = std::sin(0.4f);
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case6)
    {
        auto x = 0.5f;
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case6)
    {
        auto expected = std::sin(0.5f);
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case7)
    {
        auto x = 0.785398; 
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case7)
    {
        auto expected = std::sin(0.785398f);
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case8)
    {
        auto x = 1.0f;
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case8)
    {
        auto expected = std::sin(1.0f);
    }
}

#define SIN_SUBCASE(case_name, ...) \
SUBCASE(#case_name) \
{ \
    using namespace nmtools::testing::data::utl::sin; \
    NMTOOLS_TESTING_USE_CASE(utl,sin,case_name); \
    using namespace args; \
    auto result = nmtools::utl::sin(__VA_ARGS__); \
    NMTOOLS_ASSERT_CLOSE( result, expect::expected ); \
}

TEST_CASE("sin(case1)" * doctest::test_suite("utl"))
{
    SIN_SUBCASE( case1, x );
}

TEST_CASE("sin(case2)" * doctest::test_suite("utl"))
{
    SIN_SUBCASE( case2, x );
}

TEST_CASE("sin(case3)" * doctest::test_suite("utl"))
{
    SIN_SUBCASE( case3, x );
}

TEST_CASE("sin(case4)" * doctest::test_suite("utl"))
{
    SIN_SUBCASE( case4, x );
}

TEST_CASE("sin(case5)" * doctest::test_suite("utl"))
{
    SIN_SUBCASE( case5, x );
}

TEST_CASE("sin(case6)" * doctest::test_suite("utl"))
{
    SIN_SUBCASE( case6, x );
}

TEST_CASE("sin(case7)" * doctest::test_suite("utl"))
{
    SIN_SUBCASE( case7, x );
}

TEST_CASE("sin(case8)" * doctest::test_suite("utl"))
{
    SIN_SUBCASE( case8, x );
}

NMTOOLS_TESTING_DECLARE_CASE(utl,exp2)
{
    namespace utl = nmtools::utl;

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
        auto x = 5.3f;
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
}

#define EXP2_SUBCASE(case_name,...) \
SUBCASE(#case_name) \
{ \
    NMTOOLS_TESTING_USE_CASE(utl,exp2,case_name); \
    using namespace args; \
    auto result = nmtools::utl::exp2(__VA_ARGS__); \
    NMTOOLS_ASSERT_CLOSE( result, expect::expected ); \
}

TEST_CASE("exp2(case1)" * doctest::test_suite("utl"))
{
    EXP2_SUBCASE( case1, x );
}

TEST_CASE("exp2(case2)" * doctest::test_suite("utl"))
{
    EXP2_SUBCASE( case2, x );
}

TEST_CASE("exp2(case3)" * doctest::test_suite("utl"))
{
    EXP2_SUBCASE( case3, x );
}

TEST_CASE("exp2(case4)" * doctest::test_suite("utl"))
{
    EXP2_SUBCASE( case4, x );
}

TEST_CASE("exp2(case5)" * doctest::test_suite("utl"))
{
    EXP2_SUBCASE( case5, x );
}

// TODO: fix, increase precision
TEST_CASE("exp2(case6)" * doctest::test_suite("utl") * doctest::may_fail())
{
    EXP2_SUBCASE( case6, x );
}

TEST_CASE("exp2(case7)" * doctest::test_suite("utl"))
{
    EXP2_SUBCASE( case7, x );
}

NMTOOLS_TESTING_DECLARE_CASE(utl,exp)
{
    namespace utl = nmtools::utl;

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
        auto x = 0.5f;
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case2)
    {
        auto expected = std::exp(args::x);
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case3)
    {
        auto x = -0.5f;
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case3)
    {
        auto expected = std::exp(args::x);
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case4)
    {
        auto x = 1.0f;
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case4)
    {
        auto expected = std::exp(args::x);
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case5)
    {
        auto x = -2.5f;
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case5)
    {
        auto expected = std::exp(args::x);
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case6)
    {
        auto x = 10.0f;
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case6)
    {
        auto expected = std::exp(args::x);
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case7)
    {
        auto x = 50.0f;
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case7)
    {
        auto expected = std::exp(args::x);
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case8)
    {
        auto x = -10.5f;
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case8)
    {
        auto expected = std::exp(args::x);
    }
}

#define EXP_SUBCASE(case_name, ...) \
SUBCASE(#case_name) \
{ \
    NMTOOLS_TESTING_USE_CASE( utl, exp, case_name ); \
    using namespace args; \
    auto result = nmtools::utl::exp(__VA_ARGS__); \
    NMTOOLS_ASSERT_CLOSE( result, expect::expected ); \
}

TEST_CASE("exp(case1)" * doctest::test_suite("utl"))
{
    EXP_SUBCASE( case1, x );
}

TEST_CASE("exp(case2)" * doctest::test_suite("utl"))
{
    EXP_SUBCASE( case2, x );
}

TEST_CASE("exp(case3)" * doctest::test_suite("utl"))
{
    EXP_SUBCASE( case3, x );
}

TEST_CASE("exp(case4)" * doctest::test_suite("utl"))
{
    EXP_SUBCASE( case4, x );
}

TEST_CASE("exp(case5)" * doctest::test_suite("utl"))
{
    EXP_SUBCASE( case5, x );
}

// TODO: fix, precision
TEST_CASE("exp(case6)" * doctest::test_suite("utl") * doctest::may_fail())
{
    EXP_SUBCASE( case6, x );
}

// TODO: fix, precision
TEST_CASE("exp(case7)" * doctest::test_suite("utl") * doctest::may_fail())
{
    EXP_SUBCASE( case7, x );
}

TEST_CASE("exp(case8)" * doctest::test_suite("utl"))
{
    EXP_SUBCASE( case8, x );
}

NMTOOLS_TESTING_DECLARE_CASE(utl,log)
{
    namespace utl = nmtools::utl;

    NMTOOLS_TESTING_DECLARE_ARGS(case1)
    {
        auto x = 0.001f;
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case1)
    {
        auto expected = std::log(0.001f);
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case2)
    {
        auto x = 0.5f;
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case2)
    {
        auto expected = std::log(0.5f);
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case3)
    {
        auto x = 1.0f;
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case3)
    {
        auto expected = std::log(1.0f);
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
        auto expected = std::log(10.f);
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case6)
    {
        auto x = 100.f;
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case6)
    {
        auto expected = std::log(100.f);
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case7)
    {
        auto x = 1000000.f;
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case7)
    {
        auto expected = std::log(1000000.f);
    }
}

#define LOG_SUBCASE(case_name,...) \
SUBCASE(#case_name) \
{ \
    NMTOOLS_TESTING_USE_CASE( utl, log, case_name ); \
    using namespace args; \
    auto result = nmtools::utl::log(__VA_ARGS__); \
    NMTOOLS_ASSERT_CLOSE( result, expect::expected ); \
}

TEST_CASE("log(case1)" * doctest::test_suite("utl"))
{
    LOG_SUBCASE( case1, x );
}

TEST_CASE("log(case2)" * doctest::test_suite("utl"))
{
    LOG_SUBCASE( case2, x );
}

TEST_CASE("log(case3)" * doctest::test_suite("utl"))
{
    LOG_SUBCASE( case3, x );
}

TEST_CASE("log(case4)" * doctest::test_suite("utl"))
{
    LOG_SUBCASE( case4, x );
}

TEST_CASE("log(case5)" * doctest::test_suite("utl"))
{
    LOG_SUBCASE( case5, x );
}

TEST_CASE("log(case6)" * doctest::test_suite("utl"))
{
    LOG_SUBCASE( case6, x );
}

TEST_CASE("log(case7)" * doctest::test_suite("utl"))
{
    LOG_SUBCASE( case7, x );
}

NMTOOLS_TESTING_DECLARE_CASE(utl,log10)
{
    namespace utl = nmtools::utl;

    NMTOOLS_TESTING_DECLARE_ARGS(case1)
    {
        auto x = 0.01f;
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case1)
    {
        auto expected = std::log10(args::x);
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case2)
    {
        auto x = 0.1f;
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case2)
    {
        auto expected = std::log10(args::x);
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case3)
    {
        auto x = 1.f;
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case3)
    {
        auto expected = std::log10(args::x);
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case4)
    {
        auto x = 5.f;
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case4)
    {
        auto expected = std::log10(args::x);
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case5)
    {
        auto x = 10.f;
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case5)
    {
        auto expected = std::log10(args::x);
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case6)
    {
        auto x = 100.f;
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case6)
    {
        auto expected = std::log10(args::x);
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case7)
    {
        auto x = 1000.f;
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case7)
    {
        auto expected = std::log10(args::x);
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case8)
    {
        auto x = 12345.6f;
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case8)
    {
        auto expected = std::log10(args::x);
    }
}

#define LOG10_SUBCASE(case_name, ...) \
SUBCASE(#case_name) \
{ \
    NMTOOLS_TESTING_USE_CASE( utl, log10, case_name ); \
    using namespace args; \
    auto result = nmtools::utl::log10( __VA_ARGS__ ); \
    NMTOOLS_ASSERT_CLOSE( result, expect::expected ); \
}

TEST_CASE("log10(case1)" * doctest::test_suite("utl"))
{
    LOG10_SUBCASE( case1, x );
}

TEST_CASE("log10(case2)" * doctest::test_suite("utl"))
{
    LOG10_SUBCASE( case2, x );
}

TEST_CASE("log10(case3)" * doctest::test_suite("utl"))
{
    LOG10_SUBCASE( case3, x );
}

TEST_CASE("log10(case4)" * doctest::test_suite("utl"))
{
    LOG10_SUBCASE( case4, x );
}

TEST_CASE("log10(case5)" * doctest::test_suite("utl"))
{
    LOG10_SUBCASE( case5, x );
}

TEST_CASE("log10(case6)" * doctest::test_suite("utl"))
{
    LOG10_SUBCASE( case6, x );
}

TEST_CASE("log10(case7)" * doctest::test_suite("utl"))
{
    LOG10_SUBCASE( case7, x );
}

TEST_CASE("log10(case8)" * doctest::test_suite("utl"))
{
    LOG10_SUBCASE( case8, x );
}

NMTOOLS_TESTING_DECLARE_CASE(utl,log2)
{
    namespace utl = nmtools::utl;

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
        auto x = 1.f;
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case3)
    {
        auto expected = std::log2(args::x);
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case4)
    {
        auto x = 2.f;
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case4)
    {
        auto expected = std::log2(args::x);
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case5)
    {
        auto x = 3.14159f;
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case5)
    {
        auto expected = std::log2(args::x);
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case6)
    {
        auto x = 10.f;
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case6)
    {
        auto expected = std::log2(args::x);
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case7)
    {
        auto x = 1024.f;
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case7)
    {
        auto expected = std::log2(args::x);
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case8)
    {
        auto x = 65536.f;
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case8)
    {
        auto expected = std::log2(args::x);
    }
}

#define LOG2_SUBCASE(case_name, ...) \
SUBCASE(#case_name) \
{ \
    NMTOOLS_TESTING_USE_CASE( utl, log2, case_name ); \
    using namespace args; \
    auto result = nmtools::utl::log2( __VA_ARGS__ ); \
    NMTOOLS_ASSERT_CLOSE( result, expect::expected ); \
}

TEST_CASE("log2(case1)" * doctest::test_suite("utl"))
{
    LOG2_SUBCASE( case1, x );
}

TEST_CASE("log2(case2)" * doctest::test_suite("utl"))
{
    LOG2_SUBCASE( case2, x );
}

TEST_CASE("log2(case3)" * doctest::test_suite("utl"))
{
    LOG2_SUBCASE( case3, x );
}

TEST_CASE("log2(case4)" * doctest::test_suite("utl"))
{
    LOG2_SUBCASE( case4, x );
}

TEST_CASE("log2(case5)" * doctest::test_suite("utl"))
{
    LOG2_SUBCASE( case5, x );
}

TEST_CASE("log2(case6)" * doctest::test_suite("utl"))
{
    LOG2_SUBCASE( case6, x );
}

TEST_CASE("log2(case7)" * doctest::test_suite("utl"))
{
    LOG2_SUBCASE( case7, x );
}

TEST_CASE("log2(case8)" * doctest::test_suite("utl"))
{
    LOG2_SUBCASE( case8, x );
}