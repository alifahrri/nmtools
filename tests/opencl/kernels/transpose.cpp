#include "nmtools/array/eval/opencl/kernels/transpose.hpp"
#ifndef NMTOOLS_OPENCL_BUILD_KERNELS
#include "nmtools/array/eval/opencl/context.hpp"
#include "nmtools/array/eval/opencl/evaluator.hpp"
#include "nmtools/array/array/arange.hpp"
#include "nmtools/array/array/transpose.hpp"
#include "nmtools/array/array/reshape.hpp"
#include "nmtools/testing/doctest.hpp"

namespace nm = nmtools;
namespace ix = nm::index;
namespace na = nm::array;
namespace meta = nm::meta;
namespace opencl = na::opencl;

#define OPENCL_TEST(fn,...) \
{ \
    auto expect = na::fn(__VA_ARGS__); \
    auto result = na::fn(__VA_ARGS__,opencl::default_context()); \
    NMTOOLS_ASSERT_EQUAL( nm::shape(result),nm::shape(expect)); \
    NMTOOLS_ASSERT_CLOSE( result, expect ); \
}

TEST_CASE("transpose(case1)" * doctest::test_suite("opencl::transpose"))
{
    auto shape = nmtools_array<uint32_t,2>{1,64};
    auto inp = na::reshape(na::arange(ix::product(shape)),shape);
    auto axes = nmtools_array<uint32_t,2>{0,1};
    OPENCL_TEST(transpose,inp,axes);
}

TEST_CASE("transpose(case1)" * doctest::test_suite("opencl::transpose"))
{
    auto shape = nmtools_array<uint32_t,2>{1,64};
    auto inp = na::reshape(na::arange(ix::product(shape)),shape);
    auto axes = nmtools_array<uint32_t,2>{1,0};
    OPENCL_TEST(transpose,inp,axes);
}

#endif // NMTOOLS_OPENCL_BUILD_KERNEL