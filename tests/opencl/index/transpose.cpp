#include "nmtools/array/index/transpose.hpp"
#include "nmtools/array/view/mutable_ref.hpp"
#include "nmtools/array/eval/kernel_helper.hpp"

namespace nm = nmtools;
namespace na = nm::array;
namespace ix = nm::index;
namespace view = nm::view;
namespace meta = nm::meta;

#define shape_transpose_kernel_name "test_shape_transpose"

#ifdef NMTOOLS_OPENCL_BUILD_KERNELS

kernel void test_shape_transpose(global int* out_shape_ptr, global const int* inp_shape_ptr, global const int* axes_ptr, const int out_size, const int inp_size, const int axes_size)
{
    if (get_global_id(0)==0) {
        auto output = view::mutable_ref(out_shape_ptr,out_size);
        auto input = na::create_vector(inp_shape_ptr,inp_size);
        auto axes  = na::create_vector(axes_ptr,axes_size);

        auto result = ix::shape_transpose(input,axes);
        for (size_t i=0; i<out_size; i++) {
            nm::at(output,i) = nm::at(result,i);
        }
    }
}

#else // NMTOOLS_OPENCL_BUILD_KERNELS

#include "nmtools/testing/data/index/transpose.hpp"
#include "nmtools/testing/doctest.hpp"
#include "nmtools/testing/opencl.hpp"
#include <cstring>

namespace opencl = nmtools::array::opencl;
namespace testing = nmtools::testing;

extern unsigned char nm_cl_test_transpose_spv [];
extern unsigned int  nm_cl_test_transpose_spv_len;

TEST_CASE("shape_transpose(case1)" * doctest::test_suite("index::shape_transpose"))
{
    auto tester = testing::OpenCLTester(shape_transpose_kernel_name,nm_cl_test_transpose_spv,nm_cl_test_transpose_spv_len);

    NMTOOLS_TESTING_USE_CASE(index,shape_transpose,case4);
    tester.test(opencl::default_context(),expect::result,args::shape_a,args::axes_a);
}

TEST_CASE("shape_transpose(case2)" * doctest::test_suite("index::shape_transpose"))
{
    auto tester = testing::OpenCLTester(shape_transpose_kernel_name,nm_cl_test_transpose_spv,nm_cl_test_transpose_spv_len);

    NMTOOLS_TESTING_USE_CASE(index,shape_transpose,case5);
    tester.test(opencl::default_context(),expect::result,args::shape_a,args::axes_a);
}

TEST_CASE("shape_transpose(case3)" * doctest::test_suite("index::shape_transpose"))
{
    auto tester = testing::OpenCLTester(shape_transpose_kernel_name,nm_cl_test_transpose_spv,nm_cl_test_transpose_spv_len);

    NMTOOLS_TESTING_USE_CASE(index,shape_transpose,case6);
    tester.test(opencl::default_context(),expect::result,args::shape_a,args::axes_a);
}

TEST_CASE("shape_transpose(case4)" * doctest::test_suite("index::shape_transpose"))
{
    auto tester = testing::OpenCLTester(shape_transpose_kernel_name,nm_cl_test_transpose_spv,nm_cl_test_transpose_spv_len);

    NMTOOLS_TESTING_USE_CASE(index,shape_transpose,case7);
    tester.test(opencl::default_context(),expect::result,args::shape_a,args::axes_a);
}

TEST_CASE("shape_transpose(case5)" * doctest::test_suite("index::shape_transpose"))
{
    auto tester = testing::OpenCLTester(shape_transpose_kernel_name,nm_cl_test_transpose_spv,nm_cl_test_transpose_spv_len);

    NMTOOLS_TESTING_USE_CASE(index,shape_transpose,case8);
    tester.test(opencl::default_context(),expect::result,args::shape_a,args::axes_a);
}

TEST_CASE("shape_transpose(case6)" * doctest::test_suite("index::shape_transpose"))
{
    auto tester = testing::OpenCLTester(shape_transpose_kernel_name,nm_cl_test_transpose_spv,nm_cl_test_transpose_spv_len);

    auto result = nmtools_array{64,1};
    auto shape  = nmtools_array{64,1};
    auto axes   = nmtools_array{0,1};

    tester.test(opencl::default_context(),result,shape,axes);
}

TEST_CASE("shape_transpose(case7)" * doctest::test_suite("index::shape_transpose"))
{
    auto tester = testing::OpenCLTester(shape_transpose_kernel_name,nm_cl_test_transpose_spv,nm_cl_test_transpose_spv_len);

    auto result = nmtools_array{64,1};
    auto shape  = nmtools_array{1,64};
    auto axes   = nmtools_array{1,0};

    tester.test(opencl::default_context(),result,shape,axes);
}

TEST_CASE("shape_transpose(case8)" * doctest::test_suite("index::shape_transpose"))
{
    auto tester = testing::OpenCLTester(shape_transpose_kernel_name,nm_cl_test_transpose_spv,nm_cl_test_transpose_spv_len);

    auto result = nmtools_array<uint32_t,2>{64,1};
    auto shape  = nmtools_array<uint32_t,2>{64,1};
    auto axes   = nmtools_array<uint32_t,2>{0,1};

    tester.test(opencl::default_context(),result,shape,axes);
}

TEST_CASE("shape_transpose(case9)" * doctest::test_suite("index::shape_transpose"))
{
    auto tester = testing::OpenCLTester(shape_transpose_kernel_name,nm_cl_test_transpose_spv,nm_cl_test_transpose_spv_len);

    auto result = nmtools_array<uint32_t,2>{64,1};
    auto shape  = nmtools_array<uint32_t,2>{1,64};
    auto axes   = nmtools_array<uint32_t,2>{1,0};

    tester.test(opencl::default_context(),result,shape,axes);
}

TEST_CASE("shape_transpose(case10)" * doctest::test_suite("index::shape_transpose"))
{
    auto tester = testing::OpenCLTester(shape_transpose_kernel_name,nm_cl_test_transpose_spv,nm_cl_test_transpose_spv_len);

    auto result = nmtools_array<int32_t,2>{64,1};
    auto shape  = nmtools_array<int32_t,2>{64,1};
    auto axes   = nmtools_array<int32_t,2>{0,1};

    tester.test(opencl::default_context(),result,shape,axes);
}

TEST_CASE("shape_transpose(case11)" * doctest::test_suite("index::shape_transpose"))
{
    auto tester = testing::OpenCLTester(shape_transpose_kernel_name,nm_cl_test_transpose_spv,nm_cl_test_transpose_spv_len);

    auto result = nmtools_array<int32_t,2>{64,1};
    auto shape  = nmtools_array<int32_t,2>{1,64};
    auto axes   = nmtools_array<int32_t,2>{1,0};

    tester.test(opencl::default_context(),result,shape,axes);
}

#endif // NMTOOLS_OPENCL_BUILD_KERNELS