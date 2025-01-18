#include "nmtools/array/index/broadcast_to.hpp"
#include "nmtools/core/mutable_ref.hpp"
#include "nmtools/evaluator/opencl/kernel_helper.hpp"

namespace nm = nmtools;
namespace ix = nm::index;
namespace view = nm::view;
namespace meta = nm::meta;
namespace opencl = nm::array::opencl;

#define shape_broadcast_to_kernel_name "test_shape_broadcast_to"
#define broadcast_to_kernel_name "test_broadcast_to"

#ifdef NMTOOLS_OPENCL_BUILD_KERNELS

kernel void test_shape_broadcast_to(
      global int* out_ptr
    , global const int* ashape_ptr
    , global const int* bshape_ptr
    , const unsigned int out_size
    , const unsigned int ashape_size
    , const unsigned int bshape_size
)
{

    auto id = get_global_id(0);
    if (id==0) {
        auto output = view::mutable_ref(out_ptr,out_size);

        auto ashape = opencl::create_vector(ashape_ptr,ashape_size);
        auto bshape = opencl::create_vector(bshape_ptr,bshape_size);

        auto result = ix::shape_broadcast_to(ashape,bshape);

        const auto& success = nmtools::get<0>(result);
        const auto& shape_  = nmtools::get<1>(result);
        const auto& free    = nmtools::get<2>(result);
        
        if (success) {
            opencl::assign_vector(output,shape_);
        } else {
            for (size_t i=0; i<out_size; i++) {
                nm::at(output,i) = -1;
            }
        }
    }
}

#if 0
kernel void test_broadcast_to(global unsigned long* out_ptr, global const unsigned long* indices_ptr, global const unsigned long* src_shape_ptr, global const unsigned long* dst_shape_ptr, global const unsigned long* origin_axes_ptr, const unsigned long out_size, const unsigned long indices_size, const unsigned long src_shape_size, const unsigned long dst_shape_size, const unsigned long origin_axes_size)
{
    auto id = get_global_id(0);
    if (id==0) {
        auto output = view::mutable_ref(out_ptr,out_size);

        auto indices     = opencl::create_vector(indices_ptr,indices_size);
        auto src_shape   = opencl::create_vector(src_shape_ptr,src_shape_size);
        auto dst_shape   = opencl::create_vector(dst_shape_ptr,dst_shape_size);
        auto origin_axes = opencl::create_vector(origin_axes_ptr,origin_axes_size);

        auto result = ix::broadcast_to(indices,src_shape,dst_shape,origin_axes);
        opencl::assign_vector(output,result);
    }
}
#endif

#else

#include "nmtools/testing/data/array/broadcast_to.hpp"
#include "nmtools/testing/opencl.hpp"
#include <cstring>

namespace testing = nmtools::testing;

#define SHAPE_BROADCAST_TO_SUBCASE(case_name, ashape, bshape) \
SUBCASE(#case_name) \
{ \
    NMTOOLS_TESTING_USE_CASE(index, broadcast_to, case_name); \
    tester.test(opencl::default_context(),expect::shape,args::ashape,args::bshape); \
}

extern unsigned char nm_cl_test_broadcast_to_spv[];
extern unsigned int nm_cl_test_broadcast_to_spv_len;

TEST_CASE("shape_broadcast_to(case1)" * doctest::test_suite("index::shape_broadcast_to"))
{
    auto tester = testing::OpenCLTester(shape_broadcast_to_kernel_name,nm_cl_test_broadcast_to_spv,nm_cl_test_broadcast_to_spv_len);

    SHAPE_BROADCAST_TO_SUBCASE(case1, ashape, bshape)
    SHAPE_BROADCAST_TO_SUBCASE(case1, ashape_a, bshape_a)
    SHAPE_BROADCAST_TO_SUBCASE(case1, ashape_v, bshape_v)
    SHAPE_BROADCAST_TO_SUBCASE(case1, ashape_h, bshape_h)
    SHAPE_BROADCAST_TO_SUBCASE(case1, ashape_sv, bshape_sv)

    SHAPE_BROADCAST_TO_SUBCASE(case1, ashape_a, bshape_v)
    SHAPE_BROADCAST_TO_SUBCASE(case1, ashape_h, bshape_v)
    SHAPE_BROADCAST_TO_SUBCASE(case1, ashape_sv, bshape_v)

    SHAPE_BROADCAST_TO_SUBCASE(case1, ashape_v, bshape_a)
    SHAPE_BROADCAST_TO_SUBCASE(case1, ashape_h, bshape_a)
    SHAPE_BROADCAST_TO_SUBCASE(case1, ashape_sv, bshape_a)
    
    SHAPE_BROADCAST_TO_SUBCASE(case1, ashape_a, bshape_h)
    SHAPE_BROADCAST_TO_SUBCASE(case1, ashape_v, bshape_h)
    SHAPE_BROADCAST_TO_SUBCASE(case1, ashape_sv, bshape_h)

    SHAPE_BROADCAST_TO_SUBCASE(case1, ashape_a, bshape_sv)
    SHAPE_BROADCAST_TO_SUBCASE(case1, ashape_v, bshape_sv)
    SHAPE_BROADCAST_TO_SUBCASE(case1, ashape_h, bshape_sv)
}

TEST_CASE("shape_broadcast_to(case2)" * doctest::test_suite("index::shape_broadcast_to"))
{
    auto tester = testing::OpenCLTester(shape_broadcast_to_kernel_name,nm_cl_test_broadcast_to_spv,nm_cl_test_broadcast_to_spv_len);

    SHAPE_BROADCAST_TO_SUBCASE(case2, ashape, bshape)
    SHAPE_BROADCAST_TO_SUBCASE(case2, ashape_a, bshape_a)
    SHAPE_BROADCAST_TO_SUBCASE(case2, ashape_v, bshape_v)
    SHAPE_BROADCAST_TO_SUBCASE(case2, ashape_h, bshape_h)
    SHAPE_BROADCAST_TO_SUBCASE(case2, ashape_sv, bshape_sv)

    SHAPE_BROADCAST_TO_SUBCASE(case2, ashape_a, bshape_v)
    SHAPE_BROADCAST_TO_SUBCASE(case2, ashape_h, bshape_v)
    SHAPE_BROADCAST_TO_SUBCASE(case2, ashape_sv, bshape_v)

    SHAPE_BROADCAST_TO_SUBCASE(case2, ashape_v, bshape_a)
    SHAPE_BROADCAST_TO_SUBCASE(case2, ashape_h, bshape_a)
    SHAPE_BROADCAST_TO_SUBCASE(case2, ashape_sv, bshape_a)
    
    SHAPE_BROADCAST_TO_SUBCASE(case2, ashape_a, bshape_h)
    SHAPE_BROADCAST_TO_SUBCASE(case2, ashape_v, bshape_h)
    SHAPE_BROADCAST_TO_SUBCASE(case2, ashape_sv, bshape_h)

    SHAPE_BROADCAST_TO_SUBCASE(case2, ashape_a, bshape_sv)
    SHAPE_BROADCAST_TO_SUBCASE(case2, ashape_v, bshape_sv)
    SHAPE_BROADCAST_TO_SUBCASE(case2, ashape_h, bshape_sv)
}

TEST_CASE("shape_broadcast_to(case4)" * doctest::test_suite("index::shape_broadcast_to"))
{
    auto tester = testing::OpenCLTester(shape_broadcast_to_kernel_name,nm_cl_test_broadcast_to_spv,nm_cl_test_broadcast_to_spv_len);

    SHAPE_BROADCAST_TO_SUBCASE(case4, ashape, bshape)
    SHAPE_BROADCAST_TO_SUBCASE(case4, ashape_a, bshape_a)
    SHAPE_BROADCAST_TO_SUBCASE(case4, ashape_v, bshape_v)
    SHAPE_BROADCAST_TO_SUBCASE(case4, ashape_h, bshape_h)
    SHAPE_BROADCAST_TO_SUBCASE(case4, ashape_sv, bshape_sv)

    SHAPE_BROADCAST_TO_SUBCASE(case4, ashape_a, bshape_v)
    SHAPE_BROADCAST_TO_SUBCASE(case4, ashape_h, bshape_v)
    SHAPE_BROADCAST_TO_SUBCASE(case4, ashape_sv, bshape_v)

    SHAPE_BROADCAST_TO_SUBCASE(case4, ashape_v, bshape_a)
    SHAPE_BROADCAST_TO_SUBCASE(case4, ashape_h, bshape_a)
    SHAPE_BROADCAST_TO_SUBCASE(case4, ashape_sv, bshape_a)
    
    SHAPE_BROADCAST_TO_SUBCASE(case4, ashape_a, bshape_h)
    SHAPE_BROADCAST_TO_SUBCASE(case4, ashape_v, bshape_h)
    SHAPE_BROADCAST_TO_SUBCASE(case4, ashape_sv, bshape_h)

    SHAPE_BROADCAST_TO_SUBCASE(case4, ashape_a, bshape_sv)
    SHAPE_BROADCAST_TO_SUBCASE(case4, ashape_v, bshape_sv)
    SHAPE_BROADCAST_TO_SUBCASE(case4, ashape_h, bshape_sv)
}

#if 0
TEST_CASE("shape_broadcast_to(case5)" * doctest::test_suite("index::shape_broadcast_to"))
{
    auto tester = testing::OpenCLTester(shape_broadcast_to_kernel_name,nm_cl_test_broadcast_to_spv,nm_cl_test_broadcast_to_spv_len);

    SHAPE_BROADCAST_TO_SUBCASE(case5, ashape, bshape)
    SHAPE_BROADCAST_TO_SUBCASE(case5, ashape_a, bshape_a)
    SHAPE_BROADCAST_TO_SUBCASE(case5, ashape_v, bshape_v)
    SHAPE_BROADCAST_TO_SUBCASE(case5, ashape_h, bshape_h)
    SHAPE_BROADCAST_TO_SUBCASE(case5, ashape_sv, bshape_sv)

    SHAPE_BROADCAST_TO_SUBCASE(case5, ashape_a, bshape_v)
    SHAPE_BROADCAST_TO_SUBCASE(case5, ashape_h, bshape_v)
    SHAPE_BROADCAST_TO_SUBCASE(case5, ashape_sv, bshape_v)

    SHAPE_BROADCAST_TO_SUBCASE(case5, ashape_v, bshape_a)
    SHAPE_BROADCAST_TO_SUBCASE(case5, ashape_h, bshape_a)
    SHAPE_BROADCAST_TO_SUBCASE(case5, ashape_sv, bshape_a)
    
    SHAPE_BROADCAST_TO_SUBCASE(case5, ashape_a, bshape_h)
    SHAPE_BROADCAST_TO_SUBCASE(case5, ashape_v, bshape_h)
    SHAPE_BROADCAST_TO_SUBCASE(case5, ashape_sv, bshape_h)

    SHAPE_BROADCAST_TO_SUBCASE(case5, ashape_a, bshape_sv)
    SHAPE_BROADCAST_TO_SUBCASE(case5, ashape_v, bshape_sv)
    SHAPE_BROADCAST_TO_SUBCASE(case5, ashape_h, bshape_sv)
}

TEST_CASE("shape_broadcast_to(case6)" * doctest::test_suite("index::shape_broadcast_to"))
{
    auto tester = testing::OpenCLTester(shape_broadcast_to_kernel_name,nm_cl_test_broadcast_to_spv,nm_cl_test_broadcast_to_spv_len);

    SHAPE_BROADCAST_TO_SUBCASE(case6, ashape, bshape)
    SHAPE_BROADCAST_TO_SUBCASE(case6, ashape_a, bshape_a)
    SHAPE_BROADCAST_TO_SUBCASE(case6, ashape_v, bshape_v)
    SHAPE_BROADCAST_TO_SUBCASE(case6, ashape_h, bshape_h)
    SHAPE_BROADCAST_TO_SUBCASE(case6, ashape_sv, bshape_sv)

    SHAPE_BROADCAST_TO_SUBCASE(case6, ashape_a, bshape_v)
    SHAPE_BROADCAST_TO_SUBCASE(case6, ashape_h, bshape_v)
    SHAPE_BROADCAST_TO_SUBCASE(case6, ashape_sv, bshape_v)

    SHAPE_BROADCAST_TO_SUBCASE(case6, ashape_v, bshape_a)
    SHAPE_BROADCAST_TO_SUBCASE(case6, ashape_h, bshape_a)
    SHAPE_BROADCAST_TO_SUBCASE(case6, ashape_sv, bshape_a)
    
    SHAPE_BROADCAST_TO_SUBCASE(case6, ashape_a, bshape_h)
    SHAPE_BROADCAST_TO_SUBCASE(case6, ashape_v, bshape_h)
    SHAPE_BROADCAST_TO_SUBCASE(case6, ashape_sv, bshape_h)

    SHAPE_BROADCAST_TO_SUBCASE(case6, ashape_a, bshape_sv)
    SHAPE_BROADCAST_TO_SUBCASE(case6, ashape_v, bshape_sv)
    SHAPE_BROADCAST_TO_SUBCASE(case6, ashape_h, bshape_sv)
}
#endif

TEST_CASE("shape_broadcast_to(case7)" * doctest::test_suite("index::shape_broadcast_to"))
{
    auto tester = testing::OpenCLTester(shape_broadcast_to_kernel_name,nm_cl_test_broadcast_to_spv,nm_cl_test_broadcast_to_spv_len);

    SHAPE_BROADCAST_TO_SUBCASE(case7, ashape, bshape)
    SHAPE_BROADCAST_TO_SUBCASE(case7, ashape_a, bshape_a)
    SHAPE_BROADCAST_TO_SUBCASE(case7, ashape_v, bshape_v)
    SHAPE_BROADCAST_TO_SUBCASE(case7, ashape_h, bshape_h)
    SHAPE_BROADCAST_TO_SUBCASE(case7, ashape_sv, bshape_sv)

    SHAPE_BROADCAST_TO_SUBCASE(case7, ashape_a, bshape_v)
    SHAPE_BROADCAST_TO_SUBCASE(case7, ashape_h, bshape_v)
    SHAPE_BROADCAST_TO_SUBCASE(case7, ashape_sv, bshape_v)

    SHAPE_BROADCAST_TO_SUBCASE(case7, ashape_v, bshape_a)
    SHAPE_BROADCAST_TO_SUBCASE(case7, ashape_h, bshape_a)
    SHAPE_BROADCAST_TO_SUBCASE(case7, ashape_sv, bshape_a)
    
    SHAPE_BROADCAST_TO_SUBCASE(case7, ashape_a, bshape_h)
    SHAPE_BROADCAST_TO_SUBCASE(case7, ashape_v, bshape_h)
    SHAPE_BROADCAST_TO_SUBCASE(case7, ashape_sv, bshape_h)

    SHAPE_BROADCAST_TO_SUBCASE(case7, ashape_a, bshape_sv)
    SHAPE_BROADCAST_TO_SUBCASE(case7, ashape_v, bshape_sv)
    SHAPE_BROADCAST_TO_SUBCASE(case7, ashape_h, bshape_sv)
}

#endif // NMTOOLS_OPENCL_BUILD_KERNELS