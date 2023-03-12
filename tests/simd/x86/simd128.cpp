#include "nmtools/array/eval/x86_simd128.hpp"
#include "nmtools/array/array/arange.hpp"
#include "nmtools/array/array/ufuncs/sqrt.hpp"
#include "nmtools/array/array/ufuncs/ceil.hpp"
#include "nmtools/array/array/ufuncs/floor.hpp"
#include "nmtools/array/array/ufuncs/reciprocal.hpp"
#include "nmtools/array/array/activations/hardtanh.hpp"
#include "nmtools/array/array/activations/relu.hpp"
#include "nmtools/array/array/activations/relu6.hpp"
#include "nmtools/testing/doctest.hpp"

namespace nm = nmtools;
namespace na = nm::array;

#define SIMD_TEST_EQUAL(result, expect) \
{ \
    NMTOOLS_ASSERT_EQUAL( nm::shape(result), nm::shape(expect) ); \
    NMTOOLS_ASSERT_CLOSE( result, expect ); \
}

#define SIMD128_TEST(array,fn) \
{ \
    auto expect = na::fn(array); \
    auto result = na::fn(array,na::Simd128x86); \
    SIMD_TEST_EQUAL(result,expect); \
}

/*********************** sqrt ******************************/

TEST_CASE("simd_sqrt(case1)" * doctest::test_suite("simd::128"))
{
    auto array  = na::arange(128);
    SIMD128_TEST(array,sqrt);
}

TEST_CASE("simd_sqrt(case2)" * doctest::test_suite("simd::128"))
{
    auto array  = na::arange(127);
    SIMD128_TEST(array,sqrt);
}

TEST_CASE("simd_sqrt(case3)" * doctest::test_suite("simd::128"))
{
    auto array  = na::arange(129);
    SIMD128_TEST(array,sqrt);
}

TEST_CASE("simd_sqrt(case4)" * doctest::test_suite("simd::128"))
{
    auto array  = na::arange(4);
    SIMD128_TEST(array,sqrt);
}

TEST_CASE("simd_sqrt(case5)" * doctest::test_suite("simd::128"))
{
    auto array  = na::arange(3);
    SIMD128_TEST(array,sqrt);
}

TEST_CASE("simd_sqrt(case6)" * doctest::test_suite("simd::128"))
{
    auto array  = na::arange(5);
    SIMD128_TEST(array,sqrt);
}

TEST_CASE("simd_sqrt(case7)" * doctest::test_suite("simd::128"))
{
    auto array  = na::arange(128,nm::float64);
    SIMD128_TEST(array,sqrt);
}

TEST_CASE("simd_sqrt(case8)" * doctest::test_suite("simd::128"))
{
    auto array  = na::arange(127,nm::float64);
    SIMD128_TEST(array,sqrt);
}

TEST_CASE("simd_sqrt(case9)" * doctest::test_suite("simd::128"))
{
    auto array  = na::arange(129,nm::float64);
    SIMD128_TEST(array,sqrt);
}

TEST_CASE("simd_sqrt(case10)" * doctest::test_suite("simd::128"))
{
    auto array  = na::arange(4,nm::float64);
    SIMD128_TEST(array,sqrt);
}

TEST_CASE("simd_sqrt(case11)" * doctest::test_suite("simd::128"))
{
    auto array  = na::arange(3,nm::float64);
    SIMD128_TEST(array,sqrt);
}

TEST_CASE("simd_sqrt(case12)" * doctest::test_suite("simd::128"))
{
    auto array  = na::arange(1,nm::float64);
    SIMD128_TEST(array,sqrt);
}

/*********************** ceil ******************************/

TEST_CASE("simd_ceil(case1)" * doctest::test_suite("simd::128"))
{
    auto array  = na::arange(128);
    SIMD128_TEST(array,ceil);
}

TEST_CASE("simd_ceil(case2)" * doctest::test_suite("simd::128"))
{
    auto array  = na::arange(127);
    SIMD128_TEST(array,ceil);
}

TEST_CASE("simd_ceil(case3)" * doctest::test_suite("simd::128"))
{
    auto array  = na::arange(129);
    SIMD128_TEST(array,ceil);
}

TEST_CASE("simd_ceil(case4)" * doctest::test_suite("simd::128"))
{
    auto array  = na::arange(4);
    SIMD128_TEST(array,ceil);
}

TEST_CASE("simd_ceil(case5)" * doctest::test_suite("simd::128"))
{
    auto array  = na::arange(3);
    SIMD128_TEST(array,ceil);
}

TEST_CASE("simd_ceil(case6)" * doctest::test_suite("simd::128"))
{
    auto array  = na::arange(5);
    SIMD128_TEST(array,ceil);
}

TEST_CASE("simd_ceil(case7)" * doctest::test_suite("simd::128"))
{
    auto array  = na::arange(128,nm::float64);
    SIMD128_TEST(array,ceil);
}

TEST_CASE("simd_ceil(case8)" * doctest::test_suite("simd::128"))
{
    auto array  = na::arange(127,nm::float64);
    SIMD128_TEST(array,ceil);
}

TEST_CASE("simd_ceil(case9)" * doctest::test_suite("simd::128"))
{
    auto array  = na::arange(129,nm::float64);
    SIMD128_TEST(array,ceil);
}

TEST_CASE("simd_ceil(case10)" * doctest::test_suite("simd::128"))
{
    auto array  = na::arange(4,nm::float64);
    SIMD128_TEST(array,ceil);
}

TEST_CASE("simd_ceil(case11)" * doctest::test_suite("simd::128"))
{
    auto array  = na::arange(3,nm::float64);
    SIMD128_TEST(array,ceil);
}

TEST_CASE("simd_ceil(case12)" * doctest::test_suite("simd::128"))
{
    auto array  = na::arange(1,nm::float64);
    SIMD128_TEST(array,ceil);
}

/*********************** floor ******************************/

TEST_CASE("simd_floor(case1)" * doctest::test_suite("simd::128"))
{
    auto array  = na::arange(128);
    SIMD128_TEST(array,floor);
}

TEST_CASE("simd_floor(case2)" * doctest::test_suite("simd::128"))
{
    auto array  = na::arange(127);
    SIMD128_TEST(array,floor);
}

TEST_CASE("simd_floor(case3)" * doctest::test_suite("simd::128"))
{
    auto array  = na::arange(129);
    SIMD128_TEST(array,floor);
}

TEST_CASE("simd_floor(case4)" * doctest::test_suite("simd::128"))
{
    auto array  = na::arange(4);
    SIMD128_TEST(array,floor);
}

TEST_CASE("simd_floor(case5)" * doctest::test_suite("simd::128"))
{
    auto array  = na::arange(3);
    SIMD128_TEST(array,floor);
}

TEST_CASE("simd_floor(case6)" * doctest::test_suite("simd::128"))
{
    auto array  = na::arange(5);
    SIMD128_TEST(array,floor);
}

TEST_CASE("simd_floor(case7)" * doctest::test_suite("simd::128"))
{
    auto array  = na::arange(128,nm::float64);
    SIMD128_TEST(array,floor);
}

TEST_CASE("simd_floor(case8)" * doctest::test_suite("simd::128"))
{
    auto array  = na::arange(127,nm::float64);
    SIMD128_TEST(array,floor);
}

TEST_CASE("simd_floor(case9)" * doctest::test_suite("simd::128"))
{
    auto array  = na::arange(129,nm::float64);
    SIMD128_TEST(array,floor);
}

TEST_CASE("simd_floor(case10)" * doctest::test_suite("simd::128"))
{
    auto array  = na::arange(4,nm::float64);
    SIMD128_TEST(array,floor);
}

TEST_CASE("simd_floor(case11)" * doctest::test_suite("simd::128"))
{
    auto array  = na::arange(3,nm::float64);
    SIMD128_TEST(array,floor);
}

TEST_CASE("simd_floor(case12)" * doctest::test_suite("simd::128"))
{
    auto array  = na::arange(1,nm::float64);
    SIMD128_TEST(array,floor);
}

/*********************** relu ******************************/

TEST_CASE("simd_relu(case1)" * doctest::test_suite("simd::128"))
{
    auto array  = na::arange(-64,64);
    SIMD128_TEST(array,relu);
}

TEST_CASE("simd_relu(case2)" * doctest::test_suite("simd::128"))
{
    auto array  = na::arange(-64,63);
    SIMD128_TEST(array,relu);
}

TEST_CASE("simd_relu(case3)" * doctest::test_suite("simd::128"))
{
    auto array  = na::arange(-64,65);
    SIMD128_TEST(array,relu);
}

TEST_CASE("simd_relu(case4)" * doctest::test_suite("simd::128"))
{
    auto array  = na::arange(-64,64,nm::float64);
    SIMD128_TEST(array,relu);
}

TEST_CASE("simd_relu(case5)" * doctest::test_suite("simd::128"))
{
    auto array  = na::arange(-64,63,nm::float64);
    SIMD128_TEST(array,relu);
}

TEST_CASE("simd_relu(case6)" * doctest::test_suite("simd::128"))
{
    auto array  = na::arange(-64,65,nm::float64);
    SIMD128_TEST(array,relu);
}

/*********************** relu6 ******************************/

TEST_CASE("simd_relu6(case1)" * doctest::test_suite("simd::128"))
{
    auto array  = na::arange(-64,64);
    SIMD128_TEST(array,relu6);
}

TEST_CASE("simd_relu6(case2)" * doctest::test_suite("simd::128"))
{
    auto array  = na::arange(-64,63);
    SIMD128_TEST(array,relu6);
}

TEST_CASE("simd_relu6(case3)" * doctest::test_suite("simd::128"))
{
    auto array  = na::arange(-64,65);
    SIMD128_TEST(array,relu6);
}

TEST_CASE("simd_relu6(case4)" * doctest::test_suite("simd::128"))
{
    auto array  = na::arange(-64,64,nm::float64);
    SIMD128_TEST(array,relu6);
}

TEST_CASE("simd_relu6(case5)" * doctest::test_suite("simd::128"))
{
    auto array  = na::arange(-64,63,nm::float64);
    SIMD128_TEST(array,relu6);
}

TEST_CASE("simd_relu6(case6)" * doctest::test_suite("simd::128"))
{
    auto array  = na::arange(-64,65,nm::float64);
    SIMD128_TEST(array,relu6);
}

/*********************** hardtanh ******************************/

TEST_CASE("simd_hardtanh(case1)" * doctest::test_suite("simd::128"))
{
    auto array  = na::arange(-64,64);

    auto expect = na::hardtanh(array,-5.0f,5.0f);
    auto result = na::hardtanh(array,-5.0f,5.0f,na::Simd128x86);
    SIMD_TEST_EQUAL(result,expect);
}

/*********************** reciprocal ******************************/

TEST_CASE("simd_reciprocal(case1)" * doctest::test_suite("simd::128") * doctest::may_fail())
{
    auto array  = na::arange(128);
    SIMD128_TEST(array,reciprocal);
}