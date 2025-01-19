#include "nmtools/array/ufuncs/cbrt.hpp"
#include "nmtools/testing/data/array/cbrt.hpp"
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

TEST_CASE("cbrt(case1)" * doctest::test_suite("functional::cbrt"))
{
    NMTOOLS_TESTING_USE_CASE(view, cbrt, case1);
    using namespace args;

    FUNCTIONAL_SUBCASE( "case1", fn::cbrt, a );
    FUNCTIONAL_SUBCASE( "case1", fn::cbrt, a_a );
    FUNCTIONAL_SUBCASE( "case1", fn::cbrt, a_f );
    FUNCTIONAL_SUBCASE( "case1", fn::cbrt, a_h );
    FUNCTIONAL_SUBCASE( "case1", fn::cbrt, a_d );
}


namespace view = nmtools::view;

TEST_CASE("cbrt" * doctest::test_suite("functional::get_function_composition"))
{
    NMTOOLS_TESTING_USE_CASE(view,cbrt,case1);
    using namespace args;

    auto array = view::cbrt(a);

    auto function = fn::get_function_composition(array);
    auto expect = fn::cbrt;

    NMTOOLS_ASSERT_EQUAL( function, expect );
}

TEST_CASE("cbrt" * doctest::test_suite("functional::get_function_composition"))
{
    NMTOOLS_TESTING_USE_CASE(view,cbrt,case1);
    using namespace args;

    auto array = view::cbrt(a);

    auto function = fn::get_function_composition(array);
    auto expect = fn::unary_ufunc[array.attributes()];

    NMTOOLS_ASSERT_EQUAL( function, expect );
}