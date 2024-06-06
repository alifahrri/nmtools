#include "nmtools/array/array/arange.hpp"
#include "nmtools/testing/data/array/arange.hpp"
#include "nmtools/array/eval/hip.hpp"
#include "nmtools/testing/doctest.hpp"

namespace nm = nmtools;
namespace na = nm::array;

#define HIP_ARANGE_SUBCASE(...) \
{ \
    auto expect = na::arange(__VA_ARGS__); \
    auto result = na::arange(__VA_ARGS__, na::hip::default_context()); \
    NMTOOLS_ASSERT_EQUAL( nm::shape(result), nm::shape(expect) ); \
    NMTOOLS_ASSERT_CLOSE( expect, expect ); \
}

#define ARANGE_SUBCASE(case_name, ...) \
SUBCASE(#case_name) \
{ \
    NMTOOLS_TESTING_USE_CASE(array, arange, case_name); \
    using namespace args; \
    HIP_ARANGE_SUBCASE(__VA_ARGS__); \
}

TEST_CASE("arange(case1)" * doctest::test_suite("array::arange"))
{
    auto start = 0;
    auto stop  = 128;
    auto step  = 1;
    auto dtype = nm::float32;
    HIP_ARANGE_SUBCASE(start,stop,step,dtype);
}

TEST_CASE("arange(case2)" * doctest::test_suite("array::arange"))
{
    auto start = 0;
    auto stop  = 128;
    auto step  = 1;
    auto dtype = nm::float64;
    HIP_ARANGE_SUBCASE(start,stop,step,dtype);
}

TEST_CASE("arange(case3)" * doctest::test_suite("array::arange"))
{
    auto start = 0;
    auto stop  = 128;
    auto step  = 1;
    auto dtype = nm::int8;
    HIP_ARANGE_SUBCASE(start,stop,step,dtype);
}

TEST_CASE("arange(case4)" * doctest::test_suite("array::arange"))
{
    auto start = 0;
    auto stop  = 128;
    auto step  = 1;
    auto dtype = nm::int16;
    HIP_ARANGE_SUBCASE(start,stop,step,dtype);
}

TEST_CASE("arange(case5)" * doctest::test_suite("array::arange"))
{
    auto start = 0;
    auto stop  = 128;
    auto step  = 1;
    auto dtype = nm::int32;
    HIP_ARANGE_SUBCASE(start,stop,step,dtype);
}

TEST_CASE("arange(case6)" * doctest::test_suite("array::arange"))
{
    auto start = 0;
    auto stop  = 128;
    auto step  = 1;
    auto dtype = nm::int64;
    HIP_ARANGE_SUBCASE(start,stop,step,dtype);
}

TEST_CASE("arange(case7)" * doctest::test_suite("array::arange"))
{
    auto start = 0;
    auto stop  = 128;
    auto step  = 1;
    auto dtype = nm::uint8;
    HIP_ARANGE_SUBCASE(start,stop,step,dtype);
}

TEST_CASE("arange(case8)" * doctest::test_suite("array::arange"))
{
    auto start = 0;
    auto stop  = 128;
    auto step  = 1;
    auto dtype = nm::uint16;
    HIP_ARANGE_SUBCASE(start,stop,step,dtype);
}

TEST_CASE("arange(case9)" * doctest::test_suite("array::arange"))
{
    auto start = 0;
    auto stop  = 128;
    auto step  = 1;
    auto dtype = nm::uint32;
    HIP_ARANGE_SUBCASE(start,stop,step,dtype);
}

TEST_CASE("arange(case10)" * doctest::test_suite("array::arange"))
{
    auto start = 0;
    auto stop  = 128;
    auto step  = 1;
    auto dtype = nm::uint64;
    HIP_ARANGE_SUBCASE(start,stop,step,dtype);
}

TEST_CASE("arange(case3a)" * doctest::test_suite("array::arange"))
{
    ARANGE_SUBCASE(case3, start, stop, step, dtype );
}

TEST_CASE("arange(case4a)" * doctest::test_suite("array::arange"))
{
    ARANGE_SUBCASE(case4, start, stop, step, dtype );
}