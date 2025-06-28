#include "nmtools/index/logical_not.hpp"
#include "nmtools/core/mutable_ref.hpp"

namespace nm = nmtools;
namespace ix = nm::index;
namespace view = nm::view;
namespace meta = nm::meta;

#define logical_not_kernel_name "test_logical_not"

#ifdef NMTOOLS_OPENCL_BUILD_KERNELS

kernel void test_logical_not(global bool* out_ptr, global bool* inp_ptr, const unsigned long out_size, const unsigned long inp_size)
{
    // crashed on llvm-spirv 15 when compiling kernel
    // llvm-spirv: /home/runner/work/nmtools/nmtools/SPIRV-LLVM-Translator/lib/SPIRV/libSPIRV/SPIRVInstruction.h:1910: virtual void SPIRV::SPIRVCompositeExtractBase::validate() const: Assertion `getValueType(Composite)->isTypeArray() || getValueType(Composite)->isTypeStruct() || getValueType(Composite)->isTypeVector()' failed.
    // 2023-11-12T15:48:07.0290468Z PLEASE submit a bug report to https://github.com/llvm/llvm-project/issues/ and include the crash backtrace.
    // 2023-11-12T15:48:07.0291665Z Stack dump:
    // 2023-11-12T15:48:07.0294036Z 0.	Program arguments: llvm-spirv -spirv-max-version=1.0 -o /home/runner/work/nmtools/nmtools/tests/opencl/index/nm_cl_test_logical_not.spv /home/runner/work/nmtools/nmtools/tests/opencl/index/nm_cl_test_logical_not.bc
    #if 0
    if (get_global_id(0)==0) {
        auto output = view::mutable_ref(out_ptr,out_size);
        auto input  = ix::ref_ptr(inp_ptr,inp_size);

        auto result = ix::logical_not(input);
        for (size_t i=0; i<out_size; i++) {
            nm::at(output,i) = nm::at(result,i);
        }
    }
    #endif
}
#else

#include "nmtools/testing/opencl.hpp"

namespace opencl = nmtools::opencl;
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

    NMTOOLS_TESTING_USE_CASE(logical_not, case1);
    tester.test(opencl::default_context(),expect::x_a,args::x_a);
}

#endif // NMTOOLS_OPENCL_BUILD_KERNELS