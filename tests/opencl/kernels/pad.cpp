#include "nmtools/array/eval/opencl/kernels/pad.hpp"
#ifndef NMTOOLS_OPENCL_BUILD_KERNELS
#include "nmtools/array/eval/opencl/evaluator.hpp"
#include "nmtools/array/array/arange.hpp"
#include "nmtools/array/array/pad.hpp"
#include "nmtools/array/array/reshape.hpp"
#include "nmtools/testing/doctest.hpp"

namespace nm = nmtools;
namespace ix = nm::index;
namespace na = nm::array;
namespace meta = nm::meta;
namespace opencl = na::opencl;

#define OPENCL_TEST(fn,...) \
{ \
    auto expect = na::fn(__VA_ARGS__); \
    auto result = na::fn(__VA_ARGS__,opencl::default_context()); \
    NMTOOLS_ASSERT_EQUAL( nm::shape(result), nm::shape(expect) ); \
    NMTOOLS_ASSERT_CLOSE( result, expect ); \
}

TEST_CASE("pad(case1)" * doctest::test_suite("opencl::pad"))
{
    auto shape = nmtools_array{12,8};
    auto numel = ix::product(shape);
    auto start = 1;
    auto stop  = numel+start;
    auto input = na::reshape(na::arange(start,stop),shape);
    auto pad_width = nmtools_array{0,2,0,0};
    auto pad_value = (float)0;
    OPENCL_TEST(pad,input,pad_width,pad_value);
}


#endif // NMTOOLS_OPENCL_BUILD_KERNELS