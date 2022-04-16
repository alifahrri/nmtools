#include "nmtools/array/functional/activations/selu.hpp"
#include "nmtools/testing/data/array/selu.hpp"
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

TEST_CASE("selu(case1)" * doctest::test_suite("functional::selu"))
{
    NMTOOLS_TESTING_DECLARE_NS(activations,selu,case1);
    using namespace args;

    ACTIVATIONS_SUBCASE( "case1", fn::selu, a );
    ACTIVATIONS_SUBCASE( "case1", fn::selu, a_a );
    ACTIVATIONS_SUBCASE( "case1", fn::selu, a_f );
    ACTIVATIONS_SUBCASE( "case1", fn::selu, a_h );
    ACTIVATIONS_SUBCASE( "case1", fn::selu, a_d );
}