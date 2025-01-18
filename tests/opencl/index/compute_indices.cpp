#include "nmtools/array/index/compute_indices.hpp"
#include "nmtools/array/view/mutable_ref.hpp"
#include "nmtools/evaluator/opencl/kernel_helper.hpp"

namespace nm = nmtools;
namespace ix = nm::index;
namespace view = nm::view;
namespace meta = nm::meta;
namespace opencl = nm::array::opencl;

#define compute_indices_kernel_name "test_compute_indices"

#ifdef NMTOOLS_OPENCL_BUILD_KERNELS

kernel void test_compute_indices(
    global int* out_ptr
    , const int offset
    , global const int* shape_ptr
    , const int out_size
    , const int shape_size
) {
    auto id = get_global_id(0);
    if (id == 0) {
        auto output = view::mutable_ref(out_ptr,out_size);
        
        auto shape   = opencl::create_vector(shape_ptr,shape_size);
        auto result  = ix::compute_indices(offset,shape);
        opencl::assign_vector(output,result);
    }
}

#else

#include "nmtools/testing/data/index/compute_indices.hpp"
#include "nmtools/testing/opencl.hpp"

namespace testing = nmtools::testing;

#define COMPUTE_INDICES_SUBCASE(case_name, offset, shape) \
SUBCASE(#case_name) \
{ \
    NMTOOLS_TESTING_USE_CASE(compute_indices, case_name); \
    tester.test(opencl::default_context(),expect::indices,args::offset,args::shape); \
}

extern unsigned char nm_cl_test_compute_indices_spv[];
extern unsigned int nm_cl_test_compute_indices_spv_len;

static auto tester = testing::OpenCLTester(compute_indices_kernel_name,nm_cl_test_compute_indices_spv,nm_cl_test_compute_indices_spv_len);

TEST_CASE("compute_indices(case1)" * doctest::test_suite("index::compute_indices"))
{
    COMPUTE_INDICES_SUBCASE( case1_2d, offset, shape )
    COMPUTE_INDICES_SUBCASE( case1_2d, offset, shape_a )
    COMPUTE_INDICES_SUBCASE( case1_2d, offset, shape_v )
    COMPUTE_INDICES_SUBCASE( case1_2d, offset, shape_h )
    COMPUTE_INDICES_SUBCASE( case1_2d, offset, shape_sv )
}

TEST_CASE("compute_indices(case2)" * doctest::test_suite("index::compute_indices"))
{
    COMPUTE_INDICES_SUBCASE( case2_2d, offset, shape )
    COMPUTE_INDICES_SUBCASE( case2_2d, offset, shape_a )
    COMPUTE_INDICES_SUBCASE( case2_2d, offset, shape_v )
    COMPUTE_INDICES_SUBCASE( case2_2d, offset, shape_h )
    COMPUTE_INDICES_SUBCASE( case2_2d, offset, shape_sv )
}

TEST_CASE("compute_indices(case3)" * doctest::test_suite("index::compute_indices"))
{
    COMPUTE_INDICES_SUBCASE( case3_2d, offset, shape )
    COMPUTE_INDICES_SUBCASE( case3_2d, offset, shape_a )
    COMPUTE_INDICES_SUBCASE( case3_2d, offset, shape_v )
    COMPUTE_INDICES_SUBCASE( case3_2d, offset, shape_h )
    COMPUTE_INDICES_SUBCASE( case3_2d, offset, shape_sv )
}

TEST_CASE("compute_indices(case4)" * doctest::test_suite("index::compute_indices"))
{
    COMPUTE_INDICES_SUBCASE( case4_2d, offset, shape )
    COMPUTE_INDICES_SUBCASE( case4_2d, offset, shape_a )
    COMPUTE_INDICES_SUBCASE( case4_2d, offset, shape_v )
    COMPUTE_INDICES_SUBCASE( case4_2d, offset, shape_h )
    COMPUTE_INDICES_SUBCASE( case4_2d, offset, shape_sv )
}

TEST_CASE("compute_indices(case5)" * doctest::test_suite("index::compute_indices"))
{
    COMPUTE_INDICES_SUBCASE( case5_2d, offset, shape )
    COMPUTE_INDICES_SUBCASE( case5_2d, offset, shape_a )
    COMPUTE_INDICES_SUBCASE( case5_2d, offset, shape_v )
    COMPUTE_INDICES_SUBCASE( case5_2d, offset, shape_h )
    COMPUTE_INDICES_SUBCASE( case5_2d, offset, shape_sv )
}

TEST_CASE("compute_indices(case6)" * doctest::test_suite("index::compute_indices"))
{
    COMPUTE_INDICES_SUBCASE( case6_2d, offset, shape )
    COMPUTE_INDICES_SUBCASE( case6_2d, offset, shape_a )
    COMPUTE_INDICES_SUBCASE( case6_2d, offset, shape_v )
    COMPUTE_INDICES_SUBCASE( case6_2d, offset, shape_h )
    COMPUTE_INDICES_SUBCASE( case6_2d, offset, shape_sv )
}

TEST_CASE("compute_indices(case1)" * doctest::test_suite("index::compute_indices"))
{
    COMPUTE_INDICES_SUBCASE( case1_3d, offset, shape )
    COMPUTE_INDICES_SUBCASE( case1_3d, offset, shape_a )
    COMPUTE_INDICES_SUBCASE( case1_3d, offset, shape_v )
    COMPUTE_INDICES_SUBCASE( case1_3d, offset, shape_h )
    COMPUTE_INDICES_SUBCASE( case1_3d, offset, shape_sv )
}

TEST_CASE("compute_indices(case2)" * doctest::test_suite("index::compute_indices"))
{
    COMPUTE_INDICES_SUBCASE( case2_3d, offset, shape )
    COMPUTE_INDICES_SUBCASE( case2_3d, offset, shape_a )
    COMPUTE_INDICES_SUBCASE( case2_3d, offset, shape_v )
    COMPUTE_INDICES_SUBCASE( case2_3d, offset, shape_h )
    COMPUTE_INDICES_SUBCASE( case2_3d, offset, shape_sv )
}

TEST_CASE("compute_indices(case3)" * doctest::test_suite("index::compute_indices"))
{
    COMPUTE_INDICES_SUBCASE( case3_3d, offset, shape )
    COMPUTE_INDICES_SUBCASE( case3_3d, offset, shape_a )
    COMPUTE_INDICES_SUBCASE( case3_3d, offset, shape_v )
    COMPUTE_INDICES_SUBCASE( case3_3d, offset, shape_h )
    COMPUTE_INDICES_SUBCASE( case3_3d, offset, shape_sv )
}

TEST_CASE("compute_indices(case4)" * doctest::test_suite("index::compute_indices"))
{
    COMPUTE_INDICES_SUBCASE( case4_3d, offset, shape )
    COMPUTE_INDICES_SUBCASE( case4_3d, offset, shape_a )
    COMPUTE_INDICES_SUBCASE( case4_3d, offset, shape_v )
    COMPUTE_INDICES_SUBCASE( case4_3d, offset, shape_h )
    COMPUTE_INDICES_SUBCASE( case4_3d, offset, shape_sv )
}

TEST_CASE("compute_indices(case5)" * doctest::test_suite("index::compute_indices"))
{
    COMPUTE_INDICES_SUBCASE( case5_3d, offset, shape )
    COMPUTE_INDICES_SUBCASE( case5_3d, offset, shape_a )
    COMPUTE_INDICES_SUBCASE( case5_3d, offset, shape_v )
    COMPUTE_INDICES_SUBCASE( case5_3d, offset, shape_h )
    COMPUTE_INDICES_SUBCASE( case5_3d, offset, shape_sv )
}

TEST_CASE("compute_indices(case6)" * doctest::test_suite("index::compute_indices"))
{
    COMPUTE_INDICES_SUBCASE( case6_3d, offset, shape )
    COMPUTE_INDICES_SUBCASE( case6_3d, offset, shape_a )
    COMPUTE_INDICES_SUBCASE( case6_3d, offset, shape_v )
    COMPUTE_INDICES_SUBCASE( case6_3d, offset, shape_h )
    COMPUTE_INDICES_SUBCASE( case6_3d, offset, shape_sv )
}

#endif