#include "nmtools/array/functional/activations/leaky_relu.hpp"
#include "nmtools/testing/data/array/leaky_relu.hpp"
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

TEST_CASE("leaky_relu(case1)" * doctest::test_suite("functional::leaky_relu"))
{
    NMTOOLS_TESTING_DECLARE_NS(activations,leaky_relu,case1);
    using namespace args;

    ACTIVATIONS_SUBCASE( "case1", fn::leaky_relu, a );
    ACTIVATIONS_SUBCASE( "case1", fn::leaky_relu, a_a );
    ACTIVATIONS_SUBCASE( "case1", fn::leaky_relu, a_f );
    ACTIVATIONS_SUBCASE( "case1", fn::leaky_relu, a_h );
    ACTIVATIONS_SUBCASE( "case1", fn::leaky_relu, a_d );
}