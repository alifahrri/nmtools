#include "nmtools/array/evaluator/simd/vector_512.hpp"
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

#define VECTOR_512_TEST(fn,...) \
{ \
    auto expect = na::fn(__VA_ARGS__); \
    auto result = na::fn(__VA_ARGS__,simd::vector_512); \
    SIMD_TEST_EQUAL(result,expect); \
}

/*********************** add ******************************/

TEST_CASE("add.outer(case1a)" * doctest::test_suite("simd::vector_512"))
{
    auto lhs  = na::arange(128);
    auto rhs  = na::arange(128);
    VECTOR_512_TEST(add.outer,lhs,rhs,nm::None);
}

TEST_CASE("add.outer(case1b)" * doctest::test_suite("simd::vector_512"))
{
    auto lhs  = na::arange(128,nm::float64);
    auto rhs  = na::arange(128,nm::float64);
    VECTOR_512_TEST(add.outer,lhs,rhs,nm::None);
}

// TODO: support low precision int
#if 0
TEST_CASE("add.outer(case1c)" * doctest::test_suite("simd::vector_512"))
{
    auto lhs  = na::arange(128,nm::int8);
    auto rhs  = na::arange(128,nm::int8);
    VECTOR_512_TEST(add.outer,lhs,rhs,nm::None);
}

TEST_CASE("add.outer(case1d)" * doctest::test_suite("simd::vector_512"))
{
    auto lhs  = na::arange(128,nm::int16);
    auto rhs  = na::arange(128,nm::int16);
    VECTOR_512_TEST(add.outer,lhs,rhs,nm::None);
}
#endif

TEST_CASE("add.outer(case1e)" * doctest::test_suite("simd::vector_512"))
{
    auto lhs  = na::arange(128,nm::int32);
    auto rhs  = na::arange(128,nm::int32);
    VECTOR_512_TEST(add.outer,lhs,rhs,nm::None);
}

TEST_CASE("add.outer(case1f)" * doctest::test_suite("simd::vector_512"))
{
    auto lhs  = na::arange(128,nm::int64);
    auto rhs  = na::arange(128,nm::int64);
    VECTOR_512_TEST(add.outer,lhs,rhs,nm::None);
}

TEST_CASE("add.outer(case2a)" * doctest::test_suite("simd::vector_512"))
{
    auto lhs  = na::arange(-64,64);
    auto rhs  = na::arange(-64,64);
    VECTOR_512_TEST(add.outer,lhs,rhs,nm::None);
}

TEST_CASE("add.outer(case2b)" * doctest::test_suite("simd::vector_512"))
{
    auto lhs  = na::arange(-64,64,nm::float64);
    auto rhs  = na::arange(-64,64,nm::float64);
    VECTOR_512_TEST(add.outer,lhs,rhs,nm::None);
}

// TODO: support low precision int
#if 0
TEST_CASE("add.outer(case2c)" * doctest::test_suite("simd::vector_512"))
{
    auto lhs  = na::arange(-64,64,nm::int8);
    auto rhs  = na::arange(-64,64,nm::int8);
    VECTOR_512_TEST(add.outer,lhs,rhs,nm::None);
}

TEST_CASE("add.outer(case2d)" * doctest::test_suite("simd::vector_512"))
{
    auto lhs  = na::arange(-64,64,nm::int16);
    auto rhs  = na::arange(-64,64,nm::int16);
    VECTOR_512_TEST(add.outer,lhs,rhs,nm::None);
}
#endif

TEST_CASE("add.outer(case2e)" * doctest::test_suite("simd::vector_512"))
{
    auto lhs  = na::arange(-64,64,nm::int32);
    auto rhs  = na::arange(-64,64,nm::int32);
    VECTOR_512_TEST(add.outer,lhs,rhs,nm::None);
}

TEST_CASE("add.outer(case2f)" * doctest::test_suite("simd::vector_512"))
{
    auto lhs  = na::arange(-64,64,nm::int64);
    auto rhs  = na::arange(-64,64,nm::int64);
    VECTOR_512_TEST(add.outer,lhs,rhs,nm::None);
}

/*********************** multiply ******************************/

TEST_CASE("multiply.outer(case1a)" * doctest::test_suite("simd::vector_512"))
{
    auto lhs  = na::arange(128);
    auto rhs  = na::arange(128);
    VECTOR_512_TEST(multiply.outer,lhs,rhs,nm::None);
}

TEST_CASE("multiply.outer(case1b)" * doctest::test_suite("simd::vector_512"))
{
    auto lhs  = na::arange(128,nm::float64);
    auto rhs  = na::arange(128,nm::float64);
    VECTOR_512_TEST(multiply.outer,lhs,rhs,nm::None);
}

// TODO: support low precision int
#if 0
TEST_CASE("multiply.outer(case1c)" * doctest::test_suite("simd::vector_512"))
{
    auto lhs  = na::arange(128,nm::int8);
    auto rhs  = na::arange(128,nm::int8);
    VECTOR_512_TEST(multiply.outer,lhs,rhs,nm::None);
}

TEST_CASE("multiply.outer(case1d)" * doctest::test_suite("simd::vector_512"))
{
    auto lhs  = na::arange(128,nm::int16);
    auto rhs  = na::arange(128,nm::int16);
    VECTOR_512_TEST(multiply.outer,lhs,rhs,nm::None);
}
#endif

TEST_CASE("multiply.outer(case1e)" * doctest::test_suite("simd::vector_512"))
{
    auto lhs  = na::arange(128,nm::int32);
    auto rhs  = na::arange(128,nm::int32);
    VECTOR_512_TEST(multiply.outer,lhs,rhs,nm::None);
}

TEST_CASE("multiply.outer(case1f)" * doctest::test_suite("simd::vector_512"))
{
    auto lhs  = na::arange(128,nm::int64);
    auto rhs  = na::arange(128,nm::int64);
    VECTOR_512_TEST(multiply.outer,lhs,rhs,nm::None);
}

TEST_CASE("multiply.outer(case2a)" * doctest::test_suite("simd::vector_512"))
{
    auto lhs  = na::arange(-64,64);
    auto rhs  = na::arange(-64,64);
    VECTOR_512_TEST(multiply.outer,lhs,rhs,nm::None);
}

TEST_CASE("multiply.outer(case2b)" * doctest::test_suite("simd::vector_512"))
{
    auto lhs  = na::arange(-64,64,nm::float64);
    auto rhs  = na::arange(-64,64,nm::float64);
    VECTOR_512_TEST(multiply.outer,lhs,rhs,nm::None);
}

// TODO: support low precision int
#if 0
TEST_CASE("multiply.outer(case2c)" * doctest::test_suite("simd::vector_512"))
{
    auto lhs  = na::arange(-64,64,nm::int8);
    auto rhs  = na::arange(-64,64,nm::int8);
    VECTOR_512_TEST(multiply.outer,lhs,rhs,nm::None);
}

TEST_CASE("multiply.outer(case2d)" * doctest::test_suite("simd::vector_512"))
{
    auto lhs  = na::arange(-64,64,nm::int16);
    auto rhs  = na::arange(-64,64,nm::int16);
    VECTOR_512_TEST(multiply.outer,lhs,rhs,nm::None);
}
#endif

TEST_CASE("multiply.outer(case2e)" * doctest::test_suite("simd::vector_512"))
{
    auto lhs  = na::arange(-64,64,nm::int32);
    auto rhs  = na::arange(-64,64,nm::int32);
    VECTOR_512_TEST(multiply.outer,lhs,rhs,nm::None);
}

TEST_CASE("multiply.outer(case2f)" * doctest::test_suite("simd::vector_512"))
{
    auto lhs  = na::arange(-64,64,nm::int64);
    auto rhs  = na::arange(-64,64,nm::int64);
    VECTOR_512_TEST(multiply.outer,lhs,rhs,nm::None);
}