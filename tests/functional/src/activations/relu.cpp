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
    NMTOOLS_TESTING_USE_CASE(activations,relu,case1);
    using namespace args;

    RELU_SUBCASE("case1", fn::relu, a);
    RELU_SUBCASE("case1", fn::relu, a_a);
    RELU_SUBCASE("case1", fn::relu, a_f);
    RELU_SUBCASE("case1", fn::relu, a_h);
    RELU_SUBCASE("case1", fn::relu, a_d);
}

namespace view = nmtools::view;

TEST_CASE("relu" * doctest::test_suite("functional::get_function_composition"))
{
    NMTOOLS_TESTING_USE_CASE(activations,relu,case1);
    using namespace args;

    auto array = view::relu(a);

    auto function = fn::get_function_composition(array);
    auto expect = fn::relu;

    NMTOOLS_ASSERT_EQUAL( function, expect );
    NMTOOLS_ASSERT_CLOSE( function (a), array );
}

TEST_CASE("relu" * doctest::test_suite("functional::get_function_composition"))
{
    NMTOOLS_TESTING_USE_CASE(activations,relu,case1);
    using namespace args;

    auto array = view::relu(a);

    auto function = fn::get_function_composition(array);
    auto expect = fn::unary_ufunc[array.attributes()];

    NMTOOLS_ASSERT_EQUAL( function, expect );
    NMTOOLS_ASSERT_CLOSE( function (a), array );
}