#include "nmtools/array/functional/activations/prelu.hpp"
#include "nmtools/testing/data/array/prelu.hpp"
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

TEST_CASE("prelu(case1)" * doctest::test_suite("functional::prelu"))
{
    NMTOOLS_TESTING_DECLARE_NS(activations,prelu,case1);
    using namespace args;

    ACTIVATIONS_SUBCASE( "case1", fn::prelu, a );
    ACTIVATIONS_SUBCASE( "case1", fn::prelu, a_a );
    ACTIVATIONS_SUBCASE( "case1", fn::prelu, a_f );
    ACTIVATIONS_SUBCASE( "case1", fn::prelu, a_h );
    ACTIVATIONS_SUBCASE( "case1", fn::prelu, a_d );
}

namespace view = nmtools::view;

TEST_CASE("prelu" * doctest::test_suite("functional::get_function_composition"))
{
    NMTOOLS_TESTING_DECLARE_NS(activations,prelu,case1);
    using namespace args;

    auto array = view::prelu(a);

    auto function = fn::get_function_composition(array);
    auto expect = fn::prelu[0.25];

    NMTOOLS_ASSERT_EQUAL( function, expect );
    NMTOOLS_ASSERT_CLOSE( function (a), array );
}

TEST_CASE("prelu" * doctest::test_suite("functional::get_function_composition"))
{
    NMTOOLS_TESTING_DECLARE_NS(activations,prelu,case1);
    using namespace args;

    auto array = view::prelu(a);

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

TEST_CASE("prelu" * doctest::test_suite("functional::get_function_composition"))
{
    NMTOOLS_TESTING_DECLARE_NS(activations,prelu,case1);
    using namespace args;

    auto array = view::prelu(a,{.alpha=0.25});

    auto function = fn::get_function_composition(array);
    auto expect = fn::unary_ufunc[array.attributes()];

    NMTOOLS_ASSERT_EQUAL( function, expect );
    NMTOOLS_ASSERT_CLOSE( function (a), array );
}

#endif
#endif