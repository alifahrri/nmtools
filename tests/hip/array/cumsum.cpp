#include "nmtools/array/cumsum.hpp"
#include "nmtools/array/arange.hpp"
#include "nmtools/array/reshape.hpp"
#include "nmtools/evaluator/hip.hpp"
#include "nmtools/testing/doctest.hpp"

namespace nm = nmtools;
namespace na = nm::array;
namespace ix = nm::index;

#define HIP_CUMSUM_SUBCASE(...) \
{ \
    auto expect = na::cumsum(__VA_ARGS__); \
    auto result = na::cumsum(__VA_ARGS__, na::hip::default_context()); \
    NMTOOLS_ASSERT_EQUAL( nm::shape(result), nm::shape(expect) ); \
    NMTOOLS_ASSERT_CLOSE( expect, expect ); \
}

#define CUMSUM_SUBCASE(case_name, ...) \
SUBCASE(#case_name) \
{ \
    NMTOOLS_TESTING_USE_CASE(array, cumsum, case_name); \
    using namespace args; \
    HIP_CUMSUM_SUBCASE(__VA_ARGS__); \
}

TEST_CASE("cumsum(case1)" * doctest::test_suite("array::cumsum"))
{
    auto shape = nmtools_array{128};
    auto numel = ix::product(shape);
    auto start = 0;
    auto stop  = start + numel;
    auto step  = 1;
    auto flat  = na::arange(start,stop,step);
    auto input = na::reshape(flat,shape);

    auto dtype = nm::None;
    {
        auto axis = 0;
        HIP_CUMSUM_SUBCASE(input,axis,dtype);
    }
}

TEST_CASE("cumsum(case2)" * doctest::test_suite("array::cumsum"))
{
    auto shape = nmtools_array{64,2};
    auto numel = ix::product(shape);
    auto start = 0;
    auto stop  = start + numel;
    auto step  = 1;
    auto flat  = na::arange(start,stop,step);
    auto input = na::reshape(flat,shape);

    auto dtype = nm::None;
    {
        auto axis = 0;
        HIP_CUMSUM_SUBCASE(input,axis,dtype);
    }
    {
        auto axis = 1;
        HIP_CUMSUM_SUBCASE(input,axis,dtype);
    }
}

TEST_CASE("cumsum(case3)" * doctest::test_suite("array::cumsum"))
{
    auto shape = nmtools_array{16,4,2};
    auto numel = ix::product(shape);
    auto start = 0;
    auto stop  = start + numel;
    auto step  = 1;
    auto flat  = na::arange(start,stop,step);
    auto input = na::reshape(flat,shape);

    auto dtype = nm::None;
    {
        auto axis = 0;
        HIP_CUMSUM_SUBCASE(input,axis,dtype);
    }
    {
        auto axis = 1;
        HIP_CUMSUM_SUBCASE(input,axis,dtype);
    }
    {
        auto axis = 2;
        HIP_CUMSUM_SUBCASE(input,axis,dtype);
    }
}

TEST_CASE("cumsum(case4)" * doctest::test_suite("array::cumsum"))
{
    auto shape = nmtools_array{4,2,1,4,2};
    auto numel = ix::product(shape);
    auto start = 0;
    auto stop  = start + numel;
    auto step  = 1;
    auto flat  = na::arange(start,stop,step);
    auto input = na::reshape(flat,shape);

    auto dtype = nm::None;
    {
        auto axis = 0;
        HIP_CUMSUM_SUBCASE(input,axis,dtype);
    }
    {
        auto axis = 1;
        HIP_CUMSUM_SUBCASE(input,axis,dtype);
    }
    {
        auto axis = 2;
        HIP_CUMSUM_SUBCASE(input,axis,dtype);
    }
    {
        auto axis = 3;
        HIP_CUMSUM_SUBCASE(input,axis,dtype);
    }
    {
        auto axis = 4;
        HIP_CUMSUM_SUBCASE(input,axis,dtype);
    }
}

TEST_CASE("cumsum(case5)" * doctest::test_suite("array::cumsum"))
{
    auto shape = nmtools_array{128};
    auto numel = ix::product(shape);
    auto start = 0;
    auto stop  = start + numel;
    auto step  = 1;
    auto flat  = na::arange(start,stop,step,nm::float64);
    auto input = na::reshape(flat,shape);

    auto dtype    = nm::None;
    {
        auto axis = 0;
        HIP_CUMSUM_SUBCASE(input,axis,dtype);
    }
}

TEST_CASE("cumsum(case6)" * doctest::test_suite("array::cumsum"))
{
    auto shape = nmtools_array{64,2};
    auto numel = ix::product(shape);
    auto start = 0;
    auto stop  = start + numel;
    auto step  = 1;
    auto flat  = na::arange(start,stop,step,nm::float64);
    auto input = na::reshape(flat,shape);

    auto dtype = nm::None;
    {
        auto axis = 0;
        HIP_CUMSUM_SUBCASE(input,axis,dtype);
    }
    {
        auto axis = 1;
        HIP_CUMSUM_SUBCASE(input,axis,dtype);
    }
}

TEST_CASE("cumsum(case7)" * doctest::test_suite("array::cumsum"))
{
    auto shape = nmtools_array{16,4,2};
    auto numel = ix::product(shape);
    auto start = 0;
    auto stop  = start + numel;
    auto step  = 1;
    auto flat  = na::arange(start,stop,step,nm::float64);
    auto input = na::reshape(flat,shape);

    auto dtype = nm::None;
    {
        auto axis = 0;
        HIP_CUMSUM_SUBCASE(input,axis,dtype);
    }
    {
        auto axis = 1;
        HIP_CUMSUM_SUBCASE(input,axis,dtype);
    }
    {
        auto axis = 2;
        HIP_CUMSUM_SUBCASE(input,axis,dtype);
    }
}

TEST_CASE("cumsum(case8)" * doctest::test_suite("array::cumsum"))
{
    auto shape = nmtools_array{4,2,1,4,2};
    auto numel = ix::product(shape);
    auto start = 0;
    auto stop  = start + numel;
    auto step  = 1;
    auto flat  = na::arange(start,stop,step,nm::float64);
    auto input = na::reshape(flat,shape);

    auto dtype = nm::None;
    {
        auto axis = 0;
        HIP_CUMSUM_SUBCASE(input,axis,dtype);
    }
    {
        auto axis = 1;
        HIP_CUMSUM_SUBCASE(input,axis,dtype);
    }
    {
        auto axis = 2;
        HIP_CUMSUM_SUBCASE(input,axis,dtype);
    }
    {
        auto axis = 3;
        HIP_CUMSUM_SUBCASE(input,axis,dtype);
    }
    {
        auto axis = 4;
        HIP_CUMSUM_SUBCASE(input,axis,dtype);
    }
}

TEST_CASE("cumsum(case9)" * doctest::test_suite("array::cumsum"))
{
    auto shape = nmtools_array{128};
    auto numel = ix::product(shape);
    auto start = 0;
    auto stop  = start + numel;
    auto step  = 1;
    auto flat  = na::arange(start,stop,step,nm::int32);
    auto input = na::reshape(flat,shape);

    auto dtype    = nm::None;
    {
        auto axis = 0;
        HIP_CUMSUM_SUBCASE(input,axis,dtype);
    }
}

TEST_CASE("cumsum(case10)" * doctest::test_suite("array::cumsum"))
{
    auto shape = nmtools_array{64,2};
    auto numel = ix::product(shape);
    auto start = 0;
    auto stop  = start + numel;
    auto step  = 1;
    auto flat  = na::arange(start,stop,step,nm::int32);
    auto input = na::reshape(flat,shape);

    auto dtype = nm::None;
    {
        auto axis = 0;
        HIP_CUMSUM_SUBCASE(input,axis,dtype);
    }
    {
        auto axis = 1;
        HIP_CUMSUM_SUBCASE(input,axis,dtype);
    }
}

TEST_CASE("cumsum(case11)" * doctest::test_suite("array::cumsum"))
{
    auto shape = nmtools_array{16,4,2};
    auto numel = ix::product(shape);
    auto start = 0;
    auto stop  = start + numel;
    auto step  = 1;
    auto flat  = na::arange(start,stop,step,nm::int32);
    auto input = na::reshape(flat,shape);

    auto dtype = nm::None;
    {
        auto axis = 0;
        HIP_CUMSUM_SUBCASE(input,axis,dtype);
    }
    {
        auto axis = 1;
        HIP_CUMSUM_SUBCASE(input,axis,dtype);
    }
    {
        auto axis = 2;
        HIP_CUMSUM_SUBCASE(input,axis,dtype);
    }
}

TEST_CASE("cumsum(case12)" * doctest::test_suite("array::cumsum"))
{
    auto shape = nmtools_array{4,2,1,4,2};
    auto numel = ix::product(shape);
    auto start = 0;
    auto stop  = start + numel;
    auto step  = 1;
    auto flat  = na::arange(start,stop,step,nm::int32);
    auto input = na::reshape(flat,shape);

    auto dtype = nm::None;
    {
        auto axis = 0;
        HIP_CUMSUM_SUBCASE(input,axis,dtype);
    }
    {
        auto axis = 1;
        HIP_CUMSUM_SUBCASE(input,axis,dtype);
    }
    {
        auto axis = 2;
        HIP_CUMSUM_SUBCASE(input,axis,dtype);
    }
    {
        auto axis = 3;
        HIP_CUMSUM_SUBCASE(input,axis,dtype);
    }
    {
        auto axis = 4;
        HIP_CUMSUM_SUBCASE(input,axis,dtype);
    }
}

TEST_CASE("cumsum(case13)" * doctest::test_suite("array::cumsum"))
{
    auto shape = nmtools_array{128};
    auto numel = ix::product(shape);
    auto start = 0;
    auto stop  = start + numel;
    auto step  = 1;
    auto flat  = na::arange(start,stop,step,nm::int64);
    auto input = na::reshape(flat,shape);

    auto dtype    = nm::None;
    {
        auto axis = 0;
        HIP_CUMSUM_SUBCASE(input,axis,dtype);
    }
}

TEST_CASE("cumsum(case14)" * doctest::test_suite("array::cumsum"))
{
    auto shape = nmtools_array{64,2};
    auto numel = ix::product(shape);
    auto start = 0;
    auto stop  = start + numel;
    auto step  = 1;
    auto flat  = na::arange(start,stop,step,nm::int64);
    auto input = na::reshape(flat,shape);

    auto dtype = nm::None;
    {
        auto axis = 0;
        HIP_CUMSUM_SUBCASE(input,axis,dtype);
    }
    {
        auto axis = 1;
        HIP_CUMSUM_SUBCASE(input,axis,dtype);
    }
}

TEST_CASE("cumsum(case15)" * doctest::test_suite("array::cumsum"))
{
    auto shape = nmtools_array{16,4,2};
    auto numel = ix::product(shape);
    auto start = 0;
    auto stop  = start + numel;
    auto step  = 1;
    auto flat  = na::arange(start,stop,step,nm::int64);
    auto input = na::reshape(flat,shape);

    auto dtype = nm::None;
    {
        auto axis = 0;
        HIP_CUMSUM_SUBCASE(input,axis,dtype);
    }
    {
        auto axis = 1;
        HIP_CUMSUM_SUBCASE(input,axis,dtype);
    }
    {
        auto axis = 2;
        HIP_CUMSUM_SUBCASE(input,axis,dtype);
    }
}

TEST_CASE("cumsum(case16)" * doctest::test_suite("array::cumsum"))
{
    auto shape = nmtools_array{4,2,1,4,2};
    auto numel = ix::product(shape);
    auto start = 0;
    auto stop  = start + numel;
    auto step  = 1;
    auto flat  = na::arange(start,stop,step,nm::int64);
    auto input = na::reshape(flat,shape);

    auto dtype = nm::None;
    {
        auto axis = 0;
        HIP_CUMSUM_SUBCASE(input,axis,dtype);
    }
    {
        auto axis = 1;
        HIP_CUMSUM_SUBCASE(input,axis,dtype);
    }
    {
        auto axis = 2;
        HIP_CUMSUM_SUBCASE(input,axis,dtype);
    }
    {
        auto axis = 3;
        HIP_CUMSUM_SUBCASE(input,axis,dtype);
    }
    {
        auto axis = 4;
        HIP_CUMSUM_SUBCASE(input,axis,dtype);
    }
}

TEST_CASE("cumsum(case17)" * doctest::test_suite("array::cumsum"))
{
    auto shape = nmtools_array{128};
    auto numel = ix::product(shape);
    auto start = 0;
    auto stop  = start + numel;
    auto step  = 1;
    auto flat  = na::arange(start,stop,step,nm::int16);
    auto input = na::reshape(flat,shape);

    auto dtype    = nm::None;
    {
        auto axis = 0;
        HIP_CUMSUM_SUBCASE(input,axis,dtype);
    }
}

TEST_CASE("cumsum(case18)" * doctest::test_suite("array::cumsum"))
{
    auto shape = nmtools_array{64,2};
    auto numel = ix::product(shape);
    auto start = 0;
    auto stop  = start + numel;
    auto step  = 1;
    auto flat  = na::arange(start,stop,step,nm::int16);
    auto input = na::reshape(flat,shape);

    auto dtype = nm::None;
    {
        auto axis = 0;
        HIP_CUMSUM_SUBCASE(input,axis,dtype);
    }
    {
        auto axis = 1;
        HIP_CUMSUM_SUBCASE(input,axis,dtype);
    }
}

TEST_CASE("cumsum(case19)" * doctest::test_suite("array::cumsum"))
{
    auto shape = nmtools_array{16,4,2};
    auto numel = ix::product(shape);
    auto start = 0;
    auto stop  = start + numel;
    auto step  = 1;
    auto flat  = na::arange(start,stop,step,nm::int16);
    auto input = na::reshape(flat,shape);

    auto dtype = nm::None;
    {
        auto axis = 0;
        HIP_CUMSUM_SUBCASE(input,axis,dtype);
    }
    {
        auto axis = 1;
        HIP_CUMSUM_SUBCASE(input,axis,dtype);
    }
    {
        auto axis = 2;
        HIP_CUMSUM_SUBCASE(input,axis,dtype);
    }
}

TEST_CASE("cumsum(case20)" * doctest::test_suite("array::cumsum"))
{
    auto shape = nmtools_array{4,2,1,4,2};
    auto numel = ix::product(shape);
    auto start = 0;
    auto stop  = start + numel;
    auto step  = 1;
    auto flat  = na::arange(start,stop,step,nm::int16);
    auto input = na::reshape(flat,shape);

    auto dtype = nm::None;
    {
        auto axis = 0;
        HIP_CUMSUM_SUBCASE(input,axis,dtype);
    }
    {
        auto axis = 1;
        HIP_CUMSUM_SUBCASE(input,axis,dtype);
    }
    {
        auto axis = 2;
        HIP_CUMSUM_SUBCASE(input,axis,dtype);
    }
    {
        auto axis = 3;
        HIP_CUMSUM_SUBCASE(input,axis,dtype);
    }
    {
        auto axis = 4;
        HIP_CUMSUM_SUBCASE(input,axis,dtype);
    }
}