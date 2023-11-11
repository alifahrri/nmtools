#include "nmtools/array/index/broadcast_shape.hpp"
#include "nmtools/array/view/mutable_ref.hpp"
#include "nmtools/array/eval/opencl/kernel_helper.hpp"

namespace nm = nmtools;
namespace ix = nm::index;
namespace view = nm::view;
namespace meta = nm::meta;
namespace opencl = nm::array::opencl;

#define binary_broadcast_shape_kernel_name "test_broadcast_shape_binary"
#define ternary_broadcast_shape_kernel_name "test_broadcast_shape_ternary"
#define quaternary_broadcast_sahpe_kernel_name "test_broadcast_shape_quaternary"
// ...
#define senary_broadcast_sahpe_kernel_name "test_broadcast_shape_senary"

#ifdef NMTOOLS_OPENCL_BUILD_KERNELS

template <typename output_t, typename...shapes_t>
void broadcast_shape(output_t& output, const shapes_t&...shapes)
{
    auto id = get_global_id(0);
    if (id==0) {

        auto result = ix::broadcast_shape(shapes...);
        
        if (result) {
            opencl::assign_vector(output,*result);
        } else {
            for (size_t i=0; i<nm::size(output); i++) {
                nm::at(output,i) = -1;
            }
        }
    }
}

kernel void test_broadcast_shape_binary(
      global int* out_ptr
    , global const int* ashape_ptr
    , global const int* bshape_ptr
    , const nm_cl_index_t out_size
    , const nm_cl_index_t ashape_size
    , const nm_cl_index_t bshape_size
)
{
    static_assert( meta::has_address_space_v<const __generic nmtools_maybe<nmtools::array::hybrid_ndarray<int, 8, 1>>> );
    auto output = view::mutable_ref(out_ptr,out_size);

    auto ashape = opencl::create_vector(ashape_ptr,ashape_size);
    auto bshape = opencl::create_vector(bshape_ptr,bshape_size);

    broadcast_shape(output,ashape,bshape);
}

kernel void test_broadcast_shape_ternary(
      global int* out_ptr
    , global const int* ashape_ptr
    , global const int* bshape_ptr
    , global const int* cshape_ptr
    , const nm_cl_index_t out_size
    , const nm_cl_index_t ashape_size
    , const nm_cl_index_t bshape_size
    , const nm_cl_index_t cshape_size
)
{
    auto output = view::mutable_ref(out_ptr,out_size);

    auto ashape = opencl::create_vector(ashape_ptr,ashape_size);
    auto bshape = opencl::create_vector(bshape_ptr,bshape_size);
    auto cshape = opencl::create_vector(cshape_ptr,cshape_size);

    broadcast_shape(output,ashape,bshape,cshape);
}

kernel void test_broadcast_shape_quaternary(
      global int* out_ptr
    , global const int* ashape_ptr
    , global const int* bshape_ptr
    , global const int* cshape_ptr
    , global const int* dshape_ptr
    , const nm_cl_index_t out_size
    , const nm_cl_index_t ashape_size
    , const nm_cl_index_t bshape_size
    , const nm_cl_index_t cshape_size
    , const nm_cl_index_t dshape_size
)
{
    auto output = view::mutable_ref(out_ptr,out_size);

    auto ashape = opencl::create_vector(ashape_ptr,ashape_size);
    auto bshape = opencl::create_vector(bshape_ptr,bshape_size);
    auto cshape = opencl::create_vector(cshape_ptr,cshape_size);
    auto dshape = opencl::create_vector(dshape_ptr,dshape_size);

    broadcast_shape(output,ashape,bshape,cshape,dshape);
}

#else

#include "nmtools/testing/data/index/broadcast_shape.hpp"
#include "nmtools/testing/opencl.hpp"
#include <cstring>

namespace testing = nmtools::testing;

#define BROADCAST_SHAPE_SUBCASE(case_name, ...) \
SUBCASE(#case_name) \
{ \
    NMTOOLS_TESTING_DECLARE_NS(broadcast_shape, case_name); \
    using namespace args; \
    tester.test(opencl::default_context(),expect::expected,__VA_ARGS__); \
}

extern unsigned char nm_cl_test_broadcast_shape_spv[];
extern nm_cl_index_t nm_cl_test_broadcast_shape_spv_len;

static auto tester = testing::OpenCLTester({
        {2,binary_broadcast_shape_kernel_name},
        {3,ternary_broadcast_shape_kernel_name},
        {4,quaternary_broadcast_sahpe_kernel_name}
    }
    ,nm_cl_test_broadcast_shape_spv
    ,nm_cl_test_broadcast_shape_spv_len
);

TEST_CASE("broadcast_shape(case1)" * doctest::test_suite("index::broadcast_shape"))
{
    BROADCAST_SHAPE_SUBCASE(case1, a_a, b_a);
    BROADCAST_SHAPE_SUBCASE(case1, a_v, b_v);
    BROADCAST_SHAPE_SUBCASE(case1, a_h, b_h);
    BROADCAST_SHAPE_SUBCASE(case1, a_sv, b_sv);

    BROADCAST_SHAPE_SUBCASE(case1, a_v, b_a);
    BROADCAST_SHAPE_SUBCASE(case1, a_h, b_a);
    BROADCAST_SHAPE_SUBCASE(case1, a_sv, b_a);

    BROADCAST_SHAPE_SUBCASE(case1, a_a, b_v);
    BROADCAST_SHAPE_SUBCASE(case1, a_h, b_v);
    BROADCAST_SHAPE_SUBCASE(case1, a_sv, b_v);

    BROADCAST_SHAPE_SUBCASE(case1, a_a, b_h);
    BROADCAST_SHAPE_SUBCASE(case1, a_v, b_h);
    BROADCAST_SHAPE_SUBCASE(case1, a_sv, b_h);

    BROADCAST_SHAPE_SUBCASE(case1, a_a, b_sv);
    BROADCAST_SHAPE_SUBCASE(case1, a_v, b_sv);
    BROADCAST_SHAPE_SUBCASE(case1, a_h, b_sv);
}

TEST_CASE("broadcast_shape(case2)" * doctest::test_suite("index::broadcast_shape"))
{
    BROADCAST_SHAPE_SUBCASE(case2, a_a, b_a);
    BROADCAST_SHAPE_SUBCASE(case2, a_v, b_v);
    BROADCAST_SHAPE_SUBCASE(case2, a_h, b_h);
    BROADCAST_SHAPE_SUBCASE(case2, a_sv, b_sv);

    BROADCAST_SHAPE_SUBCASE(case2, a_v, b_a);
    BROADCAST_SHAPE_SUBCASE(case2, a_h, b_a);
    BROADCAST_SHAPE_SUBCASE(case2, a_sv, b_a);

    BROADCAST_SHAPE_SUBCASE(case2, a_a, b_v);
    BROADCAST_SHAPE_SUBCASE(case2, a_h, b_v);
    BROADCAST_SHAPE_SUBCASE(case2, a_sv, b_v);

    BROADCAST_SHAPE_SUBCASE(case2, a_a, b_h);
    BROADCAST_SHAPE_SUBCASE(case2, a_v, b_h);
    BROADCAST_SHAPE_SUBCASE(case2, a_sv, b_h);

    BROADCAST_SHAPE_SUBCASE(case2, a_a, b_sv);
    BROADCAST_SHAPE_SUBCASE(case2, a_v, b_sv);
    BROADCAST_SHAPE_SUBCASE(case2, a_h, b_sv);
}

TEST_CASE("broadcast_shape(case3)" * doctest::test_suite("index::broadcast_shape"))
{
    BROADCAST_SHAPE_SUBCASE(case3, a_a, b_a);
    BROADCAST_SHAPE_SUBCASE(case3, a_v, b_v);
    BROADCAST_SHAPE_SUBCASE(case3, a_h, b_h);
    BROADCAST_SHAPE_SUBCASE(case3, a_sv, b_sv);

    BROADCAST_SHAPE_SUBCASE(case3, a_v, b_a);
    BROADCAST_SHAPE_SUBCASE(case3, a_h, b_a);
    BROADCAST_SHAPE_SUBCASE(case3, a_sv, b_a);

    BROADCAST_SHAPE_SUBCASE(case3, a_a, b_v);
    BROADCAST_SHAPE_SUBCASE(case3, a_h, b_v);
    BROADCAST_SHAPE_SUBCASE(case3, a_sv, b_v);

    BROADCAST_SHAPE_SUBCASE(case3, a_a, b_h);
    BROADCAST_SHAPE_SUBCASE(case3, a_v, b_h);
    BROADCAST_SHAPE_SUBCASE(case3, a_sv, b_h);

    BROADCAST_SHAPE_SUBCASE(case3, a_a, b_sv);
    BROADCAST_SHAPE_SUBCASE(case3, a_v, b_sv);
    BROADCAST_SHAPE_SUBCASE(case3, a_h, b_sv);
}

TEST_CASE("broadcast_shape(case4)" * doctest::test_suite("index::broadcast_shape"))
{
    BROADCAST_SHAPE_SUBCASE(case4, a_a, b_a);
    BROADCAST_SHAPE_SUBCASE(case4, a_v, b_v);
    BROADCAST_SHAPE_SUBCASE(case4, a_h, b_h);
    BROADCAST_SHAPE_SUBCASE(case1, a_sv, b_sv);

    BROADCAST_SHAPE_SUBCASE(case4, a_v, b_a);
    BROADCAST_SHAPE_SUBCASE(case4, a_h, b_a);
    BROADCAST_SHAPE_SUBCASE(case4, a_sv, b_a);

    BROADCAST_SHAPE_SUBCASE(case4, a_a, b_v);
    BROADCAST_SHAPE_SUBCASE(case4, a_h, b_v);
    BROADCAST_SHAPE_SUBCASE(case4, a_sv, b_v);

    BROADCAST_SHAPE_SUBCASE(case4, a_a, b_h);
    BROADCAST_SHAPE_SUBCASE(case4, a_v, b_h);
    BROADCAST_SHAPE_SUBCASE(case4, a_sv, b_h);

    BROADCAST_SHAPE_SUBCASE(case4, a_a, b_sv);
    BROADCAST_SHAPE_SUBCASE(case4, a_v, b_sv);
    BROADCAST_SHAPE_SUBCASE(case4, a_h, b_sv);
}

TEST_CASE("broadcast_shape(case5)" * doctest::test_suite("index::broadcast_shape"))
{
    BROADCAST_SHAPE_SUBCASE(case5, a_a, b_a);
    BROADCAST_SHAPE_SUBCASE(case5, a_v, b_v);
    BROADCAST_SHAPE_SUBCASE(case5, a_h, b_h);
    BROADCAST_SHAPE_SUBCASE(case5, a_sv, b_sv);

    BROADCAST_SHAPE_SUBCASE(case5, a_v, b_a);
    BROADCAST_SHAPE_SUBCASE(case5, a_h, b_a);
    BROADCAST_SHAPE_SUBCASE(case5, a_sv, b_a);

    BROADCAST_SHAPE_SUBCASE(case5, a_a, b_v);
    BROADCAST_SHAPE_SUBCASE(case5, a_h, b_v);
    BROADCAST_SHAPE_SUBCASE(case5, a_sv, b_v);

    BROADCAST_SHAPE_SUBCASE(case5, a_a, b_h);
    BROADCAST_SHAPE_SUBCASE(case5, a_v, b_h);
    BROADCAST_SHAPE_SUBCASE(case5, a_sv, b_h);

    BROADCAST_SHAPE_SUBCASE(case5, a_a, b_sv);
    BROADCAST_SHAPE_SUBCASE(case5, a_v, b_sv);
    BROADCAST_SHAPE_SUBCASE(case5, a_h, b_sv);
}

TEST_CASE("broadcast_shape(case8)" * doctest::test_suite("index::broadcast_shape"))
{
    BROADCAST_SHAPE_SUBCASE(case8, a_a, b_a, c_a);
    BROADCAST_SHAPE_SUBCASE(case8, a_v, b_v, c_v);
    BROADCAST_SHAPE_SUBCASE(case8, a_h, b_h, c_h);
    BROADCAST_SHAPE_SUBCASE(case8, a_sv, b_sv, c_sv);

    BROADCAST_SHAPE_SUBCASE(case8, a_v, b_a, c_a);
    BROADCAST_SHAPE_SUBCASE(case8, a_h, b_a, c_a);
    BROADCAST_SHAPE_SUBCASE(case8, a_sv, b_a, c_a);

    BROADCAST_SHAPE_SUBCASE(case8, a_a, b_v, c_v);
    BROADCAST_SHAPE_SUBCASE(case8, a_h, b_v, c_v);
    BROADCAST_SHAPE_SUBCASE(case8, a_sv, b_v, c_v);

    BROADCAST_SHAPE_SUBCASE(case8, a_a, b_h, c_h);
    BROADCAST_SHAPE_SUBCASE(case8, a_v, b_h, c_h);
    BROADCAST_SHAPE_SUBCASE(case8, a_sv, b_h, c_h);

    BROADCAST_SHAPE_SUBCASE(case8, a_a, b_sv, c_sv);
    BROADCAST_SHAPE_SUBCASE(case8, a_v, b_sv, c_sv);
    BROADCAST_SHAPE_SUBCASE(case8, a_h, b_sv, c_sv);
}

TEST_CASE("broadcast_shape(case10)" * doctest::test_suite("index::broadcast_shape"))
{
    BROADCAST_SHAPE_SUBCASE(case10, a_a, b_a, c_a, d_a);
    BROADCAST_SHAPE_SUBCASE(case10, a_v, b_v, c_v, d_v);
    BROADCAST_SHAPE_SUBCASE(case10, a_h, b_h, c_h, d_h);
    BROADCAST_SHAPE_SUBCASE(case10, a_sv, b_sv, c_sv, d_sv);

    // BROADCAST_SHAPE_SUBCASE(case10, a_v, b_a);
    // BROADCAST_SHAPE_SUBCASE(case10, a_h, b_a);
    // BROADCAST_SHAPE_SUBCASE(case10, a_sv, b_a);

    // BROADCAST_SHAPE_SUBCASE(case10, a_a, b_v);
    // BROADCAST_SHAPE_SUBCASE(case10, a_h, b_v);
    // BROADCAST_SHAPE_SUBCASE(case10, a_sv, b_v);

    // BROADCAST_SHAPE_SUBCASE(case10, a_a, b_h);
    // BROADCAST_SHAPE_SUBCASE(case10, a_v, b_h);
    // BROADCAST_SHAPE_SUBCASE(case10, a_sv, b_h);

    // BROADCAST_SHAPE_SUBCASE(case10, a_a, b_sv);
    // BROADCAST_SHAPE_SUBCASE(case10, a_v, b_sv);
    // BROADCAST_SHAPE_SUBCASE(case10, a_h, b_sv);
}

#endif