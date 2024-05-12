// disable array log ini this file because array too big
#define NMTOOLS_CHECK_MESSAGE(result,message) \
{ \
    CHECK(result); \
}

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
namespace meta = nm::meta;

// TODO: do not explicitly unwrap, fix eval
using nmtools::unwrap;

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

TEST_CASE("add.reduce_nd(case1a)" * doctest::test_suite("simd::vector_256"))
{
    auto axis = meta::ct_v<0>;
    auto new_shape = nmtools_array{2,2,5};
    auto input     = na::reshape(na::arange(ix::product(new_shape)),new_shape);
    auto dtype     = nm::None;
    auto initial   = nm::None;
    {
        auto keepdims = nm::True;
        VECTOR_256_TEST(add.reduce,unwrap(input),axis,dtype,initial,keepdims);
    }
    {
        auto keepdims = nm::False;
        VECTOR_256_TEST(add.reduce,unwrap(input),axis,dtype,initial,keepdims);
    }
    {
        auto keepdims = true;
        VECTOR_256_TEST(add.reduce,unwrap(input),axis,dtype,initial,keepdims);
    }
    {
        auto keepdims = false;
        VECTOR_256_TEST(add.reduce,unwrap(input),axis,dtype,initial,keepdims);
    }
}

TEST_CASE("add.reduce_nd(case1b)" * doctest::test_suite("simd::vector_256"))
{
    auto axis = meta::ct_v<1>;
    auto new_shape = nmtools_array{2,2,5};
    auto input     = na::reshape(na::arange(ix::product(new_shape)),new_shape);
    auto dtype     = nm::None;
    auto initial   = nm::None;
    {
        auto keepdims = nm::True;
        VECTOR_256_TEST(add.reduce,unwrap(input),axis,dtype,initial,keepdims);
    }
    {
        auto keepdims = nm::False;
        VECTOR_256_TEST(add.reduce,unwrap(input),axis,dtype,initial,keepdims);
    }
    {
        auto keepdims = true;
        VECTOR_256_TEST(add.reduce,unwrap(input),axis,dtype,initial,keepdims);
    }
    {
        auto keepdims = false;
        VECTOR_256_TEST(add.reduce,unwrap(input),axis,dtype,initial,keepdims);
    }
}

TEST_CASE("add.reduce_nd(case1c)" * doctest::test_suite("simd::vector_256"))
{
    auto axis = meta::ct_v<2>;
    auto new_shape = nmtools_array{2,2,5};
    auto input     = na::reshape(na::arange(ix::product(new_shape)),new_shape);
    auto dtype     = nm::None;
    auto initial   = nm::None;
    {
        auto keepdims = nm::True;
        VECTOR_256_TEST(add.reduce,unwrap(input),axis,dtype,initial,keepdims);
    }
    {
        auto keepdims = nm::False;
        VECTOR_256_TEST(add.reduce,unwrap(input),axis,dtype,initial,keepdims);
    }
    {
        auto keepdims = true;
        VECTOR_256_TEST(add.reduce,unwrap(input),axis,dtype,initial,keepdims);
    }
    {
        auto keepdims = false;
        VECTOR_256_TEST(add.reduce,unwrap(input),axis,dtype,initial,keepdims);
    }
}

TEST_CASE("add.reduce_nd(case2a)" * doctest::test_suite("simd::vector_256"))
{
    auto axis = meta::ct_v<0>;
    auto new_shape = nmtools_array{2,2,6};
    auto input     = na::reshape(na::arange(ix::product(new_shape)),new_shape);
    auto dtype     = nm::None;
    auto initial   = nm::None;
    {
        auto keepdims = nm::True;
        VECTOR_256_TEST(add.reduce,unwrap(input),axis,dtype,initial,keepdims);
    }
    {
        auto keepdims = nm::False;
        VECTOR_256_TEST(add.reduce,unwrap(input),axis,dtype,initial,keepdims);
    }
    {
        auto keepdims = true;
        VECTOR_256_TEST(add.reduce,unwrap(input),axis,dtype,initial,keepdims);
    }
    {
        auto keepdims = false;
        VECTOR_256_TEST(add.reduce,unwrap(input),axis,dtype,initial,keepdims);
    }
}

TEST_CASE("add.reduce_nd(case2b)" * doctest::test_suite("simd::vector_256"))
{
    auto axis = meta::ct_v<1>;
    auto new_shape = nmtools_array{2,2,6};
    auto input     = na::reshape(na::arange(ix::product(new_shape)),new_shape);
    auto dtype     = nm::None;
    auto initial   = nm::None;
    {
        auto keepdims = nm::True;
        VECTOR_256_TEST(add.reduce,unwrap(input),axis,dtype,initial,keepdims);
    }
    {
        auto keepdims = nm::False;
        VECTOR_256_TEST(add.reduce,unwrap(input),axis,dtype,initial,keepdims);
    }
    {
        auto keepdims = true;
        VECTOR_256_TEST(add.reduce,unwrap(input),axis,dtype,initial,keepdims);
    }
    {
        auto keepdims = false;
        VECTOR_256_TEST(add.reduce,unwrap(input),axis,dtype,initial,keepdims);
    }
}

TEST_CASE("add.reduce_nd(case2c)" * doctest::test_suite("simd::vector_256"))
{
    auto axis = meta::ct_v<2>;
    auto new_shape = nmtools_array{2,2,6};
    auto input     = na::reshape(na::arange(ix::product(new_shape)),new_shape);
    auto dtype     = nm::None;
    auto initial   = nm::None;
    {
        auto keepdims = nm::True;
        VECTOR_256_TEST(add.reduce,unwrap(input),axis,dtype,initial,keepdims);
    }
    {
        auto keepdims = nm::False;
        VECTOR_256_TEST(add.reduce,unwrap(input),axis,dtype,initial,keepdims);
    }
    {
        auto keepdims = true;
        VECTOR_256_TEST(add.reduce,unwrap(input),axis,dtype,initial,keepdims);
    }
    {
        auto keepdims = false;
        VECTOR_256_TEST(add.reduce,unwrap(input),axis,dtype,initial,keepdims);
    }
}

TEST_CASE("add.reduce_nd(case3a)" * doctest::test_suite("simd::vector_256"))
{
    auto axis = meta::ct_v<0>;
    auto new_shape = nmtools_array{2,2,7};
    auto input     = na::reshape(na::arange(ix::product(new_shape)),new_shape);
    auto dtype     = nm::None;
    auto initial   = nm::None;
    {
        auto keepdims = nm::True;
        VECTOR_256_TEST(add.reduce,unwrap(input),axis,dtype,initial,keepdims);
    }
    {
        auto keepdims = nm::False;
        VECTOR_256_TEST(add.reduce,unwrap(input),axis,dtype,initial,keepdims);
    }
    {
        auto keepdims = true;
        VECTOR_256_TEST(add.reduce,unwrap(input),axis,dtype,initial,keepdims);
    }
    {
        auto keepdims = false;
        VECTOR_256_TEST(add.reduce,unwrap(input),axis,dtype,initial,keepdims);
    }
}

TEST_CASE("add.reduce_nd(case3b)" * doctest::test_suite("simd::vector_256"))
{
    auto axis = meta::ct_v<1>;
    auto new_shape = nmtools_array{2,2,7};
    auto input     = na::reshape(na::arange(ix::product(new_shape)),new_shape);
    auto dtype     = nm::None;
    auto initial   = nm::None;
    {
        auto keepdims = nm::True;
        VECTOR_256_TEST(add.reduce,unwrap(input),axis,dtype,initial,keepdims);
    }
    {
        auto keepdims = nm::False;
        VECTOR_256_TEST(add.reduce,unwrap(input),axis,dtype,initial,keepdims);
    }
    {
        auto keepdims = true;
        VECTOR_256_TEST(add.reduce,unwrap(input),axis,dtype,initial,keepdims);
    }
    {
        auto keepdims = false;
        VECTOR_256_TEST(add.reduce,unwrap(input),axis,dtype,initial,keepdims);
    }
}

TEST_CASE("add.reduce_nd(case3c)" * doctest::test_suite("simd::vector_256"))
{
    auto axis = meta::ct_v<2>;
    auto new_shape = nmtools_array{2,2,7};
    auto input     = na::reshape(na::arange(ix::product(new_shape)),new_shape);
    auto dtype     = nm::None;
    auto initial   = nm::None;
    {
        auto keepdims = nm::True;
        VECTOR_256_TEST(add.reduce,unwrap(input),axis,dtype,initial,keepdims);
    }
    {
        auto keepdims = nm::False;
        VECTOR_256_TEST(add.reduce,unwrap(input),axis,dtype,initial,keepdims);
    }
    {
        auto keepdims = true;
        VECTOR_256_TEST(add.reduce,unwrap(input),axis,dtype,initial,keepdims);
    }
    {
        auto keepdims = false;
        VECTOR_256_TEST(add.reduce,unwrap(input),axis,dtype,initial,keepdims);
    }
}

TEST_CASE("add.reduce_nd(case4a)" * doctest::test_suite("simd::vector_256"))
{
    auto axis = meta::ct_v<0>;
    auto new_shape = nmtools_array{2,2,8};
    auto input     = na::reshape(na::arange(ix::product(new_shape)),new_shape);
    auto dtype     = nm::None;
    auto initial   = nm::None;
    {
        auto keepdims = nm::True;
        VECTOR_256_TEST(add.reduce,unwrap(input),axis,dtype,initial,keepdims);
    }
    {
        auto keepdims = nm::False;
        VECTOR_256_TEST(add.reduce,unwrap(input),axis,dtype,initial,keepdims);
    }
    {
        auto keepdims = true;
        VECTOR_256_TEST(add.reduce,unwrap(input),axis,dtype,initial,keepdims);
    }
    {
        auto keepdims = false;
        VECTOR_256_TEST(add.reduce,unwrap(input),axis,dtype,initial,keepdims);
    }
}

TEST_CASE("add.reduce_nd(case4b)" * doctest::test_suite("simd::vector_256"))
{
    auto axis = meta::ct_v<1>;
    auto new_shape = nmtools_array{2,2,8};
    auto input     = na::reshape(na::arange(ix::product(new_shape)),new_shape);
    auto dtype     = nm::None;
    auto initial   = nm::None;
    {
        auto keepdims = nm::True;
        VECTOR_256_TEST(add.reduce,unwrap(input),axis,dtype,initial,keepdims);
    }
    {
        auto keepdims = nm::False;
        VECTOR_256_TEST(add.reduce,unwrap(input),axis,dtype,initial,keepdims);
    }
    {
        auto keepdims = true;
        VECTOR_256_TEST(add.reduce,unwrap(input),axis,dtype,initial,keepdims);
    }
    {
        auto keepdims = false;
        VECTOR_256_TEST(add.reduce,unwrap(input),axis,dtype,initial,keepdims);
    }
}

TEST_CASE("add.reduce_nd(case4c)" * doctest::test_suite("simd::vector_256"))
{
    auto axis = meta::ct_v<2>;
    auto new_shape = nmtools_array{2,2,8};
    auto input     = na::reshape(na::arange(ix::product(new_shape)),new_shape);
    auto dtype     = nm::None;
    auto initial   = nm::None;
    {
        auto keepdims = nm::True;
        VECTOR_256_TEST(add.reduce,unwrap(input),axis,dtype,initial,keepdims);
    }
    {
        auto keepdims = nm::False;
        VECTOR_256_TEST(add.reduce,unwrap(input),axis,dtype,initial,keepdims);
    }
    {
        auto keepdims = true;
        VECTOR_256_TEST(add.reduce,unwrap(input),axis,dtype,initial,keepdims);
    }
    {
        auto keepdims = false;
        VECTOR_256_TEST(add.reduce,unwrap(input),axis,dtype,initial,keepdims);
    }
}

/////////////////////////////////////////////////////////////////////////////////////

TEST_CASE("add.reduce_nd(case5a)" * doctest::test_suite("simd::vector_256"))
{
    auto axis = meta::ct_v<0>;
    auto new_shape = nmtools_array{3,2,5};
    auto input     = na::reshape(na::arange(ix::product(new_shape)),new_shape);
    auto dtype     = nm::None;
    auto initial   = nm::None;
    {
        auto keepdims = nm::True;
        VECTOR_256_TEST(add.reduce,unwrap(input),axis,dtype,initial,keepdims);
    }
    {
        auto keepdims = nm::False;
        VECTOR_256_TEST(add.reduce,unwrap(input),axis,dtype,initial,keepdims);
    }
    {
        auto keepdims = true;
        VECTOR_256_TEST(add.reduce,unwrap(input),axis,dtype,initial,keepdims);
    }
    {
        auto keepdims = false;
        VECTOR_256_TEST(add.reduce,unwrap(input),axis,dtype,initial,keepdims);
    }
}

TEST_CASE("add.reduce_nd(case5b)" * doctest::test_suite("simd::vector_256"))
{
    auto axis = meta::ct_v<1>;
    auto new_shape = nmtools_array{3,2,5};
    auto input     = na::reshape(na::arange(ix::product(new_shape)),new_shape);
    auto dtype     = nm::None;
    auto initial   = nm::None;
    {
        auto keepdims = nm::True;
        VECTOR_256_TEST(add.reduce,unwrap(input),axis,dtype,initial,keepdims);
    }
    {
        auto keepdims = nm::False;
        VECTOR_256_TEST(add.reduce,unwrap(input),axis,dtype,initial,keepdims);
    }
    {
        auto keepdims = true;
        VECTOR_256_TEST(add.reduce,unwrap(input),axis,dtype,initial,keepdims);
    }
    {
        auto keepdims = false;
        VECTOR_256_TEST(add.reduce,unwrap(input),axis,dtype,initial,keepdims);
    }
}

TEST_CASE("add.reduce_nd(casec)" * doctest::test_suite("simd::vector_256"))
{
    auto axis = meta::ct_v<2>;
    auto new_shape = nmtools_array{3,2,5};
    auto input     = na::reshape(na::arange(ix::product(new_shape)),new_shape);
    auto dtype     = nm::None;
    auto initial   = nm::None;
    {
        auto keepdims = nm::True;
        VECTOR_256_TEST(add.reduce,unwrap(input),axis,dtype,initial,keepdims);
    }
    {
        auto keepdims = nm::False;
        VECTOR_256_TEST(add.reduce,unwrap(input),axis,dtype,initial,keepdims);
    }
    {
        auto keepdims = true;
        VECTOR_256_TEST(add.reduce,unwrap(input),axis,dtype,initial,keepdims);
    }
    {
        auto keepdims = false;
        VECTOR_256_TEST(add.reduce,unwrap(input),axis,dtype,initial,keepdims);
    }
}

TEST_CASE("add.reduce_nd(case6a)" * doctest::test_suite("simd::vector_256"))
{
    auto axis = meta::ct_v<0>;
    auto new_shape = nmtools_array{3,2,6};
    auto input     = na::reshape(na::arange(ix::product(new_shape)),new_shape);
    auto dtype     = nm::None;
    auto initial   = nm::None;
    {
        auto keepdims = nm::True;
        VECTOR_256_TEST(add.reduce,unwrap(input),axis,dtype,initial,keepdims);
    }
    {
        auto keepdims = nm::False;
        VECTOR_256_TEST(add.reduce,unwrap(input),axis,dtype,initial,keepdims);
    }
    {
        auto keepdims = true;
        VECTOR_256_TEST(add.reduce,unwrap(input),axis,dtype,initial,keepdims);
    }
    {
        auto keepdims = false;
        VECTOR_256_TEST(add.reduce,unwrap(input),axis,dtype,initial,keepdims);
    }
}

TEST_CASE("add.reduce_nd(case6b)" * doctest::test_suite("simd::vector_256"))
{
    auto axis = meta::ct_v<1>;
    auto new_shape = nmtools_array{3,2,6};
    auto input     = na::reshape(na::arange(ix::product(new_shape)),new_shape);
    auto dtype     = nm::None;
    auto initial   = nm::None;
    {
        auto keepdims = nm::True;
        VECTOR_256_TEST(add.reduce,unwrap(input),axis,dtype,initial,keepdims);
    }
    {
        auto keepdims = nm::False;
        VECTOR_256_TEST(add.reduce,unwrap(input),axis,dtype,initial,keepdims);
    }
    {
        auto keepdims = true;
        VECTOR_256_TEST(add.reduce,unwrap(input),axis,dtype,initial,keepdims);
    }
    {
        auto keepdims = false;
        VECTOR_256_TEST(add.reduce,unwrap(input),axis,dtype,initial,keepdims);
    }
}

TEST_CASE("add.reduce_nd(case6c)" * doctest::test_suite("simd::vector_256"))
{
    auto axis = meta::ct_v<2>;
    auto new_shape = nmtools_array{3,2,6};
    auto input     = na::reshape(na::arange(ix::product(new_shape)),new_shape);
    auto dtype     = nm::None;
    auto initial   = nm::None;
    {
        auto keepdims = nm::True;
        VECTOR_256_TEST(add.reduce,unwrap(input),axis,dtype,initial,keepdims);
    }
    {
        auto keepdims = nm::False;
        VECTOR_256_TEST(add.reduce,unwrap(input),axis,dtype,initial,keepdims);
    }
    {
        auto keepdims = true;
        VECTOR_256_TEST(add.reduce,unwrap(input),axis,dtype,initial,keepdims);
    }
    {
        auto keepdims = false;
        VECTOR_256_TEST(add.reduce,unwrap(input),axis,dtype,initial,keepdims);
    }
}

TEST_CASE("add.reduce_nd(case7a)" * doctest::test_suite("simd::vector_256"))
{
    auto axis = meta::ct_v<0>;
    auto new_shape = nmtools_array{3,2,7};
    auto input     = na::reshape(na::arange(ix::product(new_shape)),new_shape);
    auto dtype     = nm::None;
    auto initial   = nm::None;
    {
        auto keepdims = nm::True;
        VECTOR_256_TEST(add.reduce,unwrap(input),axis,dtype,initial,keepdims);
    }
    {
        auto keepdims = nm::False;
        VECTOR_256_TEST(add.reduce,unwrap(input),axis,dtype,initial,keepdims);
    }
    {
        auto keepdims = true;
        VECTOR_256_TEST(add.reduce,unwrap(input),axis,dtype,initial,keepdims);
    }
    {
        auto keepdims = false;
        VECTOR_256_TEST(add.reduce,unwrap(input),axis,dtype,initial,keepdims);
    }
}

TEST_CASE("add.reduce_nd(case7b)" * doctest::test_suite("simd::vector_256"))
{
    auto axis = meta::ct_v<1>;
    auto new_shape = nmtools_array{3,2,7};
    auto input     = na::reshape(na::arange(ix::product(new_shape)),new_shape);
    auto dtype     = nm::None;
    auto initial   = nm::None;
    {
        auto keepdims = nm::True;
        VECTOR_256_TEST(add.reduce,unwrap(input),axis,dtype,initial,keepdims);
    }
    {
        auto keepdims = nm::False;
        VECTOR_256_TEST(add.reduce,unwrap(input),axis,dtype,initial,keepdims);
    }
    {
        auto keepdims = true;
        VECTOR_256_TEST(add.reduce,unwrap(input),axis,dtype,initial,keepdims);
    }
    {
        auto keepdims = false;
        VECTOR_256_TEST(add.reduce,unwrap(input),axis,dtype,initial,keepdims);
    }
}

TEST_CASE("add.reduce_nd(case7c)" * doctest::test_suite("simd::vector_256"))
{
    auto axis = meta::ct_v<2>;
    auto new_shape = nmtools_array{3,2,7};
    auto input     = na::reshape(na::arange(ix::product(new_shape)),new_shape);
    auto dtype     = nm::None;
    auto initial   = nm::None;
    {
        auto keepdims = nm::True;
        VECTOR_256_TEST(add.reduce,unwrap(input),axis,dtype,initial,keepdims);
    }
    {
        auto keepdims = nm::False;
        VECTOR_256_TEST(add.reduce,unwrap(input),axis,dtype,initial,keepdims);
    }
    {
        auto keepdims = true;
        VECTOR_256_TEST(add.reduce,unwrap(input),axis,dtype,initial,keepdims);
    }
    {
        auto keepdims = false;
        VECTOR_256_TEST(add.reduce,unwrap(input),axis,dtype,initial,keepdims);
    }
}

TEST_CASE("add.reduce_nd(case8a)" * doctest::test_suite("simd::vector_256"))
{
    auto axis = meta::ct_v<0>;
    auto new_shape = nmtools_array{3,2,8};
    auto input     = na::reshape(na::arange(ix::product(new_shape)),new_shape);
    auto dtype     = nm::None;
    auto initial   = nm::None;
    {
        auto keepdims = nm::True;
        VECTOR_256_TEST(add.reduce,unwrap(input),axis,dtype,initial,keepdims);
    }
    {
        auto keepdims = nm::False;
        VECTOR_256_TEST(add.reduce,unwrap(input),axis,dtype,initial,keepdims);
    }
    {
        auto keepdims = true;
        VECTOR_256_TEST(add.reduce,unwrap(input),axis,dtype,initial,keepdims);
    }
    {
        auto keepdims = false;
        VECTOR_256_TEST(add.reduce,unwrap(input),axis,dtype,initial,keepdims);
    }
}

TEST_CASE("add.reduce_nd(case8b)" * doctest::test_suite("simd::vector_256"))
{
    auto axis = meta::ct_v<1>;
    auto new_shape = nmtools_array{3,2,8};
    auto input     = na::reshape(na::arange(ix::product(new_shape)),new_shape);
    auto dtype     = nm::None;
    auto initial   = nm::None;
    {
        auto keepdims = nm::True;
        VECTOR_256_TEST(add.reduce,unwrap(input),axis,dtype,initial,keepdims);
    }
    {
        auto keepdims = nm::False;
        VECTOR_256_TEST(add.reduce,unwrap(input),axis,dtype,initial,keepdims);
    }
    {
        auto keepdims = true;
        VECTOR_256_TEST(add.reduce,unwrap(input),axis,dtype,initial,keepdims);
    }
    {
        auto keepdims = false;
        VECTOR_256_TEST(add.reduce,unwrap(input),axis,dtype,initial,keepdims);
    }
}

TEST_CASE("add.reduce_nd(case8c)" * doctest::test_suite("simd::vector_256"))
{
    auto axis = meta::ct_v<2>;
    auto new_shape = nmtools_array{3,2,8};
    auto input     = na::reshape(na::arange(ix::product(new_shape)),new_shape);
    auto dtype     = nm::None;
    auto initial   = nm::None;
    {
        auto keepdims = nm::True;
        VECTOR_256_TEST(add.reduce,unwrap(input),axis,dtype,initial,keepdims);
    }
    {
        auto keepdims = nm::False;
        VECTOR_256_TEST(add.reduce,unwrap(input),axis,dtype,initial,keepdims);
    }
    {
        auto keepdims = true;
        VECTOR_256_TEST(add.reduce,unwrap(input),axis,dtype,initial,keepdims);
    }
    {
        auto keepdims = false;
        VECTOR_256_TEST(add.reduce,unwrap(input),axis,dtype,initial,keepdims);
    }
}

///////////////////////////////////////////////////////////////////////////

TEST_CASE("add.reduce_nd(case9a)" * doctest::test_suite("simd::vector_256"))
{
    auto axis = meta::ct_v<0>;
    auto new_shape = nmtools_array{3,3,5};
    auto input     = na::reshape(na::arange(ix::product(new_shape)),new_shape);
    auto dtype     = nm::None;
    auto initial   = nm::None;
    {
        auto keepdims = nm::True;
        VECTOR_256_TEST(add.reduce,unwrap(input),axis,dtype,initial,keepdims);
    }
    {
        auto keepdims = nm::False;
        VECTOR_256_TEST(add.reduce,unwrap(input),axis,dtype,initial,keepdims);
    }
    {
        auto keepdims = true;
        VECTOR_256_TEST(add.reduce,unwrap(input),axis,dtype,initial,keepdims);
    }
    {
        auto keepdims = false;
        VECTOR_256_TEST(add.reduce,unwrap(input),axis,dtype,initial,keepdims);
    }
}

TEST_CASE("add.reduce_nd(case9b)" * doctest::test_suite("simd::vector_256"))
{
    auto axis = meta::ct_v<1>;
    auto new_shape = nmtools_array{3,3,5};
    auto input     = na::reshape(na::arange(ix::product(new_shape)),new_shape);
    auto dtype     = nm::None;
    auto initial   = nm::None;
    {
        auto keepdims = nm::True;
        VECTOR_256_TEST(add.reduce,unwrap(input),axis,dtype,initial,keepdims);
    }
    {
        auto keepdims = nm::False;
        VECTOR_256_TEST(add.reduce,unwrap(input),axis,dtype,initial,keepdims);
    }
    {
        auto keepdims = true;
        VECTOR_256_TEST(add.reduce,unwrap(input),axis,dtype,initial,keepdims);
    }
    {
        auto keepdims = false;
        VECTOR_256_TEST(add.reduce,unwrap(input),axis,dtype,initial,keepdims);
    }
}

TEST_CASE("add.reduce_nd(case9c)" * doctest::test_suite("simd::vector_256"))
{
    auto axis = meta::ct_v<2>;
    auto new_shape = nmtools_array{3,3,5};
    auto input     = na::reshape(na::arange(ix::product(new_shape)),new_shape);
    auto dtype     = nm::None;
    auto initial   = nm::None;
    {
        auto keepdims = nm::True;
        VECTOR_256_TEST(add.reduce,unwrap(input),axis,dtype,initial,keepdims);
    }
    {
        auto keepdims = nm::False;
        VECTOR_256_TEST(add.reduce,unwrap(input),axis,dtype,initial,keepdims);
    }
    {
        auto keepdims = true;
        VECTOR_256_TEST(add.reduce,unwrap(input),axis,dtype,initial,keepdims);
    }
    {
        auto keepdims = false;
        VECTOR_256_TEST(add.reduce,unwrap(input),axis,dtype,initial,keepdims);
    }
}

TEST_CASE("add.reduce_nd(case10a)" * doctest::test_suite("simd::vector_256"))
{
    auto axis = meta::ct_v<0>;
    auto new_shape = nmtools_array{3,3,6};
    auto input     = na::reshape(na::arange(ix::product(new_shape)),new_shape);
    auto dtype     = nm::None;
    auto initial   = nm::None;
    {
        auto keepdims = nm::True;
        VECTOR_256_TEST(add.reduce,unwrap(input),axis,dtype,initial,keepdims);
    }
    {
        auto keepdims = nm::False;
        VECTOR_256_TEST(add.reduce,unwrap(input),axis,dtype,initial,keepdims);
    }
    {
        auto keepdims = true;
        VECTOR_256_TEST(add.reduce,unwrap(input),axis,dtype,initial,keepdims);
    }
    {
        auto keepdims = false;
        VECTOR_256_TEST(add.reduce,unwrap(input),axis,dtype,initial,keepdims);
    }
}

TEST_CASE("add.reduce_nd(case10b)" * doctest::test_suite("simd::vector_256"))
{
    auto axis = meta::ct_v<1>;
    auto new_shape = nmtools_array{3,3,6};
    auto input     = na::reshape(na::arange(ix::product(new_shape)),new_shape);
    auto dtype     = nm::None;
    auto initial   = nm::None;
    {
        auto keepdims = nm::True;
        VECTOR_256_TEST(add.reduce,unwrap(input),axis,dtype,initial,keepdims);
    }
    {
        auto keepdims = nm::False;
        VECTOR_256_TEST(add.reduce,unwrap(input),axis,dtype,initial,keepdims);
    }
    {
        auto keepdims = true;
        VECTOR_256_TEST(add.reduce,unwrap(input),axis,dtype,initial,keepdims);
    }
    {
        auto keepdims = false;
        VECTOR_256_TEST(add.reduce,unwrap(input),axis,dtype,initial,keepdims);
    }
}

TEST_CASE("add.reduce_nd(case10c)" * doctest::test_suite("simd::vector_256"))
{
    auto axis = meta::ct_v<2>;
    auto new_shape = nmtools_array{3,3,6};
    auto input     = na::reshape(na::arange(ix::product(new_shape)),new_shape);
    auto dtype     = nm::None;
    auto initial   = nm::None;
    {
        auto keepdims = nm::True;
        VECTOR_256_TEST(add.reduce,unwrap(input),axis,dtype,initial,keepdims);
    }
    {
        auto keepdims = nm::False;
        VECTOR_256_TEST(add.reduce,unwrap(input),axis,dtype,initial,keepdims);
    }
    {
        auto keepdims = true;
        VECTOR_256_TEST(add.reduce,unwrap(input),axis,dtype,initial,keepdims);
    }
    {
        auto keepdims = false;
        VECTOR_256_TEST(add.reduce,unwrap(input),axis,dtype,initial,keepdims);
    }
}

TEST_CASE("add.reduce_nd(case11a)" * doctest::test_suite("simd::vector_256"))
{
    auto axis = meta::ct_v<0>;
    auto new_shape = nmtools_array{3,3,7};
    auto input     = na::reshape(na::arange(ix::product(new_shape)),new_shape);
    auto dtype     = nm::None;
    auto initial   = nm::None;
    {
        auto keepdims = nm::True;
        VECTOR_256_TEST(add.reduce,unwrap(input),axis,dtype,initial,keepdims);
    }
    {
        auto keepdims = nm::False;
        VECTOR_256_TEST(add.reduce,unwrap(input),axis,dtype,initial,keepdims);
    }
    {
        auto keepdims = true;
        VECTOR_256_TEST(add.reduce,unwrap(input),axis,dtype,initial,keepdims);
    }
    {
        auto keepdims = false;
        VECTOR_256_TEST(add.reduce,unwrap(input),axis,dtype,initial,keepdims);
    }
}

TEST_CASE("add.reduce_nd(case11b)" * doctest::test_suite("simd::vector_256"))
{
    auto axis = meta::ct_v<1>;
    auto new_shape = nmtools_array{3,3,7};
    auto input     = na::reshape(na::arange(ix::product(new_shape)),new_shape);
    auto dtype     = nm::None;
    auto initial   = nm::None;
    {
        auto keepdims = nm::True;
        VECTOR_256_TEST(add.reduce,unwrap(input),axis,dtype,initial,keepdims);
    }
    {
        auto keepdims = nm::False;
        VECTOR_256_TEST(add.reduce,unwrap(input),axis,dtype,initial,keepdims);
    }
    {
        auto keepdims = true;
        VECTOR_256_TEST(add.reduce,unwrap(input),axis,dtype,initial,keepdims);
    }
    {
        auto keepdims = false;
        VECTOR_256_TEST(add.reduce,unwrap(input),axis,dtype,initial,keepdims);
    }
}

TEST_CASE("add.reduce_nd(case11c)" * doctest::test_suite("simd::vector_256"))
{
    auto axis = meta::ct_v<2>;
    auto new_shape = nmtools_array{3,3,7};
    auto input     = na::reshape(na::arange(ix::product(new_shape)),new_shape);
    auto dtype     = nm::None;
    auto initial   = nm::None;
    {
        auto keepdims = nm::True;
        VECTOR_256_TEST(add.reduce,unwrap(input),axis,dtype,initial,keepdims);
    }
    {
        auto keepdims = nm::False;
        VECTOR_256_TEST(add.reduce,unwrap(input),axis,dtype,initial,keepdims);
    }
    {
        auto keepdims = true;
        VECTOR_256_TEST(add.reduce,unwrap(input),axis,dtype,initial,keepdims);
    }
    {
        auto keepdims = false;
        VECTOR_256_TEST(add.reduce,unwrap(input),axis,dtype,initial,keepdims);
    }
}

TEST_CASE("add.reduce_nd(case12a)" * doctest::test_suite("simd::vector_256"))
{
    auto axis = meta::ct_v<0>;
    auto new_shape = nmtools_array{3,3,8};
    auto input     = na::reshape(na::arange(ix::product(new_shape)),new_shape);
    auto dtype     = nm::None;
    auto initial   = nm::None;
    {
        auto keepdims = nm::True;
        VECTOR_256_TEST(add.reduce,unwrap(input),axis,dtype,initial,keepdims);
    }
    {
        auto keepdims = nm::False;
        VECTOR_256_TEST(add.reduce,unwrap(input),axis,dtype,initial,keepdims);
    }
    {
        auto keepdims = true;
        VECTOR_256_TEST(add.reduce,unwrap(input),axis,dtype,initial,keepdims);
    }
    {
        auto keepdims = false;
        VECTOR_256_TEST(add.reduce,unwrap(input),axis,dtype,initial,keepdims);
    }
}

TEST_CASE("add.reduce_nd(case12b)" * doctest::test_suite("simd::vector_256"))
{
    auto axis = meta::ct_v<1>;
    auto new_shape = nmtools_array{3,3,8};
    auto input     = na::reshape(na::arange(ix::product(new_shape)),new_shape);
    auto dtype     = nm::None;
    auto initial   = nm::None;
    {
        auto keepdims = nm::True;
        VECTOR_256_TEST(add.reduce,unwrap(input),axis,dtype,initial,keepdims);
    }
    {
        auto keepdims = nm::False;
        VECTOR_256_TEST(add.reduce,unwrap(input),axis,dtype,initial,keepdims);
    }
    {
        auto keepdims = true;
        VECTOR_256_TEST(add.reduce,unwrap(input),axis,dtype,initial,keepdims);
    }
    {
        auto keepdims = false;
        VECTOR_256_TEST(add.reduce,unwrap(input),axis,dtype,initial,keepdims);
    }
}

TEST_CASE("add.reduce_nd(case12c)" * doctest::test_suite("simd::vector_256"))
{
    auto axis = meta::ct_v<2>;
    auto new_shape = nmtools_array{3,3,8};
    auto input     = na::reshape(na::arange(ix::product(new_shape)),new_shape);
    auto dtype     = nm::None;
    auto initial   = nm::None;
    {
        auto keepdims = nm::True;
        VECTOR_256_TEST(add.reduce,unwrap(input),axis,dtype,initial,keepdims);
    }
    {
        auto keepdims = nm::False;
        VECTOR_256_TEST(add.reduce,unwrap(input),axis,dtype,initial,keepdims);
    }
    {
        auto keepdims = true;
        VECTOR_256_TEST(add.reduce,unwrap(input),axis,dtype,initial,keepdims);
    }
    {
        auto keepdims = false;
        VECTOR_256_TEST(add.reduce,unwrap(input),axis,dtype,initial,keepdims);
    }
}

//////////////////////////////////////////////////////////////////////////////////////


TEST_CASE("add.reduce_nd(case13a)" * doctest::test_suite("simd::vector_256"))
{
    auto axis = 0;
    auto new_shape = nmtools_array{3,3,5};
    auto input     = na::reshape(na::arange(ix::product(new_shape)),new_shape);
    auto dtype     = nm::None;
    auto initial   = nm::None;
    {
        auto keepdims = nm::True;
        VECTOR_256_TEST(add.reduce,unwrap(input),axis,dtype,initial,keepdims);
    }
    {
        auto keepdims = nm::False;
        VECTOR_256_TEST(add.reduce,unwrap(input),axis,dtype,initial,keepdims);
    }
    {
        auto keepdims = true;
        VECTOR_256_TEST(add.reduce,unwrap(input),axis,dtype,initial,keepdims);
    }
    {
        auto keepdims = false;
        VECTOR_256_TEST(add.reduce,unwrap(input),axis,dtype,initial,keepdims);
    }
}

TEST_CASE("add.reduce_nd(case13b)" * doctest::test_suite("simd::vector_256"))
{
    auto axis = 1;
    auto new_shape = nmtools_array{3,3,5};
    auto input     = na::reshape(na::arange(ix::product(new_shape)),new_shape);
    auto dtype     = nm::None;
    auto initial   = nm::None;
    {
        auto keepdims = nm::True;
        VECTOR_256_TEST(add.reduce,unwrap(input),axis,dtype,initial,keepdims);
    }
    {
        auto keepdims = nm::False;
        VECTOR_256_TEST(add.reduce,unwrap(input),axis,dtype,initial,keepdims);
    }
    {
        auto keepdims = true;
        VECTOR_256_TEST(add.reduce,unwrap(input),axis,dtype,initial,keepdims);
    }
    {
        auto keepdims = false;
        VECTOR_256_TEST(add.reduce,unwrap(input),axis,dtype,initial,keepdims);
    }
}

TEST_CASE("add.reduce_nd(case13c)" * doctest::test_suite("simd::vector_256"))
{
    auto axis = 2;
    auto new_shape = nmtools_array{3,3,5};
    auto input     = na::reshape(na::arange(ix::product(new_shape)),new_shape);
    auto dtype     = nm::None;
    auto initial   = nm::None;
    {
        auto keepdims = nm::True;
        VECTOR_256_TEST(add.reduce,unwrap(input),axis,dtype,initial,keepdims);
    }
    {
        auto keepdims = nm::False;
        VECTOR_256_TEST(add.reduce,unwrap(input),axis,dtype,initial,keepdims);
    }
    {
        auto keepdims = true;
        VECTOR_256_TEST(add.reduce,unwrap(input),axis,dtype,initial,keepdims);
    }
    {
        auto keepdims = false;
        VECTOR_256_TEST(add.reduce,unwrap(input),axis,dtype,initial,keepdims);
    }
}

TEST_CASE("add.reduce_nd(case14a)" * doctest::test_suite("simd::vector_256"))
{
    auto axis = 0;
    auto new_shape = nmtools_array{3,3,6};
    auto input     = na::reshape(na::arange(ix::product(new_shape)),new_shape);
    auto dtype     = nm::None;
    auto initial   = nm::None;
    {
        auto keepdims = nm::True;
        VECTOR_256_TEST(add.reduce,unwrap(input),axis,dtype,initial,keepdims);
    }
    {
        auto keepdims = nm::False;
        VECTOR_256_TEST(add.reduce,unwrap(input),axis,dtype,initial,keepdims);
    }
    {
        auto keepdims = true;
        VECTOR_256_TEST(add.reduce,unwrap(input),axis,dtype,initial,keepdims);
    }
    {
        auto keepdims = false;
        VECTOR_256_TEST(add.reduce,unwrap(input),axis,dtype,initial,keepdims);
    }
}

TEST_CASE("add.reduce_nd(case14b)" * doctest::test_suite("simd::vector_256"))
{
    auto axis = 1;
    auto new_shape = nmtools_array{3,3,6};
    auto input     = na::reshape(na::arange(ix::product(new_shape)),new_shape);
    auto dtype     = nm::None;
    auto initial   = nm::None;
    {
        auto keepdims = nm::True;
        VECTOR_256_TEST(add.reduce,unwrap(input),axis,dtype,initial,keepdims);
    }
    {
        auto keepdims = nm::False;
        VECTOR_256_TEST(add.reduce,unwrap(input),axis,dtype,initial,keepdims);
    }
    {
        auto keepdims = true;
        VECTOR_256_TEST(add.reduce,unwrap(input),axis,dtype,initial,keepdims);
    }
    {
        auto keepdims = false;
        VECTOR_256_TEST(add.reduce,unwrap(input),axis,dtype,initial,keepdims);
    }
}

TEST_CASE("add.reduce_nd(case14c)" * doctest::test_suite("simd::vector_256"))
{
    auto axis = 2;
    auto new_shape = nmtools_array{3,3,6};
    auto input     = na::reshape(na::arange(ix::product(new_shape)),new_shape);
    auto dtype     = nm::None;
    auto initial   = nm::None;
    {
        auto keepdims = nm::True;
        VECTOR_256_TEST(add.reduce,unwrap(input),axis,dtype,initial,keepdims);
    }
    {
        auto keepdims = nm::False;
        VECTOR_256_TEST(add.reduce,unwrap(input),axis,dtype,initial,keepdims);
    }
    {
        auto keepdims = true;
        VECTOR_256_TEST(add.reduce,unwrap(input),axis,dtype,initial,keepdims);
    }
    {
        auto keepdims = false;
        VECTOR_256_TEST(add.reduce,unwrap(input),axis,dtype,initial,keepdims);
    }
}

TEST_CASE("add.reduce_nd(case15a)" * doctest::test_suite("simd::vector_256"))
{
    auto axis = 0;
    auto new_shape = nmtools_array{3,3,7};
    auto input     = na::reshape(na::arange(ix::product(new_shape)),new_shape);
    auto dtype     = nm::None;
    auto initial   = nm::None;
    {
        auto keepdims = nm::True;
        VECTOR_256_TEST(add.reduce,unwrap(input),axis,dtype,initial,keepdims);
    }
    {
        auto keepdims = nm::False;
        VECTOR_256_TEST(add.reduce,unwrap(input),axis,dtype,initial,keepdims);
    }
    {
        auto keepdims = true;
        VECTOR_256_TEST(add.reduce,unwrap(input),axis,dtype,initial,keepdims);
    }
    {
        auto keepdims = false;
        VECTOR_256_TEST(add.reduce,unwrap(input),axis,dtype,initial,keepdims);
    }
}

TEST_CASE("add.reduce_nd(case15b)" * doctest::test_suite("simd::vector_256"))
{
    auto axis = 1;
    auto new_shape = nmtools_array{3,3,7};
    auto input     = na::reshape(na::arange(ix::product(new_shape)),new_shape);
    auto dtype     = nm::None;
    auto initial   = nm::None;
    {
        auto keepdims = nm::True;
        VECTOR_256_TEST(add.reduce,unwrap(input),axis,dtype,initial,keepdims);
    }
    {
        auto keepdims = nm::False;
        VECTOR_256_TEST(add.reduce,unwrap(input),axis,dtype,initial,keepdims);
    }
    {
        auto keepdims = true;
        VECTOR_256_TEST(add.reduce,unwrap(input),axis,dtype,initial,keepdims);
    }
    {
        auto keepdims = false;
        VECTOR_256_TEST(add.reduce,unwrap(input),axis,dtype,initial,keepdims);
    }
}

TEST_CASE("add.reduce_nd(case15c)" * doctest::test_suite("simd::vector_256"))
{
    auto axis = 2;
    auto new_shape = nmtools_array{3,3,7};
    auto input     = na::reshape(na::arange(ix::product(new_shape)),new_shape);
    auto dtype     = nm::None;
    auto initial   = nm::None;
    {
        auto keepdims = nm::True;
        VECTOR_256_TEST(add.reduce,unwrap(input),axis,dtype,initial,keepdims);
    }
    {
        auto keepdims = nm::False;
        VECTOR_256_TEST(add.reduce,unwrap(input),axis,dtype,initial,keepdims);
    }
    {
        auto keepdims = true;
        VECTOR_256_TEST(add.reduce,unwrap(input),axis,dtype,initial,keepdims);
    }
    {
        auto keepdims = false;
        VECTOR_256_TEST(add.reduce,unwrap(input),axis,dtype,initial,keepdims);
    }
}

TEST_CASE("add.reduce_nd(case16a)" * doctest::test_suite("simd::vector_256"))
{
    auto axis = 0;
    auto new_shape = nmtools_array{3,3,8};
    auto input     = na::reshape(na::arange(ix::product(new_shape)),new_shape);
    auto dtype     = nm::None;
    auto initial   = nm::None;
    {
        auto keepdims = nm::True;
        VECTOR_256_TEST(add.reduce,unwrap(input),axis,dtype,initial,keepdims);
    }
    {
        auto keepdims = nm::False;
        VECTOR_256_TEST(add.reduce,unwrap(input),axis,dtype,initial,keepdims);
    }
    {
        auto keepdims = true;
        VECTOR_256_TEST(add.reduce,unwrap(input),axis,dtype,initial,keepdims);
    }
    {
        auto keepdims = false;
        VECTOR_256_TEST(add.reduce,unwrap(input),axis,dtype,initial,keepdims);
    }
}

TEST_CASE("add.reduce_nd(case16b)" * doctest::test_suite("simd::vector_256"))
{
    auto axis = 1;
    auto new_shape = nmtools_array{3,3,8};
    auto input     = na::reshape(na::arange(ix::product(new_shape)),new_shape);
    auto dtype     = nm::None;
    auto initial   = nm::None;
    {
        auto keepdims = nm::True;
        VECTOR_256_TEST(add.reduce,unwrap(input),axis,dtype,initial,keepdims);
    }
    {
        auto keepdims = nm::False;
        VECTOR_256_TEST(add.reduce,unwrap(input),axis,dtype,initial,keepdims);
    }
    {
        auto keepdims = true;
        VECTOR_256_TEST(add.reduce,unwrap(input),axis,dtype,initial,keepdims);
    }
    {
        auto keepdims = false;
        VECTOR_256_TEST(add.reduce,unwrap(input),axis,dtype,initial,keepdims);
    }
}

TEST_CASE("add.reduce_nd(case16c)" * doctest::test_suite("simd::vector_256"))
{
    auto axis = 2;
    auto new_shape = nmtools_array{3,3,8};
    auto input     = na::reshape(na::arange(ix::product(new_shape)),new_shape);
    auto dtype     = nm::None;
    auto initial   = nm::None;
    {
        auto keepdims = nm::True;
        VECTOR_256_TEST(add.reduce,unwrap(input),axis,dtype,initial,keepdims);
    }
    {
        auto keepdims = nm::False;
        VECTOR_256_TEST(add.reduce,unwrap(input),axis,dtype,initial,keepdims);
    }
    {
        auto keepdims = true;
        VECTOR_256_TEST(add.reduce,unwrap(input),axis,dtype,initial,keepdims);
    }
    {
        auto keepdims = false;
        VECTOR_256_TEST(add.reduce,unwrap(input),axis,dtype,initial,keepdims);
    }
}

//////////////////////////////////////////////////////////////////////////////

TEST_CASE("add.reduce_nd(case17a)" * doctest::test_suite("simd::vector_256"))
{
    auto axis = 0;
    auto new_shape = nmtools_array{12,3,3,8};
    auto input     = na::reshape(na::arange(ix::product(new_shape)),new_shape);
    auto dtype     = nm::None;
    auto initial   = nm::None;
    {
        auto keepdims = nm::True;
        VECTOR_256_TEST(add.reduce,unwrap(input),axis,dtype,initial,keepdims);
    }
    {
        auto keepdims = nm::False;
        VECTOR_256_TEST(add.reduce,unwrap(input),axis,dtype,initial,keepdims);
    }
    {
        auto keepdims = true;
        VECTOR_256_TEST(add.reduce,unwrap(input),axis,dtype,initial,keepdims);
    }
    {
        auto keepdims = false;
        VECTOR_256_TEST(add.reduce,unwrap(input),axis,dtype,initial,keepdims);
    }
}

TEST_CASE("add.reduce_nd(case17b)" * doctest::test_suite("simd::vector_256"))
{
    auto axis = 1;
    auto new_shape = nmtools_array{12,3,3,8};
    auto input     = na::reshape(na::arange(ix::product(new_shape)),new_shape);
    auto dtype     = nm::None;
    auto initial   = nm::None;
    {
        auto keepdims = nm::True;
        VECTOR_256_TEST(add.reduce,unwrap(input),axis,dtype,initial,keepdims);
    }
    {
        auto keepdims = nm::False;
        VECTOR_256_TEST(add.reduce,unwrap(input),axis,dtype,initial,keepdims);
    }
    {
        auto keepdims = true;
        VECTOR_256_TEST(add.reduce,unwrap(input),axis,dtype,initial,keepdims);
    }
    {
        auto keepdims = false;
        VECTOR_256_TEST(add.reduce,unwrap(input),axis,dtype,initial,keepdims);
    }
}

TEST_CASE("add.reduce_nd(case17c)" * doctest::test_suite("simd::vector_256"))
{
    auto axis = 2;
    auto new_shape = nmtools_array{12,3,3,8};
    auto input     = na::reshape(na::arange(ix::product(new_shape)),new_shape);
    auto dtype     = nm::None;
    auto initial   = nm::None;
    {
        auto keepdims = nm::True;
        VECTOR_256_TEST(add.reduce,unwrap(input),axis,dtype,initial,keepdims);
    }
    {
        auto keepdims = nm::False;
        VECTOR_256_TEST(add.reduce,unwrap(input),axis,dtype,initial,keepdims);
    }
    {
        auto keepdims = true;
        VECTOR_256_TEST(add.reduce,unwrap(input),axis,dtype,initial,keepdims);
    }
    {
        auto keepdims = false;
        VECTOR_256_TEST(add.reduce,unwrap(input),axis,dtype,initial,keepdims);
    }
}

TEST_CASE("add.reduce_nd(case17d)" * doctest::test_suite("simd::vector_256"))
{
    auto axis = 3;
    auto new_shape = nmtools_array{12,3,3,8};
    auto input     = na::reshape(na::arange(ix::product(new_shape)),new_shape);
    auto dtype     = nm::None;
    auto initial   = nm::None;
    {
        auto keepdims = nm::True;
        VECTOR_256_TEST(add.reduce,unwrap(input),axis,dtype,initial,keepdims);
    }
    {
        auto keepdims = nm::False;
        VECTOR_256_TEST(add.reduce,unwrap(input),axis,dtype,initial,keepdims);
    }
    {
        auto keepdims = true;
        VECTOR_256_TEST(add.reduce,unwrap(input),axis,dtype,initial,keepdims);
    }
    {
        auto keepdims = false;
        VECTOR_256_TEST(add.reduce,unwrap(input),axis,dtype,initial,keepdims);
    }
}

//////////////////////////////////////////////////////////////////////////////

TEST_CASE("add.reduce_nd(case18a)" * doctest::test_suite("simd::vector_256"))
{
    auto axis = 0;
    auto new_shape = nmtools_array{2,12,3,3,9};
    auto input     = na::reshape(na::arange(ix::product(new_shape)),new_shape);
    auto dtype     = nm::None;
    auto initial   = nm::None;
    {
        auto keepdims = nm::True;
        VECTOR_256_TEST(add.reduce,unwrap(input),axis,dtype,initial,keepdims);
    }
    {
        auto keepdims = nm::False;
        VECTOR_256_TEST(add.reduce,unwrap(input),axis,dtype,initial,keepdims);
    }
    {
        auto keepdims = true;
        VECTOR_256_TEST(add.reduce,unwrap(input),axis,dtype,initial,keepdims);
    }
    {
        auto keepdims = false;
        VECTOR_256_TEST(add.reduce,unwrap(input),axis,dtype,initial,keepdims);
    }
}

TEST_CASE("add.reduce_nd(case18b)" * doctest::test_suite("simd::vector_256"))
{
    auto axis = 1;
    auto new_shape = nmtools_array{2,12,3,3,9};
    auto input     = na::reshape(na::arange(ix::product(new_shape)),new_shape);
    auto dtype     = nm::None;
    auto initial   = nm::None;
    {
        auto keepdims = nm::True;
        VECTOR_256_TEST(add.reduce,unwrap(input),axis,dtype,initial,keepdims);
    }
    {
        auto keepdims = nm::False;
        VECTOR_256_TEST(add.reduce,unwrap(input),axis,dtype,initial,keepdims);
    }
    {
        auto keepdims = true;
        VECTOR_256_TEST(add.reduce,unwrap(input),axis,dtype,initial,keepdims);
    }
    {
        auto keepdims = false;
        VECTOR_256_TEST(add.reduce,unwrap(input),axis,dtype,initial,keepdims);
    }
}

TEST_CASE("add.reduce_nd(case18c)" * doctest::test_suite("simd::vector_256"))
{
    auto axis = 2;
    auto new_shape = nmtools_array{2,12,3,3,9};
    auto input     = na::reshape(na::arange(ix::product(new_shape)),new_shape);
    auto dtype     = nm::None;
    auto initial   = nm::None;
    {
        auto keepdims = nm::True;
        VECTOR_256_TEST(add.reduce,unwrap(input),axis,dtype,initial,keepdims);
    }
    {
        auto keepdims = nm::False;
        VECTOR_256_TEST(add.reduce,unwrap(input),axis,dtype,initial,keepdims);
    }
    {
        auto keepdims = true;
        VECTOR_256_TEST(add.reduce,unwrap(input),axis,dtype,initial,keepdims);
    }
    {
        auto keepdims = false;
        VECTOR_256_TEST(add.reduce,unwrap(input),axis,dtype,initial,keepdims);
    }
}

TEST_CASE("add.reduce_nd(case18d)" * doctest::test_suite("simd::vector_256"))
{
    auto axis = 3;
    auto new_shape = nmtools_array{2,12,3,3,9};
    auto input     = na::reshape(na::arange(ix::product(new_shape)),new_shape);
    auto dtype     = nm::None;
    auto initial   = nm::None;
    {
        auto keepdims = nm::True;
        VECTOR_256_TEST(add.reduce,unwrap(input),axis,dtype,initial,keepdims);
    }
    {
        auto keepdims = nm::False;
        VECTOR_256_TEST(add.reduce,unwrap(input),axis,dtype,initial,keepdims);
    }
    {
        auto keepdims = true;
        VECTOR_256_TEST(add.reduce,unwrap(input),axis,dtype,initial,keepdims);
    }
    {
        auto keepdims = false;
        VECTOR_256_TEST(add.reduce,unwrap(input),axis,dtype,initial,keepdims);
    }
}

TEST_CASE("add.reduce_nd(case18e)" * doctest::test_suite("simd::vector_256"))
{
    auto axis = 4;
    auto new_shape = nmtools_array{2,12,3,3,9};
    auto input     = na::reshape(na::arange(ix::product(new_shape)),new_shape);
    auto dtype     = nm::None;
    auto initial   = nm::None;
    {
        auto keepdims = nm::True;
        VECTOR_256_TEST(add.reduce,unwrap(input),axis,dtype,initial,keepdims);
    }
    {
        auto keepdims = nm::False;
        VECTOR_256_TEST(add.reduce,unwrap(input),axis,dtype,initial,keepdims);
    }
    {
        auto keepdims = true;
        VECTOR_256_TEST(add.reduce,unwrap(input),axis,dtype,initial,keepdims);
    }
    {
        auto keepdims = false;
        VECTOR_256_TEST(add.reduce,unwrap(input),axis,dtype,initial,keepdims);
    }
}

/////////////////////////////////////////////////////////////////////////////////

TEST_CASE("add.reduce_nd(case19a)" * doctest::test_suite("simd::vector_256"))
{
    auto axis = 0;
    auto new_shape = nmtools_array{2,12,1,3,3,9};
    auto input     = na::reshape(na::arange(ix::product(new_shape)),new_shape);
    auto dtype     = nm::None;
    auto initial   = nm::None;
    {
        auto keepdims = nm::True;
        VECTOR_256_TEST(add.reduce,unwrap(input),axis,dtype,initial,keepdims);
    }
    {
        auto keepdims = nm::False;
        VECTOR_256_TEST(add.reduce,unwrap(input),axis,dtype,initial,keepdims);
    }
    {
        auto keepdims = true;
        VECTOR_256_TEST(add.reduce,unwrap(input),axis,dtype,initial,keepdims);
    }
    {
        auto keepdims = false;
        VECTOR_256_TEST(add.reduce,unwrap(input),axis,dtype,initial,keepdims);
    }
}

TEST_CASE("add.reduce_nd(case19b)" * doctest::test_suite("simd::vector_256"))
{
    auto axis = 1;
    auto new_shape = nmtools_array{2,12,1,3,3,9};
    auto input     = na::reshape(na::arange(ix::product(new_shape)),new_shape);
    auto dtype     = nm::None;
    auto initial   = nm::None;
    {
        auto keepdims = nm::True;
        VECTOR_256_TEST(add.reduce,unwrap(input),axis,dtype,initial,keepdims);
    }
    {
        auto keepdims = nm::False;
        VECTOR_256_TEST(add.reduce,unwrap(input),axis,dtype,initial,keepdims);
    }
    {
        auto keepdims = true;
        VECTOR_256_TEST(add.reduce,unwrap(input),axis,dtype,initial,keepdims);
    }
    {
        auto keepdims = false;
        VECTOR_256_TEST(add.reduce,unwrap(input),axis,dtype,initial,keepdims);
    }
}

TEST_CASE("add.reduce_nd(case19c)" * doctest::test_suite("simd::vector_256"))
{
    auto axis = 2;
    auto new_shape = nmtools_array{2,12,1,3,3,9};
    auto input     = na::reshape(na::arange(ix::product(new_shape)),new_shape);
    auto dtype     = nm::None;
    auto initial   = nm::None;
    {
        auto keepdims = nm::True;
        VECTOR_256_TEST(add.reduce,unwrap(input),axis,dtype,initial,keepdims);
    }
    {
        auto keepdims = nm::False;
        VECTOR_256_TEST(add.reduce,unwrap(input),axis,dtype,initial,keepdims);
    }
    {
        auto keepdims = true;
        VECTOR_256_TEST(add.reduce,unwrap(input),axis,dtype,initial,keepdims);
    }
    {
        auto keepdims = false;
        VECTOR_256_TEST(add.reduce,unwrap(input),axis,dtype,initial,keepdims);
    }
}

TEST_CASE("add.reduce_nd(case19d)" * doctest::test_suite("simd::vector_256"))
{
    auto axis = 3;
    auto new_shape = nmtools_array{2,12,1,3,3,9};
    auto input     = na::reshape(na::arange(ix::product(new_shape)),new_shape);
    auto dtype     = nm::None;
    auto initial   = nm::None;
    {
        auto keepdims = nm::True;
        VECTOR_256_TEST(add.reduce,unwrap(input),axis,dtype,initial,keepdims);
    }
    {
        auto keepdims = nm::False;
        VECTOR_256_TEST(add.reduce,unwrap(input),axis,dtype,initial,keepdims);
    }
    {
        auto keepdims = true;
        VECTOR_256_TEST(add.reduce,unwrap(input),axis,dtype,initial,keepdims);
    }
    {
        auto keepdims = false;
        VECTOR_256_TEST(add.reduce,unwrap(input),axis,dtype,initial,keepdims);
    }
}

TEST_CASE("add.reduce_nd(case19e)" * doctest::test_suite("simd::vector_256"))
{
    auto axis = 4;
    auto new_shape = nmtools_array{2,12,1,3,3,9};
    auto input     = na::reshape(na::arange(ix::product(new_shape)),new_shape);
    auto dtype     = nm::None;
    auto initial   = nm::None;
    {
        auto keepdims = nm::True;
        VECTOR_256_TEST(add.reduce,unwrap(input),axis,dtype,initial,keepdims);
    }
    {
        auto keepdims = nm::False;
        VECTOR_256_TEST(add.reduce,unwrap(input),axis,dtype,initial,keepdims);
    }
    {
        auto keepdims = true;
        VECTOR_256_TEST(add.reduce,unwrap(input),axis,dtype,initial,keepdims);
    }
    {
        auto keepdims = false;
        VECTOR_256_TEST(add.reduce,unwrap(input),axis,dtype,initial,keepdims);
    }
}

TEST_CASE("add.reduce_nd(case19f)" * doctest::test_suite("simd::vector_256"))
{
    auto axis = 5;
    auto new_shape = nmtools_array{2,12,1,3,3,9};
    auto input     = na::reshape(na::arange(ix::product(new_shape)),new_shape);
    auto dtype     = nm::None;
    auto initial   = nm::None;
    {
        auto keepdims = nm::True;
        VECTOR_256_TEST(add.reduce,unwrap(input),axis,dtype,initial,keepdims);
    }
    {
        auto keepdims = nm::False;
        VECTOR_256_TEST(add.reduce,unwrap(input),axis,dtype,initial,keepdims);
    }
    {
        auto keepdims = true;
        VECTOR_256_TEST(add.reduce,unwrap(input),axis,dtype,initial,keepdims);
    }
    {
        auto keepdims = false;
        VECTOR_256_TEST(add.reduce,unwrap(input),axis,dtype,initial,keepdims);
    }
}

/*********************** multiply ******************************/

TEST_CASE("multiply.reduce_nd(case1a)" * doctest::test_suite("simd::vector_256"))
{
    auto axis = meta::ct_v<0>;
    auto new_shape = nmtools_array{2,2,5};
    auto input     = na::reshape(na::arange(ix::product(new_shape)),new_shape);
    auto dtype     = nm::None;
    auto initial   = nm::None;
    {
        auto keepdims = nm::True;
        VECTOR_256_TEST(multiply.reduce,unwrap(input),axis,dtype,initial,keepdims);
    }
    {
        auto keepdims = nm::False;
        VECTOR_256_TEST(multiply.reduce,unwrap(input),axis,dtype,initial,keepdims);
    }
    {
        auto keepdims = true;
        VECTOR_256_TEST(multiply.reduce,unwrap(input),axis,dtype,initial,keepdims);
    }
    {
        auto keepdims = false;
        VECTOR_256_TEST(multiply.reduce,unwrap(input),axis,dtype,initial,keepdims);
    }
}

TEST_CASE("multiply.reduce_nd(case1b)" * doctest::test_suite("simd::vector_256"))
{
    auto axis = meta::ct_v<1>;
    auto new_shape = nmtools_array{2,2,5};
    auto input     = na::reshape(na::arange(ix::product(new_shape)),new_shape);
    auto dtype     = nm::None;
    auto initial   = nm::None;
    {
        auto keepdims = nm::True;
        VECTOR_256_TEST(multiply.reduce,unwrap(input),axis,dtype,initial,keepdims);
    }
    {
        auto keepdims = nm::False;
        VECTOR_256_TEST(multiply.reduce,unwrap(input),axis,dtype,initial,keepdims);
    }
    {
        auto keepdims = true;
        VECTOR_256_TEST(multiply.reduce,unwrap(input),axis,dtype,initial,keepdims);
    }
    {
        auto keepdims = false;
        VECTOR_256_TEST(multiply.reduce,unwrap(input),axis,dtype,initial,keepdims);
    }
}

TEST_CASE("multiply.reduce_nd(case1c)" * doctest::test_suite("simd::vector_256"))
{
    auto axis = meta::ct_v<2>;
    auto new_shape = nmtools_array{2,2,5};
    auto input     = na::reshape(na::arange(ix::product(new_shape)),new_shape);
    auto dtype     = nm::None;
    auto initial   = nm::None;
    {
        auto keepdims = nm::True;
        VECTOR_256_TEST(multiply.reduce,unwrap(input),axis,dtype,initial,keepdims);
    }
    {
        auto keepdims = nm::False;
        VECTOR_256_TEST(multiply.reduce,unwrap(input),axis,dtype,initial,keepdims);
    }
    {
        auto keepdims = true;
        VECTOR_256_TEST(multiply.reduce,unwrap(input),axis,dtype,initial,keepdims);
    }
    {
        auto keepdims = false;
        VECTOR_256_TEST(multiply.reduce,unwrap(input),axis,dtype,initial,keepdims);
    }
}

TEST_CASE("multiply.reduce_nd(case2a)" * doctest::test_suite("simd::vector_256"))
{
    auto axis = meta::ct_v<0>;
    auto new_shape = nmtools_array{2,2,6};
    auto input     = na::reshape(na::arange(ix::product(new_shape)),new_shape);
    auto dtype     = nm::None;
    auto initial   = nm::None;
    {
        auto keepdims = nm::True;
        VECTOR_256_TEST(multiply.reduce,unwrap(input),axis,dtype,initial,keepdims);
    }
    {
        auto keepdims = nm::False;
        VECTOR_256_TEST(multiply.reduce,unwrap(input),axis,dtype,initial,keepdims);
    }
    {
        auto keepdims = true;
        VECTOR_256_TEST(multiply.reduce,unwrap(input),axis,dtype,initial,keepdims);
    }
    {
        auto keepdims = false;
        VECTOR_256_TEST(multiply.reduce,unwrap(input),axis,dtype,initial,keepdims);
    }
}

TEST_CASE("multiply.reduce_nd(case2b)" * doctest::test_suite("simd::vector_256"))
{
    auto axis = meta::ct_v<1>;
    auto new_shape = nmtools_array{2,2,6};
    auto input     = na::reshape(na::arange(ix::product(new_shape)),new_shape);
    auto dtype     = nm::None;
    auto initial   = nm::None;
    {
        auto keepdims = nm::True;
        VECTOR_256_TEST(multiply.reduce,unwrap(input),axis,dtype,initial,keepdims);
    }
    {
        auto keepdims = nm::False;
        VECTOR_256_TEST(multiply.reduce,unwrap(input),axis,dtype,initial,keepdims);
    }
    {
        auto keepdims = true;
        VECTOR_256_TEST(multiply.reduce,unwrap(input),axis,dtype,initial,keepdims);
    }
    {
        auto keepdims = false;
        VECTOR_256_TEST(multiply.reduce,unwrap(input),axis,dtype,initial,keepdims);
    }
}

TEST_CASE("multiply.reduce_nd(case2c)" * doctest::test_suite("simd::vector_256"))
{
    auto axis = meta::ct_v<2>;
    auto new_shape = nmtools_array{2,2,6};
    auto input     = na::reshape(na::arange(ix::product(new_shape)),new_shape);
    auto dtype     = nm::None;
    auto initial   = nm::None;
    {
        auto keepdims = nm::True;
        VECTOR_256_TEST(multiply.reduce,unwrap(input),axis,dtype,initial,keepdims);
    }
    {
        auto keepdims = nm::False;
        VECTOR_256_TEST(multiply.reduce,unwrap(input),axis,dtype,initial,keepdims);
    }
    {
        auto keepdims = true;
        VECTOR_256_TEST(multiply.reduce,unwrap(input),axis,dtype,initial,keepdims);
    }
    {
        auto keepdims = false;
        VECTOR_256_TEST(multiply.reduce,unwrap(input),axis,dtype,initial,keepdims);
    }
}

TEST_CASE("multiply.reduce_nd(case3a)" * doctest::test_suite("simd::vector_256"))
{
    auto axis = meta::ct_v<0>;
    auto new_shape = nmtools_array{2,2,7};
    auto input     = na::reshape(na::arange(ix::product(new_shape)),new_shape);
    auto dtype     = nm::None;
    auto initial   = nm::None;
    {
        auto keepdims = nm::True;
        VECTOR_256_TEST(multiply.reduce,unwrap(input),axis,dtype,initial,keepdims);
    }
    {
        auto keepdims = nm::False;
        VECTOR_256_TEST(multiply.reduce,unwrap(input),axis,dtype,initial,keepdims);
    }
    {
        auto keepdims = true;
        VECTOR_256_TEST(multiply.reduce,unwrap(input),axis,dtype,initial,keepdims);
    }
    {
        auto keepdims = false;
        VECTOR_256_TEST(multiply.reduce,unwrap(input),axis,dtype,initial,keepdims);
    }
}

TEST_CASE("multiply.reduce_nd(case3b)" * doctest::test_suite("simd::vector_256"))
{
    auto axis = meta::ct_v<1>;
    auto new_shape = nmtools_array{2,2,7};
    auto input     = na::reshape(na::arange(ix::product(new_shape)),new_shape);
    auto dtype     = nm::None;
    auto initial   = nm::None;
    {
        auto keepdims = nm::True;
        VECTOR_256_TEST(multiply.reduce,unwrap(input),axis,dtype,initial,keepdims);
    }
    {
        auto keepdims = nm::False;
        VECTOR_256_TEST(multiply.reduce,unwrap(input),axis,dtype,initial,keepdims);
    }
    {
        auto keepdims = true;
        VECTOR_256_TEST(multiply.reduce,unwrap(input),axis,dtype,initial,keepdims);
    }
    {
        auto keepdims = false;
        VECTOR_256_TEST(multiply.reduce,unwrap(input),axis,dtype,initial,keepdims);
    }
}

TEST_CASE("multiply.reduce_nd(case3c)" * doctest::test_suite("simd::vector_256"))
{
    auto axis = meta::ct_v<2>;
    auto new_shape = nmtools_array{2,2,7};
    auto input     = na::reshape(na::arange(ix::product(new_shape)),new_shape);
    auto dtype     = nm::None;
    auto initial   = nm::None;
    {
        auto keepdims = nm::True;
        VECTOR_256_TEST(multiply.reduce,unwrap(input),axis,dtype,initial,keepdims);
    }
    {
        auto keepdims = nm::False;
        VECTOR_256_TEST(multiply.reduce,unwrap(input),axis,dtype,initial,keepdims);
    }
    {
        auto keepdims = true;
        VECTOR_256_TEST(multiply.reduce,unwrap(input),axis,dtype,initial,keepdims);
    }
    {
        auto keepdims = false;
        VECTOR_256_TEST(multiply.reduce,unwrap(input),axis,dtype,initial,keepdims);
    }
}

TEST_CASE("multiply.reduce_nd(case4a)" * doctest::test_suite("simd::vector_256"))
{
    auto axis = meta::ct_v<0>;
    auto new_shape = nmtools_array{2,2,8};
    auto input     = na::reshape(na::arange(ix::product(new_shape)),new_shape);
    auto dtype     = nm::None;
    auto initial   = nm::None;
    {
        auto keepdims = nm::True;
        VECTOR_256_TEST(multiply.reduce,unwrap(input),axis,dtype,initial,keepdims);
    }
    {
        auto keepdims = nm::False;
        VECTOR_256_TEST(multiply.reduce,unwrap(input),axis,dtype,initial,keepdims);
    }
    {
        auto keepdims = true;
        VECTOR_256_TEST(multiply.reduce,unwrap(input),axis,dtype,initial,keepdims);
    }
    {
        auto keepdims = false;
        VECTOR_256_TEST(multiply.reduce,unwrap(input),axis,dtype,initial,keepdims);
    }
}

TEST_CASE("multiply.reduce_nd(case4b)" * doctest::test_suite("simd::vector_256"))
{
    auto axis = meta::ct_v<1>;
    auto new_shape = nmtools_array{2,2,8};
    auto input     = na::reshape(na::arange(ix::product(new_shape)),new_shape);
    auto dtype     = nm::None;
    auto initial   = nm::None;
    {
        auto keepdims = nm::True;
        VECTOR_256_TEST(multiply.reduce,unwrap(input),axis,dtype,initial,keepdims);
    }
    {
        auto keepdims = nm::False;
        VECTOR_256_TEST(multiply.reduce,unwrap(input),axis,dtype,initial,keepdims);
    }
    {
        auto keepdims = true;
        VECTOR_256_TEST(multiply.reduce,unwrap(input),axis,dtype,initial,keepdims);
    }
    {
        auto keepdims = false;
        VECTOR_256_TEST(multiply.reduce,unwrap(input),axis,dtype,initial,keepdims);
    }
}

TEST_CASE("multiply.reduce_nd(case4c)" * doctest::test_suite("simd::vector_256"))
{
    auto axis = meta::ct_v<2>;
    auto new_shape = nmtools_array{2,2,8};
    auto input     = na::reshape(na::arange(ix::product(new_shape)),new_shape);
    auto dtype     = nm::None;
    auto initial   = nm::None;
    {
        auto keepdims = nm::True;
        VECTOR_256_TEST(multiply.reduce,unwrap(input),axis,dtype,initial,keepdims);
    }
    {
        auto keepdims = nm::False;
        VECTOR_256_TEST(multiply.reduce,unwrap(input),axis,dtype,initial,keepdims);
    }
    {
        auto keepdims = true;
        VECTOR_256_TEST(multiply.reduce,unwrap(input),axis,dtype,initial,keepdims);
    }
    {
        auto keepdims = false;
        VECTOR_256_TEST(multiply.reduce,unwrap(input),axis,dtype,initial,keepdims);
    }
}

/////////////////////////////////////////////////////////////////////////////////////

TEST_CASE("multiply.reduce_nd(case5a)" * doctest::test_suite("simd::vector_256"))
{
    auto axis = meta::ct_v<0>;
    auto new_shape = nmtools_array{3,2,5};
    auto input     = na::reshape(na::arange(ix::product(new_shape)),new_shape);
    auto dtype     = nm::None;
    auto initial   = nm::None;
    {
        auto keepdims = nm::True;
        VECTOR_256_TEST(multiply.reduce,unwrap(input),axis,dtype,initial,keepdims);
    }
    {
        auto keepdims = nm::False;
        VECTOR_256_TEST(multiply.reduce,unwrap(input),axis,dtype,initial,keepdims);
    }
    {
        auto keepdims = true;
        VECTOR_256_TEST(multiply.reduce,unwrap(input),axis,dtype,initial,keepdims);
    }
    {
        auto keepdims = false;
        VECTOR_256_TEST(multiply.reduce,unwrap(input),axis,dtype,initial,keepdims);
    }
}

TEST_CASE("multiply.reduce_nd(case5b)" * doctest::test_suite("simd::vector_256"))
{
    auto axis = meta::ct_v<1>;
    auto new_shape = nmtools_array{3,2,5};
    auto input     = na::reshape(na::arange(ix::product(new_shape)),new_shape);
    auto dtype     = nm::None;
    auto initial   = nm::None;
    {
        auto keepdims = nm::True;
        VECTOR_256_TEST(multiply.reduce,unwrap(input),axis,dtype,initial,keepdims);
    }
    {
        auto keepdims = nm::False;
        VECTOR_256_TEST(multiply.reduce,unwrap(input),axis,dtype,initial,keepdims);
    }
    {
        auto keepdims = true;
        VECTOR_256_TEST(multiply.reduce,unwrap(input),axis,dtype,initial,keepdims);
    }
    {
        auto keepdims = false;
        VECTOR_256_TEST(multiply.reduce,unwrap(input),axis,dtype,initial,keepdims);
    }
}

TEST_CASE("multiply.reduce_nd(casec)" * doctest::test_suite("simd::vector_256"))
{
    auto axis = meta::ct_v<2>;
    auto new_shape = nmtools_array{3,2,5};
    auto input     = na::reshape(na::arange(ix::product(new_shape)),new_shape);
    auto dtype     = nm::None;
    auto initial   = nm::None;
    {
        auto keepdims = nm::True;
        VECTOR_256_TEST(multiply.reduce,unwrap(input),axis,dtype,initial,keepdims);
    }
    {
        auto keepdims = nm::False;
        VECTOR_256_TEST(multiply.reduce,unwrap(input),axis,dtype,initial,keepdims);
    }
    {
        auto keepdims = true;
        VECTOR_256_TEST(multiply.reduce,unwrap(input),axis,dtype,initial,keepdims);
    }
    {
        auto keepdims = false;
        VECTOR_256_TEST(multiply.reduce,unwrap(input),axis,dtype,initial,keepdims);
    }
}

TEST_CASE("multiply.reduce_nd(case6a)" * doctest::test_suite("simd::vector_256"))
{
    auto axis = meta::ct_v<0>;
    auto new_shape = nmtools_array{3,2,6};
    auto input     = na::reshape(na::arange(ix::product(new_shape)),new_shape);
    auto dtype     = nm::None;
    auto initial   = nm::None;
    {
        auto keepdims = nm::True;
        VECTOR_256_TEST(multiply.reduce,unwrap(input),axis,dtype,initial,keepdims);
    }
    {
        auto keepdims = nm::False;
        VECTOR_256_TEST(multiply.reduce,unwrap(input),axis,dtype,initial,keepdims);
    }
    {
        auto keepdims = true;
        VECTOR_256_TEST(multiply.reduce,unwrap(input),axis,dtype,initial,keepdims);
    }
    {
        auto keepdims = false;
        VECTOR_256_TEST(multiply.reduce,unwrap(input),axis,dtype,initial,keepdims);
    }
}

TEST_CASE("multiply.reduce_nd(case6b)" * doctest::test_suite("simd::vector_256"))
{
    auto axis = meta::ct_v<1>;
    auto new_shape = nmtools_array{3,2,6};
    auto input     = na::reshape(na::arange(ix::product(new_shape)),new_shape);
    auto dtype     = nm::None;
    auto initial   = nm::None;
    {
        auto keepdims = nm::True;
        VECTOR_256_TEST(multiply.reduce,unwrap(input),axis,dtype,initial,keepdims);
    }
    {
        auto keepdims = nm::False;
        VECTOR_256_TEST(multiply.reduce,unwrap(input),axis,dtype,initial,keepdims);
    }
    {
        auto keepdims = true;
        VECTOR_256_TEST(multiply.reduce,unwrap(input),axis,dtype,initial,keepdims);
    }
    {
        auto keepdims = false;
        VECTOR_256_TEST(multiply.reduce,unwrap(input),axis,dtype,initial,keepdims);
    }
}

TEST_CASE("multiply.reduce_nd(case6c)" * doctest::test_suite("simd::vector_256"))
{
    auto axis = meta::ct_v<2>;
    auto new_shape = nmtools_array{3,2,6};
    auto input     = na::reshape(na::arange(ix::product(new_shape)),new_shape);
    auto dtype     = nm::None;
    auto initial   = nm::None;
    {
        auto keepdims = nm::True;
        VECTOR_256_TEST(multiply.reduce,unwrap(input),axis,dtype,initial,keepdims);
    }
    {
        auto keepdims = nm::False;
        VECTOR_256_TEST(multiply.reduce,unwrap(input),axis,dtype,initial,keepdims);
    }
    {
        auto keepdims = true;
        VECTOR_256_TEST(multiply.reduce,unwrap(input),axis,dtype,initial,keepdims);
    }
    {
        auto keepdims = false;
        VECTOR_256_TEST(multiply.reduce,unwrap(input),axis,dtype,initial,keepdims);
    }
}

TEST_CASE("multiply.reduce_nd(case7a)" * doctest::test_suite("simd::vector_256"))
{
    auto axis = meta::ct_v<0>;
    auto new_shape = nmtools_array{3,2,7};
    auto input     = na::reshape(na::arange(ix::product(new_shape)),new_shape);
    auto dtype     = nm::None;
    auto initial   = nm::None;
    {
        auto keepdims = nm::True;
        VECTOR_256_TEST(multiply.reduce,unwrap(input),axis,dtype,initial,keepdims);
    }
    {
        auto keepdims = nm::False;
        VECTOR_256_TEST(multiply.reduce,unwrap(input),axis,dtype,initial,keepdims);
    }
    {
        auto keepdims = true;
        VECTOR_256_TEST(multiply.reduce,unwrap(input),axis,dtype,initial,keepdims);
    }
    {
        auto keepdims = false;
        VECTOR_256_TEST(multiply.reduce,unwrap(input),axis,dtype,initial,keepdims);
    }
}

TEST_CASE("multiply.reduce_nd(case7b)" * doctest::test_suite("simd::vector_256"))
{
    auto axis = meta::ct_v<1>;
    auto new_shape = nmtools_array{3,2,7};
    auto input     = na::reshape(na::arange(ix::product(new_shape)),new_shape);
    auto dtype     = nm::None;
    auto initial   = nm::None;
    {
        auto keepdims = nm::True;
        VECTOR_256_TEST(multiply.reduce,unwrap(input),axis,dtype,initial,keepdims);
    }
    {
        auto keepdims = nm::False;
        VECTOR_256_TEST(multiply.reduce,unwrap(input),axis,dtype,initial,keepdims);
    }
    {
        auto keepdims = true;
        VECTOR_256_TEST(multiply.reduce,unwrap(input),axis,dtype,initial,keepdims);
    }
    {
        auto keepdims = false;
        VECTOR_256_TEST(multiply.reduce,unwrap(input),axis,dtype,initial,keepdims);
    }
}

TEST_CASE("multiply.reduce_nd(case7c)" * doctest::test_suite("simd::vector_256"))
{
    auto axis = meta::ct_v<2>;
    auto new_shape = nmtools_array{3,2,7};
    auto input     = na::reshape(na::arange(ix::product(new_shape)),new_shape);
    auto dtype     = nm::None;
    auto initial   = nm::None;
    {
        auto keepdims = nm::True;
        VECTOR_256_TEST(multiply.reduce,unwrap(input),axis,dtype,initial,keepdims);
    }
    {
        auto keepdims = nm::False;
        VECTOR_256_TEST(multiply.reduce,unwrap(input),axis,dtype,initial,keepdims);
    }
    {
        auto keepdims = true;
        VECTOR_256_TEST(multiply.reduce,unwrap(input),axis,dtype,initial,keepdims);
    }
    {
        auto keepdims = false;
        VECTOR_256_TEST(multiply.reduce,unwrap(input),axis,dtype,initial,keepdims);
    }
}

TEST_CASE("multiply.reduce_nd(case8a)" * doctest::test_suite("simd::vector_256"))
{
    auto axis = meta::ct_v<0>;
    auto new_shape = nmtools_array{3,2,8};
    auto input     = na::reshape(na::arange(ix::product(new_shape)),new_shape);
    auto dtype     = nm::None;
    auto initial   = nm::None;
    {
        auto keepdims = nm::True;
        VECTOR_256_TEST(multiply.reduce,unwrap(input),axis,dtype,initial,keepdims);
    }
    {
        auto keepdims = nm::False;
        VECTOR_256_TEST(multiply.reduce,unwrap(input),axis,dtype,initial,keepdims);
    }
    {
        auto keepdims = true;
        VECTOR_256_TEST(multiply.reduce,unwrap(input),axis,dtype,initial,keepdims);
    }
    {
        auto keepdims = false;
        VECTOR_256_TEST(multiply.reduce,unwrap(input),axis,dtype,initial,keepdims);
    }
}

TEST_CASE("multiply.reduce_nd(case8b)" * doctest::test_suite("simd::vector_256"))
{
    auto axis = meta::ct_v<1>;
    auto new_shape = nmtools_array{3,2,8};
    auto input     = na::reshape(na::arange(ix::product(new_shape)),new_shape);
    auto dtype     = nm::None;
    auto initial   = nm::None;
    {
        auto keepdims = nm::True;
        VECTOR_256_TEST(multiply.reduce,unwrap(input),axis,dtype,initial,keepdims);
    }
    {
        auto keepdims = nm::False;
        VECTOR_256_TEST(multiply.reduce,unwrap(input),axis,dtype,initial,keepdims);
    }
    {
        auto keepdims = true;
        VECTOR_256_TEST(multiply.reduce,unwrap(input),axis,dtype,initial,keepdims);
    }
    {
        auto keepdims = false;
        VECTOR_256_TEST(multiply.reduce,unwrap(input),axis,dtype,initial,keepdims);
    }
}

TEST_CASE("multiply.reduce_nd(case8c)" * doctest::test_suite("simd::vector_256"))
{
    auto axis = meta::ct_v<2>;
    auto new_shape = nmtools_array{3,2,8};
    auto input     = na::reshape(na::arange(ix::product(new_shape)),new_shape);
    auto dtype     = nm::None;
    auto initial   = nm::None;
    {
        auto keepdims = nm::True;
        VECTOR_256_TEST(multiply.reduce,unwrap(input),axis,dtype,initial,keepdims);
    }
    {
        auto keepdims = nm::False;
        VECTOR_256_TEST(multiply.reduce,unwrap(input),axis,dtype,initial,keepdims);
    }
    {
        auto keepdims = true;
        VECTOR_256_TEST(multiply.reduce,unwrap(input),axis,dtype,initial,keepdims);
    }
    {
        auto keepdims = false;
        VECTOR_256_TEST(multiply.reduce,unwrap(input),axis,dtype,initial,keepdims);
    }
}

///////////////////////////////////////////////////////////////////////////

TEST_CASE("multiply.reduce_nd(case9a)" * doctest::test_suite("simd::vector_256"))
{
    auto axis = meta::ct_v<0>;
    auto new_shape = nmtools_array{3,3,5};
    auto input     = na::reshape(na::arange(ix::product(new_shape)),new_shape);
    auto dtype     = nm::None;
    auto initial   = nm::None;
    {
        auto keepdims = nm::True;
        VECTOR_256_TEST(multiply.reduce,unwrap(input),axis,dtype,initial,keepdims);
    }
    {
        auto keepdims = nm::False;
        VECTOR_256_TEST(multiply.reduce,unwrap(input),axis,dtype,initial,keepdims);
    }
    {
        auto keepdims = true;
        VECTOR_256_TEST(multiply.reduce,unwrap(input),axis,dtype,initial,keepdims);
    }
    {
        auto keepdims = false;
        VECTOR_256_TEST(multiply.reduce,unwrap(input),axis,dtype,initial,keepdims);
    }
}

TEST_CASE("multiply.reduce_nd(case9b)" * doctest::test_suite("simd::vector_256"))
{
    auto axis = meta::ct_v<1>;
    auto new_shape = nmtools_array{3,3,5};
    auto input     = na::reshape(na::arange(ix::product(new_shape)),new_shape);
    auto dtype     = nm::None;
    auto initial   = nm::None;
    {
        auto keepdims = nm::True;
        VECTOR_256_TEST(multiply.reduce,unwrap(input),axis,dtype,initial,keepdims);
    }
    {
        auto keepdims = nm::False;
        VECTOR_256_TEST(multiply.reduce,unwrap(input),axis,dtype,initial,keepdims);
    }
    {
        auto keepdims = true;
        VECTOR_256_TEST(multiply.reduce,unwrap(input),axis,dtype,initial,keepdims);
    }
    {
        auto keepdims = false;
        VECTOR_256_TEST(multiply.reduce,unwrap(input),axis,dtype,initial,keepdims);
    }
}

TEST_CASE("multiply.reduce_nd(case9c)" * doctest::test_suite("simd::vector_256"))
{
    auto axis = meta::ct_v<2>;
    auto new_shape = nmtools_array{3,3,5};
    auto input     = na::reshape(na::arange(ix::product(new_shape)),new_shape);
    auto dtype     = nm::None;
    auto initial   = nm::None;
    {
        auto keepdims = nm::True;
        VECTOR_256_TEST(multiply.reduce,unwrap(input),axis,dtype,initial,keepdims);
    }
    {
        auto keepdims = nm::False;
        VECTOR_256_TEST(multiply.reduce,unwrap(input),axis,dtype,initial,keepdims);
    }
    {
        auto keepdims = true;
        VECTOR_256_TEST(multiply.reduce,unwrap(input),axis,dtype,initial,keepdims);
    }
    {
        auto keepdims = false;
        VECTOR_256_TEST(multiply.reduce,unwrap(input),axis,dtype,initial,keepdims);
    }
}

TEST_CASE("multiply.reduce_nd(case10a)" * doctest::test_suite("simd::vector_256"))
{
    auto axis = meta::ct_v<0>;
    auto new_shape = nmtools_array{3,3,6};
    auto input     = na::reshape(na::arange(ix::product(new_shape)),new_shape);
    auto dtype     = nm::None;
    auto initial   = nm::None;
    {
        auto keepdims = nm::True;
        VECTOR_256_TEST(multiply.reduce,unwrap(input),axis,dtype,initial,keepdims);
    }
    {
        auto keepdims = nm::False;
        VECTOR_256_TEST(multiply.reduce,unwrap(input),axis,dtype,initial,keepdims);
    }
    {
        auto keepdims = true;
        VECTOR_256_TEST(multiply.reduce,unwrap(input),axis,dtype,initial,keepdims);
    }
    {
        auto keepdims = false;
        VECTOR_256_TEST(multiply.reduce,unwrap(input),axis,dtype,initial,keepdims);
    }
}

TEST_CASE("multiply.reduce_nd(case10b)" * doctest::test_suite("simd::vector_256"))
{
    auto axis = meta::ct_v<1>;
    auto new_shape = nmtools_array{3,3,6};
    auto input     = na::reshape(na::arange(ix::product(new_shape)),new_shape);
    auto dtype     = nm::None;
    auto initial   = nm::None;
    {
        auto keepdims = nm::True;
        VECTOR_256_TEST(multiply.reduce,unwrap(input),axis,dtype,initial,keepdims);
    }
    {
        auto keepdims = nm::False;
        VECTOR_256_TEST(multiply.reduce,unwrap(input),axis,dtype,initial,keepdims);
    }
    {
        auto keepdims = true;
        VECTOR_256_TEST(multiply.reduce,unwrap(input),axis,dtype,initial,keepdims);
    }
    {
        auto keepdims = false;
        VECTOR_256_TEST(multiply.reduce,unwrap(input),axis,dtype,initial,keepdims);
    }
}

TEST_CASE("multiply.reduce_nd(case10c)" * doctest::test_suite("simd::vector_256"))
{
    auto axis = meta::ct_v<2>;
    auto new_shape = nmtools_array{3,3,6};
    auto input     = na::reshape(na::arange(ix::product(new_shape)),new_shape);
    auto dtype     = nm::None;
    auto initial   = nm::None;
    {
        auto keepdims = nm::True;
        VECTOR_256_TEST(multiply.reduce,unwrap(input),axis,dtype,initial,keepdims);
    }
    {
        auto keepdims = nm::False;
        VECTOR_256_TEST(multiply.reduce,unwrap(input),axis,dtype,initial,keepdims);
    }
    {
        auto keepdims = true;
        VECTOR_256_TEST(multiply.reduce,unwrap(input),axis,dtype,initial,keepdims);
    }
    {
        auto keepdims = false;
        VECTOR_256_TEST(multiply.reduce,unwrap(input),axis,dtype,initial,keepdims);
    }
}

TEST_CASE("multiply.reduce_nd(case11a)" * doctest::test_suite("simd::vector_256"))
{
    auto axis = meta::ct_v<0>;
    auto new_shape = nmtools_array{3,3,7};
    auto input     = na::reshape(na::arange(ix::product(new_shape)),new_shape);
    auto dtype     = nm::None;
    auto initial   = nm::None;
    {
        auto keepdims = nm::True;
        VECTOR_256_TEST(multiply.reduce,unwrap(input),axis,dtype,initial,keepdims);
    }
    {
        auto keepdims = nm::False;
        VECTOR_256_TEST(multiply.reduce,unwrap(input),axis,dtype,initial,keepdims);
    }
    {
        auto keepdims = true;
        VECTOR_256_TEST(multiply.reduce,unwrap(input),axis,dtype,initial,keepdims);
    }
    {
        auto keepdims = false;
        VECTOR_256_TEST(multiply.reduce,unwrap(input),axis,dtype,initial,keepdims);
    }
}

TEST_CASE("multiply.reduce_nd(case11b)" * doctest::test_suite("simd::vector_256"))
{
    auto axis = meta::ct_v<1>;
    auto new_shape = nmtools_array{3,3,7};
    auto input     = na::reshape(na::arange(ix::product(new_shape)),new_shape);
    auto dtype     = nm::None;
    auto initial   = nm::None;
    {
        auto keepdims = nm::True;
        VECTOR_256_TEST(multiply.reduce,unwrap(input),axis,dtype,initial,keepdims);
    }
    {
        auto keepdims = nm::False;
        VECTOR_256_TEST(multiply.reduce,unwrap(input),axis,dtype,initial,keepdims);
    }
    {
        auto keepdims = true;
        VECTOR_256_TEST(multiply.reduce,unwrap(input),axis,dtype,initial,keepdims);
    }
    {
        auto keepdims = false;
        VECTOR_256_TEST(multiply.reduce,unwrap(input),axis,dtype,initial,keepdims);
    }
}

TEST_CASE("multiply.reduce_nd(case11c)" * doctest::test_suite("simd::vector_256"))
{
    auto axis = meta::ct_v<2>;
    auto new_shape = nmtools_array{3,3,7};
    auto input     = na::reshape(na::arange(ix::product(new_shape)),new_shape);
    auto dtype     = nm::None;
    auto initial   = nm::None;
    {
        auto keepdims = nm::True;
        VECTOR_256_TEST(multiply.reduce,unwrap(input),axis,dtype,initial,keepdims);
    }
    {
        auto keepdims = nm::False;
        VECTOR_256_TEST(multiply.reduce,unwrap(input),axis,dtype,initial,keepdims);
    }
    {
        auto keepdims = true;
        VECTOR_256_TEST(multiply.reduce,unwrap(input),axis,dtype,initial,keepdims);
    }
    {
        auto keepdims = false;
        VECTOR_256_TEST(multiply.reduce,unwrap(input),axis,dtype,initial,keepdims);
    }
}

TEST_CASE("multiply.reduce_nd(case12a)" * doctest::test_suite("simd::vector_256"))
{
    auto axis = meta::ct_v<0>;
    auto new_shape = nmtools_array{3,3,8};
    auto input     = na::reshape(na::arange(ix::product(new_shape)),new_shape);
    auto dtype     = nm::None;
    auto initial   = nm::None;
    {
        auto keepdims = nm::True;
        VECTOR_256_TEST(multiply.reduce,unwrap(input),axis,dtype,initial,keepdims);
    }
    {
        auto keepdims = nm::False;
        VECTOR_256_TEST(multiply.reduce,unwrap(input),axis,dtype,initial,keepdims);
    }
    {
        auto keepdims = true;
        VECTOR_256_TEST(multiply.reduce,unwrap(input),axis,dtype,initial,keepdims);
    }
    {
        auto keepdims = false;
        VECTOR_256_TEST(multiply.reduce,unwrap(input),axis,dtype,initial,keepdims);
    }
}

TEST_CASE("multiply.reduce_nd(case12b)" * doctest::test_suite("simd::vector_256"))
{
    auto axis = meta::ct_v<1>;
    auto new_shape = nmtools_array{3,3,8};
    auto input     = na::reshape(na::arange(ix::product(new_shape)),new_shape);
    auto dtype     = nm::None;
    auto initial   = nm::None;
    {
        auto keepdims = nm::True;
        VECTOR_256_TEST(multiply.reduce,unwrap(input),axis,dtype,initial,keepdims);
    }
    {
        auto keepdims = nm::False;
        VECTOR_256_TEST(multiply.reduce,unwrap(input),axis,dtype,initial,keepdims);
    }
    {
        auto keepdims = true;
        VECTOR_256_TEST(multiply.reduce,unwrap(input),axis,dtype,initial,keepdims);
    }
    {
        auto keepdims = false;
        VECTOR_256_TEST(multiply.reduce,unwrap(input),axis,dtype,initial,keepdims);
    }
}

TEST_CASE("multiply.reduce_nd(case12c)" * doctest::test_suite("simd::vector_256"))
{
    auto axis = meta::ct_v<2>;
    auto new_shape = nmtools_array{3,3,8};
    auto input     = na::reshape(na::arange(ix::product(new_shape)),new_shape);
    auto dtype     = nm::None;
    auto initial   = nm::None;
    {
        auto keepdims = nm::True;
        VECTOR_256_TEST(multiply.reduce,unwrap(input),axis,dtype,initial,keepdims);
    }
    {
        auto keepdims = nm::False;
        VECTOR_256_TEST(multiply.reduce,unwrap(input),axis,dtype,initial,keepdims);
    }
    {
        auto keepdims = true;
        VECTOR_256_TEST(multiply.reduce,unwrap(input),axis,dtype,initial,keepdims);
    }
    {
        auto keepdims = false;
        VECTOR_256_TEST(multiply.reduce,unwrap(input),axis,dtype,initial,keepdims);
    }
}

//////////////////////////////////////////////////////////////////////////////////////


TEST_CASE("multiply.reduce_nd(case13a)" * doctest::test_suite("simd::vector_256"))
{
    auto axis = 0;
    auto new_shape = nmtools_array{3,3,5};
    auto input     = na::reshape(na::arange(ix::product(new_shape)),new_shape);
    auto dtype     = nm::None;
    auto initial   = nm::None;
    {
        auto keepdims = nm::True;
        VECTOR_256_TEST(multiply.reduce,unwrap(input),axis,dtype,initial,keepdims);
    }
    {
        auto keepdims = nm::False;
        VECTOR_256_TEST(multiply.reduce,unwrap(input),axis,dtype,initial,keepdims);
    }
    {
        auto keepdims = true;
        VECTOR_256_TEST(multiply.reduce,unwrap(input),axis,dtype,initial,keepdims);
    }
    {
        auto keepdims = false;
        VECTOR_256_TEST(multiply.reduce,unwrap(input),axis,dtype,initial,keepdims);
    }
}

TEST_CASE("multiply.reduce_nd(case13b)" * doctest::test_suite("simd::vector_256"))
{
    auto axis = 1;
    auto new_shape = nmtools_array{3,3,5};
    auto input     = na::reshape(na::arange(ix::product(new_shape)),new_shape);
    auto dtype     = nm::None;
    auto initial   = nm::None;
    {
        auto keepdims = nm::True;
        VECTOR_256_TEST(multiply.reduce,unwrap(input),axis,dtype,initial,keepdims);
    }
    {
        auto keepdims = nm::False;
        VECTOR_256_TEST(multiply.reduce,unwrap(input),axis,dtype,initial,keepdims);
    }
    {
        auto keepdims = true;
        VECTOR_256_TEST(multiply.reduce,unwrap(input),axis,dtype,initial,keepdims);
    }
    {
        auto keepdims = false;
        VECTOR_256_TEST(multiply.reduce,unwrap(input),axis,dtype,initial,keepdims);
    }
}

TEST_CASE("multiply.reduce_nd(case13c)" * doctest::test_suite("simd::vector_256"))
{
    auto axis = 2;
    auto new_shape = nmtools_array{3,3,5};
    auto input     = na::reshape(na::arange(ix::product(new_shape)),new_shape);
    auto dtype     = nm::None;
    auto initial   = nm::None;
    {
        auto keepdims = nm::True;
        VECTOR_256_TEST(multiply.reduce,unwrap(input),axis,dtype,initial,keepdims);
    }
    {
        auto keepdims = nm::False;
        VECTOR_256_TEST(multiply.reduce,unwrap(input),axis,dtype,initial,keepdims);
    }
    {
        auto keepdims = true;
        VECTOR_256_TEST(multiply.reduce,unwrap(input),axis,dtype,initial,keepdims);
    }
    {
        auto keepdims = false;
        VECTOR_256_TEST(multiply.reduce,unwrap(input),axis,dtype,initial,keepdims);
    }
}

TEST_CASE("multiply.reduce_nd(case14a)" * doctest::test_suite("simd::vector_256"))
{
    auto axis = 0;
    auto new_shape = nmtools_array{3,3,6};
    auto input     = na::reshape(na::arange(ix::product(new_shape)),new_shape);
    auto dtype     = nm::None;
    auto initial   = nm::None;
    {
        auto keepdims = nm::True;
        VECTOR_256_TEST(multiply.reduce,unwrap(input),axis,dtype,initial,keepdims);
    }
    {
        auto keepdims = nm::False;
        VECTOR_256_TEST(multiply.reduce,unwrap(input),axis,dtype,initial,keepdims);
    }
    {
        auto keepdims = true;
        VECTOR_256_TEST(multiply.reduce,unwrap(input),axis,dtype,initial,keepdims);
    }
    {
        auto keepdims = false;
        VECTOR_256_TEST(multiply.reduce,unwrap(input),axis,dtype,initial,keepdims);
    }
}

TEST_CASE("multiply.reduce_nd(case14b)" * doctest::test_suite("simd::vector_256"))
{
    auto axis = 1;
    auto new_shape = nmtools_array{3,3,6};
    auto input     = na::reshape(na::arange(ix::product(new_shape)),new_shape);
    auto dtype     = nm::None;
    auto initial   = nm::None;
    {
        auto keepdims = nm::True;
        VECTOR_256_TEST(multiply.reduce,unwrap(input),axis,dtype,initial,keepdims);
    }
    {
        auto keepdims = nm::False;
        VECTOR_256_TEST(multiply.reduce,unwrap(input),axis,dtype,initial,keepdims);
    }
    {
        auto keepdims = true;
        VECTOR_256_TEST(multiply.reduce,unwrap(input),axis,dtype,initial,keepdims);
    }
    {
        auto keepdims = false;
        VECTOR_256_TEST(multiply.reduce,unwrap(input),axis,dtype,initial,keepdims);
    }
}

TEST_CASE("multiply.reduce_nd(case14c)" * doctest::test_suite("simd::vector_256"))
{
    auto axis = 2;
    auto new_shape = nmtools_array{3,3,6};
    auto input     = na::reshape(na::arange(ix::product(new_shape)),new_shape);
    auto dtype     = nm::None;
    auto initial   = nm::None;
    {
        auto keepdims = nm::True;
        VECTOR_256_TEST(multiply.reduce,unwrap(input),axis,dtype,initial,keepdims);
    }
    {
        auto keepdims = nm::False;
        VECTOR_256_TEST(multiply.reduce,unwrap(input),axis,dtype,initial,keepdims);
    }
    {
        auto keepdims = true;
        VECTOR_256_TEST(multiply.reduce,unwrap(input),axis,dtype,initial,keepdims);
    }
    {
        auto keepdims = false;
        VECTOR_256_TEST(multiply.reduce,unwrap(input),axis,dtype,initial,keepdims);
    }
}

TEST_CASE("multiply.reduce_nd(case15a)" * doctest::test_suite("simd::vector_256"))
{
    auto axis = 0;
    auto new_shape = nmtools_array{3,3,7};
    auto input     = na::reshape(na::arange(ix::product(new_shape)),new_shape);
    auto dtype     = nm::None;
    auto initial   = nm::None;
    {
        auto keepdims = nm::True;
        VECTOR_256_TEST(multiply.reduce,unwrap(input),axis,dtype,initial,keepdims);
    }
    {
        auto keepdims = nm::False;
        VECTOR_256_TEST(multiply.reduce,unwrap(input),axis,dtype,initial,keepdims);
    }
    {
        auto keepdims = true;
        VECTOR_256_TEST(multiply.reduce,unwrap(input),axis,dtype,initial,keepdims);
    }
    {
        auto keepdims = false;
        VECTOR_256_TEST(multiply.reduce,unwrap(input),axis,dtype,initial,keepdims);
    }
}

TEST_CASE("multiply.reduce_nd(case15b)" * doctest::test_suite("simd::vector_256"))
{
    auto axis = 1;
    auto new_shape = nmtools_array{3,3,7};
    auto input     = na::reshape(na::arange(ix::product(new_shape)),new_shape);
    auto dtype     = nm::None;
    auto initial   = nm::None;
    {
        auto keepdims = nm::True;
        VECTOR_256_TEST(multiply.reduce,unwrap(input),axis,dtype,initial,keepdims);
    }
    {
        auto keepdims = nm::False;
        VECTOR_256_TEST(multiply.reduce,unwrap(input),axis,dtype,initial,keepdims);
    }
    {
        auto keepdims = true;
        VECTOR_256_TEST(multiply.reduce,unwrap(input),axis,dtype,initial,keepdims);
    }
    {
        auto keepdims = false;
        VECTOR_256_TEST(multiply.reduce,unwrap(input),axis,dtype,initial,keepdims);
    }
}

TEST_CASE("multiply.reduce_nd(case15c)" * doctest::test_suite("simd::vector_256"))
{
    auto axis = 2;
    auto new_shape = nmtools_array{3,3,7};
    auto input     = na::reshape(na::arange(ix::product(new_shape)),new_shape);
    auto dtype     = nm::None;
    auto initial   = nm::None;
    {
        auto keepdims = nm::True;
        VECTOR_256_TEST(multiply.reduce,unwrap(input),axis,dtype,initial,keepdims);
    }
    {
        auto keepdims = nm::False;
        VECTOR_256_TEST(multiply.reduce,unwrap(input),axis,dtype,initial,keepdims);
    }
    {
        auto keepdims = true;
        VECTOR_256_TEST(multiply.reduce,unwrap(input),axis,dtype,initial,keepdims);
    }
    {
        auto keepdims = false;
        VECTOR_256_TEST(multiply.reduce,unwrap(input),axis,dtype,initial,keepdims);
    }
}

TEST_CASE("multiply.reduce_nd(case16a)" * doctest::test_suite("simd::vector_256"))
{
    auto axis = 0;
    auto new_shape = nmtools_array{3,3,8};
    auto input     = na::reshape(na::arange(ix::product(new_shape)),new_shape);
    auto dtype     = nm::None;
    auto initial   = nm::None;
    {
        auto keepdims = nm::True;
        VECTOR_256_TEST(multiply.reduce,unwrap(input),axis,dtype,initial,keepdims);
    }
    {
        auto keepdims = nm::False;
        VECTOR_256_TEST(multiply.reduce,unwrap(input),axis,dtype,initial,keepdims);
    }
    {
        auto keepdims = true;
        VECTOR_256_TEST(multiply.reduce,unwrap(input),axis,dtype,initial,keepdims);
    }
    {
        auto keepdims = false;
        VECTOR_256_TEST(multiply.reduce,unwrap(input),axis,dtype,initial,keepdims);
    }
}

TEST_CASE("multiply.reduce_nd(case16b)" * doctest::test_suite("simd::vector_256"))
{
    auto axis = 1;
    auto new_shape = nmtools_array{3,3,8};
    auto input     = na::reshape(na::arange(ix::product(new_shape)),new_shape);
    auto dtype     = nm::None;
    auto initial   = nm::None;
    {
        auto keepdims = nm::True;
        VECTOR_256_TEST(multiply.reduce,unwrap(input),axis,dtype,initial,keepdims);
    }
    {
        auto keepdims = nm::False;
        VECTOR_256_TEST(multiply.reduce,unwrap(input),axis,dtype,initial,keepdims);
    }
    {
        auto keepdims = true;
        VECTOR_256_TEST(multiply.reduce,unwrap(input),axis,dtype,initial,keepdims);
    }
    {
        auto keepdims = false;
        VECTOR_256_TEST(multiply.reduce,unwrap(input),axis,dtype,initial,keepdims);
    }
}

TEST_CASE("multiply.reduce_nd(case16c)" * doctest::test_suite("simd::vector_256"))
{
    auto axis = 2;
    auto new_shape = nmtools_array{3,3,8};
    auto input     = na::reshape(na::arange(ix::product(new_shape)),new_shape);
    auto dtype     = nm::None;
    auto initial   = nm::None;
    {
        auto keepdims = nm::True;
        VECTOR_256_TEST(multiply.reduce,unwrap(input),axis,dtype,initial,keepdims);
    }
    {
        auto keepdims = nm::False;
        VECTOR_256_TEST(multiply.reduce,unwrap(input),axis,dtype,initial,keepdims);
    }
    {
        auto keepdims = true;
        VECTOR_256_TEST(multiply.reduce,unwrap(input),axis,dtype,initial,keepdims);
    }
    {
        auto keepdims = false;
        VECTOR_256_TEST(multiply.reduce,unwrap(input),axis,dtype,initial,keepdims);
    }
}

//////////////////////////////////////////////////////////////////////////////

TEST_CASE("multiply.reduce_nd(case17a)" * doctest::test_suite("simd::vector_256"))
{
    auto axis = 0;
    auto new_shape = nmtools_array{12,3,3,8};
    auto input     = na::reshape(na::arange(ix::product(new_shape)),new_shape);
    auto dtype     = nm::None;
    auto initial   = nm::None;
    {
        auto keepdims = nm::True;
        VECTOR_256_TEST(multiply.reduce,unwrap(input),axis,dtype,initial,keepdims);
    }
    {
        auto keepdims = nm::False;
        VECTOR_256_TEST(multiply.reduce,unwrap(input),axis,dtype,initial,keepdims);
    }
    {
        auto keepdims = true;
        VECTOR_256_TEST(multiply.reduce,unwrap(input),axis,dtype,initial,keepdims);
    }
    {
        auto keepdims = false;
        VECTOR_256_TEST(multiply.reduce,unwrap(input),axis,dtype,initial,keepdims);
    }
}

TEST_CASE("multiply.reduce_nd(case17b)" * doctest::test_suite("simd::vector_256"))
{
    auto axis = 1;
    auto new_shape = nmtools_array{12,3,3,8};
    auto input     = na::reshape(na::arange(ix::product(new_shape)),new_shape);
    auto dtype     = nm::None;
    auto initial   = nm::None;
    {
        auto keepdims = nm::True;
        VECTOR_256_TEST(multiply.reduce,unwrap(input),axis,dtype,initial,keepdims);
    }
    {
        auto keepdims = nm::False;
        VECTOR_256_TEST(multiply.reduce,unwrap(input),axis,dtype,initial,keepdims);
    }
    {
        auto keepdims = true;
        VECTOR_256_TEST(multiply.reduce,unwrap(input),axis,dtype,initial,keepdims);
    }
    {
        auto keepdims = false;
        VECTOR_256_TEST(multiply.reduce,unwrap(input),axis,dtype,initial,keepdims);
    }
}

TEST_CASE("multiply.reduce_nd(case17c)" * doctest::test_suite("simd::vector_256"))
{
    auto axis = 2;
    auto new_shape = nmtools_array{12,3,3,8};
    auto input     = na::reshape(na::arange(ix::product(new_shape)),new_shape);
    auto dtype     = nm::None;
    auto initial   = nm::None;
    {
        auto keepdims = nm::True;
        VECTOR_256_TEST(multiply.reduce,unwrap(input),axis,dtype,initial,keepdims);
    }
    {
        auto keepdims = nm::False;
        VECTOR_256_TEST(multiply.reduce,unwrap(input),axis,dtype,initial,keepdims);
    }
    {
        auto keepdims = true;
        VECTOR_256_TEST(multiply.reduce,unwrap(input),axis,dtype,initial,keepdims);
    }
    {
        auto keepdims = false;
        VECTOR_256_TEST(multiply.reduce,unwrap(input),axis,dtype,initial,keepdims);
    }
}

TEST_CASE("multiply.reduce_nd(case17d)" * doctest::test_suite("simd::vector_256"))
{
    auto axis = 3;
    auto new_shape = nmtools_array{12,3,3,8};
    auto input     = na::reshape(na::arange(ix::product(new_shape)),new_shape);
    auto dtype     = nm::None;
    auto initial   = nm::None;
    {
        auto keepdims = nm::True;
        VECTOR_256_TEST(multiply.reduce,unwrap(input),axis,dtype,initial,keepdims);
    }
    {
        auto keepdims = nm::False;
        VECTOR_256_TEST(multiply.reduce,unwrap(input),axis,dtype,initial,keepdims);
    }
    {
        auto keepdims = true;
        VECTOR_256_TEST(multiply.reduce,unwrap(input),axis,dtype,initial,keepdims);
    }
    {
        auto keepdims = false;
        VECTOR_256_TEST(multiply.reduce,unwrap(input),axis,dtype,initial,keepdims);
    }
}

//////////////////////////////////////////////////////////////////////////////

TEST_CASE("multiply.reduce_nd(case18a)" * doctest::test_suite("simd::vector_256"))
{
    auto axis = 0;
    auto new_shape = nmtools_array{2,12,3,3,9};
    auto input     = na::reshape(na::arange(ix::product(new_shape)),new_shape);
    auto dtype     = nm::None;
    auto initial   = nm::None;
    {
        auto keepdims = nm::True;
        VECTOR_256_TEST(multiply.reduce,unwrap(input),axis,dtype,initial,keepdims);
    }
    {
        auto keepdims = nm::False;
        VECTOR_256_TEST(multiply.reduce,unwrap(input),axis,dtype,initial,keepdims);
    }
    {
        auto keepdims = true;
        VECTOR_256_TEST(multiply.reduce,unwrap(input),axis,dtype,initial,keepdims);
    }
    {
        auto keepdims = false;
        VECTOR_256_TEST(multiply.reduce,unwrap(input),axis,dtype,initial,keepdims);
    }
}

TEST_CASE("multiply.reduce_nd(case18b)" * doctest::test_suite("simd::vector_256"))
{
    auto axis = 1;
    auto new_shape = nmtools_array{2,12,3,3,9};
    auto input     = na::reshape(na::arange(ix::product(new_shape)),new_shape);
    auto dtype     = nm::None;
    auto initial   = nm::None;
    {
        auto keepdims = nm::True;
        VECTOR_256_TEST(multiply.reduce,unwrap(input),axis,dtype,initial,keepdims);
    }
    {
        auto keepdims = nm::False;
        VECTOR_256_TEST(multiply.reduce,unwrap(input),axis,dtype,initial,keepdims);
    }
    {
        auto keepdims = true;
        VECTOR_256_TEST(multiply.reduce,unwrap(input),axis,dtype,initial,keepdims);
    }
    {
        auto keepdims = false;
        VECTOR_256_TEST(multiply.reduce,unwrap(input),axis,dtype,initial,keepdims);
    }
}

TEST_CASE("multiply.reduce_nd(case18c)" * doctest::test_suite("simd::vector_256"))
{
    auto axis = 2;
    auto new_shape = nmtools_array{2,12,3,3,9};
    auto input     = na::reshape(na::arange(ix::product(new_shape)),new_shape);
    auto dtype     = nm::None;
    auto initial   = nm::None;
    {
        auto keepdims = nm::True;
        VECTOR_256_TEST(multiply.reduce,unwrap(input),axis,dtype,initial,keepdims);
    }
    {
        auto keepdims = nm::False;
        VECTOR_256_TEST(multiply.reduce,unwrap(input),axis,dtype,initial,keepdims);
    }
    {
        auto keepdims = true;
        VECTOR_256_TEST(multiply.reduce,unwrap(input),axis,dtype,initial,keepdims);
    }
    {
        auto keepdims = false;
        VECTOR_256_TEST(multiply.reduce,unwrap(input),axis,dtype,initial,keepdims);
    }
}

TEST_CASE("multiply.reduce_nd(case18d)" * doctest::test_suite("simd::vector_256"))
{
    auto axis = 3;
    auto new_shape = nmtools_array{2,12,3,3,9};
    auto input     = na::reshape(na::arange(ix::product(new_shape)),new_shape);
    auto dtype     = nm::None;
    auto initial   = nm::None;
    {
        auto keepdims = nm::True;
        VECTOR_256_TEST(multiply.reduce,unwrap(input),axis,dtype,initial,keepdims);
    }
    {
        auto keepdims = nm::False;
        VECTOR_256_TEST(multiply.reduce,unwrap(input),axis,dtype,initial,keepdims);
    }
    {
        auto keepdims = true;
        VECTOR_256_TEST(multiply.reduce,unwrap(input),axis,dtype,initial,keepdims);
    }
    {
        auto keepdims = false;
        VECTOR_256_TEST(multiply.reduce,unwrap(input),axis,dtype,initial,keepdims);
    }
}

// TODO: fix multiply.reduce for gcc vector extension
TEST_CASE("multiply.reduce_nd(case18e)" * doctest::test_suite("simd::vector_256") * doctest::may_fail())
{
    auto axis = 4;
    auto new_shape = nmtools_array{2,12,3,3,9};
    auto input     = na::reshape(na::arange(ix::product(new_shape)),new_shape);
    auto dtype     = nm::None;
    auto initial   = nm::None;
    {
        auto keepdims = nm::True;
        VECTOR_256_TEST(multiply.reduce,unwrap(input),axis,dtype,initial,keepdims);
    }
    {
        auto keepdims = nm::False;
        VECTOR_256_TEST(multiply.reduce,unwrap(input),axis,dtype,initial,keepdims);
    }
    {
        auto keepdims = true;
        VECTOR_256_TEST(multiply.reduce,unwrap(input),axis,dtype,initial,keepdims);
    }
    {
        auto keepdims = false;
        VECTOR_256_TEST(multiply.reduce,unwrap(input),axis,dtype,initial,keepdims);
    }
}

/////////////////////////////////////////////////////////////////////////////////

TEST_CASE("multiply.reduce_nd(case19a)" * doctest::test_suite("simd::vector_256"))
{
    auto axis = 0;
    auto new_shape = nmtools_array{2,12,1,3,3,9};
    auto input     = na::reshape(na::arange(ix::product(new_shape)),new_shape);
    auto dtype     = nm::None;
    auto initial   = nm::None;
    {
        auto keepdims = nm::True;
        VECTOR_256_TEST(multiply.reduce,unwrap(input),axis,dtype,initial,keepdims);
    }
    {
        auto keepdims = nm::False;
        VECTOR_256_TEST(multiply.reduce,unwrap(input),axis,dtype,initial,keepdims);
    }
    {
        auto keepdims = true;
        VECTOR_256_TEST(multiply.reduce,unwrap(input),axis,dtype,initial,keepdims);
    }
    {
        auto keepdims = false;
        VECTOR_256_TEST(multiply.reduce,unwrap(input),axis,dtype,initial,keepdims);
    }
}

TEST_CASE("multiply.reduce_nd(case19b)" * doctest::test_suite("simd::vector_256"))
{
    auto axis = 1;
    auto new_shape = nmtools_array{2,12,1,3,3,9};
    auto input     = na::reshape(na::arange(ix::product(new_shape)),new_shape);
    auto dtype     = nm::None;
    auto initial   = nm::None;
    {
        auto keepdims = nm::True;
        VECTOR_256_TEST(multiply.reduce,unwrap(input),axis,dtype,initial,keepdims);
    }
    {
        auto keepdims = nm::False;
        VECTOR_256_TEST(multiply.reduce,unwrap(input),axis,dtype,initial,keepdims);
    }
    {
        auto keepdims = true;
        VECTOR_256_TEST(multiply.reduce,unwrap(input),axis,dtype,initial,keepdims);
    }
    {
        auto keepdims = false;
        VECTOR_256_TEST(multiply.reduce,unwrap(input),axis,dtype,initial,keepdims);
    }
}

TEST_CASE("multiply.reduce_nd(case19c)" * doctest::test_suite("simd::vector_256"))
{
    auto axis = 2;
    auto new_shape = nmtools_array{2,12,1,3,3,9};
    auto input     = na::reshape(na::arange(ix::product(new_shape)),new_shape);
    auto dtype     = nm::None;
    auto initial   = nm::None;
    {
        auto keepdims = nm::True;
        VECTOR_256_TEST(multiply.reduce,unwrap(input),axis,dtype,initial,keepdims);
    }
    {
        auto keepdims = nm::False;
        VECTOR_256_TEST(multiply.reduce,unwrap(input),axis,dtype,initial,keepdims);
    }
    {
        auto keepdims = true;
        VECTOR_256_TEST(multiply.reduce,unwrap(input),axis,dtype,initial,keepdims);
    }
    {
        auto keepdims = false;
        VECTOR_256_TEST(multiply.reduce,unwrap(input),axis,dtype,initial,keepdims);
    }
}

TEST_CASE("multiply.reduce_nd(case19d)" * doctest::test_suite("simd::vector_256"))
{
    auto axis = 3;
    auto new_shape = nmtools_array{2,12,1,3,3,9};
    auto input     = na::reshape(na::arange(ix::product(new_shape)),new_shape);
    auto dtype     = nm::None;
    auto initial   = nm::None;
    {
        auto keepdims = nm::True;
        VECTOR_256_TEST(multiply.reduce,unwrap(input),axis,dtype,initial,keepdims);
    }
    {
        auto keepdims = nm::False;
        VECTOR_256_TEST(multiply.reduce,unwrap(input),axis,dtype,initial,keepdims);
    }
    {
        auto keepdims = true;
        VECTOR_256_TEST(multiply.reduce,unwrap(input),axis,dtype,initial,keepdims);
    }
    {
        auto keepdims = false;
        VECTOR_256_TEST(multiply.reduce,unwrap(input),axis,dtype,initial,keepdims);
    }
}

TEST_CASE("multiply.reduce_nd(case19e)" * doctest::test_suite("simd::vector_256"))
{
    auto axis = 4;
    auto new_shape = nmtools_array{2,12,1,3,3,9};
    auto input     = na::reshape(na::arange(ix::product(new_shape)),new_shape);
    auto dtype     = nm::None;
    auto initial   = nm::None;
    {
        auto keepdims = nm::True;
        VECTOR_256_TEST(multiply.reduce,unwrap(input),axis,dtype,initial,keepdims);
    }
    {
        auto keepdims = nm::False;
        VECTOR_256_TEST(multiply.reduce,unwrap(input),axis,dtype,initial,keepdims);
    }
    {
        auto keepdims = true;
        VECTOR_256_TEST(multiply.reduce,unwrap(input),axis,dtype,initial,keepdims);
    }
    {
        auto keepdims = false;
        VECTOR_256_TEST(multiply.reduce,unwrap(input),axis,dtype,initial,keepdims);
    }
}

// TODO: fix gcc vector extension for multiply.reduce
TEST_CASE("multiply.reduce_nd(case19f)" * doctest::test_suite("simd::vector_256") * doctest::may_fail())
{
    auto axis = 5;
    auto new_shape = nmtools_array{2,12,1,3,3,9};
    auto input     = na::reshape(na::arange(ix::product(new_shape)),new_shape);
    auto dtype     = nm::None;
    auto initial   = nm::None;
    {
        auto keepdims = nm::True;
        VECTOR_256_TEST(multiply.reduce,unwrap(input),axis,dtype,initial,keepdims);
    }
    {
        auto keepdims = nm::False;
        VECTOR_256_TEST(multiply.reduce,unwrap(input),axis,dtype,initial,keepdims);
    }
    {
        auto keepdims = true;
        VECTOR_256_TEST(multiply.reduce,unwrap(input),axis,dtype,initial,keepdims);
    }
    {
        auto keepdims = false;
        VECTOR_256_TEST(multiply.reduce,unwrap(input),axis,dtype,initial,keepdims);
    }
}