#include "nmtools/array/index/logical_not.hpp"
#include "nmtools/array/view/mutable_ref.hpp"

namespace nm = nmtools;
namespace ix = nm::index;
namespace view = nm::view;
namespace meta = nm::meta;

#define logical_not_kernel_name "test_logical_not"

#ifdef NMTOOLS_OPENCL_BUILD_KERNELS

kernel void test_logical_not(global bool* out_ptr, global bool* inp_ptr, const unsigned long out_size, const unsigned long inp_size)
{
    if (get_global_id(0)==0) {
        auto output = view::mutable_ref(out_ptr,out_size);
        auto input  = ix::ref_ptr(inp_ptr,inp_size);

        auto result = ix::logical_not(input);
        for (size_t i=0; i<out_size; i++) {
            nm::at(output,i) = nm::at(result,i);
        }
    }
}
#else

#include "nmtools/testing/opencl.hpp"

namespace opencl = nmtools::array::opencl;
namespace testing = nmtools::testing;

extern unsigned char nm_cl_test_logical_not_spv[];
extern unsigned int nm_cl_test_logical_not_spv_len;

NMTOOLS_TESTING_DECLARE_CASE(logical_not)
{
    NMTOOLS_TESTING_DECLARE_ARGS(case1)
    {
        bool x[5] = {true, false, false, true, false};
        NMTOOLS_CAST_INDEX_ARRAYS(x);
        auto x_vector = x_v;
        auto x_array  = x_a;
        auto x_fixed_vector = x_f;
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case1)
    {
        bool x[5] = {false, true, true, false, true};
        NMTOOLS_CAST_INDEX_ARRAYS(x);
        auto x_vector = x_v;
        auto x_array  = x_a;
        auto x_fixed_vector = x_f;
    }
}

// TODO: fix runtime error  ERROR: test case THREW exception: Got error: CL_INVALID_VALUE when enqueueing write buffer (clEnqueueWriteBuffer)
TEST_CASE("logical_not(case1)" * doctest::test_suite("index::logical_not") * doctest::skip())
{
    auto tester = testing::OpenCLTester(logical_not_kernel_name,nm_cl_test_logical_not_spv,nm_cl_test_logical_not_spv_len);

    NMTOOLS_TESTING_DECLARE_NS(logical_not, case1);
    tester.test(opencl::default_context(),expect::x_a,args::x_a);
}

#endif // NMTOOLS_OPENCL_BUILD_KERNELS