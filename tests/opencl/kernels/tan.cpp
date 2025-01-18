#include "nmtools/array/evaluator/opencl/kernels/tan.hpp"
#ifndef NMTOOLS_OPENCL_BUILD_KERNELS
#include "nmtools/array/evaluator/opencl/context.hpp"
#include "nmtools/array/evaluator/opencl/evaluator.hpp"
#include "nmtools/array/array/arange.hpp"
#include "nmtools/array/array/ones.hpp"
#include "nmtools/array/array/ufuncs/tan.hpp"
#include "nmtools/testing/doctest.hpp"

#undef NMTOOLS_TESTING_PRECISION
#define NMTOOLS_TESTING_PRECISION 1e-3

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

TEST_CASE("tan(case1)" * doctest::test_suite("opencl::tan"))
{
    auto array = na::arange(-4,4,0.0125);
    OPENCL_TEST(array,tan);
}

#endif