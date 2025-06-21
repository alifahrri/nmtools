#include "nmtools/evaluator/opencl/kernels/flatten.hpp"
#ifndef NMTOOLS_OPENCL_BUILD_KERNELS
#include "nmtools/evaluator/opencl/evaluator.hpp"
#include "nmtools/array/arange.hpp"
#include "nmtools/array/flatten.hpp"
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

TEST_CASE("flatten(case1)" * doctest::test_suite("flatten"))
{
    auto src_shape = nmtools_array{12,8};
    auto dst_shape = nmtools_array{6,4};

    auto numel = ix::product(src_shape);
    auto start = 1;
    auto stop  = numel+start;
    auto input = na::reshape(na::arange(start,stop),src_shape);

    OPENCL_TEST(flatten,input);
}

#endif // NMTOOLS_OPENCL_BUILD_KERNELS