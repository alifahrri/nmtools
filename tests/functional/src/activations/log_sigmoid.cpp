#include "nmtools/array/functional/activations/log_sigmoid.hpp"
#include "nmtools/testing/data/array/log_sigmoid.hpp"
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

TEST_CASE("log_sigmoid(case1)" * doctest::test_suite("functional::log_sigmoid"))
{
    NMTOOLS_TESTING_DECLARE_NS(activations,log_sigmoid,case1);
    using namespace args;

    ACTIVATIONS_SUBCASE( "case1", fn::log_sigmoid, a );
    ACTIVATIONS_SUBCASE( "case1", fn::log_sigmoid, a_a );
    ACTIVATIONS_SUBCASE( "case1", fn::log_sigmoid, a_f );
    ACTIVATIONS_SUBCASE( "case1", fn::log_sigmoid, a_h );
    ACTIVATIONS_SUBCASE( "case1", fn::log_sigmoid, a_d );
}

namespace view = nmtools::view;

TEST_CASE("log_sigmoid" * doctest::test_suite("functional::get_function_composition"))
{
    NMTOOLS_TESTING_DECLARE_NS(activations,log_sigmoid,case1);
    using namespace args;

    auto array = view::log_sigmoid(a);

    auto function = fn::get_function_composition(array);
    auto expect = fn::log_sigmoid;

    NMTOOLS_ASSERT_EQUAL( function, expect );
}