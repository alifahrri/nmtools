#include "nmtools/array/evaluator/simd/simde_avx512.hpp"
#include "nmtools/array/array/arange.hpp"
#include "nmtools/array/array/reshape.hpp"
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

#define SIMDE_AVX512_TEST(array,fn,...) \
{ \
    auto expect = na::fn(array,##__VA_ARGS__); \
    auto result = na::fn(array,##__VA_ARGS__,simd::simde_AVX512); \
    SIMD_TEST_EQUAL(result,expect); \
}

/*********************** add ******************************/

TEST_CASE("broadcast_add(case1)" * doctest::test_suite("simd::simde_AVX512"))
{
    auto lhs_a = na::arange(128);
    auto rhs_a = na::arange(128);
    auto lhs_shape = nmtools_array{128,1};
    auto rhs_shape = nmtools_array{128,1};
    auto lhs = na::reshape(lhs_a,lhs_shape);
    auto rhs = na::reshape(rhs_a,rhs_shape);
    SIMDE_AVX512_TEST(lhs,add,rhs);
}

TEST_CASE("broadcast_add(case2)" * doctest::test_suite("simd::simde_AVX512"))
{
    auto n_item = 32;
    auto lhs_a = na::arange(n_item);
    auto rhs_a = na::arange(n_item);
    auto lhs_shape = nmtools_array{n_item,1};
    auto rhs_shape = nmtools_array{1,n_item};
    auto lhs = na::reshape(lhs_a,lhs_shape);
    auto rhs = na::reshape(rhs_a,rhs_shape);
    SIMDE_AVX512_TEST(lhs,add,rhs);
}

TEST_CASE("broadcast_add(case3)" * doctest::test_suite("simd::simde_AVX512"))
{
    auto n_item = 32;
    auto lhs_a = na::arange(n_item);
    auto rhs_a = na::arange(n_item);
    auto lhs_shape = nmtools_array{1,n_item};
    auto rhs_shape = nmtools_array{n_item,1};
    auto lhs = na::reshape(lhs_a,lhs_shape);
    auto rhs = na::reshape(rhs_a,rhs_shape);
    SIMDE_AVX512_TEST(lhs,add,rhs);
}

TEST_CASE("broadcast_add(case4)" * doctest::test_suite("simd::simde_AVX512"))
{
    auto n_item = 12;
    auto lhs_a = na::arange(n_item);
    auto rhs_a = na::arange(n_item);
    auto lhs_shape = nmtools_array{n_item/3,3};
    auto rhs_shape = nmtools_array{n_item/3,3};
    auto lhs = na::reshape(lhs_a,lhs_shape);
    auto rhs = na::reshape(rhs_a,rhs_shape);
    SIMDE_AVX512_TEST(lhs,add,rhs);
}

TEST_CASE("broadcast_add(case5)" * doctest::test_suite("simd::simde_AVX512"))
{
    auto n_item = 12;
    auto lhs_a = na::arange(n_item);
    auto rhs_a = na::arange(n_item);
    auto lhs_shape = nmtools_array{3,n_item/3};
    auto rhs_shape = nmtools_array{3,n_item/3};
    auto lhs = na::reshape(lhs_a,lhs_shape);
    auto rhs = na::reshape(rhs_a,rhs_shape);
    SIMDE_AVX512_TEST(lhs,add,rhs);
}

TEST_CASE("broadcast_add(case6)" * doctest::test_suite("simd::simde_AVX512"))
{
    auto n_item = 5;
    auto lhs_a = na::arange(n_item);
    auto rhs_a = na::arange(n_item);
    auto lhs_shape = nmtools_array{n_item,1};
    auto rhs_shape = nmtools_array{1,n_item};
    auto lhs = na::reshape(lhs_a,lhs_shape);
    auto rhs = na::reshape(rhs_a,rhs_shape);
    SIMDE_AVX512_TEST(lhs,add,rhs);
}

TEST_CASE("broadcast_add(case7)" * doctest::test_suite("simd::simde_AVX512"))
{
    auto n_item = 5;
    auto lhs_a = na::arange(n_item);
    auto rhs_a = na::arange(n_item);
    auto lhs_shape = nmtools_array{1,n_item};
    auto rhs_shape = nmtools_array{n_item,1};
    auto lhs = na::reshape(lhs_a,lhs_shape);
    auto rhs = na::reshape(rhs_a,rhs_shape);
    SIMDE_AVX512_TEST(lhs,add,rhs);
}

TEST_CASE("broadcast_add(case8)" * doctest::test_suite("simd::simde_AVX512"))
{
    auto n_item = 9;
    auto lhs_a = na::arange(n_item);
    auto rhs_a = na::arange(n_item);
    auto lhs_shape = nmtools_array{n_item,1};
    auto rhs_shape = nmtools_array{1,n_item};
    auto lhs = na::reshape(lhs_a,lhs_shape);
    auto rhs = na::reshape(rhs_a,rhs_shape);
    SIMDE_AVX512_TEST(lhs,add,rhs);
}

TEST_CASE("broadcast_add(case9)" * doctest::test_suite("simd::simde_AVX512"))
{
    auto n_item = 9;
    auto lhs_a = na::arange(n_item);
    auto rhs_a = na::arange(n_item);
    auto lhs_shape = nmtools_array{1,n_item};
    auto rhs_shape = nmtools_array{n_item,1};
    auto lhs = na::reshape(lhs_a,lhs_shape);
    auto rhs = na::reshape(rhs_a,rhs_shape);
    SIMDE_AVX512_TEST(lhs,add,rhs);
}

TEST_CASE("broadcast_add(case10)" * doctest::test_suite("simd::simde_AVX512"))
{
    auto lhs_a = na::arange(9 * 3);
    auto rhs_a = na::arange(3);
    auto lhs_shape = nmtools_array{3,9};
    auto rhs_shape = nmtools_array{3,1};
    auto lhs = na::reshape(lhs_a,lhs_shape);
    auto rhs = na::reshape(rhs_a,rhs_shape);
    SIMDE_AVX512_TEST(lhs,add,rhs);
}

TEST_CASE("broadcast_add(case11)" * doctest::test_suite("simd::simde_AVX512"))
{
    auto lhs_a = na::arange(9 * 3);
    auto rhs_a = na::arange(3);
    auto lhs_shape = nmtools_array{9,3};
    auto rhs_shape = nmtools_array{1,3};
    auto lhs = na::reshape(lhs_a,lhs_shape);
    auto rhs = na::reshape(rhs_a,rhs_shape);
    SIMDE_AVX512_TEST(lhs,add,rhs);
}

TEST_CASE("broadcast_add(case12)" * doctest::test_suite("simd::simde_AVX512"))
{
    auto lhs_a = na::arange(10 * 3);
    auto rhs_a = na::arange(3);
    auto lhs_shape = nmtools_array{3,10};
    auto rhs_shape = nmtools_array{3,1};
    auto lhs = na::reshape(lhs_a,lhs_shape);
    auto rhs = na::reshape(rhs_a,rhs_shape);
    SIMDE_AVX512_TEST(lhs,add,rhs);
}

TEST_CASE("broadcast_add(case13)" * doctest::test_suite("simd::simde_AVX512"))
{
    auto lhs_a = na::arange(10 * 3);
    auto rhs_a = na::arange(3);
    auto lhs_shape = nmtools_array{10,3};
    auto rhs_shape = nmtools_array{1,3};
    auto lhs = na::reshape(lhs_a,lhs_shape);
    auto rhs = na::reshape(rhs_a,rhs_shape);
    SIMDE_AVX512_TEST(lhs,add,rhs);
}