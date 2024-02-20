#include "nmtools/array/functional/activations/softsign.hpp"
#include "nmtools/testing/data/array/softsign.hpp"
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

TEST_CASE("softsign(case1)" * doctest::test_suite("functional::softsign"))
{
    NMTOOLS_TESTING_DECLARE_NS(activations,softsign,case1);
    using namespace args;

    ACTIVATIONS_SUBCASE( "case1", fn::softsign, a );
    ACTIVATIONS_SUBCASE( "case1", fn::softsign, a_a );
    ACTIVATIONS_SUBCASE( "case1", fn::softsign, a_f );
    ACTIVATIONS_SUBCASE( "case1", fn::softsign, a_h );
    ACTIVATIONS_SUBCASE( "case1", fn::softsign, a_d );
}

namespace view = nmtools::view;

TEST_CASE("softsign" * doctest::test_suite("functional::get_function_composition"))
{
    NMTOOLS_TESTING_DECLARE_NS(activations,softsign,case1);
    using namespace args;

    auto array = view::softsign(a);

    auto function = fn::get_function_composition(array);
    auto expect = fn::softsign;

    NMTOOLS_ASSERT_EQUAL( function, expect );
}