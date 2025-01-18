#include "nmtools/evaluator/opencl/kernels/expm1.hpp"
#ifndef NMTOOLS_OPENCL_BUILD_KERNELS
#include "nmtools/evaluator/opencl/context.hpp"
#include "nmtools/evaluator/opencl/evaluator.hpp"
#include "nmtools/array/arange.hpp"
#include "nmtools/array/ones.hpp"
#include "nmtools/array/ufuncs/expm1.hpp"
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

TEST_CASE("expm1(case1)" * doctest::test_suite("opencl::expm1"))
{
    auto array = na::arange(0,1,0.0125);
    OPENCL_TEST(array,expm1);
}

#endif