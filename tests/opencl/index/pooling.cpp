#include "nmtools/array/index/pooling.hpp"
#include "nmtools/array/view/mutable_ref.hpp"
#include "nmtools/array/eval/opencl/kernel_helper.hpp"

namespace nm = nmtools;
namespace na = nmtools::array;
namespace ix = nm::index;
namespace view = nm::view;
namespace meta = nm::meta;

#define shape_pool2d_kernel_name "test_shape_pool2d"

#ifdef NMTOOLS_OPENCL_BUILD_KERNELS

kernel void test_shape_pool2d(
    global nm_cl_index_t* out_shape_ptr
    , global const nm_cl_index_t* inp_shape_ptr
    , global const nm_cl_index_t* kernel_size_ptr
    , global const nm_cl_index_t* stride_ptr
    , const nm_cl_size_t out_size
    , const nm_cl_size_t inp_size
    , const nm_cl_size_t kernel_size_len
    , const nm_cl_size_t stride_len
    , const nm_cl_index_t ceil_mode
) {
    if (get_global_id(0) == 0) {
        auto inp_shape = na::create_vector(inp_shape_ptr,inp_size);
        auto kernel_size = na::create_vector(kernel_size_ptr,kernel_size_len);
        auto stride = na::create_vector(stride_ptr,stride_len);

        auto result = ix::shape_pool2d(inp_shape,kernel_size,stride,ceil_mode);
        auto out_shape = view::mutable_ref(out_shape_ptr,out_size);
        for (nm_cl_size_t i=0; i<(nm_cl_size_t)nm::len(result); i++) {
            nm::at(out_shape,i) = nm::at(result,i);
        }

    }
}

#else // NMTOOLS_OPENCL_BUILD_KERNELS

#include "nmtools/testing/data/index/pooling.hpp"
#include "nmtools/testing/doctest.hpp"
#include "nmtools/testing/opencl.hpp"
#include <cstring>

namespace opencl = nmtools::array::opencl;
namespace testing = nmtools::testing;

extern unsigned char nm_cl_test_pooling_spv[];
extern unsigned int  nm_cl_test_pooling_spv_len;

TEST_CASE("shape_pool2d(case1)" * doctest::test_suite("index::shape_pool2d"))
{
    auto tester = testing::OpenCLTester(shape_pool2d_kernel_name,nm_cl_test_pooling_spv,nm_cl_test_pooling_spv_len);

    NMTOOLS_TESTING_DECLARE_NS(index,shape_pool2d,case1);
    tester.test(opencl::default_context()
        , ix::cast<nm_cl_index_t>(expect::result)
        , ix::cast<nm_cl_index_t>(args::shape_a)
        , ix::cast<nm_cl_index_t>(args::kernel_size_a)
        , ix::cast<nm_cl_index_t>(args::stride_a)
        , ix::cast<nm_cl_index_t>(args::ceil_mode)
    );
}

#endif // NMTOOLS_OPENCL_BUILD_KERNELS