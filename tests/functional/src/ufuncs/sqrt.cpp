#include "nmtools/array/functional/ufuncs/sqrt.hpp"
#include "nmtools/testing/data/array/sqrt.hpp"
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

TEST_CASE("sqrt(case1)" * doctest::test_suite("functional::sqrt"))
{
    NMTOOLS_TESTING_USE_CASE(view, sqrt, case1);
    using namespace args;

    FUNCTIONAL_SUBCASE( "case1", fn::sqrt, a );
    FUNCTIONAL_SUBCASE( "case1", fn::sqrt, a_a );
    FUNCTIONAL_SUBCASE( "case1", fn::sqrt, a_f );
    FUNCTIONAL_SUBCASE( "case1", fn::sqrt, a_h );
    FUNCTIONAL_SUBCASE( "case1", fn::sqrt, a_d );
}

namespace view = nmtools::view;

TEST_CASE("sqrt" * doctest::test_suite("functional::get_function_composition"))
{
    NMTOOLS_TESTING_USE_CASE(view,sqrt,case1);
    using namespace args;

    auto array = view::sqrt(a);

    auto function = fn::get_function_composition(array);
    auto expect = fn::sqrt;

    NMTOOLS_ASSERT_EQUAL( function, expect );
}

TEST_CASE("sqrt" * doctest::test_suite("functional::get_function_composition"))
{
    NMTOOLS_TESTING_USE_CASE(view,sqrt,case1);
    using namespace args;

    auto array = view::sqrt(a);

    auto function = fn::get_function_composition(array);
    auto expect = fn::unary_ufunc[array.attributes()];

    NMTOOLS_ASSERT_EQUAL( function, expect );
}