#include "nmtools/array/functional/activations/elu.hpp"
#include "nmtools/testing/data/array/elu.hpp"
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

TEST_CASE("elu(case1)" * doctest::test_suite("functional::elu"))
{
    NMTOOLS_TESTING_DECLARE_NS(activations,elu,case1);
    using namespace args;

    ACTIVATIONS_SUBCASE( "case1", fn::elu, a );
    ACTIVATIONS_SUBCASE( "case1", fn::elu, a_a );
    ACTIVATIONS_SUBCASE( "case1", fn::elu, a_f );
    ACTIVATIONS_SUBCASE( "case1", fn::elu, a_h );
    ACTIVATIONS_SUBCASE( "case1", fn::elu, a_d );
}

TEST_CASE("elu(case2)" * doctest::test_suite("functional::elu"))
{
    NMTOOLS_TESTING_DECLARE_NS(activations,elu,case2);
    using namespace args;

    ACTIVATIONS_SUBCASE( "case2", fn::elu[alpha], a );
    ACTIVATIONS_SUBCASE( "case2", fn::elu[alpha], a_a );
    ACTIVATIONS_SUBCASE( "case2", fn::elu[alpha], a_f );
    ACTIVATIONS_SUBCASE( "case2", fn::elu[alpha], a_h );
    ACTIVATIONS_SUBCASE( "case2", fn::elu[alpha], a_d );
}