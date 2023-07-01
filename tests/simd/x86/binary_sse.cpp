#include "nmtools/array/eval/simd/x86_sse.hpp"
#include "nmtools/array/array/arange.hpp"
#include "nmtools/array/array/ufuncs/add.hpp"
#include "nmtools/array/array/ufuncs/multiply.hpp"
#include "nmtools/array/array/ufuncs/subtract.hpp"
#include "nmtools/array/array/ufuncs/divide.hpp"
#include "nmtools/testing/doctest.hpp"

namespace nm = nmtools;
namespace na = nm::array;
namespace simd = na::simd;

#define SIMD_TEST_EQUAL(result, expect) \
{ \
    NMTOOLS_ASSERT_EQUAL( nm::shape(result), nm::shape(expect) ); \
    NMTOOLS_ASSERT_CLOSE( result, expect ); \
}

#define X86_SSE_TEST(array,fn,...) \
{ \
    auto expect = na::fn(array,##__VA_ARGS__); \
    auto result = na::fn(array,##__VA_ARGS__,simd::x86_SSE); \
    SIMD_TEST_EQUAL(result,expect); \
}

/*********************** add ******************************/

TEST_CASE("add(case1)" * doctest::test_suite("simd::x86_SSE"))
{
    auto lhs  = na::arange(128);
    auto rhs  = na::arange(128);
    X86_SSE_TEST(lhs,add,rhs);
}

TEST_CASE("add(case2)" * doctest::test_suite("simd::x86_SSE"))
{
    auto lhs  = na::arange(128,nm::float64);
    auto rhs  = na::arange(128,nm::float64);
    X86_SSE_TEST(lhs,add,rhs);
}

TEST_CASE("add(case3)" * doctest::test_suite("simd::x86_SSE"))
{
    auto lhs  = na::arange(0,8,0.125);
    auto rhs  = na::arange(0,8,0.125);
    X86_SSE_TEST(lhs,add,rhs);
}

TEST_CASE("add(case4)" * doctest::test_suite("simd::x86_SSE"))
{
    auto lhs  = na::arange(129);
    auto rhs  = na::arange(129);
    X86_SSE_TEST(lhs,add,rhs);
}

TEST_CASE("add(case5)" * doctest::test_suite("simd::x86_SSE"))
{
    auto lhs  = na::arange(127);
    auto rhs  = na::arange(127);
    X86_SSE_TEST(lhs,add,rhs);
}

TEST_CASE("add(case6)" * doctest::test_suite("simd::x86_SSE"))
{
    auto lhs  = na::arange(129,nm::float64);
    auto rhs  = na::arange(129,nm::float64);
    X86_SSE_TEST(lhs,add,rhs);
}

TEST_CASE("add(case7)" * doctest::test_suite("simd::x86_SSE"))
{
    auto lhs  = na::arange(127,nm::float64);
    auto rhs  = na::arange(127,nm::float64);
    X86_SSE_TEST(lhs,add,rhs);
}

TEST_CASE("add(case8)" * doctest::test_suite("simd::x86_SSE"))
{
    auto lhs  = na::arange(3);
    auto rhs  = na::arange(3);
    X86_SSE_TEST(lhs,add,rhs);
}

TEST_CASE("add(case9)" * doctest::test_suite("simd::x86_SSE"))
{
    auto lhs  = na::arange(5);
    auto rhs  = na::arange(5);
    X86_SSE_TEST(lhs,add,rhs);
}

TEST_CASE("add(case10)" * doctest::test_suite("simd::x86_SSE"))
{
    auto lhs  = na::arange(3,nm::float64);
    auto rhs  = na::arange(3,nm::float64);
    X86_SSE_TEST(lhs,add,rhs);
}

TEST_CASE("add(case11)" * doctest::test_suite("simd::x86_SSE"))
{
    auto lhs  = na::arange(5,nm::float64);
    auto rhs  = na::arange(5,nm::float64);
    X86_SSE_TEST(lhs,add,rhs);
}

TEST_CASE("add(case12)" * doctest::test_suite("simd::x86_SSE"))
{
    auto lhs  = na::arange(1);
    auto rhs  = na::arange(1);
    X86_SSE_TEST(lhs,add,rhs);
}

TEST_CASE("add(case13)" * doctest::test_suite("simd::x86_SSE"))
{
    auto lhs  = na::arange(1,nm::float64);
    auto rhs  = na::arange(1,nm::float64);
    X86_SSE_TEST(lhs,add,rhs);
}

TEST_CASE("add(case14)" * doctest::test_suite("simd::x86_SSE"))
{
    auto lhs  = na::arange(128,nm::uint64);
    auto rhs  = na::arange(128,nm::uint64);
    X86_SSE_TEST(lhs,add,rhs);
}

TEST_CASE("add(case15)" * doctest::test_suite("simd::x86_SSE"))
{
    auto lhs  = na::arange(128,nm::int64);
    auto rhs  = na::arange(128,nm::int64);
    X86_SSE_TEST(lhs,add,rhs);
}

TEST_CASE("add(case16)" * doctest::test_suite("simd::x86_SSE"))
{
    auto lhs  = na::arange(128,nm::uint32);
    auto rhs  = na::arange(128,nm::uint32);
    X86_SSE_TEST(lhs,add,rhs);
}

TEST_CASE("add(case17)" * doctest::test_suite("simd::x86_SSE"))
{
    auto lhs  = na::arange(128,nm::int32);
    auto rhs  = na::arange(128,nm::int32);
    X86_SSE_TEST(lhs,add,rhs);
}

TEST_CASE("add(case18)" * doctest::test_suite("simd::x86_SSE"))
{
    auto lhs  = na::arange(128,nm::uint16);
    auto rhs  = na::arange(128,nm::uint16);
    X86_SSE_TEST(lhs,add,rhs);
}

TEST_CASE("add(case19)" * doctest::test_suite("simd::x86_SSE"))
{
    auto lhs  = na::arange(128,nm::int16);
    auto rhs  = na::arange(128,nm::int16);
    X86_SSE_TEST(lhs,add,rhs);
}

TEST_CASE("add(case20)" * doctest::test_suite("simd::x86_SSE"))
{
    auto lhs  = na::arange(128,nm::uint8);
    auto rhs  = na::arange(128,nm::uint8);
    X86_SSE_TEST(lhs,add,rhs);
}

TEST_CASE("add(case21)" * doctest::test_suite("simd::x86_SSE"))
{
    auto lhs  = na::arange(128,nm::int8);
    auto rhs  = na::arange(128,nm::int8);
    X86_SSE_TEST(lhs,add,rhs);
}

TEST_CASE("add(case22)" * doctest::test_suite("simd::x86_SSE"))
{
    auto lhs  = na::arange(-128,127,nm::int64);
    auto rhs  = na::arange(-128,127,nm::int64);
    X86_SSE_TEST(lhs,add,rhs);
}

TEST_CASE("add(case23)" * doctest::test_suite("simd::x86_SSE"))
{
    auto lhs  = na::arange(-128,127,nm::int32);
    auto rhs  = na::arange(-128,127,nm::int32);
    X86_SSE_TEST(lhs,add,rhs);
}

TEST_CASE("add(case24)" * doctest::test_suite("simd::x86_SSE"))
{
    auto lhs  = na::arange(-128,127,nm::int16);
    auto rhs  = na::arange(-128,127,nm::int16);
    X86_SSE_TEST(lhs,add,rhs);
}

TEST_CASE("add(case25)" * doctest::test_suite("simd::x86_SSE"))
{
    auto lhs  = na::arange(-64,63,nm::int8);
    auto rhs  = na::arange(-64,63,nm::int8);
    X86_SSE_TEST(lhs,add,rhs);
}


/*********************** multiply ******************************/

TEST_CASE("multiply(case1)" * doctest::test_suite("simd::x86_SSE"))
{
    auto lhs  = na::arange(128);
    auto rhs  = na::arange(128);
    X86_SSE_TEST(lhs,multiply,rhs);
}

TEST_CASE("multiply(case2)" * doctest::test_suite("simd::x86_SSE"))
{
    auto lhs  = na::arange(128,nm::float64);
    auto rhs  = na::arange(128,nm::float64);
    X86_SSE_TEST(lhs,multiply,rhs);
}

TEST_CASE("multiply(case3)" * doctest::test_suite("simd::x86_SSE"))
{
    auto lhs  = na::arange(0,8,0.125);
    auto rhs  = na::arange(0,8,0.125);
    X86_SSE_TEST(lhs,multiply,rhs);
}

TEST_CASE("multiply(case4)" * doctest::test_suite("simd::x86_SSE"))
{
    auto lhs  = na::arange(129);
    auto rhs  = na::arange(129);
    X86_SSE_TEST(lhs,multiply,rhs);
}

TEST_CASE("multiply(case5)" * doctest::test_suite("simd::x86_SSE"))
{
    auto lhs  = na::arange(127);
    auto rhs  = na::arange(127);
    X86_SSE_TEST(lhs,multiply,rhs);
}

TEST_CASE("multiply(case6)" * doctest::test_suite("simd::x86_SSE"))
{
    auto lhs  = na::arange(129,nm::float64);
    auto rhs  = na::arange(129,nm::float64);
    X86_SSE_TEST(lhs,multiply,rhs);
}

TEST_CASE("multiply(case7)" * doctest::test_suite("simd::x86_SSE"))
{
    auto lhs  = na::arange(127,nm::float64);
    auto rhs  = na::arange(127,nm::float64);
    X86_SSE_TEST(lhs,multiply,rhs);
}

TEST_CASE("multiply(case8)" * doctest::test_suite("simd::x86_SSE"))
{
    auto lhs  = na::arange(3);
    auto rhs  = na::arange(3);
    X86_SSE_TEST(lhs,multiply,rhs);
}

TEST_CASE("multiply(case9)" * doctest::test_suite("simd::x86_SSE"))
{
    auto lhs  = na::arange(5);
    auto rhs  = na::arange(5);
    X86_SSE_TEST(lhs,multiply,rhs);
}

TEST_CASE("multiply(case10)" * doctest::test_suite("simd::x86_SSE"))
{
    auto lhs  = na::arange(3,nm::float64);
    auto rhs  = na::arange(3,nm::float64);
    X86_SSE_TEST(lhs,multiply,rhs);
}

TEST_CASE("multiply(case11)" * doctest::test_suite("simd::x86_SSE"))
{
    auto lhs  = na::arange(5,nm::float64);
    auto rhs  = na::arange(5,nm::float64);
    X86_SSE_TEST(lhs,multiply,rhs);
}

TEST_CASE("multiply(case12)" * doctest::test_suite("simd::x86_SSE"))
{
    auto lhs  = na::arange(1);
    auto rhs  = na::arange(1);
    X86_SSE_TEST(lhs,multiply,rhs);
}

TEST_CASE("multiply(case13)" * doctest::test_suite("simd::x86_SSE"))
{
    auto lhs  = na::arange(1,nm::float64);
    auto rhs  = na::arange(1,nm::float64);
    X86_SSE_TEST(lhs,multiply,rhs);
}

// 64-bit multiplication not supported yet
// There is no such _mm_mullo_epi64 in sse, only on avx512
// TODO: support 64-bit mul
#if 0
TEST_CASE("multiply(case14)" * doctest::test_suite("simd::x86_SSE"))
{
    auto lhs  = na::arange(128,nm::uint64);
    auto rhs  = na::arange(128,nm::uint64);
    X86_SSE_TEST(lhs,multiply,rhs);
}

TEST_CASE("multiply(case15)" * doctest::test_suite("simd::x86_SSE"))
{
    auto lhs  = na::arange(128,nm::int64);
    auto rhs  = na::arange(128,nm::int64);
    X86_SSE_TEST(lhs,multiply,rhs);
}
#endif

TEST_CASE("multiply(case16)" * doctest::test_suite("simd::x86_SSE"))
{
    auto lhs  = na::arange(128,nm::uint32);
    auto rhs  = na::arange(128,nm::uint32);
    X86_SSE_TEST(lhs,multiply,rhs);
}

TEST_CASE("multiply(case17)" * doctest::test_suite("simd::x86_SSE"))
{
    auto lhs  = na::arange(128,nm::int32);
    auto rhs  = na::arange(128,nm::int32);
    X86_SSE_TEST(lhs,multiply,rhs);
}

TEST_CASE("multiply(case18)" * doctest::test_suite("simd::x86_SSE"))
{
    auto lhs  = na::arange(128,nm::uint16);
    auto rhs  = na::arange(128,nm::uint16);
    X86_SSE_TEST(lhs,multiply,rhs);
}

TEST_CASE("multiply(case19)" * doctest::test_suite("simd::x86_SSE"))
{
    auto lhs  = na::arange(128,nm::int16);
    auto rhs  = na::arange(128,nm::int16);
    X86_SSE_TEST(lhs,multiply,rhs);
}

// 8-bit multiplication not supported yet
// TODO: support 8-bit mul
#if 0
TEST_CASE("multiply(case20)" * doctest::test_suite("simd::x86_SSE"))
{
    auto lhs  = na::arange(128,nm::uint8);
    auto rhs  = na::arange(128,nm::uint8);
    X86_SSE_TEST(lhs,multiply,rhs);
}

TEST_CASE("multiply(case21)" * doctest::test_suite("simd::x86_SSE"))
{
    auto lhs  = na::arange(128,nm::int8);
    auto rhs  = na::arange(128,nm::int8);
    X86_SSE_TEST(lhs,multiply,rhs);
}
#endif

// 64-bit multiplication not supported yet
// There is no such _mm_mullo_epi64 in sse, only on avx512
// TODO: support 64-bit mul
#if 0
TEST_CASE("multiply(case22)" * doctest::test_suite("simd::x86_SSE"))
{
    auto lhs  = na::arange(-128,127,nm::int64);
    auto rhs  = na::arange(-128,127,nm::int64);
    X86_SSE_TEST(lhs,multiply,rhs);
}
#endif

TEST_CASE("multiply(case23)" * doctest::test_suite("simd::x86_SSE"))
{
    auto lhs  = na::arange(-128,127,nm::int32);
    auto rhs  = na::arange(-128,127,nm::int32);
    X86_SSE_TEST(lhs,multiply,rhs);
}

TEST_CASE("multiply(case24)" * doctest::test_suite("simd::x86_SSE"))
{
    auto lhs  = na::arange(-128,127,nm::int16);
    auto rhs  = na::arange(-128,127,nm::int16);
    X86_SSE_TEST(lhs,multiply,rhs);
}

// 8-bit multiplication not supported yet
// TODO: support 8-bit mul
#if 0
TEST_CASE("multiply(case25)" * doctest::test_suite("simd::x86_SSE"))
{
    auto lhs  = na::arange(-64,63,nm::int8);
    auto rhs  = na::arange(-64,63,nm::int8);
    X86_SSE_TEST(lhs,multiply,rhs);
}
#endif

/*********************** subtract ******************************/

TEST_CASE("subtract(case1)" * doctest::test_suite("simd::x86_SSE"))
{
    auto lhs  = na::arange(128);
    auto rhs  = na::arange(128);
    X86_SSE_TEST(lhs,subtract,rhs);
}

TEST_CASE("subtract(case2)" * doctest::test_suite("simd::x86_SSE"))
{
    auto lhs  = na::arange(128,nm::float64);
    auto rhs  = na::arange(128,nm::float64);
    X86_SSE_TEST(lhs,subtract,rhs);
}

TEST_CASE("subtract(case3)" * doctest::test_suite("simd::x86_SSE"))
{
    auto lhs  = na::arange(0,8,0.125);
    auto rhs  = na::arange(0,8,0.125);
    X86_SSE_TEST(lhs,subtract,rhs);
}

TEST_CASE("subtract(case4)" * doctest::test_suite("simd::x86_SSE"))
{
    auto lhs  = na::arange(129);
    auto rhs  = na::arange(129);
    X86_SSE_TEST(lhs,subtract,rhs);
}

TEST_CASE("subtract(case5)" * doctest::test_suite("simd::x86_SSE"))
{
    auto lhs  = na::arange(127);
    auto rhs  = na::arange(127);
    X86_SSE_TEST(lhs,subtract,rhs);
}

TEST_CASE("subtract(case6)" * doctest::test_suite("simd::x86_SSE"))
{
    auto lhs  = na::arange(129,nm::float64);
    auto rhs  = na::arange(129,nm::float64);
    X86_SSE_TEST(lhs,subtract,rhs);
}

TEST_CASE("subtract(case7)" * doctest::test_suite("simd::x86_SSE"))
{
    auto lhs  = na::arange(127,nm::float64);
    auto rhs  = na::arange(127,nm::float64);
    X86_SSE_TEST(lhs,subtract,rhs);
}

TEST_CASE("subtract(case8)" * doctest::test_suite("simd::x86_SSE"))
{
    auto lhs  = na::arange(3);
    auto rhs  = na::arange(3);
    X86_SSE_TEST(lhs,subtract,rhs);
}

TEST_CASE("subtract(case9)" * doctest::test_suite("simd::x86_SSE"))
{
    auto lhs  = na::arange(5);
    auto rhs  = na::arange(5);
    X86_SSE_TEST(lhs,subtract,rhs);
}

TEST_CASE("subtract(case10)" * doctest::test_suite("simd::x86_SSE"))
{
    auto lhs  = na::arange(3,nm::float64);
    auto rhs  = na::arange(3,nm::float64);
    X86_SSE_TEST(lhs,subtract,rhs);
}

TEST_CASE("subtract(case11)" * doctest::test_suite("simd::x86_SSE"))
{
    auto lhs  = na::arange(5,nm::float64);
    auto rhs  = na::arange(5,nm::float64);
    X86_SSE_TEST(lhs,subtract,rhs);
}

TEST_CASE("subtract(case12)" * doctest::test_suite("simd::x86_SSE"))
{
    auto lhs  = na::arange(1);
    auto rhs  = na::arange(1);
    X86_SSE_TEST(lhs,subtract,rhs);
}

TEST_CASE("subtract(case13)" * doctest::test_suite("simd::x86_SSE"))
{
    auto lhs  = na::arange(1,nm::float64);
    auto rhs  = na::arange(1,nm::float64);
    X86_SSE_TEST(lhs,subtract,rhs);
}

TEST_CASE("subtract(case14)" * doctest::test_suite("simd::x86_SSE"))
{
    auto lhs  = na::arange(128,nm::uint64);
    auto rhs  = na::arange(128,nm::uint64);
    X86_SSE_TEST(lhs,subtract,rhs);
}

TEST_CASE("subtract(case15)" * doctest::test_suite("simd::x86_SSE"))
{
    auto lhs  = na::arange(128,nm::int64);
    auto rhs  = na::arange(128,nm::int64);
    X86_SSE_TEST(lhs,subtract,rhs);
}

TEST_CASE("subtract(case16)" * doctest::test_suite("simd::x86_SSE"))
{
    auto lhs  = na::arange(128,nm::uint32);
    auto rhs  = na::arange(128,nm::uint32);
    X86_SSE_TEST(lhs,subtract,rhs);
}

TEST_CASE("subtract(case17)" * doctest::test_suite("simd::x86_SSE"))
{
    auto lhs  = na::arange(128,nm::int32);
    auto rhs  = na::arange(128,nm::int32);
    X86_SSE_TEST(lhs,subtract,rhs);
}

TEST_CASE("subtract(case18)" * doctest::test_suite("simd::x86_SSE"))
{
    auto lhs  = na::arange(128,nm::uint16);
    auto rhs  = na::arange(128,nm::uint16);
    X86_SSE_TEST(lhs,subtract,rhs);
}

TEST_CASE("subtract(case19)" * doctest::test_suite("simd::x86_SSE"))
{
    auto lhs  = na::arange(128,nm::int16);
    auto rhs  = na::arange(128,nm::int16);
    X86_SSE_TEST(lhs,subtract,rhs);
}

TEST_CASE("subtract(case20)" * doctest::test_suite("simd::x86_SSE"))
{
    auto lhs  = na::arange(128,nm::uint8);
    auto rhs  = na::arange(128,nm::uint8);
    X86_SSE_TEST(lhs,subtract,rhs);
}

TEST_CASE("subtract(case21)" * doctest::test_suite("simd::x86_SSE"))
{
    auto lhs  = na::arange(128,nm::int8);
    auto rhs  = na::arange(128,nm::int8);
    X86_SSE_TEST(lhs,subtract,rhs);
}

TEST_CASE("subtract(case22)" * doctest::test_suite("simd::x86_SSE"))
{
    auto lhs  = na::arange(-128,127,nm::int64);
    auto rhs  = na::arange(-128,127,nm::int64);
    X86_SSE_TEST(lhs,subtract,rhs);
}

TEST_CASE("subtract(case23)" * doctest::test_suite("simd::x86_SSE"))
{
    auto lhs  = na::arange(-128,127,nm::int32);
    auto rhs  = na::arange(-128,127,nm::int32);
    X86_SSE_TEST(lhs,subtract,rhs);
}

TEST_CASE("subtract(case24)" * doctest::test_suite("simd::x86_SSE"))
{
    auto lhs  = na::arange(-128,127,nm::int16);
    auto rhs  = na::arange(-128,127,nm::int16);
    X86_SSE_TEST(lhs,subtract,rhs);
}

TEST_CASE("subtract(case25)" * doctest::test_suite("simd::x86_SSE"))
{
    auto lhs  = na::arange(-64,63,nm::int8);
    auto rhs  = na::arange(-64,63,nm::int8);
    X86_SSE_TEST(lhs,subtract,rhs);
}

/*********************** divide ******************************/

TEST_CASE("divide(case1)" * doctest::test_suite("simd::x86_SSE"))
{
    auto lhs  = na::arange(1,128);
    auto rhs  = na::arange(1,128);
    X86_SSE_TEST(lhs,divide,rhs);
}

TEST_CASE("divide(case2)" * doctest::test_suite("simd::x86_SSE"))
{
    auto lhs  = na::arange(1,128,nm::float64);
    auto rhs  = na::arange(1,128,nm::float64);
    X86_SSE_TEST(lhs,divide,rhs);
}

TEST_CASE("divide(case3)" * doctest::test_suite("simd::x86_SSE"))
{
    auto lhs  = na::arange(1,8,0.125);
    auto rhs  = na::arange(1,8,0.125);
    X86_SSE_TEST(lhs,divide,rhs);
}

TEST_CASE("divide(case4)" * doctest::test_suite("simd::x86_SSE"))
{
    auto lhs  = na::arange(1,129);
    auto rhs  = na::arange(1,129);
    X86_SSE_TEST(lhs,divide,rhs);
}

TEST_CASE("divide(case5)" * doctest::test_suite("simd::x86_SSE"))
{
    auto lhs  = na::arange(1,127);
    auto rhs  = na::arange(1,127);
    X86_SSE_TEST(lhs,divide,rhs);
}

TEST_CASE("divide(case6)" * doctest::test_suite("simd::x86_SSE"))
{
    auto lhs  = na::arange(1,129,nm::float64);
    auto rhs  = na::arange(1,129,nm::float64);
    X86_SSE_TEST(lhs,divide,rhs);
}

TEST_CASE("divide(case7)" * doctest::test_suite("simd::x86_SSE"))
{
    auto lhs  = na::arange(1,127,nm::float64);
    auto rhs  = na::arange(1,127,nm::float64);
    X86_SSE_TEST(lhs,divide,rhs);
}

TEST_CASE("divide(case8)" * doctest::test_suite("simd::x86_SSE"))
{
    auto lhs  = na::arange(1,3);
    auto rhs  = na::arange(1,3);
    X86_SSE_TEST(lhs,divide,rhs);
}

TEST_CASE("divide(case9)" * doctest::test_suite("simd::x86_SSE"))
{
    auto lhs  = na::arange(1,5);
    auto rhs  = na::arange(1,5);
    X86_SSE_TEST(lhs,divide,rhs);
}

TEST_CASE("divide(case10)" * doctest::test_suite("simd::x86_SSE"))
{
    auto lhs  = na::arange(1,3,nm::float64);
    auto rhs  = na::arange(1,3,nm::float64);
    X86_SSE_TEST(lhs,divide,rhs);
}

TEST_CASE("divide(case11)" * doctest::test_suite("simd::x86_SSE"))
{
    auto lhs  = na::arange(1,5,nm::float64);
    auto rhs  = na::arange(1,5,nm::float64);
    X86_SSE_TEST(lhs,divide,rhs);
}

TEST_CASE("divide(case12)" * doctest::test_suite("simd::x86_SSE"))
{
    auto lhs  = na::arange(1,2);
    auto rhs  = na::arange(1,2);
    X86_SSE_TEST(lhs,divide,rhs);
}

TEST_CASE("divide(case13)" * doctest::test_suite("simd::x86_SSE"))
{
    auto lhs  = na::arange(1,2,nm::float64);
    auto rhs  = na::arange(1,2,nm::float64);
    X86_SSE_TEST(lhs,divide,rhs);
}
