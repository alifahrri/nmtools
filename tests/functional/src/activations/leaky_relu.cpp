#include "nmtools/array/activations/leaky_relu.hpp"
#include "nmtools/testing/data/array/leaky_relu.hpp"
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

TEST_CASE("leaky_relu(case1)" * doctest::test_suite("functional::leaky_relu"))
{
    NMTOOLS_TESTING_USE_CASE(activations,leaky_relu,case1);
    using namespace args;

    ACTIVATIONS_SUBCASE( "case1", fn::leaky_relu, a );
    ACTIVATIONS_SUBCASE( "case1", fn::leaky_relu, a_a );
    ACTIVATIONS_SUBCASE( "case1", fn::leaky_relu, a_f );
    ACTIVATIONS_SUBCASE( "case1", fn::leaky_relu, a_h );
    ACTIVATIONS_SUBCASE( "case1", fn::leaky_relu, a_d );
}

namespace view = nmtools::view;

TEST_CASE("leaky_relu" * doctest::test_suite("functional::get_function_composition"))
{
    NMTOOLS_TESTING_USE_CASE(activations,leaky_relu,case1);
    using namespace args;

    auto array = view::leaky_relu(a);

    auto function = fn::get_function_composition(array);
    auto expect = fn::leaky_relu[0.01];

    NMTOOLS_ASSERT_EQUAL( function, expect );
    NMTOOLS_ASSERT_CLOSE( function (a), array );
}

TEST_CASE("leaky_relu" * doctest::test_suite("functional::get_function_composition"))
{
    NMTOOLS_TESTING_USE_CASE(activations,leaky_relu,case1);
    using namespace args;

    auto array = view::leaky_relu(a);

    auto function = fn::get_function_composition(array);
    auto expect = fn::unary_ufunc[array.attributes()];

    NMTOOLS_ASSERT_EQUAL( function, expect );
    NMTOOLS_ASSERT_CLOSE( function (a), array );
}

namespace kwargs = nmtools::args;
namespace fun = view::fun;



#ifdef NMTOOLS_TESTING_KWARGS_INIT
#ifndef __clang__

TEST_CASE("leaky_relu" * doctest::test_suite("functional::get_function_composition"))
{
    NMTOOLS_TESTING_USE_CASE(activations,leaky_relu,case1);
    using namespace args;

    auto array = view::leaky_relu(a,{.negative_slope=0.01});

    auto function = fn::get_function_composition(array);
    auto expect = fn::unary_ufunc[array.attributes()];

    NMTOOLS_ASSERT_EQUAL( function, expect );
    NMTOOLS_ASSERT_CLOSE( function (a), array );
}

#endif
#endif