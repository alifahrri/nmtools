#include "nmtools/array/index/resize.hpp"
#include "nmtools/array/view/mutable_ref.hpp"
#include "nmtools/array/evaluator/opencl/kernel_helper.hpp"
#include "nmtools/utility/unwrap.hpp"

namespace nm = nmtools;
namespace na = nmtools::array;
namespace ix = nm::index;
namespace view = nm::view;
namespace meta = nm::meta;

#define shape_resize_kernel_name "test_shape_resize"
#define index_resize_kernel_name "test_index_resize"

#ifdef NMTOOLS_OPENCL_BUILD_KERNELS

kernel void test_shape_resize(
      global nm_cl_index_t* out_shape_ptr
    , global const nm_cl_index_t* inp_shape_ptr
    , global const nm_cl_index_t* dst_shape_ptr
    , const nm_cl_size_t out_size
    , const nm_cl_size_t inp_size
    , const nm_cl_size_t dst_size
) {
    if (get_global_id(0)==0) {
        auto out_shape = view::mutable_ref(out_shape_ptr,out_size);
        auto inp_shape = ix::ref_ptr(inp_shape_ptr,inp_size);
        auto dst_shape = ix::ref_ptr(dst_shape_ptr,dst_size);

        auto maybe_result = ix::shape_resize(inp_shape,dst_shape);
        auto result = nm::unwrap(maybe_result);
        for (nm_cl_size_t i=0; i<(nm_cl_size_t)out_size; i++) {
            nm::at(out_shape,i) = nm::at(result,i);
        }
    }
}

kernel void test_index_resize(
      global nm_cl_index_t* out_index_ptr
    , global const nm_cl_index_t* inp_index_ptr
    , global const nm_cl_index_t* src_shape_ptr
    , global const nm_cl_index_t* dst_shape_ptr
    , const nm_cl_size_t out_size
    , const nm_cl_size_t inp_size
    , const nm_cl_size_t src_size
    , const nm_cl_size_t dst_size
) {
    if (get_global_id(0) == 0) {
        auto inp_index = na::create_vector(inp_index_ptr,inp_size);
        auto src_shape = na::create_vector(src_shape_ptr,src_size);
        auto dst_shape = na::create_vector(dst_shape_ptr,dst_size);

        auto maybe_result = ix::resize(inp_index,src_shape,dst_shape);
        auto result = nm::unwrap(maybe_result);

        auto out_index = view::mutable_ref(out_index_ptr,out_size);
        for (nm_cl_size_t i=0; i<(nm_cl_size_t)out_size; i++) {
            nm::at(out_index,i) = nm::at(result,i);
        }
    }
}

#else // NMTOOLS_OPENCL_BUILD_KERNELS

#include "nmtools/testing/data/index/resize.hpp"
#include "nmtools/testing/doctest.hpp"
#include "nmtools/testing/opencl.hpp"
#include <cstring>

namespace opencl = nmtools::array::opencl;
namespace testing = nmtools::testing;

extern unsigned char nm_cl_test_resize_spv[];
extern unsigned int  nm_cl_test_resize_spv_len;

TEST_CASE("shape_resize(case1)" * doctest::test_suite("index::shape_resize"))
{
    auto tester = testing::OpenCLTester(shape_resize_kernel_name,nm_cl_test_resize_spv,nm_cl_test_resize_spv_len);

    NMTOOLS_TESTING_USE_CASE(index,shape_resize,case1);
    tester.test(opencl::default_context()
        , ix::cast<nm_cl_index_t>(expect::expected)
        , ix::cast<nm_cl_index_t>(args::src_shape_a)
        , ix::cast<nm_cl_index_t>(args::dst_shape_a)
    );
}

TEST_CASE("shape_resize(case2)" * doctest::test_suite("index::shape_resize"))
{
    auto tester = testing::OpenCLTester(shape_resize_kernel_name,nm_cl_test_resize_spv,nm_cl_test_resize_spv_len);

    NMTOOLS_TESTING_USE_CASE(index,shape_resize,case2);
    tester.test(opencl::default_context()
        , ix::cast<nm_cl_index_t>(expect::expected)
        , ix::cast<nm_cl_index_t>(args::src_shape_a)
        , ix::cast<nm_cl_index_t>(args::dst_shape_a)
    );
}

TEST_CASE("shape_resize(case3)" * doctest::test_suite("index::shape_resize"))
{
    auto tester = testing::OpenCLTester(shape_resize_kernel_name,nm_cl_test_resize_spv,nm_cl_test_resize_spv_len);

    NMTOOLS_TESTING_USE_CASE(index,shape_resize,case3);
    tester.test(opencl::default_context()
        , ix::cast<nm_cl_index_t>(expect::expected)
        , ix::cast<nm_cl_index_t>(args::src_shape_a)
        , ix::cast<nm_cl_index_t>(args::dst_shape_a)
    );
}

TEST_CASE("shape_resize(case4)" * doctest::test_suite("index::shape_resize"))
{
    auto tester = testing::OpenCLTester(shape_resize_kernel_name,nm_cl_test_resize_spv,nm_cl_test_resize_spv_len);

    NMTOOLS_TESTING_USE_CASE(index,shape_resize,case4);
    tester.test(opencl::default_context()
        , ix::cast<nm_cl_index_t>(expect::expected)
        , ix::cast<nm_cl_index_t>(args::src_shape_a)
        , ix::cast<nm_cl_index_t>(args::dst_shape_a)
    );
}

TEST_CASE("shape_resize(case5)" * doctest::test_suite("index::shape_resize"))
{
    auto tester = testing::OpenCLTester(shape_resize_kernel_name,nm_cl_test_resize_spv,nm_cl_test_resize_spv_len);

    NMTOOLS_TESTING_USE_CASE(index,shape_resize,case5);
    tester.test(opencl::default_context()
        , ix::cast<nm_cl_index_t>(expect::expected)
        , ix::cast<nm_cl_index_t>(args::src_shape_a)
        , ix::cast<nm_cl_index_t>(args::dst_shape_a)
    );
}

TEST_CASE("shape_resize(case6)" * doctest::test_suite("index::shape_resize"))
{
    auto tester = testing::OpenCLTester(shape_resize_kernel_name,nm_cl_test_resize_spv,nm_cl_test_resize_spv_len);

    NMTOOLS_TESTING_USE_CASE(index,shape_resize,case6);
    tester.test(opencl::default_context()
        , ix::cast<nm_cl_index_t>(expect::expected)
        , ix::cast<nm_cl_index_t>(args::src_shape_a)
        , ix::cast<nm_cl_index_t>(args::dst_shape_a)
    );
}

TEST_CASE("resize(case6)" * doctest::test_suite("index::resize"))
{
    auto tester = testing::OpenCLTester(index_resize_kernel_name,nm_cl_test_resize_spv,nm_cl_test_resize_spv_len);

    NMTOOLS_TESTING_USE_CASE(index,resize,case6);
    tester.test(opencl::default_context()
        , ix::cast<nm_cl_index_t>(expect::expected)
        , ix::cast<nm_cl_index_t>(args::indices_a)
        , ix::cast<nm_cl_index_t>(args::src_shape_a)
        , ix::cast<nm_cl_index_t>(args::dst_shape_a)
    );
}

#endif // NMTOOLS_OPENCL_BUILD_KERNELS