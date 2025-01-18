#include "nmtools/array/index/gather.hpp"
#include "nmtools/array/view/mutable_ref.hpp"
#include "nmtools/evaluator/opencl/kernel_helper.hpp"

namespace nm = nmtools;
namespace ix = nm::index;
namespace view = nm::view;
namespace meta = nm::meta;
namespace opencl = nm::array::opencl;

#define gather_kernel_name "test_gather"

#ifdef NMTOOLS_OPENCL_BUILD_KERNELS

kernel void test_gather(
    global int* out_ptr
    , global const int* vector_ptr
    , global const int* indices_ptr
    , const unsigned int out_size
    , const unsigned int vector_size
    , const unsigned int indices_size
) {
    auto id = get_global_id(0);
    if (id == 0) {
        auto output = view::mutable_ref(out_ptr,out_size);

        auto vector = opencl::create_vector(vector_ptr,vector_size);
        auto indices = opencl::create_vector(indices_ptr,indices_size);

        auto result = ix::gather(vector,indices);
        opencl::assign_vector(output,result);
    }
}

#else

#include "nmtools/testing/data/index/gather.hpp"
#include "nmtools/testing/opencl.hpp"

namespace testing = nmtools::testing;

#define GATHER_SUBCASE(case_name, vec, indices) \
SUBCASE(#case_name) \
{ \
    NMTOOLS_TESTING_USE_CASE(gather, case_name); \
    tester.test(opencl::default_context(), expect::result, args::vec, args::indices); \
} \

extern unsigned char nm_cl_test_gather_spv[];
extern unsigned int nm_cl_test_gather_spv_len;

static auto tester = testing::OpenCLTester(gather_kernel_name,nm_cl_test_gather_spv,nm_cl_test_gather_spv_len);

TEST_CASE("gather(case1)" * doctest::test_suite("index::gather"))
{
    GATHER_SUBCASE(case1, vec_a, indices_a);
    GATHER_SUBCASE(case1, vec_v, indices_v);
    GATHER_SUBCASE(case1, vec_h, indices_h);
    GATHER_SUBCASE(case1, vec_sv, indices_sv);
}

TEST_CASE("gather(case2)" * doctest::test_suite("index::gather"))
{
    GATHER_SUBCASE(case2, vec_a, indices_a);
    GATHER_SUBCASE(case2, vec_v, indices_v);
    GATHER_SUBCASE(case2, vec_h, indices_h);
    GATHER_SUBCASE(case2, vec_sv, indices_sv);
}

TEST_CASE("gather(case3)" * doctest::test_suite("index::gather"))
{
    GATHER_SUBCASE(case3, vec_a, indices_a);
    GATHER_SUBCASE(case3, vec_v, indices_v);
    GATHER_SUBCASE(case3, vec_h, indices_h);
    GATHER_SUBCASE(case3, vec_sv, indices_sv);
}

TEST_CASE("gather(case4)" * doctest::test_suite("index::gather"))
{
    GATHER_SUBCASE(case4, vec_a, indices_a);
    GATHER_SUBCASE(case4, vec_v, indices_v);
    GATHER_SUBCASE(case4, vec_h, indices_h);
    GATHER_SUBCASE(case4, vec_sv, indices_sv);
}

TEST_CASE("gather(case5)" * doctest::test_suite("index::gather"))
{
    GATHER_SUBCASE(case5, vec_a, indices_a);
    GATHER_SUBCASE(case5, vec_v, indices_v);
    GATHER_SUBCASE(case5, vec_h, indices_h);
    GATHER_SUBCASE(case5, vec_sv, indices_sv);
}

TEST_CASE("gather(case6)" * doctest::test_suite("index::gather"))
{
    GATHER_SUBCASE(case6, vec_a, indices_a);
    GATHER_SUBCASE(case6, vec_v, indices_v);
    GATHER_SUBCASE(case6, vec_h, indices_h);
    GATHER_SUBCASE(case6, vec_sv, indices_sv);
}

#endif