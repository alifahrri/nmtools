#include "nmtools/evaluator/opencl/kernels/where.hpp"
#ifndef NMTOOLS_OPENCL_BUILD_KERNELS
#include "nmtools/evaluator/opencl/evaluator.hpp"
#include "nmtools/array/arange.hpp"
#include "nmtools/array/where.hpp"
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

TEST_CASE("where(case1)" * doctest::test_suite("where"))
{
    auto x_shape = nmtools_array{12};
    auto y_shape = nmtools_array{12};

    auto x_numel = ix::product(x_shape);
    auto x_start = 1;
    auto x_stop  = x_numel+x_start;

    auto x = na::reshape(na::arange(x_start,x_stop),x_shape);

    auto y_numel = ix::product(y_shape);
    auto y_start = 13;
    auto y_stop  = y_numel+y_start;

    auto y = na::reshape(na::arange(y_start,y_stop),y_shape);

    auto cond = nmtools_array<int,12>{1,1,1,1,1,1,0,0,0,0,0,0};

    OPENCL_TEST(where,cond,x,y);
}

#endif // NMTOOLS_OPENCL_BUILD_KERNELS