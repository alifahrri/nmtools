#include "nmtools/array/evaluator/opencl/kernels/resize.hpp"
#ifndef NMTOOLS_OPENCL_BUILD_KERNELS
#include "nmtools/array/evaluator/opencl/evaluator.hpp"
#include "nmtools/array/array/arange.hpp"
#include "nmtools/array/array/resize.hpp"
#include "nmtools/array/array/reshape.hpp"
#include "nmtools/utility/unwrap.hpp"
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
    NMTOOLS_ASSERT_EQUAL( nm::shape(nm::unwrap(result)), nm::shape(nm::unwrap(expect)) ); \
    NMTOOLS_ASSERT_CLOSE( nm::unwrap(result), nm::unwrap(expect) ); \
}

TEST_CASE("resize(case1)" * doctest::test_suite("resize"))
{
    auto src_shape = nmtools_array{12,8};
    auto dst_shape = nmtools_array{6,4};

    auto numel = ix::product(src_shape);
    auto start = 1;
    auto stop  = numel+start;
    auto input = na::reshape(na::arange(start,stop),src_shape);

    OPENCL_TEST(resize,input,dst_shape);
}

TEST_CASE("resize(case2)" * doctest::test_suite("resize"))
{
    auto src_shape = nmtools_array{12,8};
    auto dst_shape = nmtools_array{6,6};

    auto numel = ix::product(src_shape);
    auto start = 1;
    auto stop  = numel+start;
    auto input = na::reshape(na::arange(start,stop),src_shape);

    OPENCL_TEST(resize,input,dst_shape);
}

TEST_CASE("resize(case3)" * doctest::test_suite("resize"))
{
    auto src_shape = nmtools_array{12,8};
    auto dst_shape = nmtools_array{8,4};

    auto numel = ix::product(src_shape);
    auto start = 1;
    auto stop  = numel+start;
    auto input = na::reshape(na::arange(start,stop),src_shape);

    OPENCL_TEST(resize,input,dst_shape);
}

TEST_CASE("resize(case4)" * doctest::test_suite("resize"))
{
    auto src_shape = nmtools_array{12,8};
    auto dst_shape = nmtools_array{8,6};

    auto numel = ix::product(src_shape);
    auto start = 1;
    auto stop  = numel+start;
    auto input = na::reshape(na::arange(start,stop),src_shape);

    OPENCL_TEST(resize,input,dst_shape);
}

TEST_CASE("resize(case5)" * doctest::test_suite("resize"))
{
    auto src_shape = nmtools_array{12,8};
    auto dst_shape = nmtools_array{12,4};

    auto numel = ix::product(src_shape);
    auto start = 1;
    auto stop  = numel+start;
    auto input = na::reshape(na::arange(start,stop),src_shape);

    OPENCL_TEST(resize,input,dst_shape);
}

TEST_CASE("resize(case6)" * doctest::test_suite("resize"))
{
    auto src_shape = nmtools_array{12,8};
    auto dst_shape = nmtools_array{24,8};

    auto numel = ix::product(src_shape);
    auto start = 1;
    auto stop  = numel+start;
    auto input = na::reshape(na::arange(start,stop),src_shape);

    OPENCL_TEST(resize,input,dst_shape);
}

#endif // NMTOOLS_OPENCL_BUILD_KERNELS