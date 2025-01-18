#include "nmtools/array/zeros.hpp"
#include "nmtools/testing/data/array/zeros.hpp"
#include "nmtools/evaluator/sycl.hpp"
#include "nmtools/testing/doctest.hpp"

namespace nm = nmtools;
namespace na = nm::array;

#define SYCL_ZEROS_SUBCASE(...) \
{ \
    auto expect = na::zeros(__VA_ARGS__); \
    auto result = na::zeros(__VA_ARGS__, na::sycl::default_context()); \
    NMTOOLS_ASSERT_EQUAL( nm::shape(result), nm::shape(expect) ); \
    NMTOOLS_ASSERT_CLOSE( expect, expect ); \
}

#define ZEROS_SUBCASE(case_name, ...) \
SUBCASE(#case_name) \
{ \
    NMTOOLS_TESTING_USE_CASE(array, zeros, case_name); \
    using namespace args; \
    SYCL_ZEROS_SUBCASE(__VA_ARGS__); \
}

TEST_CASE("zeros(case1)" * doctest::test_suite("array::zeros"))
{
    auto shape = nmtools_array{128};
    auto dtype = nm::float32;
    SYCL_ZEROS_SUBCASE(shape,dtype);
}

TEST_CASE("zeros(case13)" * doctest::test_suite("array::zeros"))
{
    auto shape = nmtools_array{128};
    auto dtype = nm::int8;
    SYCL_ZEROS_SUBCASE(shape,dtype);
}

TEST_CASE("zeros(case14)" * doctest::test_suite("array::zeros"))
{
    auto shape = nmtools_array{1,128};
    auto dtype = nm::int8;
    SYCL_ZEROS_SUBCASE(shape,dtype);
}

TEST_CASE("zeros(case15)" * doctest::test_suite("array::zeros"))
{
    auto shape = nmtools_array{64,2};
    auto dtype = nm::int8;
    SYCL_ZEROS_SUBCASE(shape,dtype);
}

TEST_CASE("zeros(case16)" * doctest::test_suite("array::zeros"))
{
    auto shape = nmtools_array{16,4,2};
    auto dtype = nm::int8;
    SYCL_ZEROS_SUBCASE(shape,dtype);
}

TEST_CASE("zeros(case17)" * doctest::test_suite("array::zeros"))
{
    auto shape = nmtools_array{8,2,4,2};
    auto dtype = nm::int8;
    SYCL_ZEROS_SUBCASE(shape,dtype);
}

TEST_CASE("zeros(case18)" * doctest::test_suite("array::zeros"))
{
    auto shape = nmtools_array{2,4,1,2,4,2};
    auto dtype = nm::int8;
    SYCL_ZEROS_SUBCASE(shape,dtype);
}

TEST_CASE("zeros(case2)" * doctest::test_suite("array::zeros"))
{
    auto shape = nmtools_array{1,128};
    auto dtype = nm::float32;
    SYCL_ZEROS_SUBCASE(shape,dtype);
}

TEST_CASE("zeros(case3)" * doctest::test_suite("array::zeros"))
{
    auto shape = nmtools_array{64,2};
    auto dtype = nm::float32;
    SYCL_ZEROS_SUBCASE(shape,dtype);
}

TEST_CASE("zeros(case4)" * doctest::test_suite("array::zeros"))
{
    auto shape = nmtools_array{16,4,2};
    auto dtype = nm::float32;
    SYCL_ZEROS_SUBCASE(shape,dtype);
}

TEST_CASE("zeros(case5)" * doctest::test_suite("array::zeros"))
{
    auto shape = nmtools_array{8,2,4,2};
    auto dtype = nm::float32;
    SYCL_ZEROS_SUBCASE(shape,dtype);
}

TEST_CASE("zeros(case6)" * doctest::test_suite("array::zeros"))
{
    auto shape = nmtools_array{2,4,1,2,4,2};
    auto dtype = nm::float32;
    SYCL_ZEROS_SUBCASE(shape,dtype);
}

TEST_CASE("zeros(case7)" * doctest::test_suite("array::zeros"))
{
    auto shape = nmtools_array{128};
    auto dtype = nm::float64;
    SYCL_ZEROS_SUBCASE(shape,dtype);
}

TEST_CASE("zeros(case8)" * doctest::test_suite("array::zeros"))
{
    auto shape = nmtools_array{1,128};
    auto dtype = nm::float64;
    SYCL_ZEROS_SUBCASE(shape,dtype);
}

TEST_CASE("zeros(case9)" * doctest::test_suite("array::zeros"))
{
    auto shape = nmtools_array{64,2};
    auto dtype = nm::float64;
    SYCL_ZEROS_SUBCASE(shape,dtype);
}

TEST_CASE("zeros(case10)" * doctest::test_suite("array::zeros"))
{
    auto shape = nmtools_array{16,4,2};
    auto dtype = nm::float64;
    SYCL_ZEROS_SUBCASE(shape,dtype);
}

TEST_CASE("zeros(case11)" * doctest::test_suite("array::zeros"))
{
    auto shape = nmtools_array{8,2,4,2};
    auto dtype = nm::float64;
    SYCL_ZEROS_SUBCASE(shape,dtype);
}

TEST_CASE("zeros(case12)" * doctest::test_suite("array::zeros"))
{
    auto shape = nmtools_array{2,4,1,2,4,2};
    auto dtype = nm::float64;
    SYCL_ZEROS_SUBCASE(shape,dtype);
}

TEST_CASE("zeros(case13)" * doctest::test_suite("array::zeros"))
{
    auto shape = nmtools_array{128};
    auto dtype = nm::int8;
    SYCL_ZEROS_SUBCASE(shape,dtype);
}

TEST_CASE("zeros(case14)" * doctest::test_suite("array::zeros"))
{
    auto shape = nmtools_array{1,128};
    auto dtype = nm::int8;
    SYCL_ZEROS_SUBCASE(shape,dtype);
}

TEST_CASE("zeros(case15)" * doctest::test_suite("array::zeros"))
{
    auto shape = nmtools_array{64,2};
    auto dtype = nm::int8;
    SYCL_ZEROS_SUBCASE(shape,dtype);
}

TEST_CASE("zeros(case16)" * doctest::test_suite("array::zeros"))
{
    auto shape = nmtools_array{16,4,2};
    auto dtype = nm::int8;
    SYCL_ZEROS_SUBCASE(shape,dtype);
}

TEST_CASE("zeros(case17)" * doctest::test_suite("array::zeros"))
{
    auto shape = nmtools_array{8,2,4,2};
    auto dtype = nm::int8;
    SYCL_ZEROS_SUBCASE(shape,dtype);
}

TEST_CASE("zeros(case18)" * doctest::test_suite("array::zeros"))
{
    auto shape = nmtools_array{2,4,1,2,4,2};
    auto dtype = nm::int8;
    SYCL_ZEROS_SUBCASE(shape,dtype);
}

TEST_CASE("zeros(case19)" * doctest::test_suite("array::zeros"))
{
    auto shape = nmtools_array{128};
    auto dtype = nm::int32;
    SYCL_ZEROS_SUBCASE(shape,dtype);
}

TEST_CASE("zeros(case20)" * doctest::test_suite("array::zeros"))
{
    auto shape = nmtools_array{1,128};
    auto dtype = nm::int32;
    SYCL_ZEROS_SUBCASE(shape,dtype);
}

TEST_CASE("zeros(case21)" * doctest::test_suite("array::zeros"))
{
    auto shape = nmtools_array{64,2};
    auto dtype = nm::int32;
    SYCL_ZEROS_SUBCASE(shape,dtype);
}

TEST_CASE("zeros(case22)" * doctest::test_suite("array::zeros"))
{
    auto shape = nmtools_array{16,4,2};
    auto dtype = nm::int32;
    SYCL_ZEROS_SUBCASE(shape,dtype);
}

TEST_CASE("zeros(case23)" * doctest::test_suite("array::zeros"))
{
    auto shape = nmtools_array{8,2,4,2};
    auto dtype = nm::int32;
    SYCL_ZEROS_SUBCASE(shape,dtype);
}

TEST_CASE("zeros(case24)" * doctest::test_suite("array::zeros"))
{
    auto shape = nmtools_array{2,4,1,2,4,2};
    auto dtype = nm::int32;
    SYCL_ZEROS_SUBCASE(shape,dtype);
}

TEST_CASE("zeros(case25)" * doctest::test_suite("array::zeros"))
{
    auto shape = nmtools_array{128};
    auto dtype = nm::int16;
    SYCL_ZEROS_SUBCASE(shape,dtype);
}

TEST_CASE("zeros(case26)" * doctest::test_suite("array::zeros"))
{
    auto shape = nmtools_array{1,128};
    auto dtype = nm::int16;
    SYCL_ZEROS_SUBCASE(shape,dtype);
}

TEST_CASE("zeros(case27)" * doctest::test_suite("array::zeros"))
{
    auto shape = nmtools_array{64,2};
    auto dtype = nm::int16;
    SYCL_ZEROS_SUBCASE(shape,dtype);
}

TEST_CASE("zeros(case28)" * doctest::test_suite("array::zeros"))
{
    auto shape = nmtools_array{16,4,2};
    auto dtype = nm::int16;
    SYCL_ZEROS_SUBCASE(shape,dtype);
}

TEST_CASE("zeros(case29)" * doctest::test_suite("array::zeros"))
{
    auto shape = nmtools_array{8,2,4,2};
    auto dtype = nm::int16;
    SYCL_ZEROS_SUBCASE(shape,dtype);
}

TEST_CASE("zeros(case30)" * doctest::test_suite("array::zeros"))
{
    auto shape = nmtools_array{2,4,1,2,4,2};
    auto dtype = nm::int16;
    SYCL_ZEROS_SUBCASE(shape,dtype);
}