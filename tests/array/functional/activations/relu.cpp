#include "nmtools/array/functional/activations/relu.hpp"
#include "nmtools/testing/data/array/relu.hpp"
#include "nmtools/testing/doctest.hpp"

namespace nm = nmtools;
namespace fn = nmtools::functional;

#define RELU_SUBCASE(subcase_name, function, operand) \
SUBCASE(subcase_name) \
{ \
    auto result = function(operand); \
    NMTOOLS_REQUIRE_EQUAL( nm::shape(result), nm::shape(expect::result) ); \
    NMTOOLS_ASSERT_CLOSE( result, expect::result ); \
}

TEST_CASE("relu(case1)" * doctest::test_suite("functional::relu"))
{
    NMTOOLS_TESTING_DECLARE_NS(activations,relu,case1);
    using namespace args;

    RELU_SUBCASE("case1", fn::relu, a);
    RELU_SUBCASE("case1", fn::relu, a_a);
    RELU_SUBCASE("case1", fn::relu, a_f);
    RELU_SUBCASE("case1", fn::relu, a_h);
    RELU_SUBCASE("case1", fn::relu, a_d);
}