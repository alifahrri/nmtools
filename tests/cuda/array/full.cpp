#include "nmtools/array/array/full.hpp"
#include "nmtools/testing/data/array/full.hpp"
#include "nmtools/array/evaluator/cuda.hpp"
#include "nmtools/testing/doctest.hpp"

namespace nm = nmtools;
namespace na = nm::array;

#define CUDA_FULL_SUBCASE(...) \
{ \
    auto expect = na::full(__VA_ARGS__); \
    auto result = na::full(__VA_ARGS__, na::cuda::default_context()); \
    NMTOOLS_ASSERT_EQUAL( nm::shape(result), nm::shape(expect) ); \
    NMTOOLS_ASSERT_CLOSE( expect, expect ); \
}

#define FULL_SUBCASE(case_name, ...) \
SUBCASE(#case_name) \
{ \
    NMTOOLS_TESTING_USE_CASE(array, full, case_name); \
    using namespace args; \
    CUDA_FULL_SUBCASE(__VA_ARGS__); \
}

TEST_CASE("full(case1)" * doctest::test_suite("array::full"))
{
    auto shape = nmtools_array{128};
    CUDA_FULL_SUBCASE(shape,3.f);
}

TEST_CASE("full(case2)" * doctest::test_suite("array::full"))
{
    auto shape = nmtools_array{1,128};
    CUDA_FULL_SUBCASE(shape,3.f);
}

TEST_CASE("full(case3)" * doctest::test_suite("array::full"))
{
    auto shape = nmtools_array{64,2};
    CUDA_FULL_SUBCASE(shape,3.f);
}

TEST_CASE("full(case4)" * doctest::test_suite("array::full"))
{
    auto shape = nmtools_array{16,4,2};
    CUDA_FULL_SUBCASE(shape,3.f);
}

TEST_CASE("full(case5)" * doctest::test_suite("array::full"))
{
    auto shape = nmtools_array{8,2,4,2};
    CUDA_FULL_SUBCASE(shape,3.f);
}

TEST_CASE("full(case6)" * doctest::test_suite("array::full"))
{
    auto shape = nmtools_array{2,4,1,2,4,2};
    CUDA_FULL_SUBCASE(shape,3.f);
}

TEST_CASE("full(case7)" * doctest::test_suite("array::full"))
{
    auto shape = nmtools_array{128};
    CUDA_FULL_SUBCASE(shape,3.);
}

TEST_CASE("full(case8)" * doctest::test_suite("array::full"))
{
    auto shape = nmtools_array{1,128};
    CUDA_FULL_SUBCASE(shape,3.);
}

TEST_CASE("full(case9)" * doctest::test_suite("array::full"))
{
    auto shape = nmtools_array{64,2};
    CUDA_FULL_SUBCASE(shape,3.);
}

TEST_CASE("full(case10)" * doctest::test_suite("array::full"))
{
    auto shape = nmtools_array{16,4,2};
    CUDA_FULL_SUBCASE(shape,3.);
}

TEST_CASE("full(case11)" * doctest::test_suite("array::full"))
{
    auto shape = nmtools_array{8,2,4,2};
    CUDA_FULL_SUBCASE(shape,3.);
}

TEST_CASE("full(case12)" * doctest::test_suite("array::full"))
{
    auto shape = nmtools_array{2,4,1,2,4,2};
    CUDA_FULL_SUBCASE(shape,3.);
}

TEST_CASE("full(case13)" * doctest::test_suite("array::full"))
{
    auto shape = nmtools_array{128};
    CUDA_FULL_SUBCASE(shape,3ul);
}

TEST_CASE("full(case14)" * doctest::test_suite("array::full"))
{
    auto shape = nmtools_array{1,128};
    CUDA_FULL_SUBCASE(shape,3ul);
}

TEST_CASE("full(case15)" * doctest::test_suite("array::full"))
{
    auto shape = nmtools_array{64,2};
    CUDA_FULL_SUBCASE(shape,3ul);
}

TEST_CASE("full(case16)" * doctest::test_suite("array::full"))
{
    auto shape = nmtools_array{16,4,2};
    CUDA_FULL_SUBCASE(shape,3ul);
}

TEST_CASE("full(case17)" * doctest::test_suite("array::full"))
{
    auto shape = nmtools_array{8,2,4,2};
    CUDA_FULL_SUBCASE(shape,3ul);
}

TEST_CASE("full(case18)" * doctest::test_suite("array::full"))
{
    auto shape = nmtools_array{2,4,1,2,4,2};
    CUDA_FULL_SUBCASE(shape,3ul);
}

TEST_CASE("full(case19)" * doctest::test_suite("array::full"))
{
    auto shape = nmtools_array{128};
    CUDA_FULL_SUBCASE(shape,3l);
}

TEST_CASE("full(case20)" * doctest::test_suite("array::full"))
{
    auto shape = nmtools_array{1,128};
    CUDA_FULL_SUBCASE(shape,3l);
}

TEST_CASE("full(case21)" * doctest::test_suite("array::full"))
{
    auto shape = nmtools_array{64,2};
    CUDA_FULL_SUBCASE(shape,3l);
}

TEST_CASE("full(case22)" * doctest::test_suite("array::full"))
{
    auto shape = nmtools_array{16,4,2};
    CUDA_FULL_SUBCASE(shape,3l);
}

TEST_CASE("full(case23)" * doctest::test_suite("array::full"))
{
    auto shape = nmtools_array{8,2,4,2};
    CUDA_FULL_SUBCASE(shape,3l);
}

TEST_CASE("full(case24)" * doctest::test_suite("array::full"))
{
    auto shape = nmtools_array{2,4,1,2,4,2};
    CUDA_FULL_SUBCASE(shape,3l);
}

TEST_CASE("full(case25)" * doctest::test_suite("array::full"))
{
    auto shape = nmtools_array{128};
    CUDA_FULL_SUBCASE(shape,(uint8_t)3);
}

TEST_CASE("full(case26)" * doctest::test_suite("array::full"))
{
    auto shape = nmtools_array{1,128};
    CUDA_FULL_SUBCASE(shape,(uint8_t)3);
}

TEST_CASE("full(case27)" * doctest::test_suite("array::full"))
{
    auto shape = nmtools_array{64,2};
    CUDA_FULL_SUBCASE(shape,(uint8_t)3);
}

TEST_CASE("full(case28)" * doctest::test_suite("array::full"))
{
    auto shape = nmtools_array{16,4,2};
    CUDA_FULL_SUBCASE(shape,(uint8_t)3);
}

TEST_CASE("full(case29)" * doctest::test_suite("array::full"))
{
    auto shape = nmtools_array{8,2,4,2};
    CUDA_FULL_SUBCASE(shape,(uint8_t)3);
}

TEST_CASE("full(case30)" * doctest::test_suite("array::full"))
{
    auto shape = nmtools_array{2,4,1,2,4,2};
    CUDA_FULL_SUBCASE(shape,(uint8_t)3);
}