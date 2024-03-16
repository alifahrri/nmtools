#include "nmtools/array/functional/ufuncs/arctan.hpp"
#include "nmtools/testing/data/array/arctan.hpp"
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

TEST_CASE("arctan(case1)" * doctest::test_suite("functional::arctan"))
{
    NMTOOLS_TESTING_DECLARE_NS(view, arctan, case1);
    using namespace args;

    FUNCTIONAL_SUBCASE( "case1", fn::arctan, a );
    FUNCTIONAL_SUBCASE( "case1", fn::arctan, a_a );
    FUNCTIONAL_SUBCASE( "case1", fn::arctan, a_f );
    FUNCTIONAL_SUBCASE( "case1", fn::arctan, a_h );
    FUNCTIONAL_SUBCASE( "case1", fn::arctan, a_d );
}


namespace view = nmtools::view;

TEST_CASE("arctan" * doctest::test_suite("functional::get_function_composition"))
{
    NMTOOLS_TESTING_DECLARE_NS(view,arctan,case1);
    using namespace args;

    auto array = view::arctan(a);

    auto function = fn::get_function_composition(array);
    auto expect = fn::arctan;

    NMTOOLS_ASSERT_EQUAL( function, expect );
}

TEST_CASE("arctan" * doctest::test_suite("functional::get_function_composition"))
{
    NMTOOLS_TESTING_DECLARE_NS(view,arctan,case1);
    using namespace args;

    auto array = view::arctan(a);

    auto function = fn::get_function_composition(array);
    auto expect = fn::unary_ufunc[array.attributes()];

    NMTOOLS_ASSERT_EQUAL( function, expect );
}