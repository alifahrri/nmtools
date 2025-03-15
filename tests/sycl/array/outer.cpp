#include "nmtools/array/outer.hpp"
#include "nmtools/evaluator/sycl.hpp"
#include "nmtools/testing/data/array/outer.hpp"
#include "nmtools/testing/doctest.hpp"

namespace nm = nmtools;
namespace na = nmtools::array;
namespace fn = nmtools::functional;
namespace meta = nm::meta;
namespace view = nmtools::view;

using nmtools_array;

#define OUTER_SUBCASE(case_name, ...) \
SUBCASE(#case_name) \
{ \
    NMTOOLS_TESTING_USE_CASE( array, outer, case_name ); \
    auto view = nmtools::view::outer(__VA_ARGS__); \
    auto ctx = na::sycl::default_context(); \
    auto result = ctx->eval(view); \
    NMTOOLS_ASSERT_EQUAL( nmtools::shape(result), nmtools::shape(expect::result) ); \
    NMTOOLS_ASSERT_CLOSE( result, expect::result ); \
}

TEST_CASE("outer(case1)" * doctest::test_suite("array::outer"))
{
    // OUTER_SUBCASE( case1, a, b );
    // OUTER_SUBCASE( case1, a_a, b_a );
    OUTER_SUBCASE( case1, a_f, b_f );
    OUTER_SUBCASE( case1, a_h, b_h );
    OUTER_SUBCASE( case1, a_d, b_d );
}

TEST_CASE("outer(case1b)" * doctest::test_suite("array::outer"))
{
    // OUTER_SUBCASE( case1b, a, b );
    // OUTER_SUBCASE( case1b, a_a, b_a );
    OUTER_SUBCASE( case1b, a_f, b_f );
    OUTER_SUBCASE( case1b, a_h, b_h );
    OUTER_SUBCASE( case1b, a_d, b_d );
}

TEST_CASE("outer(case1c)" * doctest::test_suite("array::outer"))
{
    // OUTER_SUBCASE( case1c, a, b );
    // OUTER_SUBCASE( case1c, a_a, b_a );
    OUTER_SUBCASE( case1c, a_f, b_f );
    OUTER_SUBCASE( case1c, a_h, b_h );
    OUTER_SUBCASE( case1c, a_d, b_d );
}

TEST_CASE("outer(case2)" * doctest::test_suite("array::outer"))
{
    // OUTER_SUBCASE( case2, a, b );
    // OUTER_SUBCASE( case2, a_a, b_a );
    OUTER_SUBCASE( case2, a_f, b_f );
    OUTER_SUBCASE( case2, a_h, b_h );
    OUTER_SUBCASE( case2, a_d, b_d );
}

TEST_CASE("outer(case2b)" * doctest::test_suite("array::outer"))
{
    // OUTER_SUBCASE( case2b, a, b );
    // OUTER_SUBCASE( case2b, a_a, b_a );
    OUTER_SUBCASE( case2b, a_f, b_f );
    OUTER_SUBCASE( case2b, a_h, b_h );
    OUTER_SUBCASE( case2b, a_d, b_d );
}

TEST_CASE("outer(case2c)" * doctest::test_suite("array::outer"))
{
    // OUTER_SUBCASE( case2c, a, b );
    // OUTER_SUBCASE( case2c, a_a, b_a );
    OUTER_SUBCASE( case2c, a_f, b_f );
    OUTER_SUBCASE( case2c, a_h, b_h );
    OUTER_SUBCASE( case2c, a_d, b_d );
}