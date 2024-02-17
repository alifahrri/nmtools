#include "nmtools/array/functional/ufuncs/arccosh.hpp"
#include "nmtools/testing/data/array/arccosh.hpp"
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

TEST_CASE("arccosh(case1)" * doctest::test_suite("functional::arccosh"))
{
    NMTOOLS_TESTING_DECLARE_NS(view, arccosh, case1);
    using namespace args;

    FUNCTIONAL_SUBCASE( "case1", fn::arccosh, a );
    FUNCTIONAL_SUBCASE( "case1", fn::arccosh, a_a );
    FUNCTIONAL_SUBCASE( "case1", fn::arccosh, a_f );
    FUNCTIONAL_SUBCASE( "case1", fn::arccosh, a_h );
    FUNCTIONAL_SUBCASE( "case1", fn::arccosh, a_d );
}

namespace view = nmtools::view;

TEST_CASE("arccosh" * doctest::test_suite("functional::get_function_composition"))
{
    NMTOOLS_TESTING_DECLARE_NS(view,arccosh,case1);
    using namespace args;

    auto array = view::arccosh(a);

    auto function = fn::get_function_composition(array);
    auto expect = fn::arccosh;

    NMTOOLS_ASSERT_EQUAL( function, expect );
}