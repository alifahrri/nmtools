#include "nmtools/array/index/compute_strides.hpp"
#include "nmtools/core/mutable_ref.hpp"
#include "nmtools/evaluator/opencl/kernel_helper.hpp"

namespace nm = nmtools;
namespace ix = nm::index;
namespace view = nm::view;
namespace meta = nm::meta;
namespace opencl = nm::array::opencl;

#define compute_strides_kernel_name "test_compute_strides"

#ifdef NMTOOLS_OPENCL_BUILD_KERNELS

kernel void test_compute_strides(
    global int* out_ptr
    , global const int* shape_ptr
    , const unsigned int out_size
    , const unsigned int shape_size
) {
    auto id = get_global_id(0);
    if (id == 0) {
        auto output = view::mutable_ref(out_ptr,out_size);

        auto shape = opencl::create_vector(shape_ptr,shape_size);
        auto result = ix::compute_strides(shape);
        opencl::assign_vector(output,result);
    }
}

#else

#include "nmtools/testing/data/index/compute_strides.hpp"
#include "nmtools/testing/opencl.hpp"

namespace testing = nmtools::testing;

#define COMPUTE_STRIDES_SUBCASE(case_name, shape) \
SUBCASE(#case_name) \
{ \
    NMTOOLS_TESTING_USE_CASE(compute_strides, case_name); \
    tester.test(opencl::default_context(), expect::result, args::shape); \
}

extern unsigned char nm_cl_test_compute_strides_spv[];
extern unsigned int nm_cl_test_compute_strides_spv_len;

static auto tester = testing::OpenCLTester(compute_strides_kernel_name,nm_cl_test_compute_strides_spv,nm_cl_test_compute_strides_spv_len);

TEST_CASE("compute_strides(case1)" * doctest::test_suite("index::compute_strides"))
{
    COMPUTE_STRIDES_SUBCASE(case1, shape);
    COMPUTE_STRIDES_SUBCASE(case1, shape_a);
    COMPUTE_STRIDES_SUBCASE(case1, shape_v);
    COMPUTE_STRIDES_SUBCASE(case1, shape_h);
    COMPUTE_STRIDES_SUBCASE(case1, shape_sv);
}

TEST_CASE("compute_strides(case2)" * doctest::test_suite("index::compute_strides"))
{
    COMPUTE_STRIDES_SUBCASE(case2, shape);
    COMPUTE_STRIDES_SUBCASE(case2, shape_a);
    COMPUTE_STRIDES_SUBCASE(case2, shape_v);
    COMPUTE_STRIDES_SUBCASE(case2, shape_h);
    COMPUTE_STRIDES_SUBCASE(case2, shape_sv);
}

TEST_CASE("compute_strides(case3)" * doctest::test_suite("index::compute_strides"))
{
    COMPUTE_STRIDES_SUBCASE(case3, shape);
    COMPUTE_STRIDES_SUBCASE(case3, shape_a);
    COMPUTE_STRIDES_SUBCASE(case3, shape_v);
    COMPUTE_STRIDES_SUBCASE(case3, shape_h);
    COMPUTE_STRIDES_SUBCASE(case3, shape_sv);
}

TEST_CASE("compute_strides(case4)" * doctest::test_suite("index::compute_strides"))
{
    COMPUTE_STRIDES_SUBCASE(case4, shape);
    COMPUTE_STRIDES_SUBCASE(case4, shape_a);
    COMPUTE_STRIDES_SUBCASE(case4, shape_v);
    COMPUTE_STRIDES_SUBCASE(case4, shape_h);
    COMPUTE_STRIDES_SUBCASE(case4, shape_sv);
}

#endif