#include "nmtools/array/inner.hpp"
#include "nmtools/evaluator/sycl.hpp"
#include "nmtools/array/random.hpp"
#include "nmtools/testing/data/array/inner.hpp"
#include "nmtools/testing/doctest.hpp"

namespace nm = nmtools;
namespace na = nmtools;
namespace fn = nmtools::functional;
namespace meta = nm::meta;
namespace view = nmtools::view;

using nmtools_array;

#define HIP_TEST(fn,...) \
{ \
    auto expect = na::fn(__VA_ARGS__); \
    auto result = na::fn(__VA_ARGS__,na::sycl::default_context()); \
    NMTOOLS_ASSERT_EQUAL( nm::shape(result), nm::shape(expect) ); \
    NMTOOLS_ASSERT_CLOSE( result, expect ); \
}

#define HIP_LINEAR_TEST(fun,...) \
{ \
    auto ctx = na::sycl::default_context(); \
    auto expect = na::fun(__VA_ARGS__); \
    auto view   = view::fun(__VA_ARGS__); \
    auto result = ctx->eval(view); \
    NMTOOLS_ASSERT_EQUAL( nm::shape(result), nm::shape(expect) ); \
    NMTOOLS_ASSERT_CLOSE( result, expect ); \
}

#define INNER_SUBCASE(case_name, ...) \
SUBCASE(#case_name) \
{ \
    NMTOOLS_TESTING_USE_CASE( array, inner, case_name ); \
    auto view = view::inner(__VA_ARGS__); \
    auto ctx = na::sycl::default_context(); \
    auto result = ctx->eval(view); \
    NMTOOLS_ASSERT_EQUAL( nmtools::shape(result), nmtools::shape(expect::result) ); \
    NMTOOLS_ASSERT_CLOSE( result, expect::result ); \
}

#if 1
TEST_CASE("inner(case1)" * doctest::test_suite("array::inner"))
{
    auto gen = na::random_engine();
    auto dtype = nm::float32;

    auto a = na::random(array{2,3,2},dtype,gen);
    auto b = na::random(array{1,3,2,2},dtype,gen);

    HIP_LINEAR_TEST(inner,a,b);
}
#endif

#if 0
TEST_CASE("inner(case1)" * doctest::test_suite("array::inner"))
{
    // INNER_SUBCASE( case1, a, b );
    // INNER_SUBCASE( case1, a_a, b_a );
    INNER_SUBCASE( case1, a_f, b_f );
    INNER_SUBCASE( case1, a_h, b_h );
    // TODO: fix compile
    // INNER_SUBCASE( case1, a_d, b_d );
}
#endif

#if 1
TEST_CASE("inner(case1b)" * doctest::test_suite("array::inner"))
{
    // INNER_SUBCASE( case1b, a, b );
    // INNER_SUBCASE( case1b, a_a, b_a );
    INNER_SUBCASE( case1b, a_f, b_f );
    INNER_SUBCASE( case1b, a_h, b_h );
    INNER_SUBCASE( case1b, a_d, b_d );
}

TEST_CASE("inner(case1c)" * doctest::test_suite("array::inner"))
{
    // INNER_SUBCASE( case1c, a, b );
    // INNER_SUBCASE( case1c, a_a, b_a );
    INNER_SUBCASE( case1c, a_f, b_f );
    INNER_SUBCASE( case1c, a_h, b_h );
    INNER_SUBCASE( case1c, a_d, b_d );
}

TEST_CASE("inner(case2)" * doctest::test_suite("array::inner"))
{
    // INNER_SUBCASE( case2, a, b );
    // INNER_SUBCASE( case2, a_a, b_a );
    INNER_SUBCASE( case2, a_f, b_f );
    INNER_SUBCASE( case2, a_h, b_h );
    INNER_SUBCASE( case2, a_d, b_d );
}

TEST_CASE("inner(case2b)" * doctest::test_suite("array::inner"))
{
    // INNER_SUBCASE( case2b, a, b );
    // INNER_SUBCASE( case2b, a_a, b_a );
    INNER_SUBCASE( case2b, a_f, b_f );
    INNER_SUBCASE( case2b, a_h, b_h );
    INNER_SUBCASE( case2b, a_d, b_d );
}

TEST_CASE("inner(case2c)" * doctest::test_suite("array::inner"))
{
    // INNER_SUBCASE( case2c, a, b );
    // INNER_SUBCASE( case2c, a_a, b_a );
    INNER_SUBCASE( case2c, a_f, b_f );
    INNER_SUBCASE( case2c, a_h, b_h );
    INNER_SUBCASE( case2c, a_d, b_d );
}

TEST_CASE("inner(case2d)" * doctest::test_suite("array::inner"))
{
    // INNER_SUBCASE( case2d, a, b );
    // INNER_SUBCASE( case2d, a_a, b_a );
    INNER_SUBCASE( case2d, a_f, b_f );
    INNER_SUBCASE( case2d, a_h, b_h );
    INNER_SUBCASE( case2d, a_d, b_d );
}

TEST_CASE("inner(case3)" * doctest::test_suite("array::inner"))
{
    // INNER_SUBCASE( case3, a, b );
    // INNER_SUBCASE( case3, a_a, b_a );
    INNER_SUBCASE( case3, a_f, b_f );
    INNER_SUBCASE( case3, a_h, b_h );
    INNER_SUBCASE( case3, a_d, b_d );
}

TEST_CASE("inner(case3b)" * doctest::test_suite("array::inner"))
{
    // INNER_SUBCASE( case3b, a, b );
    // INNER_SUBCASE( case3b, a_a, b_a );
    INNER_SUBCASE( case3b, a_f, b_f );
    INNER_SUBCASE( case3b, a_h, b_h );
    INNER_SUBCASE( case3b, a_d, b_d );
}

TEST_CASE("inner(case3c)" * doctest::test_suite("array::inner"))
{
    // INNER_SUBCASE( case3c, a, b );
    // INNER_SUBCASE( case3c, a_a, b_a );
    INNER_SUBCASE( case3c, a_f, b_f );
    INNER_SUBCASE( case3c, a_h, b_h );
    INNER_SUBCASE( case3c, a_d, b_d );
}

TEST_CASE("inner(case3d)" * doctest::test_suite("array::inner"))
{
    // INNER_SUBCASE( case3d, a, b );
    // INNER_SUBCASE( case3d, a_a, b_a );
    INNER_SUBCASE( case3d, a_f, b_f );
    INNER_SUBCASE( case3d, a_h, b_h );
    INNER_SUBCASE( case3d, a_d, b_d );
}
#endif