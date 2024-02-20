#include "nmtools/array/functional/ufuncs/arcsinh.hpp"
#include "nmtools/testing/data/array/arcsinh.hpp"
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

TEST_CASE("arcsinh(case1)" * doctest::test_suite("functional::arcsinh"))
{
    NMTOOLS_TESTING_DECLARE_NS(view, arcsinh, case1);
    using namespace args;

    FUNCTIONAL_SUBCASE( "case1", fn::arcsinh, a );
    FUNCTIONAL_SUBCASE( "case1", fn::arcsinh, a_a );
    FUNCTIONAL_SUBCASE( "case1", fn::arcsinh, a_f );
    FUNCTIONAL_SUBCASE( "case1", fn::arcsinh, a_h );
    FUNCTIONAL_SUBCASE( "case1", fn::arcsinh, a_d );
}


namespace view = nmtools::view;

TEST_CASE("arcsinh" * doctest::test_suite("functional::get_function_composition"))
{
    NMTOOLS_TESTING_DECLARE_NS(view,arcsinh,case1);
    using namespace args;

    auto array = view::arcsinh(a);

    auto function = fn::get_function_composition(array);
    auto expect = fn::arcsinh;

    NMTOOLS_ASSERT_EQUAL( function, expect );
}