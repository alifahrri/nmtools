#include "nmtools/evaluator/sycl.hpp"
#include "nmtools/array/matmul.hpp"
#include "nmtools/array/copy.hpp"
#include "nmtools/array/reshape.hpp"
#include "nmtools/array/arange.hpp"
#include "nmtools/dtypes.hpp"
#include "nmtools/ndarray.hpp"
#include "nmtools/testing/doctest.hpp"

namespace nm = nmtools;
namespace na = nmtools;
namespace meta = nm::meta;
namespace view = nm::view;

// TODO: fix to accept maybe type
using nmtools::unwrap;

#define SYCL_TEST(fn,...) \
{ \
    auto ctx = na::sycl::default_context(); \
    auto expect = na::matmul(__VA_ARGS__); \
    auto view   = view::matmulv2(__VA_ARGS__); \
    auto result = ctx->eval(view); \
    NMTOOLS_ASSERT_EQUAL( nm::shape(result), nm::shape(expect) ); \
    NMTOOLS_ASSERT_CLOSE( result, expect ); \
}

// TODO: fix opencl kernel compilation on pocl
TEST_CASE("matmul(case1)" * doctest::test_suite("array::matmul"))
{
    auto M = 4;
    auto N = 4;
    auto K = 4;
    auto lhs_shape = nmtools_array{M,K};
    auto rhs_shape = nmtools_array{K,N};
    auto lhs = unwrap(na::reshape(na::arange(M*K),lhs_shape));
    
    auto rhs = unwrap(na::reshape(na::arange(K*N),rhs_shape));
    SYCL_TEST(matmul,lhs,rhs);
}

// TODO: fix opencl kernel compilation on pocl
TEST_CASE("matmul(case1b)" * doctest::test_suite("array::matmul"))
{
    auto M = 4;
    auto N = 4;
    auto K = 5;
    auto lhs_shape = nmtools_array{M,K};
    auto rhs_shape = nmtools_array{K,N};
    auto lhs = unwrap(na::reshape(na::arange(M*K),lhs_shape));

    auto rhs = unwrap(na::reshape(na::arange(K*N),rhs_shape));
    SYCL_TEST(matmul,lhs,rhs);
}

// TODO: fix opencl kernel compilation on pocl
TEST_CASE("matmul(case1b)" * doctest::test_suite("array::matmul"))
{
    auto M = 2;
    auto N = 2;
    auto K = 5;
    auto lhs_shape = nmtools_array{M,K};
    auto rhs_shape = nmtools_array{K,N};
    auto lhs = unwrap(na::reshape(na::arange(M*K),lhs_shape));
    
    auto rhs = unwrap(na::reshape(na::arange(K*N),rhs_shape));
    SYCL_TEST(matmul,lhs,rhs);
}

// TODO: fix opencl kernel compilation on pocl
TEST_CASE("matmul(case1c)" * doctest::test_suite("array::matmul"))
{
    auto M = 4;
    auto N = 4;
    auto K = 6;
    auto lhs_shape = nmtools_array{M,K};
    auto rhs_shape = nmtools_array{K,N};
    auto lhs = unwrap(na::reshape(na::arange(M*K),lhs_shape));
    
    auto rhs = unwrap(na::reshape(na::arange(K*N),rhs_shape));
    SYCL_TEST(matmul,lhs,rhs);
}

// TODO: fix opencl kernel compilation on pocl
TEST_CASE("matmul(case1d)" * doctest::test_suite("array::matmul"))
{
    auto M = 4;
    auto N = 4;
    auto K = 7;
    auto lhs_shape = nmtools_array{M,K};
    auto rhs_shape = nmtools_array{K,N};
    auto lhs = unwrap(na::reshape(na::arange(M*K),lhs_shape));
    
    auto rhs = unwrap(na::reshape(na::arange(K*N),rhs_shape));
    SYCL_TEST(matmul,lhs,rhs);
}

// TODO: fix opencl kernel compilation on pocl
TEST_CASE("matmul(case1e)" * doctest::test_suite("array::matmul"))
{
    auto M = 4;
    auto N = 4;
    auto K = 8;
    auto lhs_shape = nmtools_array{M,K};
    auto rhs_shape = nmtools_array{K,N};
    auto lhs = unwrap(na::reshape(na::arange(M*K),lhs_shape));
    
    auto rhs = unwrap(na::reshape(na::arange(K*N),rhs_shape));
    SYCL_TEST(matmul,lhs,rhs);
}

// TODO: fix opencl kernel compilation on pocl
TEST_CASE("matmul(case2)" * doctest::test_suite("array::matmul"))
{
    auto M = 16;
    auto N = 16;
    auto K = 5;
    auto lhs_shape = nmtools_array{M,K};
    auto rhs_shape = nmtools_array{K,N};
    auto lhs = unwrap(na::reshape(na::arange(M*K),lhs_shape));
    
    auto rhs = unwrap(na::reshape(na::arange(K*N),rhs_shape));
    SYCL_TEST(matmul,lhs,rhs);
}

// TODO: fix opencl kernel compilation on pocl
TEST_CASE("matmul(case3)" * doctest::test_suite("array::matmul"))
{
    auto M = 16;
    auto N = 16;
    auto K = 7;
    auto lhs_shape = nmtools_array{M,K};
    auto rhs_shape = nmtools_array{K,N};
    auto lhs = unwrap(na::reshape(na::arange(M*K),lhs_shape));
    
    auto rhs = unwrap(na::reshape(na::arange(K*N),rhs_shape));
    SYCL_TEST(matmul,lhs,rhs);
}

// TODO: fix opencl kernel compilation on pocl
TEST_CASE("matmul(case4)" * doctest::test_suite("array::matmul"))
{
    auto M = 16;
    auto N = 16;
    auto K = 8;
    auto lhs_shape = nmtools_array{M,K};
    auto rhs_shape = nmtools_array{K,N};
    auto lhs = unwrap(na::reshape(na::arange(M*K),lhs_shape));
   
    auto rhs = unwrap(na::reshape(na::arange(K*N),rhs_shape));
    SYCL_TEST(matmul,lhs,rhs);
}

// TODO: fix opencl kernel compilation on pocl
TEST_CASE("matmul(case5)" * doctest::test_suite("array::matmul"))
{
    auto M = 16;
    auto N = 16;
    auto K = 9;
    auto lhs_shape = nmtools_array{M,K};
    auto rhs_shape = nmtools_array{K,N};
    auto lhs = unwrap(na::reshape(na::arange(M*K),lhs_shape));
    
    auto rhs = unwrap(na::reshape(na::arange(K*N),rhs_shape));
    SYCL_TEST(matmul,lhs,rhs);
}

// TODO: fix opencl kernel compilation on pocl
TEST_CASE("matmul(case6)" * doctest::test_suite("array::matmul"))
{
    auto M = 16;
    auto N = 16;
    auto K = 10;
    auto lhs_shape = nmtools_array{M,K};
    auto rhs_shape = nmtools_array{K,N};
    auto lhs = unwrap(na::reshape(na::arange(M*K),lhs_shape));

    auto rhs = unwrap(na::reshape(na::arange(K*N),rhs_shape));
    SYCL_TEST(matmul,lhs,rhs);
}

// TODO: fix opencl kernel compilation on pocl
TEST_CASE("matmul(case7)" * doctest::test_suite("array::matmul"))
{
    auto M = 16;
    auto N = 16;
    auto K = 11;
    auto lhs_shape = nmtools_array{M,K};
    auto rhs_shape = nmtools_array{K,N};
    auto lhs = unwrap(na::reshape(na::arange(M*K),lhs_shape));
    
    auto rhs = unwrap(na::reshape(na::arange(K*N),rhs_shape));
    SYCL_TEST(matmul,lhs,rhs);
}

// TODO: fix opencl kernel compilation on pocl
TEST_CASE("matmul(case8)" * doctest::test_suite("array::matmul"))
{
    auto M = 16;
    auto N = 16;
    auto K = 12;
    auto lhs_shape = nmtools_array{M,K};
    auto rhs_shape = nmtools_array{K,N};
    auto lhs = unwrap(na::reshape(na::arange(M*K),lhs_shape));

    auto rhs = unwrap(na::reshape(na::arange(K*N),rhs_shape));
    SYCL_TEST(matmul,lhs,rhs);
}

// TODO: fix opencl kernel compilation on pocl
TEST_CASE("matmul(case9)" * doctest::test_suite("array::matmul"))
{
    auto M = 16;
    auto N = 16;
    auto K = 13;
    auto lhs_shape = nmtools_array{M,K};
    auto rhs_shape = nmtools_array{K,N};
    auto lhs = unwrap(na::reshape(na::arange(M*K),lhs_shape));

    auto rhs = unwrap(na::reshape(na::arange(K*N),rhs_shape));
    SYCL_TEST(matmul,lhs,rhs);
}

// TODO: fix opencl kernel compilation on pocl
TEST_CASE("matmul(case10)" * doctest::test_suite("array::matmul"))
{
    auto M = 16;
    auto N = 19;
    auto K = 12;
    auto lhs_shape = nmtools_array{M,K};
    auto rhs_shape = nmtools_array{K,N};
    auto lhs = unwrap(na::reshape(na::arange(M*K),lhs_shape));

    auto rhs = unwrap(na::reshape(na::arange(K*N),rhs_shape));
    SYCL_TEST(matmul,lhs,rhs);
}

// TODO: fix opencl kernel compilation on pocl
TEST_CASE("matmul(case11)" * doctest::test_suite("array::matmul"))
{
    auto M = 16;
    auto N = 19;
    auto K = 13;
    auto lhs_shape = nmtools_array{M,K};
    auto rhs_shape = nmtools_array{K,N};
    auto lhs = unwrap(na::reshape(na::arange(M*K),lhs_shape));

    auto rhs = unwrap(na::reshape(na::arange(K*N),rhs_shape));
    SYCL_TEST(matmul,lhs,rhs);
}

// TODO: fix opencl kernel compilation on pocl
TEST_CASE("matmul(case12)" * doctest::test_suite("array::matmul"))
{
    auto M = 16;
    auto N = 19;
    auto K = 14;
    auto lhs_shape = nmtools_array{M,K};
    auto rhs_shape = nmtools_array{K,N};
    auto lhs = unwrap(na::reshape(na::arange(M*K),lhs_shape));

    auto rhs = unwrap(na::reshape(na::arange(K*N),rhs_shape));
    SYCL_TEST(matmul,lhs,rhs);
}

// TODO: fix opencl kernel compilation on pocl
TEST_CASE("matmul(case13)" * doctest::test_suite("array::matmul"))
{
    auto M = 16;
    auto N = 19;
    auto K = 15;
    auto lhs_shape = nmtools_array{M,K};
    auto rhs_shape = nmtools_array{K,N};
    auto lhs = unwrap(na::reshape(na::arange(M*K),lhs_shape));

    auto rhs = unwrap(na::reshape(na::arange(K*N),rhs_shape));
    SYCL_TEST(matmul,lhs,rhs);
}

// TODO: fix opencl kernel compilation on pocl
TEST_CASE("matmul(case14)" * doctest::test_suite("array::matmul"))
{
    auto M = 1;
    auto N = 19;
    auto K = 12;
    auto lhs_shape = nmtools_array{M,K};
    auto rhs_shape = nmtools_array{K,N};
    auto lhs = unwrap(na::reshape(na::arange(M*K),lhs_shape));

    auto rhs = unwrap(na::reshape(na::arange(K*N),rhs_shape));
    SYCL_TEST(matmul,lhs,rhs);
}

// TODO: fix opencl kernel compilation on pocl
TEST_CASE("matmul(case15)" * doctest::test_suite("array::matmul"))
{
    auto M = 16;
    auto N = 1;
    auto K = 13;
    auto lhs_shape = nmtools_array{M,K};
    auto rhs_shape = nmtools_array{K,N};
    auto lhs = unwrap(na::reshape(na::arange(M*K),lhs_shape));

    auto rhs = unwrap(na::reshape(na::arange(K*N),rhs_shape));
    SYCL_TEST(matmul,lhs,rhs);
}

////////////////////////////////////////////////////////////////////////////

// TODO: fix opencl kernel compilation on pocl
TEST_CASE("matmul(case1)" * doctest::test_suite("array::matmul"))
{
    auto dtype = nm::float64;
    auto M = 4;
    auto N = 4;
    auto K = 4;
    auto lhs_shape = nmtools_array{M,K};
    auto rhs_shape = nmtools_array{K,N};
    auto lhs = unwrap(na::reshape(na::arange(M*K,dtype),lhs_shape));
    
    auto rhs = unwrap(na::reshape(na::arange(K*N,dtype),rhs_shape));
    SYCL_TEST(matmul,lhs,rhs);
}

// TODO: fix opencl kernel compilation on pocl
TEST_CASE("matmul(case1b)" * doctest::test_suite("array::matmul"))
{
    auto dtype = nm::float64;
    auto M = 4;
    auto N = 4;
    auto K = 5;
    auto lhs_shape = nmtools_array{M,K};
    auto rhs_shape = nmtools_array{K,N};
    auto lhs = unwrap(na::reshape(na::arange(M*K,dtype),lhs_shape));

    auto rhs = unwrap(na::reshape(na::arange(K*N,dtype),rhs_shape));
    SYCL_TEST(matmul,lhs,rhs);
}

// TODO: fix opencl kernel compilation on pocl
TEST_CASE("matmul(case1b)" * doctest::test_suite("array::matmul"))
{
    auto dtype = nm::float64;
    auto M = 2;
    auto N = 2;
    auto K = 5;
    auto lhs_shape = nmtools_array{M,K};
    auto rhs_shape = nmtools_array{K,N};
    auto lhs = unwrap(na::reshape(na::arange(M*K,dtype),lhs_shape));
    
    auto rhs = unwrap(na::reshape(na::arange(K*N,dtype),rhs_shape));
    SYCL_TEST(matmul,lhs,rhs);
}

// TODO: fix opencl kernel compilation on pocl
TEST_CASE("matmul(case1c)" * doctest::test_suite("array::matmul"))
{
    auto dtype = nm::float64;
    auto M = 4;
    auto N = 4;
    auto K = 6;
    auto lhs_shape = nmtools_array{M,K};
    auto rhs_shape = nmtools_array{K,N};
    auto lhs = unwrap(na::reshape(na::arange(M*K,dtype),lhs_shape));
    
    auto rhs = unwrap(na::reshape(na::arange(K*N,dtype),rhs_shape));
    SYCL_TEST(matmul,lhs,rhs);
}

// TODO: fix opencl kernel compilation on pocl
TEST_CASE("matmul(case1d)" * doctest::test_suite("array::matmul"))
{
    auto dtype = nm::float64;
    auto M = 4;
    auto N = 4;
    auto K = 7;
    auto lhs_shape = nmtools_array{M,K};
    auto rhs_shape = nmtools_array{K,N};
    auto lhs = unwrap(na::reshape(na::arange(M*K,dtype),lhs_shape));
    
    auto rhs = unwrap(na::reshape(na::arange(K*N,dtype),rhs_shape));
    SYCL_TEST(matmul,lhs,rhs);
}

// TODO: fix opencl kernel compilation on pocl
TEST_CASE("matmul(case1e)" * doctest::test_suite("array::matmul"))
{
    auto dtype = nm::float64;
    auto M = 4;
    auto N = 4;
    auto K = 8;
    auto lhs_shape = nmtools_array{M,K};
    auto rhs_shape = nmtools_array{K,N};
    auto lhs = unwrap(na::reshape(na::arange(M*K,dtype),lhs_shape));
    
    auto rhs = unwrap(na::reshape(na::arange(K*N,dtype),rhs_shape));
    SYCL_TEST(matmul,lhs,rhs);
}

// TODO: fix opencl kernel compilation on pocl
TEST_CASE("matmul(case2)" * doctest::test_suite("array::matmul"))
{
    auto dtype = nm::float64;
    auto M = 16;
    auto N = 16;
    auto K = 5;
    auto lhs_shape = nmtools_array{M,K};
    auto rhs_shape = nmtools_array{K,N};
    auto lhs = unwrap(na::reshape(na::arange(M*K,dtype),lhs_shape));
    
    auto rhs = unwrap(na::reshape(na::arange(K*N,dtype),rhs_shape));
    SYCL_TEST(matmul,lhs,rhs);
}

// TODO: fix opencl kernel compilation on pocl
TEST_CASE("matmul(case3)" * doctest::test_suite("array::matmul"))
{
    auto dtype = nm::float64;
    auto M = 16;
    auto N = 16;
    auto K = 7;
    auto lhs_shape = nmtools_array{M,K};
    auto rhs_shape = nmtools_array{K,N};
    auto lhs = unwrap(na::reshape(na::arange(M*K,dtype),lhs_shape));
    
    auto rhs = unwrap(na::reshape(na::arange(K*N,dtype),rhs_shape));
    SYCL_TEST(matmul,lhs,rhs);
}

// TODO: fix opencl kernel compilation on pocl
TEST_CASE("matmul(case4)" * doctest::test_suite("array::matmul"))
{
    auto dtype = nm::float64;
    auto M = 16;
    auto N = 16;
    auto K = 8;
    auto lhs_shape = nmtools_array{M,K};
    auto rhs_shape = nmtools_array{K,N};
    auto lhs = unwrap(na::reshape(na::arange(M*K,dtype),lhs_shape));
   
    auto rhs = unwrap(na::reshape(na::arange(K*N,dtype),rhs_shape));
    SYCL_TEST(matmul,lhs,rhs);
}

// TODO: fix opencl kernel compilation on pocl
TEST_CASE("matmul(case5)" * doctest::test_suite("array::matmul"))
{
    auto dtype = nm::float64;
    auto M = 16;
    auto N = 16;
    auto K = 9;
    auto lhs_shape = nmtools_array{M,K};
    auto rhs_shape = nmtools_array{K,N};
    auto lhs = unwrap(na::reshape(na::arange(M*K,dtype),lhs_shape));
    
    auto rhs = unwrap(na::reshape(na::arange(K*N,dtype),rhs_shape));
    SYCL_TEST(matmul,lhs,rhs);
}

// TODO: fix opencl kernel compilation on pocl
TEST_CASE("matmul(case6)" * doctest::test_suite("array::matmul"))
{
    auto dtype = nm::float64;
    auto M = 16;
    auto N = 16;
    auto K = 10;
    auto lhs_shape = nmtools_array{M,K};
    auto rhs_shape = nmtools_array{K,N};
    auto lhs = unwrap(na::reshape(na::arange(M*K,dtype),lhs_shape));

    auto rhs = unwrap(na::reshape(na::arange(K*N,dtype),rhs_shape));
    SYCL_TEST(matmul,lhs,rhs);
}

// TODO: fix opencl kernel compilation on pocl
TEST_CASE("matmul(case7)" * doctest::test_suite("array::matmul"))
{
    auto dtype = nm::float64;
    auto M = 16;
    auto N = 16;
    auto K = 11;
    auto lhs_shape = nmtools_array{M,K};
    auto rhs_shape = nmtools_array{K,N};
    auto lhs = unwrap(na::reshape(na::arange(M*K,dtype),lhs_shape));
    
    auto rhs = unwrap(na::reshape(na::arange(K*N,dtype),rhs_shape));
    SYCL_TEST(matmul,lhs,rhs);
}

// TODO: fix opencl kernel compilation on pocl
TEST_CASE("matmul(case8)" * doctest::test_suite("array::matmul"))
{
    auto dtype = nm::float64;
    auto M = 16;
    auto N = 16;
    auto K = 12;
    auto lhs_shape = nmtools_array{M,K};
    auto rhs_shape = nmtools_array{K,N};
    auto lhs = unwrap(na::reshape(na::arange(M*K,dtype),lhs_shape));

    auto rhs = unwrap(na::reshape(na::arange(K*N,dtype),rhs_shape));
    SYCL_TEST(matmul,lhs,rhs);
}

// TODO: fix opencl kernel compilation on pocl
TEST_CASE("matmul(case9)" * doctest::test_suite("array::matmul"))
{
    auto dtype = nm::float64;
    auto M = 16;
    auto N = 16;
    auto K = 13;
    auto lhs_shape = nmtools_array{M,K};
    auto rhs_shape = nmtools_array{K,N};
    auto lhs = unwrap(na::reshape(na::arange(M*K,dtype),lhs_shape));

    auto rhs = unwrap(na::reshape(na::arange(K*N,dtype),rhs_shape));
    SYCL_TEST(matmul,lhs,rhs);
}

// TODO: fix opencl kernel compilation on pocl
TEST_CASE("matmul(case10)" * doctest::test_suite("array::matmul"))
{
    auto dtype = nm::float64;
    auto M = 16;
    auto N = 19;
    auto K = 12;
    auto lhs_shape = nmtools_array{M,K};
    auto rhs_shape = nmtools_array{K,N};
    auto lhs = unwrap(na::reshape(na::arange(M*K,dtype),lhs_shape));

    auto rhs = unwrap(na::reshape(na::arange(K*N,dtype),rhs_shape));
    SYCL_TEST(matmul,lhs,rhs);
}

// TODO: fix opencl kernel compilation on pocl
TEST_CASE("matmul(case11)" * doctest::test_suite("array::matmul"))
{
    auto dtype = nm::float64;
    auto M = 16;
    auto N = 19;
    auto K = 13;
    auto lhs_shape = nmtools_array{M,K};
    auto rhs_shape = nmtools_array{K,N};
    auto lhs = unwrap(na::reshape(na::arange(M*K,dtype),lhs_shape));

    auto rhs = unwrap(na::reshape(na::arange(K*N,dtype),rhs_shape));
    SYCL_TEST(matmul,lhs,rhs);
}

// TODO: fix opencl kernel compilation on pocl
TEST_CASE("matmul(case12)" * doctest::test_suite("array::matmul"))
{
    auto dtype = nm::float64;
    auto M = 16;
    auto N = 19;
    auto K = 14;
    auto lhs_shape = nmtools_array{M,K};
    auto rhs_shape = nmtools_array{K,N};
    auto lhs = unwrap(na::reshape(na::arange(M*K,dtype),lhs_shape));

    auto rhs = unwrap(na::reshape(na::arange(K*N,dtype),rhs_shape));
    SYCL_TEST(matmul,lhs,rhs);
}

// TODO: fix opencl kernel compilation on pocl
TEST_CASE("matmul(case13)" * doctest::test_suite("array::matmul"))
{
    auto dtype = nm::float64;
    auto M = 16;
    auto N = 19;
    auto K = 15;
    auto lhs_shape = nmtools_array{M,K};
    auto rhs_shape = nmtools_array{K,N};
    auto lhs = unwrap(na::reshape(na::arange(M*K,dtype),lhs_shape));

    auto rhs = unwrap(na::reshape(na::arange(K*N,dtype),rhs_shape));
    SYCL_TEST(matmul,lhs,rhs);
}

// TODO: fix opencl kernel compilation on pocl
TEST_CASE("matmul(case14)" * doctest::test_suite("array::matmul"))
{
    auto dtype = nm::float64;
    auto M = 1;
    auto N = 19;
    auto K = 12;
    auto lhs_shape = nmtools_array{M,K};
    auto rhs_shape = nmtools_array{K,N};
    auto lhs = unwrap(na::reshape(na::arange(M*K,dtype),lhs_shape));

    auto rhs = unwrap(na::reshape(na::arange(K*N,dtype),rhs_shape));
    SYCL_TEST(matmul,lhs,rhs);
}

// TODO: fix opencl kernel compilation on pocl
TEST_CASE("matmul(case15)" * doctest::test_suite("array::matmul"))
{
    auto dtype = nm::float64;
    auto M = 16;
    auto N = 1;
    auto K = 13;
    auto lhs_shape = nmtools_array{M,K};
    auto rhs_shape = nmtools_array{K,N};
    auto lhs = unwrap(na::reshape(na::arange(M*K,dtype),lhs_shape));

    auto rhs = unwrap(na::reshape(na::arange(K*N,dtype),rhs_shape));
    SYCL_TEST(matmul,lhs,rhs);
}

// TODO: fix opencl kernel compilation on pocl
TEST_CASE("matmul(case1)" * doctest::test_suite("array::matmul"))
{
    auto dtype = nm::int32;
    auto M = 4;
    auto N = 4;
    auto K = 4;
    auto lhs_shape = nmtools_array{M,K};
    auto rhs_shape = nmtools_array{K,N};
    auto lhs = unwrap(na::reshape(na::arange(M*K,dtype),lhs_shape));
    
    auto rhs = unwrap(na::reshape(na::arange(K*N,dtype),rhs_shape));
    SYCL_TEST(matmul,lhs,rhs);
}

// TODO: fix opencl kernel compilation on pocl
TEST_CASE("matmul(case1b)" * doctest::test_suite("array::matmul"))
{
    auto dtype = nm::int32;
    auto M = 4;
    auto N = 4;
    auto K = 5;
    auto lhs_shape = nmtools_array{M,K};
    auto rhs_shape = nmtools_array{K,N};
    auto lhs = unwrap(na::reshape(na::arange(M*K,dtype),lhs_shape));

    auto rhs = unwrap(na::reshape(na::arange(K*N,dtype),rhs_shape));
    SYCL_TEST(matmul,lhs,rhs);
}

// TODO: fix opencl kernel compilation on pocl
TEST_CASE("matmul(case1b)" * doctest::test_suite("array::matmul"))
{
    auto dtype = nm::int32;
    auto M = 2;
    auto N = 2;
    auto K = 5;
    auto lhs_shape = nmtools_array{M,K};
    auto rhs_shape = nmtools_array{K,N};
    auto lhs = unwrap(na::reshape(na::arange(M*K,dtype),lhs_shape));
    
    auto rhs = unwrap(na::reshape(na::arange(K*N,dtype),rhs_shape));
    SYCL_TEST(matmul,lhs,rhs);
}

// TODO: fix opencl kernel compilation on pocl
TEST_CASE("matmul(case1c)" * doctest::test_suite("array::matmul"))
{
    auto dtype = nm::int32;
    auto M = 4;
    auto N = 4;
    auto K = 6;
    auto lhs_shape = nmtools_array{M,K};
    auto rhs_shape = nmtools_array{K,N};
    auto lhs = unwrap(na::reshape(na::arange(M*K,dtype),lhs_shape));
    
    auto rhs = unwrap(na::reshape(na::arange(K*N,dtype),rhs_shape));
    SYCL_TEST(matmul,lhs,rhs);
}

// TODO: fix opencl kernel compilation on pocl
TEST_CASE("matmul(case1d)" * doctest::test_suite("array::matmul"))
{
    auto dtype = nm::int32;
    auto M = 4;
    auto N = 4;
    auto K = 7;
    auto lhs_shape = nmtools_array{M,K};
    auto rhs_shape = nmtools_array{K,N};
    auto lhs = unwrap(na::reshape(na::arange(M*K,dtype),lhs_shape));
    
    auto rhs = unwrap(na::reshape(na::arange(K*N,dtype),rhs_shape));
    SYCL_TEST(matmul,lhs,rhs);
}

// TODO: fix opencl kernel compilation on pocl
TEST_CASE("matmul(case1e)" * doctest::test_suite("array::matmul"))
{
    auto dtype = nm::int32;
    auto M = 4;
    auto N = 4;
    auto K = 8;
    auto lhs_shape = nmtools_array{M,K};
    auto rhs_shape = nmtools_array{K,N};
    auto lhs = unwrap(na::reshape(na::arange(M*K,dtype),lhs_shape));
    
    auto rhs = unwrap(na::reshape(na::arange(K*N,dtype),rhs_shape));
    SYCL_TEST(matmul,lhs,rhs);
}

// TODO: fix opencl kernel compilation on pocl
TEST_CASE("matmul(case2)" * doctest::test_suite("array::matmul"))
{
    auto dtype = nm::int32;
    auto M = 16;
    auto N = 16;
    auto K = 5;
    auto lhs_shape = nmtools_array{M,K};
    auto rhs_shape = nmtools_array{K,N};
    auto lhs = unwrap(na::reshape(na::arange(M*K,dtype),lhs_shape));
    
    auto rhs = unwrap(na::reshape(na::arange(K*N,dtype),rhs_shape));
    SYCL_TEST(matmul,lhs,rhs);
}

// TODO: fix opencl kernel compilation on pocl
TEST_CASE("matmul(case3)" * doctest::test_suite("array::matmul"))
{
    auto dtype = nm::int32;
    auto M = 16;
    auto N = 16;
    auto K = 7;
    auto lhs_shape = nmtools_array{M,K};
    auto rhs_shape = nmtools_array{K,N};
    auto lhs = unwrap(na::reshape(na::arange(M*K,dtype),lhs_shape));
    
    auto rhs = unwrap(na::reshape(na::arange(K*N,dtype),rhs_shape));
    SYCL_TEST(matmul,lhs,rhs);
}

// TODO: fix opencl kernel compilation on pocl
TEST_CASE("matmul(case4)" * doctest::test_suite("array::matmul"))
{
    auto dtype = nm::int32;
    auto M = 16;
    auto N = 16;
    auto K = 8;
    auto lhs_shape = nmtools_array{M,K};
    auto rhs_shape = nmtools_array{K,N};
    auto lhs = unwrap(na::reshape(na::arange(M*K,dtype),lhs_shape));
   
    auto rhs = unwrap(na::reshape(na::arange(K*N,dtype),rhs_shape));
    SYCL_TEST(matmul,lhs,rhs);
}

// TODO: fix opencl kernel compilation on pocl
TEST_CASE("matmul(case5)" * doctest::test_suite("array::matmul"))
{
    auto dtype = nm::int32;
    auto M = 16;
    auto N = 16;
    auto K = 9;
    auto lhs_shape = nmtools_array{M,K};
    auto rhs_shape = nmtools_array{K,N};
    auto lhs = unwrap(na::reshape(na::arange(M*K,dtype),lhs_shape));
    
    auto rhs = unwrap(na::reshape(na::arange(K*N,dtype),rhs_shape));
    SYCL_TEST(matmul,lhs,rhs);
}

// TODO: fix opencl kernel compilation on pocl
TEST_CASE("matmul(case6)" * doctest::test_suite("array::matmul"))
{
    auto dtype = nm::int32;
    auto M = 16;
    auto N = 16;
    auto K = 10;
    auto lhs_shape = nmtools_array{M,K};
    auto rhs_shape = nmtools_array{K,N};
    auto lhs = unwrap(na::reshape(na::arange(M*K,dtype),lhs_shape));

    auto rhs = unwrap(na::reshape(na::arange(K*N,dtype),rhs_shape));
    SYCL_TEST(matmul,lhs,rhs);
}

// TODO: fix opencl kernel compilation on pocl
TEST_CASE("matmul(case7)" * doctest::test_suite("array::matmul"))
{
    auto dtype = nm::int32;
    auto M = 16;
    auto N = 16;
    auto K = 11;
    auto lhs_shape = nmtools_array{M,K};
    auto rhs_shape = nmtools_array{K,N};
    auto lhs = unwrap(na::reshape(na::arange(M*K,dtype),lhs_shape));
    
    auto rhs = unwrap(na::reshape(na::arange(K*N,dtype),rhs_shape));
    SYCL_TEST(matmul,lhs,rhs);
}

// TODO: fix opencl kernel compilation on pocl
TEST_CASE("matmul(case8)" * doctest::test_suite("array::matmul"))
{
    auto dtype = nm::int32;
    auto M = 16;
    auto N = 16;
    auto K = 12;
    auto lhs_shape = nmtools_array{M,K};
    auto rhs_shape = nmtools_array{K,N};
    auto lhs = unwrap(na::reshape(na::arange(M*K,dtype),lhs_shape));

    auto rhs = unwrap(na::reshape(na::arange(K*N,dtype),rhs_shape));
    SYCL_TEST(matmul,lhs,rhs);
}

// TODO: fix opencl kernel compilation on pocl
TEST_CASE("matmul(case9)" * doctest::test_suite("array::matmul"))
{
    auto dtype = nm::int32;
    auto M = 16;
    auto N = 16;
    auto K = 13;
    auto lhs_shape = nmtools_array{M,K};
    auto rhs_shape = nmtools_array{K,N};
    auto lhs = unwrap(na::reshape(na::arange(M*K,dtype),lhs_shape));

    auto rhs = unwrap(na::reshape(na::arange(K*N,dtype),rhs_shape));
    SYCL_TEST(matmul,lhs,rhs);
}

// TODO: fix opencl kernel compilation on pocl
TEST_CASE("matmul(case10)" * doctest::test_suite("array::matmul"))
{
    auto dtype = nm::int32;
    auto M = 16;
    auto N = 19;
    auto K = 12;
    auto lhs_shape = nmtools_array{M,K};
    auto rhs_shape = nmtools_array{K,N};
    auto lhs = unwrap(na::reshape(na::arange(M*K,dtype),lhs_shape));

    auto rhs = unwrap(na::reshape(na::arange(K*N,dtype),rhs_shape));
    SYCL_TEST(matmul,lhs,rhs);
}

// TODO: fix opencl kernel compilation on pocl
TEST_CASE("matmul(case11)" * doctest::test_suite("array::matmul"))
{
    auto dtype = nm::int32;
    auto M = 16;
    auto N = 19;
    auto K = 13;
    auto lhs_shape = nmtools_array{M,K};
    auto rhs_shape = nmtools_array{K,N};
    auto lhs = unwrap(na::reshape(na::arange(M*K,dtype),lhs_shape));

    auto rhs = unwrap(na::reshape(na::arange(K*N,dtype),rhs_shape));
    SYCL_TEST(matmul,lhs,rhs);
}

// TODO: fix opencl kernel compilation on pocl
TEST_CASE("matmul(case12)" * doctest::test_suite("array::matmul"))
{
    auto dtype = nm::int32;
    auto M = 16;
    auto N = 19;
    auto K = 14;
    auto lhs_shape = nmtools_array{M,K};
    auto rhs_shape = nmtools_array{K,N};
    auto lhs = unwrap(na::reshape(na::arange(M*K,dtype),lhs_shape));

    auto rhs = unwrap(na::reshape(na::arange(K*N,dtype),rhs_shape));
    SYCL_TEST(matmul,lhs,rhs);
}

// TODO: fix opencl kernel compilation on pocl
TEST_CASE("matmul(case13)" * doctest::test_suite("array::matmul"))
{
    auto dtype = nm::int32;
    auto M = 16;
    auto N = 19;
    auto K = 15;
    auto lhs_shape = nmtools_array{M,K};
    auto rhs_shape = nmtools_array{K,N};
    auto lhs = unwrap(na::reshape(na::arange(M*K,dtype),lhs_shape));

    auto rhs = unwrap(na::reshape(na::arange(K*N,dtype),rhs_shape));
    SYCL_TEST(matmul,lhs,rhs);
}

// TODO: fix opencl kernel compilation on pocl
TEST_CASE("matmul(case14)" * doctest::test_suite("array::matmul"))
{
    auto dtype = nm::int32;
    auto M = 1;
    auto N = 19;
    auto K = 12;
    auto lhs_shape = nmtools_array{M,K};
    auto rhs_shape = nmtools_array{K,N};
    auto lhs = unwrap(na::reshape(na::arange(M*K,dtype),lhs_shape));

    auto rhs = unwrap(na::reshape(na::arange(K*N,dtype),rhs_shape));
    SYCL_TEST(matmul,lhs,rhs);
}

// TODO: fix opencl kernel compilation on pocl
TEST_CASE("matmul(case15)" * doctest::test_suite("array::matmul"))
{
    auto dtype = nm::int32;
    auto M = 16;
    auto N = 1;
    auto K = 13;
    auto lhs_shape = nmtools_array{M,K};
    auto rhs_shape = nmtools_array{K,N};
    auto lhs = unwrap(na::reshape(na::arange(M*K,dtype),lhs_shape));

    auto rhs = unwrap(na::reshape(na::arange(K*N,dtype),rhs_shape));
    SYCL_TEST(matmul,lhs,rhs);
}

///////////////////////////////////////////////////////////////////////

// TODO: fix opencl kernel compilation on pocl
TEST_CASE("matmul(case1)" * doctest::test_suite("array::matmul"))
{
    auto dtype = nm::int64;
    auto M = 4;
    auto N = 4;
    auto K = 4;
    auto lhs_shape = nmtools_array{M,K};
    auto rhs_shape = nmtools_array{K,N};
    auto lhs = unwrap(na::reshape(na::arange(M*K,dtype),lhs_shape));
    
    auto rhs = unwrap(na::reshape(na::arange(K*N,dtype),rhs_shape));
    SYCL_TEST(matmul,lhs,rhs);
}

// TODO: fix opencl kernel compilation on pocl
TEST_CASE("matmul(case1b)" * doctest::test_suite("array::matmul"))
{
    auto dtype = nm::int64;
    auto M = 4;
    auto N = 4;
    auto K = 5;
    auto lhs_shape = nmtools_array{M,K};
    auto rhs_shape = nmtools_array{K,N};
    auto lhs = unwrap(na::reshape(na::arange(M*K,dtype),lhs_shape));

    auto rhs = unwrap(na::reshape(na::arange(K*N,dtype),rhs_shape));
    SYCL_TEST(matmul,lhs,rhs);
}

// TODO: fix opencl kernel compilation on pocl
TEST_CASE("matmul(case1b)" * doctest::test_suite("array::matmul"))
{
    auto dtype = nm::int64;
    auto M = 2;
    auto N = 2;
    auto K = 5;
    auto lhs_shape = nmtools_array{M,K};
    auto rhs_shape = nmtools_array{K,N};
    auto lhs = unwrap(na::reshape(na::arange(M*K,dtype),lhs_shape));
    
    auto rhs = unwrap(na::reshape(na::arange(K*N,dtype),rhs_shape));
    SYCL_TEST(matmul,lhs,rhs);
}

// TODO: fix opencl kernel compilation on pocl
TEST_CASE("matmul(case1c)" * doctest::test_suite("array::matmul"))
{
    auto dtype = nm::int64;
    auto M = 4;
    auto N = 4;
    auto K = 6;
    auto lhs_shape = nmtools_array{M,K};
    auto rhs_shape = nmtools_array{K,N};
    auto lhs = unwrap(na::reshape(na::arange(M*K,dtype),lhs_shape));
    
    auto rhs = unwrap(na::reshape(na::arange(K*N,dtype),rhs_shape));
    SYCL_TEST(matmul,lhs,rhs);
}

// TODO: fix opencl kernel compilation on pocl
TEST_CASE("matmul(case1d)" * doctest::test_suite("array::matmul"))
{
    auto dtype = nm::int64;
    auto M = 4;
    auto N = 4;
    auto K = 7;
    auto lhs_shape = nmtools_array{M,K};
    auto rhs_shape = nmtools_array{K,N};
    auto lhs = unwrap(na::reshape(na::arange(M*K,dtype),lhs_shape));
    
    auto rhs = unwrap(na::reshape(na::arange(K*N,dtype),rhs_shape));
    SYCL_TEST(matmul,lhs,rhs);
}

// TODO: fix opencl kernel compilation on pocl
TEST_CASE("matmul(case1e)" * doctest::test_suite("array::matmul"))
{
    auto dtype = nm::int64;
    auto M = 4;
    auto N = 4;
    auto K = 8;
    auto lhs_shape = nmtools_array{M,K};
    auto rhs_shape = nmtools_array{K,N};
    auto lhs = unwrap(na::reshape(na::arange(M*K,dtype),lhs_shape));
    
    auto rhs = unwrap(na::reshape(na::arange(K*N,dtype),rhs_shape));
    SYCL_TEST(matmul,lhs,rhs);
}

// TODO: fix opencl kernel compilation on pocl
TEST_CASE("matmul(case2)" * doctest::test_suite("array::matmul"))
{
    auto dtype = nm::int64;
    auto M = 16;
    auto N = 16;
    auto K = 5;
    auto lhs_shape = nmtools_array{M,K};
    auto rhs_shape = nmtools_array{K,N};
    auto lhs = unwrap(na::reshape(na::arange(M*K,dtype),lhs_shape));
    
    auto rhs = unwrap(na::reshape(na::arange(K*N,dtype),rhs_shape));
    SYCL_TEST(matmul,lhs,rhs);
}

// TODO: fix opencl kernel compilation on pocl
TEST_CASE("matmul(case3)" * doctest::test_suite("array::matmul"))
{
    auto dtype = nm::int64;
    auto M = 16;
    auto N = 16;
    auto K = 7;
    auto lhs_shape = nmtools_array{M,K};
    auto rhs_shape = nmtools_array{K,N};
    auto lhs = unwrap(na::reshape(na::arange(M*K,dtype),lhs_shape));
    
    auto rhs = unwrap(na::reshape(na::arange(K*N,dtype),rhs_shape));
    SYCL_TEST(matmul,lhs,rhs);
}

// TODO: fix opencl kernel compilation on pocl
TEST_CASE("matmul(case4)" * doctest::test_suite("array::matmul"))
{
    auto dtype = nm::int64;
    auto M = 16;
    auto N = 16;
    auto K = 8;
    auto lhs_shape = nmtools_array{M,K};
    auto rhs_shape = nmtools_array{K,N};
    auto lhs = unwrap(na::reshape(na::arange(M*K,dtype),lhs_shape));
   
    auto rhs = unwrap(na::reshape(na::arange(K*N,dtype),rhs_shape));
    SYCL_TEST(matmul,lhs,rhs);
}

// TODO: fix opencl kernel compilation on pocl
TEST_CASE("matmul(case5)" * doctest::test_suite("array::matmul"))
{
    auto dtype = nm::int64;
    auto M = 16;
    auto N = 16;
    auto K = 9;
    auto lhs_shape = nmtools_array{M,K};
    auto rhs_shape = nmtools_array{K,N};
    auto lhs = unwrap(na::reshape(na::arange(M*K,dtype),lhs_shape));
    
    auto rhs = unwrap(na::reshape(na::arange(K*N,dtype),rhs_shape));
    SYCL_TEST(matmul,lhs,rhs);
}

// TODO: fix opencl kernel compilation on pocl
TEST_CASE("matmul(case6)" * doctest::test_suite("array::matmul"))
{
    auto dtype = nm::int64;
    auto M = 16;
    auto N = 16;
    auto K = 10;
    auto lhs_shape = nmtools_array{M,K};
    auto rhs_shape = nmtools_array{K,N};
    auto lhs = unwrap(na::reshape(na::arange(M*K,dtype),lhs_shape));

    auto rhs = unwrap(na::reshape(na::arange(K*N,dtype),rhs_shape));
    SYCL_TEST(matmul,lhs,rhs);
}

// TODO: fix opencl kernel compilation on pocl
TEST_CASE("matmul(case7)" * doctest::test_suite("array::matmul"))
{
    auto dtype = nm::int64;
    auto M = 16;
    auto N = 16;
    auto K = 11;
    auto lhs_shape = nmtools_array{M,K};
    auto rhs_shape = nmtools_array{K,N};
    auto lhs = unwrap(na::reshape(na::arange(M*K,dtype),lhs_shape));
    
    auto rhs = unwrap(na::reshape(na::arange(K*N,dtype),rhs_shape));
    SYCL_TEST(matmul,lhs,rhs);
}

// TODO: fix opencl kernel compilation on pocl
TEST_CASE("matmul(case8)" * doctest::test_suite("array::matmul"))
{
    auto dtype = nm::int64;
    auto M = 16;
    auto N = 16;
    auto K = 12;
    auto lhs_shape = nmtools_array{M,K};
    auto rhs_shape = nmtools_array{K,N};
    auto lhs = unwrap(na::reshape(na::arange(M*K,dtype),lhs_shape));

    auto rhs = unwrap(na::reshape(na::arange(K*N,dtype),rhs_shape));
    SYCL_TEST(matmul,lhs,rhs);
}

// TODO: fix opencl kernel compilation on pocl
TEST_CASE("matmul(case9)" * doctest::test_suite("array::matmul"))
{
    auto dtype = nm::int64;
    auto M = 16;
    auto N = 16;
    auto K = 13;
    auto lhs_shape = nmtools_array{M,K};
    auto rhs_shape = nmtools_array{K,N};
    auto lhs = unwrap(na::reshape(na::arange(M*K,dtype),lhs_shape));

    auto rhs = unwrap(na::reshape(na::arange(K*N,dtype),rhs_shape));
    SYCL_TEST(matmul,lhs,rhs);
}

// TODO: fix opencl kernel compilation on pocl
TEST_CASE("matmul(case10)" * doctest::test_suite("array::matmul"))
{
    auto dtype = nm::int64;
    auto M = 16;
    auto N = 19;
    auto K = 12;
    auto lhs_shape = nmtools_array{M,K};
    auto rhs_shape = nmtools_array{K,N};
    auto lhs = unwrap(na::reshape(na::arange(M*K,dtype),lhs_shape));

    auto rhs = unwrap(na::reshape(na::arange(K*N,dtype),rhs_shape));
    SYCL_TEST(matmul,lhs,rhs);
}

// TODO: fix opencl kernel compilation on pocl
TEST_CASE("matmul(case11)" * doctest::test_suite("array::matmul"))
{
    auto dtype = nm::int64;
    auto M = 16;
    auto N = 19;
    auto K = 13;
    auto lhs_shape = nmtools_array{M,K};
    auto rhs_shape = nmtools_array{K,N};
    auto lhs = unwrap(na::reshape(na::arange(M*K,dtype),lhs_shape));

    auto rhs = unwrap(na::reshape(na::arange(K*N,dtype),rhs_shape));
    SYCL_TEST(matmul,lhs,rhs);
}

// TODO: fix opencl kernel compilation on pocl
TEST_CASE("matmul(case12)" * doctest::test_suite("array::matmul"))
{
    auto dtype = nm::int64;
    auto M = 16;
    auto N = 19;
    auto K = 14;
    auto lhs_shape = nmtools_array{M,K};
    auto rhs_shape = nmtools_array{K,N};
    auto lhs = unwrap(na::reshape(na::arange(M*K,dtype),lhs_shape));

    auto rhs = unwrap(na::reshape(na::arange(K*N,dtype),rhs_shape));
    SYCL_TEST(matmul,lhs,rhs);
}

// TODO: fix opencl kernel compilation on pocl
TEST_CASE("matmul(case13)" * doctest::test_suite("array::matmul"))
{
    auto dtype = nm::int64;
    auto M = 16;
    auto N = 19;
    auto K = 15;
    auto lhs_shape = nmtools_array{M,K};
    auto rhs_shape = nmtools_array{K,N};
    auto lhs = unwrap(na::reshape(na::arange(M*K,dtype),lhs_shape));

    auto rhs = unwrap(na::reshape(na::arange(K*N,dtype),rhs_shape));
    SYCL_TEST(matmul,lhs,rhs);
}

// TODO: fix opencl kernel compilation on pocl
TEST_CASE("matmul(case14)" * doctest::test_suite("array::matmul"))
{
    auto dtype = nm::int64;
    auto M = 1;
    auto N = 19;
    auto K = 12;
    auto lhs_shape = nmtools_array{M,K};
    auto rhs_shape = nmtools_array{K,N};
    auto lhs = unwrap(na::reshape(na::arange(M*K,dtype),lhs_shape));

    auto rhs = unwrap(na::reshape(na::arange(K*N,dtype),rhs_shape));
    SYCL_TEST(matmul,lhs,rhs);
}

// TODO: fix opencl kernel compilation on pocl
TEST_CASE("matmul(case15)" * doctest::test_suite("array::matmul"))
{
    auto dtype = nm::int64;
    auto M = 16;
    auto N = 1;
    auto K = 13;
    auto lhs_shape = nmtools_array{M,K};
    auto rhs_shape = nmtools_array{K,N};
    auto lhs = unwrap(na::reshape(na::arange(M*K,dtype),lhs_shape));

    auto rhs = unwrap(na::reshape(na::arange(K*N,dtype),rhs_shape));
    SYCL_TEST(matmul,lhs,rhs);
}

/////////////////////////////////////////////////////////////////////

// TODO: fix opencl kernel compilation on pocl
TEST_CASE("matmul(case1)" * doctest::test_suite("array::matmul"))
{
    auto dtype = nm::int16;
    auto M = 4;
    auto N = 4;
    auto K = 4;
    auto lhs_shape = nmtools_array{M,K};
    auto rhs_shape = nmtools_array{K,N};
    auto lhs = unwrap(na::reshape(na::arange(M*K,dtype),lhs_shape));
    
    auto rhs = unwrap(na::reshape(na::arange(K*N,dtype),rhs_shape));
    SYCL_TEST(matmul,lhs,rhs);
}

// TODO: fix opencl kernel compilation on pocl
TEST_CASE("matmul(case1b)" * doctest::test_suite("array::matmul"))
{
    auto dtype = nm::int16;
    auto M = 4;
    auto N = 4;
    auto K = 5;
    auto lhs_shape = nmtools_array{M,K};
    auto rhs_shape = nmtools_array{K,N};
    auto lhs = unwrap(na::reshape(na::arange(M*K,dtype),lhs_shape));

    auto rhs = unwrap(na::reshape(na::arange(K*N,dtype),rhs_shape));
    SYCL_TEST(matmul,lhs,rhs);
}

// TODO: fix opencl kernel compilation on pocl
TEST_CASE("matmul(case1b)" * doctest::test_suite("array::matmul"))
{
    auto dtype = nm::int16;
    auto M = 2;
    auto N = 2;
    auto K = 5;
    auto lhs_shape = nmtools_array{M,K};
    auto rhs_shape = nmtools_array{K,N};
    auto lhs = unwrap(na::reshape(na::arange(M*K,dtype),lhs_shape));
    
    auto rhs = unwrap(na::reshape(na::arange(K*N,dtype),rhs_shape));
    SYCL_TEST(matmul,lhs,rhs);
}

// TODO: fix opencl kernel compilation on pocl
TEST_CASE("matmul(case1c)" * doctest::test_suite("array::matmul"))
{
    auto dtype = nm::int16;
    auto M = 4;
    auto N = 4;
    auto K = 6;
    auto lhs_shape = nmtools_array{M,K};
    auto rhs_shape = nmtools_array{K,N};
    auto lhs = unwrap(na::reshape(na::arange(M*K,dtype),lhs_shape));
    
    auto rhs = unwrap(na::reshape(na::arange(K*N,dtype),rhs_shape));
    SYCL_TEST(matmul,lhs,rhs);
}

// TODO: fix opencl kernel compilation on pocl
TEST_CASE("matmul(case1d)" * doctest::test_suite("array::matmul"))
{
    auto dtype = nm::int16;
    auto M = 4;
    auto N = 4;
    auto K = 7;
    auto lhs_shape = nmtools_array{M,K};
    auto rhs_shape = nmtools_array{K,N};
    auto lhs = unwrap(na::reshape(na::arange(M*K,dtype),lhs_shape));
    
    auto rhs = unwrap(na::reshape(na::arange(K*N,dtype),rhs_shape));
    SYCL_TEST(matmul,lhs,rhs);
}

// TODO: fix opencl kernel compilation on pocl
TEST_CASE("matmul(case1e)" * doctest::test_suite("array::matmul"))
{
    auto dtype = nm::int16;
    auto M = 4;
    auto N = 4;
    auto K = 8;
    auto lhs_shape = nmtools_array{M,K};
    auto rhs_shape = nmtools_array{K,N};
    auto lhs = unwrap(na::reshape(na::arange(M*K,dtype),lhs_shape));
    
    auto rhs = unwrap(na::reshape(na::arange(K*N,dtype),rhs_shape));
    SYCL_TEST(matmul,lhs,rhs);
}

// TODO: fix opencl kernel compilation on pocl
TEST_CASE("matmul(case2)" * doctest::test_suite("array::matmul"))
{
    auto dtype = nm::int16;
    auto M = 16;
    auto N = 16;
    auto K = 5;
    auto lhs_shape = nmtools_array{M,K};
    auto rhs_shape = nmtools_array{K,N};
    auto lhs = unwrap(na::reshape(na::arange(M*K,dtype),lhs_shape));
    
    auto rhs = unwrap(na::reshape(na::arange(K*N,dtype),rhs_shape));
    SYCL_TEST(matmul,lhs,rhs);
}

// TODO: fix opencl kernel compilation on pocl
TEST_CASE("matmul(case3)" * doctest::test_suite("array::matmul"))
{
    auto dtype = nm::int16;
    auto M = 16;
    auto N = 16;
    auto K = 7;
    auto lhs_shape = nmtools_array{M,K};
    auto rhs_shape = nmtools_array{K,N};
    auto lhs = unwrap(na::reshape(na::arange(M*K,dtype),lhs_shape));
    
    auto rhs = unwrap(na::reshape(na::arange(K*N,dtype),rhs_shape));
    SYCL_TEST(matmul,lhs,rhs);
}

// TODO: fix opencl kernel compilation on pocl
TEST_CASE("matmul(case4)" * doctest::test_suite("array::matmul"))
{
    auto dtype = nm::int16;
    auto M = 16;
    auto N = 16;
    auto K = 8;
    auto lhs_shape = nmtools_array{M,K};
    auto rhs_shape = nmtools_array{K,N};
    auto lhs = unwrap(na::reshape(na::arange(M*K,dtype),lhs_shape));
   
    auto rhs = unwrap(na::reshape(na::arange(K*N,dtype),rhs_shape));
    SYCL_TEST(matmul,lhs,rhs);
}

// TODO: fix opencl kernel compilation on pocl
TEST_CASE("matmul(case5)" * doctest::test_suite("array::matmul"))
{
    auto dtype = nm::int16;
    auto M = 16;
    auto N = 16;
    auto K = 9;
    auto lhs_shape = nmtools_array{M,K};
    auto rhs_shape = nmtools_array{K,N};
    auto lhs = unwrap(na::reshape(na::arange(M*K,dtype),lhs_shape));
    
    auto rhs = unwrap(na::reshape(na::arange(K*N,dtype),rhs_shape));
    SYCL_TEST(matmul,lhs,rhs);
}

// TODO: fix opencl kernel compilation on pocl
TEST_CASE("matmul(case6)" * doctest::test_suite("array::matmul"))
{
    auto dtype = nm::int16;
    auto M = 16;
    auto N = 16;
    auto K = 10;
    auto lhs_shape = nmtools_array{M,K};
    auto rhs_shape = nmtools_array{K,N};
    auto lhs = unwrap(na::reshape(na::arange(M*K,dtype),lhs_shape));

    auto rhs = unwrap(na::reshape(na::arange(K*N,dtype),rhs_shape));
    SYCL_TEST(matmul,lhs,rhs);
}

// TODO: fix opencl kernel compilation on pocl
TEST_CASE("matmul(case7)" * doctest::test_suite("array::matmul"))
{
    auto dtype = nm::int16;
    auto M = 16;
    auto N = 16;
    auto K = 11;
    auto lhs_shape = nmtools_array{M,K};
    auto rhs_shape = nmtools_array{K,N};
    auto lhs = unwrap(na::reshape(na::arange(M*K,dtype),lhs_shape));
    
    auto rhs = unwrap(na::reshape(na::arange(K*N,dtype),rhs_shape));
    SYCL_TEST(matmul,lhs,rhs);
}

// TODO: fix opencl kernel compilation on pocl
TEST_CASE("matmul(case8)" * doctest::test_suite("array::matmul"))
{
    auto dtype = nm::int16;
    auto M = 16;
    auto N = 16;
    auto K = 12;
    auto lhs_shape = nmtools_array{M,K};
    auto rhs_shape = nmtools_array{K,N};
    auto lhs = unwrap(na::reshape(na::arange(M*K,dtype),lhs_shape));

    auto rhs = unwrap(na::reshape(na::arange(K*N,dtype),rhs_shape));
    SYCL_TEST(matmul,lhs,rhs);
}

// TODO: fix opencl kernel compilation on pocl
TEST_CASE("matmul(case9)" * doctest::test_suite("array::matmul"))
{
    auto dtype = nm::int16;
    auto M = 16;
    auto N = 16;
    auto K = 13;
    auto lhs_shape = nmtools_array{M,K};
    auto rhs_shape = nmtools_array{K,N};
    auto lhs = unwrap(na::reshape(na::arange(M*K,dtype),lhs_shape));

    auto rhs = unwrap(na::reshape(na::arange(K*N,dtype),rhs_shape));
    SYCL_TEST(matmul,lhs,rhs);
}

// TODO: fix opencl kernel compilation on pocl
TEST_CASE("matmul(case10)" * doctest::test_suite("array::matmul"))
{
    auto dtype = nm::int16;
    auto M = 16;
    auto N = 19;
    auto K = 12;
    auto lhs_shape = nmtools_array{M,K};
    auto rhs_shape = nmtools_array{K,N};
    auto lhs = unwrap(na::reshape(na::arange(M*K,dtype),lhs_shape));

    auto rhs = unwrap(na::reshape(na::arange(K*N,dtype),rhs_shape));
    SYCL_TEST(matmul,lhs,rhs);
}

// TODO: fix opencl kernel compilation on pocl
TEST_CASE("matmul(case11)" * doctest::test_suite("array::matmul"))
{
    auto dtype = nm::int16;
    auto M = 16;
    auto N = 19;
    auto K = 13;
    auto lhs_shape = nmtools_array{M,K};
    auto rhs_shape = nmtools_array{K,N};
    auto lhs = unwrap(na::reshape(na::arange(M*K,dtype),lhs_shape));

    auto rhs = unwrap(na::reshape(na::arange(K*N,dtype),rhs_shape));
    SYCL_TEST(matmul,lhs,rhs);
}

// TODO: fix opencl kernel compilation on pocl
TEST_CASE("matmul(case12)" * doctest::test_suite("array::matmul"))
{
    auto dtype = nm::int16;
    auto M = 16;
    auto N = 19;
    auto K = 14;
    auto lhs_shape = nmtools_array{M,K};
    auto rhs_shape = nmtools_array{K,N};
    auto lhs = unwrap(na::reshape(na::arange(M*K,dtype),lhs_shape));

    auto rhs = unwrap(na::reshape(na::arange(K*N,dtype),rhs_shape));
    SYCL_TEST(matmul,lhs,rhs);
}

// TODO: fix opencl kernel compilation on pocl
TEST_CASE("matmul(case13)" * doctest::test_suite("array::matmul"))
{
    auto dtype = nm::int16;
    auto M = 16;
    auto N = 19;
    auto K = 15;
    auto lhs_shape = nmtools_array{M,K};
    auto rhs_shape = nmtools_array{K,N};
    auto lhs = unwrap(na::reshape(na::arange(M*K,dtype),lhs_shape));

    auto rhs = unwrap(na::reshape(na::arange(K*N,dtype),rhs_shape));
    SYCL_TEST(matmul,lhs,rhs);
}

// TODO: fix opencl kernel compilation on pocl
TEST_CASE("matmul(case14)" * doctest::test_suite("array::matmul"))
{
    auto dtype = nm::int16;
    auto M = 1;
    auto N = 19;
    auto K = 12;
    auto lhs_shape = nmtools_array{M,K};
    auto rhs_shape = nmtools_array{K,N};
    auto lhs = unwrap(na::reshape(na::arange(M*K,dtype),lhs_shape));

    auto rhs = unwrap(na::reshape(na::arange(K*N,dtype),rhs_shape));
    SYCL_TEST(matmul,lhs,rhs);
}

// TODO: fix opencl kernel compilation on pocl
TEST_CASE("matmul(case15)" * doctest::test_suite("array::matmul"))
{
    auto dtype = nm::int16;
    auto M = 16;
    auto N = 1;
    auto K = 13;
    auto lhs_shape = nmtools_array{M,K};
    auto rhs_shape = nmtools_array{K,N};
    auto lhs = unwrap(na::reshape(na::arange(M*K,dtype),lhs_shape));

    auto rhs = unwrap(na::reshape(na::arange(K*N,dtype),rhs_shape));
    SYCL_TEST(matmul,lhs,rhs);
}

// TODO: fix opencl kernel compilation on pocl
TEST_CASE("matmul(case1)" * doctest::test_suite("array::matmul"))
{
    auto dtype = nm::int8;
    auto M = 4;
    auto N = 4;
    auto K = 4;
    auto lhs_shape = nmtools_array{M,K};
    auto rhs_shape = nmtools_array{K,N};
    auto lhs = unwrap(na::reshape(na::arange(M*K,dtype),lhs_shape));
    
    auto rhs = unwrap(na::reshape(na::arange(K*N,dtype),rhs_shape));
    SYCL_TEST(matmul,lhs,rhs);
}

// TODO: fix opencl kernel compilation on pocl
TEST_CASE("matmul(case1b)" * doctest::test_suite("array::matmul"))
{
    auto dtype = nm::int8;
    auto M = 4;
    auto N = 4;
    auto K = 5;
    auto lhs_shape = nmtools_array{M,K};
    auto rhs_shape = nmtools_array{K,N};
    auto lhs = unwrap(na::reshape(na::arange(M*K,dtype),lhs_shape));

    auto rhs = unwrap(na::reshape(na::arange(K*N,dtype),rhs_shape));
    SYCL_TEST(matmul,lhs,rhs);
}

// TODO: fix opencl kernel compilation on pocl
TEST_CASE("matmul(case1b)" * doctest::test_suite("array::matmul"))
{
    auto dtype = nm::int8;
    auto M = 2;
    auto N = 2;
    auto K = 5;
    auto lhs_shape = nmtools_array{M,K};
    auto rhs_shape = nmtools_array{K,N};
    auto lhs = unwrap(na::reshape(na::arange(M*K,dtype),lhs_shape));
    
    auto rhs = unwrap(na::reshape(na::arange(K*N,dtype),rhs_shape));
    SYCL_TEST(matmul,lhs,rhs);
}

// TODO: fix opencl kernel compilation on pocl
TEST_CASE("matmul(case1c)" * doctest::test_suite("array::matmul"))
{
    auto dtype = nm::int8;
    auto M = 4;
    auto N = 4;
    auto K = 6;
    auto lhs_shape = nmtools_array{M,K};
    auto rhs_shape = nmtools_array{K,N};
    auto lhs = unwrap(na::reshape(na::arange(M*K,dtype),lhs_shape));
    
    auto rhs = unwrap(na::reshape(na::arange(K*N,dtype),rhs_shape));
    SYCL_TEST(matmul,lhs,rhs);
}

// TODO: fix opencl kernel compilation on pocl
TEST_CASE("matmul(case1d)" * doctest::test_suite("array::matmul"))
{
    auto dtype = nm::int8;
    auto M = 4;
    auto N = 4;
    auto K = 7;
    auto lhs_shape = nmtools_array{M,K};
    auto rhs_shape = nmtools_array{K,N};
    auto lhs = unwrap(na::reshape(na::arange(M*K,dtype),lhs_shape));
    
    auto rhs = unwrap(na::reshape(na::arange(K*N,dtype),rhs_shape));
    SYCL_TEST(matmul,lhs,rhs);
}

// TODO: fix opencl kernel compilation on pocl
TEST_CASE("matmul(case1e)" * doctest::test_suite("array::matmul"))
{
    auto dtype = nm::int8;
    auto M = 4;
    auto N = 4;
    auto K = 8;
    auto lhs_shape = nmtools_array{M,K};
    auto rhs_shape = nmtools_array{K,N};
    auto lhs = unwrap(na::reshape(na::arange(M*K,dtype),lhs_shape));
    
    auto rhs = unwrap(na::reshape(na::arange(K*N,dtype),rhs_shape));
    SYCL_TEST(matmul,lhs,rhs);
}

// TODO: fix opencl kernel compilation on pocl
TEST_CASE("matmul(case2)" * doctest::test_suite("array::matmul"))
{
    auto dtype = nm::int8;
    auto M = 16;
    auto N = 16;
    auto K = 5;
    auto lhs_shape = nmtools_array{M,K};
    auto rhs_shape = nmtools_array{K,N};
    auto lhs = unwrap(na::reshape(na::arange(M*K,dtype),lhs_shape));
    
    auto rhs = unwrap(na::reshape(na::arange(K*N,dtype),rhs_shape));
    SYCL_TEST(matmul,lhs,rhs);
}

// TODO: fix opencl kernel compilation on pocl
TEST_CASE("matmul(case3)" * doctest::test_suite("array::matmul"))
{
    auto dtype = nm::int8;
    auto M = 16;
    auto N = 16;
    auto K = 7;
    auto lhs_shape = nmtools_array{M,K};
    auto rhs_shape = nmtools_array{K,N};
    auto lhs = unwrap(na::reshape(na::arange(M*K,dtype),lhs_shape));
    
    auto rhs = unwrap(na::reshape(na::arange(K*N,dtype),rhs_shape));
    SYCL_TEST(matmul,lhs,rhs);
}

// TODO: fix opencl kernel compilation on pocl
TEST_CASE("matmul(case4)" * doctest::test_suite("array::matmul"))
{
    auto dtype = nm::int8;
    auto M = 16;
    auto N = 16;
    auto K = 8;
    auto lhs_shape = nmtools_array{M,K};
    auto rhs_shape = nmtools_array{K,N};
    auto lhs = unwrap(na::reshape(na::arange(M*K,dtype),lhs_shape));
   
    auto rhs = unwrap(na::reshape(na::arange(K*N,dtype),rhs_shape));
    SYCL_TEST(matmul,lhs,rhs);
}

// TODO: fix opencl kernel compilation on pocl
TEST_CASE("matmul(case5)" * doctest::test_suite("array::matmul"))
{
    auto dtype = nm::int8;
    auto M = 16;
    auto N = 16;
    auto K = 9;
    auto lhs_shape = nmtools_array{M,K};
    auto rhs_shape = nmtools_array{K,N};
    auto lhs = unwrap(na::reshape(na::arange(M*K,dtype),lhs_shape));
    
    auto rhs = unwrap(na::reshape(na::arange(K*N,dtype),rhs_shape));
    SYCL_TEST(matmul,lhs,rhs);
}

// TODO: fix opencl kernel compilation on pocl
TEST_CASE("matmul(case6)" * doctest::test_suite("array::matmul"))
{
    auto dtype = nm::int8;
    auto M = 16;
    auto N = 16;
    auto K = 10;
    auto lhs_shape = nmtools_array{M,K};
    auto rhs_shape = nmtools_array{K,N};
    auto lhs = unwrap(na::reshape(na::arange(M*K,dtype),lhs_shape));

    auto rhs = unwrap(na::reshape(na::arange(K*N,dtype),rhs_shape));
    SYCL_TEST(matmul,lhs,rhs);
}

// TODO: fix opencl kernel compilation on pocl
TEST_CASE("matmul(case7)" * doctest::test_suite("array::matmul"))
{
    auto dtype = nm::int8;
    auto M = 16;
    auto N = 16;
    auto K = 11;
    auto lhs_shape = nmtools_array{M,K};
    auto rhs_shape = nmtools_array{K,N};
    auto lhs = unwrap(na::reshape(na::arange(M*K,dtype),lhs_shape));
    
    auto rhs = unwrap(na::reshape(na::arange(K*N,dtype),rhs_shape));
    SYCL_TEST(matmul,lhs,rhs);
}

// TODO: fix opencl kernel compilation on pocl
TEST_CASE("matmul(case8)" * doctest::test_suite("array::matmul"))
{
    auto dtype = nm::int8;
    auto M = 16;
    auto N = 16;
    auto K = 12;
    auto lhs_shape = nmtools_array{M,K};
    auto rhs_shape = nmtools_array{K,N};
    auto lhs = unwrap(na::reshape(na::arange(M*K,dtype),lhs_shape));

    auto rhs = unwrap(na::reshape(na::arange(K*N,dtype),rhs_shape));
    SYCL_TEST(matmul,lhs,rhs);
}

// TODO: fix opencl kernel compilation on pocl
TEST_CASE("matmul(case9)" * doctest::test_suite("array::matmul"))
{
    auto dtype = nm::int8;
    auto M = 16;
    auto N = 16;
    auto K = 13;
    auto lhs_shape = nmtools_array{M,K};
    auto rhs_shape = nmtools_array{K,N};
    auto lhs = unwrap(na::reshape(na::arange(M*K,dtype),lhs_shape));

    auto rhs = unwrap(na::reshape(na::arange(K*N,dtype),rhs_shape));
    SYCL_TEST(matmul,lhs,rhs);
}

// TODO: fix opencl kernel compilation on pocl
TEST_CASE("matmul(case10)" * doctest::test_suite("array::matmul"))
{
    auto dtype = nm::int8;
    auto M = 16;
    auto N = 19;
    auto K = 12;
    auto lhs_shape = nmtools_array{M,K};
    auto rhs_shape = nmtools_array{K,N};
    auto lhs = unwrap(na::reshape(na::arange(M*K,dtype),lhs_shape));

    auto rhs = unwrap(na::reshape(na::arange(K*N,dtype),rhs_shape));
    SYCL_TEST(matmul,lhs,rhs);
}

// TODO: fix opencl kernel compilation on pocl
TEST_CASE("matmul(case11)" * doctest::test_suite("array::matmul"))
{
    auto dtype = nm::int8;
    auto M = 16;
    auto N = 19;
    auto K = 13;
    auto lhs_shape = nmtools_array{M,K};
    auto rhs_shape = nmtools_array{K,N};
    auto lhs = unwrap(na::reshape(na::arange(M*K,dtype),lhs_shape));

    auto rhs = unwrap(na::reshape(na::arange(K*N,dtype),rhs_shape));
    SYCL_TEST(matmul,lhs,rhs);
}

// TODO: fix opencl kernel compilation on pocl
TEST_CASE("matmul(case12)" * doctest::test_suite("array::matmul"))
{
    auto dtype = nm::int8;
    auto M = 16;
    auto N = 19;
    auto K = 14;
    auto lhs_shape = nmtools_array{M,K};
    auto rhs_shape = nmtools_array{K,N};
    auto lhs = unwrap(na::reshape(na::arange(M*K,dtype),lhs_shape));

    auto rhs = unwrap(na::reshape(na::arange(K*N,dtype),rhs_shape));
    SYCL_TEST(matmul,lhs,rhs);
}

// TODO: fix opencl kernel compilation on pocl
TEST_CASE("matmul(case13)" * doctest::test_suite("array::matmul"))
{
    auto dtype = nm::int8;
    auto M = 16;
    auto N = 19;
    auto K = 15;
    auto lhs_shape = nmtools_array{M,K};
    auto rhs_shape = nmtools_array{K,N};
    auto lhs = unwrap(na::reshape(na::arange(M*K,dtype),lhs_shape));

    auto rhs = unwrap(na::reshape(na::arange(K*N,dtype),rhs_shape));
    SYCL_TEST(matmul,lhs,rhs);
}

// TODO: fix opencl kernel compilation on pocl
TEST_CASE("matmul(case14)" * doctest::test_suite("array::matmul"))
{
    auto dtype = nm::int8;
    auto M = 1;
    auto N = 19;
    auto K = 12;
    auto lhs_shape = nmtools_array{M,K};
    auto rhs_shape = nmtools_array{K,N};
    auto lhs = unwrap(na::reshape(na::arange(M*K,dtype),lhs_shape));

    auto rhs = unwrap(na::reshape(na::arange(K*N,dtype),rhs_shape));
    SYCL_TEST(matmul,lhs,rhs);
}

// TODO: fix opencl kernel compilation on pocl
TEST_CASE("matmul(case15)" * doctest::test_suite("array::matmul"))
{
    auto dtype = nm::int8;
    auto M = 16;
    auto N = 1;
    auto K = 13;
    auto lhs_shape = nmtools_array{M,K};
    auto rhs_shape = nmtools_array{K,N};
    auto lhs = unwrap(na::reshape(na::arange(M*K,dtype),lhs_shape));

    auto rhs = unwrap(na::reshape(na::arange(K*N,dtype),rhs_shape));
    SYCL_TEST(matmul,lhs,rhs);
}