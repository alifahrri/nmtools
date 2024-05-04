#include "nmtools/array/functional/flatten.hpp"
#include "nmtools/testing/data/array/flatten.hpp"
#include "nmtools/testing/doctest.hpp"

namespace nm = nmtools;
namespace fn = nm::functional;

#define FLATTEN_SUBCASE(subcase_name, function, array) \
SUBCASE(subcase_name) \
{ \
    auto result = function(array); \
    NMTOOLS_REQUIRE_EQUAL( nmtools::shape(result), nmtools::shape(expect::expected) ); \
    NMTOOLS_ASSERT_CLOSE( result, expect::expected ); \
}

#define CONSTEXPR_FLATTEN_SUBCASE(subcase_name, function, array) \
SUBCASE(subcase_name) \
{ \
    constexpr auto result = function(array); \
    NMTOOLS_REQUIRE_EQUAL( nmtools::shape(result), nmtools::shape(expect::expected) ); \
    NMTOOLS_ASSERT_CLOSE( result, expect::expected ); \
}

TEST_CASE("flatten(case1)" * doctest::test_suite("functional::reshape"))
{
    NMTOOLS_TESTING_DECLARE_NS(flatten,case1);
    using namespace args;

    FLATTEN_SUBCASE( "case1", fn::flatten, array );
    FLATTEN_SUBCASE( "case1", fn::flatten, array_a );
    FLATTEN_SUBCASE( "case1", fn::flatten, array_f );
    FLATTEN_SUBCASE( "case1", fn::flatten, array_h );
    FLATTEN_SUBCASE( "case1", fn::flatten, array_d );
}

TEST_CASE("flatten(case2)" * doctest::test_suite("functional::reshape"))
{
    NMTOOLS_TESTING_DECLARE_NS(flatten,case2);
    using namespace args;

    FLATTEN_SUBCASE( "case2", fn::flatten, array );
    FLATTEN_SUBCASE( "case2", fn::flatten, array_a );
    FLATTEN_SUBCASE( "case2", fn::flatten, array_f );
    FLATTEN_SUBCASE( "case2", fn::flatten, array_h );
    FLATTEN_SUBCASE( "case2", fn::flatten, array_d );
}

TEST_CASE("flatten(case3)" * doctest::test_suite("functional::reshape"))
{
    NMTOOLS_TESTING_DECLARE_NS(flatten,case3);
    using namespace args;

    FLATTEN_SUBCASE( "case3", fn::flatten, array );
    FLATTEN_SUBCASE( "case3", fn::flatten, array_a );
    FLATTEN_SUBCASE( "case3", fn::flatten, array_f );
    FLATTEN_SUBCASE( "case3", fn::flatten, array_h );
    FLATTEN_SUBCASE( "case3", fn::flatten, array_d );
}

TEST_CASE("flatten(case4)" * doctest::test_suite("functional::reshape"))
{
    NMTOOLS_TESTING_DECLARE_NS(flatten,case4);
    using namespace args;

    FLATTEN_SUBCASE( "case4", fn::flatten, array );
    FLATTEN_SUBCASE( "case4", fn::flatten, array_a );
    FLATTEN_SUBCASE( "case4", fn::flatten, array_f );
    FLATTEN_SUBCASE( "case4", fn::flatten, array_h );
    FLATTEN_SUBCASE( "case4", fn::flatten, array_d );
}

TEST_CASE("constexpr_flatten(case4)" * doctest::test_suite("functional::reshape"))
{
    NMTOOLS_TESTING_DECLARE_NS(constexpr_flatten,case4);
    using namespace args;

    FLATTEN_SUBCASE( "case4", fn::flatten, array );
    FLATTEN_SUBCASE( "case4", fn::flatten, array_a );
    FLATTEN_SUBCASE( "case4", fn::flatten, array_f );
    FLATTEN_SUBCASE( "case4", fn::flatten, array_h );
}

namespace view = nmtools::view;
using nmtools::unwrap;

TEST_CASE("flatten" * doctest::test_suite("functional::get_function_composition") * doctest::may_fail())
{
    NMTOOLS_TESTING_DECLARE_NS(flatten,case4);
    using namespace args;

    auto a = view::flatten(array);

    auto function = fn::get_function_composition(a);
    auto expect = fn::flatten;

    NMTOOLS_ASSERT_EQUAL( function, expect );
}

TEST_CASE("flatten" * doctest::test_suite("functional::get_function_composition"))
{
    NMTOOLS_TESTING_DECLARE_NS(flatten,case4);
    using namespace args;

    auto a = view::flatten(array);

    auto function = fn::get_function_composition(a);
    auto expect = fn::indexing[unwrap(a).attributes()];

    NMTOOLS_ASSERT_EQUAL( function, expect );
}