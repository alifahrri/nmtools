#include "nmtools/index/repeat.hpp"
#include "nmtools/core/mutable_ref.hpp"
#include "nmtools/evaluator/opencl/kernel_helper.hpp"

namespace nm = nmtools;
namespace ix = nm::index;
namespace view = nm::view;
namespace meta = nm::meta;

#define shape_repeat_kernel_name "test_shape_repeat"

#ifdef NMTOOLS_OPENCL_BUILD_KERNELS

kernel void test_shape_repeat(
      global int* out_shape_ptr
    , global const int* inp_shape_ptr
    , global const int* repeats_ptr
    , const int axis
    , const nm_cl_index_t out_size
    , const nm_cl_index_t inp_size
    , const nm_cl_index_t repeats_size
) {
    if (get_global_id(0)==0) {
        auto output  = view::mutable_ref(out_shape_ptr,out_size);
        auto input   = ix::ref_ptr(inp_shape_ptr,inp_size);
        auto repeats = ix::ref_ptr(repeats_ptr,repeats_size);

        auto result = ix::shape_repeat(input,repeats,axis);
        for (size_t i=0; i<out_size; i++) {
            nm::at(output,i) = nm::at(result,i);
        }
    }
}
#else // NMTOOLS_OPENCL_BUILD_KERNELS

#include "nmtools/testing/data/index/repeat.hpp"
#include "nmtools/testing/doctest.hpp"
#include "nmtools/testing/opencl.hpp"
#include <cstring>

namespace opencl = nmtools::array::opencl;
namespace testing = nmtools::testing;

extern unsigned char nm_cl_test_repeat_spv[];
extern unsigned int  nm_cl_test_repeat_spv_len;

TEST_CASE("shape_repeat(case1)" * doctest::test_suite("index::shape_repeat"))
{
    auto tester = testing::OpenCLTester(shape_repeat_kernel_name,nm_cl_test_repeat_spv,nm_cl_test_repeat_spv_len);

    NMTOOLS_TESTING_USE_CASE(shape_repeat,case4);
    tester.test(opencl::default_context()
        ,ix::cast<int>(expect::shape)
        ,ix::cast<int>(args::shape_a)
        ,ix::cast<int>(args::repeats)
        ,(int)args::axis
    );
}

TEST_CASE("shape_repeat(case2)" * doctest::test_suite("index::shape_repeat"))
{
    auto tester = testing::OpenCLTester(shape_repeat_kernel_name,nm_cl_test_repeat_spv,nm_cl_test_repeat_spv_len);
  
    NMTOOLS_TESTING_USE_CASE(shape_repeat,case5);
    tester.test(opencl::default_context()
        ,ix::cast<int>(expect::shape)
        ,ix::cast<int>(args::shape_a)
        ,ix::cast<int>(args::repeats)
        ,(int)args::axis
    );
}

#endif // NMTOOLS_OPENCL_BUILD_KERNELS