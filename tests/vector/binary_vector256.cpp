#include "nmtools/evaluator/simd/vector_256.hpp"
#include "nmtools/array/arange.hpp"
#include "nmtools/array/ufuncs/add.hpp"
#include "nmtools/array/ufuncs/multiply.hpp"
#include "nmtools/array/ufuncs/subtract.hpp"
#include "nmtools/array/ufuncs/divide.hpp"
#include "nmtools/testing/doctest.hpp"

namespace nm = nmtools;
namespace na = nmtools;
namespace simd = na::simd;

#define SIMD_TEST_EQUAL(result, expect) \
{ \
    NMTOOLS_ASSERT_EQUAL( nm::shape(result), nm::shape(expect) ); \
    NMTOOLS_ASSERT_CLOSE( result, expect ); \
}

#define VECTOR_256_TEST(array,fn,...) \
{ \
    auto expect = na::fn(array,##__VA_ARGS__); \
    auto result = na::fn(array,##__VA_ARGS__,nm::casting::same_kind_t{},simd::vector_256); \
    SIMD_TEST_EQUAL(result,expect); \
}

/*********************** add ******************************/

#if 1
TEST_CASE("add(case1)" * doctest::test_suite("simd::vector_256"))
{
    auto lhs  = na::arange(128);
    auto rhs  = na::arange(128);
    VECTOR_256_TEST(lhs,add,rhs);
}

TEST_CASE("add(case2)" * doctest::test_suite("simd::vector_256"))
{
    auto lhs  = na::arange(128,nm::float64);
    auto rhs  = na::arange(128,nm::float64);
    VECTOR_256_TEST(lhs,add,rhs);
}

TEST_CASE("add(case3)" * doctest::test_suite("simd::vector_256"))
{
    auto lhs  = na::arange(0,8,0.125);
    auto rhs  = na::arange(0,8,0.125);
    VECTOR_256_TEST(lhs,add,rhs);
}

TEST_CASE("add(case4)" * doctest::test_suite("simd::vector_256"))
{
    auto lhs  = na::arange(129);
    auto rhs  = na::arange(129);
    VECTOR_256_TEST(lhs,add,rhs);
}

TEST_CASE("add(case5)" * doctest::test_suite("simd::vector_256"))
{
    auto lhs  = na::arange(127);
    auto rhs  = na::arange(127);
    VECTOR_256_TEST(lhs,add,rhs);
}

TEST_CASE("add(case6)" * doctest::test_suite("simd::vector_256"))
{
    auto lhs  = na::arange(129,nm::float64);
    auto rhs  = na::arange(129,nm::float64);
    VECTOR_256_TEST(lhs,add,rhs);
}

TEST_CASE("add(case7)" * doctest::test_suite("simd::vector_256"))
{
    auto lhs  = na::arange(127,nm::float64);
    auto rhs  = na::arange(127,nm::float64);
    VECTOR_256_TEST(lhs,add,rhs);
}

TEST_CASE("add(case8)" * doctest::test_suite("simd::vector_256"))
{
    auto lhs  = na::arange(3);
    auto rhs  = na::arange(3);
    VECTOR_256_TEST(lhs,add,rhs);
}

TEST_CASE("add(case9)" * doctest::test_suite("simd::vector_256"))
{
    auto lhs  = na::arange(5);
    auto rhs  = na::arange(5);
    VECTOR_256_TEST(lhs,add,rhs);
}

TEST_CASE("add(case10)" * doctest::test_suite("simd::vector_256"))
{
    auto lhs  = na::arange(3,nm::float64);
    auto rhs  = na::arange(3,nm::float64);
    VECTOR_256_TEST(lhs,add,rhs);
}

TEST_CASE("add(case11)" * doctest::test_suite("simd::vector_256"))
{
    auto lhs  = na::arange(5,nm::float64);
    auto rhs  = na::arange(5,nm::float64);
    VECTOR_256_TEST(lhs,add,rhs);
}

TEST_CASE("add(case12)" * doctest::test_suite("simd::vector_256"))
{
    auto lhs  = na::arange(1);
    auto rhs  = na::arange(1);
    VECTOR_256_TEST(lhs,add,rhs);
}

TEST_CASE("add(case13)" * doctest::test_suite("simd::vector_256"))
{
    auto lhs  = na::arange(1,nm::float64);
    auto rhs  = na::arange(1,nm::float64);
    VECTOR_256_TEST(lhs,add,rhs);
}

TEST_CASE("add(case14)" * doctest::test_suite("simd::vector_256"))
{
    auto lhs  = na::arange(128,nm::uint64);
    auto rhs  = na::arange(128,nm::uint64);
    VECTOR_256_TEST(lhs,add,rhs);
}

TEST_CASE("add(case15)" * doctest::test_suite("simd::vector_256"))
{
    auto lhs  = na::arange(128,nm::int64);
    auto rhs  = na::arange(128,nm::int64);
    VECTOR_256_TEST(lhs,add,rhs);
}

TEST_CASE("add(case16)" * doctest::test_suite("simd::vector_256"))
{
    auto lhs  = na::arange(128,nm::uint32);
    auto rhs  = na::arange(128,nm::uint32);
    VECTOR_256_TEST(lhs,add,rhs);
}

TEST_CASE("add(case17)" * doctest::test_suite("simd::vector_256"))
{
    auto lhs  = na::arange(128,nm::int32);
    auto rhs  = na::arange(128,nm::int32);
    VECTOR_256_TEST(lhs,add,rhs);
}

TEST_CASE("add(case18)" * doctest::test_suite("simd::vector_256"))
{
    auto lhs  = na::arange(128,nm::uint16);
    auto rhs  = na::arange(128,nm::uint16);
    VECTOR_256_TEST(lhs,add,rhs);
}

TEST_CASE("add(case19)" * doctest::test_suite("simd::vector_256"))
{
    auto lhs  = na::arange(128,nm::int16);
    auto rhs  = na::arange(128,nm::int16);
    VECTOR_256_TEST(lhs,add,rhs);
}

TEST_CASE("add(case20)" * doctest::test_suite("simd::vector_256"))
{
    auto lhs  = na::arange(128,nm::uint8);
    auto rhs  = na::arange(128,nm::uint8);
    VECTOR_256_TEST(lhs,add,rhs);
}

// TODO: support promotion casting
TEST_CASE("add(case21)" * doctest::test_suite("simd::vector_256") * doctest::skip())
{
    auto lhs  = na::arange(128,nm::int8);
    auto rhs  = na::arange(128,nm::int8);
    VECTOR_256_TEST(lhs,add,rhs);
}

TEST_CASE("add(case22)" * doctest::test_suite("simd::vector_256"))
{
    auto lhs  = na::arange(-128,127,nm::int64);
    auto rhs  = na::arange(-128,127,nm::int64);
    VECTOR_256_TEST(lhs,add,rhs);
}

TEST_CASE("add(case23)" * doctest::test_suite("simd::vector_256"))
{
    auto lhs  = na::arange(-128,127,nm::int32);
    auto rhs  = na::arange(-128,127,nm::int32);
    VECTOR_256_TEST(lhs,add,rhs);
}

TEST_CASE("add(case24)" * doctest::test_suite("simd::vector_256"))
{
    auto lhs  = na::arange(-128,127,nm::int16);
    auto rhs  = na::arange(-128,127,nm::int16);
    VECTOR_256_TEST(lhs,add,rhs);
}

TEST_CASE("add(case25)" * doctest::test_suite("simd::vector_256"))
{
    auto lhs  = na::arange(-64,63,nm::int8);
    auto rhs  = na::arange(-64,63,nm::int8);
    VECTOR_256_TEST(lhs,add,rhs);
}
#endif