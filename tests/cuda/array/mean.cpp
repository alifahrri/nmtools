#include "nmtools/array/array/mean.hpp"
#include "nmtools/array/array/arange.hpp"
#include "nmtools/array/array/reshape.hpp"
#include "nmtools/array/eval/cuda.hpp"
#include "nmtools/testing/doctest.hpp"

namespace nm = nmtools;
namespace na = nm::array;
namespace ix = nm::index;

#define CUDA_MEAN_SUBCASE(...) \
{ \
    auto expect = na::mean(__VA_ARGS__); \
    auto result = na::mean(__VA_ARGS__, na::cuda::default_context()); \
    NMTOOLS_ASSERT_EQUAL( nm::shape(result), nm::shape(expect) ); \
    NMTOOLS_ASSERT_CLOSE( expect, expect ); \
}

#define MEAN_SUBCASE(case_name, ...) \
SUBCASE(#case_name) \
{ \
    NMTOOLS_TESTING_DECLARE_NS(array, mean, case_name); \
    using namespace args; \
    CUDA_MEAN_SUBCASE(__VA_ARGS__); \
}

TEST_CASE("mean(case1)" * doctest::test_suite("array::mean"))
{
    auto shape = nmtools_array{128};
    auto numel = ix::product(shape);
    auto start = 0;
    auto stop  = start + numel;
    auto step  = 1;
    auto flat  = na::arange(start,stop,step);
    auto input = na::reshape(flat,shape);

    auto dtype    = nm::None;
    auto keepdims = nm::True;
    {
        auto axis = 0;
        CUDA_MEAN_SUBCASE(input,axis,dtype,keepdims);
    }
}

TEST_CASE("mean(case2)" * doctest::test_suite("array::mean"))
{
    auto shape = nmtools_array{64,2};
    auto numel = ix::product(shape);
    auto start = 0;
    auto stop  = start + numel;
    auto step  = 1;
    auto flat  = na::arange(start,stop,step);
    auto input = na::reshape(flat,shape);

    auto dtype    = nm::None;
    auto keepdims = nm::True;
    {
        auto axis = 0;
        CUDA_MEAN_SUBCASE(input,axis,dtype,keepdims);
    }
    {
        auto axis = 1;
        CUDA_MEAN_SUBCASE(input,axis,dtype,keepdims);
    }
}

TEST_CASE("mean(case3)" * doctest::test_suite("array::mean"))
{
    auto shape = nmtools_array{16,4,2};
    auto numel = ix::product(shape);
    auto start = 0;
    auto stop  = start + numel;
    auto step  = 1;
    auto flat  = na::arange(start,stop,step);
    auto input = na::reshape(flat,shape);

    auto dtype    = nm::None;
    auto keepdims = nm::True;
    {
        auto axis = 0;
        CUDA_MEAN_SUBCASE(input,axis,dtype,keepdims);
    }
    {
        auto axis = 1;
        CUDA_MEAN_SUBCASE(input,axis,dtype,keepdims);
    }
    {
        auto axis = 2;
        CUDA_MEAN_SUBCASE(input,axis,dtype,keepdims);
    }
}

TEST_CASE("mean(case4)" * doctest::test_suite("array::mean"))
{
    auto shape = nmtools_array{2,8,4,2};
    auto numel = ix::product(shape);
    auto start = 0;
    auto stop  = start + numel;
    auto step  = 1;
    auto flat  = na::arange(start,stop,step);
    auto input = na::reshape(flat,shape);

    auto dtype    = nm::None;
    auto keepdims = nm::True;
    {
        auto axis = 0;
        CUDA_MEAN_SUBCASE(input,axis,dtype,keepdims);
    }
    {
        auto axis = 1;
        CUDA_MEAN_SUBCASE(input,axis,dtype,keepdims);
    }
    {
        auto axis = 2;
        CUDA_MEAN_SUBCASE(input,axis,dtype,keepdims);
    }
    {
        auto axis = 3;
        CUDA_MEAN_SUBCASE(input,axis,dtype,keepdims);
    }
}

TEST_CASE("mean(case5)" * doctest::test_suite("array::mean"))
{
    auto shape = nmtools_array{3,2,8,4,2};
    auto numel = ix::product(shape);
    auto start = 0;
    auto stop  = start + numel;
    auto step  = 1;
    auto flat  = na::arange(start,stop,step);
    auto input = na::reshape(flat,shape);

    auto dtype    = nm::None;
    auto keepdims = nm::True;
    {
        auto axis = 0;
        CUDA_MEAN_SUBCASE(input,axis,dtype,keepdims);
    }
    {
        auto axis = 1;
        CUDA_MEAN_SUBCASE(input,axis,dtype,keepdims);
    }
    {
        auto axis = 2;
        CUDA_MEAN_SUBCASE(input,axis,dtype,keepdims);
    }
    {
        auto axis = 3;
        CUDA_MEAN_SUBCASE(input,axis,dtype,keepdims);
    }
    {
        auto axis = 4;
        CUDA_MEAN_SUBCASE(input,axis,dtype,keepdims);
    }
}