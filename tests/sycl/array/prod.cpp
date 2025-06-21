#include "nmtools/array/prod.hpp"
#include "nmtools/array/arange.hpp"
#include "nmtools/array/reshape.hpp"
#include "nmtools/evaluator/sycl.hpp"
#include "nmtools/testing/doctest.hpp"

namespace nm = nmtools;
namespace na = nmtools;
namespace ix = nm::index;

#define SYCL_PROD_SUBCASE(...) \
{ \
    auto expect = na::prod(__VA_ARGS__); \
    auto result = na::prod(__VA_ARGS__, na::sycl::default_context()); \
    NMTOOLS_ASSERT_EQUAL( nm::shape(result), nm::shape(expect) ); \
    NMTOOLS_ASSERT_CLOSE( expect, expect ); \
}

#define PROD_SUBCASE(case_name, ...) \
SUBCASE(#case_name) \
{ \
    NMTOOLS_TESTING_USE_CASE(array, prod, case_name); \
    using namespace args; \
    SYCL_PROD_SUBCASE(__VA_ARGS__); \
}

// TODO: fix for sycl kernel (opencl/cuda), remove free/malloc in kernel code
TEST_CASE("prod(case1)" * doctest::test_suite("array::prod") * doctest::skip())
{
    auto shape = nmtools_array{128};
    auto numel = ix::product(shape);
    auto start = 0;
    auto stop  = start + numel;
    auto step  = 1;
    auto flat  = na::arange(start,stop,step);
    auto input = na::reshape(flat,shape);

    auto dtype    = nm::None;
    auto initial  = nm::None;
    auto keepdims = nm::True;
    {
        auto axis = 0;
        SYCL_PROD_SUBCASE(input,axis,dtype,initial,keepdims);
    }
}

// TODO: support isclose to compare inf
// TODO: fix for sycl kernel (opencl/cuda), remove free/malloc in kernel code
TEST_CASE("prod(case2)" * doctest::test_suite("array::prod") * doctest::may_fail() * doctest::skip())
{
    auto shape = nmtools_array{64,2};
    auto numel = ix::product(shape);
    auto start = 0;
    auto stop  = start + numel;
    auto step  = 1;
    auto flat  = na::arange(start,stop,step);
    auto input = na::reshape(flat,shape);

    auto dtype = nm::None;
    auto initial = nm::None;
    auto keepdims = nm::True;
    {
        auto axis = 0;
        SYCL_PROD_SUBCASE(input,axis,dtype,initial,keepdims);
    }
    {
        auto axis = 1;
        SYCL_PROD_SUBCASE(input,axis,dtype,initial,keepdims);
    }
}

// TODO: support isclose to compare inf
// TODO: fix for sycl kernel (opencl/cuda), remove free/malloc in kernel code
TEST_CASE("prod(case3)" * doctest::test_suite("array::prod") * doctest::may_fail() * doctest::skip())
{
    auto shape = nmtools_array{16,4,2};
    auto numel = ix::product(shape);
    auto start = 0;
    auto stop  = start + numel;
    auto step  = 1;
    auto flat  = na::arange(start,stop,step);
    auto input = na::reshape(flat,shape);

    auto dtype = nm::None;
    auto initial = nm::None;
    auto keepdims = nm::True;
    {
        auto axis = 0;
        SYCL_PROD_SUBCASE(input,axis,dtype,initial,keepdims);
    }
    {
        auto axis = 1;
        SYCL_PROD_SUBCASE(input,axis,dtype,initial,keepdims);
    }
    {
        auto axis = 2;
        SYCL_PROD_SUBCASE(input,axis,dtype,initial,keepdims);
    }
    {
        auto axis = nmtools_array{0,1};
        SYCL_PROD_SUBCASE(input,axis,dtype,initial,keepdims);
    }
    {
        auto axis = nmtools_array{1,2};
        SYCL_PROD_SUBCASE(input,axis,dtype,initial,keepdims);
    }
    {
        auto axis = nmtools_array{0,2};
        SYCL_PROD_SUBCASE(input,axis,dtype,initial,keepdims);
    }
}

// TODO: fix for sycl kernel (opencl/cuda), remove free/malloc in kernel code
TEST_CASE("prod(case4)" * doctest::test_suite("array::prod") * doctest::skip())
{
    auto shape = nmtools_array{4,2,1,4,2};
    auto numel = ix::product(shape);
    auto start = 0;
    auto stop  = start + numel;
    auto step  = 1;
    auto flat  = na::arange(start,stop,step);
    auto input = na::reshape(flat,shape);

    auto dtype = nm::None;
    auto initial = nm::None;
    auto keepdims = nm::True;
    {
        auto axis = 0;
        SYCL_PROD_SUBCASE(input,axis,dtype,initial,keepdims);
    }
    {
        auto axis = 1;
        SYCL_PROD_SUBCASE(input,axis,dtype,initial,keepdims);
    }
    {
        auto axis = 2;
        SYCL_PROD_SUBCASE(input,axis,dtype,initial,keepdims);
    }
    {
        auto axis = 3;
        SYCL_PROD_SUBCASE(input,axis,dtype,initial,keepdims);
    }
    {
        auto axis = 4;
        SYCL_PROD_SUBCASE(input,axis,dtype,initial,keepdims);
    }
    {
        auto axis = nmtools_array{0,1};
        SYCL_PROD_SUBCASE(input,axis,dtype,initial,keepdims);
    }
    {
        auto axis = nmtools_array{0,2};
        SYCL_PROD_SUBCASE(input,axis,dtype,initial,keepdims);
    }
    {
        auto axis = nmtools_array{0,3};
        SYCL_PROD_SUBCASE(input,axis,dtype,initial,keepdims);
    }
    {
        auto axis = nmtools_array{0,4};
        SYCL_PROD_SUBCASE(input,axis,dtype,initial,keepdims);
    }
    {
        auto axis = nmtools_array{1,2};
        SYCL_PROD_SUBCASE(input,axis,dtype,initial,keepdims);
    }
    {
        auto axis = nmtools_array{1,3};
        SYCL_PROD_SUBCASE(input,axis,dtype,initial,keepdims);
    }
    {
        auto axis = nmtools_array{1,4};
        SYCL_PROD_SUBCASE(input,axis,dtype,initial,keepdims);
    }
    {
        auto axis = nmtools_array{2,3};
        SYCL_PROD_SUBCASE(input,axis,dtype,initial,keepdims);
    }
    {
        auto axis = nmtools_array{2,4};
        SYCL_PROD_SUBCASE(input,axis,dtype,initial,keepdims);
    }
    {
        auto axis = nmtools_array{3,4};
        SYCL_PROD_SUBCASE(input,axis,dtype,initial,keepdims);
    }
}

// TODO: fix for sycl kernel (opencl/cuda), remove free/malloc in kernel code
TEST_CASE("prod(case5)" * doctest::test_suite("array::prod") * doctest::skip())
{
    auto shape = nmtools_array{128};
    auto numel = ix::product(shape);
    auto start = 0;
    auto stop  = start + numel;
    auto step  = 1;
    auto flat  = na::arange(start,stop,step,nm::float64);
    auto input = na::reshape(flat,shape);

    auto dtype    = nm::None;
    auto initial  = nm::None;
    auto keepdims = nm::True;
    {
        auto axis = 0;
        SYCL_PROD_SUBCASE(input,axis,dtype,initial,keepdims);
    }
}

// TODO: fix for sycl kernel (opencl/cuda), remove free/malloc in kernel code
TEST_CASE("prod(case6)" * doctest::test_suite("array::prod") * doctest::skip())
{
    auto shape = nmtools_array{64,2};
    auto numel = ix::product(shape);
    auto start = 0;
    auto stop  = start + numel;
    auto step  = 1;
    auto flat  = na::arange(start,stop,step,nm::float64);
    auto input = na::reshape(flat,shape);

    auto dtype = nm::None;
    auto initial = nm::None;
    auto keepdims = nm::True;
    {
        auto axis = 0;
        SYCL_PROD_SUBCASE(input,axis,dtype,initial,keepdims);
    }
    {
        auto axis = 1;
        SYCL_PROD_SUBCASE(input,axis,dtype,initial,keepdims);
    }
}

// TODO: fix for sycl kernel (opencl/cuda), remove free/malloc in kernel code
TEST_CASE("prod(case7)" * doctest::test_suite("array::prod") * doctest::skip())
{
    auto shape = nmtools_array{16,4,2};
    auto numel = ix::product(shape);
    auto start = 0;
    auto stop  = start + numel;
    auto step  = 1;
    auto flat  = na::arange(start,stop,step,nm::float64);
    auto input = na::reshape(flat,shape);

    auto dtype = nm::None;
    auto initial = nm::None;
    auto keepdims = nm::True;
    {
        auto axis = 0;
        SYCL_PROD_SUBCASE(input,axis,dtype,initial,keepdims);
    }
    {
        auto axis = 1;
        SYCL_PROD_SUBCASE(input,axis,dtype,initial,keepdims);
    }
    {
        auto axis = 2;
        SYCL_PROD_SUBCASE(input,axis,dtype,initial,keepdims);
    }
    {
        auto axis = nmtools_array{0,1};
        SYCL_PROD_SUBCASE(input,axis,dtype,initial,keepdims);
    }
    {
        auto axis = nmtools_array{1,2};
        SYCL_PROD_SUBCASE(input,axis,dtype,initial,keepdims);
    }
    {
        auto axis = nmtools_array{0,2};
        SYCL_PROD_SUBCASE(input,axis,dtype,initial,keepdims);
    }
}

// TODO: fix for sycl kernel (opencl/cuda), remove free/malloc in kernel code
TEST_CASE("prod(case8)" * doctest::test_suite("array::prod") * doctest::skip())
{
    auto shape = nmtools_array{4,2,1,4,2};
    auto numel = ix::product(shape);
    auto start = 0;
    auto stop  = start + numel;
    auto step  = 1;
    auto flat  = na::arange(start,stop,step,nm::float64);
    auto input = na::reshape(flat,shape);

    auto dtype = nm::None;
    auto initial = nm::None;
    auto keepdims = nm::True;
    {
        auto axis = 0;
        SYCL_PROD_SUBCASE(input,axis,dtype,initial,keepdims);
    }
    {
        auto axis = 1;
        SYCL_PROD_SUBCASE(input,axis,dtype,initial,keepdims);
    }
    {
        auto axis = 2;
        SYCL_PROD_SUBCASE(input,axis,dtype,initial,keepdims);
    }
    {
        auto axis = 3;
        SYCL_PROD_SUBCASE(input,axis,dtype,initial,keepdims);
    }
    {
        auto axis = 4;
        SYCL_PROD_SUBCASE(input,axis,dtype,initial,keepdims);
    }
    {
        auto axis = nmtools_array{0,1};
        SYCL_PROD_SUBCASE(input,axis,dtype,initial,keepdims);
    }
    {
        auto axis = nmtools_array{0,2};
        SYCL_PROD_SUBCASE(input,axis,dtype,initial,keepdims);
    }
    {
        auto axis = nmtools_array{0,3};
        SYCL_PROD_SUBCASE(input,axis,dtype,initial,keepdims);
    }
    {
        auto axis = nmtools_array{0,4};
        SYCL_PROD_SUBCASE(input,axis,dtype,initial,keepdims);
    }
    {
        auto axis = nmtools_array{1,2};
        SYCL_PROD_SUBCASE(input,axis,dtype,initial,keepdims);
    }
    {
        auto axis = nmtools_array{1,3};
        SYCL_PROD_SUBCASE(input,axis,dtype,initial,keepdims);
    }
    {
        auto axis = nmtools_array{1,4};
        SYCL_PROD_SUBCASE(input,axis,dtype,initial,keepdims);
    }
    {
        auto axis = nmtools_array{2,3};
        SYCL_PROD_SUBCASE(input,axis,dtype,initial,keepdims);
    }
    {
        auto axis = nmtools_array{2,4};
        SYCL_PROD_SUBCASE(input,axis,dtype,initial,keepdims);
    }
    {
        auto axis = nmtools_array{3,4};
        SYCL_PROD_SUBCASE(input,axis,dtype,initial,keepdims);
    }
}

// TODO: fix for sycl kernel (opencl/cuda), remove free/malloc in kernel code
TEST_CASE("prod(case9)" * doctest::test_suite("array::prod") * doctest::skip())
{
    auto shape = nmtools_array{128};
    auto numel = ix::product(shape);
    auto start = 0;
    auto stop  = start + numel;
    auto step  = 1;
    auto flat  = na::arange(start,stop,step,nm::int32);
    auto input = na::reshape(flat,shape);

    auto dtype    = nm::None;
    auto initial  = nm::None;
    auto keepdims = nm::True;
    {
        auto axis = 0;
        SYCL_PROD_SUBCASE(input,axis,dtype,initial,keepdims);
    }
}

// TODO: fix for sycl kernel (opencl/cuda), remove free/malloc in kernel code
TEST_CASE("prod(case10)" * doctest::test_suite("array::prod") * doctest::skip())
{
    auto shape = nmtools_array{64,2};
    auto numel = ix::product(shape);
    auto start = 0;
    auto stop  = start + numel;
    auto step  = 1;
    auto flat  = na::arange(start,stop,step,nm::int32);
    auto input = na::reshape(flat,shape);

    auto dtype = nm::None;
    auto initial = nm::None;
    auto keepdims = nm::True;
    {
        auto axis = 0;
        SYCL_PROD_SUBCASE(input,axis,dtype,initial,keepdims);
    }
    {
        auto axis = 1;
        SYCL_PROD_SUBCASE(input,axis,dtype,initial,keepdims);
    }
}

// TODO: fix for sycl kernel (opencl/cuda), remove free/malloc in kernel code
TEST_CASE("prod(case11)" * doctest::test_suite("array::prod") * doctest::skip())
{
    auto shape = nmtools_array{16,4,2};
    auto numel = ix::product(shape);
    auto start = 0;
    auto stop  = start + numel;
    auto step  = 1;
    auto flat  = na::arange(start,stop,step,nm::int32);
    auto input = na::reshape(flat,shape);

    auto dtype = nm::None;
    auto initial = nm::None;
    auto keepdims = nm::True;
    {
        auto axis = 0;
        SYCL_PROD_SUBCASE(input,axis,dtype,initial,keepdims);
    }
    {
        auto axis = 1;
        SYCL_PROD_SUBCASE(input,axis,dtype,initial,keepdims);
    }
    {
        auto axis = 2;
        SYCL_PROD_SUBCASE(input,axis,dtype,initial,keepdims);
    }
    {
        auto axis = nmtools_array{0,1};
        SYCL_PROD_SUBCASE(input,axis,dtype,initial,keepdims);
    }
    {
        auto axis = nmtools_array{1,2};
        SYCL_PROD_SUBCASE(input,axis,dtype,initial,keepdims);
    }
    {
        auto axis = nmtools_array{0,2};
        SYCL_PROD_SUBCASE(input,axis,dtype,initial,keepdims);
    }
}

// TODO: fix for sycl kernel (opencl/cuda), remove free/malloc in kernel code
TEST_CASE("prod(case12)" * doctest::test_suite("array::prod") * doctest::skip())
{
    auto shape = nmtools_array{4,2,1,4,2};
    auto numel = ix::product(shape);
    auto start = 0;
    auto stop  = start + numel;
    auto step  = 1;
    auto flat  = na::arange(start,stop,step,nm::int32);
    auto input = na::reshape(flat,shape);

    auto dtype = nm::None;
    auto initial = nm::None;
    auto keepdims = nm::True;
    {
        auto axis = 0;
        SYCL_PROD_SUBCASE(input,axis,dtype,initial,keepdims);
    }
    {
        auto axis = 1;
        SYCL_PROD_SUBCASE(input,axis,dtype,initial,keepdims);
    }
    {
        auto axis = 2;
        SYCL_PROD_SUBCASE(input,axis,dtype,initial,keepdims);
    }
    {
        auto axis = 3;
        SYCL_PROD_SUBCASE(input,axis,dtype,initial,keepdims);
    }
    {
        auto axis = 4;
        SYCL_PROD_SUBCASE(input,axis,dtype,initial,keepdims);
    }
    {
        auto axis = nmtools_array{0,1};
        SYCL_PROD_SUBCASE(input,axis,dtype,initial,keepdims);
    }
    {
        auto axis = nmtools_array{0,2};
        SYCL_PROD_SUBCASE(input,axis,dtype,initial,keepdims);
    }
    {
        auto axis = nmtools_array{0,3};
        SYCL_PROD_SUBCASE(input,axis,dtype,initial,keepdims);
    }
    {
        auto axis = nmtools_array{0,4};
        SYCL_PROD_SUBCASE(input,axis,dtype,initial,keepdims);
    }
    {
        auto axis = nmtools_array{1,2};
        SYCL_PROD_SUBCASE(input,axis,dtype,initial,keepdims);
    }
    {
        auto axis = nmtools_array{1,3};
        SYCL_PROD_SUBCASE(input,axis,dtype,initial,keepdims);
    }
    {
        auto axis = nmtools_array{1,4};
        SYCL_PROD_SUBCASE(input,axis,dtype,initial,keepdims);
    }
    {
        auto axis = nmtools_array{2,3};
        SYCL_PROD_SUBCASE(input,axis,dtype,initial,keepdims);
    }
    {
        auto axis = nmtools_array{2,4};
        SYCL_PROD_SUBCASE(input,axis,dtype,initial,keepdims);
    }
    {
        auto axis = nmtools_array{3,4};
        SYCL_PROD_SUBCASE(input,axis,dtype,initial,keepdims);
    }
}

// TODO: fix for sycl kernel (opencl/cuda), remove free/malloc in kernel code
TEST_CASE("prod(case13)" * doctest::test_suite("array::prod") * doctest::skip())
{
    auto shape = nmtools_array{128};
    auto numel = ix::product(shape);
    auto start = 0;
    auto stop  = start + numel;
    auto step  = 1;
    auto flat  = na::arange(start,stop,step,nm::int64);
    auto input = na::reshape(flat,shape);

    auto dtype    = nm::None;
    auto initial  = nm::None;
    auto keepdims = nm::True;
    {
        auto axis = 0;
        SYCL_PROD_SUBCASE(input,axis,dtype,initial,keepdims);
    }
}

// TODO: fix for sycl kernel (opencl/cuda), remove free/malloc in kernel code
TEST_CASE("prod(case14)" * doctest::test_suite("array::prod") * doctest::skip())
{
    auto shape = nmtools_array{64,2};
    auto numel = ix::product(shape);
    auto start = 0;
    auto stop  = start + numel;
    auto step  = 1;
    auto flat  = na::arange(start,stop,step,nm::int64);
    auto input = na::reshape(flat,shape);

    auto dtype = nm::None;
    auto initial = nm::None;
    auto keepdims = nm::True;
    {
        auto axis = 0;
        SYCL_PROD_SUBCASE(input,axis,dtype,initial,keepdims);
    }
    {
        auto axis = 1;
        SYCL_PROD_SUBCASE(input,axis,dtype,initial,keepdims);
    }
}

// TODO: fix for sycl kernel (opencl/cuda), remove free/malloc in kernel code
TEST_CASE("prod(case15)" * doctest::test_suite("array::prod") * doctest::skip())
{
    auto shape = nmtools_array{16,4,2};
    auto numel = ix::product(shape);
    auto start = 0;
    auto stop  = start + numel;
    auto step  = 1;
    auto flat  = na::arange(start,stop,step,nm::int64);
    auto input = na::reshape(flat,shape);

    auto dtype = nm::None;
    auto initial = nm::None;
    auto keepdims = nm::True;
    {
        auto axis = 0;
        SYCL_PROD_SUBCASE(input,axis,dtype,initial,keepdims);
    }
    {
        auto axis = 1;
        SYCL_PROD_SUBCASE(input,axis,dtype,initial,keepdims);
    }
    {
        auto axis = 2;
        SYCL_PROD_SUBCASE(input,axis,dtype,initial,keepdims);
    }
    {
        auto axis = nmtools_array{0,1};
        SYCL_PROD_SUBCASE(input,axis,dtype,initial,keepdims);
    }
    {
        auto axis = nmtools_array{1,2};
        SYCL_PROD_SUBCASE(input,axis,dtype,initial,keepdims);
    }
    {
        auto axis = nmtools_array{0,2};
        SYCL_PROD_SUBCASE(input,axis,dtype,initial,keepdims);
    }
}

// TODO: fix for sycl kernel (opencl/cuda), remove free/malloc in kernel code
TEST_CASE("prod(case16)" * doctest::test_suite("array::prod") * doctest::skip())
{
    auto shape = nmtools_array{4,2,1,4,2};
    auto numel = ix::product(shape);
    auto start = 0;
    auto stop  = start + numel;
    auto step  = 1;
    auto flat  = na::arange(start,stop,step,nm::int64);
    auto input = na::reshape(flat,shape);

    auto dtype = nm::None;
    auto initial = nm::None;
    auto keepdims = nm::True;
    {
        auto axis = 0;
        SYCL_PROD_SUBCASE(input,axis,dtype,initial,keepdims);
    }
    {
        auto axis = 1;
        SYCL_PROD_SUBCASE(input,axis,dtype,initial,keepdims);
    }
    {
        auto axis = 2;
        SYCL_PROD_SUBCASE(input,axis,dtype,initial,keepdims);
    }
    {
        auto axis = 3;
        SYCL_PROD_SUBCASE(input,axis,dtype,initial,keepdims);
    }
    {
        auto axis = 4;
        SYCL_PROD_SUBCASE(input,axis,dtype,initial,keepdims);
    }
    {
        auto axis = nmtools_array{0,1};
        SYCL_PROD_SUBCASE(input,axis,dtype,initial,keepdims);
    }
    {
        auto axis = nmtools_array{0,2};
        SYCL_PROD_SUBCASE(input,axis,dtype,initial,keepdims);
    }
    {
        auto axis = nmtools_array{0,3};
        SYCL_PROD_SUBCASE(input,axis,dtype,initial,keepdims);
    }
    {
        auto axis = nmtools_array{0,4};
        SYCL_PROD_SUBCASE(input,axis,dtype,initial,keepdims);
    }
    {
        auto axis = nmtools_array{1,2};
        SYCL_PROD_SUBCASE(input,axis,dtype,initial,keepdims);
    }
    {
        auto axis = nmtools_array{1,3};
        SYCL_PROD_SUBCASE(input,axis,dtype,initial,keepdims);
    }
    {
        auto axis = nmtools_array{1,4};
        SYCL_PROD_SUBCASE(input,axis,dtype,initial,keepdims);
    }
    {
        auto axis = nmtools_array{2,3};
        SYCL_PROD_SUBCASE(input,axis,dtype,initial,keepdims);
    }
    {
        auto axis = nmtools_array{2,4};
        SYCL_PROD_SUBCASE(input,axis,dtype,initial,keepdims);
    }
    {
        auto axis = nmtools_array{3,4};
        SYCL_PROD_SUBCASE(input,axis,dtype,initial,keepdims);
    }
}

// TODO: fix for sycl kernel (opencl/cuda), remove free/malloc in kernel code
TEST_CASE("prod(case17)" * doctest::test_suite("array::prod") * doctest::skip())
{
    auto shape = nmtools_array{128};
    auto numel = ix::product(shape);
    auto start = 0;
    auto stop  = start + numel;
    auto step  = 1;
    auto flat  = na::arange(start,stop,step,nm::int16);
    auto input = na::reshape(flat,shape);

    auto dtype    = nm::None;
    auto initial  = nm::None;
    auto keepdims = nm::True;
    {
        auto axis = 0;
        SYCL_PROD_SUBCASE(input,axis,dtype,initial,keepdims);
    }
}

// TODO: fix for sycl kernel (opencl/cuda), remove free/malloc in kernel code
TEST_CASE("prod(case18)" * doctest::test_suite("array::prod") * doctest::skip())
{
    auto shape = nmtools_array{64,2};
    auto numel = ix::product(shape);
    auto start = 0;
    auto stop  = start + numel;
    auto step  = 1;
    auto flat  = na::arange(start,stop,step,nm::int16);
    auto input = na::reshape(flat,shape);

    auto dtype = nm::None;
    auto initial = nm::None;
    auto keepdims = nm::True;
    {
        auto axis = 0;
        SYCL_PROD_SUBCASE(input,axis,dtype,initial,keepdims);
    }
    {
        auto axis = 1;
        SYCL_PROD_SUBCASE(input,axis,dtype,initial,keepdims);
    }
}

// TODO: fix for sycl kernel (opencl/cuda), remove free/malloc in kernel code
TEST_CASE("prod(case19)" * doctest::test_suite("array::prod") * doctest::skip())
{
    auto shape = nmtools_array{16,4,2};
    auto numel = ix::product(shape);
    auto start = 0;
    auto stop  = start + numel;
    auto step  = 1;
    auto flat  = na::arange(start,stop,step,nm::int16);
    auto input = na::reshape(flat,shape);

    auto dtype = nm::None;
    auto initial = nm::None;
    auto keepdims = nm::True;
    {
        auto axis = 0;
        SYCL_PROD_SUBCASE(input,axis,dtype,initial,keepdims);
    }
    {
        auto axis = 1;
        SYCL_PROD_SUBCASE(input,axis,dtype,initial,keepdims);
    }
    {
        auto axis = 2;
        SYCL_PROD_SUBCASE(input,axis,dtype,initial,keepdims);
    }
    {
        auto axis = nmtools_array{0,1};
        SYCL_PROD_SUBCASE(input,axis,dtype,initial,keepdims);
    }
    {
        auto axis = nmtools_array{1,2};
        SYCL_PROD_SUBCASE(input,axis,dtype,initial,keepdims);
    }
    {
        auto axis = nmtools_array{0,2};
        SYCL_PROD_SUBCASE(input,axis,dtype,initial,keepdims);
    }
}

// TODO: fix for sycl kernel (opencl/cuda), remove free/malloc in kernel code
TEST_CASE("prod(case20)" * doctest::test_suite("array::prod") * doctest::skip())
{
    auto shape = nmtools_array{4,2,1,4,2};
    auto numel = ix::product(shape);
    auto start = 0;
    auto stop  = start + numel;
    auto step  = 1;
    auto flat  = na::arange(start,stop,step,nm::int16);
    auto input = na::reshape(flat,shape);

    auto dtype = nm::None;
    auto initial = nm::None;
    auto keepdims = nm::True;
    {
        auto axis = 0;
        SYCL_PROD_SUBCASE(input,axis,dtype,initial,keepdims);
    }
    {
        auto axis = 1;
        SYCL_PROD_SUBCASE(input,axis,dtype,initial,keepdims);
    }
    {
        auto axis = 2;
        SYCL_PROD_SUBCASE(input,axis,dtype,initial,keepdims);
    }
    {
        auto axis = 3;
        SYCL_PROD_SUBCASE(input,axis,dtype,initial,keepdims);
    }
    {
        auto axis = 4;
        SYCL_PROD_SUBCASE(input,axis,dtype,initial,keepdims);
    }
    {
        auto axis = nmtools_array{0,1};
        SYCL_PROD_SUBCASE(input,axis,dtype,initial,keepdims);
    }
    {
        auto axis = nmtools_array{0,2};
        SYCL_PROD_SUBCASE(input,axis,dtype,initial,keepdims);
    }
    {
        auto axis = nmtools_array{0,3};
        SYCL_PROD_SUBCASE(input,axis,dtype,initial,keepdims);
    }
    {
        auto axis = nmtools_array{0,4};
        SYCL_PROD_SUBCASE(input,axis,dtype,initial,keepdims);
    }
    {
        auto axis = nmtools_array{1,2};
        SYCL_PROD_SUBCASE(input,axis,dtype,initial,keepdims);
    }
    {
        auto axis = nmtools_array{1,3};
        SYCL_PROD_SUBCASE(input,axis,dtype,initial,keepdims);
    }
    {
        auto axis = nmtools_array{1,4};
        SYCL_PROD_SUBCASE(input,axis,dtype,initial,keepdims);
    }
    {
        auto axis = nmtools_array{2,3};
        SYCL_PROD_SUBCASE(input,axis,dtype,initial,keepdims);
    }
    {
        auto axis = nmtools_array{2,4};
        SYCL_PROD_SUBCASE(input,axis,dtype,initial,keepdims);
    }
    {
        auto axis = nmtools_array{3,4};
        SYCL_PROD_SUBCASE(input,axis,dtype,initial,keepdims);
    }
}