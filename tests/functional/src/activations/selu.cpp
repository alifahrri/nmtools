#include "nmtools/array/selu.hpp"
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
    NMTOOLS_TESTING_USE_CASE(activations,selu,case1);
    using namespace args;

    ACTIVATIONS_SUBCASE( "case1", fn::selu, a );
    ACTIVATIONS_SUBCASE( "case1", fn::selu, a_a );
    ACTIVATIONS_SUBCASE( "case1", fn::selu, a_f );
    ACTIVATIONS_SUBCASE( "case1", fn::selu, a_h );
    ACTIVATIONS_SUBCASE( "case1", fn::selu, a_d );
}

namespace view = nmtools::view;

TEST_CASE("selu" * doctest::test_suite("functional::get_function_composition"))
{
    NMTOOLS_TESTING_USE_CASE(activations,selu,case1);
    using namespace args;

    auto array = view::selu(a);

    auto function = fn::get_function_composition(array);
    auto expect = fn::selu;

    NMTOOLS_ASSERT_EQUAL( function, expect );
    NMTOOLS_ASSERT_CLOSE( function (a), array );
}

TEST_CASE("selu" * doctest::test_suite("functional::get_function_composition"))
{
    NMTOOLS_TESTING_USE_CASE(activations,selu,case1);
    using namespace args;

    auto array = view::selu(a);

    auto function = fn::get_function_composition(array);
    auto expect = fn::unary_ufunc[array.attributes()];

    NMTOOLS_ASSERT_EQUAL( function, expect );
    NMTOOLS_ASSERT_CLOSE( function (a), array );
}