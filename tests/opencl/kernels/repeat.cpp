#include "nmtools/evaluator/opencl/kernels/repeat.hpp"
#ifndef NMTOOLS_OPENCL_BUILD_KERNELS
#include "nmtools/evaluator/opencl/context.hpp"
#include "nmtools/evaluator/opencl/evaluator.hpp"
#include "nmtools/array/arange.hpp"
#include "nmtools/array/repeat.hpp"
#include "nmtools/array/reshape.hpp"
#include "nmtools/testing/doctest.hpp"

namespace nm = nmtools;
namespace ix = nm::index;
namespace na = nmtools;
namespace meta = nm::meta;
namespace opencl = na::opencl;

#define OPENCL_TEST(fn,...) \
{ \
    auto expect = na::fn(__VA_ARGS__); \
    auto result = na::fn(__VA_ARGS__,opencl::default_context()); \
    NMTOOLS_ASSERT_EQUAL( nm::shape(result), nm::shape(expect) ); \
    NMTOOLS_ASSERT_CLOSE( result, expect ); \
}

TEST_CASE("repeat(case1)" * doctest::test_suite("opencl::repeat"))
{
    auto shape = nmtools_array<uint32_t,2>{1,64};
    auto input = na::reshape(na::arange(ix::product(shape)),shape);
    auto repeats = nmtools_array<uint32_t,1>{2};
    auto axis = 0;
    OPENCL_TEST(repeat,input,repeats,axis);
}

TEST_CASE("repeat(case2)" * doctest::test_suite("opencl::repeat"))
{
    auto shape = nmtools_array<uint32_t,2>{8,8};
    auto input = na::reshape(na::arange(ix::product(shape)),shape);
    auto repeats = nmtools_array<uint32_t,8>{2,1,1,1,1,1,1,1};
    auto axis = 0;
    OPENCL_TEST(repeat,input,repeats,axis);
}

TEST_CASE("repeat(case3)" * doctest::test_suite("opencl::repeat"))
{
    auto shape = nmtools_array<uint32_t,2>{64,1};
    auto input = na::reshape(na::arange(ix::product(shape)),shape);
    auto repeats = nmtools_array<uint32_t,1>{3};
    auto axis = 1;
    OPENCL_TEST(repeat,input,repeats,axis);
}

TEST_CASE("repeat(case4)" * doctest::test_suite("opencl::repeat"))
{
    auto shape = nmtools_array<uint32_t,2>{8,8};
    auto input = na::reshape(na::arange(ix::product(shape)),shape);
    auto repeats = nmtools_array<uint32_t,8>{1,2,3,4,1,1,1,1};
    auto axis = 1;
    OPENCL_TEST(repeat,input,repeats,axis);
}

#endif // NMTOOLS_OPENCL_BUILD_KERNELS