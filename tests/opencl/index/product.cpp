#include "nmtools/array/index/product.hpp"
#include "nmtools/core/mutable_ref.hpp"
#include "nmtools/evaluator/opencl/kernel_helper.hpp"

namespace nm = nmtools;
namespace ix = nm::index;
namespace view = nm::view;
namespace meta = nm::meta;

#define product_kernel_name "test_product"

#ifdef NMTOOLS_OPENCL_BUILD_KERNELS

kernel void test_product(
      global int* out_ptr
    , global const nm_cl_index_t* inp_shape_ptr
    , const nm_cl_index_t out_size
    , const nm_cl_index_t inp_size
) {
    if (get_global_id(0)==0) {
        auto inp_shape = ix::ref_ptr(inp_shape_ptr,inp_size);
        auto result = ix::product(inp_shape);
        *out_ptr = result;
    }
}

#else // NMTOOLS_OPENCL_BUILD_KERNELS

#include "nmtools/testing/doctest.hpp"
#include "nmtools/testing/opencl.hpp"
#include <cstring>

namespace opencl = nmtools::array::opencl;
namespace testing = nmtools::testing;

extern unsigned char nm_cl_test_product_spv[];
extern unsigned int  nm_cl_test_product_spv_len;

TEST_CASE("product(case1)" * doctest::test_suite("index::product"))
{
    auto tester = testing::OpenCLTester(product_kernel_name,nm_cl_test_product_spv,nm_cl_test_product_spv_len);

    auto shape = nmtools_array{1,2,3};
    auto expect = (int)6;
    tester.test(opencl::default_context(),expect,ix::cast<nm_cl_index_t>(shape));
}

TEST_CASE("product(case2)" * doctest::test_suite("index::product"))
{
    auto tester = testing::OpenCLTester(product_kernel_name,nm_cl_test_product_spv,nm_cl_test_product_spv_len);

    auto shape = nmtools_array{1ul,2ul,3ul};
    auto expect = (int)6;
    tester.test(opencl::default_context(),expect,ix::cast<nm_cl_index_t>(shape));
}

#endif // NMTOOLS_OPENCL_BUILD_KERNELS