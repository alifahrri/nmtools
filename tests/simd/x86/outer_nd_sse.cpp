#include "nmtools/array/eval/simd/x86_sse.hpp"
#include "nmtools/array/array/arange.hpp"
#include "nmtools/array/array/ufuncs/add.hpp"
#include "nmtools/array/array/ufuncs/multiply.hpp"
#include "nmtools/array/array/ufuncs/subtract.hpp"
#include "nmtools/array/array/ufuncs/divide.hpp"
#include "nmtools/array/array/reshape.hpp"
#include "nmtools/testing/doctest.hpp"

namespace nm = nmtools;
namespace na = nm::array;
namespace ix = nm::index;
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

TEST_CASE("add.outer_nd(case1a)" * doctest::test_suite("simd::x86_SSE"))
{
    auto dtype = nm::float32;
    auto lhs_shape = nmtools_array{2,3};
    auto rhs_shape = nmtools_array{4,5,6};
    auto lhs_size = ix::product(lhs_shape);
    auto rhs_size = ix::product(rhs_shape);
    auto lhs = na::reshape(na::arange(lhs_size,dtype),lhs_shape);
    auto rhs = na::reshape(na::arange(rhs_size,dtype),rhs_shape);
    X86_SSE_TEST(add.outer,lhs,rhs,nm::None);
}

#if 1
TEST_CASE("add.outer_nd(case1b)" * doctest::test_suite("simd::x86_SSE"))
{
    auto dtype = nm::int32;
    auto lhs_shape = nmtools_array{2,3};
    auto rhs_shape = nmtools_array{4,5,6};
    auto lhs_size = ix::product(lhs_shape);
    auto rhs_size = ix::product(rhs_shape);
    auto lhs = na::reshape(na::arange(lhs_size,dtype),lhs_shape);
    auto rhs = na::reshape(na::arange(rhs_size,dtype),rhs_shape);
    X86_SSE_TEST(add.outer,lhs,rhs,nm::None);
}

TEST_CASE("add.outer_nd(case1c)" * doctest::test_suite("simd::x86_SSE"))
{
    auto dtype = nm::float64;
    auto lhs_shape = nmtools_array{2,3};
    auto rhs_shape = nmtools_array{4,5,6};
    auto lhs_size = ix::product(lhs_shape);
    auto rhs_size = ix::product(rhs_shape);
    auto lhs = na::reshape(na::arange(lhs_size,dtype),lhs_shape);
    auto rhs = na::reshape(na::arange(rhs_size,dtype),rhs_shape);
    X86_SSE_TEST(add.outer,lhs,rhs,nm::None);
}

TEST_CASE("add.outer_nd(case1d)" * doctest::test_suite("simd::x86_SSE"))
{
    auto dtype = nm::int64;
    auto lhs_shape = nmtools_array{2,3};
    auto rhs_shape = nmtools_array{4,5,6};
    auto lhs_size = ix::product(lhs_shape);
    auto rhs_size = ix::product(rhs_shape);
    auto lhs = na::reshape(na::arange(lhs_size,dtype),lhs_shape);
    auto rhs = na::reshape(na::arange(rhs_size,dtype),rhs_shape);
    X86_SSE_TEST(add.outer,lhs,rhs,nm::None);
}

#endif

TEST_CASE("add.outer_nd(case2a)" * doctest::test_suite("simd::x86_SSE"))
{
    auto dtype = nm::float32;
    auto lhs_shape = nmtools_array{1,4,2,3};
    auto rhs_shape = nmtools_array{4,5,1,6};
    auto lhs_size = ix::product(lhs_shape);
    auto rhs_size = ix::product(rhs_shape);
    auto lhs = na::reshape(na::arange(lhs_size,dtype),lhs_shape);
    auto rhs = na::reshape(na::arange(rhs_size,dtype),rhs_shape);
    X86_SSE_TEST(add.outer,lhs,rhs,nm::None);
}

#if 1
TEST_CASE("add.outer_nd(case2b)" * doctest::test_suite("simd::x86_SSE"))
{
    auto dtype = nm::int32;
    auto lhs_shape = nmtools_array{1,4,2,3};
    auto rhs_shape = nmtools_array{4,5,1,7};
    auto lhs_size = ix::product(lhs_shape);
    auto rhs_size = ix::product(rhs_shape);
    auto lhs = na::reshape(na::arange(lhs_size,dtype),lhs_shape);
    auto rhs = na::reshape(na::arange(rhs_size,dtype),rhs_shape);
    X86_SSE_TEST(add.outer,lhs,rhs,nm::None);
}

TEST_CASE("add.outer_nd(case2c)" * doctest::test_suite("simd::x86_SSE"))
{
    auto dtype = nm::float64;
    auto lhs_shape = nmtools_array{1,4,2,3};
    auto rhs_shape = nmtools_array{4,5,1,8};
    auto lhs_size = ix::product(lhs_shape);
    auto rhs_size = ix::product(rhs_shape);
    auto lhs = na::reshape(na::arange(lhs_size,dtype),lhs_shape);
    auto rhs = na::reshape(na::arange(rhs_size,dtype),rhs_shape);
    X86_SSE_TEST(add.outer,lhs,rhs,nm::None);
}

TEST_CASE("add.outer_nd(case2d)" * doctest::test_suite("simd::x86_SSE"))
{
    auto dtype = nm::int64;
    auto lhs_shape = nmtools_array{1,4,2,3};
    auto rhs_shape = nmtools_array{4,5,1,9};
    auto lhs_size = ix::product(lhs_shape);
    auto rhs_size = ix::product(rhs_shape);
    auto lhs = na::reshape(na::arange(lhs_size,dtype),lhs_shape);
    auto rhs = na::reshape(na::arange(rhs_size,dtype),rhs_shape);
    X86_SSE_TEST(add.outer,lhs,rhs,nm::None);
}

#endif

/*********************** multiply ******************************/

TEST_CASE("multiply.outer_nd(case1a)" * doctest::test_suite("simd::x86_SSE"))
{
    auto dtype = nm::float32;
    auto lhs_shape = nmtools_array{2,3};
    auto rhs_shape = nmtools_array{4,5,6};
    auto lhs_size = ix::product(lhs_shape);
    auto rhs_size = ix::product(rhs_shape);
    auto lhs = na::reshape(na::arange(lhs_size,dtype),lhs_shape);
    auto rhs = na::reshape(na::arange(rhs_size,dtype),rhs_shape);
    X86_SSE_TEST(multiply.outer,lhs,rhs,nm::None);
}

TEST_CASE("multiply.outer_nd(case1b)" * doctest::test_suite("simd::x86_SSE"))
{
    auto dtype = nm::int32;
    auto lhs_shape = nmtools_array{2,3};
    auto rhs_shape = nmtools_array{4,5,6};
    auto lhs_size = ix::product(lhs_shape);
    auto rhs_size = ix::product(rhs_shape);
    auto lhs = na::reshape(na::arange(lhs_size,dtype),lhs_shape);
    auto rhs = na::reshape(na::arange(rhs_size,dtype),rhs_shape);
    X86_SSE_TEST(multiply.outer,lhs,rhs,nm::None);
}

TEST_CASE("multiply.outer_nd(case1c)" * doctest::test_suite("simd::x86_SSE"))
{
    auto dtype = nm::float64;
    auto lhs_shape = nmtools_array{2,3};
    auto rhs_shape = nmtools_array{4,5,6};
    auto lhs_size = ix::product(lhs_shape);
    auto rhs_size = ix::product(rhs_shape);
    auto lhs = na::reshape(na::arange(lhs_size,dtype),lhs_shape);
    auto rhs = na::reshape(na::arange(rhs_size,dtype),rhs_shape);
    X86_SSE_TEST(multiply.outer,lhs,rhs,nm::None);
}

// TODO: fix simd int64 multiply
#if 0
TEST_CASE("multiply.outer_nd(case1d)" * doctest::test_suite("simd::x86_SSE"))
{
    auto dtype = nm::int64;
    auto lhs_shape = nmtools_array{2,3};
    auto rhs_shape = nmtools_array{4,5,6};
    auto lhs_size = ix::product(lhs_shape);
    auto rhs_size = ix::product(rhs_shape);
    auto lhs = na::reshape(na::arange(lhs_size,dtype),lhs_shape);
    auto rhs = na::reshape(na::arange(rhs_size,dtype),rhs_shape);
    X86_SSE_TEST(multiply.outer,lhs,rhs,nm::None);
}
#endif

TEST_CASE("multiply.outer_nd(case2a)" * doctest::test_suite("simd::x86_SSE"))
{
    auto dtype = nm::float32;
    auto lhs_shape = nmtools_array{1,4,2,3};
    auto rhs_shape = nmtools_array{4,5,1,6};
    auto lhs_size = ix::product(lhs_shape);
    auto rhs_size = ix::product(rhs_shape);
    auto lhs = na::reshape(na::arange(lhs_size,dtype),lhs_shape);
    auto rhs = na::reshape(na::arange(rhs_size,dtype),rhs_shape);
    X86_SSE_TEST(multiply.outer,lhs,rhs,nm::None);
}

TEST_CASE("multiply.outer_nd(case2b)" * doctest::test_suite("simd::x86_SSE"))
{
    auto dtype = nm::int32;
    auto lhs_shape = nmtools_array{1,4,2,3};
    auto rhs_shape = nmtools_array{4,5,1,7};
    auto lhs_size = ix::product(lhs_shape);
    auto rhs_size = ix::product(rhs_shape);
    auto lhs = na::reshape(na::arange(lhs_size,dtype),lhs_shape);
    auto rhs = na::reshape(na::arange(rhs_size,dtype),rhs_shape);
    X86_SSE_TEST(multiply.outer,lhs,rhs,nm::None);
}

TEST_CASE("multiply.outer_nd(case2c)" * doctest::test_suite("simd::x86_SSE"))
{
    auto dtype = nm::float64;
    auto lhs_shape = nmtools_array{1,4,2,3};
    auto rhs_shape = nmtools_array{4,5,1,8};
    auto lhs_size = ix::product(lhs_shape);
    auto rhs_size = ix::product(rhs_shape);
    auto lhs = na::reshape(na::arange(lhs_size,dtype),lhs_shape);
    auto rhs = na::reshape(na::arange(rhs_size,dtype),rhs_shape);
    X86_SSE_TEST(multiply.outer,lhs,rhs,nm::None);
}

// TODO: fix simd multiply
#if 0
TEST_CASE("multiply.outer_nd(case2d)" * doctest::test_suite("simd::x86_SSE"))
{
    auto dtype = nm::int64;
    auto lhs_shape = nmtools_array{1,4,2,3};
    auto rhs_shape = nmtools_array{4,5,1,9};
    auto lhs_size = ix::product(lhs_shape);
    auto rhs_size = ix::product(rhs_shape);
    auto lhs = na::reshape(na::arange(lhs_size,dtype),lhs_shape);
    auto rhs = na::reshape(na::arange(rhs_size,dtype),rhs_shape);
    X86_SSE_TEST(multiply.outer,lhs,rhs,nm::None);
}

#endif