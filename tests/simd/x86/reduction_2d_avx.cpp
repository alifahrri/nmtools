#include "nmtools/evaluator/simd/x86_avx.hpp"
#include "nmtools/array/arange.hpp"
#include "nmtools/array/ufuncs/add.hpp"
#include "nmtools/array/ufuncs/multiply.hpp"
#include "nmtools/array/ufuncs/subtract.hpp"
#include "nmtools/array/ufuncs/divide.hpp"
#include "nmtools/array/reshape.hpp"
#include "nmtools/testing/doctest.hpp"

namespace nm = nmtools;
namespace na = nm::array;
namespace simd = na::simd;
namespace meta = nm::meta;

// TODO: do not explicitly unwrap, fix eval
using nmtools::unwrap;

#define SIMD_TEST_EQUAL(result, expect) \
{ \
    NMTOOLS_ASSERT_EQUAL( nm::shape(result), nm::shape(expect) ); \
    NMTOOLS_ASSERT_CLOSE( result, expect ); \
}

#define X86_AVX_TEST(fn,...) \
{ \
    auto expect = na::fn(__VA_ARGS__); \
    auto result = na::fn(__VA_ARGS__,simd::x86_AVX); \
    SIMD_TEST_EQUAL(result,expect); \
}

/*********************** add ******************************/

TEST_CASE("add.reduce_2d(case1a)" * doctest::test_suite("simd::x86_AVX"))
{
    auto M = 3;
    auto N = 4;
    auto axis = meta::ct_v<0>;
    auto new_shape = nmtools_array{M,N};
    auto input     = na::reshape(na::arange(M*N),new_shape);
    auto dtype     = nm::None;
    auto initial   = nm::None;
    auto keepdims  = nm::True;
    X86_AVX_TEST(add.reduce,unwrap(input),axis,dtype,initial,keepdims);
}

TEST_CASE("add.reduce_2d(case1b)" * doctest::test_suite("simd::x86_AVX"))
{
    auto M = 3;
    auto N = 4;
    auto axis = 0;
    auto new_shape = nmtools_array{M,N};
    auto input     = na::reshape(na::arange(M*N),new_shape);
    auto dtype     = nm::None;
    auto initial   = nm::None;
    auto keepdims  = nm::True;
    X86_AVX_TEST(add.reduce,unwrap(input),axis,dtype,initial,keepdims);
}

TEST_CASE("add.reduce_2d(case2a)" * doctest::test_suite("simd::x86_AVX"))
{
    auto M = 3;
    auto N = 4;
    auto axis = meta::ct_v<1>;
    auto new_shape = nmtools_array{M,N};
    auto input     = na::reshape(na::arange(M*N),new_shape);
    auto dtype     = nm::None;
    auto initial   = nm::None;
    auto keepdims  = nm::True;
    X86_AVX_TEST(add.reduce,unwrap(input),axis,dtype,initial,keepdims);
}

TEST_CASE("add.reduce_2d(case2b)" * doctest::test_suite("simd::x86_AVX"))
{
    auto M = 3;
    auto N = 4;
    auto axis = 1;
    auto new_shape = nmtools_array{M,N};
    auto input     = na::reshape(na::arange(M*N),new_shape);
    auto dtype     = nm::None;
    auto initial   = nm::None;
    auto keepdims  = nm::True;
    X86_AVX_TEST(add.reduce,unwrap(input),axis,dtype,initial,keepdims);
}

TEST_CASE("add.reduce_2d(case3a)" * doctest::test_suite("simd::x86_AVX"))
{
    auto M = 4;
    auto N = 10;
    auto axis = meta::ct_v<0>;
    auto new_shape = nmtools_array{M,N};
    auto input     = na::reshape(na::arange(M*N),new_shape);
    auto dtype     = nm::None;
    auto initial   = nm::None;
    auto keepdims  = nm::True;
    X86_AVX_TEST(add.reduce,unwrap(input),axis,dtype,initial,keepdims);
}

TEST_CASE("add.reduce_2d(case3b)" * doctest::test_suite("simd::x86_AVX"))
{
    auto M = 4;
    auto N = 10;
    auto axis = 0;
    auto new_shape = nmtools_array{M,N};
    auto input     = na::reshape(na::arange(M*N),new_shape);
    auto dtype     = nm::None;
    auto initial   = nm::None;
    auto keepdims  = nm::True;
    X86_AVX_TEST(add.reduce,unwrap(input),axis,dtype,initial,keepdims);
}

#if 1
TEST_CASE("add.reduce_2d(case3c)" * doctest::test_suite("simd::x86_AVX"))
{
    auto M = 4;
    auto N = 10;
    auto axis = meta::ct_v<1>;
    auto new_shape = nmtools_array{M,N};
    auto input     = na::reshape(na::arange(M*N),new_shape);
    auto dtype     = nm::None;
    auto initial   = nm::None;
    auto keepdims  = nm::True;
    X86_AVX_TEST(add.reduce,unwrap(input),axis,dtype,initial,keepdims);
}

TEST_CASE("add.reduce_2d(case3d)" * doctest::test_suite("simd::x86_AVX"))
{
    auto M = 4;
    auto N = 10;
    auto axis = 1;
    auto new_shape = nmtools_array{M,N};
    auto input     = na::reshape(na::arange(M*N),new_shape);
    auto dtype     = nm::None;
    auto initial   = nm::None;
    auto keepdims  = nm::True;
    X86_AVX_TEST(add.reduce,unwrap(input),axis,dtype,initial,keepdims);
}
#endif


TEST_CASE("add.reduce_2d(case4a)" * doctest::test_suite("simd::x86_AVX"))
{
    auto M = 8;
    auto N = 20;
    auto axis = meta::ct_v<0>;
    auto new_shape = nmtools_array{M,N};
    auto input     = na::reshape(na::arange(M*N),new_shape);
    auto dtype     = nm::None;
    auto initial   = nm::None;
    auto keepdims  = nm::True;
    X86_AVX_TEST(add.reduce,unwrap(input),axis,dtype,initial,keepdims);
}

TEST_CASE("add.reduce_2d(case4b)" * doctest::test_suite("simd::x86_AVX"))
{
    auto M = 8;
    auto N = 20;
    auto axis = 0;
    auto new_shape = nmtools_array{M,N};
    auto input     = na::reshape(na::arange(M*N),new_shape);
    auto dtype     = nm::None;
    auto initial   = nm::None;
    auto keepdims  = nm::True;
    X86_AVX_TEST(add.reduce,unwrap(input),axis,dtype,initial,keepdims);
}

TEST_CASE("add.reduce_2d(case4c)" * doctest::test_suite("simd::x86_AVX"))
{
    auto M = 8;
    auto N = 20;
    auto axis = meta::ct_v<1>;
    auto new_shape = nmtools_array{M,N};
    auto input     = na::reshape(na::arange(M*N),new_shape);
    auto dtype     = nm::None;
    auto initial   = nm::None;
    auto keepdims  = nm::True;
    X86_AVX_TEST(add.reduce,unwrap(input),axis,dtype,initial,keepdims);
}

TEST_CASE("add.reduce_2d(case4d)" * doctest::test_suite("simd::x86_AVX"))
{
    auto M = 8;
    auto N = 20;
    auto axis = 1;
    auto new_shape = nmtools_array{M,N};
    auto input     = na::reshape(na::arange(M*N),new_shape);
    auto dtype     = nm::None;
    auto initial   = nm::None;
    auto keepdims  = nm::True;
    X86_AVX_TEST(add.reduce,unwrap(input),axis,dtype,initial,keepdims);
}


TEST_CASE("add.reduce_2d(case5a)" * doctest::test_suite("simd::x86_AVX"))
{
    auto M = 12;
    auto N = 26;
    auto axis = meta::ct_v<0>;
    auto new_shape = nmtools_array{M,N};
    auto input     = na::reshape(na::arange(M*N),new_shape);
    auto dtype     = nm::None;
    auto initial   = nm::None;
    auto keepdims  = nm::True;
    X86_AVX_TEST(add.reduce,unwrap(input),axis,dtype,initial,keepdims);
}

TEST_CASE("add.reduce_2d(case5b)" * doctest::test_suite("simd::x86_AVX"))
{
    auto M = 12;
    auto N = 26;
    auto axis = 0;
    auto new_shape = nmtools_array{M,N};
    auto input     = na::reshape(na::arange(M*N),new_shape);
    auto dtype     = nm::None;
    auto initial   = nm::None;
    auto keepdims  = nm::True;
    X86_AVX_TEST(add.reduce,unwrap(input),axis,dtype,initial,keepdims);
}

TEST_CASE("add.reduce_2d(case5c)" * doctest::test_suite("simd::x86_AVX"))
{
    auto M = 12;
    auto N = 26;
    auto axis = meta::ct_v<1>;
    auto new_shape = nmtools_array{M,N};
    auto input     = na::reshape(na::arange(M*N),new_shape);
    auto dtype     = nm::None;
    auto initial   = nm::None;
    auto keepdims  = nm::True;
    X86_AVX_TEST(add.reduce,unwrap(input),axis,dtype,initial,keepdims);
}

TEST_CASE("add.reduce_2d(case5d)" * doctest::test_suite("simd::x86_AVX"))
{
    auto M = 12;
    auto N = 26;
    auto axis = 1;
    auto new_shape = nmtools_array{M,N};
    auto input     = na::reshape(na::arange(M*N),new_shape);
    auto dtype     = nm::None;
    auto initial   = nm::None;
    auto keepdims  = nm::True;
    X86_AVX_TEST(add.reduce,unwrap(input),axis,dtype,initial,keepdims);
}

TEST_CASE("add.reduce_2d(case6a)" * doctest::test_suite("simd::x86_AVX"))
{
    auto M = 13;
    auto N = 29;
    auto axis = meta::ct_v<0>;
    auto new_shape = nmtools_array{M,N};
    auto input     = na::reshape(na::arange(M*N),new_shape);
    auto dtype     = nm::None;
    auto initial   = nm::None;
    auto keepdims  = nm::True;
    X86_AVX_TEST(add.reduce,unwrap(input),axis,dtype,initial,keepdims);
}

TEST_CASE("add.reduce_2d(case6b)" * doctest::test_suite("simd::x86_AVX"))
{
    auto M = 13;
    auto N = 29;
    auto axis = 0;
    auto new_shape = nmtools_array{M,N};
    auto input     = na::reshape(na::arange(M*N),new_shape);
    auto dtype     = nm::None;
    auto initial   = nm::None;
    auto keepdims  = nm::True;
    X86_AVX_TEST(add.reduce,unwrap(input),axis,dtype,initial,keepdims);
}

TEST_CASE("add.reduce_2d(case6c)" * doctest::test_suite("simd::x86_AVX"))
{
    auto M = 13;
    auto N = 29;
    auto axis = meta::ct_v<1>;
    auto new_shape = nmtools_array{M,N};
    auto input     = na::reshape(na::arange(M*N),new_shape);
    auto dtype     = nm::None;
    auto initial   = nm::None;
    auto keepdims  = nm::True;
    X86_AVX_TEST(add.reduce,unwrap(input),axis,dtype,initial,keepdims);
}

TEST_CASE("add.reduce_2d(case6d)" * doctest::test_suite("simd::x86_AVX"))
{
    auto M = 13;
    auto N = 29;
    auto axis = 1;
    auto new_shape = nmtools_array{M,N};
    auto input     = na::reshape(na::arange(M*N),new_shape);
    auto dtype     = nm::None;
    auto initial   = nm::None;
    auto keepdims  = nm::True;
    X86_AVX_TEST(add.reduce,unwrap(input),axis,dtype,initial,keepdims);
}

TEST_CASE("add.reduce_2d(case7a)" * doctest::test_suite("simd::x86_AVX"))
{
    auto M = 3;
    auto N = 4;
    auto axis = nmtools_tuple{meta::ct_v<0>,meta::ct_v<1>};
    auto new_shape = nmtools_array{M,N};
    auto input     = na::reshape(na::arange(M*N),new_shape);
    auto dtype     = nm::None;
    auto initial   = nm::None;
    auto keepdims  = nm::True;
    X86_AVX_TEST(add.reduce,unwrap(input),axis,dtype,initial,keepdims);
}

TEST_CASE("add.reduce_2d(case7b)" * doctest::test_suite("simd::x86_AVX"))
{
    auto M = 3;
    auto N = 4;
    auto axis = nmtools_array{0,1};
    auto new_shape = nmtools_array{M,N};
    auto input     = na::reshape(na::arange(M*N),new_shape);
    auto dtype     = nm::None;
    auto initial   = nm::None;
    auto keepdims  = nm::True;
    X86_AVX_TEST(add.reduce,unwrap(input),axis,dtype,initial,keepdims);
}

TEST_CASE("add.reduce_2d(case8a)" * doctest::test_suite("simd::x86_AVX"))
{
    auto M = 13;
    auto N = 29;
    auto axis = meta::ct_v<0>;
    auto new_shape = nmtools_array{M,N};
    auto input     = na::reshape(na::arange(M*N),new_shape);
    auto dtype     = nm::None;
    auto initial   = nm::None;
    auto keepdims  = true;
    X86_AVX_TEST(add.reduce,unwrap(input),axis,dtype,initial,keepdims);
}

TEST_CASE("add.reduce_2d(case8b)" * doctest::test_suite("simd::x86_AVX"))
{
    auto M = 13;
    auto N = 29;
    auto axis = 0;
    auto new_shape = nmtools_array{M,N};
    auto input     = na::reshape(na::arange(M*N),new_shape);
    auto dtype     = nm::None;
    auto initial   = nm::None;
    auto keepdims  = true;
    X86_AVX_TEST(add.reduce,unwrap(input),axis,dtype,initial,keepdims);
}

TEST_CASE("add.reduce_2d(case8c)" * doctest::test_suite("simd::x86_AVX"))
{
    auto M = 13;
    auto N = 29;
    auto axis = meta::ct_v<1>;
    auto new_shape = nmtools_array{M,N};
    auto input     = na::reshape(na::arange(M*N),new_shape);
    auto dtype     = nm::None;
    auto initial   = nm::None;
    auto keepdims  = true;
    X86_AVX_TEST(add.reduce,unwrap(input),axis,dtype,initial,keepdims);
}

TEST_CASE("add.reduce_2d(case8d)" * doctest::test_suite("simd::x86_AVX"))
{
    auto M = 13;
    auto N = 29;
    auto axis = 1;
    auto new_shape = nmtools_array{M,N};
    auto input     = na::reshape(na::arange(M*N),new_shape);
    auto dtype     = nm::None;
    auto initial   = nm::None;
    auto keepdims  = true;
    X86_AVX_TEST(add.reduce,unwrap(input),axis,dtype,initial,keepdims);
}

TEST_CASE("add.reduce_2d(case9a)" * doctest::test_suite("simd::x86_AVX"))
{
    auto M = 13;
    auto N = 29;
    auto axis = meta::ct_v<0>;
    auto new_shape = nmtools_array{M,N};
    auto input     = na::reshape(na::arange(M*N),new_shape);
    auto dtype     = nm::None;
    auto initial   = nm::None;
    auto keepdims  = nm::False;
    X86_AVX_TEST(add.reduce,unwrap(input),axis,dtype,initial,keepdims);
}

TEST_CASE("add.reduce_2d(case9b)" * doctest::test_suite("simd::x86_AVX"))
{
    auto M = 13;
    auto N = 29;
    auto axis = 0;
    auto new_shape = nmtools_array{M,N};
    auto input     = na::reshape(na::arange(M*N),new_shape);
    auto dtype     = nm::None;
    auto initial   = nm::None;
    auto keepdims  = nm::False;
    X86_AVX_TEST(add.reduce,unwrap(input),axis,dtype,initial,keepdims);
}

TEST_CASE("add.reduce_2d(case9c)" * doctest::test_suite("simd::x86_AVX"))
{
    auto M = 13;
    auto N = 29;
    auto axis = meta::ct_v<1>;
    auto new_shape = nmtools_array{M,N};
    auto input     = na::reshape(na::arange(M*N),new_shape);
    auto dtype     = nm::None;
    auto initial   = nm::None;
    auto keepdims  = nm::False;
    X86_AVX_TEST(add.reduce,unwrap(input),axis,dtype,initial,keepdims);
}

TEST_CASE("add.reduce_2d(case9d)" * doctest::test_suite("simd::x86_AVX"))
{
    auto M = 13;
    auto N = 29;
    auto axis = 1;
    auto new_shape = nmtools_array{M,N};
    auto input     = na::reshape(na::arange(M*N),new_shape);
    auto dtype     = nm::None;
    auto initial   = nm::None;
    auto keepdims  = nm::False;
    X86_AVX_TEST(add.reduce,unwrap(input),axis,dtype,initial,keepdims);
}


TEST_CASE("add.reduce_2d(case10a)" * doctest::test_suite("simd::x86_AVX"))
{
    auto M = 13;
    auto N = 29;
    auto axis = meta::ct_v<0>;
    auto new_shape = nmtools_array{M,N};
    auto input     = na::reshape(na::arange(M*N),new_shape);
    auto dtype     = nm::None;
    auto initial   = nm::None;
    auto keepdims  = false;
    X86_AVX_TEST(add.reduce,unwrap(input),axis,dtype,initial,keepdims);
}

TEST_CASE("add.reduce_2d(case10b)" * doctest::test_suite("simd::x86_AVX"))
{
    auto M = 13;
    auto N = 29;
    auto axis = 0;
    auto new_shape = nmtools_array{M,N};
    auto input     = na::reshape(na::arange(M*N),new_shape);
    auto dtype     = nm::None;
    auto initial   = nm::None;
    auto keepdims  = false;
    X86_AVX_TEST(add.reduce,unwrap(input),axis,dtype,initial,keepdims);
}

TEST_CASE("add.reduce_2d(case10c)" * doctest::test_suite("simd::x86_AVX"))
{
    auto M = 13;
    auto N = 29;
    auto axis = meta::ct_v<1>;
    auto new_shape = nmtools_array{M,N};
    auto input     = na::reshape(na::arange(M*N),new_shape);
    auto dtype     = nm::None;
    auto initial   = nm::None;
    auto keepdims  = false;
    X86_AVX_TEST(add.reduce,unwrap(input),axis,dtype,initial,keepdims);
}

TEST_CASE("add.reduce_2d(case10d)" * doctest::test_suite("simd::x86_AVX"))
{
    auto M = 13;
    auto N = 29;
    auto axis = 1;
    auto new_shape = nmtools_array{M,N};
    auto input     = na::reshape(na::arange(M*N),new_shape);
    auto dtype     = nm::None;
    auto initial   = nm::None;
    auto keepdims  = false;
    X86_AVX_TEST(add.reduce,unwrap(input),axis,dtype,initial,keepdims);
}

TEST_CASE("add.reduce_2d(case11a)" * doctest::test_suite("simd::x86_AVX"))
{
    auto M = 14;
    auto N = 29;
    auto axis  = 0;
    auto start = -(M*N)/2;
    auto stop  =  (M*N)/2;
    auto new_shape = nmtools_array{M,N};
    auto input     = na::reshape(na::arange(start,stop),new_shape);
    auto dtype     = nm::None;
    auto initial   = nm::None;
    auto keepdims  = false;
    X86_AVX_TEST(add.reduce,unwrap(input),axis,dtype,initial,keepdims);
}

TEST_CASE("add.reduce_2d(case11b)" * doctest::test_suite("simd::x86_AVX"))
{
    auto M = 14;
    auto N = 29;
    auto axis  = 1;
    auto start = -(M*N)/2;
    auto stop  =  (M*N)/2;
    auto new_shape = nmtools_array{M,N};
    auto input     = na::reshape(na::arange(start,stop),new_shape);
    auto dtype     = nm::None;
    auto initial   = nm::None;
    auto keepdims  = false;
    X86_AVX_TEST(add.reduce,unwrap(input),axis,dtype,initial,keepdims);
}

TEST_CASE("add.reduce_2d(case11c)" * doctest::test_suite("simd::x86_AVX"))
{
    auto M = 14;
    auto N = 29;
    auto axis  = 0;
    auto start = -(M*N)/2;
    auto stop  =  (M*N)/2;
    auto new_shape = nmtools_array{M,N};
    auto input     = na::reshape(na::arange(start,stop),new_shape);
    auto dtype     = nm::None;
    auto initial   = nm::None;
    auto keepdims  = true;
    X86_AVX_TEST(add.reduce,unwrap(input),axis,dtype,initial,keepdims);
}

TEST_CASE("add.reduce_2d(case11d)" * doctest::test_suite("simd::x86_AVX"))
{
    auto M = 14;
    auto N = 29;
    auto axis  = 1;
    auto start = -(M*N)/2;
    auto stop  =  (M*N)/2;
    auto new_shape = nmtools_array{M,N};
    auto input     = na::reshape(na::arange(start,stop),new_shape);
    auto dtype     = nm::None;
    auto initial   = nm::None;
    auto keepdims  = true;
    X86_AVX_TEST(add.reduce,unwrap(input),axis,dtype,initial,keepdims);
}

TEST_CASE("add.reduce_2d(case12a)" * doctest::test_suite("simd::x86_AVX"))
{
    auto M = 14;
    auto N = 29;
    auto axis  = 0;
    auto start = -(M*N)/2;
    auto stop  =  (M*N)/2;
    auto new_shape = nmtools_array{M,N};
    auto input     = na::reshape(na::arange(start,stop,nm::int32),new_shape);
    auto dtype     = nm::None;
    auto initial   = nm::None;
    auto keepdims  = false;
    X86_AVX_TEST(add.reduce,unwrap(input),axis,dtype,initial,keepdims);
}

TEST_CASE("add.reduce_2d(case13a)" * doctest::test_suite("simd::x86_AVX"))
{
    auto M = 14;
    auto N = 29;
    auto axis  = 0;
    auto start = -(M*N)/2;
    auto stop  =  (M*N)/2;
    auto new_shape = nmtools_array{M,N};
    auto input     = na::reshape(na::arange(start,stop,nm::int16),new_shape);
    auto dtype     = nm::None;
    auto initial   = nm::None;
    auto keepdims  = false;
    X86_AVX_TEST(add.reduce,unwrap(input),axis,dtype,initial,keepdims);
}

TEST_CASE("add.reduce_2d(case14a)" * doctest::test_suite("simd::x86_AVX"))
{
    auto M = 14;
    auto N = 29;
    auto axis  = 0;
    auto start = -(M*N)/2;
    auto stop  =  (M*N)/2;
    auto new_shape = nmtools_array{M,N};
    auto input     = na::reshape(na::arange(start,stop,nm::int8),new_shape);
    auto dtype     = nm::None;
    auto initial   = nm::None;
    auto keepdims  = false;
    X86_AVX_TEST(add.reduce,unwrap(input),axis,dtype,initial,keepdims);
}

TEST_CASE("add.reduce_2d(case15a)" * doctest::test_suite("simd::x86_AVX"))
{
    auto M = 14;
    auto N = 29;
    auto axis  = 0;
    auto start = -(M*N)/2;
    auto stop  =  (M*N)/2;
    auto new_shape = nmtools_array{M,N};
    auto input     = na::reshape(na::arange(start,stop,nm::int64),new_shape);
    auto dtype     = nm::None;
    auto initial   = nm::None;
    auto keepdims  = false;
    X86_AVX_TEST(add.reduce,unwrap(input),axis,dtype,initial,keepdims);
}

/*********************** multiply ******************************/

TEST_CASE("multiply.reduce_2d(case1a)" * doctest::test_suite("simd::x86_AVX"))
{
    auto M = 3;
    auto N = 4;
    auto axis = meta::ct_v<0>;
    auto new_shape = nmtools_array{M,N};
    auto input     = na::reshape(na::arange(M*N),new_shape);
    auto dtype     = nm::None;
    auto initial   = nm::None;
    auto keepdims  = nm::True;
    X86_AVX_TEST(multiply.reduce,unwrap(input),axis,dtype,initial,keepdims);
}

TEST_CASE("multiply.reduce_2d(case1b)" * doctest::test_suite("simd::x86_AVX"))
{
    auto M = 3;
    auto N = 4;
    auto axis = 0;
    auto new_shape = nmtools_array{M,N};
    auto input     = na::reshape(na::arange(M*N),new_shape);
    auto dtype     = nm::None;
    auto initial   = nm::None;
    auto keepdims  = nm::True;
    X86_AVX_TEST(multiply.reduce,unwrap(input),axis,dtype,initial,keepdims);
}

TEST_CASE("multiply.reduce_2d(case2a)" * doctest::test_suite("simd::x86_AVX"))
{
    auto M = 3;
    auto N = 4;
    auto axis = meta::ct_v<1>;
    auto new_shape = nmtools_array{M,N};
    auto input     = na::reshape(na::arange(M*N),new_shape);
    auto dtype     = nm::None;
    auto initial   = nm::None;
    auto keepdims  = nm::True;
    X86_AVX_TEST(multiply.reduce,unwrap(input),axis,dtype,initial,keepdims);
}

TEST_CASE("multiply.reduce_2d(case2b)" * doctest::test_suite("simd::x86_AVX"))
{
    auto M = 3;
    auto N = 4;
    auto axis = 1;
    auto new_shape = nmtools_array{M,N};
    auto input     = na::reshape(na::arange(M*N),new_shape);
    auto dtype     = nm::None;
    auto initial   = nm::None;
    auto keepdims  = nm::True;
    X86_AVX_TEST(multiply.reduce,unwrap(input),axis,dtype,initial,keepdims);
}

TEST_CASE("multiply.reduce_2d(case3a)" * doctest::test_suite("simd::x86_AVX"))
{
    auto M = 4;
    auto N = 10;
    auto axis = meta::ct_v<0>;
    auto new_shape = nmtools_array{M,N};
    auto input     = na::reshape(na::arange(M*N),new_shape);
    auto dtype     = nm::None;
    auto initial   = nm::None;
    auto keepdims  = nm::True;
    X86_AVX_TEST(multiply.reduce,unwrap(input),axis,dtype,initial,keepdims);
}

TEST_CASE("multiply.reduce_2d(case3b)" * doctest::test_suite("simd::x86_AVX"))
{
    auto M = 4;
    auto N = 10;
    auto axis = 0;
    auto new_shape = nmtools_array{M,N};
    auto input     = na::reshape(na::arange(M*N),new_shape);
    auto dtype     = nm::None;
    auto initial   = nm::None;
    auto keepdims  = nm::True;
    X86_AVX_TEST(multiply.reduce,unwrap(input),axis,dtype,initial,keepdims);
}

#if 1
// TODO; fix precision
TEST_CASE("multiply.reduce_2d(case3c)" * doctest::test_suite("simd::x86_AVX") * doctest::may_fail())
{
    auto M = 4;
    auto N = 10;
    auto axis = meta::ct_v<1>;
    auto new_shape = nmtools_array{M,N};
    auto input     = na::reshape(na::arange(M*N),new_shape);
    auto dtype     = nm::None;
    auto initial   = nm::None;
    auto keepdims  = nm::True;
    X86_AVX_TEST(multiply.reduce,unwrap(input),axis,dtype,initial,keepdims);
}

// TODO: fix precision
TEST_CASE("multiply.reduce_2d(case3d)" * doctest::test_suite("simd::x86_AVX") * doctest::may_fail())
{
    auto M = 4;
    auto N = 10;
    auto axis = 1;
    auto new_shape = nmtools_array{M,N};
    auto input     = na::reshape(na::arange(M*N),new_shape);
    auto dtype     = nm::None;
    auto initial   = nm::None;
    auto keepdims  = nm::True;
    X86_AVX_TEST(multiply.reduce,unwrap(input),axis,dtype,initial,keepdims);
}
#endif


TEST_CASE("multiply.reduce_2d(case4a)" * doctest::test_suite("simd::x86_AVX"))
{
    auto M = 8;
    auto N = 20;
    auto axis = meta::ct_v<0>;
    auto new_shape = nmtools_array{M,N};
    auto input     = na::reshape(na::arange(M*N),new_shape);
    auto dtype     = nm::None;
    auto initial   = nm::None;
    auto keepdims  = nm::True;
    X86_AVX_TEST(multiply.reduce,unwrap(input),axis,dtype,initial,keepdims);
}

TEST_CASE("multiply.reduce_2d(case4b)" * doctest::test_suite("simd::x86_AVX"))
{
    auto M = 8;
    auto N = 20;
    auto axis = 0;
    auto new_shape = nmtools_array{M,N};
    auto input     = na::reshape(na::arange(M*N),new_shape);
    auto dtype     = nm::None;
    auto initial   = nm::None;
    auto keepdims  = nm::True;
    X86_AVX_TEST(multiply.reduce,unwrap(input),axis,dtype,initial,keepdims);
}

// TODO: fix precision
TEST_CASE("multiply.reduce_2d(case4c)" * doctest::test_suite("simd::x86_AVX") * doctest::may_fail())
{
    auto M = 8;
    auto N = 20;
    auto axis = meta::ct_v<1>;
    auto new_shape = nmtools_array{M,N};
    auto input     = na::reshape(na::arange(M*N),new_shape);
    auto dtype     = nm::None;
    auto initial   = nm::None;
    auto keepdims  = nm::True;
    X86_AVX_TEST(multiply.reduce,unwrap(input),axis,dtype,initial,keepdims);
}

// TODO: fix precision
TEST_CASE("multiply.reduce_2d(case4d)" * doctest::test_suite("simd::x86_AVX") * doctest::may_fail())
{
    auto M = 8;
    auto N = 20;
    auto axis = 1;
    auto new_shape = nmtools_array{M,N};
    auto input     = na::reshape(na::arange(M*N),new_shape);
    auto dtype     = nm::None;
    auto initial   = nm::None;
    auto keepdims  = nm::True;
    X86_AVX_TEST(multiply.reduce,unwrap(input),axis,dtype,initial,keepdims);
}


TEST_CASE("multiply.reduce_2d(case5a)" * doctest::test_suite("simd::x86_AVX"))
{
    auto M = 12;
    auto N = 26;
    auto axis = meta::ct_v<0>;
    auto new_shape = nmtools_array{M,N};
    auto input     = na::reshape(na::arange(M*N),new_shape);
    auto dtype     = nm::None;
    auto initial   = nm::None;
    auto keepdims  = nm::True;
    X86_AVX_TEST(multiply.reduce,unwrap(input),axis,dtype,initial,keepdims);
}

TEST_CASE("multiply.reduce_2d(case5b)" * doctest::test_suite("simd::x86_AVX"))
{
    auto M = 12;
    auto N = 26;
    auto axis = 0;
    auto new_shape = nmtools_array{M,N};
    auto input     = na::reshape(na::arange(M*N),new_shape);
    auto dtype     = nm::None;
    auto initial   = nm::None;
    auto keepdims  = nm::True;
    X86_AVX_TEST(multiply.reduce,unwrap(input),axis,dtype,initial,keepdims);
}

// TODO: fix precision
TEST_CASE("multiply.reduce_2d(case5c)" * doctest::test_suite("simd::x86_AVX") * doctest::may_fail())
{
    auto M = 12;
    auto N = 26;
    auto axis = meta::ct_v<1>;
    auto new_shape = nmtools_array{M,N};
    auto input     = na::reshape(na::arange(M*N),new_shape);
    auto dtype     = nm::None;
    auto initial   = nm::None;
    auto keepdims  = nm::True;
    X86_AVX_TEST(multiply.reduce,unwrap(input),axis,dtype,initial,keepdims);
}

// TODO: fix precision
TEST_CASE("multiply.reduce_2d(case5d)" * doctest::test_suite("simd::x86_AVX") * doctest::may_fail())
{
    auto M = 12;
    auto N = 26;
    auto axis = 1;
    auto new_shape = nmtools_array{M,N};
    auto input     = na::reshape(na::arange(M*N),new_shape);
    auto dtype     = nm::None;
    auto initial   = nm::None;
    auto keepdims  = nm::True;
    X86_AVX_TEST(multiply.reduce,unwrap(input),axis,dtype,initial,keepdims);
}

TEST_CASE("multiply.reduce_2d(case6a)" * doctest::test_suite("simd::x86_AVX"))
{
    auto M = 13;
    auto N = 29;
    auto axis = meta::ct_v<0>;
    auto new_shape = nmtools_array{M,N};
    auto input     = na::reshape(na::arange(M*N),new_shape);
    auto dtype     = nm::None;
    auto initial   = nm::None;
    auto keepdims  = nm::True;
    X86_AVX_TEST(multiply.reduce,unwrap(input),axis,dtype,initial,keepdims);
}

TEST_CASE("multiply.reduce_2d(case6b)" * doctest::test_suite("simd::x86_AVX"))
{
    auto M = 13;
    auto N = 29;
    auto axis = 0;
    auto new_shape = nmtools_array{M,N};
    auto input     = na::reshape(na::arange(M*N),new_shape);
    auto dtype     = nm::None;
    auto initial   = nm::None;
    auto keepdims  = nm::True;
    X86_AVX_TEST(multiply.reduce,unwrap(input),axis,dtype,initial,keepdims);
}

// TODO: fix precision
TEST_CASE("multiply.reduce_2d(case6c)" * doctest::test_suite("simd::x86_AVX") * doctest::may_fail())
{
    auto M = 13;
    auto N = 29;
    auto axis = meta::ct_v<1>;
    auto new_shape = nmtools_array{M,N};
    auto input     = na::reshape(na::arange(M*N),new_shape);
    auto dtype     = nm::None;
    auto initial   = nm::None;
    auto keepdims  = nm::True;
    X86_AVX_TEST(multiply.reduce,unwrap(input),axis,dtype,initial,keepdims);
}

// TODO: fix precision
TEST_CASE("multiply.reduce_2d(case6d)" * doctest::test_suite("simd::x86_AVX") * doctest::may_fail())
{
    auto M = 13;
    auto N = 29;
    auto axis = 1;
    auto new_shape = nmtools_array{M,N};
    auto input     = na::reshape(na::arange(M*N),new_shape);
    auto dtype     = nm::None;
    auto initial   = nm::None;
    auto keepdims  = nm::True;
    X86_AVX_TEST(multiply.reduce,unwrap(input),axis,dtype,initial,keepdims);
}

TEST_CASE("multiply.reduce_2d(case7a)" * doctest::test_suite("simd::x86_AVX"))
{
    auto M = 3;
    auto N = 4;
    auto axis = nmtools_tuple{meta::ct_v<0>,meta::ct_v<1>};
    auto new_shape = nmtools_array{M,N};
    auto input     = na::reshape(na::arange(M*N),new_shape);
    auto dtype     = nm::None;
    auto initial   = nm::None;
    auto keepdims  = nm::True;
    X86_AVX_TEST(multiply.reduce,unwrap(input),axis,dtype,initial,keepdims);
}

TEST_CASE("multiply.reduce_2d(case7b)" * doctest::test_suite("simd::x86_AVX"))
{
    auto M = 3;
    auto N = 4;
    auto axis = nmtools_array{0,1};
    auto new_shape = nmtools_array{M,N};
    auto input     = na::reshape(na::arange(M*N),new_shape);
    auto dtype     = nm::None;
    auto initial   = nm::None;
    auto keepdims  = nm::True;
    X86_AVX_TEST(multiply.reduce,unwrap(input),axis,dtype,initial,keepdims);
}

TEST_CASE("multiply.reduce_2d(case8a)" * doctest::test_suite("simd::x86_AVX"))
{
    auto M = 13;
    auto N = 29;
    auto axis = meta::ct_v<0>;
    auto new_shape = nmtools_array{M,N};
    auto input     = na::reshape(na::arange(M*N),new_shape);
    auto dtype     = nm::None;
    auto initial   = nm::None;
    auto keepdims  = true;
    X86_AVX_TEST(multiply.reduce,unwrap(input),axis,dtype,initial,keepdims);
}

TEST_CASE("multiply.reduce_2d(case8b)" * doctest::test_suite("simd::x86_AVX"))
{
    auto M = 13;
    auto N = 29;
    auto axis = 0;
    auto new_shape = nmtools_array{M,N};
    auto input     = na::reshape(na::arange(M*N),new_shape);
    auto dtype     = nm::None;
    auto initial   = nm::None;
    auto keepdims  = true;
    X86_AVX_TEST(multiply.reduce,unwrap(input),axis,dtype,initial,keepdims);
}

// TODO: fix precision
TEST_CASE("multiply.reduce_2d(case8c)" * doctest::test_suite("simd::x86_AVX") * doctest::may_fail())
{
    auto M = 13;
    auto N = 29;
    auto axis = meta::ct_v<1>;
    auto new_shape = nmtools_array{M,N};
    auto input     = na::reshape(na::arange(M*N),new_shape);
    auto dtype     = nm::None;
    auto initial   = nm::None;
    auto keepdims  = true;
    X86_AVX_TEST(multiply.reduce,unwrap(input),axis,dtype,initial,keepdims);
}

// TODO: fix precision
TEST_CASE("multiply.reduce_2d(case8d)" * doctest::test_suite("simd::x86_AVX") * doctest::may_fail())
{
    auto M = 13;
    auto N = 29;
    auto axis = 1;
    auto new_shape = nmtools_array{M,N};
    auto input     = na::reshape(na::arange(M*N),new_shape);
    auto dtype     = nm::None;
    auto initial   = nm::None;
    auto keepdims  = true;
    X86_AVX_TEST(multiply.reduce,unwrap(input),axis,dtype,initial,keepdims);
}

TEST_CASE("multiply.reduce_2d(case9a)" * doctest::test_suite("simd::x86_AVX"))
{
    auto M = 13;
    auto N = 29;
    auto axis = meta::ct_v<0>;
    auto new_shape = nmtools_array{M,N};
    auto input     = na::reshape(na::arange(M*N),new_shape);
    auto dtype     = nm::None;
    auto initial   = nm::None;
    auto keepdims  = nm::False;
    X86_AVX_TEST(multiply.reduce,unwrap(input),axis,dtype,initial,keepdims);
}

TEST_CASE("multiply.reduce_2d(case9b)" * doctest::test_suite("simd::x86_AVX"))
{
    auto M = 13;
    auto N = 29;
    auto axis = 0;
    auto new_shape = nmtools_array{M,N};
    auto input     = na::reshape(na::arange(M*N),new_shape);
    auto dtype     = nm::None;
    auto initial   = nm::None;
    auto keepdims  = nm::False;
    X86_AVX_TEST(multiply.reduce,unwrap(input),axis,dtype,initial,keepdims);
}

// TODO: fix precision
TEST_CASE("multiply.reduce_2d(case9c)" * doctest::test_suite("simd::x86_AVX") * doctest::may_fail())
{
    auto M = 13;
    auto N = 29;
    auto axis = meta::ct_v<1>;
    auto new_shape = nmtools_array{M,N};
    auto input     = na::reshape(na::arange(M*N),new_shape);
    auto dtype     = nm::None;
    auto initial   = nm::None;
    auto keepdims  = nm::False;
    X86_AVX_TEST(multiply.reduce,unwrap(input),axis,dtype,initial,keepdims);
}

// TODO: fix precision
TEST_CASE("multiply.reduce_2d(case9d)" * doctest::test_suite("simd::x86_AVX") * doctest::may_fail())
{
    auto M = 13;
    auto N = 29;
    auto axis = 1;
    auto new_shape = nmtools_array{M,N};
    auto input     = na::reshape(na::arange(M*N),new_shape);
    auto dtype     = nm::None;
    auto initial   = nm::None;
    auto keepdims  = nm::False;
    X86_AVX_TEST(multiply.reduce,unwrap(input),axis,dtype,initial,keepdims);
}


TEST_CASE("multiply.reduce_2d(case10a)" * doctest::test_suite("simd::x86_AVX"))
{
    auto M = 13;
    auto N = 29;
    auto axis = meta::ct_v<0>;
    auto new_shape = nmtools_array{M,N};
    auto input     = na::reshape(na::arange(M*N),new_shape);
    auto dtype     = nm::None;
    auto initial   = nm::None;
    auto keepdims  = false;
    X86_AVX_TEST(multiply.reduce,unwrap(input),axis,dtype,initial,keepdims);
}

TEST_CASE("multiply.reduce_2d(case10b)" * doctest::test_suite("simd::x86_AVX"))
{
    auto M = 13;
    auto N = 29;
    auto axis = 0;
    auto new_shape = nmtools_array{M,N};
    auto input     = na::reshape(na::arange(M*N),new_shape);
    auto dtype     = nm::None;
    auto initial   = nm::None;
    auto keepdims  = false;
    X86_AVX_TEST(multiply.reduce,unwrap(input),axis,dtype,initial,keepdims);
}

// TODO: fix precision
TEST_CASE("multiply.reduce_2d(case10c)" * doctest::test_suite("simd::x86_AVX") * doctest::may_fail())
{
    auto M = 13;
    auto N = 29;
    auto axis = meta::ct_v<1>;
    auto new_shape = nmtools_array{M,N};
    auto input     = na::reshape(na::arange(M*N),new_shape);
    auto dtype     = nm::None;
    auto initial   = nm::None;
    auto keepdims  = false;
    X86_AVX_TEST(multiply.reduce,unwrap(input),axis,dtype,initial,keepdims);
}

// TODO: fix precision
TEST_CASE("multiply.reduce_2d(case10d)" * doctest::test_suite("simd::x86_AVX") * doctest::may_fail())
{
    auto M = 13;
    auto N = 29;
    auto axis = 1;
    auto new_shape = nmtools_array{M,N};
    auto input     = na::reshape(na::arange(M*N),new_shape);
    auto dtype     = nm::None;
    auto initial   = nm::None;
    auto keepdims  = false;
    X86_AVX_TEST(multiply.reduce,unwrap(input),axis,dtype,initial,keepdims);
}

TEST_CASE("multiply.reduce_2d(case11a)" * doctest::test_suite("simd::x86_AVX"))
{
    auto M = 14;
    auto N = 29;
    auto axis  = 0;
    auto start = -(M*N)/2;
    auto stop  =  (M*N)/2;
    auto new_shape = nmtools_array{M,N};
    auto input     = na::reshape(na::arange(start,stop),new_shape);
    auto dtype     = nm::None;
    auto initial   = nm::None;
    auto keepdims  = false;
    X86_AVX_TEST(multiply.reduce,unwrap(input),axis,dtype,initial,keepdims);
}

// TODO: fix precision
TEST_CASE("multiply.reduce_2d(case11b)" * doctest::test_suite("simd::x86_AVX") * doctest::may_fail())
{
    auto M = 14;
    auto N = 29;
    auto axis  = 1;
    auto start = -(M*N)/2;
    auto stop  =  (M*N)/2;
    auto new_shape = nmtools_array{M,N};
    auto input     = na::reshape(na::arange(start,stop),new_shape);
    auto dtype     = nm::None;
    auto initial   = nm::None;
    auto keepdims  = false;
    X86_AVX_TEST(multiply.reduce,unwrap(input),axis,dtype,initial,keepdims);
}

TEST_CASE("multiply.reduce_2d(case11c)" * doctest::test_suite("simd::x86_AVX"))
{
    auto M = 14;
    auto N = 29;
    auto axis  = 0;
    auto start = -(M*N)/2;
    auto stop  =  (M*N)/2;
    auto new_shape = nmtools_array{M,N};
    auto input     = na::reshape(na::arange(start,stop),new_shape);
    auto dtype     = nm::None;
    auto initial   = nm::None;
    auto keepdims  = true;
    X86_AVX_TEST(multiply.reduce,unwrap(input),axis,dtype,initial,keepdims);
}

// TODO: fix precision
TEST_CASE("multiply.reduce_2d(case11d)" * doctest::test_suite("simd::x86_AVX") * doctest::may_fail())
{
    auto M = 14;
    auto N = 29;
    auto axis  = 1;
    auto start = -(M*N)/2;
    auto stop  =  (M*N)/2;
    auto new_shape = nmtools_array{M,N};
    auto input     = na::reshape(na::arange(start,stop),new_shape);
    auto dtype     = nm::None;
    auto initial   = nm::None;
    auto keepdims  = true;
    X86_AVX_TEST(multiply.reduce,unwrap(input),axis,dtype,initial,keepdims);
}

TEST_CASE("multiply.reduce_2d(case12a)" * doctest::test_suite("simd::x86_AVX"))
{
    auto M = 14;
    auto N = 29;
    auto axis  = 0;
    auto start = -(M*N)/2;
    auto stop  =  (M*N)/2;
    auto new_shape = nmtools_array{M,N};
    auto input     = na::reshape(na::arange(start,stop,nm::int32),new_shape);
    auto dtype     = nm::None;
    auto initial   = nm::None;
    auto keepdims  = false;
    X86_AVX_TEST(multiply.reduce,unwrap(input),axis,dtype,initial,keepdims);
}

TEST_CASE("multiply.reduce_2d(case12b)" * doctest::test_suite("simd::x86_AVX"))
{
    auto M = 14;
    auto N = 29;
    auto axis  = 1;
    auto start = -(M*N)/2;
    auto stop  =  (M*N)/2;
    auto new_shape = nmtools_array{M,N};
    auto input     = na::reshape(na::arange(start,stop,nm::int32),new_shape);
    auto dtype     = nm::None;
    auto initial   = nm::None;
    auto keepdims  = false;
    X86_AVX_TEST(multiply.reduce,unwrap(input),axis,dtype,initial,keepdims);
}

TEST_CASE("multiply.reduce_2d(case13a)" * doctest::test_suite("simd::x86_AVX"))
{
    auto M = 14;
    auto N = 29;
    auto axis  = 0;
    auto start = -(M*N)/2;
    auto stop  =  (M*N)/2;
    auto new_shape = nmtools_array{M,N};
    auto input     = na::reshape(na::arange(start,stop,nm::int16),new_shape);
    auto dtype     = nm::None;
    auto initial   = nm::None;
    auto keepdims  = false;
    X86_AVX_TEST(multiply.reduce,unwrap(input),axis,dtype,initial,keepdims);
}

TEST_CASE("multiply.reduce_2d(case13a)" * doctest::test_suite("simd::x86_AVX"))
{
    auto M = 14;
    auto N = 29;
    auto axis  = 1;
    auto start = -(M*N)/2;
    auto stop  =  (M*N)/2;
    auto new_shape = nmtools_array{M,N};
    auto input     = na::reshape(na::arange(start,stop,nm::int16),new_shape);
    auto dtype     = nm::None;
    auto initial   = nm::None;
    auto keepdims  = false;
    X86_AVX_TEST(multiply.reduce,unwrap(input),axis,dtype,initial,keepdims);
}

#if 0
TEST_CASE("multiply.reduce_2d(case14a)" * doctest::test_suite("simd::x86_AVX"))
{
    auto M = 14;
    auto N = 29;
    auto axis  = 0;
    auto start = -(M*N)/2;
    auto stop  =  (M*N)/2;
    auto new_shape = nmtools_array{M,N};
    auto input     = na::reshape(na::arange(start,stop,nm::int8),new_shape);
    auto dtype     = nm::None;
    auto initial   = nm::None;
    auto keepdims  = false;
    X86_AVX_TEST(multiply.reduce,unwrap(input),axis,dtype,initial,keepdims);
}

TEST_CASE("multiply.reduce_2d(case15a)" * doctest::test_suite("simd::x86_AVX"))
{
    auto M = 14;
    auto N = 29;
    auto axis  = 0;
    auto start = -(M*N)/2;
    auto stop  =  (M*N)/2;
    auto new_shape = nmtools_array{M,N};
    auto input     = na::reshape(na::arange(start,stop,nm::int64),new_shape);
    auto dtype     = nm::None;
    auto initial   = nm::None;
    auto keepdims  = false;
    X86_AVX_TEST(multiply.reduce,unwrap(input),axis,dtype,initial,keepdims);
}
#endif