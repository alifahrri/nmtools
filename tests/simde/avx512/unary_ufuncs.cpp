#include "nmtools/evaluator/simd/simde_avx512.hpp"
#include "nmtools/array/arange.hpp"
#include "nmtools/array/ufuncs/add.hpp"
#include "nmtools/array/ufuncs/sqrt.hpp"
#include "nmtools/array/ufuncs/ceil.hpp"
#include "nmtools/array/ufuncs/floor.hpp"
#include "nmtools/array/activations/hardtanh.hpp"
#include "nmtools/array/activations/hardshrink.hpp"
#include "nmtools/array/activations/hardswish.hpp"
#include "nmtools/array/activations/leaky_relu.hpp"
#include "nmtools/array/activations/prelu.hpp"
#include "nmtools/array/activations/relu.hpp"
#include "nmtools/array/activations/relu6.hpp"
#include "nmtools/array/activations/softshrink.hpp"
#include "nmtools/array/activations/softsign.hpp"
#include "nmtools/testing/doctest.hpp"

namespace nm = nmtools;
namespace na = nm::array;
namespace simd = na::simd;

#define SIMD_TEST_EQUAL(result, expect) \
{ \
    NMTOOLS_ASSERT_EQUAL( nm::shape(result), nm::shape(expect) ); \
    NMTOOLS_ASSERT_CLOSE( result, expect ); \
}

#define SIMDE_AVX512_TEST(array,fn,...) \
{ \
    auto expect = na::fn(array,##__VA_ARGS__); \
    auto result = na::fn(array,##__VA_ARGS__,simd::simde_AVX512); \
    SIMD_TEST_EQUAL(result,expect); \
}

/*********************** sqrt ******************************/

TEST_CASE("sqrt(case1)" * doctest::test_suite("simd::simde_avx512"))
{
    auto array  = na::arange(128);
    SIMDE_AVX512_TEST(array,sqrt);
}

TEST_CASE("sqrt(case2)" * doctest::test_suite("simd::simde_avx512"))
{
    auto array  = na::arange(128,nm::float64);
    SIMDE_AVX512_TEST(array,sqrt);
}

TEST_CASE("sqrt(case3)" * doctest::test_suite("simd::simde_avx512"))
{
    auto array  = na::arange(0,8,0.125);
    SIMDE_AVX512_TEST(array,sqrt);
}

TEST_CASE("sqrt(case4)" * doctest::test_suite("simd::simde_avx512"))
{
    auto array  = na::arange(129);
    SIMDE_AVX512_TEST(array,sqrt);
}

TEST_CASE("sqrt(case5)" * doctest::test_suite("simd::simde_avx512"))
{
    auto array  = na::arange(127);
    SIMDE_AVX512_TEST(array,sqrt);
}

TEST_CASE("sqrt(case6)" * doctest::test_suite("simd::simde_avx512"))
{
    auto array  = na::arange(129,nm::float64);
    SIMDE_AVX512_TEST(array,sqrt);
}

TEST_CASE("sqrt(case7)" * doctest::test_suite("simd::simde_avx512"))
{
    auto array  = na::arange(127,nm::float64);
    SIMDE_AVX512_TEST(array,sqrt);
}

TEST_CASE("sqrt(case8)" * doctest::test_suite("simd::simde_avx512"))
{
    auto array  = na::arange(3);
    SIMDE_AVX512_TEST(array,sqrt);
}

TEST_CASE("sqrt(case9)" * doctest::test_suite("simd::simde_avx512"))
{
    auto array  = na::arange(5);
    SIMDE_AVX512_TEST(array,sqrt);
}

TEST_CASE("sqrt(case10)" * doctest::test_suite("simd::simde_avx512"))
{
    auto array  = na::arange(3);
    SIMDE_AVX512_TEST(array,sqrt);
}

TEST_CASE("sqrt(case11)" * doctest::test_suite("simd::simde_avx512"))
{
    auto array  = na::arange(1);
    SIMDE_AVX512_TEST(array,sqrt);
}

/*********************** ceil ******************************/

TEST_CASE("ceil(case1)" * doctest::test_suite("simd::simde_avx512"))
{
    auto array  = na::arange(128);
    SIMDE_AVX512_TEST(array,ceil);
}

TEST_CASE("ceil(case2)" * doctest::test_suite("simd::simde_avx512"))
{
    auto array  = na::arange(128,nm::float64);
    SIMDE_AVX512_TEST(array,ceil);
}

TEST_CASE("ceil(case3)" * doctest::test_suite("simd::simde_avx512"))
{
    auto array  = na::arange(0,8,0.125);
    SIMDE_AVX512_TEST(array,ceil);
}

TEST_CASE("ceil(case4)" * doctest::test_suite("simd::simde_avx512"))
{
    auto array  = na::arange(129);
    SIMDE_AVX512_TEST(array,ceil);
}

TEST_CASE("ceil(case5)" * doctest::test_suite("simd::simde_avx512"))
{
    auto array  = na::arange(127);
    SIMDE_AVX512_TEST(array,ceil);
}

TEST_CASE("ceil(case6)" * doctest::test_suite("simd::simde_avx512"))
{
    auto array  = na::arange(129,nm::float64);
    SIMDE_AVX512_TEST(array,ceil);
}

TEST_CASE("ceil(case7)" * doctest::test_suite("simd::simde_avx512"))
{
    auto array  = na::arange(127,nm::float64);
    SIMDE_AVX512_TEST(array,ceil);
}

TEST_CASE("ceil(case8)" * doctest::test_suite("simd::simde_avx512"))
{
    auto array  = na::arange(3);
    SIMDE_AVX512_TEST(array,ceil);
}

TEST_CASE("ceil(case9)" * doctest::test_suite("simd::simde_avx512"))
{
    auto array  = na::arange(5);
    SIMDE_AVX512_TEST(array,ceil);
}

TEST_CASE("ceil(case10)" * doctest::test_suite("simd::simde_avx512"))
{
    auto array  = na::arange(3);
    SIMDE_AVX512_TEST(array,ceil);
}

TEST_CASE("ceil(case11)" * doctest::test_suite("simd::simde_avx512"))
{
    auto array  = na::arange(1);
    SIMDE_AVX512_TEST(array,ceil);
}

/*********************** floor ******************************/

TEST_CASE("floor(case1)" * doctest::test_suite("simd::simde_avx512"))
{
    auto array  = na::arange(128);
    SIMDE_AVX512_TEST(array,floor);
}

TEST_CASE("floor(case2)" * doctest::test_suite("simd::simde_avx512"))
{
    auto array  = na::arange(128,nm::float64);
    SIMDE_AVX512_TEST(array,floor);
}

TEST_CASE("floor(case3)" * doctest::test_suite("simd::simde_avx512"))
{
    auto array  = na::arange(0,8,0.125);
    SIMDE_AVX512_TEST(array,floor);
}

TEST_CASE("floor(case4)" * doctest::test_suite("simd::simde_avx512"))
{
    auto array  = na::arange(129);
    SIMDE_AVX512_TEST(array,floor);
}

TEST_CASE("floor(case5)" * doctest::test_suite("simd::simde_avx512"))
{
    auto array  = na::arange(127);
    SIMDE_AVX512_TEST(array,floor);
}

TEST_CASE("floor(case6)" * doctest::test_suite("simd::simde_avx512"))
{
    auto array  = na::arange(129,nm::float64);
    SIMDE_AVX512_TEST(array,floor);
}

TEST_CASE("floor(case7)" * doctest::test_suite("simd::simde_avx512"))
{
    auto array  = na::arange(127,nm::float64);
    SIMDE_AVX512_TEST(array,floor);
}

TEST_CASE("floor(case8)" * doctest::test_suite("simd::simde_avx512"))
{
    auto array  = na::arange(3);
    SIMDE_AVX512_TEST(array,floor);
}

TEST_CASE("floor(case9)" * doctest::test_suite("simd::simde_avx512"))
{
    auto array  = na::arange(5);
    SIMDE_AVX512_TEST(array,floor);
}

TEST_CASE("floor(case10)" * doctest::test_suite("simd::simde_avx512"))
{
    auto array  = na::arange(3);
    SIMDE_AVX512_TEST(array,floor);
}

TEST_CASE("floor(case11)" * doctest::test_suite("simd::simde_avx512"))
{
    auto array  = na::arange(1);
    SIMDE_AVX512_TEST(array,floor);
}

/*********************** relu ******************************/

TEST_CASE("relu(case1)" * doctest::test_suite("simd::simde_avx512"))
{
    auto array  = na::arange(128);
    SIMDE_AVX512_TEST(array,relu);
}

TEST_CASE("relu(case2)" * doctest::test_suite("simd::simde_avx512"))
{
    auto array  = na::arange(128,nm::float64);
    SIMDE_AVX512_TEST(array,relu);
}

TEST_CASE("relu(case3)" * doctest::test_suite("simd::simde_avx512"))
{
    auto array  = na::arange(0,8,0.125);
    SIMDE_AVX512_TEST(array,relu);
}

TEST_CASE("relu(case4)" * doctest::test_suite("simd::simde_avx512"))
{
    auto array  = na::arange(129);
    SIMDE_AVX512_TEST(array,relu);
}

TEST_CASE("relu(case5)" * doctest::test_suite("simd::simde_avx512"))
{
    auto array  = na::arange(127);
    SIMDE_AVX512_TEST(array,relu);
}

TEST_CASE("relu(case6)" * doctest::test_suite("simd::simde_avx512"))
{
    auto array  = na::arange(129,nm::float64);
    SIMDE_AVX512_TEST(array,relu);
}

TEST_CASE("relu(case7)" * doctest::test_suite("simd::simde_avx512"))
{
    auto array  = na::arange(127,nm::float64);
    SIMDE_AVX512_TEST(array,relu);
}

TEST_CASE("relu(case8)" * doctest::test_suite("simd::simde_avx512"))
{
    auto array  = na::arange(3);
    SIMDE_AVX512_TEST(array,relu);
}

TEST_CASE("relu(case9)" * doctest::test_suite("simd::simde_avx512"))
{
    auto array  = na::arange(5);
    SIMDE_AVX512_TEST(array,relu);
}

TEST_CASE("relu(case10)" * doctest::test_suite("simd::simde_avx512"))
{
    auto array  = na::arange(3);
    SIMDE_AVX512_TEST(array,relu);
}

TEST_CASE("relu(case11)" * doctest::test_suite("simd::simde_avx512"))
{
    auto array  = na::arange(1);
    SIMDE_AVX512_TEST(array,relu);
}

/*********************** relu6 ******************************/

TEST_CASE("relu6(case1)" * doctest::test_suite("simd::simde_avx512"))
{
    auto array  = na::arange(128);
    SIMDE_AVX512_TEST(array,relu6);
}

TEST_CASE("relu6(case2)" * doctest::test_suite("simd::simde_avx512"))
{
    auto array  = na::arange(128,nm::float64);
    SIMDE_AVX512_TEST(array,relu6);
}

TEST_CASE("relu6(case3)" * doctest::test_suite("simd::simde_avx512"))
{
    auto array  = na::arange(0,8,0.125);
    SIMDE_AVX512_TEST(array,relu6);
}

TEST_CASE("relu6(case4)" * doctest::test_suite("simd::simde_avx512"))
{
    auto array  = na::arange(129);
    SIMDE_AVX512_TEST(array,relu6);
}

TEST_CASE("relu6(case5)" * doctest::test_suite("simd::simde_avx512"))
{
    auto array  = na::arange(127);
    SIMDE_AVX512_TEST(array,relu6);
}

TEST_CASE("relu6(case6)" * doctest::test_suite("simd::simde_avx512"))
{
    auto array  = na::arange(129,nm::float64);
    SIMDE_AVX512_TEST(array,relu6);
}

TEST_CASE("relu6(case7)" * doctest::test_suite("simd::simde_avx512"))
{
    auto array  = na::arange(127,nm::float64);
    SIMDE_AVX512_TEST(array,relu6);
}

TEST_CASE("relu6(case8)" * doctest::test_suite("simd::simde_avx512"))
{
    auto array  = na::arange(3);
    SIMDE_AVX512_TEST(array,relu6);
}

TEST_CASE("relu6(case9)" * doctest::test_suite("simd::simde_avx512"))
{
    auto array  = na::arange(5);
    SIMDE_AVX512_TEST(array,relu6);
}

TEST_CASE("relu6(case10)" * doctest::test_suite("simd::simde_avx512"))
{
    auto array  = na::arange(3);
    SIMDE_AVX512_TEST(array,relu6);
}

TEST_CASE("relu6(case11)" * doctest::test_suite("simd::simde_avx512"))
{
    auto array  = na::arange(1);
    SIMDE_AVX512_TEST(array,relu6);
}

/*********************** hardtanh ******************************/

TEST_CASE("hardtanh(case1)" * doctest::test_suite("simd::simde_avx512"))
{
    auto array  = na::arange(128);
    SIMDE_AVX512_TEST(array,hardtanh,-5.0f,5.0f);
}

TEST_CASE("hardtanh(case2)" * doctest::test_suite("simd::simde_avx512"))
{
    auto array  = na::arange(128);
    SIMDE_AVX512_TEST(array,hardtanh,-5.0,5.0);
}

TEST_CASE("hardtanh(case3)" * doctest::test_suite("simd::simde_avx512"))
{
    auto array  = na::arange(128);
    SIMDE_AVX512_TEST(array,hardtanh,-5,5);
}

TEST_CASE("hardtanh(case4)" * doctest::test_suite("simd::simde_avx512"))
{
    auto array  = na::arange(128,nm::float64);
    SIMDE_AVX512_TEST(array,hardtanh,-5.0f,5.0f);
}

TEST_CASE("hardtanh(case5)" * doctest::test_suite("simd::simde_avx512"))
{
    auto array  = na::arange(128,nm::float64);
    SIMDE_AVX512_TEST(array,hardtanh,-5.0,5.0);
}

TEST_CASE("hardtanh(case6)" * doctest::test_suite("simd::simde_avx512"))
{
    auto array  = na::arange(128,nm::float64);
    SIMDE_AVX512_TEST(array,hardtanh,-5,5);
}

TEST_CASE("hardtanh(case7)" * doctest::test_suite("simd::simde_avx512"))
{
    auto array  = na::arange(128,nm::float64);
    SIMDE_AVX512_TEST(array,hardtanh,-5,5ul);
}

/*********************** leaky_relu ******************************/

TEST_CASE("leaky_relu(case1)" * doctest::test_suite("simd::simde_avx512"))
{
    auto array  = na::arange(-64,64);
    SIMDE_AVX512_TEST(array,leaky_relu,0.01f);
}

TEST_CASE("leaky_relu(case2)" * doctest::test_suite("simd::simde_avx512"))
{
    auto array  = na::arange(-64,64);
    SIMDE_AVX512_TEST(array,leaky_relu,0.01);
}

TEST_CASE("leaky_relu(case3)" * doctest::test_suite("simd::simde_avx512"))
{
    auto array  = na::arange(-4,4,0.125);
    SIMDE_AVX512_TEST(array,leaky_relu,0.01f);
}

TEST_CASE("leaky_relu(case4)" * doctest::test_suite("simd::simde_avx512"))
{
    auto array  = na::arange(-64,64,nm::float64);
    SIMDE_AVX512_TEST(array,leaky_relu,0.01f);
}

TEST_CASE("leaky_relu(case5)" * doctest::test_suite("simd::simde_avx512"))
{
    auto array  = na::arange(-64,64,nm::float64);
    SIMDE_AVX512_TEST(array,leaky_relu,0.01);
}

TEST_CASE("leaky_relu(case6)" * doctest::test_suite("simd::simde_avx512"))
{
    auto array  = na::arange(-4,4,0.125,nm::float64);
    SIMDE_AVX512_TEST(array,leaky_relu,0.01f);
}

/*********************** prelu ******************************/

TEST_CASE("prelu(case1)" * doctest::test_suite("simd::simde_avx512"))
{
    auto array  = na::arange(-64,64);
    SIMDE_AVX512_TEST(array,prelu,0.01f);
}

TEST_CASE("prelu(case2)" * doctest::test_suite("simd::simde_avx512"))
{
    auto array  = na::arange(-64,64);
    SIMDE_AVX512_TEST(array,prelu,0.01);
}

TEST_CASE("prelu(case3)" * doctest::test_suite("simd::simde_avx512"))
{
    auto array  = na::arange(-4,4,0.125);
    SIMDE_AVX512_TEST(array,prelu,0.01f);
}

TEST_CASE("prelu(case4)" * doctest::test_suite("simd::simde_avx512"))
{
    auto array  = na::arange(-64,64,nm::float64);
    SIMDE_AVX512_TEST(array,prelu,0.01f);
}

TEST_CASE("prelu(case5)" * doctest::test_suite("simd::simde_avx512"))
{
    auto array  = na::arange(-64,64,nm::float64);
    SIMDE_AVX512_TEST(array,prelu,0.01);
}

TEST_CASE("prelu(case6)" * doctest::test_suite("simd::simde_avx512"))
{
    auto array  = na::arange(-4,4,0.125,nm::float64);
    SIMDE_AVX512_TEST(array,prelu,0.01f);
}

/*********************** softshrink ******************************/

TEST_CASE("softshrink(case1)" * doctest::test_suite("simd::simde_AVX512"))
{
    auto array  = na::arange(-64,64);
    SIMDE_AVX512_TEST(array,softshrink,3.0f);
}

TEST_CASE("softshrink(case2)" * doctest::test_suite("simd::simde_AVX512"))
{
    auto array  = na::arange(-64,64);
    SIMDE_AVX512_TEST(array,softshrink,3.0);
}

TEST_CASE("softshrink(case3)" * doctest::test_suite("simd::simde_AVX512"))
{
    auto array  = na::arange(-64,64);
    SIMDE_AVX512_TEST(array,softshrink,3);
}

TEST_CASE("softshrink(case4)" * doctest::test_suite("simd::simde_AVX512"))
{
    auto array  = na::arange(-64,64,nm::float64);
    SIMDE_AVX512_TEST(array,softshrink,3.0f);
}

TEST_CASE("softshrink(case5)" * doctest::test_suite("simd::simde_AVX512"))
{
    auto array  = na::arange(-64,64,nm::float64);
    SIMDE_AVX512_TEST(array,softshrink,3.0);
}

TEST_CASE("softshrink(case6)" * doctest::test_suite("simd::simde_AVX512"))
{
    auto array  = na::arange(-64,64,nm::float64);
    SIMDE_AVX512_TEST(array,softshrink,3);
}

/*********************** softsign ******************************/

TEST_CASE("softsign(case1)" * doctest::test_suite("simd::simde_AVX512"))
{
    auto array  = na::arange(-64,64);
    SIMDE_AVX512_TEST(array,softsign);
}

TEST_CASE("softsign(case2)" * doctest::test_suite("simd::simde_AVX512"))
{
    auto array  = na::arange(-4,4,0.125);
    SIMDE_AVX512_TEST(array,softsign);
}

TEST_CASE("softsign(case3)" * doctest::test_suite("simd::simde_AVX512"))
{
    auto array  = na::arange(-4,4,0.125f);
    SIMDE_AVX512_TEST(array,softsign);
}

TEST_CASE("softsign(case4)" * doctest::test_suite("simd::simde_AVX512"))
{
    auto array  = na::arange(-64,64,nm::float64);
    SIMDE_AVX512_TEST(array,softsign);
}

TEST_CASE("softsign(case5)" * doctest::test_suite("simd::simde_AVX512"))
{
    auto array  = na::arange(-4,4,0.125,nm::float64);
    SIMDE_AVX512_TEST(array,softsign);
}

TEST_CASE("softsign(case6)" * doctest::test_suite("simd::simde_AVX512"))
{
    auto array  = na::arange(-4,4,0.125f,nm::float64);
    SIMDE_AVX512_TEST(array,softsign);
}

/*********************** hardshrink ******************************/

TEST_CASE("hardshrink(case1)" * doctest::test_suite("simd::simde_AVX512"))
{
    auto array  = na::arange(-64,64);
    SIMDE_AVX512_TEST(array,hardshrink,3.0f);
}

TEST_CASE("hardshrink(case2)" * doctest::test_suite("simd::simde_AVX512"))
{
    auto array  = na::arange(-64,64);
    SIMDE_AVX512_TEST(array,hardshrink,3.0);
}

TEST_CASE("hardshrink(case3)" * doctest::test_suite("simd::simde_AVX512"))
{
    auto array  = na::arange(-64,64);
    SIMDE_AVX512_TEST(array,hardshrink,3);
}

TEST_CASE("hardshrink(case4)" * doctest::test_suite("simd::simde_AVX512"))
{
    auto array  = na::arange(-64,64,nm::float64);
    SIMDE_AVX512_TEST(array,hardshrink,3.0f);
}

TEST_CASE("hardshrink(case5)" * doctest::test_suite("simd::simde_AVX512"))
{
    auto array  = na::arange(-64,64,nm::float64);
    SIMDE_AVX512_TEST(array,hardshrink,3.0);
}

TEST_CASE("hardshrink(case6)" * doctest::test_suite("simd::simde_AVX512"))
{
    auto array  = na::arange(-64,64,nm::float64);
    SIMDE_AVX512_TEST(array,hardshrink,3);
}

/*********************** hardswish ******************************/

TEST_CASE("hardswish(case1)" * doctest::test_suite("simd::simde_AVX512"))
{
    auto array  = na::arange(-64,64);
    SIMDE_AVX512_TEST(array,hardswish);
}

TEST_CASE("hardswish(case2)" * doctest::test_suite("simd::simde_AVX512"))
{
    auto array  = na::arange(-4,4,0.125);
    SIMDE_AVX512_TEST(array,hardswish);
}

TEST_CASE("hardswish(case3)" * doctest::test_suite("simd::simde_AVX512"))
{
    auto array  = na::arange(-4,4,0.125f);
    SIMDE_AVX512_TEST(array,hardswish);
}

TEST_CASE("hardswish(case4)" * doctest::test_suite("simd::simde_AVX512"))
{
    auto array  = na::arange(-64,64,nm::float64);
    SIMDE_AVX512_TEST(array,hardswish);
}

TEST_CASE("hardswish(case5)" * doctest::test_suite("simd::simde_AVX512"))
{
    auto array  = na::arange(-4,4,0.125,nm::float64);
    SIMDE_AVX512_TEST(array,hardswish);
}

TEST_CASE("hardswish(case6)" * doctest::test_suite("simd::simde_AVX512"))
{
    auto array  = na::arange(-4,4,0.125f,nm::float64);
    SIMDE_AVX512_TEST(array,hardswish);
}