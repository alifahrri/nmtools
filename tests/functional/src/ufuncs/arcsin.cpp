#include "nmtools/array/ufuncs/arcsin.hpp"
#include "nmtools/testing/data/array/arcsin.hpp"
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

TEST_CASE("arcsin(case1)" * doctest::test_suite("functional::arcsin"))
{
    NMTOOLS_TESTING_USE_CASE(view, arcsin, case1);
    using namespace args;

    FUNCTIONAL_SUBCASE( "case1", fn::arcsin, a );
    FUNCTIONAL_SUBCASE( "case1", fn::arcsin, a_a );
    FUNCTIONAL_SUBCASE( "case1", fn::arcsin, a_f );
    FUNCTIONAL_SUBCASE( "case1", fn::arcsin, a_h );
    FUNCTIONAL_SUBCASE( "case1", fn::arcsin, a_d );
}


namespace view = nmtools::view;

TEST_CASE("arcsin" * doctest::test_suite("functional::get_function_composition"))
{
    NMTOOLS_TESTING_USE_CASE(view,arcsin,case1);
    using namespace args;

    auto array = view::arcsin(a);

    auto function = fn::get_function_composition(array);
    auto expect = fn::arcsin;

    NMTOOLS_ASSERT_EQUAL( function, expect );
}

TEST_CASE("arcsin" * doctest::test_suite("functional::get_function_composition"))
{
    NMTOOLS_TESTING_USE_CASE(view,arcsin,case1);
    using namespace args;

    auto array = view::arcsin(a);

    auto function = fn::get_function_composition(array);
    auto expect = fn::unary_ufunc[array.attributes()];

    NMTOOLS_ASSERT_EQUAL( function, expect );
}