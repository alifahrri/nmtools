#include "nmtools/array/functional/activations/mish.hpp"
#include "nmtools/testing/data/array/mish.hpp"
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

TEST_CASE("mish(case1)" * doctest::test_suite("functional::mish"))
{
    NMTOOLS_TESTING_USE_CASE(activations,mish,case1);
    using namespace args;

    ACTIVATIONS_SUBCASE( "case1", fn::mish, a );
    ACTIVATIONS_SUBCASE( "case1", fn::mish, a_a );
    ACTIVATIONS_SUBCASE( "case1", fn::mish, a_f );
    ACTIVATIONS_SUBCASE( "case1", fn::mish, a_h );
    ACTIVATIONS_SUBCASE( "case1", fn::mish, a_d );
}

namespace view = nmtools::view;

TEST_CASE("mish" * doctest::test_suite("functional::get_function_composition"))
{
    NMTOOLS_TESTING_USE_CASE(activations,mish,case1);
    using namespace args;

    auto array = view::mish(a);

    auto function = fn::get_function_composition(array);
    auto expect = fn::mish;

    NMTOOLS_ASSERT_EQUAL( function, expect );
    NMTOOLS_ASSERT_CLOSE( function (a), array );
}

TEST_CASE("mish" * doctest::test_suite("functional::get_function_composition"))
{
    NMTOOLS_TESTING_USE_CASE(activations,mish,case1);
    using namespace args;

    auto array = view::mish(a);

    auto function = fn::get_function_composition(array);
    auto expect = fn::unary_ufunc[array.attributes()];

    NMTOOLS_ASSERT_EQUAL( function, expect );
    NMTOOLS_ASSERT_CLOSE( function (a), array );
}