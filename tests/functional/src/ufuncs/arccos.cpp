#include "nmtools/array/functional/ufuncs/arccos.hpp"
#include "nmtools/testing/data/array/arccos.hpp"
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

TEST_CASE("arccos(case1)" * doctest::test_suite("functional::arccos"))
{
    NMTOOLS_TESTING_DECLARE_NS(view, arccos, case1);
    using namespace args;

    FUNCTIONAL_SUBCASE( "case1", fn::arccos, a );
    FUNCTIONAL_SUBCASE( "case1", fn::arccos, a_a );
    FUNCTIONAL_SUBCASE( "case1", fn::arccos, a_f );
    FUNCTIONAL_SUBCASE( "case1", fn::arccos, a_h );
    FUNCTIONAL_SUBCASE( "case1", fn::arccos, a_d );
}

namespace view = nmtools::view;

TEST_CASE("arccos" * doctest::test_suite("functional::get_function_composition"))
{
    NMTOOLS_TESTING_DECLARE_NS(view,arccos,case1);
    using namespace args;

    auto array = view::arccos(a);

    auto function = fn::get_function_composition(array);
    auto expect = fn::arccos;

    NMTOOLS_ASSERT_EQUAL( function, expect );
}