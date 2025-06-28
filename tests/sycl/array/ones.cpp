#include "nmtools/array/ones.hpp"
#include "nmtools/testing/data/array/ones.hpp"
#include "nmtools/evaluator/sycl.hpp"
#include "nmtools/testing/doctest.hpp"

namespace nm = nmtools;
namespace na = nmtools;

#define SYCL_ONES_SUBCASE(...) \
{ \
    auto expect = na::ones(__VA_ARGS__); \
    auto result = na::ones(__VA_ARGS__, na::sycl::default_context()); \
    NMTOOLS_ASSERT_EQUAL( nm::shape(result), nm::shape(expect) ); \
    NMTOOLS_ASSERT_CLOSE( expect, expect ); \
}

#define ONES_SUBCASE(case_name, ...) \
SUBCASE(#case_name) \
{ \
    NMTOOLS_TESTING_USE_CASE(array, ones, case_name); \
    using namespace args; \
    SYCL_ONES_SUBCASE(__VA_ARGS__); \
}

TEST_CASE("ones(case1)" * doctest::test_suite("array::ones"))
{
    auto shape = nmtools_array{128};
    auto dtype = nm::float32;
    SYCL_ONES_SUBCASE(shape,dtype);
}

TEST_CASE("ones(case13)" * doctest::test_suite("array::ones"))
{
    auto shape = nmtools_array{128};
    auto dtype = nm::int8;
    SYCL_ONES_SUBCASE(shape,dtype);
}

TEST_CASE("ones(case14)" * doctest::test_suite("array::ones"))
{
    auto shape = nmtools_array{1,128};
    auto dtype = nm::int8;
    SYCL_ONES_SUBCASE(shape,dtype);
}

TEST_CASE("ones(case15)" * doctest::test_suite("array::ones"))
{
    auto shape = nmtools_array{64,2};
    auto dtype = nm::int8;
    SYCL_ONES_SUBCASE(shape,dtype);
}

TEST_CASE("ones(case16)" * doctest::test_suite("array::ones"))
{
    auto shape = nmtools_array{16,4,2};
    auto dtype = nm::int8;
    SYCL_ONES_SUBCASE(shape,dtype);
}

TEST_CASE("ones(case17)" * doctest::test_suite("array::ones"))
{
    auto shape = nmtools_array{8,2,4,2};
    auto dtype = nm::int8;
    SYCL_ONES_SUBCASE(shape,dtype);
}

TEST_CASE("ones(case18)" * doctest::test_suite("array::ones"))
{
    auto shape = nmtools_array{2,4,1,2,4,2};
    auto dtype = nm::int8;
    SYCL_ONES_SUBCASE(shape,dtype);
}

TEST_CASE("ones(case2)" * doctest::test_suite("array::ones"))
{
    auto shape = nmtools_array{1,128};
    auto dtype = nm::float32;
    SYCL_ONES_SUBCASE(shape,dtype);
}

TEST_CASE("ones(case3)" * doctest::test_suite("array::ones"))
{
    auto shape = nmtools_array{64,2};
    auto dtype = nm::float32;
    SYCL_ONES_SUBCASE(shape,dtype);
}

TEST_CASE("ones(case4)" * doctest::test_suite("array::ones"))
{
    auto shape = nmtools_array{16,4,2};
    auto dtype = nm::float32;
    SYCL_ONES_SUBCASE(shape,dtype);
}

TEST_CASE("ones(case5)" * doctest::test_suite("array::ones"))
{
    auto shape = nmtools_array{8,2,4,2};
    auto dtype = nm::float32;
    SYCL_ONES_SUBCASE(shape,dtype);
}

TEST_CASE("ones(case6)" * doctest::test_suite("array::ones"))
{
    auto shape = nmtools_array{2,4,1,2,4,2};
    auto dtype = nm::float32;
    SYCL_ONES_SUBCASE(shape,dtype);
}

TEST_CASE("ones(case7)" * doctest::test_suite("array::ones"))
{
    auto shape = nmtools_array{128};
    auto dtype = nm::float64;
    SYCL_ONES_SUBCASE(shape,dtype);
}

TEST_CASE("ones(case8)" * doctest::test_suite("array::ones"))
{
    auto shape = nmtools_array{1,128};
    auto dtype = nm::float64;
    SYCL_ONES_SUBCASE(shape,dtype);
}

TEST_CASE("ones(case9)" * doctest::test_suite("array::ones"))
{
    auto shape = nmtools_array{64,2};
    auto dtype = nm::float64;
    SYCL_ONES_SUBCASE(shape,dtype);
}

TEST_CASE("ones(case10)" * doctest::test_suite("array::ones"))
{
    auto shape = nmtools_array{16,4,2};
    auto dtype = nm::float64;
    SYCL_ONES_SUBCASE(shape,dtype);
}

TEST_CASE("ones(case11)" * doctest::test_suite("array::ones"))
{
    auto shape = nmtools_array{8,2,4,2};
    auto dtype = nm::float64;
    SYCL_ONES_SUBCASE(shape,dtype);
}

TEST_CASE("ones(case12)" * doctest::test_suite("array::ones"))
{
    auto shape = nmtools_array{2,4,1,2,4,2};
    auto dtype = nm::float64;
    SYCL_ONES_SUBCASE(shape,dtype);
}

TEST_CASE("ones(case13)" * doctest::test_suite("array::ones"))
{
    auto shape = nmtools_array{128};
    auto dtype = nm::int8;
    SYCL_ONES_SUBCASE(shape,dtype);
}

TEST_CASE("ones(case14)" * doctest::test_suite("array::ones"))
{
    auto shape = nmtools_array{1,128};
    auto dtype = nm::int8;
    SYCL_ONES_SUBCASE(shape,dtype);
}

TEST_CASE("ones(case15)" * doctest::test_suite("array::ones"))
{
    auto shape = nmtools_array{64,2};
    auto dtype = nm::int8;
    SYCL_ONES_SUBCASE(shape,dtype);
}

TEST_CASE("ones(case16)" * doctest::test_suite("array::ones"))
{
    auto shape = nmtools_array{16,4,2};
    auto dtype = nm::int8;
    SYCL_ONES_SUBCASE(shape,dtype);
}

TEST_CASE("ones(case17)" * doctest::test_suite("array::ones"))
{
    auto shape = nmtools_array{8,2,4,2};
    auto dtype = nm::int8;
    SYCL_ONES_SUBCASE(shape,dtype);
}

TEST_CASE("ones(case18)" * doctest::test_suite("array::ones"))
{
    auto shape = nmtools_array{2,4,1,2,4,2};
    auto dtype = nm::int8;
    SYCL_ONES_SUBCASE(shape,dtype);
}

TEST_CASE("ones(case19)" * doctest::test_suite("array::ones"))
{
    auto shape = nmtools_array{128};
    auto dtype = nm::int32;
    SYCL_ONES_SUBCASE(shape,dtype);
}

TEST_CASE("ones(case20)" * doctest::test_suite("array::ones"))
{
    auto shape = nmtools_array{1,128};
    auto dtype = nm::int32;
    SYCL_ONES_SUBCASE(shape,dtype);
}

TEST_CASE("ones(case21)" * doctest::test_suite("array::ones"))
{
    auto shape = nmtools_array{64,2};
    auto dtype = nm::int32;
    SYCL_ONES_SUBCASE(shape,dtype);
}

TEST_CASE("ones(case22)" * doctest::test_suite("array::ones"))
{
    auto shape = nmtools_array{16,4,2};
    auto dtype = nm::int32;
    SYCL_ONES_SUBCASE(shape,dtype);
}

TEST_CASE("ones(case23)" * doctest::test_suite("array::ones"))
{
    auto shape = nmtools_array{8,2,4,2};
    auto dtype = nm::int32;
    SYCL_ONES_SUBCASE(shape,dtype);
}

TEST_CASE("ones(case24)" * doctest::test_suite("array::ones"))
{
    auto shape = nmtools_array{2,4,1,2,4,2};
    auto dtype = nm::int32;
    SYCL_ONES_SUBCASE(shape,dtype);
}

TEST_CASE("ones(case25)" * doctest::test_suite("array::ones"))
{
    auto shape = nmtools_array{128};
    auto dtype = nm::int16;
    SYCL_ONES_SUBCASE(shape,dtype);
}

TEST_CASE("ones(case26)" * doctest::test_suite("array::ones"))
{
    auto shape = nmtools_array{1,128};
    auto dtype = nm::int16;
    SYCL_ONES_SUBCASE(shape,dtype);
}

TEST_CASE("ones(case27)" * doctest::test_suite("array::ones"))
{
    auto shape = nmtools_array{64,2};
    auto dtype = nm::int16;
    SYCL_ONES_SUBCASE(shape,dtype);
}

TEST_CASE("ones(case28)" * doctest::test_suite("array::ones"))
{
    auto shape = nmtools_array{16,4,2};
    auto dtype = nm::int16;
    SYCL_ONES_SUBCASE(shape,dtype);
}

TEST_CASE("ones(case29)" * doctest::test_suite("array::ones"))
{
    auto shape = nmtools_array{8,2,4,2};
    auto dtype = nm::int16;
    SYCL_ONES_SUBCASE(shape,dtype);
}

TEST_CASE("ones(case30)" * doctest::test_suite("array::ones"))
{
    auto shape = nmtools_array{2,4,1,2,4,2};
    auto dtype = nm::int16;
    SYCL_ONES_SUBCASE(shape,dtype);
}