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
namespace simd = na::simd;
namespace meta = nm::meta;

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

TEST_CASE("add.reduce_2d(case1a)" * doctest::test_suite("simd::x86_SSE"))
{
    auto M = 3;
    auto N = 4;
    auto axis = meta::ct_v<0>;
    auto new_shape = nmtools_array{M,N};
    auto input     = na::reshape(na::arange(M*N),new_shape);
    auto dtype     = nm::None;
    auto initial   = nm::None;
    auto keepdims  = nm::True;
    X86_SSE_TEST(add.reduce,input,axis,dtype,initial,keepdims);
}

TEST_CASE("add.reduce_2d(case1b)" * doctest::test_suite("simd::x86_SSE"))
{
    auto M = 3;
    auto N = 4;
    auto axis = 0;
    auto new_shape = nmtools_array{M,N};
    auto input     = na::reshape(na::arange(M*N),new_shape);
    auto dtype     = nm::None;
    auto initial   = nm::None;
    auto keepdims  = nm::True;
    X86_SSE_TEST(add.reduce,input,axis,dtype,initial,keepdims);
}

TEST_CASE("add.reduce_2d(case2a)" * doctest::test_suite("simd::x86_SSE"))
{
    auto M = 3;
    auto N = 4;
    auto axis = meta::ct_v<1>;
    auto new_shape = nmtools_array{M,N};
    auto input     = na::reshape(na::arange(M*N),new_shape);
    auto dtype     = nm::None;
    auto initial   = nm::None;
    auto keepdims  = nm::True;
    X86_SSE_TEST(add.reduce,input,axis,dtype,initial,keepdims);
}

TEST_CASE("add.reduce_2d(case2b)" * doctest::test_suite("simd::x86_SSE"))
{
    auto M = 3;
    auto N = 4;
    auto axis = 1;
    auto new_shape = nmtools_array{M,N};
    auto input     = na::reshape(na::arange(M*N),new_shape);
    auto dtype     = nm::None;
    auto initial   = nm::None;
    auto keepdims  = nm::True;
    X86_SSE_TEST(add.reduce,input,axis,dtype,initial,keepdims);
}

TEST_CASE("add.reduce_2d(case3a)" * doctest::test_suite("simd::x86_SSE"))
{
    auto M = 4;
    auto N = 10;
    auto axis = meta::ct_v<0>;
    auto new_shape = nmtools_array{M,N};
    auto input     = na::reshape(na::arange(M*N),new_shape);
    auto dtype     = nm::None;
    auto initial   = nm::None;
    auto keepdims  = nm::True;
    X86_SSE_TEST(add.reduce,input,axis,dtype,initial,keepdims);
}

TEST_CASE("add.reduce_2d(case3b)" * doctest::test_suite("simd::x86_SSE"))
{
    auto M = 4;
    auto N = 10;
    auto axis = 0;
    auto new_shape = nmtools_array{M,N};
    auto input     = na::reshape(na::arange(M*N),new_shape);
    auto dtype     = nm::None;
    auto initial   = nm::None;
    auto keepdims  = nm::True;
    X86_SSE_TEST(add.reduce,input,axis,dtype,initial,keepdims);
}

#if 0
TEST_CASE("add.reduce_2d(case3c)" * doctest::test_suite("simd::x86_SSE"))
{
    auto M = 4;
    auto N = 10;
    auto axis = meta::ct_v<1>;
    auto new_shape = nmtools_array{M,N};
    auto input     = na::reshape(na::arange(M*N),new_shape);
    auto dtype     = nm::None;
    auto initial   = nm::None;
    auto keepdims  = nm::True;
    X86_SSE_TEST(add.reduce,input,axis,dtype,initial,keepdims);
}

TEST_CASE("add.reduce_2d(case3d)" * doctest::test_suite("simd::x86_SSE"))
{
    auto M = 4;
    auto N = 10;
    auto axis = 1;
    auto new_shape = nmtools_array{M,N};
    auto input     = na::reshape(na::arange(M*N),new_shape);
    auto dtype     = nm::None;
    auto initial   = nm::None;
    auto keepdims  = nm::True;
    X86_SSE_TEST(add.reduce,input,axis,dtype,initial,keepdims);
}
#endif


TEST_CASE("add.reduce_2d(case4a)" * doctest::test_suite("simd::x86_SSE"))
{
    auto M = 8;
    auto N = 20;
    auto axis = meta::ct_v<0>;
    auto new_shape = nmtools_array{M,N};
    auto input     = na::reshape(na::arange(M*N),new_shape);
    auto dtype     = nm::None;
    auto initial   = nm::None;
    auto keepdims  = nm::True;
    X86_SSE_TEST(add.reduce,input,axis,dtype,initial,keepdims);
}

TEST_CASE("add.reduce_2d(case4b)" * doctest::test_suite("simd::x86_SSE"))
{
    auto M = 8;
    auto N = 20;
    auto axis = 0;
    auto new_shape = nmtools_array{M,N};
    auto input     = na::reshape(na::arange(M*N),new_shape);
    auto dtype     = nm::None;
    auto initial   = nm::None;
    auto keepdims  = nm::True;
    X86_SSE_TEST(add.reduce,input,axis,dtype,initial,keepdims);
}


TEST_CASE("add.reduce_2d(case5a)" * doctest::test_suite("simd::x86_SSE"))
{
    auto M = 12;
    auto N = 26;
    auto axis = meta::ct_v<0>;
    auto new_shape = nmtools_array{M,N};
    auto input     = na::reshape(na::arange(M*N),new_shape);
    auto dtype     = nm::None;
    auto initial   = nm::None;
    auto keepdims  = nm::True;
    X86_SSE_TEST(add.reduce,input,axis,dtype,initial,keepdims);
}

TEST_CASE("add.reduce_2d(case5b)" * doctest::test_suite("simd::x86_SSE"))
{
    auto M = 12;
    auto N = 26;
    auto axis = 0;
    auto new_shape = nmtools_array{M,N};
    auto input     = na::reshape(na::arange(M*N),new_shape);
    auto dtype     = nm::None;
    auto initial   = nm::None;
    auto keepdims  = nm::True;
    X86_SSE_TEST(add.reduce,input,axis,dtype,initial,keepdims);
}

TEST_CASE("add.reduce_2d(case6a)" * doctest::test_suite("simd::x86_SSE"))
{
    auto M = 13;
    auto N = 29;
    auto axis = meta::ct_v<0>;
    auto new_shape = nmtools_array{M,N};
    auto input     = na::reshape(na::arange(M*N),new_shape);
    auto dtype     = nm::None;
    auto initial   = nm::None;
    auto keepdims  = nm::True;
    X86_SSE_TEST(add.reduce,input,axis,dtype,initial,keepdims);
}

TEST_CASE("add.reduce_2d(case6b)" * doctest::test_suite("simd::x86_SSE"))
{
    auto M = 13;
    auto N = 29;
    auto axis = 0;
    auto new_shape = nmtools_array{M,N};
    auto input     = na::reshape(na::arange(M*N),new_shape);
    auto dtype     = nm::None;
    auto initial   = nm::None;
    auto keepdims  = nm::True;
    X86_SSE_TEST(add.reduce,input,axis,dtype,initial,keepdims);
}