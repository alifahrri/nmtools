#include "nmtools/array/dstack.hpp"
#include "nmtools/evaluator/sycl.hpp"
#include "nmtools/array/random.hpp"
#include "nmtools/testing/data/array/dstack.hpp"
#include "nmtools/testing/doctest.hpp"

namespace nm = nmtools;
namespace na = nmtools::array;
namespace fn = nmtools::functional;
namespace meta = nm::meta;
namespace view = nmtools::view;

using nmtools_array;

#define DSTACK_SUBCASE( case_name, ... ) \
SUBCASE(#case_name) \
{ \
    NMTOOLS_TESTING_USE_CASE( array, dstack, case_name ); \
    auto ctx = na::sycl::default_context(); \
    auto view = nmtools::view::dstack(__VA_ARGS__); \
    auto result = ctx->eval(view); \
    NMTOOLS_ASSERT_EQUAL( nmtools::shape(result), nmtools::shape(expect::result) ); \
    NMTOOLS_ASSERT_CLOSE( result, expect::result ); \
}

TEST_CASE("dstack(case1)" * doctest::test_suite("array::dstack"))
{
    // DSTACK_SUBCASE( case1, a, b );
    // DSTACK_SUBCASE( case1, a_a, b_a );
    DSTACK_SUBCASE( case1, a_f, b_f );
    DSTACK_SUBCASE( case1, a_h, b_h );
    DSTACK_SUBCASE( case1, a_d, b_d );
}

TEST_CASE("dstack(case2)" * doctest::test_suite("array::dstack"))
{
    // DSTACK_SUBCASE( case2, a, b );
    // DSTACK_SUBCASE( case2, a_a, b_a );
    DSTACK_SUBCASE( case2, a_f, b_f );
    DSTACK_SUBCASE( case2, a_h, b_h );
    DSTACK_SUBCASE( case2, a_d, b_d );
}

TEST_CASE("dstack(case2b)" * doctest::test_suite("array::dstack"))
{
    // DSTACK_SUBCASE( case2b, a, b );
    // DSTACK_SUBCASE( case2b, a_a, b_a );
    DSTACK_SUBCASE( case2b, a_f, b_f );
    DSTACK_SUBCASE( case2b, a_h, b_h );
    DSTACK_SUBCASE( case2b, a_d, b_d );
}

TEST_CASE("dstack(case3)" * doctest::test_suite("array::dstack"))
{
    // DSTACK_SUBCASE( case3, a, b );
    // DSTACK_SUBCASE( case3, a_a, b_a );
    DSTACK_SUBCASE( case3, a_f, b_f );
    DSTACK_SUBCASE( case3, a_h, b_h );
    DSTACK_SUBCASE( case3, a_d, b_d );
}

TEST_CASE("dstack(case4)" * doctest::test_suite("array::dstack"))
{
    // DSTACK_SUBCASE( case4, a, b );
    // DSTACK_SUBCASE( case4, a_a, b_a );
    DSTACK_SUBCASE( case4, a_f, b_f );
    DSTACK_SUBCASE( case4, a_h, b_h );
    DSTACK_SUBCASE( case4, a_d, b_d );
}