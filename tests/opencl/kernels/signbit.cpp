#include "nmtools/array/evaluator/opencl/kernels/signbit.hpp"
#ifndef NMTOOLS_OPENCL_BUILD_KERNELS
#include "nmtools/array/evaluator/opencl/context.hpp"
#include "nmtools/array/evaluator/opencl/evaluator.hpp"
#include "nmtools/array/array/arange.hpp"
#include "nmtools/array/array/ones.hpp"
#include "nmtools/array/array/ufuncs/signbit.hpp"
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

// may fail in ci, Cannot find symbol _Z7signbitd in kernel library
TEST_CASE("signbit(case1)" * doctest::test_suite("opencl::signbit") * doctest::may_fail())
{
    try {
        auto array = na::arange(0,16);
        OPENCL_TEST(array,signbit);
    } catch (opencl::cl_exception& e) {
        if (e.status() == CL_BUILD_PROGRAM_FAILURE) {
            // may fail in ci, Cannot find symbol _Z7signbitd in kernel library
            std::cout << e.what() << "\n";
        } else {
            throw;
        }
    }
}

#endif