#include "nmtools/array/functional/flip.hpp"
#include "nmtools/testing/data/array/flip.hpp"
#include "nmtools/testing/doctest.hpp"

namespace nm = nmtools;
namespace fn = nm::functional;

using nmtools::unwrap;

#define FUNCTIONAL_SUBCASE(subcase_name, function, ...) \
SUBCASE(subcase_name) \
{ \
    auto result = function (__VA_ARGS__); \
    NMTOOLS_REQUIRE_EQUAL( nm::shape(result), nm::shape(expect::result) ); \
    NMTOOLS_ASSERT_CLOSE( result, expect::result ); \
}


TEST_CASE("flip(case1)" * doctest::test_suite("functional::flip"))
{
    NMTOOLS_TESTING_DECLARE_NS(flip, case1);
    using namespace args;

    FUNCTIONAL_SUBCASE( "case1", fn::flip[axis], array );
    FUNCTIONAL_SUBCASE( "case1", fn::flip[axis], array_a );
    FUNCTIONAL_SUBCASE( "case1", fn::flip[axis], array_f );
    FUNCTIONAL_SUBCASE( "case1", fn::flip[axis], array_h );
    // FUNCTIONAL_SUBCASE( "case1", fn::flip[axis], array_d );
}

TEST_CASE("flip(case2)" * doctest::test_suite("functional::flip"))
{
    NMTOOLS_TESTING_DECLARE_NS(flip, case2);
    using namespace args;

    FUNCTIONAL_SUBCASE( "case2", fn::flip[axis], array );
    FUNCTIONAL_SUBCASE( "case2", fn::flip[axis], array_a );
    FUNCTIONAL_SUBCASE( "case2", fn::flip[axis], array_f );
    FUNCTIONAL_SUBCASE( "case2", fn::flip[axis], array_h );
    // FUNCTIONAL_SUBCASE( "case2", fn::flip[axis], array_d );
}

TEST_CASE("flip(case4)" * doctest::test_suite("functional::flip"))
{
    NMTOOLS_TESTING_DECLARE_NS(flip, case4);
    using namespace args;

    FUNCTIONAL_SUBCASE( "case4", fn::flip[axis], array );
    FUNCTIONAL_SUBCASE( "case4", fn::flip[axis], array_a );
    FUNCTIONAL_SUBCASE( "case4", fn::flip[axis], array_f );
    FUNCTIONAL_SUBCASE( "case4", fn::flip[axis], array_h );
    // FUNCTIONAL_SUBCASE( "case4", fn::flip[axis], array_d );
}

namespace view = nmtools::view;

TEST_CASE("flip" * doctest::test_suite("functional::get_function_composition") * doctest::may_fail())
{
    NMTOOLS_TESTING_DECLARE_NS(flip,case4);
    using namespace args;

    auto a = view::flip(array,axis);

    auto function = fn::get_function_composition(a);
    auto expect = fn::flip[axis];

    NMTOOLS_ASSERT_EQUAL( function, expect );
}

TEST_CASE("flip" * doctest::test_suite("functional::get_function_composition"))
{
    NMTOOLS_TESTING_DECLARE_NS(flip,case4);
    using namespace args;

    auto a = view::flip(array,axis);

    auto function = fn::get_function_composition(a);
    auto expect = fn::indexing[unwrap(a).attributes()];

    NMTOOLS_ASSERT_EQUAL( function, expect );
}