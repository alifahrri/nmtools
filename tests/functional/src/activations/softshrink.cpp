#include "nmtools/array/functional/activations/softshrink.hpp"
#include "nmtools/testing/data/array/softshrink.hpp"
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

TEST_CASE("softshrink(case1)" * doctest::test_suite("functional::softshrink"))
{
    NMTOOLS_TESTING_DECLARE_NS(activations,softshrink,case1);
    using namespace args;

    ACTIVATIONS_SUBCASE( "case1", fn::softshrink, a );
    ACTIVATIONS_SUBCASE( "case1", fn::softshrink, a_a );
    ACTIVATIONS_SUBCASE( "case1", fn::softshrink, a_f );
    ACTIVATIONS_SUBCASE( "case1", fn::softshrink, a_h );
    ACTIVATIONS_SUBCASE( "case1", fn::softshrink, a_d );
}

namespace view = nmtools::view;

TEST_CASE("softshrink" * doctest::test_suite("functional::get_function_composition"))
{
    NMTOOLS_TESTING_DECLARE_NS(activations,softshrink,case1);
    using namespace args;

    auto array = view::softshrink(a);

    auto function = fn::get_function_composition(array);
    auto expect = fn::softshrink[0.5];

    NMTOOLS_ASSERT_EQUAL( function, expect );
}