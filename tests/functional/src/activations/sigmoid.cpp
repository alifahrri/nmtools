#include "nmtools/array/sigmoid.hpp"
#include "nmtools/testing/data/array/sigmoid.hpp"
#include "nmtools/testing/doctest.hpp"

namespace nm = nmtools;
namespace fn = nmtools::functional;

#define ACTIVATIONS_SUBCASE(subcase_name, function, operand) \
SUBCASE(subcase_name) \
{ \
    auto result = function (operand); \
    NMTOOLS_REQUIRE_EQUAL( nm::shape(result), nm::shape(expect::result) ); \
    NMTOOLS_ASSERT_CLOSE( result, expect::result ); \
}

TEST_CASE("sigmoid(case1)" * doctest::test_suite("functional::sigmoid"))
{
    NMTOOLS_TESTING_USE_CASE(activations,sigmoid,case1);
    using namespace args;

    ACTIVATIONS_SUBCASE( "case1", fn::sigmoid, a );
    ACTIVATIONS_SUBCASE( "case1", fn::sigmoid, a_a );
    ACTIVATIONS_SUBCASE( "case1", fn::sigmoid, a_f );
    ACTIVATIONS_SUBCASE( "case1", fn::sigmoid, a_h );
    ACTIVATIONS_SUBCASE( "case1", fn::sigmoid, a_d );
}

namespace view = nmtools::view;

TEST_CASE("sigmoid" * doctest::test_suite("functional::get_function_composition"))
{
    NMTOOLS_TESTING_USE_CASE(activations,sigmoid,case1);
    using namespace args;

    auto array = view::sigmoid(a);

    auto function = fn::get_function_composition(array);
    auto expect = fn::sigmoid;

    NMTOOLS_ASSERT_EQUAL( function, expect );
    NMTOOLS_ASSERT_CLOSE( function (a), array );
}

TEST_CASE("sigmoid" * doctest::test_suite("functional::get_function_composition"))
{
    NMTOOLS_TESTING_USE_CASE(activations,sigmoid,case1);
    using namespace args;

    auto array = view::sigmoid(a);

    auto function = fn::get_function_composition(array);
    auto expect = fn::unary_ufunc[array.attributes()];

    NMTOOLS_ASSERT_EQUAL( function, expect );
    NMTOOLS_ASSERT_CLOSE( function (a), array );
}