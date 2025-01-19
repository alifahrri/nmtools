#include "nmtools/evaluator/opencl/kernels/reshape.hpp"
#ifndef NMTOOLS_OPENCL_BUILD_KERNELS
#include "nmtools/evaluator/opencl/evaluator.hpp"
#include "nmtools/array/arange.hpp"
#include "nmtools/array/reshape.hpp"
#include "nmtools/array/reshape.hpp"
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
    NMTOOLS_ASSERT_EQUAL( nm::shape(result), nm::shape(expect) ); \
    NMTOOLS_ASSERT_CLOSE( result, expect ); \
}

TEST_CASE("reshape(case1)" * doctest::test_suite("reshape"))
{
    auto src_shape = nmtools_array{12,1};
    auto new_shape = nmtools_array{12};

    auto numel = ix::product(src_shape);
    auto start = 1;
    auto stop  = numel+start;
    auto input = na::reshape(na::arange(start,stop),src_shape);

    OPENCL_TEST(reshape,input);
}

#endif // NMTOOLS_OPENCL_BUILD_KERNELS