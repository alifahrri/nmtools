#include "nmtools/array/eval/simd/vector_256.hpp"
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

#define VECTOR_256_TEST(fn,...) \
{ \
    auto expect = na::fn(__VA_ARGS__); \
    auto result = na::fn(__VA_ARGS__,simd::vector_256); \
    SIMD_TEST_EQUAL(result,expect); \
}

/*********************** add ******************************/

TEST_CASE("add.outer_2d(case1a)" * doctest::test_suite("simd::vector_256"))
{
    auto M = 2;
    auto N = 4;
    auto K = 5;
    auto new_shape = nmtools_array{M,N};
    auto lhs = na::reshape(na::arange(M*N),new_shape);
    auto rhs = na::arange(K);
    VECTOR_256_TEST(add.outer,lhs,rhs,nm::None);
}

TEST_CASE("add.outer_2d(case1b)" * doctest::test_suite("simd::vector_256"))
{
    auto M = 12;
    auto N = 14;
    auto K = 5;
    auto new_shape = nmtools_array{M,N};
    auto lhs = na::reshape(na::arange(M*N),new_shape);
    auto rhs = na::arange(K);
    VECTOR_256_TEST(add.outer,lhs,rhs,nm::None);
}

TEST_CASE("add.outer_2d(case1c)" * doctest::test_suite("simd::vector_256"))
{
    auto M = 12;
    auto N = 14;
    auto K = 9;
    auto new_shape = nmtools_array{M,N};
    auto lhs = na::reshape(na::arange(M*N),new_shape);
    auto rhs = na::arange(K);
    VECTOR_256_TEST(add.outer,lhs,rhs,nm::None);
}

TEST_CASE("add.outer_2d(case1d)" * doctest::test_suite("simd::vector_256"))
{
    auto M = 12;
    auto N = 14;
    auto K = 13;
    auto new_shape = nmtools_array{M,N};
    auto lhs = na::reshape(na::arange(M*N),new_shape);
    auto rhs = na::arange(K);
    VECTOR_256_TEST(add.outer,lhs,rhs,nm::None);
}

TEST_CASE("add.outer_2d(case2a)" * doctest::test_suite("simd::vector_256"))
{
    auto M = 2;
    auto N = 4;
    auto K = 6;
    auto new_shape = nmtools_array{M,N};
    auto lhs = na::reshape(na::arange(M*N),new_shape);
    auto rhs = na::arange(K);
    VECTOR_256_TEST(add.outer,lhs,rhs,nm::None);
}

TEST_CASE("add.outer_2d(case2b)" * doctest::test_suite("simd::vector_256"))
{
    auto M = 12;
    auto N = 14;
    auto K = 6;
    auto new_shape = nmtools_array{M,N};
    auto lhs = na::reshape(na::arange(M*N),new_shape);
    auto rhs = na::arange(K);
    VECTOR_256_TEST(add.outer,lhs,rhs,nm::None);
}

TEST_CASE("add.outer_2d(case2c)" * doctest::test_suite("simd::vector_256"))
{
    auto M = 12;
    auto N = 14;
    auto K = 10;
    auto new_shape = nmtools_array{M,N};
    auto lhs = na::reshape(na::arange(M*N),new_shape);
    auto rhs = na::arange(K);
    VECTOR_256_TEST(add.outer,lhs,rhs,nm::None);
}

TEST_CASE("add.outer_2d(case2d)" * doctest::test_suite("simd::vector_256"))
{
    auto M = 12;
    auto N = 14;
    auto K = 14;
    auto new_shape = nmtools_array{M,N};
    auto lhs = na::reshape(na::arange(M*N),new_shape);
    auto rhs = na::arange(K);
    VECTOR_256_TEST(add.outer,lhs,rhs,nm::None);
}

TEST_CASE("add.outer_2d(case2e)" * doctest::test_suite("simd::vector_256"))
{
    auto M = 2;
    auto N = 4;
    auto K = 18;
    auto new_shape = nmtools_array{M,N};
    auto lhs = na::reshape(na::arange(M*N),new_shape);
    auto rhs = na::arange(K);
    VECTOR_256_TEST(add.outer,lhs,rhs,nm::None);
}

TEST_CASE("add.outer_2d(case3a)" * doctest::test_suite("simd::vector_256"))
{
    auto M = 2;
    auto N = 4;
    auto K = 7;
    auto new_shape = nmtools_array{M,N};
    auto lhs = na::reshape(na::arange(M*N),new_shape);
    auto rhs = na::arange(K);
    VECTOR_256_TEST(add.outer,lhs,rhs,nm::None);
}

TEST_CASE("add.outer_2d(case3b)" * doctest::test_suite("simd::vector_256"))
{
    auto M = 12;
    auto N = 14;
    auto K = 7;
    auto new_shape = nmtools_array{M,N};
    auto lhs = na::reshape(na::arange(M*N),new_shape);
    auto rhs = na::arange(K);
    VECTOR_256_TEST(add.outer,lhs,rhs,nm::None);
}

TEST_CASE("add.outer_2d(case3c)" * doctest::test_suite("simd::vector_256"))
{
    auto M = 12;
    auto N = 14;
    auto K = 11;
    auto new_shape = nmtools_array{M,N};
    auto lhs = na::reshape(na::arange(M*N),new_shape);
    auto rhs = na::arange(K);
    VECTOR_256_TEST(add.outer,lhs,rhs,nm::None);
}

TEST_CASE("add.outer_2d(case3d)" * doctest::test_suite("simd::vector_256"))
{
    auto M = 2;
    auto N = 4;
    auto K = 14;
    auto new_shape = nmtools_array{M,N};
    auto lhs = na::reshape(na::arange(M*N),new_shape);
    auto rhs = na::arange(K);
    VECTOR_256_TEST(add.outer,lhs,rhs,nm::None);
}

TEST_CASE("add.outer_2d(case4a)" * doctest::test_suite("simd::vector_256"))
{
    auto dtype = nm::float64;
    auto M = 2;
    auto N = 4;
    auto K = 5;
    auto new_shape = nmtools_array{M,N};
    auto lhs = na::reshape(na::arange(M*N,dtype),new_shape);
    auto rhs = na::arange(K,dtype);
    VECTOR_256_TEST(add.outer,lhs,rhs,nm::None);
}

TEST_CASE("add.outer_2d(case4b)" * doctest::test_suite("simd::vector_256"))
{
    auto dtype = nm::float64;
    auto M = 12;
    auto N = 14;
    auto K = 5;
    auto new_shape = nmtools_array{M,N};
    auto lhs = na::reshape(na::arange(M*N,dtype),new_shape);
    auto rhs = na::arange(K,dtype);
    VECTOR_256_TEST(add.outer,lhs,rhs,nm::None);
}

TEST_CASE("add.outer_2d(case4c)" * doctest::test_suite("simd::vector_256"))
{
    auto dtype = nm::float64;
    auto M = 12;
    auto N = 14;
    auto K = 9;
    auto new_shape = nmtools_array{M,N};
    auto lhs = na::reshape(na::arange(M*N,dtype),new_shape);
    auto rhs = na::arange(K,dtype);
    VECTOR_256_TEST(add.outer,lhs,rhs,nm::None);
}

TEST_CASE("add.outer_2d(case4d)" * doctest::test_suite("simd::vector_256"))
{
    auto dtype = nm::float64;
    auto M = 12;
    auto N = 14;
    auto K = 13;
    auto new_shape = nmtools_array{M,N};
    auto lhs = na::reshape(na::arange(M*N,dtype),new_shape);
    auto rhs = na::arange(K,dtype);
    VECTOR_256_TEST(add.outer,lhs,rhs,nm::None);
}

TEST_CASE("add.outer_2d(case5a)" * doctest::test_suite("simd::vector_256"))
{
    auto dtype = nm::float64;
    auto M = 2;
    auto N = 4;
    auto K = 6;
    auto new_shape = nmtools_array{M,N};
    auto lhs = na::reshape(na::arange(M*N,dtype),new_shape);
    auto rhs = na::arange(K,dtype);
    VECTOR_256_TEST(add.outer,lhs,rhs,nm::None);
}

TEST_CASE("add.outer_2d(case5b)" * doctest::test_suite("simd::vector_256"))
{
    auto dtype = nm::float64;
    auto M = 12;
    auto N = 14;
    auto K = 6;
    auto new_shape = nmtools_array{M,N};
    auto lhs = na::reshape(na::arange(M*N,dtype),new_shape);
    auto rhs = na::arange(K,dtype);
    VECTOR_256_TEST(add.outer,lhs,rhs,nm::None);
}

TEST_CASE("add.outer_2d(case5c)" * doctest::test_suite("simd::vector_256"))
{
    auto dtype = nm::float64;
    auto M = 12;
    auto N = 14;
    auto K = 10;
    auto new_shape = nmtools_array{M,N};
    auto lhs = na::reshape(na::arange(M*N,dtype),new_shape);
    auto rhs = na::arange(K,dtype);
    VECTOR_256_TEST(add.outer,lhs,rhs,nm::None);
}

TEST_CASE("add.outer_2d(case5d)" * doctest::test_suite("simd::vector_256"))
{
    auto dtype = nm::float64;
    auto M = 12;
    auto N = 14;
    auto K = 14;
    auto new_shape = nmtools_array{M,N};
    auto lhs = na::reshape(na::arange(M*N,dtype),new_shape);
    auto rhs = na::arange(K,dtype);
    VECTOR_256_TEST(add.outer,lhs,rhs,nm::None);
}

TEST_CASE("add.outer_2d(case5e)" * doctest::test_suite("simd::vector_256"))
{
    auto dtype = nm::float64;
    auto M = 2;
    auto N = 4;
    auto K = 18;
    auto new_shape = nmtools_array{M,N};
    auto lhs = na::reshape(na::arange(M*N,dtype),new_shape);
    auto rhs = na::arange(K,dtype);
    VECTOR_256_TEST(add.outer,lhs,rhs,nm::None);
}

TEST_CASE("add.outer_2d(case6a)" * doctest::test_suite("simd::vector_256"))
{
    auto dtype = nm::float64;
    auto M = 2;
    auto N = 4;
    auto K = 7;
    auto new_shape = nmtools_array{M,N};
    auto lhs = na::reshape(na::arange(M*N,dtype),new_shape);
    auto rhs = na::arange(K,dtype);
    VECTOR_256_TEST(add.outer,lhs,rhs,nm::None);
}

TEST_CASE("add.outer_2d(case6b)" * doctest::test_suite("simd::vector_256"))
{
    auto dtype = nm::float64;
    auto M = 12;
    auto N = 14;
    auto K = 7;
    auto new_shape = nmtools_array{M,N};
    auto lhs = na::reshape(na::arange(M*N,dtype),new_shape);
    auto rhs = na::arange(K,dtype);
    VECTOR_256_TEST(add.outer,lhs,rhs,nm::None);
}

TEST_CASE("add.outer_2d(case6c)" * doctest::test_suite("simd::vector_256"))
{
    auto dtype = nm::float64;
    auto M = 12;
    auto N = 14;
    auto K = 11;
    auto new_shape = nmtools_array{M,N};
    auto lhs = na::reshape(na::arange(M*N,dtype),new_shape);
    auto rhs = na::arange(K,dtype);
    VECTOR_256_TEST(add.outer,lhs,rhs,nm::None);
}

TEST_CASE("add.outer_2d(case6d)" * doctest::test_suite("simd::vector_256"))
{
    auto dtype = nm::float64;
    auto M = 2;
    auto N = 4;
    auto K = 14;
    auto new_shape = nmtools_array{M,N};
    auto lhs = na::reshape(na::arange(M*N,dtype),new_shape);
    auto rhs = na::arange(K,dtype);
    VECTOR_256_TEST(add.outer,lhs,rhs,nm::None);
}

TEST_CASE("add.outer_2d(case7a)" * doctest::test_suite("simd::vector_256"))
{
    auto dtype = nm::int32;
    auto M = 2;
    auto N = 4;
    auto K = 5;
    auto new_shape = nmtools_array{M,N};
    auto lhs = na::reshape(na::arange(M*N,dtype),new_shape);
    auto rhs = na::arange(K,dtype);
    VECTOR_256_TEST(add.outer,lhs,rhs,nm::None);
}

TEST_CASE("add.outer_2d(case7b)" * doctest::test_suite("simd::vector_256"))
{
    auto dtype = nm::int32;
    auto M = 12;
    auto N = 14;
    auto K = 5;
    auto new_shape = nmtools_array{M,N};
    auto lhs = na::reshape(na::arange(M*N,dtype),new_shape);
    auto rhs = na::arange(K,dtype);
    VECTOR_256_TEST(add.outer,lhs,rhs,nm::None);
}

TEST_CASE("add.outer_2d(case7c)" * doctest::test_suite("simd::vector_256"))
{
    auto dtype = nm::int32;
    auto M = 12;
    auto N = 14;
    auto K = 9;
    auto new_shape = nmtools_array{M,N};
    auto lhs = na::reshape(na::arange(M*N,dtype),new_shape);
    auto rhs = na::arange(K,dtype);
    VECTOR_256_TEST(add.outer,lhs,rhs,nm::None);
}

TEST_CASE("add.outer_2d(case7d)" * doctest::test_suite("simd::vector_256"))
{
    auto dtype = nm::int32;
    auto M = 12;
    auto N = 14;
    auto K = 13;
    auto new_shape = nmtools_array{M,N};
    auto lhs = na::reshape(na::arange(M*N,dtype),new_shape);
    auto rhs = na::arange(K,dtype);
    VECTOR_256_TEST(add.outer,lhs,rhs,nm::None);
}

TEST_CASE("add.outer_2d(case8a)" * doctest::test_suite("simd::vector_256"))
{
    auto dtype = nm::int32;
    auto M = 2;
    auto N = 4;
    auto K = 6;
    auto new_shape = nmtools_array{M,N};
    auto lhs = na::reshape(na::arange(M*N,dtype),new_shape);
    auto rhs = na::arange(K,dtype);
    VECTOR_256_TEST(add.outer,lhs,rhs,nm::None);
}

TEST_CASE("add.outer_2d(case8b)" * doctest::test_suite("simd::vector_256"))
{
    auto dtype = nm::int32;
    auto M = 12;
    auto N = 14;
    auto K = 6;
    auto new_shape = nmtools_array{M,N};
    auto lhs = na::reshape(na::arange(M*N,dtype),new_shape);
    auto rhs = na::arange(K,dtype);
    VECTOR_256_TEST(add.outer,lhs,rhs,nm::None);
}

TEST_CASE("add.outer_2d(case8c)" * doctest::test_suite("simd::vector_256"))
{
    auto dtype = nm::int32;
    auto M = 12;
    auto N = 14;
    auto K = 10;
    auto new_shape = nmtools_array{M,N};
    auto lhs = na::reshape(na::arange(M*N,dtype),new_shape);
    auto rhs = na::arange(K,dtype);
    VECTOR_256_TEST(add.outer,lhs,rhs,nm::None);
}

TEST_CASE("add.outer_2d(case8e)" * doctest::test_suite("simd::vector_256"))
{
    auto dtype = nm::int32;
    auto M = 2;
    auto N = 4;
    auto K = 18;
    auto new_shape = nmtools_array{M,N};
    auto lhs = na::reshape(na::arange(M*N,dtype),new_shape);
    auto rhs = na::arange(K,dtype);
    VECTOR_256_TEST(add.outer,lhs,rhs,nm::None);
}

TEST_CASE("add.outer_2d(case9a)" * doctest::test_suite("simd::vector_256"))
{
    auto dtype = nm::int32;
    auto M = 2;
    auto N = 4;
    auto K = 7;
    auto new_shape = nmtools_array{M,N};
    auto lhs = na::reshape(na::arange(M*N,dtype),new_shape);
    auto rhs = na::arange(K,dtype);
    VECTOR_256_TEST(add.outer,lhs,rhs,nm::None);
}

TEST_CASE("add.outer_2d(case9b)" * doctest::test_suite("simd::vector_256"))
{
    auto dtype = nm::int32;
    auto M = 12;
    auto N = 14;
    auto K = 7;
    auto new_shape = nmtools_array{M,N};
    auto lhs = na::reshape(na::arange(M*N,dtype),new_shape);
    auto rhs = na::arange(K,dtype);
    VECTOR_256_TEST(add.outer,lhs,rhs,nm::None);
}

TEST_CASE("add.outer_2d(case9c)" * doctest::test_suite("simd::vector_256"))
{
    auto dtype = nm::int32;
    auto M = 12;
    auto N = 14;
    auto K = 11;
    auto new_shape = nmtools_array{M,N};
    auto lhs = na::reshape(na::arange(M*N,dtype),new_shape);
    auto rhs = na::arange(K,dtype);
    VECTOR_256_TEST(add.outer,lhs,rhs,nm::None);
}

TEST_CASE("add.outer_2d(case10a)" * doctest::test_suite("simd::vector_256"))
{
    auto dtype = nm::int64;
    auto M = 2;
    auto N = 4;
    auto K = 5;
    auto new_shape = nmtools_array{M,N};
    auto lhs = na::reshape(na::arange(M*N,dtype),new_shape);
    auto rhs = na::arange(K,dtype);
    VECTOR_256_TEST(add.outer,lhs,rhs,nm::None);
}

TEST_CASE("add.outer_2d(case10b)" * doctest::test_suite("simd::vector_256"))
{
    auto dtype = nm::int64;
    auto M = 12;
    auto N = 14;
    auto K = 5;
    auto new_shape = nmtools_array{M,N};
    auto lhs = na::reshape(na::arange(M*N,dtype),new_shape);
    auto rhs = na::arange(K,dtype);
    VECTOR_256_TEST(add.outer,lhs,rhs,nm::None);
}

TEST_CASE("add.outer_2d(case10c)" * doctest::test_suite("simd::vector_256"))
{
    auto dtype = nm::int64;
    auto M = 12;
    auto N = 14;
    auto K = 9;
    auto new_shape = nmtools_array{M,N};
    auto lhs = na::reshape(na::arange(M*N,dtype),new_shape);
    auto rhs = na::arange(K,dtype);
    VECTOR_256_TEST(add.outer,lhs,rhs,nm::None);
}

TEST_CASE("add.outer_2d(case11a)" * doctest::test_suite("simd::vector_256"))
{
    auto dtype = nm::int64;
    auto M = 2;
    auto N = 4;
    auto K = 6;
    auto new_shape = nmtools_array{M,N};
    auto lhs = na::reshape(na::arange(M*N,dtype),new_shape);
    auto rhs = na::arange(K,dtype);
    VECTOR_256_TEST(add.outer,lhs,rhs,nm::None);
}

TEST_CASE("add.outer_2d(case11b)" * doctest::test_suite("simd::vector_256"))
{
    auto dtype = nm::int64;
    auto M = 12;
    auto N = 14;
    auto K = 6;
    auto new_shape = nmtools_array{M,N};
    auto lhs = na::reshape(na::arange(M*N,dtype),new_shape);
    auto rhs = na::arange(K,dtype);
    VECTOR_256_TEST(add.outer,lhs,rhs,nm::None);
}

TEST_CASE("add.outer_2d(case11c)" * doctest::test_suite("simd::vector_256"))
{
    auto dtype = nm::int64;
    auto M = 12;
    auto N = 14;
    auto K = 10;
    auto new_shape = nmtools_array{M,N};
    auto lhs = na::reshape(na::arange(M*N,dtype),new_shape);
    auto rhs = na::arange(K,dtype);
    VECTOR_256_TEST(add.outer,lhs,rhs,nm::None);
}

TEST_CASE("add.outer_2d(case11e)" * doctest::test_suite("simd::vector_256"))
{
    auto dtype = nm::int64;
    auto M = 2;
    auto N = 4;
    auto K = 18;
    auto new_shape = nmtools_array{M,N};
    auto lhs = na::reshape(na::arange(M*N,dtype),new_shape);
    auto rhs = na::arange(K,dtype);
    VECTOR_256_TEST(add.outer,lhs,rhs,nm::None);
}

TEST_CASE("add.outer_2d(case12a)" * doctest::test_suite("simd::vector_256"))
{
    auto dtype = nm::int64;
    auto M = 2;
    auto N = 4;
    auto K = 7;
    auto new_shape = nmtools_array{M,N};
    auto lhs = na::reshape(na::arange(M*N,dtype),new_shape);
    auto rhs = na::arange(K,dtype);
    VECTOR_256_TEST(add.outer,lhs,rhs,nm::None);
}

TEST_CASE("add.outer_2d(case12b)" * doctest::test_suite("simd::vector_256"))
{
    auto dtype = nm::int64;
    auto M = 12;
    auto N = 14;
    auto K = 7;
    auto new_shape = nmtools_array{M,N};
    auto lhs = na::reshape(na::arange(M*N,dtype),new_shape);
    auto rhs = na::arange(K,dtype);
    VECTOR_256_TEST(add.outer,lhs,rhs,nm::None);
}

TEST_CASE("add.outer_2d(case12c)" * doctest::test_suite("simd::vector_256"))
{
    auto dtype = nm::int64;
    auto M = 12;
    auto N = 14;
    auto K = 11;
    auto new_shape = nmtools_array{M,N};
    auto lhs = na::reshape(na::arange(M*N,dtype),new_shape);
    auto rhs = na::arange(K,dtype);
    VECTOR_256_TEST(add.outer,lhs,rhs,nm::None);
}

TEST_CASE("add.outer_2d(case12d)" * doctest::test_suite("simd::vector_256"))
{
    auto dtype = nm::int64;
    auto M = 2;
    auto N = 4;
    auto K = 14;
    auto new_shape = nmtools_array{M,N};
    auto lhs = na::reshape(na::arange(M*N,dtype),new_shape);
    auto rhs = na::arange(K,dtype);
    VECTOR_256_TEST(add.outer,lhs,rhs,nm::None);
}

// TODO: fix int8 add outer
#if 0
TEST_CASE("add.outer_2d(case13a)" * doctest::test_suite("simd::vector_256"))
{
    auto dtype = nm::int8;
    auto M = 2;
    auto N = 4;
    auto K = 5;
    auto new_shape = nmtools_array{M,N};
    auto lhs = na::reshape(na::arange(M*N,dtype),new_shape);
    auto rhs = na::arange(K,dtype);
    VECTOR_256_TEST(add.outer,lhs,rhs,nm::None);
}

TEST_CASE("add.outer_2d(case13b)" * doctest::test_suite("simd::vector_256"))
{
    auto dtype = nm::int8;
    auto M = 12;
    auto N = 14;
    auto K = 5;
    auto new_shape = nmtools_array{M,N};
    auto lhs = na::reshape(na::arange(M*N,dtype),new_shape);
    auto rhs = na::arange(K,dtype);
    VECTOR_256_TEST(add.outer,lhs,rhs,nm::None);
}

TEST_CASE("add.outer_2d(case13c)" * doctest::test_suite("simd::vector_256"))
{
    auto dtype = nm::int8;
    auto M = 12;
    auto N = 14;
    auto K = 9;
    auto new_shape = nmtools_array{M,N};
    auto lhs = na::reshape(na::arange(M*N,dtype),new_shape);
    auto rhs = na::arange(K,dtype);
    VECTOR_256_TEST(add.outer,lhs,rhs,nm::None);
}

TEST_CASE("add.outer_2d(case14a)" * doctest::test_suite("simd::vector_256"))
{
    auto dtype = nm::int8;
    auto M = 2;
    auto N = 4;
    auto K = 6;
    auto new_shape = nmtools_array{M,N};
    auto lhs = na::reshape(na::arange(M*N,dtype),new_shape);
    auto rhs = na::arange(K,dtype);
    VECTOR_256_TEST(add.outer,lhs,rhs,nm::None);
}

TEST_CASE("add.outer_2d(case14b)" * doctest::test_suite("simd::vector_256"))
{
    auto dtype = nm::int8;
    auto M = 12;
    auto N = 14;
    auto K = 6;
    auto new_shape = nmtools_array{M,N};
    auto lhs = na::reshape(na::arange(M*N,dtype),new_shape);
    auto rhs = na::arange(K,dtype);
    VECTOR_256_TEST(add.outer,lhs,rhs,nm::None);
}

TEST_CASE("add.outer_2d(case14c)" * doctest::test_suite("simd::vector_256"))
{
    auto dtype = nm::int8;
    auto M = 12;
    auto N = 14;
    auto K = 10;
    auto new_shape = nmtools_array{M,N};
    auto lhs = na::reshape(na::arange(M*N,dtype),new_shape);
    auto rhs = na::arange(K,dtype);
    VECTOR_256_TEST(add.outer,lhs,rhs,nm::None);
}

TEST_CASE("add.outer_2d(case14e)" * doctest::test_suite("simd::vector_256"))
{
    auto dtype = nm::int8;
    auto M = 2;
    auto N = 4;
    auto K = 18;
    auto new_shape = nmtools_array{M,N};
    auto lhs = na::reshape(na::arange(M*N,dtype),new_shape);
    auto rhs = na::arange(K,dtype);
    VECTOR_256_TEST(add.outer,lhs,rhs,nm::None);
}

TEST_CASE("add.outer_2d(case15a)" * doctest::test_suite("simd::vector_256"))
{
    auto dtype = nm::int8;
    auto M = 2;
    auto N = 4;
    auto K = 7;
    auto new_shape = nmtools_array{M,N};
    auto lhs = na::reshape(na::arange(M*N,dtype),new_shape);
    auto rhs = na::arange(K,dtype);
    VECTOR_256_TEST(add.outer,lhs,rhs,nm::None);
}

TEST_CASE("add.outer_2d(case15b)" * doctest::test_suite("simd::vector_256"))
{
    auto dtype = nm::int8;
    auto M = 12;
    auto N = 14;
    auto K = 7;
    auto new_shape = nmtools_array{M,N};
    auto lhs = na::reshape(na::arange(M*N,dtype),new_shape);
    auto rhs = na::arange(K,dtype);
    VECTOR_256_TEST(add.outer,lhs,rhs,nm::None);
}

TEST_CASE("add.outer_2d(case15c)" * doctest::test_suite("simd::vector_256"))
{
    auto dtype = nm::int8;
    auto M = 12;
    auto N = 14;
    auto K = 11;
    auto new_shape = nmtools_array{M,N};
    auto lhs = na::reshape(na::arange(M*N,dtype),new_shape);
    auto rhs = na::arange(K,dtype);
    VECTOR_256_TEST(add.outer,lhs,rhs,nm::None);
}

TEST_CASE("add.outer_2d(case15d)" * doctest::test_suite("simd::vector_256"))
{
    auto dtype = nm::int8;
    auto M = 2;
    auto N = 4;
    auto K = 14;
    auto new_shape = nmtools_array{M,N};
    auto lhs = na::reshape(na::arange(M*N,dtype),new_shape);
    auto rhs = na::arange(K,dtype);
    VECTOR_256_TEST(add.outer,lhs,rhs,nm::None);
}
#endif

TEST_CASE("add.outer_2d(case16a)" * doctest::test_suite("simd::vector_256"))
{
    auto M = 2;
    auto N = 4;
    auto O = 5;
    auto P = 6;
    auto lhs_shape = nmtools_array{M,N};
    auto rhs_shape = nmtools_array{O,P};
    auto lhs = na::reshape(na::arange(M*N),lhs_shape);
    auto rhs = na::reshape(na::arange(O*P),rhs_shape);
    VECTOR_256_TEST(add.outer,lhs,rhs,nm::None);
}

TEST_CASE("add.outer_2d(case16b)" * doctest::test_suite("simd::vector_256"))
{
    auto M = 12;
    auto N = 14;
    auto O = 5;
    auto P = 6;
    auto lhs_shape = nmtools_array{M,N};
    auto rhs_shape = nmtools_array{O,P};
    auto lhs = na::reshape(na::arange(M*N),lhs_shape);
    auto rhs = na::reshape(na::arange(O*P),rhs_shape);
    VECTOR_256_TEST(add.outer,lhs,rhs,nm::None);
}

TEST_CASE("add.outer_2d(case16c)" * doctest::test_suite("simd::vector_256"))
{
    auto M = 12;
    auto N = 14;
    auto O = 5;
    auto P = 7;
    auto lhs_shape = nmtools_array{M,N};
    auto rhs_shape = nmtools_array{O,P};
    auto lhs = na::reshape(na::arange(M*N),lhs_shape);
    auto rhs = na::reshape(na::arange(O*P),rhs_shape);
    VECTOR_256_TEST(add.outer,lhs,rhs,nm::None);
}

TEST_CASE("add.outer_2d(case16d)" * doctest::test_suite("simd::vector_256"))
{
    auto M = 12;
    auto N = 14;
    auto O = 5;
    auto P = 8;
    auto lhs_shape = nmtools_array{M,N};
    auto rhs_shape = nmtools_array{O,P};
    auto lhs = na::reshape(na::arange(M*N),lhs_shape);
    auto rhs = na::reshape(na::arange(O*P),rhs_shape);
    VECTOR_256_TEST(add.outer,lhs,rhs,nm::None);
}

TEST_CASE("add.outer_2d(case17a)" * doctest::test_suite("simd::vector_256"))
{
    auto dtype = nm::int32;
    auto M = 2;
    auto N = 4;
    auto O = 5;
    auto P = 6;
    auto lhs_shape = nmtools_array{M,N};
    auto rhs_shape = nmtools_array{O,P};
    auto lhs = na::reshape(na::arange(M*N,dtype),lhs_shape);
    auto rhs = na::reshape(na::arange(O*P,dtype),rhs_shape);
    VECTOR_256_TEST(add.outer,lhs,rhs,nm::None);
}

TEST_CASE("add.outer_2d(case17b)" * doctest::test_suite("simd::vector_256"))
{
    auto dtype = nm::int32;
    auto M = 12;
    auto N = 14;
    auto O = 5;
    auto P = 7;
    auto lhs_shape = nmtools_array{M,N};
    auto rhs_shape = nmtools_array{O,P};
    auto lhs = na::reshape(na::arange(M*N,dtype),lhs_shape);
    auto rhs = na::reshape(na::arange(O*P,dtype),rhs_shape);
    VECTOR_256_TEST(add.outer,lhs,rhs,nm::None);
}