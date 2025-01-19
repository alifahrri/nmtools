#include "nmtools/array/roll.hpp"
#include "nmtools/testing/data/array/roll.hpp"
#include "nmtools/testing/doctest.hpp"

namespace nm = nmtools;
namespace fn = nm::functional;
namespace view = nmtools::view;

using nmtools::unwrap;
using namespace nmtools::literals;

#define FUNCTIONAL_ROLL_SUBCASE(subcase_name, function, ...) \
SUBCASE(#subcase_name) \
{ \
    NMTOOLS_TESTING_USE_CASE(roll, subcase_name); \
    using namespace args; \
    auto result = function (__VA_ARGS__); \
    NMTOOLS_REQUIRE_EQUAL( nm::shape(result), nm::shape(expect::result) ); \
    NMTOOLS_ASSERT_CLOSE( result, expect::result ); \
}

TEST_CASE("roll(case1a)" * doctest::test_suite("functional::roll"))
{
    FUNCTIONAL_ROLL_SUBCASE( case1a, fn::roll[shift], array );
    FUNCTIONAL_ROLL_SUBCASE( case1a, fn::roll[shift], array_a );
    FUNCTIONAL_ROLL_SUBCASE( case1a, fn::roll[shift], array_f );
    FUNCTIONAL_ROLL_SUBCASE( case1a, fn::roll[shift], array_d );
    FUNCTIONAL_ROLL_SUBCASE( case1a, fn::roll[shift], array_h );
}

TEST_CASE("roll(case1b)" * doctest::test_suite("functional::roll"))
{
    FUNCTIONAL_ROLL_SUBCASE( case1b, fn::roll[shift], array );
    FUNCTIONAL_ROLL_SUBCASE( case1b, fn::roll[shift], array_a );
    FUNCTIONAL_ROLL_SUBCASE( case1b, fn::roll[shift], array_f );
    FUNCTIONAL_ROLL_SUBCASE( case1b, fn::roll[shift], array_d );
    FUNCTIONAL_ROLL_SUBCASE( case1b, fn::roll[shift], array_h );
}

TEST_CASE("roll(case1c)" * doctest::test_suite("functional::roll"))
{
    FUNCTIONAL_ROLL_SUBCASE( case1c, fn::roll[shift], array );
    FUNCTIONAL_ROLL_SUBCASE( case1c, fn::roll[shift], array_a );
    FUNCTIONAL_ROLL_SUBCASE( case1c, fn::roll[shift], array_f );
    FUNCTIONAL_ROLL_SUBCASE( case1c, fn::roll[shift], array_d );
    FUNCTIONAL_ROLL_SUBCASE( case1c, fn::roll[shift], array_h );
}

TEST_CASE("roll(case2a)" * doctest::test_suite("functional::roll"))
{
    FUNCTIONAL_ROLL_SUBCASE( case2a, fn::roll[shift], array );
    FUNCTIONAL_ROLL_SUBCASE( case2a, fn::roll[shift], array_a );
    FUNCTIONAL_ROLL_SUBCASE( case2a, fn::roll[shift], array_f );
    FUNCTIONAL_ROLL_SUBCASE( case2a, fn::roll[shift], array_d );
    FUNCTIONAL_ROLL_SUBCASE( case2a, fn::roll[shift], array_h );
}

TEST_CASE("roll(case2b)" * doctest::test_suite("functional::roll"))
{
    FUNCTIONAL_ROLL_SUBCASE( case2b, fn::roll[shift], array );
    FUNCTIONAL_ROLL_SUBCASE( case2b, fn::roll[shift], array_a );
    FUNCTIONAL_ROLL_SUBCASE( case2b, fn::roll[shift], array_f );
    FUNCTIONAL_ROLL_SUBCASE( case2b, fn::roll[shift], array_d );
    FUNCTIONAL_ROLL_SUBCASE( case2b, fn::roll[shift], array_h );
}

TEST_CASE("roll(case2c)" * doctest::test_suite("functional::roll"))
{
    FUNCTIONAL_ROLL_SUBCASE( case2c, fn::roll[shift][axis], array );
    FUNCTIONAL_ROLL_SUBCASE( case2c, fn::roll[shift][axis], array_a );
    FUNCTIONAL_ROLL_SUBCASE( case2c, fn::roll[shift][axis], array_f );
    FUNCTIONAL_ROLL_SUBCASE( case2c, fn::roll[shift][axis], array_d );
    FUNCTIONAL_ROLL_SUBCASE( case2c, fn::roll[shift][axis], array_h );
}

TEST_CASE("roll(case2d)" * doctest::test_suite("functional::roll"))
{
    FUNCTIONAL_ROLL_SUBCASE( case2d, fn::roll[shift][axis], array );
    FUNCTIONAL_ROLL_SUBCASE( case2d, fn::roll[shift][axis], array_a );
    FUNCTIONAL_ROLL_SUBCASE( case2d, fn::roll[shift][axis], array_f );
    FUNCTIONAL_ROLL_SUBCASE( case2d, fn::roll[shift][axis], array_d );
    FUNCTIONAL_ROLL_SUBCASE( case2d, fn::roll[shift][axis], array_h );
}

TEST_CASE("roll(case2e)" * doctest::test_suite("functional::roll"))
{
    FUNCTIONAL_ROLL_SUBCASE( case2e, fn::roll[shift][axis], array );
    FUNCTIONAL_ROLL_SUBCASE( case2e, fn::roll[shift][axis], array_a );
    FUNCTIONAL_ROLL_SUBCASE( case2e, fn::roll[shift][axis], array_f );
    FUNCTIONAL_ROLL_SUBCASE( case2e, fn::roll[shift][axis], array_d );
    FUNCTIONAL_ROLL_SUBCASE( case2e, fn::roll[shift][axis], array_h );
}

TEST_CASE("roll" * doctest::test_suite("functional::get_function_composition") * doctest::may_fail())
{
    NMTOOLS_TESTING_USE_CASE(roll,case1a);
    using namespace args;

    auto a = view::roll(array,shift);

    auto function = fn::get_function_composition(a);
    auto expect   = fn::roll[shift];

    NMTOOLS_ASSERT_EQUAL( function, expect );
}

TEST_CASE("roll" * doctest::test_suite("functional::get_function_composition"))
{
    NMTOOLS_TESTING_USE_CASE(roll,case2c);
    using namespace args;

    auto a = view::roll(array,shift,axis);

    auto function = fn::get_function_composition(a);
    auto expect   = fn::indexing[unwrap(a).attributes()];

    NMTOOLS_ASSERT_EQUAL( function, expect );
    NMTOOLS_ASSERT_EQUAL( unwrap(function) (array), a );
}