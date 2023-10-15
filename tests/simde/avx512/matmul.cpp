#include "nmtools/array/eval/simd/simde_avx512.hpp"
#include "nmtools/array/array/matmul.hpp"
#include "nmtools/array/array/copy.hpp"
#include "nmtools/array/array/reshape.hpp"
#include "nmtools/array/array/arange.hpp"
#include "nmtools/array/ndarray.hpp"
#include "nmtools/testing/doctest.hpp"

namespace nm = nmtools;
namespace na = nmtools::array;
namespace simd = na::simd;
namespace meta = nm::meta;

using buffer_t = nmtools_list<float>;
using shape_t  = nmtools_array<size_t,2>;
using output_t = na::column_major_ndarray_t<buffer_t,shape_t>;

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

TEST_CASE("matmul(case1)" * doctest::test_suite("matmul::simde_AVX512"))
{
    auto M = 4;
    auto N = 4;
    auto K = 4;
    auto lhs_shape = nmtools_array{M,K};
    auto rhs_shape = nmtools_array{K,N};
    auto lhs = na::reshape(na::arange(M*K),lhs_shape);
    
    auto output = meta::as_value_v<output_t>;
    auto rhs    = na::reshape(na::arange(K*N),rhs_shape,nm::None,output);
    SIMDE_AVX512_TEST(matmul,lhs,rhs);
}

TEST_CASE("matmul(case1b)" * doctest::test_suite("matmul::simde_AVX512"))
{
    auto M = 4;
    auto N = 4;
    auto K = 5;
    auto lhs_shape = nmtools_array{M,K};
    auto rhs_shape = nmtools_array{K,N};
    auto lhs = na::reshape(na::arange(M*K),lhs_shape);

    auto output = meta::as_value_v<output_t>;
    auto rhs    = na::reshape(na::arange(K*N),rhs_shape,nm::None,output);
    SIMDE_AVX512_TEST(matmul,lhs,rhs);
}

TEST_CASE("matmul(case1b)" * doctest::test_suite("matmul::simde_AVX512"))
{
    auto M = 2;
    auto N = 2;
    auto K = 5;
    auto lhs_shape = nmtools_array{M,K};
    auto rhs_shape = nmtools_array{K,N};
    auto lhs = na::reshape(na::arange(M*K),lhs_shape);
    
    auto output = meta::as_value_v<output_t>;
    auto rhs    = na::reshape(na::arange(K*N),rhs_shape,nm::None,output);
    SIMDE_AVX512_TEST(matmul,lhs,rhs);
}

TEST_CASE("matmul(case1c)" * doctest::test_suite("matmul::simde_AVX512"))
{
    auto M = 4;
    auto N = 4;
    auto K = 6;
    auto lhs_shape = nmtools_array{M,K};
    auto rhs_shape = nmtools_array{K,N};
    auto lhs = na::reshape(na::arange(M*K),lhs_shape);
    
    auto output = meta::as_value_v<output_t>;
    auto rhs    = na::reshape(na::arange(K*N),rhs_shape,nm::None,output);
    SIMDE_AVX512_TEST(matmul,lhs,rhs);
}

TEST_CASE("matmul(case1d)" * doctest::test_suite("matmul::simde_AVX512"))
{
    auto M = 4;
    auto N = 4;
    auto K = 7;
    auto lhs_shape = nmtools_array{M,K};
    auto rhs_shape = nmtools_array{K,N};
    auto lhs = na::reshape(na::arange(M*K),lhs_shape);
    
    auto output = meta::as_value_v<output_t>;
    auto rhs    = na::reshape(na::arange(K*N),rhs_shape,nm::None,output);
    SIMDE_AVX512_TEST(matmul,lhs,rhs);
}

TEST_CASE("matmul(case1e)" * doctest::test_suite("matmul::simde_AVX512"))
{
    auto M = 4;
    auto N = 4;
    auto K = 8;
    auto lhs_shape = nmtools_array{M,K};
    auto rhs_shape = nmtools_array{K,N};
    auto lhs = na::reshape(na::arange(M*K),lhs_shape);
    
    auto output = meta::as_value_v<output_t>;
    auto rhs    = na::reshape(na::arange(K*N),rhs_shape,nm::None,output);
    SIMDE_AVX512_TEST(matmul,lhs,rhs);
}

TEST_CASE("matmul(case2)" * doctest::test_suite("matmul::simde_AVX512"))
{
    auto M = 16;
    auto N = 16;
    auto K = 5;
    auto lhs_shape = nmtools_array{M,K};
    auto rhs_shape = nmtools_array{K,N};
    auto lhs = na::reshape(na::arange(M*K),lhs_shape);
    
    auto output = meta::as_value_v<output_t>;
    auto rhs    = na::reshape(na::arange(K*N),rhs_shape,nm::None,output);
    SIMDE_AVX512_TEST(matmul,lhs,rhs);
}

TEST_CASE("matmul(case3)" * doctest::test_suite("matmul::simde_AVX512"))
{
    auto M = 16;
    auto N = 16;
    auto K = 7;
    auto lhs_shape = nmtools_array{M,K};
    auto rhs_shape = nmtools_array{K,N};
    auto lhs = na::reshape(na::arange(M*K),lhs_shape);
    
    auto output = meta::as_value_v<output_t>;
    auto rhs    = na::reshape(na::arange(K*N),rhs_shape,nm::None,output);
    SIMDE_AVX512_TEST(matmul,lhs,rhs);
}

TEST_CASE("matmul(case4)" * doctest::test_suite("matmul::simde_AVX512"))
{
    auto M = 16;
    auto N = 16;
    auto K = 8;
    auto lhs_shape = nmtools_array{M,K};
    auto rhs_shape = nmtools_array{K,N};
    auto lhs = na::reshape(na::arange(M*K),lhs_shape);
   
    auto output = meta::as_value_v<output_t>;
    auto rhs    = na::reshape(na::arange(K*N),rhs_shape,nm::None,output);
    SIMDE_AVX512_TEST(matmul,lhs,rhs);
}

TEST_CASE("matmul(case5)" * doctest::test_suite("matmul::simde_AVX512"))
{
    auto M = 16;
    auto N = 16;
    auto K = 9;
    auto lhs_shape = nmtools_array{M,K};
    auto rhs_shape = nmtools_array{K,N};
    auto lhs = na::reshape(na::arange(M*K),lhs_shape);
    
    auto output = meta::as_value_v<output_t>;
    auto rhs    = na::reshape(na::arange(K*N),rhs_shape,nm::None,output);
    SIMDE_AVX512_TEST(matmul,lhs,rhs);
}

TEST_CASE("matmul(case6)" * doctest::test_suite("matmul::simde_AVX512"))
{
    auto M = 16;
    auto N = 16;
    auto K = 10;
    auto lhs_shape = nmtools_array{M,K};
    auto rhs_shape = nmtools_array{K,N};
    auto lhs = na::reshape(na::arange(M*K),lhs_shape);

    auto output = meta::as_value_v<output_t>;
    auto rhs    = na::reshape(na::arange(K*N),rhs_shape,nm::None,output);
    SIMDE_AVX512_TEST(matmul,lhs,rhs);
}

TEST_CASE("matmul(case7)" * doctest::test_suite("matmul::simde_AVX512"))
{
    auto M = 16;
    auto N = 16;
    auto K = 11;
    auto lhs_shape = nmtools_array{M,K};
    auto rhs_shape = nmtools_array{K,N};
    auto lhs = na::reshape(na::arange(M*K),lhs_shape);
    
    auto output = meta::as_value_v<output_t>;
    auto rhs    = na::reshape(na::arange(K*N),rhs_shape,nm::None,output);
    SIMDE_AVX512_TEST(matmul,lhs,rhs);
}

TEST_CASE("matmul(case8)" * doctest::test_suite("matmul::simde_AVX512"))
{
    auto M = 16;
    auto N = 16;
    auto K = 12;
    auto lhs_shape = nmtools_array{M,K};
    auto rhs_shape = nmtools_array{K,N};
    auto lhs = na::reshape(na::arange(M*K),lhs_shape);

    auto output = meta::as_value_v<output_t>;
    auto rhs    = na::reshape(na::arange(K*N),rhs_shape,nm::None,output);
    SIMDE_AVX512_TEST(matmul,lhs,rhs);
}

TEST_CASE("matmul(case9)" * doctest::test_suite("matmul::simde_AVX512"))
{
    auto M = 16;
    auto N = 16;
    auto K = 13;
    auto lhs_shape = nmtools_array{M,K};
    auto rhs_shape = nmtools_array{K,N};
    auto lhs = na::reshape(na::arange(M*K),lhs_shape);

    auto output = meta::as_value_v<output_t>;
    auto rhs    = na::reshape(na::arange(K*N),rhs_shape,nm::None,output);
    SIMDE_AVX512_TEST(matmul,lhs,rhs);
}

TEST_CASE("matmul(case10)" * doctest::test_suite("matmul::simde_AVX512"))
{
    auto M = 16;
    auto N = 19;
    auto K = 12;
    auto lhs_shape = nmtools_array{M,K};
    auto rhs_shape = nmtools_array{K,N};
    auto lhs = na::reshape(na::arange(M*K),lhs_shape);

    auto output = meta::as_value_v<output_t>;
    auto rhs    = na::reshape(na::arange(K*N),rhs_shape,nm::None,output);
    SIMDE_AVX512_TEST(matmul,lhs,rhs);
}

TEST_CASE("matmul(case11)" * doctest::test_suite("matmul::simde_AVX512"))
{
    auto M = 16;
    auto N = 19;
    auto K = 13;
    auto lhs_shape = nmtools_array{M,K};
    auto rhs_shape = nmtools_array{K,N};
    auto lhs = na::reshape(na::arange(M*K),lhs_shape);

    auto output = meta::as_value_v<output_t>;
    auto rhs    = na::reshape(na::arange(K*N),rhs_shape,nm::None,output);
    SIMDE_AVX512_TEST(matmul,lhs,rhs);
}

TEST_CASE("matmul(case12)" * doctest::test_suite("matmul::simde_AVX512"))
{
    auto M = 16;
    auto N = 19;
    auto K = 14;
    auto lhs_shape = nmtools_array{M,K};
    auto rhs_shape = nmtools_array{K,N};
    auto lhs = na::reshape(na::arange(M*K),lhs_shape);

    auto output = meta::as_value_v<output_t>;
    auto rhs    = na::reshape(na::arange(K*N),rhs_shape,nm::None,output);
    SIMDE_AVX512_TEST(matmul,lhs,rhs);
}

TEST_CASE("matmul(case13)" * doctest::test_suite("matmul::simde_AVX512"))
{
    auto M = 16;
    auto N = 19;
    auto K = 15;
    auto lhs_shape = nmtools_array{M,K};
    auto rhs_shape = nmtools_array{K,N};
    auto lhs = na::reshape(na::arange(M*K),lhs_shape);

    auto output = meta::as_value_v<output_t>;
    auto rhs    = na::reshape(na::arange(K*N),rhs_shape,nm::None,output);
    SIMDE_AVX512_TEST(matmul,lhs,rhs);
}

TEST_CASE("matmul(case14)" * doctest::test_suite("matmul::simde_AVX512"))
{
    auto M = 1;
    auto N = 19;
    auto K = 12;
    auto lhs_shape = nmtools_array{M,K};
    auto rhs_shape = nmtools_array{K,N};
    auto lhs = na::reshape(na::arange(M*K),lhs_shape);

    auto output = meta::as_value_v<output_t>;
    auto rhs    = na::reshape(na::arange(K*N),rhs_shape,nm::None,output);
    SIMDE_AVX512_TEST(matmul,lhs,rhs);
}

TEST_CASE("matmul(case15)" * doctest::test_suite("matmul::simde_AVX512"))
{
    auto M = 16;
    auto N = 1;
    auto K = 13;
    auto lhs_shape = nmtools_array{M,K};
    auto rhs_shape = nmtools_array{K,N};
    auto lhs = na::reshape(na::arange(M*K),lhs_shape);

    auto output = meta::as_value_v<output_t>;
    auto rhs    = na::reshape(na::arange(K*N),rhs_shape,nm::None,output);
    SIMDE_AVX512_TEST(matmul,lhs,rhs);
}

TEST_CASE("matmul(case16)" * doctest::test_suite("matmul::simde_AVX512"))
{
    auto M = 16;
    auto N = 16;
    auto K = 1;
    auto lhs_shape = nmtools_array{M,K};
    auto rhs_shape = nmtools_array{K,N};
    auto lhs = na::reshape(na::arange(M*K),lhs_shape);

    auto output = meta::as_value_v<output_t>;
    auto rhs    = na::reshape(na::arange(K*N),rhs_shape,nm::None,output);
    SIMDE_AVX512_TEST(matmul,lhs,rhs);
}


TEST_CASE("matmul(case17)" * doctest::test_suite("matmul::simde_AVX512"))
{
    auto M = 16;
    auto N = 16;
    auto K = 2;
    auto lhs_shape = nmtools_array{M,K};
    auto rhs_shape = nmtools_array{K,N};
    auto lhs = na::reshape(na::arange(M*K),lhs_shape);

    auto output = meta::as_value_v<output_t>;
    auto rhs    = na::reshape(na::arange(K*N),rhs_shape,nm::None,output);
    SIMDE_AVX512_TEST(matmul,lhs,rhs);
}


TEST_CASE("matmul(case18)" * doctest::test_suite("matmul::simde_AVX512"))
{
    auto M = 16;
    auto N = 16;
    auto K = 3;
    auto lhs_shape = nmtools_array{M,K};
    auto rhs_shape = nmtools_array{K,N};
    auto lhs = na::reshape(na::arange(M*K),lhs_shape);

    auto output = meta::as_value_v<output_t>;
    auto rhs    = na::reshape(na::arange(K*N),rhs_shape,nm::None,output);
    SIMDE_AVX512_TEST(matmul,lhs,rhs);
}


TEST_CASE("matmul(case17)" * doctest::test_suite("matmul::simde_AVX512"))
{
    auto M = 16;
    auto N = 16;
    auto K = 4;
    auto lhs_shape = nmtools_array{M,K};
    auto rhs_shape = nmtools_array{K,N};
    auto lhs = na::reshape(na::arange(M*K),lhs_shape);

    auto output = meta::as_value_v<output_t>;
    auto rhs    = na::reshape(na::arange(K*N),rhs_shape,nm::None,output);
    SIMDE_AVX512_TEST(matmul,lhs,rhs);
}


TEST_CASE("matmul(case18)" * doctest::test_suite("matmul::simde_AVX512"))
{
    auto M = 16;
    auto N = 16;
    auto K = 5;
    auto lhs_shape = nmtools_array{M,K};
    auto rhs_shape = nmtools_array{K,N};
    auto lhs = na::reshape(na::arange(M*K),lhs_shape);

    auto output = meta::as_value_v<output_t>;
    auto rhs    = na::reshape(na::arange(K*N),rhs_shape,nm::None,output);
    SIMDE_AVX512_TEST(matmul,lhs,rhs);
}


TEST_CASE("matmul(case19)" * doctest::test_suite("matmul::simde_AVX512"))
{
    auto M = 16;
    auto N = 16;
    auto K = 6;
    auto lhs_shape = nmtools_array{M,K};
    auto rhs_shape = nmtools_array{K,N};
    auto lhs = na::reshape(na::arange(M*K),lhs_shape);

    auto output = meta::as_value_v<output_t>;
    auto rhs    = na::reshape(na::arange(K*N),rhs_shape,nm::None,output);
    SIMDE_AVX512_TEST(matmul,lhs,rhs);
}


TEST_CASE("matmul(case20)" * doctest::test_suite("matmul::simde_AVX512"))
{
    auto M = 16;
    auto N = 16;
    auto K = 7;
    auto lhs_shape = nmtools_array{M,K};
    auto rhs_shape = nmtools_array{K,N};
    auto lhs = na::reshape(na::arange(M*K),lhs_shape);

    auto output = meta::as_value_v<output_t>;
    auto rhs    = na::reshape(na::arange(K*N),rhs_shape,nm::None,output);
    SIMDE_AVX512_TEST(matmul,lhs,rhs);
}

TEST_CASE("matmul(case21)" * doctest::test_suite("matmul::simde_AVX512"))
{
    auto M = 16;
    auto N = 16;
    auto K = 8;
    auto lhs_shape = nmtools_array{M,K};
    auto rhs_shape = nmtools_array{K,N};
    auto lhs = na::reshape(na::arange(M*K),lhs_shape);

    auto output = meta::as_value_v<output_t>;
    auto rhs    = na::reshape(na::arange(K*N),rhs_shape,nm::None,output);
    SIMDE_AVX512_TEST(matmul,lhs,rhs);
}

TEST_CASE("matmul(case22)" * doctest::test_suite("matmul::simde_AVX512"))
{
    auto M = 16;
    auto N = 16;
    auto K = 9;
    auto lhs_shape = nmtools_array{M,K};
    auto rhs_shape = nmtools_array{K,N};
    auto lhs = na::reshape(na::arange(M*K),lhs_shape);

    auto output = meta::as_value_v<output_t>;
    auto rhs    = na::reshape(na::arange(K*N),rhs_shape,nm::None,output);
    SIMDE_AVX512_TEST(matmul,lhs,rhs);
}

TEST_CASE("matmul(case23)" * doctest::test_suite("matmul::simde_AVX512"))
{
    auto M = 16;
    auto N = 16;
    auto K = 10;
    auto lhs_shape = nmtools_array{M,K};
    auto rhs_shape = nmtools_array{K,N};
    auto lhs = na::reshape(na::arange(M*K),lhs_shape);

    auto output = meta::as_value_v<output_t>;
    auto rhs    = na::reshape(na::arange(K*N),rhs_shape,nm::None,output);
    SIMDE_AVX512_TEST(matmul,lhs,rhs);
}

TEST_CASE("matmul(case24)" * doctest::test_suite("matmul::simde_AVX512"))
{
    auto M = 16;
    auto N = 16;
    auto K = 11;
    auto lhs_shape = nmtools_array{M,K};
    auto rhs_shape = nmtools_array{K,N};
    auto lhs = na::reshape(na::arange(M*K),lhs_shape);

    auto output = meta::as_value_v<output_t>;
    auto rhs    = na::reshape(na::arange(K*N),rhs_shape,nm::None,output);
    SIMDE_AVX512_TEST(matmul,lhs,rhs);
}

TEST_CASE("matmul(case25)" * doctest::test_suite("matmul::simde_AVX512"))
{
    auto M = 16;
    auto N = 16;
    auto K = 12;
    auto lhs_shape = nmtools_array{M,K};
    auto rhs_shape = nmtools_array{K,N};
    auto lhs = na::reshape(na::arange(M*K),lhs_shape);

    auto output = meta::as_value_v<output_t>;
    auto rhs    = na::reshape(na::arange(K*N),rhs_shape,nm::None,output);
    SIMDE_AVX512_TEST(matmul,lhs,rhs);
}

TEST_CASE("matmul(case26)" * doctest::test_suite("matmul::simde_AVX512"))
{
    auto M = 16;
    auto N = 16;
    auto K = 13;
    auto lhs_shape = nmtools_array{M,K};
    auto rhs_shape = nmtools_array{K,N};
    auto lhs = na::reshape(na::arange(M*K),lhs_shape);

    auto output = meta::as_value_v<output_t>;
    auto rhs    = na::reshape(na::arange(K*N),rhs_shape,nm::None,output);
    SIMDE_AVX512_TEST(matmul,lhs,rhs);
}

TEST_CASE("matmul(case27)" * doctest::test_suite("matmul::simde_AVX512"))
{
    auto M = 16;
    auto N = 16;
    auto K = 14;
    auto lhs_shape = nmtools_array{M,K};
    auto rhs_shape = nmtools_array{K,N};
    auto lhs = na::reshape(na::arange(M*K),lhs_shape);

    auto output = meta::as_value_v<output_t>;
    auto rhs    = na::reshape(na::arange(K*N),rhs_shape,nm::None,output);
    SIMDE_AVX512_TEST(matmul,lhs,rhs);
}

TEST_CASE("matmul(case28)" * doctest::test_suite("matmul::simde_AVX512"))
{
    auto M = 16;
    auto N = 16;
    auto K = 15;
    auto lhs_shape = nmtools_array{M,K};
    auto rhs_shape = nmtools_array{K,N};
    auto lhs = na::reshape(na::arange(M*K),lhs_shape);

    auto output = meta::as_value_v<output_t>;
    auto rhs    = na::reshape(na::arange(K*N),rhs_shape,nm::None,output);
    SIMDE_AVX512_TEST(matmul,lhs,rhs);
}

TEST_CASE("matmul(case29)" * doctest::test_suite("matmul::simde_AVX512"))
{
    auto M = 16;
    auto N = 16;
    auto K = 16;
    auto lhs_shape = nmtools_array{M,K};
    auto rhs_shape = nmtools_array{K,N};
    auto lhs = na::reshape(na::arange(M*K),lhs_shape);

    auto output = meta::as_value_v<output_t>;
    auto rhs    = na::reshape(na::arange(K*N),rhs_shape,nm::None,output);
    SIMDE_AVX512_TEST(matmul,lhs,rhs);
}

TEST_CASE("matmul(case30)" * doctest::test_suite("matmul::simde_AVX512"))
{
    auto M = 16;
    auto N = 16;
    auto K = 17;
    auto lhs_shape = nmtools_array{M,K};
    auto rhs_shape = nmtools_array{K,N};
    auto lhs = na::reshape(na::arange(M*K),lhs_shape);

    auto output = meta::as_value_v<output_t>;
    auto rhs    = na::reshape(na::arange(K*N),rhs_shape,nm::None,output);
    SIMDE_AVX512_TEST(matmul,lhs,rhs);
}

TEST_CASE("matmul(case31)" * doctest::test_suite("matmul::simde_AVX512"))
{
    auto M = 16;
    auto N = 16;
    auto K = 18;
    auto lhs_shape = nmtools_array{M,K};
    auto rhs_shape = nmtools_array{K,N};
    auto lhs = na::reshape(na::arange(M*K),lhs_shape);

    auto output = meta::as_value_v<output_t>;
    auto rhs    = na::reshape(na::arange(K*N),rhs_shape,nm::None,output);
    SIMDE_AVX512_TEST(matmul,lhs,rhs);
}

TEST_CASE("matmul(case32)" * doctest::test_suite("matmul::simde_AVX512"))
{
    auto M = 16;
    auto N = 16;
    auto K = 32;
    auto lhs_shape = nmtools_array{M,K};
    auto rhs_shape = nmtools_array{K,N};
    auto lhs = na::reshape(na::arange(M*K),lhs_shape);

    auto output = meta::as_value_v<output_t>;
    auto rhs    = na::reshape(na::arange(K*N),rhs_shape,nm::None,output);
    SIMDE_AVX512_TEST(matmul,lhs,rhs);
}

TEST_CASE("matmul(case33)" * doctest::test_suite("matmul::simde_AVX512"))
{
    auto M = 16;
    auto N = 16;
    auto K = 33;
    auto lhs_shape = nmtools_array{M,K};
    auto rhs_shape = nmtools_array{K,N};
    auto lhs = na::reshape(na::arange(M*K),lhs_shape);

    auto output = meta::as_value_v<output_t>;
    auto rhs    = na::reshape(na::arange(K*N),rhs_shape,nm::None,output);
    SIMDE_AVX512_TEST(matmul,lhs,rhs);
}