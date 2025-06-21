#include "nmtools/evaluator/simd/x86_sse.hpp"
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

#define X86_SSE_TEST(fn,...) \
{ \
    auto expect = na::fn(__VA_ARGS__); \
    auto result = na::fn(__VA_ARGS__,simd::x86_SSE); \
    SIMD_TEST_EQUAL(result,expect); \
}

/*********************** add ******************************/

TEST_CASE("add.outer(case1a)" * doctest::test_suite("simd::x86_SSE"))
{
    auto lhs  = na::arange(128);
    auto rhs  = na::arange(128);
    X86_SSE_TEST(add.outer,lhs,rhs,nm::None);
}

TEST_CASE("add.outer(case1b)" * doctest::test_suite("simd::x86_SSE"))
{
    auto lhs  = na::arange(128,nm::float64);
    auto rhs  = na::arange(128,nm::float64);
    X86_SSE_TEST(add.outer,lhs,rhs,nm::None);
}

// TODO: support low precision int
#if 0
TEST_CASE("add.outer(case1c)" * doctest::test_suite("simd::x86_SSE"))
{
    auto lhs  = na::arange(128,nm::int8);
    auto rhs  = na::arange(128,nm::int8);
    X86_SSE_TEST(add.outer,lhs,rhs,nm::None);
}

TEST_CASE("add.outer(case1d)" * doctest::test_suite("simd::x86_SSE"))
{
    auto lhs  = na::arange(128,nm::int16);
    auto rhs  = na::arange(128,nm::int16);
    X86_SSE_TEST(add.outer,lhs,rhs,nm::None);
}
#endif

TEST_CASE("add.outer(case1e)" * doctest::test_suite("simd::x86_SSE"))
{
    auto lhs  = na::arange(128,nm::int32);
    auto rhs  = na::arange(128,nm::int32);
    X86_SSE_TEST(add.outer,lhs,rhs,nm::None);
}

TEST_CASE("add.outer(case1f)" * doctest::test_suite("simd::x86_SSE"))
{
    auto lhs  = na::arange(128,nm::int64);
    auto rhs  = na::arange(128,nm::int64);
    X86_SSE_TEST(add.outer,lhs,rhs,nm::None);
}

TEST_CASE("add.outer(case2a)" * doctest::test_suite("simd::x86_SSE"))
{
    auto lhs  = na::arange(-64,64);
    auto rhs  = na::arange(-64,64);
    X86_SSE_TEST(add.outer,lhs,rhs,nm::None);
}

TEST_CASE("add.outer(case2b)" * doctest::test_suite("simd::x86_SSE"))
{
    auto lhs  = na::arange(-64,64,nm::float64);
    auto rhs  = na::arange(-64,64,nm::float64);
    X86_SSE_TEST(add.outer,lhs,rhs,nm::None);
}

// TODO: support low precision int
#if 0
TEST_CASE("add.outer(case2c)" * doctest::test_suite("simd::x86_SSE"))
{
    auto lhs  = na::arange(-64,64,nm::int8);
    auto rhs  = na::arange(-64,64,nm::int8);
    X86_SSE_TEST(add.outer,lhs,rhs,nm::None);
}

TEST_CASE("add.outer(case2d)" * doctest::test_suite("simd::x86_SSE"))
{
    auto lhs  = na::arange(-64,64,nm::int16);
    auto rhs  = na::arange(-64,64,nm::int16);
    X86_SSE_TEST(add.outer,lhs,rhs,nm::None);
}
#endif

TEST_CASE("add.outer(case2e)" * doctest::test_suite("simd::x86_SSE"))
{
    auto lhs  = na::arange(-64,64,nm::int32);
    auto rhs  = na::arange(-64,64,nm::int32);
    X86_SSE_TEST(add.outer,lhs,rhs,nm::None);
}

TEST_CASE("add.outer(case2f)" * doctest::test_suite("simd::x86_SSE"))
{
    auto lhs  = na::arange(-64,64,nm::int64);
    auto rhs  = na::arange(-64,64,nm::int64);
    X86_SSE_TEST(add.outer,lhs,rhs,nm::None);
}

/*********************** multiply ******************************/

TEST_CASE("multiply.outer(case1a)" * doctest::test_suite("simd::x86_SSE"))
{
    auto lhs  = na::arange(128);
    auto rhs  = na::arange(128);
    X86_SSE_TEST(multiply.outer,lhs,rhs,nm::None);
}

TEST_CASE("multiply.outer(case1b)" * doctest::test_suite("simd::x86_SSE"))
{
    auto lhs  = na::arange(128,nm::float64);
    auto rhs  = na::arange(128,nm::float64);
    X86_SSE_TEST(multiply.outer,lhs,rhs,nm::None);
}

// TODO: support low precision int
#if 0
TEST_CASE("multiply.outer(case1c)" * doctest::test_suite("simd::x86_SSE"))
{
    auto lhs  = na::arange(128,nm::int8);
    auto rhs  = na::arange(128,nm::int8);
    X86_SSE_TEST(multiply.outer,lhs,rhs,nm::None);
}

TEST_CASE("multiply.outer(case1d)" * doctest::test_suite("simd::x86_SSE"))
{
    auto lhs  = na::arange(128,nm::int16);
    auto rhs  = na::arange(128,nm::int16);
    X86_SSE_TEST(multiply.outer,lhs,rhs,nm::None);
}
#endif

TEST_CASE("multiply.outer(case1e)" * doctest::test_suite("simd::x86_SSE"))
{
    auto lhs  = na::arange(128,nm::int32);
    auto rhs  = na::arange(128,nm::int32);
    X86_SSE_TEST(multiply.outer,lhs,rhs,nm::None);
}

// TODO: fix
#if 0
TEST_CASE("multiply.outer(case1f)" * doctest::test_suite("simd::x86_SSE"))
{
    auto lhs  = na::arange(128,nm::int64);
    auto rhs  = na::arange(128,nm::int64);
    X86_SSE_TEST(multiply.outer,lhs,rhs,nm::None);
}
#endif

TEST_CASE("multiply.outer(case2a)" * doctest::test_suite("simd::x86_SSE"))
{
    auto lhs  = na::arange(-64,64);
    auto rhs  = na::arange(-64,64);
    X86_SSE_TEST(multiply.outer,lhs,rhs,nm::None);
}

TEST_CASE("multiply.outer(case2b)" * doctest::test_suite("simd::x86_SSE"))
{
    auto lhs  = na::arange(-64,64,nm::float64);
    auto rhs  = na::arange(-64,64,nm::float64);
    X86_SSE_TEST(multiply.outer,lhs,rhs,nm::None);
}

// TODO: support low precision int
#if 0
TEST_CASE("multiply.outer(case2c)" * doctest::test_suite("simd::x86_SSE"))
{
    auto lhs  = na::arange(-64,64,nm::int8);
    auto rhs  = na::arange(-64,64,nm::int8);
    X86_SSE_TEST(multiply.outer,lhs,rhs,nm::None);
}

TEST_CASE("multiply.outer(case2d)" * doctest::test_suite("simd::x86_SSE"))
{
    auto lhs  = na::arange(-64,64,nm::int16);
    auto rhs  = na::arange(-64,64,nm::int16);
    X86_SSE_TEST(multiply.outer,lhs,rhs,nm::None);
}
#endif

TEST_CASE("multiply.outer(case2e)" * doctest::test_suite("simd::x86_SSE"))
{
    auto lhs  = na::arange(-64,64,nm::int32);
    auto rhs  = na::arange(-64,64,nm::int32);
    X86_SSE_TEST(multiply.outer,lhs,rhs,nm::None);
}

// TODO: workaround
#if 0
TEST_CASE("multiply.outer(case2f)" * doctest::test_suite("simd::x86_SSE"))
{
    auto lhs  = na::arange(-64,64,nm::int64);
    auto rhs  = na::arange(-64,64,nm::int64);
    X86_SSE_TEST(multiply.outer,lhs,rhs,nm::None);
}
#endif