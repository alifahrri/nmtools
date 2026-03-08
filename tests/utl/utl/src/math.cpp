#include "nmtools/utl/math.hpp"
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

NMTOOLS_TESTING_DECLARE_CASE(utl,copy_sign)
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

#define COPY_SIGN_SUBCASE(case_name, ...) \
{ \
    NMTOOLS_TESTING_USE_CASE(utl, copy_sign, case_name); \
    using namespace args; \
    auto result = nmtools::utl::copy_sign(__VA_ARGS__); \
    NMTOOLS_ASSERT_EQUAL( *(uint32_t*)(&result), *(uint32_t*)(&expect::result) ); \
    NMTOOLS_ASSERT_CLOSE( result, expect::result ); \
}

TEST_CASE("copy_sign(case1)" * doctest::test_suite("utl"))
{
    COPY_SIGN_SUBCASE(case1, x, y);
}

TEST_CASE("copy_sign(case2)" * doctest::test_suite("utl"))
{
    COPY_SIGN_SUBCASE(case2, x, y);
}

TEST_CASE("copy_sign(case3)" * doctest::test_suite("utl"))
{
    COPY_SIGN_SUBCASE(case3, x, y);
}

TEST_CASE("copy_sign(case4)" * doctest::test_suite("utl"))
{
    COPY_SIGN_SUBCASE(case4, x, y);
}

TEST_CASE("copy_sign(case5)" * doctest::test_suite("utl"))
{
    COPY_SIGN_SUBCASE(case5, x, y);
}

TEST_CASE("copy_sign(case6)" * doctest::test_suite("utl"))
{
    COPY_SIGN_SUBCASE(case6, x, y);
}

NMTOOLS_TESTING_DECLARE_CASE(utl,create_integer_mask)
{
    using namespace nmtools::literals;

    NMTOOLS_TESTING_DECLARE_ARGS(case1)
    {
        auto exponent = 23;
        auto exponent_ct = 23_ct;
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case1)
    {
        auto expected = 0xFFFFFFFF;
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case2)
    {
        auto exponent = 0;
        auto exponent_ct = 0_ct;
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case2)
    {
        auto expected = 0xFF800000;
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case3)
    {
        auto exponent = 1;
        auto exponent_ct = 1_ct;
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case3)
    {
        auto expected = 0xFFC00000;
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case4)
    {
        auto exponent = -1;
        auto exponent_ct = ct_v<-1>;
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case4)
    {
        auto expected = 0x80000000;
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case5)
    {
        auto exponent = 22;
        auto exponent_ct = 22_ct;
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case5)
    {
        auto expected = 0xFFFFFFFE;
    }
}

#define CREATE_INTEGER_MASK_SUBCASE(case_name, ...) \
SUBCASE(#case_name) \
{ \
    NMTOOLS_TESTING_USE_CASE(utl,create_integer_mask,case_name) \
    using namespace args; \
    auto result = nmtools::utl::create_integer_mask(__VA_ARGS__); \
    NMTOOLS_ASSERT_EQUAL( result, expect::expected ); \
}

TEST_CASE("create_integer_mask(case1)" * doctest::test_suite("utl"))
{
    CREATE_INTEGER_MASK_SUBCASE( case1, exponent );
}

TEST_CASE("create_integer_mask(case2)" * doctest::test_suite("utl"))
{
    CREATE_INTEGER_MASK_SUBCASE( case2, exponent );
}

TEST_CASE("create_integer_mask(case3)" * doctest::test_suite("utl"))
{
    CREATE_INTEGER_MASK_SUBCASE( case3, exponent );
}

TEST_CASE("create_integer_mask(case4)" * doctest::test_suite("utl"))
{
    CREATE_INTEGER_MASK_SUBCASE( case4, exponent );
}

TEST_CASE("create_integer_mask(case5)" * doctest::test_suite("utl"))
{
    CREATE_INTEGER_MASK_SUBCASE( case5, exponent );
}

NMTOOLS_TESTING_DECLARE_CASE(utl,bitwise_and)
{
    NMTOOLS_TESTING_DECLARE_ARGS(case1)
    {
        auto x = 2.7f;
        auto mask = 0xFFFFFFFF;
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case1)
    {
        auto expected = 2.7f;
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case2)
    {
        auto x = 2.7f;
        auto mask = 0x00000000;
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case2)
    {
        auto expected = 0.0f;
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case3)
    {
        auto x = 2.7f;
        auto mask = 0xFFC00000;
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case3)
    {
        auto expected = 2.0f;
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case4)
    {
        auto x = -3.9f;
        auto mask = 0xFFE00000;
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case4)
    {
        auto expected = -3.5f;
    }
}

#define BITWISE_AND(case_name, ...) \
SUBCASE(#case_name) \
{ \
    NMTOOLS_TESTING_USE_CASE(utl,bitwise_and,case_name) \
    using namespace args; \
    auto result = utl::bitwise_and(__VA_ARGS__); \
    NMTOOLS_ASSERT_EQUAL( *(uint32_t*)&result, *(uint32_t*)&expect::expected ); \
    NMTOOLS_ASSERT_CLOSE( result, expect::expected ); \
}

TEST_CASE("bitwise_and(case1)" * doctest::test_suite("utl"))
{
    BITWISE_AND( case1, x, mask );
}

TEST_CASE("bitwise_and(case2)" * doctest::test_suite("utl"))
{
    BITWISE_AND( case2, x, mask );
}

TEST_CASE("bitwise_and(case3)" * doctest::test_suite("utl"))
{
    BITWISE_AND( case3, x, mask );
}

TEST_CASE("bitwise_and(case4)" * doctest::test_suite("utl"))
{
    BITWISE_AND( case4, x, mask );
}

NMTOOLS_TESTING_DECLARE_CASE(utl,trunc)
{
    NMTOOLS_TESTING_DECLARE_ARGS(case1)
    {
        auto x = 2.7f;
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case1)
    {
        auto expected = 2.0f;
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case2)
    {
        auto x = -3.9f;
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case2)
    {
        auto expected = -3.0f;
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case3)
    {
        auto x = 16777216.0f;
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case3)
    {
        auto expected = 16777216.0f;
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case4)
    {
        auto x = 0.5f;
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case4)
    {
        auto expected = 0.0f;
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case5)
    {
        auto x = -0.8f;
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case5)
    {
        auto expected = -0.0f;
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case6)
    {
        auto x = 8388607.5f;
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case6)
    {
        auto expected = 8388607.0f;
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case7)
    {
        auto x = 4.0f;
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
    NMTOOLS_ASSERT_EQUAL( *(uint32_t*)&result, *(uint32_t*)&expect::expected ); \
    NMTOOLS_ASSERT_CLOSE( result, expect::expected ); \
}

TEST_CASE("trunc(case1)" * doctest::test_suite("utl"))
{
    TRUNC_SUBCASE( case1, x );
}

TEST_CASE("trunc(case2)" * doctest::test_suite("utl"))
{
    TRUNC_SUBCASE( case2, x );
}

TEST_CASE("trunc(case3)" * doctest::test_suite("utl"))
{
    TRUNC_SUBCASE( case3, x );
}

TEST_CASE("trunc(case4)" * doctest::test_suite("utl"))
{
    TRUNC_SUBCASE( case4, x );
}

TEST_CASE("trunc(case5)" * doctest::test_suite("utl"))
{
    TRUNC_SUBCASE( case5, x );
}

TEST_CASE("trunc(case6)" * doctest::test_suite("utl"))
{
    TRUNC_SUBCASE( case6, x );
}

TEST_CASE("trunc(case7)" * doctest::test_suite("utl"))
{
    TRUNC_SUBCASE( case7, x );
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

NMTOOLS_TESTING_DECLARE_CASE(utl,taylor_cos)
{
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
        auto x = 0.5f;
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case2)
    {
        auto expected = 0.87758256189037f;
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case3)
    {
        auto x = 1.0f;
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case3)
    {
        auto expected = 0.54030230586814f;
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case4)
    {
        auto x = 1.570796f;
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case4)
    {
        auto expected = 3.2679e-7f;
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case5)
    {
        auto x = 3.141593f;
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case5)
    {
        auto expected = -1.0f;
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case6)
    {
        auto x = -0.785398f;
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case6)
    {
        auto expected = 0.70710678118655f;
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case7)
    {
        auto x = 6.283185f;
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case7)
    {
        auto expected = 1.0f;
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
        auto expected = 0.0f;
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case2)
    {
        auto x = 0.01f;
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case2)
    {
        auto expected = 0.00999983333417f;
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case3)
    {
        auto x = 0.5f;
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case3)
    {
        auto expected = 0.47942553860420f;
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case4)
    {
        auto x = 0.785398f;
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case4)
    {
        auto expected = 0.70710678118655f;
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case5)
    {
        auto x = 1.570796f;
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case5)
    {
        auto expected = 1.0f;
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case6)
    {
        auto x = 1.0f;
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case6)
    {
        auto expected = 0.84147098480790f;
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case7)
    {
        auto x = 3.141593f;
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case7)
    {
        auto expected = 1.2246e-16f;
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
        auto expected = 1.0f;
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case2)
    {
        auto x = 0.1f;
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case2)
    {
        auto expected = 1.10517091807565f;
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case3)
    {
        auto x = -0.1f;
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case3)
    {
        auto expected = 0.90483741803596f;
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case4)
    {
        auto x = 0.5f;
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case4)
    {
        auto expected = 1.64872127070013f;
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case5)
    {
        auto x = -0.5f;
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case5)
    {
        auto expected = 0.60653065971263f;
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case6)
    {
        auto x = 1.0f;
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case6)
    {
        auto expected = 2.71828182845905f;
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case7)
    {
        auto x = -1.0f;
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case7)
    {
        auto expected = 0.36787944117144f;
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
}

#define SOLVE_REMEZ_SUBCASE(case_name, ...) \
SUBCASE(#case_name) \
{ \
    NMTOOLS_TESTING_USE_CASE(utl,solve_remez,case_name); \
    using namespace args; \
    auto result = nmtools::utl::solve_remez(f,a,b,degree); \
    NMTOOLS_ASSERT_CLOSE( result, expect::expected ); \
}

#include <fenv.h>

// TODO: fix undefined behaviour, probably utl::vector
TEST_CASE("solve_remez(case1)" * doctest::test_suite("utl") * doctest::may_fail() * doctest::skip())
{
    // feenableexcept(FE_INVALID | FE_OVERFLOW | FE_DIVBYZERO);

    SOLVE_REMEZ_SUBCASE( case1, f, a, b, degree );
}

TEST_CASE("solve_remez(case2)" * doctest::test_suite("utl") * doctest::may_fail() * doctest::skip())
{
    // feenableexcept(FE_INVALID | FE_OVERFLOW | FE_DIVBYZERO);

    SOLVE_REMEZ_SUBCASE( case2, f, a, b, degree );
}

NMTOOLS_TESTING_DECLARE_CASE(utl,sin_poly)
{
    namespace utl = nmtools::utl;

    // --- x = 0.0f ---
    NMTOOLS_TESTING_DECLARE_ARGS(case1)
    {
        auto cos_coeffs = utl::array{1.000000f, -5.00000e-1f, 4.16666e-2f, -1.38888e-3f, 2.47998045e-4f, -2.72364189e-7};
        auto sin_coeffs = utl::array{1.000000f, -1.66667e-1f, 8.33333e-3f, -1.98412647e-4f, 2.75555594e-6f, -2.47766355e-8f};
        auto x = 0.0f;
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case1)
    {
        auto expected = std::sin(0.0f);
    }

    // --- x = 0.1f ---
    NMTOOLS_TESTING_DECLARE_ARGS(case2)
    {
        auto cos_coeffs = utl::array{1.000000f, -5.00000e-1f, 4.16666e-2f, -1.38888e-3f, 2.47998045e-4f, -2.72364189e-7};
        auto sin_coeffs = utl::array{1.000000f, -1.66667e-1f, 8.33333e-3f, -1.98412647e-4f, 2.75555594e-6f, -2.47766355e-8f};
        auto x = 0.1f;
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case2)
    {
        auto expected = std::sin(0.1f);
    }

    // --- x = 0.2f ---
    NMTOOLS_TESTING_DECLARE_ARGS(case3)
    {
        auto cos_coeffs = utl::array{1.000000f, -5.00000e-1f, 4.16666e-2f, -1.38888e-3f, 2.47998045e-4f, -2.72364189e-7};
        auto sin_coeffs = utl::array{1.000000f, -1.66667e-1f, 8.33333e-3f, -1.98412647e-4f, 2.75555594e-6f, -2.47766355e-8f};
        auto x = 0.2f;
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case3)
    {
        auto expected = std::sin(0.2f);
    }

    // --- x = 0.3f ---
    NMTOOLS_TESTING_DECLARE_ARGS(case4)
    {
        auto cos_coeffs = utl::array{1.000000f, -5.00000e-1f, 4.16666e-2f, -1.38888e-3f, 2.47998045e-4f, -2.72364189e-7};
        auto sin_coeffs = utl::array{1.000000f, -1.66667e-1f, 8.33333e-3f, -1.98412647e-4f, 2.75555594e-6f, -2.47766355e-8f};
        auto x = 0.3f;
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case4)
    {
        auto expected = std::sin(0.3f);
    }

    // --- x = 0.4f ---
    NMTOOLS_TESTING_DECLARE_ARGS(case5)
    {
        auto cos_coeffs = utl::array{1.000000f, -5.00000e-1f, 4.16666e-2f, -1.38888e-3f, 2.47998045e-4f, -2.72364189e-7};
        auto sin_coeffs = utl::array{1.000000f, -1.66667e-1f, 8.33333e-3f, -1.98412647e-4f, 2.75555594e-6f, -2.47766355e-8f};
        auto x = 0.4f;
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case5)
    {
        auto expected = std::sin(0.4f);
    }

    // --- x = 0.5f ---
    NMTOOLS_TESTING_DECLARE_ARGS(case6)
    {
        auto cos_coeffs = utl::array{1.000000f, -5.00000e-1f, 4.16666e-2f, -1.38888e-3f, 2.47998045e-4f, -2.72364189e-7};
        auto sin_coeffs = utl::array{1.000000f, -1.66667e-1f, 8.33333e-3f, -1.98412647e-4f, 2.75555594e-6f, -2.47766355e-8f};
        auto x = 0.5f;
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case6)
    {
        auto expected = std::sin(0.5f);
    }

    // --- x = pi/4 approx ---
    NMTOOLS_TESTING_DECLARE_ARGS(case7)
    {
        auto cos_coeffs = utl::array{1.000000f, -5.00000e-1f, 4.16666e-2f, -1.38888e-3f, 2.47998045e-4f, -2.72364189e-7};
        auto sin_coeffs = utl::array{1.000000f, -1.66667e-1f, 8.33333e-3f, -1.98412647e-4f, 2.75555594e-6f, -2.47766355e-8f};
        auto x = 0.785398; 
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case7)
    {
        auto expected = std::sin(0.785398f);
    }

    // --- x = 1.0f ---
    NMTOOLS_TESTING_DECLARE_ARGS(case8)
    {
        auto cos_coeffs = utl::array{1.000000f, -5.00000e-1f, 4.16666e-2f, -1.38888e-3f, 2.47998045e-4f, -2.72364189e-7};
        auto sin_coeffs = utl::array{1.000000f, -1.66667e-1f, 8.33333e-3f, -1.98412647e-4f, 2.75555594e-6f, -2.47766355e-8f};
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

    // --- x = 0.0f ---
    NMTOOLS_TESTING_DECLARE_ARGS(case1)
    {
        auto cos_coeffs = utl::array{1.000000f, -5.00000e-1f, 4.16666e-2f, -1.38888e-3f, 2.47998045e-4f, -2.72364189e-7};
        auto sin_coeffs = utl::array{1.000000f, -1.66667e-1f, 8.33333e-3f, -1.98412647e-4f, 2.75555594e-6f, -2.47766355e-8f};
        auto x = 0.0f;
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case1)
    {
        auto expected = std::cos(0.0f);
    }

    // --- x = 0.1f ---
    NMTOOLS_TESTING_DECLARE_ARGS(case2)
    {
        auto cos_coeffs = utl::array{1.000000f, -5.00000e-1f, 4.16666e-2f, -1.38888e-3f, 2.47998045e-4f, -2.72364189e-7};
        auto sin_coeffs = utl::array{1.000000f, -1.66667e-1f, 8.33333e-3f, -1.98412647e-4f, 2.75555594e-6f, -2.47766355e-8f};
        auto x = 0.1f;
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case2)
    {
        auto expected = std::cos(0.1f);
    }

    // --- x = 0.2f ---
    NMTOOLS_TESTING_DECLARE_ARGS(case3)
    {
        auto cos_coeffs = utl::array{1.000000f, -5.00000e-1f, 4.16666e-2f, -1.38888e-3f, 2.47998045e-4f, -2.72364189e-7};
        auto sin_coeffs = utl::array{1.000000f, -1.66667e-1f, 8.33333e-3f, -1.98412647e-4f, 2.75555594e-6f, -2.47766355e-8f};
        auto x = 0.2f;
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case3)
    {
        auto expected = std::cos(0.2f);
    }

    // --- x = 0.3f ---
    NMTOOLS_TESTING_DECLARE_ARGS(case4)
    {
        auto cos_coeffs = utl::array{1.000000f, -5.00000e-1f, 4.16666e-2f, -1.38888e-3f, 2.47998045e-4f, -2.72364189e-7};
        auto sin_coeffs = utl::array{1.000000f, -1.66667e-1f, 8.33333e-3f, -1.98412647e-4f, 2.75555594e-6f, -2.47766355e-8f};
        auto x = 0.3f;
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case4)
    {
        auto expected = std::cos(0.3f);
    }

    // --- x = 0.4f ---
    NMTOOLS_TESTING_DECLARE_ARGS(case5)
    {
        auto cos_coeffs = utl::array{1.000000f, -5.00000e-1f, 4.16666e-2f, -1.38888e-3f, 2.47998045e-4f, -2.72364189e-7};
        auto sin_coeffs = utl::array{1.000000f, -1.66667e-1f, 8.33333e-3f, -1.98412647e-4f, 2.75555594e-6f, -2.47766355e-8f};
        auto x = 0.4f;
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case5)
    {
        auto expected = std::cos(0.4f);
    }

    // --- x = 0.5f ---
    NMTOOLS_TESTING_DECLARE_ARGS(case6)
    {
        auto cos_coeffs = utl::array{1.000000f, -5.00000e-1f, 4.16666e-2f, -1.38888e-3f, 2.47998045e-4f, -2.72364189e-7};
        auto sin_coeffs = utl::array{1.000000f, -1.66667e-1f, 8.33333e-3f, -1.98412647e-4f, 2.75555594e-6f, -2.47766355e-8f};
        auto x = 0.5f;
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case6)
    {
        auto expected = std::cos(0.5f);
    }

    // --- x = pi/4 approx ---
    NMTOOLS_TESTING_DECLARE_ARGS(case7)
    {
        auto cos_coeffs = utl::array{1.000000f, -5.00000e-1f, 4.16666e-2f, -1.38888e-3f, 2.47998045e-4f, -2.72364189e-7};
        auto sin_coeffs = utl::array{1.000000f, -1.66667e-1f, 8.33333e-3f, -1.98412647e-4f, 2.75555594e-6f, -2.47766355e-8f};
        auto x = 0.785398; 
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case7)
    {
        auto expected = std::cos(0.785398f);
    }

    // --- x = 1.0f ---
    NMTOOLS_TESTING_DECLARE_ARGS(case8)
    {
        auto cos_coeffs = utl::array{1.000000f, -5.00000e-1f, 4.16666e-2f, -1.38888e-3f, 2.47998045e-4f, -2.72364189e-7};
        auto sin_coeffs = utl::array{1.000000f, -1.66667e-1f, 8.33333e-3f, -1.98412647e-4f, 2.75555594e-6f, -2.47766355e-8f};
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

NMTOOLS_TESTING_DECLARE_CASE(utl,cos)
{
    namespace utl = nmtools::utl;

    // --- x = 0.0f ---
    NMTOOLS_TESTING_DECLARE_ARGS(case1)
    {
        auto x = 0.0f;
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case1)
    {
        auto expected = std::cos(0.0f);
    }

    // --- x = 0.1f ---
    NMTOOLS_TESTING_DECLARE_ARGS(case2)
    {
        auto x = 0.1f;
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case2)
    {
        auto expected = std::cos(0.1f);
    }

    // --- x = 0.2f ---
    NMTOOLS_TESTING_DECLARE_ARGS(case3)
    {
        auto x = 0.2f;
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case3)
    {
        auto expected = std::cos(0.2f);
    }

    // --- x = 0.3f ---
    NMTOOLS_TESTING_DECLARE_ARGS(case4)
    {
        auto x = 0.3f;
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case4)
    {
        auto expected = std::cos(0.3f);
    }

    // --- x = 0.4f ---
    NMTOOLS_TESTING_DECLARE_ARGS(case5)
    {
        auto x = 0.4f;
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case5)
    {
        auto expected = std::cos(0.4f);
    }

    // --- x = 0.5f ---
    NMTOOLS_TESTING_DECLARE_ARGS(case6)
    {
        auto x = 0.5f;
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case6)
    {
        auto expected = std::cos(0.5f);
    }

    // --- x = pi/4 approx ---
    NMTOOLS_TESTING_DECLARE_ARGS(case7)
    {
        auto x = 0.785398f; 
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case7)
    {
        auto expected = std::cos(0.785398f);
    }

    // --- x = 1.0f ---
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