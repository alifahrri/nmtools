#include "nmtools/array/functional/activations/softplus.hpp"
#include "nmtools/testing/data/array/softplus.hpp"
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

TEST_CASE("softplus(case1)" * doctest::test_suite("functional::softplus"))
{
    NMTOOLS_TESTING_DECLARE_NS(activations,softplus,case1);
    using namespace args;

    ACTIVATIONS_SUBCASE( "case1", fn::softplus, a );
    ACTIVATIONS_SUBCASE( "case1", fn::softplus, a_a );
    ACTIVATIONS_SUBCASE( "case1", fn::softplus, a_f );
    ACTIVATIONS_SUBCASE( "case1", fn::softplus, a_h );
    ACTIVATIONS_SUBCASE( "case1", fn::softplus, a_d );
}