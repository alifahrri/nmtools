#include "nmtools/array/eval/opencl/kernels/log.hpp"
#ifndef NMTOOLS_OPENCL_BUILD_KERNELS
#include "nmtools/array/eval/opencl/context.hpp"
#include "nmtools/array/eval/opencl/evaluator.hpp"
#include "nmtools/array/array/arange.hpp"
#include "nmtools/array/array/ones.hpp"
#include "nmtools/array/array/ufuncs/log.hpp"
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

TEST_CASE("log(case1)" * doctest::test_suite("opencl::log") * doctest::may_fail())
{
    auto array = na::arange(0,1,0.0125);
    OPENCL_TEST(array,log);
}

#endif