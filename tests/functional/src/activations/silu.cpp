#include "nmtools/array/functional/activations/silu.hpp"
#include "nmtools/testing/data/array/silu.hpp"
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

TEST_CASE("silu(case1)" * doctest::test_suite("functional::silu"))
{
    NMTOOLS_TESTING_USE_CASE(activations,silu,case1);
    using namespace args;

    ACTIVATIONS_SUBCASE( "case1", fn::silu, a );
    ACTIVATIONS_SUBCASE( "case1", fn::silu, a_a );
    ACTIVATIONS_SUBCASE( "case1", fn::silu, a_f );
    ACTIVATIONS_SUBCASE( "case1", fn::silu, a_h );
    ACTIVATIONS_SUBCASE( "case1", fn::silu, a_d );
}

namespace view = nmtools::view;

TEST_CASE("silu" * doctest::test_suite("functional::get_function_composition"))
{
    NMTOOLS_TESTING_USE_CASE(activations,silu,case1);
    using namespace args;

    auto array = view::silu(a);

    auto function = fn::get_function_composition(array);
    auto expect = fn::silu;

    NMTOOLS_ASSERT_EQUAL( function, expect );
    NMTOOLS_ASSERT_CLOSE( function (a), array );
}

TEST_CASE("silu" * doctest::test_suite("functional::get_function_composition"))
{
    NMTOOLS_TESTING_USE_CASE(activations,silu,case1);
    using namespace args;

    auto array = view::silu(a);

    auto function = fn::get_function_composition(array);
    auto expect = fn::unary_ufunc[array.attributes()];

    NMTOOLS_ASSERT_EQUAL( function, expect );
    NMTOOLS_ASSERT_CLOSE( function (a), array );
}