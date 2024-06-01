#include "nmtools/array/functional/activations/hardshrink.hpp"
#include "nmtools/testing/data/array/hardshrink.hpp"
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

TEST_CASE("hardshrink(case1)" * doctest::test_suite("functional::hardshrink"))
{
    NMTOOLS_TESTING_USE_CASE(activations,hardshrink,case1);
    using namespace args;

    ACTIVATIONS_SUBCASE( "case1", fn::hardshrink, a );
    ACTIVATIONS_SUBCASE( "case1", fn::hardshrink, a_a );
    ACTIVATIONS_SUBCASE( "case1", fn::hardshrink, a_f );
    ACTIVATIONS_SUBCASE( "case1", fn::hardshrink, a_h );
    ACTIVATIONS_SUBCASE( "case1", fn::hardshrink, a_d );
}

TEST_CASE("hardshrink(case2)" * doctest::test_suite("functional::hardshrink"))
{
    NMTOOLS_TESTING_USE_CASE(activations,hardshrink,case2);
    using namespace args;

    ACTIVATIONS_SUBCASE( "case2", fn::hardshrink[lambda], a );
    ACTIVATIONS_SUBCASE( "case2", fn::hardshrink[lambda], a_a );
    ACTIVATIONS_SUBCASE( "case2", fn::hardshrink[lambda], a_f );
    ACTIVATIONS_SUBCASE( "case2", fn::hardshrink[lambda], a_h );
    ACTIVATIONS_SUBCASE( "case2", fn::hardshrink[lambda], a_d );
}

namespace view = nmtools::view;

TEST_CASE("hardshrink" * doctest::test_suite("functional::get_function_composition"))
{
    NMTOOLS_TESTING_USE_CASE(activations,hardshrink,case2);
    using namespace args;

    auto array = view::hardshrink(a,lambda);

    auto function = fn::get_function_composition(array);
    auto expect = fn::hardshrink[lambda];

    NMTOOLS_ASSERT_EQUAL( function, expect );
    NMTOOLS_ASSERT_CLOSE( function (a), array );
}

TEST_CASE("hardshrink" * doctest::test_suite("functional::get_function_composition"))
{
    NMTOOLS_TESTING_USE_CASE(activations,hardshrink,case2);
    using namespace args;

    auto array = view::hardshrink(a,lambda);

    auto function = fn::get_function_composition(array);
    auto expect = fn::unary_ufunc[array.attributes()];

    NMTOOLS_ASSERT_EQUAL( function, expect );
    NMTOOLS_ASSERT_CLOSE( function (a), array );
}

namespace kwargs = nmtools::args;
namespace fun = view::fun;



#ifdef NMTOOLS_TESTING_KWARGS_INIT
#ifndef __clang__

TEST_CASE("hardshrink" * doctest::test_suite("functional::get_function_composition"))
{
    NMTOOLS_TESTING_USE_CASE(activations,hardshrink,case2);
    using namespace args;

    auto array = view::hardshrink(a,{.lambda=lambda});

    auto function = fn::get_function_composition(array);
    auto expect = fn::unary_ufunc[kwargs::ufunc{
        .op=fun::hardshrink{.lambda=lambda}
    }];
    // TODO: make the following expression accepted
    // auto expect = fn::unary_ufunc[{
    //     .op=fun::hardshrink{.lambda=lambda}
    // }];

    NMTOOLS_ASSERT_EQUAL( function, expect );
    NMTOOLS_ASSERT_CLOSE( function (a), array );
}

#endif // __clang__
#endif // NMTOOLS_TESTING_KWARGS_INIT