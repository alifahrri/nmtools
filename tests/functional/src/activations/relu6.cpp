#include "nmtools/array/functional/activations/relu6.hpp"
#include "nmtools/testing/data/array/relu6.hpp"
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

TEST_CASE("relu6(case1)" * doctest::test_suite("functional::relu6"))
{
    NMTOOLS_TESTING_DECLARE_NS(activations,relu6,case1);
    using namespace args;

    ACTIVATIONS_SUBCASE( "case1", fn::relu6, a );
    ACTIVATIONS_SUBCASE( "case1", fn::relu6, a_a );
    ACTIVATIONS_SUBCASE( "case1", fn::relu6, a_f );
    ACTIVATIONS_SUBCASE( "case1", fn::relu6, a_h );
    ACTIVATIONS_SUBCASE( "case1", fn::relu6, a_d );
}


namespace view = nmtools::view;

TEST_CASE("relu6" * doctest::test_suite("functional::get_function_composition"))
{
    NMTOOLS_TESTING_DECLARE_NS(activations,relu6,case1);
    using namespace args;

    auto array = view::relu6(a);

    auto function = fn::get_function_composition(array);
    auto expect = fn::relu6;

    NMTOOLS_ASSERT_EQUAL( function, expect );
    NMTOOLS_ASSERT_CLOSE( function (a), array );
}

TEST_CASE("relu6" * doctest::test_suite("functional::get_function_composition"))
{
    NMTOOLS_TESTING_DECLARE_NS(activations,relu6,case1);
    using namespace args;

    auto array = view::relu6(a);

    auto function = fn::get_function_composition(array);
    auto expect = fn::unary_ufunc[array.attributes()];

    NMTOOLS_ASSERT_EQUAL( function, expect );
    NMTOOLS_ASSERT_CLOSE( function (a), array );
}