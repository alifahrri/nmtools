#include "nmtools/array/functional/activations/celu.hpp"
#include "nmtools/testing/data/array/celu.hpp"
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

TEST_CASE("celu(case1)" * doctest::test_suite("functional::celu"))
{
    NMTOOLS_TESTING_DECLARE_NS(activations,celu,case1);
    using namespace args;

    ACTIVATIONS_SUBCASE( "case1", fn::celu, a );
    ACTIVATIONS_SUBCASE( "case1", fn::celu, a_a );
    ACTIVATIONS_SUBCASE( "case1", fn::celu, a_f );
    ACTIVATIONS_SUBCASE( "case1", fn::celu, a_h );
    ACTIVATIONS_SUBCASE( "case1", fn::celu, a_d );
}

TEST_CASE("celu(case2)" * doctest::test_suite("functional::celu"))
{
    NMTOOLS_TESTING_DECLARE_NS(activations,celu,case2);
    using namespace args;

    ACTIVATIONS_SUBCASE( "case2", fn::celu[alpha], a );
    ACTIVATIONS_SUBCASE( "case2", fn::celu[alpha], a_a );
    ACTIVATIONS_SUBCASE( "case2", fn::celu[alpha], a_f );
    ACTIVATIONS_SUBCASE( "case2", fn::celu[alpha], a_h );
    ACTIVATIONS_SUBCASE( "case2", fn::celu[alpha], a_d );
}

namespace view = nmtools::view;

TEST_CASE("celu" * doctest::test_suite("functional::get_function_composition"))
{
    NMTOOLS_TESTING_DECLARE_NS(activations,celu,case2);
    using namespace args;

    auto array = view::celu(a,alpha);

    auto function = fn::get_function_composition(array);
    auto expect = fn::celu[alpha];

    NMTOOLS_ASSERT_EQUAL( function, expect );
}