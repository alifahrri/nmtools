#include "nmtools/array/activations/elu.hpp"
#include "nmtools/testing/data/array/elu.hpp"
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

TEST_CASE("elu(case1)" * doctest::test_suite("functional::elu"))
{
    NMTOOLS_TESTING_USE_CASE(activations,elu,case1);
    using namespace args;

    ACTIVATIONS_SUBCASE( "case1", fn::elu, a );
    ACTIVATIONS_SUBCASE( "case1", fn::elu, a_a );
    ACTIVATIONS_SUBCASE( "case1", fn::elu, a_f );
    ACTIVATIONS_SUBCASE( "case1", fn::elu, a_h );
    ACTIVATIONS_SUBCASE( "case1", fn::elu, a_d );
}

TEST_CASE("elu(case2)" * doctest::test_suite("functional::elu"))
{
    NMTOOLS_TESTING_USE_CASE(activations,elu,case2);
    using namespace args;

    ACTIVATIONS_SUBCASE( "case2", fn::elu[alpha], a );
    ACTIVATIONS_SUBCASE( "case2", fn::elu[alpha], a_a );
    ACTIVATIONS_SUBCASE( "case2", fn::elu[alpha], a_f );
    ACTIVATIONS_SUBCASE( "case2", fn::elu[alpha], a_h );
    ACTIVATIONS_SUBCASE( "case2", fn::elu[alpha], a_d );
}

namespace view = nmtools::view;

namespace kwargs = nmtools::args;
namespace fun = view::fun;

TEST_CASE("elu" * doctest::test_suite("functional::get_function_composition"))
{
    NMTOOLS_TESTING_USE_CASE(activations,elu,case2);
    using namespace args;

    auto array = view::elu(a);

    auto function = fn::get_function_composition(array);
    auto expect = fn::elu;

    NMTOOLS_ASSERT_EQUAL( function, expect );
    NMTOOLS_ASSERT_CLOSE( function (a), array );
    NMTOOLS_ASSERT_CLOSE( expect (a), array );
}

TEST_CASE("elu" * doctest::test_suite("functional::get_function_composition"))
{
    NMTOOLS_TESTING_USE_CASE(activations,elu,case2);
    using namespace args;

    auto array = view::elu(a,alpha);

    auto function = fn::get_function_composition(array);
    auto expect = fn::elu[alpha];

    NMTOOLS_ASSERT_EQUAL( function, expect );
    NMTOOLS_ASSERT_CLOSE( function (a), array );
    NMTOOLS_ASSERT_CLOSE( expect (a), array );
}

TEST_CASE("elu" * doctest::test_suite("functional::get_function_composition"))
{
    NMTOOLS_TESTING_USE_CASE(activations,elu,case2);
    using namespace args;

    auto array = view::elu(a,alpha);

    auto function = fn::get_function_composition(array);
    auto expect = fn::unary_ufunc[array.attributes()];

    NMTOOLS_ASSERT_EQUAL( function, expect );
    NMTOOLS_ASSERT_CLOSE( function (a), array );
    NMTOOLS_ASSERT_CLOSE( expect (a), array );
}

#ifdef NMTOOLS_TESTING_KWARGS_INIT
#ifndef __clang__

TEST_CASE("elu" * doctest::test_suite("functional::get_function_composition"))
{
    NMTOOLS_TESTING_USE_CASE(activations,elu,case2);
    using namespace args;

    auto array = view::elu(a,{.alpha=alpha});

    auto function = fn::get_function_composition(array);
    auto expect = fn::unary_ufunc[kwargs::ufunc{
        .op=fun::elu{.alpha=alpha}
    }];

    NMTOOLS_ASSERT_EQUAL( function, expect );
    NMTOOLS_ASSERT_CLOSE( function (a), array );
    NMTOOLS_ASSERT_CLOSE( expect (a), array );

    NMTOOLS_ASSERT_NOT_EQUAL( fn::elu[1.f], fn::elu[0.1f] );
    NMTOOLS_ASSERT_NOT_EQUAL( fn::unary_ufunc[kwargs::ufunc{fun::elu{1.f}}], fn::elu[0.1f] );
    NMTOOLS_ASSERT_NOT_EQUAL( fn::elu[0.1f], fn::unary_ufunc[kwargs::ufunc{fun::elu{1.f}}] );
    NMTOOLS_ASSERT_NOT_EQUAL( fn::elu, fn::unary_ufunc[kwargs::ufunc{fun::elu{0.1f}}] );

    NMTOOLS_ASSERT_EQUAL( fn::elu, fn::unary_ufunc[kwargs::ufunc{fun::elu{}}] );
    NMTOOLS_ASSERT_EQUAL( fn::elu[0.1f], fn::unary_ufunc[kwargs::ufunc{fun::elu{}}][0.1f] );
    // NMTOOLS_ASSERT_EQUAL( fn::elu, fn::unary_ufunc[kwargs::ufunc{}][fun::elu{}] );
}

TEST_CASE("elu" * doctest::test_suite("functional::get_function_composition"))
{
    NMTOOLS_TESTING_USE_CASE(activations,elu,case2);
    using namespace args;

    auto array = view::elu(a,{.alpha=0.1f});

    auto function = fn::get_function_composition(array);
    auto expect = fn::unary_ufunc[kwargs::ufunc{
        .op=fun::elu{.alpha=0.1f}
    }];

    NMTOOLS_ASSERT_EQUAL( function, expect );
    NMTOOLS_ASSERT_CLOSE( function (a), array );
    NMTOOLS_ASSERT_CLOSE( expect (a), array );
}

TEST_CASE("elu" * doctest::test_suite("functional::get_function_composition"))
{
    NMTOOLS_TESTING_USE_CASE(activations,elu,case2);
    using namespace args;

    auto array = view::elu(a,{.alpha=0.1f});

    auto function = fn::get_function_composition(array);
    auto expect   = fn::elu[0.1f];
    // auto expect = fn::elu[kwargs::ufunc{
    //     .op=fun::elu{.alpha=0.1f}
    // }];

    NMTOOLS_ASSERT_EQUAL( function, expect );
    NMTOOLS_ASSERT_CLOSE( function (a), array );
    NMTOOLS_ASSERT_CLOSE( expect (a), array );
}

TEST_CASE("elu" * doctest::test_suite("functional::get_function_composition"))
{
    NMTOOLS_TESTING_USE_CASE(activations,elu,case2);
    using namespace args;

    auto array = view::elu(a,{.alpha=0.1f});

    auto function = fn::get_function_composition(array);
    auto expect = fn::elu[0.1f];

    NMTOOLS_ASSERT_EQUAL( function, expect );
    NMTOOLS_ASSERT_CLOSE( function (a), array );
    NMTOOLS_ASSERT_CLOSE( expect (a), array );
}

#endif // __clang__
#endif // NMTOOLS_TESTING_KWARGS_INIT