#include "nmtools/array/index/nonzero.hpp"
#include "nmtools/core/mutable_ref.hpp"

namespace nm = nmtools;
namespace ix = nm::index;
namespace view = nm::view;
namespace meta = nm::meta;

#define nonzero_kernel_name "test_nonzero"

#ifdef NMTOOLS_OPENCL_BUILD_KERNELS

kernel void test_nonzero(global int* out_ptr, global const int* inp_ptr, const unsigned int out_size, const unsigned int inp_size)
{
    if (get_global_id(0)==0) {
        auto output = view::mutable_ref(out_ptr,out_size);
        auto input  = ix::ref_ptr(inp_ptr,inp_size);

        auto result = ix::nonzero(input);
        for (size_t i=0; i<out_size; i++) {
            nm::at(output,i) = nm::at(result,i);
        }
    }
}

#else

#include "nmtools/testing/opencl.hpp"
#include <cstring>

namespace opencl = nmtools::array::opencl;
namespace testing = nmtools::testing;

extern unsigned char nm_cl_test_nonzero_spv[];
extern unsigned int  nm_cl_test_nonzero_spv_len;

NMTOOLS_TESTING_DECLARE_CASE(nonzero)
{
    using namespace literals;

    NMTOOLS_TESTING_DECLARE_ARGS(case1)
    {
        int x[6] = {0,1,2,3,4,5};
        NMTOOLS_CAST_INDEX_ARRAYS(x);
        auto x_ct = nmtools_tuple{0_ct,1_ct,2_ct,3_ct,4_ct,5_ct};
        auto x_cl = nmtools_tuple{"0:[1]"_ct,"1:[1]"_ct,"2:[2]"_ct,"3:[3]"_ct,"4:[4]"_ct,"5:[5]"_ct};
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case1)
    {
        int result[5] = {1,2,3,4,5};
    }
}

TEST_CASE("nonzero(case1)" * doctest::test_suite("index::nonzero"))
{
    auto tester = testing::OpenCLTester(nonzero_kernel_name,nm_cl_test_nonzero_spv,nm_cl_test_nonzero_spv_len);

    NMTOOLS_TESTING_USE_CASE(nonzero,case1);
    tester.test(opencl::default_context(),expect::result,args::x);
}

#endif // NMTOOLS_OPENCL_BUILD_KERNELS