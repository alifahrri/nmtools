#include "nmtools/utl/fmath.hpp"
#include "nmtools/testing/doctest.hpp"

// TODO: increase precision
#undef NMTOOLS_TESTING_PRECISION
#define NMTOOLS_TESTING_PRECISION (1e-3)

namespace utl = nmtools::utl;

NMTOOLS_TESTING_DECLARE_CASE(utl, get_exponent_bits)
{
    NMTOOLS_TESTING_DECLARE_ARGS(case1)
    {
        float x = 1.0f;
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case1)
    {
        auto expected = 0;
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case2)
    {
        float x = 2.0f;
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case2)
    {
        auto expected = 1;
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case3)
    {
        float x = 0.5f;
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case3)
    {
        auto expected = -1;
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case4)
    {
        float x = 8.0f;
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case4)
    {
        auto expected = 3;
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case5)
    {
        float x = 0.125f;
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case5)
    {
        auto expected = -3;
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case6)
    {
        float x = 6.5f;
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case6)
    {
        auto expected = 2;
    }
}

#define GET_EXPONENT_BITS_SUBCASE(case_name, ...) \
{ \
    NMTOOLS_TESTING_USE_CASE(utl, get_exponent_bits, case_name); \
    using namespace args; \
    auto result = nmtools::utl::get_exponent_bits(__VA_ARGS__); \
    NMTOOLS_ASSERT_EQUAL( result, expect::expected ); \
}

TEST_CASE("get_exponent_bits(case1)" * doctest::test_suite("utl"))
{
    GET_EXPONENT_BITS_SUBCASE(case1, x)
}

TEST_CASE("get_exponent_bits(case2)" * doctest::test_suite("utl"))
{
    GET_EXPONENT_BITS_SUBCASE(case2, x)
}

TEST_CASE("get_exponent_bits(case3)" * doctest::test_suite("utl"))
{
    GET_EXPONENT_BITS_SUBCASE(case3, x)
}

TEST_CASE("get_exponent_bits(case4)" * doctest::test_suite("utl"))
{
    GET_EXPONENT_BITS_SUBCASE(case4, x)
}

TEST_CASE("get_exponent_bits(case5)" * doctest::test_suite("utl"))
{
    GET_EXPONENT_BITS_SUBCASE(case5, x)
}

TEST_CASE("get_exponent_bits(case6)" * doctest::test_suite("utl"))
{
    GET_EXPONENT_BITS_SUBCASE(case6, x)
}

NMTOOLS_TESTING_DECLARE_CASE(utl,copysign)
{
    NMTOOLS_TESTING_DECLARE_ARGS(case1)
    {
        auto x = 5.0f;
        auto y = 2.0f;
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case1)
    {
        auto result = 5.0f;
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case2)
    {
        auto x = 5.0f;
        auto y = -2.0f;
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case2)
    {
        auto result = -5.0f;
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case3)
    {
        auto x = -5.0f;
        auto y = -2.0f;
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case3)
    {
        auto result = -5.0f;
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case4)
    {
        auto x = -5.0f;
        auto y = 2.0f;
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case4)
    {
        auto result = 5.0f;
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case5)
    {
        auto x = 0.0f;
        auto y = -1.0f;
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case5)
    {
        auto result = -0.0f;
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case6)
    {
        auto x = 0.0f;
        auto y = 0.5f;
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case6)
    {
        auto result = 0.0f;
    }
}

#define COPYSIGN_SUBCASE(case_name, ...) \
{ \
    NMTOOLS_TESTING_USE_CASE(utl, copysign, case_name); \
    using namespace args; \
    auto result = nmtools::utl::copysign(__VA_ARGS__); \
    NMTOOLS_ASSERT_EQUAL( *(uint32_t*)(&result), *(uint32_t*)(&expect::result) ); \
    NMTOOLS_ASSERT_CLOSE( result, expect::result ); \
}

TEST_CASE("copysign(case1)" * doctest::test_suite("utl"))
{
    COPYSIGN_SUBCASE(case1, x, y);
}

TEST_CASE("copysign(case2)" * doctest::test_suite("utl"))
{
    COPYSIGN_SUBCASE(case2, x, y);
}

TEST_CASE("copysign(case3)" * doctest::test_suite("utl"))
{
    COPYSIGN_SUBCASE(case3, x, y);
}

TEST_CASE("copysign(case4)" * doctest::test_suite("utl"))
{
    COPYSIGN_SUBCASE(case4, x, y);
}

TEST_CASE("copysign(case5)" * doctest::test_suite("utl"))
{
    COPYSIGN_SUBCASE(case5, x, y);
}

TEST_CASE("copysign(case6)" * doctest::test_suite("utl"))
{
    COPYSIGN_SUBCASE(case6, x, y);
}

NMTOOLS_TESTING_DECLARE_CASE(utl,trunc)
{
    NMTOOLS_TESTING_DECLARE_ARGS(case1)
    {
        auto x_d = 2.7;
        auto x = static_cast<float>(x_d);
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case1)
    {
        auto expected = 2.0f;
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case2)
    {
        auto x_d = -3.9;
        auto x = static_cast<float>(x_d);
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case2)
    {
        auto expected = std::trunc(args::x);
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case3)
    {
        auto x_d = 16777216.0;
        auto x = static_cast<float>(x_d);
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case3)
    {
        auto expected = 16777216.0f;
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case4)
    {
        auto x_d = 0.5;
        auto x = static_cast<float>(x_d);
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case4)
    {
        auto expected = 0.0f;
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case5)
    {
        auto x_d = -0.8;
        auto x = static_cast<float>(x_d);
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case5)
    {
        auto expected = std::trunc(args::x);
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case6)
    {
        auto x_d = 8388607.5;
        auto x = static_cast<float>(x_d);
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case6)
    {
        auto expected = 8388607.0f;
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case7)
    {
        auto x_d = 4.0;
        auto x = static_cast<float>(x_d);
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case7)
    {
        auto expected = 4.0f;
    }
}

#define TRUNC_SUBCASE(case_name,...) \
SUBCASE(#case_name) \
{ \
    NMTOOLS_TESTING_USE_CASE(utl,trunc,case_name); \
    using namespace args; \
    auto result = utl::trunc(__VA_ARGS__); \
    NMTOOLS_ASSERT_CLOSE( result, expect::expected ); \
}

TEST_CASE("trunc(case1)" * doctest::test_suite("utl"))
{
    TRUNC_SUBCASE( case1, x );
    TRUNC_SUBCASE( case1, x_d );
}

TEST_CASE("trunc(case2)" * doctest::test_suite("utl"))
{
    TRUNC_SUBCASE( case2, x );
    TRUNC_SUBCASE( case2, x_d );
}

TEST_CASE("trunc(case3)" * doctest::test_suite("utl"))
{
    TRUNC_SUBCASE( case3, x );
    TRUNC_SUBCASE( case3, x_d );
}

TEST_CASE("trunc(case4)" * doctest::test_suite("utl"))
{
    TRUNC_SUBCASE( case4, x );
    TRUNC_SUBCASE( case4, x_d );
}

TEST_CASE("trunc(case5)" * doctest::test_suite("utl"))
{
    TRUNC_SUBCASE( case5, x );
    TRUNC_SUBCASE( case5, x_d );
}

TEST_CASE("trunc(case6)" * doctest::test_suite("utl"))
{
    TRUNC_SUBCASE( case6, x );
    TRUNC_SUBCASE( case6, x_d );
}

TEST_CASE("trunc(case7)" * doctest::test_suite("utl"))
{
    TRUNC_SUBCASE( case7, x );
    TRUNC_SUBCASE( case7, x_d );
}

NMTOOLS_TESTING_DECLARE_CASE(utl,fmod)
{
    NMTOOLS_TESTING_DECLARE_ARGS(case1)
    {
        auto x = 5.3f;
        auto y = 2.0f;
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case1)
    {
        auto expected = 1.3f;
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case2)
    {
        auto x = 6.0f;
        auto y = 2.0f;
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case2)
    {
        auto expected = 0.0f;
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case3)
    {
        auto x = -5.3f;
        auto y = 2.0f;
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case3)
    {
        auto expected = -1.3f;
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case4)
    {
        auto x = 5.3f;
        auto y = -2.0f;
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case4)
    {
        auto expected = 1.3f;
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case5)
    {
        auto x = -5.3f;
        auto y = -2.0f;
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case5)
    {
        auto expected = -1.3f;
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case6)
    {
        auto x = 1.5f;
        auto y = 10.0f;
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case6)
    {
        auto expected = 1.5f;
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case7)
    {
        auto x = 100.3f;
        auto y = 7.0f;
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case7)
    {
        auto expected = 2.3f;
    }
}

#define FMOD_SUBCASE(case_name, ...) \
SUBCASE(#case_name) \
{ \
    NMTOOLS_TESTING_USE_CASE(utl,fmod,case_name); \
    using namespace args; \
    auto result = nmtools::utl::fmod(__VA_ARGS__); \
    NMTOOLS_ASSERT_EQUAL( *(uint32_t*)&result, *(uint32_t*)&expect::expected ); \
    NMTOOLS_ASSERT_CLOSE( result, expect::expected ); \
}

TEST_CASE("fmod(case1)" * doctest::test_suite("utl") * doctest::may_fail())
{
    FMOD_SUBCASE( case1, x, y );
}

TEST_CASE("fmod(case2)" * doctest::test_suite("utl") * doctest::may_fail())
{
    FMOD_SUBCASE( case2, x, y );
}

TEST_CASE("fmod(case3)" * doctest::test_suite("utl") * doctest::may_fail())
{
    FMOD_SUBCASE( case3, x, y );
}

TEST_CASE("fmod(case4)" * doctest::test_suite("utl") * doctest::may_fail())
{
    FMOD_SUBCASE( case4, x, y );
}

TEST_CASE("fmod(case5)" * doctest::test_suite("utl") * doctest::may_fail())
{
    FMOD_SUBCASE( case5, x, y );
}

TEST_CASE("fmod(case6)" * doctest::test_suite("utl") * doctest::may_fail())
{
    FMOD_SUBCASE( case6, x, y );
}

TEST_CASE("fmod(case7)" * doctest::test_suite("utl") * doctest::may_fail())
{
    FMOD_SUBCASE( case7, x, y );
}

NMTOOLS_TESTING_DECLARE_CASE(utl,frexp)
{
    NMTOOLS_TESTING_DECLARE_ARGS(case1)
    {
        auto x_f = 8.0f;
        auto x_d = 8.0;

        #ifdef NMTOOLS_HAS_FLOAT16
        auto x_h = static_cast<float16_t>(x_f);
        #endif
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case1)
    {
        auto fraction = 0.5;
        auto exp = 4;
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case2)
    {
        auto x_f = 5.3f;
        auto x_d = 5.3;

        #ifdef NMTOOLS_HAS_FLOAT16
        auto x_h = static_cast<float16_t>(x_f);
        #endif
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case2)
    {
        auto fraction = 0.66250;
        auto exp = 3;
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case3)
    {
        auto x_f = 0.5f;
        auto x_d = 0.5;

        #ifdef NMTOOLS_HAS_FLOAT16
        auto x_h = static_cast<float16_t>(x_f);
        #endif
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case3)
    {
        auto fraction = 0.5;
        auto exp = 0;
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case4)
    {
        auto x_f = 100.f;
        auto x_d = 100.;

        #ifdef NMTOOLS_HAS_FLOAT16
        auto x_h = static_cast<float16_t>(x_f);
        #endif
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case4)
    {
        auto fraction = 0.78125;
        auto exp = 7;
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case5)
    {
        auto x_f = -12.0f;
        auto x_d = -12.0;

        #ifdef NMTOOLS_HAS_FLOAT16
        auto x_h = static_cast<float16_t>(x_f);
        #endif
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case5)
    {
        auto fraction = -0.75;
        auto exp = 4;
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case6)
    {
        auto x_f = 0.0f;
        auto x_d = 0.0;

        #ifdef NMTOOLS_HAS_FLOAT16
        auto x_h = static_cast<float16_t>(x_f);
        #endif
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case6)
    {
        auto fraction = 0.;
        auto exp = 0;
    }
}

#define FREXP_SUBCASE(case_name, x) \
{ \
    NMTOOLS_TESTING_USE_CASE(utl,frexp,case_name); \
    using namespace args; \
    int exp; \
    auto result = nmtools::utl::frexp(x,&exp); \
    NMTOOLS_ASSERT_EQUAL( exp, expect::exp ); \
    NMTOOLS_ASSERT_CLOSE( result, expect::fraction ); \
}

TEST_CASE("frexp(case1)" * doctest::test_suite("utl"))
{
    FREXP_SUBCASE( case1, x_f );
    FREXP_SUBCASE( case1, x_d );

    #ifdef NMTOOLS_HAS_FLOAT16
    FREXP_SUBCASE( case1, x_h );
    #endif
}

TEST_CASE("frexp(case2)" * doctest::test_suite("utl"))
{
    FREXP_SUBCASE( case2, x_f );
    FREXP_SUBCASE( case2, x_d );

    #ifdef NMTOOLS_HAS_FLOAT16
    FREXP_SUBCASE( case1, x_h );
    #endif
}

TEST_CASE("frexp(case3)" * doctest::test_suite("utl"))
{
    FREXP_SUBCASE( case3, x_f );
    FREXP_SUBCASE( case3, x_d );

    #ifdef NMTOOLS_HAS_FLOAT16
    FREXP_SUBCASE( case1, x_h );
    #endif
}

TEST_CASE("frexp(case4)" * doctest::test_suite("utl"))
{
    FREXP_SUBCASE( case4, x_f );
    FREXP_SUBCASE( case4, x_d );

    #ifdef NMTOOLS_HAS_FLOAT16
    FREXP_SUBCASE( case1, x_h );
    #endif
}

TEST_CASE("frexp(case5)" * doctest::test_suite("utl"))
{
    FREXP_SUBCASE( case5, x_f );
    FREXP_SUBCASE( case5, x_d );

    #ifdef NMTOOLS_HAS_FLOAT16
    FREXP_SUBCASE( case1, x_h );
    #endif
}

TEST_CASE("frexp(case6)" * doctest::test_suite("utl"))
{
    FREXP_SUBCASE( case6, x_f );
    FREXP_SUBCASE( case6, x_d );

    #ifdef NMTOOLS_HAS_FLOAT16
    FREXP_SUBCASE( case1, x_h );
    #endif
}

NMTOOLS_TESTING_DECLARE_CASE(utl,ldexp)
{
    NMTOOLS_TESTING_DECLARE_ARGS(case1)
    {
        auto val_d = 5.3;
        auto val_f = 5.3f;
        int exponent = 4;
        #ifdef NMTOOLS_HAS_FLOAT16
        auto val_h = static_cast<float16_t>(val_f);
        #endif
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case1)
    {
        auto res_d = std::ldexp(args::val_d,args::exponent);
        auto res_f = std::ldexp(args::val_f,args::exponent);
        #ifdef NMTOOLS_HAS_FLOAT16
        auto res_h = std::ldexp((float)args::val_h,args::exponent);
        #endif // NMTOOLS_HAS_FLOAT16
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case2)
    {
        auto val_d = -1.5;
        auto val_f = -1.5f;
        int exponent = -2;
        #ifdef NMTOOLS_HAS_FLOAT16
        auto val_h = static_cast<float16_t>(val_f);
        #endif
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case2)
    {
        auto res_d = std::ldexp(args::val_d,args::exponent);
        auto res_f = std::ldexp(args::val_f,args::exponent);
        #ifdef NMTOOLS_HAS_FLOAT16
        auto res_h = std::ldexp((float)args::val_h,args::exponent);
        #endif // NMTOOLS_HAS_FLOAT16
    }
}

#define LDEXP_SUBCASE(case_name, expected, ...) \
SUBCASE(#case_name) \
{ \
    NMTOOLS_TESTING_USE_CASE( utl, ldexp, case_name ); \
    using namespace args; \
    auto result = nmtools::utl::ldexp(__VA_ARGS__); \
    NMTOOLS_ASSERT_CLOSE( result, expect::expected ); \
}

TEST_CASE("ldexp(case1)" * doctest::test_suite("utl"))
{
    LDEXP_SUBCASE( case1, res_d, val_d, exponent );
    LDEXP_SUBCASE( case1, res_f, val_f, exponent );
    #ifdef NMTOOLS_HAS_FLOAT16
    LDEXP_SUBCASE( case1, res_h, val_h, exponent );
    #endif // NMTOOLS_HAS_FLOAT16
}

TEST_CASE("ldexp(case2)" * doctest::test_suite("utl"))
{
    LDEXP_SUBCASE( case2, res_d, val_d, exponent );
    LDEXP_SUBCASE( case2, res_f, val_f, exponent );
    #ifdef NMTOOLS_HAS_FLOAT16
    LDEXP_SUBCASE( case2, res_h, val_h, exponent );
    #endif // NMTOOLS_HAS_FLOAT16
}

NMTOOLS_TESTING_DECLARE_CASE(utl,sqrt)
{
    NMTOOLS_TESTING_DECLARE_ARGS(case1)
    {
        auto x = 25.f;
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case1)
    {
        auto expected = 5.f;
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case2)
    {
        auto x = 2.f;
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case2)
    {
        auto expected = 1.41421356237;
    }
}

#define SQRT_SUBCASE(case_name, ...) \
SUBCASE(#case_name) \
{ \
    NMTOOLS_TESTING_USE_CASE(utl,sqrt,case_name); \
    using namespace args; \
    auto result = nmtools::utl::sqrt(__VA_ARGS__); \
    NMTOOLS_ASSERT_CLOSE( result, expect::expected ); \
}

TEST_CASE("sqrt(case1)" * doctest::test_suite("utl"))
{
    SQRT_SUBCASE( case1, x );
}

TEST_CASE("sqrt(case2)" * doctest::test_suite("utl"))
{
    SQRT_SUBCASE( case2, x );
}

NMTOOLS_TESTING_DECLARE_CASE(utl,ilogb)
{
    NMTOOLS_TESTING_DECLARE_ARGS(case1)
    {
        auto x_f = 3.0f;
        auto x_d = 3.0;

        #ifdef NMTOOLS_HAS_FLOAT16
        auto x_h = static_cast<float16_t>(x_f);
        #endif // NMTOOLS_HAS_FLOAT16
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case1)
    {
        auto expected = std::ilogb(args::x_d);
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case2)
    {
        auto x_f = 1024.f;
        auto x_d = 1024.;

        #ifdef NMTOOLS_HAS_FLOAT16
        auto x_h = static_cast<float16_t>(x_f);
        #endif // NMTOOLS_HAS_FLOAT16
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case2)
    {
        auto expected = std::ilogb(args::x_d);
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case3)
    {
        auto x_f = 0.0625f;
        auto x_d = 0.0625;

        #ifdef NMTOOLS_HAS_FLOAT16
        auto x_h = static_cast<float16_t>(x_f);
        #endif // NMTOOLS_HAS_FLOAT16
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case3)
    {
        auto expected = std::ilogb(args::x_d);
    }
}

#define ILOGB_SUBCASE(case_name, ...) \
SUBCASE(#case_name) \
{ \
    NMTOOLS_TESTING_USE_CASE(utl,ilogb,case_name); \
    using namespace args; \
    auto result = nmtools::utl::ilogb(__VA_ARGS__); \
    NMTOOLS_ASSERT_CLOSE( result, expect::expected ); \
}

TEST_CASE("ilogb(case1)" * doctest::test_suite("utl"))
{
    ILOGB_SUBCASE( case1, x_f );
    ILOGB_SUBCASE( case1, x_d );

    #ifdef NMTOOLS_HAS_FLOAT16
    ILOGB_SUBCASE( case1, x_h );
    #endif // NMTOOLS_HAS_FLOAT16
}

TEST_CASE("ilogb(case2)" * doctest::test_suite("utl"))
{
    ILOGB_SUBCASE( case2, x_f );
    ILOGB_SUBCASE( case2, x_d );

    #ifdef NMTOOLS_HAS_FLOAT16
    ILOGB_SUBCASE( case2, x_h );
    #endif // NMTOOLS_HAS_FLOAT16
}

TEST_CASE("ilogb(case3)" * doctest::test_suite("utl"))
{
    ILOGB_SUBCASE( case3, x_f );
    ILOGB_SUBCASE( case3, x_d );

    #ifdef NMTOOLS_HAS_FLOAT16
    ILOGB_SUBCASE( case3, x_h );
    #endif // NMTOOLS_HAS_FLOAT16
}

NMTOOLS_TESTING_DECLARE_CASE(utl,remainder)
{
    NMTOOLS_TESTING_DECLARE_ARGS(case1)
    {
        auto x_d = 5.3;
        auto x_f = static_cast<float>(x_d);
        auto y_d = 2.0;
        auto y_f = static_cast<float>(y_d);
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case1)
    {
        auto expected = std::remainder(args::x_d, args::y_d);
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case2)
    {
        auto x_d = 5.0;
        auto x_f = static_cast<float>(x_d);
        auto y_d = 2.0;
        auto y_f = static_cast<float>(y_d);
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case2)
    {
        auto expected = std::remainder(args::x_d, args::y_d);
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case3)
    {
        auto x_d = 7.0;
        auto x_f = static_cast<float>(x_d);
        auto y_d = 2.0;
        auto y_f = static_cast<float>(y_d);
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case3)
    {
        auto expected = std::remainder(args::x_d, args::y_d);
    }
}

#define REMAINDER_SUBCASE(case_name,...) \
SUBCASE(#case_name) \
{ \
    NMTOOLS_TESTING_USE_CASE(utl,remainder,case_name); \
    using namespace args; \
    auto result = nmtools::utl::remainder(__VA_ARGS__); \
    NMTOOLS_ASSERT_CLOSE( result, expect::expected ); \
}

TEST_CASE("remainder(case1)" * doctest::test_suite("utl"))
{
    REMAINDER_SUBCASE( case1, x_f, y_f );
    REMAINDER_SUBCASE( case1, x_d, y_d );
}

TEST_CASE("remainder(case2)" * doctest::test_suite("utl"))
{
    REMAINDER_SUBCASE( case2, x_f, y_f );
    REMAINDER_SUBCASE( case2, x_d, y_d );
}

TEST_CASE("remainder(case3)" * doctest::test_suite("utl"))
{
    REMAINDER_SUBCASE( case3, x_f, y_f );
    REMAINDER_SUBCASE( case3, x_d, y_d );
}