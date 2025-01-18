#include "nmtools/array/evaluator/opencl/kernels/pooling.hpp"
#ifndef NMTOOLS_OPENCL_BUILD_KERNELS
#include "nmtools/array/evaluator/opencl/evaluator.hpp"
#include "nmtools/array/array/arange.hpp"
#include "nmtools/array/array/pooling.hpp"
#include "nmtools/array/array/reshape.hpp"
#include "nmtools/testing/doctest.hpp"

namespace nm = nmtools;
namespace ix = nm::index;
namespace na = nm::array;
namespace opencl = na::opencl;

#define OPENCL_TEST(fn,...) \
{ \
    auto expect = na::fn(__VA_ARGS__); \
    auto result = na::fn(__VA_ARGS__,opencl::default_context()); \
    NMTOOLS_ASSERT_EQUAL( nm::shape(result), nm::shape(expect) ); \
    NMTOOLS_ASSERT_CLOSE( result, expect ); \
}

TEST_CASE("max_pool2d(case1)" * doctest::test_suite("max_pool2d"))
{
    auto src_shape = nmtools_array{1,1,12,12};
    
    auto numel = ix::product(src_shape);
    auto start = 1;
    auto stop  = numel + start;
    auto input = na::reshape(na::arange(start,stop),src_shape);

    auto kernel_size = nmtools_array{3,3};
    auto stride = nmtools_array{2,2};
    auto ceil_mode = 1;

    OPENCL_TEST(max_pool2d,input,kernel_size,stride,ceil_mode);
}

#endif