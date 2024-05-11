#include "nmtools/array/eval/simd/simde_avx512.hpp"
#include "nmtools/array/array/arange.hpp"
#include "nmtools/array/array/ufuncs/add.hpp"
#include "nmtools/array/array/ufuncs/multiply.hpp"
#include "nmtools/array/array/ufuncs/subtract.hpp"
#include "nmtools/array/array/ufuncs/divide.hpp"
#include "nmtools/array/array/reshape.hpp"
#include "nmtools/testing/doctest.hpp"

namespace nm = nmtools;
namespace na = nm::array;
namespace simd = na::simd;

using nmtools::unwrap;

#define SIMD_TEST_EQUAL(result, expect) \
{ \
    NMTOOLS_ASSERT_EQUAL( nm::shape(result), nm::shape(expect) ); \
    NMTOOLS_ASSERT_CLOSE( result, expect ); \
}

#define SIMDE_AVX512_TEST(fn,...) \
{ \
    auto expect = na::fn(__VA_ARGS__); \
    auto result = na::fn(__VA_ARGS__,simd::simde_AVX512); \
    SIMD_TEST_EQUAL(result,expect); \
}

/*********************** add ******************************/

TEST_CASE("add.reduce(case1)" * doctest::test_suite("simd::simde_AVX512"))
{
    auto input = na::arange(128);
    auto axis     = nm::None;
    auto dtype    = nm::None;
    auto initial  = nm::None;
    {
        auto keepdims = nm::False;
        SIMDE_AVX512_TEST(add.reduce,unwrap(input),axis,dtype,initial,keepdims);
    }
    {
        auto keepdims = nm::True;
        SIMDE_AVX512_TEST(add.reduce,unwrap(input),axis,dtype,initial,keepdims);
    }
    {
        auto keepdims = false;
        SIMDE_AVX512_TEST(add.reduce,unwrap(input),axis,dtype,initial,keepdims);
    }
    {
        auto keepdims = true;
        SIMDE_AVX512_TEST(add.reduce,unwrap(input),axis,dtype,initial,keepdims);
    }
}

TEST_CASE("add.reduce(case2)" * doctest::test_suite("simd::simde_AVX512"))
{
    auto input = na::arange(128,nm::float64);
    auto axis     = nm::None;
    auto dtype    = nm::None;
    auto initial  = nm::None;
    {
        auto keepdims = nm::False;
        SIMDE_AVX512_TEST(add.reduce,unwrap(input),axis,dtype,initial,keepdims);
    }
    {
        auto keepdims = nm::True;
        SIMDE_AVX512_TEST(add.reduce,unwrap(input),axis,dtype,initial,keepdims);
    }
    {
        auto keepdims = false;
        SIMDE_AVX512_TEST(add.reduce,unwrap(input),axis,dtype,initial,keepdims);
    }
    {
        auto keepdims = true;
        SIMDE_AVX512_TEST(add.reduce,unwrap(input),axis,dtype,initial,keepdims);
    }
}

TEST_CASE("add.reduce(case3)" * doctest::test_suite("simd::simde_AVX512"))
{
    auto input = na::arange(0,8,0.125);
    auto axis     = nm::None;
    auto dtype    = nm::None;
    auto initial  = nm::None;
    {
        auto keepdims = nm::False;
        SIMDE_AVX512_TEST(add.reduce,unwrap(input),axis,dtype,initial,keepdims);
    }
    {
        auto keepdims = nm::True;
        SIMDE_AVX512_TEST(add.reduce,unwrap(input),axis,dtype,initial,keepdims);
    }
    {
        auto keepdims = false;
        SIMDE_AVX512_TEST(add.reduce,unwrap(input),axis,dtype,initial,keepdims);
    }
    {
        auto keepdims = true;
        SIMDE_AVX512_TEST(add.reduce,unwrap(input),axis,dtype,initial,keepdims);
    }
}

TEST_CASE("add.reduce(case4)" * doctest::test_suite("simd::simde_AVX512"))
{
    auto input = na::arange(129);
    auto axis     = nm::None;
    auto dtype    = nm::None;
    auto initial  = nm::None;
    {
        auto keepdims = nm::False;
        SIMDE_AVX512_TEST(add.reduce,unwrap(input),axis,dtype,initial,keepdims);
    }
    {
        auto keepdims = nm::True;
        SIMDE_AVX512_TEST(add.reduce,unwrap(input),axis,dtype,initial,keepdims);
    }
    {
        auto keepdims = false;
        SIMDE_AVX512_TEST(add.reduce,unwrap(input),axis,dtype,initial,keepdims);
    }
    {
        auto keepdims = true;
        SIMDE_AVX512_TEST(add.reduce,unwrap(input),axis,dtype,initial,keepdims);
    }
}

TEST_CASE("add.reduce(case5)" * doctest::test_suite("simd::simde_AVX512"))
{
    auto input = na::arange(127);
    auto axis     = nm::None;
    auto dtype    = nm::None;
    auto initial  = nm::None;
    {
        auto keepdims = nm::False;
        SIMDE_AVX512_TEST(add.reduce,unwrap(input),axis,dtype,initial,keepdims);
    }
    {
        auto keepdims = nm::True;
        SIMDE_AVX512_TEST(add.reduce,unwrap(input),axis,dtype,initial,keepdims);
    }
    {
        auto keepdims = false;
        SIMDE_AVX512_TEST(add.reduce,unwrap(input),axis,dtype,initial,keepdims);
    }
    {
        auto keepdims = true;
        SIMDE_AVX512_TEST(add.reduce,unwrap(input),axis,dtype,initial,keepdims);
    }
}

TEST_CASE("add.reduce(case6)" * doctest::test_suite("simd::simde_AVX512"))
{
    auto input = na::arange(129,nm::float64);
    auto axis     = nm::None;
    auto dtype    = nm::None;
    auto initial  = nm::None;
    {
        auto keepdims = nm::False;
        SIMDE_AVX512_TEST(add.reduce,unwrap(input),axis,dtype,initial,keepdims);
    }
    {
        auto keepdims = nm::True;
        SIMDE_AVX512_TEST(add.reduce,unwrap(input),axis,dtype,initial,keepdims);
    }
    {
        auto keepdims = false;
        SIMDE_AVX512_TEST(add.reduce,unwrap(input),axis,dtype,initial,keepdims);
    }
    {
        auto keepdims = true;
        SIMDE_AVX512_TEST(add.reduce,unwrap(input),axis,dtype,initial,keepdims);
    }
}

TEST_CASE("add.reduce(case7)" * doctest::test_suite("simd::simde_AVX512"))
{
    auto input = na::arange(127,nm::float64);
    auto axis     = nm::None;
    auto dtype    = nm::None;
    auto initial  = nm::None;
    {
        auto keepdims = nm::False;
        SIMDE_AVX512_TEST(add.reduce,unwrap(input),axis,dtype,initial,keepdims);
    }
    {
        auto keepdims = nm::True;
        SIMDE_AVX512_TEST(add.reduce,unwrap(input),axis,dtype,initial,keepdims);
    }
    {
        auto keepdims = false;
        SIMDE_AVX512_TEST(add.reduce,unwrap(input),axis,dtype,initial,keepdims);
    }
    {
        auto keepdims = true;
        SIMDE_AVX512_TEST(add.reduce,unwrap(input),axis,dtype,initial,keepdims);
    }
}

TEST_CASE("add.reduce(case8)" * doctest::test_suite("simd::simde_AVX512"))
{
    auto input = na::arange(3);
    auto axis     = nm::None;
    auto dtype    = nm::None;
    auto initial  = nm::None;
    {
        auto keepdims = nm::False;
        SIMDE_AVX512_TEST(add.reduce,unwrap(input),axis,dtype,initial,keepdims);
    }
    {
        auto keepdims = nm::True;
        SIMDE_AVX512_TEST(add.reduce,unwrap(input),axis,dtype,initial,keepdims);
    }
    {
        auto keepdims = false;
        SIMDE_AVX512_TEST(add.reduce,unwrap(input),axis,dtype,initial,keepdims);
    }
    {
        auto keepdims = true;
        SIMDE_AVX512_TEST(add.reduce,unwrap(input),axis,dtype,initial,keepdims);
    }
}

TEST_CASE("add.reduce(case9)" * doctest::test_suite("simd::simde_AVX512"))
{
    auto input = na::arange(5);
    auto axis     = nm::None;
    auto dtype    = nm::None;
    auto initial  = nm::None;
    {
        auto keepdims = nm::False;
        SIMDE_AVX512_TEST(add.reduce,unwrap(input),axis,dtype,initial,keepdims);
    }
    {
        auto keepdims = nm::True;
        SIMDE_AVX512_TEST(add.reduce,unwrap(input),axis,dtype,initial,keepdims);
    }
    {
        auto keepdims = false;
        SIMDE_AVX512_TEST(add.reduce,unwrap(input),axis,dtype,initial,keepdims);
    }
    {
        auto keepdims = true;
        SIMDE_AVX512_TEST(add.reduce,unwrap(input),axis,dtype,initial,keepdims);
    }
}

TEST_CASE("add.reduce(case10)" * doctest::test_suite("simd::simde_AVX512"))
{
    auto input = na::arange(3,nm::float64);
    auto axis     = nm::None;
    auto dtype    = nm::None;
    auto initial  = nm::None;
    {
        auto keepdims = nm::False;
        SIMDE_AVX512_TEST(add.reduce,unwrap(input),axis,dtype,initial,keepdims);
    }
    {
        auto keepdims = nm::True;
        SIMDE_AVX512_TEST(add.reduce,unwrap(input),axis,dtype,initial,keepdims);
    }
    {
        auto keepdims = false;
        SIMDE_AVX512_TEST(add.reduce,unwrap(input),axis,dtype,initial,keepdims);
    }
    {
        auto keepdims = true;
        SIMDE_AVX512_TEST(add.reduce,unwrap(input),axis,dtype,initial,keepdims);
    }
}

TEST_CASE("add.reduce(case11)" * doctest::test_suite("simd::simde_AVX512"))
{
    auto input = na::arange(5,nm::float64);
    auto axis     = nm::None;
    auto dtype    = nm::None;
    auto initial  = nm::None;
    {
        auto keepdims = nm::False;
        SIMDE_AVX512_TEST(add.reduce,unwrap(input),axis,dtype,initial,keepdims);
    }
    {
        auto keepdims = nm::True;
        SIMDE_AVX512_TEST(add.reduce,unwrap(input),axis,dtype,initial,keepdims);
    }
    {
        auto keepdims = false;
        SIMDE_AVX512_TEST(add.reduce,unwrap(input),axis,dtype,initial,keepdims);
    }
    {
        auto keepdims = true;
        SIMDE_AVX512_TEST(add.reduce,unwrap(input),axis,dtype,initial,keepdims);
    }
}

TEST_CASE("add.reduce(case12)" * doctest::test_suite("simd::simde_AVX512"))
{
    auto input = na::arange(1);
    auto axis     = nm::None;
    auto dtype    = nm::None;
    auto initial  = nm::None;
    {
        auto keepdims = nm::False;
        SIMDE_AVX512_TEST(add.reduce,unwrap(input),axis,dtype,initial,keepdims);
    }
    {
        auto keepdims = nm::True;
        SIMDE_AVX512_TEST(add.reduce,unwrap(input),axis,dtype,initial,keepdims);
    }
    {
        auto keepdims = false;
        SIMDE_AVX512_TEST(add.reduce,unwrap(input),axis,dtype,initial,keepdims);
    }
    {
        auto keepdims = true;
        SIMDE_AVX512_TEST(add.reduce,unwrap(input),axis,dtype,initial,keepdims);
    }
}

TEST_CASE("add.reduce(case13)" * doctest::test_suite("simd::simde_AVX512"))
{
    auto input = na::arange(1,nm::float64);
    auto axis     = nm::None;
    auto dtype    = nm::None;
    auto initial  = nm::None;
    {
        auto keepdims = nm::False;
        SIMDE_AVX512_TEST(add.reduce,unwrap(input),axis,dtype,initial,keepdims);
    }
    {
        auto keepdims = nm::True;
        SIMDE_AVX512_TEST(add.reduce,unwrap(input),axis,dtype,initial,keepdims);
    }
    {
        auto keepdims = false;
        SIMDE_AVX512_TEST(add.reduce,unwrap(input),axis,dtype,initial,keepdims);
    }
    {
        auto keepdims = true;
        SIMDE_AVX512_TEST(add.reduce,unwrap(input),axis,dtype,initial,keepdims);
    }
}

TEST_CASE("add.reduce(case14)" * doctest::test_suite("simd::simde_AVX512"))
{
    auto input = na::arange(128,nm::uint64);
    auto axis     = nm::None;
    auto dtype    = nm::None;
    auto initial  = nm::None;
    {
        auto keepdims = nm::False;
        SIMDE_AVX512_TEST(add.reduce,unwrap(input),axis,dtype,initial,keepdims);
    }
    {
        auto keepdims = nm::True;
        SIMDE_AVX512_TEST(add.reduce,unwrap(input),axis,dtype,initial,keepdims);
    }
    {
        auto keepdims = false;
        SIMDE_AVX512_TEST(add.reduce,unwrap(input),axis,dtype,initial,keepdims);
    }
    {
        auto keepdims = true;
        SIMDE_AVX512_TEST(add.reduce,unwrap(input),axis,dtype,initial,keepdims);
    }
}

TEST_CASE("add.reduce(case15)" * doctest::test_suite("simd::simde_AVX512"))
{
    auto input = na::arange(128,nm::int64);
    auto axis     = nm::None;
    auto dtype    = nm::None;
    auto initial  = nm::None;
    {
        auto keepdims = nm::False;
        SIMDE_AVX512_TEST(add.reduce,unwrap(input),axis,dtype,initial,keepdims);
    }
    {
        auto keepdims = nm::True;
        SIMDE_AVX512_TEST(add.reduce,unwrap(input),axis,dtype,initial,keepdims);
    }
    {
        auto keepdims = false;
        SIMDE_AVX512_TEST(add.reduce,unwrap(input),axis,dtype,initial,keepdims);
    }
    {
        auto keepdims = true;
        SIMDE_AVX512_TEST(add.reduce,unwrap(input),axis,dtype,initial,keepdims);
    }
}

TEST_CASE("add.reduce(case16)" * doctest::test_suite("simd::simde_AVX512"))
{
    auto input = na::arange(128,nm::uint32);
    auto axis     = nm::None;
    auto dtype    = nm::None;
    auto initial  = nm::None;
    {
        auto keepdims = nm::False;
        SIMDE_AVX512_TEST(add.reduce,unwrap(input),axis,dtype,initial,keepdims);
    }
    {
        auto keepdims = nm::True;
        SIMDE_AVX512_TEST(add.reduce,unwrap(input),axis,dtype,initial,keepdims);
    }
    {
        auto keepdims = false;
        SIMDE_AVX512_TEST(add.reduce,unwrap(input),axis,dtype,initial,keepdims);
    }
    {
        auto keepdims = true;
        SIMDE_AVX512_TEST(add.reduce,unwrap(input),axis,dtype,initial,keepdims);
    }
}

TEST_CASE("add.reduce(case17)" * doctest::test_suite("simd::simde_AVX512"))
{
    auto input = na::arange(128,nm::int32);
    auto axis     = nm::None;
    auto dtype    = nm::None;
    auto initial  = nm::None;
    {
        auto keepdims = nm::False;
        SIMDE_AVX512_TEST(add.reduce,unwrap(input),axis,dtype,initial,keepdims);
    }
    {
        auto keepdims = nm::True;
        SIMDE_AVX512_TEST(add.reduce,unwrap(input),axis,dtype,initial,keepdims);
    }
    {
        auto keepdims = false;
        SIMDE_AVX512_TEST(add.reduce,unwrap(input),axis,dtype,initial,keepdims);
    }
    {
        auto keepdims = true;
        SIMDE_AVX512_TEST(add.reduce,unwrap(input),axis,dtype,initial,keepdims);
    }
}

TEST_CASE("add.reduce(case18)" * doctest::test_suite("simd::simde_AVX512"))
{
    auto input = na::arange(128,nm::uint16);
    auto axis     = nm::None;
    auto dtype    = nm::None;
    auto initial  = nm::None;
    {
        auto keepdims = nm::False;
        SIMDE_AVX512_TEST(add.reduce,unwrap(input),axis,dtype,initial,keepdims);
    }
    {
        auto keepdims = nm::True;
        SIMDE_AVX512_TEST(add.reduce,unwrap(input),axis,dtype,initial,keepdims);
    }
    {
        auto keepdims = false;
        SIMDE_AVX512_TEST(add.reduce,unwrap(input),axis,dtype,initial,keepdims);
    }
    {
        auto keepdims = true;
        SIMDE_AVX512_TEST(add.reduce,unwrap(input),axis,dtype,initial,keepdims);
    }
}

TEST_CASE("add.reduce(case19)" * doctest::test_suite("simd::simde_AVX512"))
{
    auto input = na::arange(128,nm::int16);
    auto axis     = nm::None;
    auto dtype    = nm::None;
    auto initial  = nm::None;
    {
        auto keepdims = nm::False;
        SIMDE_AVX512_TEST(add.reduce,unwrap(input),axis,dtype,initial,keepdims);
    }
    {
        auto keepdims = nm::True;
        SIMDE_AVX512_TEST(add.reduce,unwrap(input),axis,dtype,initial,keepdims);
    }
    {
        auto keepdims = false;
        SIMDE_AVX512_TEST(add.reduce,unwrap(input),axis,dtype,initial,keepdims);
    }
    {
        auto keepdims = true;
        SIMDE_AVX512_TEST(add.reduce,unwrap(input),axis,dtype,initial,keepdims);
    }
}

TEST_CASE("add.reduce(case20)" * doctest::test_suite("simd::simde_AVX512"))
{
    auto input = na::arange(128,nm::uint8);
    auto axis     = nm::None;
    auto dtype    = nm::None;
    auto initial  = nm::None;
    {
        auto keepdims = nm::False;
        SIMDE_AVX512_TEST(add.reduce,unwrap(input),axis,dtype,initial,keepdims);
    }
    {
        auto keepdims = nm::True;
        SIMDE_AVX512_TEST(add.reduce,unwrap(input),axis,dtype,initial,keepdims);
    }
    {
        auto keepdims = false;
        SIMDE_AVX512_TEST(add.reduce,unwrap(input),axis,dtype,initial,keepdims);
    }
    {
        auto keepdims = true;
        SIMDE_AVX512_TEST(add.reduce,unwrap(input),axis,dtype,initial,keepdims);
    }
}

TEST_CASE("add.reduce(case21)" * doctest::test_suite("simd::simde_AVX512"))
{
    auto input = na::arange(128,nm::int8);
    auto axis     = nm::None;
    auto dtype    = nm::None;
    auto initial  = nm::None;
    {
        auto keepdims = nm::False;
        SIMDE_AVX512_TEST(add.reduce,unwrap(input),axis,dtype,initial,keepdims);
    }
    {
        auto keepdims = nm::True;
        SIMDE_AVX512_TEST(add.reduce,unwrap(input),axis,dtype,initial,keepdims);
    }
    {
        auto keepdims = false;
        SIMDE_AVX512_TEST(add.reduce,unwrap(input),axis,dtype,initial,keepdims);
    }
    {
        auto keepdims = true;
        SIMDE_AVX512_TEST(add.reduce,unwrap(input),axis,dtype,initial,keepdims);
    }
}

TEST_CASE("add.reduce(case22)" * doctest::test_suite("simd::simde_AVX512"))
{
    auto input = na::arange(-128,127,nm::int64);
    auto axis     = nm::None;
    auto dtype    = nm::None;
    auto initial  = nm::None;
    {
        auto keepdims = nm::False;
        SIMDE_AVX512_TEST(add.reduce,unwrap(input),axis,dtype,initial,keepdims);
    }
    {
        auto keepdims = nm::True;
        SIMDE_AVX512_TEST(add.reduce,unwrap(input),axis,dtype,initial,keepdims);
    }
    {
        auto keepdims = false;
        SIMDE_AVX512_TEST(add.reduce,unwrap(input),axis,dtype,initial,keepdims);
    }
    {
        auto keepdims = true;
        SIMDE_AVX512_TEST(add.reduce,unwrap(input),axis,dtype,initial,keepdims);
    }
}

TEST_CASE("add.reduce(case23)" * doctest::test_suite("simd::simde_AVX512"))
{
    auto input = na::arange(-128,127,nm::int32);
    auto axis     = nm::None;
    auto dtype    = nm::None;
    auto initial  = nm::None;
    {
        auto keepdims = nm::False;
        SIMDE_AVX512_TEST(add.reduce,unwrap(input),axis,dtype,initial,keepdims);
    }
    {
        auto keepdims = nm::True;
        SIMDE_AVX512_TEST(add.reduce,unwrap(input),axis,dtype,initial,keepdims);
    }
    {
        auto keepdims = false;
        SIMDE_AVX512_TEST(add.reduce,unwrap(input),axis,dtype,initial,keepdims);
    }
    {
        auto keepdims = true;
        SIMDE_AVX512_TEST(add.reduce,unwrap(input),axis,dtype,initial,keepdims);
    }
}

TEST_CASE("add.reduce(case24)" * doctest::test_suite("simd::simde_AVX512"))
{
    auto input = na::arange(-128,127,nm::int16);
    auto axis     = nm::None;
    auto dtype    = nm::None;
    auto initial  = nm::None;
    {
        auto keepdims = nm::False;
        SIMDE_AVX512_TEST(add.reduce,unwrap(input),axis,dtype,initial,keepdims);
    }
    {
        auto keepdims = nm::True;
        SIMDE_AVX512_TEST(add.reduce,unwrap(input),axis,dtype,initial,keepdims);
    }
    {
        auto keepdims = false;
        SIMDE_AVX512_TEST(add.reduce,unwrap(input),axis,dtype,initial,keepdims);
    }
    {
        auto keepdims = true;
        SIMDE_AVX512_TEST(add.reduce,unwrap(input),axis,dtype,initial,keepdims);
    }
}

TEST_CASE("add.reduce(case25)" * doctest::test_suite("simd::simde_AVX512"))
{
    auto input = na::arange(-128,127,nm::int8);
    auto axis     = nm::None;
    auto dtype    = nm::None;
    auto initial  = nm::None;
    {
        auto keepdims = nm::False;
        SIMDE_AVX512_TEST(add.reduce,unwrap(input),axis,dtype,initial,keepdims);
    }
    {
        auto keepdims = nm::True;
        SIMDE_AVX512_TEST(add.reduce,unwrap(input),axis,dtype,initial,keepdims);
    }
    {
        auto keepdims = false;
        SIMDE_AVX512_TEST(add.reduce,unwrap(input),axis,dtype,initial,keepdims);
    }
    {
        auto keepdims = true;
        SIMDE_AVX512_TEST(add.reduce,unwrap(input),axis,dtype,initial,keepdims);
    }
}

/*********************** multiply ******************************/

TEST_CASE("multiply.reduce(case1)" * doctest::test_suite("simd::simde_AVX512"))
{
    auto input = na::arange(128);
    auto axis     = nm::None;
    auto dtype    = nm::None;
    auto initial  = nm::None;
    {
        auto keepdims = nm::False;
        SIMDE_AVX512_TEST(multiply.reduce,unwrap(input),axis,dtype,initial,keepdims);
    }
    {
        auto keepdims = nm::True;
        SIMDE_AVX512_TEST(multiply.reduce,unwrap(input),axis,dtype,initial,keepdims);
    }
    {
        auto keepdims = false;
        SIMDE_AVX512_TEST(multiply.reduce,unwrap(input),axis,dtype,initial,keepdims);
    }
    {
        auto keepdims = true;
        SIMDE_AVX512_TEST(multiply.reduce,unwrap(input),axis,dtype,initial,keepdims);
    }
}

TEST_CASE("multiply.reduce(case2)" * doctest::test_suite("simd::simde_AVX512"))
{
    auto input = na::arange(128,nm::float64);
    auto axis     = nm::None;
    auto dtype    = nm::None;
    auto initial  = nm::None;
    {
        auto keepdims = nm::False;
        SIMDE_AVX512_TEST(multiply.reduce,unwrap(input),axis,dtype,initial,keepdims);
    }
    {
        auto keepdims = nm::True;
        SIMDE_AVX512_TEST(multiply.reduce,unwrap(input),axis,dtype,initial,keepdims);
    }
    {
        auto keepdims = false;
        SIMDE_AVX512_TEST(multiply.reduce,unwrap(input),axis,dtype,initial,keepdims);
    }
    {
        auto keepdims = true;
        SIMDE_AVX512_TEST(multiply.reduce,unwrap(input),axis,dtype,initial,keepdims);
    }
}

TEST_CASE("multiply.reduce(case3)" * doctest::test_suite("simd::simde_AVX512"))
{
    auto input = na::arange(0,8,0.125);
    auto axis     = nm::None;
    auto dtype    = nm::None;
    auto initial  = nm::None;
    {
        auto keepdims = nm::False;
        SIMDE_AVX512_TEST(multiply.reduce,unwrap(input),axis,dtype,initial,keepdims);
    }
    {
        auto keepdims = nm::True;
        SIMDE_AVX512_TEST(multiply.reduce,unwrap(input),axis,dtype,initial,keepdims);
    }
    {
        auto keepdims = false;
        SIMDE_AVX512_TEST(multiply.reduce,unwrap(input),axis,dtype,initial,keepdims);
    }
    {
        auto keepdims = true;
        SIMDE_AVX512_TEST(multiply.reduce,unwrap(input),axis,dtype,initial,keepdims);
    }
}

TEST_CASE("multiply.reduce(case4)" * doctest::test_suite("simd::simde_AVX512"))
{
    auto input = na::arange(129);
    auto axis     = nm::None;
    auto dtype    = nm::None;
    auto initial  = nm::None;
    {
        auto keepdims = nm::False;
        SIMDE_AVX512_TEST(multiply.reduce,unwrap(input),axis,dtype,initial,keepdims);
    }
    {
        auto keepdims = nm::True;
        SIMDE_AVX512_TEST(multiply.reduce,unwrap(input),axis,dtype,initial,keepdims);
    }
    {
        auto keepdims = false;
        SIMDE_AVX512_TEST(multiply.reduce,unwrap(input),axis,dtype,initial,keepdims);
    }
    {
        auto keepdims = true;
        SIMDE_AVX512_TEST(multiply.reduce,unwrap(input),axis,dtype,initial,keepdims);
    }
}

TEST_CASE("multiply.reduce(case5)" * doctest::test_suite("simd::simde_AVX512"))
{
    auto input = na::arange(127);
    auto axis     = nm::None;
    auto dtype    = nm::None;
    auto initial  = nm::None;
    {
        auto keepdims = nm::False;
        SIMDE_AVX512_TEST(multiply.reduce,unwrap(input),axis,dtype,initial,keepdims);
    }
    {
        auto keepdims = nm::True;
        SIMDE_AVX512_TEST(multiply.reduce,unwrap(input),axis,dtype,initial,keepdims);
    }
    {
        auto keepdims = false;
        SIMDE_AVX512_TEST(multiply.reduce,unwrap(input),axis,dtype,initial,keepdims);
    }
    {
        auto keepdims = true;
        SIMDE_AVX512_TEST(multiply.reduce,unwrap(input),axis,dtype,initial,keepdims);
    }
}

TEST_CASE("multiply.reduce(case6)" * doctest::test_suite("simd::simde_AVX512"))
{
    auto input = na::arange(129,nm::float64);
    auto axis     = nm::None;
    auto dtype    = nm::None;
    auto initial  = nm::None;
    {
        auto keepdims = nm::False;
        SIMDE_AVX512_TEST(multiply.reduce,unwrap(input),axis,dtype,initial,keepdims);
    }
    {
        auto keepdims = nm::True;
        SIMDE_AVX512_TEST(multiply.reduce,unwrap(input),axis,dtype,initial,keepdims);
    }
    {
        auto keepdims = false;
        SIMDE_AVX512_TEST(multiply.reduce,unwrap(input),axis,dtype,initial,keepdims);
    }
    {
        auto keepdims = true;
        SIMDE_AVX512_TEST(multiply.reduce,unwrap(input),axis,dtype,initial,keepdims);
    }
}

TEST_CASE("multiply.reduce(case7)" * doctest::test_suite("simd::simde_AVX512"))
{
    auto input = na::arange(127,nm::float64);
    auto axis     = nm::None;
    auto dtype    = nm::None;
    auto initial  = nm::None;
    {
        auto keepdims = nm::False;
        SIMDE_AVX512_TEST(multiply.reduce,unwrap(input),axis,dtype,initial,keepdims);
    }
    {
        auto keepdims = nm::True;
        SIMDE_AVX512_TEST(multiply.reduce,unwrap(input),axis,dtype,initial,keepdims);
    }
    {
        auto keepdims = false;
        SIMDE_AVX512_TEST(multiply.reduce,unwrap(input),axis,dtype,initial,keepdims);
    }
    {
        auto keepdims = true;
        SIMDE_AVX512_TEST(multiply.reduce,unwrap(input),axis,dtype,initial,keepdims);
    }
}

TEST_CASE("multiply.reduce(case8)" * doctest::test_suite("simd::simde_AVX512"))
{
    auto input = na::arange(3);
    auto axis     = nm::None;
    auto dtype    = nm::None;
    auto initial  = nm::None;
    {
        auto keepdims = nm::False;
        SIMDE_AVX512_TEST(multiply.reduce,unwrap(input),axis,dtype,initial,keepdims);
    }
    {
        auto keepdims = nm::True;
        SIMDE_AVX512_TEST(multiply.reduce,unwrap(input),axis,dtype,initial,keepdims);
    }
    {
        auto keepdims = false;
        SIMDE_AVX512_TEST(multiply.reduce,unwrap(input),axis,dtype,initial,keepdims);
    }
    {
        auto keepdims = true;
        SIMDE_AVX512_TEST(multiply.reduce,unwrap(input),axis,dtype,initial,keepdims);
    }
}

TEST_CASE("multiply.reduce(case9)" * doctest::test_suite("simd::simde_AVX512"))
{
    auto input = na::arange(5);
    auto axis     = nm::None;
    auto dtype    = nm::None;
    auto initial  = nm::None;
    {
        auto keepdims = nm::False;
        SIMDE_AVX512_TEST(multiply.reduce,unwrap(input),axis,dtype,initial,keepdims);
    }
    {
        auto keepdims = nm::True;
        SIMDE_AVX512_TEST(multiply.reduce,unwrap(input),axis,dtype,initial,keepdims);
    }
    {
        auto keepdims = false;
        SIMDE_AVX512_TEST(multiply.reduce,unwrap(input),axis,dtype,initial,keepdims);
    }
    {
        auto keepdims = true;
        SIMDE_AVX512_TEST(multiply.reduce,unwrap(input),axis,dtype,initial,keepdims);
    }
}

TEST_CASE("multiply.reduce(case10)" * doctest::test_suite("simd::simde_AVX512"))
{
    auto input = na::arange(3,nm::float64);
    auto axis     = nm::None;
    auto dtype    = nm::None;
    auto initial  = nm::None;
    {
        auto keepdims = nm::False;
        SIMDE_AVX512_TEST(multiply.reduce,unwrap(input),axis,dtype,initial,keepdims);
    }
    {
        auto keepdims = nm::True;
        SIMDE_AVX512_TEST(multiply.reduce,unwrap(input),axis,dtype,initial,keepdims);
    }
    {
        auto keepdims = false;
        SIMDE_AVX512_TEST(multiply.reduce,unwrap(input),axis,dtype,initial,keepdims);
    }
    {
        auto keepdims = true;
        SIMDE_AVX512_TEST(multiply.reduce,unwrap(input),axis,dtype,initial,keepdims);
    }
}

TEST_CASE("multiply.reduce(case11)" * doctest::test_suite("simd::simde_AVX512"))
{
    auto input = na::arange(5,nm::float64);
    auto axis     = nm::None;
    auto dtype    = nm::None;
    auto initial  = nm::None;
    {
        auto keepdims = nm::False;
        SIMDE_AVX512_TEST(multiply.reduce,unwrap(input),axis,dtype,initial,keepdims);
    }
    {
        auto keepdims = nm::True;
        SIMDE_AVX512_TEST(multiply.reduce,unwrap(input),axis,dtype,initial,keepdims);
    }
    {
        auto keepdims = false;
        SIMDE_AVX512_TEST(multiply.reduce,unwrap(input),axis,dtype,initial,keepdims);
    }
    {
        auto keepdims = true;
        SIMDE_AVX512_TEST(multiply.reduce,unwrap(input),axis,dtype,initial,keepdims);
    }
}

TEST_CASE("multiply.reduce(case12)" * doctest::test_suite("simd::simde_AVX512"))
{
    auto input = na::arange(1);
    auto axis     = nm::None;
    auto dtype    = nm::None;
    auto initial  = nm::None;
    {
        auto keepdims = nm::False;
        SIMDE_AVX512_TEST(multiply.reduce,unwrap(input),axis,dtype,initial,keepdims);
    }
    {
        auto keepdims = nm::True;
        SIMDE_AVX512_TEST(multiply.reduce,unwrap(input),axis,dtype,initial,keepdims);
    }
    {
        auto keepdims = false;
        SIMDE_AVX512_TEST(multiply.reduce,unwrap(input),axis,dtype,initial,keepdims);
    }
    {
        auto keepdims = true;
        SIMDE_AVX512_TEST(multiply.reduce,unwrap(input),axis,dtype,initial,keepdims);
    }
}

TEST_CASE("multiply.reduce(case13)" * doctest::test_suite("simd::simde_AVX512"))
{
    auto input = na::arange(1,nm::float64);
    auto axis     = nm::None;
    auto dtype    = nm::None;
    auto initial  = nm::None;
    {
        auto keepdims = nm::False;
        SIMDE_AVX512_TEST(multiply.reduce,unwrap(input),axis,dtype,initial,keepdims);
    }
    {
        auto keepdims = nm::True;
        SIMDE_AVX512_TEST(multiply.reduce,unwrap(input),axis,dtype,initial,keepdims);
    }
    {
        auto keepdims = false;
        SIMDE_AVX512_TEST(multiply.reduce,unwrap(input),axis,dtype,initial,keepdims);
    }
    {
        auto keepdims = true;
        SIMDE_AVX512_TEST(multiply.reduce,unwrap(input),axis,dtype,initial,keepdims);
    }
}

TEST_CASE("multiply.reduce(case14)" * doctest::test_suite("simd::simde_AVX512"))
{
    auto input = na::arange(128,nm::uint64);
    auto axis     = nm::None;
    auto dtype    = nm::None;
    auto initial  = nm::None;
    {
        auto keepdims = nm::False;
        SIMDE_AVX512_TEST(multiply.reduce,unwrap(input),axis,dtype,initial,keepdims);
    }
    {
        auto keepdims = nm::True;
        SIMDE_AVX512_TEST(multiply.reduce,unwrap(input),axis,dtype,initial,keepdims);
    }
    {
        auto keepdims = false;
        SIMDE_AVX512_TEST(multiply.reduce,unwrap(input),axis,dtype,initial,keepdims);
    }
    {
        auto keepdims = true;
        SIMDE_AVX512_TEST(multiply.reduce,unwrap(input),axis,dtype,initial,keepdims);
    }
}

TEST_CASE("multiply.reduce(case15)" * doctest::test_suite("simd::simde_AVX512"))
{
    auto input = na::arange(128,nm::int64);
    auto axis     = nm::None;
    auto dtype    = nm::None;
    auto initial  = nm::None;
    {
        auto keepdims = nm::False;
        SIMDE_AVX512_TEST(multiply.reduce,unwrap(input),axis,dtype,initial,keepdims);
    }
    {
        auto keepdims = nm::True;
        SIMDE_AVX512_TEST(multiply.reduce,unwrap(input),axis,dtype,initial,keepdims);
    }
    {
        auto keepdims = false;
        SIMDE_AVX512_TEST(multiply.reduce,unwrap(input),axis,dtype,initial,keepdims);
    }
    {
        auto keepdims = true;
        SIMDE_AVX512_TEST(multiply.reduce,unwrap(input),axis,dtype,initial,keepdims);
    }
}

TEST_CASE("multiply.reduce(case16)" * doctest::test_suite("simd::simde_AVX512"))
{
    auto input = na::arange(128,nm::uint32);
    auto axis     = nm::None;
    auto dtype    = nm::None;
    auto initial  = nm::None;
    {
        auto keepdims = nm::False;
        SIMDE_AVX512_TEST(multiply.reduce,unwrap(input),axis,dtype,initial,keepdims);
    }
    {
        auto keepdims = nm::True;
        SIMDE_AVX512_TEST(multiply.reduce,unwrap(input),axis,dtype,initial,keepdims);
    }
    {
        auto keepdims = false;
        SIMDE_AVX512_TEST(multiply.reduce,unwrap(input),axis,dtype,initial,keepdims);
    }
    {
        auto keepdims = true;
        SIMDE_AVX512_TEST(multiply.reduce,unwrap(input),axis,dtype,initial,keepdims);
    }
}

TEST_CASE("multiply.reduce(case17)" * doctest::test_suite("simd::simde_AVX512"))
{
    auto input = na::arange(128,nm::int32);
    auto axis     = nm::None;
    auto dtype    = nm::None;
    auto initial  = nm::None;
    {
        auto keepdims = nm::False;
        SIMDE_AVX512_TEST(multiply.reduce,unwrap(input),axis,dtype,initial,keepdims);
    }
    {
        auto keepdims = nm::True;
        SIMDE_AVX512_TEST(multiply.reduce,unwrap(input),axis,dtype,initial,keepdims);
    }
    {
        auto keepdims = false;
        SIMDE_AVX512_TEST(multiply.reduce,unwrap(input),axis,dtype,initial,keepdims);
    }
    {
        auto keepdims = true;
        SIMDE_AVX512_TEST(multiply.reduce,unwrap(input),axis,dtype,initial,keepdims);
    }
}

TEST_CASE("multiply.reduce(case18)" * doctest::test_suite("simd::simde_AVX512"))
{
    auto input = na::arange(128,nm::uint16);
    auto axis     = nm::None;
    auto dtype    = nm::None;
    auto initial  = nm::None;
    {
        auto keepdims = nm::False;
        SIMDE_AVX512_TEST(multiply.reduce,unwrap(input),axis,dtype,initial,keepdims);
    }
    {
        auto keepdims = nm::True;
        SIMDE_AVX512_TEST(multiply.reduce,unwrap(input),axis,dtype,initial,keepdims);
    }
    {
        auto keepdims = false;
        SIMDE_AVX512_TEST(multiply.reduce,unwrap(input),axis,dtype,initial,keepdims);
    }
    {
        auto keepdims = true;
        SIMDE_AVX512_TEST(multiply.reduce,unwrap(input),axis,dtype,initial,keepdims);
    }
}

TEST_CASE("multiply.reduce(case19)" * doctest::test_suite("simd::simde_AVX512"))
{
    auto input = na::arange(128,nm::int16);
    auto axis     = nm::None;
    auto dtype    = nm::None;
    auto initial  = nm::None;
    {
        auto keepdims = nm::False;
        SIMDE_AVX512_TEST(multiply.reduce,unwrap(input),axis,dtype,initial,keepdims);
    }
    {
        auto keepdims = nm::True;
        SIMDE_AVX512_TEST(multiply.reduce,unwrap(input),axis,dtype,initial,keepdims);
    }
    {
        auto keepdims = false;
        SIMDE_AVX512_TEST(multiply.reduce,unwrap(input),axis,dtype,initial,keepdims);
    }
    {
        auto keepdims = true;
        SIMDE_AVX512_TEST(multiply.reduce,unwrap(input),axis,dtype,initial,keepdims);
    }
}

// NOTE: uint8 not available on sse yet
#if 0
TEST_CASE("multiply.reduce(case20)" * doctest::test_suite("simd::simde_AVX512"))
{
    auto input = na::arange(128,nm::uint8);
    auto axis     = nm::None;
    auto dtype    = nm::None;
    auto initial  = nm::None;
    {
        auto keepdims = nm::False;
        SIMDE_AVX512_TEST(multiply.reduce,unwrap(input),axis,dtype,initial,keepdims);
    }
    {
        auto keepdims = nm::True;
        SIMDE_AVX512_TEST(multiply.reduce,unwrap(input),axis,dtype,initial,keepdims);
    }
    {
        auto keepdims = false;
        SIMDE_AVX512_TEST(multiply.reduce,unwrap(input),axis,dtype,initial,keepdims);
    }
    {
        auto keepdims = true;
        SIMDE_AVX512_TEST(multiply.reduce,unwrap(input),axis,dtype,initial,keepdims);
    }
}

TEST_CASE("multiply.reduce(case21)" * doctest::test_suite("simd::simde_AVX512"))
{
    auto input = na::arange(128,nm::int8);
    auto axis     = nm::None;
    auto dtype    = nm::None;
    auto initial  = nm::None;
    {
        auto keepdims = nm::False;
        SIMDE_AVX512_TEST(multiply.reduce,unwrap(input),axis,dtype,initial,keepdims);
    }
    {
        auto keepdims = nm::True;
        SIMDE_AVX512_TEST(multiply.reduce,unwrap(input),axis,dtype,initial,keepdims);
    }
    {
        auto keepdims = false;
        SIMDE_AVX512_TEST(multiply.reduce,unwrap(input),axis,dtype,initial,keepdims);
    }
    {
        auto keepdims = true;
        SIMDE_AVX512_TEST(multiply.reduce,unwrap(input),axis,dtype,initial,keepdims);
    }
}

#endif

TEST_CASE("multiply.reduce(case22)" * doctest::test_suite("simd::simde_AVX512"))
{
    auto input = na::arange(-128,127,nm::int64);
    auto axis     = nm::None;
    auto dtype    = nm::None;
    auto initial  = nm::None;
    {
        auto keepdims = nm::False;
        SIMDE_AVX512_TEST(multiply.reduce,unwrap(input),axis,dtype,initial,keepdims);
    }
    {
        auto keepdims = nm::True;
        SIMDE_AVX512_TEST(multiply.reduce,unwrap(input),axis,dtype,initial,keepdims);
    }
    {
        auto keepdims = false;
        SIMDE_AVX512_TEST(multiply.reduce,unwrap(input),axis,dtype,initial,keepdims);
    }
    {
        auto keepdims = true;
        SIMDE_AVX512_TEST(multiply.reduce,unwrap(input),axis,dtype,initial,keepdims);
    }
}

TEST_CASE("multiply.reduce(case23)" * doctest::test_suite("simd::simde_AVX512"))
{
    auto input = na::arange(-128,127,nm::int32);
    auto axis     = nm::None;
    auto dtype    = nm::None;
    auto initial  = nm::None;
    {
        auto keepdims = nm::False;
        SIMDE_AVX512_TEST(multiply.reduce,unwrap(input),axis,dtype,initial,keepdims);
    }
    {
        auto keepdims = nm::True;
        SIMDE_AVX512_TEST(multiply.reduce,unwrap(input),axis,dtype,initial,keepdims);
    }
    {
        auto keepdims = false;
        SIMDE_AVX512_TEST(multiply.reduce,unwrap(input),axis,dtype,initial,keepdims);
    }
    {
        auto keepdims = true;
        SIMDE_AVX512_TEST(multiply.reduce,unwrap(input),axis,dtype,initial,keepdims);
    }
}

TEST_CASE("multiply.reduce(case24)" * doctest::test_suite("simd::simde_AVX512"))
{
    auto input = na::arange(-128,127,nm::int16);
    auto axis     = nm::None;
    auto dtype    = nm::None;
    auto initial  = nm::None;
    {
        auto keepdims = nm::False;
        SIMDE_AVX512_TEST(multiply.reduce,unwrap(input),axis,dtype,initial,keepdims);
    }
    {
        auto keepdims = nm::True;
        SIMDE_AVX512_TEST(multiply.reduce,unwrap(input),axis,dtype,initial,keepdims);
    }
    {
        auto keepdims = false;
        SIMDE_AVX512_TEST(multiply.reduce,unwrap(input),axis,dtype,initial,keepdims);
    }
    {
        auto keepdims = true;
        SIMDE_AVX512_TEST(multiply.reduce,unwrap(input),axis,dtype,initial,keepdims);
    }
}

#if 0
TEST_CASE("multiply.reduce(case22)" * doctest::test_suite("simd::simde_AVX512"))
{
    auto input = na::arange(-128,127,nm::int8);
    auto axis     = nm::None;
    auto dtype    = nm::None;
    auto initial  = nm::None;
    {
        auto keepdims = nm::False;
        SIMDE_AVX512_TEST(multiply.reduce,unwrap(input),axis,dtype,initial,keepdims);
    }
    {
        auto keepdims = nm::True;
        SIMDE_AVX512_TEST(multiply.reduce,unwrap(input),axis,dtype,initial,keepdims);
    }
    {
        auto keepdims = false;
        SIMDE_AVX512_TEST(multiply.reduce,unwrap(input),axis,dtype,initial,keepdims);
    }
    {
        auto keepdims = true;
        SIMDE_AVX512_TEST(multiply.reduce,unwrap(input),axis,dtype,initial,keepdims);
    }
}
#endif