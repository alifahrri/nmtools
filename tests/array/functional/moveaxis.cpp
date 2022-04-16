#include "nmtools/array/functional/moveaxis.hpp"
#include "nmtools/testing/data/array/moveaxis.hpp"
#include "nmtools/testing/doctest.hpp"

namespace nm = nmtools;
namespace fn = nm::functional;

#define FUNCTIONAL_SUBCASE(subcase_name, function, ...) \
SUBCASE(subcase_name) \
{ \
    auto result = function (__VA_ARGS__); \
    NMTOOLS_REQUIRE_EQUAL( nm::shape(result), nm::shape(expect::result) ); \
    NMTOOLS_ASSERT_CLOSE( result, expect::result ); \
}


TEST_CASE("moveaxis(case1)" * doctest::test_suite("functional::moveaxis"))
{
    NMTOOLS_TESTING_DECLARE_NS(array, moveaxis, case1);
    using namespace args;

    FUNCTIONAL_SUBCASE( "case1", fn::moveaxis[source][destination], a );
    FUNCTIONAL_SUBCASE( "case1", fn::moveaxis[source][destination], a_a );
    FUNCTIONAL_SUBCASE( "case1", fn::moveaxis[source][destination], a_f );
    FUNCTIONAL_SUBCASE( "case1", fn::moveaxis[source][destination], a_h );
    FUNCTIONAL_SUBCASE( "case1", fn::moveaxis[source][destination], a_d );
}

TEST_CASE("moveaxis(case2)" * doctest::test_suite("functional::moveaxis"))
{
    NMTOOLS_TESTING_DECLARE_NS(array, moveaxis, case2);
    using namespace args;

    FUNCTIONAL_SUBCASE( "case2", fn::moveaxis[source][destination], a );
    FUNCTIONAL_SUBCASE( "case2", fn::moveaxis[source][destination], a_a );
    FUNCTIONAL_SUBCASE( "case2", fn::moveaxis[source][destination], a_f );
    FUNCTIONAL_SUBCASE( "case2", fn::moveaxis[source][destination], a_h );
    FUNCTIONAL_SUBCASE( "case2", fn::moveaxis[source][destination], a_d );
}

TEST_CASE("moveaxis(case3)" * doctest::test_suite("functional::moveaxis"))
{
    NMTOOLS_TESTING_DECLARE_NS(array, moveaxis, case3);
    using namespace args;

    FUNCTIONAL_SUBCASE( "case3", fn::moveaxis[source][destination], a );
    FUNCTIONAL_SUBCASE( "case3", fn::moveaxis[source][destination], a_a );
    FUNCTIONAL_SUBCASE( "case3", fn::moveaxis[source][destination], a_f );
    FUNCTIONAL_SUBCASE( "case3", fn::moveaxis[source][destination], a_h );
    FUNCTIONAL_SUBCASE( "case3", fn::moveaxis[source][destination], a_d );
}

TEST_CASE("moveaxis(case8)" * doctest::test_suite("functional::moveaxis"))
{
    NMTOOLS_TESTING_DECLARE_NS(array, moveaxis, case8);
    using namespace args;

    FUNCTIONAL_SUBCASE( "case8", fn::moveaxis[source][destination], a );
    FUNCTIONAL_SUBCASE( "case8", fn::moveaxis[source_a][destination_a], a_a );
    FUNCTIONAL_SUBCASE( "case8", fn::moveaxis[source_f][destination_f], a_f );
    FUNCTIONAL_SUBCASE( "case8", fn::moveaxis[source_h][destination_h], a_h );
    FUNCTIONAL_SUBCASE( "case8", fn::moveaxis[source_v][destination_v], a_d );
}