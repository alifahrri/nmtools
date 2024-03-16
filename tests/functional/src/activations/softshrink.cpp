#include "nmtools/array/functional/activations/softshrink.hpp"
#include "nmtools/testing/data/array/softshrink.hpp"
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

TEST_CASE("softshrink(case1)" * doctest::test_suite("functional::softshrink"))
{
    NMTOOLS_TESTING_DECLARE_NS(activations,softshrink,case1);
    using namespace args;

    ACTIVATIONS_SUBCASE( "case1", fn::softshrink, a );
    ACTIVATIONS_SUBCASE( "case1", fn::softshrink, a_a );
    ACTIVATIONS_SUBCASE( "case1", fn::softshrink, a_f );
    ACTIVATIONS_SUBCASE( "case1", fn::softshrink, a_h );
    ACTIVATIONS_SUBCASE( "case1", fn::softshrink, a_d );
}

namespace view = nmtools::view;

TEST_CASE("softshrink" * doctest::test_suite("functional::get_function_composition"))
{
    NMTOOLS_TESTING_DECLARE_NS(activations,softshrink,case1);
    using namespace args;

    auto array = view::softshrink(a);

    auto function = fn::get_function_composition(array);
    auto expect = fn::softshrink[0.5];

    NMTOOLS_ASSERT_EQUAL( function, expect );
    NMTOOLS_ASSERT_CLOSE( function (a), array );
}

TEST_CASE("softshrink" * doctest::test_suite("functional::get_function_composition"))
{
    NMTOOLS_TESTING_DECLARE_NS(activations,softshrink,case1);
    using namespace args;

    auto array = view::softshrink(a);

    auto function = fn::get_function_composition(array);
    auto expect = fn::unary_ufunc[array.attributes()];

    NMTOOLS_ASSERT_EQUAL( function, expect );
    NMTOOLS_ASSERT_CLOSE( function (a), array );
}

namespace kwargs = nmtools::args;
namespace fun = view::fun;

#define NMTOOLS_TESTING_KWARGS_INIT

#ifdef NMTOOLS_TESTING_KWARGS_INIT
#ifndef __clang__

TEST_CASE("softshrink" * doctest::test_suite("functional::get_function_composition"))
{
    NMTOOLS_TESTING_DECLARE_NS(activations,softshrink,case1);
    using namespace args;

    // NOTE: the following lambda deduced as double
    // auto array = view::softshrink(a,fun::softshrink{.lambda=double(0.5)});
    // NOTE: while the following lambda deduced as float
    // auto array = view::softshrink(a,{.lambda=double(0.5)});
    auto array = view::softshrink(a,{.lambda=0.5});

    auto function = fn::get_function_composition(array);
    // auto expect = fn::unary_ufunc[array.attributes()];
    auto expect = fn::unary_ufunc[kwargs::ufunc{
        .op=fun::softshrink{.lambda=0.5}
    }];

    // static_assert( std::is_same_v<const double,decltype(array.op.lambda)> );
    static_assert( std::is_same_v<const float,decltype(array.op.lambda)> );

    NMTOOLS_ASSERT_EQUAL( function, expect );
    NMTOOLS_ASSERT_CLOSE( function (a), array );
}

#endif // __clang__
#endif // NMTOOLS_TESTING_KWARGS_INIT