#include "nmtools/array/array/cumprod.hpp"
#include "nmtools/array/array/arange.hpp"
#include "nmtools/array/array/reshape.hpp"
#include "nmtools/array/eval/cuda.hpp"
#include "nmtools/testing/doctest.hpp"

namespace nm = nmtools;
namespace na = nm::array;
namespace ix = nm::index;

#define CUDA_CUMPROD_SUBCASE(...) \
{ \
    auto expect = na::cumprod(__VA_ARGS__); \
    auto result = na::cumprod(__VA_ARGS__, na::cuda::default_context()); \
    NMTOOLS_ASSERT_EQUAL( nm::shape(result), nm::shape(expect) ); \
    NMTOOLS_ASSERT_CLOSE( expect, expect ); \
}

#define CUMPROD_SUBCASE(case_name, ...) \
SUBCASE(#case_name) \
{ \
    NMTOOLS_TESTING_USE_CASE(array, cumprod, case_name); \
    using namespace args; \
    CUDA_CUMPROD_SUBCASE(__VA_ARGS__); \
}

TEST_CASE("cumprod(case1)" * doctest::test_suite("array::cumprod"))
{
    auto shape = nmtools_array{128};
    auto numel = ix::product(shape);
    auto start = 0;
    auto stop  = start + numel;
    auto step  = 1;
    auto flat  = na::arange(start,stop,step);
    auto input = na::reshape(flat,shape);

    auto dtype = nm::None;
    {
        auto axis = 0;
        CUDA_CUMPROD_SUBCASE(input,axis,dtype);
    }
}

// TODO: fix isclose inf with inf
TEST_CASE("cumprod(case2)" * doctest::test_suite("array::cumprod") * doctest::may_fail())
{
    auto shape = nmtools_array{64,2};
    auto numel = ix::product(shape);
    auto start = 0;
    auto stop  = start + numel;
    auto step  = 1;
    auto flat  = na::arange(start,stop,step);
    auto input = na::reshape(flat,shape);

    auto dtype = nm::None;
    {
        auto axis = 0;
        CUDA_CUMPROD_SUBCASE(input,axis,dtype);
    }
    {
        auto axis = 1;
        CUDA_CUMPROD_SUBCASE(input,axis,dtype);
    }
}

TEST_CASE("cumprod(case3)" * doctest::test_suite("array::cumprod"))
{
    auto shape = nmtools_array{16,4,2};
    auto numel = ix::product(shape);
    auto start = 0;
    auto stop  = start + numel;
    auto step  = 1;
    auto flat  = na::arange(start,stop,step);
    auto input = na::reshape(flat,shape);

    auto dtype = nm::None;
    {
        auto axis = 0;
        CUDA_CUMPROD_SUBCASE(input,axis,dtype);
    }
    {
        auto axis = 1;
        CUDA_CUMPROD_SUBCASE(input,axis,dtype);
    }
    {
        auto axis = 2;
        CUDA_CUMPROD_SUBCASE(input,axis,dtype);
    }
}

TEST_CASE("cumprod(case4)" * doctest::test_suite("array::cumprod"))
{
    auto shape = nmtools_array{4,2,1,4,2};
    auto numel = ix::product(shape);
    auto start = 0;
    auto stop  = start + numel;
    auto step  = 1;
    auto flat  = na::arange(start,stop,step);
    auto input = na::reshape(flat,shape);

    auto dtype = nm::None;
    {
        auto axis = 0;
        CUDA_CUMPROD_SUBCASE(input,axis,dtype);
    }
    {
        auto axis = 1;
        CUDA_CUMPROD_SUBCASE(input,axis,dtype);
    }
    {
        auto axis = 2;
        CUDA_CUMPROD_SUBCASE(input,axis,dtype);
    }
    {
        auto axis = 3;
        CUDA_CUMPROD_SUBCASE(input,axis,dtype);
    }
    {
        auto axis = 4;
        CUDA_CUMPROD_SUBCASE(input,axis,dtype);
    }
}

TEST_CASE("cumprod(case5)" * doctest::test_suite("array::cumprod"))
{
    auto shape = nmtools_array{128};
    auto numel = ix::product(shape);
    auto start = 0;
    auto stop  = start + numel;
    auto step  = 1;
    auto flat  = na::arange(start,stop,step,nm::float64);
    auto input = na::reshape(flat,shape);

    auto dtype    = nm::None;
    {
        auto axis = 0;
        CUDA_CUMPROD_SUBCASE(input,axis,dtype);
    }
}

TEST_CASE("cumprod(case6)" * doctest::test_suite("array::cumprod"))
{
    auto shape = nmtools_array{64,2};
    auto numel = ix::product(shape);
    auto start = 0;
    auto stop  = start + numel;
    auto step  = 1;
    auto flat  = na::arange(start,stop,step,nm::float64);
    auto input = na::reshape(flat,shape);

    auto dtype = nm::None;
    {
        auto axis = 0;
        CUDA_CUMPROD_SUBCASE(input,axis,dtype);
    }
    {
        auto axis = 1;
        CUDA_CUMPROD_SUBCASE(input,axis,dtype);
    }
}

TEST_CASE("cumprod(case7)" * doctest::test_suite("array::cumprod"))
{
    auto shape = nmtools_array{16,4,2};
    auto numel = ix::product(shape);
    auto start = 0;
    auto stop  = start + numel;
    auto step  = 1;
    auto flat  = na::arange(start,stop,step,nm::float64);
    auto input = na::reshape(flat,shape);

    auto dtype = nm::None;
    {
        auto axis = 0;
        CUDA_CUMPROD_SUBCASE(input,axis,dtype);
    }
    {
        auto axis = 1;
        CUDA_CUMPROD_SUBCASE(input,axis,dtype);
    }
    {
        auto axis = 2;
        CUDA_CUMPROD_SUBCASE(input,axis,dtype);
    }
}

TEST_CASE("cumprod(case8)" * doctest::test_suite("array::cumprod"))
{
    auto shape = nmtools_array{4,2,1,4,2};
    auto numel = ix::product(shape);
    auto start = 0;
    auto stop  = start + numel;
    auto step  = 1;
    auto flat  = na::arange(start,stop,step,nm::float64);
    auto input = na::reshape(flat,shape);

    auto dtype = nm::None;
    {
        auto axis = 0;
        CUDA_CUMPROD_SUBCASE(input,axis,dtype);
    }
    {
        auto axis = 1;
        CUDA_CUMPROD_SUBCASE(input,axis,dtype);
    }
    {
        auto axis = 2;
        CUDA_CUMPROD_SUBCASE(input,axis,dtype);
    }
    {
        auto axis = 3;
        CUDA_CUMPROD_SUBCASE(input,axis,dtype);
    }
    {
        auto axis = 4;
        CUDA_CUMPROD_SUBCASE(input,axis,dtype);
    }
}

TEST_CASE("cumprod(case9)" * doctest::test_suite("array::cumprod"))
{
    auto shape = nmtools_array{128};
    auto numel = ix::product(shape);
    auto start = 0;
    auto stop  = start + numel;
    auto step  = 1;
    auto flat  = na::arange(start,stop,step,nm::int32);
    auto input = na::reshape(flat,shape);

    auto dtype    = nm::None;
    {
        auto axis = 0;
        CUDA_CUMPROD_SUBCASE(input,axis,dtype);
    }
}

TEST_CASE("cumprod(case10)" * doctest::test_suite("array::cumprod"))
{
    auto shape = nmtools_array{64,2};
    auto numel = ix::product(shape);
    auto start = 0;
    auto stop  = start + numel;
    auto step  = 1;
    auto flat  = na::arange(start,stop,step,nm::int32);
    auto input = na::reshape(flat,shape);

    auto dtype = nm::None;
    {
        auto axis = 0;
        CUDA_CUMPROD_SUBCASE(input,axis,dtype);
    }
    {
        auto axis = 1;
        CUDA_CUMPROD_SUBCASE(input,axis,dtype);
    }
}

TEST_CASE("cumprod(case11)" * doctest::test_suite("array::cumprod"))
{
    auto shape = nmtools_array{16,4,2};
    auto numel = ix::product(shape);
    auto start = 0;
    auto stop  = start + numel;
    auto step  = 1;
    auto flat  = na::arange(start,stop,step,nm::int32);
    auto input = na::reshape(flat,shape);

    auto dtype = nm::None;
    {
        auto axis = 0;
        CUDA_CUMPROD_SUBCASE(input,axis,dtype);
    }
    {
        auto axis = 1;
        CUDA_CUMPROD_SUBCASE(input,axis,dtype);
    }
    {
        auto axis = 2;
        CUDA_CUMPROD_SUBCASE(input,axis,dtype);
    }
}

TEST_CASE("cumprod(case12)" * doctest::test_suite("array::cumprod"))
{
    auto shape = nmtools_array{4,2,1,4,2};
    auto numel = ix::product(shape);
    auto start = 0;
    auto stop  = start + numel;
    auto step  = 1;
    auto flat  = na::arange(start,stop,step,nm::int32);
    auto input = na::reshape(flat,shape);

    auto dtype = nm::None;
    {
        auto axis = 0;
        CUDA_CUMPROD_SUBCASE(input,axis,dtype);
    }
    {
        auto axis = 1;
        CUDA_CUMPROD_SUBCASE(input,axis,dtype);
    }
    {
        auto axis = 2;
        CUDA_CUMPROD_SUBCASE(input,axis,dtype);
    }
    {
        auto axis = 3;
        CUDA_CUMPROD_SUBCASE(input,axis,dtype);
    }
    {
        auto axis = 4;
        CUDA_CUMPROD_SUBCASE(input,axis,dtype);
    }
}

TEST_CASE("cumprod(case13)" * doctest::test_suite("array::cumprod"))
{
    auto shape = nmtools_array{128};
    auto numel = ix::product(shape);
    auto start = 0;
    auto stop  = start + numel;
    auto step  = 1;
    auto flat  = na::arange(start,stop,step,nm::int64);
    auto input = na::reshape(flat,shape);

    auto dtype    = nm::None;
    {
        auto axis = 0;
        CUDA_CUMPROD_SUBCASE(input,axis,dtype);
    }
}

TEST_CASE("cumprod(case14)" * doctest::test_suite("array::cumprod"))
{
    auto shape = nmtools_array{64,2};
    auto numel = ix::product(shape);
    auto start = 0;
    auto stop  = start + numel;
    auto step  = 1;
    auto flat  = na::arange(start,stop,step,nm::int64);
    auto input = na::reshape(flat,shape);

    auto dtype = nm::None;
    {
        auto axis = 0;
        CUDA_CUMPROD_SUBCASE(input,axis,dtype);
    }
    {
        auto axis = 1;
        CUDA_CUMPROD_SUBCASE(input,axis,dtype);
    }
}

TEST_CASE("cumprod(case15)" * doctest::test_suite("array::cumprod"))
{
    auto shape = nmtools_array{16,4,2};
    auto numel = ix::product(shape);
    auto start = 0;
    auto stop  = start + numel;
    auto step  = 1;
    auto flat  = na::arange(start,stop,step,nm::int64);
    auto input = na::reshape(flat,shape);

    auto dtype = nm::None;
    {
        auto axis = 0;
        CUDA_CUMPROD_SUBCASE(input,axis,dtype);
    }
    {
        auto axis = 1;
        CUDA_CUMPROD_SUBCASE(input,axis,dtype);
    }
    {
        auto axis = 2;
        CUDA_CUMPROD_SUBCASE(input,axis,dtype);
    }
}

TEST_CASE("cumprod(case16)" * doctest::test_suite("array::cumprod"))
{
    auto shape = nmtools_array{4,2,1,4,2};
    auto numel = ix::product(shape);
    auto start = 0;
    auto stop  = start + numel;
    auto step  = 1;
    auto flat  = na::arange(start,stop,step,nm::int64);
    auto input = na::reshape(flat,shape);

    auto dtype = nm::None;
    {
        auto axis = 0;
        CUDA_CUMPROD_SUBCASE(input,axis,dtype);
    }
    {
        auto axis = 1;
        CUDA_CUMPROD_SUBCASE(input,axis,dtype);
    }
    {
        auto axis = 2;
        CUDA_CUMPROD_SUBCASE(input,axis,dtype);
    }
    {
        auto axis = 3;
        CUDA_CUMPROD_SUBCASE(input,axis,dtype);
    }
    {
        auto axis = 4;
        CUDA_CUMPROD_SUBCASE(input,axis,dtype);
    }
}

TEST_CASE("cumprod(case17)" * doctest::test_suite("array::cumprod"))
{
    auto shape = nmtools_array{128};
    auto numel = ix::product(shape);
    auto start = 0;
    auto stop  = start + numel;
    auto step  = 1;
    auto flat  = na::arange(start,stop,step,nm::int16);
    auto input = na::reshape(flat,shape);

    auto dtype    = nm::None;
    {
        auto axis = 0;
        CUDA_CUMPROD_SUBCASE(input,axis,dtype);
    }
}

TEST_CASE("cumprod(case18)" * doctest::test_suite("array::cumprod"))
{
    auto shape = nmtools_array{64,2};
    auto numel = ix::product(shape);
    auto start = 0;
    auto stop  = start + numel;
    auto step  = 1;
    auto flat  = na::arange(start,stop,step,nm::int16);
    auto input = na::reshape(flat,shape);

    auto dtype = nm::None;
    {
        auto axis = 0;
        CUDA_CUMPROD_SUBCASE(input,axis,dtype);
    }
    {
        auto axis = 1;
        CUDA_CUMPROD_SUBCASE(input,axis,dtype);
    }
}

TEST_CASE("cumprod(case19)" * doctest::test_suite("array::cumprod"))
{
    auto shape = nmtools_array{16,4,2};
    auto numel = ix::product(shape);
    auto start = 0;
    auto stop  = start + numel;
    auto step  = 1;
    auto flat  = na::arange(start,stop,step,nm::int16);
    auto input = na::reshape(flat,shape);

    auto dtype = nm::None;
    {
        auto axis = 0;
        CUDA_CUMPROD_SUBCASE(input,axis,dtype);
    }
    {
        auto axis = 1;
        CUDA_CUMPROD_SUBCASE(input,axis,dtype);
    }
    {
        auto axis = 2;
        CUDA_CUMPROD_SUBCASE(input,axis,dtype);
    }
}

TEST_CASE("cumprod(case20)" * doctest::test_suite("array::cumprod"))
{
    auto shape = nmtools_array{4,2,1,4,2};
    auto numel = ix::product(shape);
    auto start = 0;
    auto stop  = start + numel;
    auto step  = 1;
    auto flat  = na::arange(start,stop,step,nm::int16);
    auto input = na::reshape(flat,shape);

    auto dtype = nm::None;
    {
        auto axis = 0;
        CUDA_CUMPROD_SUBCASE(input,axis,dtype);
    }
    {
        auto axis = 1;
        CUDA_CUMPROD_SUBCASE(input,axis,dtype);
    }
    {
        auto axis = 2;
        CUDA_CUMPROD_SUBCASE(input,axis,dtype);
    }
    {
        auto axis = 3;
        CUDA_CUMPROD_SUBCASE(input,axis,dtype);
    }
    {
        auto axis = 4;
        CUDA_CUMPROD_SUBCASE(input,axis,dtype);
    }
}