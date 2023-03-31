#include "nmtools/array/eval/opencl/kernels/square.hpp"
#ifndef NMTOOLS_OPENCL_BUILD_KERNELS
#include "nmtools/array/eval/opencl/context.hpp"
#include "nmtools/array/eval/opencl/evaluator.hpp"
#include "nmtools/array/array/arange.hpp"
#include "nmtools/array/array/ones.hpp"
#include "nmtools/array/array/ufuncs/square.hpp"
#include "nmtools/testing/doctest.hpp"

namespace nm = nmtools;
namespace na = nm::array;
namespace opencl = na::opencl;

#define OPENCL_TEST(array,fn,...) \
{ \
    auto expect = na::fn(array,##__VA_ARGS__); \
    auto result = na::fn(array,##__VA_ARGS__,opencl::default_context()); \
    NMTOOLS_ASSERT_EQUAL( nm::shape(result), nm::shape(expect) ); \
    NMTOOLS_ASSERT_CLOSE( result, expect ); \
}

TEST_CASE("square(case1)" * doctest::test_suite("opencl::square"))
{
    auto array = na::arange(-4,4,0.0125);
    OPENCL_TEST(array,square);
}

#endif