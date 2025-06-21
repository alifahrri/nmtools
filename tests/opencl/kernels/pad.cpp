#include "nmtools/evaluator/opencl/kernels/pad.hpp"
#ifndef NMTOOLS_OPENCL_BUILD_KERNELS
#include "nmtools/evaluator/opencl/evaluator.hpp"
#include "nmtools/array/arange.hpp"
#include "nmtools/array/pad.hpp"
#include "nmtools/array/reshape.hpp"
#include "nmtools/testing/doctest.hpp"

namespace nm = nmtools;
namespace ix = nm::index;
namespace na = nmtools;
namespace meta = nm::meta;
namespace opencl = na::opencl;

#define OPENCL_TEST(fn,...) \
{ \
    auto expect = na::fn(__VA_ARGS__); \
    auto result = na::fn(__VA_ARGS__,opencl::default_context()); \
    NMTOOLS_ASSERT_EQUAL( nm::shape(result), nm::shape(expect) ); \
    NMTOOLS_ASSERT_CLOSE( result, expect ); \
}

TEST_CASE("pad(case1a)" * doctest::test_suite("opencl::pad"))
{
    auto shape = nmtools_array{12,8};
    auto numel = ix::product(shape);
    auto start = 1;
    auto stop  = numel+start;
    auto input = na::reshape(na::arange(start,stop),shape);
    auto pads = nmtools_array{0,2,0,0};
    auto pad_value = 0;
    OPENCL_TEST(pad,input,pads,pad_value);
}

TEST_CASE("pad(case1b)" * doctest::test_suite("opencl::pad"))
{
    auto shape = nmtools_array{12,8};
    auto numel = ix::product(shape);
    auto start = 1;
    auto stop  = numel+start;
    auto input = na::reshape(na::arange(start,stop),shape);
    auto pads = nmtools_array{0,2,0,0};
    auto pad_value = 7;
    OPENCL_TEST(pad,input,pads,pad_value);
}

// TODO: fix result
TEST_CASE("pad(case1c)" * doctest::test_suite("opencl::pad") * doctest::skip())
{
    auto shape = nmtools_array{12,8};
    auto numel = ix::product(shape);
    auto start = 1;
    auto stop  = numel+start;
    auto input = na::reshape(na::arange(start,stop,nm::float64),shape);
    auto pads = nmtools_array{0,2,0,0};
    auto pad_value = 0;
    OPENCL_TEST(pad,input,pads,pad_value);
}

TEST_CASE("pad(case2a)" * doctest::test_suite("opencl::pad"))
{
    auto shape = nmtools_array{12,8};
    auto numel = ix::product(shape);
    auto start = 1;
    auto stop  = numel+start;
    auto input = na::reshape(na::arange(start,stop,nm::float32),shape);
    auto pads = nmtools_array{0,2,0,2};
    auto pad_value = 0;
    OPENCL_TEST(pad,input,pads,pad_value);
}

TEST_CASE("pad(case2b)" * doctest::test_suite("opencl::pad"))
{
    auto shape = nmtools_array{12,8};
    auto numel = ix::product(shape);
    auto start = 1;
    auto stop  = numel+start;
    auto input = na::reshape(na::arange(start,stop,nm::float32),shape);
    auto pads = nmtools_array{0,2,0,2};
    auto pad_value = 7;
    OPENCL_TEST(pad,input,pads,pad_value);
}

TEST_CASE("pad(case3a)" * doctest::test_suite("opencl::pad"))
{
    auto shape = nmtools_array{12,8};
    auto numel = ix::product(shape);
    auto start = 1;
    auto stop  = numel+start;
    auto input = na::reshape(na::arange(start,stop,nm::float32),shape);
    auto pads = nmtools_array{1,2,0,2};
    auto pad_value = 0;
    OPENCL_TEST(pad,input,pads,pad_value);
}

TEST_CASE("pad(case3b)" * doctest::test_suite("opencl::pad"))
{
    auto shape = nmtools_array{12,8};
    auto numel = ix::product(shape);
    auto start = 1;
    auto stop  = numel+start;
    auto input = na::reshape(na::arange(start,stop,nm::float32),shape);
    auto pads = nmtools_array{1,2,0,2};
    auto pad_value = 7;
    OPENCL_TEST(pad,input,pads,pad_value);
}

TEST_CASE("pad(case4a)" * doctest::test_suite("opencl::pad"))
{
    auto shape = nmtools_array{12,8};
    auto numel = ix::product(shape);
    auto start = 1;
    auto stop  = numel+start;
    auto input = na::reshape(na::arange(start,stop,nm::float32),shape);
    auto pads = nmtools_array{1,2,3,2};
    auto pad_value = 0;
    OPENCL_TEST(pad,input,pads,pad_value);
}

TEST_CASE("pad(case4b)" * doctest::test_suite("opencl::pad"))
{
    auto shape = nmtools_array{12,8};
    auto numel = ix::product(shape);
    auto start = 1;
    auto stop  = numel+start;
    auto input = na::reshape(na::arange(start,stop,nm::float32),shape);
    auto pads = nmtools_array{1,2,3,2};
    auto pad_value = 7;
    OPENCL_TEST(pad,input,pads,pad_value);
}

TEST_CASE("pad(case5a)" * doctest::test_suite("opencl::pad"))
{
    auto shape = nmtools_array{6,12,8};
    auto numel = ix::product(shape);
    auto start = 1;
    auto stop  = numel+start;
    auto input = na::reshape(na::arange(start,stop,nm::float32),shape);
    auto pads = nmtools_array{0,1,1,2,0,2};
    auto pad_value = 0;
    OPENCL_TEST(pad,input,pads,pad_value);
}

TEST_CASE("pad(case5b)" * doctest::test_suite("opencl::pad"))
{
    auto shape = nmtools_array{6,12,8};
    auto numel = ix::product(shape);
    auto start = 1;
    auto stop  = numel+start;
    auto input = na::reshape(na::arange(start,stop,nm::float32),shape);
    auto pads = nmtools_array{0,1,1,2,0,2};
    auto pad_value = 7;
    OPENCL_TEST(pad,input,pads,pad_value);
}

#endif // NMTOOLS_OPENCL_BUILD_KERNELS