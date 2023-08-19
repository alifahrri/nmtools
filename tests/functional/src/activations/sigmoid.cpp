#include "nmtools/array/functional/activations/sigmoid.hpp"
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
    NMTOOLS_TESTING_DECLARE_NS(activations,sigmoid,case1);
    using namespace args;

    ACTIVATIONS_SUBCASE( "case1", fn::sigmoid, a );
    ACTIVATIONS_SUBCASE( "case1", fn::sigmoid, a_a );
    ACTIVATIONS_SUBCASE( "case1", fn::sigmoid, a_f );
    ACTIVATIONS_SUBCASE( "case1", fn::sigmoid, a_h );
    ACTIVATIONS_SUBCASE( "case1", fn::sigmoid, a_d );
}