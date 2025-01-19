#include "nmtools/array/activations/hardtanh.hpp"
#include "nmtools/testing/data/array/hardtanh.hpp"
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

TEST_CASE("hardtanh(case1)" * doctest::test_suite("functional::hardtanh"))
{
    NMTOOLS_TESTING_USE_CASE(activations,hardtanh,case1);
    using namespace args;

    ACTIVATIONS_SUBCASE( "case1", fn::hardtanh, a );
    ACTIVATIONS_SUBCASE( "case1", fn::hardtanh, a_a );
    ACTIVATIONS_SUBCASE( "case1", fn::hardtanh, a_f );
    ACTIVATIONS_SUBCASE( "case1", fn::hardtanh, a_h );
    ACTIVATIONS_SUBCASE( "case1", fn::hardtanh, a_d );
}

namespace view = nmtools::view;

TEST_CASE("hardtanh" * doctest::test_suite("functional::get_function_composition"))
{
    NMTOOLS_TESTING_USE_CASE(activations,hardtanh,case1);
    using namespace args;

    auto array = view::hardtanh(a);

    auto function = fn::get_function_composition(array);
    auto expect = fn::hardtanh[-1.][1.];

    NMTOOLS_ASSERT_EQUAL( function, expect );
    NMTOOLS_ASSERT_CLOSE( function (a), array );
}

TEST_CASE("hardtanh" * doctest::test_suite("functional::get_function_composition"))
{
    NMTOOLS_TESTING_USE_CASE(activations,hardtanh,case1);
    using namespace args;

    auto array = view::hardtanh(a);

    auto function = fn::get_function_composition(array);
    auto expect = fn::unary_ufunc[array.attributes()];

    NMTOOLS_ASSERT_EQUAL( function, expect );
    NMTOOLS_ASSERT_CLOSE( function (a), array );
}

namespace kwargs = nmtools::args;
namespace fun = view::fun;



#ifdef NMTOOLS_TESTING_KWARGS_INIT
#ifndef __clang__

TEST_CASE("hardtanh" * doctest::test_suite("functional::get_function_composition"))
{
    NMTOOLS_TESTING_USE_CASE(activations,hardtanh,case1);
    using namespace args;

    auto array = view::hardtanh(a,{.min_val=-1.,.max_val=1.});

    auto function = fn::get_function_composition(array);
    auto expect = fn::unary_ufunc[array.attributes()];

    NMTOOLS_ASSERT_EQUAL( function, expect );
    NMTOOLS_ASSERT_CLOSE( function (a), array );
}

#endif
#endif