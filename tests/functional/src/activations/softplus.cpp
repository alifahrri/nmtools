#include "nmtools/array/softplus.hpp"
#include "nmtools/testing/data/array/softplus.hpp"
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

TEST_CASE("softplus(case1)" * doctest::test_suite("functional::softplus"))
{
    NMTOOLS_TESTING_USE_CASE(activations,softplus,case1);
    using namespace args;

    ACTIVATIONS_SUBCASE( "case1", fn::softplus, a );
    ACTIVATIONS_SUBCASE( "case1", fn::softplus, a_a );
    ACTIVATIONS_SUBCASE( "case1", fn::softplus, a_f );
    ACTIVATIONS_SUBCASE( "case1", fn::softplus, a_h );
    ACTIVATIONS_SUBCASE( "case1", fn::softplus, a_d );
}

namespace view = nmtools::view;

TEST_CASE("softplus" * doctest::test_suite("functional::get_function_composition"))
{
    NMTOOLS_TESTING_USE_CASE(activations,softplus,case1);
    using namespace args;

    auto array = view::softplus(a);

    auto function = fn::get_function_composition(array);
    // TODO: make comparison fn::unary_ufunc[fun::softplus()][...] == fn::softplus[...]
    auto expect = fn::softplus[1.][20.];

    NMTOOLS_ASSERT_EQUAL( function, expect );
    NMTOOLS_ASSERT_CLOSE( function (a), array );
}

TEST_CASE("softplus" * doctest::test_suite("functional::get_function_composition"))
{
    NMTOOLS_TESTING_USE_CASE(activations,softplus,case1);
    using namespace args;

    auto array = view::softplus(a);

    auto function = fn::get_function_composition(array);
    auto expect = fn::unary_ufunc[array.attributes()];

    NMTOOLS_ASSERT_EQUAL( function, expect );
    NMTOOLS_ASSERT_CLOSE( function (a), array );
}

namespace kwargs = nmtools::args;
namespace fun = view::fun;



#ifdef NMTOOLS_TESTING_KWARGS_INIT
#ifndef __clang__

TEST_CASE("softplus" * doctest::test_suite("functional::get_function_composition"))
{
    NMTOOLS_TESTING_USE_CASE(activations,softplus,case1);
    using namespace args;

    auto array = view::softplus(a,{.beta=1.,.threshold=20.});

    auto function = fn::get_function_composition(array);
    auto expect = fn::unary_ufunc[array.attributes()];

    NMTOOLS_ASSERT_EQUAL( function, expect );
    NMTOOLS_ASSERT_CLOSE( function (a), array );
}

#endif
#endif