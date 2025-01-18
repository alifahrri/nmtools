#include "nmtools/array/evaluator/opencl/kernels/hardtanh.hpp"
#ifndef NMTOOLS_OPENCL_BUILD_KERNELS
#include "nmtools/array/evaluator/opencl/context.hpp"
#include "nmtools/array/evaluator/opencl/evaluator.hpp"
#include "nmtools/array/array/arange.hpp"
#include "nmtools/array/array/ones.hpp"
#include "nmtools/array/array/activations/hardtanh.hpp"
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

TEST_CASE("hardtanh(case1)" * doctest::test_suite("opencl::hardtanh"))
{
    auto array = na::arange(128);
    OPENCL_TEST(array,hardtanh,-0.25f,0.25f);
}

#endif